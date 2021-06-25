<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STK1160 driver
 *
 * Copyright (C) 2012 Ezequiel Garcia
 * <elezegarcia--a.t--gmail.com>
 *
 * Based on Easycap driver by R.M. Thomas
 *	Copyright (C) 2010 R.M. Thomas
 *	<rmthomas--a.t--sciolus.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

#समावेश <media/i2c/saa7115.h>

#समावेश "stk1160.h"
#समावेश "stk1160-reg.h"

अटल bool keep_buffers;
module_param(keep_buffers, bool, 0644);
MODULE_PARM_DESC(keep_buffers, "don't release buffers upon stop streaming");

क्रमागत stk1160_decimate_mode अणु
	STK1160_DECIMATE_MORE_THAN_HALF,
	STK1160_DECIMATE_LESS_THAN_HALF,
पूर्ण;

काष्ठा stk1160_decimate_ctrl अणु
	bool col_en, row_en;
	क्रमागत stk1160_decimate_mode col_mode, row_mode;
	अचिन्हित पूर्णांक col_n, row_n;
पूर्ण;

/* supported video standards */
अटल काष्ठा stk1160_fmt क्रमmat[] = अणु
	अणु
		.fourcc   = V4L2_PIX_FMT_UYVY,
		.depth    = 16,
	पूर्ण
पूर्ण;

/*
 * Helper to find the next भागisor that results in modulo being zero.
 * This is required to guarantee valid decimation unit counts.
 */
अटल अचिन्हित पूर्णांक
भाग_round_पूर्णांकeger(अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	क्रम (;; y++) अणु
		अगर (x % y == 0)
			वापस x / y;
	पूर्ण
पूर्ण

अटल व्योम stk1160_set_std(काष्ठा stk1160 *dev)
अणु
	पूर्णांक i;

	अटल काष्ठा regval std525[] = अणु

		/* 720x480 */

		/* Frame start */
		अणुSTK116_CFSPO_STX_L, 0x0000पूर्ण,
		अणुSTK116_CFSPO_STX_H, 0x0000पूर्ण,
		अणुSTK116_CFSPO_STY_L, 0x0003पूर्ण,
		अणुSTK116_CFSPO_STY_H, 0x0000पूर्ण,

		/* Frame end */
		अणुSTK116_CFEPO_ENX_L, 0x05a0पूर्ण,
		अणुSTK116_CFEPO_ENX_H, 0x0005पूर्ण,
		अणुSTK116_CFEPO_ENY_L, 0x00f3पूर्ण,
		अणुSTK116_CFEPO_ENY_H, 0x0000पूर्ण,

		अणु0xffff, 0xffffपूर्ण
	पूर्ण;

	अटल काष्ठा regval std625[] = अणु

		/* 720x576 */

		/* TODO: Each line of frame has some junk at the end */
		/* Frame start */
		अणुSTK116_CFSPO,   0x0000पूर्ण,
		अणुSTK116_CFSPO+1, 0x0000पूर्ण,
		अणुSTK116_CFSPO+2, 0x0001पूर्ण,
		अणुSTK116_CFSPO+3, 0x0000पूर्ण,

		/* Frame end */
		अणुSTK116_CFEPO,   0x05a0पूर्ण,
		अणुSTK116_CFEPO+1, 0x0005पूर्ण,
		अणुSTK116_CFEPO+2, 0x0121पूर्ण,
		अणुSTK116_CFEPO+3, 0x0001पूर्ण,

		अणु0xffff, 0xffffपूर्ण
	पूर्ण;

	अगर (dev->norm & V4L2_STD_525_60) अणु
		stk1160_dbg("registers to NTSC like standard\n");
		क्रम (i = 0; std525[i].reg != 0xffff; i++)
			stk1160_ग_लिखो_reg(dev, std525[i].reg, std525[i].val);
	पूर्ण अन्यथा अणु
		stk1160_dbg("registers to PAL like standard\n");
		क्रम (i = 0; std625[i].reg != 0xffff; i++)
			stk1160_ग_लिखो_reg(dev, std625[i].reg, std625[i].val);
	पूर्ण

पूर्ण

अटल व्योम stk1160_set_fmt(काष्ठा stk1160 *dev,
			    काष्ठा stk1160_decimate_ctrl *ctrl)
अणु
	u32 val = 0;

	अगर (ctrl) अणु
		/*
		 * Since the क्रमmat is UYVY, the device must skip or send
		 * a number of rows/columns multiple of four. This way, the
		 * colour क्रमmat is preserved. The STK1160_DEC_UNIT_SIZE bit
		 * करोes exactly this.
		 */
		val |= STK1160_DEC_UNIT_SIZE;
		val |= ctrl->col_en ? STK1160_H_DEC_EN : 0;
		val |= ctrl->row_en ? STK1160_V_DEC_EN : 0;
		val |= ctrl->col_mode ==
			STK1160_DECIMATE_MORE_THAN_HALF ?
			STK1160_H_DEC_MODE : 0;
		val |= ctrl->row_mode ==
			STK1160_DECIMATE_MORE_THAN_HALF ?
			STK1160_V_DEC_MODE : 0;

		/* Horizontal count units */
		stk1160_ग_लिखो_reg(dev, STK1160_DMCTRL_H_UNITS, ctrl->col_n);
		/* Vertical count units */
		stk1160_ग_लिखो_reg(dev, STK1160_DMCTRL_V_UNITS, ctrl->row_n);

		stk1160_dbg("decimate 0x%x, column units %d, row units %d\n",
			    val, ctrl->col_n, ctrl->row_n);
	पूर्ण

	/* Decimation control */
	stk1160_ग_लिखो_reg(dev, STK1160_DMCTRL, val);
पूर्ण

/*
 * Set a new alternate setting.
 * Returns true is dev->max_pkt_size has changed, false otherwise.
 */
अटल bool stk1160_set_alternate(काष्ठा stk1160 *dev)
अणु
	पूर्णांक i, prev_alt = dev->alt;
	अचिन्हित पूर्णांक min_pkt_size;
	bool new_pkt_size;

	/*
	 * If we करोn't set right alternate,
	 * then we will get a green screen with junk.
	 */
	min_pkt_size = STK1160_MIN_PKT_SIZE;

	क्रम (i = 0; i < dev->num_alt; i++) अणु
		/* stop when the selected alt setting offers enough bandwidth */
		अगर (dev->alt_max_pkt_size[i] >= min_pkt_size) अणु
			dev->alt = i;
			अवरोध;
		/*
		 * otherwise make sure that we end up with the maximum bandwidth
		 * because the min_pkt_size equation might be wrong...
		 */
		पूर्ण अन्यथा अगर (dev->alt_max_pkt_size[i] >
			   dev->alt_max_pkt_size[dev->alt])
			dev->alt = i;
	पूर्ण

	stk1160_dbg("setting alternate %d\n", dev->alt);

	अगर (dev->alt != prev_alt) अणु
		stk1160_dbg("minimum isoc packet size: %u (alt=%d)\n",
				min_pkt_size, dev->alt);
		stk1160_dbg("setting alt %d with wMaxPacketSize=%u\n",
			       dev->alt, dev->alt_max_pkt_size[dev->alt]);
		usb_set_पूर्णांकerface(dev->udev, 0, dev->alt);
	पूर्ण

	new_pkt_size = dev->max_pkt_size != dev->alt_max_pkt_size[dev->alt];
	dev->max_pkt_size = dev->alt_max_pkt_size[dev->alt];

	वापस new_pkt_size;
पूर्ण

अटल पूर्णांक stk1160_start_streaming(काष्ठा stk1160 *dev)
अणु
	bool new_pkt_size;
	पूर्णांक rc = 0;
	पूर्णांक i;

	/* Check device presence */
	अगर (!dev->udev)
		वापस -ENODEV;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->v4l_lock))
		वापस -ERESTARTSYS;
	/*
	 * For some reason it is mandatory to set alternate *first*
	 * and only *then* initialize isoc urbs.
	 * Someone please explain me why ;)
	 */
	new_pkt_size = stk1160_set_alternate(dev);

	/*
	 * We (re)allocate isoc urbs अगर:
	 * there is no allocated isoc urbs, OR
	 * a new dev->max_pkt_size is detected
	 */
	अगर (!dev->isoc_ctl.num_bufs || new_pkt_size) अणु
		rc = stk1160_alloc_isoc(dev);
		अगर (rc < 0)
			जाओ out_stop_hw;
	पूर्ण

	/* submit urbs and enables IRQ */
	क्रम (i = 0; i < dev->isoc_ctl.num_bufs; i++) अणु
		rc = usb_submit_urb(dev->isoc_ctl.urb[i], GFP_KERNEL);
		अगर (rc) अणु
			stk1160_err("cannot submit urb[%d] (%d)\n", i, rc);
			जाओ out_uninit;
		पूर्ण
	पूर्ण

	/* Start saa711x */
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 1);

	dev->sequence = 0;

	/* Start stk1160 */
	stk1160_ग_लिखो_reg(dev, STK1160_DCTRL, 0xb3);
	stk1160_ग_लिखो_reg(dev, STK1160_DCTRL+3, 0x00);

	stk1160_dbg("streaming started\n");

	mutex_unlock(&dev->v4l_lock);

	वापस 0;

out_uninit:
	stk1160_uninit_isoc(dev);
out_stop_hw:
	usb_set_पूर्णांकerface(dev->udev, 0, 0);
	stk1160_clear_queue(dev);

	mutex_unlock(&dev->v4l_lock);

	वापस rc;
पूर्ण

/* Must be called with v4l_lock hold */
अटल व्योम stk1160_stop_hw(काष्ठा stk1160 *dev)
अणु
	/* If the device is not physically present, there is nothing to करो */
	अगर (!dev->udev)
		वापस;

	/* set alternate 0 */
	dev->alt = 0;
	stk1160_dbg("setting alternate %d\n", dev->alt);
	usb_set_पूर्णांकerface(dev->udev, 0, 0);

	/* Stop stk1160 */
	stk1160_ग_लिखो_reg(dev, STK1160_DCTRL, 0x00);
	stk1160_ग_लिखो_reg(dev, STK1160_DCTRL+3, 0x00);

	/* Stop saa711x */
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 0);
पूर्ण

अटल पूर्णांक stk1160_stop_streaming(काष्ठा stk1160 *dev)
अणु
	अगर (mutex_lock_पूर्णांकerruptible(&dev->v4l_lock))
		वापस -ERESTARTSYS;

	/*
	 * Once URBs are cancelled, the URB complete handler
	 * won't be running. This is required to safely release the
	 * current buffer (dev->isoc_ctl.buf).
	 */
	stk1160_cancel_isoc(dev);

	/*
	 * It is possible to keep buffers around using a module parameter.
	 * This is पूर्णांकended to aव्योम memory fragmentation.
	 */
	अगर (!keep_buffers)
		stk1160_मुक्त_isoc(dev);

	stk1160_stop_hw(dev);

	stk1160_clear_queue(dev);

	stk1160_dbg("streaming stopped\n");

	mutex_unlock(&dev->v4l_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations stk1160_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.पढ़ो = vb2_fop_पढ़ो,
	.poll = vb2_fop_poll,
	.mmap = vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

/*
 * vidioc ioctls
 */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file,
		व्योम *priv, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);

	strscpy(cap->driver, "stk1160", माप(cap->driver));
	strscpy(cap->card, "stk1160", माप(cap->card));
	usb_make_path(dev->udev, cap->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
		काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index != 0)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmat[f->index].fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);

	f->fmt.pix.width = dev->width;
	f->fmt.pix.height = dev->height;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	f->fmt.pix.pixelक्रमmat = dev->fmt->fourcc;
	f->fmt.pix.bytesperline = dev->width * 2;
	f->fmt.pix.sizeimage = dev->height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक stk1160_try_fmt(काष्ठा stk1160 *dev, काष्ठा v4l2_क्रमmat *f,
			    काष्ठा stk1160_decimate_ctrl *ctrl)
अणु
	अचिन्हित पूर्णांक width, height;
	अचिन्हित पूर्णांक base_width, base_height;
	अचिन्हित पूर्णांक col_n, row_n;
	क्रमागत stk1160_decimate_mode col_mode, row_mode;
	bool col_en, row_en;

	base_width = 720;
	base_height = (dev->norm & V4L2_STD_525_60) ? 480 : 576;

	/* Minimum width and height is 5% the frame size */
	width = clamp_t(अचिन्हित पूर्णांक, f->fmt.pix.width,
			base_width / 20, base_width);
	height = clamp_t(अचिन्हित पूर्णांक, f->fmt.pix.height,
			base_height / 20, base_height);

	/* Let's set शेष no decimation values */
	col_n = 0;
	row_n = 0;
	col_en = false;
	row_en = false;
	f->fmt.pix.width = base_width;
	f->fmt.pix.height = base_height;
	row_mode = STK1160_DECIMATE_LESS_THAN_HALF;
	col_mode = STK1160_DECIMATE_LESS_THAN_HALF;

	अगर (width < base_width && width > base_width / 2) अणु
		/*
		 * The device will send count units क्रम each
		 * unit skipped. This means count unit is:
		 *
		 * n = width / (frame width - width)
		 *
		 * And the width is:
		 *
		 * width = (n / n + 1) * frame width
		 */
		col_n = भाग_round_पूर्णांकeger(width, base_width - width);
		अगर (col_n > 0 && col_n <= 255) अणु
			col_en = true;
			col_mode = STK1160_DECIMATE_LESS_THAN_HALF;
			f->fmt.pix.width = (base_width * col_n) / (col_n + 1);
		पूर्ण

	पूर्ण अन्यथा अगर (width <= base_width / 2) अणु

		/*
		 * The device will skip count units क्रम each
		 * unit sent. This means count is:
		 *
		 * n = (frame width / width) - 1
		 *
		 * And the width is:
		 *
		 * width = frame width / (n + 1)
		 */
		col_n = भाग_round_पूर्णांकeger(base_width, width) - 1;
		अगर (col_n > 0 && col_n <= 255) अणु
			col_en = true;
			col_mode = STK1160_DECIMATE_MORE_THAN_HALF;
			f->fmt.pix.width = base_width / (col_n + 1);
		पूर्ण
	पूर्ण

	अगर (height < base_height && height > base_height / 2) अणु
		row_n = भाग_round_पूर्णांकeger(height, base_height - height);
		अगर (row_n > 0 && row_n <= 255) अणु
			row_en = true;
			row_mode = STK1160_DECIMATE_LESS_THAN_HALF;
			f->fmt.pix.height = (base_height * row_n) / (row_n + 1);
		पूर्ण

	पूर्ण अन्यथा अगर (height <= base_height / 2) अणु
		row_n = भाग_round_पूर्णांकeger(base_height, height) - 1;
		अगर (row_n > 0 && row_n <= 255) अणु
			row_en = true;
			row_mode = STK1160_DECIMATE_MORE_THAN_HALF;
			f->fmt.pix.height = base_height / (row_n + 1);
		पूर्ण
	पूर्ण

	f->fmt.pix.pixelक्रमmat = dev->fmt->fourcc;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	अगर (ctrl) अणु
		ctrl->col_en = col_en;
		ctrl->col_n = col_n;
		ctrl->col_mode = col_mode;
		ctrl->row_en = row_en;
		ctrl->row_n = row_n;
		ctrl->row_mode = row_mode;
	पूर्ण

	stk1160_dbg("width %d, height %d\n",
		    f->fmt.pix.width, f->fmt.pix.height);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);

	वापस stk1160_try_fmt(dev, f, शून्य);
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);
	काष्ठा vb2_queue *q = &dev->vb_vidq;
	काष्ठा stk1160_decimate_ctrl ctrl;
	पूर्णांक rc;

	अगर (vb2_is_busy(q))
		वापस -EBUSY;

	rc = stk1160_try_fmt(dev, f, &ctrl);
	अगर (rc < 0)
		वापस rc;
	dev->width = f->fmt.pix.width;
	dev->height = f->fmt.pix.height;
	stk1160_set_fmt(dev, &ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *norm)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, querystd, norm);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *norm)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);

	*norm = dev->norm;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id norm)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);
	काष्ठा vb2_queue *q = &dev->vb_vidq;

	अगर (dev->norm == norm)
		वापस 0;

	अगर (vb2_is_busy(q))
		वापस -EBUSY;

	/* Check device presence */
	अगर (!dev->udev)
		वापस -ENODEV;

	/* We need to set this now, beक्रमe we call stk1160_set_std */
	dev->width = 720;
	dev->height = (norm & V4L2_STD_525_60) ? 480 : 576;
	dev->norm = norm;

	stk1160_set_std(dev);

	/* Calling with शून्य disables frame decimation */
	stk1160_set_fmt(dev, शून्य);

	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_std,
			dev->norm);

	वापस 0;
पूर्ण


अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_input *i)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);

	अगर (i->index > STK1160_MAX_INPUT)
		वापस -EINVAL;

	/* S-Video special handling */
	अगर (i->index == STK1160_SVIDEO_INPUT)
		प्र_लिखो(i->name, "S-Video");
	अन्यथा
		प्र_लिखो(i->name, "Composite%d", i->index);

	i->type = V4L2_INPUT_TYPE_CAMERA;
	i->std = dev->vdev.tvnorms;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);
	*i = dev->ctl_input;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);

	अगर (i > STK1160_MAX_INPUT)
		वापस -EINVAL;

	dev->ctl_input = i;

	stk1160_select_input(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक vidioc_g_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);
	पूर्णांक rc;
	u8 val;

	/* Match host */
	rc = stk1160_पढ़ो_reg(dev, reg->reg, &val);
	reg->val = val;
	reg->size = 1;

	वापस rc;
पूर्ण

अटल पूर्णांक vidioc_s_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा stk1160 *dev = video_drvdata(file);

	/* Match host */
	वापस stk1160_ग_लिखो_reg(dev, reg->reg, reg->val);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_ioctl_ops stk1160_ioctl_ops = अणु
	.vidioc_querycap      = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap  = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap   = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_querystd      = vidioc_querystd,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_क्रमागत_input    = vidioc_क्रमागत_input,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,

	/* vb2 takes care of these */
	.vidioc_reqbufs       = vb2_ioctl_reqbufs,
	.vidioc_querybuf      = vb2_ioctl_querybuf,
	.vidioc_qbuf          = vb2_ioctl_qbuf,
	.vidioc_dqbuf         = vb2_ioctl_dqbuf,
	.vidioc_streamon      = vb2_ioctl_streamon,
	.vidioc_streamoff     = vb2_ioctl_streamoff,
	.vidioc_expbuf        = vb2_ioctl_expbuf,

	.vidioc_log_status  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर = vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर = vidioc_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

/********************************************************************/

/*
 * Videobuf2 operations
 */
अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
				अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा stk1160 *dev = vb2_get_drv_priv(vq);
	अचिन्हित दीर्घ size;

	size = dev->width * dev->height * 2;

	/*
	 * Here we can change the number of buffers being requested.
	 * So, we set a minimum and a maximum like this:
	 */
	*nbuffers = clamp_t(अचिन्हित पूर्णांक, *nbuffers,
			STK1160_MIN_VIDEO_BUFFERS, STK1160_MAX_VIDEO_BUFFERS);

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	/* This means a packed colorक्रमmat */
	*nplanes = 1;

	sizes[0] = size;

	stk1160_dbg("%s: buffer count %d, each %ld bytes\n",
		    __func__, *nbuffers, size);

	वापस 0;
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा stk1160 *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा stk1160_buffer *buf =
		container_of(vbuf, काष्ठा stk1160_buffer, vb);

	spin_lock_irqsave(&dev->buf_lock, flags);
	अगर (!dev->udev) अणु
		/*
		 * If the device is disconnected वापस the buffer to userspace
		 * directly. The next QBUF call will fail with -ENODEV.
		 */
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण अन्यथा अणु

		buf->mem = vb2_plane_vaddr(vb, 0);
		buf->length = vb2_plane_size(vb, 0);
		buf->bytesused = 0;
		buf->pos = 0;

		/*
		 * If buffer length is less from expected then we वापस
		 * the buffer to userspace directly.
		 */
		अगर (buf->length < dev->width * dev->height * 2)
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		अन्यथा
			list_add_tail(&buf->list, &dev->avail_bufs);

	पूर्ण
	spin_unlock_irqrestore(&dev->buf_lock, flags);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा stk1160 *dev = vb2_get_drv_priv(vq);
	वापस stk1160_start_streaming(dev);
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा stk1160 *dev = vb2_get_drv_priv(vq);
	stk1160_stop_streaming(dev);
पूर्ण

अटल स्थिर काष्ठा vb2_ops stk1160_video_qops = अणु
	.queue_setup		= queue_setup,
	.buf_queue		= buffer_queue,
	.start_streaming	= start_streaming,
	.stop_streaming		= stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल स्थिर काष्ठा video_device v4l_ढाँचा = अणु
	.name = "stk1160",
	.tvnorms = V4L2_STD_525_60 | V4L2_STD_625_50,
	.fops = &stk1160_fops,
	.ioctl_ops = &stk1160_ioctl_ops,
	.release = video_device_release_empty,
पूर्ण;

/********************************************************************/

/* Must be called with both v4l_lock and vb_queue_lock hold */
व्योम stk1160_clear_queue(काष्ठा stk1160 *dev)
अणु
	काष्ठा stk1160_buffer *buf;
	अचिन्हित दीर्घ flags;

	/* Release all active buffers */
	spin_lock_irqsave(&dev->buf_lock, flags);
	जबतक (!list_empty(&dev->avail_bufs)) अणु
		buf = list_first_entry(&dev->avail_bufs,
			काष्ठा stk1160_buffer, list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		stk1160_dbg("buffer [%p/%d] aborted\n",
			    buf, buf->vb.vb2_buf.index);
	पूर्ण

	/* It's important to release the current buffer */
	अगर (dev->isoc_ctl.buf) अणु
		buf = dev->isoc_ctl.buf;
		dev->isoc_ctl.buf = शून्य;

		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		stk1160_dbg("buffer [%p/%d] aborted\n",
			    buf, buf->vb.vb2_buf.index);
	पूर्ण
	spin_unlock_irqrestore(&dev->buf_lock, flags);
पूर्ण

पूर्णांक stk1160_vb2_setup(काष्ठा stk1160 *dev)
अणु
	पूर्णांक rc;
	काष्ठा vb2_queue *q;

	q = &dev->vb_vidq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_READ | VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा stk1160_buffer);
	q->ops = &stk1160_video_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;
	q->lock = &dev->vb_queue_lock;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;

	rc = vb2_queue_init(q);
	अगर (rc < 0)
		वापस rc;

	/* initialize video dma queue */
	INIT_LIST_HEAD(&dev->avail_bufs);

	वापस 0;
पूर्ण

पूर्णांक stk1160_video_रेजिस्टर(काष्ठा stk1160 *dev)
अणु
	पूर्णांक rc;

	/* Initialize video_device with a ढाँचा काष्ठाure */
	dev->vdev = v4l_ढाँचा;
	dev->vdev.queue = &dev->vb_vidq;

	/*
	 * Provide mutexes क्रम v4l2 core and क्रम videobuf2 queue.
	 * It will be used to protect *only* v4l2 ioctls.
	 */
	dev->vdev.lock = &dev->v4l_lock;

	/* This will be used to set video_device parent */
	dev->vdev.v4l2_dev = &dev->v4l2_dev;
	dev->vdev.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
				V4L2_CAP_READWRITE;

	/* NTSC is शेष */
	dev->norm = V4L2_STD_NTSC_M;
	dev->width = 720;
	dev->height = 480;

	/* set शेष क्रमmat */
	dev->fmt = &क्रमmat[0];
	stk1160_set_std(dev);

	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_std,
			dev->norm);

	video_set_drvdata(&dev->vdev, dev);
	rc = video_रेजिस्टर_device(&dev->vdev, VFL_TYPE_VIDEO, -1);
	अगर (rc < 0) अणु
		stk1160_err("video_register_device failed (%d)\n", rc);
		वापस rc;
	पूर्ण

	v4l2_info(&dev->v4l2_dev, "V4L2 device registered as %s\n",
		  video_device_node_name(&dev->vdev));

	वापस 0;
पूर्ण
