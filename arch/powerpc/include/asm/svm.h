<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * SVM helper functions
 *
 * Copyright 2018 Anshuman Khandual, IBM Corporation.
 */

#अगर_अघोषित _ASM_POWERPC_SVM_H
#घोषणा _ASM_POWERPC_SVM_H

#अगर_घोषित CONFIG_PPC_SVM

अटल अंतरभूत bool is_secure_guest(व्योम)
अणु
	वापस mfmsr() & MSR_S;
पूर्ण

व्योम __init svm_swiotlb_init(व्योम);

व्योम dtl_cache_ctor(व्योम *addr);
#घोषणा get_dtl_cache_ctor()	(is_secure_guest() ? dtl_cache_ctor : शून्य)

#अन्यथा /* CONFIG_PPC_SVM */

अटल अंतरभूत bool is_secure_guest(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम svm_swiotlb_init(व्योम) अणुपूर्ण

#घोषणा get_dtl_cache_ctor() शून्य

#पूर्ण_अगर /* CONFIG_PPC_SVM */
#पूर्ण_अगर /* _ASM_POWERPC_SVM_H */
