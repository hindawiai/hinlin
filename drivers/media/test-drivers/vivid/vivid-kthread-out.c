<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-kthपढ़ो-out.h - video/vbi output thपढ़ो support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/font.h>
#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>

#समावेश "vivid-core.h"
#समावेश "vivid-vid-common.h"
#समावेश "vivid-vid-cap.h"
#समावेश "vivid-vid-out.h"
#समावेश "vivid-radio-common.h"
#समावेश "vivid-radio-rx.h"
#समावेश "vivid-radio-tx.h"
#समावेश "vivid-sdr-cap.h"
#समावेश "vivid-vbi-cap.h"
#समावेश "vivid-vbi-out.h"
#समावेश "vivid-osd.h"
#समावेश "vivid-ctrls.h"
#समावेश "vivid-kthread-out.h"
#समावेश "vivid-meta-out.h"

अटल व्योम vivid_thपढ़ो_vid_out_tick(काष्ठा vivid_dev *dev)
अणु
	काष्ठा vivid_buffer *vid_out_buf = शून्य;
	काष्ठा vivid_buffer *vbi_out_buf = शून्य;
	काष्ठा vivid_buffer *meta_out_buf = शून्य;

	dprपूर्णांकk(dev, 1, "Video Output Thread Tick\n");

	/* Drop a certain percentage of buffers. */
	अगर (dev->perc_dropped_buffers &&
	    pअक्रमom_u32_max(100) < dev->perc_dropped_buffers)
		वापस;

	spin_lock(&dev->slock);
	/*
	 * Only dequeue buffer अगर there is at least one more pending.
	 * This makes video loopback possible.
	 */
	अगर (!list_empty(&dev->vid_out_active) &&
	    !list_is_singular(&dev->vid_out_active)) अणु
		vid_out_buf = list_entry(dev->vid_out_active.next,
					 काष्ठा vivid_buffer, list);
		list_del(&vid_out_buf->list);
	पूर्ण
	अगर (!list_empty(&dev->vbi_out_active) &&
	    (dev->field_out != V4L2_FIELD_ALTERNATE ||
	     (dev->vbi_out_seq_count & 1))) अणु
		vbi_out_buf = list_entry(dev->vbi_out_active.next,
					 काष्ठा vivid_buffer, list);
		list_del(&vbi_out_buf->list);
	पूर्ण
	अगर (!list_empty(&dev->meta_out_active)) अणु
		meta_out_buf = list_entry(dev->meta_out_active.next,
					  काष्ठा vivid_buffer, list);
		list_del(&meta_out_buf->list);
	पूर्ण
	spin_unlock(&dev->slock);

	अगर (!vid_out_buf && !vbi_out_buf && !meta_out_buf)
		वापस;

	अगर (vid_out_buf) अणु
		v4l2_ctrl_request_setup(vid_out_buf->vb.vb2_buf.req_obj.req,
					&dev->ctrl_hdl_vid_out);
		v4l2_ctrl_request_complete(vid_out_buf->vb.vb2_buf.req_obj.req,
					   &dev->ctrl_hdl_vid_out);
		vid_out_buf->vb.sequence = dev->vid_out_seq_count;
		अगर (dev->field_out == V4L2_FIELD_ALTERNATE) अणु
			/*
			 * The sequence counter counts frames, not fields.
			 * So भागide by two.
			 */
			vid_out_buf->vb.sequence /= 2;
		पूर्ण
		vid_out_buf->vb.vb2_buf.बारtamp =
			kसमय_get_ns() + dev->समय_wrap_offset;
		vb2_buffer_करोne(&vid_out_buf->vb.vb2_buf, dev->dqbuf_error ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
		dprपूर्णांकk(dev, 2, "vid_out buffer %d done\n",
			vid_out_buf->vb.vb2_buf.index);
	पूर्ण

	अगर (vbi_out_buf) अणु
		v4l2_ctrl_request_setup(vbi_out_buf->vb.vb2_buf.req_obj.req,
					&dev->ctrl_hdl_vbi_out);
		v4l2_ctrl_request_complete(vbi_out_buf->vb.vb2_buf.req_obj.req,
					   &dev->ctrl_hdl_vbi_out);
		अगर (dev->stream_sliced_vbi_out)
			vivid_sliced_vbi_out_process(dev, vbi_out_buf);

		vbi_out_buf->vb.sequence = dev->vbi_out_seq_count;
		vbi_out_buf->vb.vb2_buf.बारtamp =
			kसमय_get_ns() + dev->समय_wrap_offset;
		vb2_buffer_करोne(&vbi_out_buf->vb.vb2_buf, dev->dqbuf_error ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
		dprपूर्णांकk(dev, 2, "vbi_out buffer %d done\n",
			vbi_out_buf->vb.vb2_buf.index);
	पूर्ण
	अगर (meta_out_buf) अणु
		v4l2_ctrl_request_setup(meta_out_buf->vb.vb2_buf.req_obj.req,
					&dev->ctrl_hdl_meta_out);
		v4l2_ctrl_request_complete(meta_out_buf->vb.vb2_buf.req_obj.req,
					   &dev->ctrl_hdl_meta_out);
		vivid_meta_out_process(dev, meta_out_buf);
		meta_out_buf->vb.sequence = dev->meta_out_seq_count;
		meta_out_buf->vb.vb2_buf.बारtamp =
			kसमय_get_ns() + dev->समय_wrap_offset;
		vb2_buffer_करोne(&meta_out_buf->vb.vb2_buf, dev->dqbuf_error ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
		dprपूर्णांकk(dev, 2, "meta_out buffer %d done\n",
			meta_out_buf->vb.vb2_buf.index);
	पूर्ण

	dev->dqbuf_error = false;
पूर्ण

अटल पूर्णांक vivid_thपढ़ो_vid_out(व्योम *data)
अणु
	काष्ठा vivid_dev *dev = data;
	u64 numerators_since_start;
	u64 buffers_since_start;
	u64 next_jअगरfies_since_start;
	अचिन्हित दीर्घ jअगरfies_since_start;
	अचिन्हित दीर्घ cur_jअगरfies;
	अचिन्हित रुको_jअगरfies;
	अचिन्हित numerator;
	अचिन्हित denominator;

	dprपूर्णांकk(dev, 1, "Video Output Thread Start\n");

	set_मुक्तzable();

	/* Resets frame counters */
	dev->out_seq_offset = 0;
	अगर (dev->seq_wrap)
		dev->out_seq_count = 0xffffff80U;
	dev->jअगरfies_vid_out = jअगरfies;
	dev->vid_out_seq_start = dev->vbi_out_seq_start = 0;
	dev->meta_out_seq_start = 0;
	dev->out_seq_resync = false;

	क्रम (;;) अणु
		try_to_मुक्तze();
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर (!mutex_trylock(&dev->mutex)) अणु
			schedule();
			जारी;
		पूर्ण

		cur_jअगरfies = jअगरfies;
		अगर (dev->out_seq_resync) अणु
			dev->jअगरfies_vid_out = cur_jअगरfies;
			dev->out_seq_offset = dev->out_seq_count + 1;
			dev->out_seq_count = 0;
			dev->out_seq_resync = false;
		पूर्ण
		numerator = dev->समयperframe_vid_out.numerator;
		denominator = dev->समयperframe_vid_out.denominator;

		अगर (dev->field_out == V4L2_FIELD_ALTERNATE)
			denominator *= 2;

		/* Calculate the number of jअगरfies since we started streaming */
		jअगरfies_since_start = cur_jअगरfies - dev->jअगरfies_vid_out;
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
			dev->jअगरfies_vid_out = cur_jअगरfies;
			dev->out_seq_offset = buffers_since_start;
			buffers_since_start = 0;
		पूर्ण
		dev->out_seq_count = buffers_since_start + dev->out_seq_offset;
		dev->vid_out_seq_count = dev->out_seq_count - dev->vid_out_seq_start;
		dev->vbi_out_seq_count = dev->out_seq_count - dev->vbi_out_seq_start;
		dev->meta_out_seq_count = dev->out_seq_count - dev->meta_out_seq_start;

		vivid_thपढ़ो_vid_out_tick(dev);
		mutex_unlock(&dev->mutex);

		/*
		 * Calculate the number of 'numerators' streamed since we started,
		 * not including the current buffer.
		 */
		numerators_since_start = buffers_since_start * numerator;

		/* And the number of jअगरfies since we started */
		jअगरfies_since_start = jअगरfies - dev->jअगरfies_vid_out;

		/* Increase by the 'numerator' of one buffer */
		numerators_since_start += numerator;
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
	dprपूर्णांकk(dev, 1, "Video Output Thread End\n");
	वापस 0;
पूर्ण

अटल व्योम vivid_grab_controls(काष्ठा vivid_dev *dev, bool grab)
अणु
	v4l2_ctrl_grab(dev->ctrl_has_crop_out, grab);
	v4l2_ctrl_grab(dev->ctrl_has_compose_out, grab);
	v4l2_ctrl_grab(dev->ctrl_has_scaler_out, grab);
	v4l2_ctrl_grab(dev->ctrl_tx_mode, grab);
	v4l2_ctrl_grab(dev->ctrl_tx_rgb_range, grab);
पूर्ण

पूर्णांक vivid_start_generating_vid_out(काष्ठा vivid_dev *dev, bool *pstreaming)
अणु
	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	अगर (dev->kthपढ़ो_vid_out) अणु
		u32 seq_count = dev->out_seq_count + dev->seq_wrap * 128;

		अगर (pstreaming == &dev->vid_out_streaming)
			dev->vid_out_seq_start = seq_count;
		अन्यथा अगर (pstreaming == &dev->vbi_out_streaming)
			dev->vbi_out_seq_start = seq_count;
		अन्यथा
			dev->meta_out_seq_start = seq_count;
		*pstreaming = true;
		वापस 0;
	पूर्ण

	/* Resets frame counters */
	dev->jअगरfies_vid_out = jअगरfies;
	dev->vid_out_seq_start = dev->seq_wrap * 128;
	dev->vbi_out_seq_start = dev->seq_wrap * 128;
	dev->meta_out_seq_start = dev->seq_wrap * 128;

	dev->kthपढ़ो_vid_out = kthपढ़ो_run(vivid_thपढ़ो_vid_out, dev,
			"%s-vid-out", dev->v4l2_dev.name);

	अगर (IS_ERR(dev->kthपढ़ो_vid_out)) अणु
		पूर्णांक err = PTR_ERR(dev->kthपढ़ो_vid_out);

		dev->kthपढ़ो_vid_out = शून्य;
		v4l2_err(&dev->v4l2_dev, "kernel_thread() failed\n");
		वापस err;
	पूर्ण
	*pstreaming = true;
	vivid_grab_controls(dev, true);

	dprपूर्णांकk(dev, 1, "returning from %s\n", __func__);
	वापस 0;
पूर्ण

व्योम vivid_stop_generating_vid_out(काष्ठा vivid_dev *dev, bool *pstreaming)
अणु
	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	अगर (dev->kthपढ़ो_vid_out == शून्य)
		वापस;

	*pstreaming = false;
	अगर (pstreaming == &dev->vid_out_streaming) अणु
		/* Release all active buffers */
		जबतक (!list_empty(&dev->vid_out_active)) अणु
			काष्ठा vivid_buffer *buf;

			buf = list_entry(dev->vid_out_active.next,
					 काष्ठा vivid_buffer, list);
			list_del(&buf->list);
			v4l2_ctrl_request_complete(buf->vb.vb2_buf.req_obj.req,
						   &dev->ctrl_hdl_vid_out);
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
			dprपूर्णांकk(dev, 2, "vid_out buffer %d done\n",
				buf->vb.vb2_buf.index);
		पूर्ण
	पूर्ण

	अगर (pstreaming == &dev->vbi_out_streaming) अणु
		जबतक (!list_empty(&dev->vbi_out_active)) अणु
			काष्ठा vivid_buffer *buf;

			buf = list_entry(dev->vbi_out_active.next,
					 काष्ठा vivid_buffer, list);
			list_del(&buf->list);
			v4l2_ctrl_request_complete(buf->vb.vb2_buf.req_obj.req,
						   &dev->ctrl_hdl_vbi_out);
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
			dprपूर्णांकk(dev, 2, "vbi_out buffer %d done\n",
				buf->vb.vb2_buf.index);
		पूर्ण
	पूर्ण

	अगर (pstreaming == &dev->meta_out_streaming) अणु
		जबतक (!list_empty(&dev->meta_out_active)) अणु
			काष्ठा vivid_buffer *buf;

			buf = list_entry(dev->meta_out_active.next,
					 काष्ठा vivid_buffer, list);
			list_del(&buf->list);
			v4l2_ctrl_request_complete(buf->vb.vb2_buf.req_obj.req,
						   &dev->ctrl_hdl_meta_out);
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
			dprपूर्णांकk(dev, 2, "meta_out buffer %d done\n",
				buf->vb.vb2_buf.index);
		पूर्ण
	पूर्ण

	अगर (dev->vid_out_streaming || dev->vbi_out_streaming ||
	    dev->meta_out_streaming)
		वापस;

	/* shutकरोwn control thपढ़ो */
	vivid_grab_controls(dev, false);
	kthपढ़ो_stop(dev->kthपढ़ो_vid_out);
	dev->kthपढ़ो_vid_out = शून्य;
पूर्ण
