<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_WAIT_BIT_H
#घोषणा _LINUX_WAIT_BIT_H

/*
 * Linux रुको-bit related types and methods:
 */
#समावेश <linux/रुको.h>

काष्ठा रुको_bit_key अणु
	व्योम			*flags;
	पूर्णांक			bit_nr;
	अचिन्हित दीर्घ		समयout;
पूर्ण;

काष्ठा रुको_bit_queue_entry अणु
	काष्ठा रुको_bit_key	key;
	काष्ठा रुको_queue_entry	wq_entry;
पूर्ण;

#घोषणा __WAIT_BIT_KEY_INITIALIZER(word, bit)					\
	अणु .flags = word, .bit_nr = bit, पूर्ण

प्रकार पूर्णांक रुको_bit_action_f(काष्ठा रुको_bit_key *key, पूर्णांक mode);

व्योम __wake_up_bit(काष्ठा रुको_queue_head *wq_head, व्योम *word, पूर्णांक bit);
पूर्णांक __रुको_on_bit(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_bit_queue_entry *wbq_entry, रुको_bit_action_f *action, अचिन्हित पूर्णांक mode);
पूर्णांक __रुको_on_bit_lock(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_bit_queue_entry *wbq_entry, रुको_bit_action_f *action, अचिन्हित पूर्णांक mode);
व्योम wake_up_bit(व्योम *word, पूर्णांक bit);
पूर्णांक out_of_line_रुको_on_bit(व्योम *word, पूर्णांक, रुको_bit_action_f *action, अचिन्हित पूर्णांक mode);
पूर्णांक out_of_line_रुको_on_bit_समयout(व्योम *word, पूर्णांक, रुको_bit_action_f *action, अचिन्हित पूर्णांक mode, अचिन्हित दीर्घ समयout);
पूर्णांक out_of_line_रुको_on_bit_lock(व्योम *word, पूर्णांक, रुको_bit_action_f *action, अचिन्हित पूर्णांक mode);
काष्ठा रुको_queue_head *bit_रुकोqueue(व्योम *word, पूर्णांक bit);
बाह्य व्योम __init रुको_bit_init(व्योम);

पूर्णांक wake_bit_function(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode, पूर्णांक sync, व्योम *key);

#घोषणा DEFINE_WAIT_BIT(name, word, bit)					\
	काष्ठा रुको_bit_queue_entry name = अणु					\
		.key = __WAIT_BIT_KEY_INITIALIZER(word, bit),			\
		.wq_entry = अणु							\
			.निजी	= current,				\
			.func		= wake_bit_function,			\
			.entry		=					\
				LIST_HEAD_INIT((name).wq_entry.entry),		\
		पूर्ण,								\
	पूर्ण

बाह्य पूर्णांक bit_रुको(काष्ठा रुको_bit_key *key, पूर्णांक mode);
बाह्य पूर्णांक bit_रुको_io(काष्ठा रुको_bit_key *key, पूर्णांक mode);
बाह्य पूर्णांक bit_रुको_समयout(काष्ठा रुको_bit_key *key, पूर्णांक mode);
बाह्य पूर्णांक bit_रुको_io_समयout(काष्ठा रुको_bit_key *key, पूर्णांक mode);

/**
 * रुको_on_bit - रुको क्रम a bit to be cleared
 * @word: the word being रुकोed on, a kernel भव address
 * @bit: the bit of the word being रुकोed on
 * @mode: the task state to sleep in
 *
 * There is a standard hashed रुकोqueue table क्रम generic use. This
 * is the part of the hashtable's accessor API that रुकोs on a bit.
 * For instance, अगर one were to have रुकोers on a bitflag, one would
 * call रुको_on_bit() in thपढ़ोs रुकोing क्रम the bit to clear.
 * One uses रुको_on_bit() where one is रुकोing क्रम the bit to clear,
 * but has no पूर्णांकention of setting it.
 * Returned value will be zero अगर the bit was cleared, or non-zero
 * अगर the process received a संकेत and the mode permitted wakeup
 * on that संकेत.
 */
अटल अंतरभूत पूर्णांक
रुको_on_bit(अचिन्हित दीर्घ *word, पूर्णांक bit, अचिन्हित mode)
अणु
	might_sleep();
	अगर (!test_bit(bit, word))
		वापस 0;
	वापस out_of_line_रुको_on_bit(word, bit,
				       bit_रुको,
				       mode);
पूर्ण

/**
 * रुको_on_bit_io - रुको क्रम a bit to be cleared
 * @word: the word being रुकोed on, a kernel भव address
 * @bit: the bit of the word being रुकोed on
 * @mode: the task state to sleep in
 *
 * Use the standard hashed रुकोqueue table to रुको क्रम a bit
 * to be cleared.  This is similar to रुको_on_bit(), but calls
 * io_schedule() instead of schedule() क्रम the actual रुकोing.
 *
 * Returned value will be zero अगर the bit was cleared, or non-zero
 * अगर the process received a संकेत and the mode permitted wakeup
 * on that संकेत.
 */
अटल अंतरभूत पूर्णांक
रुको_on_bit_io(अचिन्हित दीर्घ *word, पूर्णांक bit, अचिन्हित mode)
अणु
	might_sleep();
	अगर (!test_bit(bit, word))
		वापस 0;
	वापस out_of_line_रुको_on_bit(word, bit,
				       bit_रुको_io,
				       mode);
पूर्ण

/**
 * रुको_on_bit_समयout - रुको क्रम a bit to be cleared or a समयout elapses
 * @word: the word being रुकोed on, a kernel भव address
 * @bit: the bit of the word being रुकोed on
 * @mode: the task state to sleep in
 * @समयout: समयout, in jअगरfies
 *
 * Use the standard hashed रुकोqueue table to रुको क्रम a bit
 * to be cleared. This is similar to रुको_on_bit(), except also takes a
 * समयout parameter.
 *
 * Returned value will be zero अगर the bit was cleared beक्रमe the
 * @समयout elapsed, or non-zero अगर the @समयout elapsed or process
 * received a संकेत and the mode permitted wakeup on that संकेत.
 */
अटल अंतरभूत पूर्णांक
रुको_on_bit_समयout(अचिन्हित दीर्घ *word, पूर्णांक bit, अचिन्हित mode,
		    अचिन्हित दीर्घ समयout)
अणु
	might_sleep();
	अगर (!test_bit(bit, word))
		वापस 0;
	वापस out_of_line_रुको_on_bit_समयout(word, bit,
					       bit_रुको_समयout,
					       mode, समयout);
पूर्ण

/**
 * रुको_on_bit_action - रुको क्रम a bit to be cleared
 * @word: the word being रुकोed on, a kernel भव address
 * @bit: the bit of the word being रुकोed on
 * @action: the function used to sleep, which may take special actions
 * @mode: the task state to sleep in
 *
 * Use the standard hashed रुकोqueue table to रुको क्रम a bit
 * to be cleared, and allow the रुकोing action to be specअगरied.
 * This is like रुको_on_bit() but allows fine control of how the रुकोing
 * is करोne.
 *
 * Returned value will be zero अगर the bit was cleared, or non-zero
 * अगर the process received a संकेत and the mode permitted wakeup
 * on that संकेत.
 */
अटल अंतरभूत पूर्णांक
रुको_on_bit_action(अचिन्हित दीर्घ *word, पूर्णांक bit, रुको_bit_action_f *action,
		   अचिन्हित mode)
अणु
	might_sleep();
	अगर (!test_bit(bit, word))
		वापस 0;
	वापस out_of_line_रुको_on_bit(word, bit, action, mode);
पूर्ण

/**
 * रुको_on_bit_lock - रुको क्रम a bit to be cleared, when wanting to set it
 * @word: the word being रुकोed on, a kernel भव address
 * @bit: the bit of the word being रुकोed on
 * @mode: the task state to sleep in
 *
 * There is a standard hashed रुकोqueue table क्रम generic use. This
 * is the part of the hashtable's accessor API that रुकोs on a bit
 * when one पूर्णांकends to set it, क्रम instance, trying to lock bitflags.
 * For instance, अगर one were to have रुकोers trying to set bitflag
 * and रुकोing क्रम it to clear beक्रमe setting it, one would call
 * रुको_on_bit() in thपढ़ोs रुकोing to be able to set the bit.
 * One uses रुको_on_bit_lock() where one is रुकोing क्रम the bit to
 * clear with the पूर्णांकention of setting it, and when करोne, clearing it.
 *
 * Returns zero अगर the bit was (eventually) found to be clear and was
 * set.  Returns non-zero अगर a संकेत was delivered to the process and
 * the @mode allows that संकेत to wake the process.
 */
अटल अंतरभूत पूर्णांक
रुको_on_bit_lock(अचिन्हित दीर्घ *word, पूर्णांक bit, अचिन्हित mode)
अणु
	might_sleep();
	अगर (!test_and_set_bit(bit, word))
		वापस 0;
	वापस out_of_line_रुको_on_bit_lock(word, bit, bit_रुको, mode);
पूर्ण

/**
 * रुको_on_bit_lock_io - रुको क्रम a bit to be cleared, when wanting to set it
 * @word: the word being रुकोed on, a kernel भव address
 * @bit: the bit of the word being रुकोed on
 * @mode: the task state to sleep in
 *
 * Use the standard hashed रुकोqueue table to रुको क्रम a bit
 * to be cleared and then to atomically set it.  This is similar
 * to रुको_on_bit(), but calls io_schedule() instead of schedule()
 * क्रम the actual रुकोing.
 *
 * Returns zero अगर the bit was (eventually) found to be clear and was
 * set.  Returns non-zero अगर a संकेत was delivered to the process and
 * the @mode allows that संकेत to wake the process.
 */
अटल अंतरभूत पूर्णांक
रुको_on_bit_lock_io(अचिन्हित दीर्घ *word, पूर्णांक bit, अचिन्हित mode)
अणु
	might_sleep();
	अगर (!test_and_set_bit(bit, word))
		वापस 0;
	वापस out_of_line_रुको_on_bit_lock(word, bit, bit_रुको_io, mode);
पूर्ण

/**
 * रुको_on_bit_lock_action - रुको क्रम a bit to be cleared, when wanting to set it
 * @word: the word being रुकोed on, a kernel भव address
 * @bit: the bit of the word being रुकोed on
 * @action: the function used to sleep, which may take special actions
 * @mode: the task state to sleep in
 *
 * Use the standard hashed रुकोqueue table to रुको क्रम a bit
 * to be cleared and then to set it, and allow the रुकोing action
 * to be specअगरied.
 * This is like रुको_on_bit() but allows fine control of how the रुकोing
 * is करोne.
 *
 * Returns zero अगर the bit was (eventually) found to be clear and was
 * set.  Returns non-zero अगर a संकेत was delivered to the process and
 * the @mode allows that संकेत to wake the process.
 */
अटल अंतरभूत पूर्णांक
रुको_on_bit_lock_action(अचिन्हित दीर्घ *word, पूर्णांक bit, रुको_bit_action_f *action,
			अचिन्हित mode)
अणु
	might_sleep();
	अगर (!test_and_set_bit(bit, word))
		वापस 0;
	वापस out_of_line_रुको_on_bit_lock(word, bit, action, mode);
पूर्ण

बाह्य व्योम init_रुको_var_entry(काष्ठा रुको_bit_queue_entry *wbq_entry, व्योम *var, पूर्णांक flags);
बाह्य व्योम wake_up_var(व्योम *var);
बाह्य रुको_queue_head_t *__var_रुकोqueue(व्योम *p);

#घोषणा ___रुको_var_event(var, condition, state, exclusive, ret, cmd)	\
(अणु									\
	__label__ __out;						\
	काष्ठा रुको_queue_head *__wq_head = __var_रुकोqueue(var);	\
	काष्ठा रुको_bit_queue_entry __wbq_entry;			\
	दीर्घ __ret = ret; /* explicit shaकरोw */				\
									\
	init_रुको_var_entry(&__wbq_entry, var,				\
			    exclusive ? WQ_FLAG_EXCLUSIVE : 0);		\
	क्रम (;;) अणु							\
		दीर्घ __पूर्णांक = prepare_to_रुको_event(__wq_head,		\
						   &__wbq_entry.wq_entry, \
						   state);		\
		अगर (condition)						\
			अवरोध;						\
									\
		अगर (___रुको_is_पूर्णांकerruptible(state) && __पूर्णांक) अणु		\
			__ret = __पूर्णांक;					\
			जाओ __out;					\
		पूर्ण							\
									\
		cmd;							\
	पूर्ण								\
	finish_रुको(__wq_head, &__wbq_entry.wq_entry);			\
__out:	__ret;								\
पूर्ण)

#घोषणा __रुको_var_event(var, condition)				\
	___रुको_var_event(var, condition, TASK_UNINTERRUPTIBLE, 0, 0,	\
			  schedule())

#घोषणा रुको_var_event(var, condition)					\
करो अणु									\
	might_sleep();							\
	अगर (condition)							\
		अवरोध;							\
	__रुको_var_event(var, condition);				\
पूर्ण जबतक (0)

#घोषणा __रुको_var_event_समाप्तable(var, condition)			\
	___रुको_var_event(var, condition, TASK_KILLABLE, 0, 0,		\
			  schedule())

#घोषणा रुको_var_event_समाप्तable(var, condition)				\
(अणु									\
	पूर्णांक __ret = 0;							\
	might_sleep();							\
	अगर (!(condition))						\
		__ret = __रुको_var_event_समाप्तable(var, condition);	\
	__ret;								\
पूर्ण)

#घोषणा __रुको_var_event_समयout(var, condition, समयout)		\
	___रुको_var_event(var, ___रुको_cond_समयout(condition),		\
			  TASK_UNINTERRUPTIBLE, 0, समयout,		\
			  __ret = schedule_समयout(__ret))

#घोषणा रुको_var_event_समयout(var, condition, समयout)			\
(अणु									\
	दीर्घ __ret = समयout;						\
	might_sleep();							\
	अगर (!___रुको_cond_समयout(condition))				\
		__ret = __रुको_var_event_समयout(var, condition, समयout); \
	__ret;								\
पूर्ण)

#घोषणा __रुको_var_event_पूर्णांकerruptible(var, condition)			\
	___रुको_var_event(var, condition, TASK_INTERRUPTIBLE, 0, 0,	\
			  schedule())

#घोषणा रुको_var_event_पूर्णांकerruptible(var, condition)			\
(अणु									\
	पूर्णांक __ret = 0;							\
	might_sleep();							\
	अगर (!(condition))						\
		__ret = __रुको_var_event_पूर्णांकerruptible(var, condition);	\
	__ret;								\
पूर्ण)

/**
 * clear_and_wake_up_bit - clear a bit and wake up anyone रुकोing on that bit
 *
 * @bit: the bit of the word being रुकोed on
 * @word: the word being रुकोed on, a kernel भव address
 *
 * You can use this helper अगर bitflags are manipulated atomically rather than
 * non-atomically under a lock.
 */
अटल अंतरभूत व्योम clear_and_wake_up_bit(पूर्णांक bit, व्योम *word)
अणु
	clear_bit_unlock(bit, word);
	/* See wake_up_bit() क्रम which memory barrier you need to use. */
	smp_mb__after_atomic();
	wake_up_bit(word, bit);
पूर्ण

#पूर्ण_अगर /* _LINUX_WAIT_BIT_H */
