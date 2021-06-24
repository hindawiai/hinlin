<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions related to setting various queue properties from drivers
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/gcd.h>
#समावेश <linux/lcm.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/gfp.h>
#समावेश <linux/dma-mapping.h>

#समावेश "blk.h"
#समावेश "blk-wbt.h"

व्योम blk_queue_rq_समयout(काष्ठा request_queue *q, अचिन्हित पूर्णांक समयout)
अणु
	q->rq_समयout = समयout;
पूर्ण
EXPORT_SYMBOL_GPL(blk_queue_rq_समयout);

/**
 * blk_set_शेष_limits - reset limits to शेष values
 * @lim:  the queue_limits काष्ठाure to reset
 *
 * Description:
 *   Returns a queue_limit काष्ठा to its शेष state.
 */
व्योम blk_set_शेष_limits(काष्ठा queue_limits *lim)
अणु
	lim->max_segments = BLK_MAX_SEGMENTS;
	lim->max_discard_segments = 1;
	lim->max_पूर्णांकegrity_segments = 0;
	lim->seg_boundary_mask = BLK_SEG_BOUNDARY_MASK;
	lim->virt_boundary_mask = 0;
	lim->max_segment_size = BLK_MAX_SEGMENT_SIZE;
	lim->max_sectors = lim->max_hw_sectors = BLK_SAFE_MAX_SECTORS;
	lim->max_dev_sectors = 0;
	lim->chunk_sectors = 0;
	lim->max_ग_लिखो_same_sectors = 0;
	lim->max_ग_लिखो_zeroes_sectors = 0;
	lim->max_zone_append_sectors = 0;
	lim->max_discard_sectors = 0;
	lim->max_hw_discard_sectors = 0;
	lim->discard_granularity = 0;
	lim->discard_alignment = 0;
	lim->discard_misaligned = 0;
	lim->logical_block_size = lim->physical_block_size = lim->io_min = 512;
	lim->bounce = BLK_BOUNCE_NONE;
	lim->alignment_offset = 0;
	lim->io_opt = 0;
	lim->misaligned = 0;
	lim->zoned = BLK_ZONED_NONE;
	lim->zone_ग_लिखो_granularity = 0;
पूर्ण
EXPORT_SYMBOL(blk_set_शेष_limits);

/**
 * blk_set_stacking_limits - set शेष limits क्रम stacking devices
 * @lim:  the queue_limits काष्ठाure to reset
 *
 * Description:
 *   Returns a queue_limit काष्ठा to its शेष state. Should be used
 *   by stacking drivers like DM that have no पूर्णांकernal limits.
 */
व्योम blk_set_stacking_limits(काष्ठा queue_limits *lim)
अणु
	blk_set_शेष_limits(lim);

	/* Inherit limits from component devices */
	lim->max_segments = अच_लघु_उच्च;
	lim->max_discard_segments = अच_लघु_उच्च;
	lim->max_hw_sectors = अच_पूर्णांक_उच्च;
	lim->max_segment_size = अच_पूर्णांक_उच्च;
	lim->max_sectors = अच_पूर्णांक_उच्च;
	lim->max_dev_sectors = अच_पूर्णांक_उच्च;
	lim->max_ग_लिखो_same_sectors = अच_पूर्णांक_उच्च;
	lim->max_ग_लिखो_zeroes_sectors = अच_पूर्णांक_उच्च;
	lim->max_zone_append_sectors = अच_पूर्णांक_उच्च;
पूर्ण
EXPORT_SYMBOL(blk_set_stacking_limits);

/**
 * blk_queue_bounce_limit - set bounce buffer limit क्रम queue
 * @q: the request queue क्रम the device
 * @bounce: bounce limit to enक्रमce
 *
 * Description:
 *    Force bouncing क्रम ISA DMA ranges or highmem.
 *
 *    DEPRECATED, करोn't use in new code.
 **/
व्योम blk_queue_bounce_limit(काष्ठा request_queue *q, क्रमागत blk_bounce bounce)
अणु
	q->limits.bounce = bounce;
पूर्ण
EXPORT_SYMBOL(blk_queue_bounce_limit);

/**
 * blk_queue_max_hw_sectors - set max sectors क्रम a request क्रम this queue
 * @q:  the request queue क्रम the device
 * @max_hw_sectors:  max hardware sectors in the usual 512b unit
 *
 * Description:
 *    Enables a low level driver to set a hard upper limit,
 *    max_hw_sectors, on the size of requests.  max_hw_sectors is set by
 *    the device driver based upon the capabilities of the I/O
 *    controller.
 *
 *    max_dev_sectors is a hard limit imposed by the storage device क्रम
 *    READ/WRITE requests. It is set by the disk driver.
 *
 *    max_sectors is a soft limit imposed by the block layer क्रम
 *    fileप्रणाली type requests.  This value can be overridden on a
 *    per-device basis in /sys/block/<device>/queue/max_sectors_kb.
 *    The soft limit can not exceed max_hw_sectors.
 **/
व्योम blk_queue_max_hw_sectors(काष्ठा request_queue *q, अचिन्हित पूर्णांक max_hw_sectors)
अणु
	काष्ठा queue_limits *limits = &q->limits;
	अचिन्हित पूर्णांक max_sectors;

	अगर ((max_hw_sectors << 9) < PAGE_SIZE) अणु
		max_hw_sectors = 1 << (PAGE_SHIFT - 9);
		prपूर्णांकk(KERN_INFO "%s: set to minimum %d\n",
		       __func__, max_hw_sectors);
	पूर्ण

	max_hw_sectors = round_करोwn(max_hw_sectors,
				    limits->logical_block_size >> SECTOR_SHIFT);
	limits->max_hw_sectors = max_hw_sectors;

	max_sectors = min_not_zero(max_hw_sectors, limits->max_dev_sectors);
	max_sectors = min_t(अचिन्हित पूर्णांक, max_sectors, BLK_DEF_MAX_SECTORS);
	max_sectors = round_करोwn(max_sectors,
				 limits->logical_block_size >> SECTOR_SHIFT);
	limits->max_sectors = max_sectors;

	q->backing_dev_info->io_pages = max_sectors >> (PAGE_SHIFT - 9);
पूर्ण
EXPORT_SYMBOL(blk_queue_max_hw_sectors);

/**
 * blk_queue_chunk_sectors - set size of the chunk क्रम this queue
 * @q:  the request queue क्रम the device
 * @chunk_sectors:  chunk sectors in the usual 512b unit
 *
 * Description:
 *    If a driver करोesn't want IOs to cross a given chunk size, it can set
 *    this limit and prevent merging across chunks. Note that the block layer
 *    must accept a page worth of data at any offset. So अगर the crossing of
 *    chunks is a hard limitation in the driver, it must still be prepared
 *    to split single page bios.
 **/
व्योम blk_queue_chunk_sectors(काष्ठा request_queue *q, अचिन्हित पूर्णांक chunk_sectors)
अणु
	q->limits.chunk_sectors = chunk_sectors;
पूर्ण
EXPORT_SYMBOL(blk_queue_chunk_sectors);

/**
 * blk_queue_max_discard_sectors - set max sectors क्रम a single discard
 * @q:  the request queue क्रम the device
 * @max_discard_sectors: maximum number of sectors to discard
 **/
व्योम blk_queue_max_discard_sectors(काष्ठा request_queue *q,
		अचिन्हित पूर्णांक max_discard_sectors)
अणु
	q->limits.max_hw_discard_sectors = max_discard_sectors;
	q->limits.max_discard_sectors = max_discard_sectors;
पूर्ण
EXPORT_SYMBOL(blk_queue_max_discard_sectors);

/**
 * blk_queue_max_ग_लिखो_same_sectors - set max sectors क्रम a single ग_लिखो same
 * @q:  the request queue क्रम the device
 * @max_ग_लिखो_same_sectors: maximum number of sectors to ग_लिखो per command
 **/
व्योम blk_queue_max_ग_लिखो_same_sectors(काष्ठा request_queue *q,
				      अचिन्हित पूर्णांक max_ग_लिखो_same_sectors)
अणु
	q->limits.max_ग_लिखो_same_sectors = max_ग_लिखो_same_sectors;
पूर्ण
EXPORT_SYMBOL(blk_queue_max_ग_लिखो_same_sectors);

/**
 * blk_queue_max_ग_लिखो_zeroes_sectors - set max sectors क्रम a single
 *                                      ग_लिखो zeroes
 * @q:  the request queue क्रम the device
 * @max_ग_लिखो_zeroes_sectors: maximum number of sectors to ग_लिखो per command
 **/
व्योम blk_queue_max_ग_लिखो_zeroes_sectors(काष्ठा request_queue *q,
		अचिन्हित पूर्णांक max_ग_लिखो_zeroes_sectors)
अणु
	q->limits.max_ग_लिखो_zeroes_sectors = max_ग_लिखो_zeroes_sectors;
पूर्ण
EXPORT_SYMBOL(blk_queue_max_ग_लिखो_zeroes_sectors);

/**
 * blk_queue_max_zone_append_sectors - set max sectors क्रम a single zone append
 * @q:  the request queue क्रम the device
 * @max_zone_append_sectors: maximum number of sectors to ग_लिखो per command
 **/
व्योम blk_queue_max_zone_append_sectors(काष्ठा request_queue *q,
		अचिन्हित पूर्णांक max_zone_append_sectors)
अणु
	अचिन्हित पूर्णांक max_sectors;

	अगर (WARN_ON(!blk_queue_is_zoned(q)))
		वापस;

	max_sectors = min(q->limits.max_hw_sectors, max_zone_append_sectors);
	max_sectors = min(q->limits.chunk_sectors, max_sectors);

	/*
	 * Signal eventual driver bugs resulting in the max_zone_append sectors limit
	 * being 0 due to a 0 argument, the chunk_sectors limit (zone size) not set,
	 * or the max_hw_sectors limit not set.
	 */
	WARN_ON(!max_sectors);

	q->limits.max_zone_append_sectors = max_sectors;
पूर्ण
EXPORT_SYMBOL_GPL(blk_queue_max_zone_append_sectors);

/**
 * blk_queue_max_segments - set max hw segments क्रम a request क्रम this queue
 * @q:  the request queue क्रम the device
 * @max_segments:  max number of segments
 *
 * Description:
 *    Enables a low level driver to set an upper limit on the number of
 *    hw data segments in a request.
 **/
व्योम blk_queue_max_segments(काष्ठा request_queue *q, अचिन्हित लघु max_segments)
अणु
	अगर (!max_segments) अणु
		max_segments = 1;
		prपूर्णांकk(KERN_INFO "%s: set to minimum %d\n",
		       __func__, max_segments);
	पूर्ण

	q->limits.max_segments = max_segments;
पूर्ण
EXPORT_SYMBOL(blk_queue_max_segments);

/**
 * blk_queue_max_discard_segments - set max segments क्रम discard requests
 * @q:  the request queue क्रम the device
 * @max_segments:  max number of segments
 *
 * Description:
 *    Enables a low level driver to set an upper limit on the number of
 *    segments in a discard request.
 **/
व्योम blk_queue_max_discard_segments(काष्ठा request_queue *q,
		अचिन्हित लघु max_segments)
अणु
	q->limits.max_discard_segments = max_segments;
पूर्ण
EXPORT_SYMBOL_GPL(blk_queue_max_discard_segments);

/**
 * blk_queue_max_segment_size - set max segment size क्रम blk_rq_map_sg
 * @q:  the request queue क्रम the device
 * @max_size:  max size of segment in bytes
 *
 * Description:
 *    Enables a low level driver to set an upper limit on the size of a
 *    coalesced segment
 **/
व्योम blk_queue_max_segment_size(काष्ठा request_queue *q, अचिन्हित पूर्णांक max_size)
अणु
	अगर (max_size < PAGE_SIZE) अणु
		max_size = PAGE_SIZE;
		prपूर्णांकk(KERN_INFO "%s: set to minimum %d\n",
		       __func__, max_size);
	पूर्ण

	/* see blk_queue_virt_boundary() क्रम the explanation */
	WARN_ON_ONCE(q->limits.virt_boundary_mask);

	q->limits.max_segment_size = max_size;
पूर्ण
EXPORT_SYMBOL(blk_queue_max_segment_size);

/**
 * blk_queue_logical_block_size - set logical block size क्रम the queue
 * @q:  the request queue क्रम the device
 * @size:  the logical block size, in bytes
 *
 * Description:
 *   This should be set to the lowest possible block size that the
 *   storage device can address.  The शेष of 512 covers most
 *   hardware.
 **/
व्योम blk_queue_logical_block_size(काष्ठा request_queue *q, अचिन्हित पूर्णांक size)
अणु
	काष्ठा queue_limits *limits = &q->limits;

	limits->logical_block_size = size;

	अगर (limits->physical_block_size < size)
		limits->physical_block_size = size;

	अगर (limits->io_min < limits->physical_block_size)
		limits->io_min = limits->physical_block_size;

	limits->max_hw_sectors =
		round_करोwn(limits->max_hw_sectors, size >> SECTOR_SHIFT);
	limits->max_sectors =
		round_करोwn(limits->max_sectors, size >> SECTOR_SHIFT);
पूर्ण
EXPORT_SYMBOL(blk_queue_logical_block_size);

/**
 * blk_queue_physical_block_size - set physical block size क्रम the queue
 * @q:  the request queue क्रम the device
 * @size:  the physical block size, in bytes
 *
 * Description:
 *   This should be set to the lowest possible sector size that the
 *   hardware can operate on without reverting to पढ़ो-modअगरy-ग_लिखो
 *   operations.
 */
व्योम blk_queue_physical_block_size(काष्ठा request_queue *q, अचिन्हित पूर्णांक size)
अणु
	q->limits.physical_block_size = size;

	अगर (q->limits.physical_block_size < q->limits.logical_block_size)
		q->limits.physical_block_size = q->limits.logical_block_size;

	अगर (q->limits.io_min < q->limits.physical_block_size)
		q->limits.io_min = q->limits.physical_block_size;
पूर्ण
EXPORT_SYMBOL(blk_queue_physical_block_size);

/**
 * blk_queue_zone_ग_लिखो_granularity - set zone ग_लिखो granularity क्रम the queue
 * @q:  the request queue क्रम the zoned device
 * @size:  the zone ग_लिखो granularity size, in bytes
 *
 * Description:
 *   This should be set to the lowest possible size allowing to ग_लिखो in
 *   sequential zones of a zoned block device.
 */
व्योम blk_queue_zone_ग_लिखो_granularity(काष्ठा request_queue *q,
				      अचिन्हित पूर्णांक size)
अणु
	अगर (WARN_ON_ONCE(!blk_queue_is_zoned(q)))
		वापस;

	q->limits.zone_ग_लिखो_granularity = size;

	अगर (q->limits.zone_ग_लिखो_granularity < q->limits.logical_block_size)
		q->limits.zone_ग_लिखो_granularity = q->limits.logical_block_size;
पूर्ण
EXPORT_SYMBOL_GPL(blk_queue_zone_ग_लिखो_granularity);

/**
 * blk_queue_alignment_offset - set physical block alignment offset
 * @q:	the request queue क्रम the device
 * @offset: alignment offset in bytes
 *
 * Description:
 *   Some devices are naturally misaligned to compensate क्रम things like
 *   the legacy DOS partition table 63-sector offset.  Low-level drivers
 *   should call this function क्रम devices whose first sector is not
 *   naturally aligned.
 */
व्योम blk_queue_alignment_offset(काष्ठा request_queue *q, अचिन्हित पूर्णांक offset)
अणु
	q->limits.alignment_offset =
		offset & (q->limits.physical_block_size - 1);
	q->limits.misaligned = 0;
पूर्ण
EXPORT_SYMBOL(blk_queue_alignment_offset);

व्योम blk_queue_update_पढ़ोahead(काष्ठा request_queue *q)
अणु
	/*
	 * For पढ़ो-ahead of large files to be effective, we need to पढ़ो ahead
	 * at least twice the optimal I/O size.
	 */
	q->backing_dev_info->ra_pages =
		max(queue_io_opt(q) * 2 / PAGE_SIZE, VM_READAHEAD_PAGES);
	q->backing_dev_info->io_pages =
		queue_max_sectors(q) >> (PAGE_SHIFT - 9);
पूर्ण
EXPORT_SYMBOL_GPL(blk_queue_update_पढ़ोahead);

/**
 * blk_limits_io_min - set minimum request size क्रम a device
 * @limits: the queue limits
 * @min:  smallest I/O size in bytes
 *
 * Description:
 *   Some devices have an पूर्णांकernal block size bigger than the reported
 *   hardware sector size.  This function can be used to संकेत the
 *   smallest I/O the device can perक्रमm without incurring a perक्रमmance
 *   penalty.
 */
व्योम blk_limits_io_min(काष्ठा queue_limits *limits, अचिन्हित पूर्णांक min)
अणु
	limits->io_min = min;

	अगर (limits->io_min < limits->logical_block_size)
		limits->io_min = limits->logical_block_size;

	अगर (limits->io_min < limits->physical_block_size)
		limits->io_min = limits->physical_block_size;
पूर्ण
EXPORT_SYMBOL(blk_limits_io_min);

/**
 * blk_queue_io_min - set minimum request size क्रम the queue
 * @q:	the request queue क्रम the device
 * @min:  smallest I/O size in bytes
 *
 * Description:
 *   Storage devices may report a granularity or preferred minimum I/O
 *   size which is the smallest request the device can perक्रमm without
 *   incurring a perक्रमmance penalty.  For disk drives this is often the
 *   physical block size.  For RAID arrays it is often the stripe chunk
 *   size.  A properly aligned multiple of minimum_io_size is the
 *   preferred request size क्रम workloads where a high number of I/O
 *   operations is desired.
 */
व्योम blk_queue_io_min(काष्ठा request_queue *q, अचिन्हित पूर्णांक min)
अणु
	blk_limits_io_min(&q->limits, min);
पूर्ण
EXPORT_SYMBOL(blk_queue_io_min);

/**
 * blk_limits_io_opt - set optimal request size क्रम a device
 * @limits: the queue limits
 * @opt:  smallest I/O size in bytes
 *
 * Description:
 *   Storage devices may report an optimal I/O size, which is the
 *   device's preferred unit क्रम sustained I/O.  This is rarely reported
 *   क्रम disk drives.  For RAID arrays it is usually the stripe width or
 *   the पूर्णांकernal track size.  A properly aligned multiple of
 *   optimal_io_size is the preferred request size क्रम workloads where
 *   sustained throughput is desired.
 */
व्योम blk_limits_io_opt(काष्ठा queue_limits *limits, अचिन्हित पूर्णांक opt)
अणु
	limits->io_opt = opt;
पूर्ण
EXPORT_SYMBOL(blk_limits_io_opt);

/**
 * blk_queue_io_opt - set optimal request size क्रम the queue
 * @q:	the request queue क्रम the device
 * @opt:  optimal request size in bytes
 *
 * Description:
 *   Storage devices may report an optimal I/O size, which is the
 *   device's preferred unit क्रम sustained I/O.  This is rarely reported
 *   क्रम disk drives.  For RAID arrays it is usually the stripe width or
 *   the पूर्णांकernal track size.  A properly aligned multiple of
 *   optimal_io_size is the preferred request size क्रम workloads where
 *   sustained throughput is desired.
 */
व्योम blk_queue_io_opt(काष्ठा request_queue *q, अचिन्हित पूर्णांक opt)
अणु
	blk_limits_io_opt(&q->limits, opt);
	q->backing_dev_info->ra_pages =
		max(queue_io_opt(q) * 2 / PAGE_SIZE, VM_READAHEAD_PAGES);
पूर्ण
EXPORT_SYMBOL(blk_queue_io_opt);

अटल अचिन्हित पूर्णांक blk_round_करोwn_sectors(अचिन्हित पूर्णांक sectors, अचिन्हित पूर्णांक lbs)
अणु
	sectors = round_करोwn(sectors, lbs >> SECTOR_SHIFT);
	अगर (sectors < PAGE_SIZE >> SECTOR_SHIFT)
		sectors = PAGE_SIZE >> SECTOR_SHIFT;
	वापस sectors;
पूर्ण

/**
 * blk_stack_limits - adjust queue_limits क्रम stacked devices
 * @t:	the stacking driver limits (top device)
 * @b:  the underlying queue limits (bottom, component device)
 * @start:  first data sector within component device
 *
 * Description:
 *    This function is used by stacking drivers like MD and DM to ensure
 *    that all component devices have compatible block sizes and
 *    alignments.  The stacking driver must provide a queue_limits
 *    काष्ठा (top) and then iteratively call the stacking function क्रम
 *    all component (bottom) devices.  The stacking function will
 *    attempt to combine the values and ensure proper alignment.
 *
 *    Returns 0 अगर the top and bottom queue_limits are compatible.  The
 *    top device's block sizes and alignment offsets may be adjusted to
 *    ensure alignment with the bottom device. If no compatible sizes
 *    and alignments exist, -1 is वापसed and the resulting top
 *    queue_limits will have the misaligned flag set to indicate that
 *    the alignment_offset is undefined.
 */
पूर्णांक blk_stack_limits(काष्ठा queue_limits *t, काष्ठा queue_limits *b,
		     sector_t start)
अणु
	अचिन्हित पूर्णांक top, bottom, alignment, ret = 0;

	t->max_sectors = min_not_zero(t->max_sectors, b->max_sectors);
	t->max_hw_sectors = min_not_zero(t->max_hw_sectors, b->max_hw_sectors);
	t->max_dev_sectors = min_not_zero(t->max_dev_sectors, b->max_dev_sectors);
	t->max_ग_लिखो_same_sectors = min(t->max_ग_लिखो_same_sectors,
					b->max_ग_लिखो_same_sectors);
	t->max_ग_लिखो_zeroes_sectors = min(t->max_ग_लिखो_zeroes_sectors,
					b->max_ग_लिखो_zeroes_sectors);
	t->max_zone_append_sectors = min(t->max_zone_append_sectors,
					b->max_zone_append_sectors);
	t->bounce = max(t->bounce, b->bounce);

	t->seg_boundary_mask = min_not_zero(t->seg_boundary_mask,
					    b->seg_boundary_mask);
	t->virt_boundary_mask = min_not_zero(t->virt_boundary_mask,
					    b->virt_boundary_mask);

	t->max_segments = min_not_zero(t->max_segments, b->max_segments);
	t->max_discard_segments = min_not_zero(t->max_discard_segments,
					       b->max_discard_segments);
	t->max_पूर्णांकegrity_segments = min_not_zero(t->max_पूर्णांकegrity_segments,
						 b->max_पूर्णांकegrity_segments);

	t->max_segment_size = min_not_zero(t->max_segment_size,
					   b->max_segment_size);

	t->misaligned |= b->misaligned;

	alignment = queue_limit_alignment_offset(b, start);

	/* Bottom device has dअगरferent alignment.  Check that it is
	 * compatible with the current top alignment.
	 */
	अगर (t->alignment_offset != alignment) अणु

		top = max(t->physical_block_size, t->io_min)
			+ t->alignment_offset;
		bottom = max(b->physical_block_size, b->io_min) + alignment;

		/* Verअगरy that top and bottom पूर्णांकervals line up */
		अगर (max(top, bottom) % min(top, bottom)) अणु
			t->misaligned = 1;
			ret = -1;
		पूर्ण
	पूर्ण

	t->logical_block_size = max(t->logical_block_size,
				    b->logical_block_size);

	t->physical_block_size = max(t->physical_block_size,
				     b->physical_block_size);

	t->io_min = max(t->io_min, b->io_min);
	t->io_opt = lcm_not_zero(t->io_opt, b->io_opt);

	/* Set non-घातer-of-2 compatible chunk_sectors boundary */
	अगर (b->chunk_sectors)
		t->chunk_sectors = gcd(t->chunk_sectors, b->chunk_sectors);

	/* Physical block size a multiple of the logical block size? */
	अगर (t->physical_block_size & (t->logical_block_size - 1)) अणु
		t->physical_block_size = t->logical_block_size;
		t->misaligned = 1;
		ret = -1;
	पूर्ण

	/* Minimum I/O a multiple of the physical block size? */
	अगर (t->io_min & (t->physical_block_size - 1)) अणु
		t->io_min = t->physical_block_size;
		t->misaligned = 1;
		ret = -1;
	पूर्ण

	/* Optimal I/O a multiple of the physical block size? */
	अगर (t->io_opt & (t->physical_block_size - 1)) अणु
		t->io_opt = 0;
		t->misaligned = 1;
		ret = -1;
	पूर्ण

	/* chunk_sectors a multiple of the physical block size? */
	अगर ((t->chunk_sectors << 9) & (t->physical_block_size - 1)) अणु
		t->chunk_sectors = 0;
		t->misaligned = 1;
		ret = -1;
	पूर्ण

	t->raid_partial_stripes_expensive =
		max(t->raid_partial_stripes_expensive,
		    b->raid_partial_stripes_expensive);

	/* Find lowest common alignment_offset */
	t->alignment_offset = lcm_not_zero(t->alignment_offset, alignment)
		% max(t->physical_block_size, t->io_min);

	/* Verअगरy that new alignment_offset is on a logical block boundary */
	अगर (t->alignment_offset & (t->logical_block_size - 1)) अणु
		t->misaligned = 1;
		ret = -1;
	पूर्ण

	t->max_sectors = blk_round_करोwn_sectors(t->max_sectors, t->logical_block_size);
	t->max_hw_sectors = blk_round_करोwn_sectors(t->max_hw_sectors, t->logical_block_size);
	t->max_dev_sectors = blk_round_करोwn_sectors(t->max_dev_sectors, t->logical_block_size);

	/* Discard alignment and granularity */
	अगर (b->discard_granularity) अणु
		alignment = queue_limit_discard_alignment(b, start);

		अगर (t->discard_granularity != 0 &&
		    t->discard_alignment != alignment) अणु
			top = t->discard_granularity + t->discard_alignment;
			bottom = b->discard_granularity + alignment;

			/* Verअगरy that top and bottom पूर्णांकervals line up */
			अगर ((max(top, bottom) % min(top, bottom)) != 0)
				t->discard_misaligned = 1;
		पूर्ण

		t->max_discard_sectors = min_not_zero(t->max_discard_sectors,
						      b->max_discard_sectors);
		t->max_hw_discard_sectors = min_not_zero(t->max_hw_discard_sectors,
							 b->max_hw_discard_sectors);
		t->discard_granularity = max(t->discard_granularity,
					     b->discard_granularity);
		t->discard_alignment = lcm_not_zero(t->discard_alignment, alignment) %
			t->discard_granularity;
	पूर्ण

	t->zone_ग_लिखो_granularity = max(t->zone_ग_लिखो_granularity,
					b->zone_ग_लिखो_granularity);
	t->zoned = max(t->zoned, b->zoned);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(blk_stack_limits);

/**
 * disk_stack_limits - adjust queue limits क्रम stacked drivers
 * @disk:  MD/DM gendisk (top)
 * @bdev:  the underlying block device (bottom)
 * @offset:  offset to beginning of data within component device
 *
 * Description:
 *    Merges the limits क्रम a top level gendisk and a bottom level
 *    block_device.
 */
व्योम disk_stack_limits(काष्ठा gendisk *disk, काष्ठा block_device *bdev,
		       sector_t offset)
अणु
	काष्ठा request_queue *t = disk->queue;

	अगर (blk_stack_limits(&t->limits, &bdev_get_queue(bdev)->limits,
			get_start_sect(bdev) + (offset >> 9)) < 0) अणु
		अक्षर top[BDEVNAME_SIZE], bottom[BDEVNAME_SIZE];

		disk_name(disk, 0, top);
		bdevname(bdev, bottom);

		prपूर्णांकk(KERN_NOTICE "%s: Warning: Device %s is misaligned\n",
		       top, bottom);
	पूर्ण

	blk_queue_update_पढ़ोahead(disk->queue);
पूर्ण
EXPORT_SYMBOL(disk_stack_limits);

/**
 * blk_queue_update_dma_pad - update pad mask
 * @q:     the request queue क्रम the device
 * @mask:  pad mask
 *
 * Update dma pad mask.
 *
 * Appending pad buffer to a request modअगरies the last entry of a
 * scatter list such that it includes the pad buffer.
 **/
व्योम blk_queue_update_dma_pad(काष्ठा request_queue *q, अचिन्हित पूर्णांक mask)
अणु
	अगर (mask > q->dma_pad_mask)
		q->dma_pad_mask = mask;
पूर्ण
EXPORT_SYMBOL(blk_queue_update_dma_pad);

/**
 * blk_queue_segment_boundary - set boundary rules क्रम segment merging
 * @q:  the request queue क्रम the device
 * @mask:  the memory boundary mask
 **/
व्योम blk_queue_segment_boundary(काष्ठा request_queue *q, अचिन्हित दीर्घ mask)
अणु
	अगर (mask < PAGE_SIZE - 1) अणु
		mask = PAGE_SIZE - 1;
		prपूर्णांकk(KERN_INFO "%s: set to minimum %lx\n",
		       __func__, mask);
	पूर्ण

	q->limits.seg_boundary_mask = mask;
पूर्ण
EXPORT_SYMBOL(blk_queue_segment_boundary);

/**
 * blk_queue_virt_boundary - set boundary rules क्रम bio merging
 * @q:  the request queue क्रम the device
 * @mask:  the memory boundary mask
 **/
व्योम blk_queue_virt_boundary(काष्ठा request_queue *q, अचिन्हित दीर्घ mask)
अणु
	q->limits.virt_boundary_mask = mask;

	/*
	 * Devices that require a भव boundary करो not support scatter/gather
	 * I/O natively, but instead require a descriptor list entry क्रम each
	 * page (which might not be idential to the Linux PAGE_SIZE).  Because
	 * of that they are not limited by our notion of "segment size".
	 */
	अगर (mask)
		q->limits.max_segment_size = अच_पूर्णांक_उच्च;
पूर्ण
EXPORT_SYMBOL(blk_queue_virt_boundary);

/**
 * blk_queue_dma_alignment - set dma length and memory alignment
 * @q:     the request queue क्रम the device
 * @mask:  alignment mask
 *
 * description:
 *    set required memory and length alignment क्रम direct dma transactions.
 *    this is used when building direct io requests क्रम the queue.
 *
 **/
व्योम blk_queue_dma_alignment(काष्ठा request_queue *q, पूर्णांक mask)
अणु
	q->dma_alignment = mask;
पूर्ण
EXPORT_SYMBOL(blk_queue_dma_alignment);

/**
 * blk_queue_update_dma_alignment - update dma length and memory alignment
 * @q:     the request queue क्रम the device
 * @mask:  alignment mask
 *
 * description:
 *    update required memory and length alignment क्रम direct dma transactions.
 *    If the requested alignment is larger than the current alignment, then
 *    the current queue alignment is updated to the new value, otherwise it
 *    is left alone.  The design of this is to allow multiple objects
 *    (driver, device, transport etc) to set their respective
 *    alignments without having them पूर्णांकerfere.
 *
 **/
व्योम blk_queue_update_dma_alignment(काष्ठा request_queue *q, पूर्णांक mask)
अणु
	BUG_ON(mask > PAGE_SIZE);

	अगर (mask > q->dma_alignment)
		q->dma_alignment = mask;
पूर्ण
EXPORT_SYMBOL(blk_queue_update_dma_alignment);

/**
 * blk_set_queue_depth - tell the block layer about the device queue depth
 * @q:		the request queue क्रम the device
 * @depth:		queue depth
 *
 */
व्योम blk_set_queue_depth(काष्ठा request_queue *q, अचिन्हित पूर्णांक depth)
अणु
	q->queue_depth = depth;
	rq_qos_queue_depth_changed(q);
पूर्ण
EXPORT_SYMBOL(blk_set_queue_depth);

/**
 * blk_queue_ग_लिखो_cache - configure queue's ग_लिखो cache
 * @q:		the request queue क्रम the device
 * @wc:		ग_लिखो back cache on or off
 * @fua:	device supports FUA ग_लिखोs, अगर true
 *
 * Tell the block layer about the ग_लिखो cache of @q.
 */
व्योम blk_queue_ग_लिखो_cache(काष्ठा request_queue *q, bool wc, bool fua)
अणु
	अगर (wc)
		blk_queue_flag_set(QUEUE_FLAG_WC, q);
	अन्यथा
		blk_queue_flag_clear(QUEUE_FLAG_WC, q);
	अगर (fua)
		blk_queue_flag_set(QUEUE_FLAG_FUA, q);
	अन्यथा
		blk_queue_flag_clear(QUEUE_FLAG_FUA, q);

	wbt_set_ग_लिखो_cache(q, test_bit(QUEUE_FLAG_WC, &q->queue_flags));
पूर्ण
EXPORT_SYMBOL_GPL(blk_queue_ग_लिखो_cache);

/**
 * blk_queue_required_elevator_features - Set a queue required elevator features
 * @q:		the request queue क्रम the target device
 * @features:	Required elevator features OR'ed together
 *
 * Tell the block layer that क्रम the device controlled through @q, only the
 * only elevators that can be used are those that implement at least the set of
 * features specअगरied by @features.
 */
व्योम blk_queue_required_elevator_features(काष्ठा request_queue *q,
					  अचिन्हित पूर्णांक features)
अणु
	q->required_elevator_features = features;
पूर्ण
EXPORT_SYMBOL_GPL(blk_queue_required_elevator_features);

/**
 * blk_queue_can_use_dma_map_merging - configure queue क्रम merging segments.
 * @q:		the request queue क्रम the device
 * @dev:	the device poपूर्णांकer क्रम dma
 *
 * Tell the block layer about merging the segments by dma map of @q.
 */
bool blk_queue_can_use_dma_map_merging(काष्ठा request_queue *q,
				       काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ boundary = dma_get_merge_boundary(dev);

	अगर (!boundary)
		वापस false;

	/* No need to update max_segment_size. see blk_queue_virt_boundary() */
	blk_queue_virt_boundary(q, boundary);

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(blk_queue_can_use_dma_map_merging);

/**
 * blk_queue_set_zoned - configure a disk queue zoned model.
 * @disk:	the gendisk of the queue to configure
 * @model:	the zoned model to set
 *
 * Set the zoned model of the request queue of @disk according to @model.
 * When @model is BLK_ZONED_HM (host managed), this should be called only
 * अगर zoned block device support is enabled (CONFIG_BLK_DEV_ZONED option).
 * If @model specअगरies BLK_ZONED_HA (host aware), the effective model used
 * depends on CONFIG_BLK_DEV_ZONED settings and on the existence of partitions
 * on the disk.
 */
व्योम blk_queue_set_zoned(काष्ठा gendisk *disk, क्रमागत blk_zoned_model model)
अणु
	काष्ठा request_queue *q = disk->queue;

	चयन (model) अणु
	हाल BLK_ZONED_HM:
		/*
		 * Host managed devices are supported only अगर
		 * CONFIG_BLK_DEV_ZONED is enabled.
		 */
		WARN_ON_ONCE(!IS_ENABLED(CONFIG_BLK_DEV_ZONED));
		अवरोध;
	हाल BLK_ZONED_HA:
		/*
		 * Host aware devices can be treated either as regular block
		 * devices (similar to drive managed devices) or as zoned block
		 * devices to take advantage of the zone command set, similarly
		 * to host managed devices. We try the latter अगर there are no
		 * partitions and zoned block device support is enabled, अन्यथा
		 * we करो nothing special as far as the block layer is concerned.
		 */
		अगर (!IS_ENABLED(CONFIG_BLK_DEV_ZONED) ||
		    !xa_empty(&disk->part_tbl))
			model = BLK_ZONED_NONE;
		अवरोध;
	हाल BLK_ZONED_NONE:
	शेष:
		अगर (WARN_ON_ONCE(model != BLK_ZONED_NONE))
			model = BLK_ZONED_NONE;
		अवरोध;
	पूर्ण

	q->limits.zoned = model;
	अगर (model != BLK_ZONED_NONE) अणु
		/*
		 * Set the zone ग_लिखो granularity to the device logical block
		 * size by शेष. The driver can change this value अगर needed.
		 */
		blk_queue_zone_ग_लिखो_granularity(q,
						queue_logical_block_size(q));
	पूर्ण अन्यथा अणु
		blk_queue_clear_zone_settings(q);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(blk_queue_set_zoned);
