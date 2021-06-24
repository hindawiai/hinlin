<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2014 IBM Corp.
 */

#अगर_अघोषित _MISC_CXL_BASE_H
#घोषणा _MISC_CXL_BASE_H

#अगर_घोषित CONFIG_CXL_BASE

#घोषणा CXL_IRQ_RANGES 4

काष्ठा cxl_irq_ranges अणु
	irq_hw_number_t offset[CXL_IRQ_RANGES];
	irq_hw_number_t range[CXL_IRQ_RANGES];
पूर्ण;

बाह्य atomic_t cxl_use_count;

अटल अंतरभूत bool cxl_ctx_in_use(व्योम)
अणु
       वापस (atomic_पढ़ो(&cxl_use_count) != 0);
पूर्ण

अटल अंतरभूत व्योम cxl_ctx_get(व्योम)
अणु
       atomic_inc(&cxl_use_count);
पूर्ण

अटल अंतरभूत व्योम cxl_ctx_put(व्योम)
अणु
       atomic_dec(&cxl_use_count);
पूर्ण

काष्ठा cxl_afu *cxl_afu_get(काष्ठा cxl_afu *afu);
व्योम cxl_afu_put(काष्ठा cxl_afu *afu);
व्योम cxl_slbia(काष्ठा mm_काष्ठा *mm);

#अन्यथा /* CONFIG_CXL_BASE */

अटल अंतरभूत bool cxl_ctx_in_use(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत काष्ठा cxl_afu *cxl_afu_get(काष्ठा cxl_afu *afu) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम cxl_afu_put(काष्ठा cxl_afu *afu) अणुपूर्ण
अटल अंतरभूत व्योम cxl_slbia(काष्ठा mm_काष्ठा *mm) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_CXL_BASE */

#पूर्ण_अगर
