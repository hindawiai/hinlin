<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#अगर_घोषित CONFIG_RFS_ACCEL
#समावेश <linux/cpu_rmap.h>
#पूर्ण_अगर
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/irq.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/sctp.h>
#समावेश <net/gre.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tcp.h>
#समावेश <net/vxlan.h>
#समावेश <net/geneve.h>

#समावेश "hnae3.h"
#समावेश "hns3_enet.h"
/* All hns3 tracepoपूर्णांकs are defined by the include below, which
 * must be included exactly once across the whole kernel with
 * CREATE_TRACE_POINTS defined
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश "hns3_trace.h"

#घोषणा hns3_set_field(origin, shअगरt, val)	((origin) |= (val) << (shअगरt))
#घोषणा hns3_tx_bd_count(S)	DIV_ROUND_UP(S, HNS3_MAX_BD_SIZE)

#घोषणा hns3_rl_err(fmt, ...)						\
	करो अणु								\
		अगर (net_ratelimit())					\
			netdev_err(fmt, ##__VA_ARGS__);			\
	पूर्ण जबतक (0)

अटल व्योम hns3_clear_all_ring(काष्ठा hnae3_handle *h, bool क्रमce);

अटल स्थिर अक्षर hns3_driver_name[] = "hns3";
अटल स्थिर अक्षर hns3_driver_string[] =
			"Hisilicon Ethernet Network Driver for Hip08 Family";
अटल स्थिर अक्षर hns3_copyright[] = "Copyright (c) 2017 Huawei Corporation.";
अटल काष्ठा hnae3_client client;

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, " Network interface message level setting");

#घोषणा DEFAULT_MSG_LEVEL (NETIF_MSG_PROBE | NETIF_MSG_LINK | \
			   NETIF_MSG_IFDOWN | NETIF_MSG_IFUP)

#घोषणा HNS3_INNER_VLAN_TAG	1
#घोषणा HNS3_OUTER_VLAN_TAG	2

#घोषणा HNS3_MIN_TX_LEN		33U

/* hns3_pci_tbl - PCI Device ID Table
 *
 * Last entry must be all 0s
 *
 * अणु Venकरोr ID, Device ID, SubVenकरोr ID, SubDevice ID,
 *   Class, Class Mask, निजी data (not used) पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id hns3_pci_tbl[] = अणु
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_GE), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_25GE), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_25GE_RDMA),
	 HNAE3_DEV_SUPPORT_ROCE_DCB_BITSपूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_25GE_RDMA_MACSEC),
	 HNAE3_DEV_SUPPORT_ROCE_DCB_BITSपूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_50GE_RDMA),
	 HNAE3_DEV_SUPPORT_ROCE_DCB_BITSपूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_50GE_RDMA_MACSEC),
	 HNAE3_DEV_SUPPORT_ROCE_DCB_BITSपूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_100G_RDMA_MACSEC),
	 HNAE3_DEV_SUPPORT_ROCE_DCB_BITSपूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_200G_RDMA),
	 HNAE3_DEV_SUPPORT_ROCE_DCB_BITSपूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_VF), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_RDMA_DCB_PFC_VF),
	 HNAE3_DEV_SUPPORT_ROCE_DCB_BITSपूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, hns3_pci_tbl);

अटल irqवापस_t hns3_irq_handle(पूर्णांक irq, व्योम *vector)
अणु
	काष्ठा hns3_enet_tqp_vector *tqp_vector = vector;

	napi_schedule_irqoff(&tqp_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम hns3_nic_uninit_irq(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hns3_enet_tqp_vector *tqp_vectors;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->vector_num; i++) अणु
		tqp_vectors = &priv->tqp_vector[i];

		अगर (tqp_vectors->irq_init_flag != HNS3_VECTOR_INITED)
			जारी;

		/* clear the affinity mask */
		irq_set_affinity_hपूर्णांक(tqp_vectors->vector_irq, शून्य);

		/* release the irq resource */
		मुक्त_irq(tqp_vectors->vector_irq, tqp_vectors);
		tqp_vectors->irq_init_flag = HNS3_VECTOR_NOT_INITED;
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_nic_init_irq(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hns3_enet_tqp_vector *tqp_vectors;
	पूर्णांक txrx_पूर्णांक_idx = 0;
	पूर्णांक rx_पूर्णांक_idx = 0;
	पूर्णांक tx_पूर्णांक_idx = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < priv->vector_num; i++) अणु
		tqp_vectors = &priv->tqp_vector[i];

		अगर (tqp_vectors->irq_init_flag == HNS3_VECTOR_INITED)
			जारी;

		अगर (tqp_vectors->tx_group.ring && tqp_vectors->rx_group.ring) अणु
			snम_लिखो(tqp_vectors->name, HNAE3_INT_NAME_LEN,
				 "%s-%s-%s-%d", hns3_driver_name,
				 pci_name(priv->ae_handle->pdev),
				 "TxRx", txrx_पूर्णांक_idx++);
			txrx_पूर्णांक_idx++;
		पूर्ण अन्यथा अगर (tqp_vectors->rx_group.ring) अणु
			snम_लिखो(tqp_vectors->name, HNAE3_INT_NAME_LEN,
				 "%s-%s-%s-%d", hns3_driver_name,
				 pci_name(priv->ae_handle->pdev),
				 "Rx", rx_पूर्णांक_idx++);
		पूर्ण अन्यथा अगर (tqp_vectors->tx_group.ring) अणु
			snम_लिखो(tqp_vectors->name, HNAE3_INT_NAME_LEN,
				 "%s-%s-%s-%d", hns3_driver_name,
				 pci_name(priv->ae_handle->pdev),
				 "Tx", tx_पूर्णांक_idx++);
		पूर्ण अन्यथा अणु
			/* Skip this unused q_vector */
			जारी;
		पूर्ण

		tqp_vectors->name[HNAE3_INT_NAME_LEN - 1] = '\0';

		irq_set_status_flags(tqp_vectors->vector_irq, IRQ_NOAUTOEN);
		ret = request_irq(tqp_vectors->vector_irq, hns3_irq_handle, 0,
				  tqp_vectors->name, tqp_vectors);
		अगर (ret) अणु
			netdev_err(priv->netdev, "request irq(%d) fail\n",
				   tqp_vectors->vector_irq);
			hns3_nic_uninit_irq(priv);
			वापस ret;
		पूर्ण

		irq_set_affinity_hपूर्णांक(tqp_vectors->vector_irq,
				      &tqp_vectors->affinity_mask);

		tqp_vectors->irq_init_flag = HNS3_VECTOR_INITED;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hns3_mask_vector_irq(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				 u32 mask_en)
अणु
	ग_लिखोl(mask_en, tqp_vector->mask_addr);
पूर्ण

अटल व्योम hns3_vector_enable(काष्ठा hns3_enet_tqp_vector *tqp_vector)
अणु
	napi_enable(&tqp_vector->napi);
	enable_irq(tqp_vector->vector_irq);

	/* enable vector */
	hns3_mask_vector_irq(tqp_vector, 1);
पूर्ण

अटल व्योम hns3_vector_disable(काष्ठा hns3_enet_tqp_vector *tqp_vector)
अणु
	/* disable vector */
	hns3_mask_vector_irq(tqp_vector, 0);

	disable_irq(tqp_vector->vector_irq);
	napi_disable(&tqp_vector->napi);
पूर्ण

व्योम hns3_set_vector_coalesce_rl(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				 u32 rl_value)
अणु
	u32 rl_reg = hns3_rl_usec_to_reg(rl_value);

	/* this defines the configuration क्रम RL (Interrupt Rate Limiter).
	 * Rl defines rate of पूर्णांकerrupts i.e. number of पूर्णांकerrupts-per-second
	 * GL and RL(Rate Limiter) are 2 ways to acheive पूर्णांकerrupt coalescing
	 */
	अगर (rl_reg > 0 && !tqp_vector->tx_group.coal.adapt_enable &&
	    !tqp_vector->rx_group.coal.adapt_enable)
		/* According to the hardware, the range of rl_reg is
		 * 0-59 and the unit is 4.
		 */
		rl_reg |=  HNS3_INT_RL_ENABLE_MASK;

	ग_लिखोl(rl_reg, tqp_vector->mask_addr + HNS3_VECTOR_RL_OFFSET);
पूर्ण

व्योम hns3_set_vector_coalesce_rx_gl(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				    u32 gl_value)
अणु
	u32 new_val;

	अगर (tqp_vector->rx_group.coal.unit_1us)
		new_val = gl_value | HNS3_INT_GL_1US;
	अन्यथा
		new_val = hns3_gl_usec_to_reg(gl_value);

	ग_लिखोl(new_val, tqp_vector->mask_addr + HNS3_VECTOR_GL0_OFFSET);
पूर्ण

व्योम hns3_set_vector_coalesce_tx_gl(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				    u32 gl_value)
अणु
	u32 new_val;

	अगर (tqp_vector->tx_group.coal.unit_1us)
		new_val = gl_value | HNS3_INT_GL_1US;
	अन्यथा
		new_val = hns3_gl_usec_to_reg(gl_value);

	ग_लिखोl(new_val, tqp_vector->mask_addr + HNS3_VECTOR_GL1_OFFSET);
पूर्ण

व्योम hns3_set_vector_coalesce_tx_ql(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				    u32 ql_value)
अणु
	ग_लिखोl(ql_value, tqp_vector->mask_addr + HNS3_VECTOR_TX_QL_OFFSET);
पूर्ण

व्योम hns3_set_vector_coalesce_rx_ql(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				    u32 ql_value)
अणु
	ग_लिखोl(ql_value, tqp_vector->mask_addr + HNS3_VECTOR_RX_QL_OFFSET);
पूर्ण

अटल व्योम hns3_vector_coalesce_init(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				      काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(priv->ae_handle->pdev);
	काष्ठा hns3_enet_coalesce *tx_coal = &tqp_vector->tx_group.coal;
	काष्ठा hns3_enet_coalesce *rx_coal = &tqp_vector->rx_group.coal;
	काष्ठा hns3_enet_coalesce *ptx_coal = &priv->tx_coal;
	काष्ठा hns3_enet_coalesce *prx_coal = &priv->rx_coal;

	tx_coal->adapt_enable = ptx_coal->adapt_enable;
	rx_coal->adapt_enable = prx_coal->adapt_enable;

	tx_coal->पूर्णांक_gl = ptx_coal->पूर्णांक_gl;
	rx_coal->पूर्णांक_gl = prx_coal->पूर्णांक_gl;

	rx_coal->flow_level = prx_coal->flow_level;
	tx_coal->flow_level = ptx_coal->flow_level;

	/* device version above V3(include V3), GL can configure 1us
	 * unit, so uses 1us unit.
	 */
	अगर (ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V3) अणु
		tx_coal->unit_1us = 1;
		rx_coal->unit_1us = 1;
	पूर्ण

	अगर (ae_dev->dev_specs.पूर्णांक_ql_max) अणु
		tx_coal->ql_enable = 1;
		rx_coal->ql_enable = 1;
		tx_coal->पूर्णांक_ql_max = ae_dev->dev_specs.पूर्णांक_ql_max;
		rx_coal->पूर्णांक_ql_max = ae_dev->dev_specs.पूर्णांक_ql_max;
		tx_coal->पूर्णांक_ql = ptx_coal->पूर्णांक_ql;
		rx_coal->पूर्णांक_ql = prx_coal->पूर्णांक_ql;
	पूर्ण
पूर्ण

अटल व्योम
hns3_vector_coalesce_init_hw(काष्ठा hns3_enet_tqp_vector *tqp_vector,
			     काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hns3_enet_coalesce *tx_coal = &tqp_vector->tx_group.coal;
	काष्ठा hns3_enet_coalesce *rx_coal = &tqp_vector->rx_group.coal;
	काष्ठा hnae3_handle *h = priv->ae_handle;

	hns3_set_vector_coalesce_tx_gl(tqp_vector, tx_coal->पूर्णांक_gl);
	hns3_set_vector_coalesce_rx_gl(tqp_vector, rx_coal->पूर्णांक_gl);
	hns3_set_vector_coalesce_rl(tqp_vector, h->kinfo.पूर्णांक_rl_setting);

	अगर (tx_coal->ql_enable)
		hns3_set_vector_coalesce_tx_ql(tqp_vector, tx_coal->पूर्णांक_ql);

	अगर (rx_coal->ql_enable)
		hns3_set_vector_coalesce_rx_ql(tqp_vector, rx_coal->पूर्णांक_ql);
पूर्ण

अटल पूर्णांक hns3_nic_set_real_num_queue(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा hnae3_knic_निजी_info *kinfo = &h->kinfo;
	काष्ठा hnae3_tc_info *tc_info = &kinfo->tc_info;
	अचिन्हित पूर्णांक queue_size = kinfo->num_tqps;
	पूर्णांक i, ret;

	अगर (tc_info->num_tc <= 1 && !tc_info->mqprio_active) अणु
		netdev_reset_tc(netdev);
	पूर्ण अन्यथा अणु
		ret = netdev_set_num_tc(netdev, tc_info->num_tc);
		अगर (ret) अणु
			netdev_err(netdev,
				   "netdev_set_num_tc fail, ret=%d!\n", ret);
			वापस ret;
		पूर्ण

		क्रम (i = 0; i < HNAE3_MAX_TC; i++) अणु
			अगर (!test_bit(i, &tc_info->tc_en))
				जारी;

			netdev_set_tc_queue(netdev, i, tc_info->tqp_count[i],
					    tc_info->tqp_offset[i]);
		पूर्ण
	पूर्ण

	ret = netअगर_set_real_num_tx_queues(netdev, queue_size);
	अगर (ret) अणु
		netdev_err(netdev,
			   "netif_set_real_num_tx_queues fail, ret=%d!\n", ret);
		वापस ret;
	पूर्ण

	ret = netअगर_set_real_num_rx_queues(netdev, queue_size);
	अगर (ret) अणु
		netdev_err(netdev,
			   "netif_set_real_num_rx_queues fail, ret=%d!\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 hns3_get_max_available_channels(काष्ठा hnae3_handle *h)
अणु
	u16 alloc_tqps, max_rss_size, rss_size;

	h->ae_algo->ops->get_tqps_and_rss_info(h, &alloc_tqps, &max_rss_size);
	rss_size = alloc_tqps / h->kinfo.tc_info.num_tc;

	वापस min_t(u16, rss_size, max_rss_size);
पूर्ण

अटल व्योम hns3_tqp_enable(काष्ठा hnae3_queue *tqp)
अणु
	u32 rcb_reg;

	rcb_reg = hns3_पढ़ो_dev(tqp, HNS3_RING_EN_REG);
	rcb_reg |= BIT(HNS3_RING_EN_B);
	hns3_ग_लिखो_dev(tqp, HNS3_RING_EN_REG, rcb_reg);
पूर्ण

अटल व्योम hns3_tqp_disable(काष्ठा hnae3_queue *tqp)
अणु
	u32 rcb_reg;

	rcb_reg = hns3_पढ़ो_dev(tqp, HNS3_RING_EN_REG);
	rcb_reg &= ~BIT(HNS3_RING_EN_B);
	hns3_ग_लिखो_dev(tqp, HNS3_RING_EN_REG, rcb_reg);
पूर्ण

अटल व्योम hns3_मुक्त_rx_cpu_rmap(काष्ठा net_device *netdev)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	मुक्त_irq_cpu_rmap(netdev->rx_cpu_rmap);
	netdev->rx_cpu_rmap = शून्य;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक hns3_set_rx_cpu_rmap(काष्ठा net_device *netdev)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hns3_enet_tqp_vector *tqp_vector;
	पूर्णांक i, ret;

	अगर (!netdev->rx_cpu_rmap) अणु
		netdev->rx_cpu_rmap = alloc_irq_cpu_rmap(priv->vector_num);
		अगर (!netdev->rx_cpu_rmap)
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < priv->vector_num; i++) अणु
		tqp_vector = &priv->tqp_vector[i];
		ret = irq_cpu_rmap_add(netdev->rx_cpu_rmap,
				       tqp_vector->vector_irq);
		अगर (ret) अणु
			hns3_मुक्त_rx_cpu_rmap(netdev);
			वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक hns3_nic_net_up(काष्ठा net_device *netdev)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae3_handle *h = priv->ae_handle;
	पूर्णांक i, j;
	पूर्णांक ret;

	ret = hns3_nic_reset_all_ring(h);
	अगर (ret)
		वापस ret;

	clear_bit(HNS3_NIC_STATE_DOWN, &priv->state);

	/* enable the vectors */
	क्रम (i = 0; i < priv->vector_num; i++)
		hns3_vector_enable(&priv->tqp_vector[i]);

	/* enable rcb */
	क्रम (j = 0; j < h->kinfo.num_tqps; j++)
		hns3_tqp_enable(h->kinfo.tqp[j]);

	/* start the ae_dev */
	ret = h->ae_algo->ops->start ? h->ae_algo->ops->start(h) : 0;
	अगर (ret) अणु
		set_bit(HNS3_NIC_STATE_DOWN, &priv->state);
		जबतक (j--)
			hns3_tqp_disable(h->kinfo.tqp[j]);

		क्रम (j = i - 1; j >= 0; j--)
			hns3_vector_disable(&priv->tqp_vector[j]);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hns3_config_xps(काष्ठा hns3_nic_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->vector_num; i++) अणु
		काष्ठा hns3_enet_tqp_vector *tqp_vector = &priv->tqp_vector[i];
		काष्ठा hns3_enet_ring *ring = tqp_vector->tx_group.ring;

		जबतक (ring) अणु
			पूर्णांक ret;

			ret = netअगर_set_xps_queue(priv->netdev,
						  &tqp_vector->affinity_mask,
						  ring->tqp->tqp_index);
			अगर (ret)
				netdev_warn(priv->netdev,
					    "set xps queue failed: %d", ret);

			ring = ring->next;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_nic_net_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा hnae3_knic_निजी_info *kinfo;
	पूर्णांक i, ret;

	अगर (hns3_nic_resetting(netdev))
		वापस -EBUSY;

	netअगर_carrier_off(netdev);

	ret = hns3_nic_set_real_num_queue(netdev);
	अगर (ret)
		वापस ret;

	ret = hns3_nic_net_up(netdev);
	अगर (ret) अणु
		netdev_err(netdev, "net up fail, ret=%d!\n", ret);
		वापस ret;
	पूर्ण

	kinfo = &h->kinfo;
	क्रम (i = 0; i < HNAE3_MAX_USER_PRIO; i++)
		netdev_set_prio_tc_map(netdev, i, kinfo->tc_info.prio_tc[i]);

	अगर (h->ae_algo->ops->set_समयr_task)
		h->ae_algo->ops->set_समयr_task(priv->ae_handle, true);

	hns3_config_xps(priv);

	netअगर_dbg(h, drv, netdev, "net open\n");

	वापस 0;
पूर्ण

अटल व्योम hns3_reset_tx_queue(काष्ठा hnae3_handle *h)
अणु
	काष्ठा net_device *ndev = h->kinfo.netdev;
	काष्ठा hns3_nic_priv *priv = netdev_priv(ndev);
	काष्ठा netdev_queue *dev_queue;
	u32 i;

	क्रम (i = 0; i < h->kinfo.num_tqps; i++) अणु
		dev_queue = netdev_get_tx_queue(ndev,
						priv->ring[i].queue_index);
		netdev_tx_reset_queue(dev_queue);
	पूर्ण
पूर्ण

अटल व्योम hns3_nic_net_करोwn(काष्ठा net_device *netdev)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	स्थिर काष्ठा hnae3_ae_ops *ops;
	पूर्णांक i;

	/* disable vectors */
	क्रम (i = 0; i < priv->vector_num; i++)
		hns3_vector_disable(&priv->tqp_vector[i]);

	/* disable rcb */
	क्रम (i = 0; i < h->kinfo.num_tqps; i++)
		hns3_tqp_disable(h->kinfo.tqp[i]);

	/* stop ae_dev */
	ops = priv->ae_handle->ae_algo->ops;
	अगर (ops->stop)
		ops->stop(priv->ae_handle);

	/* delay ring buffer clearing to hns3_reset_notअगरy_uninit_enet
	 * during reset process, because driver may not be able
	 * to disable the ring through firmware when करोwning the netdev.
	 */
	अगर (!hns3_nic_resetting(netdev))
		hns3_clear_all_ring(priv->ae_handle, false);

	hns3_reset_tx_queue(priv->ae_handle);
पूर्ण

अटल पूर्णांक hns3_nic_net_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (test_and_set_bit(HNS3_NIC_STATE_DOWN, &priv->state))
		वापस 0;

	netअगर_dbg(h, drv, netdev, "net stop\n");

	अगर (h->ae_algo->ops->set_समयr_task)
		h->ae_algo->ops->set_समयr_task(priv->ae_handle, false);

	netअगर_carrier_off(netdev);
	netअगर_tx_disable(netdev);

	hns3_nic_net_करोwn(netdev);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_nic_uc_sync(काष्ठा net_device *netdev,
			    स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (h->ae_algo->ops->add_uc_addr)
		वापस h->ae_algo->ops->add_uc_addr(h, addr);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_nic_uc_unsync(काष्ठा net_device *netdev,
			      स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	/* need ignore the request of removing device address, because
	 * we store the device address and other addresses of uc list
	 * in the function's mac filter list.
	 */
	अगर (ether_addr_equal(addr, netdev->dev_addr))
		वापस 0;

	अगर (h->ae_algo->ops->rm_uc_addr)
		वापस h->ae_algo->ops->rm_uc_addr(h, addr);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_nic_mc_sync(काष्ठा net_device *netdev,
			    स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (h->ae_algo->ops->add_mc_addr)
		वापस h->ae_algo->ops->add_mc_addr(h, addr);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_nic_mc_unsync(काष्ठा net_device *netdev,
			      स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (h->ae_algo->ops->rm_mc_addr)
		वापस h->ae_algo->ops->rm_mc_addr(h, addr);

	वापस 0;
पूर्ण

अटल u8 hns3_get_netdev_flags(काष्ठा net_device *netdev)
अणु
	u8 flags = 0;

	अगर (netdev->flags & IFF_PROMISC) अणु
		flags = HNAE3_USER_UPE | HNAE3_USER_MPE | HNAE3_BPE;
	पूर्ण अन्यथा अणु
		flags |= HNAE3_VLAN_FLTR;
		अगर (netdev->flags & IFF_ALLMULTI)
			flags |= HNAE3_USER_MPE;
	पूर्ण

	वापस flags;
पूर्ण

अटल व्योम hns3_nic_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	u8 new_flags;

	new_flags = hns3_get_netdev_flags(netdev);

	__dev_uc_sync(netdev, hns3_nic_uc_sync, hns3_nic_uc_unsync);
	__dev_mc_sync(netdev, hns3_nic_mc_sync, hns3_nic_mc_unsync);

	/* User mode Promisc mode enable and vlan filtering is disabled to
	 * let all packets in.
	 */
	h->netdev_flags = new_flags;
	hns3_request_update_promisc_mode(h);
पूर्ण

व्योम hns3_request_update_promisc_mode(काष्ठा hnae3_handle *handle)
अणु
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;

	अगर (ops->request_update_promisc_mode)
		ops->request_update_promisc_mode(handle);
पूर्ण

व्योम hns3_enable_vlan_filter(काष्ठा net_device *netdev, bool enable)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae3_handle *h = priv->ae_handle;
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(h->pdev);
	bool last_state;

	अगर (ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2 &&
	    h->ae_algo->ops->enable_vlan_filter) अणु
		last_state = h->netdev_flags & HNAE3_VLAN_FLTR ? true : false;
		अगर (enable != last_state) अणु
			netdev_info(netdev,
				    "%s vlan filter\n",
				    enable ? "enable" : "disable");
			h->ae_algo->ops->enable_vlan_filter(h, enable);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_set_tso(काष्ठा sk_buff *skb, u32 *paylen_fकरोp_ol4cs,
			u16 *mss, u32 *type_cs_vlan_tso, u32 *send_bytes)
अणु
	u32 l4_offset, hdr_len;
	जोड़ l3_hdr_info l3;
	जोड़ l4_hdr_info l4;
	u32 l4_paylen;
	पूर्णांक ret;

	अगर (!skb_is_gso(skb))
		वापस 0;

	ret = skb_cow_head(skb, 0);
	अगर (unlikely(ret < 0))
		वापस ret;

	l3.hdr = skb_network_header(skb);
	l4.hdr = skb_transport_header(skb);

	/* Software should clear the IPv4's checksum field when tso is
	 * needed.
	 */
	अगर (l3.v4->version == 4)
		l3.v4->check = 0;

	/* tunnel packet */
	अगर (skb_shinfo(skb)->gso_type & (SKB_GSO_GRE |
					 SKB_GSO_GRE_CSUM |
					 SKB_GSO_UDP_TUNNEL |
					 SKB_GSO_UDP_TUNNEL_CSUM)) अणु
		/* reset l3&l4 poपूर्णांकers from outer to inner headers */
		l3.hdr = skb_inner_network_header(skb);
		l4.hdr = skb_inner_transport_header(skb);

		/* Software should clear the IPv4's checksum field when
		 * tso is needed.
		 */
		अगर (l3.v4->version == 4)
			l3.v4->check = 0;
	पूर्ण

	/* normal or tunnel packet */
	l4_offset = l4.hdr - skb->data;

	/* हटाओ payload length from inner pseuकरो checksum when tso */
	l4_paylen = skb->len - l4_offset;

	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) अणु
		hdr_len = माप(*l4.udp) + l4_offset;
		csum_replace_by_dअगरf(&l4.udp->check,
				     (__क्रमce __wsum)htonl(l4_paylen));
	पूर्ण अन्यथा अणु
		hdr_len = (l4.tcp->करोff << 2) + l4_offset;
		csum_replace_by_dअगरf(&l4.tcp->check,
				     (__क्रमce __wsum)htonl(l4_paylen));
	पूर्ण

	*send_bytes = (skb_shinfo(skb)->gso_segs - 1) * hdr_len + skb->len;

	/* find the txbd field values */
	*paylen_fकरोp_ol4cs = skb->len - hdr_len;
	hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_TSO_B, 1);

	/* offload outer UDP header checksum */
	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM)
		hns3_set_field(*paylen_fकरोp_ol4cs, HNS3_TXD_OL4CS_B, 1);

	/* get MSS क्रम TSO */
	*mss = skb_shinfo(skb)->gso_size;

	trace_hns3_tso(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_get_l4_protocol(काष्ठा sk_buff *skb, u8 *ol4_proto,
				u8 *il4_proto)
अणु
	जोड़ l3_hdr_info l3;
	अचिन्हित अक्षर *l4_hdr;
	अचिन्हित अक्षर *exthdr;
	u8 l4_proto_पंचांगp;
	__be16 frag_off;

	/* find outer header poपूर्णांक */
	l3.hdr = skb_network_header(skb);
	l4_hdr = skb_transport_header(skb);

	अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		exthdr = l3.hdr + माप(*l3.v6);
		l4_proto_पंचांगp = l3.v6->nexthdr;
		अगर (l4_hdr != exthdr)
			ipv6_skip_exthdr(skb, exthdr - skb->data,
					 &l4_proto_पंचांगp, &frag_off);
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IP)) अणु
		l4_proto_पंचांगp = l3.v4->protocol;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	*ol4_proto = l4_proto_पंचांगp;

	/* tunnel packet */
	अगर (!skb->encapsulation) अणु
		*il4_proto = 0;
		वापस 0;
	पूर्ण

	/* find inner header poपूर्णांक */
	l3.hdr = skb_inner_network_header(skb);
	l4_hdr = skb_inner_transport_header(skb);

	अगर (l3.v6->version == 6) अणु
		exthdr = l3.hdr + माप(*l3.v6);
		l4_proto_पंचांगp = l3.v6->nexthdr;
		अगर (l4_hdr != exthdr)
			ipv6_skip_exthdr(skb, exthdr - skb->data,
					 &l4_proto_पंचांगp, &frag_off);
	पूर्ण अन्यथा अगर (l3.v4->version == 4) अणु
		l4_proto_पंचांगp = l3.v4->protocol;
	पूर्ण

	*il4_proto = l4_proto_पंचांगp;

	वापस 0;
पूर्ण

/* when skb->encapsulation is 0, skb->ip_summed is CHECKSUM_PARTIAL
 * and it is udp packet, which has a dest port as the IANA asचिन्हित.
 * the hardware is expected to करो the checksum offload, but the
 * hardware will not करो the checksum offload when udp dest port is
 * 4789, 4790 or 6081.
 */
अटल bool hns3_tunnel_csum_bug(काष्ठा sk_buff *skb)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(skb->dev);
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(priv->ae_handle->pdev);
	जोड़ l4_hdr_info l4;

	/* device version above V3(include V3), the hardware can
	 * करो this checksum offload.
	 */
	अगर (ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V3)
		वापस false;

	l4.hdr = skb_transport_header(skb);

	अगर (!(!skb->encapsulation &&
	      (l4.udp->dest == htons(IANA_VXLAN_UDP_PORT) ||
	      l4.udp->dest == htons(GENEVE_UDP_PORT) ||
	      l4.udp->dest == htons(4790))))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम hns3_set_outer_l2l3l4(काष्ठा sk_buff *skb, u8 ol4_proto,
				  u32 *ol_type_vlan_len_msec)
अणु
	u32 l2_len, l3_len, l4_len;
	अचिन्हित अक्षर *il2_hdr;
	जोड़ l3_hdr_info l3;
	जोड़ l4_hdr_info l4;

	l3.hdr = skb_network_header(skb);
	l4.hdr = skb_transport_header(skb);

	/* compute OL2 header size, defined in 2 Bytes */
	l2_len = l3.hdr - skb->data;
	hns3_set_field(*ol_type_vlan_len_msec, HNS3_TXD_L2LEN_S, l2_len >> 1);

	/* compute OL3 header size, defined in 4 Bytes */
	l3_len = l4.hdr - l3.hdr;
	hns3_set_field(*ol_type_vlan_len_msec, HNS3_TXD_L3LEN_S, l3_len >> 2);

	il2_hdr = skb_inner_mac_header(skb);
	/* compute OL4 header size, defined in 4 Bytes */
	l4_len = il2_hdr - l4.hdr;
	hns3_set_field(*ol_type_vlan_len_msec, HNS3_TXD_L4LEN_S, l4_len >> 2);

	/* define outer network header type */
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		अगर (skb_is_gso(skb))
			hns3_set_field(*ol_type_vlan_len_msec,
				       HNS3_TXD_OL3T_S,
				       HNS3_OL3T_IPV4_CSUM);
		अन्यथा
			hns3_set_field(*ol_type_vlan_len_msec,
				       HNS3_TXD_OL3T_S,
				       HNS3_OL3T_IPV4_NO_CSUM);
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		hns3_set_field(*ol_type_vlan_len_msec, HNS3_TXD_OL3T_S,
			       HNS3_OL3T_IPV6);
	पूर्ण

	अगर (ol4_proto == IPPROTO_UDP)
		hns3_set_field(*ol_type_vlan_len_msec, HNS3_TXD_TUNTYPE_S,
			       HNS3_TUN_MAC_IN_UDP);
	अन्यथा अगर (ol4_proto == IPPROTO_GRE)
		hns3_set_field(*ol_type_vlan_len_msec, HNS3_TXD_TUNTYPE_S,
			       HNS3_TUN_NVGRE);
पूर्ण

अटल पूर्णांक hns3_set_l2l3l4(काष्ठा sk_buff *skb, u8 ol4_proto,
			   u8 il4_proto, u32 *type_cs_vlan_tso,
			   u32 *ol_type_vlan_len_msec)
अणु
	अचिन्हित अक्षर *l2_hdr = skb->data;
	u32 l4_proto = ol4_proto;
	जोड़ l4_hdr_info l4;
	जोड़ l3_hdr_info l3;
	u32 l2_len, l3_len;

	l4.hdr = skb_transport_header(skb);
	l3.hdr = skb_network_header(skb);

	/* handle encapsulation skb */
	अगर (skb->encapsulation) अणु
		/* If this is a not UDP/GRE encapsulation skb */
		अगर (!(ol4_proto == IPPROTO_UDP || ol4_proto == IPPROTO_GRE)) अणु
			/* drop the skb tunnel packet अगर hardware करोn't support,
			 * because hardware can't calculate csum when TSO.
			 */
			अगर (skb_is_gso(skb))
				वापस -गलत_तर्क;

			/* the stack computes the IP header alपढ़ोy,
			 * driver calculate l4 checksum when not TSO.
			 */
			वापस skb_checksum_help(skb);
		पूर्ण

		hns3_set_outer_l2l3l4(skb, ol4_proto, ol_type_vlan_len_msec);

		/* चयन to inner header */
		l2_hdr = skb_inner_mac_header(skb);
		l3.hdr = skb_inner_network_header(skb);
		l4.hdr = skb_inner_transport_header(skb);
		l4_proto = il4_proto;
	पूर्ण

	अगर (l3.v4->version == 4) अणु
		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L3T_S,
			       HNS3_L3T_IPV4);

		/* the stack computes the IP header alपढ़ोy, the only समय we
		 * need the hardware to recompute it is in the हाल of TSO.
		 */
		अगर (skb_is_gso(skb))
			hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L3CS_B, 1);
	पूर्ण अन्यथा अगर (l3.v6->version == 6) अणु
		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L3T_S,
			       HNS3_L3T_IPV6);
	पूर्ण

	/* compute inner(/normal) L2 header size, defined in 2 Bytes */
	l2_len = l3.hdr - l2_hdr;
	hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L2LEN_S, l2_len >> 1);

	/* compute inner(/normal) L3 header size, defined in 4 Bytes */
	l3_len = l4.hdr - l3.hdr;
	hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L3LEN_S, l3_len >> 2);

	/* compute inner(/normal) L4 header size, defined in 4 Bytes */
	चयन (l4_proto) अणु
	हाल IPPROTO_TCP:
		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L4CS_B, 1);
		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L4T_S,
			       HNS3_L4T_TCP);
		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L4LEN_S,
			       l4.tcp->करोff);
		अवरोध;
	हाल IPPROTO_UDP:
		अगर (hns3_tunnel_csum_bug(skb))
			वापस skb_checksum_help(skb);

		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L4CS_B, 1);
		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L4T_S,
			       HNS3_L4T_UDP);
		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L4LEN_S,
			       (माप(काष्ठा udphdr) >> 2));
		अवरोध;
	हाल IPPROTO_SCTP:
		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L4CS_B, 1);
		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L4T_S,
			       HNS3_L4T_SCTP);
		hns3_set_field(*type_cs_vlan_tso, HNS3_TXD_L4LEN_S,
			       (माप(काष्ठा sctphdr) >> 2));
		अवरोध;
	शेष:
		/* drop the skb tunnel packet अगर hardware करोn't support,
		 * because hardware can't calculate csum when TSO.
		 */
		अगर (skb_is_gso(skb))
			वापस -गलत_तर्क;

		/* the stack computes the IP header alपढ़ोy,
		 * driver calculate l4 checksum when not TSO.
		 */
		वापस skb_checksum_help(skb);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_handle_vtags(काष्ठा hns3_enet_ring *tx_ring,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा hnae3_handle *handle = tx_ring->tqp->handle;
	काष्ठा hnae3_ae_dev *ae_dev;
	काष्ठा vlan_ethhdr *vhdr;
	पूर्णांक rc;

	अगर (!(skb->protocol == htons(ETH_P_8021Q) ||
	      skb_vlan_tag_present(skb)))
		वापस 0;

	/* For HW limitation on HNAE3_DEVICE_VERSION_V2, अगर port based insert
	 * VLAN enabled, only one VLAN header is allowed in skb, otherwise it
	 * will cause RAS error.
	 */
	ae_dev = pci_get_drvdata(handle->pdev);
	अगर (unlikely(skb_vlan_tagged_multi(skb) &&
		     ae_dev->dev_version <= HNAE3_DEVICE_VERSION_V2 &&
		     handle->port_base_vlan_state ==
		     HNAE3_PORT_BASE_VLAN_ENABLE))
		वापस -EINVAL;

	अगर (skb->protocol == htons(ETH_P_8021Q) &&
	    !(handle->kinfo.netdev->features & NETIF_F_HW_VLAN_CTAG_TX)) अणु
		/* When HW VLAN acceleration is turned off, and the stack
		 * sets the protocol to 802.1q, the driver just need to
		 * set the protocol to the encapsulated ethertype.
		 */
		skb->protocol = vlan_get_protocol(skb);
		वापस 0;
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		/* Based on hw strategy, use out_vtag in two layer tag हाल,
		 * and use inner_vtag in one tag हाल.
		 */
		अगर (skb->protocol == htons(ETH_P_8021Q) &&
		    handle->port_base_vlan_state ==
		    HNAE3_PORT_BASE_VLAN_DISABLE)
			rc = HNS3_OUTER_VLAN_TAG;
		अन्यथा
			rc = HNS3_INNER_VLAN_TAG;

		skb->protocol = vlan_get_protocol(skb);
		वापस rc;
	पूर्ण

	rc = skb_cow_head(skb, 0);
	अगर (unlikely(rc < 0))
		वापस rc;

	vhdr = (काष्ठा vlan_ethhdr *)skb->data;
	vhdr->h_vlan_TCI |= cpu_to_be16((skb->priority << VLAN_PRIO_SHIFT)
					 & VLAN_PRIO_MASK);

	skb->protocol = vlan_get_protocol(skb);
	वापस 0;
पूर्ण

/* check अगर the hardware is capable of checksum offloading */
अटल bool hns3_check_hw_tx_csum(काष्ठा sk_buff *skb)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(skb->dev);

	/* Kindly note, due to backward compatibility of the TX descriptor,
	 * HW checksum of the non-IP packets and GSO packets is handled at
	 * dअगरferent place in the following code
	 */
	अगर (skb_csum_is_sctp(skb) || skb_is_gso(skb) ||
	    !test_bit(HNS3_NIC_STATE_HW_TX_CSUM_ENABLE, &priv->state))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक hns3_fill_skb_desc(काष्ठा hns3_enet_ring *ring,
			      काष्ठा sk_buff *skb, काष्ठा hns3_desc *desc,
			      काष्ठा hns3_desc_cb *desc_cb)
अणु
	u32 ol_type_vlan_len_msec = 0;
	u32 paylen_ol4cs = skb->len;
	u32 type_cs_vlan_tso = 0;
	u16 mss_hw_csum = 0;
	u16 inner_vtag = 0;
	u16 out_vtag = 0;
	पूर्णांक ret;

	ret = hns3_handle_vtags(ring, skb);
	अगर (unlikely(ret < 0)) अणु
		u64_stats_update_begin(&ring->syncp);
		ring->stats.tx_vlan_err++;
		u64_stats_update_end(&ring->syncp);
		वापस ret;
	पूर्ण अन्यथा अगर (ret == HNS3_INNER_VLAN_TAG) अणु
		inner_vtag = skb_vlan_tag_get(skb);
		inner_vtag |= (skb->priority << VLAN_PRIO_SHIFT) &
				VLAN_PRIO_MASK;
		hns3_set_field(type_cs_vlan_tso, HNS3_TXD_VLAN_B, 1);
	पूर्ण अन्यथा अगर (ret == HNS3_OUTER_VLAN_TAG) अणु
		out_vtag = skb_vlan_tag_get(skb);
		out_vtag |= (skb->priority << VLAN_PRIO_SHIFT) &
				VLAN_PRIO_MASK;
		hns3_set_field(ol_type_vlan_len_msec, HNS3_TXD_OVLAN_B,
			       1);
	पूर्ण

	desc_cb->send_bytes = skb->len;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		u8 ol4_proto, il4_proto;

		अगर (hns3_check_hw_tx_csum(skb)) अणु
			/* set checksum start and offset, defined in 2 Bytes */
			hns3_set_field(type_cs_vlan_tso, HNS3_TXD_CSUM_START_S,
				       skb_checksum_start_offset(skb) >> 1);
			hns3_set_field(ol_type_vlan_len_msec,
				       HNS3_TXD_CSUM_OFFSET_S,
				       skb->csum_offset >> 1);
			mss_hw_csum |= BIT(HNS3_TXD_HW_CS_B);
			जाओ out_hw_tx_csum;
		पूर्ण

		skb_reset_mac_len(skb);

		ret = hns3_get_l4_protocol(skb, &ol4_proto, &il4_proto);
		अगर (unlikely(ret < 0)) अणु
			u64_stats_update_begin(&ring->syncp);
			ring->stats.tx_l4_proto_err++;
			u64_stats_update_end(&ring->syncp);
			वापस ret;
		पूर्ण

		ret = hns3_set_l2l3l4(skb, ol4_proto, il4_proto,
				      &type_cs_vlan_tso,
				      &ol_type_vlan_len_msec);
		अगर (unlikely(ret < 0)) अणु
			u64_stats_update_begin(&ring->syncp);
			ring->stats.tx_l2l3l4_err++;
			u64_stats_update_end(&ring->syncp);
			वापस ret;
		पूर्ण

		ret = hns3_set_tso(skb, &paylen_ol4cs, &mss_hw_csum,
				   &type_cs_vlan_tso, &desc_cb->send_bytes);
		अगर (unlikely(ret < 0)) अणु
			u64_stats_update_begin(&ring->syncp);
			ring->stats.tx_tso_err++;
			u64_stats_update_end(&ring->syncp);
			वापस ret;
		पूर्ण
	पूर्ण

out_hw_tx_csum:
	/* Set txbd */
	desc->tx.ol_type_vlan_len_msec =
		cpu_to_le32(ol_type_vlan_len_msec);
	desc->tx.type_cs_vlan_tso_len = cpu_to_le32(type_cs_vlan_tso);
	desc->tx.paylen_ol4cs = cpu_to_le32(paylen_ol4cs);
	desc->tx.mss_hw_csum = cpu_to_le16(mss_hw_csum);
	desc->tx.vlan_tag = cpu_to_le16(inner_vtag);
	desc->tx.outer_vlan_tag = cpu_to_le16(out_vtag);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_fill_desc(काष्ठा hns3_enet_ring *ring, व्योम *priv,
			  अचिन्हित पूर्णांक size, क्रमागत hns_desc_type type)
अणु
#घोषणा HNS3_LIKELY_BD_NUM	1

	काष्ठा hns3_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_use];
	काष्ठा hns3_desc *desc = &ring->desc[ring->next_to_use];
	काष्ठा device *dev = ring_to_dev(ring);
	skb_frag_t *frag;
	अचिन्हित पूर्णांक frag_buf_num;
	पूर्णांक k, मापlast;
	dma_addr_t dma;

	अगर (type == DESC_TYPE_FRAGLIST_SKB ||
	    type == DESC_TYPE_SKB) अणु
		काष्ठा sk_buff *skb = (काष्ठा sk_buff *)priv;

		dma = dma_map_single(dev, skb->data, size, DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		frag = (skb_frag_t *)priv;
		dma = skb_frag_dma_map(dev, frag, 0, size, DMA_TO_DEVICE);
	पूर्ण

	अगर (unlikely(dma_mapping_error(dev, dma))) अणु
		u64_stats_update_begin(&ring->syncp);
		ring->stats.sw_err_cnt++;
		u64_stats_update_end(&ring->syncp);
		वापस -ENOMEM;
	पूर्ण

	desc_cb->priv = priv;
	desc_cb->length = size;
	desc_cb->dma = dma;
	desc_cb->type = type;

	अगर (likely(size <= HNS3_MAX_BD_SIZE)) अणु
		desc->addr = cpu_to_le64(dma);
		desc->tx.send_size = cpu_to_le16(size);
		desc->tx.bdtp_fe_sc_vld_ra_ri =
			cpu_to_le16(BIT(HNS3_TXD_VLD_B));

		trace_hns3_tx_desc(ring, ring->next_to_use);
		ring_ptr_move_fw(ring, next_to_use);
		वापस HNS3_LIKELY_BD_NUM;
	पूर्ण

	frag_buf_num = hns3_tx_bd_count(size);
	मापlast = size % HNS3_MAX_BD_SIZE;
	मापlast = मापlast ? मापlast : HNS3_MAX_BD_SIZE;

	/* When frag size is bigger than hardware limit, split this frag */
	क्रम (k = 0; k < frag_buf_num; k++) अणु
		/* now, fill the descriptor */
		desc->addr = cpu_to_le64(dma + HNS3_MAX_BD_SIZE * k);
		desc->tx.send_size = cpu_to_le16((k == frag_buf_num - 1) ?
				     (u16)मापlast : (u16)HNS3_MAX_BD_SIZE);
		desc->tx.bdtp_fe_sc_vld_ra_ri =
				cpu_to_le16(BIT(HNS3_TXD_VLD_B));

		trace_hns3_tx_desc(ring, ring->next_to_use);
		/* move ring poपूर्णांकer to next */
		ring_ptr_move_fw(ring, next_to_use);

		desc = &ring->desc[ring->next_to_use];
	पूर्ण

	वापस frag_buf_num;
पूर्ण

अटल अचिन्हित पूर्णांक hns3_skb_bd_num(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक *bd_size,
				    अचिन्हित पूर्णांक bd_num)
अणु
	अचिन्हित पूर्णांक size;
	पूर्णांक i;

	size = skb_headlen(skb);
	जबतक (size > HNS3_MAX_BD_SIZE) अणु
		bd_size[bd_num++] = HNS3_MAX_BD_SIZE;
		size -= HNS3_MAX_BD_SIZE;

		अगर (bd_num > HNS3_MAX_TSO_BD_NUM)
			वापस bd_num;
	पूर्ण

	अगर (size) अणु
		bd_size[bd_num++] = size;
		अगर (bd_num > HNS3_MAX_TSO_BD_NUM)
			वापस bd_num;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		size = skb_frag_size(frag);
		अगर (!size)
			जारी;

		जबतक (size > HNS3_MAX_BD_SIZE) अणु
			bd_size[bd_num++] = HNS3_MAX_BD_SIZE;
			size -= HNS3_MAX_BD_SIZE;

			अगर (bd_num > HNS3_MAX_TSO_BD_NUM)
				वापस bd_num;
		पूर्ण

		bd_size[bd_num++] = size;
		अगर (bd_num > HNS3_MAX_TSO_BD_NUM)
			वापस bd_num;
	पूर्ण

	वापस bd_num;
पूर्ण

अटल अचिन्हित पूर्णांक hns3_tx_bd_num(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक *bd_size,
				   u8 max_non_tso_bd_num, अचिन्हित पूर्णांक bd_num,
				   अचिन्हित पूर्णांक recursion_level)
अणु
#घोषणा HNS3_MAX_RECURSION_LEVEL	24

	काष्ठा sk_buff *frag_skb;

	/* If the total len is within the max bd limit */
	अगर (likely(skb->len <= HNS3_MAX_BD_SIZE && !recursion_level &&
		   !skb_has_frag_list(skb) &&
		   skb_shinfo(skb)->nr_frags < max_non_tso_bd_num))
		वापस skb_shinfo(skb)->nr_frags + 1U;

	अगर (unlikely(recursion_level >= HNS3_MAX_RECURSION_LEVEL))
		वापस अच_पूर्णांक_उच्च;

	bd_num = hns3_skb_bd_num(skb, bd_size, bd_num);
	अगर (!skb_has_frag_list(skb) || bd_num > HNS3_MAX_TSO_BD_NUM)
		वापस bd_num;

	skb_walk_frags(skb, frag_skb) अणु
		bd_num = hns3_tx_bd_num(frag_skb, bd_size, max_non_tso_bd_num,
					bd_num, recursion_level + 1);
		अगर (bd_num > HNS3_MAX_TSO_BD_NUM)
			वापस bd_num;
	पूर्ण

	वापस bd_num;
पूर्ण

अटल अचिन्हित पूर्णांक hns3_gso_hdr_len(काष्ठा sk_buff *skb)
अणु
	अगर (!skb->encapsulation)
		वापस skb_transport_offset(skb) + tcp_hdrlen(skb);

	वापस skb_inner_transport_offset(skb) + inner_tcp_hdrlen(skb);
पूर्ण

/* HW need every continuous max_non_tso_bd_num buffer data to be larger
 * than MSS, we simplअगरy it by ensuring skb_headlen + the first continuous
 * max_non_tso_bd_num - 1 frags to be larger than gso header len + mss,
 * and the reमुख्यing continuous max_non_tso_bd_num - 1 frags to be larger
 * than MSS except the last max_non_tso_bd_num - 1 frags.
 */
अटल bool hns3_skb_need_linearized(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक *bd_size,
				     अचिन्हित पूर्णांक bd_num, u8 max_non_tso_bd_num)
अणु
	अचिन्हित पूर्णांक tot_len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < max_non_tso_bd_num - 1U; i++)
		tot_len += bd_size[i];

	/* ensure the first max_non_tso_bd_num frags is greater than
	 * mss + header
	 */
	अगर (tot_len + bd_size[max_non_tso_bd_num - 1U] <
	    skb_shinfo(skb)->gso_size + hns3_gso_hdr_len(skb))
		वापस true;

	/* ensure every continuous max_non_tso_bd_num - 1 buffer is greater
	 * than mss except the last one.
	 */
	क्रम (i = 0; i < bd_num - max_non_tso_bd_num; i++) अणु
		tot_len -= bd_size[i];
		tot_len += bd_size[i + max_non_tso_bd_num - 1U];

		अगर (tot_len < skb_shinfo(skb)->gso_size)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम hns3_shinfo_pack(काष्ठा skb_shared_info *shinfo, __u32 *size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_SKB_FRAGS; i++)
		size[i] = skb_frag_size(&shinfo->frags[i]);
पूर्ण

अटल पूर्णांक hns3_skb_linearize(काष्ठा hns3_enet_ring *ring,
			      काष्ठा sk_buff *skb,
			      u8 max_non_tso_bd_num,
			      अचिन्हित पूर्णांक bd_num)
अणु
	/* 'bd_num == UINT_MAX' means the skb' fraglist has a
	 * recursion level of over HNS3_MAX_RECURSION_LEVEL.
	 */
	अगर (bd_num == अच_पूर्णांक_उच्च) अणु
		u64_stats_update_begin(&ring->syncp);
		ring->stats.over_max_recursion++;
		u64_stats_update_end(&ring->syncp);
		वापस -ENOMEM;
	पूर्ण

	/* The skb->len has exceeded the hw limitation, linearization
	 * will not help.
	 */
	अगर (skb->len > HNS3_MAX_TSO_SIZE ||
	    (!skb_is_gso(skb) && skb->len >
	     HNS3_MAX_NON_TSO_SIZE(max_non_tso_bd_num))) अणु
		u64_stats_update_begin(&ring->syncp);
		ring->stats.hw_limitation++;
		u64_stats_update_end(&ring->syncp);
		वापस -ENOMEM;
	पूर्ण

	अगर (__skb_linearize(skb)) अणु
		u64_stats_update_begin(&ring->syncp);
		ring->stats.sw_err_cnt++;
		u64_stats_update_end(&ring->syncp);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_nic_maybe_stop_tx(काष्ठा hns3_enet_ring *ring,
				  काष्ठा net_device *netdev,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	u8 max_non_tso_bd_num = priv->max_non_tso_bd_num;
	अचिन्हित पूर्णांक bd_size[HNS3_MAX_TSO_BD_NUM + 1U];
	अचिन्हित पूर्णांक bd_num;

	bd_num = hns3_tx_bd_num(skb, bd_size, max_non_tso_bd_num, 0, 0);
	अगर (unlikely(bd_num > max_non_tso_bd_num)) अणु
		अगर (bd_num <= HNS3_MAX_TSO_BD_NUM && skb_is_gso(skb) &&
		    !hns3_skb_need_linearized(skb, bd_size, bd_num,
					      max_non_tso_bd_num)) अणु
			trace_hns3_over_max_bd(skb);
			जाओ out;
		पूर्ण

		अगर (hns3_skb_linearize(ring, skb, max_non_tso_bd_num,
				       bd_num))
			वापस -ENOMEM;

		bd_num = hns3_tx_bd_count(skb->len);

		u64_stats_update_begin(&ring->syncp);
		ring->stats.tx_copy++;
		u64_stats_update_end(&ring->syncp);
	पूर्ण

out:
	अगर (likely(ring_space(ring) >= bd_num))
		वापस bd_num;

	netअगर_stop_subqueue(netdev, ring->queue_index);
	smp_mb(); /* Memory barrier beक्रमe checking ring_space */

	/* Start queue in हाल hns3_clean_tx_ring has just made room
	 * available and has not seen the queue stopped state perक्रमmed
	 * by netअगर_stop_subqueue above.
	 */
	अगर (ring_space(ring) >= bd_num && netअगर_carrier_ok(netdev) &&
	    !test_bit(HNS3_NIC_STATE_DOWN, &priv->state)) अणु
		netअगर_start_subqueue(netdev, ring->queue_index);
		वापस bd_num;
	पूर्ण

	u64_stats_update_begin(&ring->syncp);
	ring->stats.tx_busy++;
	u64_stats_update_end(&ring->syncp);

	वापस -EBUSY;
पूर्ण

अटल व्योम hns3_clear_desc(काष्ठा hns3_enet_ring *ring, पूर्णांक next_to_use_orig)
अणु
	काष्ठा device *dev = ring_to_dev(ring);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ring->desc_num; i++) अणु
		काष्ठा hns3_desc *desc = &ring->desc[ring->next_to_use];

		स_रखो(desc, 0, माप(*desc));

		/* check अगर this is where we started */
		अगर (ring->next_to_use == next_to_use_orig)
			अवरोध;

		/* rollback one */
		ring_ptr_move_bw(ring, next_to_use);

		अगर (!ring->desc_cb[ring->next_to_use].dma)
			जारी;

		/* unmap the descriptor dma address */
		अगर (ring->desc_cb[ring->next_to_use].type == DESC_TYPE_SKB ||
		    ring->desc_cb[ring->next_to_use].type ==
		    DESC_TYPE_FRAGLIST_SKB)
			dma_unmap_single(dev,
					 ring->desc_cb[ring->next_to_use].dma,
					ring->desc_cb[ring->next_to_use].length,
					DMA_TO_DEVICE);
		अन्यथा अगर (ring->desc_cb[ring->next_to_use].length)
			dma_unmap_page(dev,
				       ring->desc_cb[ring->next_to_use].dma,
				       ring->desc_cb[ring->next_to_use].length,
				       DMA_TO_DEVICE);

		ring->desc_cb[ring->next_to_use].length = 0;
		ring->desc_cb[ring->next_to_use].dma = 0;
		ring->desc_cb[ring->next_to_use].type = DESC_TYPE_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_fill_skb_to_desc(काष्ठा hns3_enet_ring *ring,
				 काष्ठा sk_buff *skb, क्रमागत hns_desc_type type)
अणु
	अचिन्हित पूर्णांक size = skb_headlen(skb);
	काष्ठा sk_buff *frag_skb;
	पूर्णांक i, ret, bd_num = 0;

	अगर (size) अणु
		ret = hns3_fill_desc(ring, skb, size, type);
		अगर (unlikely(ret < 0))
			वापस ret;

		bd_num += ret;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		size = skb_frag_size(frag);
		अगर (!size)
			जारी;

		ret = hns3_fill_desc(ring, frag, size, DESC_TYPE_PAGE);
		अगर (unlikely(ret < 0))
			वापस ret;

		bd_num += ret;
	पूर्ण

	skb_walk_frags(skb, frag_skb) अणु
		ret = hns3_fill_skb_to_desc(ring, frag_skb,
					    DESC_TYPE_FRAGLIST_SKB);
		अगर (unlikely(ret < 0))
			वापस ret;

		bd_num += ret;
	पूर्ण

	वापस bd_num;
पूर्ण

अटल व्योम hns3_tx_करोorbell(काष्ठा hns3_enet_ring *ring, पूर्णांक num,
			     bool करोorbell)
अणु
	ring->pending_buf += num;

	अगर (!करोorbell) अणु
		u64_stats_update_begin(&ring->syncp);
		ring->stats.tx_more++;
		u64_stats_update_end(&ring->syncp);
		वापस;
	पूर्ण

	अगर (!ring->pending_buf)
		वापस;

	ग_लिखोl(ring->pending_buf,
	       ring->tqp->io_base + HNS3_RING_TX_RING_TAIL_REG);
	ring->pending_buf = 0;
	WRITE_ONCE(ring->last_to_use, ring->next_to_use);
पूर्ण

netdev_tx_t hns3_nic_net_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hns3_enet_ring *ring = &priv->ring[skb->queue_mapping];
	काष्ठा hns3_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_use];
	काष्ठा netdev_queue *dev_queue;
	पूर्णांक pre_ntu, next_to_use_head;
	bool करोorbell;
	पूर्णांक ret;

	/* Hardware can only handle लघु frames above 32 bytes */
	अगर (skb_put_padto(skb, HNS3_MIN_TX_LEN)) अणु
		hns3_tx_करोorbell(ring, 0, !netdev_xmit_more());

		u64_stats_update_begin(&ring->syncp);
		ring->stats.sw_err_cnt++;
		u64_stats_update_end(&ring->syncp);

		वापस NETDEV_TX_OK;
	पूर्ण

	/* Prefetch the data used later */
	prefetch(skb->data);

	ret = hns3_nic_maybe_stop_tx(ring, netdev, skb);
	अगर (unlikely(ret <= 0)) अणु
		अगर (ret == -EBUSY) अणु
			hns3_tx_करोorbell(ring, 0, true);
			वापस NETDEV_TX_BUSY;
		पूर्ण

		hns3_rl_err(netdev, "xmit error: %d!\n", ret);
		जाओ out_err_tx_ok;
	पूर्ण

	next_to_use_head = ring->next_to_use;

	ret = hns3_fill_skb_desc(ring, skb, &ring->desc[ring->next_to_use],
				 desc_cb);
	अगर (unlikely(ret < 0))
		जाओ fill_err;

	/* 'ret < 0' means filling error, 'ret == 0' means skb->len is
	 * zero, which is unlikely, and 'ret > 0' means how many tx desc
	 * need to be notअगरied to the hw.
	 */
	ret = hns3_fill_skb_to_desc(ring, skb, DESC_TYPE_SKB);
	अगर (unlikely(ret <= 0))
		जाओ fill_err;

	pre_ntu = ring->next_to_use ? (ring->next_to_use - 1) :
					(ring->desc_num - 1);
	ring->desc[pre_ntu].tx.bdtp_fe_sc_vld_ra_ri |=
				cpu_to_le16(BIT(HNS3_TXD_FE_B));
	trace_hns3_tx_desc(ring, pre_ntu);

	/* Complete translate all packets */
	dev_queue = netdev_get_tx_queue(netdev, ring->queue_index);
	करोorbell = __netdev_tx_sent_queue(dev_queue, desc_cb->send_bytes,
					  netdev_xmit_more());
	hns3_tx_करोorbell(ring, ret, करोorbell);

	वापस NETDEV_TX_OK;

fill_err:
	hns3_clear_desc(ring, next_to_use_head);

out_err_tx_ok:
	dev_kमुक्त_skb_any(skb);
	hns3_tx_करोorbell(ring, 0, !netdev_xmit_more());
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक hns3_nic_net_set_mac_address(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा sockaddr *mac_addr = p;
	पूर्णांक ret;

	अगर (!mac_addr || !is_valid_ether_addr((स्थिर u8 *)mac_addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (ether_addr_equal(netdev->dev_addr, mac_addr->sa_data)) अणु
		netdev_info(netdev, "already using mac address %pM\n",
			    mac_addr->sa_data);
		वापस 0;
	पूर्ण

	/* For VF device, अगर there is a perm_addr, then the user will not
	 * be allowed to change the address.
	 */
	अगर (!hns3_is_phys_func(h->pdev) &&
	    !is_zero_ether_addr(netdev->perm_addr)) अणु
		netdev_err(netdev, "has permanent MAC %pM, user MAC %pM not allow\n",
			   netdev->perm_addr, mac_addr->sa_data);
		वापस -EPERM;
	पूर्ण

	ret = h->ae_algo->ops->set_mac_addr(h, mac_addr->sa_data, false);
	अगर (ret) अणु
		netdev_err(netdev, "set_mac_address fail, ret=%d!\n", ret);
		वापस ret;
	पूर्ण

	ether_addr_copy(netdev->dev_addr, mac_addr->sa_data);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_nic_करो_ioctl(काष्ठा net_device *netdev,
			     काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (!netअगर_running(netdev))
		वापस -EINVAL;

	अगर (!h->ae_algo->ops->करो_ioctl)
		वापस -EOPNOTSUPP;

	वापस h->ae_algo->ops->करो_ioctl(h, अगरr, cmd);
पूर्ण

अटल पूर्णांक hns3_nic_set_features(काष्ठा net_device *netdev,
				 netdev_features_t features)
अणु
	netdev_features_t changed = netdev->features ^ features;
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae3_handle *h = priv->ae_handle;
	bool enable;
	पूर्णांक ret;

	अगर (changed & (NETIF_F_GRO_HW) && h->ae_algo->ops->set_gro_en) अणु
		enable = !!(features & NETIF_F_GRO_HW);
		ret = h->ae_algo->ops->set_gro_en(h, enable);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर ((changed & NETIF_F_HW_VLAN_CTAG_RX) &&
	    h->ae_algo->ops->enable_hw_strip_rxvtag) अणु
		enable = !!(features & NETIF_F_HW_VLAN_CTAG_RX);
		ret = h->ae_algo->ops->enable_hw_strip_rxvtag(h, enable);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर ((changed & NETIF_F_NTUPLE) && h->ae_algo->ops->enable_fd) अणु
		enable = !!(features & NETIF_F_NTUPLE);
		h->ae_algo->ops->enable_fd(h, enable);
	पूर्ण

	अगर ((netdev->features & NETIF_F_HW_TC) > (features & NETIF_F_HW_TC) &&
	    h->ae_algo->ops->cls_flower_active(h)) अणु
		netdev_err(netdev,
			   "there are offloaded TC filters active, cannot disable HW TC offload");
		वापस -EINVAL;
	पूर्ण

	netdev->features = features;
	वापस 0;
पूर्ण

अटल netdev_features_t hns3_features_check(काष्ठा sk_buff *skb,
					     काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
#घोषणा HNS3_MAX_HDR_LEN	480U
#घोषणा HNS3_MAX_L4_HDR_LEN	60U

	माप_प्रकार len;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस features;

	अगर (skb->encapsulation)
		len = skb_inner_transport_header(skb) - skb->data;
	अन्यथा
		len = skb_transport_header(skb) - skb->data;

	/* Assume L4 is 60 byte as TCP is the only protocol with a
	 * a flexible value, and it's max len is 60 bytes.
	 */
	len += HNS3_MAX_L4_HDR_LEN;

	/* Hardware only supports checksum on the skb with a max header
	 * len of 480 bytes.
	 */
	अगर (len > HNS3_MAX_HDR_LEN)
		features &= ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);

	वापस features;
पूर्ण

अटल व्योम hns3_nic_get_stats64(काष्ठा net_device *netdev,
				 काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	पूर्णांक queue_num = priv->ae_handle->kinfo.num_tqps;
	काष्ठा hnae3_handle *handle = priv->ae_handle;
	काष्ठा hns3_enet_ring *ring;
	u64 rx_length_errors = 0;
	u64 rx_crc_errors = 0;
	u64 rx_multicast = 0;
	अचिन्हित पूर्णांक start;
	u64 tx_errors = 0;
	u64 rx_errors = 0;
	अचिन्हित पूर्णांक idx;
	u64 tx_bytes = 0;
	u64 rx_bytes = 0;
	u64 tx_pkts = 0;
	u64 rx_pkts = 0;
	u64 tx_drop = 0;
	u64 rx_drop = 0;

	अगर (test_bit(HNS3_NIC_STATE_DOWN, &priv->state))
		वापस;

	handle->ae_algo->ops->update_stats(handle, &netdev->stats);

	क्रम (idx = 0; idx < queue_num; idx++) अणु
		/* fetch the tx stats */
		ring = &priv->ring[idx];
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			tx_bytes += ring->stats.tx_bytes;
			tx_pkts += ring->stats.tx_pkts;
			tx_drop += ring->stats.sw_err_cnt;
			tx_drop += ring->stats.tx_vlan_err;
			tx_drop += ring->stats.tx_l4_proto_err;
			tx_drop += ring->stats.tx_l2l3l4_err;
			tx_drop += ring->stats.tx_tso_err;
			tx_drop += ring->stats.over_max_recursion;
			tx_drop += ring->stats.hw_limitation;
			tx_errors += ring->stats.sw_err_cnt;
			tx_errors += ring->stats.tx_vlan_err;
			tx_errors += ring->stats.tx_l4_proto_err;
			tx_errors += ring->stats.tx_l2l3l4_err;
			tx_errors += ring->stats.tx_tso_err;
			tx_errors += ring->stats.over_max_recursion;
			tx_errors += ring->stats.hw_limitation;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));

		/* fetch the rx stats */
		ring = &priv->ring[idx + queue_num];
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			rx_bytes += ring->stats.rx_bytes;
			rx_pkts += ring->stats.rx_pkts;
			rx_drop += ring->stats.l2_err;
			rx_errors += ring->stats.l2_err;
			rx_errors += ring->stats.l3l4_csum_err;
			rx_crc_errors += ring->stats.l2_err;
			rx_multicast += ring->stats.rx_multicast;
			rx_length_errors += ring->stats.err_pkt_len;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
	पूर्ण

	stats->tx_bytes = tx_bytes;
	stats->tx_packets = tx_pkts;
	stats->rx_bytes = rx_bytes;
	stats->rx_packets = rx_pkts;

	stats->rx_errors = rx_errors;
	stats->multicast = rx_multicast;
	stats->rx_length_errors = rx_length_errors;
	stats->rx_crc_errors = rx_crc_errors;
	stats->rx_missed_errors = netdev->stats.rx_missed_errors;

	stats->tx_errors = tx_errors;
	stats->rx_dropped = rx_drop;
	stats->tx_dropped = tx_drop;
	stats->collisions = netdev->stats.collisions;
	stats->rx_over_errors = netdev->stats.rx_over_errors;
	stats->rx_frame_errors = netdev->stats.rx_frame_errors;
	stats->rx_fअगरo_errors = netdev->stats.rx_fअगरo_errors;
	stats->tx_पातed_errors = netdev->stats.tx_पातed_errors;
	stats->tx_carrier_errors = netdev->stats.tx_carrier_errors;
	stats->tx_fअगरo_errors = netdev->stats.tx_fअगरo_errors;
	stats->tx_heartbeat_errors = netdev->stats.tx_heartbeat_errors;
	stats->tx_winकरोw_errors = netdev->stats.tx_winकरोw_errors;
	stats->rx_compressed = netdev->stats.rx_compressed;
	stats->tx_compressed = netdev->stats.tx_compressed;
पूर्ण

अटल पूर्णांक hns3_setup_tc(काष्ठा net_device *netdev, व्योम *type_data)
अणु
	काष्ठा tc_mqprio_qopt_offload *mqprio_qopt = type_data;
	काष्ठा hnae3_knic_निजी_info *kinfo;
	u8 tc = mqprio_qopt->qopt.num_tc;
	u16 mode = mqprio_qopt->mode;
	u8 hw = mqprio_qopt->qopt.hw;
	काष्ठा hnae3_handle *h;

	अगर (!((hw == TC_MQPRIO_HW_OFFLOAD_TCS &&
	       mode == TC_MQPRIO_MODE_CHANNEL) || (!hw && tc == 0)))
		वापस -EOPNOTSUPP;

	अगर (tc > HNAE3_MAX_TC)
		वापस -EINVAL;

	अगर (!netdev)
		वापस -EINVAL;

	h = hns3_get_handle(netdev);
	kinfo = &h->kinfo;

	netअगर_dbg(h, drv, netdev, "setup tc: num_tc=%u\n", tc);

	वापस (kinfo->dcb_ops && kinfo->dcb_ops->setup_tc) ?
		kinfo->dcb_ops->setup_tc(h, mqprio_qopt) : -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hns3_setup_tc_cls_flower(काष्ठा hns3_nic_priv *priv,
				    काष्ठा flow_cls_offload *flow)
अणु
	पूर्णांक tc = tc_classid_to_hwtc(priv->netdev, flow->classid);
	काष्ठा hnae3_handle *h = hns3_get_handle(priv->netdev);

	चयन (flow->command) अणु
	हाल FLOW_CLS_REPLACE:
		अगर (h->ae_algo->ops->add_cls_flower)
			वापस h->ae_algo->ops->add_cls_flower(h, flow, tc);
		अवरोध;
	हाल FLOW_CLS_DESTROY:
		अगर (h->ae_algo->ops->del_cls_flower)
			वापस h->ae_algo->ops->del_cls_flower(h, flow);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hns3_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				  व्योम *cb_priv)
अणु
	काष्ठा hns3_nic_priv *priv = cb_priv;

	अगर (!tc_cls_can_offload_and_chain0(priv->netdev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस hns3_setup_tc_cls_flower(priv, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल LIST_HEAD(hns3_block_cb_list);

अटल पूर्णांक hns3_nic_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			     व्योम *type_data)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(dev);
	पूर्णांक ret;

	चयन (type) अणु
	हाल TC_SETUP_QDISC_MQPRIO:
		ret = hns3_setup_tc(dev, type_data);
		अवरोध;
	हाल TC_SETUP_BLOCK:
		ret = flow_block_cb_setup_simple(type_data,
						 &hns3_block_cb_list,
						 hns3_setup_tc_block_cb,
						 priv, priv, true);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_vlan_rx_add_vid(काष्ठा net_device *netdev,
				__be16 proto, u16 vid)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	पूर्णांक ret = -EIO;

	अगर (h->ae_algo->ops->set_vlan_filter)
		ret = h->ae_algo->ops->set_vlan_filter(h, proto, vid, false);

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				 __be16 proto, u16 vid)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	पूर्णांक ret = -EIO;

	अगर (h->ae_algo->ops->set_vlan_filter)
		ret = h->ae_algo->ops->set_vlan_filter(h, proto, vid, true);

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_nकरो_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf, u16 vlan,
				u8 qos, __be16 vlan_proto)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	पूर्णांक ret = -EIO;

	netअगर_dbg(h, drv, netdev,
		  "set vf vlan: vf=%d, vlan=%u, qos=%u, vlan_proto=0x%x\n",
		  vf, vlan, qos, ntohs(vlan_proto));

	अगर (h->ae_algo->ops->set_vf_vlan_filter)
		ret = h->ae_algo->ops->set_vf_vlan_filter(h, vf, vlan,
							  qos, vlan_proto);

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf, bool enable)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);

	अगर (hns3_nic_resetting(netdev))
		वापस -EBUSY;

	अगर (!handle->ae_algo->ops->set_vf_spoofchk)
		वापस -EOPNOTSUPP;

	वापस handle->ae_algo->ops->set_vf_spoofchk(handle, vf, enable);
पूर्ण

अटल पूर्णांक hns3_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf, bool enable)
अणु
	काष्ठा hnae3_handle *handle = hns3_get_handle(netdev);

	अगर (!handle->ae_algo->ops->set_vf_trust)
		वापस -EOPNOTSUPP;

	वापस handle->ae_algo->ops->set_vf_trust(handle, vf, enable);
पूर्ण

अटल पूर्णांक hns3_nic_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	पूर्णांक ret;

	अगर (hns3_nic_resetting(netdev))
		वापस -EBUSY;

	अगर (!h->ae_algo->ops->set_mtu)
		वापस -EOPNOTSUPP;

	netअगर_dbg(h, drv, netdev,
		  "change mtu from %u to %d\n", netdev->mtu, new_mtu);

	ret = h->ae_algo->ops->set_mtu(h, new_mtu);
	अगर (ret)
		netdev_err(netdev, "failed to change MTU in hardware %d\n",
			   ret);
	अन्यथा
		netdev->mtu = new_mtu;

	वापस ret;
पूर्ण

अटल bool hns3_get_tx_समयo_queue_info(काष्ठा net_device *ndev)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);
	काष्ठा hns3_enet_ring *tx_ring;
	काष्ठा napi_काष्ठा *napi;
	पूर्णांक समयout_queue = 0;
	पूर्णांक hw_head, hw_tail;
	पूर्णांक fbd_num, fbd_oft;
	पूर्णांक ebd_num, ebd_oft;
	पूर्णांक bd_num, bd_err;
	पूर्णांक ring_en, tc;
	पूर्णांक i;

	/* Find the stopped queue the same way the stack करोes */
	क्रम (i = 0; i < ndev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *q;
		अचिन्हित दीर्घ trans_start;

		q = netdev_get_tx_queue(ndev, i);
		trans_start = q->trans_start;
		अगर (netअगर_xmit_stopped(q) &&
		    समय_after(jअगरfies,
			       (trans_start + ndev->watchकरोg_समयo))) अणु
			समयout_queue = i;
			netdev_info(ndev, "queue state: 0x%lx, delta msecs: %u\n",
				    q->state,
				    jअगरfies_to_msecs(jअगरfies - trans_start));
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ndev->num_tx_queues) अणु
		netdev_info(ndev,
			    "no netdev TX timeout queue found, timeout count: %llu\n",
			    priv->tx_समयout_count);
		वापस false;
	पूर्ण

	priv->tx_समयout_count++;

	tx_ring = &priv->ring[समयout_queue];
	napi = &tx_ring->tqp_vector->napi;

	netdev_info(ndev,
		    "tx_timeout count: %llu, queue id: %d, SW_NTU: 0x%x, SW_NTC: 0x%x, napi state: %lu\n",
		    priv->tx_समयout_count, समयout_queue, tx_ring->next_to_use,
		    tx_ring->next_to_clean, napi->state);

	netdev_info(ndev,
		    "tx_pkts: %llu, tx_bytes: %llu, sw_err_cnt: %llu, tx_pending: %d\n",
		    tx_ring->stats.tx_pkts, tx_ring->stats.tx_bytes,
		    tx_ring->stats.sw_err_cnt, tx_ring->pending_buf);

	netdev_info(ndev,
		    "seg_pkt_cnt: %llu, tx_more: %llu, restart_queue: %llu, tx_busy: %llu\n",
		    tx_ring->stats.seg_pkt_cnt, tx_ring->stats.tx_more,
		    tx_ring->stats.restart_queue, tx_ring->stats.tx_busy);

	/* When mac received many छोड़ो frames continuous, it's unable to send
	 * packets, which may cause tx समयout
	 */
	अगर (h->ae_algo->ops->get_mac_stats) अणु
		काष्ठा hns3_mac_stats mac_stats;

		h->ae_algo->ops->get_mac_stats(h, &mac_stats);
		netdev_info(ndev, "tx_pause_cnt: %llu, rx_pause_cnt: %llu\n",
			    mac_stats.tx_छोड़ो_cnt, mac_stats.rx_छोड़ो_cnt);
	पूर्ण

	hw_head = पढ़ोl_relaxed(tx_ring->tqp->io_base +
				HNS3_RING_TX_RING_HEAD_REG);
	hw_tail = पढ़ोl_relaxed(tx_ring->tqp->io_base +
				HNS3_RING_TX_RING_TAIL_REG);
	fbd_num = पढ़ोl_relaxed(tx_ring->tqp->io_base +
				HNS3_RING_TX_RING_FBDNUM_REG);
	fbd_oft = पढ़ोl_relaxed(tx_ring->tqp->io_base +
				HNS3_RING_TX_RING_OFFSET_REG);
	ebd_num = पढ़ोl_relaxed(tx_ring->tqp->io_base +
				HNS3_RING_TX_RING_EBDNUM_REG);
	ebd_oft = पढ़ोl_relaxed(tx_ring->tqp->io_base +
				HNS3_RING_TX_RING_EBD_OFFSET_REG);
	bd_num = पढ़ोl_relaxed(tx_ring->tqp->io_base +
			       HNS3_RING_TX_RING_BD_NUM_REG);
	bd_err = पढ़ोl_relaxed(tx_ring->tqp->io_base +
			       HNS3_RING_TX_RING_BD_ERR_REG);
	ring_en = पढ़ोl_relaxed(tx_ring->tqp->io_base + HNS3_RING_EN_REG);
	tc = पढ़ोl_relaxed(tx_ring->tqp->io_base + HNS3_RING_TX_RING_TC_REG);

	netdev_info(ndev,
		    "BD_NUM: 0x%x HW_HEAD: 0x%x, HW_TAIL: 0x%x, BD_ERR: 0x%x, INT: 0x%x\n",
		    bd_num, hw_head, hw_tail, bd_err,
		    पढ़ोl(tx_ring->tqp_vector->mask_addr));
	netdev_info(ndev,
		    "RING_EN: 0x%x, TC: 0x%x, FBD_NUM: 0x%x FBD_OFT: 0x%x, EBD_NUM: 0x%x, EBD_OFT: 0x%x\n",
		    ring_en, tc, fbd_num, fbd_oft, ebd_num, ebd_oft);

	वापस true;
पूर्ण

अटल व्योम hns3_nic_net_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae3_handle *h = priv->ae_handle;

	अगर (!hns3_get_tx_समयo_queue_info(ndev))
		वापस;

	/* request the reset, and let the hclge to determine
	 * which reset level should be करोne
	 */
	अगर (h->ae_algo->ops->reset_event)
		h->ae_algo->ops->reset_event(h->pdev, h);
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
अटल पूर्णांक hns3_rx_flow_steer(काष्ठा net_device *dev, स्थिर काष्ठा sk_buff *skb,
			      u16 rxq_index, u32 flow_id)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(dev);
	काष्ठा flow_keys fkeys;

	अगर (!h->ae_algo->ops->add_arfs_entry)
		वापस -EOPNOTSUPP;

	अगर (skb->encapsulation)
		वापस -EPROTONOSUPPORT;

	अगर (!skb_flow_dissect_flow_keys(skb, &fkeys, 0))
		वापस -EPROTONOSUPPORT;

	अगर ((fkeys.basic.n_proto != htons(ETH_P_IP) &&
	     fkeys.basic.n_proto != htons(ETH_P_IPV6)) ||
	    (fkeys.basic.ip_proto != IPPROTO_TCP &&
	     fkeys.basic.ip_proto != IPPROTO_UDP))
		वापस -EPROTONOSUPPORT;

	वापस h->ae_algo->ops->add_arfs_entry(h, rxq_index, flow_id, &fkeys);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक hns3_nic_get_vf_config(काष्ठा net_device *ndev, पूर्णांक vf,
				  काष्ठा अगरla_vf_info *ivf)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);

	अगर (!h->ae_algo->ops->get_vf_config)
		वापस -EOPNOTSUPP;

	वापस h->ae_algo->ops->get_vf_config(h, vf, ivf);
पूर्ण

अटल पूर्णांक hns3_nic_set_vf_link_state(काष्ठा net_device *ndev, पूर्णांक vf,
				      पूर्णांक link_state)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);

	अगर (!h->ae_algo->ops->set_vf_link_state)
		वापस -EOPNOTSUPP;

	वापस h->ae_algo->ops->set_vf_link_state(h, vf, link_state);
पूर्ण

अटल पूर्णांक hns3_nic_set_vf_rate(काष्ठा net_device *ndev, पूर्णांक vf,
				पूर्णांक min_tx_rate, पूर्णांक max_tx_rate)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(ndev);

	अगर (!h->ae_algo->ops->set_vf_rate)
		वापस -EOPNOTSUPP;

	वापस h->ae_algo->ops->set_vf_rate(h, vf, min_tx_rate, max_tx_rate,
					    false);
पूर्ण

अटल पूर्णांक hns3_nic_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf_id, u8 *mac)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (!h->ae_algo->ops->set_vf_mac)
		वापस -EOPNOTSUPP;

	अगर (is_multicast_ether_addr(mac)) अणु
		netdev_err(netdev,
			   "Invalid MAC:%pM specified. Could not set MAC\n",
			   mac);
		वापस -EINVAL;
	पूर्ण

	वापस h->ae_algo->ops->set_vf_mac(h, vf_id, mac);
पूर्ण

अटल स्थिर काष्ठा net_device_ops hns3_nic_netdev_ops = अणु
	.nकरो_खोलो		= hns3_nic_net_खोलो,
	.nकरो_stop		= hns3_nic_net_stop,
	.nकरो_start_xmit		= hns3_nic_net_xmit,
	.nकरो_tx_समयout		= hns3_nic_net_समयout,
	.nकरो_set_mac_address	= hns3_nic_net_set_mac_address,
	.nकरो_करो_ioctl		= hns3_nic_करो_ioctl,
	.nकरो_change_mtu		= hns3_nic_change_mtu,
	.nकरो_set_features	= hns3_nic_set_features,
	.nकरो_features_check	= hns3_features_check,
	.nकरो_get_stats64	= hns3_nic_get_stats64,
	.nकरो_setup_tc		= hns3_nic_setup_tc,
	.nकरो_set_rx_mode	= hns3_nic_set_rx_mode,
	.nकरो_vlan_rx_add_vid	= hns3_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= hns3_vlan_rx_समाप्त_vid,
	.nकरो_set_vf_vlan	= hns3_nकरो_set_vf_vlan,
	.nकरो_set_vf_spoofchk	= hns3_set_vf_spoofchk,
	.nकरो_set_vf_trust	= hns3_set_vf_trust,
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer	= hns3_rx_flow_steer,
#पूर्ण_अगर
	.nकरो_get_vf_config	= hns3_nic_get_vf_config,
	.nकरो_set_vf_link_state	= hns3_nic_set_vf_link_state,
	.nकरो_set_vf_rate	= hns3_nic_set_vf_rate,
	.nकरो_set_vf_mac		= hns3_nic_set_vf_mac,
पूर्ण;

bool hns3_is_phys_func(काष्ठा pci_dev *pdev)
अणु
	u32 dev_id = pdev->device;

	चयन (dev_id) अणु
	हाल HNAE3_DEV_ID_GE:
	हाल HNAE3_DEV_ID_25GE:
	हाल HNAE3_DEV_ID_25GE_RDMA:
	हाल HNAE3_DEV_ID_25GE_RDMA_MACSEC:
	हाल HNAE3_DEV_ID_50GE_RDMA:
	हाल HNAE3_DEV_ID_50GE_RDMA_MACSEC:
	हाल HNAE3_DEV_ID_100G_RDMA_MACSEC:
	हाल HNAE3_DEV_ID_200G_RDMA:
		वापस true;
	हाल HNAE3_DEV_ID_VF:
	हाल HNAE3_DEV_ID_RDMA_DCB_PFC_VF:
		वापस false;
	शेष:
		dev_warn(&pdev->dev, "un-recognized pci device-id %u",
			 dev_id);
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम hns3_disable_sriov(काष्ठा pci_dev *pdev)
अणु
	/* If our VFs are asचिन्हित we cannot shut करोwn SR-IOV
	 * without causing issues, so just leave the hardware
	 * available but disabled
	 */
	अगर (pci_vfs_asचिन्हित(pdev)) अणु
		dev_warn(&pdev->dev,
			 "disabling driver while VFs are assigned\n");
		वापस;
	पूर्ण

	pci_disable_sriov(pdev);
पूर्ण

/* hns3_probe - Device initialization routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in hns3_pci_tbl
 *
 * hns3_probe initializes a PF identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the PF निजी काष्ठाure,
 * and a hardware reset occur.
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक hns3_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा hnae3_ae_dev *ae_dev;
	पूर्णांक ret;

	ae_dev = devm_kzalloc(&pdev->dev, माप(*ae_dev), GFP_KERNEL);
	अगर (!ae_dev)
		वापस -ENOMEM;

	ae_dev->pdev = pdev;
	ae_dev->flag = ent->driver_data;
	pci_set_drvdata(pdev, ae_dev);

	ret = hnae3_रेजिस्टर_ae_dev(ae_dev);
	अगर (ret)
		pci_set_drvdata(pdev, शून्य);

	वापस ret;
पूर्ण

/* hns3_हटाओ - Device removal routine
 * @pdev: PCI device inक्रमmation काष्ठा
 */
अटल व्योम hns3_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);

	अगर (hns3_is_phys_func(pdev) && IS_ENABLED(CONFIG_PCI_IOV))
		hns3_disable_sriov(pdev);

	hnae3_unरेजिस्टर_ae_dev(ae_dev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

/**
 * hns3_pci_sriov_configure
 * @pdev: poपूर्णांकer to a pci_dev काष्ठाure
 * @num_vfs: number of VFs to allocate
 *
 * Enable or change the number of VFs. Called when the user updates the number
 * of VFs in sysfs.
 **/
अटल पूर्णांक hns3_pci_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	पूर्णांक ret;

	अगर (!(hns3_is_phys_func(pdev) && IS_ENABLED(CONFIG_PCI_IOV))) अणु
		dev_warn(&pdev->dev, "Can not config SRIOV\n");
		वापस -EINVAL;
	पूर्ण

	अगर (num_vfs) अणु
		ret = pci_enable_sriov(pdev, num_vfs);
		अगर (ret)
			dev_err(&pdev->dev, "SRIOV enable failed %d\n", ret);
		अन्यथा
			वापस num_vfs;
	पूर्ण अन्यथा अगर (!pci_vfs_asचिन्हित(pdev)) अणु
		pci_disable_sriov(pdev);
	पूर्ण अन्यथा अणु
		dev_warn(&pdev->dev,
			 "Unable to free VFs because some are assigned to VMs.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hns3_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);

	hnae3_unरेजिस्टर_ae_dev(ae_dev);
	pci_set_drvdata(pdev, शून्य);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF)
		pci_set_घातer_state(pdev, PCI_D3hot);
पूर्ण

अटल पूर्णांक __maybe_unused hns3_suspend(काष्ठा device *dev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = dev_get_drvdata(dev);

	अगर (ae_dev && hns3_is_phys_func(ae_dev->pdev)) अणु
		dev_info(dev, "Begin to suspend.\n");
		अगर (ae_dev->ops && ae_dev->ops->reset_prepare)
			ae_dev->ops->reset_prepare(ae_dev, HNAE3_FUNC_RESET);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused hns3_resume(काष्ठा device *dev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = dev_get_drvdata(dev);

	अगर (ae_dev && hns3_is_phys_func(ae_dev->pdev)) अणु
		dev_info(dev, "Begin to resume.\n");
		अगर (ae_dev->ops && ae_dev->ops->reset_करोne)
			ae_dev->ops->reset_करोne(ae_dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल pci_ers_result_t hns3_error_detected(काष्ठा pci_dev *pdev,
					    pci_channel_state_t state)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);
	pci_ers_result_t ret;

	dev_info(&pdev->dev, "PCI error detected, state(=%u)!!\n", state);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (!ae_dev || !ae_dev->ops) अणु
		dev_err(&pdev->dev,
			"Can't recover - error happened before device initialized\n");
		वापस PCI_ERS_RESULT_NONE;
	पूर्ण

	अगर (ae_dev->ops->handle_hw_ras_error)
		ret = ae_dev->ops->handle_hw_ras_error(ae_dev);
	अन्यथा
		वापस PCI_ERS_RESULT_NONE;

	वापस ret;
पूर्ण

अटल pci_ers_result_t hns3_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);
	स्थिर काष्ठा hnae3_ae_ops *ops;
	क्रमागत hnae3_reset_type reset_type;
	काष्ठा device *dev = &pdev->dev;

	अगर (!ae_dev || !ae_dev->ops)
		वापस PCI_ERS_RESULT_NONE;

	ops = ae_dev->ops;
	/* request the reset */
	अगर (ops->reset_event && ops->get_reset_level &&
	    ops->set_शेष_reset_request) अणु
		अगर (ae_dev->hw_err_reset_req) अणु
			reset_type = ops->get_reset_level(ae_dev,
						&ae_dev->hw_err_reset_req);
			ops->set_शेष_reset_request(ae_dev, reset_type);
			dev_info(dev, "requesting reset due to PCI error\n");
			ops->reset_event(pdev, शून्य);
		पूर्ण

		वापस PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	वापस PCI_ERS_RESULT_DISCONNECT;
पूर्ण

अटल व्योम hns3_reset_prepare(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);

	dev_info(&pdev->dev, "FLR prepare\n");
	अगर (ae_dev && ae_dev->ops && ae_dev->ops->reset_prepare)
		ae_dev->ops->reset_prepare(ae_dev, HNAE3_FLR_RESET);
पूर्ण

अटल व्योम hns3_reset_करोne(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);

	dev_info(&pdev->dev, "FLR done\n");
	अगर (ae_dev && ae_dev->ops && ae_dev->ops->reset_करोne)
		ae_dev->ops->reset_करोne(ae_dev);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers hns3_err_handler = अणु
	.error_detected = hns3_error_detected,
	.slot_reset     = hns3_slot_reset,
	.reset_prepare	= hns3_reset_prepare,
	.reset_करोne	= hns3_reset_करोne,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(hns3_pm_ops, hns3_suspend, hns3_resume);

अटल काष्ठा pci_driver hns3_driver = अणु
	.name     = hns3_driver_name,
	.id_table = hns3_pci_tbl,
	.probe    = hns3_probe,
	.हटाओ   = hns3_हटाओ,
	.shutकरोwn = hns3_shutकरोwn,
	.driver.pm  = &hns3_pm_ops,
	.sriov_configure = hns3_pci_sriov_configure,
	.err_handler    = &hns3_err_handler,
पूर्ण;

/* set शेष feature to hns3 */
अटल व्योम hns3_set_शेष_feature(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा pci_dev *pdev = h->pdev;
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);

	netdev->priv_flags |= IFF_UNICAST_FLT;

	netdev->hw_enc_features |= NETIF_F_RXCSUM | NETIF_F_SG | NETIF_F_GSO |
		NETIF_F_GRO | NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_GSO_GRE |
		NETIF_F_GSO_GRE_CSUM | NETIF_F_GSO_UDP_TUNNEL |
		NETIF_F_SCTP_CRC | NETIF_F_TSO_MANGLEID | NETIF_F_FRAGLIST;

	netdev->gso_partial_features |= NETIF_F_GSO_GRE_CSUM;

	netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER |
		NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
		NETIF_F_RXCSUM | NETIF_F_SG | NETIF_F_GSO |
		NETIF_F_GRO | NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_GSO_GRE |
		NETIF_F_GSO_GRE_CSUM | NETIF_F_GSO_UDP_TUNNEL |
		NETIF_F_SCTP_CRC | NETIF_F_FRAGLIST;

	netdev->vlan_features |= NETIF_F_RXCSUM |
		NETIF_F_SG | NETIF_F_GSO | NETIF_F_GRO |
		NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_GSO_GRE |
		NETIF_F_GSO_GRE_CSUM | NETIF_F_GSO_UDP_TUNNEL |
		NETIF_F_SCTP_CRC | NETIF_F_FRAGLIST;

	netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX |
		NETIF_F_HW_VLAN_CTAG_RX |
		NETIF_F_RXCSUM | NETIF_F_SG | NETIF_F_GSO |
		NETIF_F_GRO | NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_GSO_GRE |
		NETIF_F_GSO_GRE_CSUM | NETIF_F_GSO_UDP_TUNNEL |
		NETIF_F_SCTP_CRC | NETIF_F_FRAGLIST;

	अगर (ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V2) अणु
		netdev->hw_features |= NETIF_F_GRO_HW;
		netdev->features |= NETIF_F_GRO_HW;

		अगर (!(h->flags & HNAE3_SUPPORT_VF)) अणु
			netdev->hw_features |= NETIF_F_NTUPLE;
			netdev->features |= NETIF_F_NTUPLE;
		पूर्ण
	पूर्ण

	अगर (test_bit(HNAE3_DEV_SUPPORT_UDP_GSO_B, ae_dev->caps)) अणु
		netdev->hw_features |= NETIF_F_GSO_UDP_L4;
		netdev->features |= NETIF_F_GSO_UDP_L4;
		netdev->vlan_features |= NETIF_F_GSO_UDP_L4;
		netdev->hw_enc_features |= NETIF_F_GSO_UDP_L4;
	पूर्ण

	अगर (test_bit(HNAE3_DEV_SUPPORT_HW_TX_CSUM_B, ae_dev->caps)) अणु
		netdev->hw_features |= NETIF_F_HW_CSUM;
		netdev->features |= NETIF_F_HW_CSUM;
		netdev->vlan_features |= NETIF_F_HW_CSUM;
		netdev->hw_enc_features |= NETIF_F_HW_CSUM;
	पूर्ण अन्यथा अणु
		netdev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
		netdev->features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
		netdev->vlan_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
		netdev->hw_enc_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	पूर्ण

	अगर (test_bit(HNAE3_DEV_SUPPORT_UDP_TUNNEL_CSUM_B, ae_dev->caps)) अणु
		netdev->hw_features |= NETIF_F_GSO_UDP_TUNNEL_CSUM;
		netdev->features |= NETIF_F_GSO_UDP_TUNNEL_CSUM;
		netdev->vlan_features |= NETIF_F_GSO_UDP_TUNNEL_CSUM;
		netdev->hw_enc_features |= NETIF_F_GSO_UDP_TUNNEL_CSUM;
	पूर्ण

	अगर (test_bit(HNAE3_DEV_SUPPORT_FD_FORWARD_TC_B, ae_dev->caps)) अणु
		netdev->hw_features |= NETIF_F_HW_TC;
		netdev->features |= NETIF_F_HW_TC;
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_alloc_buffer(काष्ठा hns3_enet_ring *ring,
			     काष्ठा hns3_desc_cb *cb)
अणु
	अचिन्हित पूर्णांक order = hns3_page_order(ring);
	काष्ठा page *p;

	p = dev_alloc_pages(order);
	अगर (!p)
		वापस -ENOMEM;

	cb->priv = p;
	cb->page_offset = 0;
	cb->reuse_flag = 0;
	cb->buf  = page_address(p);
	cb->length = hns3_page_size(ring);
	cb->type = DESC_TYPE_PAGE;
	page_ref_add(p, अच_लघु_उच्च - 1);
	cb->pagecnt_bias = अच_लघु_उच्च;

	वापस 0;
पूर्ण

अटल व्योम hns3_मुक्त_buffer(काष्ठा hns3_enet_ring *ring,
			     काष्ठा hns3_desc_cb *cb, पूर्णांक budget)
अणु
	अगर (cb->type == DESC_TYPE_SKB)
		napi_consume_skb(cb->priv, budget);
	अन्यथा अगर (!HNAE3_IS_TX_RING(ring) && cb->pagecnt_bias)
		__page_frag_cache_drain(cb->priv, cb->pagecnt_bias);
	स_रखो(cb, 0, माप(*cb));
पूर्ण

अटल पूर्णांक hns3_map_buffer(काष्ठा hns3_enet_ring *ring, काष्ठा hns3_desc_cb *cb)
अणु
	cb->dma = dma_map_page(ring_to_dev(ring), cb->priv, 0,
			       cb->length, ring_to_dma_dir(ring));

	अगर (unlikely(dma_mapping_error(ring_to_dev(ring), cb->dma)))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम hns3_unmap_buffer(काष्ठा hns3_enet_ring *ring,
			      काष्ठा hns3_desc_cb *cb)
अणु
	अगर (cb->type == DESC_TYPE_SKB || cb->type == DESC_TYPE_FRAGLIST_SKB)
		dma_unmap_single(ring_to_dev(ring), cb->dma, cb->length,
				 ring_to_dma_dir(ring));
	अन्यथा अगर (cb->length)
		dma_unmap_page(ring_to_dev(ring), cb->dma, cb->length,
			       ring_to_dma_dir(ring));
पूर्ण

अटल व्योम hns3_buffer_detach(काष्ठा hns3_enet_ring *ring, पूर्णांक i)
अणु
	hns3_unmap_buffer(ring, &ring->desc_cb[i]);
	ring->desc[i].addr = 0;
पूर्ण

अटल व्योम hns3_मुक्त_buffer_detach(काष्ठा hns3_enet_ring *ring, पूर्णांक i,
				    पूर्णांक budget)
अणु
	काष्ठा hns3_desc_cb *cb = &ring->desc_cb[i];

	अगर (!ring->desc_cb[i].dma)
		वापस;

	hns3_buffer_detach(ring, i);
	hns3_मुक्त_buffer(ring, cb, budget);
पूर्ण

अटल व्योम hns3_मुक्त_buffers(काष्ठा hns3_enet_ring *ring)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ring->desc_num; i++)
		hns3_मुक्त_buffer_detach(ring, i, 0);
पूर्ण

/* मुक्त desc aदीर्घ with its attached buffer */
अटल व्योम hns3_मुक्त_desc(काष्ठा hns3_enet_ring *ring)
अणु
	पूर्णांक size = ring->desc_num * माप(ring->desc[0]);

	hns3_मुक्त_buffers(ring);

	अगर (ring->desc) अणु
		dma_मुक्त_coherent(ring_to_dev(ring), size,
				  ring->desc, ring->desc_dma_addr);
		ring->desc = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_alloc_desc(काष्ठा hns3_enet_ring *ring)
अणु
	पूर्णांक size = ring->desc_num * माप(ring->desc[0]);

	ring->desc = dma_alloc_coherent(ring_to_dev(ring), size,
					&ring->desc_dma_addr, GFP_KERNEL);
	अगर (!ring->desc)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_alloc_and_map_buffer(काष्ठा hns3_enet_ring *ring,
				   काष्ठा hns3_desc_cb *cb)
अणु
	पूर्णांक ret;

	ret = hns3_alloc_buffer(ring, cb);
	अगर (ret)
		जाओ out;

	ret = hns3_map_buffer(ring, cb);
	अगर (ret)
		जाओ out_with_buf;

	वापस 0;

out_with_buf:
	hns3_मुक्त_buffer(ring, cb, 0);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक hns3_alloc_and_attach_buffer(काष्ठा hns3_enet_ring *ring, पूर्णांक i)
अणु
	पूर्णांक ret = hns3_alloc_and_map_buffer(ring, &ring->desc_cb[i]);

	अगर (ret)
		वापस ret;

	ring->desc[i].addr = cpu_to_le64(ring->desc_cb[i].dma);

	वापस 0;
पूर्ण

/* Allocate memory क्रम raw pkg, and map with dma */
अटल पूर्णांक hns3_alloc_ring_buffers(काष्ठा hns3_enet_ring *ring)
अणु
	पूर्णांक i, j, ret;

	क्रम (i = 0; i < ring->desc_num; i++) अणु
		ret = hns3_alloc_and_attach_buffer(ring, i);
		अगर (ret)
			जाओ out_buffer_fail;
	पूर्ण

	वापस 0;

out_buffer_fail:
	क्रम (j = i - 1; j >= 0; j--)
		hns3_मुक्त_buffer_detach(ring, j, 0);
	वापस ret;
पूर्ण

/* detach a in-used buffer and replace with a reserved one */
अटल व्योम hns3_replace_buffer(काष्ठा hns3_enet_ring *ring, पूर्णांक i,
				काष्ठा hns3_desc_cb *res_cb)
अणु
	hns3_unmap_buffer(ring, &ring->desc_cb[i]);
	ring->desc_cb[i] = *res_cb;
	ring->desc[i].addr = cpu_to_le64(ring->desc_cb[i].dma);
	ring->desc[i].rx.bd_base_info = 0;
पूर्ण

अटल व्योम hns3_reuse_buffer(काष्ठा hns3_enet_ring *ring, पूर्णांक i)
अणु
	ring->desc_cb[i].reuse_flag = 0;
	ring->desc[i].addr = cpu_to_le64(ring->desc_cb[i].dma +
					 ring->desc_cb[i].page_offset);
	ring->desc[i].rx.bd_base_info = 0;

	dma_sync_single_क्रम_device(ring_to_dev(ring),
			ring->desc_cb[i].dma + ring->desc_cb[i].page_offset,
			hns3_buf_size(ring),
			DMA_FROM_DEVICE);
पूर्ण

अटल bool hns3_nic_reclaim_desc(काष्ठा hns3_enet_ring *ring,
				  पूर्णांक *bytes, पूर्णांक *pkts, पूर्णांक budget)
अणु
	/* pair with ring->last_to_use update in hns3_tx_करोorbell(),
	 * smp_store_release() is not used in hns3_tx_करोorbell() because
	 * the करोorbell operation alपढ़ोy have the needed barrier operation.
	 */
	पूर्णांक ltu = smp_load_acquire(&ring->last_to_use);
	पूर्णांक ntc = ring->next_to_clean;
	काष्ठा hns3_desc_cb *desc_cb;
	bool reclaimed = false;
	काष्ठा hns3_desc *desc;

	जबतक (ltu != ntc) अणु
		desc = &ring->desc[ntc];

		अगर (le16_to_cpu(desc->tx.bdtp_fe_sc_vld_ra_ri) &
				BIT(HNS3_TXD_VLD_B))
			अवरोध;

		desc_cb = &ring->desc_cb[ntc];

		अगर (desc_cb->type == DESC_TYPE_SKB) अणु
			(*pkts)++;
			(*bytes) += desc_cb->send_bytes;
		पूर्ण

		/* desc_cb will be cleaned, after hnae3_मुक्त_buffer_detach */
		hns3_मुक्त_buffer_detach(ring, ntc, budget);

		अगर (++ntc == ring->desc_num)
			ntc = 0;

		/* Issue prefetch क्रम next Tx descriptor */
		prefetch(&ring->desc_cb[ntc]);
		reclaimed = true;
	पूर्ण

	अगर (unlikely(!reclaimed))
		वापस false;

	/* This smp_store_release() pairs with smp_load_acquire() in
	 * ring_space called by hns3_nic_net_xmit.
	 */
	smp_store_release(&ring->next_to_clean, ntc);
	वापस true;
पूर्ण

व्योम hns3_clean_tx_ring(काष्ठा hns3_enet_ring *ring, पूर्णांक budget)
अणु
	काष्ठा net_device *netdev = ring_to_netdev(ring);
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा netdev_queue *dev_queue;
	पूर्णांक bytes, pkts;

	bytes = 0;
	pkts = 0;

	अगर (unlikely(!hns3_nic_reclaim_desc(ring, &bytes, &pkts, budget)))
		वापस;

	ring->tqp_vector->tx_group.total_bytes += bytes;
	ring->tqp_vector->tx_group.total_packets += pkts;

	u64_stats_update_begin(&ring->syncp);
	ring->stats.tx_bytes += bytes;
	ring->stats.tx_pkts += pkts;
	u64_stats_update_end(&ring->syncp);

	dev_queue = netdev_get_tx_queue(netdev, ring->tqp->tqp_index);
	netdev_tx_completed_queue(dev_queue, pkts, bytes);

	अगर (unlikely(netअगर_carrier_ok(netdev) &&
		     ring_space(ring) > HNS3_MAX_TSO_BD_NUM)) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		अगर (netअगर_tx_queue_stopped(dev_queue) &&
		    !test_bit(HNS3_NIC_STATE_DOWN, &priv->state)) अणु
			netअगर_tx_wake_queue(dev_queue);
			ring->stats.restart_queue++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_desc_unused(काष्ठा hns3_enet_ring *ring)
अणु
	पूर्णांक ntc = ring->next_to_clean;
	पूर्णांक ntu = ring->next_to_use;

	वापस ((ntc >= ntu) ? 0 : ring->desc_num) + ntc - ntu;
पूर्ण

अटल व्योम hns3_nic_alloc_rx_buffers(काष्ठा hns3_enet_ring *ring,
				      पूर्णांक cleand_count)
अणु
	काष्ठा hns3_desc_cb *desc_cb;
	काष्ठा hns3_desc_cb res_cbs;
	पूर्णांक i, ret;

	क्रम (i = 0; i < cleand_count; i++) अणु
		desc_cb = &ring->desc_cb[ring->next_to_use];
		अगर (desc_cb->reuse_flag) अणु
			u64_stats_update_begin(&ring->syncp);
			ring->stats.reuse_pg_cnt++;
			u64_stats_update_end(&ring->syncp);

			hns3_reuse_buffer(ring, ring->next_to_use);
		पूर्ण अन्यथा अणु
			ret = hns3_alloc_and_map_buffer(ring, &res_cbs);
			अगर (ret) अणु
				u64_stats_update_begin(&ring->syncp);
				ring->stats.sw_err_cnt++;
				u64_stats_update_end(&ring->syncp);

				hns3_rl_err(ring_to_netdev(ring),
					    "alloc rx buffer failed: %d\n",
					    ret);
				अवरोध;
			पूर्ण
			hns3_replace_buffer(ring, ring->next_to_use, &res_cbs);

			u64_stats_update_begin(&ring->syncp);
			ring->stats.non_reuse_pg++;
			u64_stats_update_end(&ring->syncp);
		पूर्ण

		ring_ptr_move_fw(ring, next_to_use);
	पूर्ण

	ग_लिखोl(i, ring->tqp->io_base + HNS3_RING_RX_RING_HEAD_REG);
पूर्ण

अटल bool hns3_can_reuse_page(काष्ठा hns3_desc_cb *cb)
अणु
	वापस (page_count(cb->priv) - cb->pagecnt_bias) == 1;
पूर्ण

अटल व्योम hns3_nic_reuse_page(काष्ठा sk_buff *skb, पूर्णांक i,
				काष्ठा hns3_enet_ring *ring, पूर्णांक pull_len,
				काष्ठा hns3_desc_cb *desc_cb)
अणु
	काष्ठा hns3_desc *desc = &ring->desc[ring->next_to_clean];
	पूर्णांक size = le16_to_cpu(desc->rx.size);
	u32 truesize = hns3_buf_size(ring);

	desc_cb->pagecnt_bias--;
	skb_add_rx_frag(skb, i, desc_cb->priv, desc_cb->page_offset + pull_len,
			size - pull_len, truesize);

	/* Aव्योम re-using remote and pfmeदो_स्मृति pages, or the stack is still
	 * using the page when page_offset rollback to zero, flag शेष
	 * unreuse
	 */
	अगर (!dev_page_is_reusable(desc_cb->priv) ||
	    (!desc_cb->page_offset && !hns3_can_reuse_page(desc_cb))) अणु
		__page_frag_cache_drain(desc_cb->priv, desc_cb->pagecnt_bias);
		वापस;
	पूर्ण

	/* Move offset up to the next cache line */
	desc_cb->page_offset += truesize;

	अगर (desc_cb->page_offset + truesize <= hns3_page_size(ring)) अणु
		desc_cb->reuse_flag = 1;
	पूर्ण अन्यथा अगर (hns3_can_reuse_page(desc_cb)) अणु
		desc_cb->reuse_flag = 1;
		desc_cb->page_offset = 0;
	पूर्ण अन्यथा अगर (desc_cb->pagecnt_bias) अणु
		__page_frag_cache_drain(desc_cb->priv, desc_cb->pagecnt_bias);
		वापस;
	पूर्ण

	अगर (unlikely(!desc_cb->pagecnt_bias)) अणु
		page_ref_add(desc_cb->priv, अच_लघु_उच्च);
		desc_cb->pagecnt_bias = अच_लघु_उच्च;
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_gro_complete(काष्ठा sk_buff *skb, u32 l234info)
अणु
	__be16 type = skb->protocol;
	काष्ठा tcphdr *th;
	पूर्णांक depth = 0;

	जबतक (eth_type_vlan(type)) अणु
		काष्ठा vlan_hdr *vh;

		अगर ((depth + VLAN_HLEN) > skb_headlen(skb))
			वापस -EFAULT;

		vh = (काष्ठा vlan_hdr *)(skb->data + depth);
		type = vh->h_vlan_encapsulated_proto;
		depth += VLAN_HLEN;
	पूर्ण

	skb_set_network_header(skb, depth);

	अगर (type == htons(ETH_P_IP)) अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

		depth += माप(काष्ठा iphdr);
		skb_set_transport_header(skb, depth);
		th = tcp_hdr(skb);
		th->check = ~tcp_v4_check(skb->len - depth, iph->saddr,
					  iph->daddr, 0);
	पूर्ण अन्यथा अगर (type == htons(ETH_P_IPV6)) अणु
		स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);

		depth += माप(काष्ठा ipv6hdr);
		skb_set_transport_header(skb, depth);
		th = tcp_hdr(skb);
		th->check = ~tcp_v6_check(skb->len - depth, &iph->saddr,
					  &iph->daddr, 0);
	पूर्ण अन्यथा अणु
		hns3_rl_err(skb->dev,
			    "Error: FW GRO supports only IPv4/IPv6, not 0x%04x, depth: %d\n",
			    be16_to_cpu(type), depth);
		वापस -EFAULT;
	पूर्ण

	skb_shinfo(skb)->gso_segs = NAPI_GRO_CB(skb)->count;
	अगर (th->cwr)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_ECN;

	अगर (l234info & BIT(HNS3_RXD_GRO_FIXID_B))
		skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_FIXEDID;

	skb->csum_start = (अचिन्हित अक्षर *)th - skb->head;
	skb->csum_offset = दुरत्व(काष्ठा tcphdr, check);
	skb->ip_summed = CHECKSUM_PARTIAL;

	trace_hns3_gro(skb);

	वापस 0;
पूर्ण

अटल व्योम hns3_checksum_complete(काष्ठा hns3_enet_ring *ring,
				   काष्ठा sk_buff *skb, u32 l234info)
अणु
	u32 lo, hi;

	u64_stats_update_begin(&ring->syncp);
	ring->stats.csum_complete++;
	u64_stats_update_end(&ring->syncp);
	skb->ip_summed = CHECKSUM_COMPLETE;
	lo = hnae3_get_field(l234info, HNS3_RXD_L2_CSUM_L_M,
			     HNS3_RXD_L2_CSUM_L_S);
	hi = hnae3_get_field(l234info, HNS3_RXD_L2_CSUM_H_M,
			     HNS3_RXD_L2_CSUM_H_S);
	skb->csum = csum_unfold((__क्रमce __sum16)(lo | hi << 8));
पूर्ण

अटल व्योम hns3_rx_checksum(काष्ठा hns3_enet_ring *ring, काष्ठा sk_buff *skb,
			     u32 l234info, u32 bd_base_info, u32 ol_info)
अणु
	काष्ठा net_device *netdev = ring_to_netdev(ring);
	पूर्णांक l3_type, l4_type;
	पूर्णांक ol4_type;

	skb->ip_summed = CHECKSUM_NONE;

	skb_checksum_none_निश्चित(skb);

	अगर (!(netdev->features & NETIF_F_RXCSUM))
		वापस;

	अगर (l234info & BIT(HNS3_RXD_L2_CSUM_B)) अणु
		hns3_checksum_complete(ring, skb, l234info);
		वापस;
	पूर्ण

	/* check अगर hardware has करोne checksum */
	अगर (!(bd_base_info & BIT(HNS3_RXD_L3L4P_B)))
		वापस;

	अगर (unlikely(l234info & (BIT(HNS3_RXD_L3E_B) | BIT(HNS3_RXD_L4E_B) |
				 BIT(HNS3_RXD_OL3E_B) |
				 BIT(HNS3_RXD_OL4E_B)))) अणु
		u64_stats_update_begin(&ring->syncp);
		ring->stats.l3l4_csum_err++;
		u64_stats_update_end(&ring->syncp);

		वापस;
	पूर्ण

	ol4_type = hnae3_get_field(ol_info, HNS3_RXD_OL4ID_M,
				   HNS3_RXD_OL4ID_S);
	चयन (ol4_type) अणु
	हाल HNS3_OL4_TYPE_MAC_IN_UDP:
	हाल HNS3_OL4_TYPE_NVGRE:
		skb->csum_level = 1;
		fallthrough;
	हाल HNS3_OL4_TYPE_NO_TUN:
		l3_type = hnae3_get_field(l234info, HNS3_RXD_L3ID_M,
					  HNS3_RXD_L3ID_S);
		l4_type = hnae3_get_field(l234info, HNS3_RXD_L4ID_M,
					  HNS3_RXD_L4ID_S);
		/* Can checksum ipv4 or ipv6 + UDP/TCP/SCTP packets */
		अगर ((l3_type == HNS3_L3_TYPE_IPV4 ||
		     l3_type == HNS3_L3_TYPE_IPV6) &&
		    (l4_type == HNS3_L4_TYPE_UDP ||
		     l4_type == HNS3_L4_TYPE_TCP ||
		     l4_type == HNS3_L4_TYPE_SCTP))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hns3_rx_skb(काष्ठा hns3_enet_ring *ring, काष्ठा sk_buff *skb)
अणु
	अगर (skb_has_frag_list(skb))
		napi_gro_flush(&ring->tqp_vector->napi, false);

	napi_gro_receive(&ring->tqp_vector->napi, skb);
पूर्ण

अटल bool hns3_parse_vlan_tag(काष्ठा hns3_enet_ring *ring,
				काष्ठा hns3_desc *desc, u32 l234info,
				u16 *vlan_tag)
अणु
	काष्ठा hnae3_handle *handle = ring->tqp->handle;
	काष्ठा pci_dev *pdev = ring->tqp->handle->pdev;
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);

	अगर (unlikely(ae_dev->dev_version < HNAE3_DEVICE_VERSION_V2)) अणु
		*vlan_tag = le16_to_cpu(desc->rx.ot_vlan_tag);
		अगर (!(*vlan_tag & VLAN_VID_MASK))
			*vlan_tag = le16_to_cpu(desc->rx.vlan_tag);

		वापस (*vlan_tag != 0);
	पूर्ण

#घोषणा HNS3_STRP_OUTER_VLAN	0x1
#घोषणा HNS3_STRP_INNER_VLAN	0x2
#घोषणा HNS3_STRP_BOTH		0x3

	/* Hardware always insert VLAN tag पूर्णांकo RX descriptor when
	 * हटाओ the tag from packet, driver needs to determine
	 * reporting which tag to stack.
	 */
	चयन (hnae3_get_field(l234info, HNS3_RXD_STRP_TAGP_M,
				HNS3_RXD_STRP_TAGP_S)) अणु
	हाल HNS3_STRP_OUTER_VLAN:
		अगर (handle->port_base_vlan_state !=
				HNAE3_PORT_BASE_VLAN_DISABLE)
			वापस false;

		*vlan_tag = le16_to_cpu(desc->rx.ot_vlan_tag);
		वापस true;
	हाल HNS3_STRP_INNER_VLAN:
		अगर (handle->port_base_vlan_state !=
				HNAE3_PORT_BASE_VLAN_DISABLE)
			वापस false;

		*vlan_tag = le16_to_cpu(desc->rx.vlan_tag);
		वापस true;
	हाल HNS3_STRP_BOTH:
		अगर (handle->port_base_vlan_state ==
				HNAE3_PORT_BASE_VLAN_DISABLE)
			*vlan_tag = le16_to_cpu(desc->rx.ot_vlan_tag);
		अन्यथा
			*vlan_tag = le16_to_cpu(desc->rx.vlan_tag);

		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम hns3_rx_ring_move_fw(काष्ठा hns3_enet_ring *ring)
अणु
	ring->desc[ring->next_to_clean].rx.bd_base_info &=
		cpu_to_le32(~BIT(HNS3_RXD_VLD_B));
	ring->next_to_clean += 1;

	अगर (unlikely(ring->next_to_clean == ring->desc_num))
		ring->next_to_clean = 0;
पूर्ण

अटल पूर्णांक hns3_alloc_skb(काष्ठा hns3_enet_ring *ring, अचिन्हित पूर्णांक length,
			  अचिन्हित अक्षर *va)
अणु
	काष्ठा hns3_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_clean];
	काष्ठा net_device *netdev = ring_to_netdev(ring);
	काष्ठा sk_buff *skb;

	ring->skb = napi_alloc_skb(&ring->tqp_vector->napi, HNS3_RX_HEAD_SIZE);
	skb = ring->skb;
	अगर (unlikely(!skb)) अणु
		hns3_rl_err(netdev, "alloc rx skb fail\n");

		u64_stats_update_begin(&ring->syncp);
		ring->stats.sw_err_cnt++;
		u64_stats_update_end(&ring->syncp);

		वापस -ENOMEM;
	पूर्ण

	trace_hns3_rx_desc(ring);
	prefetchw(skb->data);

	ring->pending_buf = 1;
	ring->frag_num = 0;
	ring->tail_skb = शून्य;
	अगर (length <= HNS3_RX_HEAD_SIZE) अणु
		स_नकल(__skb_put(skb, length), va, ALIGN(length, माप(दीर्घ)));

		/* We can reuse buffer as-is, just make sure it is reusable */
		अगर (dev_page_is_reusable(desc_cb->priv))
			desc_cb->reuse_flag = 1;
		अन्यथा /* This page cannot be reused so discard it */
			__page_frag_cache_drain(desc_cb->priv,
						desc_cb->pagecnt_bias);

		hns3_rx_ring_move_fw(ring);
		वापस 0;
	पूर्ण
	u64_stats_update_begin(&ring->syncp);
	ring->stats.seg_pkt_cnt++;
	u64_stats_update_end(&ring->syncp);

	ring->pull_len = eth_get_headlen(netdev, va, HNS3_RX_HEAD_SIZE);
	__skb_put(skb, ring->pull_len);
	hns3_nic_reuse_page(skb, ring->frag_num++, ring, ring->pull_len,
			    desc_cb);
	hns3_rx_ring_move_fw(ring);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_add_frag(काष्ठा hns3_enet_ring *ring)
अणु
	काष्ठा sk_buff *skb = ring->skb;
	काष्ठा sk_buff *head_skb = skb;
	काष्ठा sk_buff *new_skb;
	काष्ठा hns3_desc_cb *desc_cb;
	काष्ठा hns3_desc *desc;
	u32 bd_base_info;

	करो अणु
		desc = &ring->desc[ring->next_to_clean];
		desc_cb = &ring->desc_cb[ring->next_to_clean];
		bd_base_info = le32_to_cpu(desc->rx.bd_base_info);
		/* make sure HW ग_लिखो desc complete */
		dma_rmb();
		अगर (!(bd_base_info & BIT(HNS3_RXD_VLD_B)))
			वापस -ENXIO;

		अगर (unlikely(ring->frag_num >= MAX_SKB_FRAGS)) अणु
			new_skb = napi_alloc_skb(&ring->tqp_vector->napi, 0);
			अगर (unlikely(!new_skb)) अणु
				hns3_rl_err(ring_to_netdev(ring),
					    "alloc rx fraglist skb fail\n");
				वापस -ENXIO;
			पूर्ण
			ring->frag_num = 0;

			अगर (ring->tail_skb) अणु
				ring->tail_skb->next = new_skb;
				ring->tail_skb = new_skb;
			पूर्ण अन्यथा अणु
				skb_shinfo(skb)->frag_list = new_skb;
				ring->tail_skb = new_skb;
			पूर्ण
		पूर्ण

		अगर (ring->tail_skb) अणु
			head_skb->truesize += hns3_buf_size(ring);
			head_skb->data_len += le16_to_cpu(desc->rx.size);
			head_skb->len += le16_to_cpu(desc->rx.size);
			skb = ring->tail_skb;
		पूर्ण

		dma_sync_single_क्रम_cpu(ring_to_dev(ring),
				desc_cb->dma + desc_cb->page_offset,
				hns3_buf_size(ring),
				DMA_FROM_DEVICE);

		hns3_nic_reuse_page(skb, ring->frag_num++, ring, 0, desc_cb);
		trace_hns3_rx_desc(ring);
		hns3_rx_ring_move_fw(ring);
		ring->pending_buf++;
	पूर्ण जबतक (!(bd_base_info & BIT(HNS3_RXD_FE_B)));

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_set_gro_and_checksum(काष्ठा hns3_enet_ring *ring,
				     काष्ठा sk_buff *skb, u32 l234info,
				     u32 bd_base_info, u32 ol_info)
अणु
	u32 l3_type;

	skb_shinfo(skb)->gso_size = hnae3_get_field(bd_base_info,
						    HNS3_RXD_GRO_SIZE_M,
						    HNS3_RXD_GRO_SIZE_S);
	/* अगर there is no HW GRO, करो not set gro params */
	अगर (!skb_shinfo(skb)->gso_size) अणु
		hns3_rx_checksum(ring, skb, l234info, bd_base_info, ol_info);
		वापस 0;
	पूर्ण

	NAPI_GRO_CB(skb)->count = hnae3_get_field(l234info,
						  HNS3_RXD_GRO_COUNT_M,
						  HNS3_RXD_GRO_COUNT_S);

	l3_type = hnae3_get_field(l234info, HNS3_RXD_L3ID_M, HNS3_RXD_L3ID_S);
	अगर (l3_type == HNS3_L3_TYPE_IPV4)
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
	अन्यथा अगर (l3_type == HNS3_L3_TYPE_IPV6)
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
	अन्यथा
		वापस -EFAULT;

	वापस  hns3_gro_complete(skb, l234info);
पूर्ण

अटल व्योम hns3_set_rx_skb_rss_type(काष्ठा hns3_enet_ring *ring,
				     काष्ठा sk_buff *skb, u32 rss_hash)
अणु
	काष्ठा hnae3_handle *handle = ring->tqp->handle;
	क्रमागत pkt_hash_types rss_type;

	अगर (rss_hash)
		rss_type = handle->kinfo.rss_type;
	अन्यथा
		rss_type = PKT_HASH_TYPE_NONE;

	skb_set_hash(skb, rss_hash, rss_type);
पूर्ण

अटल पूर्णांक hns3_handle_bdinfo(काष्ठा hns3_enet_ring *ring, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *netdev = ring_to_netdev(ring);
	क्रमागत hns3_pkt_l2t_type l2_frame_type;
	u32 bd_base_info, l234info, ol_info;
	काष्ठा hns3_desc *desc;
	अचिन्हित पूर्णांक len;
	पूर्णांक pre_ntc, ret;

	/* bdinfo handled below is only valid on the last BD of the
	 * current packet, and ring->next_to_clean indicates the first
	 * descriptor of next packet, so need - 1 below.
	 */
	pre_ntc = ring->next_to_clean ? (ring->next_to_clean - 1) :
					(ring->desc_num - 1);
	desc = &ring->desc[pre_ntc];
	bd_base_info = le32_to_cpu(desc->rx.bd_base_info);
	l234info = le32_to_cpu(desc->rx.l234_info);
	ol_info = le32_to_cpu(desc->rx.ol_info);

	/* Based on hw strategy, the tag offloaded will be stored at
	 * ot_vlan_tag in two layer tag हाल, and stored at vlan_tag
	 * in one layer tag हाल.
	 */
	अगर (netdev->features & NETIF_F_HW_VLAN_CTAG_RX) अणु
		u16 vlan_tag;

		अगर (hns3_parse_vlan_tag(ring, desc, l234info, &vlan_tag))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       vlan_tag);
	पूर्ण

	अगर (unlikely(!desc->rx.pkt_len || (l234info & (BIT(HNS3_RXD_TRUNCAT_B) |
				  BIT(HNS3_RXD_L2E_B))))) अणु
		u64_stats_update_begin(&ring->syncp);
		अगर (l234info & BIT(HNS3_RXD_L2E_B))
			ring->stats.l2_err++;
		अन्यथा
			ring->stats.err_pkt_len++;
		u64_stats_update_end(&ring->syncp);

		वापस -EFAULT;
	पूर्ण

	len = skb->len;

	/* Do update ip stack process */
	skb->protocol = eth_type_trans(skb, netdev);

	/* This is needed in order to enable क्रमwarding support */
	ret = hns3_set_gro_and_checksum(ring, skb, l234info,
					bd_base_info, ol_info);
	अगर (unlikely(ret)) अणु
		u64_stats_update_begin(&ring->syncp);
		ring->stats.rx_err_cnt++;
		u64_stats_update_end(&ring->syncp);
		वापस ret;
	पूर्ण

	l2_frame_type = hnae3_get_field(l234info, HNS3_RXD_DMAC_M,
					HNS3_RXD_DMAC_S);

	u64_stats_update_begin(&ring->syncp);
	ring->stats.rx_pkts++;
	ring->stats.rx_bytes += len;

	अगर (l2_frame_type == HNS3_L2_TYPE_MULTICAST)
		ring->stats.rx_multicast++;

	u64_stats_update_end(&ring->syncp);

	ring->tqp_vector->rx_group.total_bytes += len;

	hns3_set_rx_skb_rss_type(ring, skb, le32_to_cpu(desc->rx.rss_hash));
	वापस 0;
पूर्ण

अटल पूर्णांक hns3_handle_rx_bd(काष्ठा hns3_enet_ring *ring)
अणु
	काष्ठा sk_buff *skb = ring->skb;
	काष्ठा hns3_desc_cb *desc_cb;
	काष्ठा hns3_desc *desc;
	अचिन्हित पूर्णांक length;
	u32 bd_base_info;
	पूर्णांक ret;

	desc = &ring->desc[ring->next_to_clean];
	desc_cb = &ring->desc_cb[ring->next_to_clean];

	prefetch(desc);

	अगर (!skb) अणु
		bd_base_info = le32_to_cpu(desc->rx.bd_base_info);
		/* Check valid BD */
		अगर (unlikely(!(bd_base_info & BIT(HNS3_RXD_VLD_B))))
			वापस -ENXIO;

		dma_rmb();
		length = le16_to_cpu(desc->rx.size);

		ring->va = desc_cb->buf + desc_cb->page_offset;

		dma_sync_single_क्रम_cpu(ring_to_dev(ring),
				desc_cb->dma + desc_cb->page_offset,
				hns3_buf_size(ring),
				DMA_FROM_DEVICE);

		/* Prefetch first cache line of first page.
		 * Idea is to cache few bytes of the header of the packet.
		 * Our L1 Cache line size is 64B so need to prefetch twice to make
		 * it 128B. But in actual we can have greater size of caches with
		 * 128B Level 1 cache lines. In such a हाल, single fetch would
		 * suffice to cache in the relevant part of the header.
		 */
		net_prefetch(ring->va);

		ret = hns3_alloc_skb(ring, length, ring->va);
		skb = ring->skb;

		अगर (ret < 0) /* alloc buffer fail */
			वापस ret;
		अगर (!(bd_base_info & BIT(HNS3_RXD_FE_B))) अणु /* need add frag */
			ret = hns3_add_frag(ring);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = hns3_add_frag(ring);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* As the head data may be changed when GRO enable, copy
	 * the head data in after other data rx completed
	 */
	अगर (skb->len > HNS3_RX_HEAD_SIZE)
		स_नकल(skb->data, ring->va,
		       ALIGN(ring->pull_len, माप(दीर्घ)));

	ret = hns3_handle_bdinfo(ring, skb);
	अगर (unlikely(ret)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण

	skb_record_rx_queue(skb, ring->tqp->tqp_index);
	वापस 0;
पूर्ण

पूर्णांक hns3_clean_rx_ring(काष्ठा hns3_enet_ring *ring, पूर्णांक budget,
		       व्योम (*rx_fn)(काष्ठा hns3_enet_ring *, काष्ठा sk_buff *))
अणु
#घोषणा RCB_NOF_ALLOC_RX_BUFF_ONCE 16
	पूर्णांक unused_count = hns3_desc_unused(ring);
	पूर्णांक recv_pkts = 0;
	पूर्णांक err;

	unused_count -= ring->pending_buf;

	जबतक (recv_pkts < budget) अणु
		/* Reuse or पुनः_स्मृति buffers */
		अगर (unused_count >= RCB_NOF_ALLOC_RX_BUFF_ONCE) अणु
			hns3_nic_alloc_rx_buffers(ring, unused_count);
			unused_count = hns3_desc_unused(ring) -
					ring->pending_buf;
		पूर्ण

		/* Poll one pkt */
		err = hns3_handle_rx_bd(ring);
		/* Do not get FE क्रम the packet or failed to alloc skb */
		अगर (unlikely(!ring->skb || err == -ENXIO)) अणु
			जाओ out;
		पूर्ण अन्यथा अगर (likely(!err)) अणु
			rx_fn(ring, ring->skb);
			recv_pkts++;
		पूर्ण

		unused_count += ring->pending_buf;
		ring->skb = शून्य;
		ring->pending_buf = 0;
	पूर्ण

out:
	/* Make all data has been ग_लिखो beक्रमe submit */
	अगर (unused_count > 0)
		hns3_nic_alloc_rx_buffers(ring, unused_count);

	वापस recv_pkts;
पूर्ण

अटल bool hns3_get_new_flow_lvl(काष्ठा hns3_enet_ring_group *ring_group)
अणु
#घोषणा HNS3_RX_LOW_BYTE_RATE 10000
#घोषणा HNS3_RX_MID_BYTE_RATE 20000
#घोषणा HNS3_RX_ULTRA_PACKET_RATE 40

	क्रमागत hns3_flow_level_range new_flow_level;
	काष्ठा hns3_enet_tqp_vector *tqp_vector;
	पूर्णांक packets_per_msecs, bytes_per_msecs;
	u32 समय_passed_ms;

	tqp_vector = ring_group->ring->tqp_vector;
	समय_passed_ms =
		jअगरfies_to_msecs(jअगरfies - tqp_vector->last_jअगरfies);
	अगर (!समय_passed_ms)
		वापस false;

	करो_भाग(ring_group->total_packets, समय_passed_ms);
	packets_per_msecs = ring_group->total_packets;

	करो_भाग(ring_group->total_bytes, समय_passed_ms);
	bytes_per_msecs = ring_group->total_bytes;

	new_flow_level = ring_group->coal.flow_level;

	/* Simple throttlerate management
	 * 0-10MB/s   lower     (50000 पूर्णांकs/s)
	 * 10-20MB/s   middle    (20000 पूर्णांकs/s)
	 * 20-1249MB/s high      (18000 पूर्णांकs/s)
	 * > 40000pps  ultra     (8000 पूर्णांकs/s)
	 */
	चयन (new_flow_level) अणु
	हाल HNS3_FLOW_LOW:
		अगर (bytes_per_msecs > HNS3_RX_LOW_BYTE_RATE)
			new_flow_level = HNS3_FLOW_MID;
		अवरोध;
	हाल HNS3_FLOW_MID:
		अगर (bytes_per_msecs > HNS3_RX_MID_BYTE_RATE)
			new_flow_level = HNS3_FLOW_HIGH;
		अन्यथा अगर (bytes_per_msecs <= HNS3_RX_LOW_BYTE_RATE)
			new_flow_level = HNS3_FLOW_LOW;
		अवरोध;
	हाल HNS3_FLOW_HIGH:
	हाल HNS3_FLOW_ULTRA:
	शेष:
		अगर (bytes_per_msecs <= HNS3_RX_MID_BYTE_RATE)
			new_flow_level = HNS3_FLOW_MID;
		अवरोध;
	पूर्ण

	अगर (packets_per_msecs > HNS3_RX_ULTRA_PACKET_RATE &&
	    &tqp_vector->rx_group == ring_group)
		new_flow_level = HNS3_FLOW_ULTRA;

	ring_group->total_bytes = 0;
	ring_group->total_packets = 0;
	ring_group->coal.flow_level = new_flow_level;

	वापस true;
पूर्ण

अटल bool hns3_get_new_पूर्णांक_gl(काष्ठा hns3_enet_ring_group *ring_group)
अणु
	काष्ठा hns3_enet_tqp_vector *tqp_vector;
	u16 new_पूर्णांक_gl;

	अगर (!ring_group->ring)
		वापस false;

	tqp_vector = ring_group->ring->tqp_vector;
	अगर (!tqp_vector->last_jअगरfies)
		वापस false;

	अगर (ring_group->total_packets == 0) अणु
		ring_group->coal.पूर्णांक_gl = HNS3_INT_GL_50K;
		ring_group->coal.flow_level = HNS3_FLOW_LOW;
		वापस true;
	पूर्ण

	अगर (!hns3_get_new_flow_lvl(ring_group))
		वापस false;

	new_पूर्णांक_gl = ring_group->coal.पूर्णांक_gl;
	चयन (ring_group->coal.flow_level) अणु
	हाल HNS3_FLOW_LOW:
		new_पूर्णांक_gl = HNS3_INT_GL_50K;
		अवरोध;
	हाल HNS3_FLOW_MID:
		new_पूर्णांक_gl = HNS3_INT_GL_20K;
		अवरोध;
	हाल HNS3_FLOW_HIGH:
		new_पूर्णांक_gl = HNS3_INT_GL_18K;
		अवरोध;
	हाल HNS3_FLOW_ULTRA:
		new_पूर्णांक_gl = HNS3_INT_GL_8K;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (new_पूर्णांक_gl != ring_group->coal.पूर्णांक_gl) अणु
		ring_group->coal.पूर्णांक_gl = new_पूर्णांक_gl;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम hns3_update_new_पूर्णांक_gl(काष्ठा hns3_enet_tqp_vector *tqp_vector)
अणु
	काष्ठा hns3_enet_ring_group *rx_group = &tqp_vector->rx_group;
	काष्ठा hns3_enet_ring_group *tx_group = &tqp_vector->tx_group;
	bool rx_update, tx_update;

	/* update param every 1000ms */
	अगर (समय_beक्रमe(jअगरfies,
			tqp_vector->last_jअगरfies + msecs_to_jअगरfies(1000)))
		वापस;

	अगर (rx_group->coal.adapt_enable) अणु
		rx_update = hns3_get_new_पूर्णांक_gl(rx_group);
		अगर (rx_update)
			hns3_set_vector_coalesce_rx_gl(tqp_vector,
						       rx_group->coal.पूर्णांक_gl);
	पूर्ण

	अगर (tx_group->coal.adapt_enable) अणु
		tx_update = hns3_get_new_पूर्णांक_gl(tx_group);
		अगर (tx_update)
			hns3_set_vector_coalesce_tx_gl(tqp_vector,
						       tx_group->coal.पूर्णांक_gl);
	पूर्ण

	tqp_vector->last_jअगरfies = jअगरfies;
पूर्ण

अटल पूर्णांक hns3_nic_common_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(napi->dev);
	काष्ठा hns3_enet_ring *ring;
	पूर्णांक rx_pkt_total = 0;

	काष्ठा hns3_enet_tqp_vector *tqp_vector =
		container_of(napi, काष्ठा hns3_enet_tqp_vector, napi);
	bool clean_complete = true;
	पूर्णांक rx_budget = budget;

	अगर (unlikely(test_bit(HNS3_NIC_STATE_DOWN, &priv->state))) अणु
		napi_complete(napi);
		वापस 0;
	पूर्ण

	/* Since the actual Tx work is minimal, we can give the Tx a larger
	 * budget and be more aggressive about cleaning up the Tx descriptors.
	 */
	hns3_क्रम_each_ring(ring, tqp_vector->tx_group)
		hns3_clean_tx_ring(ring, budget);

	/* make sure rx ring budget not smaller than 1 */
	अगर (tqp_vector->num_tqps > 1)
		rx_budget = max(budget / tqp_vector->num_tqps, 1);

	hns3_क्रम_each_ring(ring, tqp_vector->rx_group) अणु
		पूर्णांक rx_cleaned = hns3_clean_rx_ring(ring, rx_budget,
						    hns3_rx_skb);
		अगर (rx_cleaned >= rx_budget)
			clean_complete = false;

		rx_pkt_total += rx_cleaned;
	पूर्ण

	tqp_vector->rx_group.total_packets += rx_pkt_total;

	अगर (!clean_complete)
		वापस budget;

	अगर (napi_complete(napi) &&
	    likely(!test_bit(HNS3_NIC_STATE_DOWN, &priv->state))) अणु
		hns3_update_new_पूर्णांक_gl(tqp_vector);
		hns3_mask_vector_irq(tqp_vector, 1);
	पूर्ण

	वापस rx_pkt_total;
पूर्ण

अटल पूर्णांक hns3_get_vector_ring_chain(काष्ठा hns3_enet_tqp_vector *tqp_vector,
				      काष्ठा hnae3_ring_chain_node *head)
अणु
	काष्ठा pci_dev *pdev = tqp_vector->handle->pdev;
	काष्ठा hnae3_ring_chain_node *cur_chain = head;
	काष्ठा hnae3_ring_chain_node *chain;
	काष्ठा hns3_enet_ring *tx_ring;
	काष्ठा hns3_enet_ring *rx_ring;

	tx_ring = tqp_vector->tx_group.ring;
	अगर (tx_ring) अणु
		cur_chain->tqp_index = tx_ring->tqp->tqp_index;
		hnae3_set_bit(cur_chain->flag, HNAE3_RING_TYPE_B,
			      HNAE3_RING_TYPE_TX);
		hnae3_set_field(cur_chain->पूर्णांक_gl_idx, HNAE3_RING_GL_IDX_M,
				HNAE3_RING_GL_IDX_S, HNAE3_RING_GL_TX);

		cur_chain->next = शून्य;

		जबतक (tx_ring->next) अणु
			tx_ring = tx_ring->next;

			chain = devm_kzalloc(&pdev->dev, माप(*chain),
					     GFP_KERNEL);
			अगर (!chain)
				जाओ err_मुक्त_chain;

			cur_chain->next = chain;
			chain->tqp_index = tx_ring->tqp->tqp_index;
			hnae3_set_bit(chain->flag, HNAE3_RING_TYPE_B,
				      HNAE3_RING_TYPE_TX);
			hnae3_set_field(chain->पूर्णांक_gl_idx,
					HNAE3_RING_GL_IDX_M,
					HNAE3_RING_GL_IDX_S,
					HNAE3_RING_GL_TX);

			cur_chain = chain;
		पूर्ण
	पूर्ण

	rx_ring = tqp_vector->rx_group.ring;
	अगर (!tx_ring && rx_ring) अणु
		cur_chain->next = शून्य;
		cur_chain->tqp_index = rx_ring->tqp->tqp_index;
		hnae3_set_bit(cur_chain->flag, HNAE3_RING_TYPE_B,
			      HNAE3_RING_TYPE_RX);
		hnae3_set_field(cur_chain->पूर्णांक_gl_idx, HNAE3_RING_GL_IDX_M,
				HNAE3_RING_GL_IDX_S, HNAE3_RING_GL_RX);

		rx_ring = rx_ring->next;
	पूर्ण

	जबतक (rx_ring) अणु
		chain = devm_kzalloc(&pdev->dev, माप(*chain), GFP_KERNEL);
		अगर (!chain)
			जाओ err_मुक्त_chain;

		cur_chain->next = chain;
		chain->tqp_index = rx_ring->tqp->tqp_index;
		hnae3_set_bit(chain->flag, HNAE3_RING_TYPE_B,
			      HNAE3_RING_TYPE_RX);
		hnae3_set_field(chain->पूर्णांक_gl_idx, HNAE3_RING_GL_IDX_M,
				HNAE3_RING_GL_IDX_S, HNAE3_RING_GL_RX);

		cur_chain = chain;

		rx_ring = rx_ring->next;
	पूर्ण

	वापस 0;

err_मुक्त_chain:
	cur_chain = head->next;
	जबतक (cur_chain) अणु
		chain = cur_chain->next;
		devm_kमुक्त(&pdev->dev, cur_chain);
		cur_chain = chain;
	पूर्ण
	head->next = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल व्योम hns3_मुक्त_vector_ring_chain(काष्ठा hns3_enet_tqp_vector *tqp_vector,
					काष्ठा hnae3_ring_chain_node *head)
अणु
	काष्ठा pci_dev *pdev = tqp_vector->handle->pdev;
	काष्ठा hnae3_ring_chain_node *chain_पंचांगp, *chain;

	chain = head->next;

	जबतक (chain) अणु
		chain_पंचांगp = chain->next;
		devm_kमुक्त(&pdev->dev, chain);
		chain = chain_पंचांगp;
	पूर्ण
पूर्ण

अटल व्योम hns3_add_ring_to_group(काष्ठा hns3_enet_ring_group *group,
				   काष्ठा hns3_enet_ring *ring)
अणु
	ring->next = group->ring;
	group->ring = ring;

	group->count++;
पूर्ण

अटल व्योम hns3_nic_set_cpumask(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा pci_dev *pdev = priv->ae_handle->pdev;
	काष्ठा hns3_enet_tqp_vector *tqp_vector;
	पूर्णांक num_vectors = priv->vector_num;
	पूर्णांक numa_node;
	पूर्णांक vector_i;

	numa_node = dev_to_node(&pdev->dev);

	क्रम (vector_i = 0; vector_i < num_vectors; vector_i++) अणु
		tqp_vector = &priv->tqp_vector[vector_i];
		cpumask_set_cpu(cpumask_local_spपढ़ो(vector_i, numa_node),
				&tqp_vector->affinity_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_nic_init_vector_data(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_handle *h = priv->ae_handle;
	काष्ठा hns3_enet_tqp_vector *tqp_vector;
	पूर्णांक ret;
	पूर्णांक i;

	hns3_nic_set_cpumask(priv);

	क्रम (i = 0; i < priv->vector_num; i++) अणु
		tqp_vector = &priv->tqp_vector[i];
		hns3_vector_coalesce_init_hw(tqp_vector, priv);
		tqp_vector->num_tqps = 0;
	पूर्ण

	क्रम (i = 0; i < h->kinfo.num_tqps; i++) अणु
		u16 vector_i = i % priv->vector_num;
		u16 tqp_num = h->kinfo.num_tqps;

		tqp_vector = &priv->tqp_vector[vector_i];

		hns3_add_ring_to_group(&tqp_vector->tx_group,
				       &priv->ring[i]);

		hns3_add_ring_to_group(&tqp_vector->rx_group,
				       &priv->ring[i + tqp_num]);

		priv->ring[i].tqp_vector = tqp_vector;
		priv->ring[i + tqp_num].tqp_vector = tqp_vector;
		tqp_vector->num_tqps++;
	पूर्ण

	क्रम (i = 0; i < priv->vector_num; i++) अणु
		काष्ठा hnae3_ring_chain_node vector_ring_chain;

		tqp_vector = &priv->tqp_vector[i];

		tqp_vector->rx_group.total_bytes = 0;
		tqp_vector->rx_group.total_packets = 0;
		tqp_vector->tx_group.total_bytes = 0;
		tqp_vector->tx_group.total_packets = 0;
		tqp_vector->handle = h;

		ret = hns3_get_vector_ring_chain(tqp_vector,
						 &vector_ring_chain);
		अगर (ret)
			जाओ map_ring_fail;

		ret = h->ae_algo->ops->map_ring_to_vector(h,
			tqp_vector->vector_irq, &vector_ring_chain);

		hns3_मुक्त_vector_ring_chain(tqp_vector, &vector_ring_chain);

		अगर (ret)
			जाओ map_ring_fail;

		netअगर_napi_add(priv->netdev, &tqp_vector->napi,
			       hns3_nic_common_poll, NAPI_POLL_WEIGHT);
	पूर्ण

	वापस 0;

map_ring_fail:
	जबतक (i--)
		netअगर_napi_del(&priv->tqp_vector[i].napi);

	वापस ret;
पूर्ण

अटल व्योम hns3_nic_init_coal_cfg(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(priv->ae_handle->pdev);
	काष्ठा hns3_enet_coalesce *tx_coal = &priv->tx_coal;
	काष्ठा hns3_enet_coalesce *rx_coal = &priv->rx_coal;

	/* initialize the configuration क्रम पूर्णांकerrupt coalescing.
	 * 1. GL (Interrupt Gap Limiter)
	 * 2. RL (Interrupt Rate Limiter)
	 * 3. QL (Interrupt Quantity Limiter)
	 *
	 * Default: enable पूर्णांकerrupt coalescing self-adaptive and GL
	 */
	tx_coal->adapt_enable = 1;
	rx_coal->adapt_enable = 1;

	tx_coal->पूर्णांक_gl = HNS3_INT_GL_50K;
	rx_coal->पूर्णांक_gl = HNS3_INT_GL_50K;

	rx_coal->flow_level = HNS3_FLOW_LOW;
	tx_coal->flow_level = HNS3_FLOW_LOW;

	अगर (ae_dev->dev_specs.पूर्णांक_ql_max) अणु
		tx_coal->पूर्णांक_ql = HNS3_INT_QL_DEFAULT_CFG;
		rx_coal->पूर्णांक_ql = HNS3_INT_QL_DEFAULT_CFG;
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_nic_alloc_vector_data(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_handle *h = priv->ae_handle;
	काष्ठा hns3_enet_tqp_vector *tqp_vector;
	काष्ठा hnae3_vector_info *vector;
	काष्ठा pci_dev *pdev = h->pdev;
	u16 tqp_num = h->kinfo.num_tqps;
	u16 vector_num;
	पूर्णांक ret = 0;
	u16 i;

	/* RSS size, cpu online and vector_num should be the same */
	/* Should consider 2p/4p later */
	vector_num = min_t(u16, num_online_cpus(), tqp_num);

	vector = devm_kसुस्मृति(&pdev->dev, vector_num, माप(*vector),
			      GFP_KERNEL);
	अगर (!vector)
		वापस -ENOMEM;

	/* save the actual available vector number */
	vector_num = h->ae_algo->ops->get_vector(h, vector_num, vector);

	priv->vector_num = vector_num;
	priv->tqp_vector = (काष्ठा hns3_enet_tqp_vector *)
		devm_kसुस्मृति(&pdev->dev, vector_num, माप(*priv->tqp_vector),
			     GFP_KERNEL);
	अगर (!priv->tqp_vector) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < priv->vector_num; i++) अणु
		tqp_vector = &priv->tqp_vector[i];
		tqp_vector->idx = i;
		tqp_vector->mask_addr = vector[i].io_addr;
		tqp_vector->vector_irq = vector[i].vector;
		hns3_vector_coalesce_init(tqp_vector, priv);
	पूर्ण

out:
	devm_kमुक्त(&pdev->dev, vector);
	वापस ret;
पूर्ण

अटल व्योम hns3_clear_ring_group(काष्ठा hns3_enet_ring_group *group)
अणु
	group->ring = शून्य;
	group->count = 0;
पूर्ण

अटल व्योम hns3_nic_uninit_vector_data(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_ring_chain_node vector_ring_chain;
	काष्ठा hnae3_handle *h = priv->ae_handle;
	काष्ठा hns3_enet_tqp_vector *tqp_vector;
	पूर्णांक i;

	क्रम (i = 0; i < priv->vector_num; i++) अणु
		tqp_vector = &priv->tqp_vector[i];

		अगर (!tqp_vector->rx_group.ring && !tqp_vector->tx_group.ring)
			जारी;

		/* Since the mapping can be overwritten, when fail to get the
		 * chain between vector and ring, we should go on to deal with
		 * the reमुख्यing options.
		 */
		अगर (hns3_get_vector_ring_chain(tqp_vector, &vector_ring_chain))
			dev_warn(priv->dev, "failed to get ring chain\n");

		h->ae_algo->ops->unmap_ring_from_vector(h,
			tqp_vector->vector_irq, &vector_ring_chain);

		hns3_मुक्त_vector_ring_chain(tqp_vector, &vector_ring_chain);

		hns3_clear_ring_group(&tqp_vector->rx_group);
		hns3_clear_ring_group(&tqp_vector->tx_group);
		netअगर_napi_del(&priv->tqp_vector[i].napi);
	पूर्ण
पूर्ण

अटल व्योम hns3_nic_dealloc_vector_data(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_handle *h = priv->ae_handle;
	काष्ठा pci_dev *pdev = h->pdev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < priv->vector_num; i++) अणु
		काष्ठा hns3_enet_tqp_vector *tqp_vector;

		tqp_vector = &priv->tqp_vector[i];
		ret = h->ae_algo->ops->put_vector(h, tqp_vector->vector_irq);
		अगर (ret)
			वापस;
	पूर्ण

	devm_kमुक्त(&pdev->dev, priv->tqp_vector);
पूर्ण

अटल व्योम hns3_ring_get_cfg(काष्ठा hnae3_queue *q, काष्ठा hns3_nic_priv *priv,
			      अचिन्हित पूर्णांक ring_type)
अणु
	पूर्णांक queue_num = priv->ae_handle->kinfo.num_tqps;
	काष्ठा hns3_enet_ring *ring;
	पूर्णांक desc_num;

	अगर (ring_type == HNAE3_RING_TYPE_TX) अणु
		ring = &priv->ring[q->tqp_index];
		desc_num = priv->ae_handle->kinfo.num_tx_desc;
		ring->queue_index = q->tqp_index;
	पूर्ण अन्यथा अणु
		ring = &priv->ring[q->tqp_index + queue_num];
		desc_num = priv->ae_handle->kinfo.num_rx_desc;
		ring->queue_index = q->tqp_index;
	पूर्ण

	hnae3_set_bit(ring->flag, HNAE3_RING_TYPE_B, ring_type);

	ring->tqp = q;
	ring->desc = शून्य;
	ring->desc_cb = शून्य;
	ring->dev = priv->dev;
	ring->desc_dma_addr = 0;
	ring->buf_size = q->buf_size;
	ring->desc_num = desc_num;
	ring->next_to_use = 0;
	ring->next_to_clean = 0;
	ring->last_to_use = 0;
पूर्ण

अटल व्योम hns3_queue_to_ring(काष्ठा hnae3_queue *tqp,
			       काष्ठा hns3_nic_priv *priv)
अणु
	hns3_ring_get_cfg(tqp, priv, HNAE3_RING_TYPE_TX);
	hns3_ring_get_cfg(tqp, priv, HNAE3_RING_TYPE_RX);
पूर्ण

अटल पूर्णांक hns3_get_ring_config(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_handle *h = priv->ae_handle;
	काष्ठा pci_dev *pdev = h->pdev;
	पूर्णांक i;

	priv->ring = devm_kzalloc(&pdev->dev,
				  array3_size(h->kinfo.num_tqps,
					      माप(*priv->ring), 2),
				  GFP_KERNEL);
	अगर (!priv->ring)
		वापस -ENOMEM;

	क्रम (i = 0; i < h->kinfo.num_tqps; i++)
		hns3_queue_to_ring(h->kinfo.tqp[i], priv);

	वापस 0;
पूर्ण

अटल व्योम hns3_put_ring_config(काष्ठा hns3_nic_priv *priv)
अणु
	अगर (!priv->ring)
		वापस;

	devm_kमुक्त(priv->dev, priv->ring);
	priv->ring = शून्य;
पूर्ण

अटल पूर्णांक hns3_alloc_ring_memory(काष्ठा hns3_enet_ring *ring)
अणु
	पूर्णांक ret;

	अगर (ring->desc_num <= 0 || ring->buf_size <= 0)
		वापस -EINVAL;

	ring->desc_cb = devm_kसुस्मृति(ring_to_dev(ring), ring->desc_num,
				     माप(ring->desc_cb[0]), GFP_KERNEL);
	अगर (!ring->desc_cb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = hns3_alloc_desc(ring);
	अगर (ret)
		जाओ out_with_desc_cb;

	अगर (!HNAE3_IS_TX_RING(ring)) अणु
		ret = hns3_alloc_ring_buffers(ring);
		अगर (ret)
			जाओ out_with_desc;
	पूर्ण

	वापस 0;

out_with_desc:
	hns3_मुक्त_desc(ring);
out_with_desc_cb:
	devm_kमुक्त(ring_to_dev(ring), ring->desc_cb);
	ring->desc_cb = शून्य;
out:
	वापस ret;
पूर्ण

व्योम hns3_fini_ring(काष्ठा hns3_enet_ring *ring)
अणु
	hns3_मुक्त_desc(ring);
	devm_kमुक्त(ring_to_dev(ring), ring->desc_cb);
	ring->desc_cb = शून्य;
	ring->next_to_clean = 0;
	ring->next_to_use = 0;
	ring->last_to_use = 0;
	ring->pending_buf = 0;
	अगर (ring->skb) अणु
		dev_kमुक्त_skb_any(ring->skb);
		ring->skb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक hns3_buf_size2type(u32 buf_size)
अणु
	पूर्णांक bd_माप_प्रकारype;

	चयन (buf_size) अणु
	हाल 512:
		bd_माप_प्रकारype = HNS3_BD_SIZE_512_TYPE;
		अवरोध;
	हाल 1024:
		bd_माप_प्रकारype = HNS3_BD_SIZE_1024_TYPE;
		अवरोध;
	हाल 2048:
		bd_माप_प्रकारype = HNS3_BD_SIZE_2048_TYPE;
		अवरोध;
	हाल 4096:
		bd_माप_प्रकारype = HNS3_BD_SIZE_4096_TYPE;
		अवरोध;
	शेष:
		bd_माप_प्रकारype = HNS3_BD_SIZE_2048_TYPE;
	पूर्ण

	वापस bd_माप_प्रकारype;
पूर्ण

अटल व्योम hns3_init_ring_hw(काष्ठा hns3_enet_ring *ring)
अणु
	dma_addr_t dma = ring->desc_dma_addr;
	काष्ठा hnae3_queue *q = ring->tqp;

	अगर (!HNAE3_IS_TX_RING(ring)) अणु
		hns3_ग_लिखो_dev(q, HNS3_RING_RX_RING_BASEADDR_L_REG, (u32)dma);
		hns3_ग_लिखो_dev(q, HNS3_RING_RX_RING_BASEADDR_H_REG,
			       (u32)((dma >> 31) >> 1));

		hns3_ग_लिखो_dev(q, HNS3_RING_RX_RING_BD_LEN_REG,
			       hns3_buf_size2type(ring->buf_size));
		hns3_ग_लिखो_dev(q, HNS3_RING_RX_RING_BD_NUM_REG,
			       ring->desc_num / 8 - 1);
	पूर्ण अन्यथा अणु
		hns3_ग_लिखो_dev(q, HNS3_RING_TX_RING_BASEADDR_L_REG,
			       (u32)dma);
		hns3_ग_लिखो_dev(q, HNS3_RING_TX_RING_BASEADDR_H_REG,
			       (u32)((dma >> 31) >> 1));

		hns3_ग_लिखो_dev(q, HNS3_RING_TX_RING_BD_NUM_REG,
			       ring->desc_num / 8 - 1);
	पूर्ण
पूर्ण

अटल व्योम hns3_init_tx_ring_tc(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &priv->ae_handle->kinfo;
	काष्ठा hnae3_tc_info *tc_info = &kinfo->tc_info;
	पूर्णांक i;

	क्रम (i = 0; i < HNAE3_MAX_TC; i++) अणु
		पूर्णांक j;

		अगर (!test_bit(i, &tc_info->tc_en))
			जारी;

		क्रम (j = 0; j < tc_info->tqp_count[i]; j++) अणु
			काष्ठा hnae3_queue *q;

			q = priv->ring[tc_info->tqp_offset[i] + j].tqp;
			hns3_ग_लिखो_dev(q, HNS3_RING_TX_RING_TC_REG, i);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक hns3_init_all_ring(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_handle *h = priv->ae_handle;
	पूर्णांक ring_num = h->kinfo.num_tqps * 2;
	पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = 0; i < ring_num; i++) अणु
		ret = hns3_alloc_ring_memory(&priv->ring[i]);
		अगर (ret) अणु
			dev_err(priv->dev,
				"Alloc ring memory fail! ret=%d\n", ret);
			जाओ out_when_alloc_ring_memory;
		पूर्ण

		u64_stats_init(&priv->ring[i].syncp);
	पूर्ण

	वापस 0;

out_when_alloc_ring_memory:
	क्रम (j = i - 1; j >= 0; j--)
		hns3_fini_ring(&priv->ring[j]);

	वापस -ENOMEM;
पूर्ण

अटल व्योम hns3_uninit_all_ring(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_handle *h = priv->ae_handle;
	पूर्णांक i;

	क्रम (i = 0; i < h->kinfo.num_tqps; i++) अणु
		hns3_fini_ring(&priv->ring[i]);
		hns3_fini_ring(&priv->ring[i + h->kinfo.num_tqps]);
	पूर्ण
पूर्ण

/* Set mac addr अगर it is configured. or leave it to the AE driver */
अटल पूर्णांक hns3_init_mac_addr(काष्ठा net_device *netdev)
अणु
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae3_handle *h = priv->ae_handle;
	u8 mac_addr_temp[ETH_ALEN];
	पूर्णांक ret = 0;

	अगर (h->ae_algo->ops->get_mac_addr)
		h->ae_algo->ops->get_mac_addr(h, mac_addr_temp);

	/* Check अगर the MAC address is valid, अगर not get a अक्रमom one */
	अगर (!is_valid_ether_addr(mac_addr_temp)) अणु
		eth_hw_addr_अक्रमom(netdev);
		dev_warn(priv->dev, "using random MAC address %pM\n",
			 netdev->dev_addr);
	पूर्ण अन्यथा अगर (!ether_addr_equal(netdev->dev_addr, mac_addr_temp)) अणु
		ether_addr_copy(netdev->dev_addr, mac_addr_temp);
		ether_addr_copy(netdev->perm_addr, mac_addr_temp);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	अगर (h->ae_algo->ops->set_mac_addr)
		ret = h->ae_algo->ops->set_mac_addr(h, netdev->dev_addr, true);

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_init_phy(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	पूर्णांक ret = 0;

	अगर (h->ae_algo->ops->mac_connect_phy)
		ret = h->ae_algo->ops->mac_connect_phy(h);

	वापस ret;
पूर्ण

अटल व्योम hns3_uninit_phy(काष्ठा net_device *netdev)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);

	अगर (h->ae_algo->ops->mac_disconnect_phy)
		h->ae_algo->ops->mac_disconnect_phy(h);
पूर्ण

अटल पूर्णांक hns3_client_start(काष्ठा hnae3_handle *handle)
अणु
	अगर (!handle->ae_algo->ops->client_start)
		वापस 0;

	वापस handle->ae_algo->ops->client_start(handle);
पूर्ण

अटल व्योम hns3_client_stop(काष्ठा hnae3_handle *handle)
अणु
	अगर (!handle->ae_algo->ops->client_stop)
		वापस;

	handle->ae_algo->ops->client_stop(handle);
पूर्ण

अटल व्योम hns3_info_show(काष्ठा hns3_nic_priv *priv)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &priv->ae_handle->kinfo;

	dev_info(priv->dev, "MAC address: %pM\n", priv->netdev->dev_addr);
	dev_info(priv->dev, "Task queue pairs numbers: %u\n", kinfo->num_tqps);
	dev_info(priv->dev, "RSS size: %u\n", kinfo->rss_size);
	dev_info(priv->dev, "Allocated RSS size: %u\n", kinfo->req_rss_size);
	dev_info(priv->dev, "RX buffer length: %u\n", kinfo->rx_buf_len);
	dev_info(priv->dev, "Desc num per TX queue: %u\n", kinfo->num_tx_desc);
	dev_info(priv->dev, "Desc num per RX queue: %u\n", kinfo->num_rx_desc);
	dev_info(priv->dev, "Total number of enabled TCs: %u\n",
		 kinfo->tc_info.num_tc);
	dev_info(priv->dev, "Max mtu size: %u\n", priv->netdev->max_mtu);
पूर्ण

अटल पूर्णांक hns3_client_init(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा pci_dev *pdev = handle->pdev;
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);
	u16 alloc_tqps, max_rss_size;
	काष्ठा hns3_nic_priv *priv;
	काष्ठा net_device *netdev;
	पूर्णांक ret;

	handle->ae_algo->ops->get_tqps_and_rss_info(handle, &alloc_tqps,
						    &max_rss_size);
	netdev = alloc_etherdev_mq(माप(काष्ठा hns3_nic_priv), alloc_tqps);
	अगर (!netdev)
		वापस -ENOMEM;

	priv = netdev_priv(netdev);
	priv->dev = &pdev->dev;
	priv->netdev = netdev;
	priv->ae_handle = handle;
	priv->tx_समयout_count = 0;
	priv->max_non_tso_bd_num = ae_dev->dev_specs.max_non_tso_bd_num;
	set_bit(HNS3_NIC_STATE_DOWN, &priv->state);

	handle->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_LEVEL);

	handle->kinfo.netdev = netdev;
	handle->priv = (व्योम *)priv;

	hns3_init_mac_addr(netdev);

	hns3_set_शेष_feature(netdev);

	netdev->watchकरोg_समयo = HNS3_TX_TIMEOUT;
	netdev->priv_flags |= IFF_UNICAST_FLT;
	netdev->netdev_ops = &hns3_nic_netdev_ops;
	SET_NETDEV_DEV(netdev, &pdev->dev);
	hns3_ethtool_set_ops(netdev);

	/* Carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(netdev);

	ret = hns3_get_ring_config(priv);
	अगर (ret) अणु
		ret = -ENOMEM;
		जाओ out_get_ring_cfg;
	पूर्ण

	hns3_nic_init_coal_cfg(priv);

	ret = hns3_nic_alloc_vector_data(priv);
	अगर (ret) अणु
		ret = -ENOMEM;
		जाओ out_alloc_vector_data;
	पूर्ण

	ret = hns3_nic_init_vector_data(priv);
	अगर (ret) अणु
		ret = -ENOMEM;
		जाओ out_init_vector_data;
	पूर्ण

	ret = hns3_init_all_ring(priv);
	अगर (ret) अणु
		ret = -ENOMEM;
		जाओ out_init_ring;
	पूर्ण

	ret = hns3_init_phy(netdev);
	अगर (ret)
		जाओ out_init_phy;

	/* the device can work without cpu rmap, only aRFS needs it */
	ret = hns3_set_rx_cpu_rmap(netdev);
	अगर (ret)
		dev_warn(priv->dev, "set rx cpu rmap fail, ret=%d\n", ret);

	ret = hns3_nic_init_irq(priv);
	अगर (ret) अणु
		dev_err(priv->dev, "init irq failed! ret=%d\n", ret);
		hns3_मुक्त_rx_cpu_rmap(netdev);
		जाओ out_init_irq_fail;
	पूर्ण

	ret = hns3_client_start(handle);
	अगर (ret) अणु
		dev_err(priv->dev, "hns3_client_start fail! ret=%d\n", ret);
		जाओ out_client_start;
	पूर्ण

	hns3_dcbnl_setup(handle);

	hns3_dbg_init(handle);

	netdev->max_mtu = HNS3_MAX_MTU(ae_dev->dev_specs.max_frm_size);

	अगर (test_bit(HNAE3_DEV_SUPPORT_HW_TX_CSUM_B, ae_dev->caps))
		set_bit(HNS3_NIC_STATE_HW_TX_CSUM_ENABLE, &priv->state);

	set_bit(HNS3_NIC_STATE_INITED, &priv->state);

	अगर (ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V3)
		set_bit(HNAE3_PFLAG_LIMIT_PROMISC, &handle->supported_pflags);

	ret = रेजिस्टर_netdev(netdev);
	अगर (ret) अणु
		dev_err(priv->dev, "probe register netdev fail!\n");
		जाओ out_reg_netdev_fail;
	पूर्ण

	अगर (netअगर_msg_drv(handle))
		hns3_info_show(priv);

	वापस ret;

out_reg_netdev_fail:
	hns3_dbg_uninit(handle);
out_client_start:
	hns3_मुक्त_rx_cpu_rmap(netdev);
	hns3_nic_uninit_irq(priv);
out_init_irq_fail:
	hns3_uninit_phy(netdev);
out_init_phy:
	hns3_uninit_all_ring(priv);
out_init_ring:
	hns3_nic_uninit_vector_data(priv);
out_init_vector_data:
	hns3_nic_dealloc_vector_data(priv);
out_alloc_vector_data:
	priv->ring = शून्य;
out_get_ring_cfg:
	priv->ae_handle = शून्य;
	मुक्त_netdev(netdev);
	वापस ret;
पूर्ण

अटल व्योम hns3_client_uninit(काष्ठा hnae3_handle *handle, bool reset)
अणु
	काष्ठा net_device *netdev = handle->kinfo.netdev;
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);

	अगर (netdev->reg_state != NETREG_UNINITIALIZED)
		unरेजिस्टर_netdev(netdev);

	hns3_client_stop(handle);

	hns3_uninit_phy(netdev);

	अगर (!test_and_clear_bit(HNS3_NIC_STATE_INITED, &priv->state)) अणु
		netdev_warn(netdev, "already uninitialized\n");
		जाओ out_netdev_मुक्त;
	पूर्ण

	hns3_मुक्त_rx_cpu_rmap(netdev);

	hns3_nic_uninit_irq(priv);

	hns3_clear_all_ring(handle, true);

	hns3_nic_uninit_vector_data(priv);

	hns3_nic_dealloc_vector_data(priv);

	hns3_uninit_all_ring(priv);

	hns3_put_ring_config(priv);

out_netdev_मुक्त:
	hns3_dbg_uninit(handle);
	मुक्त_netdev(netdev);
पूर्ण

अटल व्योम hns3_link_status_change(काष्ठा hnae3_handle *handle, bool linkup)
अणु
	काष्ठा net_device *netdev = handle->kinfo.netdev;

	अगर (!netdev)
		वापस;

	अगर (linkup) अणु
		netअगर_tx_wake_all_queues(netdev);
		netअगर_carrier_on(netdev);
		अगर (netअगर_msg_link(handle))
			netdev_info(netdev, "link up\n");
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(netdev);
		netअगर_tx_stop_all_queues(netdev);
		अगर (netअगर_msg_link(handle))
			netdev_info(netdev, "link down\n");
	पूर्ण
पूर्ण

अटल व्योम hns3_clear_tx_ring(काष्ठा hns3_enet_ring *ring)
अणु
	जबतक (ring->next_to_clean != ring->next_to_use) अणु
		ring->desc[ring->next_to_clean].tx.bdtp_fe_sc_vld_ra_ri = 0;
		hns3_मुक्त_buffer_detach(ring, ring->next_to_clean, 0);
		ring_ptr_move_fw(ring, next_to_clean);
	पूर्ण

	ring->pending_buf = 0;
पूर्ण

अटल पूर्णांक hns3_clear_rx_ring(काष्ठा hns3_enet_ring *ring)
अणु
	काष्ठा hns3_desc_cb res_cbs;
	पूर्णांक ret;

	जबतक (ring->next_to_use != ring->next_to_clean) अणु
		/* When a buffer is not reused, it's memory has been
		 * मुक्तd in hns3_handle_rx_bd or will be मुक्तd by
		 * stack, so we need to replace the buffer here.
		 */
		अगर (!ring->desc_cb[ring->next_to_use].reuse_flag) अणु
			ret = hns3_alloc_and_map_buffer(ring, &res_cbs);
			अगर (ret) अणु
				u64_stats_update_begin(&ring->syncp);
				ring->stats.sw_err_cnt++;
				u64_stats_update_end(&ring->syncp);
				/* अगर alloc new buffer fail, निकास directly
				 * and reclear in up flow.
				 */
				netdev_warn(ring_to_netdev(ring),
					    "reserve buffer map failed, ret = %d\n",
					    ret);
				वापस ret;
			पूर्ण
			hns3_replace_buffer(ring, ring->next_to_use, &res_cbs);
		पूर्ण
		ring_ptr_move_fw(ring, next_to_use);
	पूर्ण

	/* Free the pending skb in rx ring */
	अगर (ring->skb) अणु
		dev_kमुक्त_skb_any(ring->skb);
		ring->skb = शून्य;
		ring->pending_buf = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hns3_क्रमce_clear_rx_ring(काष्ठा hns3_enet_ring *ring)
अणु
	जबतक (ring->next_to_use != ring->next_to_clean) अणु
		/* When a buffer is not reused, it's memory has been
		 * मुक्तd in hns3_handle_rx_bd or will be मुक्तd by
		 * stack, so only need to unmap the buffer here.
		 */
		अगर (!ring->desc_cb[ring->next_to_use].reuse_flag) अणु
			hns3_unmap_buffer(ring,
					  &ring->desc_cb[ring->next_to_use]);
			ring->desc_cb[ring->next_to_use].dma = 0;
		पूर्ण

		ring_ptr_move_fw(ring, next_to_use);
	पूर्ण
पूर्ण

अटल व्योम hns3_clear_all_ring(काष्ठा hnae3_handle *h, bool क्रमce)
अणु
	काष्ठा net_device *ndev = h->kinfo.netdev;
	काष्ठा hns3_nic_priv *priv = netdev_priv(ndev);
	u32 i;

	क्रम (i = 0; i < h->kinfo.num_tqps; i++) अणु
		काष्ठा hns3_enet_ring *ring;

		ring = &priv->ring[i];
		hns3_clear_tx_ring(ring);

		ring = &priv->ring[i + h->kinfo.num_tqps];
		/* Continue to clear other rings even अगर clearing some
		 * rings failed.
		 */
		अगर (क्रमce)
			hns3_क्रमce_clear_rx_ring(ring);
		अन्यथा
			hns3_clear_rx_ring(ring);
	पूर्ण
पूर्ण

पूर्णांक hns3_nic_reset_all_ring(काष्ठा hnae3_handle *h)
अणु
	काष्ठा net_device *ndev = h->kinfo.netdev;
	काष्ठा hns3_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hns3_enet_ring *rx_ring;
	पूर्णांक i, j;
	पूर्णांक ret;

	ret = h->ae_algo->ops->reset_queue(h);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < h->kinfo.num_tqps; i++) अणु
		hns3_init_ring_hw(&priv->ring[i]);

		/* We need to clear tx ring here because self test will
		 * use the ring and will not run करोwn beक्रमe up
		 */
		hns3_clear_tx_ring(&priv->ring[i]);
		priv->ring[i].next_to_clean = 0;
		priv->ring[i].next_to_use = 0;
		priv->ring[i].last_to_use = 0;

		rx_ring = &priv->ring[i + h->kinfo.num_tqps];
		hns3_init_ring_hw(rx_ring);
		ret = hns3_clear_rx_ring(rx_ring);
		अगर (ret)
			वापस ret;

		/* We can not know the hardware head and tail when this
		 * function is called in reset flow, so we reuse all desc.
		 */
		क्रम (j = 0; j < rx_ring->desc_num; j++)
			hns3_reuse_buffer(rx_ring, j);

		rx_ring->next_to_clean = 0;
		rx_ring->next_to_use = 0;
	पूर्ण

	hns3_init_tx_ring_tc(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_reset_notअगरy_करोwn_enet(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा net_device *ndev = kinfo->netdev;
	काष्ठा hns3_nic_priv *priv = netdev_priv(ndev);

	अगर (test_and_set_bit(HNS3_NIC_STATE_RESETTING, &priv->state))
		वापस 0;

	अगर (!netअगर_running(ndev))
		वापस 0;

	वापस hns3_nic_net_stop(ndev);
पूर्ण

अटल पूर्णांक hns3_reset_notअगरy_up_enet(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &handle->kinfo;
	काष्ठा hns3_nic_priv *priv = netdev_priv(kinfo->netdev);
	पूर्णांक ret = 0;

	अगर (!test_bit(HNS3_NIC_STATE_INITED, &priv->state)) अणु
		netdev_err(kinfo->netdev, "device is not initialized yet\n");
		वापस -EFAULT;
	पूर्ण

	clear_bit(HNS3_NIC_STATE_RESETTING, &priv->state);

	अगर (netअगर_running(kinfo->netdev)) अणु
		ret = hns3_nic_net_खोलो(kinfo->netdev);
		अगर (ret) अणु
			set_bit(HNS3_NIC_STATE_RESETTING, &priv->state);
			netdev_err(kinfo->netdev,
				   "net up fail, ret=%d!\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_reset_notअगरy_init_enet(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा net_device *netdev = handle->kinfo.netdev;
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);
	पूर्णांक ret;

	/* Carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(netdev);

	ret = hns3_get_ring_config(priv);
	अगर (ret)
		वापस ret;

	ret = hns3_nic_alloc_vector_data(priv);
	अगर (ret)
		जाओ err_put_ring;

	ret = hns3_nic_init_vector_data(priv);
	अगर (ret)
		जाओ err_dealloc_vector;

	ret = hns3_init_all_ring(priv);
	अगर (ret)
		जाओ err_uninit_vector;

	/* the device can work without cpu rmap, only aRFS needs it */
	ret = hns3_set_rx_cpu_rmap(netdev);
	अगर (ret)
		dev_warn(priv->dev, "set rx cpu rmap fail, ret=%d\n", ret);

	ret = hns3_nic_init_irq(priv);
	अगर (ret) अणु
		dev_err(priv->dev, "init irq failed! ret=%d\n", ret);
		hns3_मुक्त_rx_cpu_rmap(netdev);
		जाओ err_init_irq_fail;
	पूर्ण

	अगर (!hns3_is_phys_func(handle->pdev))
		hns3_init_mac_addr(netdev);

	ret = hns3_client_start(handle);
	अगर (ret) अणु
		dev_err(priv->dev, "hns3_client_start fail! ret=%d\n", ret);
		जाओ err_client_start_fail;
	पूर्ण

	set_bit(HNS3_NIC_STATE_INITED, &priv->state);

	वापस ret;

err_client_start_fail:
	hns3_मुक्त_rx_cpu_rmap(netdev);
	hns3_nic_uninit_irq(priv);
err_init_irq_fail:
	hns3_uninit_all_ring(priv);
err_uninit_vector:
	hns3_nic_uninit_vector_data(priv);
err_dealloc_vector:
	hns3_nic_dealloc_vector_data(priv);
err_put_ring:
	hns3_put_ring_config(priv);

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_reset_notअगरy_uninit_enet(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा net_device *netdev = handle->kinfo.netdev;
	काष्ठा hns3_nic_priv *priv = netdev_priv(netdev);

	अगर (!test_and_clear_bit(HNS3_NIC_STATE_INITED, &priv->state)) अणु
		netdev_warn(netdev, "already uninitialized\n");
		वापस 0;
	पूर्ण

	hns3_मुक्त_rx_cpu_rmap(netdev);
	hns3_nic_uninit_irq(priv);
	hns3_clear_all_ring(handle, true);
	hns3_reset_tx_queue(priv->ae_handle);

	hns3_nic_uninit_vector_data(priv);

	hns3_nic_dealloc_vector_data(priv);

	hns3_uninit_all_ring(priv);

	hns3_put_ring_config(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_reset_notअगरy(काष्ठा hnae3_handle *handle,
			     क्रमागत hnae3_reset_notअगरy_type type)
अणु
	पूर्णांक ret = 0;

	चयन (type) अणु
	हाल HNAE3_UP_CLIENT:
		ret = hns3_reset_notअगरy_up_enet(handle);
		अवरोध;
	हाल HNAE3_DOWN_CLIENT:
		ret = hns3_reset_notअगरy_करोwn_enet(handle);
		अवरोध;
	हाल HNAE3_INIT_CLIENT:
		ret = hns3_reset_notअगरy_init_enet(handle);
		अवरोध;
	हाल HNAE3_UNINIT_CLIENT:
		ret = hns3_reset_notअगरy_uninit_enet(handle);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns3_change_channels(काष्ठा hnae3_handle *handle, u32 new_tqp_num,
				bool rxfh_configured)
अणु
	पूर्णांक ret;

	ret = handle->ae_algo->ops->set_channels(handle, new_tqp_num,
						 rxfh_configured);
	अगर (ret) अणु
		dev_err(&handle->pdev->dev,
			"Change tqp num(%u) fail.\n", new_tqp_num);
		वापस ret;
	पूर्ण

	ret = hns3_reset_notअगरy(handle, HNAE3_INIT_CLIENT);
	अगर (ret)
		वापस ret;

	ret =  hns3_reset_notअगरy(handle, HNAE3_UP_CLIENT);
	अगर (ret)
		hns3_reset_notअगरy(handle, HNAE3_UNINIT_CLIENT);

	वापस ret;
पूर्ण

पूर्णांक hns3_set_channels(काष्ठा net_device *netdev,
		      काष्ठा ethtool_channels *ch)
अणु
	काष्ठा hnae3_handle *h = hns3_get_handle(netdev);
	काष्ठा hnae3_knic_निजी_info *kinfo = &h->kinfo;
	bool rxfh_configured = netअगर_is_rxfh_configured(netdev);
	u32 new_tqp_num = ch->combined_count;
	u16 org_tqp_num;
	पूर्णांक ret;

	अगर (hns3_nic_resetting(netdev))
		वापस -EBUSY;

	अगर (ch->rx_count || ch->tx_count)
		वापस -EINVAL;

	अगर (kinfo->tc_info.mqprio_active) अणु
		dev_err(&netdev->dev,
			"it's not allowed to set channels via ethtool when MQPRIO mode is on\n");
		वापस -EINVAL;
	पूर्ण

	अगर (new_tqp_num > hns3_get_max_available_channels(h) ||
	    new_tqp_num < 1) अणु
		dev_err(&netdev->dev,
			"Change tqps fail, the tqp range is from 1 to %u",
			hns3_get_max_available_channels(h));
		वापस -EINVAL;
	पूर्ण

	अगर (kinfo->rss_size == new_tqp_num)
		वापस 0;

	netअगर_dbg(h, drv, netdev,
		  "set channels: tqp_num=%u, rxfh=%d\n",
		  new_tqp_num, rxfh_configured);

	ret = hns3_reset_notअगरy(h, HNAE3_DOWN_CLIENT);
	अगर (ret)
		वापस ret;

	ret = hns3_reset_notअगरy(h, HNAE3_UNINIT_CLIENT);
	अगर (ret)
		वापस ret;

	org_tqp_num = h->kinfo.num_tqps;
	ret = hns3_change_channels(h, new_tqp_num, rxfh_configured);
	अगर (ret) अणु
		पूर्णांक ret1;

		netdev_warn(netdev,
			    "Change channels fail, revert to old value\n");
		ret1 = hns3_change_channels(h, org_tqp_num, rxfh_configured);
		अगर (ret1) अणु
			netdev_err(netdev,
				   "revert to old channel fail\n");
			वापस ret1;
		पूर्ण

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hns3_hw_error_info hns3_hw_err[] = अणु
	अणु .type = HNAE3_PPU_POISON_ERROR,
	  .msg = "PPU poison" पूर्ण,
	अणु .type = HNAE3_CMDQ_ECC_ERROR,
	  .msg = "IMP CMDQ error" पूर्ण,
	अणु .type = HNAE3_IMP_RD_POISON_ERROR,
	  .msg = "IMP RD poison" पूर्ण,
	अणु .type = HNAE3_ROCEE_AXI_RESP_ERROR,
	  .msg = "ROCEE AXI RESP error" पूर्ण,
पूर्ण;

अटल व्योम hns3_process_hw_error(काष्ठा hnae3_handle *handle,
				  क्रमागत hnae3_hw_error_type type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hns3_hw_err); i++) अणु
		अगर (hns3_hw_err[i].type == type) अणु
			dev_err(&handle->pdev->dev, "Detected %s!\n",
				hns3_hw_err[i].msg);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hnae3_client_ops client_ops = अणु
	.init_instance = hns3_client_init,
	.uninit_instance = hns3_client_uninit,
	.link_status_change = hns3_link_status_change,
	.reset_notअगरy = hns3_reset_notअगरy,
	.process_hw_error = hns3_process_hw_error,
पूर्ण;

/* hns3_init_module - Driver registration routine
 * hns3_init_module is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 */
अटल पूर्णांक __init hns3_init_module(व्योम)
अणु
	पूर्णांक ret;

	pr_info("%s: %s - version\n", hns3_driver_name, hns3_driver_string);
	pr_info("%s: %s\n", hns3_driver_name, hns3_copyright);

	client.type = HNAE3_CLIENT_KNIC;
	snम_लिखो(client.name, HNAE3_CLIENT_NAME_LENGTH, "%s",
		 hns3_driver_name);

	client.ops = &client_ops;

	INIT_LIST_HEAD(&client.node);

	hns3_dbg_रेजिस्टर_debugfs(hns3_driver_name);

	ret = hnae3_रेजिस्टर_client(&client);
	अगर (ret)
		जाओ err_reg_client;

	ret = pci_रेजिस्टर_driver(&hns3_driver);
	अगर (ret)
		जाओ err_reg_driver;

	वापस ret;

err_reg_driver:
	hnae3_unरेजिस्टर_client(&client);
err_reg_client:
	hns3_dbg_unरेजिस्टर_debugfs();
	वापस ret;
पूर्ण
module_init(hns3_init_module);

/* hns3_निकास_module - Driver निकास cleanup routine
 * hns3_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 */
अटल व्योम __निकास hns3_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hns3_driver);
	hnae3_unरेजिस्टर_client(&client);
	hns3_dbg_unरेजिस्टर_debugfs();
पूर्ण
module_निकास(hns3_निकास_module);

MODULE_DESCRIPTION("HNS3: Hisilicon Ethernet Driver");
MODULE_AUTHOR("Huawei Tech. Co., Ltd.");
MODULE_LICENSE("GPL");
MODULE_ALIAS("pci:hns-nic");
