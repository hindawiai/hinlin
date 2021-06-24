<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"
#समावेश "mount.h"

अटल DEFINE_SPINLOCK(pin_lock);

व्योम pin_हटाओ(काष्ठा fs_pin *pin)
अणु
	spin_lock(&pin_lock);
	hlist_del_init(&pin->m_list);
	hlist_del_init(&pin->s_list);
	spin_unlock(&pin_lock);
	spin_lock_irq(&pin->रुको.lock);
	pin->करोne = 1;
	wake_up_locked(&pin->रुको);
	spin_unlock_irq(&pin->रुको.lock);
पूर्ण

व्योम pin_insert(काष्ठा fs_pin *pin, काष्ठा vfsmount *m)
अणु
	spin_lock(&pin_lock);
	hlist_add_head(&pin->s_list, &m->mnt_sb->s_pins);
	hlist_add_head(&pin->m_list, &real_mount(m)->mnt_pins);
	spin_unlock(&pin_lock);
पूर्ण

व्योम pin_समाप्त(काष्ठा fs_pin *p)
अणु
	रुको_queue_entry_t रुको;

	अगर (!p) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	init_रुको(&रुको);
	spin_lock_irq(&p->रुको.lock);
	अगर (likely(!p->करोne)) अणु
		p->करोne = -1;
		spin_unlock_irq(&p->रुको.lock);
		rcu_पढ़ो_unlock();
		p->समाप्त(p);
		वापस;
	पूर्ण
	अगर (p->करोne > 0) अणु
		spin_unlock_irq(&p->रुको.lock);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	__add_रुको_queue(&p->रुको, &रुको);
	जबतक (1) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&p->रुको.lock);
		rcu_पढ़ो_unlock();
		schedule();
		rcu_पढ़ो_lock();
		अगर (likely(list_empty(&रुको.entry)))
			अवरोध;
		/* OK, we know p couldn't have been मुक्तd yet */
		spin_lock_irq(&p->रुको.lock);
		अगर (p->करोne > 0) अणु
			spin_unlock_irq(&p->रुको.lock);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम mnt_pin_समाप्त(काष्ठा mount *m)
अणु
	जबतक (1) अणु
		काष्ठा hlist_node *p;
		rcu_पढ़ो_lock();
		p = READ_ONCE(m->mnt_pins.first);
		अगर (!p) अणु
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण
		pin_समाप्त(hlist_entry(p, काष्ठा fs_pin, m_list));
	पूर्ण
पूर्ण

व्योम group_pin_समाप्त(काष्ठा hlist_head *p)
अणु
	जबतक (1) अणु
		काष्ठा hlist_node *q;
		rcu_पढ़ो_lock();
		q = READ_ONCE(p->first);
		अगर (!q) अणु
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण
		pin_समाप्त(hlist_entry(q, काष्ठा fs_pin, s_list));
	पूर्ण
पूर्ण
