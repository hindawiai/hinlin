<शैली गुरु>
/*
 * Copyright (C) 2009-2011 Red Hat, Inc.
 *
 * Author: Mikulas Patocka <mpatocka@redhat.com>
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित _LINUX_DM_BUFIO_H
#घोषणा _LINUX_DM_BUFIO_H

#समावेश <linux/blkdev.h>
#समावेश <linux/types.h>

/*----------------------------------------------------------------*/

काष्ठा dm_bufio_client;
काष्ठा dm_buffer;

/*
 * Create a buffered IO cache on a given device
 */
काष्ठा dm_bufio_client *
dm_bufio_client_create(काष्ठा block_device *bdev, अचिन्हित block_size,
		       अचिन्हित reserved_buffers, अचिन्हित aux_size,
		       व्योम (*alloc_callback)(काष्ठा dm_buffer *),
		       व्योम (*ग_लिखो_callback)(काष्ठा dm_buffer *));

/*
 * Release a buffered IO cache.
 */
व्योम dm_bufio_client_destroy(काष्ठा dm_bufio_client *c);

/*
 * Set the sector range.
 * When this function is called, there must be no I/O in progress on the bufio
 * client.
 */
व्योम dm_bufio_set_sector_offset(काष्ठा dm_bufio_client *c, sector_t start);

/*
 * WARNING: to aव्योम deadlocks, these conditions are observed:
 *
 * - At most one thपढ़ो can hold at most "reserved_buffers" simultaneously.
 * - Each other thपढ़ोs can hold at most one buffer.
 * - Thपढ़ोs which call only dm_bufio_get can hold unlimited number of
 *   buffers.
 */

/*
 * Read a given block from disk. Returns poपूर्णांकer to data.  Returns a
 * poपूर्णांकer to dm_buffer that can be used to release the buffer or to make
 * it dirty.
 */
व्योम *dm_bufio_पढ़ो(काष्ठा dm_bufio_client *c, sector_t block,
		    काष्ठा dm_buffer **bp);

/*
 * Like dm_bufio_पढ़ो, but वापस buffer from cache, करोn't पढ़ो
 * it. If the buffer is not in the cache, वापस शून्य.
 */
व्योम *dm_bufio_get(काष्ठा dm_bufio_client *c, sector_t block,
		   काष्ठा dm_buffer **bp);

/*
 * Like dm_bufio_पढ़ो, but करोn't पढ़ो anything from the disk.  It is
 * expected that the caller initializes the buffer and marks it dirty.
 */
व्योम *dm_bufio_new(काष्ठा dm_bufio_client *c, sector_t block,
		   काष्ठा dm_buffer **bp);

/*
 * Prefetch the specअगरied blocks to the cache.
 * The function starts to पढ़ो the blocks and वापसs without रुकोing क्रम
 * I/O to finish.
 */
व्योम dm_bufio_prefetch(काष्ठा dm_bufio_client *c,
		       sector_t block, अचिन्हित n_blocks);

/*
 * Release a reference obtained with dm_bufio_अणुपढ़ो,get,newपूर्ण. The data
 * poपूर्णांकer and dm_buffer poपूर्णांकer is no दीर्घer valid after this call.
 */
व्योम dm_bufio_release(काष्ठा dm_buffer *b);

/*
 * Mark a buffer dirty. It should be called after the buffer is modअगरied.
 *
 * In हाल of memory pressure, the buffer may be written after
 * dm_bufio_mark_buffer_dirty, but beक्रमe dm_bufio_ग_लिखो_dirty_buffers.  So
 * dm_bufio_ग_लिखो_dirty_buffers guarantees that the buffer is on-disk but
 * the actual writing may occur earlier.
 */
व्योम dm_bufio_mark_buffer_dirty(काष्ठा dm_buffer *b);

/*
 * Mark a part of the buffer dirty.
 *
 * The specअगरied part of the buffer is scheduled to be written. dm-bufio may
 * ग_लिखो the specअगरied part of the buffer or it may ग_लिखो a larger superset.
 */
व्योम dm_bufio_mark_partial_buffer_dirty(काष्ठा dm_buffer *b,
					अचिन्हित start, अचिन्हित end);

/*
 * Initiate writing of dirty buffers, without रुकोing क्रम completion.
 */
व्योम dm_bufio_ग_लिखो_dirty_buffers_async(काष्ठा dm_bufio_client *c);

/*
 * Write all dirty buffers. Guarantees that all dirty buffers created prior
 * to this call are on disk when this call निकासs.
 */
पूर्णांक dm_bufio_ग_लिखो_dirty_buffers(काष्ठा dm_bufio_client *c);

/*
 * Send an empty ग_लिखो barrier to the device to flush hardware disk cache.
 */
पूर्णांक dm_bufio_issue_flush(काष्ठा dm_bufio_client *c);

/*
 * Send a discard request to the underlying device.
 */
पूर्णांक dm_bufio_issue_discard(काष्ठा dm_bufio_client *c, sector_t block, sector_t count);

/*
 * Like dm_bufio_release but also move the buffer to the new
 * block. dm_bufio_ग_लिखो_dirty_buffers is needed to commit the new block.
 */
व्योम dm_bufio_release_move(काष्ठा dm_buffer *b, sector_t new_block);

/*
 * Free the given buffer.
 * This is just a hपूर्णांक, अगर the buffer is in use or dirty, this function
 * करोes nothing.
 */
व्योम dm_bufio_क्रमget(काष्ठा dm_bufio_client *c, sector_t block);

/*
 * Free the given range of buffers.
 * This is just a hपूर्णांक, अगर the buffer is in use or dirty, this function
 * करोes nothing.
 */
व्योम dm_bufio_क्रमget_buffers(काष्ठा dm_bufio_client *c, sector_t block, sector_t n_blocks);

/*
 * Set the minimum number of buffers beक्रमe cleanup happens.
 */
व्योम dm_bufio_set_minimum_buffers(काष्ठा dm_bufio_client *c, अचिन्हित n);

अचिन्हित dm_bufio_get_block_size(काष्ठा dm_bufio_client *c);
sector_t dm_bufio_get_device_size(काष्ठा dm_bufio_client *c);
काष्ठा dm_io_client *dm_bufio_get_dm_io_client(काष्ठा dm_bufio_client *c);
sector_t dm_bufio_get_block_number(काष्ठा dm_buffer *b);
व्योम *dm_bufio_get_block_data(काष्ठा dm_buffer *b);
व्योम *dm_bufio_get_aux_data(काष्ठा dm_buffer *b);
काष्ठा dm_bufio_client *dm_bufio_get_client(काष्ठा dm_buffer *b);

/*----------------------------------------------------------------*/

#पूर्ण_अगर
