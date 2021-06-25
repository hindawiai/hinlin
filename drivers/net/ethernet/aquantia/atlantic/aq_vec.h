<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_vec.h: Definition of common काष्ठाures क्रम vector of Rx and Tx rings.
 * Declaration of functions क्रम Rx and Tx rings.
 */

#अगर_अघोषित AQ_VEC_H
#घोषणा AQ_VEC_H

#समावेश "aq_common.h"
#समावेश <linux/irqवापस.h>

काष्ठा aq_hw_s;
काष्ठा aq_hw_ops;
काष्ठा aq_nic_s;
काष्ठा aq_nic_cfg_s;
काष्ठा aq_ring_stats_rx_s;
काष्ठा aq_ring_stats_tx_s;

irqवापस_t aq_vec_isr(पूर्णांक irq, व्योम *निजी);
irqवापस_t aq_vec_isr_legacy(पूर्णांक irq, व्योम *निजी);
काष्ठा aq_vec_s *aq_vec_alloc(काष्ठा aq_nic_s *aq_nic, अचिन्हित पूर्णांक idx,
			      काष्ठा aq_nic_cfg_s *aq_nic_cfg);
पूर्णांक aq_vec_ring_alloc(काष्ठा aq_vec_s *self, काष्ठा aq_nic_s *aq_nic,
		      अचिन्हित पूर्णांक idx, काष्ठा aq_nic_cfg_s *aq_nic_cfg);
पूर्णांक aq_vec_init(काष्ठा aq_vec_s *self, स्थिर काष्ठा aq_hw_ops *aq_hw_ops,
		काष्ठा aq_hw_s *aq_hw);
व्योम aq_vec_deinit(काष्ठा aq_vec_s *self);
व्योम aq_vec_मुक्त(काष्ठा aq_vec_s *self);
व्योम aq_vec_ring_मुक्त(काष्ठा aq_vec_s *self);
पूर्णांक aq_vec_start(काष्ठा aq_vec_s *self);
व्योम aq_vec_stop(काष्ठा aq_vec_s *self);
cpumask_t *aq_vec_get_affinity_mask(काष्ठा aq_vec_s *self);
bool aq_vec_is_valid_tc(काष्ठा aq_vec_s *self, स्थिर अचिन्हित पूर्णांक tc);
अचिन्हित पूर्णांक aq_vec_get_sw_stats(काष्ठा aq_vec_s *self, स्थिर अचिन्हित पूर्णांक tc, u64 *data);

#पूर्ण_अगर /* AQ_VEC_H */
