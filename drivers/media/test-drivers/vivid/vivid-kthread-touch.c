<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-kthपढ़ो-touch.c - touch capture thपढ़ो support functions.
 *
 */

#समावेश <linux/मुक्तzer.h>
#समावेश "vivid-core.h"
#समावेश "vivid-kthread-touch.h"
#समावेश "vivid-touch-cap.h"

अटल noअंतरभूत_क्रम_stack व्योम vivid_thपढ़ो_tch_cap_tick(काष्ठा vivid_dev *dev,
							 पूर्णांक dropped_bufs)
अणु
	काष्ठा vivid_buffer *tch_cap_buf = शून्य;

	spin_lock(&dev->slock);
	अगर (!list_empty(&dev->touch_cap_active)) अणु
		tch_cap_buf = list_entry(dev->touch_cap_active.next,
					 काष्ठा vivid_buffer, list);
		list_del(&tch_cap_buf->list);
	पूर्ण

	spin_unlock(&dev->slock);

	अगर (tch_cap_buf) अणु
		v4l2_ctrl_request_setup(tch_cap_buf->vb.vb2_buf.req_obj.req,
					&dev->ctrl_hdl_touch_cap);

		vivid_fillbuff_tch(dev, tch_cap_buf);
		v4l2_ctrl_request_complete(tch_cap_buf->vb.vb2_buf.req_obj.req,
					   &dev->ctrl_hdl_touch_cap);
		vb2_buffer_करोne(&tch_cap_buf->vb.vb2_buf, dev->dqbuf_error ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
		dprपूर्णांकk(dev, 2, "touch_cap buffer %d done\n",
			tch_cap_buf->vb.vb2_buf.index);

		tch_cap_buf->vb.vb2_buf.बारtamp = kसमय_get_ns() + dev->समय_wrap_offset;
	पूर्ण
	dev->dqbuf_error = false;
पूर्ण

अटल पूर्णांक vivid_thपढ़ो_touch_cap(व्योम *data)
अणु
	काष्ठा vivid_dev *dev = data;
	u64 numerators_since_start;
	u64 buffers_since_start;
	u64 next_jअगरfies_since_start;
	अचिन्हित दीर्घ jअगरfies_since_start;
	अचिन्हित दीर्घ cur_jअगरfies;
	अचिन्हित पूर्णांक रुको_jअगरfies;
	अचिन्हित पूर्णांक numerator;
	अचिन्हित पूर्णांक denominator;
	पूर्णांक dropped_bufs;

	dprपूर्णांकk(dev, 1, "Touch Capture Thread Start\n");

	set_मुक्तzable();

	/* Resets frame counters */
	dev->touch_cap_seq_offset = 0;
	dev->touch_cap_seq_count = 0;
	dev->touch_cap_seq_resync = false;
	dev->jअगरfies_touch_cap = jअगरfies;

	क्रम (;;) अणु
		try_to_मुक्तze();
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर (!mutex_trylock(&dev->mutex)) अणु
			schedule();
			जारी;
		पूर्ण
		cur_jअगरfies = jअगरfies;
		अगर (dev->touch_cap_seq_resync) अणु
			dev->jअगरfies_touch_cap = cur_jअगरfies;
			dev->touch_cap_seq_offset = dev->touch_cap_seq_count + 1;
			dev->touch_cap_seq_count = 0;
			dev->cap_seq_resync = false;
		पूर्ण
		denominator = dev->समयperframe_tch_cap.denominator;
		numerator = dev->समयperframe_tch_cap.numerator;

		/* Calculate the number of jअगरfies since we started streaming */
		jअगरfies_since_start = cur_jअगरfies - dev->jअगरfies_touch_cap;
		/* Get the number of buffers streamed since the start */
		buffers_since_start = (u64)jअगरfies_since_start * denominator +
				      (HZ * numerator) / 2;
		करो_भाग(buffers_since_start, HZ * numerator);

		/*
		 * After more than 0xf0000000 (rounded करोwn to a multiple of
		 * 'jiffies-per-day' to ease jअगरfies_to_msecs calculation)
		 * jअगरfies have passed since we started streaming reset the
		 * counters and keep track of the sequence offset.
		 */
		अगर (jअगरfies_since_start > JIFFIES_RESYNC) अणु
			dev->jअगरfies_touch_cap = cur_jअगरfies;
			dev->cap_seq_offset = buffers_since_start;
			buffers_since_start = 0;
		पूर्ण
		dropped_bufs = buffers_since_start + dev->touch_cap_seq_offset - dev->touch_cap_seq_count;
		dev->touch_cap_seq_count = buffers_since_start + dev->touch_cap_seq_offset;

		vivid_thपढ़ो_tch_cap_tick(dev, dropped_bufs);

		/*
		 * Calculate the number of 'numerators' streamed
		 * since we started, including the current buffer.
		 */
		numerators_since_start = ++buffers_since_start * numerator;

		/* And the number of jअगरfies since we started */
		jअगरfies_since_start = jअगरfies - dev->jअगरfies_touch_cap;

		mutex_unlock(&dev->mutex);

		/*
		 * Calculate when that next buffer is supposed to start
		 * in jअगरfies since we started streaming.
		 */
		next_jअगरfies_since_start = numerators_since_start * HZ +
					   denominator / 2;
		करो_भाग(next_jअगरfies_since_start, denominator);
		/* If it is in the past, then just schedule asap */
		अगर (next_jअगरfies_since_start < jअगरfies_since_start)
			next_jअगरfies_since_start = jअगरfies_since_start;

		रुको_jअगरfies = next_jअगरfies_since_start - jअगरfies_since_start;
		जबतक (jअगरfies - cur_jअगरfies < रुको_jअगरfies &&
		       !kthपढ़ो_should_stop())
			schedule();
	पूर्ण
	dprपूर्णांकk(dev, 1, "Touch Capture Thread End\n");
	वापस 0;
पूर्ण

पूर्णांक vivid_start_generating_touch_cap(काष्ठा vivid_dev *dev)
अणु
	अगर (dev->kthपढ़ो_touch_cap) अणु
		dev->touch_cap_streaming = true;
		वापस 0;
	पूर्ण

	dev->kthपढ़ो_touch_cap = kthपढ़ो_run(vivid_thपढ़ो_touch_cap, dev,
					     "%s-tch-cap", dev->v4l2_dev.name);

	अगर (IS_ERR(dev->kthपढ़ो_touch_cap)) अणु
		पूर्णांक err = PTR_ERR(dev->kthपढ़ो_touch_cap);

		dev->kthपढ़ो_touch_cap = शून्य;
		v4l2_err(&dev->v4l2_dev, "kernel_thread() failed\n");
		वापस err;
	पूर्ण
	dev->touch_cap_streaming = true;
	dprपूर्णांकk(dev, 1, "returning from %s\n", __func__);
	वापस 0;
पूर्ण

व्योम vivid_stop_generating_touch_cap(काष्ठा vivid_dev *dev)
अणु
	अगर (!dev->kthपढ़ो_touch_cap)
		वापस;

	dev->touch_cap_streaming = false;

	जबतक (!list_empty(&dev->touch_cap_active)) अणु
		काष्ठा vivid_buffer *buf;

		buf = list_entry(dev->touch_cap_active.next,
				 काष्ठा vivid_buffer, list);
		list_del(&buf->list);
		v4l2_ctrl_request_complete(buf->vb.vb2_buf.req_obj.req,
					   &dev->ctrl_hdl_touch_cap);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		dprपूर्णांकk(dev, 2, "touch_cap buffer %d done\n",
			buf->vb.vb2_buf.index);
	पूर्ण

	kthपढ़ो_stop(dev->kthपढ़ो_touch_cap);
	dev->kthपढ़ो_touch_cap = शून्य;
पूर्ण
