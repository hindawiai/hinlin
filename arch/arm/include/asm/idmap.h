<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_IDMAP_H
#घोषणा __ASM_IDMAP_H

#समावेश <linux/compiler.h>
#समावेश <linux/pgtable.h>

/* Tag a function as requiring to be executed via an identity mapping. */
#घोषणा __idmap __section(".idmap.text") noअंतरभूत notrace

बाह्य pgd_t *idmap_pgd;

व्योम setup_mm_क्रम_reboot(व्योम);

#पूर्ण_अगर	/* __ASM_IDMAP_H */
