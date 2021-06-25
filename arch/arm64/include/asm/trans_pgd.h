<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Copyright (c) 2020, Microsoft Corporation.
 * Pavel Tatashin <pasha.tatashin@soleen.com>
 */

#अगर_अघोषित _ASM_TRANS_TABLE_H
#घोषणा _ASM_TRANS_TABLE_H

#समावेश <linux/bits.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/pgtable-types.h>

/*
 * trans_alloc_page
 *	- Allocator that should वापस exactly one zeroed page, अगर this
 *	  allocator fails, trans_pgd_create_copy() and trans_pgd_map_page()
 *	  वापस -ENOMEM error.
 *
 * trans_alloc_arg
 *	- Passed to trans_alloc_page as an argument
 */

काष्ठा trans_pgd_info अणु
	व्योम * (*trans_alloc_page)(व्योम *arg);
	व्योम *trans_alloc_arg;
पूर्ण;

पूर्णांक trans_pgd_create_copy(काष्ठा trans_pgd_info *info, pgd_t **trans_pgd,
			  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

पूर्णांक trans_pgd_map_page(काष्ठा trans_pgd_info *info, pgd_t *trans_pgd,
		       व्योम *page, अचिन्हित दीर्घ dst_addr, pgprot_t pgprot);

पूर्णांक trans_pgd_idmap_page(काष्ठा trans_pgd_info *info, phys_addr_t *trans_ttbr0,
			 अचिन्हित दीर्घ *t0sz, व्योम *page);

#पूर्ण_अगर /* _ASM_TRANS_TABLE_H */
