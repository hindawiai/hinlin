<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/lockdep.h>
#समावेश <मानककोष.स>

/* Trivial API wrappers, we करोn't (yet) have RCU in user-space: */
#घोषणा hlist_क्रम_each_entry_rcu	hlist_क्रम_each_entry
#घोषणा hlist_add_head_rcu		hlist_add_head
#घोषणा hlist_del_rcu			hlist_del
#घोषणा list_क्रम_each_entry_rcu		list_क्रम_each_entry
#घोषणा list_add_tail_rcu		list_add_tail

u32 pअक्रमom_u32(व्योम)
अणु
	/* Used only by lock_pin_lock() which is dead code */
	पात();
पूर्ण

व्योम prपूर्णांक_irqtrace_events(काष्ठा task_काष्ठा *curr)
अणु
	पात();
पूर्ण

अटल काष्ठा new_utsname *init_utsname(व्योम)
अणु
	अटल काष्ठा new_utsname n = (काष्ठा new_utsname) अणु
		.release = "liblockdep",
		.version = LIBLOCKDEP_VERSION,
	पूर्ण;

	वापस &n;
पूर्ण

#समावेश "../../../kernel/locking/lockdep.c"
