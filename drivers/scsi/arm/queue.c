<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/acorn/scsi/queue.c: queue handling primitives
 *
 *  Copyright (C) 1997-2000 Russell King
 *
 *  Changelog:
 *   15-Sep-1997 RMK	Created.
 *   11-Oct-1997 RMK	Corrected problem with queue_हटाओ_exclude
 *			not updating पूर्णांकernal linked list properly
 *			(was causing commands to go missing).
 *   30-Aug-2000 RMK	Use Linux list handling and spinlocks
 */
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>

#समावेश "../scsi.h"

#घोषणा DEBUG

प्रकार काष्ठा queue_entry अणु
	काष्ठा list_head   list;
	काष्ठा scsi_cmnd   *SCpnt;
#अगर_घोषित DEBUG
	अचिन्हित दीर्घ	   magic;
#पूर्ण_अगर
पूर्ण QE_t;

#अगर_घोषित DEBUG
#घोषणा QUEUE_MAGIC_FREE	0xf7e1c9a3
#घोषणा QUEUE_MAGIC_USED	0xf7e1cc33

#घोषणा SET_MAGIC(q,m)	((q)->magic = (m))
#घोषणा BAD_MAGIC(q,m)	((q)->magic != (m))
#अन्यथा
#घोषणा SET_MAGIC(q,m)	करो अणु पूर्ण जबतक (0)
#घोषणा BAD_MAGIC(q,m)	(0)
#पूर्ण_अगर

#समावेश "queue.h"

#घोषणा NR_QE	32

/*
 * Function: व्योम queue_initialise (Queue_t *queue)
 * Purpose : initialise a queue
 * Params  : queue - queue to initialise
 */
पूर्णांक queue_initialise (Queue_t *queue)
अणु
	अचिन्हित पूर्णांक nqueues = NR_QE;
	QE_t *q;

	spin_lock_init(&queue->queue_lock);
	INIT_LIST_HEAD(&queue->head);
	INIT_LIST_HEAD(&queue->मुक्त);

	/*
	 * If lअगरe was easier, then SCpnt would have a
	 * host-available list head, and we wouldn't
	 * need to keep मुक्त lists or allocate this
	 * memory.
	 */
	queue->alloc = q = kदो_स्मृति_array(nqueues, माप(QE_t), GFP_KERNEL);
	अगर (q) अणु
		क्रम (; nqueues; q++, nqueues--) अणु
			SET_MAGIC(q, QUEUE_MAGIC_FREE);
			q->SCpnt = शून्य;
			list_add(&q->list, &queue->मुक्त);
		पूर्ण
	पूर्ण

	वापस queue->alloc != शून्य;
पूर्ण

/*
 * Function: व्योम queue_मुक्त (Queue_t *queue)
 * Purpose : मुक्त a queue
 * Params  : queue - queue to मुक्त
 */
व्योम queue_मुक्त (Queue_t *queue)
अणु
	अगर (!list_empty(&queue->head))
		prपूर्णांकk(KERN_WARNING "freeing non-empty queue %p\n", queue);
	kमुक्त(queue->alloc);
पूर्ण
     

/*
 * Function: पूर्णांक __queue_add(Queue_t *queue, काष्ठा scsi_cmnd *SCpnt, पूर्णांक head)
 * Purpose : Add a new command onto a queue, adding REQUEST_SENSE to head.
 * Params  : queue - destination queue
 *	     SCpnt - command to add
 *	     head  - add command to head of queue
 * Returns : 0 on error, !0 on success
 */
पूर्णांक __queue_add(Queue_t *queue, काष्ठा scsi_cmnd *SCpnt, पूर्णांक head)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *l;
	QE_t *q;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&queue->queue_lock, flags);
	अगर (list_empty(&queue->मुक्त))
		जाओ empty;

	l = queue->मुक्त.next;
	list_del(l);

	q = list_entry(l, QE_t, list);
	BUG_ON(BAD_MAGIC(q, QUEUE_MAGIC_FREE));

	SET_MAGIC(q, QUEUE_MAGIC_USED);
	q->SCpnt = SCpnt;

	अगर (head)
		list_add(l, &queue->head);
	अन्यथा
		list_add_tail(l, &queue->head);

	ret = 1;
empty:
	spin_unlock_irqrestore(&queue->queue_lock, flags);
	वापस ret;
पूर्ण

अटल काष्ठा scsi_cmnd *__queue_हटाओ(Queue_t *queue, काष्ठा list_head *ent)
अणु
	QE_t *q;

	/*
	 * Move the entry from the "used" list onto the "free" list
	 */
	list_del(ent);
	q = list_entry(ent, QE_t, list);
	BUG_ON(BAD_MAGIC(q, QUEUE_MAGIC_USED));

	SET_MAGIC(q, QUEUE_MAGIC_FREE);
	list_add(ent, &queue->मुक्त);

	वापस q->SCpnt;
पूर्ण

/*
 * Function: काष्ठा scsi_cmnd *queue_हटाओ_exclude (queue, exclude)
 * Purpose : हटाओ a SCSI command from a queue
 * Params  : queue   - queue to हटाओ command from
 *	     exclude - bit array of target&lun which is busy
 * Returns : काष्ठा scsi_cmnd अगर successful (and a reference), or शून्य अगर no command available
 */
काष्ठा scsi_cmnd *queue_हटाओ_exclude(Queue_t *queue, अचिन्हित दीर्घ *exclude)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *l;
	काष्ठा scsi_cmnd *SCpnt = शून्य;

	spin_lock_irqsave(&queue->queue_lock, flags);
	list_क्रम_each(l, &queue->head) अणु
		QE_t *q = list_entry(l, QE_t, list);
		अगर (!test_bit(q->SCpnt->device->id * 8 +
			      (u8)(q->SCpnt->device->lun & 0x7), exclude)) अणु
			SCpnt = __queue_हटाओ(queue, l);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&queue->queue_lock, flags);

	वापस SCpnt;
पूर्ण

/*
 * Function: काष्ठा scsi_cmnd *queue_हटाओ (queue)
 * Purpose : हटाओs first SCSI command from a queue
 * Params  : queue   - queue to हटाओ command from
 * Returns : काष्ठा scsi_cmnd अगर successful (and a reference), or शून्य अगर no command available
 */
काष्ठा scsi_cmnd *queue_हटाओ(Queue_t *queue)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_cmnd *SCpnt = शून्य;

	spin_lock_irqsave(&queue->queue_lock, flags);
	अगर (!list_empty(&queue->head))
		SCpnt = __queue_हटाओ(queue, queue->head.next);
	spin_unlock_irqrestore(&queue->queue_lock, flags);

	वापस SCpnt;
पूर्ण

/*
 * Function: काष्ठा scsi_cmnd *queue_हटाओ_tgtluntag (queue, target, lun, tag)
 * Purpose : हटाओ a SCSI command from the queue क्रम a specअगरied target/lun/tag
 * Params  : queue  - queue to हटाओ command from
 *	     target - target that we want
 *	     lun    - lun on device
 *	     tag    - tag on device
 * Returns : काष्ठा scsi_cmnd अगर successful, or शून्य अगर no command satisfies requirements
 */
काष्ठा scsi_cmnd *queue_हटाओ_tgtluntag(Queue_t *queue, पूर्णांक target, पूर्णांक lun,
					 पूर्णांक tag)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *l;
	काष्ठा scsi_cmnd *SCpnt = शून्य;

	spin_lock_irqsave(&queue->queue_lock, flags);
	list_क्रम_each(l, &queue->head) अणु
		QE_t *q = list_entry(l, QE_t, list);
		अगर (q->SCpnt->device->id == target && q->SCpnt->device->lun == lun &&
		    q->SCpnt->tag == tag) अणु
			SCpnt = __queue_हटाओ(queue, l);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&queue->queue_lock, flags);

	वापस SCpnt;
पूर्ण

/*
 * Function: queue_हटाओ_all_target(queue, target)
 * Purpose : हटाओ all SCSI commands from the queue क्रम a specअगरied target
 * Params  : queue  - queue to हटाओ command from
 *           target - target device id
 * Returns : nothing
 */
व्योम queue_हटाओ_all_target(Queue_t *queue, पूर्णांक target)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *l;

	spin_lock_irqsave(&queue->queue_lock, flags);
	list_क्रम_each(l, &queue->head) अणु
		QE_t *q = list_entry(l, QE_t, list);
		अगर (q->SCpnt->device->id == target)
			__queue_हटाओ(queue, l);
	पूर्ण
	spin_unlock_irqrestore(&queue->queue_lock, flags);
पूर्ण

/*
 * Function: पूर्णांक queue_probetgtlun (queue, target, lun)
 * Purpose : check to see अगर we have a command in the queue क्रम the specअगरied
 *	     target/lun.
 * Params  : queue  - queue to look in
 *	     target - target we want to probe
 *	     lun    - lun on target
 * Returns : 0 अगर not found, != 0 अगर found
 */
पूर्णांक queue_probetgtlun (Queue_t *queue, पूर्णांक target, पूर्णांक lun)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *l;
	पूर्णांक found = 0;

	spin_lock_irqsave(&queue->queue_lock, flags);
	list_क्रम_each(l, &queue->head) अणु
		QE_t *q = list_entry(l, QE_t, list);
		अगर (q->SCpnt->device->id == target && q->SCpnt->device->lun == lun) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&queue->queue_lock, flags);

	वापस found;
पूर्ण

/*
 * Function: पूर्णांक queue_हटाओ_cmd(Queue_t *queue, काष्ठा scsi_cmnd *SCpnt)
 * Purpose : हटाओ a specअगरic command from the queues
 * Params  : queue - queue to look in
 *	     SCpnt - command to find
 * Returns : 0 अगर not found
 */
पूर्णांक queue_हटाओ_cmd(Queue_t *queue, काष्ठा scsi_cmnd *SCpnt)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *l;
	पूर्णांक found = 0;

	spin_lock_irqsave(&queue->queue_lock, flags);
	list_क्रम_each(l, &queue->head) अणु
		QE_t *q = list_entry(l, QE_t, list);
		अगर (q->SCpnt == SCpnt) अणु
			__queue_हटाओ(queue, l);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&queue->queue_lock, flags);

	वापस found;
पूर्ण

EXPORT_SYMBOL(queue_initialise);
EXPORT_SYMBOL(queue_मुक्त);
EXPORT_SYMBOL(__queue_add);
EXPORT_SYMBOL(queue_हटाओ);
EXPORT_SYMBOL(queue_हटाओ_exclude);
EXPORT_SYMBOL(queue_हटाओ_tgtluntag);
EXPORT_SYMBOL(queue_हटाओ_cmd);
EXPORT_SYMBOL(queue_हटाओ_all_target);
EXPORT_SYMBOL(queue_probetgtlun);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("SCSI command queueing");
MODULE_LICENSE("GPL");
