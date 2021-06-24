<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#अगर_अघोषित DRM_SCHEDULER_SPSC_QUEUE_H_
#घोषणा DRM_SCHEDULER_SPSC_QUEUE_H_

#समावेश <linux/atomic.h>
#समावेश <linux/preempt.h>

/** SPSC lockless queue */

काष्ठा spsc_node अणु

	/* Stores spsc_node* */
	काष्ठा spsc_node *next;
पूर्ण;

काष्ठा spsc_queue अणु

	 काष्ठा spsc_node *head;

	/* atomic poपूर्णांकer to काष्ठा spsc_node* */
	atomic_दीर्घ_t tail;

	atomic_t job_count;
पूर्ण;

अटल अंतरभूत व्योम spsc_queue_init(काष्ठा spsc_queue *queue)
अणु
	queue->head = शून्य;
	atomic_दीर्घ_set(&queue->tail, (दीर्घ)&queue->head);
	atomic_set(&queue->job_count, 0);
पूर्ण

अटल अंतरभूत काष्ठा spsc_node *spsc_queue_peek(काष्ठा spsc_queue *queue)
अणु
	वापस queue->head;
पूर्ण

अटल अंतरभूत पूर्णांक spsc_queue_count(काष्ठा spsc_queue *queue)
अणु
	वापस atomic_पढ़ो(&queue->job_count);
पूर्ण

अटल अंतरभूत bool spsc_queue_push(काष्ठा spsc_queue *queue, काष्ठा spsc_node *node)
अणु
	काष्ठा spsc_node **tail;

	node->next = शून्य;

	preempt_disable();

	tail = (काष्ठा spsc_node **)atomic_दीर्घ_xchg(&queue->tail, (दीर्घ)&node->next);
	WRITE_ONCE(*tail, node);
	atomic_inc(&queue->job_count);

	/*
	 * In हाल of first element verअगरy new node will be visible to the consumer
	 * thपढ़ो when we ping the kernel thपढ़ो that there is new work to करो.
	 */
	smp_wmb();

	preempt_enable();

	वापस tail == &queue->head;
पूर्ण


अटल अंतरभूत काष्ठा spsc_node *spsc_queue_pop(काष्ठा spsc_queue *queue)
अणु
	काष्ठा spsc_node *next, *node;

	/* Verअगरy पढ़ोing from memory and not the cache */
	smp_rmb();

	node = READ_ONCE(queue->head);

	अगर (!node)
		वापस शून्य;

	next = READ_ONCE(node->next);
	WRITE_ONCE(queue->head, next);

	अगर (unlikely(!next)) अणु
		/* slowpath क्रम the last element in the queue */

		अगर (atomic_दीर्घ_cmpxchg(&queue->tail,
				(दीर्घ)&node->next, (दीर्घ) &queue->head) != (दीर्घ)&node->next) अणु
			/* Updating tail failed रुको क्रम new next to appear */
			करो अणु
				smp_rmb();
			पूर्ण जबतक (unlikely(!(queue->head = READ_ONCE(node->next))));
		पूर्ण
	पूर्ण

	atomic_dec(&queue->job_count);
	वापस node;
पूर्ण



#पूर्ण_अगर /* DRM_SCHEDULER_SPSC_QUEUE_H_ */
