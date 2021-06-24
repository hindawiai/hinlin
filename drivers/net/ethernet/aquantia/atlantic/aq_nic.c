<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_nic.c: Definition of common code क्रम NIC. */

#समावेश "aq_nic.h"
#समावेश "aq_ring.h"
#समावेश "aq_vec.h"
#समावेश "aq_hw.h"
#समावेश "aq_pci_func.h"
#समावेश "aq_macsec.h"
#समावेश "aq_main.h"
#समावेश "aq_phy.h"
#समावेश "aq_ptp.h"
#समावेश "aq_filters.h"

#समावेश <linux/moduleparam.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/समयr.h>
#समावेश <linux/cpu.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <net/ip.h>
#समावेश <net/pkt_cls.h>

अटल अचिन्हित पूर्णांक aq_itr = AQ_CFG_INTERRUPT_MODERATION_AUTO;
module_param_named(aq_itr, aq_itr, uपूर्णांक, 0644);
MODULE_PARM_DESC(aq_itr, "Interrupt throttling mode");

अटल अचिन्हित पूर्णांक aq_itr_tx;
module_param_named(aq_itr_tx, aq_itr_tx, uपूर्णांक, 0644);
MODULE_PARM_DESC(aq_itr_tx, "TX interrupt throttle rate");

अटल अचिन्हित पूर्णांक aq_itr_rx;
module_param_named(aq_itr_rx, aq_itr_rx, uपूर्णांक, 0644);
MODULE_PARM_DESC(aq_itr_rx, "RX interrupt throttle rate");

अटल व्योम aq_nic_update_ndev_stats(काष्ठा aq_nic_s *self);

अटल व्योम aq_nic_rss_init(काष्ठा aq_nic_s *self, अचिन्हित पूर्णांक num_rss_queues)
अणु
	अटल u8 rss_key[AQ_CFG_RSS_HASHKEY_SIZE] = अणु
		0x1e, 0xad, 0x71, 0x87, 0x65, 0xfc, 0x26, 0x7d,
		0x0d, 0x45, 0x67, 0x74, 0xcd, 0x06, 0x1a, 0x18,
		0xb6, 0xc1, 0xf0, 0xc7, 0xbb, 0x18, 0xbe, 0xf8,
		0x19, 0x13, 0x4b, 0xa9, 0xd0, 0x3e, 0xfe, 0x70,
		0x25, 0x03, 0xab, 0x50, 0x6a, 0x8b, 0x82, 0x0c
	पूर्ण;
	काष्ठा aq_nic_cfg_s *cfg = &self->aq_nic_cfg;
	काष्ठा aq_rss_parameters *rss_params;
	पूर्णांक i = 0;

	rss_params = &cfg->aq_rss;

	rss_params->hash_secret_key_size = माप(rss_key);
	स_नकल(rss_params->hash_secret_key, rss_key, माप(rss_key));
	rss_params->indirection_table_size = AQ_CFG_RSS_INसूचीECTION_TABLE_MAX;

	क्रम (i = rss_params->indirection_table_size; i--;)
		rss_params->indirection_table[i] = i & (num_rss_queues - 1);
पूर्ण

/* Recalculate the number of vectors */
अटल व्योम aq_nic_cfg_update_num_vecs(काष्ठा aq_nic_s *self)
अणु
	काष्ठा aq_nic_cfg_s *cfg = &self->aq_nic_cfg;

	cfg->vecs = min(cfg->aq_hw_caps->vecs, AQ_CFG_VECS_DEF);
	cfg->vecs = min(cfg->vecs, num_online_cpus());
	अगर (self->irqvecs > AQ_HW_SERVICE_IRQS)
		cfg->vecs = min(cfg->vecs, self->irqvecs - AQ_HW_SERVICE_IRQS);
	/* cfg->vecs should be घातer of 2 क्रम RSS */
	cfg->vecs = roundकरोwn_घात_of_two(cfg->vecs);

	अगर (ATL_HW_IS_CHIP_FEATURE(self->aq_hw, ANTIGUA)) अणु
		अगर (cfg->tcs > 2)
			cfg->vecs = min(cfg->vecs, 4U);
	पूर्ण

	अगर (cfg->vecs <= 4)
		cfg->tc_mode = AQ_TC_MODE_8TCS;
	अन्यथा
		cfg->tc_mode = AQ_TC_MODE_4TCS;

	/*rss rings */
	cfg->num_rss_queues = min(cfg->vecs, AQ_CFG_NUM_RSS_QUEUES_DEF);
	aq_nic_rss_init(self, cfg->num_rss_queues);
पूर्ण

/* Checks hw_caps and 'corrects' aq_nic_cfg in runसमय */
व्योम aq_nic_cfg_start(काष्ठा aq_nic_s *self)
अणु
	काष्ठा aq_nic_cfg_s *cfg = &self->aq_nic_cfg;
	पूर्णांक i;

	cfg->tcs = AQ_CFG_TCS_DEF;

	cfg->is_polling = AQ_CFG_IS_POLLING_DEF;

	cfg->itr = aq_itr;
	cfg->tx_itr = aq_itr_tx;
	cfg->rx_itr = aq_itr_rx;

	cfg->rxpageorder = AQ_CFG_RX_PAGEORDER;
	cfg->is_rss = AQ_CFG_IS_RSS_DEF;
	cfg->aq_rss.base_cpu_number = AQ_CFG_RSS_BASE_CPU_NUM_DEF;
	cfg->fc.req = AQ_CFG_FC_MODE;
	cfg->wol = AQ_CFG_WOL_MODES;

	cfg->mtu = AQ_CFG_MTU_DEF;
	cfg->link_speed_msk = AQ_CFG_SPEED_MSK;
	cfg->is_स्वतःneg = AQ_CFG_IS_AUTONEG_DEF;

	cfg->is_lro = AQ_CFG_IS_LRO_DEF;
	cfg->is_ptp = true;

	/*descriptors */
	cfg->rxds = min(cfg->aq_hw_caps->rxds_max, AQ_CFG_RXDS_DEF);
	cfg->txds = min(cfg->aq_hw_caps->txds_max, AQ_CFG_TXDS_DEF);

	aq_nic_cfg_update_num_vecs(self);

	cfg->irq_type = aq_pci_func_get_irq_type(self);

	अगर ((cfg->irq_type == AQ_HW_IRQ_LEGACY) ||
	    (cfg->aq_hw_caps->vecs == 1U) ||
	    (cfg->vecs == 1U)) अणु
		cfg->is_rss = 0U;
		cfg->vecs = 1U;
	पूर्ण

	/* Check अगर we have enough vectors allocated क्रम
	 * link status IRQ. If no - we'll know link state from
	 * slower service task.
	 */
	अगर (AQ_HW_SERVICE_IRQS > 0 && cfg->vecs + 1 <= self->irqvecs)
		cfg->link_irq_vec = cfg->vecs;
	अन्यथा
		cfg->link_irq_vec = 0;

	cfg->link_speed_msk &= cfg->aq_hw_caps->link_speed_msk;
	cfg->features = cfg->aq_hw_caps->hw_features;
	cfg->is_vlan_rx_strip = !!(cfg->features & NETIF_F_HW_VLAN_CTAG_RX);
	cfg->is_vlan_tx_insert = !!(cfg->features & NETIF_F_HW_VLAN_CTAG_TX);
	cfg->is_vlan_क्रमce_promisc = true;

	क्रम (i = 0; i < माप(cfg->prio_tc_map); i++)
		cfg->prio_tc_map[i] = cfg->tcs * i / 8;
पूर्ण

अटल पूर्णांक aq_nic_update_link_status(काष्ठा aq_nic_s *self)
अणु
	पूर्णांक err = self->aq_fw_ops->update_link_status(self->aq_hw);
	u32 fc = 0;

	अगर (err)
		वापस err;

	अगर (self->aq_fw_ops->get_flow_control)
		self->aq_fw_ops->get_flow_control(self->aq_hw, &fc);
	self->aq_nic_cfg.fc.cur = fc;

	अगर (self->link_status.mbps != self->aq_hw->aq_link_status.mbps) अणु
		netdev_info(self->ndev, "%s: link change old %d new %d\n",
			    AQ_CFG_DRV_NAME, self->link_status.mbps,
			    self->aq_hw->aq_link_status.mbps);
		aq_nic_update_पूर्णांकerrupt_moderation_settings(self);

		अगर (self->aq_ptp) अणु
			aq_ptp_घड़ी_init(self);
			aq_ptp_पंचांग_offset_set(self,
					     self->aq_hw->aq_link_status.mbps);
			aq_ptp_link_change(self);
		पूर्ण

		/* Driver has to update flow control settings on RX block
		 * on any link event.
		 * We should query FW whether it negotiated FC.
		 */
		अगर (self->aq_hw_ops->hw_set_fc)
			self->aq_hw_ops->hw_set_fc(self->aq_hw, fc, 0);
	पूर्ण

	self->link_status = self->aq_hw->aq_link_status;
	अगर (!netअगर_carrier_ok(self->ndev) && self->link_status.mbps) अणु
		aq_utils_obj_set(&self->flags,
				 AQ_NIC_FLAG_STARTED);
		aq_utils_obj_clear(&self->flags,
				   AQ_NIC_LINK_DOWN);
		netअगर_carrier_on(self->ndev);
#अगर IS_ENABLED(CONFIG_MACSEC)
		aq_macsec_enable(self);
#पूर्ण_अगर
		अगर (self->aq_hw_ops->hw_tc_rate_limit_set)
			self->aq_hw_ops->hw_tc_rate_limit_set(self->aq_hw);

		netअगर_tx_wake_all_queues(self->ndev);
	पूर्ण
	अगर (netअगर_carrier_ok(self->ndev) && !self->link_status.mbps) अणु
		netअगर_carrier_off(self->ndev);
		netअगर_tx_disable(self->ndev);
		aq_utils_obj_set(&self->flags, AQ_NIC_LINK_DOWN);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t aq_linkstate_thपढ़ोed_isr(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा aq_nic_s *self = निजी;

	अगर (!self)
		वापस IRQ_NONE;

	aq_nic_update_link_status(self);

	self->aq_hw_ops->hw_irq_enable(self->aq_hw,
				       BIT(self->aq_nic_cfg.link_irq_vec));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम aq_nic_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा aq_nic_s *self = container_of(work, काष्ठा aq_nic_s,
					     service_task);
	पूर्णांक err;

	aq_ptp_service_task(self);

	अगर (aq_utils_obj_test(&self->flags, AQ_NIC_FLAGS_IS_NOT_READY))
		वापस;

	err = aq_nic_update_link_status(self);
	अगर (err)
		वापस;

#अगर IS_ENABLED(CONFIG_MACSEC)
	aq_macsec_work(self);
#पूर्ण_अगर

	mutex_lock(&self->fwreq_mutex);
	अगर (self->aq_fw_ops->update_stats)
		self->aq_fw_ops->update_stats(self->aq_hw);
	mutex_unlock(&self->fwreq_mutex);

	aq_nic_update_ndev_stats(self);
पूर्ण

अटल व्योम aq_nic_service_समयr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा aq_nic_s *self = from_समयr(self, t, service_समयr);

	mod_समयr(&self->service_समयr,
		  jअगरfies + AQ_CFG_SERVICE_TIMER_INTERVAL);

	aq_ndev_schedule_work(&self->service_task);
पूर्ण

अटल व्योम aq_nic_polling_समयr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा aq_nic_s *self = from_समयr(self, t, polling_समयr);
	काष्ठा aq_vec_s *aq_vec = शून्य;
	अचिन्हित पूर्णांक i = 0U;

	क्रम (i = 0U, aq_vec = self->aq_vec[0];
		self->aq_vecs > i; ++i, aq_vec = self->aq_vec[i])
		aq_vec_isr(i, (व्योम *)aq_vec);

	mod_समयr(&self->polling_समयr, jअगरfies +
		  AQ_CFG_POLLING_TIMER_INTERVAL);
पूर्ण

अटल पूर्णांक aq_nic_hw_prepare(काष्ठा aq_nic_s *self)
अणु
	पूर्णांक err = 0;

	err = self->aq_hw_ops->hw_soft_reset(self->aq_hw);
	अगर (err)
		जाओ निकास;

	err = self->aq_hw_ops->hw_prepare(self->aq_hw, &self->aq_fw_ops);

निकास:
	वापस err;
पूर्ण

अटल bool aq_nic_is_valid_ether_addr(स्थिर u8 *addr)
अणु
	/* Some engineering samples of Aquantia NICs are provisioned with a
	 * partially populated MAC, which is still invalid.
	 */
	वापस !(addr[0] == 0 && addr[1] == 0 && addr[2] == 0);
पूर्ण

पूर्णांक aq_nic_ndev_रेजिस्टर(काष्ठा aq_nic_s *self)
अणु
	पूर्णांक err = 0;

	अगर (!self->ndev) अणु
		err = -EINVAL;
		जाओ err_निकास;
	पूर्ण

	err = aq_nic_hw_prepare(self);
	अगर (err)
		जाओ err_निकास;

#अगर IS_ENABLED(CONFIG_MACSEC)
	aq_macsec_init(self);
#पूर्ण_अगर

	mutex_lock(&self->fwreq_mutex);
	err = self->aq_fw_ops->get_mac_permanent(self->aq_hw,
			    self->ndev->dev_addr);
	mutex_unlock(&self->fwreq_mutex);
	अगर (err)
		जाओ err_निकास;

	अगर (!is_valid_ether_addr(self->ndev->dev_addr) ||
	    !aq_nic_is_valid_ether_addr(self->ndev->dev_addr)) अणु
		netdev_warn(self->ndev, "MAC is invalid, will use random.");
		eth_hw_addr_अक्रमom(self->ndev);
	पूर्ण

#अगर defined(AQ_CFG_MAC_ADDR_PERMANENT)
	अणु
		अटल u8 mac_addr_permanent[] = AQ_CFG_MAC_ADDR_PERMANENT;

		ether_addr_copy(self->ndev->dev_addr, mac_addr_permanent);
	पूर्ण
#पूर्ण_अगर

	क्रम (self->aq_vecs = 0; self->aq_vecs < aq_nic_get_cfg(self)->vecs;
	     self->aq_vecs++) अणु
		self->aq_vec[self->aq_vecs] =
		    aq_vec_alloc(self, self->aq_vecs, aq_nic_get_cfg(self));
		अगर (!self->aq_vec[self->aq_vecs]) अणु
			err = -ENOMEM;
			जाओ err_निकास;
		पूर्ण
	पूर्ण

	netअगर_carrier_off(self->ndev);

	netअगर_tx_disable(self->ndev);

	err = रेजिस्टर_netdev(self->ndev);
	अगर (err)
		जाओ err_निकास;

err_निकास:
#अगर IS_ENABLED(CONFIG_MACSEC)
	अगर (err)
		aq_macsec_मुक्त(self);
#पूर्ण_अगर
	वापस err;
पूर्ण

व्योम aq_nic_ndev_init(काष्ठा aq_nic_s *self)
अणु
	स्थिर काष्ठा aq_hw_caps_s *aq_hw_caps = self->aq_nic_cfg.aq_hw_caps;
	काष्ठा aq_nic_cfg_s *aq_nic_cfg = &self->aq_nic_cfg;

	self->ndev->hw_features |= aq_hw_caps->hw_features;
	self->ndev->features = aq_hw_caps->hw_features;
	self->ndev->vlan_features |= NETIF_F_HW_CSUM | NETIF_F_RXCSUM |
				     NETIF_F_RXHASH | NETIF_F_SG |
				     NETIF_F_LRO | NETIF_F_TSO | NETIF_F_TSO6;
	self->ndev->gso_partial_features = NETIF_F_GSO_UDP_L4;
	self->ndev->priv_flags = aq_hw_caps->hw_priv_flags;
	self->ndev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	self->msg_enable = NETIF_MSG_DRV | NETIF_MSG_LINK;
	self->ndev->mtu = aq_nic_cfg->mtu - ETH_HLEN;
	self->ndev->max_mtu = aq_hw_caps->mtu - ETH_FCS_LEN - ETH_HLEN;

पूर्ण

व्योम aq_nic_set_tx_ring(काष्ठा aq_nic_s *self, अचिन्हित पूर्णांक idx,
			काष्ठा aq_ring_s *ring)
अणु
	self->aq_ring_tx[idx] = ring;
पूर्ण

काष्ठा net_device *aq_nic_get_ndev(काष्ठा aq_nic_s *self)
अणु
	वापस self->ndev;
पूर्ण

पूर्णांक aq_nic_init(काष्ठा aq_nic_s *self)
अणु
	काष्ठा aq_vec_s *aq_vec = शून्य;
	अचिन्हित पूर्णांक i = 0U;
	पूर्णांक err = 0;

	self->घातer_state = AQ_HW_POWER_STATE_D0;
	mutex_lock(&self->fwreq_mutex);
	err = self->aq_hw_ops->hw_reset(self->aq_hw);
	mutex_unlock(&self->fwreq_mutex);
	अगर (err < 0)
		जाओ err_निकास;
	/* Restore शेष settings */
	aq_nic_set_करोwnshअगरt(self, self->aq_nic_cfg.करोwnshअगरt_counter);
	aq_nic_set_media_detect(self, self->aq_nic_cfg.is_media_detect ?
				AQ_HW_MEDIA_DETECT_CNT : 0);

	err = self->aq_hw_ops->hw_init(self->aq_hw,
				       aq_nic_get_ndev(self)->dev_addr);
	अगर (err < 0)
		जाओ err_निकास;

	अगर (ATL_HW_IS_CHIP_FEATURE(self->aq_hw, ATLANTIC) &&
	    self->aq_nic_cfg.aq_hw_caps->media_type == AQ_HW_MEDIA_TYPE_TP) अणु
		self->aq_hw->phy_id = HW_ATL_PHY_ID_MAX;
		err = aq_phy_init(self->aq_hw);

		/* Disable the PTP on NICs where it's known to cause datapath
		 * problems.
		 * Ideally this should have been करोne by PHY provisioning, but
		 * many units have been shipped with enabled PTP block alपढ़ोy.
		 */
		अगर (self->aq_nic_cfg.aq_hw_caps->quirks & AQ_NIC_QUIRK_BAD_PTP)
			अगर (self->aq_hw->phy_id != HW_ATL_PHY_ID_MAX)
				aq_phy_disable_ptp(self->aq_hw);
	पूर्ण

	क्रम (i = 0U; i < self->aq_vecs; i++) अणु
		aq_vec = self->aq_vec[i];
		err = aq_vec_ring_alloc(aq_vec, self, i,
					aq_nic_get_cfg(self));
		अगर (err)
			जाओ err_निकास;

		aq_vec_init(aq_vec, self->aq_hw_ops, self->aq_hw);
	पूर्ण

	अगर (aq_nic_get_cfg(self)->is_ptp) अणु
		err = aq_ptp_init(self, self->irqvecs - 1);
		अगर (err < 0)
			जाओ err_निकास;

		err = aq_ptp_ring_alloc(self);
		अगर (err < 0)
			जाओ err_निकास;

		err = aq_ptp_ring_init(self);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण

	netअगर_carrier_off(self->ndev);

err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_nic_start(काष्ठा aq_nic_s *self)
अणु
	काष्ठा aq_vec_s *aq_vec = शून्य;
	काष्ठा aq_nic_cfg_s *cfg;
	अचिन्हित पूर्णांक i = 0U;
	पूर्णांक err = 0;

	cfg = aq_nic_get_cfg(self);

	err = self->aq_hw_ops->hw_multicast_list_set(self->aq_hw,
						     self->mc_list.ar,
						     self->mc_list.count);
	अगर (err < 0)
		जाओ err_निकास;

	err = self->aq_hw_ops->hw_packet_filter_set(self->aq_hw,
						    self->packet_filter);
	अगर (err < 0)
		जाओ err_निकास;

	क्रम (i = 0U, aq_vec = self->aq_vec[0];
		self->aq_vecs > i; ++i, aq_vec = self->aq_vec[i]) अणु
		err = aq_vec_start(aq_vec);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण

	err = aq_ptp_ring_start(self);
	अगर (err < 0)
		जाओ err_निकास;

	aq_nic_set_loopback(self);

	err = self->aq_hw_ops->hw_start(self->aq_hw);
	अगर (err < 0)
		जाओ err_निकास;

	err = aq_nic_update_पूर्णांकerrupt_moderation_settings(self);
	अगर (err)
		जाओ err_निकास;

	INIT_WORK(&self->service_task, aq_nic_service_task);

	समयr_setup(&self->service_समयr, aq_nic_service_समयr_cb, 0);
	aq_nic_service_समयr_cb(&self->service_समयr);

	अगर (cfg->is_polling) अणु
		समयr_setup(&self->polling_समयr, aq_nic_polling_समयr_cb, 0);
		mod_समयr(&self->polling_समयr, jअगरfies +
			  AQ_CFG_POLLING_TIMER_INTERVAL);
	पूर्ण अन्यथा अणु
		क्रम (i = 0U, aq_vec = self->aq_vec[0];
			self->aq_vecs > i; ++i, aq_vec = self->aq_vec[i]) अणु
			err = aq_pci_func_alloc_irq(self, i, self->ndev->name,
						    aq_vec_isr, aq_vec,
						    aq_vec_get_affinity_mask(aq_vec));
			अगर (err < 0)
				जाओ err_निकास;
		पूर्ण

		err = aq_ptp_irq_alloc(self);
		अगर (err < 0)
			जाओ err_निकास;

		अगर (cfg->link_irq_vec) अणु
			पूर्णांक irqvec = pci_irq_vector(self->pdev,
						    cfg->link_irq_vec);
			err = request_thपढ़ोed_irq(irqvec, शून्य,
						   aq_linkstate_thपढ़ोed_isr,
						   IRQF_SHARED | IRQF_ONESHOT,
						   self->ndev->name, self);
			अगर (err < 0)
				जाओ err_निकास;
			self->msix_entry_mask |= (1 << cfg->link_irq_vec);
		पूर्ण

		err = self->aq_hw_ops->hw_irq_enable(self->aq_hw,
						     AQ_CFG_IRQ_MASK);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण

	err = netअगर_set_real_num_tx_queues(self->ndev,
					   self->aq_vecs * cfg->tcs);
	अगर (err < 0)
		जाओ err_निकास;

	err = netअगर_set_real_num_rx_queues(self->ndev,
					   self->aq_vecs * cfg->tcs);
	अगर (err < 0)
		जाओ err_निकास;

	क्रम (i = 0; i < cfg->tcs; i++) अणु
		u16 offset = self->aq_vecs * i;

		netdev_set_tc_queue(self->ndev, i, self->aq_vecs, offset);
	पूर्ण
	netअगर_tx_start_all_queues(self->ndev);

err_निकास:
	वापस err;
पूर्ण

अचिन्हित पूर्णांक aq_nic_map_skb(काष्ठा aq_nic_s *self, काष्ठा sk_buff *skb,
			    काष्ठा aq_ring_s *ring)
अणु
	अचिन्हित पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	काष्ठा aq_nic_cfg_s *cfg = aq_nic_get_cfg(self);
	काष्ठा device *dev = aq_nic_get_dev(self);
	काष्ठा aq_ring_buff_s *first = शून्य;
	u8 ipver = ip_hdr(skb)->version;
	काष्ठा aq_ring_buff_s *dx_buff;
	bool need_context_tag = false;
	अचिन्हित पूर्णांक frag_count = 0U;
	अचिन्हित पूर्णांक ret = 0U;
	अचिन्हित पूर्णांक dx;
	u8 l4proto = 0;

	अगर (ipver == 4)
		l4proto = ip_hdr(skb)->protocol;
	अन्यथा अगर (ipver == 6)
		l4proto = ipv6_hdr(skb)->nexthdr;

	dx = ring->sw_tail;
	dx_buff = &ring->buff_ring[dx];
	dx_buff->flags = 0U;

	अगर (unlikely(skb_is_gso(skb))) अणु
		dx_buff->mss = skb_shinfo(skb)->gso_size;
		अगर (l4proto == IPPROTO_TCP) अणु
			dx_buff->is_gso_tcp = 1U;
			dx_buff->len_l4 = tcp_hdrlen(skb);
		पूर्ण अन्यथा अगर (l4proto == IPPROTO_UDP) अणु
			dx_buff->is_gso_udp = 1U;
			dx_buff->len_l4 = माप(काष्ठा udphdr);
			/* UDP GSO Hardware करोes not replace packet length. */
			udp_hdr(skb)->len = htons(dx_buff->mss +
						  dx_buff->len_l4);
		पूर्ण अन्यथा अणु
			WARN_ONCE(true, "Bad GSO mode");
			जाओ निकास;
		पूर्ण
		dx_buff->len_pkt = skb->len;
		dx_buff->len_l2 = ETH_HLEN;
		dx_buff->len_l3 = skb_network_header_len(skb);
		dx_buff->eop_index = 0xffffU;
		dx_buff->is_ipv6 = (ipver == 6);
		need_context_tag = true;
	पूर्ण

	अगर (cfg->is_vlan_tx_insert && skb_vlan_tag_present(skb)) अणु
		dx_buff->vlan_tx_tag = skb_vlan_tag_get(skb);
		dx_buff->len_pkt = skb->len;
		dx_buff->is_vlan = 1U;
		need_context_tag = true;
	पूर्ण

	अगर (need_context_tag) अणु
		dx = aq_ring_next_dx(ring, dx);
		dx_buff = &ring->buff_ring[dx];
		dx_buff->flags = 0U;
		++ret;
	पूर्ण

	dx_buff->len = skb_headlen(skb);
	dx_buff->pa = dma_map_single(dev,
				     skb->data,
				     dx_buff->len,
				     DMA_TO_DEVICE);

	अगर (unlikely(dma_mapping_error(dev, dx_buff->pa))) अणु
		ret = 0;
		जाओ निकास;
	पूर्ण

	first = dx_buff;
	dx_buff->len_pkt = skb->len;
	dx_buff->is_sop = 1U;
	dx_buff->is_mapped = 1U;
	++ret;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		dx_buff->is_ip_cso = (htons(ETH_P_IP) == skb->protocol);
		dx_buff->is_tcp_cso = (l4proto == IPPROTO_TCP);
		dx_buff->is_udp_cso = (l4proto == IPPROTO_UDP);
	पूर्ण

	क्रम (; nr_frags--; ++frag_count) अणु
		अचिन्हित पूर्णांक frag_len = 0U;
		अचिन्हित पूर्णांक buff_offset = 0U;
		अचिन्हित पूर्णांक buff_size = 0U;
		dma_addr_t frag_pa;
		skb_frag_t *frag = &skb_shinfo(skb)->frags[frag_count];

		frag_len = skb_frag_size(frag);

		जबतक (frag_len) अणु
			अगर (frag_len > AQ_CFG_TX_FRAME_MAX)
				buff_size = AQ_CFG_TX_FRAME_MAX;
			अन्यथा
				buff_size = frag_len;

			frag_pa = skb_frag_dma_map(dev,
						   frag,
						   buff_offset,
						   buff_size,
						   DMA_TO_DEVICE);

			अगर (unlikely(dma_mapping_error(dev,
						       frag_pa)))
				जाओ mapping_error;

			dx = aq_ring_next_dx(ring, dx);
			dx_buff = &ring->buff_ring[dx];

			dx_buff->flags = 0U;
			dx_buff->len = buff_size;
			dx_buff->pa = frag_pa;
			dx_buff->is_mapped = 1U;
			dx_buff->eop_index = 0xffffU;

			frag_len -= buff_size;
			buff_offset += buff_size;

			++ret;
		पूर्ण
	पूर्ण

	first->eop_index = dx;
	dx_buff->is_eop = 1U;
	dx_buff->skb = skb;
	जाओ निकास;

mapping_error:
	क्रम (dx = ring->sw_tail;
	     ret > 0;
	     --ret, dx = aq_ring_next_dx(ring, dx)) अणु
		dx_buff = &ring->buff_ring[dx];

		अगर (!(dx_buff->is_gso_tcp || dx_buff->is_gso_udp) &&
		    !dx_buff->is_vlan && dx_buff->pa) अणु
			अगर (unlikely(dx_buff->is_sop)) अणु
				dma_unmap_single(dev,
						 dx_buff->pa,
						 dx_buff->len,
						 DMA_TO_DEVICE);
			पूर्ण अन्यथा अणु
				dma_unmap_page(dev,
					       dx_buff->pa,
					       dx_buff->len,
					       DMA_TO_DEVICE);
			पूर्ण
		पूर्ण
	पूर्ण

निकास:
	वापस ret;
पूर्ण

पूर्णांक aq_nic_xmit(काष्ठा aq_nic_s *self, काष्ठा sk_buff *skb)
अणु
	काष्ठा aq_nic_cfg_s *cfg = aq_nic_get_cfg(self);
	अचिन्हित पूर्णांक vec = skb->queue_mapping % cfg->vecs;
	अचिन्हित पूर्णांक tc = skb->queue_mapping / cfg->vecs;
	काष्ठा aq_ring_s *ring = शून्य;
	अचिन्हित पूर्णांक frags = 0U;
	पूर्णांक err = NETDEV_TX_OK;

	frags = skb_shinfo(skb)->nr_frags + 1;

	ring = self->aq_ring_tx[AQ_NIC_CFG_TCVEC2RING(cfg, tc, vec)];

	अगर (frags > AQ_CFG_SKB_FRAGS_MAX) अणु
		dev_kमुक्त_skb_any(skb);
		जाओ err_निकास;
	पूर्ण

	aq_ring_update_queue_state(ring);

	अगर (cfg->priv_flags & BIT(AQ_HW_LOOPBACK_DMA_NET)) अणु
		err = NETDEV_TX_BUSY;
		जाओ err_निकास;
	पूर्ण

	/* Above status update may stop the queue. Check this. */
	अगर (__netअगर_subqueue_stopped(self->ndev,
				     AQ_NIC_RING2QMAP(self, ring->idx))) अणु
		err = NETDEV_TX_BUSY;
		जाओ err_निकास;
	पूर्ण

	frags = aq_nic_map_skb(self, skb, ring);

	अगर (likely(frags)) अणु
		err = self->aq_hw_ops->hw_ring_tx_xmit(self->aq_hw,
						       ring, frags);
	पूर्ण अन्यथा अणु
		err = NETDEV_TX_BUSY;
	पूर्ण

err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_nic_update_पूर्णांकerrupt_moderation_settings(काष्ठा aq_nic_s *self)
अणु
	वापस self->aq_hw_ops->hw_पूर्णांकerrupt_moderation_set(self->aq_hw);
पूर्ण

पूर्णांक aq_nic_set_packet_filter(काष्ठा aq_nic_s *self, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err = 0;

	err = self->aq_hw_ops->hw_packet_filter_set(self->aq_hw, flags);
	अगर (err < 0)
		जाओ err_निकास;

	self->packet_filter = flags;

err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_nic_set_multicast_list(काष्ठा aq_nic_s *self, काष्ठा net_device *ndev)
अणु
	स्थिर काष्ठा aq_hw_ops *hw_ops = self->aq_hw_ops;
	काष्ठा aq_nic_cfg_s *cfg = &self->aq_nic_cfg;
	अचिन्हित पूर्णांक packet_filter = ndev->flags;
	काष्ठा netdev_hw_addr *ha = शून्य;
	अचिन्हित पूर्णांक i = 0U;
	पूर्णांक err = 0;

	self->mc_list.count = 0;
	अगर (netdev_uc_count(ndev) > AQ_HW_MULTICAST_ADDRESS_MAX) अणु
		packet_filter |= IFF_PROMISC;
	पूर्ण अन्यथा अणु
		netdev_क्रम_each_uc_addr(ha, ndev) अणु
			ether_addr_copy(self->mc_list.ar[i++], ha->addr);
		पूर्ण
	पूर्ण

	cfg->is_mc_list_enabled = !!(packet_filter & IFF_MULTICAST);
	अगर (cfg->is_mc_list_enabled) अणु
		अगर (i + netdev_mc_count(ndev) > AQ_HW_MULTICAST_ADDRESS_MAX) अणु
			packet_filter |= IFF_ALLMULTI;
		पूर्ण अन्यथा अणु
			netdev_क्रम_each_mc_addr(ha, ndev) अणु
				ether_addr_copy(self->mc_list.ar[i++],
						ha->addr);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (i > 0 && i <= AQ_HW_MULTICAST_ADDRESS_MAX) अणु
		self->mc_list.count = i;
		err = hw_ops->hw_multicast_list_set(self->aq_hw,
						    self->mc_list.ar,
						    self->mc_list.count);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस aq_nic_set_packet_filter(self, packet_filter);
पूर्ण

पूर्णांक aq_nic_set_mtu(काष्ठा aq_nic_s *self, पूर्णांक new_mtu)
अणु
	self->aq_nic_cfg.mtu = new_mtu;

	वापस 0;
पूर्ण

पूर्णांक aq_nic_set_mac(काष्ठा aq_nic_s *self, काष्ठा net_device *ndev)
अणु
	वापस self->aq_hw_ops->hw_set_mac_address(self->aq_hw, ndev->dev_addr);
पूर्ण

अचिन्हित पूर्णांक aq_nic_get_link_speed(काष्ठा aq_nic_s *self)
अणु
	वापस self->link_status.mbps;
पूर्ण

पूर्णांक aq_nic_get_regs(काष्ठा aq_nic_s *self, काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	u32 *regs_buff = p;
	पूर्णांक err = 0;

	अगर (unlikely(!self->aq_hw_ops->hw_get_regs))
		वापस -EOPNOTSUPP;

	regs->version = 1;

	err = self->aq_hw_ops->hw_get_regs(self->aq_hw,
					   self->aq_nic_cfg.aq_hw_caps,
					   regs_buff);
	अगर (err < 0)
		जाओ err_निकास;

err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_nic_get_regs_count(काष्ठा aq_nic_s *self)
अणु
	अगर (unlikely(!self->aq_hw_ops->hw_get_regs))
		वापस 0;

	वापस self->aq_nic_cfg.aq_hw_caps->mac_regs_count;
पूर्ण

u64 *aq_nic_get_stats(काष्ठा aq_nic_s *self, u64 *data)
अणु
	काष्ठा aq_vec_s *aq_vec = शून्य;
	काष्ठा aq_stats_s *stats;
	अचिन्हित पूर्णांक count = 0U;
	अचिन्हित पूर्णांक i = 0U;
	अचिन्हित पूर्णांक tc;

	अगर (self->aq_fw_ops->update_stats) अणु
		mutex_lock(&self->fwreq_mutex);
		self->aq_fw_ops->update_stats(self->aq_hw);
		mutex_unlock(&self->fwreq_mutex);
	पूर्ण
	stats = self->aq_hw_ops->hw_get_hw_stats(self->aq_hw);

	अगर (!stats)
		जाओ err_निकास;

	data[i] = stats->uprc + stats->mprc + stats->bprc;
	data[++i] = stats->uprc;
	data[++i] = stats->mprc;
	data[++i] = stats->bprc;
	data[++i] = stats->erpt;
	data[++i] = stats->uptc + stats->mptc + stats->bptc;
	data[++i] = stats->uptc;
	data[++i] = stats->mptc;
	data[++i] = stats->bptc;
	data[++i] = stats->ubrc;
	data[++i] = stats->ubtc;
	data[++i] = stats->mbrc;
	data[++i] = stats->mbtc;
	data[++i] = stats->bbrc;
	data[++i] = stats->bbtc;
	data[++i] = stats->ubrc + stats->mbrc + stats->bbrc;
	data[++i] = stats->ubtc + stats->mbtc + stats->bbtc;
	data[++i] = stats->dma_pkt_rc;
	data[++i] = stats->dma_pkt_tc;
	data[++i] = stats->dma_oct_rc;
	data[++i] = stats->dma_oct_tc;
	data[++i] = stats->dpc;

	i++;

	data += i;

	क्रम (tc = 0U; tc < self->aq_nic_cfg.tcs; tc++) अणु
		क्रम (i = 0U, aq_vec = self->aq_vec[0];
		     aq_vec && self->aq_vecs > i;
		     ++i, aq_vec = self->aq_vec[i]) अणु
			data += count;
			count = aq_vec_get_sw_stats(aq_vec, tc, data);
		पूर्ण
	पूर्ण

	data += count;

err_निकास:
	वापस data;
पूर्ण

अटल व्योम aq_nic_update_ndev_stats(काष्ठा aq_nic_s *self)
अणु
	काष्ठा aq_stats_s *stats = self->aq_hw_ops->hw_get_hw_stats(self->aq_hw);
	काष्ठा net_device *ndev = self->ndev;

	ndev->stats.rx_packets = stats->dma_pkt_rc;
	ndev->stats.rx_bytes = stats->dma_oct_rc;
	ndev->stats.rx_errors = stats->erpr;
	ndev->stats.rx_dropped = stats->dpc;
	ndev->stats.tx_packets = stats->dma_pkt_tc;
	ndev->stats.tx_bytes = stats->dma_oct_tc;
	ndev->stats.tx_errors = stats->erpt;
	ndev->stats.multicast = stats->mprc;
पूर्ण

व्योम aq_nic_get_link_ksettings(काष्ठा aq_nic_s *self,
			       काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 lp_link_speed_msk;

	अगर (self->aq_nic_cfg.aq_hw_caps->media_type == AQ_HW_MEDIA_TYPE_FIBRE)
		cmd->base.port = PORT_FIBRE;
	अन्यथा
		cmd->base.port = PORT_TP;

	cmd->base.duplex = DUPLEX_UNKNOWN;
	अगर (self->link_status.mbps)
		cmd->base.duplex = self->link_status.full_duplex ?
				   DUPLEX_FULL : DUPLEX_HALF;
	cmd->base.स्वतःneg = self->aq_nic_cfg.is_स्वतःneg;

	ethtool_link_ksettings_zero_link_mode(cmd, supported);

	अगर (self->aq_nic_cfg.aq_hw_caps->link_speed_msk & AQ_NIC_RATE_10G)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     10000baseT_Full);

	अगर (self->aq_nic_cfg.aq_hw_caps->link_speed_msk & AQ_NIC_RATE_5G)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     5000baseT_Full);

	अगर (self->aq_nic_cfg.aq_hw_caps->link_speed_msk & AQ_NIC_RATE_2G5)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     2500baseT_Full);

	अगर (self->aq_nic_cfg.aq_hw_caps->link_speed_msk & AQ_NIC_RATE_1G)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     1000baseT_Full);

	अगर (self->aq_nic_cfg.aq_hw_caps->link_speed_msk & AQ_NIC_RATE_1G_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     1000baseT_Half);

	अगर (self->aq_nic_cfg.aq_hw_caps->link_speed_msk & AQ_NIC_RATE_100M)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     100baseT_Full);

	अगर (self->aq_nic_cfg.aq_hw_caps->link_speed_msk & AQ_NIC_RATE_100M_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     100baseT_Half);

	अगर (self->aq_nic_cfg.aq_hw_caps->link_speed_msk & AQ_NIC_RATE_10M)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     10baseT_Full);

	अगर (self->aq_nic_cfg.aq_hw_caps->link_speed_msk & AQ_NIC_RATE_10M_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     10baseT_Half);

	अगर (self->aq_nic_cfg.aq_hw_caps->flow_control) अणु
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     Pause);
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     Asym_Pause);
	पूर्ण

	ethtool_link_ksettings_add_link_mode(cmd, supported, Autoneg);

	अगर (self->aq_nic_cfg.aq_hw_caps->media_type == AQ_HW_MEDIA_TYPE_FIBRE)
		ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);
	अन्यथा
		ethtool_link_ksettings_add_link_mode(cmd, supported, TP);

	ethtool_link_ksettings_zero_link_mode(cmd, advertising);

	अगर (self->aq_nic_cfg.is_स्वतःneg)
		ethtool_link_ksettings_add_link_mode(cmd, advertising, Autoneg);

	अगर (self->aq_nic_cfg.link_speed_msk & AQ_NIC_RATE_10G)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     10000baseT_Full);

	अगर (self->aq_nic_cfg.link_speed_msk & AQ_NIC_RATE_5G)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     5000baseT_Full);

	अगर (self->aq_nic_cfg.link_speed_msk & AQ_NIC_RATE_2G5)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     2500baseT_Full);

	अगर (self->aq_nic_cfg.link_speed_msk & AQ_NIC_RATE_1G)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     1000baseT_Full);

	अगर (self->aq_nic_cfg.link_speed_msk & AQ_NIC_RATE_1G_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     1000baseT_Half);

	अगर (self->aq_nic_cfg.link_speed_msk & AQ_NIC_RATE_100M)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     100baseT_Full);

	अगर (self->aq_nic_cfg.link_speed_msk & AQ_NIC_RATE_100M_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     100baseT_Half);

	अगर (self->aq_nic_cfg.link_speed_msk & AQ_NIC_RATE_10M)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     10baseT_Full);

	अगर (self->aq_nic_cfg.link_speed_msk & AQ_NIC_RATE_10M_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     10baseT_Half);

	अगर (self->aq_nic_cfg.fc.cur & AQ_NIC_FC_RX)
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     Pause);

	/* Asym is when either RX or TX, but not both */
	अगर (!!(self->aq_nic_cfg.fc.cur & AQ_NIC_FC_TX) ^
	    !!(self->aq_nic_cfg.fc.cur & AQ_NIC_FC_RX))
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     Asym_Pause);

	अगर (self->aq_nic_cfg.aq_hw_caps->media_type == AQ_HW_MEDIA_TYPE_FIBRE)
		ethtool_link_ksettings_add_link_mode(cmd, advertising, FIBRE);
	अन्यथा
		ethtool_link_ksettings_add_link_mode(cmd, advertising, TP);

	ethtool_link_ksettings_zero_link_mode(cmd, lp_advertising);
	lp_link_speed_msk = self->aq_hw->aq_link_status.lp_link_speed_msk;

	अगर (lp_link_speed_msk & AQ_NIC_RATE_10G)
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     10000baseT_Full);

	अगर (lp_link_speed_msk & AQ_NIC_RATE_5G)
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     5000baseT_Full);

	अगर (lp_link_speed_msk & AQ_NIC_RATE_2G5)
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     2500baseT_Full);

	अगर (lp_link_speed_msk & AQ_NIC_RATE_1G)
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     1000baseT_Full);

	अगर (lp_link_speed_msk & AQ_NIC_RATE_1G_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     1000baseT_Half);

	अगर (lp_link_speed_msk & AQ_NIC_RATE_100M)
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     100baseT_Full);

	अगर (lp_link_speed_msk & AQ_NIC_RATE_100M_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     100baseT_Half);

	अगर (lp_link_speed_msk & AQ_NIC_RATE_10M)
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     10baseT_Full);

	अगर (lp_link_speed_msk & AQ_NIC_RATE_10M_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     10baseT_Half);

	अगर (self->aq_hw->aq_link_status.lp_flow_control & AQ_NIC_FC_RX)
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     Pause);
	अगर (!!(self->aq_hw->aq_link_status.lp_flow_control & AQ_NIC_FC_TX) ^
	    !!(self->aq_hw->aq_link_status.lp_flow_control & AQ_NIC_FC_RX))
		ethtool_link_ksettings_add_link_mode(cmd, lp_advertising,
						     Asym_Pause);
पूर्ण

पूर्णांक aq_nic_set_link_ksettings(काष्ठा aq_nic_s *self,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	पूर्णांक fduplex = (cmd->base.duplex == DUPLEX_FULL);
	u32 speed = cmd->base.speed;
	u32 rate = 0U;
	पूर्णांक err = 0;

	अगर (!fduplex && speed > SPEED_1000) अणु
		err = -EINVAL;
		जाओ err_निकास;
	पूर्ण

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		rate = self->aq_nic_cfg.aq_hw_caps->link_speed_msk;
		self->aq_nic_cfg.is_स्वतःneg = true;
	पूर्ण अन्यथा अणु
		चयन (speed) अणु
		हाल SPEED_10:
			rate = fduplex ? AQ_NIC_RATE_10M : AQ_NIC_RATE_10M_HALF;
			अवरोध;

		हाल SPEED_100:
			rate = fduplex ? AQ_NIC_RATE_100M
				       : AQ_NIC_RATE_100M_HALF;
			अवरोध;

		हाल SPEED_1000:
			rate = fduplex ? AQ_NIC_RATE_1G : AQ_NIC_RATE_1G_HALF;
			अवरोध;

		हाल SPEED_2500:
			rate = AQ_NIC_RATE_2G5;
			अवरोध;

		हाल SPEED_5000:
			rate = AQ_NIC_RATE_5G;
			अवरोध;

		हाल SPEED_10000:
			rate = AQ_NIC_RATE_10G;
			अवरोध;

		शेष:
			err = -1;
			जाओ err_निकास;
		पूर्ण
		अगर (!(self->aq_nic_cfg.aq_hw_caps->link_speed_msk & rate)) अणु
			err = -1;
			जाओ err_निकास;
		पूर्ण

		self->aq_nic_cfg.is_स्वतःneg = false;
	पूर्ण

	mutex_lock(&self->fwreq_mutex);
	err = self->aq_fw_ops->set_link_speed(self->aq_hw, rate);
	mutex_unlock(&self->fwreq_mutex);
	अगर (err < 0)
		जाओ err_निकास;

	self->aq_nic_cfg.link_speed_msk = rate;

err_निकास:
	वापस err;
पूर्ण

काष्ठा aq_nic_cfg_s *aq_nic_get_cfg(काष्ठा aq_nic_s *self)
अणु
	वापस &self->aq_nic_cfg;
पूर्ण

u32 aq_nic_get_fw_version(काष्ठा aq_nic_s *self)
अणु
	वापस self->aq_hw_ops->hw_get_fw_version(self->aq_hw);
पूर्ण

पूर्णांक aq_nic_set_loopback(काष्ठा aq_nic_s *self)
अणु
	काष्ठा aq_nic_cfg_s *cfg = &self->aq_nic_cfg;

	अगर (!self->aq_hw_ops->hw_set_loopback ||
	    !self->aq_fw_ops->set_phyloopback)
		वापस -EOPNOTSUPP;

	mutex_lock(&self->fwreq_mutex);
	self->aq_hw_ops->hw_set_loopback(self->aq_hw,
					 AQ_HW_LOOPBACK_DMA_SYS,
					 !!(cfg->priv_flags &
					    BIT(AQ_HW_LOOPBACK_DMA_SYS)));

	self->aq_hw_ops->hw_set_loopback(self->aq_hw,
					 AQ_HW_LOOPBACK_PKT_SYS,
					 !!(cfg->priv_flags &
					    BIT(AQ_HW_LOOPBACK_PKT_SYS)));

	self->aq_hw_ops->hw_set_loopback(self->aq_hw,
					 AQ_HW_LOOPBACK_DMA_NET,
					 !!(cfg->priv_flags &
					    BIT(AQ_HW_LOOPBACK_DMA_NET)));

	self->aq_fw_ops->set_phyloopback(self->aq_hw,
					 AQ_HW_LOOPBACK_PHYINT_SYS,
					 !!(cfg->priv_flags &
					    BIT(AQ_HW_LOOPBACK_PHYINT_SYS)));

	self->aq_fw_ops->set_phyloopback(self->aq_hw,
					 AQ_HW_LOOPBACK_PHYEXT_SYS,
					 !!(cfg->priv_flags &
					    BIT(AQ_HW_LOOPBACK_PHYEXT_SYS)));
	mutex_unlock(&self->fwreq_mutex);

	वापस 0;
पूर्ण

पूर्णांक aq_nic_stop(काष्ठा aq_nic_s *self)
अणु
	काष्ठा aq_vec_s *aq_vec = शून्य;
	अचिन्हित पूर्णांक i = 0U;

	netअगर_tx_disable(self->ndev);
	netअगर_carrier_off(self->ndev);

	del_समयr_sync(&self->service_समयr);
	cancel_work_sync(&self->service_task);

	self->aq_hw_ops->hw_irq_disable(self->aq_hw, AQ_CFG_IRQ_MASK);

	अगर (self->aq_nic_cfg.is_polling)
		del_समयr_sync(&self->polling_समयr);
	अन्यथा
		aq_pci_func_मुक्त_irqs(self);

	aq_ptp_irq_मुक्त(self);

	क्रम (i = 0U, aq_vec = self->aq_vec[0];
		self->aq_vecs > i; ++i, aq_vec = self->aq_vec[i])
		aq_vec_stop(aq_vec);

	aq_ptp_ring_stop(self);

	वापस self->aq_hw_ops->hw_stop(self->aq_hw);
पूर्ण

व्योम aq_nic_set_घातer(काष्ठा aq_nic_s *self)
अणु
	अगर (self->घातer_state != AQ_HW_POWER_STATE_D0 ||
	    self->aq_hw->aq_nic_cfg->wol)
		अगर (likely(self->aq_fw_ops->set_घातer)) अणु
			mutex_lock(&self->fwreq_mutex);
			self->aq_fw_ops->set_घातer(self->aq_hw,
						   self->घातer_state,
						   self->ndev->dev_addr);
			mutex_unlock(&self->fwreq_mutex);
		पूर्ण
पूर्ण

व्योम aq_nic_deinit(काष्ठा aq_nic_s *self, bool link_करोwn)
अणु
	काष्ठा aq_vec_s *aq_vec = शून्य;
	अचिन्हित पूर्णांक i = 0U;

	अगर (!self)
		जाओ err_निकास;

	क्रम (i = 0U; i < self->aq_vecs; i++) अणु
		aq_vec = self->aq_vec[i];
		aq_vec_deinit(aq_vec);
		aq_vec_ring_मुक्त(aq_vec);
	पूर्ण

	aq_ptp_unरेजिस्टर(self);
	aq_ptp_ring_deinit(self);
	aq_ptp_ring_मुक्त(self);
	aq_ptp_मुक्त(self);

	अगर (likely(self->aq_fw_ops->deinit) && link_करोwn) अणु
		mutex_lock(&self->fwreq_mutex);
		self->aq_fw_ops->deinit(self->aq_hw);
		mutex_unlock(&self->fwreq_mutex);
	पूर्ण

err_निकास:;
पूर्ण

व्योम aq_nic_मुक्त_vectors(काष्ठा aq_nic_s *self)
अणु
	अचिन्हित पूर्णांक i = 0U;

	अगर (!self)
		जाओ err_निकास;

	क्रम (i = ARRAY_SIZE(self->aq_vec); i--;) अणु
		अगर (self->aq_vec[i]) अणु
			aq_vec_मुक्त(self->aq_vec[i]);
			self->aq_vec[i] = शून्य;
		पूर्ण
	पूर्ण

err_निकास:;
पूर्ण

पूर्णांक aq_nic_पुनः_स्मृति_vectors(काष्ठा aq_nic_s *self)
अणु
	काष्ठा aq_nic_cfg_s *cfg = aq_nic_get_cfg(self);

	aq_nic_मुक्त_vectors(self);

	क्रम (self->aq_vecs = 0; self->aq_vecs < cfg->vecs; self->aq_vecs++) अणु
		self->aq_vec[self->aq_vecs] = aq_vec_alloc(self, self->aq_vecs,
							   cfg);
		अगर (unlikely(!self->aq_vec[self->aq_vecs]))
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम aq_nic_shutकरोwn(काष्ठा aq_nic_s *self)
अणु
	पूर्णांक err = 0;

	अगर (!self->ndev)
		वापस;

	rtnl_lock();

	netअगर_device_detach(self->ndev);

	अगर (netअगर_running(self->ndev)) अणु
		err = aq_nic_stop(self);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण
	aq_nic_deinit(self, !self->aq_hw->aq_nic_cfg->wol);
	aq_nic_set_घातer(self);

err_निकास:
	rtnl_unlock();
पूर्ण

u8 aq_nic_reserve_filter(काष्ठा aq_nic_s *self, क्रमागत aq_rx_filter_type type)
अणु
	u8 location = 0xFF;
	u32 fltr_cnt;
	u32 n_bit;

	चयन (type) अणु
	हाल aq_rx_filter_ethertype:
		location = AQ_RX_LAST_LOC_FETHERT - AQ_RX_FIRST_LOC_FETHERT -
			   self->aq_hw_rx_fltrs.fet_reserved_count;
		self->aq_hw_rx_fltrs.fet_reserved_count++;
		अवरोध;
	हाल aq_rx_filter_l3l4:
		fltr_cnt = AQ_RX_LAST_LOC_FL3L4 - AQ_RX_FIRST_LOC_FL3L4;
		n_bit = fltr_cnt - self->aq_hw_rx_fltrs.fl3l4.reserved_count;

		self->aq_hw_rx_fltrs.fl3l4.active_ipv4 |= BIT(n_bit);
		self->aq_hw_rx_fltrs.fl3l4.reserved_count++;
		location = n_bit;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस location;
पूर्ण

व्योम aq_nic_release_filter(काष्ठा aq_nic_s *self, क्रमागत aq_rx_filter_type type,
			   u32 location)
अणु
	चयन (type) अणु
	हाल aq_rx_filter_ethertype:
		self->aq_hw_rx_fltrs.fet_reserved_count--;
		अवरोध;
	हाल aq_rx_filter_l3l4:
		self->aq_hw_rx_fltrs.fl3l4.reserved_count--;
		self->aq_hw_rx_fltrs.fl3l4.active_ipv4 &= ~BIT(location);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक aq_nic_set_करोwnshअगरt(काष्ठा aq_nic_s *self, पूर्णांक val)
अणु
	पूर्णांक err = 0;
	काष्ठा aq_nic_cfg_s *cfg = &self->aq_nic_cfg;

	अगर (!self->aq_fw_ops->set_करोwnshअगरt)
		वापस -EOPNOTSUPP;

	अगर (val > 15) अणु
		netdev_err(self->ndev, "downshift counter should be <= 15\n");
		वापस -EINVAL;
	पूर्ण
	cfg->करोwnshअगरt_counter = val;

	mutex_lock(&self->fwreq_mutex);
	err = self->aq_fw_ops->set_करोwnshअगरt(self->aq_hw, cfg->करोwnshअगरt_counter);
	mutex_unlock(&self->fwreq_mutex);

	वापस err;
पूर्ण

पूर्णांक aq_nic_set_media_detect(काष्ठा aq_nic_s *self, पूर्णांक val)
अणु
	काष्ठा aq_nic_cfg_s *cfg = &self->aq_nic_cfg;
	पूर्णांक err = 0;

	अगर (!self->aq_fw_ops->set_media_detect)
		वापस -EOPNOTSUPP;

	अगर (val > 0 && val != AQ_HW_MEDIA_DETECT_CNT) अणु
		netdev_err(self->ndev, "EDPD on this device could have only fixed value of %d\n",
			   AQ_HW_MEDIA_DETECT_CNT);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&self->fwreq_mutex);
	err = self->aq_fw_ops->set_media_detect(self->aq_hw, !!val);
	mutex_unlock(&self->fwreq_mutex);

	/* msecs plays no role - configuration is always fixed in PHY */
	अगर (!err)
		cfg->is_media_detect = !!val;

	वापस err;
पूर्ण

पूर्णांक aq_nic_setup_tc_mqprio(काष्ठा aq_nic_s *self, u32 tcs, u8 *prio_tc_map)
अणु
	काष्ठा aq_nic_cfg_s *cfg = &self->aq_nic_cfg;
	स्थिर अचिन्हित पूर्णांक prev_vecs = cfg->vecs;
	bool ndev_running;
	पूर्णांक err = 0;
	पूर्णांक i;

	/* अगर alपढ़ोy the same configuration or
	 * disable request (tcs is 0) and we alपढ़ोy is disabled
	 */
	अगर (tcs == cfg->tcs || (tcs == 0 && !cfg->is_qos))
		वापस 0;

	ndev_running = netअगर_running(self->ndev);
	अगर (ndev_running)
		dev_बंद(self->ndev);

	cfg->tcs = tcs;
	अगर (cfg->tcs == 0)
		cfg->tcs = 1;
	अगर (prio_tc_map)
		स_नकल(cfg->prio_tc_map, prio_tc_map, माप(cfg->prio_tc_map));
	अन्यथा
		क्रम (i = 0; i < माप(cfg->prio_tc_map); i++)
			cfg->prio_tc_map[i] = cfg->tcs * i / 8;

	cfg->is_qos = !!tcs;
	cfg->is_ptp = (cfg->tcs <= AQ_HW_PTP_TC);
	अगर (!cfg->is_ptp)
		netdev_warn(self->ndev, "%s\n",
			    "PTP is auto disabled due to requested TC count.");

	netdev_set_num_tc(self->ndev, cfg->tcs);

	/* Changing the number of TCs might change the number of vectors */
	aq_nic_cfg_update_num_vecs(self);
	अगर (prev_vecs != cfg->vecs) अणु
		err = aq_nic_पुनः_स्मृति_vectors(self);
		अगर (err)
			जाओ err_निकास;
	पूर्ण

	अगर (ndev_running)
		err = dev_खोलो(self->ndev, शून्य);

err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_nic_setup_tc_max_rate(काष्ठा aq_nic_s *self, स्थिर अचिन्हित पूर्णांक tc,
			     स्थिर u32 max_rate)
अणु
	काष्ठा aq_nic_cfg_s *cfg = &self->aq_nic_cfg;

	अगर (tc >= AQ_CFG_TCS_MAX)
		वापस -EINVAL;

	अगर (max_rate && max_rate < 10) अणु
		netdev_warn(self->ndev,
			"Setting %s to the minimum usable value of %dMbps.\n",
			"max rate", 10);
		cfg->tc_max_rate[tc] = 10;
	पूर्ण अन्यथा अणु
		cfg->tc_max_rate[tc] = max_rate;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक aq_nic_setup_tc_min_rate(काष्ठा aq_nic_s *self, स्थिर अचिन्हित पूर्णांक tc,
			     स्थिर u32 min_rate)
अणु
	काष्ठा aq_nic_cfg_s *cfg = &self->aq_nic_cfg;

	अगर (tc >= AQ_CFG_TCS_MAX)
		वापस -EINVAL;

	अगर (min_rate)
		set_bit(tc, &cfg->tc_min_rate_msk);
	अन्यथा
		clear_bit(tc, &cfg->tc_min_rate_msk);

	अगर (min_rate && min_rate < 20) अणु
		netdev_warn(self->ndev,
			"Setting %s to the minimum usable value of %dMbps.\n",
			"min rate", 20);
		cfg->tc_min_rate[tc] = 20;
	पूर्ण अन्यथा अणु
		cfg->tc_min_rate[tc] = min_rate;
	पूर्ण

	वापस 0;
पूर्ण
