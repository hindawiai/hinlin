<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश <linux/semaphore.h>
#समावेश <linux/atomic.h>

/*
 * Reusable 2 PHASE task barrier (अक्रमevouz poपूर्णांक) implementation क्रम N tasks.
 * Based on the Little book of sempahores - https://greenteapress.com/wp/semaphores/
 */



#अगर_अघोषित DRM_TASK_BARRIER_H_
#घोषणा DRM_TASK_BARRIER_H_

/*
 * Represents an instance of a task barrier.
 */
काष्ठा task_barrier अणु
	अचिन्हित पूर्णांक n;
	atomic_t count;
	काष्ठा semaphore enter_turnstile;
	काष्ठा semaphore निकास_turnstile;
पूर्ण;

अटल अंतरभूत व्योम task_barrier_संकेत_turnstile(काष्ठा semaphore *turnstile,
						 अचिन्हित पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < n; i++)
		up(turnstile);
पूर्ण

अटल अंतरभूत व्योम task_barrier_init(काष्ठा task_barrier *tb)
अणु
	tb->n = 0;
	atomic_set(&tb->count, 0);
	sema_init(&tb->enter_turnstile, 0);
	sema_init(&tb->निकास_turnstile, 0);
पूर्ण

अटल अंतरभूत व्योम task_barrier_add_task(काष्ठा task_barrier *tb)
अणु
	tb->n++;
पूर्ण

अटल अंतरभूत व्योम task_barrier_rem_task(काष्ठा task_barrier *tb)
अणु
	tb->n--;
पूर्ण

/*
 * Lines up all the thपढ़ोs BEFORE the critical poपूर्णांक.
 *
 * When all thपढ़ो passed this code the entry barrier is back to locked state.
 */
अटल अंतरभूत व्योम task_barrier_enter(काष्ठा task_barrier *tb)
अणु
	अगर (atomic_inc_वापस(&tb->count) == tb->n)
		task_barrier_संकेत_turnstile(&tb->enter_turnstile, tb->n);

	करोwn(&tb->enter_turnstile);
पूर्ण

/*
 * Lines up all the thपढ़ोs AFTER the critical poपूर्णांक.
 *
 * This function is used to aव्योम any one thपढ़ो running ahead अगर the barrier is
 *  used repeatedly .
 */
अटल अंतरभूत व्योम task_barrier_निकास(काष्ठा task_barrier *tb)
अणु
	अगर (atomic_dec_वापस(&tb->count) == 0)
		task_barrier_संकेत_turnstile(&tb->निकास_turnstile, tb->n);

	करोwn(&tb->निकास_turnstile);
पूर्ण

/* Convinieince function when nothing to be करोne in between entry and निकास */
अटल अंतरभूत व्योम task_barrier_full(काष्ठा task_barrier *tb)
अणु
	task_barrier_enter(tb);
	task_barrier_निकास(tb);
पूर्ण

#पूर्ण_अगर
