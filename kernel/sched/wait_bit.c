<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The implementation of the रुको_bit*() and related रुकोing APIs:
 */
#समावेश "sched.h"

#घोषणा WAIT_TABLE_BITS 8
#घोषणा WAIT_TABLE_SIZE (1 << WAIT_TABLE_BITS)

अटल रुको_queue_head_t bit_रुको_table[WAIT_TABLE_SIZE] __cacheline_aligned;

रुको_queue_head_t *bit_रुकोqueue(व्योम *word, पूर्णांक bit)
अणु
	स्थिर पूर्णांक shअगरt = BITS_PER_LONG == 32 ? 5 : 6;
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ)word << shअगरt | bit;

	वापस bit_रुको_table + hash_दीर्घ(val, WAIT_TABLE_BITS);
पूर्ण
EXPORT_SYMBOL(bit_रुकोqueue);

पूर्णांक wake_bit_function(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode, पूर्णांक sync, व्योम *arg)
अणु
	काष्ठा रुको_bit_key *key = arg;
	काष्ठा रुको_bit_queue_entry *रुको_bit = container_of(wq_entry, काष्ठा रुको_bit_queue_entry, wq_entry);

	अगर (रुको_bit->key.flags != key->flags ||
			रुको_bit->key.bit_nr != key->bit_nr ||
			test_bit(key->bit_nr, key->flags))
		वापस 0;

	वापस स्वतःहटाओ_wake_function(wq_entry, mode, sync, key);
पूर्ण
EXPORT_SYMBOL(wake_bit_function);

/*
 * To allow पूर्णांकerruptible रुकोing and asynchronous (i.e. nonblocking)
 * रुकोing, the actions of __रुको_on_bit() and __रुको_on_bit_lock() are
 * permitted वापस codes. Nonzero वापस codes halt रुकोing and वापस.
 */
पूर्णांक __sched
__रुको_on_bit(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_bit_queue_entry *wbq_entry,
	      रुको_bit_action_f *action, अचिन्हित mode)
अणु
	पूर्णांक ret = 0;

	करो अणु
		prepare_to_रुको(wq_head, &wbq_entry->wq_entry, mode);
		अगर (test_bit(wbq_entry->key.bit_nr, wbq_entry->key.flags))
			ret = (*action)(&wbq_entry->key, mode);
	पूर्ण जबतक (test_bit(wbq_entry->key.bit_nr, wbq_entry->key.flags) && !ret);

	finish_रुको(wq_head, &wbq_entry->wq_entry);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(__रुको_on_bit);

पूर्णांक __sched out_of_line_रुको_on_bit(व्योम *word, पूर्णांक bit,
				    रुको_bit_action_f *action, अचिन्हित mode)
अणु
	काष्ठा रुको_queue_head *wq_head = bit_रुकोqueue(word, bit);
	DEFINE_WAIT_BIT(wq_entry, word, bit);

	वापस __रुको_on_bit(wq_head, &wq_entry, action, mode);
पूर्ण
EXPORT_SYMBOL(out_of_line_रुको_on_bit);

पूर्णांक __sched out_of_line_रुको_on_bit_समयout(
	व्योम *word, पूर्णांक bit, रुको_bit_action_f *action,
	अचिन्हित mode, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा रुको_queue_head *wq_head = bit_रुकोqueue(word, bit);
	DEFINE_WAIT_BIT(wq_entry, word, bit);

	wq_entry.key.समयout = jअगरfies + समयout;

	वापस __रुको_on_bit(wq_head, &wq_entry, action, mode);
पूर्ण
EXPORT_SYMBOL_GPL(out_of_line_रुको_on_bit_समयout);

पूर्णांक __sched
__रुको_on_bit_lock(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_bit_queue_entry *wbq_entry,
			रुको_bit_action_f *action, अचिन्हित mode)
अणु
	पूर्णांक ret = 0;

	क्रम (;;) अणु
		prepare_to_रुको_exclusive(wq_head, &wbq_entry->wq_entry, mode);
		अगर (test_bit(wbq_entry->key.bit_nr, wbq_entry->key.flags)) अणु
			ret = action(&wbq_entry->key, mode);
			/*
			 * See the comment in prepare_to_रुको_event().
			 * finish_रुको() करोes not necessarily takes wwq_head->lock,
			 * but test_and_set_bit() implies mb() which pairs with
			 * smp_mb__after_atomic() beक्रमe wake_up_page().
			 */
			अगर (ret)
				finish_रुको(wq_head, &wbq_entry->wq_entry);
		पूर्ण
		अगर (!test_and_set_bit(wbq_entry->key.bit_nr, wbq_entry->key.flags)) अणु
			अगर (!ret)
				finish_रुको(wq_head, &wbq_entry->wq_entry);
			वापस 0;
		पूर्ण अन्यथा अगर (ret) अणु
			वापस ret;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__रुको_on_bit_lock);

पूर्णांक __sched out_of_line_रुको_on_bit_lock(व्योम *word, पूर्णांक bit,
					 रुको_bit_action_f *action, अचिन्हित mode)
अणु
	काष्ठा रुको_queue_head *wq_head = bit_रुकोqueue(word, bit);
	DEFINE_WAIT_BIT(wq_entry, word, bit);

	वापस __रुको_on_bit_lock(wq_head, &wq_entry, action, mode);
पूर्ण
EXPORT_SYMBOL(out_of_line_रुको_on_bit_lock);

व्योम __wake_up_bit(काष्ठा रुको_queue_head *wq_head, व्योम *word, पूर्णांक bit)
अणु
	काष्ठा रुको_bit_key key = __WAIT_BIT_KEY_INITIALIZER(word, bit);

	अगर (रुकोqueue_active(wq_head))
		__wake_up(wq_head, TASK_NORMAL, 1, &key);
पूर्ण
EXPORT_SYMBOL(__wake_up_bit);

/**
 * wake_up_bit - wake up a रुकोer on a bit
 * @word: the word being रुकोed on, a kernel भव address
 * @bit: the bit of the word being रुकोed on
 *
 * There is a standard hashed रुकोqueue table क्रम generic use. This
 * is the part of the hashtable's accessor API that wakes up रुकोers
 * on a bit. For instance, अगर one were to have रुकोers on a bitflag,
 * one would call wake_up_bit() after clearing the bit.
 *
 * In order क्रम this to function properly, as it uses रुकोqueue_active()
 * पूर्णांकernally, some kind of memory barrier must be करोne prior to calling
 * this. Typically, this will be smp_mb__after_atomic(), but in some
 * हालs where bitflags are manipulated non-atomically under a lock, one
 * may need to use a less regular barrier, such fs/inode.c's smp_mb(),
 * because spin_unlock() करोes not guarantee a memory barrier.
 */
व्योम wake_up_bit(व्योम *word, पूर्णांक bit)
अणु
	__wake_up_bit(bit_रुकोqueue(word, bit), word, bit);
पूर्ण
EXPORT_SYMBOL(wake_up_bit);

रुको_queue_head_t *__var_रुकोqueue(व्योम *p)
अणु
	वापस bit_रुको_table + hash_ptr(p, WAIT_TABLE_BITS);
पूर्ण
EXPORT_SYMBOL(__var_रुकोqueue);

अटल पूर्णांक
var_wake_function(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित पूर्णांक mode,
		  पूर्णांक sync, व्योम *arg)
अणु
	काष्ठा रुको_bit_key *key = arg;
	काष्ठा रुको_bit_queue_entry *wbq_entry =
		container_of(wq_entry, काष्ठा रुको_bit_queue_entry, wq_entry);

	अगर (wbq_entry->key.flags != key->flags ||
	    wbq_entry->key.bit_nr != key->bit_nr)
		वापस 0;

	वापस स्वतःहटाओ_wake_function(wq_entry, mode, sync, key);
पूर्ण

व्योम init_रुको_var_entry(काष्ठा रुको_bit_queue_entry *wbq_entry, व्योम *var, पूर्णांक flags)
अणु
	*wbq_entry = (काष्ठा रुको_bit_queue_entry)अणु
		.key = अणु
			.flags	= (var),
			.bit_nr = -1,
		पूर्ण,
		.wq_entry = अणु
			.flags	 = flags,
			.निजी = current,
			.func	 = var_wake_function,
			.entry	 = LIST_HEAD_INIT(wbq_entry->wq_entry.entry),
		पूर्ण,
	पूर्ण;
पूर्ण
EXPORT_SYMBOL(init_रुको_var_entry);

व्योम wake_up_var(व्योम *var)
अणु
	__wake_up_bit(__var_रुकोqueue(var), var, -1);
पूर्ण
EXPORT_SYMBOL(wake_up_var);

__sched पूर्णांक bit_रुको(काष्ठा रुको_bit_key *word, पूर्णांक mode)
अणु
	schedule();
	अगर (संकेत_pending_state(mode, current))
		वापस -EINTR;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(bit_रुको);

__sched पूर्णांक bit_रुको_io(काष्ठा रुको_bit_key *word, पूर्णांक mode)
अणु
	io_schedule();
	अगर (संकेत_pending_state(mode, current))
		वापस -EINTR;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(bit_रुको_io);

__sched पूर्णांक bit_रुको_समयout(काष्ठा रुको_bit_key *word, पूर्णांक mode)
अणु
	अचिन्हित दीर्घ now = READ_ONCE(jअगरfies);

	अगर (समय_after_eq(now, word->समयout))
		वापस -EAGAIN;
	schedule_समयout(word->समयout - now);
	अगर (संकेत_pending_state(mode, current))
		वापस -EINTR;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bit_रुको_समयout);

__sched पूर्णांक bit_रुको_io_समयout(काष्ठा रुको_bit_key *word, पूर्णांक mode)
अणु
	अचिन्हित दीर्घ now = READ_ONCE(jअगरfies);

	अगर (समय_after_eq(now, word->समयout))
		वापस -EAGAIN;
	io_schedule_समयout(word->समयout - now);
	अगर (संकेत_pending_state(mode, current))
		वापस -EINTR;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bit_रुको_io_समयout);

व्योम __init रुको_bit_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < WAIT_TABLE_SIZE; i++)
		init_रुकोqueue_head(bit_रुको_table + i);
पूर्ण
