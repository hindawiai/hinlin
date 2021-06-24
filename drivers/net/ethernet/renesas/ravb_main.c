<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Renesas Ethernet AVB device driver
 *
 * Copyright (C) 2014-2019 Renesas Electronics Corporation
 * Copyright (C) 2015 Renesas Solutions Corp.
 * Copyright (C) 2015-2016 Cogent Embedded, Inc. <source@cogentembedded.com>
 *
 * Based on the SuperH Ethernet driver
 */

#समावेश <linux/cache.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sys_soc.h>

#समावेश <यंत्र/भाग64.h>

#समावेश "ravb.h"

#घोषणा RAVB_DEF_MSG_ENABLE \
		(NETIF_MSG_LINK	  | \
		 NETIF_MSG_TIMER  | \
		 NETIF_MSG_RX_ERR | \
		 NETIF_MSG_TX_ERR)

अटल स्थिर अक्षर *ravb_rx_irqs[NUM_RX_QUEUE] = अणु
	"ch0", /* RAVB_BE */
	"ch1", /* RAVB_NC */
पूर्ण;

अटल स्थिर अक्षर *ravb_tx_irqs[NUM_TX_QUEUE] = अणु
	"ch18", /* RAVB_BE */
	"ch19", /* RAVB_NC */
पूर्ण;

व्योम ravb_modअगरy(काष्ठा net_device *ndev, क्रमागत ravb_reg reg, u32 clear,
		 u32 set)
अणु
	ravb_ग_लिखो(ndev, (ravb_पढ़ो(ndev, reg) & ~clear) | set, reg);
पूर्ण

पूर्णांक ravb_रुको(काष्ठा net_device *ndev, क्रमागत ravb_reg reg, u32 mask, u32 value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10000; i++) अणु
		अगर ((ravb_पढ़ो(ndev, reg) & mask) == value)
			वापस 0;
		udelay(10);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ravb_config(काष्ठा net_device *ndev)
अणु
	पूर्णांक error;

	/* Set config mode */
	ravb_modअगरy(ndev, CCC, CCC_OPC, CCC_OPC_CONFIG);
	/* Check अगर the operating mode is changed to the config mode */
	error = ravb_रुको(ndev, CSR, CSR_OPS, CSR_OPS_CONFIG);
	अगर (error)
		netdev_err(ndev, "failed to switch device to config mode\n");

	वापस error;
पूर्ण

अटल व्योम ravb_set_rate(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	चयन (priv->speed) अणु
	हाल 100:		/* 100BASE */
		ravb_ग_लिखो(ndev, GECMR_SPEED_100, GECMR);
		अवरोध;
	हाल 1000:		/* 1000BASE */
		ravb_ग_लिखो(ndev, GECMR_SPEED_1000, GECMR);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ravb_set_buffer_align(काष्ठा sk_buff *skb)
अणु
	u32 reserve = (अचिन्हित दीर्घ)skb->data & (RAVB_ALIGN - 1);

	अगर (reserve)
		skb_reserve(skb, RAVB_ALIGN - reserve);
पूर्ण

/* Get MAC address from the MAC address रेजिस्टरs
 *
 * Ethernet AVB device करोesn't have ROM क्रम MAC address.
 * This function माला_लो the MAC address that was used by a bootloader.
 */
अटल व्योम ravb_पढ़ो_mac_address(काष्ठा device_node *np,
				  काष्ठा net_device *ndev)
अणु
	पूर्णांक ret;

	ret = of_get_mac_address(np, ndev->dev_addr);
	अगर (ret) अणु
		u32 mahr = ravb_पढ़ो(ndev, MAHR);
		u32 malr = ravb_पढ़ो(ndev, MALR);

		ndev->dev_addr[0] = (mahr >> 24) & 0xFF;
		ndev->dev_addr[1] = (mahr >> 16) & 0xFF;
		ndev->dev_addr[2] = (mahr >>  8) & 0xFF;
		ndev->dev_addr[3] = (mahr >>  0) & 0xFF;
		ndev->dev_addr[4] = (malr >>  8) & 0xFF;
		ndev->dev_addr[5] = (malr >>  0) & 0xFF;
	पूर्ण
पूर्ण

अटल व्योम ravb_mdio_ctrl(काष्ठा mdiobb_ctrl *ctrl, u32 mask, पूर्णांक set)
अणु
	काष्ठा ravb_निजी *priv = container_of(ctrl, काष्ठा ravb_निजी,
						 mdiobb);

	ravb_modअगरy(priv->ndev, PIR, mask, set ? mask : 0);
पूर्ण

/* MDC pin control */
अटल व्योम ravb_set_mdc(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक level)
अणु
	ravb_mdio_ctrl(ctrl, PIR_MDC, level);
पूर्ण

/* Data I/O pin control */
अटल व्योम ravb_set_mdio_dir(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक output)
अणु
	ravb_mdio_ctrl(ctrl, PIR_MMD, output);
पूर्ण

/* Set data bit */
अटल व्योम ravb_set_mdio_data(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक value)
अणु
	ravb_mdio_ctrl(ctrl, PIR_MDO, value);
पूर्ण

/* Get data bit */
अटल पूर्णांक ravb_get_mdio_data(काष्ठा mdiobb_ctrl *ctrl)
अणु
	काष्ठा ravb_निजी *priv = container_of(ctrl, काष्ठा ravb_निजी,
						 mdiobb);

	वापस (ravb_पढ़ो(priv->ndev, PIR) & PIR_MDI) != 0;
पूर्ण

/* MDIO bus control काष्ठा */
अटल स्थिर काष्ठा mdiobb_ops bb_ops = अणु
	.owner = THIS_MODULE,
	.set_mdc = ravb_set_mdc,
	.set_mdio_dir = ravb_set_mdio_dir,
	.set_mdio_data = ravb_set_mdio_data,
	.get_mdio_data = ravb_get_mdio_data,
पूर्ण;

/* Free TX skb function क्रम AVB-IP */
अटल पूर्णांक ravb_tx_मुक्त(काष्ठा net_device *ndev, पूर्णांक q, bool मुक्त_txed_only)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &priv->stats[q];
	पूर्णांक num_tx_desc = priv->num_tx_desc;
	काष्ठा ravb_tx_desc *desc;
	पूर्णांक मुक्त_num = 0;
	पूर्णांक entry;
	u32 size;

	क्रम (; priv->cur_tx[q] - priv->dirty_tx[q] > 0; priv->dirty_tx[q]++) अणु
		bool txed;

		entry = priv->dirty_tx[q] % (priv->num_tx_ring[q] *
					     num_tx_desc);
		desc = &priv->tx_ring[q][entry];
		txed = desc->die_dt == DT_FEMPTY;
		अगर (मुक्त_txed_only && !txed)
			अवरोध;
		/* Descriptor type must be checked beक्रमe all other पढ़ोs */
		dma_rmb();
		size = le16_to_cpu(desc->ds_tagl) & TX_DS;
		/* Free the original skb. */
		अगर (priv->tx_skb[q][entry / num_tx_desc]) अणु
			dma_unmap_single(ndev->dev.parent, le32_to_cpu(desc->dptr),
					 size, DMA_TO_DEVICE);
			/* Last packet descriptor? */
			अगर (entry % num_tx_desc == num_tx_desc - 1) अणु
				entry /= num_tx_desc;
				dev_kमुक्त_skb_any(priv->tx_skb[q][entry]);
				priv->tx_skb[q][entry] = शून्य;
				अगर (txed)
					stats->tx_packets++;
			पूर्ण
			मुक्त_num++;
		पूर्ण
		अगर (txed)
			stats->tx_bytes += size;
		desc->die_dt = DT_EEMPTY;
	पूर्ण
	वापस मुक्त_num;
पूर्ण

/* Free skb's and DMA buffers क्रम Ethernet AVB */
अटल व्योम ravb_ring_मुक्त(काष्ठा net_device *ndev, पूर्णांक q)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक num_tx_desc = priv->num_tx_desc;
	पूर्णांक ring_size;
	पूर्णांक i;

	अगर (priv->rx_ring[q]) अणु
		क्रम (i = 0; i < priv->num_rx_ring[q]; i++) अणु
			काष्ठा ravb_ex_rx_desc *desc = &priv->rx_ring[q][i];

			अगर (!dma_mapping_error(ndev->dev.parent,
					       le32_to_cpu(desc->dptr)))
				dma_unmap_single(ndev->dev.parent,
						 le32_to_cpu(desc->dptr),
						 RX_BUF_SZ,
						 DMA_FROM_DEVICE);
		पूर्ण
		ring_size = माप(काष्ठा ravb_ex_rx_desc) *
			    (priv->num_rx_ring[q] + 1);
		dma_मुक्त_coherent(ndev->dev.parent, ring_size, priv->rx_ring[q],
				  priv->rx_desc_dma[q]);
		priv->rx_ring[q] = शून्य;
	पूर्ण

	अगर (priv->tx_ring[q]) अणु
		ravb_tx_मुक्त(ndev, q, false);

		ring_size = माप(काष्ठा ravb_tx_desc) *
			    (priv->num_tx_ring[q] * num_tx_desc + 1);
		dma_मुक्त_coherent(ndev->dev.parent, ring_size, priv->tx_ring[q],
				  priv->tx_desc_dma[q]);
		priv->tx_ring[q] = शून्य;
	पूर्ण

	/* Free RX skb ringbuffer */
	अगर (priv->rx_skb[q]) अणु
		क्रम (i = 0; i < priv->num_rx_ring[q]; i++)
			dev_kमुक्त_skb(priv->rx_skb[q][i]);
	पूर्ण
	kमुक्त(priv->rx_skb[q]);
	priv->rx_skb[q] = शून्य;

	/* Free aligned TX buffers */
	kमुक्त(priv->tx_align[q]);
	priv->tx_align[q] = शून्य;

	/* Free TX skb ringbuffer.
	 * SKBs are मुक्तd by ravb_tx_मुक्त() call above.
	 */
	kमुक्त(priv->tx_skb[q]);
	priv->tx_skb[q] = शून्य;
पूर्ण

/* Format skb and descriptor buffer क्रम Ethernet AVB */
अटल व्योम ravb_ring_क्रमmat(काष्ठा net_device *ndev, पूर्णांक q)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक num_tx_desc = priv->num_tx_desc;
	काष्ठा ravb_ex_rx_desc *rx_desc;
	काष्ठा ravb_tx_desc *tx_desc;
	काष्ठा ravb_desc *desc;
	पूर्णांक rx_ring_size = माप(*rx_desc) * priv->num_rx_ring[q];
	पूर्णांक tx_ring_size = माप(*tx_desc) * priv->num_tx_ring[q] *
			   num_tx_desc;
	dma_addr_t dma_addr;
	पूर्णांक i;

	priv->cur_rx[q] = 0;
	priv->cur_tx[q] = 0;
	priv->dirty_rx[q] = 0;
	priv->dirty_tx[q] = 0;

	स_रखो(priv->rx_ring[q], 0, rx_ring_size);
	/* Build RX ring buffer */
	क्रम (i = 0; i < priv->num_rx_ring[q]; i++) अणु
		/* RX descriptor */
		rx_desc = &priv->rx_ring[q][i];
		rx_desc->ds_cc = cpu_to_le16(RX_BUF_SZ);
		dma_addr = dma_map_single(ndev->dev.parent, priv->rx_skb[q][i]->data,
					  RX_BUF_SZ,
					  DMA_FROM_DEVICE);
		/* We just set the data size to 0 क्रम a failed mapping which
		 * should prevent DMA from happening...
		 */
		अगर (dma_mapping_error(ndev->dev.parent, dma_addr))
			rx_desc->ds_cc = cpu_to_le16(0);
		rx_desc->dptr = cpu_to_le32(dma_addr);
		rx_desc->die_dt = DT_FEMPTY;
	पूर्ण
	rx_desc = &priv->rx_ring[q][i];
	rx_desc->dptr = cpu_to_le32((u32)priv->rx_desc_dma[q]);
	rx_desc->die_dt = DT_LINKFIX; /* type */

	स_रखो(priv->tx_ring[q], 0, tx_ring_size);
	/* Build TX ring buffer */
	क्रम (i = 0, tx_desc = priv->tx_ring[q]; i < priv->num_tx_ring[q];
	     i++, tx_desc++) अणु
		tx_desc->die_dt = DT_EEMPTY;
		अगर (num_tx_desc > 1) अणु
			tx_desc++;
			tx_desc->die_dt = DT_EEMPTY;
		पूर्ण
	पूर्ण
	tx_desc->dptr = cpu_to_le32((u32)priv->tx_desc_dma[q]);
	tx_desc->die_dt = DT_LINKFIX; /* type */

	/* RX descriptor base address क्रम best efक्रमt */
	desc = &priv->desc_bat[RX_QUEUE_OFFSET + q];
	desc->die_dt = DT_LINKFIX; /* type */
	desc->dptr = cpu_to_le32((u32)priv->rx_desc_dma[q]);

	/* TX descriptor base address क्रम best efक्रमt */
	desc = &priv->desc_bat[q];
	desc->die_dt = DT_LINKFIX; /* type */
	desc->dptr = cpu_to_le32((u32)priv->tx_desc_dma[q]);
पूर्ण

/* Init skb and descriptor buffer क्रम Ethernet AVB */
अटल पूर्णांक ravb_ring_init(काष्ठा net_device *ndev, पूर्णांक q)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक num_tx_desc = priv->num_tx_desc;
	काष्ठा sk_buff *skb;
	पूर्णांक ring_size;
	पूर्णांक i;

	/* Allocate RX and TX skb rings */
	priv->rx_skb[q] = kसुस्मृति(priv->num_rx_ring[q],
				  माप(*priv->rx_skb[q]), GFP_KERNEL);
	priv->tx_skb[q] = kसुस्मृति(priv->num_tx_ring[q],
				  माप(*priv->tx_skb[q]), GFP_KERNEL);
	अगर (!priv->rx_skb[q] || !priv->tx_skb[q])
		जाओ error;

	क्रम (i = 0; i < priv->num_rx_ring[q]; i++) अणु
		skb = netdev_alloc_skb(ndev, RX_BUF_SZ + RAVB_ALIGN - 1);
		अगर (!skb)
			जाओ error;
		ravb_set_buffer_align(skb);
		priv->rx_skb[q][i] = skb;
	पूर्ण

	अगर (num_tx_desc > 1) अणु
		/* Allocate rings क्रम the aligned buffers */
		priv->tx_align[q] = kदो_स्मृति(DPTR_ALIGN * priv->num_tx_ring[q] +
					    DPTR_ALIGN - 1, GFP_KERNEL);
		अगर (!priv->tx_align[q])
			जाओ error;
	पूर्ण

	/* Allocate all RX descriptors. */
	ring_size = माप(काष्ठा ravb_ex_rx_desc) * (priv->num_rx_ring[q] + 1);
	priv->rx_ring[q] = dma_alloc_coherent(ndev->dev.parent, ring_size,
					      &priv->rx_desc_dma[q],
					      GFP_KERNEL);
	अगर (!priv->rx_ring[q])
		जाओ error;

	priv->dirty_rx[q] = 0;

	/* Allocate all TX descriptors. */
	ring_size = माप(काष्ठा ravb_tx_desc) *
		    (priv->num_tx_ring[q] * num_tx_desc + 1);
	priv->tx_ring[q] = dma_alloc_coherent(ndev->dev.parent, ring_size,
					      &priv->tx_desc_dma[q],
					      GFP_KERNEL);
	अगर (!priv->tx_ring[q])
		जाओ error;

	वापस 0;

error:
	ravb_ring_मुक्त(ndev, q);

	वापस -ENOMEM;
पूर्ण

/* E-MAC init function */
अटल व्योम ravb_emac_init(काष्ठा net_device *ndev)
अणु
	/* Receive frame limit set रेजिस्टर */
	ravb_ग_लिखो(ndev, ndev->mtu + ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN, RFLR);

	/* EMAC Mode: PAUSE prohibition; Duplex; RX Checksum; TX; RX */
	ravb_ग_लिखो(ndev, ECMR_ZPF | ECMR_DM |
		   (ndev->features & NETIF_F_RXCSUM ? ECMR_RCSC : 0) |
		   ECMR_TE | ECMR_RE, ECMR);

	ravb_set_rate(ndev);

	/* Set MAC address */
	ravb_ग_लिखो(ndev,
		   (ndev->dev_addr[0] << 24) | (ndev->dev_addr[1] << 16) |
		   (ndev->dev_addr[2] << 8)  | (ndev->dev_addr[3]), MAHR);
	ravb_ग_लिखो(ndev,
		   (ndev->dev_addr[4] << 8)  | (ndev->dev_addr[5]), MALR);

	/* E-MAC status रेजिस्टर clear */
	ravb_ग_लिखो(ndev, ECSR_ICD | ECSR_MPD, ECSR);

	/* E-MAC पूर्णांकerrupt enable रेजिस्टर */
	ravb_ग_लिखो(ndev, ECSIPR_ICDIP | ECSIPR_MPDIP | ECSIPR_LCHNGIP, ECSIPR);
पूर्ण

/* Device init function क्रम Ethernet AVB */
अटल पूर्णांक ravb_dmac_init(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक error;

	/* Set CONFIG mode */
	error = ravb_config(ndev);
	अगर (error)
		वापस error;

	error = ravb_ring_init(ndev, RAVB_BE);
	अगर (error)
		वापस error;
	error = ravb_ring_init(ndev, RAVB_NC);
	अगर (error) अणु
		ravb_ring_मुक्त(ndev, RAVB_BE);
		वापस error;
	पूर्ण

	/* Descriptor क्रमmat */
	ravb_ring_क्रमmat(ndev, RAVB_BE);
	ravb_ring_क्रमmat(ndev, RAVB_NC);

	/* Set AVB RX */
	ravb_ग_लिखो(ndev,
		   RCR_EFFS | RCR_ENCF | RCR_ETS0 | RCR_ESF | 0x18000000, RCR);

	/* Set FIFO size */
	ravb_ग_लिखो(ndev, TGC_TQP_AVBMODE1 | 0x00112200, TGC);

	/* Timestamp enable */
	ravb_ग_लिखो(ndev, TCCR_TFEN, TCCR);

	/* Interrupt init: */
	अगर (priv->chip_id == RCAR_GEN3) अणु
		/* Clear DIL.DPLx */
		ravb_ग_लिखो(ndev, 0, DIL);
		/* Set queue specअगरic पूर्णांकerrupt */
		ravb_ग_लिखो(ndev, CIE_CRIE | CIE_CTIE | CIE_CL0M, CIE);
	पूर्ण
	/* Frame receive */
	ravb_ग_लिखो(ndev, RIC0_FRE0 | RIC0_FRE1, RIC0);
	/* Disable FIFO full warning */
	ravb_ग_लिखो(ndev, 0, RIC1);
	/* Receive FIFO full error, descriptor empty */
	ravb_ग_लिखो(ndev, RIC2_QFE0 | RIC2_QFE1 | RIC2_RFFE, RIC2);
	/* Frame transmitted, बारtamp FIFO updated */
	ravb_ग_लिखो(ndev, TIC_FTE0 | TIC_FTE1 | TIC_TFUE, TIC);

	/* Setting the control will start the AVB-DMAC process. */
	ravb_modअगरy(ndev, CCC, CCC_OPC, CCC_OPC_OPERATION);

	वापस 0;
पूर्ण

अटल व्योम ravb_get_tx_tstamp(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	काष्ठा ravb_tstamp_skb *ts_skb, *ts_skb2;
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	काष्ठा sk_buff *skb;
	काष्ठा बारpec64 ts;
	u16 tag, tfa_tag;
	पूर्णांक count;
	u32 tfa2;

	count = (ravb_पढ़ो(ndev, TSR) & TSR_TFFL) >> 8;
	जबतक (count--) अणु
		tfa2 = ravb_पढ़ो(ndev, TFA2);
		tfa_tag = (tfa2 & TFA2_TST) >> 16;
		ts.tv_nsec = (u64)ravb_पढ़ो(ndev, TFA0);
		ts.tv_sec = ((u64)(tfa2 & TFA2_TSV) << 32) |
			    ravb_पढ़ो(ndev, TFA1);
		स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
		shhwtstamps.hwtstamp = बारpec64_to_kसमय(ts);
		list_क्रम_each_entry_safe(ts_skb, ts_skb2, &priv->ts_skb_list,
					 list) अणु
			skb = ts_skb->skb;
			tag = ts_skb->tag;
			list_del(&ts_skb->list);
			kमुक्त(ts_skb);
			अगर (tag == tfa_tag) अणु
				skb_tstamp_tx(skb, &shhwtstamps);
				dev_consume_skb_any(skb);
				अवरोध;
			पूर्ण अन्यथा अणु
				dev_kमुक्त_skb_any(skb);
			पूर्ण
		पूर्ण
		ravb_modअगरy(ndev, TCCR, TCCR_TFR, TCCR_TFR);
	पूर्ण
पूर्ण

अटल व्योम ravb_rx_csum(काष्ठा sk_buff *skb)
अणु
	u8 *hw_csum;

	/* The hardware checksum is contained in माप(__sum16) (2) bytes
	 * appended to packet data
	 */
	अगर (unlikely(skb->len < माप(__sum16)))
		वापस;
	hw_csum = skb_tail_poपूर्णांकer(skb) - माप(__sum16);
	skb->csum = csum_unfold((__क्रमce __sum16)get_unaligned_le16(hw_csum));
	skb->ip_summed = CHECKSUM_COMPLETE;
	skb_trim(skb, skb->len - माप(__sum16));
पूर्ण

/* Packet receive function क्रम Ethernet AVB */
अटल bool ravb_rx(काष्ठा net_device *ndev, पूर्णांक *quota, पूर्णांक q)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक entry = priv->cur_rx[q] % priv->num_rx_ring[q];
	पूर्णांक boguscnt = (priv->dirty_rx[q] + priv->num_rx_ring[q]) -
			priv->cur_rx[q];
	काष्ठा net_device_stats *stats = &priv->stats[q];
	काष्ठा ravb_ex_rx_desc *desc;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
	काष्ठा बारpec64 ts;
	u8  desc_status;
	u16 pkt_len;
	पूर्णांक limit;

	boguscnt = min(boguscnt, *quota);
	limit = boguscnt;
	desc = &priv->rx_ring[q][entry];
	जबतक (desc->die_dt != DT_FEMPTY) अणु
		/* Descriptor type must be checked beक्रमe all other पढ़ोs */
		dma_rmb();
		desc_status = desc->msc;
		pkt_len = le16_to_cpu(desc->ds_cc) & RX_DS;

		अगर (--boguscnt < 0)
			अवरोध;

		/* We use 0-byte descriptors to mark the DMA mapping errors */
		अगर (!pkt_len)
			जारी;

		अगर (desc_status & MSC_MC)
			stats->multicast++;

		अगर (desc_status & (MSC_CRC | MSC_RFE | MSC_RTSF | MSC_RTLF |
				   MSC_CEEF)) अणु
			stats->rx_errors++;
			अगर (desc_status & MSC_CRC)
				stats->rx_crc_errors++;
			अगर (desc_status & MSC_RFE)
				stats->rx_frame_errors++;
			अगर (desc_status & (MSC_RTLF | MSC_RTSF))
				stats->rx_length_errors++;
			अगर (desc_status & MSC_CEEF)
				stats->rx_missed_errors++;
		पूर्ण अन्यथा अणु
			u32 get_ts = priv->tstamp_rx_ctrl & RAVB_RXTSTAMP_TYPE;

			skb = priv->rx_skb[q][entry];
			priv->rx_skb[q][entry] = शून्य;
			dma_unmap_single(ndev->dev.parent, le32_to_cpu(desc->dptr),
					 RX_BUF_SZ,
					 DMA_FROM_DEVICE);
			get_ts &= (q == RAVB_NC) ?
					RAVB_RXTSTAMP_TYPE_V2_L2_EVENT :
					~RAVB_RXTSTAMP_TYPE_V2_L2_EVENT;
			अगर (get_ts) अणु
				काष्ठा skb_shared_hwtstamps *shhwtstamps;

				shhwtstamps = skb_hwtstamps(skb);
				स_रखो(shhwtstamps, 0, माप(*shhwtstamps));
				ts.tv_sec = ((u64) le16_to_cpu(desc->ts_sh) <<
					     32) | le32_to_cpu(desc->ts_sl);
				ts.tv_nsec = le32_to_cpu(desc->ts_n);
				shhwtstamps->hwtstamp = बारpec64_to_kसमय(ts);
			पूर्ण

			skb_put(skb, pkt_len);
			skb->protocol = eth_type_trans(skb, ndev);
			अगर (ndev->features & NETIF_F_RXCSUM)
				ravb_rx_csum(skb);
			napi_gro_receive(&priv->napi[q], skb);
			stats->rx_packets++;
			stats->rx_bytes += pkt_len;
		पूर्ण

		entry = (++priv->cur_rx[q]) % priv->num_rx_ring[q];
		desc = &priv->rx_ring[q][entry];
	पूर्ण

	/* Refill the RX ring buffers. */
	क्रम (; priv->cur_rx[q] - priv->dirty_rx[q] > 0; priv->dirty_rx[q]++) अणु
		entry = priv->dirty_rx[q] % priv->num_rx_ring[q];
		desc = &priv->rx_ring[q][entry];
		desc->ds_cc = cpu_to_le16(RX_BUF_SZ);

		अगर (!priv->rx_skb[q][entry]) अणु
			skb = netdev_alloc_skb(ndev,
					       RX_BUF_SZ +
					       RAVB_ALIGN - 1);
			अगर (!skb)
				अवरोध;	/* Better luck next round. */
			ravb_set_buffer_align(skb);
			dma_addr = dma_map_single(ndev->dev.parent, skb->data,
						  le16_to_cpu(desc->ds_cc),
						  DMA_FROM_DEVICE);
			skb_checksum_none_निश्चित(skb);
			/* We just set the data size to 0 क्रम a failed mapping
			 * which should prevent DMA  from happening...
			 */
			अगर (dma_mapping_error(ndev->dev.parent, dma_addr))
				desc->ds_cc = cpu_to_le16(0);
			desc->dptr = cpu_to_le32(dma_addr);
			priv->rx_skb[q][entry] = skb;
		पूर्ण
		/* Descriptor type must be set after all the above ग_लिखोs */
		dma_wmb();
		desc->die_dt = DT_FEMPTY;
	पूर्ण

	*quota -= limit - (++boguscnt);

	वापस boguscnt <= 0;
पूर्ण

अटल व्योम ravb_rcv_snd_disable(काष्ठा net_device *ndev)
अणु
	/* Disable TX and RX */
	ravb_modअगरy(ndev, ECMR, ECMR_RE | ECMR_TE, 0);
पूर्ण

अटल व्योम ravb_rcv_snd_enable(काष्ठा net_device *ndev)
अणु
	/* Enable TX and RX */
	ravb_modअगरy(ndev, ECMR, ECMR_RE | ECMR_TE, ECMR_RE | ECMR_TE);
पूर्ण

/* function क्रम रुकोing dma process finished */
अटल पूर्णांक ravb_stop_dma(काष्ठा net_device *ndev)
अणु
	पूर्णांक error;

	/* Wait क्रम stopping the hardware TX process */
	error = ravb_रुको(ndev, TCCR,
			  TCCR_TSRQ0 | TCCR_TSRQ1 | TCCR_TSRQ2 | TCCR_TSRQ3, 0);
	अगर (error)
		वापस error;

	error = ravb_रुको(ndev, CSR, CSR_TPO0 | CSR_TPO1 | CSR_TPO2 | CSR_TPO3,
			  0);
	अगर (error)
		वापस error;

	/* Stop the E-MAC's RX/TX processes. */
	ravb_rcv_snd_disable(ndev);

	/* Wait क्रम stopping the RX DMA process */
	error = ravb_रुको(ndev, CSR, CSR_RPO, 0);
	अगर (error)
		वापस error;

	/* Stop AVB-DMAC process */
	वापस ravb_config(ndev);
पूर्ण

/* E-MAC पूर्णांकerrupt handler */
अटल व्योम ravb_emac_पूर्णांकerrupt_unlocked(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	u32 ecsr, psr;

	ecsr = ravb_पढ़ो(ndev, ECSR);
	ravb_ग_लिखो(ndev, ecsr, ECSR);	/* clear पूर्णांकerrupt */

	अगर (ecsr & ECSR_MPD)
		pm_wakeup_event(&priv->pdev->dev, 0);
	अगर (ecsr & ECSR_ICD)
		ndev->stats.tx_carrier_errors++;
	अगर (ecsr & ECSR_LCHNG) अणु
		/* Link changed */
		अगर (priv->no_avb_link)
			वापस;
		psr = ravb_पढ़ो(ndev, PSR);
		अगर (priv->avb_link_active_low)
			psr ^= PSR_LMON;
		अगर (!(psr & PSR_LMON)) अणु
			/* DIsable RX and TX */
			ravb_rcv_snd_disable(ndev);
		पूर्ण अन्यथा अणु
			/* Enable RX and TX */
			ravb_rcv_snd_enable(ndev);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t ravb_emac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	spin_lock(&priv->lock);
	ravb_emac_पूर्णांकerrupt_unlocked(ndev);
	spin_unlock(&priv->lock);
	वापस IRQ_HANDLED;
पूर्ण

/* Error पूर्णांकerrupt handler */
अटल व्योम ravb_error_पूर्णांकerrupt(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	u32 eis, ris2;

	eis = ravb_पढ़ो(ndev, EIS);
	ravb_ग_लिखो(ndev, ~(EIS_QFS | EIS_RESERVED), EIS);
	अगर (eis & EIS_QFS) अणु
		ris2 = ravb_पढ़ो(ndev, RIS2);
		ravb_ग_लिखो(ndev, ~(RIS2_QFF0 | RIS2_RFFF | RIS2_RESERVED),
			   RIS2);

		/* Receive Descriptor Empty पूर्णांक */
		अगर (ris2 & RIS2_QFF0)
			priv->stats[RAVB_BE].rx_over_errors++;

		    /* Receive Descriptor Empty पूर्णांक */
		अगर (ris2 & RIS2_QFF1)
			priv->stats[RAVB_NC].rx_over_errors++;

		/* Receive FIFO Overflow पूर्णांक */
		अगर (ris2 & RIS2_RFFF)
			priv->rx_fअगरo_errors++;
	पूर्ण
पूर्ण

अटल bool ravb_queue_पूर्णांकerrupt(काष्ठा net_device *ndev, पूर्णांक q)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	u32 ris0 = ravb_पढ़ो(ndev, RIS0);
	u32 ric0 = ravb_पढ़ो(ndev, RIC0);
	u32 tis  = ravb_पढ़ो(ndev, TIS);
	u32 tic  = ravb_पढ़ो(ndev, TIC);

	अगर (((ris0 & ric0) & BIT(q)) || ((tis  & tic)  & BIT(q))) अणु
		अगर (napi_schedule_prep(&priv->napi[q])) अणु
			/* Mask RX and TX पूर्णांकerrupts */
			अगर (priv->chip_id == RCAR_GEN2) अणु
				ravb_ग_लिखो(ndev, ric0 & ~BIT(q), RIC0);
				ravb_ग_लिखो(ndev, tic & ~BIT(q), TIC);
			पूर्ण अन्यथा अणु
				ravb_ग_लिखो(ndev, BIT(q), RID0);
				ravb_ग_लिखो(ndev, BIT(q), TID);
			पूर्ण
			__napi_schedule(&priv->napi[q]);
		पूर्ण अन्यथा अणु
			netdev_warn(ndev,
				    "ignoring interrupt, rx status 0x%08x, rx mask 0x%08x,\n",
				    ris0, ric0);
			netdev_warn(ndev,
				    "                    tx status 0x%08x, tx mask 0x%08x.\n",
				    tis, tic);
		पूर्ण
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool ravb_बारtamp_पूर्णांकerrupt(काष्ठा net_device *ndev)
अणु
	u32 tis = ravb_पढ़ो(ndev, TIS);

	अगर (tis & TIS_TFUF) अणु
		ravb_ग_लिखो(ndev, ~(TIS_TFUF | TIS_RESERVED), TIS);
		ravb_get_tx_tstamp(ndev);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल irqवापस_t ravb_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	irqवापस_t result = IRQ_NONE;
	u32 iss;

	spin_lock(&priv->lock);
	/* Get पूर्णांकerrupt status */
	iss = ravb_पढ़ो(ndev, ISS);

	/* Received and transmitted पूर्णांकerrupts */
	अगर (iss & (ISS_FRS | ISS_FTS | ISS_TFUS)) अणु
		पूर्णांक q;

		/* Timestamp updated */
		अगर (ravb_बारtamp_पूर्णांकerrupt(ndev))
			result = IRQ_HANDLED;

		/* Network control and best efक्रमt queue RX/TX */
		क्रम (q = RAVB_NC; q >= RAVB_BE; q--) अणु
			अगर (ravb_queue_पूर्णांकerrupt(ndev, q))
				result = IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* E-MAC status summary */
	अगर (iss & ISS_MS) अणु
		ravb_emac_पूर्णांकerrupt_unlocked(ndev);
		result = IRQ_HANDLED;
	पूर्ण

	/* Error status summary */
	अगर (iss & ISS_ES) अणु
		ravb_error_पूर्णांकerrupt(ndev);
		result = IRQ_HANDLED;
	पूर्ण

	/* gPTP पूर्णांकerrupt status summary */
	अगर (iss & ISS_CGIS) अणु
		ravb_ptp_पूर्णांकerrupt(ndev);
		result = IRQ_HANDLED;
	पूर्ण

	spin_unlock(&priv->lock);
	वापस result;
पूर्ण

/* Timestamp/Error/gPTP पूर्णांकerrupt handler */
अटल irqवापस_t ravb_multi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	irqवापस_t result = IRQ_NONE;
	u32 iss;

	spin_lock(&priv->lock);
	/* Get पूर्णांकerrupt status */
	iss = ravb_पढ़ो(ndev, ISS);

	/* Timestamp updated */
	अगर ((iss & ISS_TFUS) && ravb_बारtamp_पूर्णांकerrupt(ndev))
		result = IRQ_HANDLED;

	/* Error status summary */
	अगर (iss & ISS_ES) अणु
		ravb_error_पूर्णांकerrupt(ndev);
		result = IRQ_HANDLED;
	पूर्ण

	/* gPTP पूर्णांकerrupt status summary */
	अगर (iss & ISS_CGIS) अणु
		ravb_ptp_पूर्णांकerrupt(ndev);
		result = IRQ_HANDLED;
	पूर्ण

	spin_unlock(&priv->lock);
	वापस result;
पूर्ण

अटल irqवापस_t ravb_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id, पूर्णांक q)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	irqवापस_t result = IRQ_NONE;

	spin_lock(&priv->lock);

	/* Network control/Best efक्रमt queue RX/TX */
	अगर (ravb_queue_पूर्णांकerrupt(ndev, q))
		result = IRQ_HANDLED;

	spin_unlock(&priv->lock);
	वापस result;
पूर्ण

अटल irqवापस_t ravb_be_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस ravb_dma_पूर्णांकerrupt(irq, dev_id, RAVB_BE);
पूर्ण

अटल irqवापस_t ravb_nc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस ravb_dma_पूर्णांकerrupt(irq, dev_id, RAVB_NC);
पूर्ण

अटल पूर्णांक ravb_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा net_device *ndev = napi->dev;
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;
	पूर्णांक q = napi - priv->napi;
	पूर्णांक mask = BIT(q);
	पूर्णांक quota = budget;

	/* Processing RX Descriptor Ring */
	/* Clear RX पूर्णांकerrupt */
	ravb_ग_लिखो(ndev, ~(mask | RIS0_RESERVED), RIS0);
	अगर (ravb_rx(ndev, &quota, q))
		जाओ out;

	/* Processing RX Descriptor Ring */
	spin_lock_irqsave(&priv->lock, flags);
	/* Clear TX पूर्णांकerrupt */
	ravb_ग_लिखो(ndev, ~(mask | TIS_RESERVED), TIS);
	ravb_tx_मुक्त(ndev, q, true);
	netअगर_wake_subqueue(ndev, q);
	spin_unlock_irqrestore(&priv->lock, flags);

	napi_complete(napi);

	/* Re-enable RX/TX पूर्णांकerrupts */
	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->chip_id == RCAR_GEN2) अणु
		ravb_modअगरy(ndev, RIC0, mask, mask);
		ravb_modअगरy(ndev, TIC,  mask, mask);
	पूर्ण अन्यथा अणु
		ravb_ग_लिखो(ndev, mask, RIE0);
		ravb_ग_लिखो(ndev, mask, TIE);
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	/* Receive error message handling */
	priv->rx_over_errors =  priv->stats[RAVB_BE].rx_over_errors;
	priv->rx_over_errors += priv->stats[RAVB_NC].rx_over_errors;
	अगर (priv->rx_over_errors != ndev->stats.rx_over_errors)
		ndev->stats.rx_over_errors = priv->rx_over_errors;
	अगर (priv->rx_fअगरo_errors != ndev->stats.rx_fअगरo_errors)
		ndev->stats.rx_fअगरo_errors = priv->rx_fअगरo_errors;
out:
	वापस budget - quota;
पूर्ण

/* PHY state control function */
अटल व्योम ravb_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;
	bool new_state = false;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	/* Disable TX and RX right over here, अगर E-MAC change is ignored */
	अगर (priv->no_avb_link)
		ravb_rcv_snd_disable(ndev);

	अगर (phydev->link) अणु
		अगर (phydev->speed != priv->speed) अणु
			new_state = true;
			priv->speed = phydev->speed;
			ravb_set_rate(ndev);
		पूर्ण
		अगर (!priv->link) अणु
			ravb_modअगरy(ndev, ECMR, ECMR_TXF, 0);
			new_state = true;
			priv->link = phydev->link;
		पूर्ण
	पूर्ण अन्यथा अगर (priv->link) अणु
		new_state = true;
		priv->link = 0;
		priv->speed = 0;
	पूर्ण

	/* Enable TX and RX right over here, अगर E-MAC change is ignored */
	अगर (priv->no_avb_link && phydev->link)
		ravb_rcv_snd_enable(ndev);

	spin_unlock_irqrestore(&priv->lock, flags);

	अगर (new_state && netअगर_msg_link(priv))
		phy_prपूर्णांक_status(phydev);
पूर्ण

अटल स्थिर काष्ठा soc_device_attribute r8a7795es10[] = अणु
	अणु .soc_id = "r8a7795", .revision = "ES1.0", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

/* PHY init function */
अटल पूर्णांक ravb_phy_init(काष्ठा net_device *ndev)
अणु
	काष्ठा device_node *np = ndev->dev.parent->of_node;
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev;
	काष्ठा device_node *pn;
	phy_पूर्णांकerface_t अगरace;
	पूर्णांक err;

	priv->link = 0;
	priv->speed = 0;

	/* Try connecting to PHY */
	pn = of_parse_phandle(np, "phy-handle", 0);
	अगर (!pn) अणु
		/* In the हाल of a fixed PHY, the DT node associated
		 * to the PHY is the Ethernet MAC DT node.
		 */
		अगर (of_phy_is_fixed_link(np)) अणु
			err = of_phy_रेजिस्टर_fixed_link(np);
			अगर (err)
				वापस err;
		पूर्ण
		pn = of_node_get(np);
	पूर्ण

	अगरace = priv->rgmii_override ? PHY_INTERFACE_MODE_RGMII
				     : priv->phy_पूर्णांकerface;
	phydev = of_phy_connect(ndev, pn, ravb_adjust_link, 0, अगरace);
	of_node_put(pn);
	अगर (!phydev) अणु
		netdev_err(ndev, "failed to connect PHY\n");
		err = -ENOENT;
		जाओ err_deरेजिस्टर_fixed_link;
	पूर्ण

	/* This driver only support 10/100Mbit speeds on R-Car H3 ES1.0
	 * at this समय.
	 */
	अगर (soc_device_match(r8a7795es10)) अणु
		err = phy_set_max_speed(phydev, SPEED_100);
		अगर (err) अणु
			netdev_err(ndev, "failed to limit PHY to 100Mbit/s\n");
			जाओ err_phy_disconnect;
		पूर्ण

		netdev_info(ndev, "limited PHY to 100Mbit/s\n");
	पूर्ण

	/* 10BASE, Pause and Asym Pause is not supported */
	phy_हटाओ_link_mode(phydev, ETHTOOL_LINK_MODE_10baseT_Half_BIT);
	phy_हटाओ_link_mode(phydev, ETHTOOL_LINK_MODE_10baseT_Full_BIT);
	phy_हटाओ_link_mode(phydev, ETHTOOL_LINK_MODE_Pause_BIT);
	phy_हटाओ_link_mode(phydev, ETHTOOL_LINK_MODE_Asym_Pause_BIT);

	/* Half Duplex is not supported */
	phy_हटाओ_link_mode(phydev, ETHTOOL_LINK_MODE_1000baseT_Half_BIT);
	phy_हटाओ_link_mode(phydev, ETHTOOL_LINK_MODE_100baseT_Half_BIT);

	phy_attached_info(phydev);

	वापस 0;

err_phy_disconnect:
	phy_disconnect(phydev);
err_deरेजिस्टर_fixed_link:
	अगर (of_phy_is_fixed_link(np))
		of_phy_deरेजिस्टर_fixed_link(np);

	वापस err;
पूर्ण

/* PHY control start function */
अटल पूर्णांक ravb_phy_start(काष्ठा net_device *ndev)
अणु
	पूर्णांक error;

	error = ravb_phy_init(ndev);
	अगर (error)
		वापस error;

	phy_start(ndev->phydev);

	वापस 0;
पूर्ण

अटल u32 ravb_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम ravb_set_msglevel(काष्ठा net_device *ndev, u32 value)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	priv->msg_enable = value;
पूर्ण

अटल स्थिर अक्षर ravb_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"rx_queue_0_current",
	"tx_queue_0_current",
	"rx_queue_0_dirty",
	"tx_queue_0_dirty",
	"rx_queue_0_packets",
	"tx_queue_0_packets",
	"rx_queue_0_bytes",
	"tx_queue_0_bytes",
	"rx_queue_0_mcast_packets",
	"rx_queue_0_errors",
	"rx_queue_0_crc_errors",
	"rx_queue_0_frame_errors",
	"rx_queue_0_length_errors",
	"rx_queue_0_missed_errors",
	"rx_queue_0_over_errors",

	"rx_queue_1_current",
	"tx_queue_1_current",
	"rx_queue_1_dirty",
	"tx_queue_1_dirty",
	"rx_queue_1_packets",
	"tx_queue_1_packets",
	"rx_queue_1_bytes",
	"tx_queue_1_bytes",
	"rx_queue_1_mcast_packets",
	"rx_queue_1_errors",
	"rx_queue_1_crc_errors",
	"rx_queue_1_frame_errors",
	"rx_queue_1_length_errors",
	"rx_queue_1_missed_errors",
	"rx_queue_1_over_errors",
पूर्ण;

#घोषणा RAVB_STATS_LEN	ARRAY_SIZE(ravb_gstrings_stats)

अटल पूर्णांक ravb_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस RAVB_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम ravb_get_ethtool_stats(काष्ठा net_device *ndev,
				   काष्ठा ethtool_stats *estats, u64 *data)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक i = 0;
	पूर्णांक q;

	/* Device-specअगरic stats */
	क्रम (q = RAVB_BE; q < NUM_RX_QUEUE; q++) अणु
		काष्ठा net_device_stats *stats = &priv->stats[q];

		data[i++] = priv->cur_rx[q];
		data[i++] = priv->cur_tx[q];
		data[i++] = priv->dirty_rx[q];
		data[i++] = priv->dirty_tx[q];
		data[i++] = stats->rx_packets;
		data[i++] = stats->tx_packets;
		data[i++] = stats->rx_bytes;
		data[i++] = stats->tx_bytes;
		data[i++] = stats->multicast;
		data[i++] = stats->rx_errors;
		data[i++] = stats->rx_crc_errors;
		data[i++] = stats->rx_frame_errors;
		data[i++] = stats->rx_length_errors;
		data[i++] = stats->rx_missed_errors;
		data[i++] = stats->rx_over_errors;
	पूर्ण
पूर्ण

अटल व्योम ravb_get_strings(काष्ठा net_device *ndev, u32 stringset, u8 *data)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(data, ravb_gstrings_stats, माप(ravb_gstrings_stats));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ravb_get_ringparam(काष्ठा net_device *ndev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	ring->rx_max_pending = BE_RX_RING_MAX;
	ring->tx_max_pending = BE_TX_RING_MAX;
	ring->rx_pending = priv->num_rx_ring[RAVB_BE];
	ring->tx_pending = priv->num_tx_ring[RAVB_BE];
पूर्ण

अटल पूर्णांक ravb_set_ringparam(काष्ठा net_device *ndev,
			      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक error;

	अगर (ring->tx_pending > BE_TX_RING_MAX ||
	    ring->rx_pending > BE_RX_RING_MAX ||
	    ring->tx_pending < BE_TX_RING_MIN ||
	    ring->rx_pending < BE_RX_RING_MIN)
		वापस -EINVAL;
	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending)
		वापस -EINVAL;

	अगर (netअगर_running(ndev)) अणु
		netअगर_device_detach(ndev);
		/* Stop PTP Clock driver */
		अगर (priv->chip_id == RCAR_GEN2)
			ravb_ptp_stop(ndev);
		/* Wait क्रम DMA stopping */
		error = ravb_stop_dma(ndev);
		अगर (error) अणु
			netdev_err(ndev,
				   "cannot set ringparam! Any AVB processes are still running?\n");
			वापस error;
		पूर्ण
		synchronize_irq(ndev->irq);

		/* Free all the skb's in the RX queue and the DMA buffers. */
		ravb_ring_मुक्त(ndev, RAVB_BE);
		ravb_ring_मुक्त(ndev, RAVB_NC);
	पूर्ण

	/* Set new parameters */
	priv->num_rx_ring[RAVB_BE] = ring->rx_pending;
	priv->num_tx_ring[RAVB_BE] = ring->tx_pending;

	अगर (netअगर_running(ndev)) अणु
		error = ravb_dmac_init(ndev);
		अगर (error) अणु
			netdev_err(ndev,
				   "%s: ravb_dmac_init() failed, error %d\n",
				   __func__, error);
			वापस error;
		पूर्ण

		ravb_emac_init(ndev);

		/* Initialise PTP Clock driver */
		अगर (priv->chip_id == RCAR_GEN2)
			ravb_ptp_init(ndev, priv->pdev);

		netअगर_device_attach(ndev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ravb_get_ts_info(काष्ठा net_device *ndev,
			    काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_SOFTWARE |
		SOF_TIMESTAMPING_RX_SOFTWARE |
		SOF_TIMESTAMPING_SOFTWARE |
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);
	info->rx_filters =
		(1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
		(1 << HWTSTAMP_FILTER_ALL);
	info->phc_index = ptp_घड़ी_index(priv->ptp.घड़ी);

	वापस 0;
पूर्ण

अटल व्योम ravb_get_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	wol->supported = WAKE_MAGIC;
	wol->wolopts = priv->wol_enabled ? WAKE_MAGIC : 0;
पूर्ण

अटल पूर्णांक ravb_set_wol(काष्ठा net_device *ndev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EOPNOTSUPP;

	priv->wol_enabled = !!(wol->wolopts & WAKE_MAGIC);

	device_set_wakeup_enable(&priv->pdev->dev, priv->wol_enabled);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ravb_ethtool_ops = अणु
	.nway_reset		= phy_ethtool_nway_reset,
	.get_msglevel		= ravb_get_msglevel,
	.set_msglevel		= ravb_set_msglevel,
	.get_link		= ethtool_op_get_link,
	.get_strings		= ravb_get_strings,
	.get_ethtool_stats	= ravb_get_ethtool_stats,
	.get_sset_count		= ravb_get_sset_count,
	.get_ringparam		= ravb_get_ringparam,
	.set_ringparam		= ravb_set_ringparam,
	.get_ts_info		= ravb_get_ts_info,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
	.get_wol		= ravb_get_wol,
	.set_wol		= ravb_set_wol,
पूर्ण;

अटल अंतरभूत पूर्णांक ravb_hook_irq(अचिन्हित पूर्णांक irq, irq_handler_t handler,
				काष्ठा net_device *ndev, काष्ठा device *dev,
				स्थिर अक्षर *ch)
अणु
	अक्षर *name;
	पूर्णांक error;

	name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s:%s", ndev->name, ch);
	अगर (!name)
		वापस -ENOMEM;
	error = request_irq(irq, handler, 0, name, ndev);
	अगर (error)
		netdev_err(ndev, "cannot request IRQ %s\n", name);

	वापस error;
पूर्ण

/* Network device खोलो function क्रम Ethernet AVB */
अटल पूर्णांक ravb_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	काष्ठा platक्रमm_device *pdev = priv->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक error;

	napi_enable(&priv->napi[RAVB_BE]);
	napi_enable(&priv->napi[RAVB_NC]);

	अगर (priv->chip_id == RCAR_GEN2) अणु
		error = request_irq(ndev->irq, ravb_पूर्णांकerrupt, IRQF_SHARED,
				    ndev->name, ndev);
		अगर (error) अणु
			netdev_err(ndev, "cannot request IRQ\n");
			जाओ out_napi_off;
		पूर्ण
	पूर्ण अन्यथा अणु
		error = ravb_hook_irq(ndev->irq, ravb_multi_पूर्णांकerrupt, ndev,
				      dev, "ch22:multi");
		अगर (error)
			जाओ out_napi_off;
		error = ravb_hook_irq(priv->emac_irq, ravb_emac_पूर्णांकerrupt, ndev,
				      dev, "ch24:emac");
		अगर (error)
			जाओ out_मुक्त_irq;
		error = ravb_hook_irq(priv->rx_irqs[RAVB_BE], ravb_be_पूर्णांकerrupt,
				      ndev, dev, "ch0:rx_be");
		अगर (error)
			जाओ out_मुक्त_irq_emac;
		error = ravb_hook_irq(priv->tx_irqs[RAVB_BE], ravb_be_पूर्णांकerrupt,
				      ndev, dev, "ch18:tx_be");
		अगर (error)
			जाओ out_मुक्त_irq_be_rx;
		error = ravb_hook_irq(priv->rx_irqs[RAVB_NC], ravb_nc_पूर्णांकerrupt,
				      ndev, dev, "ch1:rx_nc");
		अगर (error)
			जाओ out_मुक्त_irq_be_tx;
		error = ravb_hook_irq(priv->tx_irqs[RAVB_NC], ravb_nc_पूर्णांकerrupt,
				      ndev, dev, "ch19:tx_nc");
		अगर (error)
			जाओ out_मुक्त_irq_nc_rx;
	पूर्ण

	/* Device init */
	error = ravb_dmac_init(ndev);
	अगर (error)
		जाओ out_मुक्त_irq_nc_tx;
	ravb_emac_init(ndev);

	/* Initialise PTP Clock driver */
	अगर (priv->chip_id == RCAR_GEN2)
		ravb_ptp_init(ndev, priv->pdev);

	netअगर_tx_start_all_queues(ndev);

	/* PHY control start */
	error = ravb_phy_start(ndev);
	अगर (error)
		जाओ out_ptp_stop;

	वापस 0;

out_ptp_stop:
	/* Stop PTP Clock driver */
	अगर (priv->chip_id == RCAR_GEN2)
		ravb_ptp_stop(ndev);
out_मुक्त_irq_nc_tx:
	अगर (priv->chip_id == RCAR_GEN2)
		जाओ out_मुक्त_irq;
	मुक्त_irq(priv->tx_irqs[RAVB_NC], ndev);
out_मुक्त_irq_nc_rx:
	मुक्त_irq(priv->rx_irqs[RAVB_NC], ndev);
out_मुक्त_irq_be_tx:
	मुक्त_irq(priv->tx_irqs[RAVB_BE], ndev);
out_मुक्त_irq_be_rx:
	मुक्त_irq(priv->rx_irqs[RAVB_BE], ndev);
out_मुक्त_irq_emac:
	मुक्त_irq(priv->emac_irq, ndev);
out_मुक्त_irq:
	मुक्त_irq(ndev->irq, ndev);
out_napi_off:
	napi_disable(&priv->napi[RAVB_NC]);
	napi_disable(&priv->napi[RAVB_BE]);
	वापस error;
पूर्ण

/* Timeout function क्रम Ethernet AVB */
अटल व्योम ravb_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	netअगर_err(priv, tx_err, ndev,
		  "transmit timed out, status %08x, resetting...\n",
		  ravb_पढ़ो(ndev, ISS));

	/* tx_errors count up */
	ndev->stats.tx_errors++;

	schedule_work(&priv->work);
पूर्ण

अटल व्योम ravb_tx_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ravb_निजी *priv = container_of(work, काष्ठा ravb_निजी,
						 work);
	काष्ठा net_device *ndev = priv->ndev;
	पूर्णांक error;

	netअगर_tx_stop_all_queues(ndev);

	/* Stop PTP Clock driver */
	अगर (priv->chip_id == RCAR_GEN2)
		ravb_ptp_stop(ndev);

	/* Wait क्रम DMA stopping */
	अगर (ravb_stop_dma(ndev)) अणु
		/* If ravb_stop_dma() fails, the hardware is still operating
		 * क्रम TX and/or RX. So, this should not call the following
		 * functions because ravb_dmac_init() is possible to fail too.
		 * Also, this should not retry ravb_stop_dma() again and again
		 * here because it's possible to रुको क्रमever. So, this just
		 * re-enables the TX and RX and skip the following
		 * re-initialization procedure.
		 */
		ravb_rcv_snd_enable(ndev);
		जाओ out;
	पूर्ण

	ravb_ring_मुक्त(ndev, RAVB_BE);
	ravb_ring_मुक्त(ndev, RAVB_NC);

	/* Device init */
	error = ravb_dmac_init(ndev);
	अगर (error) अणु
		/* If ravb_dmac_init() fails, descriptors are मुक्तd. So, this
		 * should वापस here to aव्योम re-enabling the TX and RX in
		 * ravb_emac_init().
		 */
		netdev_err(ndev, "%s: ravb_dmac_init() failed, error %d\n",
			   __func__, error);
		वापस;
	पूर्ण
	ravb_emac_init(ndev);

out:
	/* Initialise PTP Clock driver */
	अगर (priv->chip_id == RCAR_GEN2)
		ravb_ptp_init(ndev, priv->pdev);

	netअगर_tx_start_all_queues(ndev);
पूर्ण

/* Packet transmit function क्रम Ethernet AVB */
अटल netdev_tx_t ravb_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक num_tx_desc = priv->num_tx_desc;
	u16 q = skb_get_queue_mapping(skb);
	काष्ठा ravb_tstamp_skb *ts_skb;
	काष्ठा ravb_tx_desc *desc;
	अचिन्हित दीर्घ flags;
	u32 dma_addr;
	व्योम *buffer;
	u32 entry;
	u32 len;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->cur_tx[q] - priv->dirty_tx[q] > (priv->num_tx_ring[q] - 1) *
	    num_tx_desc) अणु
		netअगर_err(priv, tx_queued, ndev,
			  "still transmitting with the full ring!\n");
		netअगर_stop_subqueue(ndev, q);
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (skb_put_padto(skb, ETH_ZLEN))
		जाओ निकास;

	entry = priv->cur_tx[q] % (priv->num_tx_ring[q] * num_tx_desc);
	priv->tx_skb[q][entry / num_tx_desc] = skb;

	अगर (num_tx_desc > 1) अणु
		buffer = PTR_ALIGN(priv->tx_align[q], DPTR_ALIGN) +
			 entry / num_tx_desc * DPTR_ALIGN;
		len = PTR_ALIGN(skb->data, DPTR_ALIGN) - skb->data;

		/* Zero length DMA descriptors are problematic as they seem
		 * to terminate DMA transfers. Aव्योम them by simply using a
		 * length of DPTR_ALIGN (4) when skb data is aligned to
		 * DPTR_ALIGN.
		 *
		 * As skb is guaranteed to have at least ETH_ZLEN (60)
		 * bytes of data by the call to skb_put_padto() above this
		 * is safe with respect to both the length of the first DMA
		 * descriptor (len) overflowing the available data and the
		 * length of the second DMA descriptor (skb->len - len)
		 * being negative.
		 */
		अगर (len == 0)
			len = DPTR_ALIGN;

		स_नकल(buffer, skb->data, len);
		dma_addr = dma_map_single(ndev->dev.parent, buffer, len,
					  DMA_TO_DEVICE);
		अगर (dma_mapping_error(ndev->dev.parent, dma_addr))
			जाओ drop;

		desc = &priv->tx_ring[q][entry];
		desc->ds_tagl = cpu_to_le16(len);
		desc->dptr = cpu_to_le32(dma_addr);

		buffer = skb->data + len;
		len = skb->len - len;
		dma_addr = dma_map_single(ndev->dev.parent, buffer, len,
					  DMA_TO_DEVICE);
		अगर (dma_mapping_error(ndev->dev.parent, dma_addr))
			जाओ unmap;

		desc++;
	पूर्ण अन्यथा अणु
		desc = &priv->tx_ring[q][entry];
		len = skb->len;
		dma_addr = dma_map_single(ndev->dev.parent, skb->data, skb->len,
					  DMA_TO_DEVICE);
		अगर (dma_mapping_error(ndev->dev.parent, dma_addr))
			जाओ drop;
	पूर्ण
	desc->ds_tagl = cpu_to_le16(len);
	desc->dptr = cpu_to_le32(dma_addr);

	/* TX बारtamp required */
	अगर (q == RAVB_NC) अणु
		ts_skb = kदो_स्मृति(माप(*ts_skb), GFP_ATOMIC);
		अगर (!ts_skb) अणु
			अगर (num_tx_desc > 1) अणु
				desc--;
				dma_unmap_single(ndev->dev.parent, dma_addr,
						 len, DMA_TO_DEVICE);
			पूर्ण
			जाओ unmap;
		पूर्ण
		ts_skb->skb = skb_get(skb);
		ts_skb->tag = priv->ts_skb_tag++;
		priv->ts_skb_tag &= 0x3ff;
		list_add_tail(&ts_skb->list, &priv->ts_skb_list);

		/* TAG and बारtamp required flag */
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		desc->tagh_tsr = (ts_skb->tag >> 4) | TX_TSR;
		desc->ds_tagl |= cpu_to_le16(ts_skb->tag << 12);
	पूर्ण

	skb_tx_बारtamp(skb);
	/* Descriptor type must be set after all the above ग_लिखोs */
	dma_wmb();
	अगर (num_tx_desc > 1) अणु
		desc->die_dt = DT_FEND;
		desc--;
		desc->die_dt = DT_FSTART;
	पूर्ण अन्यथा अणु
		desc->die_dt = DT_FSINGLE;
	पूर्ण
	ravb_modअगरy(ndev, TCCR, TCCR_TSRQ0 << q, TCCR_TSRQ0 << q);

	priv->cur_tx[q] += num_tx_desc;
	अगर (priv->cur_tx[q] - priv->dirty_tx[q] >
	    (priv->num_tx_ring[q] - 1) * num_tx_desc &&
	    !ravb_tx_मुक्त(ndev, q, true))
		netअगर_stop_subqueue(ndev, q);

निकास:
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस NETDEV_TX_OK;

unmap:
	dma_unmap_single(ndev->dev.parent, le32_to_cpu(desc->dptr),
			 le16_to_cpu(desc->ds_tagl), DMA_TO_DEVICE);
drop:
	dev_kमुक्त_skb_any(skb);
	priv->tx_skb[q][entry / num_tx_desc] = शून्य;
	जाओ निकास;
पूर्ण

अटल u16 ravb_select_queue(काष्ठा net_device *ndev, काष्ठा sk_buff *skb,
			     काष्ठा net_device *sb_dev)
अणु
	/* If skb needs TX बारtamp, it is handled in network control queue */
	वापस (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) ? RAVB_NC :
							       RAVB_BE;

पूर्ण

अटल काष्ठा net_device_stats *ravb_get_stats(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *nstats, *stats0, *stats1;

	nstats = &ndev->stats;
	stats0 = &priv->stats[RAVB_BE];
	stats1 = &priv->stats[RAVB_NC];

	अगर (priv->chip_id == RCAR_GEN3) अणु
		nstats->tx_dropped += ravb_पढ़ो(ndev, TROCR);
		ravb_ग_लिखो(ndev, 0, TROCR);	/* (ग_लिखो clear) */
	पूर्ण

	nstats->rx_packets = stats0->rx_packets + stats1->rx_packets;
	nstats->tx_packets = stats0->tx_packets + stats1->tx_packets;
	nstats->rx_bytes = stats0->rx_bytes + stats1->rx_bytes;
	nstats->tx_bytes = stats0->tx_bytes + stats1->tx_bytes;
	nstats->multicast = stats0->multicast + stats1->multicast;
	nstats->rx_errors = stats0->rx_errors + stats1->rx_errors;
	nstats->rx_crc_errors = stats0->rx_crc_errors + stats1->rx_crc_errors;
	nstats->rx_frame_errors =
		stats0->rx_frame_errors + stats1->rx_frame_errors;
	nstats->rx_length_errors =
		stats0->rx_length_errors + stats1->rx_length_errors;
	nstats->rx_missed_errors =
		stats0->rx_missed_errors + stats1->rx_missed_errors;
	nstats->rx_over_errors =
		stats0->rx_over_errors + stats1->rx_over_errors;

	वापस nstats;
पूर्ण

/* Update promiscuous bit */
अटल व्योम ravb_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	ravb_modअगरy(ndev, ECMR, ECMR_PRM,
		    ndev->flags & IFF_PROMISC ? ECMR_PRM : 0);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

/* Device बंद function क्रम Ethernet AVB */
अटल पूर्णांक ravb_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा device_node *np = ndev->dev.parent->of_node;
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	काष्ठा ravb_tstamp_skb *ts_skb, *ts_skb2;

	netअगर_tx_stop_all_queues(ndev);

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt masks. */
	ravb_ग_लिखो(ndev, 0, RIC0);
	ravb_ग_लिखो(ndev, 0, RIC2);
	ravb_ग_लिखो(ndev, 0, TIC);

	/* Stop PTP Clock driver */
	अगर (priv->chip_id == RCAR_GEN2)
		ravb_ptp_stop(ndev);

	/* Set the config mode to stop the AVB-DMAC's processes */
	अगर (ravb_stop_dma(ndev) < 0)
		netdev_err(ndev,
			   "device will be stopped after h/w processes are done.\n");

	/* Clear the बारtamp list */
	list_क्रम_each_entry_safe(ts_skb, ts_skb2, &priv->ts_skb_list, list) अणु
		list_del(&ts_skb->list);
		kमुक्त_skb(ts_skb->skb);
		kमुक्त(ts_skb);
	पूर्ण

	/* PHY disconnect */
	अगर (ndev->phydev) अणु
		phy_stop(ndev->phydev);
		phy_disconnect(ndev->phydev);
		अगर (of_phy_is_fixed_link(np))
			of_phy_deरेजिस्टर_fixed_link(np);
	पूर्ण

	अगर (priv->chip_id != RCAR_GEN2) अणु
		मुक्त_irq(priv->tx_irqs[RAVB_NC], ndev);
		मुक्त_irq(priv->rx_irqs[RAVB_NC], ndev);
		मुक्त_irq(priv->tx_irqs[RAVB_BE], ndev);
		मुक्त_irq(priv->rx_irqs[RAVB_BE], ndev);
		मुक्त_irq(priv->emac_irq, ndev);
	पूर्ण
	मुक्त_irq(ndev->irq, ndev);

	napi_disable(&priv->napi[RAVB_NC]);
	napi_disable(&priv->napi[RAVB_BE]);

	/* Free all the skb's in the RX queue and the DMA buffers. */
	ravb_ring_मुक्त(ndev, RAVB_BE);
	ravb_ring_मुक्त(ndev, RAVB_NC);

	वापस 0;
पूर्ण

अटल पूर्णांक ravb_hwtstamp_get(काष्ठा net_device *ndev, काष्ठा अगरreq *req)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	काष्ठा hwtstamp_config config;

	config.flags = 0;
	config.tx_type = priv->tstamp_tx_ctrl ? HWTSTAMP_TX_ON :
						HWTSTAMP_TX_OFF;
	चयन (priv->tstamp_rx_ctrl & RAVB_RXTSTAMP_TYPE) अणु
	हाल RAVB_RXTSTAMP_TYPE_V2_L2_EVENT:
		config.rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		अवरोध;
	हाल RAVB_RXTSTAMP_TYPE_ALL:
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	शेष:
		config.rx_filter = HWTSTAMP_FILTER_NONE;
	पूर्ण

	वापस copy_to_user(req->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

/* Control hardware समय stamping */
अटल पूर्णांक ravb_hwtstamp_set(काष्ठा net_device *ndev, काष्ठा अगरreq *req)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	काष्ठा hwtstamp_config config;
	u32 tstamp_rx_ctrl = RAVB_RXTSTAMP_ENABLED;
	u32 tstamp_tx_ctrl;

	अगर (copy_from_user(&config, req->अगरr_data, माप(config)))
		वापस -EFAULT;

	/* Reserved क्रम future extensions */
	अगर (config.flags)
		वापस -EINVAL;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		tstamp_tx_ctrl = 0;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		tstamp_tx_ctrl = RAVB_TXTSTAMP_ENABLED;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		tstamp_rx_ctrl = 0;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		tstamp_rx_ctrl |= RAVB_RXTSTAMP_TYPE_V2_L2_EVENT;
		अवरोध;
	शेष:
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		tstamp_rx_ctrl |= RAVB_RXTSTAMP_TYPE_ALL;
	पूर्ण

	priv->tstamp_tx_ctrl = tstamp_tx_ctrl;
	priv->tstamp_rx_ctrl = tstamp_rx_ctrl;

	वापस copy_to_user(req->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

/* ioctl to device function */
अटल पूर्णांक ravb_करो_ioctl(काष्ठा net_device *ndev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा phy_device *phydev = ndev->phydev;

	अगर (!netअगर_running(ndev))
		वापस -EINVAL;

	अगर (!phydev)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल SIOCGHWTSTAMP:
		वापस ravb_hwtstamp_get(ndev, req);
	हाल SIOCSHWTSTAMP:
		वापस ravb_hwtstamp_set(ndev, req);
	पूर्ण

	वापस phy_mii_ioctl(phydev, req, cmd);
पूर्ण

अटल पूर्णांक ravb_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	ndev->mtu = new_mtu;

	अगर (netअगर_running(ndev)) अणु
		synchronize_irq(priv->emac_irq);
		ravb_emac_init(ndev);
	पूर्ण

	netdev_update_features(ndev);

	वापस 0;
पूर्ण

अटल व्योम ravb_set_rx_csum(काष्ठा net_device *ndev, bool enable)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	/* Disable TX and RX */
	ravb_rcv_snd_disable(ndev);

	/* Modअगरy RX Checksum setting */
	ravb_modअगरy(ndev, ECMR, ECMR_RCSC, enable ? ECMR_RCSC : 0);

	/* Enable TX and RX */
	ravb_rcv_snd_enable(ndev);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल पूर्णांक ravb_set_features(काष्ठा net_device *ndev,
			     netdev_features_t features)
अणु
	netdev_features_t changed = ndev->features ^ features;

	अगर (changed & NETIF_F_RXCSUM)
		ravb_set_rx_csum(ndev, features & NETIF_F_RXCSUM);

	ndev->features = features;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ravb_netdev_ops = अणु
	.nकरो_खोलो		= ravb_खोलो,
	.nकरो_stop		= ravb_बंद,
	.nकरो_start_xmit		= ravb_start_xmit,
	.nकरो_select_queue	= ravb_select_queue,
	.nकरो_get_stats		= ravb_get_stats,
	.nकरो_set_rx_mode	= ravb_set_rx_mode,
	.nकरो_tx_समयout		= ravb_tx_समयout,
	.nकरो_करो_ioctl		= ravb_करो_ioctl,
	.nकरो_change_mtu		= ravb_change_mtu,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_set_features	= ravb_set_features,
पूर्ण;

/* MDIO bus init function */
अटल पूर्णांक ravb_mdio_init(काष्ठा ravb_निजी *priv)
अणु
	काष्ठा platक्रमm_device *pdev = priv->pdev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक error;

	/* Bitbang init */
	priv->mdiobb.ops = &bb_ops;

	/* MII controller setting */
	priv->mii_bus = alloc_mdio_bitbang(&priv->mdiobb);
	अगर (!priv->mii_bus)
		वापस -ENOMEM;

	/* Hook up MII support क्रम ethtool */
	priv->mii_bus->name = "ravb_mii";
	priv->mii_bus->parent = dev;
	snम_लिखो(priv->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 pdev->name, pdev->id);

	/* Register MDIO bus */
	error = of_mdiobus_रेजिस्टर(priv->mii_bus, dev->of_node);
	अगर (error)
		जाओ out_मुक्त_bus;

	वापस 0;

out_मुक्त_bus:
	मुक्त_mdio_bitbang(priv->mii_bus);
	वापस error;
पूर्ण

/* MDIO bus release function */
अटल पूर्णांक ravb_mdio_release(काष्ठा ravb_निजी *priv)
अणु
	/* Unरेजिस्टर mdio bus */
	mdiobus_unरेजिस्टर(priv->mii_bus);

	/* Free bitbang info */
	मुक्त_mdio_bitbang(priv->mii_bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ravb_match_table[] = अणु
	अणु .compatible = "renesas,etheravb-r8a7790", .data = (व्योम *)RCAR_GEN2 पूर्ण,
	अणु .compatible = "renesas,etheravb-r8a7794", .data = (व्योम *)RCAR_GEN2 पूर्ण,
	अणु .compatible = "renesas,etheravb-rcar-gen2", .data = (व्योम *)RCAR_GEN2 पूर्ण,
	अणु .compatible = "renesas,etheravb-r8a7795", .data = (व्योम *)RCAR_GEN3 पूर्ण,
	अणु .compatible = "renesas,etheravb-rcar-gen3", .data = (व्योम *)RCAR_GEN3 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ravb_match_table);

अटल पूर्णांक ravb_set_gti(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	काष्ठा device *dev = ndev->dev.parent;
	अचिन्हित दीर्घ rate;
	uपूर्णांक64_t inc;

	rate = clk_get_rate(priv->clk);
	अगर (!rate)
		वापस -EINVAL;

	inc = 1000000000ULL << 20;
	करो_भाग(inc, rate);

	अगर (inc < GTI_TIV_MIN || inc > GTI_TIV_MAX) अणु
		dev_err(dev, "gti.tiv increment 0x%llx is outside the range 0x%x - 0x%x\n",
			inc, GTI_TIV_MIN, GTI_TIV_MAX);
		वापस -EINVAL;
	पूर्ण

	ravb_ग_लिखो(ndev, inc, GTI);

	वापस 0;
पूर्ण

अटल व्योम ravb_set_config_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	अगर (priv->chip_id == RCAR_GEN2) अणु
		ravb_modअगरy(ndev, CCC, CCC_OPC, CCC_OPC_CONFIG);
		/* Set CSEL value */
		ravb_modअगरy(ndev, CCC, CCC_CSEL, CCC_CSEL_HPB);
	पूर्ण अन्यथा अणु
		ravb_modअगरy(ndev, CCC, CCC_OPC, CCC_OPC_CONFIG |
			    CCC_GAC | CCC_CSEL_HPB);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा soc_device_attribute ravb_delay_mode_quirk_match[] = अणु
	अणु .soc_id = "r8a774c0" पूर्ण,
	अणु .soc_id = "r8a77990" पूर्ण,
	अणु .soc_id = "r8a77995" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

/* Set tx and rx घड़ी पूर्णांकernal delay modes */
अटल व्योम ravb_parse_delay_mode(काष्ठा device_node *np, काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	bool explicit_delay = false;
	u32 delay;

	अगर (!of_property_पढ़ो_u32(np, "rx-internal-delay-ps", &delay)) अणु
		/* Valid values are 0 and 1800, according to DT bindings */
		priv->rxcidm = !!delay;
		explicit_delay = true;
	पूर्ण
	अगर (!of_property_पढ़ो_u32(np, "tx-internal-delay-ps", &delay)) अणु
		/* Valid values are 0 and 2000, according to DT bindings */
		priv->txcidm = !!delay;
		explicit_delay = true;
	पूर्ण

	अगर (explicit_delay)
		वापस;

	/* Fall back to legacy rgmii-*id behavior */
	अगर (priv->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    priv->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) अणु
		priv->rxcidm = 1;
		priv->rgmii_override = 1;
	पूर्ण

	अगर (priv->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    priv->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID) अणु
		अगर (!WARN(soc_device_match(ravb_delay_mode_quirk_match),
			  "phy-mode %s requires TX clock internal delay mode which is not supported by this hardware revision. Please update device tree",
			  phy_modes(priv->phy_पूर्णांकerface))) अणु
			priv->txcidm = 1;
			priv->rgmii_override = 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ravb_set_delay_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	u32 set = 0;

	अगर (priv->rxcidm)
		set |= APSR_RDM;
	अगर (priv->txcidm)
		set |= APSR_TDM;
	ravb_modअगरy(ndev, APSR, APSR_RDM | APSR_TDM, set);
पूर्ण

अटल पूर्णांक ravb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा ravb_निजी *priv;
	क्रमागत ravb_chip_id chip_id;
	काष्ठा net_device *ndev;
	पूर्णांक error, irq, q;
	काष्ठा resource *res;
	पूर्णांक i;

	अगर (!np) अणु
		dev_err(&pdev->dev,
			"this driver is required to be instantiated from device tree\n");
		वापस -EINVAL;
	पूर्ण

	/* Get base address */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "invalid resource\n");
		वापस -EINVAL;
	पूर्ण

	ndev = alloc_etherdev_mqs(माप(काष्ठा ravb_निजी),
				  NUM_TX_QUEUE, NUM_RX_QUEUE);
	अगर (!ndev)
		वापस -ENOMEM;

	ndev->features = NETIF_F_RXCSUM;
	ndev->hw_features = NETIF_F_RXCSUM;

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	/* The Ether-specअगरic entries in the device काष्ठाure. */
	ndev->base_addr = res->start;

	chip_id = (क्रमागत ravb_chip_id)of_device_get_match_data(&pdev->dev);

	अगर (chip_id == RCAR_GEN3)
		irq = platक्रमm_get_irq_byname(pdev, "ch22");
	अन्यथा
		irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		error = irq;
		जाओ out_release;
	पूर्ण
	ndev->irq = irq;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	priv = netdev_priv(ndev);
	priv->ndev = ndev;
	priv->pdev = pdev;
	priv->num_tx_ring[RAVB_BE] = BE_TX_RING_SIZE;
	priv->num_rx_ring[RAVB_BE] = BE_RX_RING_SIZE;
	priv->num_tx_ring[RAVB_NC] = NC_TX_RING_SIZE;
	priv->num_rx_ring[RAVB_NC] = NC_RX_RING_SIZE;
	priv->addr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->addr)) अणु
		error = PTR_ERR(priv->addr);
		जाओ out_release;
	पूर्ण

	spin_lock_init(&priv->lock);
	INIT_WORK(&priv->work, ravb_tx_समयout_work);

	error = of_get_phy_mode(np, &priv->phy_पूर्णांकerface);
	अगर (error && error != -ENODEV)
		जाओ out_release;

	priv->no_avb_link = of_property_पढ़ो_bool(np, "renesas,no-ether-link");
	priv->avb_link_active_low =
		of_property_पढ़ो_bool(np, "renesas,ether-link-active-low");

	अगर (chip_id == RCAR_GEN3) अणु
		irq = platक्रमm_get_irq_byname(pdev, "ch24");
		अगर (irq < 0) अणु
			error = irq;
			जाओ out_release;
		पूर्ण
		priv->emac_irq = irq;
		क्रम (i = 0; i < NUM_RX_QUEUE; i++) अणु
			irq = platक्रमm_get_irq_byname(pdev, ravb_rx_irqs[i]);
			अगर (irq < 0) अणु
				error = irq;
				जाओ out_release;
			पूर्ण
			priv->rx_irqs[i] = irq;
		पूर्ण
		क्रम (i = 0; i < NUM_TX_QUEUE; i++) अणु
			irq = platक्रमm_get_irq_byname(pdev, ravb_tx_irqs[i]);
			अगर (irq < 0) अणु
				error = irq;
				जाओ out_release;
			पूर्ण
			priv->tx_irqs[i] = irq;
		पूर्ण
	पूर्ण

	priv->chip_id = chip_id;

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		error = PTR_ERR(priv->clk);
		जाओ out_release;
	पूर्ण

	priv->refclk = devm_clk_get_optional(&pdev->dev, "refclk");
	अगर (IS_ERR(priv->refclk)) अणु
		error = PTR_ERR(priv->refclk);
		जाओ out_release;
	पूर्ण
	clk_prepare_enable(priv->refclk);

	ndev->max_mtu = 2048 - (ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN);
	ndev->min_mtu = ETH_MIN_MTU;

	priv->num_tx_desc = chip_id == RCAR_GEN2 ?
		NUM_TX_DESC_GEN2 : NUM_TX_DESC_GEN3;

	/* Set function */
	ndev->netdev_ops = &ravb_netdev_ops;
	ndev->ethtool_ops = &ravb_ethtool_ops;

	/* Set AVB config mode */
	ravb_set_config_mode(ndev);

	/* Set GTI value */
	error = ravb_set_gti(ndev);
	अगर (error)
		जाओ out_disable_refclk;

	/* Request GTI loading */
	ravb_modअगरy(ndev, GCCR, GCCR_LTI, GCCR_LTI);

	अगर (priv->chip_id != RCAR_GEN2) अणु
		ravb_parse_delay_mode(np, ndev);
		ravb_set_delay_mode(ndev);
	पूर्ण

	/* Allocate descriptor base address table */
	priv->desc_bat_size = माप(काष्ठा ravb_desc) * DBAT_ENTRY_NUM;
	priv->desc_bat = dma_alloc_coherent(ndev->dev.parent, priv->desc_bat_size,
					    &priv->desc_bat_dma, GFP_KERNEL);
	अगर (!priv->desc_bat) अणु
		dev_err(&pdev->dev,
			"Cannot allocate desc base address table (size %d bytes)\n",
			priv->desc_bat_size);
		error = -ENOMEM;
		जाओ out_disable_refclk;
	पूर्ण
	क्रम (q = RAVB_BE; q < DBAT_ENTRY_NUM; q++)
		priv->desc_bat[q].die_dt = DT_EOS;
	ravb_ग_लिखो(ndev, priv->desc_bat_dma, DBAT);

	/* Initialise HW बारtamp list */
	INIT_LIST_HEAD(&priv->ts_skb_list);

	/* Initialise PTP Clock driver */
	अगर (chip_id != RCAR_GEN2)
		ravb_ptp_init(ndev, pdev);

	/* Debug message level */
	priv->msg_enable = RAVB_DEF_MSG_ENABLE;

	/* Read and set MAC address */
	ravb_पढ़ो_mac_address(np, ndev);
	अगर (!is_valid_ether_addr(ndev->dev_addr)) अणु
		dev_warn(&pdev->dev,
			 "no valid MAC address supplied, using a random one\n");
		eth_hw_addr_अक्रमom(ndev);
	पूर्ण

	/* MDIO bus init */
	error = ravb_mdio_init(priv);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to initialize MDIO\n");
		जाओ out_dma_मुक्त;
	पूर्ण

	netअगर_napi_add(ndev, &priv->napi[RAVB_BE], ravb_poll, 64);
	netअगर_napi_add(ndev, &priv->napi[RAVB_NC], ravb_poll, 64);

	/* Network device रेजिस्टर */
	error = रेजिस्टर_netdev(ndev);
	अगर (error)
		जाओ out_napi_del;

	device_set_wakeup_capable(&pdev->dev, 1);

	/* Prपूर्णांक device inक्रमmation */
	netdev_info(ndev, "Base address at %#x, %pM, IRQ %d.\n",
		    (u32)ndev->base_addr, ndev->dev_addr, ndev->irq);

	platक्रमm_set_drvdata(pdev, ndev);

	वापस 0;

out_napi_del:
	netअगर_napi_del(&priv->napi[RAVB_NC]);
	netअगर_napi_del(&priv->napi[RAVB_BE]);
	ravb_mdio_release(priv);
out_dma_मुक्त:
	dma_मुक्त_coherent(ndev->dev.parent, priv->desc_bat_size, priv->desc_bat,
			  priv->desc_bat_dma);

	/* Stop PTP Clock driver */
	अगर (chip_id != RCAR_GEN2)
		ravb_ptp_stop(ndev);
out_disable_refclk:
	clk_disable_unprepare(priv->refclk);
out_release:
	मुक्त_netdev(ndev);

	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस error;
पूर्ण

अटल पूर्णांक ravb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	/* Stop PTP Clock driver */
	अगर (priv->chip_id != RCAR_GEN2)
		ravb_ptp_stop(ndev);

	clk_disable_unprepare(priv->refclk);

	dma_मुक्त_coherent(ndev->dev.parent, priv->desc_bat_size, priv->desc_bat,
			  priv->desc_bat_dma);
	/* Set reset mode */
	ravb_ग_लिखो(ndev, CCC_OPC_RESET, CCC);
	pm_runसमय_put_sync(&pdev->dev);
	unरेजिस्टर_netdev(ndev);
	netअगर_napi_del(&priv->napi[RAVB_NC]);
	netअगर_napi_del(&priv->napi[RAVB_BE]);
	ravb_mdio_release(priv);
	pm_runसमय_disable(&pdev->dev);
	मुक्त_netdev(ndev);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक ravb_wol_setup(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	/* Disable पूर्णांकerrupts by clearing the पूर्णांकerrupt masks. */
	ravb_ग_लिखो(ndev, 0, RIC0);
	ravb_ग_लिखो(ndev, 0, RIC2);
	ravb_ग_लिखो(ndev, 0, TIC);

	/* Only allow ECI पूर्णांकerrupts */
	synchronize_irq(priv->emac_irq);
	napi_disable(&priv->napi[RAVB_NC]);
	napi_disable(&priv->napi[RAVB_BE]);
	ravb_ग_लिखो(ndev, ECSIPR_MPDIP, ECSIPR);

	/* Enable MagicPacket */
	ravb_modअगरy(ndev, ECMR, ECMR_MPDE, ECMR_MPDE);

	वापस enable_irq_wake(priv->emac_irq);
पूर्ण

अटल पूर्णांक ravb_wol_restore(काष्ठा net_device *ndev)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक ret;

	napi_enable(&priv->napi[RAVB_NC]);
	napi_enable(&priv->napi[RAVB_BE]);

	/* Disable MagicPacket */
	ravb_modअगरy(ndev, ECMR, ECMR_MPDE, 0);

	ret = ravb_बंद(ndev);
	अगर (ret < 0)
		वापस ret;

	वापस disable_irq_wake(priv->emac_irq);
पूर्ण

अटल पूर्णांक __maybe_unused ravb_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक ret;

	अगर (!netअगर_running(ndev))
		वापस 0;

	netअगर_device_detach(ndev);

	अगर (priv->wol_enabled)
		ret = ravb_wol_setup(ndev);
	अन्यथा
		ret = ravb_बंद(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ravb_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);
	पूर्णांक ret = 0;

	/* If WoL is enabled set reset mode to rearm the WoL logic */
	अगर (priv->wol_enabled)
		ravb_ग_लिखो(ndev, CCC_OPC_RESET, CCC);

	/* All रेजिस्टर have been reset to शेष values.
	 * Restore all रेजिस्टरs which where setup at probe समय and
	 * reखोलो device अगर it was running beक्रमe प्रणाली suspended.
	 */

	/* Set AVB config mode */
	ravb_set_config_mode(ndev);

	/* Set GTI value */
	ret = ravb_set_gti(ndev);
	अगर (ret)
		वापस ret;

	/* Request GTI loading */
	ravb_modअगरy(ndev, GCCR, GCCR_LTI, GCCR_LTI);

	अगर (priv->chip_id != RCAR_GEN2)
		ravb_set_delay_mode(ndev);

	/* Restore descriptor base address table */
	ravb_ग_लिखो(ndev, priv->desc_bat_dma, DBAT);

	अगर (netअगर_running(ndev)) अणु
		अगर (priv->wol_enabled) अणु
			ret = ravb_wol_restore(ndev);
			अगर (ret)
				वापस ret;
		पूर्ण
		ret = ravb_खोलो(ndev);
		अगर (ret < 0)
			वापस ret;
		netअगर_device_attach(ndev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ravb_runसमय_nop(काष्ठा device *dev)
अणु
	/* Runसमय PM callback shared between ->runसमय_suspend()
	 * and ->runसमय_resume(). Simply वापसs success.
	 *
	 * This driver re-initializes all रेजिस्टरs after
	 * pm_runसमय_get_sync() anyway so there is no need
	 * to save and restore रेजिस्टरs here.
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ravb_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ravb_suspend, ravb_resume)
	SET_RUNTIME_PM_OPS(ravb_runसमय_nop, ravb_runसमय_nop, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver ravb_driver = अणु
	.probe		= ravb_probe,
	.हटाओ		= ravb_हटाओ,
	.driver = अणु
		.name	= "ravb",
		.pm	= &ravb_dev_pm_ops,
		.of_match_table = ravb_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ravb_driver);

MODULE_AUTHOR("Mitsuhiro Kimura, Masaru Nagai");
MODULE_DESCRIPTION("Renesas Ethernet AVB driver");
MODULE_LICENSE("GPL v2");
