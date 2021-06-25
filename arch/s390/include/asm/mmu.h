<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MMU_H
#घोषणा __MMU_H

#समावेश <linux/cpumask.h>
#समावेश <linux/त्रुटिसं.स>

प्रकार काष्ठा अणु
	spinlock_t lock;
	cpumask_t cpu_attach_mask;
	atomic_t flush_count;
	अचिन्हित पूर्णांक flush_mm;
	काष्ठा list_head pgtable_list;
	काष्ठा list_head gmap_list;
	अचिन्हित दीर्घ gmap_asce;
	अचिन्हित दीर्घ asce;
	अचिन्हित दीर्घ asce_limit;
	अचिन्हित दीर्घ vdso_base;
	/* The mmu context beदीर्घs to a secure guest. */
	atomic_t is_रक्षित;
	/*
	 * The following bitfields need a करोwn_ग_लिखो on the mm
	 * semaphore when they are written to. As they are only
	 * written once, they can be पढ़ो without a lock.
	 *
	 * The mmu context allocates 4K page tables.
	 */
	अचिन्हित पूर्णांक alloc_pgste:1;
	/* The mmu context uses extended page tables. */
	अचिन्हित पूर्णांक has_pgste:1;
	/* The mmu context uses storage keys. */
	अचिन्हित पूर्णांक uses_skeys:1;
	/* The mmu context uses CMM. */
	अचिन्हित पूर्णांक uses_cmm:1;
	/* The gmaps associated with this context are allowed to use huge pages. */
	अचिन्हित पूर्णांक allow_gmap_hpage_1m:1;
पूर्ण mm_context_t;

#घोषणा INIT_MM_CONTEXT(name)						   \
	.context.lock =	__SPIN_LOCK_UNLOCKED(name.context.lock),	   \
	.context.pgtable_list = LIST_HEAD_INIT(name.context.pgtable_list), \
	.context.gmap_list = LIST_HEAD_INIT(name.context.gmap_list),

अटल अंतरभूत पूर्णांक tprot(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक rc = -EFAULT;

	यंत्र अस्थिर(
		"	tprot	0(%1),0\n"
		"0:	ipm	%0\n"
		"	srl	%0,28\n"
		"1:\n"
		EX_TABLE(0b,1b)
		: "+d" (rc) : "a" (addr) : "cc");
	वापस rc;
पूर्ण

#पूर्ण_अगर
