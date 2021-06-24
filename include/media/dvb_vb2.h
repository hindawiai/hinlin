<शैली गुरु>
/*
 * SPDX-License-Identअगरier: GPL-2.0
 *
 * dvb-vb2.h - DVB driver helper framework क्रम streaming I/O
 *
 * Copyright (C) 2015 Samsung Electronics
 *
 * Author: jh1009.sung@samsung.com
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित _DVB_VB2_H
#घोषणा _DVB_VB2_H

#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/dvb/dmx.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

/**
 * क्रमागत dvb_buf_type - types of Digital TV memory-mapped buffers
 *
 * @DVB_BUF_TYPE_CAPTURE: buffer is filled by the Kernel,
 *			  with a received Digital TV stream
 */
क्रमागत dvb_buf_type अणु
	DVB_BUF_TYPE_CAPTURE        = 1,
पूर्ण;

/**
 * क्रमागत dvb_vb2_states - states to control VB2 state machine
 * @DVB_VB2_STATE_NONE:
 *	VB2 engine not initialized yet, init failed or VB2 was released.
 * @DVB_VB2_STATE_INIT:
 *	VB2 engine initialized.
 * @DVB_VB2_STATE_REQBUFS:
 *	Buffers were requested
 * @DVB_VB2_STATE_STREAMON:
 *	VB2 is streaming. Callers should not check it directly. Instead,
 *	they should use dvb_vb2_is_streaming().
 *
 * Note:
 *
 * Callers should not touch at the state machine directly. This
 * is handled inside dvb_vb2.c.
 */
क्रमागत dvb_vb2_states अणु
	DVB_VB2_STATE_NONE	= 0x0,
	DVB_VB2_STATE_INIT	= 0x1,
	DVB_VB2_STATE_REQBUFS	= 0x2,
	DVB_VB2_STATE_STREAMON	= 0x4,
पूर्ण;

#घोषणा DVB_VB2_NAME_MAX (20)

/**
 * काष्ठा dvb_buffer - video buffer inक्रमmation क्रम v4l2.
 *
 * @vb:		embedded काष्ठा &vb2_buffer.
 * @list:	list of &काष्ठा dvb_buffer.
 */
काष्ठा dvb_buffer अणु
	काष्ठा vb2_buffer	vb;
	काष्ठा list_head	list;
पूर्ण;

/**
 * काष्ठा dvb_vb2_ctx - control काष्ठा क्रम VB2 handler
 * @vb_q:	poपूर्णांकer to &काष्ठा vb2_queue with videobuf2 queue.
 * @mutex:	mutex to serialize vb2 operations. Used by
 *		vb2 core %रुको_prepare and %रुको_finish operations.
 * @slock:	spin lock used to protect buffer filling at dvb_vb2.c.
 * @dvb_q:	List of buffers that are not filled yet.
 * @buf:	Poपूर्णांकer to the buffer that are currently being filled.
 * @offset:	index to the next position at the @buf to be filled.
 * @reमुख्य:	How many bytes are left to be filled at @buf.
 * @state:	biपंचांगask of buffer states as defined by &क्रमागत dvb_vb2_states.
 * @buf_siz:	size of each VB2 buffer.
 * @buf_cnt:	number of VB2 buffers.
 * @nonblocking:
 *		If dअगरferent than zero, device is operating on non-blocking
 *		mode.
 * @flags:	buffer flags as defined by &क्रमागत dmx_buffer_flags.
 *		Filled only at &DMX_DQBUF. &DMX_QBUF should zero this field.
 * @count:	monotonic counter क्रम filled buffers. Helps to identअगरy
 *		data stream loses. Filled only at &DMX_DQBUF. &DMX_QBUF should
 *		zero this field.
 *
 * @name:	name of the device type. Currently, it can either be
 *		"dvr" or "demux_filter".
 */
काष्ठा dvb_vb2_ctx अणु
	काष्ठा vb2_queue	vb_q;
	काष्ठा mutex		mutex;
	spinlock_t		slock;
	काष्ठा list_head	dvb_q;
	काष्ठा dvb_buffer	*buf;
	पूर्णांक	offset;
	पूर्णांक	reमुख्य;
	पूर्णांक	state;
	पूर्णांक	buf_siz;
	पूर्णांक	buf_cnt;
	पूर्णांक	nonblocking;

	क्रमागत dmx_buffer_flags flags;
	u32	count;

	अक्षर	name[DVB_VB2_NAME_MAX + 1];
पूर्ण;

#अगर_अघोषित CONFIG_DVB_MMAP
अटल अंतरभूत पूर्णांक dvb_vb2_init(काष्ठा dvb_vb2_ctx *ctx,
			       स्थिर अक्षर *name, पूर्णांक non_blocking)
अणु
	वापस 0;
पूर्ण;
अटल अंतरभूत पूर्णांक dvb_vb2_release(काष्ठा dvb_vb2_ctx *ctx)
अणु
	वापस 0;
पूर्ण;
#घोषणा dvb_vb2_is_streaming(ctx) (0)
#घोषणा dvb_vb2_fill_buffer(ctx, file, रुको, flags) (0)

अटल अंतरभूत __poll_t dvb_vb2_poll(काष्ठा dvb_vb2_ctx *ctx,
				    काष्ठा file *file,
				    poll_table *रुको)
अणु
	वापस 0;
पूर्ण
#अन्यथा
/**
 * dvb_vb2_init - initializes VB2 handler
 *
 * @ctx:	control काष्ठा क्रम VB2 handler
 * @name:	name क्रम the VB2 handler
 * @non_blocking:
 *		अगर not zero, it means that the device is at non-blocking mode
 */
पूर्णांक dvb_vb2_init(काष्ठा dvb_vb2_ctx *ctx, स्थिर अक्षर *name, पूर्णांक non_blocking);

/**
 * dvb_vb2_release - Releases the VB2 handler allocated resources and
 *	put @ctx at DVB_VB2_STATE_NONE state.
 * @ctx:	control काष्ठा क्रम VB2 handler
 */
पूर्णांक dvb_vb2_release(काष्ठा dvb_vb2_ctx *ctx);

/**
 * dvb_vb2_is_streaming - checks अगर the VB2 handler is streaming
 * @ctx:	control काष्ठा क्रम VB2 handler
 *
 * Return: 0 अगर not streaming, 1 otherwise.
 */
पूर्णांक dvb_vb2_is_streaming(काष्ठा dvb_vb2_ctx *ctx);

/**
 * dvb_vb2_fill_buffer - fills a VB2 buffer
 * @ctx:	control काष्ठा क्रम VB2 handler
 * @src:	place where the data is stored
 * @len:	number of bytes to be copied from @src
 * @buffer_flags:
 *		poपूर्णांकer to buffer flags as defined by &क्रमागत dmx_buffer_flags.
 *		can be शून्य.
 */
पूर्णांक dvb_vb2_fill_buffer(काष्ठा dvb_vb2_ctx *ctx,
			स्थिर अचिन्हित अक्षर *src, पूर्णांक len,
			क्रमागत dmx_buffer_flags *buffer_flags);

/**
 * dvb_vb2_poll - Wrapper to vb2_core_streamon() क्रम Digital TV
 *      buffer handling.
 *
 * @ctx:	control काष्ठा क्रम VB2 handler
 * @file:	&काष्ठा file argument passed to the poll
 *		file operation handler.
 * @रुको:	&poll_table रुको argument passed to the poll
 *		file operation handler.
 *
 * Implements poll syscall() logic.
 */
__poll_t dvb_vb2_poll(काष्ठा dvb_vb2_ctx *ctx, काष्ठा file *file,
		      poll_table *रुको);
#पूर्ण_अगर

/**
 * dvb_vb2_stream_on() - Wrapper to vb2_core_streamon() क्रम Digital TV
 *	buffer handling.
 *
 * @ctx:	control काष्ठा क्रम VB2 handler
 *
 * Starts dvb streaming
 */
पूर्णांक dvb_vb2_stream_on(काष्ठा dvb_vb2_ctx *ctx);
/**
 * dvb_vb2_stream_off() - Wrapper to vb2_core_streamoff() क्रम Digital TV
 *	buffer handling.
 *
 * @ctx:	control काष्ठा क्रम VB2 handler
 *
 * Stops dvb streaming
 */
पूर्णांक dvb_vb2_stream_off(काष्ठा dvb_vb2_ctx *ctx);

/**
 * dvb_vb2_reqbufs() - Wrapper to vb2_core_reqbufs() क्रम Digital TV
 *	buffer handling.
 *
 * @ctx:	control काष्ठा क्रम VB2 handler
 * @req:	&काष्ठा dmx_requestbuffers passed from userspace in
 *		order to handle &DMX_REQBUFS.
 *
 * Initiate streaming by requesting a number of buffers. Also used to
 * मुक्त previously requested buffers, is ``req->count`` is zero.
 */
पूर्णांक dvb_vb2_reqbufs(काष्ठा dvb_vb2_ctx *ctx, काष्ठा dmx_requestbuffers *req);

/**
 * dvb_vb2_querybuf() - Wrapper to vb2_core_querybuf() क्रम Digital TV
 *	buffer handling.
 *
 * @ctx:	control काष्ठा क्रम VB2 handler
 * @b:		&काष्ठा dmx_buffer passed from userspace in
 *		order to handle &DMX_QUERYBUF.
 *
 *
 */
पूर्णांक dvb_vb2_querybuf(काष्ठा dvb_vb2_ctx *ctx, काष्ठा dmx_buffer *b);

/**
 * dvb_vb2_expbuf() - Wrapper to vb2_core_expbuf() क्रम Digital TV
 *	buffer handling.
 *
 * @ctx:	control काष्ठा क्रम VB2 handler
 * @exp:	&काष्ठा dmx_exportbuffer passed from userspace in
 *		order to handle &DMX_EXPBUF.
 *
 * Export a buffer as a file descriptor.
 */
पूर्णांक dvb_vb2_expbuf(काष्ठा dvb_vb2_ctx *ctx, काष्ठा dmx_exportbuffer *exp);

/**
 * dvb_vb2_qbuf() - Wrapper to vb2_core_qbuf() क्रम Digital TV buffer handling.
 *
 * @ctx:	control काष्ठा क्रम VB2 handler
 * @b:		&काष्ठा dmx_buffer passed from userspace in
 *		order to handle &DMX_QBUF.
 *
 * Queue a Digital TV buffer as requested by userspace
 */
पूर्णांक dvb_vb2_qbuf(काष्ठा dvb_vb2_ctx *ctx, काष्ठा dmx_buffer *b);

/**
 * dvb_vb2_dqbuf() - Wrapper to vb2_core_dqbuf() क्रम Digital TV
 *	buffer handling.
 *
 * @ctx:	control काष्ठा क्रम VB2 handler
 * @b:		&काष्ठा dmx_buffer passed from userspace in
 *		order to handle &DMX_DQBUF.
 *
 * Dequeue a Digital TV buffer to the userspace
 */
पूर्णांक dvb_vb2_dqbuf(काष्ठा dvb_vb2_ctx *ctx, काष्ठा dmx_buffer *b);

/**
 * dvb_vb2_mmap() - Wrapper to vb2_mmap() क्रम Digital TV buffer handling.
 *
 * @ctx:	control काष्ठा क्रम VB2 handler
 * @vma:        poपूर्णांकer to &काष्ठा vm_area_काष्ठा with the vma passed
 *              to the mmap file operation handler in the driver.
 *
 * map Digital TV video buffers पूर्णांकo application address space.
 */
पूर्णांक dvb_vb2_mmap(काष्ठा dvb_vb2_ctx *ctx, काष्ठा vm_area_काष्ठा *vma);

#पूर्ण_अगर /* _DVB_VB2_H */
