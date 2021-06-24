<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2019-2020 The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित _ATH11K_PCI_H
#घोषणा _ATH11K_PCI_H

#समावेश <linux/mhi.h>

#समावेश "core.h"

#घोषणा PCIE_SOC_GLOBAL_RESET			0x3008
#घोषणा PCIE_SOC_GLOBAL_RESET_V			1

#घोषणा WLAON_WARM_SW_ENTRY			0x1f80504
#घोषणा WLAON_SOC_RESET_CAUSE_REG		0x01f8060c

#घोषणा PCIE_Q6_COOKIE_ADDR			0x01f80500
#घोषणा PCIE_Q6_COOKIE_DATA			0xc0000000

/* रेजिस्टर to wake the UMAC from घातer collapse */
#घोषणा PCIE_SCRATCH_0_SOC_PCIE_REG		0x4040

/* रेजिस्टर used क्रम handshake mechanism to validate UMAC is awake */
#घोषणा PCIE_SOC_WAKE_PCIE_LOCAL_REG		0x3004

#घोषणा PCIE_PCIE_PARF_LTSSM			0x1e081b0
#घोषणा PARM_LTSSM_VALUE			0x111

#घोषणा GCC_GCC_PCIE_HOT_RST			0x1e402bc
#घोषणा GCC_GCC_PCIE_HOT_RST_VAL		0x10

#घोषणा PCIE_PCIE_INT_ALL_CLEAR			0x1e08228
#घोषणा PCIE_SMLH_REQ_RST_LINK_DOWN		0x2
#घोषणा PCIE_INT_CLEAR_ALL			0xffffffff

#घोषणा PCIE_QSERDES_COM_SYSCLK_EN_SEL_REG(x) \
		(ab->hw_params.regs->pcie_qserdes_sysclk_en_sel)
#घोषणा PCIE_QSERDES_COM_SYSCLK_EN_SEL_VAL	0x10
#घोषणा PCIE_QSERDES_COM_SYSCLK_EN_SEL_MSK	0xffffffff
#घोषणा PCIE_PCS_OSC_DTCT_CONFIG1_REG(x) \
		(ab->hw_params.regs->pcie_pcs_osc_dtct_config_base)
#घोषणा PCIE_PCS_OSC_DTCT_CONFIG1_VAL		0x02
#घोषणा PCIE_PCS_OSC_DTCT_CONFIG2_REG(x) \
		(ab->hw_params.regs->pcie_pcs_osc_dtct_config_base + 0x4)
#घोषणा PCIE_PCS_OSC_DTCT_CONFIG2_VAL		0x52
#घोषणा PCIE_PCS_OSC_DTCT_CONFIG4_REG(x) \
		(ab->hw_params.regs->pcie_pcs_osc_dtct_config_base + 0xc)
#घोषणा PCIE_PCS_OSC_DTCT_CONFIG4_VAL		0xff
#घोषणा PCIE_PCS_OSC_DTCT_CONFIG_MSK		0x000000ff

#घोषणा WLAON_QFPROM_PWR_CTRL_REG		0x01f8031c
#घोषणा QFPROM_PWR_CTRL_VDD4BLOW_MASK		0x4

काष्ठा ath11k_msi_user अणु
	अक्षर *name;
	पूर्णांक num_vectors;
	u32 base_vector;
पूर्ण;

काष्ठा ath11k_msi_config अणु
	पूर्णांक total_vectors;
	पूर्णांक total_users;
	काष्ठा ath11k_msi_user *users;
पूर्ण;

क्रमागत ath11k_pci_flags अणु
	ATH11K_PCI_FLAG_INIT_DONE,
	ATH11K_PCI_FLAG_IS_MSI_64,
	ATH11K_PCI_ASPM_RESTORE,
पूर्ण;

काष्ठा ath11k_pci अणु
	काष्ठा pci_dev *pdev;
	काष्ठा ath11k_base *ab;
	u16 dev_id;
	अक्षर amss_path[100];
	u32 msi_ep_base_data;
	काष्ठा mhi_controller *mhi_ctrl;
	स्थिर काष्ठा ath11k_msi_config *msi_config;
	अचिन्हित दीर्घ mhi_state;
	u32 रेजिस्टर_winकरोw;

	/* protects रेजिस्टर_winकरोw above */
	spinlock_t winकरोw_lock;

	/* क्रमागत ath11k_pci_flags */
	अचिन्हित दीर्घ flags;
	u16 link_ctl;
पूर्ण;

अटल अंतरभूत काष्ठा ath11k_pci *ath11k_pci_priv(काष्ठा ath11k_base *ab)
अणु
	वापस (काष्ठा ath11k_pci *)ab->drv_priv;
पूर्ण

पूर्णांक ath11k_pci_get_user_msi_assignment(काष्ठा ath11k_pci *ar_pci, अक्षर *user_name,
				       पूर्णांक *num_vectors, u32 *user_base_data,
				       u32 *base_vector);
पूर्णांक ath11k_pci_get_msi_irq(काष्ठा device *dev, अचिन्हित पूर्णांक vector);
व्योम ath11k_pci_ग_लिखो32(काष्ठा ath11k_base *ab, u32 offset, u32 value);
u32 ath11k_pci_पढ़ो32(काष्ठा ath11k_base *ab, u32 offset);

#पूर्ण_अगर
