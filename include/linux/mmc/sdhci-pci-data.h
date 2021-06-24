<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_MMC_SDHCI_PCI_DATA_H
#घोषणा LINUX_MMC_SDHCI_PCI_DATA_H

काष्ठा pci_dev;

काष्ठा sdhci_pci_data अणु
	काष्ठा pci_dev	*pdev;
	पूर्णांक		slotno;
	पूर्णांक		rst_n_gpio; /* Set to -EINVAL अगर unused */
	पूर्णांक		cd_gpio;    /* Set to -EINVAL अगर unused */
	पूर्णांक		(*setup)(काष्ठा sdhci_pci_data *data);
	व्योम		(*cleanup)(काष्ठा sdhci_pci_data *data);
पूर्ण;

बाह्य काष्ठा sdhci_pci_data *(*sdhci_pci_get_data)(काष्ठा pci_dev *pdev,
				पूर्णांक slotno);
#पूर्ण_अगर
