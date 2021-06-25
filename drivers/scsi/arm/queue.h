<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/acorn/scsi/queue.h: queue handling
 *
 *  Copyright (C) 1997 Russell King
 */
#अगर_अघोषित QUEUE_H
#घोषणा QUEUE_H

प्रकार काष्ठा अणु
	काष्ठा list_head head;
	काष्ठा list_head मुक्त;
	spinlock_t queue_lock;
	व्योम *alloc;			/* start of allocated mem */
पूर्ण Queue_t;

/*
 * Function: व्योम queue_initialise (Queue_t *queue)
 * Purpose : initialise a queue
 * Params  : queue - queue to initialise
 */
बाह्य पूर्णांक queue_initialise (Queue_t *queue);

/*
 * Function: व्योम queue_मुक्त (Queue_t *queue)
 * Purpose : मुक्त a queue
 * Params  : queue - queue to मुक्त
 */
बाह्य व्योम queue_मुक्त (Queue_t *queue);

/*
 * Function: काष्ठा scsi_cmnd *queue_हटाओ (queue)
 * Purpose : हटाओs first SCSI command from a queue
 * Params  : queue   - queue to हटाओ command from
 * Returns : काष्ठा scsi_cmnd अगर successful (and a reference), or शून्य अगर no command available
 */
बाह्य काष्ठा scsi_cmnd *queue_हटाओ (Queue_t *queue);

/*
 * Function: काष्ठा scsi_cmnd *queue_हटाओ_exclude_ref (queue, exclude)
 * Purpose : हटाओ a SCSI command from a queue
 * Params  : queue   - queue to हटाओ command from
 *	     exclude - array of busy LUNs
 * Returns : काष्ठा scsi_cmnd अगर successful (and a reference), or शून्य अगर no command available
 */
बाह्य काष्ठा scsi_cmnd *queue_हटाओ_exclude(Queue_t *queue,
					      अचिन्हित दीर्घ *exclude);

#घोषणा queue_add_cmd_ordered(queue,SCpnt) \
	__queue_add(queue,SCpnt,(SCpnt)->cmnd[0] == REQUEST_SENSE)
#घोषणा queue_add_cmd_tail(queue,SCpnt) \
	__queue_add(queue,SCpnt,0)
/*
 * Function: पूर्णांक __queue_add(Queue_t *queue, काष्ठा scsi_cmnd *SCpnt, पूर्णांक head)
 * Purpose : Add a new command onto a queue
 * Params  : queue - destination queue
 *	     SCpnt - command to add
 *	     head  - add command to head of queue
 * Returns : 0 on error, !0 on success
 */
बाह्य पूर्णांक __queue_add(Queue_t *queue, काष्ठा scsi_cmnd *SCpnt, पूर्णांक head);

/*
 * Function: काष्ठा scsi_cmnd *queue_हटाओ_tgtluntag (queue, target, lun, tag)
 * Purpose : हटाओ a SCSI command from the queue क्रम a specअगरied target/lun/tag
 * Params  : queue  - queue to हटाओ command from
 *	     target - target that we want
 *	     lun    - lun on device
 *	     tag    - tag on device
 * Returns : काष्ठा scsi_cmnd अगर successful, or शून्य अगर no command satisfies requirements
 */
बाह्य काष्ठा scsi_cmnd *queue_हटाओ_tgtluntag(Queue_t *queue, पूर्णांक target,
						पूर्णांक lun, पूर्णांक tag);

/*
 * Function: queue_हटाओ_all_target(queue, target)
 * Purpose : हटाओ all SCSI commands from the queue क्रम a specअगरied target
 * Params  : queue  - queue to हटाओ command from
 *           target - target device id
 * Returns : nothing
 */
बाह्य व्योम queue_हटाओ_all_target(Queue_t *queue, पूर्णांक target);

/*
 * Function: पूर्णांक queue_probetgtlun (queue, target, lun)
 * Purpose : check to see अगर we have a command in the queue क्रम the specअगरied
 *	     target/lun.
 * Params  : queue  - queue to look in
 *	     target - target we want to probe
 *	     lun    - lun on target
 * Returns : 0 अगर not found, != 0 अगर found
 */
बाह्य पूर्णांक queue_probetgtlun (Queue_t *queue, पूर्णांक target, पूर्णांक lun);

/*
 * Function: पूर्णांक queue_हटाओ_cmd (Queue_t *queue, काष्ठा scsi_cmnd *SCpnt)
 * Purpose : हटाओ a specअगरic command from the queues
 * Params  : queue - queue to look in
 *	     SCpnt - command to find
 * Returns : 0 अगर not found
 */
पूर्णांक queue_हटाओ_cmd(Queue_t *queue, काष्ठा scsi_cmnd *SCpnt);

#पूर्ण_अगर /* QUEUE_H */
