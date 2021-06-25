<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_MM_INIT_H
#घोषणा _SPARC64_MM_INIT_H

#समावेश <यंत्र/page.h>

/* Most of the symbols in this file are defined in init.c and
 * marked non-अटल so that assembler code can get at them.
 */

#घोषणा MAX_PHYS_ADDRESS	(1UL << MAX_PHYS_ADDRESS_BITS)

बाह्य अचिन्हित दीर्घ kern_linear_pte_xor[4];
बाह्य अचिन्हित पूर्णांक sparc64_highest_unlocked_tlb_ent;
बाह्य अचिन्हित दीर्घ sparc64_kern_pri_context;
बाह्य अचिन्हित दीर्घ sparc64_kern_pri_nuc_bits;
बाह्य अचिन्हित दीर्घ sparc64_kern_sec_context;
व्योम mmu_info(काष्ठा seq_file *m);

काष्ठा linux_prom_translation अणु
	अचिन्हित दीर्घ virt;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ data;
पूर्ण;

/* Exported क्रम kernel TLB miss handling in ktlb.S */
बाह्य काष्ठा linux_prom_translation prom_trans[512];
बाह्य अचिन्हित पूर्णांक prom_trans_ents;

/* Exported क्रम SMP bootup purposes. */
बाह्य अचिन्हित दीर्घ kern_locked_tte_data;

व्योम prom_world(पूर्णांक enter);

#पूर्ण_अगर /* _SPARC64_MM_INIT_H */
