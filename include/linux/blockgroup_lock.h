<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BLOCKGROUP_LOCK_H
#घोषणा _LINUX_BLOCKGROUP_LOCK_H
/*
 * Per-blockgroup locking क्रम ext2 and ext3.
 *
 * Simple hashed spinlocking.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/cache.h>

#अगर_घोषित CONFIG_SMP
#घोषणा NR_BG_LOCKS	(4 << ilog2(NR_CPUS < 32 ? NR_CPUS : 32))
#अन्यथा
#घोषणा NR_BG_LOCKS	1
#पूर्ण_अगर

काष्ठा bgl_lock अणु
	spinlock_t lock;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा blockgroup_lock अणु
	काष्ठा bgl_lock locks[NR_BG_LOCKS];
पूर्ण;

अटल अंतरभूत व्योम bgl_lock_init(काष्ठा blockgroup_lock *bgl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_BG_LOCKS; i++)
		spin_lock_init(&bgl->locks[i].lock);
पूर्ण

अटल अंतरभूत spinlock_t *
bgl_lock_ptr(काष्ठा blockgroup_lock *bgl, अचिन्हित पूर्णांक block_group)
अणु
	वापस &bgl->locks[block_group & (NR_BG_LOCKS-1)].lock;
पूर्ण

#पूर्ण_अगर
