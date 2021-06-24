<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#समावेश <linux/iopoll.h>

#समावेश "aq_hw.h"
#समावेश "aq_hw_utils.h"
#समावेश "aq_nic.h"
#समावेश "hw_atl/hw_atl_llh.h"
#समावेश "hw_atl2_utils.h"
#समावेश "hw_atl2_llh.h"
#समावेश "hw_atl2_internal.h"

#घोषणा AQ_A2_FW_READ_TRY_MAX 1000

#घोषणा hw_atl2_shared_buffer_ग_लिखो(HW, ITEM, VARIABLE) \
अणु\
	BUILD_BUG_ON_MSG((दुरत्व(काष्ठा fw_पूर्णांकerface_in, ITEM) % \
			 माप(u32)) != 0,\
			 "Unaligned write " # ITEM);\
	BUILD_BUG_ON_MSG((माप(VARIABLE) %  माप(u32)) != 0,\
			 "Unaligned write length " # ITEM);\
	hw_atl2_mअगर_shared_buf_ग_लिखो(HW,\
		(दुरत्व(काष्ठा fw_पूर्णांकerface_in, ITEM) / माप(u32)),\
		(u32 *)&(VARIABLE), माप(VARIABLE) / माप(u32));\
पूर्ण

#घोषणा hw_atl2_shared_buffer_get(HW, ITEM, VARIABLE) \
अणु\
	BUILD_BUG_ON_MSG((दुरत्व(काष्ठा fw_पूर्णांकerface_in, ITEM) % \
			 माप(u32)) != 0,\
			 "Unaligned get " # ITEM);\
	BUILD_BUG_ON_MSG((माप(VARIABLE) %  माप(u32)) != 0,\
			 "Unaligned get length " # ITEM);\
	hw_atl2_mअगर_shared_buf_get(HW, \
		(दुरत्व(काष्ठा fw_पूर्णांकerface_in, ITEM) / माप(u32)),\
		(u32 *)&(VARIABLE), \
		माप(VARIABLE) / माप(u32));\
पूर्ण

/* This should never be used on non atomic fields,
 * treat any > u32 पढ़ो as non atomic.
 */
#घोषणा hw_atl2_shared_buffer_पढ़ो(HW, ITEM, VARIABLE) \
अणु\
	BUILD_BUG_ON_MSG((दुरत्व(काष्ठा fw_पूर्णांकerface_out, ITEM) % \
			 माप(u32)) != 0,\
			 "Unaligned read " # ITEM);\
	BUILD_BUG_ON_MSG((माप(VARIABLE) %  माप(u32)) != 0,\
			 "Unaligned read length " # ITEM);\
	BUILD_BUG_ON_MSG(माप(VARIABLE) > माप(u32),\
			 "Non atomic read " # ITEM);\
	hw_atl2_mअगर_shared_buf_पढ़ो(HW, \
		(दुरत्व(काष्ठा fw_पूर्णांकerface_out, ITEM) / माप(u32)),\
		(u32 *)&(VARIABLE), माप(VARIABLE) / माप(u32));\
पूर्ण

#घोषणा hw_atl2_shared_buffer_पढ़ो_safe(HW, ITEM, DATA) \
(अणु\
	BUILD_BUG_ON_MSG((दुरत्व(काष्ठा fw_पूर्णांकerface_out, ITEM) % \
			 माप(u32)) != 0,\
			 "Unaligned read_safe " # ITEM);\
	BUILD_BUG_ON_MSG((माप(((काष्ठा fw_पूर्णांकerface_out *)0)->ITEM) % \
			 माप(u32)) != 0,\
			 "Unaligned read_safe length " # ITEM);\
	hw_atl2_shared_buffer_पढ़ो_block((HW), \
		(दुरत्व(काष्ठा fw_पूर्णांकerface_out, ITEM) / माप(u32)),\
		माप(((काष्ठा fw_पूर्णांकerface_out *)0)->ITEM) / माप(u32),\
		(DATA));\
पूर्ण)

अटल पूर्णांक hw_atl2_shared_buffer_पढ़ो_block(काष्ठा aq_hw_s *self,
					    u32 offset, u32 dwords, व्योम *data)
अणु
	काष्ठा transaction_counter_s tid1, tid2;
	पूर्णांक cnt = 0;

	करो अणु
		करो अणु
			hw_atl2_shared_buffer_पढ़ो(self, transaction_id, tid1);
			cnt++;
			अगर (cnt > AQ_A2_FW_READ_TRY_MAX)
				वापस -ETIME;
			अगर (tid1.transaction_cnt_a != tid1.transaction_cnt_b)
				udelay(1);
		पूर्ण जबतक (tid1.transaction_cnt_a != tid1.transaction_cnt_b);

		hw_atl2_mअगर_shared_buf_पढ़ो(self, offset, (u32 *)data, dwords);

		hw_atl2_shared_buffer_पढ़ो(self, transaction_id, tid2);

		cnt++;
		अगर (cnt > AQ_A2_FW_READ_TRY_MAX)
			वापस -ETIME;
	पूर्ण जबतक (tid2.transaction_cnt_a != tid2.transaction_cnt_b ||
		 tid1.transaction_cnt_a != tid2.transaction_cnt_a);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hw_atl2_shared_buffer_finish_ack(काष्ठा aq_hw_s *self)
अणु
	u32 val;
	पूर्णांक err;

	hw_atl2_mअगर_host_finished_ग_लिखो_set(self, 1U);
	err = पढ़ोx_poll_समयout_atomic(hw_atl2_mअगर_mcp_finished_पढ़ो_get,
					self, val, val == 0U,
					100, 100000U);
	WARN(err, "hw_atl2_shared_buffer_finish_ack");

	वापस err;
पूर्ण

अटल पूर्णांक aq_a2_fw_init(काष्ठा aq_hw_s *self)
अणु
	काष्ठा link_control_s link_control;
	u32 mtu;
	u32 val;
	पूर्णांक err;

	hw_atl2_shared_buffer_get(self, link_control, link_control);
	link_control.mode = AQ_HOST_MODE_ACTIVE;
	hw_atl2_shared_buffer_ग_लिखो(self, link_control, link_control);

	hw_atl2_shared_buffer_get(self, mtu, mtu);
	mtu = HW_ATL2_MTU_JUMBO;
	hw_atl2_shared_buffer_ग_लिखो(self, mtu, mtu);

	hw_atl2_mअगर_host_finished_ग_लिखो_set(self, 1U);
	err = पढ़ोx_poll_समयout_atomic(hw_atl2_mअगर_mcp_finished_पढ़ो_get,
					self, val, val == 0U,
					100, 5000000U);
	WARN(err, "hw_atl2_shared_buffer_finish_ack");

	वापस err;
पूर्ण

अटल पूर्णांक aq_a2_fw_deinit(काष्ठा aq_hw_s *self)
अणु
	काष्ठा link_control_s link_control;

	hw_atl2_shared_buffer_get(self, link_control, link_control);
	link_control.mode = AQ_HOST_MODE_SHUTDOWN;
	hw_atl2_shared_buffer_ग_लिखो(self, link_control, link_control);

	वापस hw_atl2_shared_buffer_finish_ack(self);
पूर्ण

अटल व्योम a2_link_speed_mask2fw(u32 speed,
				  काष्ठा link_options_s *link_options)
अणु
	link_options->rate_10G = !!(speed & AQ_NIC_RATE_10G);
	link_options->rate_5G = !!(speed & AQ_NIC_RATE_5G);
	link_options->rate_N5G = !!(speed & AQ_NIC_RATE_5GSR);
	link_options->rate_2P5G = !!(speed & AQ_NIC_RATE_2G5);
	link_options->rate_N2P5G = link_options->rate_2P5G;
	link_options->rate_1G = !!(speed & AQ_NIC_RATE_1G);
	link_options->rate_100M = !!(speed & AQ_NIC_RATE_100M);
	link_options->rate_10M = !!(speed & AQ_NIC_RATE_10M);

	link_options->rate_1G_hd = !!(speed & AQ_NIC_RATE_1G_HALF);
	link_options->rate_100M_hd = !!(speed & AQ_NIC_RATE_100M_HALF);
	link_options->rate_10M_hd = !!(speed & AQ_NIC_RATE_10M_HALF);
पूर्ण

अटल u32 a2_fw_dev_to_eee_mask(काष्ठा device_link_caps_s *device_link_caps)
अणु
	u32 rate = 0;

	अगर (device_link_caps->eee_10G)
		rate |= AQ_NIC_RATE_EEE_10G;
	अगर (device_link_caps->eee_5G)
		rate |= AQ_NIC_RATE_EEE_5G;
	अगर (device_link_caps->eee_2P5G)
		rate |= AQ_NIC_RATE_EEE_2G5;
	अगर (device_link_caps->eee_1G)
		rate |= AQ_NIC_RATE_EEE_1G;
	अगर (device_link_caps->eee_100M)
		rate |= AQ_NIC_RATE_EEE_100M;

	वापस rate;
पूर्ण

अटल u32 a2_fw_lkp_to_mask(काष्ठा lkp_link_caps_s *lkp_link_caps)
अणु
	u32 rate = 0;

	अगर (lkp_link_caps->rate_10G)
		rate |= AQ_NIC_RATE_10G;
	अगर (lkp_link_caps->rate_5G)
		rate |= AQ_NIC_RATE_5G;
	अगर (lkp_link_caps->rate_N5G)
		rate |= AQ_NIC_RATE_5GSR;
	अगर (lkp_link_caps->rate_2P5G)
		rate |= AQ_NIC_RATE_2G5;
	अगर (lkp_link_caps->rate_1G)
		rate |= AQ_NIC_RATE_1G;
	अगर (lkp_link_caps->rate_1G_hd)
		rate |= AQ_NIC_RATE_1G_HALF;
	अगर (lkp_link_caps->rate_100M)
		rate |= AQ_NIC_RATE_100M;
	अगर (lkp_link_caps->rate_100M_hd)
		rate |= AQ_NIC_RATE_100M_HALF;
	अगर (lkp_link_caps->rate_10M)
		rate |= AQ_NIC_RATE_10M;
	अगर (lkp_link_caps->rate_10M_hd)
		rate |= AQ_NIC_RATE_10M_HALF;

	अगर (lkp_link_caps->eee_10G)
		rate |= AQ_NIC_RATE_EEE_10G;
	अगर (lkp_link_caps->eee_5G)
		rate |= AQ_NIC_RATE_EEE_5G;
	अगर (lkp_link_caps->eee_2P5G)
		rate |= AQ_NIC_RATE_EEE_2G5;
	अगर (lkp_link_caps->eee_1G)
		rate |= AQ_NIC_RATE_EEE_1G;
	अगर (lkp_link_caps->eee_100M)
		rate |= AQ_NIC_RATE_EEE_100M;

	वापस rate;
पूर्ण

अटल पूर्णांक aq_a2_fw_set_link_speed(काष्ठा aq_hw_s *self, u32 speed)
अणु
	काष्ठा link_options_s link_options;

	hw_atl2_shared_buffer_get(self, link_options, link_options);
	link_options.link_up = 1U;
	a2_link_speed_mask2fw(speed, &link_options);
	hw_atl2_shared_buffer_ग_लिखो(self, link_options, link_options);

	वापस hw_atl2_shared_buffer_finish_ack(self);
पूर्ण

अटल व्योम aq_a2_fw_set_mpi_flow_control(काष्ठा aq_hw_s *self,
					  काष्ठा link_options_s *link_options)
अणु
	u32 flow_control = self->aq_nic_cfg->fc.req;

	link_options->छोड़ो_rx = !!(flow_control & AQ_NIC_FC_RX);
	link_options->छोड़ो_tx = !!(flow_control & AQ_NIC_FC_TX);
पूर्ण

अटल व्योम aq_a2_fw_upd_eee_rate_bits(काष्ठा aq_hw_s *self,
				       काष्ठा link_options_s *link_options,
				       u32 eee_speeds)
अणु
	link_options->eee_10G =  !!(eee_speeds & AQ_NIC_RATE_EEE_10G);
	link_options->eee_5G = !!(eee_speeds & AQ_NIC_RATE_EEE_5G);
	link_options->eee_2P5G = !!(eee_speeds & AQ_NIC_RATE_EEE_2G5);
	link_options->eee_1G = !!(eee_speeds & AQ_NIC_RATE_EEE_1G);
	link_options->eee_100M = !!(eee_speeds & AQ_NIC_RATE_EEE_100M);
पूर्ण

अटल पूर्णांक aq_a2_fw_set_state(काष्ठा aq_hw_s *self,
			      क्रमागत hal_atl_utils_fw_state_e state)
अणु
	काष्ठा link_options_s link_options;

	hw_atl2_shared_buffer_get(self, link_options, link_options);

	चयन (state) अणु
	हाल MPI_INIT:
		link_options.link_up = 1U;
		aq_a2_fw_upd_eee_rate_bits(self, &link_options,
					   self->aq_nic_cfg->eee_speeds);
		aq_a2_fw_set_mpi_flow_control(self, &link_options);
		अवरोध;
	हाल MPI_DEINIT:
		link_options.link_up = 0U;
		अवरोध;
	हाल MPI_RESET:
	हाल MPI_POWER:
		/* No actions */
		अवरोध;
	पूर्ण

	hw_atl2_shared_buffer_ग_लिखो(self, link_options, link_options);

	वापस hw_atl2_shared_buffer_finish_ack(self);
पूर्ण

अटल पूर्णांक aq_a2_fw_update_link_status(काष्ठा aq_hw_s *self)
अणु
	काष्ठा lkp_link_caps_s lkp_link_caps;
	काष्ठा link_status_s link_status;

	hw_atl2_shared_buffer_पढ़ो(self, link_status, link_status);

	चयन (link_status.link_rate) अणु
	हाल AQ_A2_FW_LINK_RATE_10G:
		self->aq_link_status.mbps = 10000;
		अवरोध;
	हाल AQ_A2_FW_LINK_RATE_5G:
		self->aq_link_status.mbps = 5000;
		अवरोध;
	हाल AQ_A2_FW_LINK_RATE_2G5:
		self->aq_link_status.mbps = 2500;
		अवरोध;
	हाल AQ_A2_FW_LINK_RATE_1G:
		self->aq_link_status.mbps = 1000;
		अवरोध;
	हाल AQ_A2_FW_LINK_RATE_100M:
		self->aq_link_status.mbps = 100;
		अवरोध;
	हाल AQ_A2_FW_LINK_RATE_10M:
		self->aq_link_status.mbps = 10;
		अवरोध;
	शेष:
		self->aq_link_status.mbps = 0;
	पूर्ण
	self->aq_link_status.full_duplex = link_status.duplex;

	hw_atl2_shared_buffer_पढ़ो(self, lkp_link_caps, lkp_link_caps);

	self->aq_link_status.lp_link_speed_msk =
				 a2_fw_lkp_to_mask(&lkp_link_caps);
	self->aq_link_status.lp_flow_control =
				((lkp_link_caps.छोड़ो_rx) ? AQ_NIC_FC_RX : 0) |
				((lkp_link_caps.छोड़ो_tx) ? AQ_NIC_FC_TX : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_a2_fw_get_mac_permanent(काष्ठा aq_hw_s *self, u8 *mac)
अणु
	काष्ठा mac_address_aligned_s mac_address;

	hw_atl2_shared_buffer_get(self, mac_address, mac_address);
	ether_addr_copy(mac, (u8 *)mac_address.aligned.mac_address);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_a2_fw_update_stats(काष्ठा aq_hw_s *self)
अणु
	काष्ठा hw_atl2_priv *priv = (काष्ठा hw_atl2_priv *)self->priv;
	काष्ठा statistics_s stats;

	hw_atl2_shared_buffer_पढ़ो_safe(self, stats, &stats);

#घोषणा AQ_SDELTA(_N_, _F_) (self->curr_stats._N_ += \
			stats.msm._F_ - priv->last_stats.msm._F_)

	अगर (self->aq_link_status.mbps) अणु
		AQ_SDELTA(uprc, rx_unicast_frames);
		AQ_SDELTA(mprc, rx_multicast_frames);
		AQ_SDELTA(bprc, rx_broadcast_frames);
		AQ_SDELTA(erpr, rx_error_frames);

		AQ_SDELTA(uptc, tx_unicast_frames);
		AQ_SDELTA(mptc, tx_multicast_frames);
		AQ_SDELTA(bptc, tx_broadcast_frames);
		AQ_SDELTA(erpt, tx_errors);

		AQ_SDELTA(ubrc, rx_unicast_octets);
		AQ_SDELTA(ubtc, tx_unicast_octets);
		AQ_SDELTA(mbrc, rx_multicast_octets);
		AQ_SDELTA(mbtc, tx_multicast_octets);
		AQ_SDELTA(bbrc, rx_broadcast_octets);
		AQ_SDELTA(bbtc, tx_broadcast_octets);
	पूर्ण
#अघोषित AQ_SDELTA
	self->curr_stats.dma_pkt_rc =
		hw_atl_stats_rx_dma_good_pkt_counter_get(self);
	self->curr_stats.dma_pkt_tc =
		hw_atl_stats_tx_dma_good_pkt_counter_get(self);
	self->curr_stats.dma_oct_rc =
		hw_atl_stats_rx_dma_good_octet_counter_get(self);
	self->curr_stats.dma_oct_tc =
		hw_atl_stats_tx_dma_good_octet_counter_get(self);
	self->curr_stats.dpc = hw_atl_rpb_rx_dma_drop_pkt_cnt_get(self);

	स_नकल(&priv->last_stats, &stats, माप(stats));

	वापस 0;
पूर्ण

अटल पूर्णांक aq_a2_fw_get_phy_temp(काष्ठा aq_hw_s *self, पूर्णांक *temp)
अणु
	काष्ठा phy_health_monitor_s phy_health_monitor;

	hw_atl2_shared_buffer_पढ़ो_safe(self, phy_health_monitor,
					&phy_health_monitor);

	*temp = (पूर्णांक8_t)phy_health_monitor.phy_temperature * 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक aq_a2_fw_get_mac_temp(काष्ठा aq_hw_s *self, पूर्णांक *temp)
अणु
	/* There's only one temperature sensor on A2, use it क्रम
	 * both MAC and PHY.
	 */
	वापस aq_a2_fw_get_phy_temp(self, temp);
पूर्ण

अटल पूर्णांक aq_a2_fw_set_eee_rate(काष्ठा aq_hw_s *self, u32 speed)
अणु
	काष्ठा link_options_s link_options;

	hw_atl2_shared_buffer_get(self, link_options, link_options);

	aq_a2_fw_upd_eee_rate_bits(self, &link_options, speed);

	hw_atl2_shared_buffer_ग_लिखो(self, link_options, link_options);

	वापस hw_atl2_shared_buffer_finish_ack(self);
पूर्ण

अटल पूर्णांक aq_a2_fw_get_eee_rate(काष्ठा aq_hw_s *self, u32 *rate,
				 u32 *supported_rates)
अणु
	काष्ठा device_link_caps_s device_link_caps;
	काष्ठा lkp_link_caps_s lkp_link_caps;

	hw_atl2_shared_buffer_पढ़ो(self, device_link_caps, device_link_caps);
	hw_atl2_shared_buffer_पढ़ो(self, lkp_link_caps, lkp_link_caps);

	*supported_rates = a2_fw_dev_to_eee_mask(&device_link_caps);
	*rate = a2_fw_lkp_to_mask(&lkp_link_caps);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_a2_fw_renegotiate(काष्ठा aq_hw_s *self)
अणु
	काष्ठा link_options_s link_options;
	पूर्णांक err;

	hw_atl2_shared_buffer_get(self, link_options, link_options);
	link_options.link_renegotiate = 1U;
	hw_atl2_shared_buffer_ग_लिखो(self, link_options, link_options);

	err = hw_atl2_shared_buffer_finish_ack(self);

	/* We should put renegotiate status back to zero
	 * after command completes
	 */
	link_options.link_renegotiate = 0U;
	hw_atl2_shared_buffer_ग_लिखो(self, link_options, link_options);

	वापस err;
पूर्ण

अटल पूर्णांक aq_a2_fw_set_flow_control(काष्ठा aq_hw_s *self)
अणु
	काष्ठा link_options_s link_options;

	hw_atl2_shared_buffer_get(self, link_options, link_options);

	aq_a2_fw_set_mpi_flow_control(self, &link_options);

	hw_atl2_shared_buffer_ग_लिखो(self, link_options, link_options);

	वापस hw_atl2_shared_buffer_finish_ack(self);
पूर्ण

अटल u32 aq_a2_fw_get_flow_control(काष्ठा aq_hw_s *self, u32 *fcmode)
अणु
	काष्ठा link_status_s link_status;

	hw_atl2_shared_buffer_पढ़ो(self, link_status, link_status);

	*fcmode = ((link_status.छोड़ो_rx) ? AQ_NIC_FC_RX : 0) |
		  ((link_status.छोड़ो_tx) ? AQ_NIC_FC_TX : 0);
	वापस 0;
पूर्ण

अटल पूर्णांक aq_a2_fw_set_phyloopback(काष्ठा aq_hw_s *self, u32 mode, bool enable)
अणु
	काष्ठा link_options_s link_options;

	hw_atl2_shared_buffer_get(self, link_options, link_options);

	चयन (mode) अणु
	हाल AQ_HW_LOOPBACK_PHYINT_SYS:
		link_options.पूर्णांकernal_loopback = enable;
		अवरोध;
	हाल AQ_HW_LOOPBACK_PHYEXT_SYS:
		link_options.बाह्यal_loopback = enable;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	hw_atl2_shared_buffer_ग_लिखो(self, link_options, link_options);

	वापस hw_atl2_shared_buffer_finish_ack(self);
पूर्ण

u32 hw_atl2_utils_get_fw_version(काष्ठा aq_hw_s *self)
अणु
	काष्ठा version_s version;

	hw_atl2_shared_buffer_पढ़ो_safe(self, version, &version);

	/* A2 FW version is stored in reverse order */
	वापस version.mac.major << 24 |
	       version.mac.minor << 16 |
	       version.mac.build;
पूर्ण

पूर्णांक hw_atl2_utils_get_action_resolve_table_caps(काष्ठा aq_hw_s *self,
						u8 *base_index, u8 *count)
अणु
	काष्ठा filter_caps_s filter_caps;
	पूर्णांक err;

	err = hw_atl2_shared_buffer_पढ़ो_safe(self, filter_caps, &filter_caps);
	अगर (err)
		वापस err;

	*base_index = filter_caps.rslv_tbl_base_index;
	*count = filter_caps.rslv_tbl_count;
	वापस 0;
पूर्ण

अटल पूर्णांक aq_a2_fw_set_करोwnshअगरt(काष्ठा aq_hw_s *self, u32 counter)
अणु
	काष्ठा link_options_s link_options;

	hw_atl2_shared_buffer_get(self, link_options, link_options);
	link_options.करोwnshअगरt = !!counter;
	link_options.करोwnshअगरt_retry = counter;
	hw_atl2_shared_buffer_ग_लिखो(self, link_options, link_options);

	वापस hw_atl2_shared_buffer_finish_ack(self);
पूर्ण

स्थिर काष्ठा aq_fw_ops aq_a2_fw_ops = अणु
	.init               = aq_a2_fw_init,
	.deinit             = aq_a2_fw_deinit,
	.reset              = शून्य,
	.renegotiate        = aq_a2_fw_renegotiate,
	.get_mac_permanent  = aq_a2_fw_get_mac_permanent,
	.set_link_speed     = aq_a2_fw_set_link_speed,
	.set_state          = aq_a2_fw_set_state,
	.update_link_status = aq_a2_fw_update_link_status,
	.update_stats       = aq_a2_fw_update_stats,
	.get_mac_temp       = aq_a2_fw_get_mac_temp,
	.get_phy_temp       = aq_a2_fw_get_phy_temp,
	.set_eee_rate       = aq_a2_fw_set_eee_rate,
	.get_eee_rate       = aq_a2_fw_get_eee_rate,
	.set_flow_control   = aq_a2_fw_set_flow_control,
	.get_flow_control   = aq_a2_fw_get_flow_control,
	.set_phyloopback    = aq_a2_fw_set_phyloopback,
	.set_करोwnshअगरt      = aq_a2_fw_set_करोwnshअगरt,
पूर्ण;
