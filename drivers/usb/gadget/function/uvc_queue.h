<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _UVC_QUEUE_H_
#घोषणा _UVC_QUEUE_H_

#समावेश <linux/list.h>
#समावेश <linux/poll.h>
#समावेश <linux/spinlock.h>

#समावेश <media/videobuf2-v4l2.h>

काष्ठा file;
काष्ठा mutex;

/* Maximum frame size in bytes, क्रम sanity checking. */
#घोषणा UVC_MAX_FRAME_SIZE	(16*1024*1024)
/* Maximum number of video buffers. */
#घोषणा UVC_MAX_VIDEO_BUFFERS	32

/* ------------------------------------------------------------------------
 * Structures.
 */

क्रमागत uvc_buffer_state अणु
	UVC_BUF_STATE_IDLE	= 0,
	UVC_BUF_STATE_QUEUED	= 1,
	UVC_BUF_STATE_ACTIVE	= 2,
	UVC_BUF_STATE_DONE	= 3,
	UVC_BUF_STATE_ERROR	= 4,
पूर्ण;

काष्ठा uvc_buffer अणु
	काष्ठा vb2_v4l2_buffer buf;
	काष्ठा list_head queue;

	क्रमागत uvc_buffer_state state;
	व्योम *mem;
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक bytesused;
पूर्ण;

#घोषणा UVC_QUEUE_DISCONNECTED		(1 << 0)
#घोषणा UVC_QUEUE_DROP_INCOMPLETE	(1 << 1)
#घोषणा UVC_QUEUE_PAUSED		(1 << 2)

काष्ठा uvc_video_queue अणु
	काष्ठा vb2_queue queue;

	अचिन्हित पूर्णांक flags;
	__u32 sequence;

	अचिन्हित पूर्णांक buf_used;

	spinlock_t irqlock;	/* Protects flags and irqqueue */
	काष्ठा list_head irqqueue;
पूर्ण;

अटल अंतरभूत पूर्णांक uvc_queue_streaming(काष्ठा uvc_video_queue *queue)
अणु
	वापस vb2_is_streaming(&queue->queue);
पूर्ण

पूर्णांक uvcg_queue_init(काष्ठा uvc_video_queue *queue, क्रमागत v4l2_buf_type type,
		    काष्ठा mutex *lock);

व्योम uvcg_मुक्त_buffers(काष्ठा uvc_video_queue *queue);

पूर्णांक uvcg_alloc_buffers(काष्ठा uvc_video_queue *queue,
		       काष्ठा v4l2_requestbuffers *rb);

पूर्णांक uvcg_query_buffer(काष्ठा uvc_video_queue *queue, काष्ठा v4l2_buffer *buf);

पूर्णांक uvcg_queue_buffer(काष्ठा uvc_video_queue *queue, काष्ठा v4l2_buffer *buf);

पूर्णांक uvcg_dequeue_buffer(काष्ठा uvc_video_queue *queue,
			काष्ठा v4l2_buffer *buf, पूर्णांक nonblocking);

__poll_t uvcg_queue_poll(काष्ठा uvc_video_queue *queue,
			     काष्ठा file *file, poll_table *रुको);

पूर्णांक uvcg_queue_mmap(काष्ठा uvc_video_queue *queue, काष्ठा vm_area_काष्ठा *vma);

#अगर_अघोषित CONFIG_MMU
अचिन्हित दीर्घ uvcg_queue_get_unmapped_area(काष्ठा uvc_video_queue *queue,
					   अचिन्हित दीर्घ pgoff);
#पूर्ण_अगर /* CONFIG_MMU */

व्योम uvcg_queue_cancel(काष्ठा uvc_video_queue *queue, पूर्णांक disconnect);

पूर्णांक uvcg_queue_enable(काष्ठा uvc_video_queue *queue, पूर्णांक enable);

काष्ठा uvc_buffer *uvcg_queue_next_buffer(काष्ठा uvc_video_queue *queue,
					  काष्ठा uvc_buffer *buf);

काष्ठा uvc_buffer *uvcg_queue_head(काष्ठा uvc_video_queue *queue);

#पूर्ण_अगर /* _UVC_QUEUE_H_ */

