<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File hw_atl_b0.h: Declaration of असलtract पूर्णांकerface क्रम Atlantic hardware
 * specअगरic functions.
 */

#अगर_अघोषित HW_ATL_B0_H
#घोषणा HW_ATL_B0_H

#समावेश "../aq_common.h"

बाह्य स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc100;
बाह्य स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc107;
बाह्य स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc108;
बाह्य स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc109;
बाह्य स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc111;
बाह्य स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc112;

#घोषणा hw_atl_b0_caps_aqc100s hw_atl_b0_caps_aqc100
#घोषणा hw_atl_b0_caps_aqc107s hw_atl_b0_caps_aqc107
#घोषणा hw_atl_b0_caps_aqc108s hw_atl_b0_caps_aqc108
#घोषणा hw_atl_b0_caps_aqc109s hw_atl_b0_caps_aqc109
#घोषणा hw_atl_b0_caps_aqc111s hw_atl_b0_caps_aqc111
#घोषणा hw_atl_b0_caps_aqc112s hw_atl_b0_caps_aqc112

बाह्य स्थिर काष्ठा aq_hw_ops hw_atl_ops_b0;

#घोषणा hw_atl_ops_b1 hw_atl_ops_b0

पूर्णांक hw_atl_b0_hw_rss_hash_set(काष्ठा aq_hw_s *self,
			      काष्ठा aq_rss_parameters *rss_params);
पूर्णांक hw_atl_b0_hw_offload_set(काष्ठा aq_hw_s *self,
			     काष्ठा aq_nic_cfg_s *aq_nic_cfg);

पूर्णांक hw_atl_b0_hw_ring_tx_start(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring);
पूर्णांक hw_atl_b0_hw_ring_rx_start(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring);

पूर्णांक hw_atl_b0_hw_ring_rx_init(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *aq_ring,
			      काष्ठा aq_ring_param_s *aq_ring_param);
पूर्णांक hw_atl_b0_hw_ring_rx_fill(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring,
			      अचिन्हित पूर्णांक sw_tail_old);
पूर्णांक hw_atl_b0_hw_ring_rx_receive(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring);

पूर्णांक hw_atl_b0_hw_ring_tx_init(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *aq_ring,
			      काष्ठा aq_ring_param_s *aq_ring_param);
पूर्णांक hw_atl_b0_hw_ring_tx_xmit(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring,
			      अचिन्हित पूर्णांक frags);
पूर्णांक hw_atl_b0_hw_ring_tx_head_update(काष्ठा aq_hw_s *self,
				     काष्ठा aq_ring_s *ring);

पूर्णांक hw_atl_b0_hw_ring_tx_stop(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring);
पूर्णांक hw_atl_b0_hw_ring_rx_stop(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring);

व्योम hw_atl_b0_hw_init_rx_rss_ctrl1(काष्ठा aq_hw_s *self);

पूर्णांक hw_atl_b0_hw_mac_addr_set(काष्ठा aq_hw_s *self, u8 *mac_addr);

पूर्णांक hw_atl_b0_set_fc(काष्ठा aq_hw_s *self, u32 fc, u32 tc);
पूर्णांक hw_atl_b0_set_loopback(काष्ठा aq_hw_s *self, u32 mode, bool enable);

पूर्णांक hw_atl_b0_hw_start(काष्ठा aq_hw_s *self);

पूर्णांक hw_atl_b0_hw_irq_enable(काष्ठा aq_hw_s *self, u64 mask);
पूर्णांक hw_atl_b0_hw_irq_disable(काष्ठा aq_hw_s *self, u64 mask);
पूर्णांक hw_atl_b0_hw_irq_पढ़ो(काष्ठा aq_hw_s *self, u64 *mask);

पूर्णांक hw_atl_b0_hw_packet_filter_set(काष्ठा aq_hw_s *self,
				   अचिन्हित पूर्णांक packet_filter);

#पूर्ण_अगर /* HW_ATL_B0_H */
