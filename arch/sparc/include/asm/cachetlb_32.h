<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_CACHETLB_H
#घोषणा _SPARC_CACHETLB_H

काष्ठा mm_काष्ठा;
काष्ठा vm_area_काष्ठा;

काष्ठा sparc32_cachetlb_ops अणु
	व्योम (*cache_all)(व्योम);
	व्योम (*cache_mm)(काष्ठा mm_काष्ठा *);
	व्योम (*cache_range)(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ,
			    अचिन्हित दीर्घ);
	व्योम (*cache_page)(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ);

	व्योम (*tlb_all)(व्योम);
	व्योम (*tlb_mm)(काष्ठा mm_काष्ठा *);
	व्योम (*tlb_range)(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ,
			  अचिन्हित दीर्घ);
	व्योम (*tlb_page)(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ);

	व्योम (*page_to_ram)(अचिन्हित दीर्घ);
	व्योम (*sig_insns)(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ);
	व्योम (*page_क्रम_dma)(अचिन्हित दीर्घ);
पूर्ण;
बाह्य स्थिर काष्ठा sparc32_cachetlb_ops *sparc32_cachetlb_ops;
#अगर_घोषित CONFIG_SMP
बाह्य स्थिर काष्ठा sparc32_cachetlb_ops *local_ops;
#पूर्ण_अगर

#पूर्ण_अगर /* SPARC_CACHETLB_H */
