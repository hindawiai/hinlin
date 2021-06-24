<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>

#समावेश "hnae.h"
#समावेश "hns_dsaf_mac.h"
#समावेश "hns_dsaf_main.h"
#समावेश "hns_dsaf_ppe.h"
#समावेश "hns_dsaf_rcb.h"

अटल काष्ठा hns_mac_cb *hns_get_mac_cb(काष्ठा hnae_handle *handle)
अणु
	काष्ठा  hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);

	वापस vf_cb->mac_cb;
पूर्ण

अटल काष्ठा dsaf_device *hns_ae_get_dsaf_dev(काष्ठा hnae_ae_dev *dev)
अणु
	वापस container_of(dev, काष्ठा dsaf_device, ae_dev);
पूर्ण

अटल काष्ठा hns_ppe_cb *hns_get_ppe_cb(काष्ठा hnae_handle *handle)
अणु
	पूर्णांक ppe_index;
	काष्ठा ppe_common_cb *ppe_comm;
	काष्ठा  hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);

	ppe_comm = vf_cb->dsaf_dev->ppe_common[0];
	ppe_index = vf_cb->port_index;

	वापस &ppe_comm->ppe_cb[ppe_index];
पूर्ण

अटल पूर्णांक hns_ae_get_q_num_per_vf(
	काष्ठा dsaf_device *dsaf_dev, पूर्णांक port)
अणु
	वापस dsaf_dev->rcb_common[0]->max_q_per_vf;
पूर्ण

अटल पूर्णांक hns_ae_get_vf_num_per_port(
	काष्ठा dsaf_device *dsaf_dev, पूर्णांक port)
अणु
	वापस dsaf_dev->rcb_common[0]->max_vfn;
पूर्ण

अटल काष्ठा ring_pair_cb *hns_ae_get_base_ring_pair(
	काष्ठा dsaf_device *dsaf_dev, पूर्णांक port)
अणु
	काष्ठा rcb_common_cb *rcb_comm = dsaf_dev->rcb_common[0];
	पूर्णांक q_num = rcb_comm->max_q_per_vf;
	पूर्णांक vf_num = rcb_comm->max_vfn;

	वापस &rcb_comm->ring_pair_cb[port * q_num * vf_num];
पूर्ण

अटल काष्ठा ring_pair_cb *hns_ae_get_ring_pair(काष्ठा hnae_queue *q)
अणु
	वापस container_of(q, काष्ठा ring_pair_cb, q);
पूर्ण

अटल काष्ठा hnae_handle *hns_ae_get_handle(काष्ठा hnae_ae_dev *dev,
					     u32 port_id)
अणु
	पूर्णांक vfnum_per_port;
	पूर्णांक qnum_per_vf;
	पूर्णांक i;
	काष्ठा dsaf_device *dsaf_dev;
	काष्ठा hnae_handle *ae_handle;
	काष्ठा ring_pair_cb *ring_pair_cb;
	काष्ठा hnae_vf_cb *vf_cb;

	dsaf_dev = hns_ae_get_dsaf_dev(dev);

	ring_pair_cb = hns_ae_get_base_ring_pair(dsaf_dev, port_id);
	vfnum_per_port = hns_ae_get_vf_num_per_port(dsaf_dev, port_id);
	qnum_per_vf = hns_ae_get_q_num_per_vf(dsaf_dev, port_id);

	vf_cb = kzalloc(माप(*vf_cb) +
			qnum_per_vf * माप(काष्ठा hnae_queue *), GFP_KERNEL);
	अगर (unlikely(!vf_cb)) अणु
		dev_err(dsaf_dev->dev, "malloc vf_cb fail!\n");
		ae_handle = ERR_PTR(-ENOMEM);
		जाओ handle_err;
	पूर्ण
	ae_handle = &vf_cb->ae_handle;
	/* ae_handle Init  */
	ae_handle->owner_dev = dsaf_dev->dev;
	ae_handle->dev = dev;
	ae_handle->q_num = qnum_per_vf;
	ae_handle->coal_param = HNAE_LOWEST_LATENCY_COAL_PARAM;

	/* find ring pair, and set vf id*/
	क्रम (ae_handle->vf_id = 0;
		ae_handle->vf_id < vfnum_per_port; ae_handle->vf_id++) अणु
		अगर (!ring_pair_cb->used_by_vf)
			अवरोध;
		ring_pair_cb += qnum_per_vf;
	पूर्ण
	अगर (ae_handle->vf_id >= vfnum_per_port) अणु
		dev_err(dsaf_dev->dev, "malloc queue fail!\n");
		ae_handle = ERR_PTR(-EINVAL);
		जाओ vf_id_err;
	पूर्ण

	ae_handle->qs = (काष्ठा hnae_queue **)(&ae_handle->qs + 1);
	क्रम (i = 0; i < qnum_per_vf; i++) अणु
		ae_handle->qs[i] = &ring_pair_cb->q;
		ae_handle->qs[i]->rx_ring.q = ae_handle->qs[i];
		ae_handle->qs[i]->tx_ring.q = ae_handle->qs[i];

		ring_pair_cb->used_by_vf = 1;
		ring_pair_cb++;
	पूर्ण

	vf_cb->dsaf_dev = dsaf_dev;
	vf_cb->port_index = port_id;
	vf_cb->mac_cb = dsaf_dev->mac_cb[port_id];

	ae_handle->phy_अगर = vf_cb->mac_cb->phy_अगर;
	ae_handle->phy_dev = vf_cb->mac_cb->phy_dev;
	ae_handle->अगर_support = vf_cb->mac_cb->अगर_support;
	ae_handle->port_type = vf_cb->mac_cb->mac_type;
	ae_handle->media_type = vf_cb->mac_cb->media_type;
	ae_handle->dport_id = port_id;

	वापस ae_handle;
vf_id_err:
	kमुक्त(vf_cb);
handle_err:
	वापस ae_handle;
पूर्ण

अटल व्योम hns_ae_put_handle(काष्ठा hnae_handle *handle)
अणु
	काष्ठा hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);
	पूर्णांक i;

	क्रम (i = 0; i < handle->q_num; i++)
		hns_ae_get_ring_pair(handle->qs[i])->used_by_vf = 0;

	kमुक्त(vf_cb);
पूर्ण

अटल पूर्णांक hns_ae_रुको_flow_करोwn(काष्ठा hnae_handle *handle)
अणु
	काष्ठा dsaf_device *dsaf_dev;
	काष्ठा hns_ppe_cb *ppe_cb;
	काष्ठा hnae_vf_cb *vf_cb;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < handle->q_num; i++) अणु
		ret = hns_rcb_रुको_tx_ring_clean(handle->qs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	ppe_cb = hns_get_ppe_cb(handle);
	ret = hns_ppe_रुको_tx_fअगरo_clean(ppe_cb);
	अगर (ret)
		वापस ret;

	dsaf_dev = hns_ae_get_dsaf_dev(handle->dev);
	अगर (!dsaf_dev)
		वापस -EINVAL;
	ret = hns_dsaf_रुको_pkt_clean(dsaf_dev, handle->dport_id);
	अगर (ret)
		वापस ret;

	vf_cb = hns_ae_get_vf_cb(handle);
	ret = hns_mac_रुको_fअगरo_clean(vf_cb->mac_cb);
	अगर (ret)
		वापस ret;

	mdelay(10);
	वापस 0;
पूर्ण

अटल व्योम hns_ae_ring_enable_all(काष्ठा hnae_handle *handle, पूर्णांक val)
अणु
	पूर्णांक q_num = handle->q_num;
	पूर्णांक i;

	क्रम (i = 0; i < q_num; i++)
		hns_rcb_ring_enable_hw(handle->qs[i], val);
पूर्ण

अटल व्योम hns_ae_init_queue(काष्ठा hnae_queue *q)
अणु
	काष्ठा ring_pair_cb *ring =
		container_of(q, काष्ठा ring_pair_cb, q);

	hns_rcb_init_hw(ring);
पूर्ण

अटल व्योम hns_ae_fini_queue(काष्ठा hnae_queue *q)
अणु
	काष्ठा hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(q->handle);

	अगर (vf_cb->mac_cb->mac_type == HNAE_PORT_SERVICE)
		hns_rcb_reset_ring_hw(q);
पूर्ण

अटल पूर्णांक hns_ae_set_mac_address(काष्ठा hnae_handle *handle, व्योम *p)
अणु
	पूर्णांक ret;
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	अगर (!p || !is_valid_ether_addr((स्थिर u8 *)p)) अणु
		dev_err(handle->owner_dev, "is not valid ether addr !\n");
		वापस -EADDRNOTAVAIL;
	पूर्ण

	ret = hns_mac_change_vf_addr(mac_cb, handle->vf_id, p);
	अगर (ret != 0) अणु
		dev_err(handle->owner_dev,
			"set_mac_address fail, ret=%d!\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_ae_add_uc_address(काष्ठा hnae_handle *handle,
				 स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	अगर (mac_cb->mac_type != HNAE_PORT_SERVICE)
		वापस -ENOSPC;

	वापस hns_mac_add_uc_addr(mac_cb, handle->vf_id, addr);
पूर्ण

अटल पूर्णांक hns_ae_rm_uc_address(काष्ठा hnae_handle *handle,
				स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	अगर (mac_cb->mac_type != HNAE_PORT_SERVICE)
		वापस -ENOSPC;

	वापस hns_mac_rm_uc_addr(mac_cb, handle->vf_id, addr);
पूर्ण

अटल पूर्णांक hns_ae_set_multicast_one(काष्ठा hnae_handle *handle, व्योम *addr)
अणु
	पूर्णांक ret;
	अक्षर *mac_addr = (अक्षर *)addr;
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);
	u8 port_num;

	निश्चित(mac_cb);

	अगर (mac_cb->mac_type != HNAE_PORT_SERVICE)
		वापस 0;

	ret = hns_mac_set_multi(mac_cb, mac_cb->mac_id, mac_addr, true);
	अगर (ret) अणु
		dev_err(handle->owner_dev,
			"mac add mul_mac:%pM port%d  fail, ret = %#x!\n",
			mac_addr, mac_cb->mac_id, ret);
		वापस ret;
	पूर्ण

	ret = hns_mac_get_inner_port_num(mac_cb, handle->vf_id, &port_num);
	अगर (ret)
		वापस ret;

	ret = hns_mac_set_multi(mac_cb, port_num, mac_addr, true);
	अगर (ret)
		dev_err(handle->owner_dev,
			"mac add mul_mac:%pM port%d  fail, ret = %#x!\n",
			mac_addr, DSAF_BASE_INNER_PORT_NUM, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_ae_clr_multicast(काष्ठा hnae_handle *handle)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	अगर (mac_cb->mac_type != HNAE_PORT_SERVICE)
		वापस 0;

	वापस hns_mac_clr_multicast(mac_cb, handle->vf_id);
पूर्ण

अटल पूर्णांक hns_ae_set_mtu(काष्ठा hnae_handle *handle, पूर्णांक new_mtu)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);
	काष्ठा hnae_queue *q;
	u32 rx_buf_size;
	पूर्णांक i, ret;

	/* when buf_size is 2048, max mtu is 6K क्रम rx ring max bd num is 3. */
	अगर (!AE_IS_VER1(mac_cb->dsaf_dev->dsaf_ver)) अणु
		अगर (new_mtu <= BD_SIZE_2048_MAX_MTU)
			rx_buf_size = 2048;
		अन्यथा
			rx_buf_size = 4096;
	पूर्ण अन्यथा अणु
		rx_buf_size = mac_cb->dsaf_dev->buf_size;
	पूर्ण

	ret = hns_mac_set_mtu(mac_cb, new_mtu, rx_buf_size);

	अगर (!ret) अणु
		/* reinit ring buf_size */
		क्रम (i = 0; i < handle->q_num; i++) अणु
			q = handle->qs[i];
			q->rx_ring.buf_size = rx_buf_size;
			hns_rcb_set_rx_ring_bs(q, rx_buf_size);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hns_ae_set_tso_stats(काष्ठा hnae_handle *handle, पूर्णांक enable)
अणु
	काष्ठा hns_ppe_cb *ppe_cb = hns_get_ppe_cb(handle);

	hns_ppe_set_tso_enable(ppe_cb, enable);
पूर्ण

अटल पूर्णांक hns_ae_start(काष्ठा hnae_handle *handle)
अणु
	पूर्णांक ret;
	पूर्णांक k;
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	ret = hns_mac_vm_config_bc_en(mac_cb, 0, true);
	अगर (ret)
		वापस ret;

	क्रम (k = 0; k < handle->q_num; k++) अणु
		अगर (AE_IS_VER1(mac_cb->dsaf_dev->dsaf_ver))
			hns_rcb_पूर्णांक_clr_hw(handle->qs[k],
					   RCB_INT_FLAG_TX | RCB_INT_FLAG_RX);
		अन्यथा
			hns_rcbv2_पूर्णांक_clr_hw(handle->qs[k],
					     RCB_INT_FLAG_TX | RCB_INT_FLAG_RX);
	पूर्ण
	hns_ae_ring_enable_all(handle, 1);
	msleep(100);

	hns_mac_start(mac_cb);

	वापस 0;
पूर्ण

अटल व्योम hns_ae_stop(काष्ठा hnae_handle *handle)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	/* just clean tx fbd, neednot rx fbd*/
	hns_rcb_रुको_fbd_clean(handle->qs, handle->q_num, RCB_INT_FLAG_TX);

	msleep(20);

	hns_mac_stop(mac_cb);

	usleep_range(10000, 20000);

	hns_ae_ring_enable_all(handle, 0);

	/* clean rx fbd. */
	hns_rcb_रुको_fbd_clean(handle->qs, handle->q_num, RCB_INT_FLAG_RX);

	(व्योम)hns_mac_vm_config_bc_en(mac_cb, 0, false);
पूर्ण

अटल व्योम hns_ae_reset(काष्ठा hnae_handle *handle)
अणु
	काष्ठा hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);

	अगर (vf_cb->mac_cb->mac_type == HNAE_PORT_DEBUG) अणु
		hns_mac_reset(vf_cb->mac_cb);
		hns_ppe_reset_common(vf_cb->dsaf_dev, 0);
	पूर्ण
पूर्ण

अटल व्योम hns_ae_toggle_ring_irq(काष्ठा hnae_ring *ring, u32 mask)
अणु
	u32 flag;

	अगर (is_tx_ring(ring))
		flag = RCB_INT_FLAG_TX;
	अन्यथा
		flag = RCB_INT_FLAG_RX;

	hns_rcb_पूर्णांक_ctrl_hw(ring->q, flag, mask);
पूर्ण

अटल व्योम hns_aev2_toggle_ring_irq(काष्ठा hnae_ring *ring, u32 mask)
अणु
	u32 flag;

	अगर (is_tx_ring(ring))
		flag = RCB_INT_FLAG_TX;
	अन्यथा
		flag = RCB_INT_FLAG_RX;

	hns_rcbv2_पूर्णांक_ctrl_hw(ring->q, flag, mask);
पूर्ण

अटल पूर्णांक hns_ae_get_link_status(काष्ठा hnae_handle *handle)
अणु
	u32 link_status;
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	hns_mac_get_link_status(mac_cb, &link_status);

	वापस !!link_status;
पूर्ण

अटल पूर्णांक hns_ae_get_mac_info(काष्ठा hnae_handle *handle,
			       u8 *स्वतः_neg, u16 *speed, u8 *duplex)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	वापस hns_mac_get_port_info(mac_cb, स्वतः_neg, speed, duplex);
पूर्ण

अटल bool hns_ae_need_adjust_link(काष्ठा hnae_handle *handle, पूर्णांक speed,
				    पूर्णांक duplex)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	वापस hns_mac_need_adjust_link(mac_cb, speed, duplex);
पूर्ण

अटल व्योम hns_ae_adjust_link(काष्ठा hnae_handle *handle, पूर्णांक speed,
			       पूर्णांक duplex)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	चयन (mac_cb->dsaf_dev->dsaf_ver) अणु
	हाल AE_VERSION_1:
		hns_mac_adjust_link(mac_cb, speed, duplex);
		अवरोध;

	हाल AE_VERSION_2:
		/* chip need to clear all pkt inside */
		hns_mac_disable(mac_cb, MAC_COMM_MODE_RX);
		अगर (hns_ae_रुको_flow_करोwn(handle)) अणु
			hns_mac_enable(mac_cb, MAC_COMM_MODE_RX);
			अवरोध;
		पूर्ण

		hns_mac_adjust_link(mac_cb, speed, duplex);
		hns_mac_enable(mac_cb, MAC_COMM_MODE_RX);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस;
पूर्ण

अटल व्योम hns_ae_get_ring_bdnum_limit(काष्ठा hnae_queue *queue,
					u32 *uplimit)
अणु
	*uplimit = HNS_RCB_RING_MAX_PENDING_BD;
पूर्ण

अटल व्योम hns_ae_get_छोड़ोparam(काष्ठा hnae_handle *handle,
				  u32 *स्वतः_neg, u32 *rx_en, u32 *tx_en)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;

	hns_mac_get_स्वतःneg(mac_cb, स्वतः_neg);

	hns_mac_get_छोड़ोparam(mac_cb, rx_en, tx_en);

	/* Service port's छोड़ो feature is provided by DSAF, not mac */
	अगर (handle->port_type == HNAE_PORT_SERVICE)
		hns_dsaf_get_rx_mac_छोड़ो_en(dsaf_dev, mac_cb->mac_id, rx_en);
पूर्ण

अटल व्योम hns_ae_set_promisc_mode(काष्ठा hnae_handle *handle, u32 en)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	hns_dsaf_set_promisc_mode(hns_ae_get_dsaf_dev(handle->dev), en);
	hns_mac_set_promisc(mac_cb, (u8)!!en);
पूर्ण

अटल पूर्णांक hns_ae_set_छोड़ोparam(काष्ठा hnae_handle *handle,
				 u32 स्वतःneg, u32 rx_en, u32 tx_en)
अणु
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	पूर्णांक ret;

	ret = hns_mac_set_स्वतःneg(mac_cb, स्वतःneg);
	अगर (ret)
		वापस ret;

	/* Service port's छोड़ो feature is provided by DSAF, not mac */
	अगर (handle->port_type == HNAE_PORT_SERVICE) अणु
		ret = hns_dsaf_set_rx_mac_छोड़ो_en(dsaf_dev,
						   mac_cb->mac_id, rx_en);
		अगर (ret)
			वापस ret;
		rx_en = 0;
	पूर्ण
	वापस hns_mac_set_छोड़ोparam(mac_cb, rx_en, tx_en);
पूर्ण

अटल व्योम hns_ae_get_coalesce_usecs(काष्ठा hnae_handle *handle,
				      u32 *tx_usecs, u32 *rx_usecs)
अणु
	काष्ठा ring_pair_cb *ring_pair =
		container_of(handle->qs[0], काष्ठा ring_pair_cb, q);

	*tx_usecs = hns_rcb_get_coalesce_usecs(ring_pair->rcb_common,
					       ring_pair->port_id_in_comm);
	*rx_usecs = hns_rcb_get_coalesce_usecs(ring_pair->rcb_common,
					       ring_pair->port_id_in_comm);
पूर्ण

अटल व्योम hns_ae_get_max_coalesced_frames(काष्ठा hnae_handle *handle,
					    u32 *tx_frames, u32 *rx_frames)
अणु
	काष्ठा ring_pair_cb *ring_pair =
		container_of(handle->qs[0], काष्ठा ring_pair_cb, q);
	काष्ठा dsaf_device *dsaf_dev = hns_ae_get_dsaf_dev(handle->dev);

	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver) ||
	    handle->port_type == HNAE_PORT_DEBUG)
		*tx_frames = hns_rcb_get_rx_coalesced_frames(
			ring_pair->rcb_common, ring_pair->port_id_in_comm);
	अन्यथा
		*tx_frames = hns_rcb_get_tx_coalesced_frames(
			ring_pair->rcb_common, ring_pair->port_id_in_comm);
	*rx_frames = hns_rcb_get_rx_coalesced_frames(ring_pair->rcb_common,
						  ring_pair->port_id_in_comm);
पूर्ण

अटल पूर्णांक hns_ae_set_coalesce_usecs(काष्ठा hnae_handle *handle,
				     u32 समयout)
अणु
	काष्ठा ring_pair_cb *ring_pair =
		container_of(handle->qs[0], काष्ठा ring_pair_cb, q);

	वापस hns_rcb_set_coalesce_usecs(
		ring_pair->rcb_common, ring_pair->port_id_in_comm, समयout);
पूर्ण

अटल पूर्णांक hns_ae_set_coalesce_frames(काष्ठा hnae_handle *handle,
				      u32 tx_frames, u32 rx_frames)
अणु
	पूर्णांक ret;
	काष्ठा ring_pair_cb *ring_pair =
		container_of(handle->qs[0], काष्ठा ring_pair_cb, q);
	काष्ठा dsaf_device *dsaf_dev = hns_ae_get_dsaf_dev(handle->dev);

	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver) ||
	    handle->port_type == HNAE_PORT_DEBUG) अणु
		अगर (tx_frames != rx_frames)
			वापस -EINVAL;
		वापस hns_rcb_set_rx_coalesced_frames(
			ring_pair->rcb_common,
			ring_pair->port_id_in_comm, rx_frames);
	पूर्ण अन्यथा अणु
		अगर (tx_frames != 1)
			वापस -EINVAL;
		ret = hns_rcb_set_tx_coalesced_frames(
			ring_pair->rcb_common,
			ring_pair->port_id_in_comm, tx_frames);
		अगर (ret)
			वापस ret;

		वापस hns_rcb_set_rx_coalesced_frames(
			ring_pair->rcb_common,
			ring_pair->port_id_in_comm, rx_frames);
	पूर्ण
पूर्ण

अटल व्योम hns_ae_get_coalesce_range(काष्ठा hnae_handle *handle,
				      u32 *tx_frames_low, u32 *rx_frames_low,
				      u32 *tx_frames_high, u32 *rx_frames_high,
				      u32 *tx_usecs_low, u32 *rx_usecs_low,
				      u32 *tx_usecs_high, u32 *rx_usecs_high)
अणु
	काष्ठा dsaf_device *dsaf_dev;

	निश्चित(handle);

	dsaf_dev = hns_ae_get_dsaf_dev(handle->dev);

	*tx_frames_low  = HNS_RCB_TX_FRAMES_LOW;
	*rx_frames_low  = HNS_RCB_RX_FRAMES_LOW;

	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver) ||
	    handle->port_type == HNAE_PORT_DEBUG)
		*tx_frames_high =
			(dsaf_dev->desc_num - 1 > HNS_RCB_TX_FRAMES_HIGH) ?
			HNS_RCB_TX_FRAMES_HIGH : dsaf_dev->desc_num - 1;
	अन्यथा
		*tx_frames_high = 1;

	*rx_frames_high = (dsaf_dev->desc_num - 1 > HNS_RCB_RX_FRAMES_HIGH) ?
		HNS_RCB_RX_FRAMES_HIGH : dsaf_dev->desc_num - 1;
	*tx_usecs_low   = HNS_RCB_TX_USECS_LOW;
	*rx_usecs_low   = HNS_RCB_RX_USECS_LOW;
	*tx_usecs_high  = HNS_RCB_TX_USECS_HIGH;
	*rx_usecs_high  = HNS_RCB_RX_USECS_HIGH;
पूर्ण

अटल व्योम hns_ae_update_stats(काष्ठा hnae_handle *handle,
				काष्ठा net_device_stats *net_stats)
अणु
	पूर्णांक port;
	पूर्णांक idx;
	काष्ठा dsaf_device *dsaf_dev;
	काष्ठा hns_mac_cb *mac_cb;
	काष्ठा hns_ppe_cb *ppe_cb;
	काष्ठा hnae_queue *queue;
	काष्ठा hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);
	u64 tx_bytes = 0, rx_bytes = 0, tx_packets = 0, rx_packets = 0;
	u64 rx_errors = 0, tx_errors = 0, tx_dropped = 0;
	u64 rx_missed_errors;

	dsaf_dev = hns_ae_get_dsaf_dev(handle->dev);
	अगर (!dsaf_dev)
		वापस;
	port = vf_cb->port_index;
	ppe_cb = hns_get_ppe_cb(handle);
	mac_cb = hns_get_mac_cb(handle);

	क्रम (idx = 0; idx < handle->q_num; idx++) अणु
		queue = handle->qs[idx];
		hns_rcb_update_stats(queue);

		tx_bytes += queue->tx_ring.stats.tx_bytes;
		tx_packets += queue->tx_ring.stats.tx_pkts;
		rx_bytes += queue->rx_ring.stats.rx_bytes;
		rx_packets += queue->rx_ring.stats.rx_pkts;

		rx_errors += queue->rx_ring.stats.err_pkt_len
				+ queue->rx_ring.stats.l2_err
				+ queue->rx_ring.stats.l3l4_csum_err;
	पूर्ण

	hns_ppe_update_stats(ppe_cb);
	rx_missed_errors = ppe_cb->hw_stats.rx_drop_no_buf;
	tx_errors += ppe_cb->hw_stats.tx_err_checksum
		+ ppe_cb->hw_stats.tx_err_fअगरo_empty;

	अगर (mac_cb->mac_type == HNAE_PORT_SERVICE) अणु
		hns_dsaf_update_stats(dsaf_dev, port);
		/* क्रम port upline direction, i.e., rx. */
		rx_missed_errors += dsaf_dev->hw_stats[port].bp_drop;
		rx_missed_errors += dsaf_dev->hw_stats[port].pad_drop;
		rx_missed_errors += dsaf_dev->hw_stats[port].crc_false;

		/* क्रम port करोwnline direction, i.e., tx. */
		port = port + DSAF_PPE_INODE_BASE;
		hns_dsaf_update_stats(dsaf_dev, port);
		tx_dropped += dsaf_dev->hw_stats[port].bp_drop;
		tx_dropped += dsaf_dev->hw_stats[port].pad_drop;
		tx_dropped += dsaf_dev->hw_stats[port].crc_false;
		tx_dropped += dsaf_dev->hw_stats[port].rslt_drop;
		tx_dropped += dsaf_dev->hw_stats[port].vlan_drop;
		tx_dropped += dsaf_dev->hw_stats[port].stp_drop;
	पूर्ण

	hns_mac_update_stats(mac_cb);
	rx_errors += mac_cb->hw_stats.rx_fअगरo_overrun_err;

	tx_errors += mac_cb->hw_stats.tx_bad_pkts
		+ mac_cb->hw_stats.tx_fragment_err
		+ mac_cb->hw_stats.tx_jabber_err
		+ mac_cb->hw_stats.tx_underrun_err
		+ mac_cb->hw_stats.tx_crc_err;

	net_stats->tx_bytes = tx_bytes;
	net_stats->tx_packets = tx_packets;
	net_stats->rx_bytes = rx_bytes;
	net_stats->rx_dropped = 0;
	net_stats->rx_packets = rx_packets;
	net_stats->rx_errors = rx_errors;
	net_stats->tx_errors = tx_errors;
	net_stats->tx_dropped = tx_dropped;
	net_stats->rx_missed_errors = rx_missed_errors;
	net_stats->rx_crc_errors = mac_cb->hw_stats.rx_fcs_err;
	net_stats->rx_frame_errors = mac_cb->hw_stats.rx_align_err;
	net_stats->rx_fअगरo_errors = mac_cb->hw_stats.rx_fअगरo_overrun_err;
	net_stats->rx_length_errors = mac_cb->hw_stats.rx_len_err;
	net_stats->multicast = mac_cb->hw_stats.rx_mc_pkts;
पूर्ण

अटल व्योम hns_ae_get_stats(काष्ठा hnae_handle *handle, u64 *data)
अणु
	पूर्णांक idx;
	काष्ठा hns_mac_cb *mac_cb;
	काष्ठा hns_ppe_cb *ppe_cb;
	u64 *p = data;
	काष्ठा  hnae_vf_cb *vf_cb;

	अगर (!handle || !data) अणु
		pr_err("hns_ae_get_stats NULL handle or data pointer!\n");
		वापस;
	पूर्ण

	vf_cb = hns_ae_get_vf_cb(handle);
	mac_cb = hns_get_mac_cb(handle);
	ppe_cb = hns_get_ppe_cb(handle);

	क्रम (idx = 0; idx < handle->q_num; idx++) अणु
		hns_rcb_get_stats(handle->qs[idx], p);
		p += hns_rcb_get_ring_sset_count((पूर्णांक)ETH_SS_STATS);
	पूर्ण

	hns_ppe_get_stats(ppe_cb, p);
	p += hns_ppe_get_sset_count((पूर्णांक)ETH_SS_STATS);

	hns_mac_get_stats(mac_cb, p);
	p += hns_mac_get_sset_count(mac_cb, (पूर्णांक)ETH_SS_STATS);

	अगर (mac_cb->mac_type == HNAE_PORT_SERVICE)
		hns_dsaf_get_stats(vf_cb->dsaf_dev, p, vf_cb->port_index);
पूर्ण

अटल व्योम hns_ae_get_strings(काष्ठा hnae_handle *handle,
			       u32 stringset, u8 *data)
अणु
	पूर्णांक port;
	पूर्णांक idx;
	काष्ठा hns_mac_cb *mac_cb;
	काष्ठा hns_ppe_cb *ppe_cb;
	काष्ठा dsaf_device *dsaf_dev = hns_ae_get_dsaf_dev(handle->dev);
	u8 *p = data;
	काष्ठा	hnae_vf_cb *vf_cb;

	निश्चित(handle);

	vf_cb = hns_ae_get_vf_cb(handle);
	port = vf_cb->port_index;
	mac_cb = hns_get_mac_cb(handle);
	ppe_cb = hns_get_ppe_cb(handle);

	क्रम (idx = 0; idx < handle->q_num; idx++) अणु
		hns_rcb_get_strings(stringset, p, idx);
		p += ETH_GSTRING_LEN * hns_rcb_get_ring_sset_count(stringset);
	पूर्ण

	hns_ppe_get_strings(ppe_cb, stringset, p);
	p += ETH_GSTRING_LEN * hns_ppe_get_sset_count(stringset);

	hns_mac_get_strings(mac_cb, stringset, p);
	p += ETH_GSTRING_LEN * hns_mac_get_sset_count(mac_cb, stringset);

	अगर (mac_cb->mac_type == HNAE_PORT_SERVICE)
		hns_dsaf_get_strings(stringset, p, port, dsaf_dev);
पूर्ण

अटल पूर्णांक hns_ae_get_sset_count(काष्ठा hnae_handle *handle, पूर्णांक stringset)
अणु
	u32 sset_count = 0;
	काष्ठा hns_mac_cb *mac_cb;
	काष्ठा dsaf_device *dsaf_dev = hns_ae_get_dsaf_dev(handle->dev);

	निश्चित(handle);

	mac_cb = hns_get_mac_cb(handle);

	sset_count += hns_rcb_get_ring_sset_count(stringset) * handle->q_num;
	sset_count += hns_ppe_get_sset_count(stringset);
	sset_count += hns_mac_get_sset_count(mac_cb, stringset);

	अगर (mac_cb->mac_type == HNAE_PORT_SERVICE)
		sset_count += hns_dsaf_get_sset_count(dsaf_dev, stringset);

	वापस sset_count;
पूर्ण

अटल पूर्णांक hns_ae_config_loopback(काष्ठा hnae_handle *handle,
				  क्रमागत hnae_loop loop, पूर्णांक en)
अणु
	पूर्णांक ret;
	काष्ठा hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);
	काष्ठा hns_mac_cb *mac_cb = hns_get_mac_cb(handle);
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;

	चयन (loop) अणु
	हाल MAC_INTERNALLOOP_PHY:
		ret = 0;
		अवरोध;
	हाल MAC_INTERNALLOOP_SERDES:
		ret = dsaf_dev->misc_op->cfg_serdes_loopback(vf_cb->mac_cb,
							     !!en);
		अवरोध;
	हाल MAC_INTERNALLOOP_MAC:
		ret = hns_mac_config_mac_loopback(vf_cb->mac_cb, loop, en);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hns_ae_update_led_status(काष्ठा hnae_handle *handle)
अणु
	काष्ठा hns_mac_cb *mac_cb;

	निश्चित(handle);
	mac_cb = hns_get_mac_cb(handle);
	अगर (mac_cb->media_type != HNAE_MEDIA_TYPE_FIBER)
		वापस;

	hns_set_led_opt(mac_cb);
पूर्ण

अटल पूर्णांक hns_ae_cpld_set_led_id(काष्ठा hnae_handle *handle,
				  क्रमागत hnae_led_state status)
अणु
	काष्ठा hns_mac_cb *mac_cb;

	निश्चित(handle);

	mac_cb = hns_get_mac_cb(handle);

	वापस hns_cpld_led_set_id(mac_cb, status);
पूर्ण

अटल व्योम hns_ae_get_regs(काष्ठा hnae_handle *handle, व्योम *data)
अणु
	u32 *p = data;
	पूर्णांक i;
	काष्ठा hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);
	काष्ठा hns_ppe_cb *ppe_cb = hns_get_ppe_cb(handle);

	hns_ppe_get_regs(ppe_cb, p);
	p += hns_ppe_get_regs_count();

	hns_rcb_get_common_regs(vf_cb->dsaf_dev->rcb_common[0], p);
	p += hns_rcb_get_common_regs_count();

	क्रम (i = 0; i < handle->q_num; i++) अणु
		hns_rcb_get_ring_regs(handle->qs[i], p);
		p += hns_rcb_get_ring_regs_count();
	पूर्ण

	hns_mac_get_regs(vf_cb->mac_cb, p);
	p += hns_mac_get_regs_count(vf_cb->mac_cb);

	अगर (vf_cb->mac_cb->mac_type == HNAE_PORT_SERVICE)
		hns_dsaf_get_regs(vf_cb->dsaf_dev, vf_cb->port_index, p);
पूर्ण

अटल पूर्णांक hns_ae_get_regs_len(काष्ठा hnae_handle *handle)
अणु
	u32 total_num;
	काष्ठा hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);

	total_num = hns_ppe_get_regs_count();
	total_num += hns_rcb_get_common_regs_count();
	total_num += hns_rcb_get_ring_regs_count() * handle->q_num;
	total_num += hns_mac_get_regs_count(vf_cb->mac_cb);

	अगर (vf_cb->mac_cb->mac_type == HNAE_PORT_SERVICE)
		total_num += hns_dsaf_get_regs_count();

	वापस total_num;
पूर्ण

अटल u32 hns_ae_get_rss_key_size(काष्ठा hnae_handle *handle)
अणु
	वापस HNS_PPEV2_RSS_KEY_SIZE;
पूर्ण

अटल u32 hns_ae_get_rss_indir_size(काष्ठा hnae_handle *handle)
अणु
	वापस HNS_PPEV2_RSS_IND_TBL_SIZE;
पूर्ण

अटल पूर्णांक hns_ae_get_rss(काष्ठा hnae_handle *handle, u32 *indir, u8 *key,
			  u8 *hfunc)
अणु
	काष्ठा hns_ppe_cb *ppe_cb = hns_get_ppe_cb(handle);

	/* currently we support only one type of hash function i.e. Toep hash */
	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	/* get the RSS Key required by the user */
	अगर (key)
		स_नकल(key, ppe_cb->rss_key, HNS_PPEV2_RSS_KEY_SIZE);

	/* update the current hash->queue mappings from the shaकरोw RSS table */
	अगर (indir)
		स_नकल(indir, ppe_cb->rss_indir_table,
		       HNS_PPEV2_RSS_IND_TBL_SIZE  * माप(*indir));

	वापस 0;
पूर्ण

अटल पूर्णांक hns_ae_set_rss(काष्ठा hnae_handle *handle, स्थिर u32 *indir,
			  स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा hns_ppe_cb *ppe_cb = hns_get_ppe_cb(handle);

	/* set the RSS Hash Key अगर specअगरअगरed by the user */
	अगर (key) अणु
		स_नकल(ppe_cb->rss_key, key, HNS_PPEV2_RSS_KEY_SIZE);
		hns_ppe_set_rss_key(ppe_cb, ppe_cb->rss_key);
	पूर्ण

	अगर (indir) अणु
		/* update the shaकरोw RSS table with user specअगरied qids */
		स_नकल(ppe_cb->rss_indir_table, indir,
		       HNS_PPEV2_RSS_IND_TBL_SIZE  * माप(*indir));

		/* now update the hardware */
		hns_ppe_set_indir_table(ppe_cb, ppe_cb->rss_indir_table);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा hnae_ae_ops hns_dsaf_ops = अणु
	.get_handle = hns_ae_get_handle,
	.put_handle = hns_ae_put_handle,
	.init_queue = hns_ae_init_queue,
	.fini_queue = hns_ae_fini_queue,
	.start = hns_ae_start,
	.stop = hns_ae_stop,
	.reset = hns_ae_reset,
	.toggle_ring_irq = hns_ae_toggle_ring_irq,
	.get_status = hns_ae_get_link_status,
	.get_info = hns_ae_get_mac_info,
	.adjust_link = hns_ae_adjust_link,
	.need_adjust_link = hns_ae_need_adjust_link,
	.set_loopback = hns_ae_config_loopback,
	.get_ring_bdnum_limit = hns_ae_get_ring_bdnum_limit,
	.get_छोड़ोparam = hns_ae_get_छोड़ोparam,
	.set_छोड़ोparam = hns_ae_set_छोड़ोparam,
	.get_coalesce_usecs = hns_ae_get_coalesce_usecs,
	.get_max_coalesced_frames = hns_ae_get_max_coalesced_frames,
	.set_coalesce_usecs = hns_ae_set_coalesce_usecs,
	.set_coalesce_frames = hns_ae_set_coalesce_frames,
	.get_coalesce_range = hns_ae_get_coalesce_range,
	.set_promisc_mode = hns_ae_set_promisc_mode,
	.set_mac_addr = hns_ae_set_mac_address,
	.add_uc_addr = hns_ae_add_uc_address,
	.rm_uc_addr = hns_ae_rm_uc_address,
	.set_mc_addr = hns_ae_set_multicast_one,
	.clr_mc_addr = hns_ae_clr_multicast,
	.set_mtu = hns_ae_set_mtu,
	.update_stats = hns_ae_update_stats,
	.set_tso_stats = hns_ae_set_tso_stats,
	.get_stats = hns_ae_get_stats,
	.get_strings = hns_ae_get_strings,
	.get_sset_count = hns_ae_get_sset_count,
	.update_led_status = hns_ae_update_led_status,
	.set_led_id = hns_ae_cpld_set_led_id,
	.get_regs = hns_ae_get_regs,
	.get_regs_len = hns_ae_get_regs_len,
	.get_rss_key_size = hns_ae_get_rss_key_size,
	.get_rss_indir_size = hns_ae_get_rss_indir_size,
	.get_rss = hns_ae_get_rss,
	.set_rss = hns_ae_set_rss
पूर्ण;

पूर्णांक hns_dsaf_ae_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	काष्ठा hnae_ae_dev *ae_dev = &dsaf_dev->ae_dev;
	अटल atomic_t id = ATOMIC_INIT(-1);

	चयन (dsaf_dev->dsaf_ver) अणु
	हाल AE_VERSION_1:
		hns_dsaf_ops.toggle_ring_irq = hns_ae_toggle_ring_irq;
		अवरोध;
	हाल AE_VERSION_2:
		hns_dsaf_ops.toggle_ring_irq = hns_aev2_toggle_ring_irq;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	snम_लिखो(ae_dev->name, AE_NAME_SIZE, "%s%d", DSAF_DEVICE_NAME,
		 (पूर्णांक)atomic_inc_वापस(&id));
	ae_dev->ops = &hns_dsaf_ops;
	ae_dev->dev = dsaf_dev->dev;

	वापस hnae_ae_रेजिस्टर(ae_dev, THIS_MODULE);
पूर्ण

व्योम hns_dsaf_ae_uninit(काष्ठा dsaf_device *dsaf_dev)
अणु
	hnae_ae_unरेजिस्टर(&dsaf_dev->ae_dev);
पूर्ण
