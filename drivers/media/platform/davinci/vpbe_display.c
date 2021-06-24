<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com/
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/रुको.h>
#समावेश <linux/समय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>


#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/davinci/vpbe_display.h>
#समावेश <media/davinci/vpbe_types.h>
#समावेश <media/davinci/vpbe.h>
#समावेश <media/davinci/vpbe_venc.h>
#समावेश <media/davinci/vpbe_osd.h>
#समावेश "vpbe_venc_regs.h"

#घोषणा VPBE_DISPLAY_DRIVER "vpbe-v4l2"

अटल पूर्णांक debug;

#घोषणा VPBE_DEFAULT_NUM_BUFS 3

module_param(debug, पूर्णांक, 0644);

अटल पूर्णांक vpbe_set_osd_display_params(काष्ठा vpbe_display *disp_dev,
			काष्ठा vpbe_layer *layer);

अटल पूर्णांक venc_is_second_field(काष्ठा vpbe_display *disp_dev)
अणु
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	पूर्णांक ret, val;

	ret = v4l2_subdev_call(vpbe_dev->venc,
			       core,
			       ioctl,
			       VENC_GET_FLD,
			       &val);
	अगर (ret < 0) अणु
		v4l2_err(&vpbe_dev->v4l2_dev,
			 "Error in getting Field ID 0\n");
		वापस 1;
	पूर्ण
	वापस val;
पूर्ण

अटल व्योम vpbe_isr_even_field(काष्ठा vpbe_display *disp_obj,
				काष्ठा vpbe_layer *layer)
अणु
	अगर (layer->cur_frm == layer->next_frm)
		वापस;

	layer->cur_frm->vb.vb2_buf.बारtamp = kसमय_get_ns();
	vb2_buffer_करोne(&layer->cur_frm->vb.vb2_buf, VB2_BUF_STATE_DONE);
	/* Make cur_frm poपूर्णांकing to next_frm */
	layer->cur_frm = layer->next_frm;
पूर्ण

अटल व्योम vpbe_isr_odd_field(काष्ठा vpbe_display *disp_obj,
				काष्ठा vpbe_layer *layer)
अणु
	काष्ठा osd_state *osd_device = disp_obj->osd_device;
	अचिन्हित दीर्घ addr;

	spin_lock(&disp_obj->dma_queue_lock);
	अगर (list_empty(&layer->dma_queue) ||
		(layer->cur_frm != layer->next_frm)) अणु
		spin_unlock(&disp_obj->dma_queue_lock);
		वापस;
	पूर्ण
	/*
	 * one field is displayed configure
	 * the next frame अगर it is available
	 * otherwise hold on current frame
	 * Get next from the buffer queue
	 */
	layer->next_frm = list_entry(layer->dma_queue.next,
			  काष्ठा  vpbe_disp_buffer, list);
	/* Remove that from the buffer queue */
	list_del(&layer->next_frm->list);
	spin_unlock(&disp_obj->dma_queue_lock);
	/* Mark state of the frame to active */
	layer->next_frm->vb.vb2_buf.state = VB2_BUF_STATE_ACTIVE;
	addr = vb2_dma_contig_plane_dma_addr(&layer->next_frm->vb.vb2_buf, 0);
	osd_device->ops.start_layer(osd_device,
			layer->layer_info.id,
			addr,
			disp_obj->cbcr_ofst);
पूर्ण

/* पूर्णांकerrupt service routine */
अटल irqवापस_t venc_isr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा vpbe_display *disp_dev = (काष्ठा vpbe_display *)arg;
	काष्ठा vpbe_layer *layer;
	अटल अचिन्हित last_event;
	अचिन्हित event = 0;
	पूर्णांक fid;
	पूर्णांक i;

	अगर (!arg || !disp_dev->dev[0])
		वापस IRQ_HANDLED;

	अगर (venc_is_second_field(disp_dev))
		event |= VENC_SECOND_FIELD;
	अन्यथा
		event |= VENC_FIRST_FIELD;

	अगर (event == (last_event & ~VENC_END_OF_FRAME)) अणु
		/*
		* If the display is non-पूर्णांकerlaced, then we need to flag the
		* end-of-frame event at every पूर्णांकerrupt regardless of the
		* value of the FIDST bit.  We can conclude that the display is
		* non-पूर्णांकerlaced अगर the value of the FIDST bit is unchanged
		* from the previous पूर्णांकerrupt.
		*/
		event |= VENC_END_OF_FRAME;
	पूर्ण अन्यथा अगर (event == VENC_SECOND_FIELD) अणु
		/* end-of-frame क्रम पूर्णांकerlaced display */
		event |= VENC_END_OF_FRAME;
	पूर्ण
	last_event = event;

	क्रम (i = 0; i < VPBE_DISPLAY_MAX_DEVICES; i++) अणु
		layer = disp_dev->dev[i];

		अगर (!vb2_start_streaming_called(&layer->buffer_queue))
			जारी;

		अगर (layer->layer_first_पूर्णांक) अणु
			layer->layer_first_पूर्णांक = 0;
			जारी;
		पूर्ण
		/* Check the field क्रमmat */
		अगर ((V4L2_FIELD_NONE == layer->pix_fmt.field) &&
			(event & VENC_END_OF_FRAME)) अणु
			/* Progressive mode */

			vpbe_isr_even_field(disp_dev, layer);
			vpbe_isr_odd_field(disp_dev, layer);
		पूर्ण अन्यथा अणु
		/* Interlaced mode */

			layer->field_id ^= 1;
			अगर (event & VENC_FIRST_FIELD)
				fid = 0;
			अन्यथा
				fid = 1;

			/*
			* If field id करोes not match with store
			* field id
			*/
			अगर (fid != layer->field_id) अणु
				/* Make them in sync */
				layer->field_id = fid;
				जारी;
			पूर्ण
			/*
			* device field id and local field id are
			* in sync. If this is even field
			*/
			अगर (0 == fid)
				vpbe_isr_even_field(disp_dev, layer);
			अन्यथा  /* odd field */
				vpbe_isr_odd_field(disp_dev, layer);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * vpbe_buffer_prepare()
 * This is the callback function called from vb2_qbuf() function
 * the buffer is prepared and user space भव address is converted पूर्णांकo
 * physical address
 */
अटल पूर्णांक vpbe_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_queue *q = vb->vb2_queue;
	काष्ठा vpbe_layer *layer = vb2_get_drv_priv(q);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	अचिन्हित दीर्घ addr;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
				"vpbe_buffer_prepare\n");

	vb2_set_plane_payload(vb, 0, layer->pix_fmt.sizeimage);
	अगर (vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0))
		वापस -EINVAL;

	addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	अगर (!IS_ALIGNED(addr, 8)) अणु
		v4l2_err(&vpbe_dev->v4l2_dev,
			 "buffer_prepare:offset is not aligned to 32 bytes\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * vpbe_buffer_setup()
 * This function allocates memory क्रम the buffers
 */
अटल पूर्णांक
vpbe_buffer_queue_setup(काष्ठा vb2_queue *vq,
			अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])

अणु
	/* Get the file handle object and layer object */
	काष्ठा vpbe_layer *layer = vb2_get_drv_priv(vq);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "vpbe_buffer_setup\n");

	/* Store number of buffers allocated in numbuffer member */
	अगर (vq->num_buffers + *nbuffers < VPBE_DEFAULT_NUM_BUFS)
		*nbuffers = VPBE_DEFAULT_NUM_BUFS - vq->num_buffers;

	अगर (*nplanes)
		वापस sizes[0] < layer->pix_fmt.sizeimage ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = layer->pix_fmt.sizeimage;

	वापस 0;
पूर्ण

/*
 * vpbe_buffer_queue()
 * This function adds the buffer to DMA queue
 */
अटल व्योम vpbe_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	/* Get the file handle object and layer object */
	काष्ठा vpbe_disp_buffer *buf = container_of(vbuf,
				काष्ठा vpbe_disp_buffer, vb);
	काष्ठा vpbe_layer *layer = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vpbe_display *disp = layer->disp_dev;
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	अचिन्हित दीर्घ flags;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
			"vpbe_buffer_queue\n");

	/* add the buffer to the DMA queue */
	spin_lock_irqsave(&disp->dma_queue_lock, flags);
	list_add_tail(&buf->list, &layer->dma_queue);
	spin_unlock_irqrestore(&disp->dma_queue_lock, flags);
पूर्ण

अटल पूर्णांक vpbe_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा vpbe_layer *layer = vb2_get_drv_priv(vq);
	काष्ठा osd_state *osd_device = layer->disp_dev->osd_device;
	पूर्णांक ret;

	osd_device->ops.disable_layer(osd_device, layer->layer_info.id);

	/* Get the next frame from the buffer queue */
	layer->next_frm = layer->cur_frm = list_entry(layer->dma_queue.next,
				काष्ठा vpbe_disp_buffer, list);
	/* Remove buffer from the buffer queue */
	list_del(&layer->cur_frm->list);
	/* Mark state of the current frame to active */
	layer->cur_frm->vb.vb2_buf.state = VB2_BUF_STATE_ACTIVE;
	/* Initialize field_id and started member */
	layer->field_id = 0;

	/* Set parameters in OSD and VENC */
	ret = vpbe_set_osd_display_params(layer->disp_dev, layer);
	अगर (ret < 0) अणु
		काष्ठा vpbe_disp_buffer *buf, *पंचांगp;

		vb2_buffer_करोne(&layer->cur_frm->vb.vb2_buf,
				VB2_BUF_STATE_QUEUED);
		list_क्रम_each_entry_safe(buf, पंचांगp, &layer->dma_queue, list) अणु
			list_del(&buf->list);
			vb2_buffer_करोne(&buf->vb.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण

		वापस ret;
	पूर्ण

	/*
	 * अगर request क्रमmat is yuv420 semiplanar, need to
	 * enable both video winकरोws
	 */
	layer->layer_first_पूर्णांक = 1;

	वापस ret;
पूर्ण

अटल व्योम vpbe_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा vpbe_layer *layer = vb2_get_drv_priv(vq);
	काष्ठा osd_state *osd_device = layer->disp_dev->osd_device;
	काष्ठा vpbe_display *disp = layer->disp_dev;
	अचिन्हित दीर्घ flags;

	अगर (!vb2_is_streaming(vq))
		वापस;

	osd_device->ops.disable_layer(osd_device, layer->layer_info.id);

	/* release all active buffers */
	spin_lock_irqsave(&disp->dma_queue_lock, flags);
	अगर (layer->cur_frm == layer->next_frm) अणु
		vb2_buffer_करोne(&layer->cur_frm->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
	पूर्ण अन्यथा अणु
		अगर (layer->cur_frm)
			vb2_buffer_करोne(&layer->cur_frm->vb.vb2_buf,
					VB2_BUF_STATE_ERROR);
		अगर (layer->next_frm)
			vb2_buffer_करोne(&layer->next_frm->vb.vb2_buf,
					VB2_BUF_STATE_ERROR);
	पूर्ण

	जबतक (!list_empty(&layer->dma_queue)) अणु
		layer->next_frm = list_entry(layer->dma_queue.next,
						काष्ठा vpbe_disp_buffer, list);
		list_del(&layer->next_frm->list);
		vb2_buffer_करोne(&layer->next_frm->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&disp->dma_queue_lock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops video_qops = अणु
	.queue_setup = vpbe_buffer_queue_setup,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.buf_prepare = vpbe_buffer_prepare,
	.start_streaming = vpbe_start_streaming,
	.stop_streaming = vpbe_stop_streaming,
	.buf_queue = vpbe_buffer_queue,
पूर्ण;

अटल
काष्ठा vpbe_layer*
_vpbe_display_get_other_win_layer(काष्ठा vpbe_display *disp_dev,
			काष्ठा vpbe_layer *layer)
अणु
	क्रमागत vpbe_display_device_id thiswin, otherwin;
	thiswin = layer->device_id;

	otherwin = (thiswin == VPBE_DISPLAY_DEVICE_0) ?
	VPBE_DISPLAY_DEVICE_1 : VPBE_DISPLAY_DEVICE_0;
	वापस disp_dev->dev[otherwin];
पूर्ण

अटल पूर्णांक vpbe_set_osd_display_params(काष्ठा vpbe_display *disp_dev,
			काष्ठा vpbe_layer *layer)
अणु
	काष्ठा osd_layer_config *cfg  = &layer->layer_info.config;
	काष्ठा osd_state *osd_device = disp_dev->osd_device;
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	अचिन्हित दीर्घ addr;
	पूर्णांक ret;

	addr = vb2_dma_contig_plane_dma_addr(&layer->cur_frm->vb.vb2_buf, 0);
	/* Set address in the display रेजिस्टरs */
	osd_device->ops.start_layer(osd_device,
				    layer->layer_info.id,
				    addr,
				    disp_dev->cbcr_ofst);

	ret = osd_device->ops.enable_layer(osd_device,
				layer->layer_info.id, 0);
	अगर (ret < 0) अणु
		v4l2_err(&vpbe_dev->v4l2_dev,
			"Error in enabling osd window layer 0\n");
		वापस -1;
	पूर्ण

	/* Enable the winकरोw */
	layer->layer_info.enable = 1;
	अगर (cfg->pixfmt == PIXFMT_NV12) अणु
		काष्ठा vpbe_layer *otherlayer =
			_vpbe_display_get_other_win_layer(disp_dev, layer);

		ret = osd_device->ops.enable_layer(osd_device,
				otherlayer->layer_info.id, 1);
		अगर (ret < 0) अणु
			v4l2_err(&vpbe_dev->v4l2_dev,
				"Error in enabling osd window layer 1\n");
			वापस -1;
		पूर्ण
		otherlayer->layer_info.enable = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
vpbe_disp_calculate_scale_factor(काष्ठा vpbe_display *disp_dev,
			काष्ठा vpbe_layer *layer,
			पूर्णांक expected_xsize, पूर्णांक expected_ysize)
अणु
	काष्ठा display_layer_info *layer_info = &layer->layer_info;
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &layer->pix_fmt;
	काष्ठा osd_layer_config *cfg  = &layer->layer_info.config;
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	पूर्णांक calculated_xsize;
	पूर्णांक h_exp = 0;
	पूर्णांक v_exp = 0;
	पूर्णांक h_scale;
	पूर्णांक v_scale;

	v4l2_std_id standard_id = vpbe_dev->current_timings.std_id;

	/*
	 * Application initially set the image क्रमmat. Current display
	 * size is obtained from the vpbe display controller. expected_xsize
	 * and expected_ysize are set through S_SELECTION ioctl. Based on this,
	 * driver will calculate the scale factors क्रम vertical and
	 * horizontal direction so that the image is displayed scaled
	 * and expanded. Application uses expansion to display the image
	 * in a square pixel. Otherwise it is displayed using displays
	 * pixel aspect ratio.It is expected that application chooses
	 * the crop coordinates क्रम cropped or scaled display. अगर crop
	 * size is less than the image size, it is displayed cropped or
	 * it is displayed scaled and/or expanded.
	 *
	 * to begin with, set the crop winकरोw same as expected. Later we
	 * will override with scaled winकरोw size
	 */

	cfg->xsize = pixfmt->width;
	cfg->ysize = pixfmt->height;
	layer_info->h_zoom = ZOOM_X1;	/* no horizontal zoom */
	layer_info->v_zoom = ZOOM_X1;	/* no horizontal zoom */
	layer_info->h_exp = H_EXP_OFF;	/* no horizontal zoom */
	layer_info->v_exp = V_EXP_OFF;	/* no horizontal zoom */

	अगर (pixfmt->width < expected_xsize) अणु
		h_scale = vpbe_dev->current_timings.xres / pixfmt->width;
		अगर (h_scale < 2)
			h_scale = 1;
		अन्यथा अगर (h_scale >= 4)
			h_scale = 4;
		अन्यथा
			h_scale = 2;
		cfg->xsize *= h_scale;
		अगर (cfg->xsize < expected_xsize) अणु
			अगर ((standard_id & V4L2_STD_525_60) ||
			(standard_id & V4L2_STD_625_50)) अणु
				calculated_xsize = (cfg->xsize *
					VPBE_DISPLAY_H_EXP_RATIO_N) /
					VPBE_DISPLAY_H_EXP_RATIO_D;
				अगर (calculated_xsize <= expected_xsize) अणु
					h_exp = 1;
					cfg->xsize = calculated_xsize;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (h_scale == 2)
			layer_info->h_zoom = ZOOM_X2;
		अन्यथा अगर (h_scale == 4)
			layer_info->h_zoom = ZOOM_X4;
		अगर (h_exp)
			layer_info->h_exp = H_EXP_9_OVER_8;
	पूर्ण अन्यथा अणु
		/* no scaling, only cropping. Set display area to crop area */
		cfg->xsize = expected_xsize;
	पूर्ण

	अगर (pixfmt->height < expected_ysize) अणु
		v_scale = expected_ysize / pixfmt->height;
		अगर (v_scale < 2)
			v_scale = 1;
		अन्यथा अगर (v_scale >= 4)
			v_scale = 4;
		अन्यथा
			v_scale = 2;
		cfg->ysize *= v_scale;
		अगर (cfg->ysize < expected_ysize) अणु
			अगर ((standard_id & V4L2_STD_625_50)) अणु
				calculated_xsize = (cfg->ysize *
					VPBE_DISPLAY_V_EXP_RATIO_N) /
					VPBE_DISPLAY_V_EXP_RATIO_D;
				अगर (calculated_xsize <= expected_ysize) अणु
					v_exp = 1;
					cfg->ysize = calculated_xsize;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (v_scale == 2)
			layer_info->v_zoom = ZOOM_X2;
		अन्यथा अगर (v_scale == 4)
			layer_info->v_zoom = ZOOM_X4;
		अगर (v_exp)
			layer_info->v_exp = V_EXP_6_OVER_5;
	पूर्ण अन्यथा अणु
		/* no scaling, only cropping. Set display area to crop area */
		cfg->ysize = expected_ysize;
	पूर्ण
	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
		"crop display xsize = %d, ysize = %d\n",
		cfg->xsize, cfg->ysize);
पूर्ण

अटल व्योम vpbe_disp_adj_position(काष्ठा vpbe_display *disp_dev,
			काष्ठा vpbe_layer *layer,
			पूर्णांक top, पूर्णांक left)
अणु
	काष्ठा osd_layer_config *cfg = &layer->layer_info.config;
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;

	cfg->xpos = min((अचिन्हित पूर्णांक)left,
			vpbe_dev->current_timings.xres - cfg->xsize);
	cfg->ypos = min((अचिन्हित पूर्णांक)top,
			vpbe_dev->current_timings.yres - cfg->ysize);

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
		"new xpos = %d, ypos = %d\n",
		cfg->xpos, cfg->ypos);
पूर्ण

अटल व्योम vpbe_disp_check_winकरोw_params(काष्ठा vpbe_display *disp_dev,
			काष्ठा v4l2_rect *c)
अणु
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;

	अगर ((c->width == 0) ||
	  ((c->width + c->left) > vpbe_dev->current_timings.xres))
		c->width = vpbe_dev->current_timings.xres - c->left;

	अगर ((c->height == 0) || ((c->height + c->top) >
	  vpbe_dev->current_timings.yres))
		c->height = vpbe_dev->current_timings.yres - c->top;

	/* winकरोw height must be even क्रम पूर्णांकerlaced display */
	अगर (vpbe_dev->current_timings.पूर्णांकerlaced)
		c->height &= (~0x01);

पूर्ण

/*
 * vpbe_try_क्रमmat()
 * If user application provides width and height, and have bytesperline set
 * to zero, driver calculates bytesperline and sizeimage based on hardware
 * limits.
 */
अटल पूर्णांक vpbe_try_क्रमmat(काष्ठा vpbe_display *disp_dev,
			काष्ठा v4l2_pix_क्रमmat *pixfmt, पूर्णांक check)
अणु
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	पूर्णांक min_height = 1;
	पूर्णांक min_width = 32;
	पूर्णांक max_height;
	पूर्णांक max_width;
	पूर्णांक bpp;

	अगर ((pixfmt->pixelक्रमmat != V4L2_PIX_FMT_UYVY) &&
	    (pixfmt->pixelक्रमmat != V4L2_PIX_FMT_NV12))
		/* choose शेष as V4L2_PIX_FMT_UYVY */
		pixfmt->pixelक्रमmat = V4L2_PIX_FMT_UYVY;

	/* Check the field क्रमmat */
	अगर ((pixfmt->field != V4L2_FIELD_INTERLACED) &&
		(pixfmt->field != V4L2_FIELD_NONE)) अणु
		अगर (vpbe_dev->current_timings.पूर्णांकerlaced)
			pixfmt->field = V4L2_FIELD_INTERLACED;
		अन्यथा
			pixfmt->field = V4L2_FIELD_NONE;
	पूर्ण

	अगर (pixfmt->field == V4L2_FIELD_INTERLACED)
		min_height = 2;

	अगर (pixfmt->pixelक्रमmat == V4L2_PIX_FMT_NV12)
		bpp = 1;
	अन्यथा
		bpp = 2;

	max_width = vpbe_dev->current_timings.xres;
	max_height = vpbe_dev->current_timings.yres;

	min_width /= bpp;

	अगर (!pixfmt->width || (pixfmt->width < min_width) ||
		(pixfmt->width > max_width)) अणु
		pixfmt->width = vpbe_dev->current_timings.xres;
	पूर्ण

	अगर (!pixfmt->height || (pixfmt->height  < min_height) ||
		(pixfmt->height  > max_height)) अणु
		pixfmt->height = vpbe_dev->current_timings.yres;
	पूर्ण

	अगर (pixfmt->bytesperline < (pixfmt->width * bpp))
		pixfmt->bytesperline = pixfmt->width * bpp;

	/* Make the bytesperline 32 byte aligned */
	pixfmt->bytesperline = ((pixfmt->width * bpp + 31) & ~31);

	अगर (pixfmt->pixelक्रमmat == V4L2_PIX_FMT_NV12)
		pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height +
				(pixfmt->bytesperline * pixfmt->height >> 1);
	अन्यथा
		pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;

	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_display_querycap(काष्ठा file *file, व्योम  *priv,
			       काष्ठा v4l2_capability *cap)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	snम_लिखो(cap->driver, माप(cap->driver), "%s",
		dev_name(vpbe_dev->pdev));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(vpbe_dev->pdev));
	strscpy(cap->card, vpbe_dev->cfg->module_name, माप(cap->card));

	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_display_s_selection(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_selection *sel)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_display *disp_dev = layer->disp_dev;
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	काष्ठा osd_layer_config *cfg = &layer->layer_info.config;
	काष्ठा osd_state *osd_device = disp_dev->osd_device;
	काष्ठा v4l2_rect rect = sel->r;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
		"VIDIOC_S_SELECTION, layer id = %d\n", layer->device_id);

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	अगर (rect.top < 0)
		rect.top = 0;
	अगर (rect.left < 0)
		rect.left = 0;

	vpbe_disp_check_winकरोw_params(disp_dev, &rect);

	osd_device->ops.get_layer_config(osd_device,
			layer->layer_info.id, cfg);

	vpbe_disp_calculate_scale_factor(disp_dev, layer,
					rect.width,
					rect.height);
	vpbe_disp_adj_position(disp_dev, layer, rect.top,
					rect.left);
	ret = osd_device->ops.set_layer_config(osd_device,
				layer->layer_info.id, cfg);
	अगर (ret < 0) अणु
		v4l2_err(&vpbe_dev->v4l2_dev,
			"Error in set layer config:\n");
		वापस -EINVAL;
	पूर्ण

	/* apply zooming and h or v expansion */
	osd_device->ops.set_zoom(osd_device,
			layer->layer_info.id,
			layer->layer_info.h_zoom,
			layer->layer_info.v_zoom);
	ret = osd_device->ops.set_vid_expansion(osd_device,
			layer->layer_info.h_exp,
			layer->layer_info.v_exp);
	अगर (ret < 0) अणु
		v4l2_err(&vpbe_dev->v4l2_dev,
		"Error in set vid expansion:\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((layer->layer_info.h_zoom != ZOOM_X1) ||
		(layer->layer_info.v_zoom != ZOOM_X1) ||
		(layer->layer_info.h_exp != H_EXP_OFF) ||
		(layer->layer_info.v_exp != V_EXP_OFF))
		/* Enable expansion filter */
		osd_device->ops.set_पूर्णांकerpolation_filter(osd_device, 1);
	अन्यथा
		osd_device->ops.set_पूर्णांकerpolation_filter(osd_device, 0);

	sel->r = rect;
	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_display_g_selection(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_selection *sel)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा osd_layer_config *cfg = &layer->layer_info.config;
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	काष्ठा osd_state *osd_device = layer->disp_dev->osd_device;
	काष्ठा v4l2_rect *rect = &sel->r;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
			"VIDIOC_G_SELECTION, layer id = %d\n",
			layer->device_id);

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		osd_device->ops.get_layer_config(osd_device,
						 layer->layer_info.id, cfg);
		rect->top = cfg->ypos;
		rect->left = cfg->xpos;
		rect->width = cfg->xsize;
		rect->height = cfg->ysize;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		rect->left = 0;
		rect->top = 0;
		rect->width = vpbe_dev->current_timings.xres;
		rect->height = vpbe_dev->current_timings.yres;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_display_g_pixelaspect(काष्ठा file *file, व्योम *priv,
				      पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_CROPCAP ioctl\n");

	अगर (type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	*f = vpbe_dev->current_timings.aspect;
	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_display_g_fmt(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
			"VIDIOC_G_FMT, layer id = %d\n",
			layer->device_id);

	/* If buffer type is video output */
	अगर (V4L2_BUF_TYPE_VIDEO_OUTPUT != fmt->type) अणु
		v4l2_err(&vpbe_dev->v4l2_dev, "invalid type\n");
		वापस -EINVAL;
	पूर्ण
	/* Fill in the inक्रमmation about क्रमmat */
	fmt->fmt.pix = layer->pix_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_display_क्रमागत_fmt(काष्ठा file *file, व्योम  *priv,
				   काष्ठा v4l2_fmtdesc *fmt)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
				"VIDIOC_ENUM_FMT, layer id = %d\n",
				layer->device_id);
	अगर (fmt->index > 1) अणु
		v4l2_err(&vpbe_dev->v4l2_dev, "Invalid format index\n");
		वापस -EINVAL;
	पूर्ण

	/* Fill in the inक्रमmation about क्रमmat */
	अगर (fmt->index == 0)
		fmt->pixelक्रमmat = V4L2_PIX_FMT_UYVY;
	अन्यथा
		fmt->pixelक्रमmat = V4L2_PIX_FMT_NV12;

	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_display_s_fmt(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_display *disp_dev = layer->disp_dev;
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	काष्ठा osd_layer_config *cfg  = &layer->layer_info.config;
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &fmt->fmt.pix;
	काष्ठा osd_state *osd_device = disp_dev->osd_device;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
			"VIDIOC_S_FMT, layer id = %d\n",
			layer->device_id);

	अगर (vb2_is_busy(&layer->buffer_queue))
		वापस -EBUSY;

	अगर (V4L2_BUF_TYPE_VIDEO_OUTPUT != fmt->type) अणु
		v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "invalid type\n");
		वापस -EINVAL;
	पूर्ण
	/* Check क्रम valid pixel क्रमmat */
	ret = vpbe_try_क्रमmat(disp_dev, pixfmt, 1);
	अगर (ret)
		वापस ret;

	/* YUV420 is requested, check availability of the
	other video winकरोw */

	layer->pix_fmt = *pixfmt;
	अगर (pixfmt->pixelक्रमmat == V4L2_PIX_FMT_NV12) अणु
		काष्ठा vpbe_layer *otherlayer;

		otherlayer = _vpbe_display_get_other_win_layer(disp_dev, layer);
		/* अगर other layer is available, only
		 * claim it, करो not configure it
		 */
		ret = osd_device->ops.request_layer(osd_device,
						    otherlayer->layer_info.id);
		अगर (ret < 0) अणु
			v4l2_err(&vpbe_dev->v4l2_dev,
				 "Display Manager failed to allocate layer\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Get osd layer config */
	osd_device->ops.get_layer_config(osd_device,
			layer->layer_info.id, cfg);
	/* Store the pixel क्रमmat in the layer object */
	cfg->xsize = pixfmt->width;
	cfg->ysize = pixfmt->height;
	cfg->line_length = pixfmt->bytesperline;
	cfg->ypos = 0;
	cfg->xpos = 0;
	cfg->पूर्णांकerlaced = vpbe_dev->current_timings.पूर्णांकerlaced;

	अगर (V4L2_PIX_FMT_UYVY == pixfmt->pixelक्रमmat)
		cfg->pixfmt = PIXFMT_YCBCRI;

	/* Change of the शेष pixel क्रमmat क्रम both video winकरोws */
	अगर (V4L2_PIX_FMT_NV12 == pixfmt->pixelक्रमmat) अणु
		काष्ठा vpbe_layer *otherlayer;
		cfg->pixfmt = PIXFMT_NV12;
		otherlayer = _vpbe_display_get_other_win_layer(disp_dev,
								layer);
		otherlayer->layer_info.config.pixfmt = PIXFMT_NV12;
	पूर्ण

	/* Set the layer config in the osd winकरोw */
	ret = osd_device->ops.set_layer_config(osd_device,
				layer->layer_info.id, cfg);
	अगर (ret < 0) अणु
		v4l2_err(&vpbe_dev->v4l2_dev,
				"Error in S_FMT params:\n");
		वापस -EINVAL;
	पूर्ण

	/* Readback and fill the local copy of current pix क्रमmat */
	osd_device->ops.get_layer_config(osd_device,
			layer->layer_info.id, cfg);

	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_display_try_fmt(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_display *disp_dev = layer->disp_dev;
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	काष्ठा v4l2_pix_क्रमmat *pixfmt = &fmt->fmt.pix;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_TRY_FMT\n");

	अगर (V4L2_BUF_TYPE_VIDEO_OUTPUT != fmt->type) अणु
		v4l2_err(&vpbe_dev->v4l2_dev, "invalid type\n");
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम valid field क्रमmat */
	वापस  vpbe_try_क्रमmat(disp_dev, pixfmt, 0);

पूर्ण

/*
 * vpbe_display_s_std - Set the given standard in the encoder
 *
 * Sets the standard अगर supported by the current encoder. Return the status.
 * 0 - success & -EINVAL on error
 */
अटल पूर्णांक vpbe_display_s_std(काष्ठा file *file, व्योम *priv,
				v4l2_std_id std_id)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_S_STD\n");

	अगर (vb2_is_busy(&layer->buffer_queue))
		वापस -EBUSY;

	अगर (vpbe_dev->ops.s_std) अणु
		ret = vpbe_dev->ops.s_std(vpbe_dev, std_id);
		अगर (ret) अणु
			v4l2_err(&vpbe_dev->v4l2_dev,
			"Failed to set standard for sub devices\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vpbe_display_g_std - Get the standard in the current encoder
 *
 * Get the standard in the current encoder. Return the status. 0 - success
 * -EINVAL on error
 */
अटल पूर्णांक vpbe_display_g_std(काष्ठा file *file, व्योम *priv,
				v4l2_std_id *std_id)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,	"VIDIOC_G_STD\n");

	/* Get the standard from the current encoder */
	अगर (vpbe_dev->current_timings.timings_type & VPBE_ENC_STD) अणु
		*std_id = vpbe_dev->current_timings.std_id;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * vpbe_display_क्रमागत_output - क्रमागतerate outमाला_दो
 *
 * Enumerates the outमाला_दो available at the vpbe display
 * वापसs the status, -EINVAL अगर end of output list
 */
अटल पूर्णांक vpbe_display_क्रमागत_output(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_output *output)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,	"VIDIOC_ENUM_OUTPUT\n");

	/* Enumerate outमाला_दो */
	अगर (!vpbe_dev->ops.क्रमागत_outमाला_दो)
		वापस -EINVAL;

	ret = vpbe_dev->ops.क्रमागत_outमाला_दो(vpbe_dev, output);
	अगर (ret) अणु
		v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
			"Failed to enumerate outputs\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vpbe_display_s_output - Set output to
 * the output specअगरied by the index
 */
अटल पूर्णांक vpbe_display_s_output(काष्ठा file *file, व्योम *priv,
				अचिन्हित पूर्णांक i)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,	"VIDIOC_S_OUTPUT\n");

	अगर (vb2_is_busy(&layer->buffer_queue))
		वापस -EBUSY;

	अगर (!vpbe_dev->ops.set_output)
		वापस -EINVAL;

	ret = vpbe_dev->ops.set_output(vpbe_dev, i);
	अगर (ret) अणु
		v4l2_err(&vpbe_dev->v4l2_dev,
			"Failed to set output for sub devices\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vpbe_display_g_output - Get output from subdevice
 * क्रम a given by the index
 */
अटल पूर्णांक vpbe_display_g_output(काष्ठा file *file, व्योम *priv,
				अचिन्हित पूर्णांक *i)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_G_OUTPUT\n");
	/* Get the standard from the current encoder */
	*i = vpbe_dev->current_out_index;

	वापस 0;
पूर्ण

/*
 * vpbe_display_क्रमागत_dv_timings - Enumerate the dv timings
 *
 * क्रमागत the timings in the current encoder. Return the status. 0 - success
 * -EINVAL on error
 */
अटल पूर्णांक
vpbe_display_क्रमागत_dv_timings(काष्ठा file *file, व्योम *priv,
			काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_ENUM_DV_TIMINGS\n");

	/* Enumerate outमाला_दो */
	अगर (!vpbe_dev->ops.क्रमागत_dv_timings)
		वापस -EINVAL;

	ret = vpbe_dev->ops.क्रमागत_dv_timings(vpbe_dev, timings);
	अगर (ret) अणु
		v4l2_err(&vpbe_dev->v4l2_dev,
			"Failed to enumerate dv timings info\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vpbe_display_s_dv_timings - Set the dv timings
 *
 * Set the timings in the current encoder. Return the status. 0 - success
 * -EINVAL on error
 */
अटल पूर्णांक
vpbe_display_s_dv_timings(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	पूर्णांक ret;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_S_DV_TIMINGS\n");

	अगर (vb2_is_busy(&layer->buffer_queue))
		वापस -EBUSY;

	/* Set the given standard in the encoder */
	अगर (!vpbe_dev->ops.s_dv_timings)
		वापस -EINVAL;

	ret = vpbe_dev->ops.s_dv_timings(vpbe_dev, timings);
	अगर (ret) अणु
		v4l2_err(&vpbe_dev->v4l2_dev,
			"Failed to set the dv timings info\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vpbe_display_g_dv_timings - Set the dv timings
 *
 * Get the timings in the current encoder. Return the status. 0 - success
 * -EINVAL on error
 */
अटल पूर्णांक
vpbe_display_g_dv_timings(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_dv_timings *dv_timings)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "VIDIOC_G_DV_TIMINGS\n");

	/* Get the given standard in the encoder */

	अगर (vpbe_dev->current_timings.timings_type &
				VPBE_ENC_DV_TIMINGS) अणु
		*dv_timings = vpbe_dev->current_timings.dv_timings;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * vpbe_display_खोलो()
 * It creates object of file handle काष्ठाure and stores it in निजी_data
 * member of filepoपूर्णांकer
 */
अटल पूर्णांक vpbe_display_खोलो(काष्ठा file *file)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा vpbe_display *disp_dev = layer->disp_dev;
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	काष्ठा osd_state *osd_device = disp_dev->osd_device;
	पूर्णांक err;

	/* creating context क्रम file descriptor */
	err = v4l2_fh_खोलो(file);
	अगर (err) अणु
		v4l2_err(&vpbe_dev->v4l2_dev, "v4l2_fh_open failed\n");
		वापस err;
	पूर्ण

	/* leaving अगर layer is alपढ़ोy initialized */
	अगर (!v4l2_fh_is_singular_file(file))
		वापस err;

	अगर (!layer->usrs) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&layer->opslock))
			वापस -ERESTARTSYS;
		/* First claim the layer क्रम this device */
		err = osd_device->ops.request_layer(osd_device,
						layer->layer_info.id);
		mutex_unlock(&layer->opslock);
		अगर (err < 0) अणु
			/* Couldn't get layer */
			v4l2_err(&vpbe_dev->v4l2_dev,
				"Display Manager failed to allocate layer\n");
			v4l2_fh_release(file);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* Increment layer usrs counter */
	layer->usrs++;
	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
			"vpbe display device opened successfully\n");
	वापस 0;
पूर्ण

/*
 * vpbe_display_release()
 * This function deletes buffer queue, मुक्तs the buffers and the davinci
 * display file * handle
 */
अटल पूर्णांक vpbe_display_release(काष्ठा file *file)
अणु
	काष्ठा vpbe_layer *layer = video_drvdata(file);
	काष्ठा osd_layer_config *cfg  = &layer->layer_info.config;
	काष्ठा vpbe_display *disp_dev = layer->disp_dev;
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	काष्ठा osd_state *osd_device = disp_dev->osd_device;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "vpbe_display_release\n");

	mutex_lock(&layer->opslock);

	osd_device->ops.disable_layer(osd_device,
			layer->layer_info.id);
	/* Decrement layer usrs counter */
	layer->usrs--;
	/* If this file handle has initialize encoder device, reset it */
	अगर (!layer->usrs) अणु
		अगर (cfg->pixfmt == PIXFMT_NV12) अणु
			काष्ठा vpbe_layer *otherlayer;
			otherlayer =
			_vpbe_display_get_other_win_layer(disp_dev, layer);
			osd_device->ops.disable_layer(osd_device,
					otherlayer->layer_info.id);
			osd_device->ops.release_layer(osd_device,
					otherlayer->layer_info.id);
		पूर्ण
		osd_device->ops.disable_layer(osd_device,
				layer->layer_info.id);
		osd_device->ops.release_layer(osd_device,
				layer->layer_info.id);
	पूर्ण

	_vb2_fop_release(file, शून्य);
	mutex_unlock(&layer->opslock);

	disp_dev->cbcr_ofst = 0;

	वापस 0;
पूर्ण

/* vpbe capture ioctl operations */
अटल स्थिर काष्ठा v4l2_ioctl_ops vpbe_ioctl_ops = अणु
	.vidioc_querycap	 = vpbe_display_querycap,
	.vidioc_g_fmt_vid_out    = vpbe_display_g_fmt,
	.vidioc_क्रमागत_fmt_vid_out = vpbe_display_क्रमागत_fmt,
	.vidioc_s_fmt_vid_out    = vpbe_display_s_fmt,
	.vidioc_try_fmt_vid_out  = vpbe_display_try_fmt,

	.vidioc_reqbufs		 = vb2_ioctl_reqbufs,
	.vidioc_create_bufs	 = vb2_ioctl_create_bufs,
	.vidioc_querybuf	 = vb2_ioctl_querybuf,
	.vidioc_qbuf		 = vb2_ioctl_qbuf,
	.vidioc_dqbuf		 = vb2_ioctl_dqbuf,
	.vidioc_streamon	 = vb2_ioctl_streamon,
	.vidioc_streamoff	 = vb2_ioctl_streamoff,
	.vidioc_expbuf		 = vb2_ioctl_expbuf,

	.vidioc_g_pixelaspect	 = vpbe_display_g_pixelaspect,
	.vidioc_g_selection	 = vpbe_display_g_selection,
	.vidioc_s_selection	 = vpbe_display_s_selection,

	.vidioc_s_std		 = vpbe_display_s_std,
	.vidioc_g_std		 = vpbe_display_g_std,

	.vidioc_क्रमागत_output	 = vpbe_display_क्रमागत_output,
	.vidioc_s_output	 = vpbe_display_s_output,
	.vidioc_g_output	 = vpbe_display_g_output,

	.vidioc_s_dv_timings	 = vpbe_display_s_dv_timings,
	.vidioc_g_dv_timings	 = vpbe_display_g_dv_timings,
	.vidioc_क्रमागत_dv_timings	 = vpbe_display_क्रमागत_dv_timings,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations vpbe_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = vpbe_display_खोलो,
	.release = vpbe_display_release,
	.unlocked_ioctl = video_ioctl2,
	.mmap = vb2_fop_mmap,
	.poll =  vb2_fop_poll,
पूर्ण;

अटल पूर्णांक vpbe_device_get(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा vpbe_display *vpbe_disp  = data;

	अगर (म_भेद("vpbe_controller", pdev->name) == 0)
		vpbe_disp->vpbe_dev = platक्रमm_get_drvdata(pdev);

	अगर (म_माला(pdev->name, "vpbe-osd"))
		vpbe_disp->osd_device = platक्रमm_get_drvdata(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक init_vpbe_layer(पूर्णांक i, काष्ठा vpbe_display *disp_dev,
			   काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpbe_layer *vpbe_display_layer = शून्य;
	काष्ठा video_device *vbd = शून्य;

	/* Allocate memory क्रम four plane display objects */
	disp_dev->dev[i] = kzalloc(माप(*disp_dev->dev[i]), GFP_KERNEL);
	अगर (!disp_dev->dev[i])
		वापस  -ENOMEM;

	spin_lock_init(&disp_dev->dev[i]->irqlock);
	mutex_init(&disp_dev->dev[i]->opslock);

	/* Get the poपूर्णांकer to the layer object */
	vpbe_display_layer = disp_dev->dev[i];
	vbd = &vpbe_display_layer->video_dev;
	/* Initialize field of video device */
	vbd->release	= video_device_release_empty;
	vbd->fops	= &vpbe_fops;
	vbd->ioctl_ops	= &vpbe_ioctl_ops;
	vbd->minor	= -1;
	vbd->v4l2_dev   = &disp_dev->vpbe_dev->v4l2_dev;
	vbd->lock	= &vpbe_display_layer->opslock;
	vbd->vfl_dir	= VFL_सूची_TX;
	vbd->device_caps = V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_STREAMING;

	अगर (disp_dev->vpbe_dev->current_timings.timings_type &
			VPBE_ENC_STD)
		vbd->tvnorms = (V4L2_STD_525_60 | V4L2_STD_625_50);

	snम_लिखो(vbd->name, माप(vbd->name),
			"DaVinci_VPBE Display_DRIVER_V%d.%d.%d",
			(VPBE_DISPLAY_VERSION_CODE >> 16) & 0xff,
			(VPBE_DISPLAY_VERSION_CODE >> 8) & 0xff,
			(VPBE_DISPLAY_VERSION_CODE) & 0xff);

	vpbe_display_layer->device_id = i;

	vpbe_display_layer->layer_info.id =
		((i == VPBE_DISPLAY_DEVICE_0) ? WIN_VID0 : WIN_VID1);


	वापस 0;
पूर्ण

अटल पूर्णांक रेजिस्टर_device(काष्ठा vpbe_layer *vpbe_display_layer,
			   काष्ठा vpbe_display *disp_dev,
			   काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;

	v4l2_info(&disp_dev->vpbe_dev->v4l2_dev,
		  "Trying to register VPBE display device.\n");
	v4l2_info(&disp_dev->vpbe_dev->v4l2_dev,
		  "layer=%p,layer->video_dev=%p\n",
		  vpbe_display_layer,
		  &vpbe_display_layer->video_dev);

	vpbe_display_layer->video_dev.queue = &vpbe_display_layer->buffer_queue;
	err = video_रेजिस्टर_device(&vpbe_display_layer->video_dev,
				    VFL_TYPE_VIDEO,
				    -1);
	अगर (err)
		वापस -ENODEV;

	vpbe_display_layer->disp_dev = disp_dev;
	/* set the driver data in platक्रमm device */
	platक्रमm_set_drvdata(pdev, disp_dev);
	video_set_drvdata(&vpbe_display_layer->video_dev,
			  vpbe_display_layer);

	वापस 0;
पूर्ण



/*
 * vpbe_display_probe()
 * This function creates device entries by रेजिस्टर itself to the V4L2 driver
 * and initializes fields of each layer objects
 */
अटल पूर्णांक vpbe_display_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpbe_display *disp_dev;
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा resource *res = शून्य;
	काष्ठा vb2_queue *q;
	पूर्णांक k;
	पूर्णांक i;
	पूर्णांक err;
	पूर्णांक irq;

	prपूर्णांकk(KERN_DEBUG "vpbe_display_probe\n");
	/* Allocate memory क्रम vpbe_display */
	disp_dev = devm_kzalloc(&pdev->dev, माप(*disp_dev), GFP_KERNEL);
	अगर (!disp_dev)
		वापस -ENOMEM;

	spin_lock_init(&disp_dev->dma_queue_lock);
	/*
	 * Scan all the platक्रमm devices to find the vpbe
	 * controller device and get the vpbe_dev object
	 */
	err = bus_क्रम_each_dev(&platक्रमm_bus_type, शून्य, disp_dev,
			vpbe_device_get);
	अगर (err < 0)
		वापस err;

	v4l2_dev = &disp_dev->vpbe_dev->v4l2_dev;
	/* Initialize the vpbe display controller */
	अगर (disp_dev->vpbe_dev->ops.initialize) अणु
		err = disp_dev->vpbe_dev->ops.initialize(&pdev->dev,
							 disp_dev->vpbe_dev);
		अगर (err) अणु
			v4l2_err(v4l2_dev, "Error initing vpbe\n");
			err = -ENOMEM;
			जाओ probe_out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < VPBE_DISPLAY_MAX_DEVICES; i++) अणु
		अगर (init_vpbe_layer(i, disp_dev, pdev)) अणु
			err = -ENODEV;
			जाओ probe_out;
		पूर्ण
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		v4l2_err(v4l2_dev, "Unable to get VENC interrupt resource\n");
		err = -ENODEV;
		जाओ probe_out;
	पूर्ण

	irq = res->start;
	err = devm_request_irq(&pdev->dev, irq, venc_isr, 0,
			       VPBE_DISPLAY_DRIVER, disp_dev);
	अगर (err) अणु
		v4l2_err(v4l2_dev, "VPBE IRQ request failed\n");
		जाओ probe_out;
	पूर्ण

	क्रम (i = 0; i < VPBE_DISPLAY_MAX_DEVICES; i++) अणु
		/* initialize vb2 queue */
		q = &disp_dev->dev[i]->buffer_queue;
		स_रखो(q, 0, माप(*q));
		q->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
		q->drv_priv = disp_dev->dev[i];
		q->ops = &video_qops;
		q->mem_ops = &vb2_dma_contig_memops;
		q->buf_काष्ठा_size = माप(काष्ठा vpbe_disp_buffer);
		q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
		q->min_buffers_needed = 1;
		q->lock = &disp_dev->dev[i]->opslock;
		q->dev = disp_dev->vpbe_dev->pdev;
		err = vb2_queue_init(q);
		अगर (err) अणु
			v4l2_err(v4l2_dev, "vb2_queue_init() failed\n");
			जाओ probe_out;
		पूर्ण

		INIT_LIST_HEAD(&disp_dev->dev[i]->dma_queue);

		अगर (रेजिस्टर_device(disp_dev->dev[i], disp_dev, pdev)) अणु
			err = -ENODEV;
			जाओ probe_out;
		पूर्ण
	पूर्ण

	v4l2_dbg(1, debug, v4l2_dev,
		 "Successfully completed the probing of vpbe v4l2 device\n");

	वापस 0;

probe_out:
	क्रम (k = 0; k < VPBE_DISPLAY_MAX_DEVICES; k++) अणु
		/* Unरेजिस्टर video device */
		अगर (disp_dev->dev[k]) अणु
			video_unरेजिस्टर_device(&disp_dev->dev[k]->video_dev);
			kमुक्त(disp_dev->dev[k]);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/*
 * vpbe_display_हटाओ()
 * It un-रेजिस्टर hardware layer from V4L2 driver
 */
अटल पूर्णांक vpbe_display_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpbe_layer *vpbe_display_layer;
	काष्ठा vpbe_display *disp_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	पूर्णांक i;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "vpbe_display_remove\n");

	/* deinitialize the vpbe display controller */
	अगर (vpbe_dev->ops.deinitialize)
		vpbe_dev->ops.deinitialize(&pdev->dev, vpbe_dev);
	/* un-रेजिस्टर device */
	क्रम (i = 0; i < VPBE_DISPLAY_MAX_DEVICES; i++) अणु
		/* Get the poपूर्णांकer to the layer object */
		vpbe_display_layer = disp_dev->dev[i];
		/* Unरेजिस्टर video device */
		video_unरेजिस्टर_device(&vpbe_display_layer->video_dev);

	पूर्ण
	क्रम (i = 0; i < VPBE_DISPLAY_MAX_DEVICES; i++) अणु
		kमुक्त(disp_dev->dev[i]);
		disp_dev->dev[i] = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vpbe_display_driver = अणु
	.driver = अणु
		.name = VPBE_DISPLAY_DRIVER,
		.bus = &platक्रमm_bus_type,
	पूर्ण,
	.probe = vpbe_display_probe,
	.हटाओ = vpbe_display_हटाओ,
पूर्ण;

module_platक्रमm_driver(vpbe_display_driver);

MODULE_DESCRIPTION("TI DM644x/DM355/DM365 VPBE Display controller");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Texas Instruments");
