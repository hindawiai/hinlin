<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2015 Synaptics Incorporated
 * Copyright (C) 2016 Zodiac Inflight Innovations
 */

#समावेश <linux/kernel.h>
#समावेश <linux/rmi.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश "rmi_driver.h"

#घोषणा F54_NAME		"rmi4_f54"

/* F54 data offsets */
#घोषणा F54_REPORT_DATA_OFFSET  3
#घोषणा F54_FIFO_OFFSET         1
#घोषणा F54_NUM_TX_OFFSET       1
#घोषणा F54_NUM_RX_OFFSET       0

/*
 * The smbus protocol can पढ़ो only 32 bytes max at a समय.
 * But this should be fine क्रम i2c/spi as well.
 */
#घोषणा F54_REPORT_DATA_SIZE	32

/* F54 commands */
#घोषणा F54_GET_REPORT          1
#घोषणा F54_FORCE_CAL           2

/* F54 capabilities */
#घोषणा F54_CAP_BASELINE	(1 << 2)
#घोषणा F54_CAP_IMAGE8		(1 << 3)
#घोषणा F54_CAP_IMAGE16		(1 << 6)

/**
 * क्रमागत rmi_f54_report_type - RMI4 F54 report types
 *
 * @F54_REPORT_NONE:	No Image Report.
 *
 * @F54_8BIT_IMAGE:	Normalized 8-Bit Image Report. The capacitance variance
 *			from baseline क्रम each pixel.
 *
 * @F54_16BIT_IMAGE:	Normalized 16-Bit Image Report. The capacitance variance
 *			from baseline क्रम each pixel.
 *
 * @F54_RAW_16BIT_IMAGE:
 *			Raw 16-Bit Image Report. The raw capacitance क्रम each
 *			pixel.
 *
 * @F54_TRUE_BASELINE:	True Baseline Report. The baseline capacitance क्रम each
 *			pixel.
 *
 * @F54_FULL_RAW_CAP:   Full Raw Capacitance Report. The raw capacitance with
 *			low reference set to its minimum value and high
 *			reference set to its maximum value.
 *
 * @F54_FULL_RAW_CAP_RX_OFFSET_REMOVED:
 *			Full Raw Capacitance with Receiver Offset Removed
 *			Report. Set Low reference to its minimum value and high
 *			references to its maximum value, then report the raw
 *			capacitance क्रम each pixel.
 *
 * @F54_MAX_REPORT_TYPE:
 *			Maximum number of Report Types.  Used क्रम sanity
 *			checking.
 */
क्रमागत rmi_f54_report_type अणु
	F54_REPORT_NONE = 0,
	F54_8BIT_IMAGE = 1,
	F54_16BIT_IMAGE = 2,
	F54_RAW_16BIT_IMAGE = 3,
	F54_TRUE_BASELINE = 9,
	F54_FULL_RAW_CAP = 19,
	F54_FULL_RAW_CAP_RX_OFFSET_REMOVED = 20,
	F54_MAX_REPORT_TYPE,
पूर्ण;

अटल स्थिर अक्षर * स्थिर rmi_f54_report_type_names[] = अणु
	[F54_REPORT_NONE]		= "Unknown",
	[F54_8BIT_IMAGE]		= "Normalized 8-Bit Image",
	[F54_16BIT_IMAGE]		= "Normalized 16-Bit Image",
	[F54_RAW_16BIT_IMAGE]		= "Raw 16-Bit Image",
	[F54_TRUE_BASELINE]		= "True Baseline",
	[F54_FULL_RAW_CAP]		= "Full Raw Capacitance",
	[F54_FULL_RAW_CAP_RX_OFFSET_REMOVED]
					= "Full Raw Capacitance RX Offset Removed",
पूर्ण;

काष्ठा f54_data अणु
	काष्ठा rmi_function *fn;

	u8 num_rx_electrodes;
	u8 num_tx_electrodes;
	u8 capabilities;
	u16 घड़ी_rate;
	u8 family;

	क्रमागत rmi_f54_report_type report_type;
	u8 *report_data;
	पूर्णांक report_size;

	bool is_busy;
	काष्ठा mutex status_mutex;
	काष्ठा mutex data_mutex;

	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा delayed_work work;
	अचिन्हित दीर्घ समयout;

	काष्ठा completion cmd_करोne;

	/* V4L2 support */
	काष्ठा v4l2_device v4l2;
	काष्ठा v4l2_pix_क्रमmat क्रमmat;
	काष्ठा video_device vdev;
	काष्ठा vb2_queue queue;
	काष्ठा mutex lock;
	u32 sequence;
	पूर्णांक input;
	क्रमागत rmi_f54_report_type inमाला_दो[F54_MAX_REPORT_TYPE];
पूर्ण;

/*
 * Basic checks on report_type to ensure we ग_लिखो a valid type
 * to the sensor.
 */
अटल bool is_f54_report_type_valid(काष्ठा f54_data *f54,
				     क्रमागत rmi_f54_report_type reptype)
अणु
	चयन (reptype) अणु
	हाल F54_8BIT_IMAGE:
		वापस f54->capabilities & F54_CAP_IMAGE8;
	हाल F54_16BIT_IMAGE:
	हाल F54_RAW_16BIT_IMAGE:
		वापस f54->capabilities & F54_CAP_IMAGE16;
	हाल F54_TRUE_BASELINE:
		वापस f54->capabilities & F54_CAP_IMAGE16;
	हाल F54_FULL_RAW_CAP:
	हाल F54_FULL_RAW_CAP_RX_OFFSET_REMOVED:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल क्रमागत rmi_f54_report_type rmi_f54_get_reptype(काष्ठा f54_data *f54,
						अचिन्हित पूर्णांक i)
अणु
	अगर (i >= F54_MAX_REPORT_TYPE)
		वापस F54_REPORT_NONE;

	वापस f54->inमाला_दो[i];
पूर्ण

अटल व्योम rmi_f54_create_input_map(काष्ठा f54_data *f54)
अणु
	पूर्णांक i = 0;
	क्रमागत rmi_f54_report_type reptype;

	क्रम (reptype = 1; reptype < F54_MAX_REPORT_TYPE; reptype++) अणु
		अगर (!is_f54_report_type_valid(f54, reptype))
			जारी;

		f54->inमाला_दो[i++] = reptype;
	पूर्ण

	/* Reमुख्यing values are zero via kzalloc */
पूर्ण

अटल पूर्णांक rmi_f54_request_report(काष्ठा rmi_function *fn, u8 report_type)
अणु
	काष्ठा f54_data *f54 = dev_get_drvdata(&fn->dev);
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	पूर्णांक error;

	/* Write Report Type पूर्णांकo F54_AD_Data0 */
	अगर (f54->report_type != report_type) अणु
		error = rmi_ग_लिखो(rmi_dev, f54->fn->fd.data_base_addr,
				  report_type);
		अगर (error)
			वापस error;
		f54->report_type = report_type;
	पूर्ण

	/*
	 * Small delay after disabling पूर्णांकerrupts to aव्योम race condition
	 * in firmare. This value is a bit higher than असलolutely necessary.
	 * Should be हटाओd once issue is resolved in firmware.
	 */
	usleep_range(2000, 3000);

	mutex_lock(&f54->data_mutex);

	error = rmi_ग_लिखो(rmi_dev, fn->fd.command_base_addr, F54_GET_REPORT);
	अगर (error < 0)
		जाओ unlock;

	init_completion(&f54->cmd_करोne);

	f54->is_busy = 1;
	f54->समयout = jअगरfies + msecs_to_jअगरfies(100);

	queue_delayed_work(f54->workqueue, &f54->work, 0);

unlock:
	mutex_unlock(&f54->data_mutex);

	वापस error;
पूर्ण

अटल माप_प्रकार rmi_f54_get_report_size(काष्ठा f54_data *f54)
अणु
	काष्ठा rmi_device *rmi_dev = f54->fn->rmi_dev;
	काष्ठा rmi_driver_data *drv_data = dev_get_drvdata(&rmi_dev->dev);
	u8 rx = drv_data->num_rx_electrodes ? : f54->num_rx_electrodes;
	u8 tx = drv_data->num_tx_electrodes ? : f54->num_tx_electrodes;
	माप_प्रकार size;

	चयन (rmi_f54_get_reptype(f54, f54->input)) अणु
	हाल F54_8BIT_IMAGE:
		size = rx * tx;
		अवरोध;
	हाल F54_16BIT_IMAGE:
	हाल F54_RAW_16BIT_IMAGE:
	हाल F54_TRUE_BASELINE:
	हाल F54_FULL_RAW_CAP:
	हाल F54_FULL_RAW_CAP_RX_OFFSET_REMOVED:
		size = माप(u16) * rx * tx;
		अवरोध;
	शेष:
		size = 0;
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक rmi_f54_get_pixel_fmt(क्रमागत rmi_f54_report_type reptype, u32 *pixfmt)
अणु
	पूर्णांक ret = 0;

	चयन (reptype) अणु
	हाल F54_8BIT_IMAGE:
		*pixfmt = V4L2_TCH_FMT_DELTA_TD08;
		अवरोध;

	हाल F54_16BIT_IMAGE:
		*pixfmt = V4L2_TCH_FMT_DELTA_TD16;
		अवरोध;

	हाल F54_RAW_16BIT_IMAGE:
	हाल F54_TRUE_BASELINE:
	हाल F54_FULL_RAW_CAP:
	हाल F54_FULL_RAW_CAP_RX_OFFSET_REMOVED:
		*pixfmt = V4L2_TCH_FMT_TU16;
		अवरोध;

	हाल F54_REPORT_NONE:
	हाल F54_MAX_REPORT_TYPE:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations rmi_f54_video_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.unlocked_ioctl = video_ioctl2,
	.पढ़ो = vb2_fop_पढ़ो,
	.mmap = vb2_fop_mmap,
	.poll = vb2_fop_poll,
पूर्ण;

अटल पूर्णांक rmi_f54_queue_setup(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक *nbuffers,
			       अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
			       काष्ठा device *alloc_devs[])
अणु
	काष्ठा f54_data *f54 = q->drv_priv;

	अगर (*nplanes)
		वापस sizes[0] < rmi_f54_get_report_size(f54) ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = rmi_f54_get_report_size(f54);

	वापस 0;
पूर्ण

अटल व्योम rmi_f54_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा f54_data *f54 = vb2_get_drv_priv(vb->vb2_queue);
	u16 *ptr;
	क्रमागत vb2_buffer_state state;
	क्रमागत rmi_f54_report_type reptype;
	पूर्णांक ret;

	mutex_lock(&f54->status_mutex);

	vb2_set_plane_payload(vb, 0, 0);
	reptype = rmi_f54_get_reptype(f54, f54->input);
	अगर (reptype == F54_REPORT_NONE) अणु
		state = VB2_BUF_STATE_ERROR;
		जाओ करोne;
	पूर्ण

	अगर (f54->is_busy) अणु
		state = VB2_BUF_STATE_ERROR;
		जाओ करोne;
	पूर्ण

	ret = rmi_f54_request_report(f54->fn, reptype);
	अगर (ret) अणु
		dev_err(&f54->fn->dev, "Error requesting F54 report\n");
		state = VB2_BUF_STATE_ERROR;
		जाओ करोne;
	पूर्ण

	/* get frame data */
	mutex_lock(&f54->data_mutex);

	जबतक (f54->is_busy) अणु
		mutex_unlock(&f54->data_mutex);
		अगर (!रुको_क्रम_completion_समयout(&f54->cmd_करोne,
						 msecs_to_jअगरfies(1000))) अणु
			dev_err(&f54->fn->dev, "Timed out\n");
			state = VB2_BUF_STATE_ERROR;
			जाओ करोne;
		पूर्ण
		mutex_lock(&f54->data_mutex);
	पूर्ण

	ptr = vb2_plane_vaddr(vb, 0);
	अगर (!ptr) अणु
		dev_err(&f54->fn->dev, "Error acquiring frame ptr\n");
		state = VB2_BUF_STATE_ERROR;
		जाओ data_करोne;
	पूर्ण

	स_नकल(ptr, f54->report_data, f54->report_size);
	vb2_set_plane_payload(vb, 0, rmi_f54_get_report_size(f54));
	state = VB2_BUF_STATE_DONE;

data_करोne:
	mutex_unlock(&f54->data_mutex);
करोne:
	vb->बारtamp = kसमय_get_ns();
	vbuf->field = V4L2_FIELD_NONE;
	vbuf->sequence = f54->sequence++;
	vb2_buffer_करोne(vb, state);
	mutex_unlock(&f54->status_mutex);
पूर्ण

अटल व्योम rmi_f54_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा f54_data *f54 = vb2_get_drv_priv(q);

	f54->sequence = 0;
पूर्ण

/* V4L2 काष्ठाures */
अटल स्थिर काष्ठा vb2_ops rmi_f54_queue_ops = अणु
	.queue_setup            = rmi_f54_queue_setup,
	.buf_queue              = rmi_f54_buffer_queue,
	.stop_streaming		= rmi_f54_stop_streaming,
	.रुको_prepare           = vb2_ops_रुको_prepare,
	.रुको_finish            = vb2_ops_रुको_finish,
पूर्ण;

अटल स्थिर काष्ठा vb2_queue rmi_f54_queue = अणु
	.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
	.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ,
	.buf_काष्ठा_size = माप(काष्ठा vb2_v4l2_buffer),
	.ops = &rmi_f54_queue_ops,
	.mem_ops = &vb2_vदो_स्मृति_memops,
	.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC,
पूर्ण;

अटल पूर्णांक rmi_f54_vidioc_querycap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा f54_data *f54 = video_drvdata(file);

	strlcpy(cap->driver, F54_NAME, माप(cap->driver));
	strlcpy(cap->card, SYNAPTICS_INPUT_DEVICE_NAME, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		"rmi4:%s", dev_name(&f54->fn->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f54_vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_input *i)
अणु
	काष्ठा f54_data *f54 = video_drvdata(file);
	क्रमागत rmi_f54_report_type reptype;

	reptype = rmi_f54_get_reptype(f54, i->index);
	अगर (reptype == F54_REPORT_NONE)
		वापस -EINVAL;

	i->type = V4L2_INPUT_TYPE_TOUCH;

	strlcpy(i->name, rmi_f54_report_type_names[reptype], माप(i->name));
	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f54_set_input(काष्ठा f54_data *f54, अचिन्हित पूर्णांक i)
अणु
	काष्ठा rmi_device *rmi_dev = f54->fn->rmi_dev;
	काष्ठा rmi_driver_data *drv_data = dev_get_drvdata(&rmi_dev->dev);
	u8 rx = drv_data->num_rx_electrodes ? : f54->num_rx_electrodes;
	u8 tx = drv_data->num_tx_electrodes ? : f54->num_tx_electrodes;
	काष्ठा v4l2_pix_क्रमmat *f = &f54->क्रमmat;
	क्रमागत rmi_f54_report_type reptype;
	पूर्णांक ret;

	reptype = rmi_f54_get_reptype(f54, i);
	अगर (reptype == F54_REPORT_NONE)
		वापस -EINVAL;

	ret = rmi_f54_get_pixel_fmt(reptype, &f->pixelक्रमmat);
	अगर (ret)
		वापस ret;

	f54->input = i;

	f->width = rx;
	f->height = tx;
	f->field = V4L2_FIELD_NONE;
	f->colorspace = V4L2_COLORSPACE_RAW;
	f->bytesperline = f->width * माप(u16);
	f->sizeimage = f->width * f->height * माप(u16);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f54_vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	वापस rmi_f54_set_input(video_drvdata(file), i);
पूर्ण

अटल पूर्णांक rmi_f54_vidioc_g_input(काष्ठा file *file, व्योम *priv,
				  अचिन्हित पूर्णांक *i)
अणु
	काष्ठा f54_data *f54 = video_drvdata(file);

	*i = f54->input;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f54_vidioc_fmt(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा f54_data *f54 = video_drvdata(file);

	f->fmt.pix = f54->क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f54_vidioc_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_fmtdesc *fmt)
अणु
	काष्ठा f54_data *f54 = video_drvdata(file);

	अगर (fmt->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (fmt->index)
		वापस -EINVAL;

	fmt->pixelक्रमmat = f54->क्रमmat.pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f54_vidioc_g_parm(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_streamparm *a)
अणु
	अगर (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	a->parm.capture.पढ़ोbuffers = 1;
	a->parm.capture.समयperframe.numerator = 1;
	a->parm.capture.समयperframe.denominator = 10;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops rmi_f54_video_ioctl_ops = अणु
	.vidioc_querycap	= rmi_f54_vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = rmi_f54_vidioc_क्रमागत_fmt,
	.vidioc_s_fmt_vid_cap	= rmi_f54_vidioc_fmt,
	.vidioc_g_fmt_vid_cap	= rmi_f54_vidioc_fmt,
	.vidioc_try_fmt_vid_cap	= rmi_f54_vidioc_fmt,
	.vidioc_g_parm		= rmi_f54_vidioc_g_parm,

	.vidioc_क्रमागत_input	= rmi_f54_vidioc_क्रमागत_input,
	.vidioc_g_input		= rmi_f54_vidioc_g_input,
	.vidioc_s_input		= rmi_f54_vidioc_s_input,

	.vidioc_reqbufs		= vb2_ioctl_reqbufs,
	.vidioc_create_bufs	= vb2_ioctl_create_bufs,
	.vidioc_querybuf	= vb2_ioctl_querybuf,
	.vidioc_qbuf		= vb2_ioctl_qbuf,
	.vidioc_dqbuf		= vb2_ioctl_dqbuf,
	.vidioc_expbuf		= vb2_ioctl_expbuf,

	.vidioc_streamon	= vb2_ioctl_streamon,
	.vidioc_streamoff	= vb2_ioctl_streamoff,
पूर्ण;

अटल स्थिर काष्ठा video_device rmi_f54_video_device = अणु
	.name = "Synaptics RMI4",
	.fops = &rmi_f54_video_fops,
	.ioctl_ops = &rmi_f54_video_ioctl_ops,
	.release = video_device_release_empty,
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TOUCH |
		       V4L2_CAP_READWRITE | V4L2_CAP_STREAMING,
पूर्ण;

अटल व्योम rmi_f54_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा f54_data *f54 = container_of(work, काष्ठा f54_data, work.work);
	काष्ठा rmi_function *fn = f54->fn;
	u8 fअगरo[2];
	पूर्णांक report_size;
	u8 command;
	पूर्णांक error;
	पूर्णांक i;

	report_size = rmi_f54_get_report_size(f54);
	अगर (report_size == 0) अणु
		dev_err(&fn->dev, "Bad report size, report type=%d\n",
				f54->report_type);
		error = -EINVAL;
		जाओ error;     /* retry won't help */
	पूर्ण

	mutex_lock(&f54->data_mutex);

	/*
	 * Need to check अगर command has completed.
	 * If not try again later.
	 */
	error = rmi_पढ़ो(fn->rmi_dev, f54->fn->fd.command_base_addr,
			 &command);
	अगर (error) अणु
		dev_err(&fn->dev, "Failed to read back command\n");
		जाओ error;
	पूर्ण
	अगर (command & F54_GET_REPORT) अणु
		अगर (समय_after(jअगरfies, f54->समयout)) अणु
			dev_err(&fn->dev, "Get report command timed out\n");
			error = -ETIMEDOUT;
		पूर्ण
		report_size = 0;
		जाओ error;
	पूर्ण

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "Get report command completed, reading data\n");

	क्रम (i = 0; i < report_size; i += F54_REPORT_DATA_SIZE) अणु
		पूर्णांक size = min(F54_REPORT_DATA_SIZE, report_size - i);

		fअगरo[0] = i & 0xff;
		fअगरo[1] = i >> 8;
		error = rmi_ग_लिखो_block(fn->rmi_dev,
					fn->fd.data_base_addr + F54_FIFO_OFFSET,
					fअगरo, माप(fअगरo));
		अगर (error) अणु
			dev_err(&fn->dev, "Failed to set fifo start offset\n");
			जाओ पात;
		पूर्ण

		error = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.data_base_addr +
				       F54_REPORT_DATA_OFFSET,
				       f54->report_data + i, size);
		अगर (error) अणु
			dev_err(&fn->dev, "%s: read [%d bytes] returned %d\n",
				__func__, size, error);
			जाओ पात;
		पूर्ण
	पूर्ण

पात:
	f54->report_size = error ? 0 : report_size;
error:
	अगर (error)
		report_size = 0;

	अगर (report_size == 0 && !error) अणु
		queue_delayed_work(f54->workqueue, &f54->work,
				   msecs_to_jअगरfies(1));
	पूर्ण अन्यथा अणु
		f54->is_busy = false;
		complete(&f54->cmd_करोne);
	पूर्ण

	mutex_unlock(&f54->data_mutex);
पूर्ण

अटल पूर्णांक rmi_f54_config(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_driver *drv = fn->rmi_dev->driver;

	drv->clear_irq_bits(fn->rmi_dev, fn->irq_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f54_detect(काष्ठा rmi_function *fn)
अणु
	पूर्णांक error;
	काष्ठा f54_data *f54;
	u8 buf[6];

	f54 = dev_get_drvdata(&fn->dev);

	error = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.query_base_addr,
			       buf, माप(buf));
	अगर (error) अणु
		dev_err(&fn->dev, "%s: Failed to query F54 properties\n",
			__func__);
		वापस error;
	पूर्ण

	f54->num_rx_electrodes = buf[0];
	f54->num_tx_electrodes = buf[1];
	f54->capabilities = buf[2];
	f54->घड़ी_rate = buf[3] | (buf[4] << 8);
	f54->family = buf[5];

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "F54 num_rx_electrodes: %d\n",
		f54->num_rx_electrodes);
	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "F54 num_tx_electrodes: %d\n",
		f54->num_tx_electrodes);
	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "F54 capabilities: 0x%x\n",
		f54->capabilities);
	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "F54 clock rate: 0x%x\n",
		f54->घड़ी_rate);
	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "F54 family: 0x%x\n",
		f54->family);

	f54->is_busy = false;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f54_probe(काष्ठा rmi_function *fn)
अणु
	काष्ठा f54_data *f54;
	पूर्णांक ret;
	u8 rx, tx;

	f54 = devm_kzalloc(&fn->dev, माप(काष्ठा f54_data), GFP_KERNEL);
	अगर (!f54)
		वापस -ENOMEM;

	f54->fn = fn;
	dev_set_drvdata(&fn->dev, f54);

	ret = rmi_f54_detect(fn);
	अगर (ret)
		वापस ret;

	mutex_init(&f54->data_mutex);
	mutex_init(&f54->status_mutex);

	rx = f54->num_rx_electrodes;
	tx = f54->num_tx_electrodes;
	f54->report_data = devm_kzalloc(&fn->dev,
					array3_size(tx, rx, माप(u16)),
					GFP_KERNEL);
	अगर (f54->report_data == शून्य)
		वापस -ENOMEM;

	INIT_DELAYED_WORK(&f54->work, rmi_f54_work);

	f54->workqueue = create_singlethपढ़ो_workqueue("rmi4-poller");
	अगर (!f54->workqueue)
		वापस -ENOMEM;

	rmi_f54_create_input_map(f54);
	rmi_f54_set_input(f54, 0);

	/* रेजिस्टर video device */
	strlcpy(f54->v4l2.name, F54_NAME, माप(f54->v4l2.name));
	ret = v4l2_device_रेजिस्टर(&fn->dev, &f54->v4l2);
	अगर (ret) अणु
		dev_err(&fn->dev, "Unable to register video dev.\n");
		जाओ हटाओ_wq;
	पूर्ण

	/* initialize the queue */
	mutex_init(&f54->lock);
	f54->queue = rmi_f54_queue;
	f54->queue.drv_priv = f54;
	f54->queue.lock = &f54->lock;
	f54->queue.dev = &fn->dev;

	ret = vb2_queue_init(&f54->queue);
	अगर (ret)
		जाओ हटाओ_v4l2;

	f54->vdev = rmi_f54_video_device;
	f54->vdev.v4l2_dev = &f54->v4l2;
	f54->vdev.lock = &f54->lock;
	f54->vdev.vfl_dir = VFL_सूची_RX;
	f54->vdev.queue = &f54->queue;
	video_set_drvdata(&f54->vdev, f54);

	ret = video_रेजिस्टर_device(&f54->vdev, VFL_TYPE_TOUCH, -1);
	अगर (ret) अणु
		dev_err(&fn->dev, "Unable to register video subdevice.");
		जाओ हटाओ_v4l2;
	पूर्ण

	वापस 0;

हटाओ_v4l2:
	v4l2_device_unरेजिस्टर(&f54->v4l2);
हटाओ_wq:
	cancel_delayed_work_sync(&f54->work);
	flush_workqueue(f54->workqueue);
	destroy_workqueue(f54->workqueue);
	वापस ret;
पूर्ण

अटल व्योम rmi_f54_हटाओ(काष्ठा rmi_function *fn)
अणु
	काष्ठा f54_data *f54 = dev_get_drvdata(&fn->dev);

	video_unरेजिस्टर_device(&f54->vdev);
	v4l2_device_unरेजिस्टर(&f54->v4l2);
	destroy_workqueue(f54->workqueue);
पूर्ण

काष्ठा rmi_function_handler rmi_f54_handler = अणु
	.driver = अणु
		.name = F54_NAME,
	पूर्ण,
	.func = 0x54,
	.probe = rmi_f54_probe,
	.config = rmi_f54_config,
	.हटाओ = rmi_f54_हटाओ,
पूर्ण;
