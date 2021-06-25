<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_X86_IOMAP_H
#घोषणा _ASM_X86_IOMAP_H

/*
 * Copyright तऊ 2008 Ingo Molnar
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

व्योम __iomem *__iomap_local_pfn_prot(अचिन्हित दीर्घ pfn, pgprot_t prot);

पूर्णांक iomap_create_wc(resource_माप_प्रकार base, अचिन्हित दीर्घ size, pgprot_t *prot);

व्योम iomap_मुक्त(resource_माप_प्रकार base, अचिन्हित दीर्घ size);

#पूर्ण_अगर /* _ASM_X86_IOMAP_H */
