<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SWIOTLB_H
#घोषणा _ASM_X86_SWIOTLB_H

#समावेश <linux/swiotlb.h>

#अगर_घोषित CONFIG_SWIOTLB
बाह्य पूर्णांक swiotlb;
बाह्य पूर्णांक __init pci_swiotlb_detect_override(व्योम);
बाह्य पूर्णांक __init pci_swiotlb_detect_4gb(व्योम);
बाह्य व्योम __init pci_swiotlb_init(व्योम);
बाह्य व्योम __init pci_swiotlb_late_init(व्योम);
#अन्यथा
#घोषणा swiotlb 0
अटल अंतरभूत पूर्णांक pci_swiotlb_detect_override(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pci_swiotlb_detect_4gb(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम pci_swiotlb_init(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम pci_swiotlb_late_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_X86_SWIOTLB_H */
