<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2021, Microsoft Corporation. */

#अगर_अघोषित _SHM_CHANNEL_H
#घोषणा _SHM_CHANNEL_H

काष्ठा shm_channel अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
पूर्ण;

व्योम mana_smc_init(काष्ठा shm_channel *sc, काष्ठा device *dev,
		   व्योम __iomem *base);

पूर्णांक mana_smc_setup_hwc(काष्ठा shm_channel *sc, bool reset_vf, u64 eq_addr,
		       u64 cq_addr, u64 rq_addr, u64 sq_addr,
		       u32 eq_msix_index);

पूर्णांक mana_smc_tearकरोwn_hwc(काष्ठा shm_channel *sc, bool reset_vf);

#पूर्ण_अगर /* _SHM_CHANNEL_H */
