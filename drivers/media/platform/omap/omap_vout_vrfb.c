<शैली गुरु>
/*
 * omap_vout_vrfb.c
 *
 * Copyright (C) 2010 Texas Instruments.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */

#समावेश <linux/sched.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-device.h>

#समावेश <video/omapvrfb.h>

#समावेश "omap_voutdef.h"
#समावेश "omap_voutlib.h"
#समावेश "omap_vout_vrfb.h"

#घोषणा OMAP_DMA_NO_DEVICE	0

/*
 * Function क्रम allocating video buffers
 */
अटल पूर्णांक omap_vout_allocate_vrfb_buffers(काष्ठा omap_vout_device *vout,
		अचिन्हित पूर्णांक *count, पूर्णांक startindex)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < *count; i++) अणु
		अगर (!vout->smsshaकरो_virt_addr[i]) अणु
			vout->smsshaकरो_virt_addr[i] =
				omap_vout_alloc_buffer(vout->smsshaकरो_size,
						&vout->smsshaकरो_phy_addr[i]);
		पूर्ण
		अगर (!vout->smsshaकरो_virt_addr[i] && startindex != -1) अणु
			अगर (vout->vq.memory == V4L2_MEMORY_MMAP && i >= startindex)
				अवरोध;
		पूर्ण
		अगर (!vout->smsshaकरो_virt_addr[i]) अणु
			क्रम (j = 0; j < i; j++) अणु
				omap_vout_मुक्त_buffer(
						vout->smsshaकरो_virt_addr[j],
						vout->smsshaकरो_size);
				vout->smsshaकरो_virt_addr[j] = 0;
				vout->smsshaकरो_phy_addr[j] = 0;
			पूर्ण
			*count = 0;
			वापस -ENOMEM;
		पूर्ण
		स_रखो((व्योम *)(दीर्घ)vout->smsshaकरो_virt_addr[i], 0,
		       vout->smsshaकरो_size);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Wakes up the application once the DMA transfer to VRFB space is completed.
 */
अटल व्योम omap_vout_vrfb_dma_tx_callback(व्योम *data)
अणु
	काष्ठा vid_vrfb_dma *t = (काष्ठा vid_vrfb_dma *) data;

	t->tx_status = 1;
	wake_up_पूर्णांकerruptible(&t->रुको);
पूर्ण

/*
 * Free VRFB buffers
 */
व्योम omap_vout_मुक्त_vrfb_buffers(काष्ठा omap_vout_device *vout)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < VRFB_NUM_BUFS; j++) अणु
		अगर (vout->smsshaकरो_virt_addr[j]) अणु
			omap_vout_मुक्त_buffer(vout->smsshaकरो_virt_addr[j],
					      vout->smsshaकरो_size);
			vout->smsshaकरो_virt_addr[j] = 0;
			vout->smsshaकरो_phy_addr[j] = 0;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक omap_vout_setup_vrfb_bufs(काष्ठा platक्रमm_device *pdev, पूर्णांक vid_num,
			      bool अटल_vrfb_allocation)
अणु
	पूर्णांक ret = 0, i, j;
	काष्ठा omap_vout_device *vout;
	काष्ठा video_device *vfd;
	dma_cap_mask_t mask;
	पूर्णांक image_width, image_height;
	पूर्णांक vrfb_num_bufs = VRFB_NUM_BUFS;
	काष्ठा v4l2_device *v4l2_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा omap2video_device *vid_dev =
		container_of(v4l2_dev, काष्ठा omap2video_device, v4l2_dev);

	vout = vid_dev->vouts[vid_num];
	vfd = vout->vfd;

	क्रम (i = 0; i < VRFB_NUM_BUFS; i++) अणु
		अगर (omap_vrfb_request_ctx(&vout->vrfb_context[i])) अणु
			dev_info(&pdev->dev, ": VRFB allocation failed\n");
			क्रम (j = 0; j < i; j++)
				omap_vrfb_release_ctx(&vout->vrfb_context[j]);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Calculate VRFB memory size */
	/* allocate क्रम worst हाल size */
	image_width = VID_MAX_WIDTH / TILE_SIZE;
	अगर (VID_MAX_WIDTH % TILE_SIZE)
		image_width++;

	image_width = image_width * TILE_SIZE;
	image_height = VID_MAX_HEIGHT / TILE_SIZE;

	अगर (VID_MAX_HEIGHT % TILE_SIZE)
		image_height++;

	image_height = image_height * TILE_SIZE;
	vout->smsshaकरो_size = PAGE_ALIGN(image_width * image_height * 2 * 2);

	/*
	 * Request and Initialize DMA, क्रम DMA based VRFB transfer
	 */
	dma_cap_zero(mask);
	dma_cap_set(DMA_INTERLEAVE, mask);
	vout->vrfb_dma_tx.chan = dma_request_chan_by_mask(&mask);
	अगर (IS_ERR(vout->vrfb_dma_tx.chan)) अणु
		vout->vrfb_dma_tx.req_status = DMA_CHAN_NOT_ALLOTED;
	पूर्ण अन्यथा अणु
		माप_प्रकार xt_size = माप(काष्ठा dma_पूर्णांकerleaved_ढाँचा) +
				 माप(काष्ठा data_chunk);

		vout->vrfb_dma_tx.xt = kzalloc(xt_size, GFP_KERNEL);
		अगर (!vout->vrfb_dma_tx.xt) अणु
			dma_release_channel(vout->vrfb_dma_tx.chan);
			vout->vrfb_dma_tx.req_status = DMA_CHAN_NOT_ALLOTED;
		पूर्ण
	पूर्ण

	अगर (vout->vrfb_dma_tx.req_status == DMA_CHAN_NOT_ALLOTED)
		dev_info(&pdev->dev,
			 ": failed to allocate DMA Channel for video%d\n",
			 vfd->minor);

	init_रुकोqueue_head(&vout->vrfb_dma_tx.रुको);

	/*
	 * अटलally allocated the VRFB buffer is करोne through
	 * command line arguments
	 */
	अगर (अटल_vrfb_allocation) अणु
		अगर (omap_vout_allocate_vrfb_buffers(vout, &vrfb_num_bufs, -1)) अणु
			ret =  -ENOMEM;
			जाओ release_vrfb_ctx;
		पूर्ण
		vout->vrfb_अटल_allocation = true;
	पूर्ण
	वापस 0;

release_vrfb_ctx:
	क्रम (j = 0; j < VRFB_NUM_BUFS; j++)
		omap_vrfb_release_ctx(&vout->vrfb_context[j]);
	वापस ret;
पूर्ण

/*
 * Release the VRFB context once the module निकासs
 */
व्योम omap_vout_release_vrfb(काष्ठा omap_vout_device *vout)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VRFB_NUM_BUFS; i++)
		omap_vrfb_release_ctx(&vout->vrfb_context[i]);

	अगर (vout->vrfb_dma_tx.req_status == DMA_CHAN_ALLOTED) अणु
		vout->vrfb_dma_tx.req_status = DMA_CHAN_NOT_ALLOTED;
		kमुक्त(vout->vrfb_dma_tx.xt);
		dmaengine_terminate_sync(vout->vrfb_dma_tx.chan);
		dma_release_channel(vout->vrfb_dma_tx.chan);
	पूर्ण
पूर्ण

/*
 * Allocate the buffers क्रम the VRFB space.  Data is copied from V4L2
 * buffers to the VRFB buffers using the DMA engine.
 */
पूर्णांक omap_vout_vrfb_buffer_setup(काष्ठा omap_vout_device *vout,
			  अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक startindex)
अणु
	पूर्णांक i;
	bool yuv_mode;

	अगर (!is_rotation_enabled(vout))
		वापस 0;

	/* If rotation is enabled, allocate memory क्रम VRFB space also */
	*count = *count > VRFB_NUM_BUFS ? VRFB_NUM_BUFS : *count;

	/* Allocate the VRFB buffers only अगर the buffers are not
	 * allocated during init समय.
	 */
	अगर (!vout->vrfb_अटल_allocation)
		अगर (omap_vout_allocate_vrfb_buffers(vout, count, startindex))
			वापस -ENOMEM;

	अगर (vout->dss_mode == OMAP_DSS_COLOR_YUV2 ||
			vout->dss_mode == OMAP_DSS_COLOR_UYVY)
		yuv_mode = true;
	अन्यथा
		yuv_mode = false;

	क्रम (i = 0; i < *count; i++)
		omap_vrfb_setup(&vout->vrfb_context[i],
				vout->smsshaकरो_phy_addr[i], vout->pix.width,
				vout->pix.height, vout->bpp, yuv_mode);

	वापस 0;
पूर्ण

पूर्णांक omap_vout_prepare_vrfb(काष्ठा omap_vout_device *vout,
			   काष्ठा vb2_buffer *vb)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	क्रमागत dma_ctrl_flags flags = DMA_PREP_INTERRUPT | DMA_CTRL_ACK;
	काष्ठा dma_chan *chan = vout->vrfb_dma_tx.chan;
	काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt = vout->vrfb_dma_tx.xt;
	dma_cookie_t cookie;
	dma_addr_t buf_phy_addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	क्रमागत dma_status status;
	क्रमागत dss_rotation rotation;
	माप_प्रकार dst_icg;
	u32 pixsize;

	अगर (!is_rotation_enabled(vout))
		वापस 0;

	/* If rotation is enabled, copy input buffer पूर्णांकo VRFB
	 * memory space using DMA. We are copying input buffer
	 * पूर्णांकo VRFB memory space of desired angle and DSS will
	 * पढ़ो image VRFB memory क्रम 0 degree angle
	 */

	pixsize = vout->bpp * vout->vrfb_bpp;
	dst_icg = MAX_PIXELS_PER_LINE * pixsize - vout->pix.width * vout->bpp;

	xt->src_start = buf_phy_addr;
	xt->dst_start = vout->vrfb_context[vb->index].paddr[0];

	xt->numf = vout->pix.height;
	xt->frame_size = 1;
	xt->sgl[0].size = vout->pix.width * vout->bpp;
	xt->sgl[0].icg = dst_icg;

	xt->dir = DMA_MEM_TO_MEM;
	xt->src_sgl = false;
	xt->src_inc = true;
	xt->dst_sgl = true;
	xt->dst_inc = true;

	tx = dmaengine_prep_पूर्णांकerleaved_dma(chan, xt, flags);
	अगर (tx == शून्य) अणु
		pr_err("%s: DMA interleaved prep error\n", __func__);
		वापस -EINVAL;
	पूर्ण

	tx->callback = omap_vout_vrfb_dma_tx_callback;
	tx->callback_param = &vout->vrfb_dma_tx;

	cookie = dmaengine_submit(tx);
	अगर (dma_submit_error(cookie)) अणु
		pr_err("%s: dmaengine_submit failed (%d)\n", __func__, cookie);
		वापस -EINVAL;
	पूर्ण

	vout->vrfb_dma_tx.tx_status = 0;
	dma_async_issue_pending(chan);

	रुको_event_पूर्णांकerruptible_समयout(vout->vrfb_dma_tx.रुको,
					 vout->vrfb_dma_tx.tx_status == 1,
					 VRFB_TX_TIMEOUT);

	status = dma_async_is_tx_complete(chan, cookie, शून्य, शून्य);

	अगर (vout->vrfb_dma_tx.tx_status == 0) अणु
		pr_err("%s: Timeout while waiting for DMA\n", __func__);
		dmaengine_terminate_sync(chan);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (status != DMA_COMPLETE) अणु
		pr_err("%s: DMA completion %s status\n", __func__,
		       status == DMA_ERROR ? "error" : "busy");
		dmaengine_terminate_sync(chan);
		वापस -EINVAL;
	पूर्ण

	/* Store buffers physical address पूर्णांकo an array. Addresses
	 * from this array will be used to configure DSS */
	rotation = calc_rotation(vout);
	vout->queued_buf_addr[vb->index] = (u8 *)
		vout->vrfb_context[vb->index].paddr[rotation];
	वापस 0;
पूर्ण

/*
 * Calculate the buffer offsets from which the streaming should
 * start. This offset calculation is मुख्यly required because of
 * the VRFB 32 pixels alignment with rotation.
 */
व्योम omap_vout_calculate_vrfb_offset(काष्ठा omap_vout_device *vout)
अणु
	क्रमागत dss_rotation rotation;
	bool mirroring = vout->mirror;
	काष्ठा v4l2_rect *crop = &vout->crop;
	काष्ठा v4l2_pix_क्रमmat *pix = &vout->pix;
	पूर्णांक *cropped_offset = &vout->cropped_offset;
	पूर्णांक vr_ps = 1, ps = 2, temp_ps = 2;
	पूर्णांक offset = 0, ctop = 0, cleft = 0, line_length = 0;

	rotation = calc_rotation(vout);

	अगर (V4L2_PIX_FMT_YUYV == pix->pixelक्रमmat ||
			V4L2_PIX_FMT_UYVY == pix->pixelक्रमmat) अणु
		अगर (is_rotation_enabled(vout)) अणु
			/*
			 * ps    - Actual pixel size क्रम YUYV/UYVY क्रम
			 *         VRFB/Mirroring is 4 bytes
			 * vr_ps - Virtually pixel size क्रम YUYV/UYVY is
			 *         2 bytes
			 */
			ps = 4;
			vr_ps = 2;
		पूर्ण अन्यथा अणु
			ps = 2;	/* otherwise the pixel size is 2 byte */
		पूर्ण
	पूर्ण अन्यथा अगर (V4L2_PIX_FMT_RGB32 == pix->pixelक्रमmat) अणु
		ps = 4;
	पूर्ण अन्यथा अगर (V4L2_PIX_FMT_RGB24 == pix->pixelक्रमmat) अणु
		ps = 3;
	पूर्ण
	vout->ps = ps;
	vout->vr_ps = vr_ps;

	अगर (is_rotation_enabled(vout)) अणु
		line_length = MAX_PIXELS_PER_LINE;
		ctop = (pix->height - crop->height) - crop->top;
		cleft = (pix->width - crop->width) - crop->left;
	पूर्ण अन्यथा अणु
		line_length = pix->width;
	पूर्ण
	vout->line_length = line_length;
	चयन (rotation) अणु
	हाल dss_rotation_90_degree:
		offset = vout->vrfb_context[0].yoffset *
			vout->vrfb_context[0].bytespp;
		temp_ps = ps / vr_ps;
		अगर (!mirroring) अणु
			*cropped_offset = offset + line_length *
				temp_ps * cleft + crop->top * temp_ps;
		पूर्ण अन्यथा अणु
			*cropped_offset = offset + line_length * temp_ps *
				cleft + crop->top * temp_ps + (line_length *
				((crop->width / (vr_ps)) - 1) * ps);
		पूर्ण
		अवरोध;
	हाल dss_rotation_180_degree:
		offset = ((MAX_PIXELS_PER_LINE * vout->vrfb_context[0].yoffset *
			vout->vrfb_context[0].bytespp) +
			(vout->vrfb_context[0].xoffset *
			vout->vrfb_context[0].bytespp));
		अगर (!mirroring) अणु
			*cropped_offset = offset + (line_length * ps * ctop) +
				(cleft / vr_ps) * ps;

		पूर्ण अन्यथा अणु
			*cropped_offset = offset + (line_length * ps * ctop) +
				(cleft / vr_ps) * ps + (line_length *
				(crop->height - 1) * ps);
		पूर्ण
		अवरोध;
	हाल dss_rotation_270_degree:
		offset = MAX_PIXELS_PER_LINE * vout->vrfb_context[0].xoffset *
			vout->vrfb_context[0].bytespp;
		temp_ps = ps / vr_ps;
		अगर (!mirroring) अणु
			*cropped_offset = offset + line_length *
			    temp_ps * crop->left + ctop * ps;
		पूर्ण अन्यथा अणु
			*cropped_offset = offset + line_length *
				temp_ps * crop->left + ctop * ps +
				(line_length * ((crop->width / vr_ps) - 1) *
				 ps);
		पूर्ण
		अवरोध;
	हाल dss_rotation_0_degree:
		अगर (!mirroring) अणु
			*cropped_offset = (line_length * ps) *
				crop->top + (crop->left / vr_ps) * ps;
		पूर्ण अन्यथा अणु
			*cropped_offset = (line_length * ps) *
				crop->top + (crop->left / vr_ps) * ps +
				(line_length * (crop->height - 1) * ps);
		पूर्ण
		अवरोध;
	शेष:
		*cropped_offset = (line_length * ps * crop->top) /
			vr_ps + (crop->left * ps) / vr_ps +
			((crop->width / vr_ps) - 1) * ps;
		अवरोध;
	पूर्ण
पूर्ण
