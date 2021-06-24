<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions related to setting various queue properties from drivers
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/sched/sysctl.h>

#समावेश "blk.h"
#समावेश "blk-mq-sched.h"

/**
 * blk_end_sync_rq - executes a completion event on a request
 * @rq: request to complete
 * @error: end I/O status of the request
 */
अटल व्योम blk_end_sync_rq(काष्ठा request *rq, blk_status_t error)
अणु
	काष्ठा completion *रुकोing = rq->end_io_data;

	rq->end_io_data = शून्य;

	/*
	 * complete last, अगर this is a stack request the process (and thus
	 * the rq poपूर्णांकer) could be invalid right after this complete()
	 */
	complete(रुकोing);
पूर्ण

/**
 * blk_execute_rq_noरुको - insert a request to I/O scheduler क्रम execution
 * @bd_disk:	matching gendisk
 * @rq:		request to insert
 * @at_head:    insert request at head or tail of queue
 * @करोne:	I/O completion handler
 *
 * Description:
 *    Insert a fully prepared request at the back of the I/O scheduler queue
 *    क्रम execution.  Don't रुको क्रम completion.
 *
 * Note:
 *    This function will invoke @करोne directly अगर the queue is dead.
 */
व्योम blk_execute_rq_noरुको(काष्ठा gendisk *bd_disk, काष्ठा request *rq,
			   पूर्णांक at_head, rq_end_io_fn *करोne)
अणु
	WARN_ON(irqs_disabled());
	WARN_ON(!blk_rq_is_passthrough(rq));

	rq->rq_disk = bd_disk;
	rq->end_io = करोne;

	blk_account_io_start(rq);

	/*
	 * करोn't check dying flag for MQ because the request won't
	 * be reused after dying flag is set
	 */
	blk_mq_sched_insert_request(rq, at_head, true, false);
पूर्ण
EXPORT_SYMBOL_GPL(blk_execute_rq_noरुको);

/**
 * blk_execute_rq - insert a request पूर्णांकo queue क्रम execution
 * @bd_disk:	matching gendisk
 * @rq:		request to insert
 * @at_head:    insert request at head or tail of queue
 *
 * Description:
 *    Insert a fully prepared request at the back of the I/O scheduler queue
 *    क्रम execution and रुको क्रम completion.
 */
व्योम blk_execute_rq(काष्ठा gendisk *bd_disk, काष्ठा request *rq, पूर्णांक at_head)
अणु
	DECLARE_COMPLETION_ONSTACK(रुको);
	अचिन्हित दीर्घ hang_check;

	rq->end_io_data = &रुको;
	blk_execute_rq_noरुको(bd_disk, rq, at_head, blk_end_sync_rq);

	/* Prevent hang_check समयr from firing at us during very दीर्घ I/O */
	hang_check = sysctl_hung_task_समयout_secs;
	अगर (hang_check)
		जबतक (!रुको_क्रम_completion_io_समयout(&रुको, hang_check * (HZ/2)));
	अन्यथा
		रुको_क्रम_completion_io(&रुको);
पूर्ण
EXPORT_SYMBOL(blk_execute_rq);
