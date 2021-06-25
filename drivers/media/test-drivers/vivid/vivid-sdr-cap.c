<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-sdr-cap.c - software defined radio support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/math64.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <linux/fixp-arith.h>

#समावेश "vivid-core.h"
#समावेश "vivid-ctrls.h"
#समावेश "vivid-sdr-cap.h"

/* stream क्रमmats */
काष्ठा vivid_क्रमmat अणु
	u32	pixelक्रमmat;
	u32	buffersize;
पूर्ण;

/* क्रमmat descriptions क्रम capture and preview */
अटल स्थिर काष्ठा vivid_क्रमmat क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_CU8,
		.buffersize	= SDR_CAP_SAMPLES_PER_BUF * 2,
	पूर्ण, अणु
		.pixelक्रमmat	= V4L2_SDR_FMT_CS8,
		.buffersize	= SDR_CAP_SAMPLES_PER_BUF * 2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_frequency_band bands_adc[] = अणु
	अणु
		.tuner = 0,
		.type = V4L2_TUNER_ADC,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =  300000,
		.rangehigh  =  300000,
	पूर्ण,
	अणु
		.tuner = 0,
		.type = V4L2_TUNER_ADC,
		.index = 1,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =  900001,
		.rangehigh  = 2800000,
	पूर्ण,
	अणु
		.tuner = 0,
		.type = V4L2_TUNER_ADC,
		.index = 2,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   = 3200000,
		.rangehigh  = 3200000,
	पूर्ण,
पूर्ण;

/* ADC band midpoपूर्णांकs */
#घोषणा BAND_ADC_0 ((bands_adc[0].rangehigh + bands_adc[1].rangelow) / 2)
#घोषणा BAND_ADC_1 ((bands_adc[1].rangehigh + bands_adc[2].rangelow) / 2)

अटल स्थिर काष्ठा v4l2_frequency_band bands_fm[] = अणु
	अणु
		.tuner = 1,
		.type = V4L2_TUNER_RF,
		.index = 0,
		.capability = V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS,
		.rangelow   =    50000000,
		.rangehigh  =  2000000000,
	पूर्ण,
पूर्ण;

अटल व्योम vivid_thपढ़ो_sdr_cap_tick(काष्ठा vivid_dev *dev)
अणु
	काष्ठा vivid_buffer *sdr_cap_buf = शून्य;

	dprपूर्णांकk(dev, 1, "SDR Capture Thread Tick\n");

	/* Drop a certain percentage of buffers. */
	अगर (dev->perc_dropped_buffers &&
	    pअक्रमom_u32_max(100) < dev->perc_dropped_buffers)
		वापस;

	spin_lock(&dev->slock);
	अगर (!list_empty(&dev->sdr_cap_active)) अणु
		sdr_cap_buf = list_entry(dev->sdr_cap_active.next,
					 काष्ठा vivid_buffer, list);
		list_del(&sdr_cap_buf->list);
	पूर्ण
	spin_unlock(&dev->slock);

	अगर (sdr_cap_buf) अणु
		sdr_cap_buf->vb.sequence = dev->sdr_cap_seq_count;
		v4l2_ctrl_request_setup(sdr_cap_buf->vb.vb2_buf.req_obj.req,
					&dev->ctrl_hdl_sdr_cap);
		v4l2_ctrl_request_complete(sdr_cap_buf->vb.vb2_buf.req_obj.req,
					   &dev->ctrl_hdl_sdr_cap);
		vivid_sdr_cap_process(dev, sdr_cap_buf);
		sdr_cap_buf->vb.vb2_buf.बारtamp =
			kसमय_get_ns() + dev->समय_wrap_offset;
		vb2_buffer_करोne(&sdr_cap_buf->vb.vb2_buf, dev->dqbuf_error ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
		dev->dqbuf_error = false;
	पूर्ण
पूर्ण

अटल पूर्णांक vivid_thपढ़ो_sdr_cap(व्योम *data)
अणु
	काष्ठा vivid_dev *dev = data;
	u64 samples_since_start;
	u64 buffers_since_start;
	u64 next_jअगरfies_since_start;
	अचिन्हित दीर्घ jअगरfies_since_start;
	अचिन्हित दीर्घ cur_jअगरfies;
	अचिन्हित रुको_jअगरfies;

	dprपूर्णांकk(dev, 1, "SDR Capture Thread Start\n");

	set_मुक्तzable();

	/* Resets frame counters */
	dev->sdr_cap_seq_offset = 0;
	अगर (dev->seq_wrap)
		dev->sdr_cap_seq_offset = 0xffffff80U;
	dev->jअगरfies_sdr_cap = jअगरfies;
	dev->sdr_cap_seq_resync = false;

	क्रम (;;) अणु
		try_to_मुक्तze();
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर (!mutex_trylock(&dev->mutex)) अणु
			schedule();
			जारी;
		पूर्ण

		cur_jअगरfies = jअगरfies;
		अगर (dev->sdr_cap_seq_resync) अणु
			dev->jअगरfies_sdr_cap = cur_jअगरfies;
			dev->sdr_cap_seq_offset = dev->sdr_cap_seq_count + 1;
			dev->sdr_cap_seq_count = 0;
			dev->sdr_cap_seq_resync = false;
		पूर्ण
		/* Calculate the number of jअगरfies since we started streaming */
		jअगरfies_since_start = cur_jअगरfies - dev->jअगरfies_sdr_cap;
		/* Get the number of buffers streamed since the start */
		buffers_since_start =
			(u64)jअगरfies_since_start * dev->sdr_adc_freq +
				      (HZ * SDR_CAP_SAMPLES_PER_BUF) / 2;
		करो_भाग(buffers_since_start, HZ * SDR_CAP_SAMPLES_PER_BUF);

		/*
		 * After more than 0xf0000000 (rounded करोwn to a multiple of
		 * 'jiffies-per-day' to ease jअगरfies_to_msecs calculation)
		 * jअगरfies have passed since we started streaming reset the
		 * counters and keep track of the sequence offset.
		 */
		अगर (jअगरfies_since_start > JIFFIES_RESYNC) अणु
			dev->jअगरfies_sdr_cap = cur_jअगरfies;
			dev->sdr_cap_seq_offset = buffers_since_start;
			buffers_since_start = 0;
		पूर्ण
		dev->sdr_cap_seq_count =
			buffers_since_start + dev->sdr_cap_seq_offset;

		vivid_thपढ़ो_sdr_cap_tick(dev);
		mutex_unlock(&dev->mutex);

		/*
		 * Calculate the number of samples streamed since we started,
		 * not including the current buffer.
		 */
		samples_since_start = buffers_since_start * SDR_CAP_SAMPLES_PER_BUF;

		/* And the number of jअगरfies since we started */
		jअगरfies_since_start = jअगरfies - dev->jअगरfies_sdr_cap;

		/* Increase by the number of samples in one buffer */
		samples_since_start += SDR_CAP_SAMPLES_PER_BUF;
		/*
		 * Calculate when that next buffer is supposed to start
		 * in jअगरfies since we started streaming.
		 */
		next_jअगरfies_since_start = samples_since_start * HZ +
					   dev->sdr_adc_freq / 2;
		करो_भाग(next_jअगरfies_since_start, dev->sdr_adc_freq);
		/* If it is in the past, then just schedule asap */
		अगर (next_jअगरfies_since_start < jअगरfies_since_start)
			next_jअगरfies_since_start = jअगरfies_since_start;

		रुको_jअगरfies = next_jअगरfies_since_start - jअगरfies_since_start;
		जबतक (jअगरfies - cur_jअगरfies < रुको_jअगरfies &&
		       !kthपढ़ो_should_stop())
			schedule();
	पूर्ण
	dprपूर्णांकk(dev, 1, "SDR Capture Thread End\n");
	वापस 0;
पूर्ण

अटल पूर्णांक sdr_cap_queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित *nbuffers, अचिन्हित *nplanes,
		       अचिन्हित sizes[], काष्ठा device *alloc_devs[])
अणु
	/* 2 = max 16-bit sample वापसed */
	sizes[0] = SDR_CAP_SAMPLES_PER_BUF * 2;
	*nplanes = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक sdr_cap_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित size = SDR_CAP_SAMPLES_PER_BUF * 2;

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	अगर (dev->buf_prepare_error) अणु
		/*
		 * Error injection: test what happens अगर buf_prepare() वापसs
		 * an error.
		 */
		dev->buf_prepare_error = false;
		वापस -EINVAL;
	पूर्ण
	अगर (vb2_plane_size(vb, 0) < size) अणु
		dprपूर्णांकk(dev, 1, "%s data will not fit into plane (%lu < %u)\n",
				__func__, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण
	vb2_set_plane_payload(vb, 0, size);

	वापस 0;
पूर्ण

अटल व्योम sdr_cap_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vivid_buffer *buf = container_of(vbuf, काष्ठा vivid_buffer, vb);

	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	spin_lock(&dev->slock);
	list_add_tail(&buf->list, &dev->sdr_cap_active);
	spin_unlock(&dev->slock);
पूर्ण

अटल पूर्णांक sdr_cap_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित count)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	पूर्णांक err = 0;

	dprपूर्णांकk(dev, 1, "%s\n", __func__);
	dev->sdr_cap_seq_count = 0;
	अगर (dev->start_streaming_error) अणु
		dev->start_streaming_error = false;
		err = -EINVAL;
	पूर्ण अन्यथा अगर (dev->kthपढ़ो_sdr_cap == शून्य) अणु
		dev->kthपढ़ो_sdr_cap = kthपढ़ो_run(vivid_thपढ़ो_sdr_cap, dev,
				"%s-sdr-cap", dev->v4l2_dev.name);

		अगर (IS_ERR(dev->kthपढ़ो_sdr_cap)) अणु
			v4l2_err(&dev->v4l2_dev, "kernel_thread() failed\n");
			err = PTR_ERR(dev->kthपढ़ो_sdr_cap);
			dev->kthपढ़ो_sdr_cap = शून्य;
		पूर्ण
	पूर्ण
	अगर (err) अणु
		काष्ठा vivid_buffer *buf, *पंचांगp;

		list_क्रम_each_entry_safe(buf, पंचांगp, &dev->sdr_cap_active, list) अणु
			list_del(&buf->list);
			vb2_buffer_करोne(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम sdr_cap_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);

	अगर (dev->kthपढ़ो_sdr_cap == शून्य)
		वापस;

	जबतक (!list_empty(&dev->sdr_cap_active)) अणु
		काष्ठा vivid_buffer *buf;

		buf = list_entry(dev->sdr_cap_active.next,
				काष्ठा vivid_buffer, list);
		list_del(&buf->list);
		v4l2_ctrl_request_complete(buf->vb.vb2_buf.req_obj.req,
					   &dev->ctrl_hdl_sdr_cap);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण

	/* shutकरोwn control thपढ़ो */
	kthपढ़ो_stop(dev->kthपढ़ो_sdr_cap);
	dev->kthपढ़ो_sdr_cap = शून्य;
पूर्ण

अटल व्योम sdr_cap_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &dev->ctrl_hdl_sdr_cap);
पूर्ण

स्थिर काष्ठा vb2_ops vivid_sdr_cap_qops = अणु
	.queue_setup		= sdr_cap_queue_setup,
	.buf_prepare		= sdr_cap_buf_prepare,
	.buf_queue		= sdr_cap_buf_queue,
	.start_streaming	= sdr_cap_start_streaming,
	.stop_streaming		= sdr_cap_stop_streaming,
	.buf_request_complete	= sdr_cap_buf_request_complete,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

पूर्णांक vivid_sdr_क्रमागत_freq_bands(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_frequency_band *band)
अणु
	चयन (band->tuner) अणु
	हाल 0:
		अगर (band->index >= ARRAY_SIZE(bands_adc))
			वापस -EINVAL;
		*band = bands_adc[band->index];
		वापस 0;
	हाल 1:
		अगर (band->index >= ARRAY_SIZE(bands_fm))
			वापस -EINVAL;
		*band = bands_fm[band->index];
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक vivid_sdr_g_frequency(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	चयन (vf->tuner) अणु
	हाल 0:
		vf->frequency = dev->sdr_adc_freq;
		vf->type = V4L2_TUNER_ADC;
		वापस 0;
	हाल 1:
		vf->frequency = dev->sdr_fm_freq;
		vf->type = V4L2_TUNER_RF;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक vivid_sdr_s_frequency(काष्ठा file *file, व्योम *fh,
		स्थिर काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	अचिन्हित freq = vf->frequency;
	अचिन्हित band;

	चयन (vf->tuner) अणु
	हाल 0:
		अगर (vf->type != V4L2_TUNER_ADC)
			वापस -EINVAL;
		अगर (freq < BAND_ADC_0)
			band = 0;
		अन्यथा अगर (freq < BAND_ADC_1)
			band = 1;
		अन्यथा
			band = 2;

		freq = clamp_t(अचिन्हित, freq,
				bands_adc[band].rangelow,
				bands_adc[band].rangehigh);

		अगर (vb2_is_streaming(&dev->vb_sdr_cap_q) &&
		    freq != dev->sdr_adc_freq) अणु
			/* resync the thपढ़ो's timings */
			dev->sdr_cap_seq_resync = true;
		पूर्ण
		dev->sdr_adc_freq = freq;
		वापस 0;
	हाल 1:
		अगर (vf->type != V4L2_TUNER_RF)
			वापस -EINVAL;
		dev->sdr_fm_freq = clamp_t(अचिन्हित, freq,
				bands_fm[0].rangelow,
				bands_fm[0].rangehigh);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक vivid_sdr_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *vt)
अणु
	चयन (vt->index) अणु
	हाल 0:
		strscpy(vt->name, "ADC", माप(vt->name));
		vt->type = V4L2_TUNER_ADC;
		vt->capability =
			V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		vt->rangelow = bands_adc[0].rangelow;
		vt->rangehigh = bands_adc[2].rangehigh;
		वापस 0;
	हाल 1:
		strscpy(vt->name, "RF", माप(vt->name));
		vt->type = V4L2_TUNER_RF;
		vt->capability =
			V4L2_TUNER_CAP_1HZ | V4L2_TUNER_CAP_FREQ_BANDS;
		vt->rangelow = bands_fm[0].rangelow;
		vt->rangehigh = bands_fm[0].rangehigh;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक vivid_sdr_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	अगर (vt->index > 1)
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक vidioc_क्रमागत_fmt_sdr_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;
	f->pixelक्रमmat = क्रमmats[f->index].pixelक्रमmat;
	वापस 0;
पूर्ण

पूर्णांक vidioc_g_fmt_sdr_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	f->fmt.sdr.pixelक्रमmat = dev->sdr_pixelक्रमmat;
	f->fmt.sdr.buffersize = dev->sdr_buffersize;
	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));
	वापस 0;
पूर्ण

पूर्णांक vidioc_s_fmt_sdr_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा vb2_queue *q = &dev->vb_sdr_cap_q;
	पूर्णांक i;

	अगर (vb2_is_busy(q))
		वापस -EBUSY;

	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));
	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == f->fmt.sdr.pixelक्रमmat) अणु
			dev->sdr_pixelक्रमmat = क्रमmats[i].pixelक्रमmat;
			dev->sdr_buffersize = क्रमmats[i].buffersize;
			f->fmt.sdr.buffersize = क्रमmats[i].buffersize;
			वापस 0;
		पूर्ण
	पूर्ण
	dev->sdr_pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	dev->sdr_buffersize = क्रमmats[0].buffersize;
	f->fmt.sdr.pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	f->fmt.sdr.buffersize = क्रमmats[0].buffersize;
	वापस 0;
पूर्ण

पूर्णांक vidioc_try_fmt_sdr_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक i;

	स_रखो(f->fmt.sdr.reserved, 0, माप(f->fmt.sdr.reserved));
	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		अगर (क्रमmats[i].pixelक्रमmat == f->fmt.sdr.pixelक्रमmat) अणु
			f->fmt.sdr.buffersize = क्रमmats[i].buffersize;
			वापस 0;
		पूर्ण
	पूर्ण
	f->fmt.sdr.pixelक्रमmat = क्रमmats[0].pixelक्रमmat;
	f->fmt.sdr.buffersize = क्रमmats[0].buffersize;
	वापस 0;
पूर्ण

#घोषणा FIXP_N    (15)
#घोषणा FIXP_FRAC (1 << FIXP_N)
#घोषणा FIXP_2PI  ((पूर्णांक)(2 * 3.141592653589 * FIXP_FRAC))
#घोषणा M_100000PI (3.14159 * 100000)

व्योम vivid_sdr_cap_process(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf)
अणु
	u8 *vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ plane_size = vb2_plane_size(&buf->vb.vb2_buf, 0);
	s64 s64पंचांगp;
	s32 src_phase_step;
	s32 mod_phase_step;
	s32 fixp_i;
	s32 fixp_q;

	/* calculate phase step */
	#घोषणा BEEP_FREQ 1000 /* 1kHz beep */
	src_phase_step = DIV_ROUND_CLOSEST(FIXP_2PI * BEEP_FREQ,
					   dev->sdr_adc_freq);

	क्रम (i = 0; i < plane_size; i += 2) अणु
		mod_phase_step = fixp_cos32_rad(dev->sdr_fixp_src_phase,
						FIXP_2PI) >> (31 - FIXP_N);

		dev->sdr_fixp_src_phase += src_phase_step;
		s64पंचांगp = (s64) mod_phase_step * dev->sdr_fm_deviation;
		dev->sdr_fixp_mod_phase += भाग_s64(s64पंचांगp, M_100000PI);

		/*
		 * Transfer phase angle to [0, 2xPI] in order to aव्योम variable
		 * overflow and make it suitable क्रम cosine implementation
		 * used, which करोes not support negative angles.
		 */
		dev->sdr_fixp_src_phase %= FIXP_2PI;
		dev->sdr_fixp_mod_phase %= FIXP_2PI;

		अगर (dev->sdr_fixp_mod_phase < 0)
			dev->sdr_fixp_mod_phase += FIXP_2PI;

		fixp_i = fixp_cos32_rad(dev->sdr_fixp_mod_phase, FIXP_2PI);
		fixp_q = fixp_sin32_rad(dev->sdr_fixp_mod_phase, FIXP_2PI);

		/* Normalize fraction values represented with 32 bit precision
		 * to fixed poपूर्णांक representation with FIXP_N bits */
		fixp_i >>= (31 - FIXP_N);
		fixp_q >>= (31 - FIXP_N);

		चयन (dev->sdr_pixelक्रमmat) अणु
		हाल V4L2_SDR_FMT_CU8:
			/* convert 'fixp float' to u8 [0, +255] */
			/* u8 = X * 127.5 + 127.5; X is भग्न [-1.0, +1.0] */
			fixp_i = fixp_i * 1275 + FIXP_FRAC * 1275;
			fixp_q = fixp_q * 1275 + FIXP_FRAC * 1275;
			*vbuf++ = DIV_ROUND_CLOSEST(fixp_i, FIXP_FRAC * 10);
			*vbuf++ = DIV_ROUND_CLOSEST(fixp_q, FIXP_FRAC * 10);
			अवरोध;
		हाल V4L2_SDR_FMT_CS8:
			/* convert 'fixp float' to s8 [-128, +127] */
			/* s8 = X * 127.5 - 0.5; X is भग्न [-1.0, +1.0] */
			fixp_i = fixp_i * 1275 - FIXP_FRAC * 5;
			fixp_q = fixp_q * 1275 - FIXP_FRAC * 5;
			*vbuf++ = DIV_ROUND_CLOSEST(fixp_i, FIXP_FRAC * 10);
			*vbuf++ = DIV_ROUND_CLOSEST(fixp_q, FIXP_FRAC * 10);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
