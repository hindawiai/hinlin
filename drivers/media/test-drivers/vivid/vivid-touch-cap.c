<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-touch-cap.c - touch support functions.
 */

#समावेश "vivid-core.h"
#समावेश "vivid-kthread-touch.h"
#समावेश "vivid-vid-common.h"
#समावेश "vivid-touch-cap.h"

अटल पूर्णांक touch_cap_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *nbuffers,
				 अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
				 काष्ठा device *alloc_devs[])
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	काष्ठा v4l2_pix_क्रमmat *f = &dev->tch_क्रमmat;
	अचिन्हित पूर्णांक size = f->sizeimage;

	अगर (*nplanes) अणु
		अगर (sizes[0] < size)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		sizes[0] = size;
	पूर्ण

	अगर (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;

	*nplanes = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक touch_cap_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा v4l2_pix_क्रमmat *f = &dev->tch_क्रमmat;
	अचिन्हित पूर्णांक size = f->sizeimage;

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

अटल व्योम touch_cap_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vivid_buffer *buf = container_of(vbuf, काष्ठा vivid_buffer, vb);

	vbuf->field = V4L2_FIELD_NONE;
	spin_lock(&dev->slock);
	list_add_tail(&buf->list, &dev->touch_cap_active);
	spin_unlock(&dev->slock);
पूर्ण

अटल पूर्णांक touch_cap_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);
	पूर्णांक err;

	dev->touch_cap_seq_count = 0;
	अगर (dev->start_streaming_error) अणु
		dev->start_streaming_error = false;
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = vivid_start_generating_touch_cap(dev);
	पूर्ण
	अगर (err) अणु
		काष्ठा vivid_buffer *buf, *पंचांगp;

		list_क्रम_each_entry_safe(buf, पंचांगp,
					 &dev->touch_cap_active, list) अणु
			list_del(&buf->list);
			vb2_buffer_करोne(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम touch_cap_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vq);

	vivid_stop_generating_touch_cap(dev);
पूर्ण

अटल व्योम touch_cap_buf_request_complete(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vivid_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	v4l2_ctrl_request_complete(vb->req_obj.req, &dev->ctrl_hdl_touch_cap);
पूर्ण

स्थिर काष्ठा vb2_ops vivid_touch_cap_qops = अणु
	.queue_setup		= touch_cap_queue_setup,
	.buf_prepare		= touch_cap_buf_prepare,
	.buf_queue		= touch_cap_buf_queue,
	.start_streaming	= touch_cap_start_streaming,
	.stop_streaming		= touch_cap_stop_streaming,
	.buf_request_complete	= touch_cap_buf_request_complete,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

पूर्णांक vivid_क्रमागत_fmt_tch(काष्ठा file *file, व्योम  *priv, काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_TCH_FMT_DELTA_TD16;
	वापस 0;
पूर्ण

पूर्णांक vivid_g_fmt_tch(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (dev->multiplanar)
		वापस -ENOTTY;
	f->fmt.pix = dev->tch_क्रमmat;
	वापस 0;
पूर्ण

पूर्णांक vivid_g_fmt_tch_mplane(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);
	काष्ठा v4l2_क्रमmat sp_fmt;

	अगर (!dev->multiplanar)
		वापस -ENOTTY;
	sp_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	sp_fmt.fmt.pix = dev->tch_क्रमmat;
	fmt_sp2mp(&sp_fmt, f);
	वापस 0;
पूर्ण

पूर्णांक vivid_g_parm_tch(काष्ठा file *file, व्योम *priv,
		     काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा vivid_dev *dev = video_drvdata(file);

	अगर (parm->type != (dev->multiplanar ?
			   V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE :
			   V4L2_BUF_TYPE_VIDEO_CAPTURE))
		वापस -EINVAL;

	parm->parm.capture.capability   = V4L2_CAP_TIMEPERFRAME;
	parm->parm.capture.समयperframe = dev->समयperframe_tch_cap;
	parm->parm.capture.पढ़ोbuffers  = 1;
	वापस 0;
पूर्ण

पूर्णांक vivid_क्रमागत_input_tch(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_input *inp)
अणु
	अगर (inp->index)
		वापस -EINVAL;

	inp->type = V4L2_INPUT_TYPE_TOUCH;
	strscpy(inp->name, "Vivid Touch", माप(inp->name));
	inp->capabilities = 0;
	वापस 0;
पूर्ण

पूर्णांक vivid_g_input_tch(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

पूर्णांक vivid_set_touch(काष्ठा vivid_dev *dev, अचिन्हित पूर्णांक i)
अणु
	काष्ठा v4l2_pix_क्रमmat *f = &dev->tch_क्रमmat;

	अगर (i)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_TCH_FMT_DELTA_TD16;
	f->width =  VIVID_TCH_WIDTH;
	f->height = VIVID_TCH_HEIGHT;
	f->field = V4L2_FIELD_NONE;
	f->colorspace = V4L2_COLORSPACE_RAW;
	f->bytesperline = f->width * माप(s16);
	f->sizeimage = f->width * f->height * माप(s16);
	वापस 0;
पूर्ण

पूर्णांक vivid_s_input_tch(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	वापस vivid_set_touch(video_drvdata(file), i);
पूर्ण

अटल व्योम vivid_fill_buff_noise(__s16 *tch_buf, पूर्णांक size)
अणु
	पूर्णांक i;

	/* Fill 10% of the values within range -3 and 3, zero the others */
	क्रम (i = 0; i < size; i++) अणु
		अचिन्हित पूर्णांक अक्रम = get_अक्रमom_पूर्णांक();

		अगर (अक्रम % 10)
			tch_buf[i] = 0;
		अन्यथा
			tch_buf[i] = (अक्रम / 10) % 7 - 3;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक get_अक्रमom_pressure(व्योम)
अणु
	वापस get_अक्रमom_पूर्णांक() % VIVID_PRESSURE_LIMIT;
पूर्ण

अटल व्योम vivid_tch_buf_set(काष्ठा v4l2_pix_क्रमmat *f,
			      __s16 *tch_buf,
			      पूर्णांक index)
अणु
	अचिन्हित पूर्णांक x = index % f->width;
	अचिन्हित पूर्णांक y = index / f->width;
	अचिन्हित पूर्णांक offset = VIVID_MIN_PRESSURE;

	tch_buf[index] = offset + get_अक्रमom_pressure();
	offset /= 2;
	अगर (x)
		tch_buf[index - 1] = offset + get_अक्रमom_pressure();
	अगर (x < f->width - 1)
		tch_buf[index + 1] = offset + get_अक्रमom_pressure();
	अगर (y)
		tch_buf[index - f->width] = offset + get_अक्रमom_pressure();
	अगर (y < f->height - 1)
		tch_buf[index + f->width] = offset + get_अक्रमom_pressure();
	offset /= 2;
	अगर (x && y)
		tch_buf[index - 1 - f->width] = offset + get_अक्रमom_pressure();
	अगर (x < f->width - 1 && y)
		tch_buf[index + 1 - f->width] = offset + get_अक्रमom_pressure();
	अगर (x && y < f->height - 1)
		tch_buf[index - 1 + f->width] = offset + get_अक्रमom_pressure();
	अगर (x < f->width - 1 && y < f->height - 1)
		tch_buf[index + 1 + f->width] = offset + get_अक्रमom_pressure();
पूर्ण

व्योम vivid_fillbuff_tch(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf)
अणु
	काष्ठा v4l2_pix_क्रमmat *f = &dev->tch_क्रमmat;
	पूर्णांक size = f->width * f->height;
	पूर्णांक x, y, xstart, ystart, offset_x, offset_y;
	अचिन्हित पूर्णांक test_pattern, test_pat_idx, अक्रम;

	__s16 *tch_buf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	buf->vb.sequence = dev->touch_cap_seq_count;
	test_pattern = (buf->vb.sequence / TCH_SEQ_COUNT) % TEST_CASE_MAX;
	test_pat_idx = buf->vb.sequence % TCH_SEQ_COUNT;

	vivid_fill_buff_noise(tch_buf, size);

	अगर (test_pat_idx >= TCH_PATTERN_COUNT)
		वापस;

	अगर (test_pat_idx == 0)
		dev->tch_pat_अक्रमom = get_अक्रमom_पूर्णांक();
	अक्रम = dev->tch_pat_अक्रमom;

	चयन (test_pattern) अणु
	हाल SINGLE_TAP:
		अगर (test_pat_idx == 2)
			vivid_tch_buf_set(f, tch_buf, अक्रम % size);
		अवरोध;
	हाल DOUBLE_TAP:
		अगर (test_pat_idx == 2 || test_pat_idx == 4)
			vivid_tch_buf_set(f, tch_buf, अक्रम % size);
		अवरोध;
	हाल TRIPLE_TAP:
		अगर (test_pat_idx == 2 || test_pat_idx == 4 || test_pat_idx == 6)
			vivid_tch_buf_set(f, tch_buf, अक्रम % size);
		अवरोध;
	हाल MOVE_LEFT_TO_RIGHT:
		vivid_tch_buf_set(f, tch_buf,
				  (अक्रम % f->height) * f->width +
				  test_pat_idx *
				  (f->width / TCH_PATTERN_COUNT));
		अवरोध;
	हाल ZOOM_IN:
		x = f->width / 2;
		y = f->height / 2;
		offset_x = ((TCH_PATTERN_COUNT - 1 - test_pat_idx) * x) /
				TCH_PATTERN_COUNT;
		offset_y = ((TCH_PATTERN_COUNT - 1 - test_pat_idx) * y) /
				TCH_PATTERN_COUNT;
		vivid_tch_buf_set(f, tch_buf,
				  (x - offset_x) + f->width * (y - offset_y));
		vivid_tch_buf_set(f, tch_buf,
				  (x + offset_x) + f->width * (y + offset_y));
		अवरोध;
	हाल ZOOM_OUT:
		x = f->width / 2;
		y = f->height / 2;
		offset_x = (test_pat_idx * x) / TCH_PATTERN_COUNT;
		offset_y = (test_pat_idx * y) / TCH_PATTERN_COUNT;
		vivid_tch_buf_set(f, tch_buf,
				  (x - offset_x) + f->width * (y - offset_y));
		vivid_tch_buf_set(f, tch_buf,
				  (x + offset_x) + f->width * (y + offset_y));
		अवरोध;
	हाल PALM_PRESS:
		क्रम (x = 0; x < f->width; x++)
			क्रम (y = f->height / 2; y < f->height; y++)
				tch_buf[x + f->width * y] = VIVID_MIN_PRESSURE +
							get_अक्रमom_pressure();
		अवरोध;
	हाल MULTIPLE_PRESS:
		/* 16 pressure poपूर्णांकs */
		क्रम (y = 0; y < 4; y++) अणु
			क्रम (x = 0; x < 4; x++) अणु
				ystart = (y * f->height) / 4 + f->height / 8;
				xstart = (x * f->width) / 4 + f->width / 8;
				vivid_tch_buf_set(f, tch_buf,
						  ystart * f->width + xstart);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
#अगर_घोषित __BIG_ENDIAN__
	क्रम (x = 0; x < size; x++)
		tch_buf[x] = (__क्रमce s16)__cpu_to_le16((u16)tch_buf[x]);
#पूर्ण_अगर
पूर्ण
