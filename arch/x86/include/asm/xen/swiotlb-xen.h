<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SWIOTLB_XEN_H
#घोषणा _ASM_X86_SWIOTLB_XEN_H

#अगर_घोषित CONFIG_SWIOTLB_XEN
बाह्य पूर्णांक xen_swiotlb;
बाह्य पूर्णांक __init pci_xen_swiotlb_detect(व्योम);
बाह्य व्योम __init pci_xen_swiotlb_init(व्योम);
बाह्य पूर्णांक pci_xen_swiotlb_init_late(व्योम);
#अन्यथा
#घोषणा xen_swiotlb (0)
अटल अंतरभूत पूर्णांक __init pci_xen_swiotlb_detect(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम __init pci_xen_swiotlb_init(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_xen_swiotlb_init_late(व्योम) अणु वापस -ENXIO; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_SWIOTLB_XEN_H */
