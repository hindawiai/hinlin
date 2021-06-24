<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2013-2015 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित __INDUSTRIALIO_DMA_BUFFER_H__
#घोषणा __INDUSTRIALIO_DMA_BUFFER_H__

#समावेश <linux/list.h>
#समावेश <linux/kref.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/iio/buffer_impl.h>

काष्ठा iio_dma_buffer_queue;
काष्ठा iio_dma_buffer_ops;
काष्ठा device;

काष्ठा iio_buffer_block अणु
	u32 size;
	u32 bytes_used;
पूर्ण;

/**
 * क्रमागत iio_block_state - State of a काष्ठा iio_dma_buffer_block
 * @IIO_BLOCK_STATE_DEQUEUED: Block is not queued
 * @IIO_BLOCK_STATE_QUEUED: Block is on the incoming queue
 * @IIO_BLOCK_STATE_ACTIVE: Block is currently being processed by the DMA
 * @IIO_BLOCK_STATE_DONE: Block is on the outgoing queue
 * @IIO_BLOCK_STATE_DEAD: Block has been marked as to be मुक्तd
 */
क्रमागत iio_block_state अणु
	IIO_BLOCK_STATE_DEQUEUED,
	IIO_BLOCK_STATE_QUEUED,
	IIO_BLOCK_STATE_ACTIVE,
	IIO_BLOCK_STATE_DONE,
	IIO_BLOCK_STATE_DEAD,
पूर्ण;

/**
 * काष्ठा iio_dma_buffer_block - IIO buffer block
 * @head: List head
 * @size: Total size of the block in bytes
 * @bytes_used: Number of bytes that contain valid data
 * @vaddr: Virutal address of the blocks memory
 * @phys_addr: Physical address of the blocks memory
 * @queue: Parent DMA buffer queue
 * @kref: kref used to manage the lअगरeसमय of block
 * @state: Current state of the block
 */
काष्ठा iio_dma_buffer_block अणु
	/* May only be accessed by the owner of the block */
	काष्ठा list_head head;
	माप_प्रकार bytes_used;

	/*
	 * Set during allocation, स्थिरant thereafter. May be accessed पढ़ो-only
	 * by anybody holding a reference to the block.
	 */
	व्योम *vaddr;
	dma_addr_t phys_addr;
	माप_प्रकार size;
	काष्ठा iio_dma_buffer_queue *queue;

	/* Must not be accessed outside the core. */
	काष्ठा kref kref;
	/*
	 * Must not be accessed outside the core. Access needs to hold
	 * queue->list_lock अगर the block is not owned by the core.
	 */
	क्रमागत iio_block_state state;
पूर्ण;

/**
 * काष्ठा iio_dma_buffer_queue_fileio - FileIO state क्रम the DMA buffer
 * @blocks: Buffer blocks used क्रम fileio
 * @active_block: Block being used in पढ़ो()
 * @pos: Read offset in the active block
 * @block_size: Size of each block
 */
काष्ठा iio_dma_buffer_queue_fileio अणु
	काष्ठा iio_dma_buffer_block *blocks[2];
	काष्ठा iio_dma_buffer_block *active_block;
	माप_प्रकार pos;
	माप_प्रकार block_size;
पूर्ण;

/**
 * काष्ठा iio_dma_buffer_queue - DMA buffer base काष्ठाure
 * @buffer: IIO buffer base काष्ठाure
 * @dev: Parent device
 * @ops: DMA buffer callbacks
 * @lock: Protects the incoming list, active and the fields in the fileio
 *   subकाष्ठा
 * @list_lock: Protects lists that contain blocks which can be modअगरied in
 *   atomic context as well as blocks on those lists. This is the outgoing queue
 *   list and typically also a list of active blocks in the part that handles
 *   the DMA controller
 * @incoming: List of buffers on the incoming queue
 * @outgoing: List of buffers on the outgoing queue
 * @active: Whether the buffer is currently active
 * @fileio: FileIO state
 */
काष्ठा iio_dma_buffer_queue अणु
	काष्ठा iio_buffer buffer;
	काष्ठा device *dev;
	स्थिर काष्ठा iio_dma_buffer_ops *ops;

	काष्ठा mutex lock;
	spinlock_t list_lock;
	काष्ठा list_head incoming;
	काष्ठा list_head outgoing;

	bool active;

	काष्ठा iio_dma_buffer_queue_fileio fileio;
पूर्ण;

/**
 * काष्ठा iio_dma_buffer_ops - DMA buffer callback operations
 * @submit: Called when a block is submitted to the DMA controller
 * @पात: Should पात all pending transfers
 */
काष्ठा iio_dma_buffer_ops अणु
	पूर्णांक (*submit)(काष्ठा iio_dma_buffer_queue *queue,
		काष्ठा iio_dma_buffer_block *block);
	व्योम (*पात)(काष्ठा iio_dma_buffer_queue *queue);
पूर्ण;

व्योम iio_dma_buffer_block_करोne(काष्ठा iio_dma_buffer_block *block);
व्योम iio_dma_buffer_block_list_पात(काष्ठा iio_dma_buffer_queue *queue,
	काष्ठा list_head *list);

पूर्णांक iio_dma_buffer_enable(काष्ठा iio_buffer *buffer,
	काष्ठा iio_dev *indio_dev);
पूर्णांक iio_dma_buffer_disable(काष्ठा iio_buffer *buffer,
	काष्ठा iio_dev *indio_dev);
पूर्णांक iio_dma_buffer_पढ़ो(काष्ठा iio_buffer *buffer, माप_प्रकार n,
	अक्षर __user *user_buffer);
माप_प्रकार iio_dma_buffer_data_available(काष्ठा iio_buffer *buffer);
पूर्णांक iio_dma_buffer_set_bytes_per_datum(काष्ठा iio_buffer *buffer, माप_प्रकार bpd);
पूर्णांक iio_dma_buffer_set_length(काष्ठा iio_buffer *buffer, अचिन्हित पूर्णांक length);
पूर्णांक iio_dma_buffer_request_update(काष्ठा iio_buffer *buffer);

पूर्णांक iio_dma_buffer_init(काष्ठा iio_dma_buffer_queue *queue,
	काष्ठा device *dma_dev, स्थिर काष्ठा iio_dma_buffer_ops *ops);
व्योम iio_dma_buffer_निकास(काष्ठा iio_dma_buffer_queue *queue);
व्योम iio_dma_buffer_release(काष्ठा iio_dma_buffer_queue *queue);

#पूर्ण_अगर
