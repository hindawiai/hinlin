<शैली गुरु>
/*
 * vpअगर-display - VPIF display driver
 * Display driver क्रम TI DaVinci VPIF
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - https://www.ti.com/
 * Copyright (C) 2014 Lad, Prabhakar <prabhakar.csengg@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed .as is. WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-ioctl.h>

#समावेश "vpif.h"
#समावेश "vpif_display.h"

MODULE_DESCRIPTION("TI DaVinci VPIF Display driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(VPIF_DISPLAY_VERSION);

#घोषणा VPIF_V4L2_STD (V4L2_STD_525_60 | V4L2_STD_625_50)

#घोषणा vpअगर_err(fmt, arg...)	v4l2_err(&vpअगर_obj.v4l2_dev, fmt, ## arg)
#घोषणा vpअगर_dbg(level, debug, fmt, arg...)	\
		v4l2_dbg(level, debug, &vpअगर_obj.v4l2_dev, fmt, ## arg)

अटल पूर्णांक debug = 1;

module_param(debug, पूर्णांक, 0644);

MODULE_PARM_DESC(debug, "Debug level 0-1");

#घोषणा VPIF_DRIVER_NAME	"vpif_display"
MODULE_ALIAS("platform:" VPIF_DRIVER_NAME);

/* Is set to 1 in हाल of SDTV क्रमmats, 2 in हाल of HDTV क्रमmats. */
अटल पूर्णांक ycmux_mode;

अटल u8 channel_first_पूर्णांक[VPIF_NUMOBJECTS][2] = अणु अणु1, 1पूर्ण पूर्ण;

अटल काष्ठा vpअगर_device vpअगर_obj = अणु अणुशून्यपूर्ण पूर्ण;
अटल काष्ठा device *vpअगर_dev;
अटल व्योम vpअगर_calculate_offsets(काष्ठा channel_obj *ch);
अटल व्योम vpअगर_config_addr(काष्ठा channel_obj *ch, पूर्णांक muxmode);

अटल अंतरभूत
काष्ठा vpअगर_disp_buffer *to_vpअगर_buffer(काष्ठा vb2_v4l2_buffer *vb)
अणु
	वापस container_of(vb, काष्ठा vpअगर_disp_buffer, vb);
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
	काष्ठा channel_obj *ch = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा common_obj *common;

	common = &ch->common[VPIF_VIDEO_INDEX];

	vb2_set_plane_payload(vb, 0, common->fmt.fmt.pix.sizeimage);
	अगर (vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0))
		वापस -EINVAL;

	vbuf->field = common->fmt.fmt.pix.field;

	अगर (vb->vb2_queue->type != V4L2_BUF_TYPE_SLICED_VBI_OUTPUT) अणु
		अचिन्हित दीर्घ addr = vb2_dma_contig_plane_dma_addr(vb, 0);

		अगर (!ISALIGNED(addr + common->ytop_off) ||
			!ISALIGNED(addr + common->ybपंचांग_off) ||
			!ISALIGNED(addr + common->ctop_off) ||
			!ISALIGNED(addr + common->cbपंचांग_off)) अणु
			vpअगर_err("buffer offset not aligned to 8 bytes\n");
			वापस -EINVAL;
		पूर्ण
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

	अगर (*nplanes) अणु
		अगर (sizes[0] < size)
			वापस -EINVAL;
		size = sizes[0];
	पूर्ण

	अगर (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	*nplanes = 1;
	sizes[0] = size;

	/* Calculate the offset क्रम Y and C data  in the buffer */
	vpअगर_calculate_offsets(ch);

	वापस 0;
पूर्ण

/**
 * vpअगर_buffer_queue : Callback function to add buffer to DMA queue
 * @vb: ptr to vb2_buffer
 *
 * This callback function queues the buffer to DMA engine
 */
अटल व्योम vpअगर_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा vpअगर_disp_buffer *buf = to_vpअगर_buffer(vbuf);
	काष्ठा channel_obj *ch = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा common_obj *common;
	अचिन्हित दीर्घ flags;

	common = &ch->common[VPIF_VIDEO_INDEX];

	/* add the buffer to the DMA queue */
	spin_lock_irqsave(&common->irqlock, flags);
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
	काष्ठा vpअगर_display_config *vpअगर_config_data =
					vpअगर_dev->platक्रमm_data;
	काष्ठा channel_obj *ch = vb2_get_drv_priv(vq);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा vpअगर_params *vpअगर = &ch->vpअगरparams;
	काष्ठा vpअगर_disp_buffer *buf, *पंचांगp;
	अचिन्हित दीर्घ addr, flags;
	पूर्णांक ret;

	spin_lock_irqsave(&common->irqlock, flags);

	/* Initialize field_id */
	ch->field_id = 0;

	/* घड़ी settings */
	अगर (vpअगर_config_data->set_घड़ी) अणु
		ret = vpअगर_config_data->set_घड़ी(ch->vpअगरparams.std_info.
		ycmux_mode, ch->vpअगरparams.std_info.hd_sd);
		अगर (ret < 0) अणु
			vpअगर_err("can't set clock\n");
			जाओ err;
		पूर्ण
	पूर्ण

	/* set the parameters and addresses */
	ret = vpअगर_set_video_params(vpअगर, ch->channel_id + 2);
	अगर (ret < 0)
		जाओ err;

	ycmux_mode = ret;
	vpअगर_config_addr(ch, ret);
	/* Get the next frame from the buffer queue */
	common->next_frm = common->cur_frm =
			    list_entry(common->dma_queue.next,
				       काष्ठा vpअगर_disp_buffer, list);

	list_del(&common->cur_frm->list);
	spin_unlock_irqrestore(&common->irqlock, flags);

	addr = vb2_dma_contig_plane_dma_addr(&common->cur_frm->vb.vb2_buf, 0);
	common->set_addr((addr + common->ytop_off),
			    (addr + common->ybपंचांग_off),
			    (addr + common->ctop_off),
			    (addr + common->cbपंचांग_off));

	/*
	 * Set पूर्णांकerrupt क्रम both the fields in VPIF
	 * Register enable channel in VPIF रेजिस्टर
	 */
	channel_first_पूर्णांक[VPIF_VIDEO_INDEX][ch->channel_id] = 1;
	अगर (VPIF_CHANNEL2_VIDEO == ch->channel_id) अणु
		channel2_पूर्णांकr_निश्चित();
		channel2_पूर्णांकr_enable(1);
		enable_channel2(1);
		अगर (vpअगर_config_data->chan_config[VPIF_CHANNEL2_VIDEO].clip_en)
			channel2_clipping_enable(1);
	पूर्ण

	अगर (VPIF_CHANNEL3_VIDEO == ch->channel_id || ycmux_mode == 2) अणु
		channel3_पूर्णांकr_निश्चित();
		channel3_पूर्णांकr_enable(1);
		enable_channel3(1);
		अगर (vpअगर_config_data->chan_config[VPIF_CHANNEL3_VIDEO].clip_en)
			channel3_clipping_enable(1);
	पूर्ण

	वापस 0;

err:
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

	common = &ch->common[VPIF_VIDEO_INDEX];

	/* Disable channel */
	अगर (VPIF_CHANNEL2_VIDEO == ch->channel_id) अणु
		enable_channel2(0);
		channel2_पूर्णांकr_enable(0);
	पूर्ण
	अगर (VPIF_CHANNEL3_VIDEO == ch->channel_id || ycmux_mode == 2) अणु
		enable_channel3(0);
		channel3_पूर्णांकr_enable(0);
	पूर्ण

	/* release all active buffers */
	spin_lock_irqsave(&common->irqlock, flags);
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

	जबतक (!list_empty(&common->dma_queue)) अणु
		common->next_frm = list_entry(common->dma_queue.next,
						काष्ठा vpअगर_disp_buffer, list);
		list_del(&common->next_frm->list);
		vb2_buffer_करोne(&common->next_frm->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&common->irqlock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops video_qops = अणु
	.queue_setup		= vpअगर_buffer_queue_setup,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
	.buf_prepare		= vpअगर_buffer_prepare,
	.start_streaming	= vpअगर_start_streaming,
	.stop_streaming		= vpअगर_stop_streaming,
	.buf_queue		= vpअगर_buffer_queue,
पूर्ण;

अटल व्योम process_progressive_mode(काष्ठा common_obj *common)
अणु
	अचिन्हित दीर्घ addr;

	spin_lock(&common->irqlock);
	/* Get the next buffer from buffer queue */
	common->next_frm = list_entry(common->dma_queue.next,
				काष्ठा vpअगर_disp_buffer, list);
	/* Remove that buffer from the buffer queue */
	list_del(&common->next_frm->list);
	spin_unlock(&common->irqlock);

	/* Set top and bottom field addrs in VPIF रेजिस्टरs */
	addr = vb2_dma_contig_plane_dma_addr(&common->next_frm->vb.vb2_buf, 0);
	common->set_addr(addr + common->ytop_off,
				 addr + common->ybपंचांग_off,
				 addr + common->ctop_off,
				 addr + common->cbपंचांग_off);
पूर्ण

अटल व्योम process_पूर्णांकerlaced_mode(पूर्णांक fid, काष्ठा common_obj *common)
अणु
	/* device field id and local field id are in sync */
	/* If this is even field */
	अगर (0 == fid) अणु
		अगर (common->cur_frm == common->next_frm)
			वापस;

		/* one frame is displayed If next frame is
		 *  available, release cur_frm and move on */
		/* Copy frame display समय */
		common->cur_frm->vb.vb2_buf.बारtamp = kसमय_get_ns();
		/* Change status of the cur_frm */
		vb2_buffer_करोne(&common->cur_frm->vb.vb2_buf,
					VB2_BUF_STATE_DONE);
		/* Make cur_frm poपूर्णांकing to next_frm */
		common->cur_frm = common->next_frm;

	पूर्ण अन्यथा अगर (1 == fid) अणु	/* odd field */
		spin_lock(&common->irqlock);
		अगर (list_empty(&common->dma_queue)
		    || (common->cur_frm != common->next_frm)) अणु
			spin_unlock(&common->irqlock);
			वापस;
		पूर्ण
		spin_unlock(&common->irqlock);
		/* one field is displayed configure the next
		 * frame अगर it is available अन्यथा hold on current
		 * frame */
		/* Get next from the buffer queue */
		process_progressive_mode(common);
	पूर्ण
पूर्ण

/*
 * vpअगर_channel_isr: It changes status of the displayed buffer, takes next
 * buffer from the queue and sets its address in VPIF रेजिस्टरs
 */
अटल irqवापस_t vpअगर_channel_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vpअगर_device *dev = &vpअगर_obj;
	काष्ठा channel_obj *ch;
	काष्ठा common_obj *common;
	पूर्णांक fid = -1, i;
	पूर्णांक channel_id;

	channel_id = *(पूर्णांक *)(dev_id);
	अगर (!vpअगर_पूर्णांकr_status(channel_id + 2))
		वापस IRQ_NONE;

	ch = dev->dev[channel_id];
	क्रम (i = 0; i < VPIF_NUMOBJECTS; i++) अणु
		common = &ch->common[i];
		/* If streaming is started in this channel */

		अगर (1 == ch->vpअगरparams.std_info.frm_fmt) अणु
			spin_lock(&common->irqlock);
			अगर (list_empty(&common->dma_queue)) अणु
				spin_unlock(&common->irqlock);
				जारी;
			पूर्ण
			spin_unlock(&common->irqlock);

			/* Progressive mode */
			अगर (!channel_first_पूर्णांक[i][channel_id]) अणु
				/* Mark status of the cur_frm to
				 * करोne and unlock semaphore on it */
				common->cur_frm->vb.vb2_buf.बारtamp =
						kसमय_get_ns();
				vb2_buffer_करोne(&common->cur_frm->vb.vb2_buf,
						VB2_BUF_STATE_DONE);
				/* Make cur_frm poपूर्णांकing to next_frm */
				common->cur_frm = common->next_frm;
			पूर्ण

			channel_first_पूर्णांक[i][channel_id] = 0;
			process_progressive_mode(common);
		पूर्ण अन्यथा अणु
			/* Interlaced mode */
			/* If it is first पूर्णांकerrupt, ignore it */

			अगर (channel_first_पूर्णांक[i][channel_id]) अणु
				channel_first_पूर्णांक[i][channel_id] = 0;
				जारी;
			पूर्ण

			अगर (0 == i) अणु
				ch->field_id ^= 1;
				/* Get field id from VPIF रेजिस्टरs */
				fid = vpअगर_channel_getfid(ch->channel_id + 2);
				/* If fid करोes not match with stored field id */
				अगर (fid != ch->field_id) अणु
					/* Make them in sync */
					अगर (0 == fid)
						ch->field_id = fid;

					वापस IRQ_HANDLED;
				पूर्ण
			पूर्ण
			process_पूर्णांकerlaced_mode(fid, common);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vpअगर_update_std_info(काष्ठा channel_obj *ch)
अणु
	काष्ठा video_obj *vid_ch = &ch->video;
	काष्ठा vpअगर_params *vpअगरparams = &ch->vpअगरparams;
	काष्ठा vpअगर_channel_config_params *std_info = &vpअगरparams->std_info;
	स्थिर काष्ठा vpअगर_channel_config_params *config;

	पूर्णांक i;

	क्रम (i = 0; i < vpअगर_ch_params_count; i++) अणु
		config = &vpअगर_ch_params[i];
		अगर (config->hd_sd == 0) अणु
			vpअगर_dbg(2, debug, "SD format\n");
			अगर (config->stdid & vid_ch->stdid) अणु
				स_नकल(std_info, config, माप(*config));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (i == vpअगर_ch_params_count) अणु
		vpअगर_dbg(1, debug, "Format not found\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_update_resolution(काष्ठा channel_obj *ch)
अणु
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा video_obj *vid_ch = &ch->video;
	काष्ठा vpअगर_params *vpअगरparams = &ch->vpअगरparams;
	काष्ठा vpअगर_channel_config_params *std_info = &vpअगरparams->std_info;

	अगर (!vid_ch->stdid && !vid_ch->dv_timings.bt.height)
		वापस -EINVAL;

	अगर (vid_ch->stdid) अणु
		अगर (vpअगर_update_std_info(ch))
			वापस -EINVAL;
	पूर्ण

	common->fmt.fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_YUV422P;
	common->fmt.fmt.pix.width = std_info->width;
	common->fmt.fmt.pix.height = std_info->height;
	vpअगर_dbg(1, debug, "Pixel details: Width = %d,Height = %d\n",
			common->fmt.fmt.pix.width, common->fmt.fmt.pix.height);

	/* Set height and width paramateres */
	common->height = std_info->height;
	common->width = std_info->width;
	common->fmt.fmt.pix.sizeimage = common->height * common->width * 2;

	अगर (vid_ch->stdid)
		common->fmt.fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	अन्यथा
		common->fmt.fmt.pix.colorspace = V4L2_COLORSPACE_REC709;

	अगर (ch->vpअगरparams.std_info.frm_fmt)
		common->fmt.fmt.pix.field = V4L2_FIELD_NONE;
	अन्यथा
		common->fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	वापस 0;
पूर्ण

/*
 * vpअगर_calculate_offsets: This function calculates buffers offset क्रम Y and C
 * in the top and bottom field
 */
अटल व्योम vpअगर_calculate_offsets(काष्ठा channel_obj *ch)
अणु
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा vpअगर_params *vpअगरparams = &ch->vpअगरparams;
	क्रमागत v4l2_field field = common->fmt.fmt.pix.field;
	काष्ठा video_obj *vid_ch = &ch->video;
	अचिन्हित पूर्णांक hpitch, sizeimage;

	अगर (V4L2_FIELD_ANY == common->fmt.fmt.pix.field) अणु
		अगर (ch->vpअगरparams.std_info.frm_fmt)
			vid_ch->buf_field = V4L2_FIELD_NONE;
		अन्यथा
			vid_ch->buf_field = V4L2_FIELD_INTERLACED;
	पूर्ण अन्यथा अणु
		vid_ch->buf_field = common->fmt.fmt.pix.field;
	पूर्ण

	sizeimage = common->fmt.fmt.pix.sizeimage;

	hpitch = common->fmt.fmt.pix.bytesperline;
	अगर ((V4L2_FIELD_NONE == vid_ch->buf_field) ||
	    (V4L2_FIELD_INTERLACED == vid_ch->buf_field)) अणु
		common->ytop_off = 0;
		common->ybपंचांग_off = hpitch;
		common->ctop_off = sizeimage / 2;
		common->cbपंचांग_off = sizeimage / 2 + hpitch;
	पूर्ण अन्यथा अगर (V4L2_FIELD_SEQ_TB == vid_ch->buf_field) अणु
		common->ytop_off = 0;
		common->ybपंचांग_off = sizeimage / 4;
		common->ctop_off = sizeimage / 2;
		common->cbपंचांग_off = common->ctop_off + sizeimage / 4;
	पूर्ण अन्यथा अगर (V4L2_FIELD_SEQ_BT == vid_ch->buf_field) अणु
		common->ybपंचांग_off = 0;
		common->ytop_off = sizeimage / 4;
		common->cbपंचांग_off = sizeimage / 2;
		common->ctop_off = common->cbपंचांग_off + sizeimage / 4;
	पूर्ण

	अगर ((V4L2_FIELD_NONE == vid_ch->buf_field) ||
	    (V4L2_FIELD_INTERLACED == vid_ch->buf_field)) अणु
		vpअगरparams->video_params.storage_mode = 1;
	पूर्ण अन्यथा अणु
		vpअगरparams->video_params.storage_mode = 0;
	पूर्ण

	अगर (ch->vpअगरparams.std_info.frm_fmt == 1) अणु
		vpअगरparams->video_params.hpitch =
		    common->fmt.fmt.pix.bytesperline;
	पूर्ण अन्यथा अणु
		अगर ((field == V4L2_FIELD_ANY) ||
			(field == V4L2_FIELD_INTERLACED))
			vpअगरparams->video_params.hpitch =
			    common->fmt.fmt.pix.bytesperline * 2;
		अन्यथा
			vpअगरparams->video_params.hpitch =
			    common->fmt.fmt.pix.bytesperline;
	पूर्ण

	ch->vpअगरparams.video_params.stdid = ch->vpअगरparams.std_info.stdid;
पूर्ण

अटल व्योम vpअगर_config_addr(काष्ठा channel_obj *ch, पूर्णांक muxmode)
अणु
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];

	अगर (VPIF_CHANNEL3_VIDEO == ch->channel_id) अणु
		common->set_addr = ch3_set_videobuf_addr;
	पूर्ण अन्यथा अणु
		अगर (2 == muxmode)
			common->set_addr = ch2_set_videobuf_addr_yc_nmux;
		अन्यथा
			common->set_addr = ch2_set_videobuf_addr;
	पूर्ण
पूर्ण

/* functions implementing ioctls */
/**
 * vpअगर_querycap() - QUERYCAP handler
 * @file: file ptr
 * @priv: file handle
 * @cap: ptr to v4l2_capability काष्ठाure
 */
अटल पूर्णांक vpअगर_querycap(काष्ठा file *file, व्योम  *priv,
				काष्ठा v4l2_capability *cap)
अणु
	काष्ठा vpअगर_display_config *config = vpअगर_dev->platक्रमm_data;

	strscpy(cap->driver, VPIF_DRIVER_NAME, माप(cap->driver));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(vpअगर_dev));
	strscpy(cap->card, config->card_name, माप(cap->card));

	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *fmt)
अणु
	अगर (fmt->index != 0)
		वापस -EINVAL;

	/* Fill in the inक्रमmation about क्रमmat */
	fmt->pixelक्रमmat = V4L2_PIX_FMT_YUV422P;
	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_g_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];

	/* Check the validity of the buffer type */
	अगर (common->fmt.type != fmt->type)
		वापस -EINVAL;

	अगर (vpअगर_update_resolution(ch))
		वापस -EINVAL;
	*fmt = common->fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_try_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &fmt->fmt.pix;

	/*
	 * to suppress v4l-compliance warnings silently correct
	 * the pixelक्रमmat
	 */
	अगर (pixfmt->pixelक्रमmat != V4L2_PIX_FMT_YUV422P)
		pixfmt->pixelक्रमmat = common->fmt.fmt.pix.pixelक्रमmat;

	अगर (vpअगर_update_resolution(ch))
		वापस -EINVAL;

	pixfmt->colorspace = common->fmt.fmt.pix.colorspace;
	pixfmt->field = common->fmt.fmt.pix.field;
	pixfmt->bytesperline = common->fmt.fmt.pix.width;
	pixfmt->width = common->fmt.fmt.pix.width;
	pixfmt->height = common->fmt.fmt.pix.height;
	pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height * 2;

	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_s_fmt_vid_out(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &fmt->fmt.pix;
	पूर्णांक ret;

	अगर (vb2_is_busy(&common->buffer_queue))
		वापस -EBUSY;

	ret = vpअगर_try_fmt_vid_out(file, priv, fmt);
	अगर (ret)
		वापस ret;

	/* store the pix क्रमmat in the channel object */
	common->fmt.fmt.pix = *pixfmt;

	/* store the क्रमmat in the channel object */
	common->fmt = *fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std_id)
अणु
	काष्ठा vpअगर_display_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा vpअगर_display_chan_config *chan_cfg;
	काष्ठा v4l2_output output;
	पूर्णांक ret;

	अगर (!config->chan_config[ch->channel_id].outमाला_दो)
		वापस -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	output = chan_cfg->outमाला_दो[ch->output_idx].output;
	अगर (output.capabilities != V4L2_OUT_CAP_STD)
		वापस -ENODATA;

	अगर (vb2_is_busy(&common->buffer_queue))
		वापस -EBUSY;


	अगर (!(std_id & VPIF_V4L2_STD))
		वापस -EINVAL;

	/* Call encoder subdevice function to set the standard */
	ch->video.stdid = std_id;
	स_रखो(&ch->video.dv_timings, 0, माप(ch->video.dv_timings));
	/* Get the inक्रमmation about the standard */
	अगर (vpअगर_update_resolution(ch))
		वापस -EINVAL;

	common->fmt.fmt.pix.bytesperline = common->fmt.fmt.pix.width;

	ret = v4l2_device_call_until_err(&vpअगर_obj.v4l2_dev, 1, video,
						s_std_output, std_id);
	अगर (ret < 0) अणु
		vpअगर_err("Failed to set output standard\n");
		वापस ret;
	पूर्ण

	ret = v4l2_device_call_until_err(&vpअगर_obj.v4l2_dev, 1, video,
							s_std, std_id);
	अगर (ret < 0)
		vpअगर_err("Failed to set standard for sub devices\n");
	वापस ret;
पूर्ण

अटल पूर्णांक vpअगर_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा vpअगर_display_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_display_chan_config *chan_cfg;
	काष्ठा v4l2_output output;

	अगर (!config->chan_config[ch->channel_id].outमाला_दो)
		वापस -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	output = chan_cfg->outमाला_दो[ch->output_idx].output;
	अगर (output.capabilities != V4L2_OUT_CAP_STD)
		वापस -ENODATA;

	*std = ch->video.stdid;
	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_क्रमागत_output(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_output *output)
अणु

	काष्ठा vpअगर_display_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_display_chan_config *chan_cfg;

	chan_cfg = &config->chan_config[ch->channel_id];
	अगर (output->index >= chan_cfg->output_count) अणु
		vpअगर_dbg(1, debug, "Invalid output index\n");
		वापस -EINVAL;
	पूर्ण

	*output = chan_cfg->outमाला_दो[output->index].output;
	वापस 0;
पूर्ण

/**
 * vpअगर_output_to_subdev() - Maps output to sub device
 * @vpअगर_cfg: global config ptr
 * @chan_cfg: channel config ptr
 * @index: Given output index from application
 *
 * lookup the sub device inक्रमmation क्रम a given output index.
 * we report all the output to application. output table also
 * has sub device name क्रम the each output
 */
अटल पूर्णांक
vpअगर_output_to_subdev(काष्ठा vpअगर_display_config *vpअगर_cfg,
		      काष्ठा vpअगर_display_chan_config *chan_cfg, पूर्णांक index)
अणु
	काष्ठा vpअगर_subdev_info *subdev_info;
	स्थिर अक्षर *subdev_name;
	पूर्णांक i;

	vpअगर_dbg(2, debug, "vpif_output_to_subdev\n");

	अगर (!chan_cfg->outमाला_दो)
		वापस -1;

	subdev_name = chan_cfg->outमाला_दो[index].subdev_name;
	अगर (!subdev_name)
		वापस -1;

	/* loop through the sub device list to get the sub device info */
	क्रम (i = 0; i < vpअगर_cfg->subdev_count; i++) अणु
		subdev_info = &vpअगर_cfg->subdevinfo[i];
		अगर (!म_भेद(subdev_info->name, subdev_name))
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

/**
 * vpअगर_set_output() - Select an output
 * @vpअगर_cfg: global config ptr
 * @ch: channel
 * @index: Given output index from application
 *
 * Select the given output.
 */
अटल पूर्णांक vpअगर_set_output(काष्ठा vpअगर_display_config *vpअगर_cfg,
		      काष्ठा channel_obj *ch, पूर्णांक index)
अणु
	काष्ठा vpअगर_display_chan_config *chan_cfg =
		&vpअगर_cfg->chan_config[ch->channel_id];
	काष्ठा v4l2_subdev *sd = शून्य;
	u32 input = 0, output = 0;
	पूर्णांक sd_index;
	पूर्णांक ret;

	sd_index = vpअगर_output_to_subdev(vpअगर_cfg, chan_cfg, index);
	अगर (sd_index >= 0)
		sd = vpअगर_obj.sd[sd_index];

	अगर (sd) अणु
		input = chan_cfg->outमाला_दो[index].input_route;
		output = chan_cfg->outमाला_दो[index].output_route;
		ret = v4l2_subdev_call(sd, video, s_routing, input, output, 0);
		अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
			vpअगर_err("Failed to set output\n");
			वापस ret;
		पूर्ण

	पूर्ण
	ch->output_idx = index;
	ch->sd = sd;
	अगर (chan_cfg->outमाला_दो)
		/* update tvnorms from the sub device output info */
		ch->video_dev.tvnorms = chan_cfg->outमाला_दो[index].output.std;
	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_s_output(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा vpअगर_display_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_display_chan_config *chan_cfg;
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];

	अगर (vb2_is_busy(&common->buffer_queue))
		वापस -EBUSY;

	chan_cfg = &config->chan_config[ch->channel_id];

	अगर (i >= chan_cfg->output_count)
		वापस -EINVAL;

	वापस vpअगर_set_output(config, ch, i);
पूर्ण

अटल पूर्णांक vpअगर_g_output(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);

	*i = ch->output_idx;

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
	काष्ठा vpअगर_display_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_display_chan_config *chan_cfg;
	काष्ठा v4l2_output output;
	पूर्णांक ret;

	अगर (!config->chan_config[ch->channel_id].outमाला_दो)
		वापस -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	output = chan_cfg->outमाला_दो[ch->output_idx].output;
	अगर (output.capabilities != V4L2_OUT_CAP_DV_TIMINGS)
		वापस -ENODATA;

	timings->pad = 0;

	ret = v4l2_subdev_call(ch->sd, pad, क्रमागत_dv_timings, timings);
	अगर (ret == -ENOIOCTLCMD || ret == -ENODEV)
		वापस -EINVAL;
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
	काष्ठा vpअगर_display_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_params *vpअगरparams = &ch->vpअगरparams;
	काष्ठा common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	काष्ठा vpअगर_channel_config_params *std_info = &vpअगरparams->std_info;
	काष्ठा video_obj *vid_ch = &ch->video;
	काष्ठा v4l2_bt_timings *bt = &vid_ch->dv_timings.bt;
	काष्ठा vpअगर_display_chan_config *chan_cfg;
	काष्ठा v4l2_output output;
	पूर्णांक ret;

	अगर (!config->chan_config[ch->channel_id].outमाला_दो)
		वापस -ENODATA;

	chan_cfg = &config->chan_config[ch->channel_id];
	output = chan_cfg->outमाला_दो[ch->output_idx].output;
	अगर (output.capabilities != V4L2_OUT_CAP_DV_TIMINGS)
		वापस -ENODATA;

	अगर (vb2_is_busy(&common->buffer_queue))
		वापस -EBUSY;

	अगर (timings->type != V4L2_DV_BT_656_1120) अणु
		vpअगर_dbg(2, debug, "Timing type not defined\n");
		वापस -EINVAL;
	पूर्ण

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
	काष्ठा vpअगर_display_config *config = vpअगर_dev->platक्रमm_data;
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा channel_obj *ch = video_get_drvdata(vdev);
	काष्ठा vpअगर_display_chan_config *chan_cfg;
	काष्ठा video_obj *vid_ch = &ch->video;
	काष्ठा v4l2_output output;

	अगर (!config->chan_config[ch->channel_id].outमाला_दो)
		जाओ error;

	chan_cfg = &config->chan_config[ch->channel_id];
	output = chan_cfg->outमाला_दो[ch->output_idx].output;

	अगर (output.capabilities != V4L2_OUT_CAP_DV_TIMINGS)
		जाओ error;

	*timings = vid_ch->dv_timings;

	वापस 0;
error:
	वापस -ENODATA;
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

/* vpअगर display ioctl operations */
अटल स्थिर काष्ठा v4l2_ioctl_ops vpअगर_ioctl_ops = अणु
	.vidioc_querycap		= vpअगर_querycap,
	.vidioc_क्रमागत_fmt_vid_out	= vpअगर_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out		= vpअगर_g_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= vpअगर_s_fmt_vid_out,
	.vidioc_try_fmt_vid_out		= vpअगर_try_fmt_vid_out,

	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,

	.vidioc_s_std			= vpअगर_s_std,
	.vidioc_g_std			= vpअगर_g_std,

	.vidioc_क्रमागत_output		= vpअगर_क्रमागत_output,
	.vidioc_s_output		= vpअगर_s_output,
	.vidioc_g_output		= vpअगर_g_output,

	.vidioc_क्रमागत_dv_timings		= vpअगर_क्रमागत_dv_timings,
	.vidioc_s_dv_timings		= vpअगर_s_dv_timings,
	.vidioc_g_dv_timings		= vpअगर_g_dv_timings,

	.vidioc_log_status		= vpअगर_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations vpअगर_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.release	= vb2_fop_release,
	.unlocked_ioctl	= video_ioctl2,
	.mmap		= vb2_fop_mmap,
	.poll		= vb2_fop_poll
पूर्ण;

/*Configure the channels, buffer sizei, request irq */
अटल पूर्णांक initialize_vpअगर(व्योम)
अणु
	पूर्णांक मुक्त_channel_objects_index;
	पूर्णांक err, i, j;

	/* Allocate memory क्रम six channel objects */
	क्रम (i = 0; i < VPIF_DISPLAY_MAX_DEVICES; i++) अणु
		vpअगर_obj.dev[i] =
		    kzalloc(माप(काष्ठा channel_obj), GFP_KERNEL);
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

अटल व्योम मुक्त_vpअगर_objs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VPIF_DISPLAY_MAX_DEVICES; i++)
		kमुक्त(vpअगर_obj.dev[i]);
पूर्ण

अटल पूर्णांक vpअगर_probe_complete(व्योम)
अणु
	काष्ठा common_obj *common;
	काष्ठा video_device *vdev;
	काष्ठा channel_obj *ch;
	काष्ठा vb2_queue *q;
	पूर्णांक j, err, k;

	क्रम (j = 0; j < VPIF_DISPLAY_MAX_DEVICES; j++) अणु
		ch = vpअगर_obj.dev[j];
		/* Initialize field of the channel objects */
		क्रम (k = 0; k < VPIF_NUMOBJECTS; k++) अणु
			common = &ch->common[k];
			spin_lock_init(&common->irqlock);
			mutex_init(&common->lock);
			common->set_addr = शून्य;
			common->ytop_off = 0;
			common->ybपंचांग_off = 0;
			common->ctop_off = 0;
			common->cbपंचांग_off = 0;
			common->cur_frm = शून्य;
			common->next_frm = शून्य;
			स_रखो(&common->fmt, 0, माप(common->fmt));
		पूर्ण
		ch->initialized = 0;
		अगर (vpअगर_obj.config->subdev_count)
			ch->sd = vpअगर_obj.sd[0];
		ch->channel_id = j;

		स_रखो(&ch->vpअगरparams, 0, माप(ch->vpअगरparams));

		ch->common[VPIF_VIDEO_INDEX].fmt.type =
						V4L2_BUF_TYPE_VIDEO_OUTPUT;

		/* select output 0 */
		err = vpअगर_set_output(vpअगर_obj.config, ch, 0);
		अगर (err)
			जाओ probe_out;

		/* set initial क्रमmat */
		ch->video.stdid = V4L2_STD_525_60;
		स_रखो(&ch->video.dv_timings, 0, माप(ch->video.dv_timings));
		vpअगर_update_resolution(ch);

		/* Initialize vb2 queue */
		q = &common->buffer_queue;
		q->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
		q->drv_priv = ch;
		q->ops = &video_qops;
		q->mem_ops = &vb2_dma_contig_memops;
		q->buf_काष्ठा_size = माप(काष्ठा vpअगर_disp_buffer);
		q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
		q->min_buffers_needed = 1;
		q->lock = &common->lock;
		q->dev = vpअगर_dev;
		err = vb2_queue_init(q);
		अगर (err) अणु
			vpअगर_err("vpif_display: vb2_queue_init() failed\n");
			जाओ probe_out;
		पूर्ण

		INIT_LIST_HEAD(&common->dma_queue);

		/* रेजिस्टर video device */
		vpअगर_dbg(1, debug, "channel=%p,channel->video_dev=%p\n",
			 ch, &ch->video_dev);

		/* Initialize the video_device काष्ठाure */
		vdev = &ch->video_dev;
		strscpy(vdev->name, VPIF_DRIVER_NAME, माप(vdev->name));
		vdev->release = video_device_release_empty;
		vdev->fops = &vpअगर_fops;
		vdev->ioctl_ops = &vpअगर_ioctl_ops;
		vdev->v4l2_dev = &vpअगर_obj.v4l2_dev;
		vdev->vfl_dir = VFL_सूची_TX;
		vdev->queue = q;
		vdev->lock = &common->lock;
		vdev->device_caps = V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_STREAMING;
		video_set_drvdata(&ch->video_dev, ch);
		err = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO,
					    (j ? 3 : 2));
		अगर (err < 0)
			जाओ probe_out;
	पूर्ण

	वापस 0;

probe_out:
	क्रम (k = 0; k < j; k++) अणु
		ch = vpअगर_obj.dev[k];
		video_unरेजिस्टर_device(&ch->video_dev);
	पूर्ण
	वापस err;
पूर्ण

/*
 * vpअगर_probe: This function creates device entries by रेजिस्टर itself to the
 * V4L2 driver and initializes fields of each channel objects
 */
अटल __init पूर्णांक vpअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpअगर_subdev_info *subdevdata;
	काष्ठा i2c_adapter *i2c_adap;
	काष्ठा resource *res;
	पूर्णांक subdev_count;
	पूर्णांक res_idx = 0;
	पूर्णांक i, err;

	अगर (!pdev->dev.platक्रमm_data) अणु
		dev_warn(&pdev->dev, "Missing platform data.  Giving up.\n");
		वापस -EINVAL;
	पूर्ण

	vpअगर_dev = &pdev->dev;
	err = initialize_vpअगर();

	अगर (err) अणु
		v4l2_err(vpअगर_dev->driver, "Error initializing vpif\n");
		वापस err;
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
			vpअगर_err("VPIF IRQ request failed\n");
			जाओ vpअगर_unरेजिस्टर;
		पूर्ण
		res_idx++;
	पूर्ण

	vpअगर_obj.config = pdev->dev.platक्रमm_data;
	subdev_count = vpअगर_obj.config->subdev_count;
	subdevdata = vpअगर_obj.config->subdevinfo;
	vpअगर_obj.sd = kसुस्मृति(subdev_count, माप(*vpअगर_obj.sd), GFP_KERNEL);
	अगर (!vpअगर_obj.sd) अणु
		err = -ENOMEM;
		जाओ vpअगर_unरेजिस्टर;
	पूर्ण

	i2c_adap = i2c_get_adapter(vpअगर_obj.config->i2c_adapter_id);
	क्रम (i = 0; i < subdev_count; i++) अणु
		vpअगर_obj.sd[i] =
			v4l2_i2c_new_subdev_board(&vpअगर_obj.v4l2_dev,
						  i2c_adap,
						  &subdevdata[i].board_info,
						  शून्य);
		अगर (!vpअगर_obj.sd[i]) अणु
			vpअगर_err("Error registering v4l2 subdevice\n");
			err = -ENODEV;
			जाओ probe_subdev_out;
		पूर्ण

		अगर (vpअगर_obj.sd[i])
			vpअगर_obj.sd[i]->grp_id = 1 << i;
	पूर्ण
	err = vpअगर_probe_complete();
	अगर (err)
		जाओ probe_subdev_out;

	वापस 0;

probe_subdev_out:
	kमुक्त(vpअगर_obj.sd);
vpअगर_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&vpअगर_obj.v4l2_dev);
vpअगर_मुक्त:
	मुक्त_vpअगर_objs();

	वापस err;
पूर्ण

/*
 * vpअगर_हटाओ: It un-रेजिस्टर channels from V4L2 driver
 */
अटल पूर्णांक vpअगर_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा channel_obj *ch;
	पूर्णांक i;

	v4l2_device_unरेजिस्टर(&vpअगर_obj.v4l2_dev);

	kमुक्त(vpअगर_obj.sd);
	/* un-रेजिस्टर device */
	क्रम (i = 0; i < VPIF_DISPLAY_MAX_DEVICES; i++) अणु
		/* Get the poपूर्णांकer to the channel object */
		ch = vpअगर_obj.dev[i];
		/* Unरेजिस्टर video device */
		video_unरेजिस्टर_device(&ch->video_dev);
	पूर्ण
	मुक्त_vpअगर_objs();

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक vpअगर_suspend(काष्ठा device *dev)
अणु
	काष्ठा common_obj *common;
	काष्ठा channel_obj *ch;
	पूर्णांक i;

	क्रम (i = 0; i < VPIF_DISPLAY_MAX_DEVICES; i++) अणु
		/* Get the poपूर्णांकer to the channel object */
		ch = vpअगर_obj.dev[i];
		common = &ch->common[VPIF_VIDEO_INDEX];

		अगर (!vb2_start_streaming_called(&common->buffer_queue))
			जारी;

		mutex_lock(&common->lock);
		/* Disable channel */
		अगर (ch->channel_id == VPIF_CHANNEL2_VIDEO) अणु
			enable_channel2(0);
			channel2_पूर्णांकr_enable(0);
		पूर्ण
		अगर (ch->channel_id == VPIF_CHANNEL3_VIDEO ||
			ycmux_mode == 2) अणु
			enable_channel3(0);
			channel3_पूर्णांकr_enable(0);
		पूर्ण
		mutex_unlock(&common->lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vpअगर_resume(काष्ठा device *dev)
अणु

	काष्ठा common_obj *common;
	काष्ठा channel_obj *ch;
	पूर्णांक i;

	क्रम (i = 0; i < VPIF_DISPLAY_MAX_DEVICES; i++) अणु
		/* Get the poपूर्णांकer to the channel object */
		ch = vpअगर_obj.dev[i];
		common = &ch->common[VPIF_VIDEO_INDEX];

		अगर (!vb2_start_streaming_called(&common->buffer_queue))
			जारी;

		mutex_lock(&common->lock);
		/* Enable channel */
		अगर (ch->channel_id == VPIF_CHANNEL2_VIDEO) अणु
			enable_channel2(1);
			channel2_पूर्णांकr_enable(1);
		पूर्ण
		अगर (ch->channel_id == VPIF_CHANNEL3_VIDEO ||
				ycmux_mode == 2) अणु
			enable_channel3(1);
			channel3_पूर्णांकr_enable(1);
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
	.probe	= vpअगर_probe,
	.हटाओ	= vpअगर_हटाओ,
पूर्ण;

module_platक्रमm_driver(vpअगर_driver);
