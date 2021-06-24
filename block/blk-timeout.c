<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions related to generic समयout handling of requests.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/fault-inject.h>

#समावेश "blk.h"
#समावेश "blk-mq.h"

#अगर_घोषित CONFIG_FAIL_IO_TIMEOUT

अटल DECLARE_FAULT_ATTR(fail_io_समयout);

अटल पूर्णांक __init setup_fail_io_समयout(अक्षर *str)
अणु
	वापस setup_fault_attr(&fail_io_समयout, str);
पूर्ण
__setup("fail_io_timeout=", setup_fail_io_समयout);

bool __blk_should_fake_समयout(काष्ठा request_queue *q)
अणु
	वापस should_fail(&fail_io_समयout, 1);
पूर्ण
EXPORT_SYMBOL_GPL(__blk_should_fake_समयout);

अटल पूर्णांक __init fail_io_समयout_debugfs(व्योम)
अणु
	काष्ठा dentry *dir = fault_create_debugfs_attr("fail_io_timeout",
						शून्य, &fail_io_समयout);

	वापस PTR_ERR_OR_ZERO(dir);
पूर्ण

late_initcall(fail_io_समयout_debugfs);

sमाप_प्रकार part_समयout_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	पूर्णांक set = test_bit(QUEUE_FLAG_FAIL_IO, &disk->queue->queue_flags);

	वापस प्र_लिखो(buf, "%d\n", set != 0);
पूर्ण

sमाप_प्रकार part_समयout_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	पूर्णांक val;

	अगर (count) अणु
		काष्ठा request_queue *q = disk->queue;
		अक्षर *p = (अक्षर *) buf;

		val = simple_म_से_अदीर्घ(p, &p, 10);
		अगर (val)
			blk_queue_flag_set(QUEUE_FLAG_FAIL_IO, q);
		अन्यथा
			blk_queue_flag_clear(QUEUE_FLAG_FAIL_IO, q);
	पूर्ण

	वापस count;
पूर्ण

#पूर्ण_अगर /* CONFIG_FAIL_IO_TIMEOUT */

/**
 * blk_पात_request - Request recovery क्रम the specअगरied command
 * @req:	poपूर्णांकer to the request of पूर्णांकerest
 *
 * This function requests that the block layer start recovery क्रम the
 * request by deleting the समयr and calling the q's समयout function.
 * LLDDs who implement their own error recovery MAY ignore the समयout
 * event अगर they generated blk_पात_request.
 */
व्योम blk_पात_request(काष्ठा request *req)
अणु
	/*
	 * All we need to ensure is that समयout scan takes place
	 * immediately and that scan sees the new समयout value.
	 * No need क्रम fancy synchronizations.
	 */
	WRITE_ONCE(req->deadline, jअगरfies);
	kblockd_schedule_work(&req->q->समयout_work);
पूर्ण
EXPORT_SYMBOL_GPL(blk_पात_request);

अटल अचिन्हित दीर्घ blk_समयout_mask __पढ़ो_mostly;

अटल पूर्णांक __init blk_समयout_init(व्योम)
अणु
	blk_समयout_mask = roundup_घात_of_two(HZ) - 1;
	वापस 0;
पूर्ण

late_initcall(blk_समयout_init);

/*
 * Just a rough estimate, we करोn't care about specअगरic values क्रम समयouts.
 */
अटल अंतरभूत अचिन्हित दीर्घ blk_round_jअगरfies(अचिन्हित दीर्घ j)
अणु
	वापस (j + blk_समयout_mask) + 1;
पूर्ण

अचिन्हित दीर्घ blk_rq_समयout(अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ maxt;

	maxt = blk_round_jअगरfies(jअगरfies + BLK_MAX_TIMEOUT);
	अगर (समय_after(समयout, maxt))
		समयout = maxt;

	वापस समयout;
पूर्ण

/**
 * blk_add_समयr - Start समयout समयr क्रम a single request
 * @req:	request that is about to start running.
 *
 * Notes:
 *    Each request has its own समयr, and as it is added to the queue, we
 *    set up the समयr. When the request completes, we cancel the समयr.
 */
व्योम blk_add_समयr(काष्ठा request *req)
अणु
	काष्ठा request_queue *q = req->q;
	अचिन्हित दीर्घ expiry;

	/*
	 * Some LLDs, like scsi, peek at the समयout to prevent a
	 * command from being retried क्रमever.
	 */
	अगर (!req->समयout)
		req->समयout = q->rq_समयout;

	req->rq_flags &= ~RQF_TIMED_OUT;

	expiry = jअगरfies + req->समयout;
	WRITE_ONCE(req->deadline, expiry);

	/*
	 * If the समयr isn't alपढ़ोy pending or this समयout is earlier
	 * than an existing one, modअगरy the समयr. Round up to next nearest
	 * second.
	 */
	expiry = blk_rq_समयout(blk_round_jअगरfies(expiry));

	अगर (!समयr_pending(&q->समयout) ||
	    समय_beक्रमe(expiry, q->समयout.expires)) अणु
		अचिन्हित दीर्घ dअगरf = q->समयout.expires - expiry;

		/*
		 * Due to added समयr slack to group समयrs, the समयr
		 * will often be a little in front of what we asked क्रम.
		 * So apply some tolerance here too, otherwise we keep
		 * modअगरying the समयr because expires क्रम value X
		 * will be X + something.
		 */
		अगर (!समयr_pending(&q->समयout) || (dअगरf >= HZ / 2))
			mod_समयr(&q->समयout, expiry);
	पूर्ण

पूर्ण
