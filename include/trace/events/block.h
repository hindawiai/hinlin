<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM block

#अगर !defined(_TRACE_BLOCK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_BLOCK_H

#समावेश <linux/blktrace_api.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा RWBS_LEN	8

DECLARE_EVENT_CLASS(block_buffer,

	TP_PROTO(काष्ठा buffer_head *bh),

	TP_ARGS(bh),

	TP_STRUCT__entry (
		__field(  dev_t,	dev			)
		__field(  sector_t,	sector			)
		__field(  माप_प्रकार,	size			)
	),

	TP_fast_assign(
		__entry->dev		= bh->b_bdev->bd_dev;
		__entry->sector		= bh->b_blocknr;
		__entry->size		= bh->b_size;
	),

	TP_prपूर्णांकk("%d,%d sector=%llu size=%zu",
		MAJOR(__entry->dev), MINOR(__entry->dev),
		(अचिन्हित दीर्घ दीर्घ)__entry->sector, __entry->size
	)
);

/**
 * block_touch_buffer - mark a buffer accessed
 * @bh: buffer_head being touched
 *
 * Called from touch_buffer().
 */
DEFINE_EVENT(block_buffer, block_touch_buffer,

	TP_PROTO(काष्ठा buffer_head *bh),

	TP_ARGS(bh)
);

/**
 * block_dirty_buffer - mark a buffer dirty
 * @bh: buffer_head being dirtied
 *
 * Called from mark_buffer_dirty().
 */
DEFINE_EVENT(block_buffer, block_dirty_buffer,

	TP_PROTO(काष्ठा buffer_head *bh),

	TP_ARGS(bh)
);

/**
 * block_rq_requeue - place block IO request back on a queue
 * @rq: block IO operation request
 *
 * The block operation request @rq is being placed back पूर्णांकo queue
 * @q.  For some reason the request was not completed and needs to be
 * put back in the queue.
 */
TRACE_EVENT(block_rq_requeue,

	TP_PROTO(काष्ठा request *rq),

	TP_ARGS(rq),

	TP_STRUCT__entry(
		__field(  dev_t,	dev			)
		__field(  sector_t,	sector			)
		__field(  अचिन्हित पूर्णांक,	nr_sector		)
		__array(  अक्षर,		rwbs,	RWBS_LEN	)
		__dynamic_array( अक्षर,	cmd,	1		)
	),

	TP_fast_assign(
		__entry->dev	   = rq->rq_disk ? disk_devt(rq->rq_disk) : 0;
		__entry->sector    = blk_rq_trace_sector(rq);
		__entry->nr_sector = blk_rq_trace_nr_sectors(rq);

		blk_fill_rwbs(__entry->rwbs, rq->cmd_flags);
		__get_str(cmd)[0] = '\0';
	),

	TP_prपूर्णांकk("%d,%d %s (%s) %llu + %u [%d]",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->rwbs, __get_str(cmd),
		  (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  __entry->nr_sector, 0)
);

/**
 * block_rq_complete - block IO operation completed by device driver
 * @rq: block operations request
 * @error: status code
 * @nr_bytes: number of completed bytes
 *
 * The block_rq_complete tracepoपूर्णांक event indicates that some portion
 * of operation request has been completed by the device driver.  If
 * the @rq->bio is %शून्य, then there is असलolutely no additional work to
 * करो क्रम the request. If @rq->bio is non-शून्य then there is
 * additional work required to complete the request.
 */
TRACE_EVENT(block_rq_complete,

	TP_PROTO(काष्ठा request *rq, पूर्णांक error, अचिन्हित पूर्णांक nr_bytes),

	TP_ARGS(rq, error, nr_bytes),

	TP_STRUCT__entry(
		__field(  dev_t,	dev			)
		__field(  sector_t,	sector			)
		__field(  अचिन्हित पूर्णांक,	nr_sector		)
		__field(  पूर्णांक,		error			)
		__array(  अक्षर,		rwbs,	RWBS_LEN	)
		__dynamic_array( अक्षर,	cmd,	1		)
	),

	TP_fast_assign(
		__entry->dev	   = rq->rq_disk ? disk_devt(rq->rq_disk) : 0;
		__entry->sector    = blk_rq_pos(rq);
		__entry->nr_sector = nr_bytes >> 9;
		__entry->error     = error;

		blk_fill_rwbs(__entry->rwbs, rq->cmd_flags);
		__get_str(cmd)[0] = '\0';
	),

	TP_prपूर्णांकk("%d,%d %s (%s) %llu + %u [%d]",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->rwbs, __get_str(cmd),
		  (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  __entry->nr_sector, __entry->error)
);

DECLARE_EVENT_CLASS(block_rq,

	TP_PROTO(काष्ठा request *rq),

	TP_ARGS(rq),

	TP_STRUCT__entry(
		__field(  dev_t,	dev			)
		__field(  sector_t,	sector			)
		__field(  अचिन्हित पूर्णांक,	nr_sector		)
		__field(  अचिन्हित पूर्णांक,	bytes			)
		__array(  अक्षर,		rwbs,	RWBS_LEN	)
		__array(  अक्षर,         comm,   TASK_COMM_LEN   )
		__dynamic_array( अक्षर,	cmd,	1		)
	),

	TP_fast_assign(
		__entry->dev	   = rq->rq_disk ? disk_devt(rq->rq_disk) : 0;
		__entry->sector    = blk_rq_trace_sector(rq);
		__entry->nr_sector = blk_rq_trace_nr_sectors(rq);
		__entry->bytes     = blk_rq_bytes(rq);

		blk_fill_rwbs(__entry->rwbs, rq->cmd_flags);
		__get_str(cmd)[0] = '\0';
		स_नकल(__entry->comm, current->comm, TASK_COMM_LEN);
	),

	TP_prपूर्णांकk("%d,%d %s %u (%s) %llu + %u [%s]",
		  MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->rwbs, __entry->bytes, __get_str(cmd),
		  (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  __entry->nr_sector, __entry->comm)
);

/**
 * block_rq_insert - insert block operation request पूर्णांकo queue
 * @rq: block IO operation request
 *
 * Called immediately beक्रमe block operation request @rq is inserted
 * पूर्णांकo queue @q.  The fields in the operation request @rq काष्ठा can
 * be examined to determine which device and sectors the pending
 * operation would access.
 */
DEFINE_EVENT(block_rq, block_rq_insert,

	TP_PROTO(काष्ठा request *rq),

	TP_ARGS(rq)
);

/**
 * block_rq_issue - issue pending block IO request operation to device driver
 * @rq: block IO operation request
 *
 * Called when block operation request @rq from queue @q is sent to a
 * device driver क्रम processing.
 */
DEFINE_EVENT(block_rq, block_rq_issue,

	TP_PROTO(काष्ठा request *rq),

	TP_ARGS(rq)
);

/**
 * block_rq_merge - merge request with another one in the elevator
 * @rq: block IO operation request
 *
 * Called when block operation request @rq from queue @q is merged to another
 * request queued in the elevator.
 */
DEFINE_EVENT(block_rq, block_rq_merge,

	TP_PROTO(काष्ठा request *rq),

	TP_ARGS(rq)
);

/**
 * block_bio_complete - completed all work on the block operation
 * @q: queue holding the block operation
 * @bio: block operation completed
 *
 * This tracepoपूर्णांक indicates there is no further work to करो on this
 * block IO operation @bio.
 */
TRACE_EVENT(block_bio_complete,

	TP_PROTO(काष्ठा request_queue *q, काष्ठा bio *bio),

	TP_ARGS(q, bio),

	TP_STRUCT__entry(
		__field( dev_t,		dev		)
		__field( sector_t,	sector		)
		__field( अचिन्हित,	nr_sector	)
		__field( पूर्णांक,		error		)
		__array( अक्षर,		rwbs,	RWBS_LEN)
	),

	TP_fast_assign(
		__entry->dev		= bio_dev(bio);
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->nr_sector	= bio_sectors(bio);
		__entry->error		= blk_status_to_त्रुटि_सं(bio->bi_status);
		blk_fill_rwbs(__entry->rwbs, bio->bi_opf);
	),

	TP_prपूर्णांकk("%d,%d %s %llu + %u [%d]",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->rwbs,
		  (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  __entry->nr_sector, __entry->error)
);

DECLARE_EVENT_CLASS(block_bio,

	TP_PROTO(काष्ठा bio *bio),

	TP_ARGS(bio),

	TP_STRUCT__entry(
		__field( dev_t,		dev			)
		__field( sector_t,	sector			)
		__field( अचिन्हित पूर्णांक,	nr_sector		)
		__array( अक्षर,		rwbs,	RWBS_LEN	)
		__array( अक्षर,		comm,	TASK_COMM_LEN	)
	),

	TP_fast_assign(
		__entry->dev		= bio_dev(bio);
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->nr_sector	= bio_sectors(bio);
		blk_fill_rwbs(__entry->rwbs, bio->bi_opf);
		स_नकल(__entry->comm, current->comm, TASK_COMM_LEN);
	),

	TP_prपूर्णांकk("%d,%d %s %llu + %u [%s]",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->rwbs,
		  (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  __entry->nr_sector, __entry->comm)
);

/**
 * block_bio_bounce - used bounce buffer when processing block operation
 * @bio: block operation
 *
 * A bounce buffer was used to handle the block operation @bio in @q.
 * This occurs when hardware limitations prevent a direct transfer of
 * data between the @bio data memory area and the IO device.  Use of a
 * bounce buffer requires extra copying of data and decreases
 * perक्रमmance.
 */
DEFINE_EVENT(block_bio, block_bio_bounce,
	TP_PROTO(काष्ठा bio *bio),
	TP_ARGS(bio)
);

/**
 * block_bio_backmerge - merging block operation to the end of an existing operation
 * @bio: new block operation to merge
 *
 * Merging block request @bio to the end of an existing block request.
 */
DEFINE_EVENT(block_bio, block_bio_backmerge,
	TP_PROTO(काष्ठा bio *bio),
	TP_ARGS(bio)
);

/**
 * block_bio_fronपंचांगerge - merging block operation to the beginning of an existing operation
 * @bio: new block operation to merge
 *
 * Merging block IO operation @bio to the beginning of an existing block request.
 */
DEFINE_EVENT(block_bio, block_bio_fronपंचांगerge,
	TP_PROTO(काष्ठा bio *bio),
	TP_ARGS(bio)
);

/**
 * block_bio_queue - putting new block IO operation in queue
 * @bio: new block operation
 *
 * About to place the block IO operation @bio पूर्णांकo queue @q.
 */
DEFINE_EVENT(block_bio, block_bio_queue,
	TP_PROTO(काष्ठा bio *bio),
	TP_ARGS(bio)
);

/**
 * block_getrq - get a मुक्त request entry in queue क्रम block IO operations
 * @bio: pending block IO operation (can be %शून्य)
 *
 * A request काष्ठा has been allocated to handle the block IO operation @bio.
 */
DEFINE_EVENT(block_bio, block_getrq,
	TP_PROTO(काष्ठा bio *bio),
	TP_ARGS(bio)
);

/**
 * block_plug - keep operations requests in request queue
 * @q: request queue to plug
 *
 * Plug the request queue @q.  Do not allow block operation requests
 * to be sent to the device driver. Instead, accumulate requests in
 * the queue to improve throughput perक्रमmance of the block device.
 */
TRACE_EVENT(block_plug,

	TP_PROTO(काष्ठा request_queue *q),

	TP_ARGS(q),

	TP_STRUCT__entry(
		__array( अक्षर,		comm,	TASK_COMM_LEN	)
	),

	TP_fast_assign(
		स_नकल(__entry->comm, current->comm, TASK_COMM_LEN);
	),

	TP_prपूर्णांकk("[%s]", __entry->comm)
);

DECLARE_EVENT_CLASS(block_unplug,

	TP_PROTO(काष्ठा request_queue *q, अचिन्हित पूर्णांक depth, bool explicit),

	TP_ARGS(q, depth, explicit),

	TP_STRUCT__entry(
		__field( पूर्णांक,		nr_rq			)
		__array( अक्षर,		comm,	TASK_COMM_LEN	)
	),

	TP_fast_assign(
		__entry->nr_rq = depth;
		स_नकल(__entry->comm, current->comm, TASK_COMM_LEN);
	),

	TP_prपूर्णांकk("[%s] %d", __entry->comm, __entry->nr_rq)
);

/**
 * block_unplug - release of operations requests in request queue
 * @q: request queue to unplug
 * @depth: number of requests just added to the queue
 * @explicit: whether this was an explicit unplug, or one from schedule()
 *
 * Unplug request queue @q because device driver is scheduled to work
 * on elements in the request queue.
 */
DEFINE_EVENT(block_unplug, block_unplug,

	TP_PROTO(काष्ठा request_queue *q, अचिन्हित पूर्णांक depth, bool explicit),

	TP_ARGS(q, depth, explicit)
);

/**
 * block_split - split a single bio काष्ठा पूर्णांकo two bio काष्ठाs
 * @bio: block operation being split
 * @new_sector: The starting sector क्रम the new bio
 *
 * The bio request @bio needs to be split पूर्णांकo two bio requests.  The newly
 * created @bio request starts at @new_sector. This split may be required due to
 * hardware limitations such as operation crossing device boundaries in a RAID
 * प्रणाली.
 */
TRACE_EVENT(block_split,

	TP_PROTO(काष्ठा bio *bio, अचिन्हित पूर्णांक new_sector),

	TP_ARGS(bio, new_sector),

	TP_STRUCT__entry(
		__field( dev_t,		dev				)
		__field( sector_t,	sector				)
		__field( sector_t,	new_sector			)
		__array( अक्षर,		rwbs,		RWBS_LEN	)
		__array( अक्षर,		comm,		TASK_COMM_LEN	)
	),

	TP_fast_assign(
		__entry->dev		= bio_dev(bio);
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->new_sector	= new_sector;
		blk_fill_rwbs(__entry->rwbs, bio->bi_opf);
		स_नकल(__entry->comm, current->comm, TASK_COMM_LEN);
	),

	TP_prपूर्णांकk("%d,%d %s %llu / %llu [%s]",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->rwbs,
		  (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  (अचिन्हित दीर्घ दीर्घ)__entry->new_sector,
		  __entry->comm)
);

/**
 * block_bio_remap - map request क्रम a logical device to the raw device
 * @bio: revised operation
 * @dev: original device क्रम the operation
 * @from: original sector क्रम the operation
 *
 * An operation क्रम a logical device has been mapped to the
 * raw block device.
 */
TRACE_EVENT(block_bio_remap,

	TP_PROTO(काष्ठा bio *bio, dev_t dev, sector_t from),

	TP_ARGS(bio, dev, from),

	TP_STRUCT__entry(
		__field( dev_t,		dev		)
		__field( sector_t,	sector		)
		__field( अचिन्हित पूर्णांक,	nr_sector	)
		__field( dev_t,		old_dev		)
		__field( sector_t,	old_sector	)
		__array( अक्षर,		rwbs,	RWBS_LEN)
	),

	TP_fast_assign(
		__entry->dev		= bio_dev(bio);
		__entry->sector		= bio->bi_iter.bi_sector;
		__entry->nr_sector	= bio_sectors(bio);
		__entry->old_dev	= dev;
		__entry->old_sector	= from;
		blk_fill_rwbs(__entry->rwbs, bio->bi_opf);
	),

	TP_prपूर्णांकk("%d,%d %s %llu + %u <- (%d,%d) %llu",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->rwbs,
		  (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  __entry->nr_sector,
		  MAJOR(__entry->old_dev), MINOR(__entry->old_dev),
		  (अचिन्हित दीर्घ दीर्घ)__entry->old_sector)
);

/**
 * block_rq_remap - map request क्रम a block operation request
 * @rq: block IO operation request
 * @dev: device क्रम the operation
 * @from: original sector क्रम the operation
 *
 * The block operation request @rq in @q has been remapped.  The block
 * operation request @rq holds the current inक्रमmation and @from hold
 * the original sector.
 */
TRACE_EVENT(block_rq_remap,

	TP_PROTO(काष्ठा request *rq, dev_t dev, sector_t from),

	TP_ARGS(rq, dev, from),

	TP_STRUCT__entry(
		__field( dev_t,		dev		)
		__field( sector_t,	sector		)
		__field( अचिन्हित पूर्णांक,	nr_sector	)
		__field( dev_t,		old_dev		)
		__field( sector_t,	old_sector	)
		__field( अचिन्हित पूर्णांक,	nr_bios		)
		__array( अक्षर,		rwbs,	RWBS_LEN)
	),

	TP_fast_assign(
		__entry->dev		= disk_devt(rq->rq_disk);
		__entry->sector		= blk_rq_pos(rq);
		__entry->nr_sector	= blk_rq_sectors(rq);
		__entry->old_dev	= dev;
		__entry->old_sector	= from;
		__entry->nr_bios	= blk_rq_count_bios(rq);
		blk_fill_rwbs(__entry->rwbs, rq->cmd_flags);
	),

	TP_prपूर्णांकk("%d,%d %s %llu + %u <- (%d,%d) %llu %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->rwbs,
		  (अचिन्हित दीर्घ दीर्घ)__entry->sector,
		  __entry->nr_sector,
		  MAJOR(__entry->old_dev), MINOR(__entry->old_dev),
		  (अचिन्हित दीर्घ दीर्घ)__entry->old_sector, __entry->nr_bios)
);

#पूर्ण_अगर /* _TRACE_BLOCK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>

