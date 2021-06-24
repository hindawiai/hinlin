<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Marvell OcteonTx2 RVU Ethernet driver
 *
 * Copyright (C) 2020 Marvell.
 */

#अगर_अघोषित CN10K_H
#घोषणा CN10K_H

#समावेश "otx2_common.h"

व्योम cn10k_refill_pool_ptrs(व्योम *dev, काष्ठा otx2_cq_queue *cq);
व्योम cn10k_sqe_flush(व्योम *dev, काष्ठा otx2_snd_queue *sq, पूर्णांक size, पूर्णांक qidx);
पूर्णांक cn10k_sq_aq_init(व्योम *dev, u16 qidx, u16 sqb_aura);
पूर्णांक cn10k_pf_lmtst_init(काष्ठा otx2_nic *pf);
पूर्णांक cn10k_vf_lmtst_init(काष्ठा otx2_nic *vf);
#पूर्ण_अगर /* CN10K_H */
