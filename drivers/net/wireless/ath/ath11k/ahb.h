<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित ATH11K_AHB_H
#घोषणा ATH11K_AHB_H

#समावेश "core.h"

#घोषणा ATH11K_AHB_RECOVERY_TIMEOUT (3 * HZ)
काष्ठा ath11k_base;

काष्ठा ath11k_ahb अणु
	काष्ठा rproc *tgt_rproc;
पूर्ण;

अटल अंतरभूत काष्ठा ath11k_ahb *ath11k_ahb_priv(काष्ठा ath11k_base *ab)
अणु
	वापस (काष्ठा ath11k_ahb *)ab->drv_priv;
पूर्ण
#पूर्ण_अगर
