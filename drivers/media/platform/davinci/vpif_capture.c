<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Texas Instruments Inc
 * Copyright (C) 2014 Lad, Prabhakar <prabhakar.csengg@gmail.com>
 *
 * TODO : add support क्रम VBI & HBI data service
 *	  add अटल buffer allocation
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/i2c/tvp514x.h>
#समावेश <media/v4l2-mediabus.h>

#समावेश <linux/videodev2.h>

#समावेश "vpif.h"
#समावेश "vpif_capture.h"

MODULE_DESCRIPTION("TI DaVinci VPIF Capture driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(VPIF_CAPTURE_VERSION);

#घोषणा vpअगर_err(fmt, arg...)	v4l2_err(&vpअगर_obj.v4l2_dev, fmt, ## arg)
#घोषणा vpअगर_dbg(level, debug, fmt, arg...)	\
		v4l2_dbg(level, debug, &vpअगर_obj.v4l2_dev, fmt, ## arg)

अटल पूर्णांक debug = 1;

module_param(debug, पूर्णांक, 0644);

MODULE_PARM_DESC(debug, "Debug level 0-1");

#घोषणा VPIF_DRIVER_NAME	"vpif_capture"
MODULE_ALIAS("platform:" VPIF_DRIVER_NAME);

/* global variables */
अटल काष्ठा vpअगर_device vpअगर_obj = अणु अणुशून्यपूर्ण पूर्ण;
अटल काष्ठा device *vpअगर_dev;
अटल व्योम vpअगर_calculate_offsets(काष्ठा channel_obj *ch);
अटल व्योम vpअगर_config_addr(काष्ठा channel_obj *ch, पूर्णांक muxmode);

अटल u8 channel_first_पूर्णांक[VPIF_NUMBER_OF_OBJECTS][2] = अणु अणु1, 1पूर्ण पूर्ण;

/* Is set to 1 in हाल of SDTV क्रमmats, 2 in हाल of HDTV क्रमmats. */
अटल पूर्णांक ycmux_mode;

अटल अंतरभूत
काष्ठा vpअगर_cap_buffer *to_vpअगर_buffer(काष्ठा vb2_v4l2_buffer *vb)
अणु
	वापस container_of(vb, काष्ठा vpअगर_cap_buffer, vb);
पूर्ण

/**
 * vpअगर_buffer_prepare :  callback function क्रम buffer prepare
 * @vb: ptr to vb2_buffer
 *
 * This is the callback function क्रम buffer prepare when vb2_qbuf()
 * function is called. The buffer is prepared and user space भव address
 * or user address is converted पूर्णांकo  physical address
 */
अटल पूर्णांक vpअगर_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vb2_queue *q = vb->vb2_queue;
	काष्ठा channel_obj *ch = vb2_get_drv_priv(q);
	काष्ठा common_obj *common;
	अचिन्हित दीर्घ addr;

	vpअगर_dbg(2, debug, "vpif_buffer_prepare\n");

	common = &ch->common[VPIF_VIDEO_INDEX];

	vb2_set_plane_payload(vb, 0, common->fmt.fmt.pix.sizeimage);
	अगर (vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0))
		वापस -EINVAL;

	vbuf->field = common->fmt.fmt.pix.field;

	addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	अगर (!IS_ALIGNED((addr + common->ytop_off), 8) ||
		!IS_ALIGNED((addr + common->ybपंचांग_off), 8) ||
		!IS_ALIGNED((addr + common->ctop_off), 8) ||
		!IS_ALIGNED((addr + common->cbपंचांग_off), 8)) अणु
		vpअगर_dbg(1, debug, "offset is not aligned\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vpअगर_buffer_queue_setup : Callback function क्रम buffer setup.
 * @vq: vb2_queue ptr
 * @nbuffers: ptr to number of buffers requested by application
 * @nplanes:: contains number of distinct video planes needed to hold a frame
 * @sizes: contains the size (in bytes) of each plane.
 * @alloc_devs: ptr to allocation context
 *
 * This callback function is called when reqbuf() is called to adjust
 * the buffer count and buffer size
 */
अटल पूर्णांक vpअगर_buffer_queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
				अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा channel_obj *ch = vb2_get_drv_priv(vq);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	अचिन्हित size = common->fmt.fmt.pix.sizeimage;

	vpअगर_dbg(2, debug, "vpif_buffer_setup\n");

	अगर (*nplanes) अणु
		अगर (sizes[0] < size)
			वापस -EINVAL;
		size = sizes[0];
	पूर्ण

	अगर (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	*nplanes = 1;
	sizes[0] = size;

	/* Calculate the offset क्रम Y and C data in the buffer */
	vpअगर_calculate_offsets(ch);

	वापस 0;
पूर्ण

/**
 * vpअगर_buffer_queue : Callback function to add buffer to DMA queue
 * @vb: ptr to vb2_buffer
 */
अटल व्योम vpअगर_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा channel_obj *ch = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vpअगर_cap_buffer *buf = to_vpअगर_buffer(vbuf);
	काष्ठा common_obj *common;
	अचिन्हित दीर्घ flags;

	common = &ch->common[VPIF_VIDEO_INDEX];

	vpअगर_dbg(2, debug, "vpif_buffer_queue\n");

	spin_lock_irqsave(&common->irqlock, flags);
	/* add the buffer to the DMA queue */
	list_add_tail(&buf->list, &common->dma_queue);
	spin_unlock_irqrestore(&common->irqlock, flags);
पूर्ण

/**
 * vpअगर_start_streaming : Starts the DMA engine क्रम streaming
 * @vq: ptr to vb2_buffer
 * @count: number of buffers
 */
अटल पूर्णांक vpअगर_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vpअगर_capture_config *vpअगर_config_data =
					vpअगर_dev->platक्रमm_data;
	काष्ठा channel_obj *ch = vb2_get_drv_priv(vq);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा vpअगर_params *vpअगर = &ch->vpअगरparams;
	काष्ठा vpअगर_cap_buffer *buf, *पंचांगp;
	अचिन्हित दीर्घ addr, flags;
	पूर्णांक ret;

	/* Initialize field_id */
	ch->field_id = 0;

	/* configure 1 or 2 channel mode */
	अगर (vpअगर_config_data->setup_input_channel_mode) अणु
		ret = vpअगर_config_data->
			setup_input_channel_mode(vpअगर->std_info.ycmux_mode);
		अगर (ret < 0) अणु
			vpअगर_dbg(1, debug, "can't set vpif channel mode\n");
			जाओ err;
		पूर्ण
	पूर्ण

	ret = v4l2_subdev_call(ch->sd, video, s_stream, 1);
	अगर (ret && ret != -ENOIOCTLCMD && ret != -ENODEV) अणु
		vpअगर_dbg(1, debug, "stream on failed in subdev\n");
		जाओ err;
	पूर्ण

	/* Call vpअगर_set_params function to set the parameters and addresses */
	ret = vpअगर_set_video_params(vpअगर, ch->channel_id);
	अगर (ret < 0) अणु
		vpअगर_dbg(1, debug, "can't set video params\n");
		जाओ err;
	पूर्ण

	ycmux_mode = ret;
	vpअगर_config_addr(ch, ret);

	/* Get the next frame from the buffer queue */
	spin_lock_irqsave(&common->irqlock, flags);
	common->cur_frm = common->next_frm = list_entry(common->dma_queue.next,
				    काष्ठा vpअगर_cap_buffer, list);
	/* Remove buffer from the buffer queue */
	list_del(&common->cur_frm->list);
	spin_unlock_irqrestore(&common->irqlock, flags);

	addr = vb2_dma_contig_plane_dma_addr(&common->cur_frm->vb.vb2_buf, 0);

	common->set_addr(addr + common->ytop_off,
			 addr + common->ybपंचांग_off,
			 addr + common->ctop_off,
			 addr + common->cbपंचांग_off);

	/**
	 * Set पूर्णांकerrupt क्रम both the fields in VPIF Register enable channel in
	 * VPIF रेजिस्टर
	 */
	channel_first_पूर्णांक[VPIF_VIDEO_INDEX][ch->channel_id] = 1;
	अगर (VPIF_CHANNEL0_VIDEO == ch->channel_id) अणु
		channel0_पूर्णांकr_निश्चित();
		channel0_पूर्णांकr_enable(1);
		enable_channel0(1);
	पूर्ण
	अगर (VPIF_CHANNEL1_VIDEO == ch->channel_id ||
		ycmux_mode == 2) अणु
		channel1_पूर्णांकr_निश्चित();
		channel1_पूर्णांकr_enable(1);
		enable_channel1(1);
	पूर्ण

	वापस 0;

err:
	spin_lock_irqsave(&common->irqlock, flags);
	list_क्रम_each_entry_safe(buf, पंचांगp, &common->dma_queue, list) अणु
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	पूर्ण
	spin_unlock_irqrestore(&common->irqlock, flags);

	वापस ret;
पूर्ण

/**
 * vpअगर_stop_streaming : Stop the DMA engine
 * @vq: ptr to vb2_queue
 *
 * This callback stops the DMA engine and any reमुख्यing buffers
 * in the DMA queue are released.
 */
अटल व्योम vpअगर_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा channel_obj *ch = vb2_get_drv_priv(vq);
	काष्ठा common_obj *common;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	common = &ch->common[VPIF_VIDEO_INDEX];

	/* Disable channel as per its device type and channel id */
	अगर (VPIF_CHANNEL0_VIDEO == ch->channel_id) अणु
		enable_channel0(0);
		channel0_पूर्णांकr_enable(0);
	पूर्ण
	अगर (VPIF_CHANNEL1_VIDEO == ch->channel_id ||
		ycmux_mode == 2) अणु
		enable_channel1(0);
		channel1_पूर्णांकr_enable(0);
	पूर्ण

	ycmux_mode = 0;

	ret = v4l2_subdev_call(ch->sd, video, s_stream, 0);
	अगर (ret && ret != -ENOIOCTLCMD && ret != -ENODEV)
		vpअगर_dbg(1, debug, "stream off failed in subdev\n");

	/* release all active buffers */
	अगर (common->cur_frm == common->next_frm) अणु
		vb2_buffer_करोne(&common->cur_frm->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
	पूर्ण अन्यथा अणु
		अगर (common->cur_frm)
			vb2_buffer_करोne(&common->cur_frm->vb.vb2_buf,
					VB2_BUF_STATE_ERROR);
		अगर (common->next_frm)
			vb2_buffer_करोne(&common->next_frm->vb.vb2_buf,
					VB2_BUF_STATE_ERROR);
	पूर्ण

	spin_lock_irqsave(&common->irqlock, flags);
	जबतक (!list_empty(&common->dma_queue)) अणु
		common->next_frm = list_entry(common->dma_queue.next,
						काष्ठा vpअगर_cap_buffer, list);
		list_del(&common->next_frm->list);
		vb2_buffer_करोne(&common->next_frm->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&common->irqlock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops video_qops = अणु
	.queue_setup		= vpअगर_buffer_queue_setup,
	.buf_prepare		= vpअगर_buffer_prepare,
	.start_streaming	= vpअगर_start_streaming,
	.stop_streaming		= vpअगर_stop_streaming,
	.buf_queue		= vpअगर_buffer_queue,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/**
 * vpअगर_process_buffer_complete: process a completed buffer
 * @common: ptr to common channel object
 *
 * This function समय stamp the buffer and mark it as DONE. It also
 * wake up any process रुकोing on the QUEUE and set the next buffer
 * as current
 */
अटल व्योम vpअगर_process_buffer_complete(काष्ठा common_obj *common)
अणु
	common->cur_frm->vb.vb2_buf.बारtamp = kसमय_get_ns();
	vb2_buffer_करोne(&common->cur_frm->vb.vb2_buf, VB2_BUF_STATE_DONE);
	/* Make curFrm poपूर्णांकing to nextFrm */
	common->cur_frm = common->next_frm;
पूर्ण

/**
 * vpअगर_schedule_next_buffer: set next buffer address क्रम capture
 * @common : ptr to common channel object
 *
 * This function will get next buffer from the dma queue and
 * set the buffer address in the vpअगर रेजिस्टर क्रम capture.
 * the buffer is marked active
 */
अटल व्योम vpअगर_schedule_next_buffer(काष्ठा common_obj *common)
अणु
	अचिन्हित दीर्घ addr = 0;

	spin_lock(&common->irqlock);
	common->next_frm = list_entry(common->dma_queue.next,
				     काष्ठा vpअगर_cap_buffer, list);
	/* Remove that buffer from the buffer queue */
	list_del(&common->next_frm->list);
	spin_unlock(&common->irqlock);
	addr = vb2_dma_contig_plane_dma_addr(&common->next_frm->vb.vb2_buf, 0);

	/* Set top and bottom field addresses in VPIF रेजिस्टरs */
	common->set_addr(addr + common->ytop_off,
			 addr + common->ybपंचांग_off,
			 addr + common->ctop_off,
			 addr + common->cbपंचांग_off);
पूर्ण

/**
 * vpअगर_channel_isr : ISR handler क्रम vpअगर capture
 * @irq: irq number
 * @dev_id: dev_id ptr
 *
 * It changes status of the captured buffer, takes next buffer from the queue
 * and sets its address in VPIF रेजिस्टरs
 */
अटल irqवापस_t vpअगर_channel_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vpअगर_device *dev = &vpअगर_obj;
	काष्ठा common_obj *common;
	काष्ठा channel_obj *ch;
	पूर्णांक channel_id;
	पूर्णांक fid = -1, i;

	channel_id = *(पूर्णांक *)(dev_id);
	अगर (!vpअगर_पूर्णांकr_status(channel_id))
		वापस IRQ_NONE;

	ch = dev->dev[channel_id];

	क्रम (i = 0; i < VPIF_NUMBER_OF_OBJECTS; i++) अणु
		common = &ch->common[i];
		/* skip If streaming is not started in this channel */
		/* Check the field क्रमmat */
		अगर (1 == ch->vpअगरparams.std_info.frm_fmt ||
		    common->fmt.fmt.pix.field == V4L2_FIELD_NONE) अणु
			/* Progressive mode */
			spin_lock(&common->irqlock);
			अगर (list_empty(&common->dma_queue)) अणु
				spin_unlock(&common->irqlock);
				जारी;
			पूर्ण
			spin_unlock(&common->irqlock);

			अगर (!channel_first_पूर्णांक[i][channel_id])
				vpअगर_process_buffer_complete(common);

			channel_first_पूर्णांक[i][channel_id] = 0;

			vpअगर_schedule_next_buffer(common);


			channel_first_पूर्णांक[i][channel_id] = 0;
		पूर्ण अन्यथा अणु
			/**
			 * Interlaced mode. If it is first पूर्णांकerrupt, ignore
			 * it
			 */
			अगर (channel_first_पूर्णांक[i][channel_id]) अणु
				channel_first_पूर्णांक[i][channel_id] = 0;
				जारी;
			पूर्ण
			अगर (0 == i) अणु
				ch->field_id ^= 1;
				/* Get field id from VPIF रेजिस्टरs */
				fid = vpअगर_channel_getfid(ch->channel_id);
				अगर (fid != ch->field_id) अणु
					/**
					 * If field id करोes not match stored
					 * field id, make them in sync
					 */
					अगर (0 == fid)
						ch->field_id = fid;
					वापस IRQ_HANDLED;
				पूर्ण
			पूर्ण
			/* device field id and local field id are in sync */
			अगर (0 == fid) अणु
				/* this is even field */
				अगर (common->cur_frm == common->next_frm)
					जारी;

				/* mark the current buffer as करोne */
				vpअगर_process_buffer_complete(common);
			पूर्ण अन्यथा अगर (1 == fid) अणु
				/* odd field */
				spin_lock(&common->irqlock);
				अगर (list_empty(&common->dma_queue) ||
				    (common->cur_frm != common->next_frm)) अणु
					spin_unlock(&common->irqlock);
					जारी;
				पूर्ण
				spin_unlock(&common->irqlock);

				vpअगर_schedule_next_buffer(common);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/**
 * vpअगर_update_std_info() - update standard related info
 * @ch: ptr to channel object
 *
 * For a given standard selected by application, update values
 * in the device data काष्ठाures
 */
अटल पूर्णांक vpअगर_update_std_info(काष्ठा channel_obj *ch)
अणु
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा vpअगर_params *vpअगरparams = &ch->vpअगरparams;
	स्थिर काष्ठा vpअगर_channel_config_params *config;
	काष्ठा vpअगर_channel_config_params *std_info = &vpअगरparams->std_info;
	काष्ठा video_obj *vid_ch = &ch->video;
	पूर्णांक index;
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &common->fmt.fmt.pix;

	vpअगर_dbg(2, debug, "vpif_update_std_info\n");

	/*
	 * अगर called after try_fmt or g_fmt, there will alपढ़ोy be a size
	 * so use that by शेष.
	 */
	अगर (pixfmt->width && pixfmt->height) अणु
		अगर (pixfmt->field == V4L2_FIELD_ANY ||
		    pixfmt->field == V4L2_FIELD_NONE)
			pixfmt->field = V4L2_FIELD_NONE;

		vpअगरparams->अगरace.अगर_type = VPIF_IF_BT656;
		अगर (pixfmt->pixelक्रमmat == V4L2_PIX_FMT_SGRBG10 ||
		    pixfmt->pixelक्रमmat == V4L2_PIX_FMT_SBGGR8)
			vpअगरparams->अगरace.अगर_type = VPIF_IF_RAW_BAYER;

		अगर (pixfmt->pixelक्रमmat == V4L2_PIX_FMT_SGRBG10)
			vpअगरparams->params.data_sz = 1; /* 10 bits/pixel.  */

		/*
		 * For raw क्रमmats from camera sensors, we करोn't need
		 * the std_info from table lookup, so nothing अन्यथा to करो here.
		 */
		अगर (vpअगरparams->अगरace.अगर_type == VPIF_IF_RAW_BAYER) अणु
			स_रखो(std_info, 0, माप(काष्ठा vpअगर_channel_config_params));
			vpअगरparams->std_info.capture_क्रमmat = 1; /* CCD/raw mode */
			वापस 0;
		पूर्ण
	पूर्ण

	क्रम (index = 0; index < vpअगर_ch_params_count; index++) अणु
		config = &vpअगर_ch_params[index];
		अगर (config->hd_sd == 0) अणु
			vpअगर_dbg(2, debug, "SD format\n");
			अगर (config->stdid & vid_ch->stdid) अणु
				स_नकल(std_info, config, माप(*config));
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			vpअगर_dbg(2, debug, "HD format\n");
			अगर (!स_भेद(&config->dv_timings, &vid_ch->dv_timings,
				माप(vid_ch->dv_timings))) अणु
				स_नकल(std_info, config, माप(*config));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* standard not found */
	अगर (index == vpअगर_ch_params_count)
		वापस -EINVAL;

	common->fmt.fmt.pix.width = std_info->width;
	common->width = std_info->width;
	common->fmt.fmt.pix.height = std_info->height;
	common->height = std_info->height;
	common->fmt.fmt.pix.sizeimage = common->height * common->width * 2;
	common->fmt.fmt.pix.bytesperline = std_info->width;
	vpअगरparams->video_params.hpitch = std_info->width;
	vpअगरparams->video_params.storage_mode = std_info->frm_fmt;

	अगर (vid_ch->stdid)
		common->fmt.fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	अन्यथा
		common->fmt.fmt.pix.colorspace = V4L2_COLORSPACE_REC709;

	अगर (ch->vpअगरparams.std_info.frm_fmt)
		common->fmt.fmt.pix.field = V4L2_FIELD_NONE;
	अन्यथा
		common->fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	अगर (ch->vpअगरparams.अगरace.अगर_type == VPIF_IF_RAW_BAYER)
		common->fmt.fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_SBGGR8;
	अन्यथा
		common->fmt.fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_NV16;

	common->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	वापस 0;
पूर्ण

/**
 * vpअगर_calculate_offsets : This function calculates buffers offsets
 * @ch : ptr to channel object
 *
 * This function calculates buffer offsets क्रम Y and C in the top and
 * bottom field
 */
अटल व्योम vpअगर_calculate_offsets(काष्ठा channel_obj *ch)
अणु
	अचिन्हित पूर्णांक hpitch, sizeimage;
	काष्ठा video_obj *vid_ch = &(ch->video);
	काष्ठा vpअगर_params *vpअगरparams = &ch->vpअगरparams;
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	क्रमागत v4l2_field field = common->fmt.fmt.pix.field;

	vpअगर_dbg(2, debug, "vpif_calculate_offsets\n");

	अगर (V4L2_FIELD_ANY == field) अणु
		अगर (vpअगरparams->std_info.frm_fmt)
			vid_ch->buf_field = V4L2_FIELD_NONE;
		अन्यथा
			vid_ch->buf_field = V4L2_FIELD_INTERLACED;
	पूर्ण अन्यथा
		vid_ch->buf_field = common->fmt.fmt.pix.field;

	sizeimage = common->fmt.fmt.pix.sizeimage;

	hpitch = common->fmt.fmt.pix.bytesperline;

	अगर ((V4L2_FIELD_NONE == vid_ch->buf_field) ||
	    (V4L2_FIELD_INTERLACED == vid_ch->buf_field)) अणु
		/* Calculate offsets क्रम Y top, Y Bottom, C top and C Bottom */
		common->ytop_off = 0;
		common->ybपंचांग_off = hpitch;
		common->ctop_off = sizeimage / 2;
		common->cbपंचांग_off = sizeimage / 2 + hpitch;
	पूर्ण अन्यथा अगर (V4L2_FIELD_SEQ_TB == vid_ch->buf_field) अणु
		/* Calculate offsets क्रम Y top, Y Bottom, C top and C Bottom */
		common->ytop_off = 0;
		common->ybपंचांग_off = sizeimage / 4;
		common->ctop_off = sizeimage / 2;
		common->cbपंचांग_off = common->ctop_off + sizeimage / 4;
	पूर्ण अन्यथा अगर (V4L2_FIELD_SEQ_BT == vid_ch->buf_field) अणु
		/* Calculate offsets क्रम Y top, Y Bottom, C top and C Bottom */
		common->ybपंचांग_off = 0;
		common->ytop_off = sizeimage / 4;
		common->cbपंचांग_off = sizeimage / 2;
		common->ctop_off = common->cbपंचांग_off + sizeimage / 4;
	पूर्ण
	अगर ((V4L2_FIELD_NONE == vid_ch->buf_field) ||
	    (V4L2_FIELD_INTERLACED == vid_ch->buf_field))
		vpअगरparams->video_params.storage_mode = 1;
	अन्यथा
		vpअगरparams->video_params.storage_mode = 0;

	अगर (1 == vpअगरparams->std_info.frm_fmt)
		vpअगरparams->video_params.hpitch =
		    common->fmt.fmt.pix.bytesperline;
	अन्यथा अणु
		अगर ((field == V4L2_FIELD_ANY)
		    || (field == V4L2_FIELD_INTERLACED))
			vpअगरparams->video_params.hpitch =
			    common->fmt.fmt.pix.bytesperline * 2;
		अन्यथा
			vpअगरparams->video_params.hpitch =
			    common->fmt.fmt.pix.bytesperline;
	पूर्ण

	ch->vpअगरparams.video_params.stdid = vpअगरparams->std_info.stdid;
पूर्ण

/**
 * vpअगर_get_शेष_field() - Get शेष field type based on पूर्णांकerface
 * @अगरace: ptr to vpअगर पूर्णांकerface
 */
अटल अंतरभूत क्रमागत v4l2_field vpअगर_get_शेष_field(
				काष्ठा vpअगर_पूर्णांकerface *अगरace)
अणु
	वापस (अगरace->अगर_type == VPIF_IF_RAW_BAYER) ? V4L2_FIELD_NONE :
						V4L2_FIELD_INTERLACED;
पूर्ण

/**
 * vpअगर_config_addr() - function to configure buffer address in vpअगर
 * @ch: channel ptr
 * @muxmode: channel mux mode
 */
अटल व्योम vpअगर_config_addr(काष्ठा channel_obj *ch, पूर्णांक muxmode)
अणु
	काष्ठा common_obj *common;

	vpअगर_dbg(2, debug, "vpif_config_addr\n");

	common = &(ch->common[VPIF_VIDEO_INDEX]);

	अगर (VPIF_CHANNEL1_VIDEO == ch->channel_id)
		common->set_addr = ch1_set_videobuf_addr;
	अन्यथा अगर (2 == muxmode)
		common->set_addr = ch0_set_videobuf_addr_yc_nmux;
	अन्यथा
		common->set_addr = ch0_set_videobuf_addr;
पूर्ण

/**
 * vpअगर_input_to_subdev() - Maps input to sub device
 * @vpअगर_cfg: global config ptr
 * @chan_cfg: channel config ptr
 * @input_index: Given input index from application
 *
 * lookup the sub device inक्रमmation क्रम a given input index.
 * we report all the inमाला_दो to application. inमाला_दो table also
 * has sub device name क्रम the each input
 */
अटल पूर्णांक vpअगर_input_to_subdev(
		काष्ठा vpअगर_capture_config *vpअगर_cfg,
		काष्ठा vpअगर_capture_chan_config *chan_cfg,
		पूर्णांक input_index)
अणु
	काष्ठा vpअगर_subdev_info *subdev_info;
	स्थिर अक्षर *subdev_name;
	पूर्णांक i;

	vpअगर_dbg(2, debug, "vpif_input_to_subdev\n");

	अगर (!chan_cfg)
		वापस -1;
	अगर (input_index >= chan_cfg->input_count)
		वापस -1;
	subdev_name = chan_cfg->inमाला_दो[input_index].subdev_name;
	अगर (!subdev_name)
		वापस -1;

	/* loop through the sub device list to get the sub device info */
	क्रम (i = 0; i < vpअगर_cfg->subdev_count; i++) अणु
		subdev_info = &vpअगर_cfg->subdev_info[i];
		अगर (subdev_info && !म_भेद(subdev_info->name, subdev_name))
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

/**
 * vpअगर_set_input() - Select an input
 * @vpअगर_cfg: global config ptr
 * @ch: channel
 * @index: Given input index from application
 *
 * Select the given input.
 */
अटल पूर्णांक vpअगर_set_input(
		काष्ठा vpअगर_capture_config *vpअगर_cfg,
		काष्ठा channel_obj *ch,
		पूर्णांक index)
अणु
	काष्ठा vpअगर_capture_chan_config *chan_cfg =
			&vpअगर_cfg->chan_config[ch->channel_id];
	काष्ठा vpअगर_subdev_info *subdev_info = शून्य;
	काष्ठा v4l2_subdev *sd = शून्य;
	u32 input = 0, output = 0;
	पूर्णांक sd_index;
	पूर्णांक ret;

	sd_index = vpअगर_input_to_subdev(vpअगर_cfg, chan_cfg, index);
	अगर (sd_index >= 0) अणु
		sd = vpअगर_obj.sd[sd_index];
		subdev_info = &vpअगर_cfg->subdev_info[sd_index];
	पूर्ण अन्यथा अणु
		/* no subdevice, no input to setup */
		वापस 0;
	पूर्ण

	/* first setup input path from sub device to vpअगर */
	अगर (sd && vpअगर_cfg->setup_input_path) अणु
		ret = vpअगर_cfg->setup_input_path(ch->channel_id,
				       subdev_info->name);
		अगर (ret < 0) अणु
			vpअगर_dbg(1, debug, "couldn't setup input path for the" \
			" sub device %s, for input index %d\n",
			subdev_info->name, index);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (sd) अणु
		input = chan_cfg->inमाला_दो[index].input_route;
		output = chan_cfg->inमाला_दो[index].output_route;
		ret = v4l2_subdev_call(sd, video, s_routing,
				input, output, 0);
		अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
			vpअगर_dbg(1, debug, "Failed to set input\n");
			वापस ret;
		पूर्ण
	पूर्ण
	ch->input_idx = index;
	ch->sd = sd;
	/* copy पूर्णांकerface parameters to vpअगर */
	ch->vpअगरparams.अगरace = chan_cfg->vpअगर_अगर;

	/* update tvnorms from the sub device input info */
	ch->video_dev.tvnorms = chan_cfg->inमाला_दो[index].input.std;
	वापस 0;
पूर्ण

/**
 * vpअगर_querystd() - querystd handler
 * @file: file ptr
 * @priv: file handle
 * @std_id: ptr to std id
 *
 * This function is called to detect standard at the selected input
 */
अटल पूर्णांक vpअगर_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std_id)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	पूर्णांक ret;

	vpअगर_dbg(2, debug, "vpif_querystd\n");

	/* Call querystd function of decoder device */
	ret = v4l2_subdev_call(ch->sd, video, querystd, std_id);

	अगर (ret == -ENOIOCTLCMD || ret == -ENODEV)
		वापस -ENODATA;
	अगर (ret) अणु
		vpअगर_dbg(1, debug, "Failed to query standard for sub devices\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vpअगर_g_std() - get STD handler
 * @file: file ptr
 * @priv: file handle
 * @std: ptr to std id
 */
अटल पूर्णांक vpअगर_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा vpअगर_capture_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_capture_chan_config *chan_cfg;
	काष्ठा v4l2_input input;

	vpअगर_dbg(2, debug, "vpif_g_std\n");

	अगर (!config->chan_config[ch->channel_id].inमाला_दो)
		वापस -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	input = chan_cfg->inमाला_दो[ch->input_idx].input;
	अगर (input.capabilities != V4L2_IN_CAP_STD)
		वापस -ENODATA;

	*std = ch->video.stdid;
	वापस 0;
पूर्ण

/**
 * vpअगर_s_std() - set STD handler
 * @file: file ptr
 * @priv: file handle
 * @std_id: ptr to std id
 */
अटल पूर्णांक vpअगर_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std_id)
अणु
	काष्ठा vpअगर_capture_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा vpअगर_capture_chan_config *chan_cfg;
	काष्ठा v4l2_input input;
	पूर्णांक ret;

	vpअगर_dbg(2, debug, "vpif_s_std\n");

	अगर (!config->chan_config[ch->channel_id].inमाला_दो)
		वापस -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	input = chan_cfg->inमाला_दो[ch->input_idx].input;
	अगर (input.capabilities != V4L2_IN_CAP_STD)
		वापस -ENODATA;

	अगर (vb2_is_busy(&common->buffer_queue))
		वापस -EBUSY;

	/* Call encoder subdevice function to set the standard */
	ch->video.stdid = std_id;
	स_रखो(&ch->video.dv_timings, 0, माप(ch->video.dv_timings));

	/* Get the inक्रमmation about the standard */
	अगर (vpअगर_update_std_info(ch)) अणु
		vpअगर_err("Error getting the standard info\n");
		वापस -EINVAL;
	पूर्ण

	/* set standard in the sub device */
	ret = v4l2_subdev_call(ch->sd, video, s_std, std_id);
	अगर (ret && ret != -ENOIOCTLCMD && ret != -ENODEV) अणु
		vpअगर_dbg(1, debug, "Failed to set standard for sub devices\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * vpअगर_क्रमागत_input() - ENUMINPUT handler
 * @file: file ptr
 * @priv: file handle
 * @input: ptr to input काष्ठाure
 */
अटल पूर्णांक vpअगर_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_input *input)
अणु

	काष्ठा vpअगर_capture_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_capture_chan_config *chan_cfg;

	chan_cfg = &config->chan_config[ch->channel_id];

	अगर (input->index >= chan_cfg->input_count)
		वापस -EINVAL;

	स_नकल(input, &chan_cfg->inमाला_दो[input->index].input,
		माप(*input));
	वापस 0;
पूर्ण

/**
 * vpअगर_g_input() - Get INPUT handler
 * @file: file ptr
 * @priv: file handle
 * @index: ptr to input index
 */
अटल पूर्णांक vpअगर_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *index)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);

	*index = ch->input_idx;
	वापस 0;
पूर्ण

/**
 * vpअगर_s_input() - Set INPUT handler
 * @file: file ptr
 * @priv: file handle
 * @index: input index
 */
अटल पूर्णांक vpअगर_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक index)
अणु
	काष्ठा vpअगर_capture_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा vpअगर_capture_chan_config *chan_cfg;

	chan_cfg = &config->chan_config[ch->channel_id];

	अगर (index >= chan_cfg->input_count)
		वापस -EINVAL;

	अगर (vb2_is_busy(&common->buffer_queue))
		वापस -EBUSY;

	वापस vpअगर_set_input(config, ch, index);
पूर्ण

/**
 * vpअगर_क्रमागत_fmt_vid_cap() - ENUM_FMT handler
 * @file: file ptr
 * @priv: file handle
 * @fmt: ptr to V4L2 क्रमmat descriptor
 */
अटल पूर्णांक vpअगर_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *fmt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);

	अगर (fmt->index != 0) अणु
		vpअगर_dbg(1, debug, "Invalid format index\n");
		वापस -EINVAL;
	पूर्ण

	/* Fill in the inक्रमmation about क्रमmat */
	अगर (ch->vpअगरparams.अगरace.अगर_type == VPIF_IF_RAW_BAYER)
		fmt->pixelक्रमmat = V4L2_PIX_FMT_SBGGR8;
	अन्यथा
		fmt->pixelक्रमmat = V4L2_PIX_FMT_NV16;
	वापस 0;
पूर्ण

/**
 * vpअगर_try_fmt_vid_cap() - TRY_FMT handler
 * @file: file ptr
 * @priv: file handle
 * @fmt: ptr to v4l2 क्रमmat काष्ठाure
 */
अटल पूर्णांक vpअगर_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &fmt->fmt.pix;
	काष्ठा common_obj *common = &(ch->common[VPIF_VIDEO_INDEX]);

	common->fmt = *fmt;
	vpअगर_update_std_info(ch);

	pixfmt->field = common->fmt.fmt.pix.field;
	pixfmt->colorspace = common->fmt.fmt.pix.colorspace;
	pixfmt->bytesperline = common->fmt.fmt.pix.width;
	pixfmt->width = common->fmt.fmt.pix.width;
	pixfmt->height = common->fmt.fmt.pix.height;
	pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height * 2;
	अगर (pixfmt->pixelक्रमmat == V4L2_PIX_FMT_SGRBG10) अणु
		pixfmt->bytesperline = common->fmt.fmt.pix.width * 2;
		pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;
	पूर्ण

	dev_dbg(vpअगर_dev, "%s: %d x %d; pitch=%d pixelformat=0x%08x, field=%d, size=%d\n", __func__,
		pixfmt->width, pixfmt->height,
		pixfmt->bytesperline, pixfmt->pixelक्रमmat,
		pixfmt->field, pixfmt->sizeimage);

	वापस 0;
पूर्ण


/**
 * vpअगर_g_fmt_vid_cap() - Set INPUT handler
 * @file: file ptr
 * @priv: file handle
 * @fmt: ptr to v4l2 क्रमmat काष्ठाure
 */
अटल पूर्णांक vpअगर_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा v4l2_pix_क्रमmat *pix_fmt = &fmt->fmt.pix;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &क्रमmat.क्रमmat;
	पूर्णांक ret;

	/* Check the validity of the buffer type */
	अगर (common->fmt.type != fmt->type)
		वापस -EINVAL;

	/* By शेष, use currently set fmt */
	*fmt = common->fmt;

	/* If subdev has get_fmt, use that to override */
	ret = v4l2_subdev_call(ch->sd, pad, get_fmt, शून्य, &क्रमmat);
	अगर (!ret && mbus_fmt->code) अणु
		v4l2_fill_pix_क्रमmat(pix_fmt, mbus_fmt);
		pix_fmt->bytesperline = pix_fmt->width;
		अगर (mbus_fmt->code == MEDIA_BUS_FMT_SGRBG10_1X10) अणु
			/* e.g. mt9v032 */
			pix_fmt->pixelक्रमmat = V4L2_PIX_FMT_SGRBG10;
			pix_fmt->bytesperline = pix_fmt->width * 2;
		पूर्ण अन्यथा अगर (mbus_fmt->code == MEDIA_BUS_FMT_UYVY8_2X8) अणु
			/* e.g. tvp514x */
			pix_fmt->pixelक्रमmat = V4L2_PIX_FMT_NV16;
			pix_fmt->bytesperline = pix_fmt->width * 2;
		पूर्ण अन्यथा अणु
			dev_warn(vpअगर_dev, "%s: Unhandled media-bus format 0x%x\n",
				 __func__, mbus_fmt->code);
		पूर्ण
		pix_fmt->sizeimage = pix_fmt->bytesperline * pix_fmt->height;
		dev_dbg(vpअगर_dev, "%s: %d x %d; pitch=%d, pixelformat=0x%08x, code=0x%x, field=%d, size=%d\n", __func__,
			pix_fmt->width, pix_fmt->height,
			pix_fmt->bytesperline, pix_fmt->pixelक्रमmat,
			mbus_fmt->code, pix_fmt->field, pix_fmt->sizeimage);

		common->fmt = *fmt;
		vpअगर_update_std_info(ch);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vpअगर_s_fmt_vid_cap() - Set FMT handler
 * @file: file ptr
 * @priv: file handle
 * @fmt: ptr to v4l2 क्रमmat काष्ठाure
 */
अटल पूर्णांक vpअगर_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	पूर्णांक ret;

	vpअगर_dbg(2, debug, "%s\n", __func__);

	अगर (vb2_is_busy(&common->buffer_queue))
		वापस -EBUSY;

	ret = vpअगर_try_fmt_vid_cap(file, priv, fmt);
	अगर (ret)
		वापस ret;

	/* store the क्रमmat in the channel object */
	common->fmt = *fmt;
	वापस 0;
पूर्ण

/**
 * vpअगर_querycap() - QUERYCAP handler
 * @file: file ptr
 * @priv: file handle
 * @cap: ptr to v4l2_capability काष्ठाure
 */
अटल पूर्णांक vpअगर_querycap(काष्ठा file *file, व्योम  *priv,
				काष्ठा v4l2_capability *cap)
अणु
	काष्ठा vpअगर_capture_config *config = vpअगर_dev->platक्रमm_data;

	strscpy(cap->driver, VPIF_DRIVER_NAME, माप(cap->driver));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(vpअगर_dev));
	strscpy(cap->card, config->card_name, माप(cap->card));

	वापस 0;
पूर्ण

/**
 * vpअगर_क्रमागत_dv_timings() - ENUM_DV_TIMINGS handler
 * @file: file ptr
 * @priv: file handle
 * @timings: input timings
 */
अटल पूर्णांक
vpअगर_क्रमागत_dv_timings(काष्ठा file *file, व्योम *priv,
		     काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	काष्ठा vpअगर_capture_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_capture_chan_config *chan_cfg;
	काष्ठा v4l2_input input;
	पूर्णांक ret;

	अगर (!config->chan_config[ch->channel_id].inमाला_दो)
		वापस -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	input = chan_cfg->inमाला_दो[ch->input_idx].input;
	अगर (input.capabilities != V4L2_IN_CAP_DV_TIMINGS)
		वापस -ENODATA;

	timings->pad = 0;

	ret = v4l2_subdev_call(ch->sd, pad, क्रमागत_dv_timings, timings);
	अगर (ret == -ENOIOCTLCMD || ret == -ENODEV)
		वापस -EINVAL;

	वापस ret;
पूर्ण

/**
 * vpअगर_query_dv_timings() - QUERY_DV_TIMINGS handler
 * @file: file ptr
 * @priv: file handle
 * @timings: input timings
 */
अटल पूर्णांक
vpअगर_query_dv_timings(काष्ठा file *file, व्योम *priv,
		      काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा vpअगर_capture_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_capture_chan_config *chan_cfg;
	काष्ठा v4l2_input input;
	पूर्णांक ret;

	अगर (!config->chan_config[ch->channel_id].inमाला_दो)
		वापस -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	input = chan_cfg->inमाला_दो[ch->input_idx].input;
	अगर (input.capabilities != V4L2_IN_CAP_DV_TIMINGS)
		वापस -ENODATA;

	ret = v4l2_subdev_call(ch->sd, video, query_dv_timings, timings);
	अगर (ret == -ENOIOCTLCMD || ret == -ENODEV)
		वापस -ENODATA;

	वापस ret;
पूर्ण

/**
 * vpअगर_s_dv_timings() - S_DV_TIMINGS handler
 * @file: file ptr
 * @priv: file handle
 * @timings: digital video timings
 */
अटल पूर्णांक vpअगर_s_dv_timings(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा vpअगर_capture_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_params *vpअगरparams = &ch->vpअगरparams;
	काष्ठा vpअगर_channel_config_params *std_info = &vpअगरparams->std_info;
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा video_obj *vid_ch = &ch->video;
	काष्ठा v4l2_bt_timings *bt = &vid_ch->dv_timings.bt;
	काष्ठा vpअगर_capture_chan_config *chan_cfg;
	काष्ठा v4l2_input input;
	पूर्णांक ret;

	अगर (!config->chan_config[ch->channel_id].inमाला_दो)
		वापस -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	input = chan_cfg->inमाला_दो[ch->input_idx].input;
	अगर (input.capabilities != V4L2_IN_CAP_DV_TIMINGS)
		वापस -ENODATA;

	अगर (timings->type != V4L2_DV_BT_656_1120) अणु
		vpअगर_dbg(2, debug, "Timing type not defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vb2_is_busy(&common->buffer_queue))
		वापस -EBUSY;

	/* Configure subdevice timings, अगर any */
	ret = v4l2_subdev_call(ch->sd, video, s_dv_timings, timings);
	अगर (ret == -ENOIOCTLCMD || ret == -ENODEV)
		ret = 0;
	अगर (ret < 0) अणु
		vpअगर_dbg(2, debug, "Error setting custom DV timings\n");
		वापस ret;
	पूर्ण

	अगर (!(timings->bt.width && timings->bt.height &&
				(timings->bt.hbackporch ||
				 timings->bt.hfrontporch ||
				 timings->bt.hsync) &&
				timings->bt.vfrontporch &&
				(timings->bt.vbackporch ||
				 timings->bt.vsync))) अणु
		vpअगर_dbg(2, debug, "Timings for width, height, horizontal back porch, horizontal sync, horizontal front porch, vertical back porch, vertical sync and vertical back porch must be defined\n");
		वापस -EINVAL;
	पूर्ण

	vid_ch->dv_timings = *timings;

	/* Configure video port timings */

	std_info->eav2sav = V4L2_DV_BT_BLANKING_WIDTH(bt) - 8;
	std_info->sav2eav = bt->width;

	std_info->l1 = 1;
	std_info->l3 = bt->vsync + bt->vbackporch + 1;

	std_info->vsize = V4L2_DV_BT_FRAME_HEIGHT(bt);
	अगर (bt->पूर्णांकerlaced) अणु
		अगर (bt->il_vbackporch || bt->il_vfrontporch || bt->il_vsync) अणु
			std_info->l5 = std_info->vsize/2 -
				(bt->vfrontporch - 1);
			std_info->l7 = std_info->vsize/2 + 1;
			std_info->l9 = std_info->l7 + bt->il_vsync +
				bt->il_vbackporch + 1;
			std_info->l11 = std_info->vsize -
				(bt->il_vfrontporch - 1);
		पूर्ण अन्यथा अणु
			vpअगर_dbg(2, debug, "Required timing values for interlaced BT format missing\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		std_info->l5 = std_info->vsize - (bt->vfrontporch - 1);
	पूर्ण
	strscpy(std_info->name, "Custom timings BT656/1120",
		माप(std_info->name));
	std_info->width = bt->width;
	std_info->height = bt->height;
	std_info->frm_fmt = bt->पूर्णांकerlaced ? 0 : 1;
	std_info->ycmux_mode = 0;
	std_info->capture_क्रमmat = 0;
	std_info->vbi_supported = 0;
	std_info->hd_sd = 1;
	std_info->stdid = 0;

	vid_ch->stdid = 0;
	वापस 0;
पूर्ण

/**
 * vpअगर_g_dv_timings() - G_DV_TIMINGS handler
 * @file: file ptr
 * @priv: file handle
 * @timings: digital video timings
 */
अटल पूर्णांक vpअगर_g_dv_timings(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा vpअगर_capture_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा video_obj *vid_ch = &ch->video;
	काष्ठा vpअगर_capture_chan_config *chan_cfg;
	काष्ठा v4l2_input input;

	अगर (!config->chan_config[ch->channel_id].inमाला_दो)
		वापस -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	input = chan_cfg->inमाला_दो[ch->input_idx].input;
	अगर (input.capabilities != V4L2_IN_CAP_DV_TIMINGS)
		वापस -ENODATA;

	*timings = vid_ch->dv_timings;

	वापस 0;
पूर्ण

/*
 * vpअगर_log_status() - Status inक्रमmation
 * @file: file ptr
 * @priv: file handle
 *
 * Returns zero.
 */
अटल पूर्णांक vpअगर_log_status(काष्ठा file *filep, व्योम *priv)
अणु
	/* status क्रम sub devices */
	v4l2_device_call_all(&vpअगर_obj.v4l2_dev, 0, core, log_status);

	वापस 0;
पूर्ण

/* vpअगर capture ioctl operations */
अटल स्थिर काष्ठा v4l2_ioctl_ops vpअगर_ioctl_ops = अणु
	.vidioc_querycap		= vpअगर_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= vpअगर_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= vpअगर_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= vpअगर_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= vpअगर_try_fmt_vid_cap,

	.vidioc_क्रमागत_input		= vpअगर_क्रमागत_input,
	.vidioc_s_input			= vpअगर_s_input,
	.vidioc_g_input			= vpअगर_g_input,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_querystd		= vpअगर_querystd,
	.vidioc_s_std			= vpअगर_s_std,
	.vidioc_g_std			= vpअगर_g_std,

	.vidioc_क्रमागत_dv_timings		= vpअगर_क्रमागत_dv_timings,
	.vidioc_query_dv_timings	= vpअगर_query_dv_timings,
	.vidioc_s_dv_timings		= vpअगर_s_dv_timings,
	.vidioc_g_dv_timings		= vpअगर_g_dv_timings,

	.vidioc_log_status		= vpअगर_log_status,
पूर्ण;

/* vpअगर file operations */
अटल स्थिर काष्ठा v4l2_file_operations vpअगर_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.unlocked_ioctl = video_ioctl2,
	.mmap = vb2_fop_mmap,
	.poll = vb2_fop_poll
पूर्ण;

/**
 * initialize_vpअगर() - Initialize vpअगर data काष्ठाures
 *
 * Allocate memory क्रम data काष्ठाures and initialize them
 */
अटल पूर्णांक initialize_vpअगर(व्योम)
अणु
	पूर्णांक err, i, j;
	पूर्णांक मुक्त_channel_objects_index;

	/* Allocate memory क्रम six channel objects */
	क्रम (i = 0; i < VPIF_CAPTURE_MAX_DEVICES; i++) अणु
		vpअगर_obj.dev[i] =
		    kzalloc(माप(*vpअगर_obj.dev[i]), GFP_KERNEL);
		/* If memory allocation fails, वापस error */
		अगर (!vpअगर_obj.dev[i]) अणु
			मुक्त_channel_objects_index = i;
			err = -ENOMEM;
			जाओ vpअगर_init_मुक्त_channel_objects;
		पूर्ण
	पूर्ण
	वापस 0;

vpअगर_init_मुक्त_channel_objects:
	क्रम (j = 0; j < मुक्त_channel_objects_index; j++)
		kमुक्त(vpअगर_obj.dev[j]);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम मुक्त_vpअगर_objs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VPIF_CAPTURE_MAX_DEVICES; i++)
		kमुक्त(vpअगर_obj.dev[i]);
पूर्ण

अटल पूर्णांक vpअगर_async_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
			    काष्ठा v4l2_subdev *subdev,
			    काष्ठा v4l2_async_subdev *asd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vpअगर_obj.config->asd_sizes[0]; i++) अणु
		काष्ठा v4l2_async_subdev *_asd = vpअगर_obj.config->asd[i];
		स्थिर काष्ठा fwnode_handle *fwnode = _asd->match.fwnode;

		अगर (fwnode == subdev->fwnode) अणु
			vpअगर_obj.sd[i] = subdev;
			vpअगर_obj.config->chan_config->inमाला_दो[i].subdev_name =
				(अक्षर *)to_of_node(subdev->fwnode)->full_name;
			vpअगर_dbg(2, debug,
				 "%s: setting input %d subdev_name = %s\n",
				 __func__, i,
				vpअगर_obj.config->chan_config->inमाला_दो[i].subdev_name);
			वापस 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < vpअगर_obj.config->subdev_count; i++)
		अगर (!म_भेद(vpअगर_obj.config->subdev_info[i].name,
			    subdev->name)) अणु
			vpअगर_obj.sd[i] = subdev;
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vpअगर_probe_complete(व्योम)
अणु
	काष्ठा common_obj *common;
	काष्ठा video_device *vdev;
	काष्ठा channel_obj *ch;
	काष्ठा vb2_queue *q;
	पूर्णांक j, err, k;

	क्रम (j = 0; j < VPIF_CAPTURE_MAX_DEVICES; j++) अणु
		ch = vpअगर_obj.dev[j];
		ch->channel_id = j;
		common = &(ch->common[VPIF_VIDEO_INDEX]);
		spin_lock_init(&common->irqlock);
		mutex_init(&common->lock);

		/* select input 0 */
		err = vpअगर_set_input(vpअगर_obj.config, ch, 0);
		अगर (err)
			जाओ probe_out;

		/* set initial क्रमmat */
		ch->video.stdid = V4L2_STD_525_60;
		स_रखो(&ch->video.dv_timings, 0, माप(ch->video.dv_timings));
		common->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		vpअगर_update_std_info(ch);

		/* Initialize vb2 queue */
		q = &common->buffer_queue;
		q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
		q->drv_priv = ch;
		q->ops = &video_qops;
		q->mem_ops = &vb2_dma_contig_memops;
		q->buf_काष्ठा_size = माप(काष्ठा vpअगर_cap_buffer);
		q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
		q->min_buffers_needed = 1;
		q->lock = &common->lock;
		q->dev = vpअगर_dev;

		err = vb2_queue_init(q);
		अगर (err) अणु
			vpअगर_err("vpif_capture: vb2_queue_init() failed\n");
			जाओ probe_out;
		पूर्ण

		INIT_LIST_HEAD(&common->dma_queue);

		/* Initialize the video_device काष्ठाure */
		vdev = &ch->video_dev;
		strscpy(vdev->name, VPIF_DRIVER_NAME, माप(vdev->name));
		vdev->release = video_device_release_empty;
		vdev->fops = &vpअगर_fops;
		vdev->ioctl_ops = &vpअगर_ioctl_ops;
		vdev->v4l2_dev = &vpअगर_obj.v4l2_dev;
		vdev->vfl_dir = VFL_सूची_RX;
		vdev->queue = q;
		vdev->lock = &common->lock;
		vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING;
		video_set_drvdata(&ch->video_dev, ch);
		err = video_रेजिस्टर_device(vdev,
					    VFL_TYPE_VIDEO, (j ? 1 : 0));
		अगर (err)
			जाओ probe_out;
	पूर्ण

	v4l2_info(&vpअगर_obj.v4l2_dev, "VPIF capture driver initialized\n");
	वापस 0;

probe_out:
	क्रम (k = 0; k < j; k++) अणु
		/* Get the poपूर्णांकer to the channel object */
		ch = vpअगर_obj.dev[k];
		common = &ch->common[k];
		/* Unरेजिस्टर video device */
		video_unरेजिस्टर_device(&ch->video_dev);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक vpअगर_async_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	वापस vpअगर_probe_complete();
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations vpअगर_async_ops = अणु
	.bound = vpअगर_async_bound,
	.complete = vpअगर_async_complete,
पूर्ण;

अटल काष्ठा vpअगर_capture_config *
vpअगर_capture_get_pdata(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *endpoपूर्णांक = शून्य;
	काष्ठा device_node *rem = शून्य;
	काष्ठा vpअगर_capture_config *pdata;
	काष्ठा vpअगर_subdev_info *sdinfo;
	काष्ठा vpअगर_capture_chan_config *chan;
	अचिन्हित पूर्णांक i;

	v4l2_async_notअगरier_init(&vpअगर_obj.notअगरier);

	/*
	 * DT boot: OF node from parent device contains
	 * video ports & endpoपूर्णांकs data.
	 */
	अगर (pdev->dev.parent && pdev->dev.parent->of_node)
		pdev->dev.of_node = pdev->dev.parent->of_node;
	अगर (!IS_ENABLED(CONFIG_OF) || !pdev->dev.of_node)
		वापस pdev->dev.platक्रमm_data;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;
	pdata->subdev_info =
		devm_kसुस्मृति(&pdev->dev,
			     VPIF_CAPTURE_NUM_CHANNELS,
			     माप(*pdata->subdev_info),
			     GFP_KERNEL);

	अगर (!pdata->subdev_info)
		वापस शून्य;

	क्रम (i = 0; i < VPIF_CAPTURE_NUM_CHANNELS; i++) अणु
		काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु .bus_type = 0 पूर्ण;
		अचिन्हित पूर्णांक flags;
		पूर्णांक err;

		endpoपूर्णांक = of_graph_get_next_endpoपूर्णांक(pdev->dev.of_node,
						      endpoपूर्णांक);
		अगर (!endpoपूर्णांक)
			अवरोध;

		rem = of_graph_get_remote_port_parent(endpoपूर्णांक);
		अगर (!rem) अणु
			dev_dbg(&pdev->dev, "Remote device at %pOF not found\n",
				endpoपूर्णांक);
			जाओ करोne;
		पूर्ण

		sdinfo = &pdata->subdev_info[i];
		chan = &pdata->chan_config[i];
		chan->inमाला_दो = devm_kसुस्मृति(&pdev->dev,
					    VPIF_CAPTURE_NUM_CHANNELS,
					    माप(*chan->inमाला_दो),
					    GFP_KERNEL);
		अगर (!chan->inमाला_दो)
			जाओ err_cleanup;

		chan->input_count++;
		chan->inमाला_दो[i].input.type = V4L2_INPUT_TYPE_CAMERA;
		chan->inमाला_दो[i].input.std = V4L2_STD_ALL;
		chan->inमाला_दो[i].input.capabilities = V4L2_IN_CAP_STD;

		err = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(endpoपूर्णांक),
						 &bus_cfg);
		अगर (err) अणु
			dev_err(&pdev->dev, "Could not parse the endpoint\n");
			of_node_put(rem);
			जाओ करोne;
		पूर्ण

		dev_dbg(&pdev->dev, "Endpoint %pOF, bus_width = %d\n",
			endpoपूर्णांक, bus_cfg.bus.parallel.bus_width);

		flags = bus_cfg.bus.parallel.flags;

		अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
			chan->vpअगर_अगर.hd_pol = 1;

		अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
			chan->vpअगर_अगर.vd_pol = 1;

		dev_dbg(&pdev->dev, "Remote device %pOF found\n", rem);
		sdinfo->name = rem->full_name;

		pdata->asd[i] = v4l2_async_notअगरier_add_fwnode_subdev(
			&vpअगर_obj.notअगरier, of_fwnode_handle(rem),
			काष्ठा v4l2_async_subdev);
		अगर (IS_ERR(pdata->asd[i]))
			जाओ err_cleanup;

		of_node_put(rem);
	पूर्ण

करोne:
	of_node_put(endpoपूर्णांक);
	pdata->asd_sizes[0] = i;
	pdata->subdev_count = i;
	pdata->card_name = "DA850/OMAP-L138 Video Capture";

	वापस pdata;

err_cleanup:
	of_node_put(rem);
	of_node_put(endpoपूर्णांक);
	v4l2_async_notअगरier_cleanup(&vpअगर_obj.notअगरier);

	वापस शून्य;
पूर्ण

/**
 * vpअगर_probe : This function probes the vpअगर capture driver
 * @pdev: platक्रमm device poपूर्णांकer
 *
 * This creates device entries by रेजिस्टर itself to the V4L2 driver and
 * initializes fields of each channel objects
 */
अटल __init पूर्णांक vpअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpअगर_subdev_info *subdevdata;
	काष्ठा i2c_adapter *i2c_adap;
	काष्ठा resource *res;
	पूर्णांक subdev_count;
	पूर्णांक res_idx = 0;
	पूर्णांक i, err;

	pdev->dev.platक्रमm_data = vpअगर_capture_get_pdata(pdev);
	अगर (!pdev->dev.platक्रमm_data) अणु
		dev_warn(&pdev->dev, "Missing platform data.  Giving up.\n");
		वापस -EINVAL;
	पूर्ण

	vpअगर_dev = &pdev->dev;

	err = initialize_vpअगर();
	अगर (err) अणु
		v4l2_err(vpअगर_dev->driver, "Error initializing vpif\n");
		जाओ cleanup;
	पूर्ण

	err = v4l2_device_रेजिस्टर(vpअगर_dev, &vpअगर_obj.v4l2_dev);
	अगर (err) अणु
		v4l2_err(vpअगर_dev->driver, "Error registering v4l2 device\n");
		जाओ vpअगर_मुक्त;
	पूर्ण

	जबतक ((res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, res_idx))) अणु
		err = devm_request_irq(&pdev->dev, res->start, vpअगर_channel_isr,
					IRQF_SHARED, VPIF_DRIVER_NAME,
					(व्योम *)(&vpअगर_obj.dev[res_idx]->
					channel_id));
		अगर (err) अणु
			err = -EINVAL;
			जाओ vpअगर_unरेजिस्टर;
		पूर्ण
		res_idx++;
	पूर्ण

	vpअगर_obj.config = pdev->dev.platक्रमm_data;

	subdev_count = vpअगर_obj.config->subdev_count;
	vpअगर_obj.sd = kसुस्मृति(subdev_count, माप(*vpअगर_obj.sd), GFP_KERNEL);
	अगर (!vpअगर_obj.sd) अणु
		err = -ENOMEM;
		जाओ vpअगर_unरेजिस्टर;
	पूर्ण

	अगर (!vpअगर_obj.config->asd_sizes[0]) अणु
		पूर्णांक i2c_id = vpअगर_obj.config->i2c_adapter_id;

		i2c_adap = i2c_get_adapter(i2c_id);
		WARN_ON(!i2c_adap);
		क्रम (i = 0; i < subdev_count; i++) अणु
			subdevdata = &vpअगर_obj.config->subdev_info[i];
			vpअगर_obj.sd[i] =
				v4l2_i2c_new_subdev_board(&vpअगर_obj.v4l2_dev,
							  i2c_adap,
							  &subdevdata->
							  board_info,
							  शून्य);

			अगर (!vpअगर_obj.sd[i]) अणु
				vpअगर_err("Error registering v4l2 subdevice\n");
				err = -ENODEV;
				जाओ probe_subdev_out;
			पूर्ण
			v4l2_info(&vpअगर_obj.v4l2_dev,
				  "registered sub device %s\n",
				   subdevdata->name);
		पूर्ण
		err = vpअगर_probe_complete();
		अगर (err)
			जाओ probe_subdev_out;
	पूर्ण अन्यथा अणु
		vpअगर_obj.notअगरier.ops = &vpअगर_async_ops;
		err = v4l2_async_notअगरier_रेजिस्टर(&vpअगर_obj.v4l2_dev,
						   &vpअगर_obj.notअगरier);
		अगर (err) अणु
			vpअगर_err("Error registering async notifier\n");
			err = -EINVAL;
			जाओ probe_subdev_out;
		पूर्ण
	पूर्ण

	वापस 0;

probe_subdev_out:
	/* मुक्त sub devices memory */
	kमुक्त(vpअगर_obj.sd);
vpअगर_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&vpअगर_obj.v4l2_dev);
vpअगर_मुक्त:
	मुक्त_vpअगर_objs();
cleanup:
	v4l2_async_notअगरier_cleanup(&vpअगर_obj.notअगरier);

	वापस err;
पूर्ण

/**
 * vpअगर_हटाओ() - driver हटाओ handler
 * @device: ptr to platक्रमm device काष्ठाure
 *
 * The viकरोe device is unरेजिस्टरed
 */
अटल पूर्णांक vpअगर_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा channel_obj *ch;
	पूर्णांक i;

	v4l2_async_notअगरier_unरेजिस्टर(&vpअगर_obj.notअगरier);
	v4l2_async_notअगरier_cleanup(&vpअगर_obj.notअगरier);
	v4l2_device_unरेजिस्टर(&vpअगर_obj.v4l2_dev);

	kमुक्त(vpअगर_obj.sd);
	/* un-रेजिस्टर device */
	क्रम (i = 0; i < VPIF_CAPTURE_MAX_DEVICES; i++) अणु
		/* Get the poपूर्णांकer to the channel object */
		ch = vpअगर_obj.dev[i];
		/* Unरेजिस्टर video device */
		video_unरेजिस्टर_device(&ch->video_dev);
		kमुक्त(vpअगर_obj.dev[i]);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * vpअगर_suspend: vpअगर device suspend
 * @dev: poपूर्णांकer to &काष्ठा device
 */
अटल पूर्णांक vpअगर_suspend(काष्ठा device *dev)
अणु

	काष्ठा common_obj *common;
	काष्ठा channel_obj *ch;
	पूर्णांक i;

	क्रम (i = 0; i < VPIF_CAPTURE_MAX_DEVICES; i++) अणु
		/* Get the poपूर्णांकer to the channel object */
		ch = vpअगर_obj.dev[i];
		common = &ch->common[VPIF_VIDEO_INDEX];

		अगर (!vb2_start_streaming_called(&common->buffer_queue))
			जारी;

		mutex_lock(&common->lock);
		/* Disable channel */
		अगर (ch->channel_id == VPIF_CHANNEL0_VIDEO) अणु
			enable_channel0(0);
			channel0_पूर्णांकr_enable(0);
		पूर्ण
		अगर (ch->channel_id == VPIF_CHANNEL1_VIDEO ||
			ycmux_mode == 2) अणु
			enable_channel1(0);
			channel1_पूर्णांकr_enable(0);
		पूर्ण
		mutex_unlock(&common->lock);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vpअगर_resume: vpअगर device suspend
 */
अटल पूर्णांक vpअगर_resume(काष्ठा device *dev)
अणु
	काष्ठा common_obj *common;
	काष्ठा channel_obj *ch;
	पूर्णांक i;

	क्रम (i = 0; i < VPIF_CAPTURE_MAX_DEVICES; i++) अणु
		/* Get the poपूर्णांकer to the channel object */
		ch = vpअगर_obj.dev[i];
		common = &ch->common[VPIF_VIDEO_INDEX];

		अगर (!vb2_start_streaming_called(&common->buffer_queue))
			जारी;

		mutex_lock(&common->lock);
		/* Enable channel */
		अगर (ch->channel_id == VPIF_CHANNEL0_VIDEO) अणु
			enable_channel0(1);
			channel0_पूर्णांकr_enable(1);
		पूर्ण
		अगर (ch->channel_id == VPIF_CHANNEL1_VIDEO ||
			ycmux_mode == 2) अणु
			enable_channel1(1);
			channel1_पूर्णांकr_enable(1);
		पूर्ण
		mutex_unlock(&common->lock);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(vpअगर_pm_ops, vpअगर_suspend, vpअगर_resume);

अटल __refdata काष्ठा platक्रमm_driver vpअगर_driver = अणु
	.driver	= अणु
		.name	= VPIF_DRIVER_NAME,
		.pm	= &vpअगर_pm_ops,
	पूर्ण,
	.probe = vpअगर_probe,
	.हटाओ = vpअगर_हटाओ,
पूर्ण;

module_platक्रमm_driver(vpअगर_driver);
