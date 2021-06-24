<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SWAP_SLOTS_H
#घोषणा _LINUX_SWAP_SLOTS_H

#समावेश <linux/swap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>

#घोषणा SWAP_SLOTS_CACHE_SIZE			SWAP_BATCH
#घोषणा THRESHOLD_ACTIVATE_SWAP_SLOTS_CACHE	(5*SWAP_SLOTS_CACHE_SIZE)
#घोषणा THRESHOLD_DEACTIVATE_SWAP_SLOTS_CACHE	(2*SWAP_SLOTS_CACHE_SIZE)

काष्ठा swap_slots_cache अणु
	bool		lock_initialized;
	काष्ठा mutex	alloc_lock; /* protects slots, nr, cur */
	swp_entry_t	*slots;
	पूर्णांक		nr;
	पूर्णांक		cur;
	spinlock_t	मुक्त_lock;  /* protects slots_ret, n_ret */
	swp_entry_t	*slots_ret;
	पूर्णांक		n_ret;
पूर्ण;

व्योम disable_swap_slots_cache_lock(व्योम);
व्योम reenable_swap_slots_cache_unlock(व्योम);
व्योम enable_swap_slots_cache(व्योम);
पूर्णांक मुक्त_swap_slot(swp_entry_t entry);

बाह्य bool swap_slot_cache_enabled;

#पूर्ण_अगर /* _LINUX_SWAP_SLOTS_H */
