<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel MID specअगरic setup code
 *
 * (C) Copyright 2009, 2021 Intel Corporation
 */
#अगर_अघोषित _ASM_X86_INTEL_MID_H
#घोषणा _ASM_X86_INTEL_MID_H

#समावेश <linux/pci.h>

बाह्य पूर्णांक पूर्णांकel_mid_pci_init(व्योम);
बाह्य पूर्णांक पूर्णांकel_mid_pci_set_घातer_state(काष्ठा pci_dev *pdev, pci_घातer_t state);
बाह्य pci_घातer_t पूर्णांकel_mid_pci_get_घातer_state(काष्ठा pci_dev *pdev);

बाह्य व्योम पूर्णांकel_mid_pwr_घातer_off(व्योम);

#घोषणा INTEL_MID_PWR_LSS_OFFSET	4
#घोषणा INTEL_MID_PWR_LSS_TYPE		(1 << 7)

बाह्य पूर्णांक पूर्णांकel_mid_pwr_get_lss_id(काष्ठा pci_dev *pdev);

#अगर_घोषित CONFIG_X86_INTEL_MID

बाह्य व्योम पूर्णांकel_scu_devices_create(व्योम);
बाह्य व्योम पूर्णांकel_scu_devices_destroy(व्योम);

#अन्यथा /* !CONFIG_X86_INTEL_MID */

अटल अंतरभूत व्योम पूर्णांकel_scu_devices_create(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम पूर्णांकel_scu_devices_destroy(व्योम) अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_X86_INTEL_MID */

/* Bus Select SoC Fuse value */
#घोषणा BSEL_SOC_FUSE_MASK		0x7
/* FSB 133MHz */
#घोषणा BSEL_SOC_FUSE_001		0x1
/* FSB 100MHz */
#घोषणा BSEL_SOC_FUSE_101		0x5
/* FSB 83MHz */
#घोषणा BSEL_SOC_FUSE_111		0x7

#पूर्ण_अगर /* _ASM_X86_INTEL_MID_H */
