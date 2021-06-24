<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2008-2009 Texas Instruments Inc
 *
 * Driver name : VPFE Capture driver
 *    VPFE Capture driver allows applications to capture and stream video
 *    frames on DaVinci SoCs (DM6446, DM355 etc) from a YUV source such as
 *    TVP5146 or  Raw Bayer RGB image data from an image sensor
 *    such as Microns' MT9T001, MT9T031 etc.
 *
 *    These SoCs have, in common, a Video Processing Subप्रणाली (VPSS) that
 *    consists of a Video Processing Front End (VPFE) क्रम capturing
 *    video/raw image data and Video Processing Back End (VPBE) क्रम displaying
 *    YUV data through an in-built analog encoder or Digital LCD port. This
 *    driver is क्रम capture through VPFE. A typical EVM using these SoCs have
 *    following high level configuration.
 *
 *    decoder(TVP5146/		YUV/
 *	     MT9T001)   -->  Raw Bayer RGB ---> MUX -> VPFE (CCDC/ISIF)
 *				data input              |      |
 *							V      |
 *						      SDRAM    |
 *							       V
 *							   Image Processor
 *							       |
 *							       V
 *							     SDRAM
 *    The data flow happens from a decoder connected to the VPFE over a
 *    YUV embedded (BT.656/BT.1120) or separate sync or raw bayer rgb पूर्णांकerface
 *    and to the input of VPFE through an optional MUX (अगर more inमाला_दो are
 *    to be पूर्णांकerfaced on the EVM). The input data is first passed through
 *    CCDC (CCD Controller, a.k.a Image Sensor Interface, ISIF). The CCDC
 *    करोes very little or no processing on YUV data and करोes pre-process Raw
 *    Bayer RGB data through modules such as Defect Pixel Correction (DFC)
 *    Color Space Conversion (CSC), data gain/offset etc. After this, data
 *    can be written to SDRAM or can be connected to the image processing
 *    block such as IPIPE (on DM355 only).
 *
 *    Features supported
 *		- MMAP IO
 *		- Capture using TVP5146 over BT.656
 *		- support क्रम पूर्णांकerfacing decoders using sub device model
 *		- Work with DM355 or DM6446 CCDC to करो Raw Bayer RGB/YUV
 *		  data capture to SDRAM.
 *    TODO list
 *		- Support multiple REQBUF after खोलो
 *		- Support क्रम de-allocating buffers through REQBUF
 *		- Support क्रम Raw Bayer RGB capture
 *		- Support क्रम chaining Image Processor
 *		- Support क्रम अटल allocation of buffers
 *		- Support क्रम USERPTR IO
 *		- Support क्रम STREAMON beक्रमe QBUF
 *		- Support क्रम control ioctls
 */
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <media/v4l2-common.h>
#समावेश <linux/पन.स>
#समावेश <media/davinci/vpfe_capture.h>
#समावेश "ccdc_hw_device.h"

अटल पूर्णांक debug;
अटल u32 numbuffers = 3;
अटल u32 bufsize = (720 * 576 * 2);

module_param(numbuffers, uपूर्णांक, S_IRUGO);
module_param(bufsize, uपूर्णांक, S_IRUGO);
module_param(debug, पूर्णांक, 0644);

MODULE_PARM_DESC(numbuffers, "buffer count (default:3)");
MODULE_PARM_DESC(bufsize, "buffer size in bytes (default:720 x 576 x 2)");
MODULE_PARM_DESC(debug, "Debug level 0-1");

MODULE_DESCRIPTION("VPFE Video for Linux Capture Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Texas Instruments");

/* standard inक्रमmation */
काष्ठा vpfe_standard अणु
	v4l2_std_id std_id;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	काष्ठा v4l2_fract pixelaspect;
	/* 0 - progressive, 1 - पूर्णांकerlaced */
	पूर्णांक frame_क्रमmat;
पूर्ण;

/* ccdc configuration */
काष्ठा ccdc_config अणु
	/* This make sure vpfe is probed and पढ़ोy to go */
	पूर्णांक vpfe_probed;
	/* name of ccdc device */
	अक्षर name[32];
पूर्ण;

/* data काष्ठाures */
अटल काष्ठा vpfe_config_params config_params = अणु
	.min_numbuffers = 3,
	.numbuffers = 3,
	.min_bufsize = 720 * 480 * 2,
	.device_bufsize = 720 * 576 * 2,
पूर्ण;

/* ccdc device रेजिस्टरed */
अटल स्थिर काष्ठा ccdc_hw_device *ccdc_dev;
/* lock क्रम accessing ccdc inक्रमmation */
अटल DEFINE_MUTEX(ccdc_lock);
/* ccdc configuration */
अटल काष्ठा ccdc_config *ccdc_cfg;

अटल स्थिर काष्ठा vpfe_standard vpfe_standards[] = अणु
	अणुV4L2_STD_525_60, 720, 480, अणु11, 10पूर्ण, 1पूर्ण,
	अणुV4L2_STD_625_50, 720, 576, अणु54, 59पूर्ण, 1पूर्ण,
पूर्ण;

/* Used when raw Bayer image from ccdc is directly captured to SDRAM */
अटल स्थिर काष्ठा vpfe_pixel_क्रमmat vpfe_pix_fmts[] = अणु
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR8,
		.bpp = 1,
	पूर्ण,
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SBGGR16,
		.bpp = 2,
	पूर्ण,
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_SGRBG10DPCM8,
		.bpp = 1,
	पूर्ण,
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_UYVY,
		.bpp = 2,
	पूर्ण,
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_YUYV,
		.bpp = 2,
	पूर्ण,
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_NV12,
		.bpp = 1,
	पूर्ण,
पूर्ण;

/*
 * vpfe_lookup_pix_क्रमmat()
 * lookup an entry in the vpfe pix क्रमmat table based on pix_क्रमmat
 */
अटल स्थिर काष्ठा vpfe_pixel_क्रमmat *vpfe_lookup_pix_क्रमmat(u32 pix_क्रमmat)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vpfe_pix_fmts); i++) अणु
		अगर (pix_क्रमmat == vpfe_pix_fmts[i].pixelक्रमmat)
			वापस &vpfe_pix_fmts[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * vpfe_रेजिस्टर_ccdc_device. CCDC module calls this to
 * रेजिस्टर with vpfe capture
 */
पूर्णांक vpfe_रेजिस्टर_ccdc_device(स्थिर काष्ठा ccdc_hw_device *dev)
अणु
	पूर्णांक ret = 0;
	prपूर्णांकk(KERN_NOTICE "vpfe_register_ccdc_device: %s\n", dev->name);

	अगर (!dev->hw_ops.खोलो ||
	    !dev->hw_ops.enable ||
	    !dev->hw_ops.set_hw_अगर_params ||
	    !dev->hw_ops.configure ||
	    !dev->hw_ops.set_buftype ||
	    !dev->hw_ops.get_buftype ||
	    !dev->hw_ops.क्रमागत_pix ||
	    !dev->hw_ops.set_frame_क्रमmat ||
	    !dev->hw_ops.get_frame_क्रमmat ||
	    !dev->hw_ops.get_pixel_क्रमmat ||
	    !dev->hw_ops.set_pixel_क्रमmat ||
	    !dev->hw_ops.set_image_winकरोw ||
	    !dev->hw_ops.get_image_winकरोw ||
	    !dev->hw_ops.get_line_length ||
	    !dev->hw_ops.getfid)
		वापस -EINVAL;

	mutex_lock(&ccdc_lock);
	अगर (!ccdc_cfg) अणु
		/*
		 * TODO. Will this ever happen? अगर so, we need to fix it.
		 * Proabably we need to add the request to a linked list and
		 * walk through it during vpfe probe
		 */
		prपूर्णांकk(KERN_ERR "vpfe capture not initialized\n");
		ret = -EFAULT;
		जाओ unlock;
	पूर्ण

	अगर (म_भेद(dev->name, ccdc_cfg->name)) अणु
		/* ignore this ccdc */
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (ccdc_dev) अणु
		prपूर्णांकk(KERN_ERR "ccdc already registered\n");
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	ccdc_dev = dev;
unlock:
	mutex_unlock(&ccdc_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vpfe_रेजिस्टर_ccdc_device);

/*
 * vpfe_unरेजिस्टर_ccdc_device. CCDC module calls this to
 * unरेजिस्टर with vpfe capture
 */
व्योम vpfe_unरेजिस्टर_ccdc_device(स्थिर काष्ठा ccdc_hw_device *dev)
अणु
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "invalid ccdc device ptr\n");
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_NOTICE "vpfe_unregister_ccdc_device, dev->name = %s\n",
		dev->name);

	अगर (म_भेद(dev->name, ccdc_cfg->name)) अणु
		/* ignore this ccdc */
		वापस;
	पूर्ण

	mutex_lock(&ccdc_lock);
	ccdc_dev = शून्य;
	mutex_unlock(&ccdc_lock);
पूर्ण
EXPORT_SYMBOL(vpfe_unरेजिस्टर_ccdc_device);

/*
 * vpfe_config_ccdc_image_क्रमmat()
 * For a pix क्रमmat, configure ccdc to setup the capture
 */
अटल पूर्णांक vpfe_config_ccdc_image_क्रमmat(काष्ठा vpfe_device *vpfe_dev)
अणु
	क्रमागत ccdc_frmfmt frm_fmt = CCDC_FRMFMT_INTERLACED;
	पूर्णांक ret = 0;

	अगर (ccdc_dev->hw_ops.set_pixel_क्रमmat(
			vpfe_dev->fmt.fmt.pix.pixelक्रमmat) < 0) अणु
		v4l2_err(&vpfe_dev->v4l2_dev,
			"couldn't set pix format in ccdc\n");
		वापस -EINVAL;
	पूर्ण
	/* configure the image winकरोw */
	ccdc_dev->hw_ops.set_image_winकरोw(&vpfe_dev->crop);

	चयन (vpfe_dev->fmt.fmt.pix.field) अणु
	हाल V4L2_FIELD_INTERLACED:
		/* करो nothing, since it is शेष */
		ret = ccdc_dev->hw_ops.set_buftype(
				CCDC_BUFTYPE_FLD_INTERLEAVED);
		अवरोध;
	हाल V4L2_FIELD_NONE:
		frm_fmt = CCDC_FRMFMT_PROGRESSIVE;
		/* buffer type only applicable क्रम पूर्णांकerlaced scan */
		अवरोध;
	हाल V4L2_FIELD_SEQ_TB:
		ret = ccdc_dev->hw_ops.set_buftype(
				CCDC_BUFTYPE_FLD_SEPARATED);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set the frame क्रमmat */
	अगर (!ret)
		ret = ccdc_dev->hw_ops.set_frame_क्रमmat(frm_fmt);
	वापस ret;
पूर्ण
/*
 * vpfe_config_image_क्रमmat()
 * For a given standard, this functions sets up the शेष
 * pix क्रमmat & crop values in the vpfe device and ccdc.  It first
 * starts with शेषs based values from the standard table.
 * It then checks अगर sub device supports get_fmt and then override the
 * values based on that.Sets crop values to match with scan resolution
 * starting at 0,0. It calls vpfe_config_ccdc_image_क्रमmat() set the
 * values in ccdc
 */
अटल पूर्णांक vpfe_config_image_क्रमmat(काष्ठा vpfe_device *vpfe_dev,
				    v4l2_std_id std_id)
अणु
	काष्ठा vpfe_subdev_info *sdinfo = vpfe_dev->current_subdev;
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &fmt.क्रमmat;
	काष्ठा v4l2_pix_क्रमmat *pix = &vpfe_dev->fmt.fmt.pix;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(vpfe_standards); i++) अणु
		अगर (vpfe_standards[i].std_id & std_id) अणु
			vpfe_dev->std_info.active_pixels =
					vpfe_standards[i].width;
			vpfe_dev->std_info.active_lines =
					vpfe_standards[i].height;
			vpfe_dev->std_info.frame_क्रमmat =
					vpfe_standards[i].frame_क्रमmat;
			vpfe_dev->std_index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i ==  ARRAY_SIZE(vpfe_standards)) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "standard not supported\n");
		वापस -EINVAL;
	पूर्ण

	vpfe_dev->crop.top = 0;
	vpfe_dev->crop.left = 0;
	vpfe_dev->crop.width = vpfe_dev->std_info.active_pixels;
	vpfe_dev->crop.height = vpfe_dev->std_info.active_lines;
	pix->width = vpfe_dev->crop.width;
	pix->height = vpfe_dev->crop.height;

	/* first field and frame क्रमmat based on standard frame क्रमmat */
	अगर (vpfe_dev->std_info.frame_क्रमmat) अणु
		pix->field = V4L2_FIELD_INTERLACED;
		/* assume V4L2_PIX_FMT_UYVY as शेष */
		pix->pixelक्रमmat = V4L2_PIX_FMT_UYVY;
		v4l2_fill_mbus_क्रमmat(mbus_fmt, pix,
				MEDIA_BUS_FMT_YUYV10_2X10);
	पूर्ण अन्यथा अणु
		pix->field = V4L2_FIELD_NONE;
		/* assume V4L2_PIX_FMT_SBGGR8 */
		pix->pixelक्रमmat = V4L2_PIX_FMT_SBGGR8;
		v4l2_fill_mbus_क्रमmat(mbus_fmt, pix,
				MEDIA_BUS_FMT_SBGGR8_1X8);
	पूर्ण

	/* अगर sub device supports get_fmt, override the शेषs */
	ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev,
			sdinfo->grp_id, pad, get_fmt, शून्य, &fmt);

	अगर (ret && ret != -ENOIOCTLCMD) अणु
		v4l2_err(&vpfe_dev->v4l2_dev,
			"error in getting get_fmt from sub device\n");
		वापस ret;
	पूर्ण
	v4l2_fill_pix_क्रमmat(pix, mbus_fmt);
	pix->bytesperline = pix->width * 2;
	pix->sizeimage = pix->bytesperline * pix->height;

	/* Sets the values in CCDC */
	ret = vpfe_config_ccdc_image_क्रमmat(vpfe_dev);
	अगर (ret)
		वापस ret;

	/* Update the values of sizeimage and bytesperline */
	pix->bytesperline = ccdc_dev->hw_ops.get_line_length();
	pix->sizeimage = pix->bytesperline * pix->height;

	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_initialize_device(काष्ठा vpfe_device *vpfe_dev)
अणु
	पूर्णांक ret;

	/* set first input of current subdevice as the current input */
	vpfe_dev->current_input = 0;

	/* set शेष standard */
	vpfe_dev->std_index = 0;

	/* Configure the शेष क्रमmat inक्रमmation */
	ret = vpfe_config_image_क्रमmat(vpfe_dev,
				vpfe_standards[vpfe_dev->std_index].std_id);
	अगर (ret)
		वापस ret;

	/* now खोलो the ccdc device to initialize it */
	mutex_lock(&ccdc_lock);
	अगर (!ccdc_dev) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "ccdc device not registered\n");
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगर (!try_module_get(ccdc_dev->owner)) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Couldn't lock ccdc module\n");
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण
	ret = ccdc_dev->hw_ops.खोलो(vpfe_dev->pdev);
	अगर (!ret)
		vpfe_dev->initialized = 1;

	/* Clear all VPFE/CCDC पूर्णांकerrupts */
	अगर (vpfe_dev->cfg->clr_पूर्णांकr)
		vpfe_dev->cfg->clr_पूर्णांकr(-1);

unlock:
	mutex_unlock(&ccdc_lock);
	वापस ret;
पूर्ण

/*
 * vpfe_खोलो : It creates object of file handle काष्ठाure and
 * stores it in निजी_data  member of filepoपूर्णांकer
 */
अटल पूर्णांक vpfe_खोलो(काष्ठा file *file)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा vpfe_fh *fh;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_open\n");

	अगर (!vpfe_dev->cfg->num_subdevs) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "No decoder registered\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate memory क्रम the file handle object */
	fh = kदो_स्मृति(माप(*fh), GFP_KERNEL);
	अगर (!fh)
		वापस -ENOMEM;

	/* store poपूर्णांकer to fh in निजी_data member of file */
	file->निजी_data = fh;
	fh->vpfe_dev = vpfe_dev;
	v4l2_fh_init(&fh->fh, vdev);
	mutex_lock(&vpfe_dev->lock);
	/* If decoder is not initialized. initialize it */
	अगर (!vpfe_dev->initialized) अणु
		अगर (vpfe_initialize_device(vpfe_dev)) अणु
			mutex_unlock(&vpfe_dev->lock);
			v4l2_fh_निकास(&fh->fh);
			kमुक्त(fh);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	/* Increment device usrs counter */
	vpfe_dev->usrs++;
	/* Set io_allowed member to false */
	fh->io_allowed = 0;
	v4l2_fh_add(&fh->fh);
	mutex_unlock(&vpfe_dev->lock);
	वापस 0;
पूर्ण

अटल व्योम vpfe_schedule_next_buffer(काष्ठा vpfe_device *vpfe_dev)
अणु
	अचिन्हित दीर्घ addr;

	vpfe_dev->next_frm = list_entry(vpfe_dev->dma_queue.next,
					काष्ठा videobuf_buffer, queue);
	list_del(&vpfe_dev->next_frm->queue);
	vpfe_dev->next_frm->state = VIDEOBUF_ACTIVE;
	addr = videobuf_to_dma_contig(vpfe_dev->next_frm);

	ccdc_dev->hw_ops.setfbaddr(addr);
पूर्ण

अटल व्योम vpfe_schedule_bottom_field(काष्ठा vpfe_device *vpfe_dev)
अणु
	अचिन्हित दीर्घ addr;

	addr = videobuf_to_dma_contig(vpfe_dev->cur_frm);
	addr += vpfe_dev->field_off;
	ccdc_dev->hw_ops.setfbaddr(addr);
पूर्ण

अटल व्योम vpfe_process_buffer_complete(काष्ठा vpfe_device *vpfe_dev)
अणु
	vpfe_dev->cur_frm->ts = kसमय_get_ns();
	vpfe_dev->cur_frm->state = VIDEOBUF_DONE;
	vpfe_dev->cur_frm->size = vpfe_dev->fmt.fmt.pix.sizeimage;
	wake_up_पूर्णांकerruptible(&vpfe_dev->cur_frm->करोne);
	vpfe_dev->cur_frm = vpfe_dev->next_frm;
पूर्ण

/* ISR क्रम VINT0*/
अटल irqवापस_t vpfe_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vpfe_device *vpfe_dev = dev_id;
	क्रमागत v4l2_field field;
	पूर्णांक fid;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "\nStarting vpfe_isr...\n");
	field = vpfe_dev->fmt.fmt.pix.field;

	/* अगर streaming not started, करोn't करो anything */
	अगर (!vpfe_dev->started)
		जाओ clear_पूर्णांकr;

	/* only क्रम 6446 this will be applicable */
	अगर (ccdc_dev->hw_ops.reset)
		ccdc_dev->hw_ops.reset();

	अगर (field == V4L2_FIELD_NONE) अणु
		/* handle progressive frame capture */
		v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev,
			"frame format is progressive...\n");
		अगर (vpfe_dev->cur_frm != vpfe_dev->next_frm)
			vpfe_process_buffer_complete(vpfe_dev);
		जाओ clear_पूर्णांकr;
	पूर्ण

	/* पूर्णांकerlaced or TB capture check which field we are in hardware */
	fid = ccdc_dev->hw_ops.getfid();

	/* चयन the software मुख्यtained field id */
	vpfe_dev->field_id ^= 1;
	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "field id = %x:%x.\n",
		fid, vpfe_dev->field_id);
	अगर (fid == vpfe_dev->field_id) अणु
		/* we are in-sync here,जारी */
		अगर (fid == 0) अणु
			/*
			 * One frame is just being captured. If the next frame
			 * is available, release the current frame and move on
			 */
			अगर (vpfe_dev->cur_frm != vpfe_dev->next_frm)
				vpfe_process_buffer_complete(vpfe_dev);
			/*
			 * based on whether the two fields are stored
			 * पूर्णांकerleavely or separately in memory, reconfigure
			 * the CCDC memory address
			 */
			अगर (field == V4L2_FIELD_SEQ_TB)
				vpfe_schedule_bottom_field(vpfe_dev);
			जाओ clear_पूर्णांकr;
		पूर्ण
		/*
		 * अगर one field is just being captured configure
		 * the next frame get the next frame from the empty
		 * queue अगर no frame is available hold on to the
		 * current buffer
		 */
		spin_lock(&vpfe_dev->dma_queue_lock);
		अगर (!list_empty(&vpfe_dev->dma_queue) &&
		    vpfe_dev->cur_frm == vpfe_dev->next_frm)
			vpfe_schedule_next_buffer(vpfe_dev);
		spin_unlock(&vpfe_dev->dma_queue_lock);
	पूर्ण अन्यथा अगर (fid == 0) अणु
		/*
		 * out of sync. Recover from any hardware out-of-sync.
		 * May loose one frame
		 */
		vpfe_dev->field_id = fid;
	पूर्ण
clear_पूर्णांकr:
	अगर (vpfe_dev->cfg->clr_पूर्णांकr)
		vpfe_dev->cfg->clr_पूर्णांकr(irq);

	वापस IRQ_HANDLED;
पूर्ण

/* vdपूर्णांक1_isr - isr handler क्रम VINT1 पूर्णांकerrupt */
अटल irqवापस_t vdपूर्णांक1_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vpfe_device *vpfe_dev = dev_id;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "\nInside vdint1_isr...\n");

	/* अगर streaming not started, करोn't करो anything */
	अगर (!vpfe_dev->started) अणु
		अगर (vpfe_dev->cfg->clr_पूर्णांकr)
			vpfe_dev->cfg->clr_पूर्णांकr(irq);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock(&vpfe_dev->dma_queue_lock);
	अगर ((vpfe_dev->fmt.fmt.pix.field == V4L2_FIELD_NONE) &&
	    !list_empty(&vpfe_dev->dma_queue) &&
	    vpfe_dev->cur_frm == vpfe_dev->next_frm)
		vpfe_schedule_next_buffer(vpfe_dev);
	spin_unlock(&vpfe_dev->dma_queue_lock);

	अगर (vpfe_dev->cfg->clr_पूर्णांकr)
		vpfe_dev->cfg->clr_पूर्णांकr(irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम vpfe_detach_irq(काष्ठा vpfe_device *vpfe_dev)
अणु
	क्रमागत ccdc_frmfmt frame_क्रमmat;

	frame_क्रमmat = ccdc_dev->hw_ops.get_frame_क्रमmat();
	अगर (frame_क्रमmat == CCDC_FRMFMT_PROGRESSIVE)
		मुक्त_irq(vpfe_dev->ccdc_irq1, vpfe_dev);
पूर्ण

अटल पूर्णांक vpfe_attach_irq(काष्ठा vpfe_device *vpfe_dev)
अणु
	क्रमागत ccdc_frmfmt frame_क्रमmat;

	frame_क्रमmat = ccdc_dev->hw_ops.get_frame_क्रमmat();
	अगर (frame_क्रमmat == CCDC_FRMFMT_PROGRESSIVE) अणु
		वापस request_irq(vpfe_dev->ccdc_irq1, vdपूर्णांक1_isr,
				    0, "vpfe_capture1",
				    vpfe_dev);
	पूर्ण
	वापस 0;
पूर्ण

/* vpfe_stop_ccdc_capture: stop streaming in ccdc/isअगर */
अटल व्योम vpfe_stop_ccdc_capture(काष्ठा vpfe_device *vpfe_dev)
अणु
	vpfe_dev->started = 0;
	ccdc_dev->hw_ops.enable(0);
	अगर (ccdc_dev->hw_ops.enable_out_to_sdram)
		ccdc_dev->hw_ops.enable_out_to_sdram(0);
पूर्ण

/*
 * vpfe_release : This function deletes buffer queue, मुक्तs the
 * buffers and the vpfe file  handle
 */
अटल पूर्णांक vpfe_release(काष्ठा file *file)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा vpfe_fh *fh = file->निजी_data;
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_release\n");

	/* Get the device lock */
	mutex_lock(&vpfe_dev->lock);
	/* अगर this instance is करोing IO */
	अगर (fh->io_allowed) अणु
		अगर (vpfe_dev->started) अणु
			sdinfo = vpfe_dev->current_subdev;
			ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev,
							 sdinfo->grp_id,
							 video, s_stream, 0);
			अगर (ret && (ret != -ENOIOCTLCMD))
				v4l2_err(&vpfe_dev->v4l2_dev,
				"stream off failed in subdev\n");
			vpfe_stop_ccdc_capture(vpfe_dev);
			vpfe_detach_irq(vpfe_dev);
			videobuf_streamoff(&vpfe_dev->buffer_queue);
		पूर्ण
		vpfe_dev->io_usrs = 0;
		vpfe_dev->numbuffers = config_params.numbuffers;
		videobuf_stop(&vpfe_dev->buffer_queue);
		videobuf_mmap_मुक्त(&vpfe_dev->buffer_queue);
	पूर्ण

	/* Decrement device usrs counter */
	vpfe_dev->usrs--;
	v4l2_fh_del(&fh->fh);
	v4l2_fh_निकास(&fh->fh);
	/* If this is the last file handle */
	अगर (!vpfe_dev->usrs) अणु
		vpfe_dev->initialized = 0;
		अगर (ccdc_dev->hw_ops.बंद)
			ccdc_dev->hw_ops.बंद(vpfe_dev->pdev);
		module_put(ccdc_dev->owner);
	पूर्ण
	mutex_unlock(&vpfe_dev->lock);
	file->निजी_data = शून्य;
	/* Free memory allocated to file handle object */
	kमुक्त(fh);
	वापस 0;
पूर्ण

/*
 * vpfe_mmap : It is used to map kernel space buffers
 * पूर्णांकo user spaces
 */
अटल पूर्णांक vpfe_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	/* Get the device object and file handle object */
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_mmap\n");

	वापस videobuf_mmap_mapper(&vpfe_dev->buffer_queue, vma);
पूर्ण

/*
 * vpfe_poll: It is used क्रम select/poll प्रणाली call
 */
अटल __poll_t vpfe_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_poll\n");

	अगर (vpfe_dev->started)
		वापस videobuf_poll_stream(file,
					    &vpfe_dev->buffer_queue, रुको);
	वापस 0;
पूर्ण

/* vpfe capture driver file operations */
अटल स्थिर काष्ठा v4l2_file_operations vpfe_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = vpfe_खोलो,
	.release = vpfe_release,
	.unlocked_ioctl = video_ioctl2,
	.mmap = vpfe_mmap,
	.poll = vpfe_poll
पूर्ण;

/*
 * vpfe_check_क्रमmat()
 * This function adjust the input pixel क्रमmat as per hardware
 * capabilities and update the same in pixfmt.
 * Following algorithm used :-
 *
 *	If given pixक्रमmat is not in the vpfe list of pix क्रमmats or not
 *	supported by the hardware, current value of pixक्रमmat in the device
 *	is used
 *	If given field is not supported, then current field is used. If field
 *	is dअगरferent from current, then it is matched with that from sub device.
 *	Minimum height is 2 lines क्रम पूर्णांकerlaced or tb field and 1 line क्रम
 *	progressive. Maximum height is clamped to active active lines of scan
 *	Minimum width is 32 bytes in memory and width is clamped to active
 *	pixels of scan.
 *	bytesperline is a multiple of 32.
 */
अटल स्थिर काष्ठा vpfe_pixel_क्रमmat *
	vpfe_check_क्रमmat(काष्ठा vpfe_device *vpfe_dev,
			  काष्ठा v4l2_pix_क्रमmat *pixfmt)
अणु
	u32 min_height = 1, min_width = 32, max_width, max_height;
	स्थिर काष्ठा vpfe_pixel_क्रमmat *vpfe_pix_fmt;
	u32 pix;
	पूर्णांक temp, found;

	vpfe_pix_fmt = vpfe_lookup_pix_क्रमmat(pixfmt->pixelक्रमmat);
	अगर (!vpfe_pix_fmt) अणु
		/*
		 * use current pixel क्रमmat in the vpfe device. We
		 * will find this pix क्रमmat in the table
		 */
		pixfmt->pixelक्रमmat = vpfe_dev->fmt.fmt.pix.pixelक्रमmat;
		vpfe_pix_fmt = vpfe_lookup_pix_क्रमmat(pixfmt->pixelक्रमmat);
	पूर्ण

	/* check अगर hw supports it */
	temp = 0;
	found = 0;
	जबतक (ccdc_dev->hw_ops.क्रमागत_pix(&pix, temp) >= 0) अणु
		अगर (vpfe_pix_fmt->pixelक्रमmat == pix) अणु
			found = 1;
			अवरोध;
		पूर्ण
		temp++;
	पूर्ण

	अगर (!found) अणु
		/* use current pixel क्रमmat */
		pixfmt->pixelक्रमmat = vpfe_dev->fmt.fmt.pix.pixelक्रमmat;
		/*
		 * Since this is currently used in the vpfe device, we
		 * will find this pix क्रमmat in the table
		 */
		vpfe_pix_fmt = vpfe_lookup_pix_क्रमmat(pixfmt->pixelक्रमmat);
	पूर्ण

	/* check what field क्रमmat is supported */
	अगर (pixfmt->field == V4L2_FIELD_ANY) अणु
		/* अगर field is any, use current value as शेष */
		pixfmt->field = vpfe_dev->fmt.fmt.pix.field;
	पूर्ण

	/*
	 * अगर field is not same as current field in the vpfe device
	 * try matching the field with the sub device field
	 */
	अगर (vpfe_dev->fmt.fmt.pix.field != pixfmt->field) अणु
		/*
		 * If field value is not in the supported fields, use current
		 * field used in the device as शेष
		 */
		चयन (pixfmt->field) अणु
		हाल V4L2_FIELD_INTERLACED:
		हाल V4L2_FIELD_SEQ_TB:
			/* अगर sub device is supporting progressive, use that */
			अगर (!vpfe_dev->std_info.frame_क्रमmat)
				pixfmt->field = V4L2_FIELD_NONE;
			अवरोध;
		हाल V4L2_FIELD_NONE:
			अगर (vpfe_dev->std_info.frame_क्रमmat)
				pixfmt->field = V4L2_FIELD_INTERLACED;
			अवरोध;

		शेष:
			/* use current field as शेष */
			pixfmt->field = vpfe_dev->fmt.fmt.pix.field;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Now adjust image resolutions supported */
	अगर (pixfmt->field == V4L2_FIELD_INTERLACED ||
	    pixfmt->field == V4L2_FIELD_SEQ_TB)
		min_height = 2;

	max_width = vpfe_dev->std_info.active_pixels;
	max_height = vpfe_dev->std_info.active_lines;
	min_width /= vpfe_pix_fmt->bpp;

	v4l2_info(&vpfe_dev->v4l2_dev, "width = %d, height = %d, bpp = %d\n",
		  pixfmt->width, pixfmt->height, vpfe_pix_fmt->bpp);

	pixfmt->width = clamp((pixfmt->width), min_width, max_width);
	pixfmt->height = clamp((pixfmt->height), min_height, max_height);

	/* If पूर्णांकerlaced, adjust height to be a multiple of 2 */
	अगर (pixfmt->field == V4L2_FIELD_INTERLACED)
		pixfmt->height &= (~1);
	/*
	 * recalculate bytesperline and sizeimage since width
	 * and height might have changed
	 */
	pixfmt->bytesperline = (((pixfmt->width * vpfe_pix_fmt->bpp) + 31)
				& ~31);
	अगर (pixfmt->pixelक्रमmat == V4L2_PIX_FMT_NV12)
		pixfmt->sizeimage =
			pixfmt->bytesperline * pixfmt->height +
			((pixfmt->bytesperline * pixfmt->height) >> 1);
	अन्यथा
		pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;

	v4l2_info(&vpfe_dev->v4l2_dev, "adjusted width = %d, height = %d, bpp = %d, bytesperline = %d, sizeimage = %d\n",
		 pixfmt->width, pixfmt->height, vpfe_pix_fmt->bpp,
		 pixfmt->bytesperline, pixfmt->sizeimage);
	वापस vpfe_pix_fmt;
पूर्ण

अटल पूर्णांक vpfe_querycap(काष्ठा file *file, व्योम  *priv,
			       काष्ठा v4l2_capability *cap)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_querycap\n");

	strscpy(cap->driver, CAPTURE_DRV_NAME, माप(cap->driver));
	strscpy(cap->bus_info, "VPFE", माप(cap->bus_info));
	strscpy(cap->card, vpfe_dev->cfg->card_name, माप(cap->card));
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_g_fmt_vid_cap\n");
	/* Fill in the inक्रमmation about क्रमmat */
	*fmt = vpfe_dev->fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
				   काष्ठा v4l2_fmtdesc *fmt)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	स्थिर काष्ठा vpfe_pixel_क्रमmat *pix_fmt;
	u32 pix;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_enum_fmt_vid_cap\n");

	अगर (ccdc_dev->hw_ops.क्रमागत_pix(&pix, fmt->index) < 0)
		वापस -EINVAL;

	/* Fill in the inक्रमmation about क्रमmat */
	pix_fmt = vpfe_lookup_pix_क्रमmat(pix);
	अगर (pix_fmt) अणु
		fmt->pixelक्रमmat = pix_fmt->pixelक्रमmat;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vpfe_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	स्थिर काष्ठा vpfe_pixel_क्रमmat *pix_fmts;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_fmt_vid_cap\n");

	/* If streaming is started, वापस error */
	अगर (vpfe_dev->started) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Streaming is started\n");
		वापस -EBUSY;
	पूर्ण

	/* Check क्रम valid frame क्रमmat */
	pix_fmts = vpfe_check_क्रमmat(vpfe_dev, &fmt->fmt.pix);
	अगर (!pix_fmts)
		वापस -EINVAL;

	/* store the pixel क्रमmat in the device  object */
	ret = mutex_lock_पूर्णांकerruptible(&vpfe_dev->lock);
	अगर (ret)
		वापस ret;

	/* First detach any IRQ अगर currently attached */
	vpfe_detach_irq(vpfe_dev);
	vpfe_dev->fmt = *fmt;
	/* set image capture parameters in the ccdc */
	ret = vpfe_config_ccdc_image_क्रमmat(vpfe_dev);
	mutex_unlock(&vpfe_dev->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vpfe_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	स्थिर काष्ठा vpfe_pixel_क्रमmat *pix_fmts;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_try_fmt_vid_cap\n");

	pix_fmts = vpfe_check_क्रमmat(vpfe_dev, &f->fmt.pix);
	अगर (!pix_fmts)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * vpfe_get_subdev_input_index - Get subdev index and subdev input index क्रम a
 * given app input index
 */
अटल पूर्णांक vpfe_get_subdev_input_index(काष्ठा vpfe_device *vpfe_dev,
					पूर्णांक *subdev_index,
					पूर्णांक *subdev_input_index,
					पूर्णांक app_input_index)
अणु
	काष्ठा vpfe_config *cfg = vpfe_dev->cfg;
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < cfg->num_subdevs; i++) अणु
		sdinfo = &cfg->sub_devs[i];
		अगर (app_input_index < (j + sdinfo->num_inमाला_दो)) अणु
			*subdev_index = i;
			*subdev_input_index = app_input_index - j;
			वापस 0;
		पूर्ण
		j += sdinfo->num_inमाला_दो;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * vpfe_get_app_input - Get app input index क्रम a given subdev input index
 * driver stores the input index of the current sub device and translate it
 * when application request the current input
 */
अटल पूर्णांक vpfe_get_app_input_index(काष्ठा vpfe_device *vpfe_dev,
				    पूर्णांक *app_input_index)
अणु
	काष्ठा vpfe_config *cfg = vpfe_dev->cfg;
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < cfg->num_subdevs; i++) अणु
		sdinfo = &cfg->sub_devs[i];
		अगर (!म_भेद(sdinfo->name, vpfe_dev->current_subdev->name)) अणु
			अगर (vpfe_dev->current_input >= sdinfo->num_inमाला_दो)
				वापस -1;
			*app_input_index = j + vpfe_dev->current_input;
			वापस 0;
		पूर्ण
		j += sdinfo->num_inमाला_दो;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vpfe_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_input *inp)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक subdev, index ;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_enum_input\n");

	अगर (vpfe_get_subdev_input_index(vpfe_dev,
					&subdev,
					&index,
					inp->index) < 0) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "input information not found for the subdev\n");
		वापस -EINVAL;
	पूर्ण
	sdinfo = &vpfe_dev->cfg->sub_devs[subdev];
	*inp = sdinfo->inमाला_दो[index];
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *index)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_g_input\n");

	वापस vpfe_get_app_input_index(vpfe_dev, index);
पूर्ण


अटल पूर्णांक vpfe_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक index)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा v4l2_subdev *sd;
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक subdev_index, inp_index;
	काष्ठा vpfe_route *route;
	u32 input, output;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_input\n");

	ret = mutex_lock_पूर्णांकerruptible(&vpfe_dev->lock);
	अगर (ret)
		वापस ret;

	/*
	 * If streaming is started वापस device busy
	 * error
	 */
	अगर (vpfe_dev->started) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Streaming is on\n");
		ret = -EBUSY;
		जाओ unlock_out;
	पूर्ण
	ret = vpfe_get_subdev_input_index(vpfe_dev,
					  &subdev_index,
					  &inp_index,
					  index);
	अगर (ret < 0) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "invalid input index\n");
		जाओ unlock_out;
	पूर्ण

	sdinfo = &vpfe_dev->cfg->sub_devs[subdev_index];
	sd = vpfe_dev->sd[subdev_index];
	route = &sdinfo->routes[inp_index];
	अगर (route && sdinfo->can_route) अणु
		input = route->input;
		output = route->output;
	पूर्ण अन्यथा अणु
		input = 0;
		output = 0;
	पूर्ण

	अगर (sd)
		ret = v4l2_subdev_call(sd, video, s_routing, input, output, 0);

	अगर (ret) अणु
		v4l2_err(&vpfe_dev->v4l2_dev,
			"vpfe_doioctl:error in setting input in decoder\n");
		ret = -EINVAL;
		जाओ unlock_out;
	पूर्ण
	vpfe_dev->current_subdev = sdinfo;
	अगर (sd)
		vpfe_dev->v4l2_dev.ctrl_handler = sd->ctrl_handler;
	vpfe_dev->current_input = index;
	vpfe_dev->std_index = 0;

	/* set the bus/पूर्णांकerface parameter क्रम the sub device in ccdc */
	ret = ccdc_dev->hw_ops.set_hw_अगर_params(&sdinfo->ccdc_अगर_params);
	अगर (ret)
		जाओ unlock_out;

	/* set the शेष image parameters in the device */
	ret = vpfe_config_image_क्रमmat(vpfe_dev,
				vpfe_standards[vpfe_dev->std_index].std_id);
unlock_out:
	mutex_unlock(&vpfe_dev->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vpfe_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std_id)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_querystd\n");

	ret = mutex_lock_पूर्णांकerruptible(&vpfe_dev->lock);
	sdinfo = vpfe_dev->current_subdev;
	अगर (ret)
		वापस ret;
	/* Call querystd function of decoder device */
	ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev, sdinfo->grp_id,
					 video, querystd, std_id);
	mutex_unlock(&vpfe_dev->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vpfe_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std_id)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_std\n");

	/* Call decoder driver function to set the standard */
	ret = mutex_lock_पूर्णांकerruptible(&vpfe_dev->lock);
	अगर (ret)
		वापस ret;

	sdinfo = vpfe_dev->current_subdev;
	/* If streaming is started, वापस device busy error */
	अगर (vpfe_dev->started) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "streaming is started\n");
		ret = -EBUSY;
		जाओ unlock_out;
	पूर्ण

	ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev, sdinfo->grp_id,
					 video, s_std, std_id);
	अगर (ret < 0) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Failed to set standard\n");
		जाओ unlock_out;
	पूर्ण
	ret = vpfe_config_image_क्रमmat(vpfe_dev, std_id);

unlock_out:
	mutex_unlock(&vpfe_dev->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vpfe_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *std_id)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_g_std\n");

	*std_id = vpfe_standards[vpfe_dev->std_index].std_id;
	वापस 0;
पूर्ण
/*
 *  Videobuf operations
 */
अटल पूर्णांक vpfe_videobuf_setup(काष्ठा videobuf_queue *vq,
				अचिन्हित पूर्णांक *count,
				अचिन्हित पूर्णांक *size)
अणु
	काष्ठा vpfe_fh *fh = vq->priv_data;
	काष्ठा vpfe_device *vpfe_dev = fh->vpfe_dev;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_buffer_setup\n");
	*size = vpfe_dev->fmt.fmt.pix.sizeimage;
	अगर (vpfe_dev->memory == V4L2_MEMORY_MMAP &&
		vpfe_dev->fmt.fmt.pix.sizeimage > config_params.device_bufsize)
		*size = config_params.device_bufsize;

	अगर (*count < config_params.min_numbuffers)
		*count = config_params.min_numbuffers;
	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev,
		"count=%d, size=%d\n", *count, *size);
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_videobuf_prepare(काष्ठा videobuf_queue *vq,
				काष्ठा videobuf_buffer *vb,
				क्रमागत v4l2_field field)
अणु
	काष्ठा vpfe_fh *fh = vq->priv_data;
	काष्ठा vpfe_device *vpfe_dev = fh->vpfe_dev;
	अचिन्हित दीर्घ addr;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_buffer_prepare\n");

	/* If buffer is not initialized, initialize it */
	अगर (VIDEOBUF_NEEDS_INIT == vb->state) अणु
		vb->width = vpfe_dev->fmt.fmt.pix.width;
		vb->height = vpfe_dev->fmt.fmt.pix.height;
		vb->size = vpfe_dev->fmt.fmt.pix.sizeimage;
		vb->field = field;

		ret = videobuf_iolock(vq, vb, शून्य);
		अगर (ret < 0)
			वापस ret;

		addr = videobuf_to_dma_contig(vb);
		/* Make sure user addresses are aligned to 32 bytes */
		अगर (!ALIGN(addr, 32))
			वापस -EINVAL;

		vb->state = VIDEOBUF_PREPARED;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vpfe_videobuf_queue(काष्ठा videobuf_queue *vq,
				काष्ठा videobuf_buffer *vb)
अणु
	/* Get the file handle object and device object */
	काष्ठा vpfe_fh *fh = vq->priv_data;
	काष्ठा vpfe_device *vpfe_dev = fh->vpfe_dev;
	अचिन्हित दीर्घ flags;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_buffer_queue\n");

	/* add the buffer to the DMA queue */
	spin_lock_irqsave(&vpfe_dev->dma_queue_lock, flags);
	list_add_tail(&vb->queue, &vpfe_dev->dma_queue);
	spin_unlock_irqrestore(&vpfe_dev->dma_queue_lock, flags);

	/* Change state of the buffer */
	vb->state = VIDEOBUF_QUEUED;
पूर्ण

अटल व्योम vpfe_videobuf_release(काष्ठा videobuf_queue *vq,
				  काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा vpfe_fh *fh = vq->priv_data;
	काष्ठा vpfe_device *vpfe_dev = fh->vpfe_dev;
	अचिन्हित दीर्घ flags;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_videobuf_release\n");

	/*
	 * We need to flush the buffer from the dma queue since
	 * they are de-allocated
	 */
	spin_lock_irqsave(&vpfe_dev->dma_queue_lock, flags);
	INIT_LIST_HEAD(&vpfe_dev->dma_queue);
	spin_unlock_irqrestore(&vpfe_dev->dma_queue_lock, flags);
	videobuf_dma_contig_मुक्त(vq, vb);
	vb->state = VIDEOBUF_NEEDS_INIT;
पूर्ण

अटल स्थिर काष्ठा videobuf_queue_ops vpfe_videobuf_qops = अणु
	.buf_setup      = vpfe_videobuf_setup,
	.buf_prepare    = vpfe_videobuf_prepare,
	.buf_queue      = vpfe_videobuf_queue,
	.buf_release    = vpfe_videobuf_release,
पूर्ण;

/*
 * vpfe_reqbufs. currently support REQBUF only once खोलोing
 * the device.
 */
अटल पूर्णांक vpfe_reqbufs(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_requestbuffers *req_buf)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा vpfe_fh *fh = file->निजी_data;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_reqbufs\n");

	अगर (V4L2_BUF_TYPE_VIDEO_CAPTURE != req_buf->type) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buffer type\n");
		वापस -EINVAL;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&vpfe_dev->lock);
	अगर (ret)
		वापस ret;

	अगर (vpfe_dev->io_usrs != 0) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Only one IO user allowed\n");
		ret = -EBUSY;
		जाओ unlock_out;
	पूर्ण

	vpfe_dev->memory = req_buf->memory;
	videobuf_queue_dma_contig_init(&vpfe_dev->buffer_queue,
				&vpfe_videobuf_qops,
				vpfe_dev->pdev,
				&vpfe_dev->irqlock,
				req_buf->type,
				vpfe_dev->fmt.fmt.pix.field,
				माप(काष्ठा videobuf_buffer),
				fh, शून्य);

	fh->io_allowed = 1;
	vpfe_dev->io_usrs = 1;
	INIT_LIST_HEAD(&vpfe_dev->dma_queue);
	ret = videobuf_reqbufs(&vpfe_dev->buffer_queue, req_buf);
unlock_out:
	mutex_unlock(&vpfe_dev->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vpfe_querybuf(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_querybuf\n");

	अगर (V4L2_BUF_TYPE_VIDEO_CAPTURE != buf->type) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buf type\n");
		वापस  -EINVAL;
	पूर्ण

	अगर (vpfe_dev->memory != V4L2_MEMORY_MMAP) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid memory\n");
		वापस -EINVAL;
	पूर्ण
	/* Call videobuf_querybuf to get inक्रमmation */
	वापस videobuf_querybuf(&vpfe_dev->buffer_queue, buf);
पूर्ण

अटल पूर्णांक vpfe_qbuf(काष्ठा file *file, व्योम *priv,
		     काष्ठा v4l2_buffer *p)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा vpfe_fh *fh = file->निजी_data;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_qbuf\n");

	अगर (V4L2_BUF_TYPE_VIDEO_CAPTURE != p->type) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buf type\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * If this file handle is not allowed to करो IO,
	 * वापस error
	 */
	अगर (!fh->io_allowed) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "fh->io_allowed\n");
		वापस -EACCES;
	पूर्ण
	वापस videobuf_qbuf(&vpfe_dev->buffer_queue, p);
पूर्ण

अटल पूर्णांक vpfe_dqbuf(काष्ठा file *file, व्योम *priv,
		      काष्ठा v4l2_buffer *buf)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_dqbuf\n");

	अगर (V4L2_BUF_TYPE_VIDEO_CAPTURE != buf->type) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buf type\n");
		वापस -EINVAL;
	पूर्ण
	वापस videobuf_dqbuf(&vpfe_dev->buffer_queue,
				      buf, file->f_flags & O_NONBLOCK);
पूर्ण

/*
 * vpfe_calculate_offsets : This function calculates buffers offset
 * क्रम top and bottom field
 */
अटल व्योम vpfe_calculate_offsets(काष्ठा vpfe_device *vpfe_dev)
अणु
	काष्ठा v4l2_rect image_win;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_calculate_offsets\n");

	ccdc_dev->hw_ops.get_image_winकरोw(&image_win);
	vpfe_dev->field_off = image_win.height * image_win.width;
पूर्ण

/* vpfe_start_ccdc_capture: start streaming in ccdc/isअगर */
अटल व्योम vpfe_start_ccdc_capture(काष्ठा vpfe_device *vpfe_dev)
अणु
	ccdc_dev->hw_ops.enable(1);
	अगर (ccdc_dev->hw_ops.enable_out_to_sdram)
		ccdc_dev->hw_ops.enable_out_to_sdram(1);
	vpfe_dev->started = 1;
पूर्ण

/*
 * vpfe_streamon. Assume the DMA queue is not empty.
 * application is expected to call QBUF beक्रमe calling
 * this ioctl. If not, driver वापसs error
 */
अटल पूर्णांक vpfe_streamon(काष्ठा file *file, व्योम *priv,
			 क्रमागत v4l2_buf_type buf_type)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा vpfe_fh *fh = file->निजी_data;
	काष्ठा vpfe_subdev_info *sdinfo;
	अचिन्हित दीर्घ addr;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_streamon\n");

	अगर (V4L2_BUF_TYPE_VIDEO_CAPTURE != buf_type) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buf type\n");
		वापस -EINVAL;
	पूर्ण

	/* If file handle is not allowed IO, वापस error */
	अगर (!fh->io_allowed) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "fh->io_allowed\n");
		वापस -EACCES;
	पूर्ण

	sdinfo = vpfe_dev->current_subdev;
	ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev, sdinfo->grp_id,
					video, s_stream, 1);

	अगर (ret && (ret != -ENOIOCTLCMD)) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "stream on failed in subdev\n");
		वापस -EINVAL;
	पूर्ण

	/* If buffer queue is empty, वापस error */
	अगर (list_empty(&vpfe_dev->buffer_queue.stream)) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "buffer queue is empty\n");
		वापस -EIO;
	पूर्ण

	/* Call videobuf_streamon to start streaming * in videobuf */
	ret = videobuf_streamon(&vpfe_dev->buffer_queue);
	अगर (ret)
		वापस ret;


	ret = mutex_lock_पूर्णांकerruptible(&vpfe_dev->lock);
	अगर (ret)
		जाओ streamoff;
	/* Get the next frame from the buffer queue */
	vpfe_dev->next_frm = list_entry(vpfe_dev->dma_queue.next,
					काष्ठा videobuf_buffer, queue);
	vpfe_dev->cur_frm = vpfe_dev->next_frm;
	/* Remove buffer from the buffer queue */
	list_del(&vpfe_dev->cur_frm->queue);
	/* Mark state of the current frame to active */
	vpfe_dev->cur_frm->state = VIDEOBUF_ACTIVE;
	/* Initialize field_id and started member */
	vpfe_dev->field_id = 0;
	addr = videobuf_to_dma_contig(vpfe_dev->cur_frm);

	/* Calculate field offset */
	vpfe_calculate_offsets(vpfe_dev);

	अगर (vpfe_attach_irq(vpfe_dev) < 0) अणु
		v4l2_err(&vpfe_dev->v4l2_dev,
			 "Error in attaching interrupt handle\n");
		ret = -EFAULT;
		जाओ unlock_out;
	पूर्ण
	अगर (ccdc_dev->hw_ops.configure() < 0) अणु
		v4l2_err(&vpfe_dev->v4l2_dev,
			 "Error in configuring ccdc\n");
		ret = -EINVAL;
		जाओ unlock_out;
	पूर्ण
	ccdc_dev->hw_ops.setfbaddr((अचिन्हित दीर्घ)(addr));
	vpfe_start_ccdc_capture(vpfe_dev);
	mutex_unlock(&vpfe_dev->lock);
	वापस ret;
unlock_out:
	mutex_unlock(&vpfe_dev->lock);
streamoff:
	videobuf_streamoff(&vpfe_dev->buffer_queue);
	वापस ret;
पूर्ण

अटल पूर्णांक vpfe_streamoff(काष्ठा file *file, व्योम *priv,
			  क्रमागत v4l2_buf_type buf_type)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा vpfe_fh *fh = file->निजी_data;
	काष्ठा vpfe_subdev_info *sdinfo;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_streamoff\n");

	अगर (V4L2_BUF_TYPE_VIDEO_CAPTURE != buf_type) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buf type\n");
		वापस -EINVAL;
	पूर्ण

	/* If io is allowed क्रम this file handle, वापस error */
	अगर (!fh->io_allowed) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "fh->io_allowed\n");
		वापस -EACCES;
	पूर्ण

	/* If streaming is not started, वापस error */
	अगर (!vpfe_dev->started) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "device started\n");
		वापस -EINVAL;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&vpfe_dev->lock);
	अगर (ret)
		वापस ret;

	vpfe_stop_ccdc_capture(vpfe_dev);
	vpfe_detach_irq(vpfe_dev);

	sdinfo = vpfe_dev->current_subdev;
	ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev, sdinfo->grp_id,
					video, s_stream, 0);

	अगर (ret && (ret != -ENOIOCTLCMD))
		v4l2_err(&vpfe_dev->v4l2_dev, "stream off failed in subdev\n");
	ret = videobuf_streamoff(&vpfe_dev->buffer_queue);
	mutex_unlock(&vpfe_dev->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vpfe_g_pixelaspect(काष्ठा file *file, व्योम *priv,
			      पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_g_pixelaspect\n");

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	/* If std_index is invalid, then just वापस (== 1:1 aspect) */
	अगर (vpfe_dev->std_index >= ARRAY_SIZE(vpfe_standards))
		वापस 0;

	*f = vpfe_standards[vpfe_dev->std_index].pixelaspect;
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_g_selection(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_selection *sel)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_g_selection\n");

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		sel->r = vpfe_dev->crop;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.width = vpfe_standards[vpfe_dev->std_index].width;
		sel->r.height = vpfe_standards[vpfe_dev->std_index].height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_s_selection(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_selection *sel)
अणु
	काष्ठा vpfe_device *vpfe_dev = video_drvdata(file);
	काष्ठा v4l2_rect rect = sel->r;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_selection\n");

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	अगर (vpfe_dev->started) अणु
		/* make sure streaming is not started */
		v4l2_err(&vpfe_dev->v4l2_dev,
			"Cannot change crop when streaming is ON\n");
		वापस -EBUSY;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&vpfe_dev->lock);
	अगर (ret)
		वापस ret;

	अगर (rect.top < 0 || rect.left < 0) अणु
		v4l2_err(&vpfe_dev->v4l2_dev,
			"doesn't support negative values for top & left\n");
		ret = -EINVAL;
		जाओ unlock_out;
	पूर्ण

	/* adjust the width to 16 pixel boundary */
	rect.width = ((rect.width + 15) & ~0xf);

	/* make sure parameters are valid */
	अगर ((rect.left + rect.width >
		vpfe_dev->std_info.active_pixels) ||
	    (rect.top + rect.height >
		vpfe_dev->std_info.active_lines)) अणु
		v4l2_err(&vpfe_dev->v4l2_dev, "Error in S_SELECTION params\n");
		ret = -EINVAL;
		जाओ unlock_out;
	पूर्ण
	ccdc_dev->hw_ops.set_image_winकरोw(&rect);
	vpfe_dev->fmt.fmt.pix.width = rect.width;
	vpfe_dev->fmt.fmt.pix.height = rect.height;
	vpfe_dev->fmt.fmt.pix.bytesperline =
		ccdc_dev->hw_ops.get_line_length();
	vpfe_dev->fmt.fmt.pix.sizeimage =
		vpfe_dev->fmt.fmt.pix.bytesperline *
		vpfe_dev->fmt.fmt.pix.height;
	vpfe_dev->crop = rect;
	sel->r = rect;
unlock_out:
	mutex_unlock(&vpfe_dev->lock);
	वापस ret;
पूर्ण

/* vpfe capture ioctl operations */
अटल स्थिर काष्ठा v4l2_ioctl_ops vpfe_ioctl_ops = अणु
	.vidioc_querycap	 = vpfe_querycap,
	.vidioc_g_fmt_vid_cap    = vpfe_g_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_cap = vpfe_क्रमागत_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap    = vpfe_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap  = vpfe_try_fmt_vid_cap,
	.vidioc_क्रमागत_input	 = vpfe_क्रमागत_input,
	.vidioc_g_input		 = vpfe_g_input,
	.vidioc_s_input		 = vpfe_s_input,
	.vidioc_querystd	 = vpfe_querystd,
	.vidioc_s_std		 = vpfe_s_std,
	.vidioc_g_std		 = vpfe_g_std,
	.vidioc_reqbufs		 = vpfe_reqbufs,
	.vidioc_querybuf	 = vpfe_querybuf,
	.vidioc_qbuf		 = vpfe_qbuf,
	.vidioc_dqbuf		 = vpfe_dqbuf,
	.vidioc_streamon	 = vpfe_streamon,
	.vidioc_streamoff	 = vpfe_streamoff,
	.vidioc_g_pixelaspect	 = vpfe_g_pixelaspect,
	.vidioc_g_selection	 = vpfe_g_selection,
	.vidioc_s_selection	 = vpfe_s_selection,
पूर्ण;

अटल काष्ठा vpfe_device *vpfe_initialize(व्योम)
अणु
	काष्ठा vpfe_device *vpfe_dev;

	/* Default number of buffers should be 3 */
	अगर ((numbuffers > 0) &&
	    (numbuffers < config_params.min_numbuffers))
		numbuffers = config_params.min_numbuffers;

	/*
	 * Set buffer size to min buffers size अगर invalid buffer size is
	 * given
	 */
	अगर (bufsize < config_params.min_bufsize)
		bufsize = config_params.min_bufsize;

	config_params.numbuffers = numbuffers;

	अगर (numbuffers)
		config_params.device_bufsize = bufsize;

	/* Allocate memory क्रम device objects */
	vpfe_dev = kzalloc(माप(*vpfe_dev), GFP_KERNEL);

	वापस vpfe_dev;
पूर्ण

/*
 * vpfe_probe : This function creates device entries by रेजिस्टर
 * itself to the V4L2 driver and initializes fields of each
 * device objects
 */
अटल पूर्णांक vpfe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpfe_subdev_info *sdinfo;
	काष्ठा vpfe_config *vpfe_cfg;
	काष्ठा resource *res1;
	काष्ठा vpfe_device *vpfe_dev;
	काष्ठा i2c_adapter *i2c_adap;
	काष्ठा video_device *vfd;
	पूर्णांक ret, i, j;
	पूर्णांक num_subdevs = 0;

	/* Get the poपूर्णांकer to the device object */
	vpfe_dev = vpfe_initialize();

	अगर (!vpfe_dev) अणु
		v4l2_err(pdev->dev.driver,
			"Failed to allocate memory for vpfe_dev\n");
		वापस -ENOMEM;
	पूर्ण

	vpfe_dev->pdev = &pdev->dev;

	अगर (!pdev->dev.platक्रमm_data) अणु
		v4l2_err(pdev->dev.driver, "Unable to get vpfe config\n");
		ret = -ENODEV;
		जाओ probe_मुक्त_dev_mem;
	पूर्ण

	vpfe_cfg = pdev->dev.platक्रमm_data;
	vpfe_dev->cfg = vpfe_cfg;
	अगर (!vpfe_cfg->ccdc || !vpfe_cfg->card_name || !vpfe_cfg->sub_devs) अणु
		v4l2_err(pdev->dev.driver, "null ptr in vpfe_cfg\n");
		ret = -ENOENT;
		जाओ probe_मुक्त_dev_mem;
	पूर्ण

	/* Allocate memory क्रम ccdc configuration */
	ccdc_cfg = kदो_स्मृति(माप(*ccdc_cfg), GFP_KERNEL);
	अगर (!ccdc_cfg) अणु
		ret = -ENOMEM;
		जाओ probe_मुक्त_dev_mem;
	पूर्ण

	mutex_lock(&ccdc_lock);

	strscpy(ccdc_cfg->name, vpfe_cfg->ccdc, माप(ccdc_cfg->name));
	/* Get VINT0 irq resource */
	res1 = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res1) अणु
		v4l2_err(pdev->dev.driver,
			 "Unable to get interrupt for VINT0\n");
		ret = -ENODEV;
		जाओ probe_मुक्त_ccdc_cfg_mem;
	पूर्ण
	vpfe_dev->ccdc_irq0 = res1->start;

	/* Get VINT1 irq resource */
	res1 = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 1);
	अगर (!res1) अणु
		v4l2_err(pdev->dev.driver,
			 "Unable to get interrupt for VINT1\n");
		ret = -ENODEV;
		जाओ probe_मुक्त_ccdc_cfg_mem;
	पूर्ण
	vpfe_dev->ccdc_irq1 = res1->start;

	ret = request_irq(vpfe_dev->ccdc_irq0, vpfe_isr, 0,
			  "vpfe_capture0", vpfe_dev);

	अगर (0 != ret) अणु
		v4l2_err(pdev->dev.driver, "Unable to request interrupt\n");
		जाओ probe_मुक्त_ccdc_cfg_mem;
	पूर्ण

	vfd = &vpfe_dev->video_dev;
	/* Initialize field of video device */
	vfd->release		= video_device_release_empty;
	vfd->fops		= &vpfe_fops;
	vfd->ioctl_ops		= &vpfe_ioctl_ops;
	vfd->tvnorms		= 0;
	vfd->v4l2_dev		= &vpfe_dev->v4l2_dev;
	vfd->device_caps	= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING;
	snम_लिखो(vfd->name, माप(vfd->name),
		 "%s_V%d.%d.%d",
		 CAPTURE_DRV_NAME,
		 (VPFE_CAPTURE_VERSION_CODE >> 16) & 0xff,
		 (VPFE_CAPTURE_VERSION_CODE >> 8) & 0xff,
		 (VPFE_CAPTURE_VERSION_CODE) & 0xff);

	ret = v4l2_device_रेजिस्टर(&pdev->dev, &vpfe_dev->v4l2_dev);
	अगर (ret) अणु
		v4l2_err(pdev->dev.driver,
			"Unable to register v4l2 device.\n");
		जाओ probe_out_release_irq;
	पूर्ण
	v4l2_info(&vpfe_dev->v4l2_dev, "v4l2 device registered\n");
	spin_lock_init(&vpfe_dev->irqlock);
	spin_lock_init(&vpfe_dev->dma_queue_lock);
	mutex_init(&vpfe_dev->lock);

	/* Initialize field of the device objects */
	vpfe_dev->numbuffers = config_params.numbuffers;

	/* रेजिस्टर video device */
	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev,
		"trying to register vpfe device.\n");
	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev,
		"video_dev=%p\n", &vpfe_dev->video_dev);
	vpfe_dev->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = video_रेजिस्टर_device(&vpfe_dev->video_dev,
				    VFL_TYPE_VIDEO, -1);

	अगर (ret) अणु
		v4l2_err(pdev->dev.driver,
			"Unable to register video device.\n");
		जाओ probe_out_v4l2_unरेजिस्टर;
	पूर्ण

	v4l2_info(&vpfe_dev->v4l2_dev, "video device registered\n");
	/* set the driver data in platक्रमm device */
	platक्रमm_set_drvdata(pdev, vpfe_dev);
	/* set driver निजी data */
	video_set_drvdata(&vpfe_dev->video_dev, vpfe_dev);
	i2c_adap = i2c_get_adapter(vpfe_cfg->i2c_adapter_id);
	num_subdevs = vpfe_cfg->num_subdevs;
	vpfe_dev->sd = kदो_स्मृति_array(num_subdevs,
				     माप(*vpfe_dev->sd),
				     GFP_KERNEL);
	अगर (!vpfe_dev->sd) अणु
		ret = -ENOMEM;
		जाओ probe_out_video_unरेजिस्टर;
	पूर्ण

	क्रम (i = 0; i < num_subdevs; i++) अणु
		काष्ठा v4l2_input *inps;

		sdinfo = &vpfe_cfg->sub_devs[i];

		/* Load up the subdevice */
		vpfe_dev->sd[i] =
			v4l2_i2c_new_subdev_board(&vpfe_dev->v4l2_dev,
						  i2c_adap,
						  &sdinfo->board_info,
						  शून्य);
		अगर (vpfe_dev->sd[i]) अणु
			v4l2_info(&vpfe_dev->v4l2_dev,
				  "v4l2 sub device %s registered\n",
				  sdinfo->name);
			vpfe_dev->sd[i]->grp_id = sdinfo->grp_id;
			/* update tvnorms from the sub devices */
			क्रम (j = 0; j < sdinfo->num_inमाला_दो; j++) अणु
				inps = &sdinfo->inमाला_दो[j];
				vfd->tvnorms |= inps->std;
			पूर्ण
		पूर्ण अन्यथा अणु
			v4l2_info(&vpfe_dev->v4l2_dev,
				  "v4l2 sub device %s register fails\n",
				  sdinfo->name);
			ret = -ENXIO;
			जाओ probe_sd_out;
		पूर्ण
	पूर्ण

	/* set first sub device as current one */
	vpfe_dev->current_subdev = &vpfe_cfg->sub_devs[0];
	vpfe_dev->v4l2_dev.ctrl_handler = vpfe_dev->sd[0]->ctrl_handler;

	/* We have at least one sub device to work with */
	mutex_unlock(&ccdc_lock);
	वापस 0;

probe_sd_out:
	kमुक्त(vpfe_dev->sd);
probe_out_video_unरेजिस्टर:
	video_unरेजिस्टर_device(&vpfe_dev->video_dev);
probe_out_v4l2_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&vpfe_dev->v4l2_dev);
probe_out_release_irq:
	मुक्त_irq(vpfe_dev->ccdc_irq0, vpfe_dev);
probe_मुक्त_ccdc_cfg_mem:
	kमुक्त(ccdc_cfg);
	mutex_unlock(&ccdc_lock);
probe_मुक्त_dev_mem:
	kमुक्त(vpfe_dev);
	वापस ret;
पूर्ण

/*
 * vpfe_हटाओ : It un-रेजिस्टर device from V4L2 driver
 */
अटल पूर्णांक vpfe_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpfe_device *vpfe_dev = platक्रमm_get_drvdata(pdev);

	v4l2_info(pdev->dev.driver, "vpfe_remove\n");

	मुक्त_irq(vpfe_dev->ccdc_irq0, vpfe_dev);
	kमुक्त(vpfe_dev->sd);
	v4l2_device_unरेजिस्टर(&vpfe_dev->v4l2_dev);
	video_unरेजिस्टर_device(&vpfe_dev->video_dev);
	kमुक्त(vpfe_dev);
	kमुक्त(ccdc_cfg);
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vpfe_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vpfe_dev_pm_ops = अणु
	.suspend = vpfe_suspend,
	.resume = vpfe_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver vpfe_driver = अणु
	.driver = अणु
		.name = CAPTURE_DRV_NAME,
		.pm = &vpfe_dev_pm_ops,
	पूर्ण,
	.probe = vpfe_probe,
	.हटाओ = vpfe_हटाओ,
पूर्ण;

module_platक्रमm_driver(vpfe_driver);
