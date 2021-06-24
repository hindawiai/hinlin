<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PASEMI_PASEMI_H
#घोषणा _PASEMI_PASEMI_H

बाह्य समय64_t pas_get_boot_समय(व्योम);
बाह्य व्योम pas_pci_init(व्योम);
बाह्य व्योम pas_pci_irq_fixup(काष्ठा pci_dev *dev);
बाह्य व्योम pas_pci_dma_dev_setup(काष्ठा pci_dev *dev);

बाह्य व्योम __iomem *pasemi_pci_अ_लोfgaddr(काष्ठा pci_dev *dev, पूर्णांक offset);

बाह्य व्योम __init pasemi_map_रेजिस्टरs(व्योम);

/* Power savings modes, implemented in यंत्र */
बाह्य व्योम idle_spin(व्योम);
बाह्य व्योम idle_करोze(व्योम);

/* Restore astate to last set */
#अगर_घोषित CONFIG_PPC_PASEMI_CPUFREQ
बाह्य पूर्णांक check_astate(व्योम);
बाह्य व्योम restore_astate(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत पूर्णांक check_astate(व्योम)
अणु
	/* Always वापस >0 so we never घातer save */
	वापस 1;
पूर्ण
अटल अंतरभूत व्योम restore_astate(पूर्णांक cpu)
अणु
पूर्ण
#पूर्ण_अगर

बाह्य काष्ठा pci_controller_ops pasemi_pci_controller_ops;

#पूर्ण_अगर /* _PASEMI_PASEMI_H */
