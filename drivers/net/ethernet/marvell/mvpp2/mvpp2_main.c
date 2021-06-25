<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Marvell PPv2 network controller क्रम Armada 375 SoC.
 *
 * Copyright (C) 2014 Marvell
 *
 * Marcin Wojtas <mw@semihalf.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/mbus.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/phylink.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/clk.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/regmap.h>
#समावेश <uapi/linux/ppp_defs.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/tso.h>
#समावेश <linux/bpf_trace.h>

#समावेश "mvpp2.h"
#समावेश "mvpp2_prs.h"
#समावेश "mvpp2_cls.h"

क्रमागत mvpp2_bm_pool_log_num अणु
	MVPP2_BM_SHORT,
	MVPP2_BM_LONG,
	MVPP2_BM_JUMBO,
	MVPP2_BM_POOLS_NUM
पूर्ण;

अटल काष्ठा अणु
	पूर्णांक pkt_size;
	पूर्णांक buf_num;
पूर्ण mvpp2_pools[MVPP2_BM_POOLS_NUM];

/* The prototype is added here to be used in start_dev when using ACPI. This
 * will be हटाओd once phylink is used क्रम all modes (dt+ACPI).
 */
अटल व्योम mvpp2_acpi_start(काष्ठा mvpp2_port *port);

/* Queue modes */
#घोषणा MVPP2_QDIST_SINGLE_MODE	0
#घोषणा MVPP2_QDIST_MULTI_MODE	1

अटल पूर्णांक queue_mode = MVPP2_QDIST_MULTI_MODE;

module_param(queue_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(queue_mode, "Set queue_mode (single=0, multi=1)");

/* Utility/helper methods */

व्योम mvpp2_ग_लिखो(काष्ठा mvpp2 *priv, u32 offset, u32 data)
अणु
	ग_लिखोl(data, priv->swth_base[0] + offset);
पूर्ण

u32 mvpp2_पढ़ो(काष्ठा mvpp2 *priv, u32 offset)
अणु
	वापस पढ़ोl(priv->swth_base[0] + offset);
पूर्ण

अटल u32 mvpp2_पढ़ो_relaxed(काष्ठा mvpp2 *priv, u32 offset)
अणु
	वापस पढ़ोl_relaxed(priv->swth_base[0] + offset);
पूर्ण

अटल अंतरभूत u32 mvpp2_cpu_to_thपढ़ो(काष्ठा mvpp2 *priv, पूर्णांक cpu)
अणु
	वापस cpu % priv->nthपढ़ोs;
पूर्ण

अटल व्योम mvpp2_cm3_ग_लिखो(काष्ठा mvpp2 *priv, u32 offset, u32 data)
अणु
	ग_लिखोl(data, priv->cm3_base + offset);
पूर्ण

अटल u32 mvpp2_cm3_पढ़ो(काष्ठा mvpp2 *priv, u32 offset)
अणु
	वापस पढ़ोl(priv->cm3_base + offset);
पूर्ण

अटल काष्ठा page_pool *
mvpp2_create_page_pool(काष्ठा device *dev, पूर्णांक num, पूर्णांक len,
		       क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा page_pool_params pp_params = अणु
		/* पूर्णांकernal DMA mapping in page_pool */
		.flags = PP_FLAG_DMA_MAP | PP_FLAG_DMA_SYNC_DEV,
		.pool_size = num,
		.nid = NUMA_NO_NODE,
		.dev = dev,
		.dma_dir = dma_dir,
		.offset = MVPP2_SKB_HEADROOM,
		.max_len = len,
	पूर्ण;

	वापस page_pool_create(&pp_params);
पूर्ण

/* These accessors should be used to access:
 *
 * - per-thपढ़ो रेजिस्टरs, where each thपढ़ो has its own copy of the
 *   रेजिस्टर.
 *
 *   MVPP2_BM_VIRT_ALLOC_REG
 *   MVPP2_BM_ADDR_HIGH_ALLOC
 *   MVPP22_BM_ADDR_HIGH_RLS_REG
 *   MVPP2_BM_VIRT_RLS_REG
 *   MVPP2_ISR_RX_TX_CAUSE_REG
 *   MVPP2_ISR_RX_TX_MASK_REG
 *   MVPP2_TXQ_NUM_REG
 *   MVPP2_AGGR_TXQ_UPDATE_REG
 *   MVPP2_TXQ_RSVD_REQ_REG
 *   MVPP2_TXQ_RSVD_RSLT_REG
 *   MVPP2_TXQ_SENT_REG
 *   MVPP2_RXQ_NUM_REG
 *
 * - global रेजिस्टरs that must be accessed through a specअगरic thपढ़ो
 *   winकरोw, because they are related to an access to a per-thपढ़ो
 *   रेजिस्टर
 *
 *   MVPP2_BM_PHY_ALLOC_REG    (related to MVPP2_BM_VIRT_ALLOC_REG)
 *   MVPP2_BM_PHY_RLS_REG      (related to MVPP2_BM_VIRT_RLS_REG)
 *   MVPP2_RXQ_THRESH_REG      (related to MVPP2_RXQ_NUM_REG)
 *   MVPP2_RXQ_DESC_ADDR_REG   (related to MVPP2_RXQ_NUM_REG)
 *   MVPP2_RXQ_DESC_SIZE_REG   (related to MVPP2_RXQ_NUM_REG)
 *   MVPP2_RXQ_INDEX_REG       (related to MVPP2_RXQ_NUM_REG)
 *   MVPP2_TXQ_PENDING_REG     (related to MVPP2_TXQ_NUM_REG)
 *   MVPP2_TXQ_DESC_ADDR_REG   (related to MVPP2_TXQ_NUM_REG)
 *   MVPP2_TXQ_DESC_SIZE_REG   (related to MVPP2_TXQ_NUM_REG)
 *   MVPP2_TXQ_INDEX_REG       (related to MVPP2_TXQ_NUM_REG)
 *   MVPP2_TXQ_PENDING_REG     (related to MVPP2_TXQ_NUM_REG)
 *   MVPP2_TXQ_PREF_BUF_REG    (related to MVPP2_TXQ_NUM_REG)
 *   MVPP2_TXQ_PREF_BUF_REG    (related to MVPP2_TXQ_NUM_REG)
 */
अटल व्योम mvpp2_thपढ़ो_ग_लिखो(काष्ठा mvpp2 *priv, अचिन्हित पूर्णांक thपढ़ो,
			       u32 offset, u32 data)
अणु
	ग_लिखोl(data, priv->swth_base[thपढ़ो] + offset);
पूर्ण

अटल u32 mvpp2_thपढ़ो_पढ़ो(काष्ठा mvpp2 *priv, अचिन्हित पूर्णांक thपढ़ो,
			     u32 offset)
अणु
	वापस पढ़ोl(priv->swth_base[thपढ़ो] + offset);
पूर्ण

अटल व्योम mvpp2_thपढ़ो_ग_लिखो_relaxed(काष्ठा mvpp2 *priv, अचिन्हित पूर्णांक thपढ़ो,
				       u32 offset, u32 data)
अणु
	ग_लिखोl_relaxed(data, priv->swth_base[thपढ़ो] + offset);
पूर्ण

अटल u32 mvpp2_thपढ़ो_पढ़ो_relaxed(काष्ठा mvpp2 *priv, अचिन्हित पूर्णांक thपढ़ो,
				     u32 offset)
अणु
	वापस पढ़ोl_relaxed(priv->swth_base[thपढ़ो] + offset);
पूर्ण

अटल dma_addr_t mvpp2_txdesc_dma_addr_get(काष्ठा mvpp2_port *port,
					    काष्ठा mvpp2_tx_desc *tx_desc)
अणु
	अगर (port->priv->hw_version == MVPP21)
		वापस le32_to_cpu(tx_desc->pp21.buf_dma_addr);
	अन्यथा
		वापस le64_to_cpu(tx_desc->pp22.buf_dma_addr_ptp) &
		       MVPP2_DESC_DMA_MASK;
पूर्ण

अटल व्योम mvpp2_txdesc_dma_addr_set(काष्ठा mvpp2_port *port,
				      काष्ठा mvpp2_tx_desc *tx_desc,
				      dma_addr_t dma_addr)
अणु
	dma_addr_t addr, offset;

	addr = dma_addr & ~MVPP2_TX_DESC_ALIGN;
	offset = dma_addr & MVPP2_TX_DESC_ALIGN;

	अगर (port->priv->hw_version == MVPP21) अणु
		tx_desc->pp21.buf_dma_addr = cpu_to_le32(addr);
		tx_desc->pp21.packet_offset = offset;
	पूर्ण अन्यथा अणु
		__le64 val = cpu_to_le64(addr);

		tx_desc->pp22.buf_dma_addr_ptp &= ~cpu_to_le64(MVPP2_DESC_DMA_MASK);
		tx_desc->pp22.buf_dma_addr_ptp |= val;
		tx_desc->pp22.packet_offset = offset;
	पूर्ण
पूर्ण

अटल माप_प्रकार mvpp2_txdesc_size_get(काष्ठा mvpp2_port *port,
				    काष्ठा mvpp2_tx_desc *tx_desc)
अणु
	अगर (port->priv->hw_version == MVPP21)
		वापस le16_to_cpu(tx_desc->pp21.data_size);
	अन्यथा
		वापस le16_to_cpu(tx_desc->pp22.data_size);
पूर्ण

अटल व्योम mvpp2_txdesc_size_set(काष्ठा mvpp2_port *port,
				  काष्ठा mvpp2_tx_desc *tx_desc,
				  माप_प्रकार size)
अणु
	अगर (port->priv->hw_version == MVPP21)
		tx_desc->pp21.data_size = cpu_to_le16(size);
	अन्यथा
		tx_desc->pp22.data_size = cpu_to_le16(size);
पूर्ण

अटल व्योम mvpp2_txdesc_txq_set(काष्ठा mvpp2_port *port,
				 काष्ठा mvpp2_tx_desc *tx_desc,
				 अचिन्हित पूर्णांक txq)
अणु
	अगर (port->priv->hw_version == MVPP21)
		tx_desc->pp21.phys_txq = txq;
	अन्यथा
		tx_desc->pp22.phys_txq = txq;
पूर्ण

अटल व्योम mvpp2_txdesc_cmd_set(काष्ठा mvpp2_port *port,
				 काष्ठा mvpp2_tx_desc *tx_desc,
				 अचिन्हित पूर्णांक command)
अणु
	अगर (port->priv->hw_version == MVPP21)
		tx_desc->pp21.command = cpu_to_le32(command);
	अन्यथा
		tx_desc->pp22.command = cpu_to_le32(command);
पूर्ण

अटल अचिन्हित पूर्णांक mvpp2_txdesc_offset_get(काष्ठा mvpp2_port *port,
					    काष्ठा mvpp2_tx_desc *tx_desc)
अणु
	अगर (port->priv->hw_version == MVPP21)
		वापस tx_desc->pp21.packet_offset;
	अन्यथा
		वापस tx_desc->pp22.packet_offset;
पूर्ण

अटल dma_addr_t mvpp2_rxdesc_dma_addr_get(काष्ठा mvpp2_port *port,
					    काष्ठा mvpp2_rx_desc *rx_desc)
अणु
	अगर (port->priv->hw_version == MVPP21)
		वापस le32_to_cpu(rx_desc->pp21.buf_dma_addr);
	अन्यथा
		वापस le64_to_cpu(rx_desc->pp22.buf_dma_addr_key_hash) &
		       MVPP2_DESC_DMA_MASK;
पूर्ण

अटल अचिन्हित दीर्घ mvpp2_rxdesc_cookie_get(काष्ठा mvpp2_port *port,
					     काष्ठा mvpp2_rx_desc *rx_desc)
अणु
	अगर (port->priv->hw_version == MVPP21)
		वापस le32_to_cpu(rx_desc->pp21.buf_cookie);
	अन्यथा
		वापस le64_to_cpu(rx_desc->pp22.buf_cookie_misc) &
		       MVPP2_DESC_DMA_MASK;
पूर्ण

अटल माप_प्रकार mvpp2_rxdesc_size_get(काष्ठा mvpp2_port *port,
				    काष्ठा mvpp2_rx_desc *rx_desc)
अणु
	अगर (port->priv->hw_version == MVPP21)
		वापस le16_to_cpu(rx_desc->pp21.data_size);
	अन्यथा
		वापस le16_to_cpu(rx_desc->pp22.data_size);
पूर्ण

अटल u32 mvpp2_rxdesc_status_get(काष्ठा mvpp2_port *port,
				   काष्ठा mvpp2_rx_desc *rx_desc)
अणु
	अगर (port->priv->hw_version == MVPP21)
		वापस le32_to_cpu(rx_desc->pp21.status);
	अन्यथा
		वापस le32_to_cpu(rx_desc->pp22.status);
पूर्ण

अटल व्योम mvpp2_txq_inc_get(काष्ठा mvpp2_txq_pcpu *txq_pcpu)
अणु
	txq_pcpu->txq_get_index++;
	अगर (txq_pcpu->txq_get_index == txq_pcpu->size)
		txq_pcpu->txq_get_index = 0;
पूर्ण

अटल व्योम mvpp2_txq_inc_put(काष्ठा mvpp2_port *port,
			      काष्ठा mvpp2_txq_pcpu *txq_pcpu,
			      व्योम *data,
			      काष्ठा mvpp2_tx_desc *tx_desc,
			      क्रमागत mvpp2_tx_buf_type buf_type)
अणु
	काष्ठा mvpp2_txq_pcpu_buf *tx_buf =
		txq_pcpu->buffs + txq_pcpu->txq_put_index;
	tx_buf->type = buf_type;
	अगर (buf_type == MVPP2_TYPE_SKB)
		tx_buf->skb = data;
	अन्यथा
		tx_buf->xdpf = data;
	tx_buf->size = mvpp2_txdesc_size_get(port, tx_desc);
	tx_buf->dma = mvpp2_txdesc_dma_addr_get(port, tx_desc) +
		mvpp2_txdesc_offset_get(port, tx_desc);
	txq_pcpu->txq_put_index++;
	अगर (txq_pcpu->txq_put_index == txq_pcpu->size)
		txq_pcpu->txq_put_index = 0;
पूर्ण

/* Get number of maximum RXQ */
अटल पूर्णांक mvpp2_get_nrxqs(काष्ठा mvpp2 *priv)
अणु
	अचिन्हित पूर्णांक nrxqs;

	अगर (priv->hw_version >= MVPP22 && queue_mode == MVPP2_QDIST_SINGLE_MODE)
		वापस 1;

	/* According to the PPv2.2 datasheet and our experiments on
	 * PPv2.1, RX queues have an allocation granularity of 4 (when
	 * more than a single one on PPv2.2).
	 * Round up to nearest multiple of 4.
	 */
	nrxqs = (num_possible_cpus() + 3) & ~0x3;
	अगर (nrxqs > MVPP2_PORT_MAX_RXQ)
		nrxqs = MVPP2_PORT_MAX_RXQ;

	वापस nrxqs;
पूर्ण

/* Get number of physical egress port */
अटल अंतरभूत पूर्णांक mvpp2_egress_port(काष्ठा mvpp2_port *port)
अणु
	वापस MVPP2_MAX_TCONT + port->id;
पूर्ण

/* Get number of physical TXQ */
अटल अंतरभूत पूर्णांक mvpp2_txq_phys(पूर्णांक port, पूर्णांक txq)
अणु
	वापस (MVPP2_MAX_TCONT + port) * MVPP2_MAX_TXQ + txq;
पूर्ण

/* Returns a काष्ठा page अगर page_pool is set, otherwise a buffer */
अटल व्योम *mvpp2_frag_alloc(स्थिर काष्ठा mvpp2_bm_pool *pool,
			      काष्ठा page_pool *page_pool)
अणु
	अगर (page_pool)
		वापस page_pool_dev_alloc_pages(page_pool);

	अगर (likely(pool->frag_size <= PAGE_SIZE))
		वापस netdev_alloc_frag(pool->frag_size);

	वापस kदो_स्मृति(pool->frag_size, GFP_ATOMIC);
पूर्ण

अटल व्योम mvpp2_frag_मुक्त(स्थिर काष्ठा mvpp2_bm_pool *pool,
			    काष्ठा page_pool *page_pool, व्योम *data)
अणु
	अगर (page_pool)
		page_pool_put_full_page(page_pool, virt_to_head_page(data), false);
	अन्यथा अगर (likely(pool->frag_size <= PAGE_SIZE))
		skb_मुक्त_frag(data);
	अन्यथा
		kमुक्त(data);
पूर्ण

/* Buffer Manager configuration routines */

/* Create pool */
अटल पूर्णांक mvpp2_bm_pool_create(काष्ठा device *dev, काष्ठा mvpp2 *priv,
				काष्ठा mvpp2_bm_pool *bm_pool, पूर्णांक size)
अणु
	u32 val;

	/* Number of buffer poपूर्णांकers must be a multiple of 16, as per
	 * hardware स्थिरraपूर्णांकs
	 */
	अगर (!IS_ALIGNED(size, 16))
		वापस -EINVAL;

	/* PPv2.1 needs 8 bytes per buffer poपूर्णांकer, PPv2.2 and PPv2.3 needs 16
	 * bytes per buffer poपूर्णांकer
	 */
	अगर (priv->hw_version == MVPP21)
		bm_pool->size_bytes = 2 * माप(u32) * size;
	अन्यथा
		bm_pool->size_bytes = 2 * माप(u64) * size;

	bm_pool->virt_addr = dma_alloc_coherent(dev, bm_pool->size_bytes,
						&bm_pool->dma_addr,
						GFP_KERNEL);
	अगर (!bm_pool->virt_addr)
		वापस -ENOMEM;

	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)bm_pool->virt_addr,
			MVPP2_BM_POOL_PTR_ALIGN)) अणु
		dma_मुक्त_coherent(dev, bm_pool->size_bytes,
				  bm_pool->virt_addr, bm_pool->dma_addr);
		dev_err(dev, "BM pool %d is not %d bytes aligned\n",
			bm_pool->id, MVPP2_BM_POOL_PTR_ALIGN);
		वापस -ENOMEM;
	पूर्ण

	mvpp2_ग_लिखो(priv, MVPP2_BM_POOL_BASE_REG(bm_pool->id),
		    lower_32_bits(bm_pool->dma_addr));
	mvpp2_ग_लिखो(priv, MVPP2_BM_POOL_SIZE_REG(bm_pool->id), size);

	val = mvpp2_पढ़ो(priv, MVPP2_BM_POOL_CTRL_REG(bm_pool->id));
	val |= MVPP2_BM_START_MASK;

	val &= ~MVPP2_BM_LOW_THRESH_MASK;
	val &= ~MVPP2_BM_HIGH_THRESH_MASK;

	/* Set 8 Pools BPPI threshold क्रम MVPP23 */
	अगर (priv->hw_version == MVPP23) अणु
		val |= MVPP2_BM_LOW_THRESH_VALUE(MVPP23_BM_BPPI_LOW_THRESH);
		val |= MVPP2_BM_HIGH_THRESH_VALUE(MVPP23_BM_BPPI_HIGH_THRESH);
	पूर्ण अन्यथा अणु
		val |= MVPP2_BM_LOW_THRESH_VALUE(MVPP2_BM_BPPI_LOW_THRESH);
		val |= MVPP2_BM_HIGH_THRESH_VALUE(MVPP2_BM_BPPI_HIGH_THRESH);
	पूर्ण

	mvpp2_ग_लिखो(priv, MVPP2_BM_POOL_CTRL_REG(bm_pool->id), val);

	bm_pool->size = size;
	bm_pool->pkt_size = 0;
	bm_pool->buf_num = 0;

	वापस 0;
पूर्ण

/* Set pool buffer size */
अटल व्योम mvpp2_bm_pool_bufsize_set(काष्ठा mvpp2 *priv,
				      काष्ठा mvpp2_bm_pool *bm_pool,
				      पूर्णांक buf_size)
अणु
	u32 val;

	bm_pool->buf_size = buf_size;

	val = ALIGN(buf_size, 1 << MVPP2_POOL_BUF_SIZE_OFFSET);
	mvpp2_ग_लिखो(priv, MVPP2_POOL_BUF_SIZE_REG(bm_pool->id), val);
पूर्ण

अटल व्योम mvpp2_bm_bufs_get_addrs(काष्ठा device *dev, काष्ठा mvpp2 *priv,
				    काष्ठा mvpp2_bm_pool *bm_pool,
				    dma_addr_t *dma_addr,
				    phys_addr_t *phys_addr)
अणु
	अचिन्हित पूर्णांक thपढ़ो = mvpp2_cpu_to_thपढ़ो(priv, get_cpu());

	*dma_addr = mvpp2_thपढ़ो_पढ़ो(priv, thपढ़ो,
				      MVPP2_BM_PHY_ALLOC_REG(bm_pool->id));
	*phys_addr = mvpp2_thपढ़ो_पढ़ो(priv, thपढ़ो, MVPP2_BM_VIRT_ALLOC_REG);

	अगर (priv->hw_version >= MVPP22) अणु
		u32 val;
		u32 dma_addr_highbits, phys_addr_highbits;

		val = mvpp2_thपढ़ो_पढ़ो(priv, thपढ़ो, MVPP22_BM_ADDR_HIGH_ALLOC);
		dma_addr_highbits = (val & MVPP22_BM_ADDR_HIGH_PHYS_MASK);
		phys_addr_highbits = (val & MVPP22_BM_ADDR_HIGH_VIRT_MASK) >>
			MVPP22_BM_ADDR_HIGH_VIRT_SHIFT;

		अगर (माप(dma_addr_t) == 8)
			*dma_addr |= (u64)dma_addr_highbits << 32;

		अगर (माप(phys_addr_t) == 8)
			*phys_addr |= (u64)phys_addr_highbits << 32;
	पूर्ण

	put_cpu();
पूर्ण

/* Free all buffers from the pool */
अटल व्योम mvpp2_bm_bufs_मुक्त(काष्ठा device *dev, काष्ठा mvpp2 *priv,
			       काष्ठा mvpp2_bm_pool *bm_pool, पूर्णांक buf_num)
अणु
	काष्ठा page_pool *pp = शून्य;
	पूर्णांक i;

	अगर (buf_num > bm_pool->buf_num) अणु
		WARN(1, "Pool does not have so many bufs pool(%d) bufs(%d)\n",
		     bm_pool->id, buf_num);
		buf_num = bm_pool->buf_num;
	पूर्ण

	अगर (priv->percpu_pools)
		pp = priv->page_pool[bm_pool->id];

	क्रम (i = 0; i < buf_num; i++) अणु
		dma_addr_t buf_dma_addr;
		phys_addr_t buf_phys_addr;
		व्योम *data;

		mvpp2_bm_bufs_get_addrs(dev, priv, bm_pool,
					&buf_dma_addr, &buf_phys_addr);

		अगर (!pp)
			dma_unmap_single(dev, buf_dma_addr,
					 bm_pool->buf_size, DMA_FROM_DEVICE);

		data = (व्योम *)phys_to_virt(buf_phys_addr);
		अगर (!data)
			अवरोध;

		mvpp2_frag_मुक्त(bm_pool, pp, data);
	पूर्ण

	/* Update BM driver with number of buffers हटाओd from pool */
	bm_pool->buf_num -= i;
पूर्ण

/* Check number of buffers in BM pool */
अटल पूर्णांक mvpp2_check_hw_buf_num(काष्ठा mvpp2 *priv, काष्ठा mvpp2_bm_pool *bm_pool)
अणु
	पूर्णांक buf_num = 0;

	buf_num += mvpp2_पढ़ो(priv, MVPP2_BM_POOL_PTRS_NUM_REG(bm_pool->id)) &
				    MVPP22_BM_POOL_PTRS_NUM_MASK;
	buf_num += mvpp2_पढ़ो(priv, MVPP2_BM_BPPI_PTRS_NUM_REG(bm_pool->id)) &
				    MVPP2_BM_BPPI_PTR_NUM_MASK;

	/* HW has one buffer पढ़ोy which is not reflected in the counters */
	अगर (buf_num)
		buf_num += 1;

	वापस buf_num;
पूर्ण

/* Cleanup pool */
अटल पूर्णांक mvpp2_bm_pool_destroy(काष्ठा device *dev, काष्ठा mvpp2 *priv,
				 काष्ठा mvpp2_bm_pool *bm_pool)
अणु
	पूर्णांक buf_num;
	u32 val;

	buf_num = mvpp2_check_hw_buf_num(priv, bm_pool);
	mvpp2_bm_bufs_मुक्त(dev, priv, bm_pool, buf_num);

	/* Check buffer counters after मुक्त */
	buf_num = mvpp2_check_hw_buf_num(priv, bm_pool);
	अगर (buf_num) अणु
		WARN(1, "cannot free all buffers in pool %d, buf_num left %d\n",
		     bm_pool->id, bm_pool->buf_num);
		वापस 0;
	पूर्ण

	val = mvpp2_पढ़ो(priv, MVPP2_BM_POOL_CTRL_REG(bm_pool->id));
	val |= MVPP2_BM_STOP_MASK;
	mvpp2_ग_लिखो(priv, MVPP2_BM_POOL_CTRL_REG(bm_pool->id), val);

	अगर (priv->percpu_pools) अणु
		page_pool_destroy(priv->page_pool[bm_pool->id]);
		priv->page_pool[bm_pool->id] = शून्य;
	पूर्ण

	dma_मुक्त_coherent(dev, bm_pool->size_bytes,
			  bm_pool->virt_addr,
			  bm_pool->dma_addr);
	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_bm_pools_init(काष्ठा device *dev, काष्ठा mvpp2 *priv)
अणु
	पूर्णांक i, err, size, poolnum = MVPP2_BM_POOLS_NUM;
	काष्ठा mvpp2_bm_pool *bm_pool;

	अगर (priv->percpu_pools)
		poolnum = mvpp2_get_nrxqs(priv) * 2;

	/* Create all pools with maximum size */
	size = MVPP2_BM_POOL_SIZE_MAX;
	क्रम (i = 0; i < poolnum; i++) अणु
		bm_pool = &priv->bm_pools[i];
		bm_pool->id = i;
		err = mvpp2_bm_pool_create(dev, priv, bm_pool, size);
		अगर (err)
			जाओ err_unroll_pools;
		mvpp2_bm_pool_bufsize_set(priv, bm_pool, 0);
	पूर्ण
	वापस 0;

err_unroll_pools:
	dev_err(dev, "failed to create BM pool %d, size %d\n", i, size);
	क्रम (i = i - 1; i >= 0; i--)
		mvpp2_bm_pool_destroy(dev, priv, &priv->bm_pools[i]);
	वापस err;
पूर्ण

/* Routine enable PPv23 8 pool mode */
अटल व्योम mvpp23_bm_set_8pool_mode(काष्ठा mvpp2 *priv)
अणु
	पूर्णांक val;

	val = mvpp2_पढ़ो(priv, MVPP22_BM_POOL_BASE_ADDR_HIGH_REG);
	val |= MVPP23_BM_8POOL_MODE;
	mvpp2_ग_लिखो(priv, MVPP22_BM_POOL_BASE_ADDR_HIGH_REG, val);
पूर्ण

अटल पूर्णांक mvpp2_bm_init(काष्ठा device *dev, काष्ठा mvpp2 *priv)
अणु
	क्रमागत dma_data_direction dma_dir = DMA_FROM_DEVICE;
	पूर्णांक i, err, poolnum = MVPP2_BM_POOLS_NUM;
	काष्ठा mvpp2_port *port;

	अगर (priv->percpu_pools) अणु
		क्रम (i = 0; i < priv->port_count; i++) अणु
			port = priv->port_list[i];
			अगर (port->xdp_prog) अणु
				dma_dir = DMA_BIसूचीECTIONAL;
				अवरोध;
			पूर्ण
		पूर्ण

		poolnum = mvpp2_get_nrxqs(priv) * 2;
		क्रम (i = 0; i < poolnum; i++) अणु
			/* the pool in use */
			पूर्णांक pn = i / (poolnum / 2);

			priv->page_pool[i] =
				mvpp2_create_page_pool(dev,
						       mvpp2_pools[pn].buf_num,
						       mvpp2_pools[pn].pkt_size,
						       dma_dir);
			अगर (IS_ERR(priv->page_pool[i])) अणु
				पूर्णांक j;

				क्रम (j = 0; j < i; j++) अणु
					page_pool_destroy(priv->page_pool[j]);
					priv->page_pool[j] = शून्य;
				पूर्ण
				वापस PTR_ERR(priv->page_pool[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	dev_info(dev, "using %d %s buffers\n", poolnum,
		 priv->percpu_pools ? "per-cpu" : "shared");

	क्रम (i = 0; i < poolnum; i++) अणु
		/* Mask BM all पूर्णांकerrupts */
		mvpp2_ग_लिखो(priv, MVPP2_BM_INTR_MASK_REG(i), 0);
		/* Clear BM cause रेजिस्टर */
		mvpp2_ग_लिखो(priv, MVPP2_BM_INTR_CAUSE_REG(i), 0);
	पूर्ण

	/* Allocate and initialize BM pools */
	priv->bm_pools = devm_kसुस्मृति(dev, poolnum,
				      माप(*priv->bm_pools), GFP_KERNEL);
	अगर (!priv->bm_pools)
		वापस -ENOMEM;

	अगर (priv->hw_version == MVPP23)
		mvpp23_bm_set_8pool_mode(priv);

	err = mvpp2_bm_pools_init(dev, priv);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल व्योम mvpp2_setup_bm_pool(व्योम)
अणु
	/* Short pool */
	mvpp2_pools[MVPP2_BM_SHORT].buf_num  = MVPP2_BM_SHORT_BUF_NUM;
	mvpp2_pools[MVPP2_BM_SHORT].pkt_size = MVPP2_BM_SHORT_PKT_SIZE;

	/* Long pool */
	mvpp2_pools[MVPP2_BM_LONG].buf_num  = MVPP2_BM_LONG_BUF_NUM;
	mvpp2_pools[MVPP2_BM_LONG].pkt_size = MVPP2_BM_LONG_PKT_SIZE;

	/* Jumbo pool */
	mvpp2_pools[MVPP2_BM_JUMBO].buf_num  = MVPP2_BM_JUMBO_BUF_NUM;
	mvpp2_pools[MVPP2_BM_JUMBO].pkt_size = MVPP2_BM_JUMBO_PKT_SIZE;
पूर्ण

/* Attach दीर्घ pool to rxq */
अटल व्योम mvpp2_rxq_दीर्घ_pool_set(काष्ठा mvpp2_port *port,
				    पूर्णांक lrxq, पूर्णांक दीर्घ_pool)
अणु
	u32 val, mask;
	पूर्णांक prxq;

	/* Get queue physical ID */
	prxq = port->rxqs[lrxq]->id;

	अगर (port->priv->hw_version == MVPP21)
		mask = MVPP21_RXQ_POOL_LONG_MASK;
	अन्यथा
		mask = MVPP22_RXQ_POOL_LONG_MASK;

	val = mvpp2_पढ़ो(port->priv, MVPP2_RXQ_CONFIG_REG(prxq));
	val &= ~mask;
	val |= (दीर्घ_pool << MVPP2_RXQ_POOL_LONG_OFFS) & mask;
	mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_CONFIG_REG(prxq), val);
पूर्ण

/* Attach लघु pool to rxq */
अटल व्योम mvpp2_rxq_लघु_pool_set(काष्ठा mvpp2_port *port,
				     पूर्णांक lrxq, पूर्णांक लघु_pool)
अणु
	u32 val, mask;
	पूर्णांक prxq;

	/* Get queue physical ID */
	prxq = port->rxqs[lrxq]->id;

	अगर (port->priv->hw_version == MVPP21)
		mask = MVPP21_RXQ_POOL_SHORT_MASK;
	अन्यथा
		mask = MVPP22_RXQ_POOL_SHORT_MASK;

	val = mvpp2_पढ़ो(port->priv, MVPP2_RXQ_CONFIG_REG(prxq));
	val &= ~mask;
	val |= (लघु_pool << MVPP2_RXQ_POOL_SHORT_OFFS) & mask;
	mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_CONFIG_REG(prxq), val);
पूर्ण

अटल व्योम *mvpp2_buf_alloc(काष्ठा mvpp2_port *port,
			     काष्ठा mvpp2_bm_pool *bm_pool,
			     काष्ठा page_pool *page_pool,
			     dma_addr_t *buf_dma_addr,
			     phys_addr_t *buf_phys_addr,
			     gfp_t gfp_mask)
अणु
	dma_addr_t dma_addr;
	काष्ठा page *page;
	व्योम *data;

	data = mvpp2_frag_alloc(bm_pool, page_pool);
	अगर (!data)
		वापस शून्य;

	अगर (page_pool) अणु
		page = (काष्ठा page *)data;
		dma_addr = page_pool_get_dma_addr(page);
		data = page_to_virt(page);
	पूर्ण अन्यथा अणु
		dma_addr = dma_map_single(port->dev->dev.parent, data,
					  MVPP2_RX_BUF_SIZE(bm_pool->pkt_size),
					  DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(port->dev->dev.parent, dma_addr))) अणु
			mvpp2_frag_मुक्त(bm_pool, शून्य, data);
			वापस शून्य;
		पूर्ण
	पूर्ण
	*buf_dma_addr = dma_addr;
	*buf_phys_addr = virt_to_phys(data);

	वापस data;
पूर्ण

/* Routine enable flow control क्रम RXQs condition */
अटल व्योम mvpp2_rxq_enable_fc(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक val, cm3_state, host_id, q;
	पूर्णांक fq = port->first_rxq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->priv->mss_spinlock, flags);

	/* Remove Flow control enable bit to prevent race between FW and Kernel
	 * If Flow control was enabled, it would be re-enabled.
	 */
	val = mvpp2_cm3_पढ़ो(port->priv, MSS_FC_COM_REG);
	cm3_state = (val & FLOW_CONTROL_ENABLE_BIT);
	val &= ~FLOW_CONTROL_ENABLE_BIT;
	mvpp2_cm3_ग_लिखो(port->priv, MSS_FC_COM_REG, val);

	/* Set same Flow control क्रम all RXQs */
	क्रम (q = 0; q < port->nrxqs; q++) अणु
		/* Set stop and start Flow control RXQ thresholds */
		val = MSS_THRESHOLD_START;
		val |= (MSS_THRESHOLD_STOP << MSS_RXQ_TRESH_STOP_OFFS);
		mvpp2_cm3_ग_लिखो(port->priv, MSS_RXQ_TRESH_REG(q, fq), val);

		val = mvpp2_cm3_पढ़ो(port->priv, MSS_RXQ_ASS_REG(q, fq));
		/* Set RXQ port ID */
		val &= ~(MSS_RXQ_ASS_PORTID_MASK << MSS_RXQ_ASS_Q_BASE(q, fq));
		val |= (port->id << MSS_RXQ_ASS_Q_BASE(q, fq));
		val &= ~(MSS_RXQ_ASS_HOSTID_MASK << (MSS_RXQ_ASS_Q_BASE(q, fq)
			+ MSS_RXQ_ASS_HOSTID_OFFS));

		/* Calculate RXQ host ID:
		 * In Single queue mode: Host ID equal to Host ID used क्रम
		 *			 shared RX पूर्णांकerrupt
		 * In Multi queue mode: Host ID equal to number of
		 *			RXQ ID / number of CoS queues
		 * In Single resource mode: Host ID always equal to 0
		 */
		अगर (queue_mode == MVPP2_QDIST_SINGLE_MODE)
			host_id = port->nqvecs;
		अन्यथा अगर (queue_mode == MVPP2_QDIST_MULTI_MODE)
			host_id = q;
		अन्यथा
			host_id = 0;

		/* Set RXQ host ID */
		val |= (host_id << (MSS_RXQ_ASS_Q_BASE(q, fq)
			+ MSS_RXQ_ASS_HOSTID_OFFS));

		mvpp2_cm3_ग_लिखो(port->priv, MSS_RXQ_ASS_REG(q, fq), val);
	पूर्ण

	/* Notअगरy Firmware that Flow control config space पढ़ोy क्रम update */
	val = mvpp2_cm3_पढ़ो(port->priv, MSS_FC_COM_REG);
	val |= FLOW_CONTROL_UPDATE_COMMAND_BIT;
	val |= cm3_state;
	mvpp2_cm3_ग_लिखो(port->priv, MSS_FC_COM_REG, val);

	spin_unlock_irqrestore(&port->priv->mss_spinlock, flags);
पूर्ण

/* Routine disable flow control क्रम RXQs condition */
अटल व्योम mvpp2_rxq_disable_fc(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक val, cm3_state, q;
	अचिन्हित दीर्घ flags;
	पूर्णांक fq = port->first_rxq;

	spin_lock_irqsave(&port->priv->mss_spinlock, flags);

	/* Remove Flow control enable bit to prevent race between FW and Kernel
	 * If Flow control was enabled, it would be re-enabled.
	 */
	val = mvpp2_cm3_पढ़ो(port->priv, MSS_FC_COM_REG);
	cm3_state = (val & FLOW_CONTROL_ENABLE_BIT);
	val &= ~FLOW_CONTROL_ENABLE_BIT;
	mvpp2_cm3_ग_लिखो(port->priv, MSS_FC_COM_REG, val);

	/* Disable Flow control क्रम all RXQs */
	क्रम (q = 0; q < port->nrxqs; q++) अणु
		/* Set threshold 0 to disable Flow control */
		val = 0;
		val |= (0 << MSS_RXQ_TRESH_STOP_OFFS);
		mvpp2_cm3_ग_लिखो(port->priv, MSS_RXQ_TRESH_REG(q, fq), val);

		val = mvpp2_cm3_पढ़ो(port->priv, MSS_RXQ_ASS_REG(q, fq));

		val &= ~(MSS_RXQ_ASS_PORTID_MASK << MSS_RXQ_ASS_Q_BASE(q, fq));

		val &= ~(MSS_RXQ_ASS_HOSTID_MASK << (MSS_RXQ_ASS_Q_BASE(q, fq)
			+ MSS_RXQ_ASS_HOSTID_OFFS));

		mvpp2_cm3_ग_लिखो(port->priv, MSS_RXQ_ASS_REG(q, fq), val);
	पूर्ण

	/* Notअगरy Firmware that Flow control config space पढ़ोy क्रम update */
	val = mvpp2_cm3_पढ़ो(port->priv, MSS_FC_COM_REG);
	val |= FLOW_CONTROL_UPDATE_COMMAND_BIT;
	val |= cm3_state;
	mvpp2_cm3_ग_लिखो(port->priv, MSS_FC_COM_REG, val);

	spin_unlock_irqrestore(&port->priv->mss_spinlock, flags);
पूर्ण

/* Routine disable/enable flow control क्रम BM pool condition */
अटल व्योम mvpp2_bm_pool_update_fc(काष्ठा mvpp2_port *port,
				    काष्ठा mvpp2_bm_pool *pool,
				    bool en)
अणु
	पूर्णांक val, cm3_state;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->priv->mss_spinlock, flags);

	/* Remove Flow control enable bit to prevent race between FW and Kernel
	 * If Flow control were enabled, it would be re-enabled.
	 */
	val = mvpp2_cm3_पढ़ो(port->priv, MSS_FC_COM_REG);
	cm3_state = (val & FLOW_CONTROL_ENABLE_BIT);
	val &= ~FLOW_CONTROL_ENABLE_BIT;
	mvpp2_cm3_ग_लिखो(port->priv, MSS_FC_COM_REG, val);

	/* Check अगर BM pool should be enabled/disable */
	अगर (en) अणु
		/* Set BM pool start and stop thresholds per port */
		val = mvpp2_cm3_पढ़ो(port->priv, MSS_BUF_POOL_REG(pool->id));
		val |= MSS_BUF_POOL_PORT_OFFS(port->id);
		val &= ~MSS_BUF_POOL_START_MASK;
		val |= (MSS_THRESHOLD_START << MSS_BUF_POOL_START_OFFS);
		val &= ~MSS_BUF_POOL_STOP_MASK;
		val |= MSS_THRESHOLD_STOP;
		mvpp2_cm3_ग_लिखो(port->priv, MSS_BUF_POOL_REG(pool->id), val);
	पूर्ण अन्यथा अणु
		/* Remove BM pool from the port */
		val = mvpp2_cm3_पढ़ो(port->priv, MSS_BUF_POOL_REG(pool->id));
		val &= ~MSS_BUF_POOL_PORT_OFFS(port->id);

		/* Zero BM pool start and stop thresholds to disable pool
		 * flow control अगर pool empty (not used by any port)
		 */
		अगर (!pool->buf_num) अणु
			val &= ~MSS_BUF_POOL_START_MASK;
			val &= ~MSS_BUF_POOL_STOP_MASK;
		पूर्ण

		mvpp2_cm3_ग_लिखो(port->priv, MSS_BUF_POOL_REG(pool->id), val);
	पूर्ण

	/* Notअगरy Firmware that Flow control config space पढ़ोy क्रम update */
	val = mvpp2_cm3_पढ़ो(port->priv, MSS_FC_COM_REG);
	val |= FLOW_CONTROL_UPDATE_COMMAND_BIT;
	val |= cm3_state;
	mvpp2_cm3_ग_लिखो(port->priv, MSS_FC_COM_REG, val);

	spin_unlock_irqrestore(&port->priv->mss_spinlock, flags);
पूर्ण

/* disable/enable flow control क्रम BM pool on all ports */
अटल व्योम mvpp2_bm_pool_update_priv_fc(काष्ठा mvpp2 *priv, bool en)
अणु
	काष्ठा mvpp2_port *port;
	पूर्णांक i;

	क्रम (i = 0; i < priv->port_count; i++) अणु
		port = priv->port_list[i];
		अगर (port->priv->percpu_pools) अणु
			क्रम (i = 0; i < port->nrxqs; i++)
				mvpp2_bm_pool_update_fc(port, &port->priv->bm_pools[i],
							port->tx_fc & en);
		पूर्ण अन्यथा अणु
			mvpp2_bm_pool_update_fc(port, port->pool_दीर्घ, port->tx_fc & en);
			mvpp2_bm_pool_update_fc(port, port->pool_लघु, port->tx_fc & en);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mvpp2_enable_global_fc(काष्ठा mvpp2 *priv)
अणु
	पूर्णांक val, समयout = 0;

	/* Enable global flow control. In this stage global
	 * flow control enabled, but still disabled per port.
	 */
	val = mvpp2_cm3_पढ़ो(priv, MSS_FC_COM_REG);
	val |= FLOW_CONTROL_ENABLE_BIT;
	mvpp2_cm3_ग_लिखो(priv, MSS_FC_COM_REG, val);

	/* Check अगर Firmware running and disable FC अगर not*/
	val |= FLOW_CONTROL_UPDATE_COMMAND_BIT;
	mvpp2_cm3_ग_लिखो(priv, MSS_FC_COM_REG, val);

	जबतक (समयout < MSS_FC_MAX_TIMEOUT) अणु
		val = mvpp2_cm3_पढ़ो(priv, MSS_FC_COM_REG);

		अगर (!(val & FLOW_CONTROL_UPDATE_COMMAND_BIT))
			वापस 0;
		usleep_range(10, 20);
		समयout++;
	पूर्ण

	priv->global_tx_fc = false;
	वापस -EOPNOTSUPP;
पूर्ण

/* Release buffer to BM */
अटल अंतरभूत व्योम mvpp2_bm_pool_put(काष्ठा mvpp2_port *port, पूर्णांक pool,
				     dma_addr_t buf_dma_addr,
				     phys_addr_t buf_phys_addr)
अणु
	अचिन्हित पूर्णांक thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, get_cpu());
	अचिन्हित दीर्घ flags = 0;

	अगर (test_bit(thपढ़ो, &port->priv->lock_map))
		spin_lock_irqsave(&port->bm_lock[thपढ़ो], flags);

	अगर (port->priv->hw_version >= MVPP22) अणु
		u32 val = 0;

		अगर (माप(dma_addr_t) == 8)
			val |= upper_32_bits(buf_dma_addr) &
				MVPP22_BM_ADDR_HIGH_PHYS_RLS_MASK;

		अगर (माप(phys_addr_t) == 8)
			val |= (upper_32_bits(buf_phys_addr)
				<< MVPP22_BM_ADDR_HIGH_VIRT_RLS_SHIFT) &
				MVPP22_BM_ADDR_HIGH_VIRT_RLS_MASK;

		mvpp2_thपढ़ो_ग_लिखो_relaxed(port->priv, thपढ़ो,
					   MVPP22_BM_ADDR_HIGH_RLS_REG, val);
	पूर्ण

	/* MVPP2_BM_VIRT_RLS_REG is not पूर्णांकerpreted by HW, and simply
	 * वापसed in the "cookie" field of the RX
	 * descriptor. Instead of storing the भव address, we
	 * store the physical address
	 */
	mvpp2_thपढ़ो_ग_लिखो_relaxed(port->priv, thपढ़ो,
				   MVPP2_BM_VIRT_RLS_REG, buf_phys_addr);
	mvpp2_thपढ़ो_ग_लिखो_relaxed(port->priv, thपढ़ो,
				   MVPP2_BM_PHY_RLS_REG(pool), buf_dma_addr);

	अगर (test_bit(thपढ़ो, &port->priv->lock_map))
		spin_unlock_irqrestore(&port->bm_lock[thपढ़ो], flags);

	put_cpu();
पूर्ण

/* Allocate buffers क्रम the pool */
अटल पूर्णांक mvpp2_bm_bufs_add(काष्ठा mvpp2_port *port,
			     काष्ठा mvpp2_bm_pool *bm_pool, पूर्णांक buf_num)
अणु
	पूर्णांक i, buf_size, total_size;
	dma_addr_t dma_addr;
	phys_addr_t phys_addr;
	काष्ठा page_pool *pp = शून्य;
	व्योम *buf;

	अगर (port->priv->percpu_pools &&
	    bm_pool->pkt_size > MVPP2_BM_LONG_PKT_SIZE) अणु
		netdev_err(port->dev,
			   "attempted to use jumbo frames with per-cpu pools");
		वापस 0;
	पूर्ण

	buf_size = MVPP2_RX_BUF_SIZE(bm_pool->pkt_size);
	total_size = MVPP2_RX_TOTAL_SIZE(buf_size);

	अगर (buf_num < 0 ||
	    (buf_num + bm_pool->buf_num > bm_pool->size)) अणु
		netdev_err(port->dev,
			   "cannot allocate %d buffers for pool %d\n",
			   buf_num, bm_pool->id);
		वापस 0;
	पूर्ण

	अगर (port->priv->percpu_pools)
		pp = port->priv->page_pool[bm_pool->id];
	क्रम (i = 0; i < buf_num; i++) अणु
		buf = mvpp2_buf_alloc(port, bm_pool, pp, &dma_addr,
				      &phys_addr, GFP_KERNEL);
		अगर (!buf)
			अवरोध;

		mvpp2_bm_pool_put(port, bm_pool->id, dma_addr,
				  phys_addr);
	पूर्ण

	/* Update BM driver with number of buffers added to pool */
	bm_pool->buf_num += i;

	netdev_dbg(port->dev,
		   "pool %d: pkt_size=%4d, buf_size=%4d, total_size=%4d\n",
		   bm_pool->id, bm_pool->pkt_size, buf_size, total_size);

	netdev_dbg(port->dev,
		   "pool %d: %d of %d buffers added\n",
		   bm_pool->id, i, buf_num);
	वापस i;
पूर्ण

/* Notअगरy the driver that BM pool is being used as specअगरic type and वापस the
 * pool poपूर्णांकer on success
 */
अटल काष्ठा mvpp2_bm_pool *
mvpp2_bm_pool_use(काष्ठा mvpp2_port *port, अचिन्हित pool, पूर्णांक pkt_size)
अणु
	काष्ठा mvpp2_bm_pool *new_pool = &port->priv->bm_pools[pool];
	पूर्णांक num;

	अगर ((port->priv->percpu_pools && pool > mvpp2_get_nrxqs(port->priv) * 2) ||
	    (!port->priv->percpu_pools && pool >= MVPP2_BM_POOLS_NUM)) अणु
		netdev_err(port->dev, "Invalid pool %d\n", pool);
		वापस शून्य;
	पूर्ण

	/* Allocate buffers in हाल BM pool is used as दीर्घ pool, but packet
	 * size करोesn't match MTU or BM pool hasn't being used yet
	 */
	अगर (new_pool->pkt_size == 0) अणु
		पूर्णांक pkts_num;

		/* Set शेष buffer number or मुक्त all the buffers in हाल
		 * the pool is not empty
		 */
		pkts_num = new_pool->buf_num;
		अगर (pkts_num == 0) अणु
			अगर (port->priv->percpu_pools) अणु
				अगर (pool < port->nrxqs)
					pkts_num = mvpp2_pools[MVPP2_BM_SHORT].buf_num;
				अन्यथा
					pkts_num = mvpp2_pools[MVPP2_BM_LONG].buf_num;
			पूर्ण अन्यथा अणु
				pkts_num = mvpp2_pools[pool].buf_num;
			पूर्ण
		पूर्ण अन्यथा अणु
			mvpp2_bm_bufs_मुक्त(port->dev->dev.parent,
					   port->priv, new_pool, pkts_num);
		पूर्ण

		new_pool->pkt_size = pkt_size;
		new_pool->frag_size =
			SKB_DATA_ALIGN(MVPP2_RX_BUF_SIZE(pkt_size)) +
			MVPP2_SKB_SHINFO_SIZE;

		/* Allocate buffers क्रम this pool */
		num = mvpp2_bm_bufs_add(port, new_pool, pkts_num);
		अगर (num != pkts_num) अणु
			WARN(1, "pool %d: %d of %d allocated\n",
			     new_pool->id, num, pkts_num);
			वापस शून्य;
		पूर्ण
	पूर्ण

	mvpp2_bm_pool_bufsize_set(port->priv, new_pool,
				  MVPP2_RX_BUF_SIZE(new_pool->pkt_size));

	वापस new_pool;
पूर्ण

अटल काष्ठा mvpp2_bm_pool *
mvpp2_bm_pool_use_percpu(काष्ठा mvpp2_port *port, पूर्णांक type,
			 अचिन्हित पूर्णांक pool, पूर्णांक pkt_size)
अणु
	काष्ठा mvpp2_bm_pool *new_pool = &port->priv->bm_pools[pool];
	पूर्णांक num;

	अगर (pool > port->nrxqs * 2) अणु
		netdev_err(port->dev, "Invalid pool %d\n", pool);
		वापस शून्य;
	पूर्ण

	/* Allocate buffers in हाल BM pool is used as दीर्घ pool, but packet
	 * size करोesn't match MTU or BM pool hasn't being used yet
	 */
	अगर (new_pool->pkt_size == 0) अणु
		पूर्णांक pkts_num;

		/* Set शेष buffer number or मुक्त all the buffers in हाल
		 * the pool is not empty
		 */
		pkts_num = new_pool->buf_num;
		अगर (pkts_num == 0)
			pkts_num = mvpp2_pools[type].buf_num;
		अन्यथा
			mvpp2_bm_bufs_मुक्त(port->dev->dev.parent,
					   port->priv, new_pool, pkts_num);

		new_pool->pkt_size = pkt_size;
		new_pool->frag_size =
			SKB_DATA_ALIGN(MVPP2_RX_BUF_SIZE(pkt_size)) +
			MVPP2_SKB_SHINFO_SIZE;

		/* Allocate buffers क्रम this pool */
		num = mvpp2_bm_bufs_add(port, new_pool, pkts_num);
		अगर (num != pkts_num) अणु
			WARN(1, "pool %d: %d of %d allocated\n",
			     new_pool->id, num, pkts_num);
			वापस शून्य;
		पूर्ण
	पूर्ण

	mvpp2_bm_pool_bufsize_set(port->priv, new_pool,
				  MVPP2_RX_BUF_SIZE(new_pool->pkt_size));

	वापस new_pool;
पूर्ण

/* Initialize pools क्रम swf, shared buffers variant */
अटल पूर्णांक mvpp2_swf_bm_pool_init_shared(काष्ठा mvpp2_port *port)
अणु
	क्रमागत mvpp2_bm_pool_log_num दीर्घ_log_pool, लघु_log_pool;
	पूर्णांक rxq;

	/* If port pkt_size is higher than 1518B:
	 * HW Long pool - SW Jumbo pool, HW Short pool - SW Long pool
	 * अन्यथा: HW Long pool - SW Long pool, HW Short pool - SW Short pool
	 */
	अगर (port->pkt_size > MVPP2_BM_LONG_PKT_SIZE) अणु
		दीर्घ_log_pool = MVPP2_BM_JUMBO;
		लघु_log_pool = MVPP2_BM_LONG;
	पूर्ण अन्यथा अणु
		दीर्घ_log_pool = MVPP2_BM_LONG;
		लघु_log_pool = MVPP2_BM_SHORT;
	पूर्ण

	अगर (!port->pool_दीर्घ) अणु
		port->pool_दीर्घ =
			mvpp2_bm_pool_use(port, दीर्घ_log_pool,
					  mvpp2_pools[दीर्घ_log_pool].pkt_size);
		अगर (!port->pool_दीर्घ)
			वापस -ENOMEM;

		port->pool_दीर्घ->port_map |= BIT(port->id);

		क्रम (rxq = 0; rxq < port->nrxqs; rxq++)
			mvpp2_rxq_दीर्घ_pool_set(port, rxq, port->pool_दीर्घ->id);
	पूर्ण

	अगर (!port->pool_लघु) अणु
		port->pool_लघु =
			mvpp2_bm_pool_use(port, लघु_log_pool,
					  mvpp2_pools[लघु_log_pool].pkt_size);
		अगर (!port->pool_लघु)
			वापस -ENOMEM;

		port->pool_लघु->port_map |= BIT(port->id);

		क्रम (rxq = 0; rxq < port->nrxqs; rxq++)
			mvpp2_rxq_लघु_pool_set(port, rxq,
						 port->pool_लघु->id);
	पूर्ण

	वापस 0;
पूर्ण

/* Initialize pools क्रम swf, percpu buffers variant */
अटल पूर्णांक mvpp2_swf_bm_pool_init_percpu(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2_bm_pool *bm_pool;
	पूर्णांक i;

	क्रम (i = 0; i < port->nrxqs; i++) अणु
		bm_pool = mvpp2_bm_pool_use_percpu(port, MVPP2_BM_SHORT, i,
						   mvpp2_pools[MVPP2_BM_SHORT].pkt_size);
		अगर (!bm_pool)
			वापस -ENOMEM;

		bm_pool->port_map |= BIT(port->id);
		mvpp2_rxq_लघु_pool_set(port, i, bm_pool->id);
	पूर्ण

	क्रम (i = 0; i < port->nrxqs; i++) अणु
		bm_pool = mvpp2_bm_pool_use_percpu(port, MVPP2_BM_LONG, i + port->nrxqs,
						   mvpp2_pools[MVPP2_BM_LONG].pkt_size);
		अगर (!bm_pool)
			वापस -ENOMEM;

		bm_pool->port_map |= BIT(port->id);
		mvpp2_rxq_दीर्घ_pool_set(port, i, bm_pool->id);
	पूर्ण

	port->pool_दीर्घ = शून्य;
	port->pool_लघु = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_swf_bm_pool_init(काष्ठा mvpp2_port *port)
अणु
	अगर (port->priv->percpu_pools)
		वापस mvpp2_swf_bm_pool_init_percpu(port);
	अन्यथा
		वापस mvpp2_swf_bm_pool_init_shared(port);
पूर्ण

अटल व्योम mvpp2_set_hw_csum(काष्ठा mvpp2_port *port,
			      क्रमागत mvpp2_bm_pool_log_num new_दीर्घ_pool)
अणु
	स्थिर netdev_features_t csums = NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;

	/* Update L4 checksum when jumbo enable/disable on port.
	 * Only port 0 supports hardware checksum offload due to
	 * the Tx FIFO size limitation.
	 * Also, करोn't set NETIF_F_HW_CSUM because L3_offset in TX descriptor
	 * has 7 bits, so the maximum L3 offset is 128.
	 */
	अगर (new_दीर्घ_pool == MVPP2_BM_JUMBO && port->id != 0) अणु
		port->dev->features &= ~csums;
		port->dev->hw_features &= ~csums;
	पूर्ण अन्यथा अणु
		port->dev->features |= csums;
		port->dev->hw_features |= csums;
	पूर्ण
पूर्ण

अटल पूर्णांक mvpp2_bm_update_mtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	क्रमागत mvpp2_bm_pool_log_num new_दीर्घ_pool;
	पूर्णांक pkt_size = MVPP2_RX_PKT_SIZE(mtu);

	अगर (port->priv->percpu_pools)
		जाओ out_set;

	/* If port MTU is higher than 1518B:
	 * HW Long pool - SW Jumbo pool, HW Short pool - SW Long pool
	 * अन्यथा: HW Long pool - SW Long pool, HW Short pool - SW Short pool
	 */
	अगर (pkt_size > MVPP2_BM_LONG_PKT_SIZE)
		new_दीर्घ_pool = MVPP2_BM_JUMBO;
	अन्यथा
		new_दीर्घ_pool = MVPP2_BM_LONG;

	अगर (new_दीर्घ_pool != port->pool_दीर्घ->id) अणु
		अगर (port->tx_fc) अणु
			अगर (pkt_size > MVPP2_BM_LONG_PKT_SIZE)
				mvpp2_bm_pool_update_fc(port,
							port->pool_लघु,
							false);
			अन्यथा
				mvpp2_bm_pool_update_fc(port, port->pool_दीर्घ,
							false);
		पूर्ण

		/* Remove port from old लघु & दीर्घ pool */
		port->pool_दीर्घ = mvpp2_bm_pool_use(port, port->pool_दीर्घ->id,
						    port->pool_दीर्घ->pkt_size);
		port->pool_दीर्घ->port_map &= ~BIT(port->id);
		port->pool_दीर्घ = शून्य;

		port->pool_लघु = mvpp2_bm_pool_use(port, port->pool_लघु->id,
						     port->pool_लघु->pkt_size);
		port->pool_लघु->port_map &= ~BIT(port->id);
		port->pool_लघु = शून्य;

		port->pkt_size =  pkt_size;

		/* Add port to new लघु & दीर्घ pool */
		mvpp2_swf_bm_pool_init(port);

		mvpp2_set_hw_csum(port, new_दीर्घ_pool);

		अगर (port->tx_fc) अणु
			अगर (pkt_size > MVPP2_BM_LONG_PKT_SIZE)
				mvpp2_bm_pool_update_fc(port, port->pool_दीर्घ,
							true);
			अन्यथा
				mvpp2_bm_pool_update_fc(port, port->pool_लघु,
							true);
		पूर्ण

		/* Update L4 checksum when jumbo enable/disable on port */
		अगर (new_दीर्घ_pool == MVPP2_BM_JUMBO && port->id != 0) अणु
			dev->features &= ~(NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM);
			dev->hw_features &= ~(NETIF_F_IP_CSUM |
					      NETIF_F_IPV6_CSUM);
		पूर्ण अन्यथा अणु
			dev->features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
			dev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
		पूर्ण
	पूर्ण

out_set:
	dev->mtu = mtu;
	dev->wanted_features = dev->features;

	netdev_update_features(dev);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mvpp2_पूर्णांकerrupts_enable(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक i, sw_thपढ़ो_mask = 0;

	क्रम (i = 0; i < port->nqvecs; i++)
		sw_thपढ़ो_mask |= port->qvecs[i].sw_thपढ़ो_mask;

	mvpp2_ग_लिखो(port->priv, MVPP2_ISR_ENABLE_REG(port->id),
		    MVPP2_ISR_ENABLE_INTERRUPT(sw_thपढ़ो_mask));
पूर्ण

अटल अंतरभूत व्योम mvpp2_पूर्णांकerrupts_disable(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक i, sw_thपढ़ो_mask = 0;

	क्रम (i = 0; i < port->nqvecs; i++)
		sw_thपढ़ो_mask |= port->qvecs[i].sw_thपढ़ो_mask;

	mvpp2_ग_लिखो(port->priv, MVPP2_ISR_ENABLE_REG(port->id),
		    MVPP2_ISR_DISABLE_INTERRUPT(sw_thपढ़ो_mask));
पूर्ण

अटल अंतरभूत व्योम mvpp2_qvec_पूर्णांकerrupt_enable(काष्ठा mvpp2_queue_vector *qvec)
अणु
	काष्ठा mvpp2_port *port = qvec->port;

	mvpp2_ग_लिखो(port->priv, MVPP2_ISR_ENABLE_REG(port->id),
		    MVPP2_ISR_ENABLE_INTERRUPT(qvec->sw_thपढ़ो_mask));
पूर्ण

अटल अंतरभूत व्योम mvpp2_qvec_पूर्णांकerrupt_disable(काष्ठा mvpp2_queue_vector *qvec)
अणु
	काष्ठा mvpp2_port *port = qvec->port;

	mvpp2_ग_लिखो(port->priv, MVPP2_ISR_ENABLE_REG(port->id),
		    MVPP2_ISR_DISABLE_INTERRUPT(qvec->sw_thपढ़ो_mask));
पूर्ण

/* Mask the current thपढ़ो's Rx/Tx पूर्णांकerrupts
 * Called by on_each_cpu(), guaranteed to run with migration disabled,
 * using smp_processor_id() is OK.
 */
अटल व्योम mvpp2_पूर्णांकerrupts_mask(व्योम *arg)
अणु
	काष्ठा mvpp2_port *port = arg;
	पूर्णांक cpu = smp_processor_id();
	u32 thपढ़ो;

	/* If the thपढ़ो isn't used, don't करो anything */
	अगर (cpu > port->priv->nthपढ़ोs)
		वापस;

	thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, cpu);

	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो,
			   MVPP2_ISR_RX_TX_MASK_REG(port->id), 0);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो,
			   MVPP2_ISR_RX_ERR_CAUSE_REG(port->id), 0);
पूर्ण

/* Unmask the current thपढ़ो's Rx/Tx पूर्णांकerrupts.
 * Called by on_each_cpu(), guaranteed to run with migration disabled,
 * using smp_processor_id() is OK.
 */
अटल व्योम mvpp2_पूर्णांकerrupts_unmask(व्योम *arg)
अणु
	काष्ठा mvpp2_port *port = arg;
	पूर्णांक cpu = smp_processor_id();
	u32 val, thपढ़ो;

	/* If the thपढ़ो isn't used, don't करो anything */
	अगर (cpu >= port->priv->nthपढ़ोs)
		वापस;

	thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, cpu);

	val = MVPP2_CAUSE_MISC_SUM_MASK |
		MVPP2_CAUSE_RXQ_OCCUP_DESC_ALL_MASK(port->priv->hw_version);
	अगर (port->has_tx_irqs)
		val |= MVPP2_CAUSE_TXQ_OCCUP_DESC_ALL_MASK;

	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो,
			   MVPP2_ISR_RX_TX_MASK_REG(port->id), val);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो,
			   MVPP2_ISR_RX_ERR_CAUSE_REG(port->id),
			   MVPP2_ISR_RX_ERR_CAUSE_NONOCC_MASK);
पूर्ण

अटल व्योम
mvpp2_shared_पूर्णांकerrupt_mask_unmask(काष्ठा mvpp2_port *port, bool mask)
अणु
	u32 val;
	पूर्णांक i;

	अगर (port->priv->hw_version == MVPP21)
		वापस;

	अगर (mask)
		val = 0;
	अन्यथा
		val = MVPP2_CAUSE_RXQ_OCCUP_DESC_ALL_MASK(MVPP22);

	क्रम (i = 0; i < port->nqvecs; i++) अणु
		काष्ठा mvpp2_queue_vector *v = port->qvecs + i;

		अगर (v->type != MVPP2_QUEUE_VECTOR_SHARED)
			जारी;

		mvpp2_thपढ़ो_ग_लिखो(port->priv, v->sw_thपढ़ो_id,
				   MVPP2_ISR_RX_TX_MASK_REG(port->id), val);
		mvpp2_thपढ़ो_ग_लिखो(port->priv, v->sw_thपढ़ो_id,
				   MVPP2_ISR_RX_ERR_CAUSE_REG(port->id),
				   MVPP2_ISR_RX_ERR_CAUSE_NONOCC_MASK);
	पूर्ण
पूर्ण

/* Only GOP port 0 has an XLG MAC */
अटल bool mvpp2_port_supports_xlg(काष्ठा mvpp2_port *port)
अणु
	वापस port->gop_id == 0;
पूर्ण

अटल bool mvpp2_port_supports_rgmii(काष्ठा mvpp2_port *port)
अणु
	वापस !(port->priv->hw_version >= MVPP22 && port->gop_id == 0);
पूर्ण

/* Port configuration routines */
अटल bool mvpp2_is_xlg(phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	वापस पूर्णांकerface == PHY_INTERFACE_MODE_10GBASER ||
	       पूर्णांकerface == PHY_INTERFACE_MODE_XAUI;
पूर्ण

अटल व्योम mvpp2_modअगरy(व्योम __iomem *ptr, u32 mask, u32 set)
अणु
	u32 old, val;

	old = val = पढ़ोl(ptr);
	val &= ~mask;
	val |= set;
	अगर (old != val)
		ग_लिखोl(val, ptr);
पूर्ण

अटल व्योम mvpp22_gop_init_rgmii(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	u32 val;

	regmap_पढ़ो(priv->sysctrl_base, GENCONF_PORT_CTRL0, &val);
	val |= GENCONF_PORT_CTRL0_BUS_WIDTH_SELECT;
	regmap_ग_लिखो(priv->sysctrl_base, GENCONF_PORT_CTRL0, val);

	regmap_पढ़ो(priv->sysctrl_base, GENCONF_CTRL0, &val);
	अगर (port->gop_id == 2)
		val |= GENCONF_CTRL0_PORT2_RGMII;
	अन्यथा अगर (port->gop_id == 3)
		val |= GENCONF_CTRL0_PORT3_RGMII_MII;
	regmap_ग_लिखो(priv->sysctrl_base, GENCONF_CTRL0, val);
पूर्ण

अटल व्योम mvpp22_gop_init_sgmii(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	u32 val;

	regmap_पढ़ो(priv->sysctrl_base, GENCONF_PORT_CTRL0, &val);
	val |= GENCONF_PORT_CTRL0_BUS_WIDTH_SELECT |
	       GENCONF_PORT_CTRL0_RX_DATA_SAMPLE;
	regmap_ग_लिखो(priv->sysctrl_base, GENCONF_PORT_CTRL0, val);

	अगर (port->gop_id > 1) अणु
		regmap_पढ़ो(priv->sysctrl_base, GENCONF_CTRL0, &val);
		अगर (port->gop_id == 2)
			val &= ~GENCONF_CTRL0_PORT2_RGMII;
		अन्यथा अगर (port->gop_id == 3)
			val &= ~GENCONF_CTRL0_PORT3_RGMII_MII;
		regmap_ग_लिखो(priv->sysctrl_base, GENCONF_CTRL0, val);
	पूर्ण
पूर्ण

अटल व्योम mvpp22_gop_init_10gkr(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	व्योम __iomem *mpcs = priv->अगरace_base + MVPP22_MPCS_BASE(port->gop_id);
	व्योम __iomem *xpcs = priv->अगरace_base + MVPP22_XPCS_BASE(port->gop_id);
	u32 val;

	val = पढ़ोl(xpcs + MVPP22_XPCS_CFG0);
	val &= ~(MVPP22_XPCS_CFG0_PCS_MODE(0x3) |
		 MVPP22_XPCS_CFG0_ACTIVE_LANE(0x3));
	val |= MVPP22_XPCS_CFG0_ACTIVE_LANE(2);
	ग_लिखोl(val, xpcs + MVPP22_XPCS_CFG0);

	val = पढ़ोl(mpcs + MVPP22_MPCS_CTRL);
	val &= ~MVPP22_MPCS_CTRL_FWD_ERR_CONN;
	ग_लिखोl(val, mpcs + MVPP22_MPCS_CTRL);

	val = पढ़ोl(mpcs + MVPP22_MPCS_CLK_RESET);
	val &= ~MVPP22_MPCS_CLK_RESET_DIV_RATIO(0x7);
	val |= MVPP22_MPCS_CLK_RESET_DIV_RATIO(1);
	ग_लिखोl(val, mpcs + MVPP22_MPCS_CLK_RESET);
पूर्ण

अटल व्योम mvpp22_gop_fca_enable_periodic(काष्ठा mvpp2_port *port, bool en)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	व्योम __iomem *fca = priv->अगरace_base + MVPP22_FCA_BASE(port->gop_id);
	u32 val;

	val = पढ़ोl(fca + MVPP22_FCA_CONTROL_REG);
	val &= ~MVPP22_FCA_ENABLE_PERIODIC;
	अगर (en)
		val |= MVPP22_FCA_ENABLE_PERIODIC;
	ग_लिखोl(val, fca + MVPP22_FCA_CONTROL_REG);
पूर्ण

अटल व्योम mvpp22_gop_fca_set_समयr(काष्ठा mvpp2_port *port, u32 समयr)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	व्योम __iomem *fca = priv->अगरace_base + MVPP22_FCA_BASE(port->gop_id);
	u32 lsb, msb;

	lsb = समयr & MVPP22_FCA_REG_MASK;
	msb = समयr >> MVPP22_FCA_REG_SIZE;

	ग_लिखोl(lsb, fca + MVPP22_PERIODIC_COUNTER_LSB_REG);
	ग_लिखोl(msb, fca + MVPP22_PERIODIC_COUNTER_MSB_REG);
पूर्ण

/* Set Flow Control समयr x100 faster than छोड़ो quanta to ensure that link
 * partner won't send traffic अगर port is in XOFF mode.
 */
अटल व्योम mvpp22_gop_fca_set_periodic_समयr(काष्ठा mvpp2_port *port)
अणु
	u32 समयr;

	समयr = (port->priv->tclk / (USEC_PER_SEC * FC_CLK_DIVIDER))
		* FC_QUANTA;

	mvpp22_gop_fca_enable_periodic(port, false);

	mvpp22_gop_fca_set_समयr(port, समयr);

	mvpp22_gop_fca_enable_periodic(port, true);
पूर्ण

अटल पूर्णांक mvpp22_gop_init(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	u32 val;

	अगर (!priv->sysctrl_base)
		वापस 0;

	चयन (port->phy_पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		अगर (!mvpp2_port_supports_rgmii(port))
			जाओ invalid_conf;
		mvpp22_gop_init_rgmii(port);
		अवरोध;
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_2500BASEX:
		mvpp22_gop_init_sgmii(port);
		अवरोध;
	हाल PHY_INTERFACE_MODE_10GBASER:
		अगर (!mvpp2_port_supports_xlg(port))
			जाओ invalid_conf;
		mvpp22_gop_init_10gkr(port);
		अवरोध;
	शेष:
		जाओ unsupported_conf;
	पूर्ण

	regmap_पढ़ो(priv->sysctrl_base, GENCONF_PORT_CTRL1, &val);
	val |= GENCONF_PORT_CTRL1_RESET(port->gop_id) |
	       GENCONF_PORT_CTRL1_EN(port->gop_id);
	regmap_ग_लिखो(priv->sysctrl_base, GENCONF_PORT_CTRL1, val);

	regmap_पढ़ो(priv->sysctrl_base, GENCONF_PORT_CTRL0, &val);
	val |= GENCONF_PORT_CTRL0_CLK_DIV_PHASE_CLR;
	regmap_ग_लिखो(priv->sysctrl_base, GENCONF_PORT_CTRL0, val);

	regmap_पढ़ो(priv->sysctrl_base, GENCONF_SOFT_RESET1, &val);
	val |= GENCONF_SOFT_RESET1_GOP;
	regmap_ग_लिखो(priv->sysctrl_base, GENCONF_SOFT_RESET1, val);

	mvpp22_gop_fca_set_periodic_समयr(port);

unsupported_conf:
	वापस 0;

invalid_conf:
	netdev_err(port->dev, "Invalid port configuration\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम mvpp22_gop_unmask_irq(काष्ठा mvpp2_port *port)
अणु
	u32 val;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(port->phy_पूर्णांकerface) ||
	    phy_पूर्णांकerface_mode_is_8023z(port->phy_पूर्णांकerface) ||
	    port->phy_पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		/* Enable the GMAC link status irq क्रम this port */
		val = पढ़ोl(port->base + MVPP22_GMAC_INT_SUM_MASK);
		val |= MVPP22_GMAC_INT_SUM_MASK_LINK_STAT;
		ग_लिखोl(val, port->base + MVPP22_GMAC_INT_SUM_MASK);
	पूर्ण

	अगर (mvpp2_port_supports_xlg(port)) अणु
		/* Enable the XLG/GIG irqs क्रम this port */
		val = पढ़ोl(port->base + MVPP22_XLG_EXT_INT_MASK);
		अगर (mvpp2_is_xlg(port->phy_पूर्णांकerface))
			val |= MVPP22_XLG_EXT_INT_MASK_XLG;
		अन्यथा
			val |= MVPP22_XLG_EXT_INT_MASK_GIG;
		ग_लिखोl(val, port->base + MVPP22_XLG_EXT_INT_MASK);
	पूर्ण
पूर्ण

अटल व्योम mvpp22_gop_mask_irq(काष्ठा mvpp2_port *port)
अणु
	u32 val;

	अगर (mvpp2_port_supports_xlg(port)) अणु
		val = पढ़ोl(port->base + MVPP22_XLG_EXT_INT_MASK);
		val &= ~(MVPP22_XLG_EXT_INT_MASK_XLG |
			 MVPP22_XLG_EXT_INT_MASK_GIG);
		ग_लिखोl(val, port->base + MVPP22_XLG_EXT_INT_MASK);
	पूर्ण

	अगर (phy_पूर्णांकerface_mode_is_rgmii(port->phy_पूर्णांकerface) ||
	    phy_पूर्णांकerface_mode_is_8023z(port->phy_पूर्णांकerface) ||
	    port->phy_पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		val = पढ़ोl(port->base + MVPP22_GMAC_INT_SUM_MASK);
		val &= ~MVPP22_GMAC_INT_SUM_MASK_LINK_STAT;
		ग_लिखोl(val, port->base + MVPP22_GMAC_INT_SUM_MASK);
	पूर्ण
पूर्ण

अटल व्योम mvpp22_gop_setup_irq(काष्ठा mvpp2_port *port)
अणु
	u32 val;

	mvpp2_modअगरy(port->base + MVPP22_GMAC_INT_SUM_MASK,
		     MVPP22_GMAC_INT_SUM_MASK_PTP,
		     MVPP22_GMAC_INT_SUM_MASK_PTP);

	अगर (port->phylink ||
	    phy_पूर्णांकerface_mode_is_rgmii(port->phy_पूर्णांकerface) ||
	    phy_पूर्णांकerface_mode_is_8023z(port->phy_पूर्णांकerface) ||
	    port->phy_पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		val = पढ़ोl(port->base + MVPP22_GMAC_INT_MASK);
		val |= MVPP22_GMAC_INT_MASK_LINK_STAT;
		ग_लिखोl(val, port->base + MVPP22_GMAC_INT_MASK);
	पूर्ण

	अगर (mvpp2_port_supports_xlg(port)) अणु
		val = पढ़ोl(port->base + MVPP22_XLG_INT_MASK);
		val |= MVPP22_XLG_INT_MASK_LINK;
		ग_लिखोl(val, port->base + MVPP22_XLG_INT_MASK);

		mvpp2_modअगरy(port->base + MVPP22_XLG_EXT_INT_MASK,
			     MVPP22_XLG_EXT_INT_MASK_PTP,
			     MVPP22_XLG_EXT_INT_MASK_PTP);
	पूर्ण

	mvpp22_gop_unmask_irq(port);
पूर्ण

/* Sets the PHY mode of the COMPHY (which configures the serdes lanes).
 *
 * The PHY mode used by the PPv2 driver comes from the network subप्रणाली, जबतक
 * the one given to the COMPHY comes from the generic PHY subप्रणाली. Hence they
 * dअगरfer.
 *
 * The COMPHY configures the serdes lanes regardless of the actual use of the
 * lanes by the physical layer. This is why configurations like
 * "PPv2 (2500BaseX) - COMPHY (2500SGMII)" are valid.
 */
अटल पूर्णांक mvpp22_comphy_init(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक ret;

	अगर (!port->comphy)
		वापस 0;

	ret = phy_set_mode_ext(port->comphy, PHY_MODE_ETHERNET,
			       port->phy_पूर्णांकerface);
	अगर (ret)
		वापस ret;

	वापस phy_घातer_on(port->comphy);
पूर्ण

अटल व्योम mvpp2_port_enable(काष्ठा mvpp2_port *port)
अणु
	u32 val;

	अगर (mvpp2_port_supports_xlg(port) &&
	    mvpp2_is_xlg(port->phy_पूर्णांकerface)) अणु
		val = पढ़ोl(port->base + MVPP22_XLG_CTRL0_REG);
		val |= MVPP22_XLG_CTRL0_PORT_EN;
		val &= ~MVPP22_XLG_CTRL0_MIB_CNT_DIS;
		ग_लिखोl(val, port->base + MVPP22_XLG_CTRL0_REG);
	पूर्ण अन्यथा अणु
		val = पढ़ोl(port->base + MVPP2_GMAC_CTRL_0_REG);
		val |= MVPP2_GMAC_PORT_EN_MASK;
		val |= MVPP2_GMAC_MIB_CNTR_EN_MASK;
		ग_लिखोl(val, port->base + MVPP2_GMAC_CTRL_0_REG);
	पूर्ण
पूर्ण

अटल व्योम mvpp2_port_disable(काष्ठा mvpp2_port *port)
अणु
	u32 val;

	अगर (mvpp2_port_supports_xlg(port) &&
	    mvpp2_is_xlg(port->phy_पूर्णांकerface)) अणु
		val = पढ़ोl(port->base + MVPP22_XLG_CTRL0_REG);
		val &= ~MVPP22_XLG_CTRL0_PORT_EN;
		ग_लिखोl(val, port->base + MVPP22_XLG_CTRL0_REG);
	पूर्ण

	val = पढ़ोl(port->base + MVPP2_GMAC_CTRL_0_REG);
	val &= ~(MVPP2_GMAC_PORT_EN_MASK);
	ग_लिखोl(val, port->base + MVPP2_GMAC_CTRL_0_REG);
पूर्ण

/* Set IEEE 802.3x Flow Control Xon Packet Transmission Mode */
अटल व्योम mvpp2_port_periodic_xon_disable(काष्ठा mvpp2_port *port)
अणु
	u32 val;

	val = पढ़ोl(port->base + MVPP2_GMAC_CTRL_1_REG) &
		    ~MVPP2_GMAC_PERIODIC_XON_EN_MASK;
	ग_लिखोl(val, port->base + MVPP2_GMAC_CTRL_1_REG);
पूर्ण

/* Configure loopback port */
अटल व्योम mvpp2_port_loopback_set(काष्ठा mvpp2_port *port,
				    स्थिर काष्ठा phylink_link_state *state)
अणु
	u32 val;

	val = पढ़ोl(port->base + MVPP2_GMAC_CTRL_1_REG);

	अगर (state->speed == 1000)
		val |= MVPP2_GMAC_GMII_LB_EN_MASK;
	अन्यथा
		val &= ~MVPP2_GMAC_GMII_LB_EN_MASK;

	अगर (phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface) ||
	    state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
		val |= MVPP2_GMAC_PCS_LB_EN_MASK;
	अन्यथा
		val &= ~MVPP2_GMAC_PCS_LB_EN_MASK;

	ग_लिखोl(val, port->base + MVPP2_GMAC_CTRL_1_REG);
पूर्ण

क्रमागत अणु
	ETHTOOL_XDP_REसूचीECT,
	ETHTOOL_XDP_PASS,
	ETHTOOL_XDP_DROP,
	ETHTOOL_XDP_TX,
	ETHTOOL_XDP_TX_ERR,
	ETHTOOL_XDP_XMIT,
	ETHTOOL_XDP_XMIT_ERR,
पूर्ण;

काष्ठा mvpp2_ethtool_counter अणु
	अचिन्हित पूर्णांक offset;
	स्थिर अक्षर string[ETH_GSTRING_LEN];
	bool reg_is_64b;
पूर्ण;

अटल u64 mvpp2_पढ़ो_count(काष्ठा mvpp2_port *port,
			    स्थिर काष्ठा mvpp2_ethtool_counter *counter)
अणु
	u64 val;

	val = पढ़ोl(port->stats_base + counter->offset);
	अगर (counter->reg_is_64b)
		val += (u64)पढ़ोl(port->stats_base + counter->offset + 4) << 32;

	वापस val;
पूर्ण

/* Some counters are accessed indirectly by first writing an index to
 * MVPP2_CTRS_IDX. The index can represent various resources depending on the
 * रेजिस्टर we access, it can be a hit counter क्रम some classअगरication tables,
 * a counter specअगरic to a rxq, a txq or a buffer pool.
 */
अटल u32 mvpp2_पढ़ो_index(काष्ठा mvpp2 *priv, u32 index, u32 reg)
अणु
	mvpp2_ग_लिखो(priv, MVPP2_CTRS_IDX, index);
	वापस mvpp2_पढ़ो(priv, reg);
पूर्ण

/* Due to the fact that software statistics and hardware statistics are, by
 * design, incremented at dअगरferent moments in the chain of packet processing,
 * it is very likely that incoming packets could have been dropped after being
 * counted by hardware but beक्रमe reaching software statistics (most probably
 * multicast packets), and in the oppposite way, during transmission, FCS bytes
 * are added in between as well as TSO skb will be split and header bytes added.
 * Hence, statistics gathered from userspace with अगरconfig (software) and
 * ethtool (hardware) cannot be compared.
 */
अटल स्थिर काष्ठा mvpp2_ethtool_counter mvpp2_ethtool_mib_regs[] = अणु
	अणु MVPP2_MIB_GOOD_OCTETS_RCVD, "good_octets_received", true पूर्ण,
	अणु MVPP2_MIB_BAD_OCTETS_RCVD, "bad_octets_received" पूर्ण,
	अणु MVPP2_MIB_CRC_ERRORS_SENT, "crc_errors_sent" पूर्ण,
	अणु MVPP2_MIB_UNICAST_FRAMES_RCVD, "unicast_frames_received" पूर्ण,
	अणु MVPP2_MIB_BROADCAST_FRAMES_RCVD, "broadcast_frames_received" पूर्ण,
	अणु MVPP2_MIB_MULTICAST_FRAMES_RCVD, "multicast_frames_received" पूर्ण,
	अणु MVPP2_MIB_FRAMES_64_OCTETS, "frames_64_octets" पूर्ण,
	अणु MVPP2_MIB_FRAMES_65_TO_127_OCTETS, "frames_65_to_127_octet" पूर्ण,
	अणु MVPP2_MIB_FRAMES_128_TO_255_OCTETS, "frames_128_to_255_octet" पूर्ण,
	अणु MVPP2_MIB_FRAMES_256_TO_511_OCTETS, "frames_256_to_511_octet" पूर्ण,
	अणु MVPP2_MIB_FRAMES_512_TO_1023_OCTETS, "frames_512_to_1023_octet" पूर्ण,
	अणु MVPP2_MIB_FRAMES_1024_TO_MAX_OCTETS, "frames_1024_to_max_octet" पूर्ण,
	अणु MVPP2_MIB_GOOD_OCTETS_SENT, "good_octets_sent", true पूर्ण,
	अणु MVPP2_MIB_UNICAST_FRAMES_SENT, "unicast_frames_sent" पूर्ण,
	अणु MVPP2_MIB_MULTICAST_FRAMES_SENT, "multicast_frames_sent" पूर्ण,
	अणु MVPP2_MIB_BROADCAST_FRAMES_SENT, "broadcast_frames_sent" पूर्ण,
	अणु MVPP2_MIB_FC_SENT, "fc_sent" पूर्ण,
	अणु MVPP2_MIB_FC_RCVD, "fc_received" पूर्ण,
	अणु MVPP2_MIB_RX_FIFO_OVERRUN, "rx_fifo_overrun" पूर्ण,
	अणु MVPP2_MIB_UNDERSIZE_RCVD, "undersize_received" पूर्ण,
	अणु MVPP2_MIB_FRAGMENTS_RCVD, "fragments_received" पूर्ण,
	अणु MVPP2_MIB_OVERSIZE_RCVD, "oversize_received" पूर्ण,
	अणु MVPP2_MIB_JABBER_RCVD, "jabber_received" पूर्ण,
	अणु MVPP2_MIB_MAC_RCV_ERROR, "mac_receive_error" पूर्ण,
	अणु MVPP2_MIB_BAD_CRC_EVENT, "bad_crc_event" पूर्ण,
	अणु MVPP2_MIB_COLLISION, "collision" पूर्ण,
	अणु MVPP2_MIB_LATE_COLLISION, "late_collision" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mvpp2_ethtool_counter mvpp2_ethtool_port_regs[] = अणु
	अणु MVPP2_OVERRUN_ETH_DROP, "rx_fifo_or_parser_overrun_drops" पूर्ण,
	अणु MVPP2_CLS_ETH_DROP, "rx_classifier_drops" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mvpp2_ethtool_counter mvpp2_ethtool_txq_regs[] = अणु
	अणु MVPP2_TX_DESC_ENQ_CTR, "txq_%d_desc_enqueue" पूर्ण,
	अणु MVPP2_TX_DESC_ENQ_TO_DDR_CTR, "txq_%d_desc_enqueue_to_ddr" पूर्ण,
	अणु MVPP2_TX_BUFF_ENQ_TO_DDR_CTR, "txq_%d_buff_euqueue_to_ddr" पूर्ण,
	अणु MVPP2_TX_DESC_ENQ_HW_FWD_CTR, "txq_%d_desc_hardware_forwarded" पूर्ण,
	अणु MVPP2_TX_PKTS_DEQ_CTR, "txq_%d_packets_dequeued" पूर्ण,
	अणु MVPP2_TX_PKTS_FULL_QUEUE_DROP_CTR, "txq_%d_queue_full_drops" पूर्ण,
	अणु MVPP2_TX_PKTS_EARLY_DROP_CTR, "txq_%d_packets_early_drops" पूर्ण,
	अणु MVPP2_TX_PKTS_BM_DROP_CTR, "txq_%d_packets_bm_drops" पूर्ण,
	अणु MVPP2_TX_PKTS_BM_MC_DROP_CTR, "txq_%d_packets_rep_bm_drops" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mvpp2_ethtool_counter mvpp2_ethtool_rxq_regs[] = अणु
	अणु MVPP2_RX_DESC_ENQ_CTR, "rxq_%d_desc_enqueue" पूर्ण,
	अणु MVPP2_RX_PKTS_FULL_QUEUE_DROP_CTR, "rxq_%d_queue_full_drops" पूर्ण,
	अणु MVPP2_RX_PKTS_EARLY_DROP_CTR, "rxq_%d_packets_early_drops" पूर्ण,
	अणु MVPP2_RX_PKTS_BM_DROP_CTR, "rxq_%d_packets_bm_drops" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mvpp2_ethtool_counter mvpp2_ethtool_xdp[] = अणु
	अणु ETHTOOL_XDP_REसूचीECT, "rx_xdp_redirect", पूर्ण,
	अणु ETHTOOL_XDP_PASS, "rx_xdp_pass", पूर्ण,
	अणु ETHTOOL_XDP_DROP, "rx_xdp_drop", पूर्ण,
	अणु ETHTOOL_XDP_TX, "rx_xdp_tx", पूर्ण,
	अणु ETHTOOL_XDP_TX_ERR, "rx_xdp_tx_errors", पूर्ण,
	अणु ETHTOOL_XDP_XMIT, "tx_xdp_xmit", पूर्ण,
	अणु ETHTOOL_XDP_XMIT_ERR, "tx_xdp_xmit_errors", पूर्ण,
पूर्ण;

#घोषणा MVPP2_N_ETHTOOL_STATS(ntxqs, nrxqs)	(ARRAY_SIZE(mvpp2_ethtool_mib_regs) + \
						 ARRAY_SIZE(mvpp2_ethtool_port_regs) + \
						 (ARRAY_SIZE(mvpp2_ethtool_txq_regs) * (ntxqs)) + \
						 (ARRAY_SIZE(mvpp2_ethtool_rxq_regs) * (nrxqs)) + \
						 ARRAY_SIZE(mvpp2_ethtool_xdp))

अटल व्योम mvpp2_ethtool_get_strings(काष्ठा net_device *netdev, u32 sset,
				      u8 *data)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(netdev);
	पूर्णांक i, q;

	अगर (sset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_mib_regs); i++) अणु
		strscpy(data, mvpp2_ethtool_mib_regs[i].string,
			ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_port_regs); i++) अणु
		strscpy(data, mvpp2_ethtool_port_regs[i].string,
			ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	पूर्ण

	क्रम (q = 0; q < port->ntxqs; q++) अणु
		क्रम (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_txq_regs); i++) अणु
			snम_लिखो(data, ETH_GSTRING_LEN,
				 mvpp2_ethtool_txq_regs[i].string, q);
			data += ETH_GSTRING_LEN;
		पूर्ण
	पूर्ण

	क्रम (q = 0; q < port->nrxqs; q++) अणु
		क्रम (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_rxq_regs); i++) अणु
			snम_लिखो(data, ETH_GSTRING_LEN,
				 mvpp2_ethtool_rxq_regs[i].string,
				 q);
			data += ETH_GSTRING_LEN;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_xdp); i++) अणु
		strscpy(data, mvpp2_ethtool_xdp[i].string,
			ETH_GSTRING_LEN);
		data += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल व्योम
mvpp2_get_xdp_stats(काष्ठा mvpp2_port *port, काष्ठा mvpp2_pcpu_stats *xdp_stats)
अणु
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक cpu;

	/* Gather XDP Statistics */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा mvpp2_pcpu_stats *cpu_stats;
		u64	xdp_redirect;
		u64	xdp_pass;
		u64	xdp_drop;
		u64	xdp_xmit;
		u64	xdp_xmit_err;
		u64	xdp_tx;
		u64	xdp_tx_err;

		cpu_stats = per_cpu_ptr(port->stats, cpu);
		करो अणु
			start = u64_stats_fetch_begin_irq(&cpu_stats->syncp);
			xdp_redirect = cpu_stats->xdp_redirect;
			xdp_pass   = cpu_stats->xdp_pass;
			xdp_drop = cpu_stats->xdp_drop;
			xdp_xmit   = cpu_stats->xdp_xmit;
			xdp_xmit_err   = cpu_stats->xdp_xmit_err;
			xdp_tx   = cpu_stats->xdp_tx;
			xdp_tx_err   = cpu_stats->xdp_tx_err;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&cpu_stats->syncp, start));

		xdp_stats->xdp_redirect += xdp_redirect;
		xdp_stats->xdp_pass   += xdp_pass;
		xdp_stats->xdp_drop += xdp_drop;
		xdp_stats->xdp_xmit   += xdp_xmit;
		xdp_stats->xdp_xmit_err   += xdp_xmit_err;
		xdp_stats->xdp_tx   += xdp_tx;
		xdp_stats->xdp_tx_err   += xdp_tx_err;
	पूर्ण
पूर्ण

अटल व्योम mvpp2_पढ़ो_stats(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2_pcpu_stats xdp_stats = अणुपूर्ण;
	स्थिर काष्ठा mvpp2_ethtool_counter *s;
	u64 *pstats;
	पूर्णांक i, q;

	pstats = port->ethtool_stats;

	क्रम (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_mib_regs); i++)
		*pstats++ += mvpp2_पढ़ो_count(port, &mvpp2_ethtool_mib_regs[i]);

	क्रम (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_port_regs); i++)
		*pstats++ += mvpp2_पढ़ो(port->priv,
					mvpp2_ethtool_port_regs[i].offset +
					4 * port->id);

	क्रम (q = 0; q < port->ntxqs; q++)
		क्रम (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_txq_regs); i++)
			*pstats++ += mvpp2_पढ़ो_index(port->priv,
						      MVPP22_CTRS_TX_CTR(port->id, q),
						      mvpp2_ethtool_txq_regs[i].offset);

	/* Rxqs are numbered from 0 from the user standpoपूर्णांक, but not from the
	 * driver's. We need to add the  port->first_rxq offset.
	 */
	क्रम (q = 0; q < port->nrxqs; q++)
		क्रम (i = 0; i < ARRAY_SIZE(mvpp2_ethtool_rxq_regs); i++)
			*pstats++ += mvpp2_पढ़ो_index(port->priv,
						      port->first_rxq + q,
						      mvpp2_ethtool_rxq_regs[i].offset);

	/* Gather XDP Statistics */
	mvpp2_get_xdp_stats(port, &xdp_stats);

	क्रम (i = 0, s = mvpp2_ethtool_xdp;
		 s < mvpp2_ethtool_xdp + ARRAY_SIZE(mvpp2_ethtool_xdp);
	     s++, i++) अणु
		चयन (s->offset) अणु
		हाल ETHTOOL_XDP_REसूचीECT:
			*pstats++ = xdp_stats.xdp_redirect;
			अवरोध;
		हाल ETHTOOL_XDP_PASS:
			*pstats++ = xdp_stats.xdp_pass;
			अवरोध;
		हाल ETHTOOL_XDP_DROP:
			*pstats++ = xdp_stats.xdp_drop;
			अवरोध;
		हाल ETHTOOL_XDP_TX:
			*pstats++ = xdp_stats.xdp_tx;
			अवरोध;
		हाल ETHTOOL_XDP_TX_ERR:
			*pstats++ = xdp_stats.xdp_tx_err;
			अवरोध;
		हाल ETHTOOL_XDP_XMIT:
			*pstats++ = xdp_stats.xdp_xmit;
			अवरोध;
		हाल ETHTOOL_XDP_XMIT_ERR:
			*pstats++ = xdp_stats.xdp_xmit_err;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mvpp2_gather_hw_statistics(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *del_work = to_delayed_work(work);
	काष्ठा mvpp2_port *port = container_of(del_work, काष्ठा mvpp2_port,
					       stats_work);

	mutex_lock(&port->gather_stats_lock);

	mvpp2_पढ़ो_stats(port);

	/* No need to पढ़ो again the counters right after this function अगर it
	 * was called asynchronously by the user (ie. use of ethtool).
	 */
	cancel_delayed_work(&port->stats_work);
	queue_delayed_work(port->priv->stats_queue, &port->stats_work,
			   MVPP2_MIB_COUNTERS_STATS_DELAY);

	mutex_unlock(&port->gather_stats_lock);
पूर्ण

अटल व्योम mvpp2_ethtool_get_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	/* Update statistics क्रम the given port, then take the lock to aव्योम
	 * concurrent accesses on the ethtool_stats काष्ठाure during its copy.
	 */
	mvpp2_gather_hw_statistics(&port->stats_work.work);

	mutex_lock(&port->gather_stats_lock);
	स_नकल(data, port->ethtool_stats,
	       माप(u64) * MVPP2_N_ETHTOOL_STATS(port->ntxqs, port->nrxqs));
	mutex_unlock(&port->gather_stats_lock);
पूर्ण

अटल पूर्णांक mvpp2_ethtool_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	अगर (sset == ETH_SS_STATS)
		वापस MVPP2_N_ETHTOOL_STATS(port->ntxqs, port->nrxqs);

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम mvpp2_mac_reset_निश्चित(काष्ठा mvpp2_port *port)
अणु
	u32 val;

	val = पढ़ोl(port->base + MVPP2_GMAC_CTRL_2_REG) |
	      MVPP2_GMAC_PORT_RESET_MASK;
	ग_लिखोl(val, port->base + MVPP2_GMAC_CTRL_2_REG);

	अगर (port->priv->hw_version >= MVPP22 && port->gop_id == 0) अणु
		val = पढ़ोl(port->base + MVPP22_XLG_CTRL0_REG) &
		      ~MVPP22_XLG_CTRL0_MAC_RESET_DIS;
		ग_लिखोl(val, port->base + MVPP22_XLG_CTRL0_REG);
	पूर्ण
पूर्ण

अटल व्योम mvpp22_pcs_reset_निश्चित(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	व्योम __iomem *mpcs, *xpcs;
	u32 val;

	अगर (port->priv->hw_version == MVPP21 || port->gop_id != 0)
		वापस;

	mpcs = priv->अगरace_base + MVPP22_MPCS_BASE(port->gop_id);
	xpcs = priv->अगरace_base + MVPP22_XPCS_BASE(port->gop_id);

	val = पढ़ोl(mpcs + MVPP22_MPCS_CLK_RESET);
	val &= ~(MAC_CLK_RESET_MAC | MAC_CLK_RESET_SD_RX | MAC_CLK_RESET_SD_TX);
	val |= MVPP22_MPCS_CLK_RESET_DIV_SET;
	ग_लिखोl(val, mpcs + MVPP22_MPCS_CLK_RESET);

	val = पढ़ोl(xpcs + MVPP22_XPCS_CFG0);
	ग_लिखोl(val & ~MVPP22_XPCS_CFG0_RESET_DIS, xpcs + MVPP22_XPCS_CFG0);
पूर्ण

अटल व्योम mvpp22_pcs_reset_deनिश्चित(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	व्योम __iomem *mpcs, *xpcs;
	u32 val;

	अगर (port->priv->hw_version == MVPP21 || port->gop_id != 0)
		वापस;

	mpcs = priv->अगरace_base + MVPP22_MPCS_BASE(port->gop_id);
	xpcs = priv->अगरace_base + MVPP22_XPCS_BASE(port->gop_id);

	चयन (port->phy_पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_10GBASER:
		val = पढ़ोl(mpcs + MVPP22_MPCS_CLK_RESET);
		val |= MAC_CLK_RESET_MAC | MAC_CLK_RESET_SD_RX |
		       MAC_CLK_RESET_SD_TX;
		val &= ~MVPP22_MPCS_CLK_RESET_DIV_SET;
		ग_लिखोl(val, mpcs + MVPP22_MPCS_CLK_RESET);
		अवरोध;
	हाल PHY_INTERFACE_MODE_XAUI:
	हाल PHY_INTERFACE_MODE_RXAUI:
		val = पढ़ोl(xpcs + MVPP22_XPCS_CFG0);
		ग_लिखोl(val | MVPP22_XPCS_CFG0_RESET_DIS, xpcs + MVPP22_XPCS_CFG0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* Change maximum receive size of the port */
अटल अंतरभूत व्योम mvpp2_gmac_max_rx_size_set(काष्ठा mvpp2_port *port)
अणु
	u32 val;

	val = पढ़ोl(port->base + MVPP2_GMAC_CTRL_0_REG);
	val &= ~MVPP2_GMAC_MAX_RX_SIZE_MASK;
	val |= (((port->pkt_size - MVPP2_MH_SIZE) / 2) <<
		    MVPP2_GMAC_MAX_RX_SIZE_OFFS);
	ग_लिखोl(val, port->base + MVPP2_GMAC_CTRL_0_REG);
पूर्ण

/* Change maximum receive size of the port */
अटल अंतरभूत व्योम mvpp2_xlg_max_rx_size_set(काष्ठा mvpp2_port *port)
अणु
	u32 val;

	val =  पढ़ोl(port->base + MVPP22_XLG_CTRL1_REG);
	val &= ~MVPP22_XLG_CTRL1_FRAMESIZELIMIT_MASK;
	val |= ((port->pkt_size - MVPP2_MH_SIZE) / 2) <<
	       MVPP22_XLG_CTRL1_FRAMESIZELIMIT_OFFS;
	ग_लिखोl(val, port->base + MVPP22_XLG_CTRL1_REG);
पूर्ण

/* Set शेषs to the MVPP2 port */
अटल व्योम mvpp2_शेषs_set(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक tx_port_num, val, queue, lrxq;

	अगर (port->priv->hw_version == MVPP21) अणु
		/* Update TX FIFO MIN Threshold */
		val = पढ़ोl(port->base + MVPP2_GMAC_PORT_FIFO_CFG_1_REG);
		val &= ~MVPP2_GMAC_TX_FIFO_MIN_TH_ALL_MASK;
		/* Min. TX threshold must be less than minimal packet length */
		val |= MVPP2_GMAC_TX_FIFO_MIN_TH_MASK(64 - 4 - 2);
		ग_लिखोl(val, port->base + MVPP2_GMAC_PORT_FIFO_CFG_1_REG);
	पूर्ण

	/* Disable Legacy WRR, Disable EJP, Release from reset */
	tx_port_num = mvpp2_egress_port(port);
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_PORT_INDEX_REG,
		    tx_port_num);
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_CMD_1_REG, 0);

	/* Set TXQ scheduling to Round-Robin */
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_FIXED_PRIO_REG, 0);

	/* Close bandwidth क्रम all queues */
	क्रम (queue = 0; queue < MVPP2_MAX_TXQ; queue++)
		mvpp2_ग_लिखो(port->priv,
			    MVPP2_TXQ_SCHED_TOKEN_CNTR_REG(queue), 0);

	/* Set refill period to 1 usec, refill tokens
	 * and bucket size to maximum
	 */
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_PERIOD_REG,
		    port->priv->tclk / USEC_PER_SEC);
	val = mvpp2_पढ़ो(port->priv, MVPP2_TXP_SCHED_REFILL_REG);
	val &= ~MVPP2_TXP_REFILL_PERIOD_ALL_MASK;
	val |= MVPP2_TXP_REFILL_PERIOD_MASK(1);
	val |= MVPP2_TXP_REFILL_TOKENS_ALL_MASK;
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_REFILL_REG, val);
	val = MVPP2_TXP_TOKEN_SIZE_MAX;
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_TOKEN_SIZE_REG, val);

	/* Set MaximumLowLatencyPacketSize value to 256 */
	mvpp2_ग_लिखो(port->priv, MVPP2_RX_CTRL_REG(port->id),
		    MVPP2_RX_USE_PSEUDO_FOR_CSUM_MASK |
		    MVPP2_RX_LOW_LATENCY_PKT_SIZE(256));

	/* Enable Rx cache snoop */
	क्रम (lrxq = 0; lrxq < port->nrxqs; lrxq++) अणु
		queue = port->rxqs[lrxq]->id;
		val = mvpp2_पढ़ो(port->priv, MVPP2_RXQ_CONFIG_REG(queue));
		val |= MVPP2_SNOOP_PKT_SIZE_MASK |
			   MVPP2_SNOOP_BUF_HDR_MASK;
		mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_CONFIG_REG(queue), val);
	पूर्ण

	/* At शेष, mask all पूर्णांकerrupts to all present cpus */
	mvpp2_पूर्णांकerrupts_disable(port);
पूर्ण

/* Enable/disable receiving packets */
अटल व्योम mvpp2_ingress_enable(काष्ठा mvpp2_port *port)
अणु
	u32 val;
	पूर्णांक lrxq, queue;

	क्रम (lrxq = 0; lrxq < port->nrxqs; lrxq++) अणु
		queue = port->rxqs[lrxq]->id;
		val = mvpp2_पढ़ो(port->priv, MVPP2_RXQ_CONFIG_REG(queue));
		val &= ~MVPP2_RXQ_DISABLE_MASK;
		mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_CONFIG_REG(queue), val);
	पूर्ण
पूर्ण

अटल व्योम mvpp2_ingress_disable(काष्ठा mvpp2_port *port)
अणु
	u32 val;
	पूर्णांक lrxq, queue;

	क्रम (lrxq = 0; lrxq < port->nrxqs; lrxq++) अणु
		queue = port->rxqs[lrxq]->id;
		val = mvpp2_पढ़ो(port->priv, MVPP2_RXQ_CONFIG_REG(queue));
		val |= MVPP2_RXQ_DISABLE_MASK;
		mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_CONFIG_REG(queue), val);
	पूर्ण
पूर्ण

/* Enable transmit via physical egress queue
 * - HW starts take descriptors from DRAM
 */
अटल व्योम mvpp2_egress_enable(काष्ठा mvpp2_port *port)
अणु
	u32 qmap;
	पूर्णांक queue;
	पूर्णांक tx_port_num = mvpp2_egress_port(port);

	/* Enable all initialized TXs. */
	qmap = 0;
	क्रम (queue = 0; queue < port->ntxqs; queue++) अणु
		काष्ठा mvpp2_tx_queue *txq = port->txqs[queue];

		अगर (txq->descs)
			qmap |= (1 << queue);
	पूर्ण

	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_PORT_INDEX_REG, tx_port_num);
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_Q_CMD_REG, qmap);
पूर्ण

/* Disable transmit via physical egress queue
 * - HW करोesn't take descriptors from DRAM
 */
अटल व्योम mvpp2_egress_disable(काष्ठा mvpp2_port *port)
अणु
	u32 reg_data;
	पूर्णांक delay;
	पूर्णांक tx_port_num = mvpp2_egress_port(port);

	/* Issue stop command क्रम active channels only */
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_PORT_INDEX_REG, tx_port_num);
	reg_data = (mvpp2_पढ़ो(port->priv, MVPP2_TXP_SCHED_Q_CMD_REG)) &
		    MVPP2_TXP_SCHED_ENQ_MASK;
	अगर (reg_data != 0)
		mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_Q_CMD_REG,
			    (reg_data << MVPP2_TXP_SCHED_DISQ_OFFSET));

	/* Wait क्रम all Tx activity to terminate. */
	delay = 0;
	करो अणु
		अगर (delay >= MVPP2_TX_DISABLE_TIMEOUT_MSEC) अणु
			netdev_warn(port->dev,
				    "Tx stop timed out, status=0x%08x\n",
				    reg_data);
			अवरोध;
		पूर्ण
		mdelay(1);
		delay++;

		/* Check port TX Command रेजिस्टर that all
		 * Tx queues are stopped
		 */
		reg_data = mvpp2_पढ़ो(port->priv, MVPP2_TXP_SCHED_Q_CMD_REG);
	पूर्ण जबतक (reg_data & MVPP2_TXP_SCHED_ENQ_MASK);
पूर्ण

/* Rx descriptors helper methods */

/* Get number of Rx descriptors occupied by received packets */
अटल अंतरभूत पूर्णांक
mvpp2_rxq_received(काष्ठा mvpp2_port *port, पूर्णांक rxq_id)
अणु
	u32 val = mvpp2_पढ़ो(port->priv, MVPP2_RXQ_STATUS_REG(rxq_id));

	वापस val & MVPP2_RXQ_OCCUPIED_MASK;
पूर्ण

/* Update Rx queue status with the number of occupied and available
 * Rx descriptor slots.
 */
अटल अंतरभूत व्योम
mvpp2_rxq_status_update(काष्ठा mvpp2_port *port, पूर्णांक rxq_id,
			पूर्णांक used_count, पूर्णांक मुक्त_count)
अणु
	/* Decrement the number of used descriptors and increment count
	 * increment the number of मुक्त descriptors.
	 */
	u32 val = used_count | (मुक्त_count << MVPP2_RXQ_NUM_NEW_OFFSET);

	mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_STATUS_UPDATE_REG(rxq_id), val);
पूर्ण

/* Get poपूर्णांकer to next RX descriptor to be processed by SW */
अटल अंतरभूत काष्ठा mvpp2_rx_desc *
mvpp2_rxq_next_desc_get(काष्ठा mvpp2_rx_queue *rxq)
अणु
	पूर्णांक rx_desc = rxq->next_desc_to_proc;

	rxq->next_desc_to_proc = MVPP2_QUEUE_NEXT_DESC(rxq, rx_desc);
	prefetch(rxq->descs + rxq->next_desc_to_proc);
	वापस rxq->descs + rx_desc;
पूर्ण

/* Set rx queue offset */
अटल व्योम mvpp2_rxq_offset_set(काष्ठा mvpp2_port *port,
				 पूर्णांक prxq, पूर्णांक offset)
अणु
	u32 val;

	/* Convert offset from bytes to units of 32 bytes */
	offset = offset >> 5;

	val = mvpp2_पढ़ो(port->priv, MVPP2_RXQ_CONFIG_REG(prxq));
	val &= ~MVPP2_RXQ_PACKET_OFFSET_MASK;

	/* Offset is in */
	val |= ((offset << MVPP2_RXQ_PACKET_OFFSET_OFFS) &
		    MVPP2_RXQ_PACKET_OFFSET_MASK);

	mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_CONFIG_REG(prxq), val);
पूर्ण

/* Tx descriptors helper methods */

/* Get poपूर्णांकer to next Tx descriptor to be processed (send) by HW */
अटल काष्ठा mvpp2_tx_desc *
mvpp2_txq_next_desc_get(काष्ठा mvpp2_tx_queue *txq)
अणु
	पूर्णांक tx_desc = txq->next_desc_to_proc;

	txq->next_desc_to_proc = MVPP2_QUEUE_NEXT_DESC(txq, tx_desc);
	वापस txq->descs + tx_desc;
पूर्ण

/* Update HW with number of aggregated Tx descriptors to be sent
 *
 * Called only from mvpp2_tx(), so migration is disabled, using
 * smp_processor_id() is OK.
 */
अटल व्योम mvpp2_aggr_txq_pend_desc_add(काष्ठा mvpp2_port *port, पूर्णांक pending)
अणु
	/* aggregated access - relevant TXQ number is written in TX desc */
	mvpp2_thपढ़ो_ग_लिखो(port->priv,
			   mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id()),
			   MVPP2_AGGR_TXQ_UPDATE_REG, pending);
पूर्ण

/* Check अगर there are enough मुक्त descriptors in aggregated txq.
 * If not, update the number of occupied descriptors and repeat the check.
 *
 * Called only from mvpp2_tx(), so migration is disabled, using
 * smp_processor_id() is OK.
 */
अटल पूर्णांक mvpp2_aggr_desc_num_check(काष्ठा mvpp2_port *port,
				     काष्ठा mvpp2_tx_queue *aggr_txq, पूर्णांक num)
अणु
	अगर ((aggr_txq->count + num) > MVPP2_AGGR_TXQ_SIZE) अणु
		/* Update number of occupied aggregated Tx descriptors */
		अचिन्हित पूर्णांक thपढ़ो =
			mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id());
		u32 val = mvpp2_पढ़ो_relaxed(port->priv,
					     MVPP2_AGGR_TXQ_STATUS_REG(thपढ़ो));

		aggr_txq->count = val & MVPP2_AGGR_TXQ_PENDING_MASK;

		अगर ((aggr_txq->count + num) > MVPP2_AGGR_TXQ_SIZE)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/* Reserved Tx descriptors allocation request
 *
 * Called only from mvpp2_txq_reserved_desc_num_proc(), itself called
 * only by mvpp2_tx(), so migration is disabled, using
 * smp_processor_id() is OK.
 */
अटल पूर्णांक mvpp2_txq_alloc_reserved_desc(काष्ठा mvpp2_port *port,
					 काष्ठा mvpp2_tx_queue *txq, पूर्णांक num)
अणु
	अचिन्हित पूर्णांक thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id());
	काष्ठा mvpp2 *priv = port->priv;
	u32 val;

	val = (txq->id << MVPP2_TXQ_RSVD_REQ_Q_OFFSET) | num;
	mvpp2_thपढ़ो_ग_लिखो_relaxed(priv, thपढ़ो, MVPP2_TXQ_RSVD_REQ_REG, val);

	val = mvpp2_thपढ़ो_पढ़ो_relaxed(priv, thपढ़ो, MVPP2_TXQ_RSVD_RSLT_REG);

	वापस val & MVPP2_TXQ_RSVD_RSLT_MASK;
पूर्ण

/* Check अगर there are enough reserved descriptors क्रम transmission.
 * If not, request chunk of reserved descriptors and check again.
 */
अटल पूर्णांक mvpp2_txq_reserved_desc_num_proc(काष्ठा mvpp2_port *port,
					    काष्ठा mvpp2_tx_queue *txq,
					    काष्ठा mvpp2_txq_pcpu *txq_pcpu,
					    पूर्णांक num)
अणु
	पूर्णांक req, desc_count;
	अचिन्हित पूर्णांक thपढ़ो;

	अगर (txq_pcpu->reserved_num >= num)
		वापस 0;

	/* Not enough descriptors reserved! Update the reserved descriptor
	 * count and check again.
	 */

	desc_count = 0;
	/* Compute total of used descriptors */
	क्रम (thपढ़ो = 0; thपढ़ो < port->priv->nthपढ़ोs; thपढ़ो++) अणु
		काष्ठा mvpp2_txq_pcpu *txq_pcpu_aux;

		txq_pcpu_aux = per_cpu_ptr(txq->pcpu, thपढ़ो);
		desc_count += txq_pcpu_aux->count;
		desc_count += txq_pcpu_aux->reserved_num;
	पूर्ण

	req = max(MVPP2_CPU_DESC_CHUNK, num - txq_pcpu->reserved_num);
	desc_count += req;

	अगर (desc_count >
	   (txq->size - (MVPP2_MAX_THREADS * MVPP2_CPU_DESC_CHUNK)))
		वापस -ENOMEM;

	txq_pcpu->reserved_num += mvpp2_txq_alloc_reserved_desc(port, txq, req);

	/* OK, the descriptor could have been updated: check again. */
	अगर (txq_pcpu->reserved_num < num)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/* Release the last allocated Tx descriptor. Useful to handle DMA
 * mapping failures in the Tx path.
 */
अटल व्योम mvpp2_txq_desc_put(काष्ठा mvpp2_tx_queue *txq)
अणु
	अगर (txq->next_desc_to_proc == 0)
		txq->next_desc_to_proc = txq->last_desc - 1;
	अन्यथा
		txq->next_desc_to_proc--;
पूर्ण

/* Set Tx descriptors fields relevant क्रम CSUM calculation */
अटल u32 mvpp2_txq_desc_csum(पूर्णांक l3_offs, __be16 l3_proto,
			       पूर्णांक ip_hdr_len, पूर्णांक l4_proto)
अणु
	u32 command;

	/* fields: L3_offset, IP_hdrlen, L3_type, G_IPv4_chk,
	 * G_L4_chk, L4_type required only क्रम checksum calculation
	 */
	command = (l3_offs << MVPP2_TXD_L3_OFF_SHIFT);
	command |= (ip_hdr_len << MVPP2_TXD_IP_HLEN_SHIFT);
	command |= MVPP2_TXD_IP_CSUM_DISABLE;

	अगर (l3_proto == htons(ETH_P_IP)) अणु
		command &= ~MVPP2_TXD_IP_CSUM_DISABLE;	/* enable IPv4 csum */
		command &= ~MVPP2_TXD_L3_IP6;		/* enable IPv4 */
	पूर्ण अन्यथा अणु
		command |= MVPP2_TXD_L3_IP6;		/* enable IPv6 */
	पूर्ण

	अगर (l4_proto == IPPROTO_TCP) अणु
		command &= ~MVPP2_TXD_L4_UDP;		/* enable TCP */
		command &= ~MVPP2_TXD_L4_CSUM_FRAG;	/* generate L4 csum */
	पूर्ण अन्यथा अगर (l4_proto == IPPROTO_UDP) अणु
		command |= MVPP2_TXD_L4_UDP;		/* enable UDP */
		command &= ~MVPP2_TXD_L4_CSUM_FRAG;	/* generate L4 csum */
	पूर्ण अन्यथा अणु
		command |= MVPP2_TXD_L4_CSUM_NOT;
	पूर्ण

	वापस command;
पूर्ण

/* Get number of sent descriptors and decrement counter.
 * The number of sent descriptors is वापसed.
 * Per-thपढ़ो access
 *
 * Called only from mvpp2_txq_करोne(), called from mvpp2_tx()
 * (migration disabled) and from the TX completion tasklet (migration
 * disabled) so using smp_processor_id() is OK.
 */
अटल अंतरभूत पूर्णांक mvpp2_txq_sent_desc_proc(काष्ठा mvpp2_port *port,
					   काष्ठा mvpp2_tx_queue *txq)
अणु
	u32 val;

	/* Reading status reg resets transmitted descriptor counter */
	val = mvpp2_thपढ़ो_पढ़ो_relaxed(port->priv,
					mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id()),
					MVPP2_TXQ_SENT_REG(txq->id));

	वापस (val & MVPP2_TRANSMITTED_COUNT_MASK) >>
		MVPP2_TRANSMITTED_COUNT_OFFSET;
पूर्ण

/* Called through on_each_cpu(), so runs on all CPUs, with migration
 * disabled, thereक्रमe using smp_processor_id() is OK.
 */
अटल व्योम mvpp2_txq_sent_counter_clear(व्योम *arg)
अणु
	काष्ठा mvpp2_port *port = arg;
	पूर्णांक queue;

	/* If the thपढ़ो isn't used, don't करो anything */
	अगर (smp_processor_id() >= port->priv->nthपढ़ोs)
		वापस;

	क्रम (queue = 0; queue < port->ntxqs; queue++) अणु
		पूर्णांक id = port->txqs[queue]->id;

		mvpp2_thपढ़ो_पढ़ो(port->priv,
				  mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id()),
				  MVPP2_TXQ_SENT_REG(id));
	पूर्ण
पूर्ण

/* Set max sizes क्रम Tx queues */
अटल व्योम mvpp2_txp_max_tx_size_set(काष्ठा mvpp2_port *port)
अणु
	u32	val, size, mtu;
	पूर्णांक	txq, tx_port_num;

	mtu = port->pkt_size * 8;
	अगर (mtu > MVPP2_TXP_MTU_MAX)
		mtu = MVPP2_TXP_MTU_MAX;

	/* WA क्रम wrong Token bucket update: Set MTU value = 3*real MTU value */
	mtu = 3 * mtu;

	/* Indirect access to रेजिस्टरs */
	tx_port_num = mvpp2_egress_port(port);
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_PORT_INDEX_REG, tx_port_num);

	/* Set MTU */
	val = mvpp2_पढ़ो(port->priv, MVPP2_TXP_SCHED_MTU_REG);
	val &= ~MVPP2_TXP_MTU_MAX;
	val |= mtu;
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_MTU_REG, val);

	/* TXP token size and all TXQs token size must be larger that MTU */
	val = mvpp2_पढ़ो(port->priv, MVPP2_TXP_SCHED_TOKEN_SIZE_REG);
	size = val & MVPP2_TXP_TOKEN_SIZE_MAX;
	अगर (size < mtu) अणु
		size = mtu;
		val &= ~MVPP2_TXP_TOKEN_SIZE_MAX;
		val |= size;
		mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_TOKEN_SIZE_REG, val);
	पूर्ण

	क्रम (txq = 0; txq < port->ntxqs; txq++) अणु
		val = mvpp2_पढ़ो(port->priv,
				 MVPP2_TXQ_SCHED_TOKEN_SIZE_REG(txq));
		size = val & MVPP2_TXQ_TOKEN_SIZE_MAX;

		अगर (size < mtu) अणु
			size = mtu;
			val &= ~MVPP2_TXQ_TOKEN_SIZE_MAX;
			val |= size;
			mvpp2_ग_लिखो(port->priv,
				    MVPP2_TXQ_SCHED_TOKEN_SIZE_REG(txq),
				    val);
		पूर्ण
	पूर्ण
पूर्ण

/* Set the number of non-occupied descriptors threshold */
अटल व्योम mvpp2_set_rxq_मुक्त_tresh(काष्ठा mvpp2_port *port,
				     काष्ठा mvpp2_rx_queue *rxq)
अणु
	u32 val;

	mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_NUM_REG, rxq->id);

	val = mvpp2_पढ़ो(port->priv, MVPP2_RXQ_THRESH_REG);
	val &= ~MVPP2_RXQ_NON_OCCUPIED_MASK;
	val |= MSS_THRESHOLD_STOP << MVPP2_RXQ_NON_OCCUPIED_OFFSET;
	mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_THRESH_REG, val);
पूर्ण

/* Set the number of packets that will be received beक्रमe Rx पूर्णांकerrupt
 * will be generated by HW.
 */
अटल व्योम mvpp2_rx_pkts_coal_set(काष्ठा mvpp2_port *port,
				   काष्ठा mvpp2_rx_queue *rxq)
अणु
	अचिन्हित पूर्णांक thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, get_cpu());

	अगर (rxq->pkts_coal > MVPP2_OCCUPIED_THRESH_MASK)
		rxq->pkts_coal = MVPP2_OCCUPIED_THRESH_MASK;

	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_RXQ_NUM_REG, rxq->id);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_RXQ_THRESH_REG,
			   rxq->pkts_coal);

	put_cpu();
पूर्ण

/* For some reason in the LSP this is करोne on each CPU. Why ? */
अटल व्योम mvpp2_tx_pkts_coal_set(काष्ठा mvpp2_port *port,
				   काष्ठा mvpp2_tx_queue *txq)
अणु
	अचिन्हित पूर्णांक thपढ़ो;
	u32 val;

	अगर (txq->करोne_pkts_coal > MVPP2_TXQ_THRESH_MASK)
		txq->करोne_pkts_coal = MVPP2_TXQ_THRESH_MASK;

	val = (txq->करोne_pkts_coal << MVPP2_TXQ_THRESH_OFFSET);
	/* PKT-coalescing रेजिस्टरs are per-queue + per-thपढ़ो */
	क्रम (thपढ़ो = 0; thपढ़ो < MVPP2_MAX_THREADS; thपढ़ो++) अणु
		mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_NUM_REG, txq->id);
		mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_THRESH_REG, val);
	पूर्ण
पूर्ण

अटल u32 mvpp2_usec_to_cycles(u32 usec, अचिन्हित दीर्घ clk_hz)
अणु
	u64 पंचांगp = (u64)clk_hz * usec;

	करो_भाग(पंचांगp, USEC_PER_SEC);

	वापस पंचांगp > U32_MAX ? U32_MAX : पंचांगp;
पूर्ण

अटल u32 mvpp2_cycles_to_usec(u32 cycles, अचिन्हित दीर्घ clk_hz)
अणु
	u64 पंचांगp = (u64)cycles * USEC_PER_SEC;

	करो_भाग(पंचांगp, clk_hz);

	वापस पंचांगp > U32_MAX ? U32_MAX : पंचांगp;
पूर्ण

/* Set the समय delay in usec beक्रमe Rx पूर्णांकerrupt */
अटल व्योम mvpp2_rx_समय_coal_set(काष्ठा mvpp2_port *port,
				   काष्ठा mvpp2_rx_queue *rxq)
अणु
	अचिन्हित दीर्घ freq = port->priv->tclk;
	u32 val = mvpp2_usec_to_cycles(rxq->समय_coal, freq);

	अगर (val > MVPP2_MAX_ISR_RX_THRESHOLD) अणु
		rxq->समय_coal =
			mvpp2_cycles_to_usec(MVPP2_MAX_ISR_RX_THRESHOLD, freq);

		/* re-evaluate to get actual रेजिस्टर value */
		val = mvpp2_usec_to_cycles(rxq->समय_coal, freq);
	पूर्ण

	mvpp2_ग_लिखो(port->priv, MVPP2_ISR_RX_THRESHOLD_REG(rxq->id), val);
पूर्ण

अटल व्योम mvpp2_tx_समय_coal_set(काष्ठा mvpp2_port *port)
अणु
	अचिन्हित दीर्घ freq = port->priv->tclk;
	u32 val = mvpp2_usec_to_cycles(port->tx_समय_coal, freq);

	अगर (val > MVPP2_MAX_ISR_TX_THRESHOLD) अणु
		port->tx_समय_coal =
			mvpp2_cycles_to_usec(MVPP2_MAX_ISR_TX_THRESHOLD, freq);

		/* re-evaluate to get actual रेजिस्टर value */
		val = mvpp2_usec_to_cycles(port->tx_समय_coal, freq);
	पूर्ण

	mvpp2_ग_लिखो(port->priv, MVPP2_ISR_TX_THRESHOLD_REG(port->id), val);
पूर्ण

/* Free Tx queue skbuffs */
अटल व्योम mvpp2_txq_bufs_मुक्त(काष्ठा mvpp2_port *port,
				काष्ठा mvpp2_tx_queue *txq,
				काष्ठा mvpp2_txq_pcpu *txq_pcpu, पूर्णांक num)
अणु
	काष्ठा xdp_frame_bulk bq;
	पूर्णांक i;

	xdp_frame_bulk_init(&bq);

	rcu_पढ़ो_lock(); /* need क्रम xdp_वापस_frame_bulk */

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा mvpp2_txq_pcpu_buf *tx_buf =
			txq_pcpu->buffs + txq_pcpu->txq_get_index;

		अगर (!IS_TSO_HEADER(txq_pcpu, tx_buf->dma) &&
		    tx_buf->type != MVPP2_TYPE_XDP_TX)
			dma_unmap_single(port->dev->dev.parent, tx_buf->dma,
					 tx_buf->size, DMA_TO_DEVICE);
		अगर (tx_buf->type == MVPP2_TYPE_SKB && tx_buf->skb)
			dev_kमुक्त_skb_any(tx_buf->skb);
		अन्यथा अगर (tx_buf->type == MVPP2_TYPE_XDP_TX ||
			 tx_buf->type == MVPP2_TYPE_XDP_NDO)
			xdp_वापस_frame_bulk(tx_buf->xdpf, &bq);

		mvpp2_txq_inc_get(txq_pcpu);
	पूर्ण
	xdp_flush_frame_bulk(&bq);

	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत काष्ठा mvpp2_rx_queue *mvpp2_get_rx_queue(काष्ठा mvpp2_port *port,
							u32 cause)
अणु
	पूर्णांक queue = fls(cause) - 1;

	वापस port->rxqs[queue];
पूर्ण

अटल अंतरभूत काष्ठा mvpp2_tx_queue *mvpp2_get_tx_queue(काष्ठा mvpp2_port *port,
							u32 cause)
अणु
	पूर्णांक queue = fls(cause) - 1;

	वापस port->txqs[queue];
पूर्ण

/* Handle end of transmission */
अटल व्योम mvpp2_txq_करोne(काष्ठा mvpp2_port *port, काष्ठा mvpp2_tx_queue *txq,
			   काष्ठा mvpp2_txq_pcpu *txq_pcpu)
अणु
	काष्ठा netdev_queue *nq = netdev_get_tx_queue(port->dev, txq->log_id);
	पूर्णांक tx_करोne;

	अगर (txq_pcpu->thपढ़ो != mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id()))
		netdev_err(port->dev, "wrong cpu on the end of Tx processing\n");

	tx_करोne = mvpp2_txq_sent_desc_proc(port, txq);
	अगर (!tx_करोne)
		वापस;
	mvpp2_txq_bufs_मुक्त(port, txq, txq_pcpu, tx_करोne);

	txq_pcpu->count -= tx_करोne;

	अगर (netअगर_tx_queue_stopped(nq))
		अगर (txq_pcpu->count <= txq_pcpu->wake_threshold)
			netअगर_tx_wake_queue(nq);
पूर्ण

अटल अचिन्हित पूर्णांक mvpp2_tx_करोne(काष्ठा mvpp2_port *port, u32 cause,
				  अचिन्हित पूर्णांक thपढ़ो)
अणु
	काष्ठा mvpp2_tx_queue *txq;
	काष्ठा mvpp2_txq_pcpu *txq_pcpu;
	अचिन्हित पूर्णांक tx_toकरो = 0;

	जबतक (cause) अणु
		txq = mvpp2_get_tx_queue(port, cause);
		अगर (!txq)
			अवरोध;

		txq_pcpu = per_cpu_ptr(txq->pcpu, thपढ़ो);

		अगर (txq_pcpu->count) अणु
			mvpp2_txq_करोne(port, txq, txq_pcpu);
			tx_toकरो += txq_pcpu->count;
		पूर्ण

		cause &= ~(1 << txq->log_id);
	पूर्ण
	वापस tx_toकरो;
पूर्ण

/* Rx/Tx queue initialization/cleanup methods */

/* Allocate and initialize descriptors क्रम aggr TXQ */
अटल पूर्णांक mvpp2_aggr_txq_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा mvpp2_tx_queue *aggr_txq,
			       अचिन्हित पूर्णांक thपढ़ो, काष्ठा mvpp2 *priv)
अणु
	u32 txq_dma;

	/* Allocate memory क्रम TX descriptors */
	aggr_txq->descs = dma_alloc_coherent(&pdev->dev,
					     MVPP2_AGGR_TXQ_SIZE * MVPP2_DESC_ALIGNED_SIZE,
					     &aggr_txq->descs_dma, GFP_KERNEL);
	अगर (!aggr_txq->descs)
		वापस -ENOMEM;

	aggr_txq->last_desc = MVPP2_AGGR_TXQ_SIZE - 1;

	/* Aggr TXQ no reset WA */
	aggr_txq->next_desc_to_proc = mvpp2_पढ़ो(priv,
						 MVPP2_AGGR_TXQ_INDEX_REG(thपढ़ो));

	/* Set Tx descriptors queue starting address indirect
	 * access
	 */
	अगर (priv->hw_version == MVPP21)
		txq_dma = aggr_txq->descs_dma;
	अन्यथा
		txq_dma = aggr_txq->descs_dma >>
			MVPP22_AGGR_TXQ_DESC_ADDR_OFFS;

	mvpp2_ग_लिखो(priv, MVPP2_AGGR_TXQ_DESC_ADDR_REG(thपढ़ो), txq_dma);
	mvpp2_ग_लिखो(priv, MVPP2_AGGR_TXQ_DESC_SIZE_REG(thपढ़ो),
		    MVPP2_AGGR_TXQ_SIZE);

	वापस 0;
पूर्ण

/* Create a specअगरied Rx queue */
अटल पूर्णांक mvpp2_rxq_init(काष्ठा mvpp2_port *port,
			  काष्ठा mvpp2_rx_queue *rxq)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	अचिन्हित पूर्णांक thपढ़ो;
	u32 rxq_dma;
	पूर्णांक err;

	rxq->size = port->rx_ring_size;

	/* Allocate memory क्रम RX descriptors */
	rxq->descs = dma_alloc_coherent(port->dev->dev.parent,
					rxq->size * MVPP2_DESC_ALIGNED_SIZE,
					&rxq->descs_dma, GFP_KERNEL);
	अगर (!rxq->descs)
		वापस -ENOMEM;

	rxq->last_desc = rxq->size - 1;

	/* Zero occupied and non-occupied counters - direct access */
	mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_STATUS_REG(rxq->id), 0);

	/* Set Rx descriptors queue starting address - indirect access */
	thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, get_cpu());
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_RXQ_NUM_REG, rxq->id);
	अगर (port->priv->hw_version == MVPP21)
		rxq_dma = rxq->descs_dma;
	अन्यथा
		rxq_dma = rxq->descs_dma >> MVPP22_DESC_ADDR_OFFS;
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_RXQ_DESC_ADDR_REG, rxq_dma);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_RXQ_DESC_SIZE_REG, rxq->size);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_RXQ_INDEX_REG, 0);
	put_cpu();

	/* Set Offset */
	mvpp2_rxq_offset_set(port, rxq->id, MVPP2_SKB_HEADROOM);

	/* Set coalescing pkts and समय */
	mvpp2_rx_pkts_coal_set(port, rxq);
	mvpp2_rx_समय_coal_set(port, rxq);

	/* Set the number of non occupied descriptors threshold */
	mvpp2_set_rxq_मुक्त_tresh(port, rxq);

	/* Add number of descriptors पढ़ोy क्रम receiving packets */
	mvpp2_rxq_status_update(port, rxq->id, 0, rxq->size);

	अगर (priv->percpu_pools) अणु
		err = xdp_rxq_info_reg(&rxq->xdp_rxq_लघु, port->dev, rxq->id, 0);
		अगर (err < 0)
			जाओ err_मुक्त_dma;

		err = xdp_rxq_info_reg(&rxq->xdp_rxq_दीर्घ, port->dev, rxq->id, 0);
		अगर (err < 0)
			जाओ err_unरेजिस्टर_rxq_लघु;

		/* Every RXQ has a pool क्रम लघु and another क्रम दीर्घ packets */
		err = xdp_rxq_info_reg_mem_model(&rxq->xdp_rxq_लघु,
						 MEM_TYPE_PAGE_POOL,
						 priv->page_pool[rxq->logic_rxq]);
		अगर (err < 0)
			जाओ err_unरेजिस्टर_rxq_दीर्घ;

		err = xdp_rxq_info_reg_mem_model(&rxq->xdp_rxq_दीर्घ,
						 MEM_TYPE_PAGE_POOL,
						 priv->page_pool[rxq->logic_rxq +
								 port->nrxqs]);
		अगर (err < 0)
			जाओ err_unरेजिस्टर_mem_rxq_लघु;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_mem_rxq_लघु:
	xdp_rxq_info_unreg_mem_model(&rxq->xdp_rxq_लघु);
err_unरेजिस्टर_rxq_दीर्घ:
	xdp_rxq_info_unreg(&rxq->xdp_rxq_दीर्घ);
err_unरेजिस्टर_rxq_लघु:
	xdp_rxq_info_unreg(&rxq->xdp_rxq_लघु);
err_मुक्त_dma:
	dma_मुक्त_coherent(port->dev->dev.parent,
			  rxq->size * MVPP2_DESC_ALIGNED_SIZE,
			  rxq->descs, rxq->descs_dma);
	वापस err;
पूर्ण

/* Push packets received by the RXQ to BM pool */
अटल व्योम mvpp2_rxq_drop_pkts(काष्ठा mvpp2_port *port,
				काष्ठा mvpp2_rx_queue *rxq)
अणु
	पूर्णांक rx_received, i;

	rx_received = mvpp2_rxq_received(port, rxq->id);
	अगर (!rx_received)
		वापस;

	क्रम (i = 0; i < rx_received; i++) अणु
		काष्ठा mvpp2_rx_desc *rx_desc = mvpp2_rxq_next_desc_get(rxq);
		u32 status = mvpp2_rxdesc_status_get(port, rx_desc);
		पूर्णांक pool;

		pool = (status & MVPP2_RXD_BM_POOL_ID_MASK) >>
			MVPP2_RXD_BM_POOL_ID_OFFS;

		mvpp2_bm_pool_put(port, pool,
				  mvpp2_rxdesc_dma_addr_get(port, rx_desc),
				  mvpp2_rxdesc_cookie_get(port, rx_desc));
	पूर्ण
	mvpp2_rxq_status_update(port, rxq->id, rx_received, rx_received);
पूर्ण

/* Cleanup Rx queue */
अटल व्योम mvpp2_rxq_deinit(काष्ठा mvpp2_port *port,
			     काष्ठा mvpp2_rx_queue *rxq)
अणु
	अचिन्हित पूर्णांक thपढ़ो;

	अगर (xdp_rxq_info_is_reg(&rxq->xdp_rxq_लघु))
		xdp_rxq_info_unreg(&rxq->xdp_rxq_लघु);

	अगर (xdp_rxq_info_is_reg(&rxq->xdp_rxq_दीर्घ))
		xdp_rxq_info_unreg(&rxq->xdp_rxq_दीर्घ);

	mvpp2_rxq_drop_pkts(port, rxq);

	अगर (rxq->descs)
		dma_मुक्त_coherent(port->dev->dev.parent,
				  rxq->size * MVPP2_DESC_ALIGNED_SIZE,
				  rxq->descs,
				  rxq->descs_dma);

	rxq->descs             = शून्य;
	rxq->last_desc         = 0;
	rxq->next_desc_to_proc = 0;
	rxq->descs_dma         = 0;

	/* Clear Rx descriptors queue starting address and size;
	 * मुक्त descriptor number
	 */
	mvpp2_ग_लिखो(port->priv, MVPP2_RXQ_STATUS_REG(rxq->id), 0);
	thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, get_cpu());
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_RXQ_NUM_REG, rxq->id);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_RXQ_DESC_ADDR_REG, 0);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_RXQ_DESC_SIZE_REG, 0);
	put_cpu();
पूर्ण

/* Create and initialize a Tx queue */
अटल पूर्णांक mvpp2_txq_init(काष्ठा mvpp2_port *port,
			  काष्ठा mvpp2_tx_queue *txq)
अणु
	u32 val;
	अचिन्हित पूर्णांक thपढ़ो;
	पूर्णांक desc, desc_per_txq, tx_port_num;
	काष्ठा mvpp2_txq_pcpu *txq_pcpu;

	txq->size = port->tx_ring_size;

	/* Allocate memory क्रम Tx descriptors */
	txq->descs = dma_alloc_coherent(port->dev->dev.parent,
				txq->size * MVPP2_DESC_ALIGNED_SIZE,
				&txq->descs_dma, GFP_KERNEL);
	अगर (!txq->descs)
		वापस -ENOMEM;

	txq->last_desc = txq->size - 1;

	/* Set Tx descriptors queue starting address - indirect access */
	thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, get_cpu());
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_NUM_REG, txq->id);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_DESC_ADDR_REG,
			   txq->descs_dma);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_DESC_SIZE_REG,
			   txq->size & MVPP2_TXQ_DESC_SIZE_MASK);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_INDEX_REG, 0);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_RSVD_CLR_REG,
			   txq->id << MVPP2_TXQ_RSVD_CLR_OFFSET);
	val = mvpp2_thपढ़ो_पढ़ो(port->priv, thपढ़ो, MVPP2_TXQ_PENDING_REG);
	val &= ~MVPP2_TXQ_PENDING_MASK;
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_PENDING_REG, val);

	/* Calculate base address in prefetch buffer. We reserve 16 descriptors
	 * क्रम each existing TXQ.
	 * TCONTS क्रम PON port must be continuous from 0 to MVPP2_MAX_TCONT
	 * GBE ports assumed to be continuous from 0 to MVPP2_MAX_PORTS
	 */
	desc_per_txq = 16;
	desc = (port->id * MVPP2_MAX_TXQ * desc_per_txq) +
	       (txq->log_id * desc_per_txq);

	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_PREF_BUF_REG,
			   MVPP2_PREF_BUF_PTR(desc) | MVPP2_PREF_BUF_SIZE_16 |
			   MVPP2_PREF_BUF_THRESH(desc_per_txq / 2));
	put_cpu();

	/* WRR / EJP configuration - indirect access */
	tx_port_num = mvpp2_egress_port(port);
	mvpp2_ग_लिखो(port->priv, MVPP2_TXP_SCHED_PORT_INDEX_REG, tx_port_num);

	val = mvpp2_पढ़ो(port->priv, MVPP2_TXQ_SCHED_REFILL_REG(txq->log_id));
	val &= ~MVPP2_TXQ_REFILL_PERIOD_ALL_MASK;
	val |= MVPP2_TXQ_REFILL_PERIOD_MASK(1);
	val |= MVPP2_TXQ_REFILL_TOKENS_ALL_MASK;
	mvpp2_ग_लिखो(port->priv, MVPP2_TXQ_SCHED_REFILL_REG(txq->log_id), val);

	val = MVPP2_TXQ_TOKEN_SIZE_MAX;
	mvpp2_ग_लिखो(port->priv, MVPP2_TXQ_SCHED_TOKEN_SIZE_REG(txq->log_id),
		    val);

	क्रम (thपढ़ो = 0; thपढ़ो < port->priv->nthपढ़ोs; thपढ़ो++) अणु
		txq_pcpu = per_cpu_ptr(txq->pcpu, thपढ़ो);
		txq_pcpu->size = txq->size;
		txq_pcpu->buffs = kदो_स्मृति_array(txq_pcpu->size,
						माप(*txq_pcpu->buffs),
						GFP_KERNEL);
		अगर (!txq_pcpu->buffs)
			वापस -ENOMEM;

		txq_pcpu->count = 0;
		txq_pcpu->reserved_num = 0;
		txq_pcpu->txq_put_index = 0;
		txq_pcpu->txq_get_index = 0;
		txq_pcpu->tso_headers = शून्य;

		txq_pcpu->stop_threshold = txq->size - MVPP2_MAX_SKB_DESCS;
		txq_pcpu->wake_threshold = txq_pcpu->stop_threshold / 2;

		txq_pcpu->tso_headers =
			dma_alloc_coherent(port->dev->dev.parent,
					   txq_pcpu->size * TSO_HEADER_SIZE,
					   &txq_pcpu->tso_headers_dma,
					   GFP_KERNEL);
		अगर (!txq_pcpu->tso_headers)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/* Free allocated TXQ resources */
अटल व्योम mvpp2_txq_deinit(काष्ठा mvpp2_port *port,
			     काष्ठा mvpp2_tx_queue *txq)
अणु
	काष्ठा mvpp2_txq_pcpu *txq_pcpu;
	अचिन्हित पूर्णांक thपढ़ो;

	क्रम (thपढ़ो = 0; thपढ़ो < port->priv->nthपढ़ोs; thपढ़ो++) अणु
		txq_pcpu = per_cpu_ptr(txq->pcpu, thपढ़ो);
		kमुक्त(txq_pcpu->buffs);

		अगर (txq_pcpu->tso_headers)
			dma_मुक्त_coherent(port->dev->dev.parent,
					  txq_pcpu->size * TSO_HEADER_SIZE,
					  txq_pcpu->tso_headers,
					  txq_pcpu->tso_headers_dma);

		txq_pcpu->tso_headers = शून्य;
	पूर्ण

	अगर (txq->descs)
		dma_मुक्त_coherent(port->dev->dev.parent,
				  txq->size * MVPP2_DESC_ALIGNED_SIZE,
				  txq->descs, txq->descs_dma);

	txq->descs             = शून्य;
	txq->last_desc         = 0;
	txq->next_desc_to_proc = 0;
	txq->descs_dma         = 0;

	/* Set minimum bandwidth क्रम disabled TXQs */
	mvpp2_ग_लिखो(port->priv, MVPP2_TXQ_SCHED_TOKEN_CNTR_REG(txq->log_id), 0);

	/* Set Tx descriptors queue starting address and size */
	thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, get_cpu());
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_NUM_REG, txq->id);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_DESC_ADDR_REG, 0);
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_DESC_SIZE_REG, 0);
	put_cpu();
पूर्ण

/* Cleanup Tx ports */
अटल व्योम mvpp2_txq_clean(काष्ठा mvpp2_port *port, काष्ठा mvpp2_tx_queue *txq)
अणु
	काष्ठा mvpp2_txq_pcpu *txq_pcpu;
	पूर्णांक delay, pending;
	अचिन्हित पूर्णांक thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, get_cpu());
	u32 val;

	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_NUM_REG, txq->id);
	val = mvpp2_thपढ़ो_पढ़ो(port->priv, thपढ़ो, MVPP2_TXQ_PREF_BUF_REG);
	val |= MVPP2_TXQ_DRAIN_EN_MASK;
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_PREF_BUF_REG, val);

	/* The napi queue has been stopped so रुको क्रम all packets
	 * to be transmitted.
	 */
	delay = 0;
	करो अणु
		अगर (delay >= MVPP2_TX_PENDING_TIMEOUT_MSEC) अणु
			netdev_warn(port->dev,
				    "port %d: cleaning queue %d timed out\n",
				    port->id, txq->log_id);
			अवरोध;
		पूर्ण
		mdelay(1);
		delay++;

		pending = mvpp2_thपढ़ो_पढ़ो(port->priv, thपढ़ो,
					    MVPP2_TXQ_PENDING_REG);
		pending &= MVPP2_TXQ_PENDING_MASK;
	पूर्ण जबतक (pending);

	val &= ~MVPP2_TXQ_DRAIN_EN_MASK;
	mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो, MVPP2_TXQ_PREF_BUF_REG, val);
	put_cpu();

	क्रम (thपढ़ो = 0; thपढ़ो < port->priv->nthपढ़ोs; thपढ़ो++) अणु
		txq_pcpu = per_cpu_ptr(txq->pcpu, thपढ़ो);

		/* Release all packets */
		mvpp2_txq_bufs_मुक्त(port, txq, txq_pcpu, txq_pcpu->count);

		/* Reset queue */
		txq_pcpu->count = 0;
		txq_pcpu->txq_put_index = 0;
		txq_pcpu->txq_get_index = 0;
	पूर्ण
पूर्ण

/* Cleanup all Tx queues */
अटल व्योम mvpp2_cleanup_txqs(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2_tx_queue *txq;
	पूर्णांक queue;
	u32 val;

	val = mvpp2_पढ़ो(port->priv, MVPP2_TX_PORT_FLUSH_REG);

	/* Reset Tx ports and delete Tx queues */
	val |= MVPP2_TX_PORT_FLUSH_MASK(port->id);
	mvpp2_ग_लिखो(port->priv, MVPP2_TX_PORT_FLUSH_REG, val);

	क्रम (queue = 0; queue < port->ntxqs; queue++) अणु
		txq = port->txqs[queue];
		mvpp2_txq_clean(port, txq);
		mvpp2_txq_deinit(port, txq);
	पूर्ण

	on_each_cpu(mvpp2_txq_sent_counter_clear, port, 1);

	val &= ~MVPP2_TX_PORT_FLUSH_MASK(port->id);
	mvpp2_ग_लिखो(port->priv, MVPP2_TX_PORT_FLUSH_REG, val);
पूर्ण

/* Cleanup all Rx queues */
अटल व्योम mvpp2_cleanup_rxqs(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक queue;

	क्रम (queue = 0; queue < port->nrxqs; queue++)
		mvpp2_rxq_deinit(port, port->rxqs[queue]);

	अगर (port->tx_fc)
		mvpp2_rxq_disable_fc(port);
पूर्ण

/* Init all Rx queues क्रम port */
अटल पूर्णांक mvpp2_setup_rxqs(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक queue, err;

	क्रम (queue = 0; queue < port->nrxqs; queue++) अणु
		err = mvpp2_rxq_init(port, port->rxqs[queue]);
		अगर (err)
			जाओ err_cleanup;
	पूर्ण

	अगर (port->tx_fc)
		mvpp2_rxq_enable_fc(port);

	वापस 0;

err_cleanup:
	mvpp2_cleanup_rxqs(port);
	वापस err;
पूर्ण

/* Init all tx queues क्रम port */
अटल पूर्णांक mvpp2_setup_txqs(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2_tx_queue *txq;
	पूर्णांक queue, err;

	क्रम (queue = 0; queue < port->ntxqs; queue++) अणु
		txq = port->txqs[queue];
		err = mvpp2_txq_init(port, txq);
		अगर (err)
			जाओ err_cleanup;

		/* Assign this queue to a CPU */
		अगर (queue < num_possible_cpus())
			netअगर_set_xps_queue(port->dev, cpumask_of(queue), queue);
	पूर्ण

	अगर (port->has_tx_irqs) अणु
		mvpp2_tx_समय_coal_set(port);
		क्रम (queue = 0; queue < port->ntxqs; queue++) अणु
			txq = port->txqs[queue];
			mvpp2_tx_pkts_coal_set(port, txq);
		पूर्ण
	पूर्ण

	on_each_cpu(mvpp2_txq_sent_counter_clear, port, 1);
	वापस 0;

err_cleanup:
	mvpp2_cleanup_txqs(port);
	वापस err;
पूर्ण

/* The callback क्रम per-port पूर्णांकerrupt */
अटल irqवापस_t mvpp2_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mvpp2_queue_vector *qv = dev_id;

	mvpp2_qvec_पूर्णांकerrupt_disable(qv);

	napi_schedule(&qv->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mvpp2_isr_handle_ptp_queue(काष्ठा mvpp2_port *port, पूर्णांक nq)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	काष्ठा mvpp2_hwtstamp_queue *queue;
	काष्ठा sk_buff *skb;
	व्योम __iomem *ptp_q;
	अचिन्हित पूर्णांक id;
	u32 r0, r1, r2;

	ptp_q = port->priv->अगरace_base + MVPP22_PTP_BASE(port->gop_id);
	अगर (nq)
		ptp_q += MVPP22_PTP_TX_Q1_R0 - MVPP22_PTP_TX_Q0_R0;

	queue = &port->tx_hwtstamp_queue[nq];

	जबतक (1) अणु
		r0 = पढ़ोl_relaxed(ptp_q + MVPP22_PTP_TX_Q0_R0) & 0xffff;
		अगर (!r0)
			अवरोध;

		r1 = पढ़ोl_relaxed(ptp_q + MVPP22_PTP_TX_Q0_R1) & 0xffff;
		r2 = पढ़ोl_relaxed(ptp_q + MVPP22_PTP_TX_Q0_R2) & 0xffff;

		id = (r0 >> 1) & 31;

		skb = queue->skb[id];
		queue->skb[id] = शून्य;
		अगर (skb) अणु
			u32 ts = r2 << 19 | r1 << 3 | r0 >> 13;

			mvpp22_tai_tstamp(port->priv->tai, ts, &shhwtstamps);
			skb_tstamp_tx(skb, &shhwtstamps);
			dev_kमुक्त_skb_any(skb);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mvpp2_isr_handle_ptp(काष्ठा mvpp2_port *port)
अणु
	व्योम __iomem *ptp;
	u32 val;

	ptp = port->priv->अगरace_base + MVPP22_PTP_BASE(port->gop_id);
	val = पढ़ोl(ptp + MVPP22_PTP_INT_CAUSE);
	अगर (val & MVPP22_PTP_INT_CAUSE_QUEUE0)
		mvpp2_isr_handle_ptp_queue(port, 0);
	अगर (val & MVPP22_PTP_INT_CAUSE_QUEUE1)
		mvpp2_isr_handle_ptp_queue(port, 1);
पूर्ण

अटल व्योम mvpp2_isr_handle_link(काष्ठा mvpp2_port *port, bool link)
अणु
	काष्ठा net_device *dev = port->dev;

	अगर (port->phylink) अणु
		phylink_mac_change(port->phylink, link);
		वापस;
	पूर्ण

	अगर (!netअगर_running(dev))
		वापस;

	अगर (link) अणु
		mvpp2_पूर्णांकerrupts_enable(port);

		mvpp2_egress_enable(port);
		mvpp2_ingress_enable(port);
		netअगर_carrier_on(dev);
		netअगर_tx_wake_all_queues(dev);
	पूर्ण अन्यथा अणु
		netअगर_tx_stop_all_queues(dev);
		netअगर_carrier_off(dev);
		mvpp2_ingress_disable(port);
		mvpp2_egress_disable(port);

		mvpp2_पूर्णांकerrupts_disable(port);
	पूर्ण
पूर्ण

अटल व्योम mvpp2_isr_handle_xlg(काष्ठा mvpp2_port *port)
अणु
	bool link;
	u32 val;

	val = पढ़ोl(port->base + MVPP22_XLG_INT_STAT);
	अगर (val & MVPP22_XLG_INT_STAT_LINK) अणु
		val = पढ़ोl(port->base + MVPP22_XLG_STATUS);
		link = (val & MVPP22_XLG_STATUS_LINK_UP);
		mvpp2_isr_handle_link(port, link);
	पूर्ण
पूर्ण

अटल व्योम mvpp2_isr_handle_gmac_पूर्णांकernal(काष्ठा mvpp2_port *port)
अणु
	bool link;
	u32 val;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(port->phy_पूर्णांकerface) ||
	    phy_पूर्णांकerface_mode_is_8023z(port->phy_पूर्णांकerface) ||
	    port->phy_पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		val = पढ़ोl(port->base + MVPP22_GMAC_INT_STAT);
		अगर (val & MVPP22_GMAC_INT_STAT_LINK) अणु
			val = पढ़ोl(port->base + MVPP2_GMAC_STATUS0);
			link = (val & MVPP2_GMAC_STATUS0_LINK_UP);
			mvpp2_isr_handle_link(port, link);
		पूर्ण
	पूर्ण
पूर्ण

/* Per-port पूर्णांकerrupt क्रम link status changes */
अटल irqवापस_t mvpp2_port_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mvpp2_port *port = (काष्ठा mvpp2_port *)dev_id;
	u32 val;

	mvpp22_gop_mask_irq(port);

	अगर (mvpp2_port_supports_xlg(port) &&
	    mvpp2_is_xlg(port->phy_पूर्णांकerface)) अणु
		/* Check the बाह्यal status रेजिस्टर */
		val = पढ़ोl(port->base + MVPP22_XLG_EXT_INT_STAT);
		अगर (val & MVPP22_XLG_EXT_INT_STAT_XLG)
			mvpp2_isr_handle_xlg(port);
		अगर (val & MVPP22_XLG_EXT_INT_STAT_PTP)
			mvpp2_isr_handle_ptp(port);
	पूर्ण अन्यथा अणु
		/* If it's not the XLG, we must be using the GMAC.
		 * Check the summary status.
		 */
		val = पढ़ोl(port->base + MVPP22_GMAC_INT_SUM_STAT);
		अगर (val & MVPP22_GMAC_INT_SUM_STAT_INTERNAL)
			mvpp2_isr_handle_gmac_पूर्णांकernal(port);
		अगर (val & MVPP22_GMAC_INT_SUM_STAT_PTP)
			mvpp2_isr_handle_ptp(port);
	पूर्ण

	mvpp22_gop_unmask_irq(port);
	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत hrसमयr_restart mvpp2_hr_समयr_cb(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा net_device *dev;
	काष्ठा mvpp2_port *port;
	काष्ठा mvpp2_port_pcpu *port_pcpu;
	अचिन्हित पूर्णांक tx_toकरो, cause;

	port_pcpu = container_of(समयr, काष्ठा mvpp2_port_pcpu, tx_करोne_समयr);
	dev = port_pcpu->dev;

	अगर (!netअगर_running(dev))
		वापस HRTIMER_NORESTART;

	port_pcpu->समयr_scheduled = false;
	port = netdev_priv(dev);

	/* Process all the Tx queues */
	cause = (1 << port->ntxqs) - 1;
	tx_toकरो = mvpp2_tx_करोne(port, cause,
				mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id()));

	/* Set the समयr in हाल not all the packets were processed */
	अगर (tx_toकरो && !port_pcpu->समयr_scheduled) अणु
		port_pcpu->समयr_scheduled = true;
		hrसमयr_क्रमward_now(&port_pcpu->tx_करोne_समयr,
				    MVPP2_TXDONE_HRTIMER_PERIOD_NS);

		वापस HRTIMER_RESTART;
	पूर्ण
	वापस HRTIMER_NORESTART;
पूर्ण

/* Main RX/TX processing routines */

/* Display more error info */
अटल व्योम mvpp2_rx_error(काष्ठा mvpp2_port *port,
			   काष्ठा mvpp2_rx_desc *rx_desc)
अणु
	u32 status = mvpp2_rxdesc_status_get(port, rx_desc);
	माप_प्रकार sz = mvpp2_rxdesc_size_get(port, rx_desc);
	अक्षर *err_str = शून्य;

	चयन (status & MVPP2_RXD_ERR_CODE_MASK) अणु
	हाल MVPP2_RXD_ERR_CRC:
		err_str = "crc";
		अवरोध;
	हाल MVPP2_RXD_ERR_OVERRUN:
		err_str = "overrun";
		अवरोध;
	हाल MVPP2_RXD_ERR_RESOURCE:
		err_str = "resource";
		अवरोध;
	पूर्ण
	अगर (err_str && net_ratelimit())
		netdev_err(port->dev,
			   "bad rx status %08x (%s error), size=%zu\n",
			   status, err_str, sz);
पूर्ण

/* Handle RX checksum offload */
अटल व्योम mvpp2_rx_csum(काष्ठा mvpp2_port *port, u32 status,
			  काष्ठा sk_buff *skb)
अणु
	अगर (((status & MVPP2_RXD_L3_IP4) &&
	     !(status & MVPP2_RXD_IP4_HEADER_ERR)) ||
	    (status & MVPP2_RXD_L3_IP6))
		अगर (((status & MVPP2_RXD_L4_UDP) ||
		     (status & MVPP2_RXD_L4_TCP)) &&
		     (status & MVPP2_RXD_L4_CSUM_OK)) अणु
			skb->csum = 0;
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			वापस;
		पूर्ण

	skb->ip_summed = CHECKSUM_NONE;
पूर्ण

/* Allocate a new skb and add it to BM pool */
अटल पूर्णांक mvpp2_rx_refill(काष्ठा mvpp2_port *port,
			   काष्ठा mvpp2_bm_pool *bm_pool,
			   काष्ठा page_pool *page_pool, पूर्णांक pool)
अणु
	dma_addr_t dma_addr;
	phys_addr_t phys_addr;
	व्योम *buf;

	buf = mvpp2_buf_alloc(port, bm_pool, page_pool,
			      &dma_addr, &phys_addr, GFP_ATOMIC);
	अगर (!buf)
		वापस -ENOMEM;

	mvpp2_bm_pool_put(port, pool, dma_addr, phys_addr);

	वापस 0;
पूर्ण

/* Handle tx checksum */
अटल u32 mvpp2_skb_tx_csum(काष्ठा mvpp2_port *port, काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		पूर्णांक ip_hdr_len = 0;
		u8 l4_proto;
		__be16 l3_proto = vlan_get_protocol(skb);

		अगर (l3_proto == htons(ETH_P_IP)) अणु
			काष्ठा iphdr *ip4h = ip_hdr(skb);

			/* Calculate IPv4 checksum and L4 checksum */
			ip_hdr_len = ip4h->ihl;
			l4_proto = ip4h->protocol;
		पूर्ण अन्यथा अगर (l3_proto == htons(ETH_P_IPV6)) अणु
			काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);

			/* Read l4_protocol from one of IPv6 extra headers */
			अगर (skb_network_header_len(skb) > 0)
				ip_hdr_len = (skb_network_header_len(skb) >> 2);
			l4_proto = ip6h->nexthdr;
		पूर्ण अन्यथा अणु
			वापस MVPP2_TXD_L4_CSUM_NOT;
		पूर्ण

		वापस mvpp2_txq_desc_csum(skb_network_offset(skb),
					   l3_proto, ip_hdr_len, l4_proto);
	पूर्ण

	वापस MVPP2_TXD_L4_CSUM_NOT | MVPP2_TXD_IP_CSUM_DISABLE;
पूर्ण

अटल व्योम mvpp2_xdp_finish_tx(काष्ठा mvpp2_port *port, u16 txq_id, पूर्णांक nxmit, पूर्णांक nxmit_byte)
अणु
	अचिन्हित पूर्णांक thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id());
	काष्ठा mvpp2_tx_queue *aggr_txq;
	काष्ठा mvpp2_txq_pcpu *txq_pcpu;
	काष्ठा mvpp2_tx_queue *txq;
	काष्ठा netdev_queue *nq;

	txq = port->txqs[txq_id];
	txq_pcpu = per_cpu_ptr(txq->pcpu, thपढ़ो);
	nq = netdev_get_tx_queue(port->dev, txq_id);
	aggr_txq = &port->priv->aggr_txqs[thपढ़ो];

	txq_pcpu->reserved_num -= nxmit;
	txq_pcpu->count += nxmit;
	aggr_txq->count += nxmit;

	/* Enable transmit */
	wmb();
	mvpp2_aggr_txq_pend_desc_add(port, nxmit);

	अगर (txq_pcpu->count >= txq_pcpu->stop_threshold)
		netअगर_tx_stop_queue(nq);

	/* Finalize TX processing */
	अगर (!port->has_tx_irqs && txq_pcpu->count >= txq->करोne_pkts_coal)
		mvpp2_txq_करोne(port, txq, txq_pcpu);
पूर्ण

अटल पूर्णांक
mvpp2_xdp_submit_frame(काष्ठा mvpp2_port *port, u16 txq_id,
		       काष्ठा xdp_frame *xdpf, bool dma_map)
अणु
	अचिन्हित पूर्णांक thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id());
	u32 tx_cmd = MVPP2_TXD_L4_CSUM_NOT | MVPP2_TXD_IP_CSUM_DISABLE |
		     MVPP2_TXD_F_DESC | MVPP2_TXD_L_DESC;
	क्रमागत mvpp2_tx_buf_type buf_type;
	काष्ठा mvpp2_txq_pcpu *txq_pcpu;
	काष्ठा mvpp2_tx_queue *aggr_txq;
	काष्ठा mvpp2_tx_desc *tx_desc;
	काष्ठा mvpp2_tx_queue *txq;
	पूर्णांक ret = MVPP2_XDP_TX;
	dma_addr_t dma_addr;

	txq = port->txqs[txq_id];
	txq_pcpu = per_cpu_ptr(txq->pcpu, thपढ़ो);
	aggr_txq = &port->priv->aggr_txqs[thपढ़ो];

	/* Check number of available descriptors */
	अगर (mvpp2_aggr_desc_num_check(port, aggr_txq, 1) ||
	    mvpp2_txq_reserved_desc_num_proc(port, txq, txq_pcpu, 1)) अणु
		ret = MVPP2_XDP_DROPPED;
		जाओ out;
	पूर्ण

	/* Get a descriptor क्रम the first part of the packet */
	tx_desc = mvpp2_txq_next_desc_get(aggr_txq);
	mvpp2_txdesc_txq_set(port, tx_desc, txq->id);
	mvpp2_txdesc_size_set(port, tx_desc, xdpf->len);

	अगर (dma_map) अणु
		/* XDP_REसूचीECT or AF_XDP */
		dma_addr = dma_map_single(port->dev->dev.parent, xdpf->data,
					  xdpf->len, DMA_TO_DEVICE);

		अगर (unlikely(dma_mapping_error(port->dev->dev.parent, dma_addr))) अणु
			mvpp2_txq_desc_put(txq);
			ret = MVPP2_XDP_DROPPED;
			जाओ out;
		पूर्ण

		buf_type = MVPP2_TYPE_XDP_NDO;
	पूर्ण अन्यथा अणु
		/* XDP_TX */
		काष्ठा page *page = virt_to_page(xdpf->data);

		dma_addr = page_pool_get_dma_addr(page) +
			   माप(*xdpf) + xdpf->headroom;
		dma_sync_single_क्रम_device(port->dev->dev.parent, dma_addr,
					   xdpf->len, DMA_BIसूचीECTIONAL);

		buf_type = MVPP2_TYPE_XDP_TX;
	पूर्ण

	mvpp2_txdesc_dma_addr_set(port, tx_desc, dma_addr);

	mvpp2_txdesc_cmd_set(port, tx_desc, tx_cmd);
	mvpp2_txq_inc_put(port, txq_pcpu, xdpf, tx_desc, buf_type);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक
mvpp2_xdp_xmit_back(काष्ठा mvpp2_port *port, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा mvpp2_pcpu_stats *stats = this_cpu_ptr(port->stats);
	काष्ठा xdp_frame *xdpf;
	u16 txq_id;
	पूर्णांक ret;

	xdpf = xdp_convert_buff_to_frame(xdp);
	अगर (unlikely(!xdpf))
		वापस MVPP2_XDP_DROPPED;

	/* The first of the TX queues are used क्रम XPS,
	 * the second half क्रम XDP_TX
	 */
	txq_id = mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id()) + (port->ntxqs / 2);

	ret = mvpp2_xdp_submit_frame(port, txq_id, xdpf, false);
	अगर (ret == MVPP2_XDP_TX) अणु
		u64_stats_update_begin(&stats->syncp);
		stats->tx_bytes += xdpf->len;
		stats->tx_packets++;
		stats->xdp_tx++;
		u64_stats_update_end(&stats->syncp);

		mvpp2_xdp_finish_tx(port, txq_id, 1, xdpf->len);
	पूर्ण अन्यथा अणु
		u64_stats_update_begin(&stats->syncp);
		stats->xdp_tx_err++;
		u64_stats_update_end(&stats->syncp);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
mvpp2_xdp_xmit(काष्ठा net_device *dev, पूर्णांक num_frame,
	       काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक i, nxmit_byte = 0, nxmit = 0;
	काष्ठा mvpp2_pcpu_stats *stats;
	u16 txq_id;
	u32 ret;

	अगर (unlikely(test_bit(0, &port->state)))
		वापस -ENETDOWN;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	/* The first of the TX queues are used क्रम XPS,
	 * the second half क्रम XDP_TX
	 */
	txq_id = mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id()) + (port->ntxqs / 2);

	क्रम (i = 0; i < num_frame; i++) अणु
		ret = mvpp2_xdp_submit_frame(port, txq_id, frames[i], true);
		अगर (ret != MVPP2_XDP_TX)
			अवरोध;

		nxmit_byte += frames[i]->len;
		nxmit++;
	पूर्ण

	अगर (likely(nxmit > 0))
		mvpp2_xdp_finish_tx(port, txq_id, nxmit, nxmit_byte);

	stats = this_cpu_ptr(port->stats);
	u64_stats_update_begin(&stats->syncp);
	stats->tx_bytes += nxmit_byte;
	stats->tx_packets += nxmit;
	stats->xdp_xmit += nxmit;
	stats->xdp_xmit_err += num_frame - nxmit;
	u64_stats_update_end(&stats->syncp);

	वापस nxmit;
पूर्ण

अटल पूर्णांक
mvpp2_run_xdp(काष्ठा mvpp2_port *port, काष्ठा mvpp2_rx_queue *rxq,
	      काष्ठा bpf_prog *prog, काष्ठा xdp_buff *xdp,
	      काष्ठा page_pool *pp, काष्ठा mvpp2_pcpu_stats *stats)
अणु
	अचिन्हित पूर्णांक len, sync, err;
	काष्ठा page *page;
	u32 ret, act;

	len = xdp->data_end - xdp->data_hard_start - MVPP2_SKB_HEADROOM;
	act = bpf_prog_run_xdp(prog, xdp);

	/* Due xdp_adjust_tail: DMA sync क्रम_device cover max len CPU touch */
	sync = xdp->data_end - xdp->data_hard_start - MVPP2_SKB_HEADROOM;
	sync = max(sync, len);

	चयन (act) अणु
	हाल XDP_PASS:
		stats->xdp_pass++;
		ret = MVPP2_XDP_PASS;
		अवरोध;
	हाल XDP_REसूचीECT:
		err = xdp_करो_redirect(port->dev, xdp, prog);
		अगर (unlikely(err)) अणु
			ret = MVPP2_XDP_DROPPED;
			page = virt_to_head_page(xdp->data);
			page_pool_put_page(pp, page, sync, true);
		पूर्ण अन्यथा अणु
			ret = MVPP2_XDP_REसूची;
			stats->xdp_redirect++;
		पूर्ण
		अवरोध;
	हाल XDP_TX:
		ret = mvpp2_xdp_xmit_back(port, xdp);
		अगर (ret != MVPP2_XDP_TX) अणु
			page = virt_to_head_page(xdp->data);
			page_pool_put_page(pp, page, sync, true);
		पूर्ण
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(port->dev, prog, act);
		fallthrough;
	हाल XDP_DROP:
		page = virt_to_head_page(xdp->data);
		page_pool_put_page(pp, page, sync, true);
		ret = MVPP2_XDP_DROPPED;
		stats->xdp_drop++;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mvpp2_buff_hdr_pool_put(काष्ठा mvpp2_port *port, काष्ठा mvpp2_rx_desc *rx_desc,
				    पूर्णांक pool, u32 rx_status)
अणु
	phys_addr_t phys_addr, phys_addr_next;
	dma_addr_t dma_addr, dma_addr_next;
	काष्ठा mvpp2_buff_hdr *buff_hdr;

	phys_addr = mvpp2_rxdesc_dma_addr_get(port, rx_desc);
	dma_addr = mvpp2_rxdesc_cookie_get(port, rx_desc);

	करो अणु
		buff_hdr = (काष्ठा mvpp2_buff_hdr *)phys_to_virt(phys_addr);

		phys_addr_next = le32_to_cpu(buff_hdr->next_phys_addr);
		dma_addr_next = le32_to_cpu(buff_hdr->next_dma_addr);

		अगर (port->priv->hw_version >= MVPP22) अणु
			phys_addr_next |= ((u64)buff_hdr->next_phys_addr_high << 32);
			dma_addr_next |= ((u64)buff_hdr->next_dma_addr_high << 32);
		पूर्ण

		mvpp2_bm_pool_put(port, pool, dma_addr, phys_addr);

		phys_addr = phys_addr_next;
		dma_addr = dma_addr_next;

	पूर्ण जबतक (!MVPP2_B_HDR_INFO_IS_LAST(le16_to_cpu(buff_hdr->info)));
पूर्ण

/* Main rx processing */
अटल पूर्णांक mvpp2_rx(काष्ठा mvpp2_port *port, काष्ठा napi_काष्ठा *napi,
		    पूर्णांक rx_toकरो, काष्ठा mvpp2_rx_queue *rxq)
अणु
	काष्ठा net_device *dev = port->dev;
	काष्ठा mvpp2_pcpu_stats ps = अणुपूर्ण;
	क्रमागत dma_data_direction dma_dir;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा xdp_buff xdp;
	पूर्णांक rx_received;
	पूर्णांक rx_करोne = 0;
	u32 xdp_ret = 0;

	rcu_पढ़ो_lock();

	xdp_prog = READ_ONCE(port->xdp_prog);

	/* Get number of received packets and clamp the to-करो */
	rx_received = mvpp2_rxq_received(port, rxq->id);
	अगर (rx_toकरो > rx_received)
		rx_toकरो = rx_received;

	जबतक (rx_करोne < rx_toकरो) अणु
		काष्ठा mvpp2_rx_desc *rx_desc = mvpp2_rxq_next_desc_get(rxq);
		काष्ठा mvpp2_bm_pool *bm_pool;
		काष्ठा page_pool *pp = शून्य;
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक frag_size;
		dma_addr_t dma_addr;
		phys_addr_t phys_addr;
		u32 rx_status, बारtamp;
		पूर्णांक pool, rx_bytes, err, ret;
		व्योम *data;

		rx_करोne++;
		rx_status = mvpp2_rxdesc_status_get(port, rx_desc);
		rx_bytes = mvpp2_rxdesc_size_get(port, rx_desc);
		rx_bytes -= MVPP2_MH_SIZE;
		dma_addr = mvpp2_rxdesc_dma_addr_get(port, rx_desc);
		phys_addr = mvpp2_rxdesc_cookie_get(port, rx_desc);
		data = (व्योम *)phys_to_virt(phys_addr);

		pool = (rx_status & MVPP2_RXD_BM_POOL_ID_MASK) >>
			MVPP2_RXD_BM_POOL_ID_OFFS;
		bm_pool = &port->priv->bm_pools[pool];

		अगर (port->priv->percpu_pools) अणु
			pp = port->priv->page_pool[pool];
			dma_dir = page_pool_get_dma_dir(pp);
		पूर्ण अन्यथा अणु
			dma_dir = DMA_FROM_DEVICE;
		पूर्ण

		dma_sync_single_क्रम_cpu(dev->dev.parent, dma_addr,
					rx_bytes + MVPP2_MH_SIZE,
					dma_dir);

		/* Buffer header not supported */
		अगर (rx_status & MVPP2_RXD_BUF_HDR)
			जाओ err_drop_frame;

		/* In हाल of an error, release the requested buffer poपूर्णांकer
		 * to the Buffer Manager. This request process is controlled
		 * by the hardware, and the inक्रमmation about the buffer is
		 * comprised by the RX descriptor.
		 */
		अगर (rx_status & MVPP2_RXD_ERR_SUMMARY)
			जाओ err_drop_frame;

		/* Prefetch header */
		prefetch(data);

		अगर (bm_pool->frag_size > PAGE_SIZE)
			frag_size = 0;
		अन्यथा
			frag_size = bm_pool->frag_size;

		अगर (xdp_prog) अणु
			काष्ठा xdp_rxq_info *xdp_rxq;

			अगर (bm_pool->pkt_size == MVPP2_BM_SHORT_PKT_SIZE)
				xdp_rxq = &rxq->xdp_rxq_लघु;
			अन्यथा
				xdp_rxq = &rxq->xdp_rxq_दीर्घ;

			xdp_init_buff(&xdp, PAGE_SIZE, xdp_rxq);
			xdp_prepare_buff(&xdp, data,
					 MVPP2_MH_SIZE + MVPP2_SKB_HEADROOM,
					 rx_bytes, false);

			ret = mvpp2_run_xdp(port, rxq, xdp_prog, &xdp, pp, &ps);

			अगर (ret) अणु
				xdp_ret |= ret;
				err = mvpp2_rx_refill(port, bm_pool, pp, pool);
				अगर (err) अणु
					netdev_err(port->dev, "failed to refill BM pools\n");
					जाओ err_drop_frame;
				पूर्ण

				ps.rx_packets++;
				ps.rx_bytes += rx_bytes;
				जारी;
			पूर्ण
		पूर्ण

		skb = build_skb(data, frag_size);
		अगर (!skb) अणु
			netdev_warn(port->dev, "skb build failed\n");
			जाओ err_drop_frame;
		पूर्ण

		/* If we have RX hardware बारtamping enabled, grab the
		 * बारtamp from the queue and convert.
		 */
		अगर (mvpp22_rx_hwtstamping(port)) अणु
			बारtamp = le32_to_cpu(rx_desc->pp22.बारtamp);
			mvpp22_tai_tstamp(port->priv->tai, बारtamp,
					 skb_hwtstamps(skb));
		पूर्ण

		err = mvpp2_rx_refill(port, bm_pool, pp, pool);
		अगर (err) अणु
			netdev_err(port->dev, "failed to refill BM pools\n");
			dev_kमुक्त_skb_any(skb);
			जाओ err_drop_frame;
		पूर्ण

		अगर (pp)
			page_pool_release_page(pp, virt_to_page(data));
		अन्यथा
			dma_unmap_single_attrs(dev->dev.parent, dma_addr,
					       bm_pool->buf_size, DMA_FROM_DEVICE,
					       DMA_ATTR_SKIP_CPU_SYNC);

		ps.rx_packets++;
		ps.rx_bytes += rx_bytes;

		skb_reserve(skb, MVPP2_MH_SIZE + MVPP2_SKB_HEADROOM);
		skb_put(skb, rx_bytes);
		skb->protocol = eth_type_trans(skb, dev);
		mvpp2_rx_csum(port, rx_status, skb);

		napi_gro_receive(napi, skb);
		जारी;

err_drop_frame:
		dev->stats.rx_errors++;
		mvpp2_rx_error(port, rx_desc);
		/* Return the buffer to the pool */
		अगर (rx_status & MVPP2_RXD_BUF_HDR)
			mvpp2_buff_hdr_pool_put(port, rx_desc, pool, rx_status);
		अन्यथा
			mvpp2_bm_pool_put(port, pool, dma_addr, phys_addr);
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (xdp_ret & MVPP2_XDP_REसूची)
		xdp_करो_flush_map();

	अगर (ps.rx_packets) अणु
		काष्ठा mvpp2_pcpu_stats *stats = this_cpu_ptr(port->stats);

		u64_stats_update_begin(&stats->syncp);
		stats->rx_packets += ps.rx_packets;
		stats->rx_bytes   += ps.rx_bytes;
		/* xdp */
		stats->xdp_redirect += ps.xdp_redirect;
		stats->xdp_pass += ps.xdp_pass;
		stats->xdp_drop += ps.xdp_drop;
		u64_stats_update_end(&stats->syncp);
	पूर्ण

	/* Update Rx queue management counters */
	wmb();
	mvpp2_rxq_status_update(port, rxq->id, rx_करोne, rx_करोne);

	वापस rx_toकरो;
पूर्ण

अटल अंतरभूत व्योम
tx_desc_unmap_put(काष्ठा mvpp2_port *port, काष्ठा mvpp2_tx_queue *txq,
		  काष्ठा mvpp2_tx_desc *desc)
अणु
	अचिन्हित पूर्णांक thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id());
	काष्ठा mvpp2_txq_pcpu *txq_pcpu = per_cpu_ptr(txq->pcpu, thपढ़ो);

	dma_addr_t buf_dma_addr =
		mvpp2_txdesc_dma_addr_get(port, desc);
	माप_प्रकार buf_sz =
		mvpp2_txdesc_size_get(port, desc);
	अगर (!IS_TSO_HEADER(txq_pcpu, buf_dma_addr))
		dma_unmap_single(port->dev->dev.parent, buf_dma_addr,
				 buf_sz, DMA_TO_DEVICE);
	mvpp2_txq_desc_put(txq);
पूर्ण

अटल व्योम mvpp2_txdesc_clear_ptp(काष्ठा mvpp2_port *port,
				   काष्ठा mvpp2_tx_desc *desc)
अणु
	/* We only need to clear the low bits */
	अगर (port->priv->hw_version >= MVPP22)
		desc->pp22.ptp_descriptor &=
			cpu_to_le32(~MVPP22_PTP_DESC_MASK_LOW);
पूर्ण

अटल bool mvpp2_tx_hw_tstamp(काष्ठा mvpp2_port *port,
			       काष्ठा mvpp2_tx_desc *tx_desc,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा mvpp2_hwtstamp_queue *queue;
	अचिन्हित पूर्णांक mtype, type, i;
	काष्ठा ptp_header *hdr;
	u64 ptpdesc;

	अगर (port->priv->hw_version == MVPP21 ||
	    port->tx_hwtstamp_type == HWTSTAMP_TX_OFF)
		वापस false;

	type = ptp_classअगरy_raw(skb);
	अगर (!type)
		वापस false;

	hdr = ptp_parse_header(skb, type);
	अगर (!hdr)
		वापस false;

	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

	ptpdesc = MVPP22_PTP_MACTIMESTAMPINGEN |
		  MVPP22_PTP_ACTION_CAPTURE;
	queue = &port->tx_hwtstamp_queue[0];

	चयन (type & PTP_CLASS_VMASK) अणु
	हाल PTP_CLASS_V1:
		ptpdesc |= MVPP22_PTP_PACKETFORMAT(MVPP22_PTP_PKT_FMT_PTPV1);
		अवरोध;

	हाल PTP_CLASS_V2:
		ptpdesc |= MVPP22_PTP_PACKETFORMAT(MVPP22_PTP_PKT_FMT_PTPV2);
		mtype = hdr->tsmt & 15;
		/* Direct PTP Sync messages to queue 1 */
		अगर (mtype == 0) अणु
			ptpdesc |= MVPP22_PTP_TIMESTAMPQUEUESELECT;
			queue = &port->tx_hwtstamp_queue[1];
		पूर्ण
		अवरोध;
	पूर्ण

	/* Take a reference on the skb and insert पूर्णांकo our queue */
	i = queue->next;
	queue->next = (i + 1) & 31;
	अगर (queue->skb[i])
		dev_kमुक्त_skb_any(queue->skb[i]);
	queue->skb[i] = skb_get(skb);

	ptpdesc |= MVPP22_PTP_TIMESTAMPENTRYID(i);

	/*
	 * 3:0		- PTPAction
	 * 6:4		- PTPPacketFormat
	 * 7		- PTP_CF_WraparoundCheckEn
	 * 9:8		- IngressTimestampSeconds[1:0]
	 * 10		- Reserved
	 * 11		- MACTimestampingEn
	 * 17:12	- PTP_TimestampQueueEntryID[5:0]
	 * 18		- PTPTimestampQueueSelect
	 * 19		- UDPChecksumUpdateEn
	 * 27:20	- TimestampOffset
	 *			PTP, NTPTransmit, OWAMP/TWAMP - L3 to PTP header
	 *			NTPTs, Y.1731 - L3 to बारtamp entry
	 * 35:28	- UDP Checksum Offset
	 *
	 * stored in tx descriptor bits 75:64 (11:0) and 191:168 (35:12)
	 */
	tx_desc->pp22.ptp_descriptor &=
		cpu_to_le32(~MVPP22_PTP_DESC_MASK_LOW);
	tx_desc->pp22.ptp_descriptor |=
		cpu_to_le32(ptpdesc & MVPP22_PTP_DESC_MASK_LOW);
	tx_desc->pp22.buf_dma_addr_ptp &= cpu_to_le64(~0xffffff0000000000ULL);
	tx_desc->pp22.buf_dma_addr_ptp |= cpu_to_le64((ptpdesc >> 12) << 40);

	वापस true;
पूर्ण

/* Handle tx fragmentation processing */
अटल पूर्णांक mvpp2_tx_frag_process(काष्ठा mvpp2_port *port, काष्ठा sk_buff *skb,
				 काष्ठा mvpp2_tx_queue *aggr_txq,
				 काष्ठा mvpp2_tx_queue *txq)
अणु
	अचिन्हित पूर्णांक thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id());
	काष्ठा mvpp2_txq_pcpu *txq_pcpu = per_cpu_ptr(txq->pcpu, thपढ़ो);
	काष्ठा mvpp2_tx_desc *tx_desc;
	पूर्णांक i;
	dma_addr_t buf_dma_addr;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		व्योम *addr = skb_frag_address(frag);

		tx_desc = mvpp2_txq_next_desc_get(aggr_txq);
		mvpp2_txdesc_clear_ptp(port, tx_desc);
		mvpp2_txdesc_txq_set(port, tx_desc, txq->id);
		mvpp2_txdesc_size_set(port, tx_desc, skb_frag_size(frag));

		buf_dma_addr = dma_map_single(port->dev->dev.parent, addr,
					      skb_frag_size(frag),
					      DMA_TO_DEVICE);
		अगर (dma_mapping_error(port->dev->dev.parent, buf_dma_addr)) अणु
			mvpp2_txq_desc_put(txq);
			जाओ cleanup;
		पूर्ण

		mvpp2_txdesc_dma_addr_set(port, tx_desc, buf_dma_addr);

		अगर (i == (skb_shinfo(skb)->nr_frags - 1)) अणु
			/* Last descriptor */
			mvpp2_txdesc_cmd_set(port, tx_desc,
					     MVPP2_TXD_L_DESC);
			mvpp2_txq_inc_put(port, txq_pcpu, skb, tx_desc, MVPP2_TYPE_SKB);
		पूर्ण अन्यथा अणु
			/* Descriptor in the middle: Not First, Not Last */
			mvpp2_txdesc_cmd_set(port, tx_desc, 0);
			mvpp2_txq_inc_put(port, txq_pcpu, शून्य, tx_desc, MVPP2_TYPE_SKB);
		पूर्ण
	पूर्ण

	वापस 0;
cleanup:
	/* Release all descriptors that were used to map fragments of
	 * this packet, as well as the corresponding DMA mappings
	 */
	क्रम (i = i - 1; i >= 0; i--) अणु
		tx_desc = txq->descs + i;
		tx_desc_unmap_put(port, txq, tx_desc);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम mvpp2_tso_put_hdr(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev,
				     काष्ठा mvpp2_tx_queue *txq,
				     काष्ठा mvpp2_tx_queue *aggr_txq,
				     काष्ठा mvpp2_txq_pcpu *txq_pcpu,
				     पूर्णांक hdr_sz)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	काष्ठा mvpp2_tx_desc *tx_desc = mvpp2_txq_next_desc_get(aggr_txq);
	dma_addr_t addr;

	mvpp2_txdesc_clear_ptp(port, tx_desc);
	mvpp2_txdesc_txq_set(port, tx_desc, txq->id);
	mvpp2_txdesc_size_set(port, tx_desc, hdr_sz);

	addr = txq_pcpu->tso_headers_dma +
	       txq_pcpu->txq_put_index * TSO_HEADER_SIZE;
	mvpp2_txdesc_dma_addr_set(port, tx_desc, addr);

	mvpp2_txdesc_cmd_set(port, tx_desc, mvpp2_skb_tx_csum(port, skb) |
					    MVPP2_TXD_F_DESC |
					    MVPP2_TXD_PADDING_DISABLE);
	mvpp2_txq_inc_put(port, txq_pcpu, शून्य, tx_desc, MVPP2_TYPE_SKB);
पूर्ण

अटल अंतरभूत पूर्णांक mvpp2_tso_put_data(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev, काष्ठा tso_t *tso,
				     काष्ठा mvpp2_tx_queue *txq,
				     काष्ठा mvpp2_tx_queue *aggr_txq,
				     काष्ठा mvpp2_txq_pcpu *txq_pcpu,
				     पूर्णांक sz, bool left, bool last)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	काष्ठा mvpp2_tx_desc *tx_desc = mvpp2_txq_next_desc_get(aggr_txq);
	dma_addr_t buf_dma_addr;

	mvpp2_txdesc_clear_ptp(port, tx_desc);
	mvpp2_txdesc_txq_set(port, tx_desc, txq->id);
	mvpp2_txdesc_size_set(port, tx_desc, sz);

	buf_dma_addr = dma_map_single(dev->dev.parent, tso->data, sz,
				      DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev->dev.parent, buf_dma_addr))) अणु
		mvpp2_txq_desc_put(txq);
		वापस -ENOMEM;
	पूर्ण

	mvpp2_txdesc_dma_addr_set(port, tx_desc, buf_dma_addr);

	अगर (!left) अणु
		mvpp2_txdesc_cmd_set(port, tx_desc, MVPP2_TXD_L_DESC);
		अगर (last) अणु
			mvpp2_txq_inc_put(port, txq_pcpu, skb, tx_desc, MVPP2_TYPE_SKB);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		mvpp2_txdesc_cmd_set(port, tx_desc, 0);
	पूर्ण

	mvpp2_txq_inc_put(port, txq_pcpu, शून्य, tx_desc, MVPP2_TYPE_SKB);
	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_tx_tso(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			काष्ठा mvpp2_tx_queue *txq,
			काष्ठा mvpp2_tx_queue *aggr_txq,
			काष्ठा mvpp2_txq_pcpu *txq_pcpu)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक hdr_sz, i, len, descs = 0;
	काष्ठा tso_t tso;

	/* Check number of available descriptors */
	अगर (mvpp2_aggr_desc_num_check(port, aggr_txq, tso_count_descs(skb)) ||
	    mvpp2_txq_reserved_desc_num_proc(port, txq, txq_pcpu,
					     tso_count_descs(skb)))
		वापस 0;

	hdr_sz = tso_start(skb, &tso);

	len = skb->len - hdr_sz;
	जबतक (len > 0) अणु
		पूर्णांक left = min_t(पूर्णांक, skb_shinfo(skb)->gso_size, len);
		अक्षर *hdr = txq_pcpu->tso_headers +
			    txq_pcpu->txq_put_index * TSO_HEADER_SIZE;

		len -= left;
		descs++;

		tso_build_hdr(skb, hdr, &tso, left, len == 0);
		mvpp2_tso_put_hdr(skb, dev, txq, aggr_txq, txq_pcpu, hdr_sz);

		जबतक (left > 0) अणु
			पूर्णांक sz = min_t(पूर्णांक, tso.size, left);
			left -= sz;
			descs++;

			अगर (mvpp2_tso_put_data(skb, dev, &tso, txq, aggr_txq,
					       txq_pcpu, sz, left, len == 0))
				जाओ release;
			tso_build_data(skb, &tso, sz);
		पूर्ण
	पूर्ण

	वापस descs;

release:
	क्रम (i = descs - 1; i >= 0; i--) अणु
		काष्ठा mvpp2_tx_desc *tx_desc = txq->descs + i;
		tx_desc_unmap_put(port, txq, tx_desc);
	पूर्ण
	वापस 0;
पूर्ण

/* Main tx processing */
अटल netdev_tx_t mvpp2_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	काष्ठा mvpp2_tx_queue *txq, *aggr_txq;
	काष्ठा mvpp2_txq_pcpu *txq_pcpu;
	काष्ठा mvpp2_tx_desc *tx_desc;
	dma_addr_t buf_dma_addr;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक thपढ़ो;
	पूर्णांक frags = 0;
	u16 txq_id;
	u32 tx_cmd;

	thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id());

	txq_id = skb_get_queue_mapping(skb);
	txq = port->txqs[txq_id];
	txq_pcpu = per_cpu_ptr(txq->pcpu, thपढ़ो);
	aggr_txq = &port->priv->aggr_txqs[thपढ़ो];

	अगर (test_bit(thपढ़ो, &port->priv->lock_map))
		spin_lock_irqsave(&port->tx_lock[thपढ़ो], flags);

	अगर (skb_is_gso(skb)) अणु
		frags = mvpp2_tx_tso(skb, dev, txq, aggr_txq, txq_pcpu);
		जाओ out;
	पूर्ण
	frags = skb_shinfo(skb)->nr_frags + 1;

	/* Check number of available descriptors */
	अगर (mvpp2_aggr_desc_num_check(port, aggr_txq, frags) ||
	    mvpp2_txq_reserved_desc_num_proc(port, txq, txq_pcpu, frags)) अणु
		frags = 0;
		जाओ out;
	पूर्ण

	/* Get a descriptor क्रम the first part of the packet */
	tx_desc = mvpp2_txq_next_desc_get(aggr_txq);
	अगर (!(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) ||
	    !mvpp2_tx_hw_tstamp(port, tx_desc, skb))
		mvpp2_txdesc_clear_ptp(port, tx_desc);
	mvpp2_txdesc_txq_set(port, tx_desc, txq->id);
	mvpp2_txdesc_size_set(port, tx_desc, skb_headlen(skb));

	buf_dma_addr = dma_map_single(dev->dev.parent, skb->data,
				      skb_headlen(skb), DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev->dev.parent, buf_dma_addr))) अणु
		mvpp2_txq_desc_put(txq);
		frags = 0;
		जाओ out;
	पूर्ण

	mvpp2_txdesc_dma_addr_set(port, tx_desc, buf_dma_addr);

	tx_cmd = mvpp2_skb_tx_csum(port, skb);

	अगर (frags == 1) अणु
		/* First and Last descriptor */
		tx_cmd |= MVPP2_TXD_F_DESC | MVPP2_TXD_L_DESC;
		mvpp2_txdesc_cmd_set(port, tx_desc, tx_cmd);
		mvpp2_txq_inc_put(port, txq_pcpu, skb, tx_desc, MVPP2_TYPE_SKB);
	पूर्ण अन्यथा अणु
		/* First but not Last */
		tx_cmd |= MVPP2_TXD_F_DESC | MVPP2_TXD_PADDING_DISABLE;
		mvpp2_txdesc_cmd_set(port, tx_desc, tx_cmd);
		mvpp2_txq_inc_put(port, txq_pcpu, शून्य, tx_desc, MVPP2_TYPE_SKB);

		/* Continue with other skb fragments */
		अगर (mvpp2_tx_frag_process(port, skb, aggr_txq, txq)) अणु
			tx_desc_unmap_put(port, txq, tx_desc);
			frags = 0;
		पूर्ण
	पूर्ण

out:
	अगर (frags > 0) अणु
		काष्ठा mvpp2_pcpu_stats *stats = per_cpu_ptr(port->stats, thपढ़ो);
		काष्ठा netdev_queue *nq = netdev_get_tx_queue(dev, txq_id);

		txq_pcpu->reserved_num -= frags;
		txq_pcpu->count += frags;
		aggr_txq->count += frags;

		/* Enable transmit */
		wmb();
		mvpp2_aggr_txq_pend_desc_add(port, frags);

		अगर (txq_pcpu->count >= txq_pcpu->stop_threshold)
			netअगर_tx_stop_queue(nq);

		u64_stats_update_begin(&stats->syncp);
		stats->tx_packets++;
		stats->tx_bytes += skb->len;
		u64_stats_update_end(&stats->syncp);
	पूर्ण अन्यथा अणु
		dev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	/* Finalize TX processing */
	अगर (!port->has_tx_irqs && txq_pcpu->count >= txq->करोne_pkts_coal)
		mvpp2_txq_करोne(port, txq, txq_pcpu);

	/* Set the समयr in हाल not all frags were processed */
	अगर (!port->has_tx_irqs && txq_pcpu->count <= frags &&
	    txq_pcpu->count > 0) अणु
		काष्ठा mvpp2_port_pcpu *port_pcpu = per_cpu_ptr(port->pcpu, thपढ़ो);

		अगर (!port_pcpu->समयr_scheduled) अणु
			port_pcpu->समयr_scheduled = true;
			hrसमयr_start(&port_pcpu->tx_करोne_समयr,
				      MVPP2_TXDONE_HRTIMER_PERIOD_NS,
				      HRTIMER_MODE_REL_PINNED_SOFT);
		पूर्ण
	पूर्ण

	अगर (test_bit(thपढ़ो, &port->priv->lock_map))
		spin_unlock_irqrestore(&port->tx_lock[thपढ़ो], flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल अंतरभूत व्योम mvpp2_cause_error(काष्ठा net_device *dev, पूर्णांक cause)
अणु
	अगर (cause & MVPP2_CAUSE_FCS_ERR_MASK)
		netdev_err(dev, "FCS error\n");
	अगर (cause & MVPP2_CAUSE_RX_FIFO_OVERRUN_MASK)
		netdev_err(dev, "rx fifo overrun error\n");
	अगर (cause & MVPP2_CAUSE_TX_FIFO_UNDERRUN_MASK)
		netdev_err(dev, "tx fifo underrun error\n");
पूर्ण

अटल पूर्णांक mvpp2_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	u32 cause_rx_tx, cause_rx, cause_tx, cause_misc;
	पूर्णांक rx_करोne = 0;
	काष्ठा mvpp2_port *port = netdev_priv(napi->dev);
	काष्ठा mvpp2_queue_vector *qv;
	अचिन्हित पूर्णांक thपढ़ो = mvpp2_cpu_to_thपढ़ो(port->priv, smp_processor_id());

	qv = container_of(napi, काष्ठा mvpp2_queue_vector, napi);

	/* Rx/Tx cause रेजिस्टर
	 *
	 * Bits 0-15: each bit indicates received packets on the Rx queue
	 * (bit 0 is क्रम Rx queue 0).
	 *
	 * Bits 16-23: each bit indicates transmitted packets on the Tx queue
	 * (bit 16 is क्रम Tx queue 0).
	 *
	 * Each CPU has its own Rx/Tx cause रेजिस्टर
	 */
	cause_rx_tx = mvpp2_thपढ़ो_पढ़ो_relaxed(port->priv, qv->sw_thपढ़ो_id,
						MVPP2_ISR_RX_TX_CAUSE_REG(port->id));

	cause_misc = cause_rx_tx & MVPP2_CAUSE_MISC_SUM_MASK;
	अगर (cause_misc) अणु
		mvpp2_cause_error(port->dev, cause_misc);

		/* Clear the cause रेजिस्टर */
		mvpp2_ग_लिखो(port->priv, MVPP2_ISR_MISC_CAUSE_REG, 0);
		mvpp2_thपढ़ो_ग_लिखो(port->priv, thपढ़ो,
				   MVPP2_ISR_RX_TX_CAUSE_REG(port->id),
				   cause_rx_tx & ~MVPP2_CAUSE_MISC_SUM_MASK);
	पूर्ण

	अगर (port->has_tx_irqs) अणु
		cause_tx = cause_rx_tx & MVPP2_CAUSE_TXQ_OCCUP_DESC_ALL_MASK;
		अगर (cause_tx) अणु
			cause_tx >>= MVPP2_CAUSE_TXQ_OCCUP_DESC_ALL_OFFSET;
			mvpp2_tx_करोne(port, cause_tx, qv->sw_thपढ़ो_id);
		पूर्ण
	पूर्ण

	/* Process RX packets */
	cause_rx = cause_rx_tx &
		   MVPP2_CAUSE_RXQ_OCCUP_DESC_ALL_MASK(port->priv->hw_version);
	cause_rx <<= qv->first_rxq;
	cause_rx |= qv->pending_cause_rx;
	जबतक (cause_rx && budget > 0) अणु
		पूर्णांक count;
		काष्ठा mvpp2_rx_queue *rxq;

		rxq = mvpp2_get_rx_queue(port, cause_rx);
		अगर (!rxq)
			अवरोध;

		count = mvpp2_rx(port, napi, budget, rxq);
		rx_करोne += count;
		budget -= count;
		अगर (budget > 0) अणु
			/* Clear the bit associated to this Rx queue
			 * so that next iteration will जारी from
			 * the next Rx queue.
			 */
			cause_rx &= ~(1 << rxq->logic_rxq);
		पूर्ण
	पूर्ण

	अगर (budget > 0) अणु
		cause_rx = 0;
		napi_complete_करोne(napi, rx_करोne);

		mvpp2_qvec_पूर्णांकerrupt_enable(qv);
	पूर्ण
	qv->pending_cause_rx = cause_rx;
	वापस rx_करोne;
पूर्ण

अटल व्योम mvpp22_mode_reconfigure(काष्ठा mvpp2_port *port)
अणु
	u32 ctrl3;

	/* Set the GMAC & XLG MAC in reset */
	mvpp2_mac_reset_निश्चित(port);

	/* Set the MPCS and XPCS in reset */
	mvpp22_pcs_reset_निश्चित(port);

	/* comphy reconfiguration */
	mvpp22_comphy_init(port);

	/* gop reconfiguration */
	mvpp22_gop_init(port);

	mvpp22_pcs_reset_deनिश्चित(port);

	अगर (mvpp2_port_supports_xlg(port)) अणु
		ctrl3 = पढ़ोl(port->base + MVPP22_XLG_CTRL3_REG);
		ctrl3 &= ~MVPP22_XLG_CTRL3_MACMODESELECT_MASK;

		अगर (mvpp2_is_xlg(port->phy_पूर्णांकerface))
			ctrl3 |= MVPP22_XLG_CTRL3_MACMODESELECT_10G;
		अन्यथा
			ctrl3 |= MVPP22_XLG_CTRL3_MACMODESELECT_GMAC;

		ग_लिखोl(ctrl3, port->base + MVPP22_XLG_CTRL3_REG);
	पूर्ण

	अगर (mvpp2_port_supports_xlg(port) && mvpp2_is_xlg(port->phy_पूर्णांकerface))
		mvpp2_xlg_max_rx_size_set(port);
	अन्यथा
		mvpp2_gmac_max_rx_size_set(port);
पूर्ण

/* Set hw पूर्णांकernals when starting port */
अटल व्योम mvpp2_start_dev(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक i;

	mvpp2_txp_max_tx_size_set(port);

	क्रम (i = 0; i < port->nqvecs; i++)
		napi_enable(&port->qvecs[i].napi);

	/* Enable पूर्णांकerrupts on all thपढ़ोs */
	mvpp2_पूर्णांकerrupts_enable(port);

	अगर (port->priv->hw_version >= MVPP22)
		mvpp22_mode_reconfigure(port);

	अगर (port->phylink) अणु
		phylink_start(port->phylink);
	पूर्ण अन्यथा अणु
		mvpp2_acpi_start(port);
	पूर्ण

	netअगर_tx_start_all_queues(port->dev);

	clear_bit(0, &port->state);
पूर्ण

/* Set hw पूर्णांकernals when stopping port */
अटल व्योम mvpp2_stop_dev(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक i;

	set_bit(0, &port->state);

	/* Disable पूर्णांकerrupts on all thपढ़ोs */
	mvpp2_पूर्णांकerrupts_disable(port);

	क्रम (i = 0; i < port->nqvecs; i++)
		napi_disable(&port->qvecs[i].napi);

	अगर (port->phylink)
		phylink_stop(port->phylink);
	phy_घातer_off(port->comphy);
पूर्ण

अटल पूर्णांक mvpp2_check_ringparam_valid(काष्ठा net_device *dev,
				       काष्ठा ethtool_ringparam *ring)
अणु
	u16 new_rx_pending = ring->rx_pending;
	u16 new_tx_pending = ring->tx_pending;

	अगर (ring->rx_pending == 0 || ring->tx_pending == 0)
		वापस -EINVAL;

	अगर (ring->rx_pending > MVPP2_MAX_RXD_MAX)
		new_rx_pending = MVPP2_MAX_RXD_MAX;
	अन्यथा अगर (ring->rx_pending < MSS_THRESHOLD_START)
		new_rx_pending = MSS_THRESHOLD_START;
	अन्यथा अगर (!IS_ALIGNED(ring->rx_pending, 16))
		new_rx_pending = ALIGN(ring->rx_pending, 16);

	अगर (ring->tx_pending > MVPP2_MAX_TXD_MAX)
		new_tx_pending = MVPP2_MAX_TXD_MAX;
	अन्यथा अगर (!IS_ALIGNED(ring->tx_pending, 32))
		new_tx_pending = ALIGN(ring->tx_pending, 32);

	/* The Tx ring size cannot be smaller than the minimum number of
	 * descriptors needed क्रम TSO.
	 */
	अगर (new_tx_pending < MVPP2_MAX_SKB_DESCS)
		new_tx_pending = ALIGN(MVPP2_MAX_SKB_DESCS, 32);

	अगर (ring->rx_pending != new_rx_pending) अणु
		netdev_info(dev, "illegal Rx ring size value %d, round to %d\n",
			    ring->rx_pending, new_rx_pending);
		ring->rx_pending = new_rx_pending;
	पूर्ण

	अगर (ring->tx_pending != new_tx_pending) अणु
		netdev_info(dev, "illegal Tx ring size value %d, round to %d\n",
			    ring->tx_pending, new_tx_pending);
		ring->tx_pending = new_tx_pending;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mvpp21_get_mac_address(काष्ठा mvpp2_port *port, अचिन्हित अक्षर *addr)
अणु
	u32 mac_addr_l, mac_addr_m, mac_addr_h;

	mac_addr_l = पढ़ोl(port->base + MVPP2_GMAC_CTRL_1_REG);
	mac_addr_m = पढ़ोl(port->priv->lms_base + MVPP2_SRC_ADDR_MIDDLE);
	mac_addr_h = पढ़ोl(port->priv->lms_base + MVPP2_SRC_ADDR_HIGH);
	addr[0] = (mac_addr_h >> 24) & 0xFF;
	addr[1] = (mac_addr_h >> 16) & 0xFF;
	addr[2] = (mac_addr_h >> 8) & 0xFF;
	addr[3] = mac_addr_h & 0xFF;
	addr[4] = mac_addr_m & 0xFF;
	addr[5] = (mac_addr_l >> MVPP2_GMAC_SA_LOW_OFFS) & 0xFF;
पूर्ण

अटल पूर्णांक mvpp2_irqs_init(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < port->nqvecs; i++) अणु
		काष्ठा mvpp2_queue_vector *qv = port->qvecs + i;

		अगर (qv->type == MVPP2_QUEUE_VECTOR_PRIVATE) अणु
			qv->mask = kzalloc(cpumask_size(), GFP_KERNEL);
			अगर (!qv->mask) अणु
				err = -ENOMEM;
				जाओ err;
			पूर्ण

			irq_set_status_flags(qv->irq, IRQ_NO_BALANCING);
		पूर्ण

		err = request_irq(qv->irq, mvpp2_isr, 0, port->dev->name, qv);
		अगर (err)
			जाओ err;

		अगर (qv->type == MVPP2_QUEUE_VECTOR_PRIVATE) अणु
			अचिन्हित पूर्णांक cpu;

			क्रम_each_present_cpu(cpu) अणु
				अगर (mvpp2_cpu_to_thपढ़ो(port->priv, cpu) ==
				    qv->sw_thपढ़ो_id)
					cpumask_set_cpu(cpu, qv->mask);
			पूर्ण

			irq_set_affinity_hपूर्णांक(qv->irq, qv->mask);
		पूर्ण
	पूर्ण

	वापस 0;
err:
	क्रम (i = 0; i < port->nqvecs; i++) अणु
		काष्ठा mvpp2_queue_vector *qv = port->qvecs + i;

		irq_set_affinity_hपूर्णांक(qv->irq, शून्य);
		kमुक्त(qv->mask);
		qv->mask = शून्य;
		मुक्त_irq(qv->irq, qv);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mvpp2_irqs_deinit(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < port->nqvecs; i++) अणु
		काष्ठा mvpp2_queue_vector *qv = port->qvecs + i;

		irq_set_affinity_hपूर्णांक(qv->irq, शून्य);
		kमुक्त(qv->mask);
		qv->mask = शून्य;
		irq_clear_status_flags(qv->irq, IRQ_NO_BALANCING);
		मुक्त_irq(qv->irq, qv);
	पूर्ण
पूर्ण

अटल bool mvpp22_rss_is_supported(काष्ठा mvpp2_port *port)
अणु
	वापस (queue_mode == MVPP2_QDIST_MULTI_MODE) &&
		!(port->flags & MVPP2_F_LOOPBACK);
पूर्ण

अटल पूर्णांक mvpp2_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	काष्ठा mvpp2 *priv = port->priv;
	अचिन्हित अक्षर mac_bcast[ETH_ALEN] = अणु
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;
	bool valid = false;
	पूर्णांक err;

	err = mvpp2_prs_mac_da_accept(port, mac_bcast, true);
	अगर (err) अणु
		netdev_err(dev, "mvpp2_prs_mac_da_accept BC failed\n");
		वापस err;
	पूर्ण
	err = mvpp2_prs_mac_da_accept(port, dev->dev_addr, true);
	अगर (err) अणु
		netdev_err(dev, "mvpp2_prs_mac_da_accept own addr failed\n");
		वापस err;
	पूर्ण
	err = mvpp2_prs_tag_mode_set(port->priv, port->id, MVPP2_TAG_TYPE_MH);
	अगर (err) अणु
		netdev_err(dev, "mvpp2_prs_tag_mode_set failed\n");
		वापस err;
	पूर्ण
	err = mvpp2_prs_def_flow(port);
	अगर (err) अणु
		netdev_err(dev, "mvpp2_prs_def_flow failed\n");
		वापस err;
	पूर्ण

	/* Allocate the Rx/Tx queues */
	err = mvpp2_setup_rxqs(port);
	अगर (err) अणु
		netdev_err(port->dev, "cannot allocate Rx queues\n");
		वापस err;
	पूर्ण

	err = mvpp2_setup_txqs(port);
	अगर (err) अणु
		netdev_err(port->dev, "cannot allocate Tx queues\n");
		जाओ err_cleanup_rxqs;
	पूर्ण

	err = mvpp2_irqs_init(port);
	अगर (err) अणु
		netdev_err(port->dev, "cannot init IRQs\n");
		जाओ err_cleanup_txqs;
	पूर्ण

	/* Phylink isn't supported yet in ACPI mode */
	अगर (port->of_node) अणु
		err = phylink_of_phy_connect(port->phylink, port->of_node, 0);
		अगर (err) अणु
			netdev_err(port->dev, "could not attach PHY (%d)\n",
				   err);
			जाओ err_मुक्त_irq;
		पूर्ण

		valid = true;
	पूर्ण

	अगर (priv->hw_version >= MVPP22 && port->port_irq) अणु
		err = request_irq(port->port_irq, mvpp2_port_isr, 0,
				  dev->name, port);
		अगर (err) अणु
			netdev_err(port->dev,
				   "cannot request port link/ptp IRQ %d\n",
				   port->port_irq);
			जाओ err_मुक्त_irq;
		पूर्ण

		mvpp22_gop_setup_irq(port);

		/* In शेष link is करोwn */
		netअगर_carrier_off(port->dev);

		valid = true;
	पूर्ण अन्यथा अणु
		port->port_irq = 0;
	पूर्ण

	अगर (!valid) अणु
		netdev_err(port->dev,
			   "invalid configuration: no dt or link IRQ");
		err = -ENOENT;
		जाओ err_मुक्त_irq;
	पूर्ण

	/* Unmask पूर्णांकerrupts on all CPUs */
	on_each_cpu(mvpp2_पूर्णांकerrupts_unmask, port, 1);
	mvpp2_shared_पूर्णांकerrupt_mask_unmask(port, false);

	mvpp2_start_dev(port);

	/* Start hardware statistics gathering */
	queue_delayed_work(priv->stats_queue, &port->stats_work,
			   MVPP2_MIB_COUNTERS_STATS_DELAY);

	वापस 0;

err_मुक्त_irq:
	mvpp2_irqs_deinit(port);
err_cleanup_txqs:
	mvpp2_cleanup_txqs(port);
err_cleanup_rxqs:
	mvpp2_cleanup_rxqs(port);
	वापस err;
पूर्ण

अटल पूर्णांक mvpp2_stop(काष्ठा net_device *dev)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	काष्ठा mvpp2_port_pcpu *port_pcpu;
	अचिन्हित पूर्णांक thपढ़ो;

	mvpp2_stop_dev(port);

	/* Mask पूर्णांकerrupts on all thपढ़ोs */
	on_each_cpu(mvpp2_पूर्णांकerrupts_mask, port, 1);
	mvpp2_shared_पूर्णांकerrupt_mask_unmask(port, true);

	अगर (port->phylink)
		phylink_disconnect_phy(port->phylink);
	अगर (port->port_irq)
		मुक्त_irq(port->port_irq, port);

	mvpp2_irqs_deinit(port);
	अगर (!port->has_tx_irqs) अणु
		क्रम (thपढ़ो = 0; thपढ़ो < port->priv->nthपढ़ोs; thपढ़ो++) अणु
			port_pcpu = per_cpu_ptr(port->pcpu, thपढ़ो);

			hrसमयr_cancel(&port_pcpu->tx_करोne_समयr);
			port_pcpu->समयr_scheduled = false;
		पूर्ण
	पूर्ण
	mvpp2_cleanup_rxqs(port);
	mvpp2_cleanup_txqs(port);

	cancel_delayed_work_sync(&port->stats_work);

	mvpp2_mac_reset_निश्चित(port);
	mvpp22_pcs_reset_निश्चित(port);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_prs_mac_da_accept_list(काष्ठा mvpp2_port *port,
					काष्ठा netdev_hw_addr_list *list)
अणु
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक ret;

	netdev_hw_addr_list_क्रम_each(ha, list) अणु
		ret = mvpp2_prs_mac_da_accept(port, ha->addr, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mvpp2_set_rx_promisc(काष्ठा mvpp2_port *port, bool enable)
अणु
	अगर (!enable && (port->dev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		mvpp2_prs_vid_enable_filtering(port);
	अन्यथा
		mvpp2_prs_vid_disable_filtering(port);

	mvpp2_prs_mac_promisc_set(port->priv, port->id,
				  MVPP2_PRS_L2_UNI_CAST, enable);

	mvpp2_prs_mac_promisc_set(port->priv, port->id,
				  MVPP2_PRS_L2_MULTI_CAST, enable);
पूर्ण

अटल व्योम mvpp2_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	/* Clear the whole UC and MC list */
	mvpp2_prs_mac_del_all(port);

	अगर (dev->flags & IFF_PROMISC) अणु
		mvpp2_set_rx_promisc(port, true);
		वापस;
	पूर्ण

	mvpp2_set_rx_promisc(port, false);

	अगर (netdev_uc_count(dev) > MVPP2_PRS_MAC_UC_FILT_MAX ||
	    mvpp2_prs_mac_da_accept_list(port, &dev->uc))
		mvpp2_prs_mac_promisc_set(port->priv, port->id,
					  MVPP2_PRS_L2_UNI_CAST, true);

	अगर (dev->flags & IFF_ALLMULTI) अणु
		mvpp2_prs_mac_promisc_set(port->priv, port->id,
					  MVPP2_PRS_L2_MULTI_CAST, true);
		वापस;
	पूर्ण

	अगर (netdev_mc_count(dev) > MVPP2_PRS_MAC_MC_FILT_MAX ||
	    mvpp2_prs_mac_da_accept_list(port, &dev->mc))
		mvpp2_prs_mac_promisc_set(port->priv, port->id,
					  MVPP2_PRS_L2_MULTI_CAST, true);
पूर्ण

अटल पूर्णांक mvpp2_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	स्थिर काष्ठा sockaddr *addr = p;
	पूर्णांक err;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	err = mvpp2_prs_update_mac_da(dev, addr->sa_data);
	अगर (err) अणु
		/* Reconfigure parser accept the original MAC address */
		mvpp2_prs_update_mac_da(dev, dev->dev_addr);
		netdev_err(dev, "failed to change MAC address\n");
	पूर्ण
	वापस err;
पूर्ण

/* Shut करोwn all the ports, reconfigure the pools as percpu or shared,
 * then bring up again all ports.
 */
अटल पूर्णांक mvpp2_bm_चयन_buffers(काष्ठा mvpp2 *priv, bool percpu)
अणु
	bool change_percpu = (percpu != priv->percpu_pools);
	पूर्णांक numbufs = MVPP2_BM_POOLS_NUM, i;
	काष्ठा mvpp2_port *port = शून्य;
	bool status[MVPP2_MAX_PORTS];

	क्रम (i = 0; i < priv->port_count; i++) अणु
		port = priv->port_list[i];
		status[i] = netअगर_running(port->dev);
		अगर (status[i])
			mvpp2_stop(port->dev);
	पूर्ण

	/* nrxqs is the same क्रम all ports */
	अगर (priv->percpu_pools)
		numbufs = port->nrxqs * 2;

	अगर (change_percpu)
		mvpp2_bm_pool_update_priv_fc(priv, false);

	क्रम (i = 0; i < numbufs; i++)
		mvpp2_bm_pool_destroy(port->dev->dev.parent, priv, &priv->bm_pools[i]);

	devm_kमुक्त(port->dev->dev.parent, priv->bm_pools);
	priv->percpu_pools = percpu;
	mvpp2_bm_init(port->dev->dev.parent, priv);

	क्रम (i = 0; i < priv->port_count; i++) अणु
		port = priv->port_list[i];
		mvpp2_swf_bm_pool_init(port);
		अगर (status[i])
			mvpp2_खोलो(port->dev);
	पूर्ण

	अगर (change_percpu)
		mvpp2_bm_pool_update_priv_fc(priv, true);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_change_mtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	bool running = netअगर_running(dev);
	काष्ठा mvpp2 *priv = port->priv;
	पूर्णांक err;

	अगर (!IS_ALIGNED(MVPP2_RX_PKT_SIZE(mtu), 8)) अणु
		netdev_info(dev, "illegal MTU value %d, round to %d\n", mtu,
			    ALIGN(MVPP2_RX_PKT_SIZE(mtu), 8));
		mtu = ALIGN(MVPP2_RX_PKT_SIZE(mtu), 8);
	पूर्ण

	अगर (MVPP2_RX_PKT_SIZE(mtu) > MVPP2_BM_LONG_PKT_SIZE) अणु
		अगर (port->xdp_prog) अणु
			netdev_err(dev, "Jumbo frames are not supported with XDP\n");
			वापस -EINVAL;
		पूर्ण
		अगर (priv->percpu_pools) अणु
			netdev_warn(dev, "mtu %d too high, switching to shared buffers", mtu);
			mvpp2_bm_चयन_buffers(priv, false);
		पूर्ण
	पूर्ण अन्यथा अणु
		bool jumbo = false;
		पूर्णांक i;

		क्रम (i = 0; i < priv->port_count; i++)
			अगर (priv->port_list[i] != port &&
			    MVPP2_RX_PKT_SIZE(priv->port_list[i]->dev->mtu) >
			    MVPP2_BM_LONG_PKT_SIZE) अणु
				jumbo = true;
				अवरोध;
			पूर्ण

		/* No port is using jumbo frames */
		अगर (!jumbo) अणु
			dev_info(port->dev->dev.parent,
				 "all ports have a low MTU, switching to per-cpu buffers");
			mvpp2_bm_चयन_buffers(priv, true);
		पूर्ण
	पूर्ण

	अगर (running)
		mvpp2_stop_dev(port);

	err = mvpp2_bm_update_mtu(dev, mtu);
	अगर (err) अणु
		netdev_err(dev, "failed to change MTU\n");
		/* Reconfigure BM to the original MTU */
		mvpp2_bm_update_mtu(dev, dev->mtu);
	पूर्ण अन्यथा अणु
		port->pkt_size =  MVPP2_RX_PKT_SIZE(mtu);
	पूर्ण

	अगर (running) अणु
		mvpp2_start_dev(port);
		mvpp2_egress_enable(port);
		mvpp2_ingress_enable(port);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mvpp2_check_pagepool_dma(काष्ठा mvpp2_port *port)
अणु
	क्रमागत dma_data_direction dma_dir = DMA_FROM_DEVICE;
	काष्ठा mvpp2 *priv = port->priv;
	पूर्णांक err = -1, i;

	अगर (!priv->percpu_pools)
		वापस err;

	अगर (!priv->page_pool[0])
		वापस -ENOMEM;

	क्रम (i = 0; i < priv->port_count; i++) अणु
		port = priv->port_list[i];
		अगर (port->xdp_prog) अणु
			dma_dir = DMA_BIसूचीECTIONAL;
			अवरोध;
		पूर्ण
	पूर्ण

	/* All pools are equal in terms of DMA direction */
	अगर (priv->page_pool[0]->p.dma_dir != dma_dir)
		err = mvpp2_bm_चयन_buffers(priv, true);

	वापस err;
पूर्ण

अटल व्योम
mvpp2_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा mvpp2_pcpu_stats *cpu_stats;
		u64 rx_packets;
		u64 rx_bytes;
		u64 tx_packets;
		u64 tx_bytes;

		cpu_stats = per_cpu_ptr(port->stats, cpu);
		करो अणु
			start = u64_stats_fetch_begin_irq(&cpu_stats->syncp);
			rx_packets = cpu_stats->rx_packets;
			rx_bytes   = cpu_stats->rx_bytes;
			tx_packets = cpu_stats->tx_packets;
			tx_bytes   = cpu_stats->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&cpu_stats->syncp, start));

		stats->rx_packets += rx_packets;
		stats->rx_bytes   += rx_bytes;
		stats->tx_packets += tx_packets;
		stats->tx_bytes   += tx_bytes;
	पूर्ण

	stats->rx_errors	= dev->stats.rx_errors;
	stats->rx_dropped	= dev->stats.rx_dropped;
	stats->tx_dropped	= dev->stats.tx_dropped;
पूर्ण

अटल पूर्णांक mvpp2_set_ts_config(काष्ठा mvpp2_port *port, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	व्योम __iomem *ptp;
	u32 gcr, पूर्णांक_mask;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	अगर (config.flags)
		वापस -EINVAL;

	अगर (config.tx_type != HWTSTAMP_TX_OFF &&
	    config.tx_type != HWTSTAMP_TX_ON)
		वापस -दुस्फल;

	ptp = port->priv->अगरace_base + MVPP22_PTP_BASE(port->gop_id);

	पूर्णांक_mask = gcr = 0;
	अगर (config.tx_type != HWTSTAMP_TX_OFF) अणु
		gcr |= MVPP22_PTP_GCR_TSU_ENABLE | MVPP22_PTP_GCR_TX_RESET;
		पूर्णांक_mask |= MVPP22_PTP_INT_MASK_QUEUE1 |
			    MVPP22_PTP_INT_MASK_QUEUE0;
	पूर्ण

	/* It seems we must also release the TX reset when enabling the TSU */
	अगर (config.rx_filter != HWTSTAMP_FILTER_NONE)
		gcr |= MVPP22_PTP_GCR_TSU_ENABLE | MVPP22_PTP_GCR_RX_RESET |
		       MVPP22_PTP_GCR_TX_RESET;

	अगर (gcr & MVPP22_PTP_GCR_TSU_ENABLE)
		mvpp22_tai_start(port->priv->tai);

	अगर (config.rx_filter != HWTSTAMP_FILTER_NONE) अणु
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		mvpp2_modअगरy(ptp + MVPP22_PTP_GCR,
			     MVPP22_PTP_GCR_RX_RESET |
			     MVPP22_PTP_GCR_TX_RESET |
			     MVPP22_PTP_GCR_TSU_ENABLE, gcr);
		port->rx_hwtstamp = true;
	पूर्ण अन्यथा अणु
		port->rx_hwtstamp = false;
		mvpp2_modअगरy(ptp + MVPP22_PTP_GCR,
			     MVPP22_PTP_GCR_RX_RESET |
			     MVPP22_PTP_GCR_TX_RESET |
			     MVPP22_PTP_GCR_TSU_ENABLE, gcr);
	पूर्ण

	mvpp2_modअगरy(ptp + MVPP22_PTP_INT_MASK,
		     MVPP22_PTP_INT_MASK_QUEUE1 |
		     MVPP22_PTP_INT_MASK_QUEUE0, पूर्णांक_mask);

	अगर (!(gcr & MVPP22_PTP_GCR_TSU_ENABLE))
		mvpp22_tai_stop(port->priv->tai);

	port->tx_hwtstamp_type = config.tx_type;

	अगर (copy_to_user(अगरr->अगरr_data, &config, माप(config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_get_ts_config(काष्ठा mvpp2_port *port, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;

	स_रखो(&config, 0, माप(config));

	config.tx_type = port->tx_hwtstamp_type;
	config.rx_filter = port->rx_hwtstamp ?
		HWTSTAMP_FILTER_ALL : HWTSTAMP_FILTER_NONE;

	अगर (copy_to_user(अगरr->अगरr_data, &config, माप(config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_ethtool_get_ts_info(काष्ठा net_device *dev,
				     काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	अगर (!port->hwtstamp)
		वापस -EOPNOTSUPP;

	info->phc_index = mvpp22_tai_ptp_घड़ी_index(port->priv->tai);
	info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE |
				SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;
	info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			 BIT(HWTSTAMP_TX_ON);
	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE) |
			   BIT(HWTSTAMP_FILTER_ALL);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		अगर (port->hwtstamp)
			वापस mvpp2_set_ts_config(port, अगरr);
		अवरोध;

	हाल SIOCGHWTSTAMP:
		अगर (port->hwtstamp)
			वापस mvpp2_get_ts_config(port, अगरr);
		अवरोध;
	पूर्ण

	अगर (!port->phylink)
		वापस -ENOTSUPP;

	वापस phylink_mii_ioctl(port->phylink, अगरr, cmd);
पूर्ण

अटल पूर्णांक mvpp2_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक ret;

	ret = mvpp2_prs_vid_entry_add(port, vid);
	अगर (ret)
		netdev_err(dev, "rx-vlan-filter offloading cannot accept more than %d VIDs per port\n",
			   MVPP2_PRS_VLAN_FILT_MAX - 1);
	वापस ret;
पूर्ण

अटल पूर्णांक mvpp2_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto, u16 vid)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	mvpp2_prs_vid_entry_हटाओ(port, vid);
	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_set_features(काष्ठा net_device *dev,
			      netdev_features_t features)
अणु
	netdev_features_t changed = dev->features ^ features;
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	अगर (changed & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
		अगर (features & NETIF_F_HW_VLAN_CTAG_FILTER) अणु
			mvpp2_prs_vid_enable_filtering(port);
		पूर्ण अन्यथा अणु
			/* Invalidate all रेजिस्टरed VID filters क्रम this
			 * port
			 */
			mvpp2_prs_vid_हटाओ_all(port);

			mvpp2_prs_vid_disable_filtering(port);
		पूर्ण
	पूर्ण

	अगर (changed & NETIF_F_RXHASH) अणु
		अगर (features & NETIF_F_RXHASH)
			mvpp22_port_rss_enable(port);
		अन्यथा
			mvpp22_port_rss_disable(port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_xdp_setup(काष्ठा mvpp2_port *port, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा bpf_prog *prog = bpf->prog, *old_prog;
	bool running = netअगर_running(port->dev);
	bool reset = !prog != !port->xdp_prog;

	अगर (port->dev->mtu > ETH_DATA_LEN) अणु
		NL_SET_ERR_MSG_MOD(bpf->extack, "XDP is not supported with jumbo frames enabled");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!port->priv->percpu_pools) अणु
		NL_SET_ERR_MSG_MOD(bpf->extack, "Per CPU Pools required for XDP");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (port->ntxqs < num_possible_cpus() * 2) अणु
		NL_SET_ERR_MSG_MOD(bpf->extack, "XDP_TX needs two TX queues per CPU");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* device is up and bpf is added/हटाओd, must setup the RX queues */
	अगर (running && reset)
		mvpp2_stop(port->dev);

	old_prog = xchg(&port->xdp_prog, prog);
	अगर (old_prog)
		bpf_prog_put(old_prog);

	/* bpf is just replaced, RXQ and MTU are alपढ़ोy setup */
	अगर (!reset)
		वापस 0;

	/* device was up, restore the link */
	अगर (running)
		mvpp2_खोलो(port->dev);

	/* Check Page Pool DMA Direction */
	mvpp2_check_pagepool_dma(port);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस mvpp2_xdp_setup(port, xdp);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Ethtool methods */

अटल पूर्णांक mvpp2_ethtool_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	अगर (!port->phylink)
		वापस -ENOTSUPP;

	वापस phylink_ethtool_nway_reset(port->phylink);
पूर्ण

/* Set पूर्णांकerrupt coalescing क्रम ethtools */
अटल पूर्णांक mvpp2_ethtool_set_coalesce(काष्ठा net_device *dev,
				      काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक queue;

	क्रम (queue = 0; queue < port->nrxqs; queue++) अणु
		काष्ठा mvpp2_rx_queue *rxq = port->rxqs[queue];

		rxq->समय_coal = c->rx_coalesce_usecs;
		rxq->pkts_coal = c->rx_max_coalesced_frames;
		mvpp2_rx_pkts_coal_set(port, rxq);
		mvpp2_rx_समय_coal_set(port, rxq);
	पूर्ण

	अगर (port->has_tx_irqs) अणु
		port->tx_समय_coal = c->tx_coalesce_usecs;
		mvpp2_tx_समय_coal_set(port);
	पूर्ण

	क्रम (queue = 0; queue < port->ntxqs; queue++) अणु
		काष्ठा mvpp2_tx_queue *txq = port->txqs[queue];

		txq->करोne_pkts_coal = c->tx_max_coalesced_frames;

		अगर (port->has_tx_irqs)
			mvpp2_tx_pkts_coal_set(port, txq);
	पूर्ण

	वापस 0;
पूर्ण

/* get coalescing क्रम ethtools */
अटल पूर्णांक mvpp2_ethtool_get_coalesce(काष्ठा net_device *dev,
				      काष्ठा ethtool_coalesce *c)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	c->rx_coalesce_usecs       = port->rxqs[0]->समय_coal;
	c->rx_max_coalesced_frames = port->rxqs[0]->pkts_coal;
	c->tx_max_coalesced_frames = port->txqs[0]->करोne_pkts_coal;
	c->tx_coalesce_usecs       = port->tx_समय_coal;
	वापस 0;
पूर्ण

अटल व्योम mvpp2_ethtool_get_drvinfo(काष्ठा net_device *dev,
				      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, MVPP2_DRIVER_NAME,
		माप(drvinfo->driver));
	strlcpy(drvinfo->version, MVPP2_DRIVER_VERSION,
		माप(drvinfo->version));
	strlcpy(drvinfo->bus_info, dev_name(&dev->dev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम mvpp2_ethtool_get_ringparam(काष्ठा net_device *dev,
					काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	ring->rx_max_pending = MVPP2_MAX_RXD_MAX;
	ring->tx_max_pending = MVPP2_MAX_TXD_MAX;
	ring->rx_pending = port->rx_ring_size;
	ring->tx_pending = port->tx_ring_size;
पूर्ण

अटल पूर्णांक mvpp2_ethtool_set_ringparam(काष्ठा net_device *dev,
				       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	u16 prev_rx_ring_size = port->rx_ring_size;
	u16 prev_tx_ring_size = port->tx_ring_size;
	पूर्णांक err;

	err = mvpp2_check_ringparam_valid(dev, ring);
	अगर (err)
		वापस err;

	अगर (!netअगर_running(dev)) अणु
		port->rx_ring_size = ring->rx_pending;
		port->tx_ring_size = ring->tx_pending;
		वापस 0;
	पूर्ण

	/* The पूर्णांकerface is running, so we have to क्रमce a
	 * पुनः_स्मृतिation of the queues
	 */
	mvpp2_stop_dev(port);
	mvpp2_cleanup_rxqs(port);
	mvpp2_cleanup_txqs(port);

	port->rx_ring_size = ring->rx_pending;
	port->tx_ring_size = ring->tx_pending;

	err = mvpp2_setup_rxqs(port);
	अगर (err) अणु
		/* Reallocate Rx queues with the original ring size */
		port->rx_ring_size = prev_rx_ring_size;
		ring->rx_pending = prev_rx_ring_size;
		err = mvpp2_setup_rxqs(port);
		अगर (err)
			जाओ err_out;
	पूर्ण
	err = mvpp2_setup_txqs(port);
	अगर (err) अणु
		/* Reallocate Tx queues with the original ring size */
		port->tx_ring_size = prev_tx_ring_size;
		ring->tx_pending = prev_tx_ring_size;
		err = mvpp2_setup_txqs(port);
		अगर (err)
			जाओ err_clean_rxqs;
	पूर्ण

	mvpp2_start_dev(port);
	mvpp2_egress_enable(port);
	mvpp2_ingress_enable(port);

	वापस 0;

err_clean_rxqs:
	mvpp2_cleanup_rxqs(port);
err_out:
	netdev_err(dev, "failed to change ring parameters");
	वापस err;
पूर्ण

अटल व्योम mvpp2_ethtool_get_छोड़ो_param(काष्ठा net_device *dev,
					  काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	अगर (!port->phylink)
		वापस;

	phylink_ethtool_get_छोड़ोparam(port->phylink, छोड़ो);
पूर्ण

अटल पूर्णांक mvpp2_ethtool_set_छोड़ो_param(काष्ठा net_device *dev,
					 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	अगर (!port->phylink)
		वापस -ENOTSUPP;

	वापस phylink_ethtool_set_छोड़ोparam(port->phylink, छोड़ो);
पूर्ण

अटल पूर्णांक mvpp2_ethtool_get_link_ksettings(काष्ठा net_device *dev,
					    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	अगर (!port->phylink)
		वापस -ENOTSUPP;

	वापस phylink_ethtool_ksettings_get(port->phylink, cmd);
पूर्ण

अटल पूर्णांक mvpp2_ethtool_set_link_ksettings(काष्ठा net_device *dev,
					    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	अगर (!port->phylink)
		वापस -ENOTSUPP;

	वापस phylink_ethtool_ksettings_set(port->phylink, cmd);
पूर्ण

अटल पूर्णांक mvpp2_ethtool_get_rxnfc(काष्ठा net_device *dev,
				   काष्ठा ethtool_rxnfc *info, u32 *rules)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक ret = 0, i, loc = 0;

	अगर (!mvpp22_rss_is_supported(port))
		वापस -EOPNOTSUPP;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXFH:
		ret = mvpp2_ethtool_rxfh_get(port, info);
		अवरोध;
	हाल ETHTOOL_GRXRINGS:
		info->data = port->nrxqs;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		info->rule_cnt = port->n_rfs_rules;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		ret = mvpp2_ethtool_cls_rule_get(port, info);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		क्रम (i = 0; i < MVPP2_N_RFS_ENTRIES_PER_FLOW; i++) अणु
			अगर (port->rfs_rules[i])
				rules[loc++] = i;
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mvpp2_ethtool_set_rxnfc(काष्ठा net_device *dev,
				   काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (!mvpp22_rss_is_supported(port))
		वापस -EOPNOTSUPP;

	चयन (info->cmd) अणु
	हाल ETHTOOL_SRXFH:
		ret = mvpp2_ethtool_rxfh_set(port, info);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLINS:
		ret = mvpp2_ethtool_cls_rule_ins(port, info);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		ret = mvpp2_ethtool_cls_rule_del(port, info);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

अटल u32 mvpp2_ethtool_get_rxfh_indir_size(काष्ठा net_device *dev)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);

	वापस mvpp22_rss_is_supported(port) ? MVPP22_RSS_TABLE_ENTRIES : 0;
पूर्ण

अटल पूर्णांक mvpp2_ethtool_get_rxfh(काष्ठा net_device *dev, u32 *indir, u8 *key,
				  u8 *hfunc)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (!mvpp22_rss_is_supported(port))
		वापस -EOPNOTSUPP;

	अगर (indir)
		ret = mvpp22_port_rss_ctx_indir_get(port, 0, indir);

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_CRC32;

	वापस ret;
पूर्ण

अटल पूर्णांक mvpp2_ethtool_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir,
				  स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (!mvpp22_rss_is_supported(port))
		वापस -EOPNOTSUPP;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_CRC32)
		वापस -EOPNOTSUPP;

	अगर (key)
		वापस -EOPNOTSUPP;

	अगर (indir)
		ret = mvpp22_port_rss_ctx_indir_set(port, 0, indir);

	वापस ret;
पूर्ण

अटल पूर्णांक mvpp2_ethtool_get_rxfh_context(काष्ठा net_device *dev, u32 *indir,
					  u8 *key, u8 *hfunc, u32 rss_context)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक ret = 0;

	अगर (!mvpp22_rss_is_supported(port))
		वापस -EOPNOTSUPP;
	अगर (rss_context >= MVPP22_N_RSS_TABLES)
		वापस -EINVAL;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_CRC32;

	अगर (indir)
		ret = mvpp22_port_rss_ctx_indir_get(port, rss_context, indir);

	वापस ret;
पूर्ण

अटल पूर्णांक mvpp2_ethtool_set_rxfh_context(काष्ठा net_device *dev,
					  स्थिर u32 *indir, स्थिर u8 *key,
					  स्थिर u8 hfunc, u32 *rss_context,
					  bool delete)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	पूर्णांक ret;

	अगर (!mvpp22_rss_is_supported(port))
		वापस -EOPNOTSUPP;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_CRC32)
		वापस -EOPNOTSUPP;

	अगर (key)
		वापस -EOPNOTSUPP;

	अगर (delete)
		वापस mvpp22_port_rss_ctx_delete(port, *rss_context);

	अगर (*rss_context == ETH_RXFH_CONTEXT_ALLOC) अणु
		ret = mvpp22_port_rss_ctx_create(port, rss_context);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस mvpp22_port_rss_ctx_indir_set(port, *rss_context, indir);
पूर्ण
/* Device ops */

अटल स्थिर काष्ठा net_device_ops mvpp2_netdev_ops = अणु
	.nकरो_खोलो		= mvpp2_खोलो,
	.nकरो_stop		= mvpp2_stop,
	.nकरो_start_xmit		= mvpp2_tx,
	.nकरो_set_rx_mode	= mvpp2_set_rx_mode,
	.nकरो_set_mac_address	= mvpp2_set_mac_address,
	.nकरो_change_mtu		= mvpp2_change_mtu,
	.nकरो_get_stats64	= mvpp2_get_stats64,
	.nकरो_करो_ioctl		= mvpp2_ioctl,
	.nकरो_vlan_rx_add_vid	= mvpp2_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= mvpp2_vlan_rx_समाप्त_vid,
	.nकरो_set_features	= mvpp2_set_features,
	.nकरो_bpf		= mvpp2_xdp,
	.nकरो_xdp_xmit		= mvpp2_xdp_xmit,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops mvpp2_eth_tool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.nway_reset		= mvpp2_ethtool_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_ts_info		= mvpp2_ethtool_get_ts_info,
	.set_coalesce		= mvpp2_ethtool_set_coalesce,
	.get_coalesce		= mvpp2_ethtool_get_coalesce,
	.get_drvinfo		= mvpp2_ethtool_get_drvinfo,
	.get_ringparam		= mvpp2_ethtool_get_ringparam,
	.set_ringparam		= mvpp2_ethtool_set_ringparam,
	.get_strings		= mvpp2_ethtool_get_strings,
	.get_ethtool_stats	= mvpp2_ethtool_get_stats,
	.get_sset_count		= mvpp2_ethtool_get_sset_count,
	.get_छोड़ोparam		= mvpp2_ethtool_get_छोड़ो_param,
	.set_छोड़ोparam		= mvpp2_ethtool_set_छोड़ो_param,
	.get_link_ksettings	= mvpp2_ethtool_get_link_ksettings,
	.set_link_ksettings	= mvpp2_ethtool_set_link_ksettings,
	.get_rxnfc		= mvpp2_ethtool_get_rxnfc,
	.set_rxnfc		= mvpp2_ethtool_set_rxnfc,
	.get_rxfh_indir_size	= mvpp2_ethtool_get_rxfh_indir_size,
	.get_rxfh		= mvpp2_ethtool_get_rxfh,
	.set_rxfh		= mvpp2_ethtool_set_rxfh,
	.get_rxfh_context	= mvpp2_ethtool_get_rxfh_context,
	.set_rxfh_context	= mvpp2_ethtool_set_rxfh_context,
पूर्ण;

/* Used क्रम PPv2.1, or PPv2.2 with the old Device Tree binding that
 * had a single IRQ defined per-port.
 */
अटल पूर्णांक mvpp2_simple_queue_vectors_init(काष्ठा mvpp2_port *port,
					   काष्ठा device_node *port_node)
अणु
	काष्ठा mvpp2_queue_vector *v = &port->qvecs[0];

	v->first_rxq = 0;
	v->nrxqs = port->nrxqs;
	v->type = MVPP2_QUEUE_VECTOR_SHARED;
	v->sw_thपढ़ो_id = 0;
	v->sw_thपढ़ो_mask = *cpumask_bits(cpu_online_mask);
	v->port = port;
	v->irq = irq_of_parse_and_map(port_node, 0);
	अगर (v->irq <= 0)
		वापस -EINVAL;
	netअगर_napi_add(port->dev, &v->napi, mvpp2_poll,
		       NAPI_POLL_WEIGHT);

	port->nqvecs = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_multi_queue_vectors_init(काष्ठा mvpp2_port *port,
					  काष्ठा device_node *port_node)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	काष्ठा mvpp2_queue_vector *v;
	पूर्णांक i, ret;

	चयन (queue_mode) अणु
	हाल MVPP2_QDIST_SINGLE_MODE:
		port->nqvecs = priv->nthपढ़ोs + 1;
		अवरोध;
	हाल MVPP2_QDIST_MULTI_MODE:
		port->nqvecs = priv->nthपढ़ोs;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < port->nqvecs; i++) अणु
		अक्षर irqname[16];

		v = port->qvecs + i;

		v->port = port;
		v->type = MVPP2_QUEUE_VECTOR_PRIVATE;
		v->sw_thपढ़ो_id = i;
		v->sw_thपढ़ो_mask = BIT(i);

		अगर (port->flags & MVPP2_F_DT_COMPAT)
			snम_लिखो(irqname, माप(irqname), "tx-cpu%d", i);
		अन्यथा
			snम_लिखो(irqname, माप(irqname), "hif%d", i);

		अगर (queue_mode == MVPP2_QDIST_MULTI_MODE) अणु
			v->first_rxq = i;
			v->nrxqs = 1;
		पूर्ण अन्यथा अगर (queue_mode == MVPP2_QDIST_SINGLE_MODE &&
			   i == (port->nqvecs - 1)) अणु
			v->first_rxq = 0;
			v->nrxqs = port->nrxqs;
			v->type = MVPP2_QUEUE_VECTOR_SHARED;

			अगर (port->flags & MVPP2_F_DT_COMPAT)
				म_नकलन(irqname, "rx-shared", माप(irqname));
		पूर्ण

		अगर (port_node)
			v->irq = of_irq_get_byname(port_node, irqname);
		अन्यथा
			v->irq = fwnode_irq_get(port->fwnode, i);
		अगर (v->irq <= 0) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		netअगर_napi_add(port->dev, &v->napi, mvpp2_poll,
			       NAPI_POLL_WEIGHT);
	पूर्ण

	वापस 0;

err:
	क्रम (i = 0; i < port->nqvecs; i++)
		irq_dispose_mapping(port->qvecs[i].irq);
	वापस ret;
पूर्ण

अटल पूर्णांक mvpp2_queue_vectors_init(काष्ठा mvpp2_port *port,
				    काष्ठा device_node *port_node)
अणु
	अगर (port->has_tx_irqs)
		वापस mvpp2_multi_queue_vectors_init(port, port_node);
	अन्यथा
		वापस mvpp2_simple_queue_vectors_init(port, port_node);
पूर्ण

अटल व्योम mvpp2_queue_vectors_deinit(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < port->nqvecs; i++)
		irq_dispose_mapping(port->qvecs[i].irq);
पूर्ण

/* Configure Rx queue group पूर्णांकerrupt क्रम this port */
अटल व्योम mvpp2_rx_irqs_setup(काष्ठा mvpp2_port *port)
अणु
	काष्ठा mvpp2 *priv = port->priv;
	u32 val;
	पूर्णांक i;

	अगर (priv->hw_version == MVPP21) अणु
		mvpp2_ग_लिखो(priv, MVPP21_ISR_RXQ_GROUP_REG(port->id),
			    port->nrxqs);
		वापस;
	पूर्ण

	/* Handle the more complicated PPv2.2 and PPv2.3 हाल */
	क्रम (i = 0; i < port->nqvecs; i++) अणु
		काष्ठा mvpp2_queue_vector *qv = port->qvecs + i;

		अगर (!qv->nrxqs)
			जारी;

		val = qv->sw_thपढ़ो_id;
		val |= port->id << MVPP22_ISR_RXQ_GROUP_INDEX_GROUP_OFFSET;
		mvpp2_ग_लिखो(priv, MVPP22_ISR_RXQ_GROUP_INDEX_REG, val);

		val = qv->first_rxq;
		val |= qv->nrxqs << MVPP22_ISR_RXQ_SUB_GROUP_SIZE_OFFSET;
		mvpp2_ग_लिखो(priv, MVPP22_ISR_RXQ_SUB_GROUP_CONFIG_REG, val);
	पूर्ण
पूर्ण

/* Initialize port HW */
अटल पूर्णांक mvpp2_port_init(काष्ठा mvpp2_port *port)
अणु
	काष्ठा device *dev = port->dev->dev.parent;
	काष्ठा mvpp2 *priv = port->priv;
	काष्ठा mvpp2_txq_pcpu *txq_pcpu;
	अचिन्हित पूर्णांक thपढ़ो;
	पूर्णांक queue, err, val;

	/* Checks क्रम hardware स्थिरraपूर्णांकs */
	अगर (port->first_rxq + port->nrxqs >
	    MVPP2_MAX_PORTS * priv->max_port_rxqs)
		वापस -EINVAL;

	अगर (port->nrxqs > priv->max_port_rxqs || port->ntxqs > MVPP2_MAX_TXQ)
		वापस -EINVAL;

	/* Disable port */
	mvpp2_egress_disable(port);
	mvpp2_port_disable(port);

	अगर (mvpp2_is_xlg(port->phy_पूर्णांकerface)) अणु
		val = पढ़ोl(port->base + MVPP22_XLG_CTRL0_REG);
		val &= ~MVPP22_XLG_CTRL0_FORCE_LINK_PASS;
		val |= MVPP22_XLG_CTRL0_FORCE_LINK_DOWN;
		ग_लिखोl(val, port->base + MVPP22_XLG_CTRL0_REG);
	पूर्ण अन्यथा अणु
		val = पढ़ोl(port->base + MVPP2_GMAC_AUTONEG_CONFIG);
		val &= ~MVPP2_GMAC_FORCE_LINK_PASS;
		val |= MVPP2_GMAC_FORCE_LINK_DOWN;
		ग_लिखोl(val, port->base + MVPP2_GMAC_AUTONEG_CONFIG);
	पूर्ण

	port->tx_समय_coal = MVPP2_TXDONE_COAL_USEC;

	port->txqs = devm_kसुस्मृति(dev, port->ntxqs, माप(*port->txqs),
				  GFP_KERNEL);
	अगर (!port->txqs)
		वापस -ENOMEM;

	/* Associate physical Tx queues to this port and initialize.
	 * The mapping is predefined.
	 */
	क्रम (queue = 0; queue < port->ntxqs; queue++) अणु
		पूर्णांक queue_phy_id = mvpp2_txq_phys(port->id, queue);
		काष्ठा mvpp2_tx_queue *txq;

		txq = devm_kzalloc(dev, माप(*txq), GFP_KERNEL);
		अगर (!txq) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_percpu;
		पूर्ण

		txq->pcpu = alloc_percpu(काष्ठा mvpp2_txq_pcpu);
		अगर (!txq->pcpu) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_percpu;
		पूर्ण

		txq->id = queue_phy_id;
		txq->log_id = queue;
		txq->करोne_pkts_coal = MVPP2_TXDONE_COAL_PKTS_THRESH;
		क्रम (thपढ़ो = 0; thपढ़ो < priv->nthपढ़ोs; thपढ़ो++) अणु
			txq_pcpu = per_cpu_ptr(txq->pcpu, thपढ़ो);
			txq_pcpu->thपढ़ो = thपढ़ो;
		पूर्ण

		port->txqs[queue] = txq;
	पूर्ण

	port->rxqs = devm_kसुस्मृति(dev, port->nrxqs, माप(*port->rxqs),
				  GFP_KERNEL);
	अगर (!port->rxqs) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_percpu;
	पूर्ण

	/* Allocate and initialize Rx queue क्रम this port */
	क्रम (queue = 0; queue < port->nrxqs; queue++) अणु
		काष्ठा mvpp2_rx_queue *rxq;

		/* Map physical Rx queue to port's logical Rx queue */
		rxq = devm_kzalloc(dev, माप(*rxq), GFP_KERNEL);
		अगर (!rxq) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_percpu;
		पूर्ण
		/* Map this Rx queue to a physical queue */
		rxq->id = port->first_rxq + queue;
		rxq->port = port->id;
		rxq->logic_rxq = queue;

		port->rxqs[queue] = rxq;
	पूर्ण

	mvpp2_rx_irqs_setup(port);

	/* Create Rx descriptor rings */
	क्रम (queue = 0; queue < port->nrxqs; queue++) अणु
		काष्ठा mvpp2_rx_queue *rxq = port->rxqs[queue];

		rxq->size = port->rx_ring_size;
		rxq->pkts_coal = MVPP2_RX_COAL_PKTS;
		rxq->समय_coal = MVPP2_RX_COAL_USEC;
	पूर्ण

	mvpp2_ingress_disable(port);

	/* Port शेष configuration */
	mvpp2_शेषs_set(port);

	/* Port's classअगरier configuration */
	mvpp2_cls_oversize_rxq_set(port);
	mvpp2_cls_port_config(port);

	अगर (mvpp22_rss_is_supported(port))
		mvpp22_port_rss_init(port);

	/* Provide an initial Rx packet size */
	port->pkt_size = MVPP2_RX_PKT_SIZE(port->dev->mtu);

	/* Initialize pools क्रम swf */
	err = mvpp2_swf_bm_pool_init(port);
	अगर (err)
		जाओ err_मुक्त_percpu;

	/* Clear all port stats */
	mvpp2_पढ़ो_stats(port);
	स_रखो(port->ethtool_stats, 0,
	       MVPP2_N_ETHTOOL_STATS(port->ntxqs, port->nrxqs) * माप(u64));

	वापस 0;

err_मुक्त_percpu:
	क्रम (queue = 0; queue < port->ntxqs; queue++) अणु
		अगर (!port->txqs[queue])
			जारी;
		मुक्त_percpu(port->txqs[queue]->pcpu);
	पूर्ण
	वापस err;
पूर्ण

अटल bool mvpp22_port_has_legacy_tx_irqs(काष्ठा device_node *port_node,
					   अचिन्हित दीर्घ *flags)
अणु
	अक्षर *irqs[5] = अणु "rx-shared", "tx-cpu0", "tx-cpu1", "tx-cpu2",
			  "tx-cpu3" पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++)
		अगर (of_property_match_string(port_node, "interrupt-names",
					     irqs[i]) < 0)
			वापस false;

	*flags |= MVPP2_F_DT_COMPAT;
	वापस true;
पूर्ण

/* Checks अगर the port dt description has the required Tx पूर्णांकerrupts:
 * - PPv2.1: there are no such पूर्णांकerrupts.
 * - PPv2.2 and PPv2.3:
 *   - The old DTs have: "rx-shared", "tx-cpuX" with X in [0...3]
 *   - The new ones have: "hifX" with X in [0..8]
 *
 * All those variants are supported to keep the backward compatibility.
 */
अटल bool mvpp2_port_has_irqs(काष्ठा mvpp2 *priv,
				काष्ठा device_node *port_node,
				अचिन्हित दीर्घ *flags)
अणु
	अक्षर name[5];
	पूर्णांक i;

	/* ACPI */
	अगर (!port_node)
		वापस true;

	अगर (priv->hw_version == MVPP21)
		वापस false;

	अगर (mvpp22_port_has_legacy_tx_irqs(port_node, flags))
		वापस true;

	क्रम (i = 0; i < MVPP2_MAX_THREADS; i++) अणु
		snम_लिखो(name, 5, "hif%d", i);
		अगर (of_property_match_string(port_node, "interrupt-names",
					     name) < 0)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम mvpp2_port_copy_mac_addr(काष्ठा net_device *dev, काष्ठा mvpp2 *priv,
				     काष्ठा fwnode_handle *fwnode,
				     अक्षर **mac_from)
अणु
	काष्ठा mvpp2_port *port = netdev_priv(dev);
	अक्षर hw_mac_addr[ETH_ALEN] = अणु0पूर्ण;
	अक्षर fw_mac_addr[ETH_ALEN];

	अगर (fwnode_get_mac_address(fwnode, fw_mac_addr, ETH_ALEN)) अणु
		*mac_from = "firmware node";
		ether_addr_copy(dev->dev_addr, fw_mac_addr);
		वापस;
	पूर्ण

	अगर (priv->hw_version == MVPP21) अणु
		mvpp21_get_mac_address(port, hw_mac_addr);
		अगर (is_valid_ether_addr(hw_mac_addr)) अणु
			*mac_from = "hardware";
			ether_addr_copy(dev->dev_addr, hw_mac_addr);
			वापस;
		पूर्ण
	पूर्ण

	*mac_from = "random";
	eth_hw_addr_अक्रमom(dev);
पूर्ण

अटल काष्ठा mvpp2_port *mvpp2_phylink_to_port(काष्ठा phylink_config *config)
अणु
	वापस container_of(config, काष्ठा mvpp2_port, phylink_config);
पूर्ण

अटल काष्ठा mvpp2_port *mvpp2_pcs_to_port(काष्ठा phylink_pcs *pcs)
अणु
	वापस container_of(pcs, काष्ठा mvpp2_port, phylink_pcs);
पूर्ण

अटल व्योम mvpp2_xlg_pcs_get_state(काष्ठा phylink_pcs *pcs,
				    काष्ठा phylink_link_state *state)
अणु
	काष्ठा mvpp2_port *port = mvpp2_pcs_to_port(pcs);
	u32 val;

	state->speed = SPEED_10000;
	state->duplex = 1;
	state->an_complete = 1;

	val = पढ़ोl(port->base + MVPP22_XLG_STATUS);
	state->link = !!(val & MVPP22_XLG_STATUS_LINK_UP);

	state->छोड़ो = 0;
	val = पढ़ोl(port->base + MVPP22_XLG_CTRL0_REG);
	अगर (val & MVPP22_XLG_CTRL0_TX_FLOW_CTRL_EN)
		state->छोड़ो |= MLO_PAUSE_TX;
	अगर (val & MVPP22_XLG_CTRL0_RX_FLOW_CTRL_EN)
		state->छोड़ो |= MLO_PAUSE_RX;
पूर्ण

अटल पूर्णांक mvpp2_xlg_pcs_config(काष्ठा phylink_pcs *pcs,
				अचिन्हित पूर्णांक mode,
				phy_पूर्णांकerface_t पूर्णांकerface,
				स्थिर अचिन्हित दीर्घ *advertising,
				bool permit_छोड़ो_to_mac)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phylink_pcs_ops mvpp2_phylink_xlg_pcs_ops = अणु
	.pcs_get_state = mvpp2_xlg_pcs_get_state,
	.pcs_config = mvpp2_xlg_pcs_config,
पूर्ण;

अटल व्योम mvpp2_gmac_pcs_get_state(काष्ठा phylink_pcs *pcs,
				     काष्ठा phylink_link_state *state)
अणु
	काष्ठा mvpp2_port *port = mvpp2_pcs_to_port(pcs);
	u32 val;

	val = पढ़ोl(port->base + MVPP2_GMAC_STATUS0);

	state->an_complete = !!(val & MVPP2_GMAC_STATUS0_AN_COMPLETE);
	state->link = !!(val & MVPP2_GMAC_STATUS0_LINK_UP);
	state->duplex = !!(val & MVPP2_GMAC_STATUS0_FULL_DUPLEX);

	चयन (port->phy_पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_1000BASEX:
		state->speed = SPEED_1000;
		अवरोध;
	हाल PHY_INTERFACE_MODE_2500BASEX:
		state->speed = SPEED_2500;
		अवरोध;
	शेष:
		अगर (val & MVPP2_GMAC_STATUS0_GMII_SPEED)
			state->speed = SPEED_1000;
		अन्यथा अगर (val & MVPP2_GMAC_STATUS0_MII_SPEED)
			state->speed = SPEED_100;
		अन्यथा
			state->speed = SPEED_10;
	पूर्ण

	state->छोड़ो = 0;
	अगर (val & MVPP2_GMAC_STATUS0_RX_PAUSE)
		state->छोड़ो |= MLO_PAUSE_RX;
	अगर (val & MVPP2_GMAC_STATUS0_TX_PAUSE)
		state->छोड़ो |= MLO_PAUSE_TX;
पूर्ण

अटल पूर्णांक mvpp2_gmac_pcs_config(काष्ठा phylink_pcs *pcs, अचिन्हित पूर्णांक mode,
				 phy_पूर्णांकerface_t पूर्णांकerface,
				 स्थिर अचिन्हित दीर्घ *advertising,
				 bool permit_छोड़ो_to_mac)
अणु
	काष्ठा mvpp2_port *port = mvpp2_pcs_to_port(pcs);
	u32 mask, val, an, old_an, changed;

	mask = MVPP2_GMAC_IN_BAND_AUTONEG_BYPASS |
	       MVPP2_GMAC_IN_BAND_AUTONEG |
	       MVPP2_GMAC_AN_SPEED_EN |
	       MVPP2_GMAC_FLOW_CTRL_AUTONEG |
	       MVPP2_GMAC_AN_DUPLEX_EN;

	अगर (phylink_स्वतःneg_inband(mode)) अणु
		mask |= MVPP2_GMAC_CONFIG_MII_SPEED |
			MVPP2_GMAC_CONFIG_GMII_SPEED |
			MVPP2_GMAC_CONFIG_FULL_DUPLEX;
		val = MVPP2_GMAC_IN_BAND_AUTONEG;

		अगर (पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
			/* SGMII mode receives the speed and duplex from PHY */
			val |= MVPP2_GMAC_AN_SPEED_EN |
			       MVPP2_GMAC_AN_DUPLEX_EN;
		पूर्ण अन्यथा अणु
			/* 802.3z mode has fixed speed and duplex */
			val |= MVPP2_GMAC_CONFIG_GMII_SPEED |
			       MVPP2_GMAC_CONFIG_FULL_DUPLEX;

			/* The FLOW_CTRL_AUTONEG bit selects either the hardware
			 * स्वतःmatically or the bits in MVPP22_GMAC_CTRL_4_REG
			 * manually controls the GMAC छोड़ो modes.
			 */
			अगर (permit_छोड़ो_to_mac)
				val |= MVPP2_GMAC_FLOW_CTRL_AUTONEG;

			/* Configure advertisement bits */
			mask |= MVPP2_GMAC_FC_ADV_EN | MVPP2_GMAC_FC_ADV_ASM_EN;
			अगर (phylink_test(advertising, Pause))
				val |= MVPP2_GMAC_FC_ADV_EN;
			अगर (phylink_test(advertising, Asym_Pause))
				val |= MVPP2_GMAC_FC_ADV_ASM_EN;
		पूर्ण
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण

	old_an = an = पढ़ोl(port->base + MVPP2_GMAC_AUTONEG_CONFIG);
	an = (an & ~mask) | val;
	changed = an ^ old_an;
	अगर (changed)
		ग_लिखोl(an, port->base + MVPP2_GMAC_AUTONEG_CONFIG);

	/* We are only पूर्णांकerested in the advertisement bits changing */
	वापस changed & (MVPP2_GMAC_FC_ADV_EN | MVPP2_GMAC_FC_ADV_ASM_EN);
पूर्ण

अटल व्योम mvpp2_gmac_pcs_an_restart(काष्ठा phylink_pcs *pcs)
अणु
	काष्ठा mvpp2_port *port = mvpp2_pcs_to_port(pcs);
	u32 val = पढ़ोl(port->base + MVPP2_GMAC_AUTONEG_CONFIG);

	ग_लिखोl(val | MVPP2_GMAC_IN_BAND_RESTART_AN,
	       port->base + MVPP2_GMAC_AUTONEG_CONFIG);
	ग_लिखोl(val & ~MVPP2_GMAC_IN_BAND_RESTART_AN,
	       port->base + MVPP2_GMAC_AUTONEG_CONFIG);
पूर्ण

अटल स्थिर काष्ठा phylink_pcs_ops mvpp2_phylink_gmac_pcs_ops = अणु
	.pcs_get_state = mvpp2_gmac_pcs_get_state,
	.pcs_config = mvpp2_gmac_pcs_config,
	.pcs_an_restart = mvpp2_gmac_pcs_an_restart,
पूर्ण;

अटल व्योम mvpp2_phylink_validate(काष्ठा phylink_config *config,
				   अचिन्हित दीर्घ *supported,
				   काष्ठा phylink_link_state *state)
अणु
	काष्ठा mvpp2_port *port = mvpp2_phylink_to_port(config);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	/* Invalid combinations */
	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_10GBASER:
	हाल PHY_INTERFACE_MODE_XAUI:
		अगर (!mvpp2_port_supports_xlg(port))
			जाओ empty_set;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		अगर (!mvpp2_port_supports_rgmii(port))
			जाओ empty_set;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	phylink_set(mask, Autoneg);
	phylink_set_port_modes(mask);

	अगर (port->priv->global_tx_fc) अणु
		phylink_set(mask, Pause);
		phylink_set(mask, Asym_Pause);
	पूर्ण

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_10GBASER:
	हाल PHY_INTERFACE_MODE_XAUI:
	हाल PHY_INTERFACE_MODE_NA:
		अगर (mvpp2_port_supports_xlg(port)) अणु
			phylink_set(mask, 10000baseT_Full);
			phylink_set(mask, 10000baseCR_Full);
			phylink_set(mask, 10000baseSR_Full);
			phylink_set(mask, 10000baseLR_Full);
			phylink_set(mask, 10000baseLRM_Full);
			phylink_set(mask, 10000baseER_Full);
			phylink_set(mask, 10000baseKR_Full);
		पूर्ण
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA)
			अवरोध;
		fallthrough;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
	हाल PHY_INTERFACE_MODE_SGMII:
		phylink_set(mask, 10baseT_Half);
		phylink_set(mask, 10baseT_Full);
		phylink_set(mask, 100baseT_Half);
		phylink_set(mask, 100baseT_Full);
		phylink_set(mask, 1000baseT_Full);
		phylink_set(mask, 1000baseX_Full);
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA)
			अवरोध;
		fallthrough;
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_2500BASEX:
		अगर (port->comphy ||
		    state->पूर्णांकerface != PHY_INTERFACE_MODE_2500BASEX) अणु
			phylink_set(mask, 1000baseT_Full);
			phylink_set(mask, 1000baseX_Full);
		पूर्ण
		अगर (port->comphy ||
		    state->पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX) अणु
			phylink_set(mask, 2500baseT_Full);
			phylink_set(mask, 2500baseX_Full);
		पूर्ण
		अवरोध;
	शेष:
		जाओ empty_set;
	पूर्ण

	biपंचांगap_and(supported, supported, mask, __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);

	phylink_helper_basex_speed(state);
	वापस;

empty_set:
	biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल व्योम mvpp2_xlg_config(काष्ठा mvpp2_port *port, अचिन्हित पूर्णांक mode,
			     स्थिर काष्ठा phylink_link_state *state)
अणु
	u32 val;

	mvpp2_modअगरy(port->base + MVPP22_XLG_CTRL0_REG,
		     MVPP22_XLG_CTRL0_MAC_RESET_DIS,
		     MVPP22_XLG_CTRL0_MAC_RESET_DIS);
	mvpp2_modअगरy(port->base + MVPP22_XLG_CTRL4_REG,
		     MVPP22_XLG_CTRL4_MACMODSELECT_GMAC |
		     MVPP22_XLG_CTRL4_EN_IDLE_CHECK |
		     MVPP22_XLG_CTRL4_FWD_FC | MVPP22_XLG_CTRL4_FWD_PFC,
		     MVPP22_XLG_CTRL4_FWD_FC | MVPP22_XLG_CTRL4_FWD_PFC);

	/* Wait क्रम reset to deनिश्चित */
	करो अणु
		val = पढ़ोl(port->base + MVPP22_XLG_CTRL0_REG);
	पूर्ण जबतक (!(val & MVPP22_XLG_CTRL0_MAC_RESET_DIS));
पूर्ण

अटल व्योम mvpp2_gmac_config(काष्ठा mvpp2_port *port, अचिन्हित पूर्णांक mode,
			      स्थिर काष्ठा phylink_link_state *state)
अणु
	u32 old_ctrl0, ctrl0;
	u32 old_ctrl2, ctrl2;
	u32 old_ctrl4, ctrl4;

	old_ctrl0 = ctrl0 = पढ़ोl(port->base + MVPP2_GMAC_CTRL_0_REG);
	old_ctrl2 = ctrl2 = पढ़ोl(port->base + MVPP2_GMAC_CTRL_2_REG);
	old_ctrl4 = ctrl4 = पढ़ोl(port->base + MVPP22_GMAC_CTRL_4_REG);

	ctrl0 &= ~MVPP2_GMAC_PORT_TYPE_MASK;
	ctrl2 &= ~(MVPP2_GMAC_INBAND_AN_MASK | MVPP2_GMAC_PCS_ENABLE_MASK | MVPP2_GMAC_FLOW_CTRL_MASK);

	/* Configure port type */
	अगर (phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface)) अणु
		ctrl2 |= MVPP2_GMAC_PCS_ENABLE_MASK;
		ctrl4 &= ~MVPP22_CTRL4_EXT_PIN_GMII_SEL;
		ctrl4 |= MVPP22_CTRL4_SYNC_BYPASS_DIS |
			 MVPP22_CTRL4_DP_CLK_SEL |
			 MVPP22_CTRL4_QSGMII_BYPASS_ACTIVE;
	पूर्ण अन्यथा अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		ctrl2 |= MVPP2_GMAC_PCS_ENABLE_MASK | MVPP2_GMAC_INBAND_AN_MASK;
		ctrl4 &= ~MVPP22_CTRL4_EXT_PIN_GMII_SEL;
		ctrl4 |= MVPP22_CTRL4_SYNC_BYPASS_DIS |
			 MVPP22_CTRL4_DP_CLK_SEL |
			 MVPP22_CTRL4_QSGMII_BYPASS_ACTIVE;
	पूर्ण अन्यथा अगर (phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface)) अणु
		ctrl4 &= ~MVPP22_CTRL4_DP_CLK_SEL;
		ctrl4 |= MVPP22_CTRL4_EXT_PIN_GMII_SEL |
			 MVPP22_CTRL4_SYNC_BYPASS_DIS |
			 MVPP22_CTRL4_QSGMII_BYPASS_ACTIVE;
	पूर्ण

	/* Configure negotiation style */
	अगर (!phylink_स्वतःneg_inband(mode)) अणु
		/* Phy or fixed speed - no in-band AN, nothing to करो, leave the
		 * configured speed, duplex and flow control as-is.
		 */
	पूर्ण अन्यथा अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		/* SGMII in-band mode receives the speed and duplex from
		 * the PHY. Flow control inक्रमmation is not received. */
	पूर्ण अन्यथा अगर (phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface)) अणु
		/* 1000BaseX and 2500BaseX ports cannot negotiate speed nor can
		 * they negotiate duplex: they are always operating with a fixed
		 * speed of 1000/2500Mbps in full duplex, so क्रमce 1000/2500
		 * speed and full duplex here.
		 */
		ctrl0 |= MVPP2_GMAC_PORT_TYPE_MASK;
	पूर्ण

	अगर (old_ctrl0 != ctrl0)
		ग_लिखोl(ctrl0, port->base + MVPP2_GMAC_CTRL_0_REG);
	अगर (old_ctrl2 != ctrl2)
		ग_लिखोl(ctrl2, port->base + MVPP2_GMAC_CTRL_2_REG);
	अगर (old_ctrl4 != ctrl4)
		ग_लिखोl(ctrl4, port->base + MVPP22_GMAC_CTRL_4_REG);
पूर्ण

अटल पूर्णांक mvpp2__mac_prepare(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			      phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mvpp2_port *port = mvpp2_phylink_to_port(config);

	/* Check क्रम invalid configuration */
	अगर (mvpp2_is_xlg(पूर्णांकerface) && port->gop_id != 0) अणु
		netdev_err(port->dev, "Invalid mode on %s\n", port->dev->name);
		वापस -EINVAL;
	पूर्ण

	अगर (port->phy_पूर्णांकerface != पूर्णांकerface ||
	    phylink_स्वतःneg_inband(mode)) अणु
		/* Force the link करोwn when changing the पूर्णांकerface or अगर in
		 * in-band mode to ensure we करो not change the configuration
		 * जबतक the hardware is indicating link is up. We क्रमce both
		 * XLG and GMAC करोwn to ensure that they're both in a known
		 * state.
		 */
		mvpp2_modअगरy(port->base + MVPP2_GMAC_AUTONEG_CONFIG,
			     MVPP2_GMAC_FORCE_LINK_PASS |
			     MVPP2_GMAC_FORCE_LINK_DOWN,
			     MVPP2_GMAC_FORCE_LINK_DOWN);

		अगर (mvpp2_port_supports_xlg(port))
			mvpp2_modअगरy(port->base + MVPP22_XLG_CTRL0_REG,
				     MVPP22_XLG_CTRL0_FORCE_LINK_PASS |
				     MVPP22_XLG_CTRL0_FORCE_LINK_DOWN,
				     MVPP22_XLG_CTRL0_FORCE_LINK_DOWN);
	पूर्ण

	/* Make sure the port is disabled when reconfiguring the mode */
	mvpp2_port_disable(port);

	अगर (port->phy_पूर्णांकerface != पूर्णांकerface) अणु
		/* Place GMAC पूर्णांकo reset */
		mvpp2_modअगरy(port->base + MVPP2_GMAC_CTRL_2_REG,
			     MVPP2_GMAC_PORT_RESET_MASK,
			     MVPP2_GMAC_PORT_RESET_MASK);

		अगर (port->priv->hw_version >= MVPP22) अणु
			mvpp22_gop_mask_irq(port);

			phy_घातer_off(port->comphy);
		पूर्ण
	पूर्ण

	/* Select the appropriate PCS operations depending on the
	 * configured पूर्णांकerface mode. We will only चयन to a mode
	 * that the validate() checks have alपढ़ोy passed.
	 */
	अगर (mvpp2_is_xlg(पूर्णांकerface))
		port->phylink_pcs.ops = &mvpp2_phylink_xlg_pcs_ops;
	अन्यथा
		port->phylink_pcs.ops = &mvpp2_phylink_gmac_pcs_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_mac_prepare(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			     phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mvpp2_port *port = mvpp2_phylink_to_port(config);
	पूर्णांक ret;

	ret = mvpp2__mac_prepare(config, mode, पूर्णांकerface);
	अगर (ret == 0)
		phylink_set_pcs(port->phylink, &port->phylink_pcs);

	वापस ret;
पूर्ण

अटल व्योम mvpp2_mac_config(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			     स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा mvpp2_port *port = mvpp2_phylink_to_port(config);

	/* mac (re)configuration */
	अगर (mvpp2_is_xlg(state->पूर्णांकerface))
		mvpp2_xlg_config(port, mode, state);
	अन्यथा अगर (phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface) ||
		 phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface) ||
		 state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
		mvpp2_gmac_config(port, mode, state);

	अगर (port->priv->hw_version == MVPP21 && port->flags & MVPP2_F_LOOPBACK)
		mvpp2_port_loopback_set(port, state);
पूर्ण

अटल पूर्णांक mvpp2_mac_finish(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			    phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mvpp2_port *port = mvpp2_phylink_to_port(config);

	अगर (port->priv->hw_version >= MVPP22 &&
	    port->phy_पूर्णांकerface != पूर्णांकerface) अणु
		port->phy_पूर्णांकerface = पूर्णांकerface;

		/* Reconfigure the serdes lanes */
		mvpp22_mode_reconfigure(port);

		/* Unmask पूर्णांकerrupts */
		mvpp22_gop_unmask_irq(port);
	पूर्ण

	अगर (!mvpp2_is_xlg(पूर्णांकerface)) अणु
		/* Release GMAC reset and रुको */
		mvpp2_modअगरy(port->base + MVPP2_GMAC_CTRL_2_REG,
			     MVPP2_GMAC_PORT_RESET_MASK, 0);

		जबतक (पढ़ोl(port->base + MVPP2_GMAC_CTRL_2_REG) &
		       MVPP2_GMAC_PORT_RESET_MASK)
			जारी;
	पूर्ण

	mvpp2_port_enable(port);

	/* Allow the link to come up अगर in in-band mode, otherwise the
	 * link is क्रमced via mac_link_करोwn()/mac_link_up()
	 */
	अगर (phylink_स्वतःneg_inband(mode)) अणु
		अगर (mvpp2_is_xlg(पूर्णांकerface))
			mvpp2_modअगरy(port->base + MVPP22_XLG_CTRL0_REG,
				     MVPP22_XLG_CTRL0_FORCE_LINK_PASS |
				     MVPP22_XLG_CTRL0_FORCE_LINK_DOWN, 0);
		अन्यथा
			mvpp2_modअगरy(port->base + MVPP2_GMAC_AUTONEG_CONFIG,
				     MVPP2_GMAC_FORCE_LINK_PASS |
				     MVPP2_GMAC_FORCE_LINK_DOWN, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mvpp2_mac_link_up(काष्ठा phylink_config *config,
			      काष्ठा phy_device *phy,
			      अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
			      पूर्णांक speed, पूर्णांक duplex,
			      bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा mvpp2_port *port = mvpp2_phylink_to_port(config);
	u32 val;
	पूर्णांक i;

	अगर (mvpp2_is_xlg(पूर्णांकerface)) अणु
		अगर (!phylink_स्वतःneg_inband(mode)) अणु
			val = MVPP22_XLG_CTRL0_FORCE_LINK_PASS;
			अगर (tx_छोड़ो)
				val |= MVPP22_XLG_CTRL0_TX_FLOW_CTRL_EN;
			अगर (rx_छोड़ो)
				val |= MVPP22_XLG_CTRL0_RX_FLOW_CTRL_EN;

			mvpp2_modअगरy(port->base + MVPP22_XLG_CTRL0_REG,
				     MVPP22_XLG_CTRL0_FORCE_LINK_DOWN |
				     MVPP22_XLG_CTRL0_FORCE_LINK_PASS |
				     MVPP22_XLG_CTRL0_TX_FLOW_CTRL_EN |
				     MVPP22_XLG_CTRL0_RX_FLOW_CTRL_EN, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!phylink_स्वतःneg_inband(mode)) अणु
			val = MVPP2_GMAC_FORCE_LINK_PASS;

			अगर (speed == SPEED_1000 || speed == SPEED_2500)
				val |= MVPP2_GMAC_CONFIG_GMII_SPEED;
			अन्यथा अगर (speed == SPEED_100)
				val |= MVPP2_GMAC_CONFIG_MII_SPEED;

			अगर (duplex == DUPLEX_FULL)
				val |= MVPP2_GMAC_CONFIG_FULL_DUPLEX;

			mvpp2_modअगरy(port->base + MVPP2_GMAC_AUTONEG_CONFIG,
				     MVPP2_GMAC_FORCE_LINK_DOWN |
				     MVPP2_GMAC_FORCE_LINK_PASS |
				     MVPP2_GMAC_CONFIG_MII_SPEED |
				     MVPP2_GMAC_CONFIG_GMII_SPEED |
				     MVPP2_GMAC_CONFIG_FULL_DUPLEX, val);
		पूर्ण

		/* We can always update the flow control enable bits;
		 * these will only be effective अगर flow control AN
		 * (MVPP2_GMAC_FLOW_CTRL_AUTONEG) is disabled.
		 */
		val = 0;
		अगर (tx_छोड़ो)
			val |= MVPP22_CTRL4_TX_FC_EN;
		अगर (rx_छोड़ो)
			val |= MVPP22_CTRL4_RX_FC_EN;

		mvpp2_modअगरy(port->base + MVPP22_GMAC_CTRL_4_REG,
			     MVPP22_CTRL4_RX_FC_EN | MVPP22_CTRL4_TX_FC_EN,
			     val);
	पूर्ण

	अगर (port->priv->global_tx_fc) अणु
		port->tx_fc = tx_छोड़ो;
		अगर (tx_छोड़ो)
			mvpp2_rxq_enable_fc(port);
		अन्यथा
			mvpp2_rxq_disable_fc(port);
		अगर (port->priv->percpu_pools) अणु
			क्रम (i = 0; i < port->nrxqs; i++)
				mvpp2_bm_pool_update_fc(port, &port->priv->bm_pools[i], tx_छोड़ो);
		पूर्ण अन्यथा अणु
			mvpp2_bm_pool_update_fc(port, port->pool_दीर्घ, tx_छोड़ो);
			mvpp2_bm_pool_update_fc(port, port->pool_लघु, tx_छोड़ो);
		पूर्ण
		अगर (port->priv->hw_version == MVPP23)
			mvpp23_rx_fअगरo_fc_en(port->priv, port->id, tx_छोड़ो);
	पूर्ण

	mvpp2_port_enable(port);

	mvpp2_egress_enable(port);
	mvpp2_ingress_enable(port);
	netअगर_tx_wake_all_queues(port->dev);
पूर्ण

अटल व्योम mvpp2_mac_link_करोwn(काष्ठा phylink_config *config,
				अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mvpp2_port *port = mvpp2_phylink_to_port(config);
	u32 val;

	अगर (!phylink_स्वतःneg_inband(mode)) अणु
		अगर (mvpp2_is_xlg(पूर्णांकerface)) अणु
			val = पढ़ोl(port->base + MVPP22_XLG_CTRL0_REG);
			val &= ~MVPP22_XLG_CTRL0_FORCE_LINK_PASS;
			val |= MVPP22_XLG_CTRL0_FORCE_LINK_DOWN;
			ग_लिखोl(val, port->base + MVPP22_XLG_CTRL0_REG);
		पूर्ण अन्यथा अणु
			val = पढ़ोl(port->base + MVPP2_GMAC_AUTONEG_CONFIG);
			val &= ~MVPP2_GMAC_FORCE_LINK_PASS;
			val |= MVPP2_GMAC_FORCE_LINK_DOWN;
			ग_लिखोl(val, port->base + MVPP2_GMAC_AUTONEG_CONFIG);
		पूर्ण
	पूर्ण

	netअगर_tx_stop_all_queues(port->dev);
	mvpp2_egress_disable(port);
	mvpp2_ingress_disable(port);

	mvpp2_port_disable(port);
पूर्ण

अटल स्थिर काष्ठा phylink_mac_ops mvpp2_phylink_ops = अणु
	.validate = mvpp2_phylink_validate,
	.mac_prepare = mvpp2_mac_prepare,
	.mac_config = mvpp2_mac_config,
	.mac_finish = mvpp2_mac_finish,
	.mac_link_up = mvpp2_mac_link_up,
	.mac_link_करोwn = mvpp2_mac_link_करोwn,
पूर्ण;

/* Work-around क्रम ACPI */
अटल व्योम mvpp2_acpi_start(काष्ठा mvpp2_port *port)
अणु
	/* Phylink isn't used as of now क्रम ACPI, so the MAC has to be
	 * configured manually when the पूर्णांकerface is started. This will
	 * be हटाओd as soon as the phylink ACPI support lands in.
	 */
	काष्ठा phylink_link_state state = अणु
		.पूर्णांकerface = port->phy_पूर्णांकerface,
	पूर्ण;
	mvpp2__mac_prepare(&port->phylink_config, MLO_AN_INBAND,
			   port->phy_पूर्णांकerface);
	mvpp2_mac_config(&port->phylink_config, MLO_AN_INBAND, &state);
	port->phylink_pcs.ops->pcs_config(&port->phylink_pcs, MLO_AN_INBAND,
					  port->phy_पूर्णांकerface,
					  state.advertising, false);
	mvpp2_mac_finish(&port->phylink_config, MLO_AN_INBAND,
			 port->phy_पूर्णांकerface);
	mvpp2_mac_link_up(&port->phylink_config, शून्य,
			  MLO_AN_INBAND, port->phy_पूर्णांकerface,
			  SPEED_UNKNOWN, DUPLEX_UNKNOWN, false, false);
पूर्ण

/* Ports initialization */
अटल पूर्णांक mvpp2_port_probe(काष्ठा platक्रमm_device *pdev,
			    काष्ठा fwnode_handle *port_fwnode,
			    काष्ठा mvpp2 *priv)
अणु
	काष्ठा phy *comphy = शून्य;
	काष्ठा mvpp2_port *port;
	काष्ठा mvpp2_port_pcpu *port_pcpu;
	काष्ठा device_node *port_node = to_of_node(port_fwnode);
	netdev_features_t features;
	काष्ठा net_device *dev;
	काष्ठा phylink *phylink;
	अक्षर *mac_from = "";
	अचिन्हित पूर्णांक ntxqs, nrxqs, thपढ़ो;
	अचिन्हित दीर्घ flags = 0;
	bool has_tx_irqs;
	u32 id;
	पूर्णांक phy_mode;
	पूर्णांक err, i;

	has_tx_irqs = mvpp2_port_has_irqs(priv, port_node, &flags);
	अगर (!has_tx_irqs && queue_mode == MVPP2_QDIST_MULTI_MODE) अणु
		dev_err(&pdev->dev,
			"not enough IRQs to support multi queue mode\n");
		वापस -EINVAL;
	पूर्ण

	ntxqs = MVPP2_MAX_TXQ;
	nrxqs = mvpp2_get_nrxqs(priv);

	dev = alloc_etherdev_mqs(माप(*port), ntxqs, nrxqs);
	अगर (!dev)
		वापस -ENOMEM;

	phy_mode = fwnode_get_phy_mode(port_fwnode);
	अगर (phy_mode < 0) अणु
		dev_err(&pdev->dev, "incorrect phy mode\n");
		err = phy_mode;
		जाओ err_मुक्त_netdev;
	पूर्ण

	/*
	 * Reग_लिखो 10GBASE-KR to 10GBASE-R क्रम compatibility with existing DT.
	 * Existing usage of 10GBASE-KR is not correct; no backplane
	 * negotiation is करोne, and this driver करोes not actually support
	 * 10GBASE-KR.
	 */
	अगर (phy_mode == PHY_INTERFACE_MODE_10GKR)
		phy_mode = PHY_INTERFACE_MODE_10GBASER;

	अगर (port_node) अणु
		comphy = devm_of_phy_get(&pdev->dev, port_node, शून्य);
		अगर (IS_ERR(comphy)) अणु
			अगर (PTR_ERR(comphy) == -EPROBE_DEFER) अणु
				err = -EPROBE_DEFER;
				जाओ err_मुक्त_netdev;
			पूर्ण
			comphy = शून्य;
		पूर्ण
	पूर्ण

	अगर (fwnode_property_पढ़ो_u32(port_fwnode, "port-id", &id)) अणु
		err = -EINVAL;
		dev_err(&pdev->dev, "missing port-id value\n");
		जाओ err_मुक्त_netdev;
	पूर्ण

	dev->tx_queue_len = MVPP2_MAX_TXD_MAX;
	dev->watchकरोg_समयo = 5 * HZ;
	dev->netdev_ops = &mvpp2_netdev_ops;
	dev->ethtool_ops = &mvpp2_eth_tool_ops;

	port = netdev_priv(dev);
	port->dev = dev;
	port->fwnode = port_fwnode;
	port->has_phy = !!of_find_property(port_node, "phy", शून्य);
	port->ntxqs = ntxqs;
	port->nrxqs = nrxqs;
	port->priv = priv;
	port->has_tx_irqs = has_tx_irqs;
	port->flags = flags;

	err = mvpp2_queue_vectors_init(port, port_node);
	अगर (err)
		जाओ err_मुक्त_netdev;

	अगर (port_node)
		port->port_irq = of_irq_get_byname(port_node, "link");
	अन्यथा
		port->port_irq = fwnode_irq_get(port_fwnode, port->nqvecs + 1);
	अगर (port->port_irq == -EPROBE_DEFER) अणु
		err = -EPROBE_DEFER;
		जाओ err_deinit_qvecs;
	पूर्ण
	अगर (port->port_irq <= 0)
		/* the link irq is optional */
		port->port_irq = 0;

	अगर (fwnode_property_पढ़ो_bool(port_fwnode, "marvell,loopback"))
		port->flags |= MVPP2_F_LOOPBACK;

	port->id = id;
	अगर (priv->hw_version == MVPP21)
		port->first_rxq = port->id * port->nrxqs;
	अन्यथा
		port->first_rxq = port->id * priv->max_port_rxqs;

	port->of_node = port_node;
	port->phy_पूर्णांकerface = phy_mode;
	port->comphy = comphy;

	अगर (priv->hw_version == MVPP21) अणु
		port->base = devm_platक्रमm_ioremap_resource(pdev, 2 + id);
		अगर (IS_ERR(port->base)) अणु
			err = PTR_ERR(port->base);
			जाओ err_मुक्त_irq;
		पूर्ण

		port->stats_base = port->priv->lms_base +
				   MVPP21_MIB_COUNTERS_OFFSET +
				   port->gop_id * MVPP21_MIB_COUNTERS_PORT_SZ;
	पूर्ण अन्यथा अणु
		अगर (fwnode_property_पढ़ो_u32(port_fwnode, "gop-port-id",
					     &port->gop_id)) अणु
			err = -EINVAL;
			dev_err(&pdev->dev, "missing gop-port-id value\n");
			जाओ err_deinit_qvecs;
		पूर्ण

		port->base = priv->अगरace_base + MVPP22_GMAC_BASE(port->gop_id);
		port->stats_base = port->priv->अगरace_base +
				   MVPP22_MIB_COUNTERS_OFFSET +
				   port->gop_id * MVPP22_MIB_COUNTERS_PORT_SZ;

		/* We may want a property to describe whether we should use
		 * MAC hardware बारtamping.
		 */
		अगर (priv->tai)
			port->hwtstamp = true;
	पूर्ण

	/* Alloc per-cpu and ethtool stats */
	port->stats = netdev_alloc_pcpu_stats(काष्ठा mvpp2_pcpu_stats);
	अगर (!port->stats) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_irq;
	पूर्ण

	port->ethtool_stats = devm_kसुस्मृति(&pdev->dev,
					   MVPP2_N_ETHTOOL_STATS(ntxqs, nrxqs),
					   माप(u64), GFP_KERNEL);
	अगर (!port->ethtool_stats) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_stats;
	पूर्ण

	mutex_init(&port->gather_stats_lock);
	INIT_DELAYED_WORK(&port->stats_work, mvpp2_gather_hw_statistics);

	mvpp2_port_copy_mac_addr(dev, priv, port_fwnode, &mac_from);

	port->tx_ring_size = MVPP2_MAX_TXD_DFLT;
	port->rx_ring_size = MVPP2_MAX_RXD_DFLT;
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = mvpp2_port_init(port);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to init port %d\n", id);
		जाओ err_मुक्त_stats;
	पूर्ण

	mvpp2_port_periodic_xon_disable(port);

	mvpp2_mac_reset_निश्चित(port);
	mvpp22_pcs_reset_निश्चित(port);

	port->pcpu = alloc_percpu(काष्ठा mvpp2_port_pcpu);
	अगर (!port->pcpu) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_txq_pcpu;
	पूर्ण

	अगर (!port->has_tx_irqs) अणु
		क्रम (thपढ़ो = 0; thपढ़ो < priv->nthपढ़ोs; thपढ़ो++) अणु
			port_pcpu = per_cpu_ptr(port->pcpu, thपढ़ो);

			hrसमयr_init(&port_pcpu->tx_करोne_समयr, CLOCK_MONOTONIC,
				     HRTIMER_MODE_REL_PINNED_SOFT);
			port_pcpu->tx_करोne_समयr.function = mvpp2_hr_समयr_cb;
			port_pcpu->समयr_scheduled = false;
			port_pcpu->dev = dev;
		पूर्ण
	पूर्ण

	features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		   NETIF_F_TSO;
	dev->features = features | NETIF_F_RXCSUM;
	dev->hw_features |= features | NETIF_F_RXCSUM | NETIF_F_GRO |
			    NETIF_F_HW_VLAN_CTAG_FILTER;

	अगर (mvpp22_rss_is_supported(port)) अणु
		dev->hw_features |= NETIF_F_RXHASH;
		dev->features |= NETIF_F_NTUPLE;
	पूर्ण

	अगर (!port->priv->percpu_pools)
		mvpp2_set_hw_csum(port, port->pool_दीर्घ->id);

	dev->vlan_features |= features;
	dev->gso_max_segs = MVPP2_MAX_TSO_SEGS;
	dev->priv_flags |= IFF_UNICAST_FLT;

	/* MTU range: 68 - 9704 */
	dev->min_mtu = ETH_MIN_MTU;
	/* 9704 == 9728 - 20 and rounding to 8 */
	dev->max_mtu = MVPP2_BM_JUMBO_PKT_SIZE;
	dev->dev.of_node = port_node;

	/* Phylink isn't used w/ ACPI as of now */
	अगर (port_node) अणु
		port->phylink_config.dev = &dev->dev;
		port->phylink_config.type = PHYLINK_NETDEV;

		phylink = phylink_create(&port->phylink_config, port_fwnode,
					 phy_mode, &mvpp2_phylink_ops);
		अगर (IS_ERR(phylink)) अणु
			err = PTR_ERR(phylink);
			जाओ err_मुक्त_port_pcpu;
		पूर्ण
		port->phylink = phylink;
	पूर्ण अन्यथा अणु
		port->phylink = शून्य;
	पूर्ण

	/* Cycle the comphy to घातer it करोwn, saving 270mW per port -
	 * करोn't worry about an error घातering it up. When the comphy
	 * driver करोes this, we can हटाओ this code.
	 */
	अगर (port->comphy) अणु
		err = mvpp22_comphy_init(port);
		अगर (err == 0)
			phy_घातer_off(port->comphy);
	पूर्ण

	err = रेजिस्टर_netdev(dev);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register netdev\n");
		जाओ err_phylink;
	पूर्ण
	netdev_info(dev, "Using %s mac address %pM\n", mac_from, dev->dev_addr);

	priv->port_list[priv->port_count++] = port;

	वापस 0;

err_phylink:
	अगर (port->phylink)
		phylink_destroy(port->phylink);
err_मुक्त_port_pcpu:
	मुक्त_percpu(port->pcpu);
err_मुक्त_txq_pcpu:
	क्रम (i = 0; i < port->ntxqs; i++)
		मुक्त_percpu(port->txqs[i]->pcpu);
err_मुक्त_stats:
	मुक्त_percpu(port->stats);
err_मुक्त_irq:
	अगर (port->port_irq)
		irq_dispose_mapping(port->port_irq);
err_deinit_qvecs:
	mvpp2_queue_vectors_deinit(port);
err_मुक्त_netdev:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

/* Ports removal routine */
अटल व्योम mvpp2_port_हटाओ(काष्ठा mvpp2_port *port)
अणु
	पूर्णांक i;

	unरेजिस्टर_netdev(port->dev);
	अगर (port->phylink)
		phylink_destroy(port->phylink);
	मुक्त_percpu(port->pcpu);
	मुक्त_percpu(port->stats);
	क्रम (i = 0; i < port->ntxqs; i++)
		मुक्त_percpu(port->txqs[i]->pcpu);
	mvpp2_queue_vectors_deinit(port);
	अगर (port->port_irq)
		irq_dispose_mapping(port->port_irq);
	मुक्त_netdev(port->dev);
पूर्ण

/* Initialize decoding winकरोws */
अटल व्योम mvpp2_conf_mbus_winकरोws(स्थिर काष्ठा mbus_dram_target_info *dram,
				    काष्ठा mvpp2 *priv)
अणु
	u32 win_enable;
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++) अणु
		mvpp2_ग_लिखो(priv, MVPP2_WIN_BASE(i), 0);
		mvpp2_ग_लिखो(priv, MVPP2_WIN_SIZE(i), 0);

		अगर (i < 4)
			mvpp2_ग_लिखो(priv, MVPP2_WIN_REMAP(i), 0);
	पूर्ण

	win_enable = 0;

	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		mvpp2_ग_लिखो(priv, MVPP2_WIN_BASE(i),
			    (cs->base & 0xffff0000) | (cs->mbus_attr << 8) |
			    dram->mbus_dram_target_id);

		mvpp2_ग_लिखो(priv, MVPP2_WIN_SIZE(i),
			    (cs->size - 1) & 0xffff0000);

		win_enable |= (1 << i);
	पूर्ण

	mvpp2_ग_लिखो(priv, MVPP2_BASE_ADDR_ENABLE, win_enable);
पूर्ण

/* Initialize Rx FIFO's */
अटल व्योम mvpp2_rx_fअगरo_init(काष्ठा mvpp2 *priv)
अणु
	पूर्णांक port;

	क्रम (port = 0; port < MVPP2_MAX_PORTS; port++) अणु
		mvpp2_ग_लिखो(priv, MVPP2_RX_DATA_FIFO_SIZE_REG(port),
			    MVPP2_RX_FIFO_PORT_DATA_SIZE_4KB);
		mvpp2_ग_लिखो(priv, MVPP2_RX_ATTR_FIFO_SIZE_REG(port),
			    MVPP2_RX_FIFO_PORT_ATTR_SIZE_4KB);
	पूर्ण

	mvpp2_ग_लिखो(priv, MVPP2_RX_MIN_PKT_SIZE_REG,
		    MVPP2_RX_FIFO_PORT_MIN_PKT);
	mvpp2_ग_लिखो(priv, MVPP2_RX_FIFO_INIT_REG, 0x1);
पूर्ण

अटल व्योम mvpp22_rx_fअगरo_set_hw(काष्ठा mvpp2 *priv, पूर्णांक port, पूर्णांक data_size)
अणु
	पूर्णांक attr_size = MVPP2_RX_FIFO_PORT_ATTR_SIZE(data_size);

	mvpp2_ग_लिखो(priv, MVPP2_RX_DATA_FIFO_SIZE_REG(port), data_size);
	mvpp2_ग_लिखो(priv, MVPP2_RX_ATTR_FIFO_SIZE_REG(port), attr_size);
पूर्ण

/* Initialize TX FIFO's: the total FIFO size is 48kB on PPv2.2 and PPv2.3.
 * 4kB fixed space must be asचिन्हित क्रम the loopback port.
 * Redistribute reमुख्यing avialable 44kB space among all active ports.
 * Guarantee minimum 32kB क्रम 10G port and 8kB क्रम port 1, capable of 2.5G
 * SGMII link.
 */
अटल व्योम mvpp22_rx_fअगरo_init(काष्ठा mvpp2 *priv)
अणु
	पूर्णांक reमुख्यing_ports_count;
	अचिन्हित दीर्घ port_map;
	पूर्णांक size_reमुख्यder;
	पूर्णांक port, size;

	/* The loopback requires fixed 4kB of the FIFO space assignment. */
	mvpp22_rx_fअगरo_set_hw(priv, MVPP2_LOOPBACK_PORT_INDEX,
			      MVPP2_RX_FIFO_PORT_DATA_SIZE_4KB);
	port_map = priv->port_map & ~BIT(MVPP2_LOOPBACK_PORT_INDEX);

	/* Set RX FIFO size to 0 क्रम inactive ports. */
	क्रम_each_clear_bit(port, &port_map, MVPP2_LOOPBACK_PORT_INDEX)
		mvpp22_rx_fअगरo_set_hw(priv, port, 0);

	/* Assign reमुख्यing RX FIFO space among all active ports. */
	size_reमुख्यder = MVPP2_RX_FIFO_PORT_DATA_SIZE_44KB;
	reमुख्यing_ports_count = hweight_दीर्घ(port_map);

	क्रम_each_set_bit(port, &port_map, MVPP2_LOOPBACK_PORT_INDEX) अणु
		अगर (reमुख्यing_ports_count == 1)
			size = size_reमुख्यder;
		अन्यथा अगर (port == 0)
			size = max(size_reमुख्यder / reमुख्यing_ports_count,
				   MVPP2_RX_FIFO_PORT_DATA_SIZE_32KB);
		अन्यथा अगर (port == 1)
			size = max(size_reमुख्यder / reमुख्यing_ports_count,
				   MVPP2_RX_FIFO_PORT_DATA_SIZE_8KB);
		अन्यथा
			size = size_reमुख्यder / reमुख्यing_ports_count;

		size_reमुख्यder -= size;
		reमुख्यing_ports_count--;

		mvpp22_rx_fअगरo_set_hw(priv, port, size);
	पूर्ण

	mvpp2_ग_लिखो(priv, MVPP2_RX_MIN_PKT_SIZE_REG,
		    MVPP2_RX_FIFO_PORT_MIN_PKT);
	mvpp2_ग_लिखो(priv, MVPP2_RX_FIFO_INIT_REG, 0x1);
पूर्ण

/* Configure Rx FIFO Flow control thresholds */
अटल व्योम mvpp23_rx_fअगरo_fc_set_tresh(काष्ठा mvpp2 *priv)
अणु
	पूर्णांक port, val;

	/* Port 0: maximum speed -10Gb/s port
	 *	   required by spec RX FIFO threshold 9KB
	 * Port 1: maximum speed -5Gb/s port
	 *	   required by spec RX FIFO threshold 4KB
	 * Port 2: maximum speed -1Gb/s port
	 *	   required by spec RX FIFO threshold 2KB
	 */

	/* Without loopback port */
	क्रम (port = 0; port < (MVPP2_MAX_PORTS - 1); port++) अणु
		अगर (port == 0) अणु
			val = (MVPP23_PORT0_FIFO_TRSH / MVPP2_RX_FC_TRSH_UNIT)
				<< MVPP2_RX_FC_TRSH_OFFS;
			val &= MVPP2_RX_FC_TRSH_MASK;
			mvpp2_ग_लिखो(priv, MVPP2_RX_FC_REG(port), val);
		पूर्ण अन्यथा अगर (port == 1) अणु
			val = (MVPP23_PORT1_FIFO_TRSH / MVPP2_RX_FC_TRSH_UNIT)
				<< MVPP2_RX_FC_TRSH_OFFS;
			val &= MVPP2_RX_FC_TRSH_MASK;
			mvpp2_ग_लिखो(priv, MVPP2_RX_FC_REG(port), val);
		पूर्ण अन्यथा अणु
			val = (MVPP23_PORT2_FIFO_TRSH / MVPP2_RX_FC_TRSH_UNIT)
				<< MVPP2_RX_FC_TRSH_OFFS;
			val &= MVPP2_RX_FC_TRSH_MASK;
			mvpp2_ग_लिखो(priv, MVPP2_RX_FC_REG(port), val);
		पूर्ण
	पूर्ण
पूर्ण

/* Configure Rx FIFO Flow control thresholds */
व्योम mvpp23_rx_fअगरo_fc_en(काष्ठा mvpp2 *priv, पूर्णांक port, bool en)
अणु
	पूर्णांक val;

	val = mvpp2_पढ़ो(priv, MVPP2_RX_FC_REG(port));

	अगर (en)
		val |= MVPP2_RX_FC_EN;
	अन्यथा
		val &= ~MVPP2_RX_FC_EN;

	mvpp2_ग_लिखो(priv, MVPP2_RX_FC_REG(port), val);
पूर्ण

अटल व्योम mvpp22_tx_fअगरo_set_hw(काष्ठा mvpp2 *priv, पूर्णांक port, पूर्णांक size)
अणु
	पूर्णांक threshold = MVPP2_TX_FIFO_THRESHOLD(size);

	mvpp2_ग_लिखो(priv, MVPP22_TX_FIFO_SIZE_REG(port), size);
	mvpp2_ग_लिखो(priv, MVPP22_TX_FIFO_THRESH_REG(port), threshold);
पूर्ण

/* Initialize TX FIFO's: the total FIFO size is 19kB on PPv2.2 and PPv2.3.
 * 1kB fixed space must be asचिन्हित क्रम the loopback port.
 * Redistribute reमुख्यing avialable 18kB space among all active ports.
 * The 10G पूर्णांकerface should use 10kB (which is maximum possible size
 * per single port).
 */
अटल व्योम mvpp22_tx_fअगरo_init(काष्ठा mvpp2 *priv)
अणु
	पूर्णांक reमुख्यing_ports_count;
	अचिन्हित दीर्घ port_map;
	पूर्णांक size_reमुख्यder;
	पूर्णांक port, size;

	/* The loopback requires fixed 1kB of the FIFO space assignment. */
	mvpp22_tx_fअगरo_set_hw(priv, MVPP2_LOOPBACK_PORT_INDEX,
			      MVPP22_TX_FIFO_DATA_SIZE_1KB);
	port_map = priv->port_map & ~BIT(MVPP2_LOOPBACK_PORT_INDEX);

	/* Set TX FIFO size to 0 क्रम inactive ports. */
	क्रम_each_clear_bit(port, &port_map, MVPP2_LOOPBACK_PORT_INDEX)
		mvpp22_tx_fअगरo_set_hw(priv, port, 0);

	/* Assign reमुख्यing TX FIFO space among all active ports. */
	size_reमुख्यder = MVPP22_TX_FIFO_DATA_SIZE_18KB;
	reमुख्यing_ports_count = hweight_दीर्घ(port_map);

	क्रम_each_set_bit(port, &port_map, MVPP2_LOOPBACK_PORT_INDEX) अणु
		अगर (reमुख्यing_ports_count == 1)
			size = min(size_reमुख्यder,
				   MVPP22_TX_FIFO_DATA_SIZE_10KB);
		अन्यथा अगर (port == 0)
			size = MVPP22_TX_FIFO_DATA_SIZE_10KB;
		अन्यथा
			size = size_reमुख्यder / reमुख्यing_ports_count;

		size_reमुख्यder -= size;
		reमुख्यing_ports_count--;

		mvpp22_tx_fअगरo_set_hw(priv, port, size);
	पूर्ण
पूर्ण

अटल व्योम mvpp2_axi_init(काष्ठा mvpp2 *priv)
अणु
	u32 val, rdval, wrval;

	mvpp2_ग_लिखो(priv, MVPP22_BM_ADDR_HIGH_RLS_REG, 0x0);

	/* AXI Bridge Configuration */

	rdval = MVPP22_AXI_CODE_CACHE_RD_CACHE
		<< MVPP22_AXI_ATTR_CACHE_OFFS;
	rdval |= MVPP22_AXI_CODE_DOMAIN_OUTER_DOM
		<< MVPP22_AXI_ATTR_DOMAIN_OFFS;

	wrval = MVPP22_AXI_CODE_CACHE_WR_CACHE
		<< MVPP22_AXI_ATTR_CACHE_OFFS;
	wrval |= MVPP22_AXI_CODE_DOMAIN_OUTER_DOM
		<< MVPP22_AXI_ATTR_DOMAIN_OFFS;

	/* BM */
	mvpp2_ग_लिखो(priv, MVPP22_AXI_BM_WR_ATTR_REG, wrval);
	mvpp2_ग_लिखो(priv, MVPP22_AXI_BM_RD_ATTR_REG, rdval);

	/* Descriptors */
	mvpp2_ग_लिखो(priv, MVPP22_AXI_AGGRQ_DESCR_RD_ATTR_REG, rdval);
	mvpp2_ग_लिखो(priv, MVPP22_AXI_TXQ_DESCR_WR_ATTR_REG, wrval);
	mvpp2_ग_लिखो(priv, MVPP22_AXI_TXQ_DESCR_RD_ATTR_REG, rdval);
	mvpp2_ग_लिखो(priv, MVPP22_AXI_RXQ_DESCR_WR_ATTR_REG, wrval);

	/* Buffer Data */
	mvpp2_ग_लिखो(priv, MVPP22_AXI_TX_DATA_RD_ATTR_REG, rdval);
	mvpp2_ग_लिखो(priv, MVPP22_AXI_RX_DATA_WR_ATTR_REG, wrval);

	val = MVPP22_AXI_CODE_CACHE_NON_CACHE
		<< MVPP22_AXI_CODE_CACHE_OFFS;
	val |= MVPP22_AXI_CODE_DOMAIN_SYSTEM
		<< MVPP22_AXI_CODE_DOMAIN_OFFS;
	mvpp2_ग_लिखो(priv, MVPP22_AXI_RD_NORMAL_CODE_REG, val);
	mvpp2_ग_लिखो(priv, MVPP22_AXI_WR_NORMAL_CODE_REG, val);

	val = MVPP22_AXI_CODE_CACHE_RD_CACHE
		<< MVPP22_AXI_CODE_CACHE_OFFS;
	val |= MVPP22_AXI_CODE_DOMAIN_OUTER_DOM
		<< MVPP22_AXI_CODE_DOMAIN_OFFS;

	mvpp2_ग_लिखो(priv, MVPP22_AXI_RD_SNOOP_CODE_REG, val);

	val = MVPP22_AXI_CODE_CACHE_WR_CACHE
		<< MVPP22_AXI_CODE_CACHE_OFFS;
	val |= MVPP22_AXI_CODE_DOMAIN_OUTER_DOM
		<< MVPP22_AXI_CODE_DOMAIN_OFFS;

	mvpp2_ग_लिखो(priv, MVPP22_AXI_WR_SNOOP_CODE_REG, val);
पूर्ण

/* Initialize network controller common part HW */
अटल पूर्णांक mvpp2_init(काष्ठा platक्रमm_device *pdev, काष्ठा mvpp2 *priv)
अणु
	स्थिर काष्ठा mbus_dram_target_info *dram_target_info;
	पूर्णांक err, i;
	u32 val;

	/* MBUS winकरोws configuration */
	dram_target_info = mv_mbus_dram_info();
	अगर (dram_target_info)
		mvpp2_conf_mbus_winकरोws(dram_target_info, priv);

	अगर (priv->hw_version >= MVPP22)
		mvpp2_axi_init(priv);

	/* Disable HW PHY polling */
	अगर (priv->hw_version == MVPP21) अणु
		val = पढ़ोl(priv->lms_base + MVPP2_PHY_AN_CFG0_REG);
		val |= MVPP2_PHY_AN_STOP_SMI0_MASK;
		ग_लिखोl(val, priv->lms_base + MVPP2_PHY_AN_CFG0_REG);
	पूर्ण अन्यथा अणु
		val = पढ़ोl(priv->अगरace_base + MVPP22_SMI_MISC_CFG_REG);
		val &= ~MVPP22_SMI_POLLING_EN;
		ग_लिखोl(val, priv->अगरace_base + MVPP22_SMI_MISC_CFG_REG);
	पूर्ण

	/* Allocate and initialize aggregated TXQs */
	priv->aggr_txqs = devm_kसुस्मृति(&pdev->dev, MVPP2_MAX_THREADS,
				       माप(*priv->aggr_txqs),
				       GFP_KERNEL);
	अगर (!priv->aggr_txqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < MVPP2_MAX_THREADS; i++) अणु
		priv->aggr_txqs[i].id = i;
		priv->aggr_txqs[i].size = MVPP2_AGGR_TXQ_SIZE;
		err = mvpp2_aggr_txq_init(pdev, &priv->aggr_txqs[i], i, priv);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Fअगरo Init */
	अगर (priv->hw_version == MVPP21) अणु
		mvpp2_rx_fअगरo_init(priv);
	पूर्ण अन्यथा अणु
		mvpp22_rx_fअगरo_init(priv);
		mvpp22_tx_fअगरo_init(priv);
		अगर (priv->hw_version == MVPP23)
			mvpp23_rx_fअगरo_fc_set_tresh(priv);
	पूर्ण

	अगर (priv->hw_version == MVPP21)
		ग_लिखोl(MVPP2_EXT_GLOBAL_CTRL_DEFAULT,
		       priv->lms_base + MVPP2_MNG_EXTENDED_GLOBAL_CTRL_REG);

	/* Allow cache snoop when transmiting packets */
	mvpp2_ग_लिखो(priv, MVPP2_TX_SNOOP_REG, 0x1);

	/* Buffer Manager initialization */
	err = mvpp2_bm_init(&pdev->dev, priv);
	अगर (err < 0)
		वापस err;

	/* Parser शेष initialization */
	err = mvpp2_prs_शेष_init(pdev, priv);
	अगर (err < 0)
		वापस err;

	/* Classअगरier शेष initialization */
	mvpp2_cls_init(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक mvpp2_get_sram(काष्ठा platक्रमm_device *pdev,
			  काष्ठा mvpp2 *priv)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	अगर (!res) अणु
		अगर (has_acpi_companion(&pdev->dev))
			dev_warn(&pdev->dev, "ACPI is too old, Flow control not supported\n");
		अन्यथा
			dev_warn(&pdev->dev, "DT is too old, Flow control not supported\n");
		वापस 0;
	पूर्ण

	priv->cm3_base = devm_ioremap_resource(&pdev->dev, res);

	वापस PTR_ERR_OR_ZERO(priv->cm3_base);
पूर्ण

अटल पूर्णांक mvpp2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा acpi_device_id *acpi_id;
	काष्ठा fwnode_handle *fwnode = pdev->dev.fwnode;
	काष्ठा fwnode_handle *port_fwnode;
	काष्ठा mvpp2 *priv;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक i, shared;
	पूर्णांक err;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (has_acpi_companion(&pdev->dev)) अणु
		acpi_id = acpi_match_device(pdev->dev.driver->acpi_match_table,
					    &pdev->dev);
		अगर (!acpi_id)
			वापस -EINVAL;
		priv->hw_version = (अचिन्हित दीर्घ)acpi_id->driver_data;
	पूर्ण अन्यथा अणु
		priv->hw_version =
			(अचिन्हित दीर्घ)of_device_get_match_data(&pdev->dev);
	पूर्ण

	/* multi queue mode isn't supported on PPV2.1, fallback to single
	 * mode
	 */
	अगर (priv->hw_version == MVPP21)
		queue_mode = MVPP2_QDIST_SINGLE_MODE;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	अगर (priv->hw_version == MVPP21) अणु
		priv->lms_base = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(priv->lms_base))
			वापस PTR_ERR(priv->lms_base);
	पूर्ण अन्यथा अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		अगर (has_acpi_companion(&pdev->dev)) अणु
			/* In हाल the MDIO memory region is declared in
			 * the ACPI, it can alपढ़ोy appear as 'in-use'
			 * in the OS. Because it is overlapped by second
			 * region of the network controller, make
			 * sure it is released, beक्रमe requesting it again.
			 * The care is taken by mvpp2 driver to aव्योम
			 * concurrent access to this memory region.
			 */
			release_resource(res);
		पूर्ण
		priv->अगरace_base = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(priv->अगरace_base))
			वापस PTR_ERR(priv->अगरace_base);

		/* Map CM3 SRAM */
		err = mvpp2_get_sram(pdev, priv);
		अगर (err)
			dev_warn(&pdev->dev, "Fail to alloc CM3 SRAM\n");

		/* Enable global Flow Control only अगर handler to SRAM not शून्य */
		अगर (priv->cm3_base)
			priv->global_tx_fc = true;
	पूर्ण

	अगर (priv->hw_version >= MVPP22 && dev_of_node(&pdev->dev)) अणु
		priv->sysctrl_base =
			syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							"marvell,system-controller");
		अगर (IS_ERR(priv->sysctrl_base))
			/* The प्रणाली controller regmap is optional क्रम dt
			 * compatibility reasons. When not provided, the
			 * configuration of the GoP relies on the
			 * firmware/bootloader.
			 */
			priv->sysctrl_base = शून्य;
	पूर्ण

	अगर (priv->hw_version >= MVPP22 &&
	    mvpp2_get_nrxqs(priv) * 2 <= MVPP2_BM_MAX_POOLS)
		priv->percpu_pools = 1;

	mvpp2_setup_bm_pool();


	priv->nthपढ़ोs = min_t(अचिन्हित पूर्णांक, num_present_cpus(),
			       MVPP2_MAX_THREADS);

	shared = num_present_cpus() - priv->nthपढ़ोs;
	अगर (shared > 0)
		biपंचांगap_fill(&priv->lock_map,
			    min_t(पूर्णांक, shared, MVPP2_MAX_THREADS));

	क्रम (i = 0; i < MVPP2_MAX_THREADS; i++) अणु
		u32 addr_space_sz;

		addr_space_sz = (priv->hw_version == MVPP21 ?
				 MVPP21_ADDR_SPACE_SZ : MVPP22_ADDR_SPACE_SZ);
		priv->swth_base[i] = base + i * addr_space_sz;
	पूर्ण

	अगर (priv->hw_version == MVPP21)
		priv->max_port_rxqs = 8;
	अन्यथा
		priv->max_port_rxqs = 32;

	अगर (dev_of_node(&pdev->dev)) अणु
		priv->pp_clk = devm_clk_get(&pdev->dev, "pp_clk");
		अगर (IS_ERR(priv->pp_clk))
			वापस PTR_ERR(priv->pp_clk);
		err = clk_prepare_enable(priv->pp_clk);
		अगर (err < 0)
			वापस err;

		priv->gop_clk = devm_clk_get(&pdev->dev, "gop_clk");
		अगर (IS_ERR(priv->gop_clk)) अणु
			err = PTR_ERR(priv->gop_clk);
			जाओ err_pp_clk;
		पूर्ण
		err = clk_prepare_enable(priv->gop_clk);
		अगर (err < 0)
			जाओ err_pp_clk;

		अगर (priv->hw_version >= MVPP22) अणु
			priv->mg_clk = devm_clk_get(&pdev->dev, "mg_clk");
			अगर (IS_ERR(priv->mg_clk)) अणु
				err = PTR_ERR(priv->mg_clk);
				जाओ err_gop_clk;
			पूर्ण

			err = clk_prepare_enable(priv->mg_clk);
			अगर (err < 0)
				जाओ err_gop_clk;

			priv->mg_core_clk = devm_clk_get(&pdev->dev, "mg_core_clk");
			अगर (IS_ERR(priv->mg_core_clk)) अणु
				priv->mg_core_clk = शून्य;
			पूर्ण अन्यथा अणु
				err = clk_prepare_enable(priv->mg_core_clk);
				अगर (err < 0)
					जाओ err_mg_clk;
			पूर्ण
		पूर्ण

		priv->axi_clk = devm_clk_get(&pdev->dev, "axi_clk");
		अगर (IS_ERR(priv->axi_clk)) अणु
			err = PTR_ERR(priv->axi_clk);
			अगर (err == -EPROBE_DEFER)
				जाओ err_mg_core_clk;
			priv->axi_clk = शून्य;
		पूर्ण अन्यथा अणु
			err = clk_prepare_enable(priv->axi_clk);
			अगर (err < 0)
				जाओ err_mg_core_clk;
		पूर्ण

		/* Get प्रणाली's tclk rate */
		priv->tclk = clk_get_rate(priv->pp_clk);
	पूर्ण अन्यथा अगर (device_property_पढ़ो_u32(&pdev->dev, "clock-frequency",
					    &priv->tclk)) अणु
		dev_err(&pdev->dev, "missing clock-frequency value\n");
		वापस -EINVAL;
	पूर्ण

	अगर (priv->hw_version >= MVPP22) अणु
		err = dma_set_mask(&pdev->dev, MVPP2_DESC_DMA_MASK);
		अगर (err)
			जाओ err_axi_clk;
		/* Sadly, the BM pools all share the same रेजिस्टर to
		 * store the high 32 bits of their address. So they
		 * must all have the same high 32 bits, which क्रमces
		 * us to restrict coherent memory to DMA_BIT_MASK(32).
		 */
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err)
			जाओ err_axi_clk;
	पूर्ण

	/* Map DTS-active ports. Should be करोne beक्रमe FIFO mvpp2_init */
	fwnode_क्रम_each_available_child_node(fwnode, port_fwnode) अणु
		अगर (!fwnode_property_पढ़ो_u32(port_fwnode, "port-id", &i))
			priv->port_map |= BIT(i);
	पूर्ण

	अगर (mvpp2_पढ़ो(priv, MVPP2_VER_ID_REG) == MVPP2_VER_PP23)
		priv->hw_version = MVPP23;

	/* Init mss lock */
	spin_lock_init(&priv->mss_spinlock);

	/* Initialize network controller */
	err = mvpp2_init(pdev, priv);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to initialize controller\n");
		जाओ err_axi_clk;
	पूर्ण

	err = mvpp22_tai_probe(&pdev->dev, priv);
	अगर (err < 0)
		जाओ err_axi_clk;

	/* Initialize ports */
	fwnode_क्रम_each_available_child_node(fwnode, port_fwnode) अणु
		err = mvpp2_port_probe(pdev, port_fwnode, priv);
		अगर (err < 0)
			जाओ err_port_probe;
	पूर्ण

	अगर (priv->port_count == 0) अणु
		dev_err(&pdev->dev, "no ports enabled\n");
		err = -ENODEV;
		जाओ err_axi_clk;
	पूर्ण

	/* Statistics must be gathered regularly because some of them (like
	 * packets counters) are 32-bit रेजिस्टरs and could overflow quite
	 * quickly. For instance, a 10Gb link used at full bandwidth with the
	 * smallest packets (64B) will overflow a 32-bit counter in less than
	 * 30 seconds. Then, use a workqueue to fill 64-bit counters.
	 */
	snम_लिखो(priv->queue_name, माप(priv->queue_name),
		 "stats-wq-%s%s", netdev_name(priv->port_list[0]->dev),
		 priv->port_count > 1 ? "+" : "");
	priv->stats_queue = create_singlethपढ़ो_workqueue(priv->queue_name);
	अगर (!priv->stats_queue) अणु
		err = -ENOMEM;
		जाओ err_port_probe;
	पूर्ण

	अगर (priv->global_tx_fc && priv->hw_version >= MVPP22) अणु
		err = mvpp2_enable_global_fc(priv);
		अगर (err)
			dev_warn(&pdev->dev, "Minimum of CM3 firmware 18.09 and chip revision B0 required for flow control\n");
	पूर्ण

	mvpp2_dbgfs_init(priv, pdev->name);

	platक्रमm_set_drvdata(pdev, priv);
	वापस 0;

err_port_probe:
	i = 0;
	fwnode_क्रम_each_available_child_node(fwnode, port_fwnode) अणु
		अगर (priv->port_list[i])
			mvpp2_port_हटाओ(priv->port_list[i]);
		i++;
	पूर्ण
err_axi_clk:
	clk_disable_unprepare(priv->axi_clk);

err_mg_core_clk:
	अगर (priv->hw_version >= MVPP22)
		clk_disable_unprepare(priv->mg_core_clk);
err_mg_clk:
	अगर (priv->hw_version >= MVPP22)
		clk_disable_unprepare(priv->mg_clk);
err_gop_clk:
	clk_disable_unprepare(priv->gop_clk);
err_pp_clk:
	clk_disable_unprepare(priv->pp_clk);
	वापस err;
पूर्ण

अटल पूर्णांक mvpp2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mvpp2 *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा fwnode_handle *fwnode = pdev->dev.fwnode;
	पूर्णांक i = 0, poolnum = MVPP2_BM_POOLS_NUM;
	काष्ठा fwnode_handle *port_fwnode;

	mvpp2_dbgfs_cleanup(priv);

	fwnode_क्रम_each_available_child_node(fwnode, port_fwnode) अणु
		अगर (priv->port_list[i]) अणु
			mutex_destroy(&priv->port_list[i]->gather_stats_lock);
			mvpp2_port_हटाओ(priv->port_list[i]);
		पूर्ण
		i++;
	पूर्ण

	destroy_workqueue(priv->stats_queue);

	अगर (priv->percpu_pools)
		poolnum = mvpp2_get_nrxqs(priv) * 2;

	क्रम (i = 0; i < poolnum; i++) अणु
		काष्ठा mvpp2_bm_pool *bm_pool = &priv->bm_pools[i];

		mvpp2_bm_pool_destroy(&pdev->dev, priv, bm_pool);
	पूर्ण

	क्रम (i = 0; i < MVPP2_MAX_THREADS; i++) अणु
		काष्ठा mvpp2_tx_queue *aggr_txq = &priv->aggr_txqs[i];

		dma_मुक्त_coherent(&pdev->dev,
				  MVPP2_AGGR_TXQ_SIZE * MVPP2_DESC_ALIGNED_SIZE,
				  aggr_txq->descs,
				  aggr_txq->descs_dma);
	पूर्ण

	अगर (is_acpi_node(port_fwnode))
		वापस 0;

	clk_disable_unprepare(priv->axi_clk);
	clk_disable_unprepare(priv->mg_core_clk);
	clk_disable_unprepare(priv->mg_clk);
	clk_disable_unprepare(priv->pp_clk);
	clk_disable_unprepare(priv->gop_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mvpp2_match[] = अणु
	अणु
		.compatible = "marvell,armada-375-pp2",
		.data = (व्योम *)MVPP21,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-7k-pp22",
		.data = (व्योम *)MVPP22,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mvpp2_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id mvpp2_acpi_match[] = अणु
	अणु "MRVL0110", MVPP22 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mvpp2_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mvpp2_driver = अणु
	.probe = mvpp2_probe,
	.हटाओ = mvpp2_हटाओ,
	.driver = अणु
		.name = MVPP2_DRIVER_NAME,
		.of_match_table = mvpp2_match,
		.acpi_match_table = ACPI_PTR(mvpp2_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mvpp2_driver);

MODULE_DESCRIPTION("Marvell PPv2 Ethernet Driver - www.marvell.com");
MODULE_AUTHOR("Marcin Wojtas <mw@semihalf.com>");
MODULE_LICENSE("GPL v2");
