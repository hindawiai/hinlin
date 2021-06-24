<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * generic helper functions क्रम handling video4linux capture buffers
 *
 * (c) 2007 Mauro Carvalho Chehab, <mchehab@kernel.org>
 *
 * Highly based on video-buf written originally by:
 * (c) 2001,02 Gerd Knorr <kraxel@bytesex.org>
 * (c) 2006 Mauro Carvalho Chehab, <mchehab@kernel.org>
 * (c) 2006 Ted Walther and John Sokol
 */

#अगर_अघोषित _VIDEOBUF_CORE_H
#घोषणा _VIDEOBUF_CORE_H

#समावेश <linux/poll.h>
#समावेश <linux/videodev2.h>

#घोषणा UNSET (-1U)


काष्ठा videobuf_buffer;
काष्ठा videobuf_queue;

/* --------------------------------------------------------------------- */

/*
 * A small set of helper functions to manage video4linux buffers.
 *
 * काष्ठा videobuf_buffer holds the data काष्ठाures used by the helper
 * functions, additionally some commonly used fields क्रम v4l buffers
 * (width, height, lists, रुकोqueue) are in there.  That काष्ठा should
 * be used as first element in the drivers buffer काष्ठा.
 *
 * about the mmap helpers (videobuf_mmap_*):
 *
 * The mmaper function allows to map any subset of contiguous buffers.
 * This includes one mmap() call क्रम all buffers (which the original
 * video4linux API uses) as well as one mmap() क्रम every single buffer
 * (which v4l2 uses).
 *
 * If there is a valid mapping क्रम a buffer, buffer->baddr/bsize holds
 * userspace address + size which can be fed पूर्णांकo the
 * videobuf_dma_init_user function listed above.
 *
 */

काष्ठा videobuf_mapping अणु
	अचिन्हित पूर्णांक count;
	काष्ठा videobuf_queue *q;
पूर्ण;

क्रमागत videobuf_state अणु
	VIDEOBUF_NEEDS_INIT = 0,
	VIDEOBUF_PREPARED   = 1,
	VIDEOBUF_QUEUED     = 2,
	VIDEOBUF_ACTIVE     = 3,
	VIDEOBUF_DONE       = 4,
	VIDEOBUF_ERROR      = 5,
	VIDEOBUF_IDLE       = 6,
पूर्ण;

काष्ठा videobuf_buffer अणु
	अचिन्हित पूर्णांक            i;
	u32                     magic;

	/* info about the buffer */
	अचिन्हित पूर्णांक            width;
	अचिन्हित पूर्णांक            height;
	अचिन्हित पूर्णांक            bytesperline; /* use only अगर != 0 */
	अचिन्हित दीर्घ           size;
	क्रमागत v4l2_field         field;
	क्रमागत videobuf_state     state;
	काष्ठा list_head        stream;  /* QBUF/DQBUF list */

	/* touched by irq handler */
	काष्ठा list_head        queue;
	रुको_queue_head_t       करोne;
	अचिन्हित पूर्णांक            field_count;
	u64			ts;

	/* Memory type */
	क्रमागत v4l2_memory        memory;

	/* buffer size */
	माप_प्रकार                  bsize;

	/* buffer offset (mmap + overlay) */
	माप_प्रकार                  boff;

	/* buffer addr (userland ptr!) */
	अचिन्हित दीर्घ           baddr;

	/* क्रम mmap'ed buffers */
	काष्ठा videobuf_mapping *map;

	/* Private poपूर्णांकer to allow specअगरic methods to store their data */
	पूर्णांक			privsize;
	व्योम                    *priv;
पूर्ण;

काष्ठा videobuf_queue_ops अणु
	पूर्णांक (*buf_setup)(काष्ठा videobuf_queue *q,
			 अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक *size);
	पूर्णांक (*buf_prepare)(काष्ठा videobuf_queue *q,
			   काष्ठा videobuf_buffer *vb,
			   क्रमागत v4l2_field field);
	व्योम (*buf_queue)(काष्ठा videobuf_queue *q,
			  काष्ठा videobuf_buffer *vb);
	व्योम (*buf_release)(काष्ठा videobuf_queue *q,
			    काष्ठा videobuf_buffer *vb);
पूर्ण;

#घोषणा MAGIC_QTYPE_OPS	0x12261003

/* Helper operations - device type dependent */
काष्ठा videobuf_qtype_ops अणु
	u32                     magic;

	काष्ठा videobuf_buffer *(*alloc_vb)(माप_प्रकार size);
	व्योम *(*vaddr)		(काष्ठा videobuf_buffer *buf);
	पूर्णांक (*iolock)		(काष्ठा videobuf_queue *q,
				 काष्ठा videobuf_buffer *vb,
				 काष्ठा v4l2_framebuffer *fbuf);
	पूर्णांक (*sync)		(काष्ठा videobuf_queue *q,
				 काष्ठा videobuf_buffer *buf);
	पूर्णांक (*mmap_mapper)	(काष्ठा videobuf_queue *q,
				 काष्ठा videobuf_buffer *buf,
				 काष्ठा vm_area_काष्ठा *vma);
पूर्ण;

काष्ठा videobuf_queue अणु
	काष्ठा mutex               vb_lock;
	काष्ठा mutex               *ext_lock;
	spinlock_t                 *irqlock;
	काष्ठा device		   *dev;

	रुको_queue_head_t	   रुको; /* रुको अगर queue is empty */

	क्रमागत v4l2_buf_type         type;
	अचिन्हित पूर्णांक               msize;
	क्रमागत v4l2_field            field;
	क्रमागत v4l2_field            last;   /* क्रम field=V4L2_FIELD_ALTERNATE */
	काष्ठा videobuf_buffer     *bufs[VIDEO_MAX_FRAME];
	स्थिर काष्ठा videobuf_queue_ops  *ops;
	काष्ठा videobuf_qtype_ops  *पूर्णांक_ops;

	अचिन्हित पूर्णांक               streaming:1;
	अचिन्हित पूर्णांक               पढ़ोing:1;

	/* capture via mmap() + ioctl(QBUF/DQBUF) */
	काष्ठा list_head           stream;

	/* capture via पढ़ो() */
	अचिन्हित पूर्णांक               पढ़ो_off;
	काष्ठा videobuf_buffer     *पढ़ो_buf;

	/* driver निजी data */
	व्योम                       *priv_data;
पूर्ण;

अटल अंतरभूत व्योम videobuf_queue_lock(काष्ठा videobuf_queue *q)
अणु
	अगर (!q->ext_lock)
		mutex_lock(&q->vb_lock);
पूर्ण

अटल अंतरभूत व्योम videobuf_queue_unlock(काष्ठा videobuf_queue *q)
अणु
	अगर (!q->ext_lock)
		mutex_unlock(&q->vb_lock);
पूर्ण

पूर्णांक videobuf_रुकोon(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb,
		पूर्णांक non_blocking, पूर्णांक पूर्णांकr);
पूर्णांक videobuf_iolock(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb,
		काष्ठा v4l2_framebuffer *fbuf);

काष्ठा videobuf_buffer *videobuf_alloc_vb(काष्ठा videobuf_queue *q);

/* Used on videobuf-dvb */
व्योम *videobuf_queue_to_vaddr(काष्ठा videobuf_queue *q,
			      काष्ठा videobuf_buffer *buf);

व्योम videobuf_queue_core_init(काष्ठा videobuf_queue *q,
			 स्थिर काष्ठा videobuf_queue_ops *ops,
			 काष्ठा device *dev,
			 spinlock_t *irqlock,
			 क्रमागत v4l2_buf_type type,
			 क्रमागत v4l2_field field,
			 अचिन्हित पूर्णांक msize,
			 व्योम *priv,
			 काष्ठा videobuf_qtype_ops *पूर्णांक_ops,
			 काष्ठा mutex *ext_lock);
पूर्णांक  videobuf_queue_is_busy(काष्ठा videobuf_queue *q);
व्योम videobuf_queue_cancel(काष्ठा videobuf_queue *q);

क्रमागत v4l2_field videobuf_next_field(काष्ठा videobuf_queue *q);
पूर्णांक videobuf_reqbufs(काष्ठा videobuf_queue *q,
		     काष्ठा v4l2_requestbuffers *req);
पूर्णांक videobuf_querybuf(काष्ठा videobuf_queue *q, काष्ठा v4l2_buffer *b);
पूर्णांक videobuf_qbuf(काष्ठा videobuf_queue *q,
		  काष्ठा v4l2_buffer *b);
पूर्णांक videobuf_dqbuf(काष्ठा videobuf_queue *q,
		   काष्ठा v4l2_buffer *b, पूर्णांक nonblocking);
पूर्णांक videobuf_streamon(काष्ठा videobuf_queue *q);
पूर्णांक videobuf_streamoff(काष्ठा videobuf_queue *q);

व्योम videobuf_stop(काष्ठा videobuf_queue *q);

पूर्णांक videobuf_पढ़ो_start(काष्ठा videobuf_queue *q);
व्योम videobuf_पढ़ो_stop(काष्ठा videobuf_queue *q);
sमाप_प्रकार videobuf_पढ़ो_stream(काष्ठा videobuf_queue *q,
			     अक्षर __user *data, माप_प्रकार count, loff_t *ppos,
			     पूर्णांक vbihack, पूर्णांक nonblocking);
sमाप_प्रकार videobuf_पढ़ो_one(काष्ठा videobuf_queue *q,
			  अक्षर __user *data, माप_प्रकार count, loff_t *ppos,
			  पूर्णांक nonblocking);
__poll_t videobuf_poll_stream(काष्ठा file *file,
				  काष्ठा videobuf_queue *q,
				  poll_table *रुको);

पूर्णांक videobuf_mmap_setup(काष्ठा videobuf_queue *q,
			अचिन्हित पूर्णांक bcount, अचिन्हित पूर्णांक bsize,
			क्रमागत v4l2_memory memory);
पूर्णांक __videobuf_mmap_setup(काष्ठा videobuf_queue *q,
			अचिन्हित पूर्णांक bcount, अचिन्हित पूर्णांक bsize,
			क्रमागत v4l2_memory memory);
पूर्णांक videobuf_mmap_मुक्त(काष्ठा videobuf_queue *q);
पूर्णांक videobuf_mmap_mapper(काष्ठा videobuf_queue *q,
			 काष्ठा vm_area_काष्ठा *vma);

#पूर्ण_अगर
