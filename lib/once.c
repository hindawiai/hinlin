<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/once.h>
#समावेश <linux/अक्रमom.h>

काष्ठा once_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा अटल_key_true *key;
पूर्ण;

अटल व्योम once_deferred(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा once_work *work;

	work = container_of(w, काष्ठा once_work, work);
	BUG_ON(!अटल_key_enabled(work->key));
	अटल_branch_disable(work->key);
	kमुक्त(work);
पूर्ण

अटल व्योम once_disable_jump(काष्ठा अटल_key_true *key)
अणु
	काष्ठा once_work *w;

	w = kदो_स्मृति(माप(*w), GFP_ATOMIC);
	अगर (!w)
		वापस;

	INIT_WORK(&w->work, once_deferred);
	w->key = key;
	schedule_work(&w->work);
पूर्ण

अटल DEFINE_SPINLOCK(once_lock);

bool __करो_once_start(bool *करोne, अचिन्हित दीर्घ *flags)
	__acquires(once_lock)
अणु
	spin_lock_irqsave(&once_lock, *flags);
	अगर (*करोne) अणु
		spin_unlock_irqrestore(&once_lock, *flags);
		/* Keep sparse happy by restoring an even lock count on
		 * this lock. In हाल we वापस here, we करोn't call पूर्णांकo
		 * __करो_once_करोne but वापस early in the DO_ONCE() macro.
		 */
		__acquire(once_lock);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(__करो_once_start);

व्योम __करो_once_करोne(bool *करोne, काष्ठा अटल_key_true *once_key,
		    अचिन्हित दीर्घ *flags)
	__releases(once_lock)
अणु
	*करोne = true;
	spin_unlock_irqrestore(&once_lock, *flags);
	once_disable_jump(once_key);
पूर्ण
EXPORT_SYMBOL(__करो_once_करोne);
