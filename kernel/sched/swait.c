<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * <linux/sरुको.h> (simple रुको queues ) implementation:
 */
#समावेश "sched.h"

व्योम __init_sरुको_queue_head(काष्ठा sरुको_queue_head *q, स्थिर अक्षर *name,
			     काष्ठा lock_class_key *key)
अणु
	raw_spin_lock_init(&q->lock);
	lockdep_set_class_and_name(&q->lock, key, name);
	INIT_LIST_HEAD(&q->task_list);
पूर्ण
EXPORT_SYMBOL(__init_sरुको_queue_head);

/*
 * The thing about the wake_up_state() वापस value; I think we can ignore it.
 *
 * If क्रम some reason it would वापस 0, that means the previously रुकोing
 * task is alपढ़ोy running, so it will observe condition true (or has alपढ़ोy).
 */
व्योम swake_up_locked(काष्ठा sरुको_queue_head *q)
अणु
	काष्ठा sरुको_queue *curr;

	अगर (list_empty(&q->task_list))
		वापस;

	curr = list_first_entry(&q->task_list, typeof(*curr), task_list);
	wake_up_process(curr->task);
	list_del_init(&curr->task_list);
पूर्ण
EXPORT_SYMBOL(swake_up_locked);

/*
 * Wake up all रुकोers. This is an पूर्णांकerface which is solely exposed क्रम
 * completions and not क्रम general usage.
 *
 * It is पूर्णांकentionally dअगरferent from swake_up_all() to allow usage from
 * hard पूर्णांकerrupt context and पूर्णांकerrupt disabled regions.
 */
व्योम swake_up_all_locked(काष्ठा sरुको_queue_head *q)
अणु
	जबतक (!list_empty(&q->task_list))
		swake_up_locked(q);
पूर्ण

व्योम swake_up_one(काष्ठा sरुको_queue_head *q)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&q->lock, flags);
	swake_up_locked(q);
	raw_spin_unlock_irqrestore(&q->lock, flags);
पूर्ण
EXPORT_SYMBOL(swake_up_one);

/*
 * Does not allow usage from IRQ disabled, since we must be able to
 * release IRQs to guarantee bounded hold समय.
 */
व्योम swake_up_all(काष्ठा sरुको_queue_head *q)
अणु
	काष्ठा sरुको_queue *curr;
	LIST_HEAD(पंचांगp);

	raw_spin_lock_irq(&q->lock);
	list_splice_init(&q->task_list, &पंचांगp);
	जबतक (!list_empty(&पंचांगp)) अणु
		curr = list_first_entry(&पंचांगp, typeof(*curr), task_list);

		wake_up_state(curr->task, TASK_NORMAL);
		list_del_init(&curr->task_list);

		अगर (list_empty(&पंचांगp))
			अवरोध;

		raw_spin_unlock_irq(&q->lock);
		raw_spin_lock_irq(&q->lock);
	पूर्ण
	raw_spin_unlock_irq(&q->lock);
पूर्ण
EXPORT_SYMBOL(swake_up_all);

व्योम __prepare_to_sरुको(काष्ठा sरुको_queue_head *q, काष्ठा sरुको_queue *रुको)
अणु
	रुको->task = current;
	अगर (list_empty(&रुको->task_list))
		list_add_tail(&रुको->task_list, &q->task_list);
पूर्ण

व्योम prepare_to_sरुको_exclusive(काष्ठा sरुको_queue_head *q, काष्ठा sरुको_queue *रुको, पूर्णांक state)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&q->lock, flags);
	__prepare_to_sरुको(q, रुको);
	set_current_state(state);
	raw_spin_unlock_irqrestore(&q->lock, flags);
पूर्ण
EXPORT_SYMBOL(prepare_to_sरुको_exclusive);

दीर्घ prepare_to_sरुको_event(काष्ठा sरुको_queue_head *q, काष्ठा sरुको_queue *रुको, पूर्णांक state)
अणु
	अचिन्हित दीर्घ flags;
	दीर्घ ret = 0;

	raw_spin_lock_irqsave(&q->lock, flags);
	अगर (संकेत_pending_state(state, current)) अणु
		/*
		 * See prepare_to_रुको_event(). TL;DR, subsequent swake_up_one()
		 * must not see us.
		 */
		list_del_init(&रुको->task_list);
		ret = -ERESTARTSYS;
	पूर्ण अन्यथा अणु
		__prepare_to_sरुको(q, रुको);
		set_current_state(state);
	पूर्ण
	raw_spin_unlock_irqrestore(&q->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(prepare_to_sरुको_event);

व्योम __finish_sरुको(काष्ठा sरुको_queue_head *q, काष्ठा sरुको_queue *रुको)
अणु
	__set_current_state(TASK_RUNNING);
	अगर (!list_empty(&रुको->task_list))
		list_del_init(&रुको->task_list);
पूर्ण

व्योम finish_sरुको(काष्ठा sरुको_queue_head *q, काष्ठा sरुको_queue *रुको)
अणु
	अचिन्हित दीर्घ flags;

	__set_current_state(TASK_RUNNING);

	अगर (!list_empty_careful(&रुको->task_list)) अणु
		raw_spin_lock_irqsave(&q->lock, flags);
		list_del_init(&रुको->task_list);
		raw_spin_unlock_irqrestore(&q->lock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(finish_sरुको);
