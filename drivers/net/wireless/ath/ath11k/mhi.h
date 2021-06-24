<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2020 The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित _ATH11K_MHI_H
#घोषणा _ATH11K_MHI_H

#समावेश "pci.h"

#घोषणा PCIE_TXVECDB				0x360
#घोषणा PCIE_TXVECSTATUS			0x368
#घोषणा PCIE_RXVECDB				0x394
#घोषणा PCIE_RXVECSTATUS			0x39C

#घोषणा MHISTATUS				0x48
#घोषणा MHICTRL					0x38
#घोषणा MHICTRL_RESET_MASK			0x2

क्रमागत ath11k_mhi_state अणु
	ATH11K_MHI_INIT,
	ATH11K_MHI_DEINIT,
	ATH11K_MHI_POWER_ON,
	ATH11K_MHI_POWER_OFF,
	ATH11K_MHI_FORCE_POWER_OFF,
	ATH11K_MHI_SUSPEND,
	ATH11K_MHI_RESUME,
	ATH11K_MHI_TRIGGER_RDDM,
	ATH11K_MHI_RDDM,
	ATH11K_MHI_RDDM_DONE,
पूर्ण;

पूर्णांक ath11k_mhi_start(काष्ठा ath11k_pci *ar_pci);
व्योम ath11k_mhi_stop(काष्ठा ath11k_pci *ar_pci);
पूर्णांक ath11k_mhi_रेजिस्टर(काष्ठा ath11k_pci *ar_pci);
व्योम ath11k_mhi_unरेजिस्टर(काष्ठा ath11k_pci *ar_pci);
व्योम ath11k_mhi_set_mhictrl_reset(काष्ठा ath11k_base *ab);
व्योम ath11k_mhi_clear_vector(काष्ठा ath11k_base *ab);

व्योम ath11k_mhi_suspend(काष्ठा ath11k_pci *ar_pci);
व्योम ath11k_mhi_resume(काष्ठा ath11k_pci *ar_pci);

#पूर्ण_अगर
