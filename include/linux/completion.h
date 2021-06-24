<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_COMPLETION_H
#घोषणा __LINUX_COMPLETION_H

/*
 * (C) Copyright 2001 Linus Torvalds
 *
 * Atomic रुको-क्रम-completion handler data काष्ठाures.
 * See kernel/sched/completion.c क्रम details.
 */

#समावेश <linux/sरुको.h>

/*
 * काष्ठा completion - काष्ठाure used to मुख्यtain state क्रम a "completion"
 *
 * This is the opaque काष्ठाure used to मुख्यtain the state क्रम a "completion".
 * Completions currently use a FIFO to queue thपढ़ोs that have to रुको क्रम
 * the "completion" event.
 *
 * See also:  complete(), रुको_क्रम_completion() (and मित्रs _समयout,
 * _पूर्णांकerruptible, _पूर्णांकerruptible_समयout, and _समाप्तable), init_completion(),
 * reinit_completion(), and macros DECLARE_COMPLETION(),
 * DECLARE_COMPLETION_ONSTACK().
 */
काष्ठा completion अणु
	अचिन्हित पूर्णांक करोne;
	काष्ठा sरुको_queue_head रुको;
पूर्ण;

#घोषणा init_completion_map(x, m) init_completion(x)
अटल अंतरभूत व्योम complete_acquire(काष्ठा completion *x) अणुपूर्ण
अटल अंतरभूत व्योम complete_release(काष्ठा completion *x) अणुपूर्ण

#घोषणा COMPLETION_INITIALIZER(work) \
	अणु 0, __SWAIT_QUEUE_HEAD_INITIALIZER((work).रुको) पूर्ण

#घोषणा COMPLETION_INITIALIZER_ONSTACK_MAP(work, map) \
	(*(अणु init_completion_map(&(work), &(map)); &(work); पूर्ण))

#घोषणा COMPLETION_INITIALIZER_ONSTACK(work) \
	(*(अणु init_completion(&work); &work; पूर्ण))

/**
 * DECLARE_COMPLETION - declare and initialize a completion काष्ठाure
 * @work:  identअगरier क्रम the completion काष्ठाure
 *
 * This macro declares and initializes a completion काष्ठाure. Generally used
 * क्रम अटल declarations. You should use the _ONSTACK variant क्रम स्वतःmatic
 * variables.
 */
#घोषणा DECLARE_COMPLETION(work) \
	काष्ठा completion work = COMPLETION_INITIALIZER(work)

/*
 * Lockdep needs to run a non-स्थिरant initializer क्रम on-stack
 * completions - so we use the _ONSTACK() variant क्रम those that
 * are on the kernel stack:
 */
/**
 * DECLARE_COMPLETION_ONSTACK - declare and initialize a completion काष्ठाure
 * @work:  identअगरier क्रम the completion काष्ठाure
 *
 * This macro declares and initializes a completion काष्ठाure on the kernel
 * stack.
 */
#अगर_घोषित CONFIG_LOCKDEP
# define DECLARE_COMPLETION_ONSTACK(work) \
	काष्ठा completion work = COMPLETION_INITIALIZER_ONSTACK(work)
# define DECLARE_COMPLETION_ONSTACK_MAP(work, map) \
	काष्ठा completion work = COMPLETION_INITIALIZER_ONSTACK_MAP(work, map)
#अन्यथा
# define DECLARE_COMPLETION_ONSTACK(work) DECLARE_COMPLETION(work)
# define DECLARE_COMPLETION_ONSTACK_MAP(work, map) DECLARE_COMPLETION(work)
#पूर्ण_अगर

/**
 * init_completion - Initialize a dynamically allocated completion
 * @x:  poपूर्णांकer to completion काष्ठाure that is to be initialized
 *
 * This अंतरभूत function will initialize a dynamically created completion
 * काष्ठाure.
 */
अटल अंतरभूत व्योम init_completion(काष्ठा completion *x)
अणु
	x->करोne = 0;
	init_sरुको_queue_head(&x->रुको);
पूर्ण

/**
 * reinit_completion - reinitialize a completion काष्ठाure
 * @x:  poपूर्णांकer to completion काष्ठाure that is to be reinitialized
 *
 * This अंतरभूत function should be used to reinitialize a completion काष्ठाure so it can
 * be reused. This is especially important after complete_all() is used.
 */
अटल अंतरभूत व्योम reinit_completion(काष्ठा completion *x)
अणु
	x->करोne = 0;
पूर्ण

बाह्य व्योम रुको_क्रम_completion(काष्ठा completion *);
बाह्य व्योम रुको_क्रम_completion_io(काष्ठा completion *);
बाह्य पूर्णांक रुको_क्रम_completion_पूर्णांकerruptible(काष्ठा completion *x);
बाह्य पूर्णांक रुको_क्रम_completion_समाप्तable(काष्ठा completion *x);
बाह्य अचिन्हित दीर्घ रुको_क्रम_completion_समयout(काष्ठा completion *x,
						   अचिन्हित दीर्घ समयout);
बाह्य अचिन्हित दीर्घ रुको_क्रम_completion_io_समयout(काष्ठा completion *x,
						    अचिन्हित दीर्घ समयout);
बाह्य दीर्घ रुको_क्रम_completion_पूर्णांकerruptible_समयout(
	काष्ठा completion *x, अचिन्हित दीर्घ समयout);
बाह्य दीर्घ रुको_क्रम_completion_समाप्तable_समयout(
	काष्ठा completion *x, अचिन्हित दीर्घ समयout);
बाह्य bool try_रुको_क्रम_completion(काष्ठा completion *x);
बाह्य bool completion_करोne(काष्ठा completion *x);

बाह्य व्योम complete(काष्ठा completion *);
बाह्य व्योम complete_all(काष्ठा completion *);

#पूर्ण_अगर
