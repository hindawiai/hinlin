<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * SVM helper functions
 *
 * Copyright 2018 IBM Corporation
 */

#अगर_अघोषित _ASM_POWERPC_MEM_ENCRYPT_H
#घोषणा _ASM_POWERPC_MEM_ENCRYPT_H

#समावेश <यंत्र/svm.h>

अटल अंतरभूत bool mem_encrypt_active(व्योम)
अणु
	वापस is_secure_guest();
पूर्ण

अटल अंतरभूत bool क्रमce_dma_unencrypted(काष्ठा device *dev)
अणु
	वापस is_secure_guest();
पूर्ण

पूर्णांक set_memory_encrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages);
पूर्णांक set_memory_decrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages);

#पूर्ण_अगर /* _ASM_POWERPC_MEM_ENCRYPT_H */
