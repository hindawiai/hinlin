<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AMD Memory Encryption Support
 *
 * Copyright (C) 2016 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 */

#अगर_अघोषित __MEM_ENCRYPT_H__
#घोषणा __MEM_ENCRYPT_H__

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_ARCH_HAS_MEM_ENCRYPT

#समावेश <यंत्र/mem_encrypt.h>

#अन्यथा	/* !CONFIG_ARCH_HAS_MEM_ENCRYPT */

अटल अंतरभूत bool mem_encrypt_active(व्योम) अणु वापस false; पूर्ण

#पूर्ण_अगर	/* CONFIG_ARCH_HAS_MEM_ENCRYPT */

#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
/*
 * The __sme_set() and __sme_clr() macros are useful क्रम adding or removing
 * the encryption mask from a value (e.g. when dealing with pagetable
 * entries).
 */
#घोषणा __sme_set(x)		((x) | sme_me_mask)
#घोषणा __sme_clr(x)		((x) & ~sme_me_mask)
#अन्यथा
#घोषणा __sme_set(x)		(x)
#घोषणा __sme_clr(x)		(x)
#पूर्ण_अगर

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर	/* __MEM_ENCRYPT_H__ */
