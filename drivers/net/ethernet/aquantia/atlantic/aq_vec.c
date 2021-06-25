<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_vec.c: Definition of common काष्ठाure क्रम vector of Rx and Tx rings.
 * Definition of functions क्रम Rx and Tx rings. Friendly module क्रम aq_nic.
 */

#समावेश "aq_vec.h"
#समावेश "aq_nic.h"
#समावेश "aq_ring.h"
#समावेश "aq_hw.h"

#समावेश <linux/netdevice.h>

काष्ठा aq_vec_s अणु
	स्थिर काष्ठा aq_hw_ops *aq_hw_ops;
	काष्ठा aq_hw_s *aq_hw;
	काष्ठा aq_nic_s *aq_nic;
	अचिन्हित पूर्णांक tx_rings;
	अचिन्हित पूर्णांक rx_rings;
	काष्ठा aq_ring_param_s aq_ring_param;
	काष्ठा napi_काष्ठा napi;
	काष्ठा aq_ring_s ring[AQ_CFG_TCS_MAX][2];
पूर्ण;

#घोषणा AQ_VEC_TX_ID 0
#घोषणा AQ_VEC_RX_ID 1

अटल पूर्णांक aq_vec_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा aq_vec_s *self = container_of(napi, काष्ठा aq_vec_s, napi);
	अचिन्हित पूर्णांक sw_tail_old = 0U;
	काष्ठा aq_ring_s *ring = शून्य;
	bool was_tx_cleaned = true;
	अचिन्हित पूर्णांक i = 0U;
	पूर्णांक work_करोne = 0;
	पूर्णांक err = 0;

	अगर (!self) अणु
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		क्रम (i = 0U, ring = self->ring[0];
			self->tx_rings > i; ++i, ring = self->ring[i]) अणु
			u64_stats_update_begin(&ring[AQ_VEC_RX_ID].stats.rx.syncp);
			ring[AQ_VEC_RX_ID].stats.rx.polls++;
			u64_stats_update_end(&ring[AQ_VEC_RX_ID].stats.rx.syncp);
			अगर (self->aq_hw_ops->hw_ring_tx_head_update) अणु
				err = self->aq_hw_ops->hw_ring_tx_head_update(
							self->aq_hw,
							&ring[AQ_VEC_TX_ID]);
				अगर (err < 0)
					जाओ err_निकास;
			पूर्ण

			अगर (ring[AQ_VEC_TX_ID].sw_head !=
			    ring[AQ_VEC_TX_ID].hw_head) अणु
				was_tx_cleaned = aq_ring_tx_clean(&ring[AQ_VEC_TX_ID]);
				aq_ring_update_queue_state(&ring[AQ_VEC_TX_ID]);
			पूर्ण

			err = self->aq_hw_ops->hw_ring_rx_receive(self->aq_hw,
					    &ring[AQ_VEC_RX_ID]);
			अगर (err < 0)
				जाओ err_निकास;

			अगर (ring[AQ_VEC_RX_ID].sw_head !=
				ring[AQ_VEC_RX_ID].hw_head) अणु
				err = aq_ring_rx_clean(&ring[AQ_VEC_RX_ID],
						       napi,
						       &work_करोne,
						       budget - work_करोne);
				अगर (err < 0)
					जाओ err_निकास;

				sw_tail_old = ring[AQ_VEC_RX_ID].sw_tail;

				err = aq_ring_rx_fill(&ring[AQ_VEC_RX_ID]);
				अगर (err < 0)
					जाओ err_निकास;

				err = self->aq_hw_ops->hw_ring_rx_fill(
					self->aq_hw,
					&ring[AQ_VEC_RX_ID], sw_tail_old);
				अगर (err < 0)
					जाओ err_निकास;
			पूर्ण
		पूर्ण

err_निकास:
		अगर (!was_tx_cleaned)
			work_करोne = budget;

		अगर (work_करोne < budget) अणु
			napi_complete_करोne(napi, work_करोne);
			self->aq_hw_ops->hw_irq_enable(self->aq_hw,
					1U << self->aq_ring_param.vec_idx);
		पूर्ण
	पूर्ण

	वापस work_करोne;
पूर्ण

काष्ठा aq_vec_s *aq_vec_alloc(काष्ठा aq_nic_s *aq_nic, अचिन्हित पूर्णांक idx,
			      काष्ठा aq_nic_cfg_s *aq_nic_cfg)
अणु
	काष्ठा aq_vec_s *self = शून्य;

	self = kzalloc(माप(*self), GFP_KERNEL);
	अगर (!self)
		जाओ err_निकास;

	self->aq_nic = aq_nic;
	self->aq_ring_param.vec_idx = idx;
	self->aq_ring_param.cpu =
		idx + aq_nic_cfg->aq_rss.base_cpu_number;

	cpumask_set_cpu(self->aq_ring_param.cpu,
			&self->aq_ring_param.affinity_mask);

	self->tx_rings = 0;
	self->rx_rings = 0;

	netअगर_napi_add(aq_nic_get_ndev(aq_nic), &self->napi,
		       aq_vec_poll, AQ_CFG_NAPI_WEIGHT);

err_निकास:
	वापस self;
पूर्ण

पूर्णांक aq_vec_ring_alloc(काष्ठा aq_vec_s *self, काष्ठा aq_nic_s *aq_nic,
		      अचिन्हित पूर्णांक idx, काष्ठा aq_nic_cfg_s *aq_nic_cfg)
अणु
	काष्ठा aq_ring_s *ring = शून्य;
	अचिन्हित पूर्णांक i = 0U;
	पूर्णांक err = 0;

	क्रम (i = 0; i < aq_nic_cfg->tcs; ++i) अणु
		स्थिर अचिन्हित पूर्णांक idx_ring = AQ_NIC_CFG_TCVEC2RING(aq_nic_cfg,
								    i, idx);

		ring = aq_ring_tx_alloc(&self->ring[i][AQ_VEC_TX_ID], aq_nic,
					idx_ring, aq_nic_cfg);
		अगर (!ring) अणु
			err = -ENOMEM;
			जाओ err_निकास;
		पूर्ण

		++self->tx_rings;

		aq_nic_set_tx_ring(aq_nic, idx_ring, ring);

		ring = aq_ring_rx_alloc(&self->ring[i][AQ_VEC_RX_ID], aq_nic,
					idx_ring, aq_nic_cfg);
		अगर (!ring) अणु
			err = -ENOMEM;
			जाओ err_निकास;
		पूर्ण

		++self->rx_rings;
	पूर्ण

err_निकास:
	अगर (err < 0) अणु
		aq_vec_ring_मुक्त(self);
		self = शून्य;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक aq_vec_init(काष्ठा aq_vec_s *self, स्थिर काष्ठा aq_hw_ops *aq_hw_ops,
		काष्ठा aq_hw_s *aq_hw)
अणु
	काष्ठा aq_ring_s *ring = शून्य;
	अचिन्हित पूर्णांक i = 0U;
	पूर्णांक err = 0;

	self->aq_hw_ops = aq_hw_ops;
	self->aq_hw = aq_hw;

	क्रम (i = 0U, ring = self->ring[0];
		self->tx_rings > i; ++i, ring = self->ring[i]) अणु
		err = aq_ring_init(&ring[AQ_VEC_TX_ID], ATL_RING_TX);
		अगर (err < 0)
			जाओ err_निकास;

		err = self->aq_hw_ops->hw_ring_tx_init(self->aq_hw,
						       &ring[AQ_VEC_TX_ID],
						       &self->aq_ring_param);
		अगर (err < 0)
			जाओ err_निकास;

		err = aq_ring_init(&ring[AQ_VEC_RX_ID], ATL_RING_RX);
		अगर (err < 0)
			जाओ err_निकास;

		err = self->aq_hw_ops->hw_ring_rx_init(self->aq_hw,
						       &ring[AQ_VEC_RX_ID],
						       &self->aq_ring_param);
		अगर (err < 0)
			जाओ err_निकास;

		err = aq_ring_rx_fill(&ring[AQ_VEC_RX_ID]);
		अगर (err < 0)
			जाओ err_निकास;

		err = self->aq_hw_ops->hw_ring_rx_fill(self->aq_hw,
						       &ring[AQ_VEC_RX_ID], 0U);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण

err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_vec_start(काष्ठा aq_vec_s *self)
अणु
	काष्ठा aq_ring_s *ring = शून्य;
	अचिन्हित पूर्णांक i = 0U;
	पूर्णांक err = 0;

	क्रम (i = 0U, ring = self->ring[0];
		self->tx_rings > i; ++i, ring = self->ring[i]) अणु
		err = self->aq_hw_ops->hw_ring_tx_start(self->aq_hw,
							&ring[AQ_VEC_TX_ID]);
		अगर (err < 0)
			जाओ err_निकास;

		err = self->aq_hw_ops->hw_ring_rx_start(self->aq_hw,
							&ring[AQ_VEC_RX_ID]);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण

	napi_enable(&self->napi);

err_निकास:
	वापस err;
पूर्ण

व्योम aq_vec_stop(काष्ठा aq_vec_s *self)
अणु
	काष्ठा aq_ring_s *ring = शून्य;
	अचिन्हित पूर्णांक i = 0U;

	क्रम (i = 0U, ring = self->ring[0];
		self->tx_rings > i; ++i, ring = self->ring[i]) अणु
		self->aq_hw_ops->hw_ring_tx_stop(self->aq_hw,
						 &ring[AQ_VEC_TX_ID]);

		self->aq_hw_ops->hw_ring_rx_stop(self->aq_hw,
						 &ring[AQ_VEC_RX_ID]);
	पूर्ण

	napi_disable(&self->napi);
पूर्ण

व्योम aq_vec_deinit(काष्ठा aq_vec_s *self)
अणु
	काष्ठा aq_ring_s *ring = शून्य;
	अचिन्हित पूर्णांक i = 0U;

	अगर (!self)
		जाओ err_निकास;

	क्रम (i = 0U, ring = self->ring[0];
		self->tx_rings > i; ++i, ring = self->ring[i]) अणु
		aq_ring_tx_clean(&ring[AQ_VEC_TX_ID]);
		aq_ring_rx_deinit(&ring[AQ_VEC_RX_ID]);
	पूर्ण

err_निकास:;
पूर्ण

व्योम aq_vec_मुक्त(काष्ठा aq_vec_s *self)
अणु
	अगर (!self)
		जाओ err_निकास;

	netअगर_napi_del(&self->napi);

	kमुक्त(self);

err_निकास:;
पूर्ण

व्योम aq_vec_ring_मुक्त(काष्ठा aq_vec_s *self)
अणु
	काष्ठा aq_ring_s *ring = शून्य;
	अचिन्हित पूर्णांक i = 0U;

	अगर (!self)
		जाओ err_निकास;

	क्रम (i = 0U, ring = self->ring[0];
		self->tx_rings > i; ++i, ring = self->ring[i]) अणु
		aq_ring_मुक्त(&ring[AQ_VEC_TX_ID]);
		अगर (i < self->rx_rings)
			aq_ring_मुक्त(&ring[AQ_VEC_RX_ID]);
	पूर्ण

	self->tx_rings = 0;
	self->rx_rings = 0;
err_निकास:;
पूर्ण

irqवापस_t aq_vec_isr(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा aq_vec_s *self = निजी;
	पूर्णांक err = 0;

	अगर (!self) अणु
		err = -EINVAL;
		जाओ err_निकास;
	पूर्ण
	napi_schedule(&self->napi);

err_निकास:
	वापस err >= 0 ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

irqवापस_t aq_vec_isr_legacy(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा aq_vec_s *self = निजी;
	u64 irq_mask = 0U;
	पूर्णांक err;

	अगर (!self)
		वापस IRQ_NONE;
	err = self->aq_hw_ops->hw_irq_पढ़ो(self->aq_hw, &irq_mask);
	अगर (err < 0)
		वापस IRQ_NONE;

	अगर (irq_mask) अणु
		self->aq_hw_ops->hw_irq_disable(self->aq_hw,
			      1U << self->aq_ring_param.vec_idx);
		napi_schedule(&self->napi);
	पूर्ण अन्यथा अणु
		self->aq_hw_ops->hw_irq_enable(self->aq_hw, 1U);
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

cpumask_t *aq_vec_get_affinity_mask(काष्ठा aq_vec_s *self)
अणु
	वापस &self->aq_ring_param.affinity_mask;
पूर्ण

bool aq_vec_is_valid_tc(काष्ठा aq_vec_s *self, स्थिर अचिन्हित पूर्णांक tc)
अणु
	वापस tc < self->rx_rings && tc < self->tx_rings;
पूर्ण

अचिन्हित पूर्णांक aq_vec_get_sw_stats(काष्ठा aq_vec_s *self, स्थिर अचिन्हित पूर्णांक tc, u64 *data)
अणु
	अचिन्हित पूर्णांक count;

	WARN_ONCE(!aq_vec_is_valid_tc(self, tc),
		  "Invalid tc %u (#rx=%u, #tx=%u)\n",
		  tc, self->rx_rings, self->tx_rings);
	अगर (!aq_vec_is_valid_tc(self, tc))
		वापस 0;

	count = aq_ring_fill_stats_data(&self->ring[tc][AQ_VEC_RX_ID], data);
	count += aq_ring_fill_stats_data(&self->ring[tc][AQ_VEC_TX_ID], data + count);

	वापस count;
पूर्ण
