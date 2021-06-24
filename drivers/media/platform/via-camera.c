<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the VIA Chrome पूर्णांकegrated camera controller.
 *
 * Copyright 2009,2010 Jonathan Corbet <corbet@lwn.net>
 *
 * This work was supported by the One Laptop Per Child project
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/i2c/ov7670.h>
#समावेश <media/videobuf2-dma-sg.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/via-core.h>
#समावेश <linux/via-gpपन.स>
#समावेश <linux/via_i2c.h>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/olpc.h>
#अन्यथा
#घोषणा machine_is_olpc(x) 0
#पूर्ण_अगर

#समावेश "via-camera.h"

MODULE_ALIAS("platform:viafb-camera");
MODULE_AUTHOR("Jonathan Corbet <corbet@lwn.net>");
MODULE_DESCRIPTION("VIA framebuffer-based camera controller driver");
MODULE_LICENSE("GPL");

अटल bool flip_image;
module_param(flip_image, bool, 0444);
MODULE_PARM_DESC(flip_image,
		"If set, the sensor will be instructed to flip the image vertically.");

अटल bool override_serial;
module_param(override_serial, bool, 0444);
MODULE_PARM_DESC(override_serial,
		"The camera driver will normally refuse to load if the XO 1.5 serial port is enabled.  Set this option to force-enable the camera.");

/*
 * The काष्ठाure describing our camera.
 */
क्रमागत viacam_opstate अणु S_IDLE = 0, S_RUNNING = 1 पूर्ण;

काष्ठा via_camera अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा video_device vdev;
	काष्ठा v4l2_subdev *sensor;
	काष्ठा platक्रमm_device *platdev;
	काष्ठा viafb_dev *viadev;
	काष्ठा mutex lock;
	क्रमागत viacam_opstate opstate;
	अचिन्हित दीर्घ flags;
	काष्ठा pm_qos_request qos_request;
	/*
	 * GPIO info क्रम घातer/reset management
	 */
	पूर्णांक घातer_gpio;
	पूर्णांक reset_gpio;
	/*
	 * I/O memory stuff.
	 */
	व्योम __iomem *mmio;	/* Where the रेजिस्टरs live */
	व्योम __iomem *fbmem;	/* Frame buffer memory */
	u32 fb_offset;		/* Reserved memory offset (FB) */
	/*
	 * Capture buffers and related.	 The controller supports
	 * up to three, so that's what we have here.  These buffers
	 * live in frame buffer memory, so we करोn't call them "DMA".
	 */
	अचिन्हित पूर्णांक cb_offsets[3];	/* offsets पूर्णांकo fb mem */
	u8 __iomem *cb_addrs[3];	/* Kernel-space addresses */
	पूर्णांक n_cap_bufs;			/* How many are we using? */
	काष्ठा vb2_queue vq;
	काष्ठा list_head buffer_queue;
	u32 sequence;
	/*
	 * Video क्रमmat inक्रमmation.  sensor_क्रमmat is kept in a क्रमm
	 * that we can use to pass to the sensor.  We always run the
	 * sensor in VGA resolution, though, and let the controller
	 * करोwnscale things अगर need be.	 So we keep the "real*
	 * dimensions separately.
	 */
	काष्ठा v4l2_pix_क्रमmat sensor_क्रमmat;
	काष्ठा v4l2_pix_क्रमmat user_क्रमmat;
	u32 mbus_code;
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा via_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer		vbuf;
	काष्ठा list_head		queue;
पूर्ण;

/*
 * Yes, this is a hack, but there's only going to be one of these
 * on any प्रणाली we know of.
 */
अटल काष्ठा via_camera *via_cam_info;

/*
 * Flag values, manipulated with bitops
 */
#घोषणा CF_DMA_ACTIVE	 0	/* A frame is incoming */
#घोषणा CF_CONFIG_NEEDED 1	/* Must configure hardware */


/*
 * Nasty ugly v4l2 boilerplate.
 */
#घोषणा sensor_call(cam, optype, func, args...) \
	v4l2_subdev_call(cam->sensor, optype, func, ##args)

/*
 * Debugging and related.
 */
#घोषणा cam_err(cam, fmt, arg...) \
	dev_err(&(cam)->platdev->dev, fmt, ##arg);
#घोषणा cam_warn(cam, fmt, arg...) \
	dev_warn(&(cam)->platdev->dev, fmt, ##arg);
#घोषणा cam_dbg(cam, fmt, arg...) \
	dev_dbg(&(cam)->platdev->dev, fmt, ##arg);

/*
 * Format handling.  This is ripped almost directly from Hans's changes
 * to cafe_ccic.c.  It's a little unक्रमtunate; until this change, we
 * didn't need to know anything about the क्रमmat except its byte depth;
 * now this inक्रमmation must be managed at this level too.
 */
अटल काष्ठा via_क्रमmat अणु
	__u32 pixelक्रमmat;
	पूर्णांक bpp;   /* Bytes per pixel */
	u32 mbus_code;
पूर्ण via_क्रमmats[] = अणु
	अणु
		.pixelक्रमmat	= V4L2_PIX_FMT_YUYV,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.bpp		= 2,
	पूर्ण,
	/* RGB444 and Bayer should be करोable, but have never been
	   tested with this driver. RGB565 seems to work at the शेष
	   resolution, but results in color corruption when being scaled by
	   viacam_set_scaled(), and is disabled as a result. */
पूर्ण;
#घोषणा N_VIA_FMTS ARRAY_SIZE(via_क्रमmats)

अटल काष्ठा via_क्रमmat *via_find_क्रमmat(u32 pixelक्रमmat)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < N_VIA_FMTS; i++)
		अगर (via_क्रमmats[i].pixelक्रमmat == pixelक्रमmat)
			वापस via_क्रमmats + i;
	/* Not found? Then वापस the first क्रमmat. */
	वापस via_क्रमmats;
पूर्ण


/*--------------------------------------------------------------------------*/
/*
 * Sensor घातer/reset management.  This piece is OLPC-specअगरic क्रम
 * sure; other configurations will have things connected dअगरferently.
 */
अटल पूर्णांक via_sensor_घातer_setup(काष्ठा via_camera *cam)
अणु
	पूर्णांक ret;

	cam->घातer_gpio = viafb_gpio_lookup("VGPIO3");
	cam->reset_gpio = viafb_gpio_lookup("VGPIO2");
	अगर (!gpio_is_valid(cam->घातer_gpio) || !gpio_is_valid(cam->reset_gpio)) अणु
		dev_err(&cam->platdev->dev, "Unable to find GPIO lines\n");
		वापस -EINVAL;
	पूर्ण
	ret = gpio_request(cam->घातer_gpio, "viafb-camera");
	अगर (ret) अणु
		dev_err(&cam->platdev->dev, "Unable to request power GPIO\n");
		वापस ret;
	पूर्ण
	ret = gpio_request(cam->reset_gpio, "viafb-camera");
	अगर (ret) अणु
		dev_err(&cam->platdev->dev, "Unable to request reset GPIO\n");
		gpio_मुक्त(cam->घातer_gpio);
		वापस ret;
	पूर्ण
	gpio_direction_output(cam->घातer_gpio, 0);
	gpio_direction_output(cam->reset_gpio, 0);
	वापस 0;
पूर्ण

/*
 * Power up the sensor and perक्रमm the reset dance.
 */
अटल व्योम via_sensor_घातer_up(काष्ठा via_camera *cam)
अणु
	gpio_set_value(cam->घातer_gpio, 1);
	gpio_set_value(cam->reset_gpio, 0);
	msleep(20);  /* Probably excessive */
	gpio_set_value(cam->reset_gpio, 1);
	msleep(20);
पूर्ण

अटल व्योम via_sensor_घातer_करोwn(काष्ठा via_camera *cam)
अणु
	gpio_set_value(cam->घातer_gpio, 0);
	gpio_set_value(cam->reset_gpio, 0);
पूर्ण


अटल व्योम via_sensor_घातer_release(काष्ठा via_camera *cam)
अणु
	via_sensor_घातer_करोwn(cam);
	gpio_मुक्त(cam->घातer_gpio);
	gpio_मुक्त(cam->reset_gpio);
पूर्ण

/* --------------------------------------------------------------------------*/
/* Sensor ops */

/*
 * Manage the ov7670 "flip" bit, which needs special help.
 */
अटल पूर्णांक viacam_set_flip(काष्ठा via_camera *cam)
अणु
	काष्ठा v4l2_control ctrl;

	स_रखो(&ctrl, 0, माप(ctrl));
	ctrl.id = V4L2_CID_VFLIP;
	ctrl.value = flip_image;
	वापस v4l2_s_ctrl(शून्य, cam->sensor->ctrl_handler, &ctrl);
पूर्ण

/*
 * Configure the sensor.  It's up to the caller to ensure
 * that the camera is in the correct operating state.
 */
अटल पूर्णांक viacam_configure_sensor(काष्ठा via_camera *cam)
अणु
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	पूर्णांक ret;

	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, &cam->sensor_क्रमmat, cam->mbus_code);
	ret = sensor_call(cam, core, init, 0);
	अगर (ret == 0)
		ret = sensor_call(cam, pad, set_fmt, शून्य, &क्रमmat);
	/*
	 * OV7670 करोes weird things अगर flip is set *beक्रमe* क्रमmat...
	 */
	अगर (ret == 0)
		ret = viacam_set_flip(cam);
	वापस ret;
पूर्ण



/* --------------------------------------------------------------------------*/
/*
 * Some simple रेजिस्टर accessors; they assume that the lock is held.
 *
 * Should we want to support the second capture engine, we could
 * hide the रेजिस्टर dअगरference by adding 0x1000 to रेजिस्टरs in the
 * 0x300-350 range.
 */
अटल अंतरभूत व्योम viacam_ग_लिखो_reg(काष्ठा via_camera *cam,
		पूर्णांक reg, पूर्णांक value)
अणु
	ioग_लिखो32(value, cam->mmio + reg);
पूर्ण

अटल अंतरभूत पूर्णांक viacam_पढ़ो_reg(काष्ठा via_camera *cam, पूर्णांक reg)
अणु
	वापस ioपढ़ो32(cam->mmio + reg);
पूर्ण

अटल अंतरभूत व्योम viacam_ग_लिखो_reg_mask(काष्ठा via_camera *cam,
		पूर्णांक reg, पूर्णांक value, पूर्णांक mask)
अणु
	पूर्णांक पंचांगp = viacam_पढ़ो_reg(cam, reg);

	पंचांगp = (पंचांगp & ~mask) | (value & mask);
	viacam_ग_लिखो_reg(cam, reg, पंचांगp);
पूर्ण


/* --------------------------------------------------------------------------*/
/* Interrupt management and handling */

अटल irqवापस_t viacam_quick_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा via_camera *cam = data;
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक icv;

	/*
	 * All we करो here is to clear the पूर्णांकerrupts and tell
	 * the handler thपढ़ो to wake up.
	 */
	spin_lock(&cam->viadev->reg_lock);
	icv = viacam_पढ़ो_reg(cam, VCR_INTCTRL);
	अगर (icv & VCR_IC_EAV) अणु
		icv |= VCR_IC_EAV|VCR_IC_EVBI|VCR_IC_FFULL;
		viacam_ग_लिखो_reg(cam, VCR_INTCTRL, icv);
		ret = IRQ_WAKE_THREAD;
	पूर्ण
	spin_unlock(&cam->viadev->reg_lock);
	वापस ret;
पूर्ण

/*
 * Find the next buffer which has somebody रुकोing on it.
 */
अटल काष्ठा via_buffer *viacam_next_buffer(काष्ठा via_camera *cam)
अणु
	अगर (cam->opstate != S_RUNNING)
		वापस शून्य;
	अगर (list_empty(&cam->buffer_queue))
		वापस शून्य;
	वापस list_entry(cam->buffer_queue.next, काष्ठा via_buffer, queue);
पूर्ण

/*
 * The thपढ़ोed IRQ handler.
 */
अटल irqवापस_t viacam_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा via_camera *cam = data;
	काष्ठा via_buffer *vb;
	पूर्णांक bufn;
	काष्ठा sg_table *sgt;

	mutex_lock(&cam->lock);
	/*
	 * If there is no place to put the data frame, करोn't bother
	 * with anything अन्यथा.
	 */
	vb = viacam_next_buffer(cam);
	अगर (vb == शून्य)
		जाओ करोne;
	/*
	 * Figure out which buffer we just completed.
	 */
	bufn = (viacam_पढ़ो_reg(cam, VCR_INTCTRL) & VCR_IC_ACTBUF) >> 3;
	bufn -= 1;
	अगर (bufn < 0)
		bufn = cam->n_cap_bufs - 1;
	/*
	 * Copy over the data and let any रुकोers know.
	 */
	sgt = vb2_dma_sg_plane_desc(&vb->vbuf.vb2_buf, 0);
	vb->vbuf.vb2_buf.बारtamp = kसमय_get_ns();
	viafb_dma_copy_out_sg(cam->cb_offsets[bufn], sgt->sgl, sgt->nents);
	vb->vbuf.sequence = cam->sequence++;
	vb->vbuf.field = V4L2_FIELD_NONE;
	list_del(&vb->queue);
	vb2_buffer_करोne(&vb->vbuf.vb2_buf, VB2_BUF_STATE_DONE);
करोne:
	mutex_unlock(&cam->lock);
	वापस IRQ_HANDLED;
पूर्ण


/*
 * These functions must mess around with the general पूर्णांकerrupt
 * control रेजिस्टर, which is relevant to much more than just the
 * camera.  Nothing अन्यथा uses पूर्णांकerrupts, though, as of this writing.
 * Should that situation change, we'll have to improve support at
 * the via-core level.
 */
अटल व्योम viacam_पूर्णांक_enable(काष्ठा via_camera *cam)
अणु
	viacam_ग_लिखो_reg(cam, VCR_INTCTRL,
			VCR_IC_INTEN|VCR_IC_EAV|VCR_IC_EVBI|VCR_IC_FFULL);
	viafb_irq_enable(VDE_I_C0AVEN);
पूर्ण

अटल व्योम viacam_पूर्णांक_disable(काष्ठा via_camera *cam)
अणु
	viafb_irq_disable(VDE_I_C0AVEN);
	viacam_ग_लिखो_reg(cam, VCR_INTCTRL, 0);
पूर्ण



/* --------------------------------------------------------------------------*/
/* Controller operations */

/*
 * Set up our capture buffers in framebuffer memory.
 */
अटल पूर्णांक viacam_ctlr_cbufs(काष्ठा via_camera *cam)
अणु
	पूर्णांक nbuf = cam->viadev->camera_fbmem_size/cam->sensor_क्रमmat.sizeimage;
	पूर्णांक i;
	अचिन्हित पूर्णांक offset;

	/*
	 * See how many buffers we can work with.
	 */
	अगर (nbuf >= 3) अणु
		cam->n_cap_bufs = 3;
		viacam_ग_लिखो_reg_mask(cam, VCR_CAPINTC, VCR_CI_3BUFS,
				VCR_CI_3BUFS);
	पूर्ण अन्यथा अगर (nbuf == 2) अणु
		cam->n_cap_bufs = 2;
		viacam_ग_लिखो_reg_mask(cam, VCR_CAPINTC, 0, VCR_CI_3BUFS);
	पूर्ण अन्यथा अणु
		cam_warn(cam, "Insufficient frame buffer memory\n");
		वापस -ENOMEM;
	पूर्ण
	/*
	 * Set them up.
	 */
	offset = cam->fb_offset;
	क्रम (i = 0; i < cam->n_cap_bufs; i++) अणु
		cam->cb_offsets[i] = offset;
		cam->cb_addrs[i] = cam->fbmem + offset;
		viacam_ग_लिखो_reg(cam, VCR_VBUF1 + i*4, offset & VCR_VBUF_MASK);
		offset += cam->sensor_क्रमmat.sizeimage;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Set the scaling रेजिस्टर क्रम करोwnscaling the image.
 *
 * This रेजिस्टर works like this...  Vertical scaling is enabled
 * by bit 26; अगर that bit is set, करोwnscaling is controlled by the
 * value in bits 16:25.	 Those bits are भागided by 1024 to get
 * the scaling factor; setting just bit 25 thus cuts the height
 * in half.
 *
 * Horizontal scaling works about the same, but it's enabled by
 * bit 11, with bits 0:10 giving the numerator of a fraction
 * (over 2048) क्रम the scaling value.
 *
 * This function is naive in that, अगर the user departs from
 * the 3x4 VGA scaling factor, the image will distort.	We
 * could work around that अगर it really seemed important.
 */
अटल व्योम viacam_set_scale(काष्ठा via_camera *cam)
अणु
	अचिन्हित पूर्णांक avscale;
	पूर्णांक sf;

	अगर (cam->user_क्रमmat.width == VGA_WIDTH)
		avscale = 0;
	अन्यथा अणु
		sf = (cam->user_क्रमmat.width*2048)/VGA_WIDTH;
		avscale = VCR_AVS_HEN | sf;
	पूर्ण
	अगर (cam->user_क्रमmat.height < VGA_HEIGHT) अणु
		sf = (1024*cam->user_क्रमmat.height)/VGA_HEIGHT;
		avscale |= VCR_AVS_VEN | (sf << 16);
	पूर्ण
	viacam_ग_लिखो_reg(cam, VCR_AVSCALE, avscale);
पूर्ण


/*
 * Configure image-related inक्रमmation पूर्णांकo the capture engine.
 */
अटल व्योम viacam_ctlr_image(काष्ठा via_camera *cam)
अणु
	पूर्णांक cicreg;

	/*
	 * Disable घड़ी beक्रमe messing with stuff - from the via
	 * sample driver.
	 */
	viacam_ग_लिखो_reg(cam, VCR_CAPINTC, ~(VCR_CI_ENABLE|VCR_CI_CLKEN));
	/*
	 * Set up the controller क्रम VGA resolution, modulo magic
	 * offsets from the via sample driver.
	 */
	viacam_ग_लिखो_reg(cam, VCR_HORRANGE, 0x06200120);
	viacam_ग_लिखो_reg(cam, VCR_VERTRANGE, 0x01de0000);
	viacam_set_scale(cam);
	/*
	 * Image size info.
	 */
	viacam_ग_लिखो_reg(cam, VCR_MAXDATA,
			(cam->sensor_क्रमmat.height << 16) |
			(cam->sensor_क्रमmat.bytesperline >> 3));
	viacam_ग_लिखो_reg(cam, VCR_MAXVBI, 0);
	viacam_ग_लिखो_reg(cam, VCR_VSTRIDE,
			cam->user_क्रमmat.bytesperline & VCR_VS_STRIDE);
	/*
	 * Set up the capture पूर्णांकerface control रेजिस्टर,
	 * everything but the "go" bit.
	 *
	 * The FIFO threshold is a bit of a magic number; 8 is what
	 * VIA's sample code uses.
	 */
	cicreg = VCR_CI_CLKEN |
		0x08000000 |		/* FIFO threshold */
		VCR_CI_FLDINV |		/* OLPC-specअगरic? */
		VCR_CI_VREFINV |	/* OLPC-specअगरic? */
		VCR_CI_DIBOTH |		/* Capture both fields */
		VCR_CI_CCIR601_8;
	अगर (cam->n_cap_bufs == 3)
		cicreg |= VCR_CI_3BUFS;
	/*
	 * YUV क्रमmats need dअगरferent byte swapping than RGB.
	 */
	अगर (cam->user_क्रमmat.pixelक्रमmat == V4L2_PIX_FMT_YUYV)
		cicreg |= VCR_CI_YUYV;
	अन्यथा
		cicreg |= VCR_CI_UYVY;
	viacam_ग_लिखो_reg(cam, VCR_CAPINTC, cicreg);
पूर्ण


अटल पूर्णांक viacam_config_controller(काष्ठा via_camera *cam)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cam->viadev->reg_lock, flags);
	ret = viacam_ctlr_cbufs(cam);
	अगर (!ret)
		viacam_ctlr_image(cam);
	spin_unlock_irqrestore(&cam->viadev->reg_lock, flags);
	clear_bit(CF_CONFIG_NEEDED, &cam->flags);
	वापस ret;
पूर्ण

/*
 * Make it start grabbing data.
 */
अटल व्योम viacam_start_engine(काष्ठा via_camera *cam)
अणु
	spin_lock_irq(&cam->viadev->reg_lock);
	viacam_ग_लिखो_reg_mask(cam, VCR_CAPINTC, VCR_CI_ENABLE, VCR_CI_ENABLE);
	viacam_पूर्णांक_enable(cam);
	(व्योम) viacam_पढ़ो_reg(cam, VCR_CAPINTC); /* Force post */
	cam->opstate = S_RUNNING;
	spin_unlock_irq(&cam->viadev->reg_lock);
पूर्ण


अटल व्योम viacam_stop_engine(काष्ठा via_camera *cam)
अणु
	spin_lock_irq(&cam->viadev->reg_lock);
	viacam_पूर्णांक_disable(cam);
	viacam_ग_लिखो_reg_mask(cam, VCR_CAPINTC, 0, VCR_CI_ENABLE);
	(व्योम) viacam_पढ़ो_reg(cam, VCR_CAPINTC); /* Force post */
	cam->opstate = S_IDLE;
	spin_unlock_irq(&cam->viadev->reg_lock);
पूर्ण


/* --------------------------------------------------------------------------*/
/* vb2 callback ops */

अटल काष्ठा via_buffer *vb2_to_via_buffer(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	वापस container_of(vbuf, काष्ठा via_buffer, vbuf);
पूर्ण

अटल व्योम viacam_vb2_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा via_camera *cam = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा via_buffer *via = vb2_to_via_buffer(vb);

	list_add_tail(&via->queue, &cam->buffer_queue);
पूर्ण

अटल पूर्णांक viacam_vb2_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा via_camera *cam = vb2_get_drv_priv(vb->vb2_queue);

	अगर (vb2_plane_size(vb, 0) < cam->user_क्रमmat.sizeimage) अणु
		cam_dbg(cam,
			"Plane size too small (%lu < %u)\n",
			vb2_plane_size(vb, 0),
			cam->user_क्रमmat.sizeimage);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, cam->user_क्रमmat.sizeimage);

	वापस 0;
पूर्ण

अटल पूर्णांक viacam_vb2_queue_setup(काष्ठा vb2_queue *vq,
				  अचिन्हित पूर्णांक *nbufs,
				  अचिन्हित पूर्णांक *num_planes, अचिन्हित पूर्णांक sizes[],
				  काष्ठा device *alloc_devs[])
अणु
	काष्ठा via_camera *cam = vb2_get_drv_priv(vq);
	पूर्णांक size = cam->user_क्रमmat.sizeimage;

	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*num_planes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण

अटल पूर्णांक viacam_vb2_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा via_camera *cam = vb2_get_drv_priv(vq);
	काष्ठा via_buffer *buf, *पंचांगp;
	पूर्णांक ret = 0;

	अगर (cam->opstate != S_IDLE) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	/*
	 * Configure things अगर need be.
	 */
	अगर (test_bit(CF_CONFIG_NEEDED, &cam->flags)) अणु
		ret = viacam_configure_sensor(cam);
		अगर (ret)
			जाओ out;
		ret = viacam_config_controller(cam);
		अगर (ret)
			जाओ out;
	पूर्ण
	cam->sequence = 0;
	/*
	 * If the CPU goes पूर्णांकo C3, the DMA transfer माला_लो corrupted and
	 * users start filing unsightly bug reports.  Put in a "latency"
	 * requirement which will keep the CPU out of the deeper sleep
	 * states.
	 */
	cpu_latency_qos_add_request(&cam->qos_request, 50);
	viacam_start_engine(cam);
	वापस 0;
out:
	list_क्रम_each_entry_safe(buf, पंचांगp, &cam->buffer_queue, queue) अणु
		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vbuf.vb2_buf, VB2_BUF_STATE_QUEUED);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम viacam_vb2_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा via_camera *cam = vb2_get_drv_priv(vq);
	काष्ठा via_buffer *buf, *पंचांगp;

	cpu_latency_qos_हटाओ_request(&cam->qos_request);
	viacam_stop_engine(cam);

	list_क्रम_each_entry_safe(buf, पंचांगp, &cam->buffer_queue, queue) अणु
		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vbuf.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vb2_ops viacam_vb2_ops = अणु
	.queue_setup		= viacam_vb2_queue_setup,
	.buf_queue		= viacam_vb2_queue,
	.buf_prepare		= viacam_vb2_prepare,
	.start_streaming	= viacam_vb2_start_streaming,
	.stop_streaming		= viacam_vb2_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/* --------------------------------------------------------------------------*/
/* File operations */

अटल पूर्णांक viacam_खोलो(काष्ठा file *filp)
अणु
	काष्ठा via_camera *cam = video_drvdata(filp);
	पूर्णांक ret;

	/*
	 * Note the new user.  If this is the first one, we'll also
	 * need to घातer up the sensor.
	 */
	mutex_lock(&cam->lock);
	ret = v4l2_fh_खोलो(filp);
	अगर (ret)
		जाओ out;
	अगर (v4l2_fh_is_singular_file(filp)) अणु
		ret = viafb_request_dma();

		अगर (ret) अणु
			v4l2_fh_release(filp);
			जाओ out;
		पूर्ण
		via_sensor_घातer_up(cam);
		set_bit(CF_CONFIG_NEEDED, &cam->flags);
	पूर्ण
out:
	mutex_unlock(&cam->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक viacam_release(काष्ठा file *filp)
अणु
	काष्ठा via_camera *cam = video_drvdata(filp);
	bool last_खोलो;

	mutex_lock(&cam->lock);
	last_खोलो = v4l2_fh_is_singular_file(filp);
	_vb2_fop_release(filp, शून्य);
	/*
	 * Last one out needs to turn out the lights.
	 */
	अगर (last_खोलो) अणु
		via_sensor_घातer_करोwn(cam);
		viafb_release_dma();
	पूर्ण
	mutex_unlock(&cam->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations viacam_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= viacam_खोलो,
	.release	= viacam_release,
	.पढ़ो		= vb2_fop_पढ़ो,
	.poll		= vb2_fop_poll,
	.mmap		= vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

/*----------------------------------------------------------------------------*/
/*
 * The दीर्घ list of v4l2 ioctl ops
 */

/*
 * Only one input.
 */
अटल पूर्णांक viacam_क्रमागत_input(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_input *input)
अणु
	अगर (input->index != 0)
		वापस -EINVAL;

	input->type = V4L2_INPUT_TYPE_CAMERA;
	strscpy(input->name, "Camera", माप(input->name));
	वापस 0;
पूर्ण

अटल पूर्णांक viacam_g_input(काष्ठा file *filp, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक viacam_s_input(काष्ठा file *filp, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	अगर (i != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * Video क्रमmat stuff.	Here is our शेष क्रमmat until
 * user space messes with things.
 */
अटल स्थिर काष्ठा v4l2_pix_क्रमmat viacam_def_pix_क्रमmat = अणु
	.width		= VGA_WIDTH,
	.height		= VGA_HEIGHT,
	.pixelक्रमmat	= V4L2_PIX_FMT_YUYV,
	.field		= V4L2_FIELD_NONE,
	.bytesperline	= VGA_WIDTH * 2,
	.sizeimage	= VGA_WIDTH * VGA_HEIGHT * 2,
	.colorspace	= V4L2_COLORSPACE_SRGB,
पूर्ण;

अटल स्थिर u32 via_def_mbus_code = MEDIA_BUS_FMT_YUYV8_2X8;

अटल पूर्णांक viacam_क्रमागत_fmt_vid_cap(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_fmtdesc *fmt)
अणु
	अगर (fmt->index >= N_VIA_FMTS)
		वापस -EINVAL;
	fmt->pixelक्रमmat = via_क्रमmats[fmt->index].pixelक्रमmat;
	वापस 0;
पूर्ण

/*
 * Figure out proper image dimensions, but always क्रमce the
 * sensor to VGA.
 */
अटल व्योम viacam_fmt_pre(काष्ठा v4l2_pix_क्रमmat *userfmt,
		काष्ठा v4l2_pix_क्रमmat *sensorfmt)
अणु
	*sensorfmt = *userfmt;
	अगर (userfmt->width < QCIF_WIDTH || userfmt->height < QCIF_HEIGHT) अणु
		userfmt->width = QCIF_WIDTH;
		userfmt->height = QCIF_HEIGHT;
	पूर्ण
	अगर (userfmt->width > VGA_WIDTH || userfmt->height > VGA_HEIGHT) अणु
		userfmt->width = VGA_WIDTH;
		userfmt->height = VGA_HEIGHT;
	पूर्ण
	sensorfmt->width = VGA_WIDTH;
	sensorfmt->height = VGA_HEIGHT;
पूर्ण

अटल व्योम viacam_fmt_post(काष्ठा v4l2_pix_क्रमmat *userfmt,
		काष्ठा v4l2_pix_क्रमmat *sensorfmt)
अणु
	काष्ठा via_क्रमmat *f = via_find_क्रमmat(userfmt->pixelक्रमmat);

	sensorfmt->bytesperline = sensorfmt->width * f->bpp;
	sensorfmt->sizeimage = sensorfmt->height * sensorfmt->bytesperline;
	userfmt->pixelक्रमmat = sensorfmt->pixelक्रमmat;
	userfmt->field = sensorfmt->field;
	userfmt->bytesperline = 2 * userfmt->width;
	userfmt->sizeimage = userfmt->bytesperline * userfmt->height;
	userfmt->colorspace = sensorfmt->colorspace;
	userfmt->ycbcr_enc = sensorfmt->ycbcr_enc;
	userfmt->quantization = sensorfmt->quantization;
	userfmt->xfer_func = sensorfmt->xfer_func;
पूर्ण


/*
 * The real work of figuring out a workable क्रमmat.
 */
अटल पूर्णांक viacam_करो_try_fmt(काष्ठा via_camera *cam,
		काष्ठा v4l2_pix_क्रमmat *upix, काष्ठा v4l2_pix_क्रमmat *spix)
अणु
	पूर्णांक ret;
	काष्ठा v4l2_subdev_pad_config pad_cfg;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_TRY,
	पूर्ण;
	काष्ठा via_क्रमmat *f = via_find_क्रमmat(upix->pixelक्रमmat);

	upix->pixelक्रमmat = f->pixelक्रमmat;
	viacam_fmt_pre(upix, spix);
	v4l2_fill_mbus_क्रमmat(&क्रमmat.क्रमmat, spix, f->mbus_code);
	ret = sensor_call(cam, pad, set_fmt, &pad_cfg, &क्रमmat);
	v4l2_fill_pix_क्रमmat(spix, &क्रमmat.क्रमmat);
	viacam_fmt_post(upix, spix);
	वापस ret;
पूर्ण



अटल पूर्णांक viacam_try_fmt_vid_cap(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा via_camera *cam = video_drvdata(filp);
	काष्ठा v4l2_क्रमmat sfmt;

	वापस viacam_करो_try_fmt(cam, &fmt->fmt.pix, &sfmt.fmt.pix);
पूर्ण


अटल पूर्णांक viacam_g_fmt_vid_cap(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा via_camera *cam = video_drvdata(filp);

	fmt->fmt.pix = cam->user_क्रमmat;
	वापस 0;
पूर्ण

अटल पूर्णांक viacam_s_fmt_vid_cap(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा via_camera *cam = video_drvdata(filp);
	पूर्णांक ret;
	काष्ठा v4l2_क्रमmat sfmt;
	काष्ठा via_क्रमmat *f = via_find_क्रमmat(fmt->fmt.pix.pixelक्रमmat);

	/*
	 * Camera must be idle or we can't mess with the
	 * video setup.
	 */
	अगर (cam->opstate != S_IDLE)
		वापस -EBUSY;
	/*
	 * Let the sensor code look over and tweak the
	 * requested क्रमmatting.
	 */
	ret = viacam_करो_try_fmt(cam, &fmt->fmt.pix, &sfmt.fmt.pix);
	अगर (ret)
		वापस ret;
	/*
	 * OK, let's commit to the new क्रमmat.
	 */
	cam->user_क्रमmat = fmt->fmt.pix;
	cam->sensor_क्रमmat = sfmt.fmt.pix;
	cam->mbus_code = f->mbus_code;
	ret = viacam_configure_sensor(cam);
	अगर (!ret)
		ret = viacam_config_controller(cam);
	वापस ret;
पूर्ण

अटल पूर्णांक viacam_querycap(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, "via-camera", माप(cap->driver));
	strscpy(cap->card, "via-camera", माप(cap->card));
	strscpy(cap->bus_info, "platform:via-camera", माप(cap->bus_info));
	वापस 0;
पूर्ण

/* G/S_PARM */

अटल पूर्णांक viacam_g_parm(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा via_camera *cam = video_drvdata(filp);

	वापस v4l2_g_parm_cap(video_devdata(filp), cam->sensor, parm);
पूर्ण

अटल पूर्णांक viacam_s_parm(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा via_camera *cam = video_drvdata(filp);

	वापस v4l2_s_parm_cap(video_devdata(filp), cam->sensor, parm);
पूर्ण

अटल पूर्णांक viacam_क्रमागत_framesizes(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_frmsizeक्रमागत *sizes)
अणु
	अचिन्हित पूर्णांक i;

	अगर (sizes->index != 0)
		वापस -EINVAL;
	क्रम (i = 0; i < N_VIA_FMTS; i++)
		अगर (sizes->pixel_क्रमmat == via_क्रमmats[i].pixelक्रमmat)
			अवरोध;
	अगर (i >= N_VIA_FMTS)
		वापस -EINVAL;
	sizes->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	sizes->stepwise.min_width = QCIF_WIDTH;
	sizes->stepwise.min_height = QCIF_HEIGHT;
	sizes->stepwise.max_width = VGA_WIDTH;
	sizes->stepwise.max_height = VGA_HEIGHT;
	sizes->stepwise.step_width = sizes->stepwise.step_height = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक viacam_क्रमागत_frameपूर्णांकervals(काष्ठा file *filp, व्योम *priv,
		काष्ठा v4l2_frmivalक्रमागत *पूर्णांकerval)
अणु
	काष्ठा via_camera *cam = video_drvdata(filp);
	काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत fie = अणु
		.index = पूर्णांकerval->index,
		.code = cam->mbus_code,
		.width = cam->sensor_क्रमmat.width,
		.height = cam->sensor_क्रमmat.height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < N_VIA_FMTS; i++)
		अगर (पूर्णांकerval->pixel_क्रमmat == via_क्रमmats[i].pixelक्रमmat)
			अवरोध;
	अगर (i >= N_VIA_FMTS)
		वापस -EINVAL;
	अगर (पूर्णांकerval->width < QCIF_WIDTH || पूर्णांकerval->width > VGA_WIDTH ||
	    पूर्णांकerval->height < QCIF_HEIGHT || पूर्णांकerval->height > VGA_HEIGHT)
		वापस -EINVAL;
	ret = sensor_call(cam, pad, क्रमागत_frame_पूर्णांकerval, शून्य, &fie);
	अगर (ret)
		वापस ret;
	पूर्णांकerval->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	पूर्णांकerval->discrete = fie.पूर्णांकerval;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops viacam_ioctl_ops = अणु
	.vidioc_क्रमागत_input	= viacam_क्रमागत_input,
	.vidioc_g_input		= viacam_g_input,
	.vidioc_s_input		= viacam_s_input,
	.vidioc_क्रमागत_fmt_vid_cap = viacam_क्रमागत_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = viacam_try_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= viacam_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= viacam_s_fmt_vid_cap,
	.vidioc_querycap	= viacam_querycap,
	.vidioc_reqbufs		= vb2_ioctl_reqbufs,
	.vidioc_create_bufs	= vb2_ioctl_create_bufs,
	.vidioc_querybuf	= vb2_ioctl_querybuf,
	.vidioc_prepare_buf	= vb2_ioctl_prepare_buf,
	.vidioc_qbuf		= vb2_ioctl_qbuf,
	.vidioc_dqbuf		= vb2_ioctl_dqbuf,
	.vidioc_expbuf		= vb2_ioctl_expbuf,
	.vidioc_streamon	= vb2_ioctl_streamon,
	.vidioc_streamoff	= vb2_ioctl_streamoff,
	.vidioc_g_parm		= viacam_g_parm,
	.vidioc_s_parm		= viacam_s_parm,
	.vidioc_क्रमागत_framesizes = viacam_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = viacam_क्रमागत_frameपूर्णांकervals,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

/*----------------------------------------------------------------------------*/

/*
 * Power management.
 */
#अगर_घोषित CONFIG_PM

अटल पूर्णांक viacam_suspend(व्योम *priv)
अणु
	काष्ठा via_camera *cam = priv;
	क्रमागत viacam_opstate state = cam->opstate;

	अगर (cam->opstate != S_IDLE) अणु
		viacam_stop_engine(cam);
		cam->opstate = state; /* So resume restarts */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक viacam_resume(व्योम *priv)
अणु
	काष्ठा via_camera *cam = priv;
	पूर्णांक ret = 0;

	/*
	 * Get back to a reasonable operating state.
	 */
	via_ग_लिखो_reg_mask(VIASR, 0x78, 0, 0x80);
	via_ग_लिखो_reg_mask(VIASR, 0x1e, 0xc0, 0xc0);
	viacam_पूर्णांक_disable(cam);
	set_bit(CF_CONFIG_NEEDED, &cam->flags);
	/*
	 * Make sure the sensor's घातer state is correct
	 */
	अगर (!list_empty(&cam->vdev.fh_list))
		via_sensor_घातer_up(cam);
	अन्यथा
		via_sensor_घातer_करोwn(cam);
	/*
	 * If it was operating, try to restart it.
	 */
	अगर (cam->opstate != S_IDLE) अणु
		mutex_lock(&cam->lock);
		ret = viacam_configure_sensor(cam);
		अगर (!ret)
			ret = viacam_config_controller(cam);
		mutex_unlock(&cam->lock);
		अगर (!ret)
			viacam_start_engine(cam);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा viafb_pm_hooks viacam_pm_hooks = अणु
	.suspend = viacam_suspend,
	.resume = viacam_resume
पूर्ण;

#पूर्ण_अगर /* CONFIG_PM */

/*
 * Setup stuff.
 */

अटल स्थिर काष्ठा video_device viacam_v4l_ढाँचा = अणु
	.name		= "via-camera",
	.minor		= -1,
	.fops		= &viacam_fops,
	.ioctl_ops	= &viacam_ioctl_ops,
	.release	= video_device_release_empty, /* Check this */
	.device_caps	= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
			  V4L2_CAP_STREAMING,
पूर्ण;

/*
 * The OLPC folks put the serial port on the same pin as
 * the camera.	They also get grumpy अगर we अवरोध the
 * serial port and keep them from using it.  So we have
 * to check the serial enable bit and not step on it.
 */
#घोषणा VIACAM_SERIAL_DEVFN 0x88
#घोषणा VIACAM_SERIAL_CREG 0x46
#घोषणा VIACAM_SERIAL_BIT 0x40

अटल bool viacam_serial_is_enabled(व्योम)
अणु
	काष्ठा pci_bus *pbus = pci_find_bus(0, 0);
	u8 cbyte;

	अगर (!pbus)
		वापस false;
	pci_bus_पढ़ो_config_byte(pbus, VIACAM_SERIAL_DEVFN,
			VIACAM_SERIAL_CREG, &cbyte);
	अगर ((cbyte & VIACAM_SERIAL_BIT) == 0)
		वापस false; /* Not enabled */
	अगर (!override_serial) अणु
		prपूर्णांकk(KERN_NOTICE "Via camera: serial port is enabled, " \
				"refusing to load.\n");
		prपूर्णांकk(KERN_NOTICE "Specify override_serial=1 to force " \
				"module loading.\n");
		वापस true;
	पूर्ण
	prपूर्णांकk(KERN_NOTICE "Via camera: overriding serial port\n");
	pci_bus_ग_लिखो_config_byte(pbus, VIACAM_SERIAL_DEVFN,
			VIACAM_SERIAL_CREG, cbyte & ~VIACAM_SERIAL_BIT);
	वापस false;
पूर्ण

अटल काष्ठा ov7670_config sensor_cfg = अणु
	/* The XO-1.5 (only known user) घड़ीs the camera at 90MHz. */
	.घड़ी_speed = 90,
पूर्ण;

अटल पूर्णांक viacam_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा i2c_adapter *sensor_adapter;
	काष्ठा viafb_dev *viadev = pdev->dev.platक्रमm_data;
	काष्ठा vb2_queue *vq;
	काष्ठा i2c_board_info ov7670_info = अणु
		.type = "ov7670",
		.addr = 0x42 >> 1,
		.platक्रमm_data = &sensor_cfg,
	पूर्ण;

	/*
	 * Note that there are actually two capture channels on
	 * the device.	We only deal with one क्रम now.	That
	 * is encoded here; nothing अन्यथा assumes it's dealing with
	 * a unique capture device.
	 */
	काष्ठा via_camera *cam;

	/*
	 * Ensure that frame buffer memory has been set aside क्रम
	 * this purpose.  As an arbitrary limit, refuse to work
	 * with less than two frames of VGA 16-bit data.
	 *
	 * If we ever support the second port, we'll need to set
	 * aside more memory.
	 */
	अगर (viadev->camera_fbmem_size < (VGA_HEIGHT*VGA_WIDTH*4)) अणु
		prपूर्णांकk(KERN_ERR "viacam: insufficient FB memory reserved\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (viadev->engine_mmio == शून्य) अणु
		prपूर्णांकk(KERN_ERR "viacam: No I/O memory, so no pictures\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (machine_is_olpc() && viacam_serial_is_enabled())
		वापस -EBUSY;

	/*
	 * Basic काष्ठाure initialization.
	 */
	cam = kzalloc (माप(काष्ठा via_camera), GFP_KERNEL);
	अगर (cam == शून्य)
		वापस -ENOMEM;
	via_cam_info = cam;
	cam->platdev = pdev;
	cam->viadev = viadev;
	cam->opstate = S_IDLE;
	cam->user_क्रमmat = cam->sensor_क्रमmat = viacam_def_pix_क्रमmat;
	mutex_init(&cam->lock);
	INIT_LIST_HEAD(&cam->buffer_queue);
	cam->mmio = viadev->engine_mmio;
	cam->fbmem = viadev->fbmem;
	cam->fb_offset = viadev->camera_fbmem_offset;
	cam->flags = 1 << CF_CONFIG_NEEDED;
	cam->mbus_code = via_def_mbus_code;
	/*
	 * Tell V4L that we exist.
	 */
	ret = v4l2_device_रेजिस्टर(&pdev->dev, &cam->v4l2_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to register v4l2 device\n");
		जाओ out_मुक्त;
	पूर्ण
	ret = v4l2_ctrl_handler_init(&cam->ctrl_handler, 10);
	अगर (ret)
		जाओ out_unरेजिस्टर;
	cam->v4l2_dev.ctrl_handler = &cam->ctrl_handler;
	/*
	 * Convince the प्रणाली that we can करो DMA.
	 */
	pdev->dev.dma_mask = &viadev->pdev->dma_mask;
	dma_set_mask(&pdev->dev, 0xffffffff);
	/*
	 * Fire up the capture port.  The ग_लिखो to 0x78 looks purely
	 * OLPCish; any प्रणाली will need to tweak 0x1e.
	 */
	via_ग_लिखो_reg_mask(VIASR, 0x78, 0, 0x80);
	via_ग_लिखो_reg_mask(VIASR, 0x1e, 0xc0, 0xc0);
	/*
	 * Get the sensor घातered up.
	 */
	ret = via_sensor_घातer_setup(cam);
	अगर (ret)
		जाओ out_ctrl_hdl_मुक्त;
	via_sensor_घातer_up(cam);

	/*
	 * See अगर we can't find it on the bus.	The VIA_PORT_31 assumption
	 * is OLPC-specअगरic.  0x42 assumption is ov7670-specअगरic.
	 */
	sensor_adapter = viafb_find_i2c_adapter(VIA_PORT_31);
	cam->sensor = v4l2_i2c_new_subdev_board(&cam->v4l2_dev, sensor_adapter,
			&ov7670_info, शून्य);
	अगर (cam->sensor == शून्य) अणु
		dev_err(&pdev->dev, "Unable to find the sensor!\n");
		ret = -ENODEV;
		जाओ out_घातer_करोwn;
	पूर्ण
	/*
	 * Get the IRQ.
	 */
	viacam_पूर्णांक_disable(cam);
	ret = request_thपढ़ोed_irq(viadev->pdev->irq, viacam_quick_irq,
			viacam_irq, IRQF_SHARED, "via-camera", cam);
	अगर (ret)
		जाओ out_घातer_करोwn;

	vq = &cam->vq;
	vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
	vq->drv_priv = cam;
	vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vq->buf_काष्ठा_size = माप(काष्ठा via_buffer);
	vq->dev = cam->v4l2_dev.dev;

	vq->ops = &viacam_vb2_ops;
	vq->mem_ops = &vb2_dma_sg_memops;
	vq->lock = &cam->lock;

	ret = vb2_queue_init(vq);
	/*
	 * Tell V4l2 that we exist.
	 */
	cam->vdev = viacam_v4l_ढाँचा;
	cam->vdev.v4l2_dev = &cam->v4l2_dev;
	cam->vdev.lock = &cam->lock;
	cam->vdev.queue = vq;
	video_set_drvdata(&cam->vdev, cam);
	ret = video_रेजिस्टर_device(&cam->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret)
		जाओ out_irq;

#अगर_घोषित CONFIG_PM
	/*
	 * Hook पूर्णांकo PM events
	 */
	viacam_pm_hooks.निजी = cam;
	viafb_pm_रेजिस्टर(&viacam_pm_hooks);
#पूर्ण_अगर

	/* Power the sensor करोwn until somebody खोलोs the device */
	via_sensor_घातer_करोwn(cam);
	वापस 0;

out_irq:
	मुक्त_irq(viadev->pdev->irq, cam);
out_घातer_करोwn:
	via_sensor_घातer_release(cam);
out_ctrl_hdl_मुक्त:
	v4l2_ctrl_handler_मुक्त(&cam->ctrl_handler);
out_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&cam->v4l2_dev);
out_मुक्त:
	kमुक्त(cam);
	वापस ret;
पूर्ण

अटल पूर्णांक viacam_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा via_camera *cam = via_cam_info;
	काष्ठा viafb_dev *viadev = pdev->dev.platक्रमm_data;

	video_unरेजिस्टर_device(&cam->vdev);
	v4l2_device_unरेजिस्टर(&cam->v4l2_dev);
#अगर_घोषित CONFIG_PM
	viafb_pm_unरेजिस्टर(&viacam_pm_hooks);
#पूर्ण_अगर
	मुक्त_irq(viadev->pdev->irq, cam);
	via_sensor_घातer_release(cam);
	v4l2_ctrl_handler_मुक्त(&cam->ctrl_handler);
	kमुक्त(cam);
	via_cam_info = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver viacam_driver = अणु
	.driver = अणु
		.name = "viafb-camera",
	पूर्ण,
	.probe = viacam_probe,
	.हटाओ = viacam_हटाओ,
पूर्ण;

module_platक्रमm_driver(viacam_driver);
