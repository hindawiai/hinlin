<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
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

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <media/videobuf-core.h>
#समावेश <media/v4l2-common.h>

#घोषणा MAGIC_BUFFER 0x20070728
#घोषणा MAGIC_CHECK(is, should)						\
	करो अणु								\
		अगर (unlikely((is) != (should))) अणु			\
			prपूर्णांकk(KERN_ERR					\
				"magic mismatch: %x (expected %x)\n",	\
					is, should);			\
			BUG();						\
		पूर्ण							\
	पूर्ण जबतक (0)

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

MODULE_DESCRIPTION("helper module to manage video4linux buffers");
MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@kernel.org>");
MODULE_LICENSE("GPL");

#घोषणा dprपूर्णांकk(level, fmt, arg...)					\
	करो अणु								\
		अगर (debug >= level)					\
			prपूर्णांकk(KERN_DEBUG "vbuf: " fmt, ## arg);	\
	पूर्ण जबतक (0)

/* --------------------------------------------------------------------- */

#घोषणा CALL(q, f, arg...)						\
	((q->पूर्णांक_ops->f) ? q->पूर्णांक_ops->f(arg) : 0)
#घोषणा CALLPTR(q, f, arg...)						\
	((q->पूर्णांक_ops->f) ? q->पूर्णांक_ops->f(arg) : शून्य)

काष्ठा videobuf_buffer *videobuf_alloc_vb(काष्ठा videobuf_queue *q)
अणु
	काष्ठा videobuf_buffer *vb;

	BUG_ON(q->msize < माप(*vb));

	अगर (!q->पूर्णांक_ops || !q->पूर्णांक_ops->alloc_vb) अणु
		prपूर्णांकk(KERN_ERR "No specific ops defined!\n");
		BUG();
	पूर्ण

	vb = q->पूर्णांक_ops->alloc_vb(q->msize);
	अगर (शून्य != vb) अणु
		init_रुकोqueue_head(&vb->करोne);
		vb->magic = MAGIC_BUFFER;
	पूर्ण

	वापस vb;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_alloc_vb);

अटल पूर्णांक state_neither_active_nor_queued(काष्ठा videobuf_queue *q,
					   काष्ठा videobuf_buffer *vb)
अणु
	अचिन्हित दीर्घ flags;
	bool rc;

	spin_lock_irqsave(q->irqlock, flags);
	rc = vb->state != VIDEOBUF_ACTIVE && vb->state != VIDEOBUF_QUEUED;
	spin_unlock_irqrestore(q->irqlock, flags);
	वापस rc;
पूर्ण;

पूर्णांक videobuf_रुकोon(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb,
		पूर्णांक non_blocking, पूर्णांक पूर्णांकr)
अणु
	bool is_ext_locked;
	पूर्णांक ret = 0;

	MAGIC_CHECK(vb->magic, MAGIC_BUFFER);

	अगर (non_blocking) अणु
		अगर (state_neither_active_nor_queued(q, vb))
			वापस 0;
		वापस -EAGAIN;
	पूर्ण

	is_ext_locked = q->ext_lock && mutex_is_locked(q->ext_lock);

	/* Release vdev lock to prevent this रुको from blocking outside access to
	   the device. */
	अगर (is_ext_locked)
		mutex_unlock(q->ext_lock);
	अगर (पूर्णांकr)
		ret = रुको_event_पूर्णांकerruptible(vb->करोne,
					state_neither_active_nor_queued(q, vb));
	अन्यथा
		रुको_event(vb->करोne, state_neither_active_nor_queued(q, vb));
	/* Relock */
	अगर (is_ext_locked)
		mutex_lock(q->ext_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_रुकोon);

पूर्णांक videobuf_iolock(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb,
		    काष्ठा v4l2_framebuffer *fbuf)
अणु
	MAGIC_CHECK(vb->magic, MAGIC_BUFFER);
	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	वापस CALL(q, iolock, q, vb, fbuf);
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_iolock);

व्योम *videobuf_queue_to_vaddr(काष्ठा videobuf_queue *q,
			      काष्ठा videobuf_buffer *buf)
अणु
	अगर (q->पूर्णांक_ops->vaddr)
		वापस q->पूर्णांक_ops->vaddr(buf);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_queue_to_vaddr);

/* --------------------------------------------------------------------- */


व्योम videobuf_queue_core_init(काष्ठा videobuf_queue *q,
			 स्थिर काष्ठा videobuf_queue_ops *ops,
			 काष्ठा device *dev,
			 spinlock_t *irqlock,
			 क्रमागत v4l2_buf_type type,
			 क्रमागत v4l2_field field,
			 अचिन्हित पूर्णांक msize,
			 व्योम *priv,
			 काष्ठा videobuf_qtype_ops *पूर्णांक_ops,
			 काष्ठा mutex *ext_lock)
अणु
	BUG_ON(!q);
	स_रखो(q, 0, माप(*q));
	q->irqlock   = irqlock;
	q->ext_lock  = ext_lock;
	q->dev       = dev;
	q->type      = type;
	q->field     = field;
	q->msize     = msize;
	q->ops       = ops;
	q->priv_data = priv;
	q->पूर्णांक_ops   = पूर्णांक_ops;

	/* All buffer operations are mandatory */
	BUG_ON(!q->ops->buf_setup);
	BUG_ON(!q->ops->buf_prepare);
	BUG_ON(!q->ops->buf_queue);
	BUG_ON(!q->ops->buf_release);

	/* Lock is mandatory क्रम queue_cancel to work */
	BUG_ON(!irqlock);

	/* Having implementations क्रम असलtract methods are mandatory */
	BUG_ON(!q->पूर्णांक_ops);

	mutex_init(&q->vb_lock);
	init_रुकोqueue_head(&q->रुको);
	INIT_LIST_HEAD(&q->stream);
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_queue_core_init);

/* Locking: Only usage in bttv unsafe find way to हटाओ */
पूर्णांक videobuf_queue_is_busy(काष्ठा videobuf_queue *q)
अणु
	पूर्णांक i;

	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	अगर (q->streaming) अणु
		dprपूर्णांकk(1, "busy: streaming active\n");
		वापस 1;
	पूर्ण
	अगर (q->पढ़ोing) अणु
		dprपूर्णांकk(1, "busy: pending read #1\n");
		वापस 1;
	पूर्ण
	अगर (q->पढ़ो_buf) अणु
		dprपूर्णांकk(1, "busy: pending read #2\n");
		वापस 1;
	पूर्ण
	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
		अगर (शून्य == q->bufs[i])
			जारी;
		अगर (q->bufs[i]->map) अणु
			dprपूर्णांकk(1, "busy: buffer #%d mapped\n", i);
			वापस 1;
		पूर्ण
		अगर (q->bufs[i]->state == VIDEOBUF_QUEUED) अणु
			dprपूर्णांकk(1, "busy: buffer #%d queued\n", i);
			वापस 1;
		पूर्ण
		अगर (q->bufs[i]->state == VIDEOBUF_ACTIVE) अणु
			dprपूर्णांकk(1, "busy: buffer #%d active\n", i);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_queue_is_busy);

/*
 * __videobuf_मुक्त() - मुक्त all the buffers and their control काष्ठाures
 *
 * This function can only be called अगर streaming/पढ़ोing is off, i.e. no buffers
 * are under control of the driver.
 */
/* Locking: Caller holds q->vb_lock */
अटल पूर्णांक __videobuf_मुक्त(काष्ठा videobuf_queue *q)
अणु
	पूर्णांक i;

	dprपूर्णांकk(1, "%s\n", __func__);
	अगर (!q)
		वापस 0;

	अगर (q->streaming || q->पढ़ोing) अणु
		dprपूर्णांकk(1, "Cannot free buffers when streaming or reading\n");
		वापस -EBUSY;
	पूर्ण

	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++)
		अगर (q->bufs[i] && q->bufs[i]->map) अणु
			dprपूर्णांकk(1, "Cannot free mmapped buffers\n");
			वापस -EBUSY;
		पूर्ण

	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
		अगर (शून्य == q->bufs[i])
			जारी;
		q->ops->buf_release(q, q->bufs[i]);
		kमुक्त(q->bufs[i]);
		q->bufs[i] = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/* Locking: Caller holds q->vb_lock */
व्योम videobuf_queue_cancel(काष्ठा videobuf_queue *q)
अणु
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक i;

	q->streaming = 0;
	q->पढ़ोing  = 0;
	wake_up_पूर्णांकerruptible_sync(&q->रुको);

	/* हटाओ queued buffers from list */
	spin_lock_irqsave(q->irqlock, flags);
	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
		अगर (शून्य == q->bufs[i])
			जारी;
		अगर (q->bufs[i]->state == VIDEOBUF_QUEUED) अणु
			list_del(&q->bufs[i]->queue);
			q->bufs[i]->state = VIDEOBUF_ERROR;
			wake_up_all(&q->bufs[i]->करोne);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(q->irqlock, flags);

	/* मुक्त all buffers + clear queue */
	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
		अगर (शून्य == q->bufs[i])
			जारी;
		q->ops->buf_release(q, q->bufs[i]);
	पूर्ण
	INIT_LIST_HEAD(&q->stream);
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_queue_cancel);

/* --------------------------------------------------------------------- */

/* Locking: Caller holds q->vb_lock */
क्रमागत v4l2_field videobuf_next_field(काष्ठा videobuf_queue *q)
अणु
	क्रमागत v4l2_field field = q->field;

	BUG_ON(V4L2_FIELD_ANY == field);

	अगर (V4L2_FIELD_ALTERNATE == field) अणु
		अगर (V4L2_FIELD_TOP == q->last) अणु
			field   = V4L2_FIELD_BOTTOM;
			q->last = V4L2_FIELD_BOTTOM;
		पूर्ण अन्यथा अणु
			field   = V4L2_FIELD_TOP;
			q->last = V4L2_FIELD_TOP;
		पूर्ण
	पूर्ण
	वापस field;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_next_field);

/* Locking: Caller holds q->vb_lock */
अटल व्योम videobuf_status(काष्ठा videobuf_queue *q, काष्ठा v4l2_buffer *b,
			    काष्ठा videobuf_buffer *vb, क्रमागत v4l2_buf_type type)
अणु
	MAGIC_CHECK(vb->magic, MAGIC_BUFFER);
	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	b->index    = vb->i;
	b->type     = type;

	b->memory   = vb->memory;
	चयन (b->memory) अणु
	हाल V4L2_MEMORY_MMAP:
		b->m.offset  = vb->boff;
		b->length    = vb->bsize;
		अवरोध;
	हाल V4L2_MEMORY_USERPTR:
		b->m.userptr = vb->baddr;
		b->length    = vb->bsize;
		अवरोध;
	हाल V4L2_MEMORY_OVERLAY:
		b->m.offset  = vb->boff;
		अवरोध;
	हाल V4L2_MEMORY_DMABUF:
		/* DMABUF is not handled in videobuf framework */
		अवरोध;
	पूर्ण

	b->flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	अगर (vb->map)
		b->flags |= V4L2_BUF_FLAG_MAPPED;

	चयन (vb->state) अणु
	हाल VIDEOBUF_PREPARED:
	हाल VIDEOBUF_QUEUED:
	हाल VIDEOBUF_ACTIVE:
		b->flags |= V4L2_BUF_FLAG_QUEUED;
		अवरोध;
	हाल VIDEOBUF_ERROR:
		b->flags |= V4L2_BUF_FLAG_ERROR;
		fallthrough;
	हाल VIDEOBUF_DONE:
		b->flags |= V4L2_BUF_FLAG_DONE;
		अवरोध;
	हाल VIDEOBUF_NEEDS_INIT:
	हाल VIDEOBUF_IDLE:
		/* nothing */
		अवरोध;
	पूर्ण

	b->field     = vb->field;
	v4l2_buffer_set_बारtamp(b, vb->ts);
	b->bytesused = vb->size;
	b->sequence  = vb->field_count >> 1;
पूर्ण

पूर्णांक videobuf_mmap_मुक्त(काष्ठा videobuf_queue *q)
अणु
	पूर्णांक ret;
	videobuf_queue_lock(q);
	ret = __videobuf_मुक्त(q);
	videobuf_queue_unlock(q);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_mmap_मुक्त);

/* Locking: Caller holds q->vb_lock */
पूर्णांक __videobuf_mmap_setup(काष्ठा videobuf_queue *q,
			अचिन्हित पूर्णांक bcount, अचिन्हित पूर्णांक bsize,
			क्रमागत v4l2_memory memory)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	err = __videobuf_मुक्त(q);
	अगर (0 != err)
		वापस err;

	/* Allocate and initialize buffers */
	क्रम (i = 0; i < bcount; i++) अणु
		q->bufs[i] = videobuf_alloc_vb(q);

		अगर (शून्य == q->bufs[i])
			अवरोध;

		q->bufs[i]->i      = i;
		q->bufs[i]->memory = memory;
		q->bufs[i]->bsize  = bsize;
		चयन (memory) अणु
		हाल V4L2_MEMORY_MMAP:
			q->bufs[i]->boff = PAGE_ALIGN(bsize) * i;
			अवरोध;
		हाल V4L2_MEMORY_USERPTR:
		हाल V4L2_MEMORY_OVERLAY:
		हाल V4L2_MEMORY_DMABUF:
			/* nothing */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!i)
		वापस -ENOMEM;

	dprपूर्णांकk(1, "mmap setup: %d buffers, %d bytes each\n", i, bsize);

	वापस i;
पूर्ण
EXPORT_SYMBOL_GPL(__videobuf_mmap_setup);

पूर्णांक videobuf_mmap_setup(काष्ठा videobuf_queue *q,
			अचिन्हित पूर्णांक bcount, अचिन्हित पूर्णांक bsize,
			क्रमागत v4l2_memory memory)
अणु
	पूर्णांक ret;
	videobuf_queue_lock(q);
	ret = __videobuf_mmap_setup(q, bcount, bsize, memory);
	videobuf_queue_unlock(q);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_mmap_setup);

पूर्णांक videobuf_reqbufs(काष्ठा videobuf_queue *q,
		 काष्ठा v4l2_requestbuffers *req)
अणु
	अचिन्हित पूर्णांक size, count;
	पूर्णांक retval;

	अगर (req->memory != V4L2_MEMORY_MMAP     &&
	    req->memory != V4L2_MEMORY_USERPTR  &&
	    req->memory != V4L2_MEMORY_OVERLAY) अणु
		dprपूर्णांकk(1, "reqbufs: memory type invalid\n");
		वापस -EINVAL;
	पूर्ण

	videobuf_queue_lock(q);
	अगर (req->type != q->type) अणु
		dprपूर्णांकk(1, "reqbufs: queue type invalid\n");
		retval = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (q->streaming) अणु
		dprपूर्णांकk(1, "reqbufs: streaming already exists\n");
		retval = -EBUSY;
		जाओ करोne;
	पूर्ण
	अगर (!list_empty(&q->stream)) अणु
		dprपूर्णांकk(1, "reqbufs: stream running\n");
		retval = -EBUSY;
		जाओ करोne;
	पूर्ण

	अगर (req->count == 0) अणु
		dprपूर्णांकk(1, "reqbufs: count invalid (%d)\n", req->count);
		retval = __videobuf_मुक्त(q);
		जाओ करोne;
	पूर्ण

	count = req->count;
	अगर (count > VIDEO_MAX_FRAME)
		count = VIDEO_MAX_FRAME;
	size = 0;
	q->ops->buf_setup(q, &count, &size);
	dprपूर्णांकk(1, "reqbufs: bufs=%d, size=0x%x [%u pages total]\n",
		count, size,
		(अचिन्हित पूर्णांक)((count * PAGE_ALIGN(size)) >> PAGE_SHIFT));

	retval = __videobuf_mmap_setup(q, count, size, req->memory);
	अगर (retval < 0) अणु
		dprपूर्णांकk(1, "reqbufs: mmap setup returned %d\n", retval);
		जाओ करोne;
	पूर्ण

	req->count = retval;
	retval = 0;

 करोne:
	videobuf_queue_unlock(q);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_reqbufs);

पूर्णांक videobuf_querybuf(काष्ठा videobuf_queue *q, काष्ठा v4l2_buffer *b)
अणु
	पूर्णांक ret = -EINVAL;

	videobuf_queue_lock(q);
	अगर (unlikely(b->type != q->type)) अणु
		dprपूर्णांकk(1, "querybuf: Wrong type.\n");
		जाओ करोne;
	पूर्ण
	अगर (unlikely(b->index >= VIDEO_MAX_FRAME)) अणु
		dprपूर्णांकk(1, "querybuf: index out of range.\n");
		जाओ करोne;
	पूर्ण
	अगर (unlikely(शून्य == q->bufs[b->index])) अणु
		dprपूर्णांकk(1, "querybuf: buffer is null.\n");
		जाओ करोne;
	पूर्ण

	videobuf_status(q, b, q->bufs[b->index], q->type);

	ret = 0;
करोne:
	videobuf_queue_unlock(q);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_querybuf);

पूर्णांक videobuf_qbuf(काष्ठा videobuf_queue *q, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा videobuf_buffer *buf;
	क्रमागत v4l2_field field;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक retval;

	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	अगर (b->memory == V4L2_MEMORY_MMAP)
		mmap_पढ़ो_lock(current->mm);

	videobuf_queue_lock(q);
	retval = -EBUSY;
	अगर (q->पढ़ोing) अणु
		dprपूर्णांकk(1, "qbuf: Reading running...\n");
		जाओ करोne;
	पूर्ण
	retval = -EINVAL;
	अगर (b->type != q->type) अणु
		dprपूर्णांकk(1, "qbuf: Wrong type.\n");
		जाओ करोne;
	पूर्ण
	अगर (b->index >= VIDEO_MAX_FRAME) अणु
		dprपूर्णांकk(1, "qbuf: index out of range.\n");
		जाओ करोne;
	पूर्ण
	buf = q->bufs[b->index];
	अगर (शून्य == buf) अणु
		dprपूर्णांकk(1, "qbuf: buffer is null.\n");
		जाओ करोne;
	पूर्ण
	MAGIC_CHECK(buf->magic, MAGIC_BUFFER);
	अगर (buf->memory != b->memory) अणु
		dprपूर्णांकk(1, "qbuf: memory type is wrong.\n");
		जाओ करोne;
	पूर्ण
	अगर (buf->state != VIDEOBUF_NEEDS_INIT && buf->state != VIDEOBUF_IDLE) अणु
		dprपूर्णांकk(1, "qbuf: buffer is already queued or active.\n");
		जाओ करोne;
	पूर्ण

	चयन (b->memory) अणु
	हाल V4L2_MEMORY_MMAP:
		अगर (0 == buf->baddr) अणु
			dprपूर्णांकk(1, "qbuf: mmap requested but buffer addr is zero!\n");
			जाओ करोne;
		पूर्ण
		अगर (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT
		    || q->type == V4L2_BUF_TYPE_VBI_OUTPUT
		    || q->type == V4L2_BUF_TYPE_SLICED_VBI_OUTPUT
		    || q->type == V4L2_BUF_TYPE_SDR_OUTPUT) अणु
			buf->size = b->bytesused;
			buf->field = b->field;
			buf->ts = v4l2_buffer_get_बारtamp(b);
		पूर्ण
		अवरोध;
	हाल V4L2_MEMORY_USERPTR:
		अगर (b->length < buf->bsize) अणु
			dprपूर्णांकk(1, "qbuf: buffer length is not enough\n");
			जाओ करोne;
		पूर्ण
		अगर (VIDEOBUF_NEEDS_INIT != buf->state &&
		    buf->baddr != b->m.userptr)
			q->ops->buf_release(q, buf);
		buf->baddr = b->m.userptr;
		अवरोध;
	हाल V4L2_MEMORY_OVERLAY:
		buf->boff = b->m.offset;
		अवरोध;
	शेष:
		dprपूर्णांकk(1, "qbuf: wrong memory type\n");
		जाओ करोne;
	पूर्ण

	dprपूर्णांकk(1, "qbuf: requesting next field\n");
	field = videobuf_next_field(q);
	retval = q->ops->buf_prepare(q, buf, field);
	अगर (0 != retval) अणु
		dprपूर्णांकk(1, "qbuf: buffer_prepare returned %d\n", retval);
		जाओ करोne;
	पूर्ण

	list_add_tail(&buf->stream, &q->stream);
	अगर (q->streaming) अणु
		spin_lock_irqsave(q->irqlock, flags);
		q->ops->buf_queue(q, buf);
		spin_unlock_irqrestore(q->irqlock, flags);
	पूर्ण
	dprपूर्णांकk(1, "qbuf: succeeded\n");
	retval = 0;
	wake_up_पूर्णांकerruptible_sync(&q->रुको);

करोne:
	videobuf_queue_unlock(q);

	अगर (b->memory == V4L2_MEMORY_MMAP)
		mmap_पढ़ो_unlock(current->mm);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_qbuf);

/* Locking: Caller holds q->vb_lock */
अटल पूर्णांक stream_next_buffer_check_queue(काष्ठा videobuf_queue *q, पूर्णांक noblock)
अणु
	पूर्णांक retval;

checks:
	अगर (!q->streaming) अणु
		dprपूर्णांकk(1, "next_buffer: Not streaming\n");
		retval = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (list_empty(&q->stream)) अणु
		अगर (noblock) अणु
			retval = -EAGAIN;
			dprपूर्णांकk(2, "next_buffer: no buffers to dequeue\n");
			जाओ करोne;
		पूर्ण अन्यथा अणु
			dprपूर्णांकk(2, "next_buffer: waiting on buffer\n");

			/* Drop lock to aव्योम deadlock with qbuf */
			videobuf_queue_unlock(q);

			/* Checking list_empty and streaming is safe without
			 * locks because we जाओ checks to validate जबतक
			 * holding locks beक्रमe proceeding */
			retval = रुको_event_पूर्णांकerruptible(q->रुको,
				!list_empty(&q->stream) || !q->streaming);
			videobuf_queue_lock(q);

			अगर (retval)
				जाओ करोne;

			जाओ checks;
		पूर्ण
	पूर्ण

	retval = 0;

करोne:
	वापस retval;
पूर्ण

/* Locking: Caller holds q->vb_lock */
अटल पूर्णांक stream_next_buffer(काष्ठा videobuf_queue *q,
			काष्ठा videobuf_buffer **vb, पूर्णांक nonblocking)
अणु
	पूर्णांक retval;
	काष्ठा videobuf_buffer *buf = शून्य;

	retval = stream_next_buffer_check_queue(q, nonblocking);
	अगर (retval)
		जाओ करोne;

	buf = list_entry(q->stream.next, काष्ठा videobuf_buffer, stream);
	retval = videobuf_रुकोon(q, buf, nonblocking, 1);
	अगर (retval < 0)
		जाओ करोne;

	*vb = buf;
करोne:
	वापस retval;
पूर्ण

पूर्णांक videobuf_dqbuf(काष्ठा videobuf_queue *q,
		   काष्ठा v4l2_buffer *b, पूर्णांक nonblocking)
अणु
	काष्ठा videobuf_buffer *buf = शून्य;
	पूर्णांक retval;

	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	स_रखो(b, 0, माप(*b));
	videobuf_queue_lock(q);

	retval = stream_next_buffer(q, &buf, nonblocking);
	अगर (retval < 0) अणु
		dprपूर्णांकk(1, "dqbuf: next_buffer error: %i\n", retval);
		जाओ करोne;
	पूर्ण

	चयन (buf->state) अणु
	हाल VIDEOBUF_ERROR:
		dprपूर्णांकk(1, "dqbuf: state is error\n");
		अवरोध;
	हाल VIDEOBUF_DONE:
		dprपूर्णांकk(1, "dqbuf: state is done\n");
		अवरोध;
	शेष:
		dprपूर्णांकk(1, "dqbuf: state invalid\n");
		retval = -EINVAL;
		जाओ करोne;
	पूर्ण
	CALL(q, sync, q, buf);
	videobuf_status(q, b, buf, q->type);
	list_del(&buf->stream);
	buf->state = VIDEOBUF_IDLE;
	b->flags &= ~V4L2_BUF_FLAG_DONE;
करोne:
	videobuf_queue_unlock(q);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_dqbuf);

पूर्णांक videobuf_streamon(काष्ठा videobuf_queue *q)
अणु
	काष्ठा videobuf_buffer *buf;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक retval;

	videobuf_queue_lock(q);
	retval = -EBUSY;
	अगर (q->पढ़ोing)
		जाओ करोne;
	retval = 0;
	अगर (q->streaming)
		जाओ करोne;
	q->streaming = 1;
	spin_lock_irqsave(q->irqlock, flags);
	list_क्रम_each_entry(buf, &q->stream, stream)
		अगर (buf->state == VIDEOBUF_PREPARED)
			q->ops->buf_queue(q, buf);
	spin_unlock_irqrestore(q->irqlock, flags);

	wake_up_पूर्णांकerruptible_sync(&q->रुको);
करोne:
	videobuf_queue_unlock(q);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_streamon);

/* Locking: Caller holds q->vb_lock */
अटल पूर्णांक __videobuf_streamoff(काष्ठा videobuf_queue *q)
अणु
	अगर (!q->streaming)
		वापस -EINVAL;

	videobuf_queue_cancel(q);

	वापस 0;
पूर्ण

पूर्णांक videobuf_streamoff(काष्ठा videobuf_queue *q)
अणु
	पूर्णांक retval;

	videobuf_queue_lock(q);
	retval = __videobuf_streamoff(q);
	videobuf_queue_unlock(q);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_streamoff);

/* Locking: Caller holds q->vb_lock */
अटल sमाप_प्रकार videobuf_पढ़ो_zerocopy(काष्ठा videobuf_queue *q,
				      अक्षर __user *data,
				      माप_प्रकार count, loff_t *ppos)
अणु
	क्रमागत v4l2_field field;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक retval;

	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	/* setup stuff */
	q->पढ़ो_buf = videobuf_alloc_vb(q);
	अगर (शून्य == q->पढ़ो_buf)
		वापस -ENOMEM;

	q->पढ़ो_buf->memory = V4L2_MEMORY_USERPTR;
	q->पढ़ो_buf->baddr  = (अचिन्हित दीर्घ)data;
	q->पढ़ो_buf->bsize  = count;

	field = videobuf_next_field(q);
	retval = q->ops->buf_prepare(q, q->पढ़ो_buf, field);
	अगर (0 != retval)
		जाओ करोne;

	/* start capture & रुको */
	spin_lock_irqsave(q->irqlock, flags);
	q->ops->buf_queue(q, q->पढ़ो_buf);
	spin_unlock_irqrestore(q->irqlock, flags);
	retval = videobuf_रुकोon(q, q->पढ़ो_buf, 0, 0);
	अगर (0 == retval) अणु
		CALL(q, sync, q, q->पढ़ो_buf);
		अगर (VIDEOBUF_ERROR == q->पढ़ो_buf->state)
			retval = -EIO;
		अन्यथा
			retval = q->पढ़ो_buf->size;
	पूर्ण

करोne:
	/* cleanup */
	q->ops->buf_release(q, q->पढ़ो_buf);
	kमुक्त(q->पढ़ो_buf);
	q->पढ़ो_buf = शून्य;
	वापस retval;
पूर्ण

अटल पूर्णांक __videobuf_copy_to_user(काष्ठा videobuf_queue *q,
				   काष्ठा videobuf_buffer *buf,
				   अक्षर __user *data, माप_प्रकार count,
				   पूर्णांक nonblocking)
अणु
	व्योम *vaddr = CALLPTR(q, vaddr, buf);

	/* copy to userspace */
	अगर (count > buf->size - q->पढ़ो_off)
		count = buf->size - q->पढ़ो_off;

	अगर (copy_to_user(data, vaddr + q->पढ़ो_off, count))
		वापस -EFAULT;

	वापस count;
पूर्ण

अटल पूर्णांक __videobuf_copy_stream(काष्ठा videobuf_queue *q,
				  काष्ठा videobuf_buffer *buf,
				  अक्षर __user *data, माप_प्रकार count, माप_प्रकार pos,
				  पूर्णांक vbihack, पूर्णांक nonblocking)
अणु
	अचिन्हित पूर्णांक *fc = CALLPTR(q, vaddr, buf);

	अगर (vbihack) अणु
		/* dirty, unकरोcumented hack -- pass the frame counter
			* within the last four bytes of each vbi data block.
			* We need that one to मुख्यtain backward compatibility
			* to all vbi decoding software out there ... */
		fc += (buf->size >> 2) - 1;
		*fc = buf->field_count >> 1;
		dprपूर्णांकk(1, "vbihack: %d\n", *fc);
	पूर्ण

	/* copy stuff using the common method */
	count = __videobuf_copy_to_user(q, buf, data, count, nonblocking);

	अगर ((count == -EFAULT) && (pos == 0))
		वापस -EFAULT;

	वापस count;
पूर्ण

sमाप_प्रकार videobuf_पढ़ो_one(काष्ठा videobuf_queue *q,
			  अक्षर __user *data, माप_प्रकार count, loff_t *ppos,
			  पूर्णांक nonblocking)
अणु
	क्रमागत v4l2_field field;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित size = 0, nbufs = 1;
	पूर्णांक retval;

	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	videobuf_queue_lock(q);

	q->ops->buf_setup(q, &nbufs, &size);

	अगर (शून्य == q->पढ़ो_buf  &&
	    count >= size        &&
	    !nonblocking) अणु
		retval = videobuf_पढ़ो_zerocopy(q, data, count, ppos);
		अगर (retval >= 0  ||  retval == -EIO)
			/* ok, all करोne */
			जाओ करोne;
		/* fallback to kernel bounce buffer on failures */
	पूर्ण

	अगर (शून्य == q->पढ़ो_buf) अणु
		/* need to capture a new frame */
		retval = -ENOMEM;
		q->पढ़ो_buf = videobuf_alloc_vb(q);

		dprपूर्णांकk(1, "video alloc=0x%p\n", q->पढ़ो_buf);
		अगर (शून्य == q->पढ़ो_buf)
			जाओ करोne;
		q->पढ़ो_buf->memory = V4L2_MEMORY_USERPTR;
		q->पढ़ो_buf->bsize = count; /* preferred size */
		field = videobuf_next_field(q);
		retval = q->ops->buf_prepare(q, q->पढ़ो_buf, field);

		अगर (0 != retval) अणु
			kमुक्त(q->पढ़ो_buf);
			q->पढ़ो_buf = शून्य;
			जाओ करोne;
		पूर्ण

		spin_lock_irqsave(q->irqlock, flags);
		q->ops->buf_queue(q, q->पढ़ो_buf);
		spin_unlock_irqrestore(q->irqlock, flags);

		q->पढ़ो_off = 0;
	पूर्ण

	/* रुको until capture is करोne */
	retval = videobuf_रुकोon(q, q->पढ़ो_buf, nonblocking, 1);
	अगर (0 != retval)
		जाओ करोne;

	CALL(q, sync, q, q->पढ़ो_buf);

	अगर (VIDEOBUF_ERROR == q->पढ़ो_buf->state) अणु
		/* catch I/O errors */
		q->ops->buf_release(q, q->पढ़ो_buf);
		kमुक्त(q->पढ़ो_buf);
		q->पढ़ो_buf = शून्य;
		retval = -EIO;
		जाओ करोne;
	पूर्ण

	/* Copy to userspace */
	retval = __videobuf_copy_to_user(q, q->पढ़ो_buf, data, count, nonblocking);
	अगर (retval < 0)
		जाओ करोne;

	q->पढ़ो_off += retval;
	अगर (q->पढ़ो_off == q->पढ़ो_buf->size) अणु
		/* all data copied, cleanup */
		q->ops->buf_release(q, q->पढ़ो_buf);
		kमुक्त(q->पढ़ो_buf);
		q->पढ़ो_buf = शून्य;
	पूर्ण

करोne:
	videobuf_queue_unlock(q);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_पढ़ो_one);

/* Locking: Caller holds q->vb_lock */
अटल पूर्णांक __videobuf_पढ़ो_start(काष्ठा videobuf_queue *q)
अणु
	क्रमागत v4l2_field field;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक count = 0, size = 0;
	पूर्णांक err, i;

	q->ops->buf_setup(q, &count, &size);
	अगर (count < 2)
		count = 2;
	अगर (count > VIDEO_MAX_FRAME)
		count = VIDEO_MAX_FRAME;
	size = PAGE_ALIGN(size);

	err = __videobuf_mmap_setup(q, count, size, V4L2_MEMORY_USERPTR);
	अगर (err < 0)
		वापस err;

	count = err;

	क्रम (i = 0; i < count; i++) अणु
		field = videobuf_next_field(q);
		err = q->ops->buf_prepare(q, q->bufs[i], field);
		अगर (err)
			वापस err;
		list_add_tail(&q->bufs[i]->stream, &q->stream);
	पूर्ण
	spin_lock_irqsave(q->irqlock, flags);
	क्रम (i = 0; i < count; i++)
		q->ops->buf_queue(q, q->bufs[i]);
	spin_unlock_irqrestore(q->irqlock, flags);
	q->पढ़ोing = 1;
	वापस 0;
पूर्ण

अटल व्योम __videobuf_पढ़ो_stop(काष्ठा videobuf_queue *q)
अणु
	पूर्णांक i;

	videobuf_queue_cancel(q);
	__videobuf_मुक्त(q);
	INIT_LIST_HEAD(&q->stream);
	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
		अगर (शून्य == q->bufs[i])
			जारी;
		kमुक्त(q->bufs[i]);
		q->bufs[i] = शून्य;
	पूर्ण
	q->पढ़ो_buf = शून्य;
पूर्ण

पूर्णांक videobuf_पढ़ो_start(काष्ठा videobuf_queue *q)
अणु
	पूर्णांक rc;

	videobuf_queue_lock(q);
	rc = __videobuf_पढ़ो_start(q);
	videobuf_queue_unlock(q);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_पढ़ो_start);

व्योम videobuf_पढ़ो_stop(काष्ठा videobuf_queue *q)
अणु
	videobuf_queue_lock(q);
	__videobuf_पढ़ो_stop(q);
	videobuf_queue_unlock(q);
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_पढ़ो_stop);

व्योम videobuf_stop(काष्ठा videobuf_queue *q)
अणु
	videobuf_queue_lock(q);

	अगर (q->streaming)
		__videobuf_streamoff(q);

	अगर (q->पढ़ोing)
		__videobuf_पढ़ो_stop(q);

	videobuf_queue_unlock(q);
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_stop);

sमाप_प्रकार videobuf_पढ़ो_stream(काष्ठा videobuf_queue *q,
			     अक्षर __user *data, माप_प्रकार count, loff_t *ppos,
			     पूर्णांक vbihack, पूर्णांक nonblocking)
अणु
	पूर्णांक rc, retval;
	अचिन्हित दीर्घ flags = 0;

	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	dprपूर्णांकk(2, "%s\n", __func__);
	videobuf_queue_lock(q);
	retval = -EBUSY;
	अगर (q->streaming)
		जाओ करोne;
	अगर (!q->पढ़ोing) अणु
		retval = __videobuf_पढ़ो_start(q);
		अगर (retval < 0)
			जाओ करोne;
	पूर्ण

	retval = 0;
	जबतक (count > 0) अणु
		/* get / रुको क्रम data */
		अगर (शून्य == q->पढ़ो_buf) अणु
			q->पढ़ो_buf = list_entry(q->stream.next,
						 काष्ठा videobuf_buffer,
						 stream);
			list_del(&q->पढ़ो_buf->stream);
			q->पढ़ो_off = 0;
		पूर्ण
		rc = videobuf_रुकोon(q, q->पढ़ो_buf, nonblocking, 1);
		अगर (rc < 0) अणु
			अगर (0 == retval)
				retval = rc;
			अवरोध;
		पूर्ण

		अगर (q->पढ़ो_buf->state == VIDEOBUF_DONE) अणु
			rc = __videobuf_copy_stream(q, q->पढ़ो_buf, data + retval, count,
					retval, vbihack, nonblocking);
			अगर (rc < 0) अणु
				retval = rc;
				अवरोध;
			पूर्ण
			retval      += rc;
			count       -= rc;
			q->पढ़ो_off += rc;
		पूर्ण अन्यथा अणु
			/* some error */
			q->पढ़ो_off = q->पढ़ो_buf->size;
			अगर (0 == retval)
				retval = -EIO;
		पूर्ण

		/* requeue buffer when करोne with copying */
		अगर (q->पढ़ो_off == q->पढ़ो_buf->size) अणु
			list_add_tail(&q->पढ़ो_buf->stream,
				      &q->stream);
			spin_lock_irqsave(q->irqlock, flags);
			q->ops->buf_queue(q, q->पढ़ो_buf);
			spin_unlock_irqrestore(q->irqlock, flags);
			q->पढ़ो_buf = शून्य;
		पूर्ण
		अगर (retval < 0)
			अवरोध;
	पूर्ण

करोne:
	videobuf_queue_unlock(q);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_पढ़ो_stream);

__poll_t videobuf_poll_stream(काष्ठा file *file,
			      काष्ठा videobuf_queue *q,
			      poll_table *रुको)
अणु
	__poll_t req_events = poll_requested_events(रुको);
	काष्ठा videobuf_buffer *buf = शून्य;
	__poll_t rc = 0;

	videobuf_queue_lock(q);
	अगर (q->streaming) अणु
		अगर (!list_empty(&q->stream))
			buf = list_entry(q->stream.next,
					 काष्ठा videobuf_buffer, stream);
	पूर्ण अन्यथा अगर (req_events & (EPOLLIN | EPOLLRDNORM)) अणु
		अगर (!q->पढ़ोing)
			__videobuf_पढ़ो_start(q);
		अगर (!q->पढ़ोing) अणु
			rc = EPOLLERR;
		पूर्ण अन्यथा अगर (शून्य == q->पढ़ो_buf) अणु
			q->पढ़ो_buf = list_entry(q->stream.next,
						 काष्ठा videobuf_buffer,
						 stream);
			list_del(&q->पढ़ो_buf->stream);
			q->पढ़ो_off = 0;
		पूर्ण
		buf = q->पढ़ो_buf;
	पूर्ण
	अगर (buf)
		poll_रुको(file, &buf->करोne, रुको);
	अन्यथा
		rc = EPOLLERR;

	अगर (0 == rc) अणु
		अगर (buf->state == VIDEOBUF_DONE ||
		    buf->state == VIDEOBUF_ERROR) अणु
			चयन (q->type) अणु
			हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
			हाल V4L2_BUF_TYPE_VBI_OUTPUT:
			हाल V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
			हाल V4L2_BUF_TYPE_SDR_OUTPUT:
				rc = EPOLLOUT | EPOLLWRNORM;
				अवरोध;
			शेष:
				rc = EPOLLIN | EPOLLRDNORM;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	videobuf_queue_unlock(q);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_poll_stream);

पूर्णांक videobuf_mmap_mapper(काष्ठा videobuf_queue *q, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक rc = -EINVAL;
	पूर्णांक i;

	MAGIC_CHECK(q->पूर्णांक_ops->magic, MAGIC_QTYPE_OPS);

	अगर (!(vma->vm_flags & VM_WRITE) || !(vma->vm_flags & VM_SHARED)) अणु
		dprपूर्णांकk(1, "mmap appl bug: PROT_WRITE and MAP_SHARED are required\n");
		वापस -EINVAL;
	पूर्ण

	videobuf_queue_lock(q);
	क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
		काष्ठा videobuf_buffer *buf = q->bufs[i];

		अगर (buf && buf->memory == V4L2_MEMORY_MMAP &&
				buf->boff == (vma->vm_pgoff << PAGE_SHIFT)) अणु
			rc = CALL(q, mmap_mapper, q, buf, vma);
			अवरोध;
		पूर्ण
	पूर्ण
	videobuf_queue_unlock(q);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_mmap_mapper);
