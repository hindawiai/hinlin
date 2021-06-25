<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm_types.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/mman.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/atomic.h>
#समावेश <linux/user_namespace.h>
#समावेश <यंत्र/mmu.h>

#अगर_अघोषित INIT_MM_CONTEXT
#घोषणा INIT_MM_CONTEXT(name)
#पूर्ण_अगर

/*
 * For dynamically allocated mm_काष्ठाs, there is a dynamically sized cpumask
 * at the end of the काष्ठाure, the size of which depends on the maximum CPU
 * number the प्रणाली can see. That way we allocate only as much memory क्रम
 * mm_cpumask() as needed क्रम the hundreds, or thousands of processes that
 * a प्रणाली typically runs.
 *
 * Since there is only one init_mm in the entire प्रणाली, keep it simple
 * and size this cpu_biपंचांगask to NR_CPUS.
 */
काष्ठा mm_काष्ठा init_mm = अणु
	.mm_rb		= RB_ROOT,
	.pgd		= swapper_pg_dir,
	.mm_users	= ATOMIC_INIT(2),
	.mm_count	= ATOMIC_INIT(1),
	.ग_लिखो_protect_seq = SEQCNT_ZERO(init_mm.ग_लिखो_protect_seq),
	MMAP_LOCK_INITIALIZER(init_mm)
	.page_table_lock =  __SPIN_LOCK_UNLOCKED(init_mm.page_table_lock),
	.arg_lock	=  __SPIN_LOCK_UNLOCKED(init_mm.arg_lock),
	.mmlist		= LIST_HEAD_INIT(init_mm.mmlist),
	.user_ns	= &init_user_ns,
	.cpu_biपंचांगap	= CPU_BITS_NONE,
	INIT_MM_CONTEXT(init_mm)
पूर्ण;
