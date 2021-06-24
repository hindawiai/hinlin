<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * V4L2 Capture IC Preprocess Subdev क्रम Freescale i.MX5/6 SOC
 *
 * This subdevice handles capture of video frames from the CSI or VDIC,
 * which are routed directly to the Image Converter preprocess tasks,
 * क्रम resizing, colorspace conversion, and rotation.
 *
 * Copyright (c) 2012-2017 Mentor Graphics Inc.
 */
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/imx.h>
#समावेश "imx-media.h"
#समावेश "imx-ic.h"

/*
 * Min/Max supported width and heights.
 *
 * We allow planar output, so we have to align width at the source pad
 * by 16 pixels to meet IDMAC alignment requirements क्रम possible planar
 * output.
 *
 * TODO: move this पूर्णांकo pad क्रमmat negotiation, अगर capture device
 * has not requested a planar क्रमmat, we should allow 8 pixel
 * alignment at the source pad.
 */
#घोषणा MIN_W_SINK   32
#घोषणा MIN_H_SINK   32
#घोषणा MAX_W_SINK 4096
#घोषणा MAX_H_SINK 4096
#घोषणा W_ALIGN_SINK  3 /* multiple of 8 pixels */
#घोषणा H_ALIGN_SINK  1 /* multiple of 2 lines */

#घोषणा MAX_W_SRC  1024
#घोषणा MAX_H_SRC  1024
#घोषणा W_ALIGN_SRC   1 /* multiple of 2 pixels */
#घोषणा H_ALIGN_SRC   1 /* multiple of 2 lines */

#घोषणा S_ALIGN       1 /* multiple of 2 */

काष्ठा prp_priv अणु
	काष्ठा imx_ic_priv *ic_priv;
	काष्ठा media_pad pad[PRPENCVF_NUM_PADS];
	/* the video device at output pad */
	काष्ठा imx_media_video_dev *vdev;

	/* lock to protect all members below */
	काष्ठा mutex lock;

	/* IPU units we require */
	काष्ठा ipu_ic *ic;
	काष्ठा ipuv3_channel *out_ch;
	काष्ठा ipuv3_channel *rot_in_ch;
	काष्ठा ipuv3_channel *rot_out_ch;

	/* active vb2 buffers to send to video dev sink */
	काष्ठा imx_media_buffer *active_vb2_buf[2];
	काष्ठा imx_media_dma_buf underrun_buf;

	पूर्णांक ipu_buf_num;  /* ipu द्विगुन buffer index: 0-1 */

	/* the sink क्रम the captured frames */
	काष्ठा media_entity *sink;
	/* the source subdev */
	काष्ठा v4l2_subdev *src_sd;

	काष्ठा v4l2_mbus_framefmt क्रमmat_mbus[PRPENCVF_NUM_PADS];
	स्थिर काष्ठा imx_media_pixfmt *cc[PRPENCVF_NUM_PADS];
	काष्ठा v4l2_fract frame_पूर्णांकerval;

	काष्ठा imx_media_dma_buf rot_buf[2];

	/* controls */
	काष्ठा v4l2_ctrl_handler ctrl_hdlr;
	पूर्णांक  rotation; /* degrees */
	bool hflip;
	bool vflip;

	/* derived from rotation, hflip, vflip controls */
	क्रमागत ipu_rotate_mode rot_mode;

	spinlock_t irqlock; /* protect eof_irq handler */

	काष्ठा समयr_list eof_समयout_समयr;
	पूर्णांक eof_irq;
	पूर्णांक nfb4eof_irq;

	पूर्णांक stream_count;
	u32 frame_sequence; /* frame sequence counter */
	bool last_eof;  /* रुकोing क्रम last खातापूर्ण at stream off */
	bool nfb4eof;    /* NFB4खातापूर्ण encountered during streaming */
	bool पूर्णांकerweave_swap; /* swap top/bottom lines when पूर्णांकerweaving */
	काष्ठा completion last_eof_comp;
पूर्ण;

अटल स्थिर काष्ठा prp_channels अणु
	u32 out_ch;
	u32 rot_in_ch;
	u32 rot_out_ch;
पूर्ण prp_channel[] = अणु
	[IC_TASK_ENCODER] = अणु
		.out_ch = IPUV3_CHANNEL_IC_PRP_ENC_MEM,
		.rot_in_ch = IPUV3_CHANNEL_MEM_ROT_ENC,
		.rot_out_ch = IPUV3_CHANNEL_ROT_ENC_MEM,
	पूर्ण,
	[IC_TASK_VIEWFINDER] = अणु
		.out_ch = IPUV3_CHANNEL_IC_PRP_VF_MEM,
		.rot_in_ch = IPUV3_CHANNEL_MEM_ROT_VF,
		.rot_out_ch = IPUV3_CHANNEL_ROT_VF_MEM,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा prp_priv *sd_to_priv(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा imx_ic_priv *ic_priv = v4l2_get_subdevdata(sd);

	वापस ic_priv->task_priv;
पूर्ण

अटल व्योम prp_put_ipu_resources(काष्ठा prp_priv *priv)
अणु
	अगर (priv->ic)
		ipu_ic_put(priv->ic);
	priv->ic = शून्य;

	अगर (priv->out_ch)
		ipu_idmac_put(priv->out_ch);
	priv->out_ch = शून्य;

	अगर (priv->rot_in_ch)
		ipu_idmac_put(priv->rot_in_ch);
	priv->rot_in_ch = शून्य;

	अगर (priv->rot_out_ch)
		ipu_idmac_put(priv->rot_out_ch);
	priv->rot_out_ch = शून्य;
पूर्ण

अटल पूर्णांक prp_get_ipu_resources(काष्ठा prp_priv *priv)
अणु
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;
	काष्ठा ipu_ic *ic;
	काष्ठा ipuv3_channel *out_ch, *rot_in_ch, *rot_out_ch;
	पूर्णांक ret, task = ic_priv->task_id;

	ic = ipu_ic_get(ic_priv->ipu, task);
	अगर (IS_ERR(ic)) अणु
		v4l2_err(&ic_priv->sd, "failed to get IC\n");
		ret = PTR_ERR(ic);
		जाओ out;
	पूर्ण
	priv->ic = ic;

	out_ch = ipu_idmac_get(ic_priv->ipu, prp_channel[task].out_ch);
	अगर (IS_ERR(out_ch)) अणु
		v4l2_err(&ic_priv->sd, "could not get IDMAC channel %u\n",
			 prp_channel[task].out_ch);
		ret = PTR_ERR(out_ch);
		जाओ out;
	पूर्ण
	priv->out_ch = out_ch;

	rot_in_ch = ipu_idmac_get(ic_priv->ipu, prp_channel[task].rot_in_ch);
	अगर (IS_ERR(rot_in_ch)) अणु
		v4l2_err(&ic_priv->sd, "could not get IDMAC channel %u\n",
			 prp_channel[task].rot_in_ch);
		ret = PTR_ERR(rot_in_ch);
		जाओ out;
	पूर्ण
	priv->rot_in_ch = rot_in_ch;

	rot_out_ch = ipu_idmac_get(ic_priv->ipu, prp_channel[task].rot_out_ch);
	अगर (IS_ERR(rot_out_ch)) अणु
		v4l2_err(&ic_priv->sd, "could not get IDMAC channel %u\n",
			 prp_channel[task].rot_out_ch);
		ret = PTR_ERR(rot_out_ch);
		जाओ out;
	पूर्ण
	priv->rot_out_ch = rot_out_ch;

	वापस 0;
out:
	prp_put_ipu_resources(priv);
	वापस ret;
पूर्ण

अटल व्योम prp_vb2_buf_करोne(काष्ठा prp_priv *priv, काष्ठा ipuv3_channel *ch)
अणु
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	काष्ठा imx_media_buffer *करोne, *next;
	काष्ठा vb2_buffer *vb;
	dma_addr_t phys;

	करोne = priv->active_vb2_buf[priv->ipu_buf_num];
	अगर (करोne) अणु
		करोne->vbuf.field = vdev->fmt.field;
		करोne->vbuf.sequence = priv->frame_sequence;
		vb = &करोne->vbuf.vb2_buf;
		vb->बारtamp = kसमय_get_ns();
		vb2_buffer_करोne(vb, priv->nfb4eof ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
	पूर्ण

	priv->frame_sequence++;
	priv->nfb4eof = false;

	/* get next queued buffer */
	next = imx_media_capture_device_next_buf(vdev);
	अगर (next) अणु
		phys = vb2_dma_contig_plane_dma_addr(&next->vbuf.vb2_buf, 0);
		priv->active_vb2_buf[priv->ipu_buf_num] = next;
	पूर्ण अन्यथा अणु
		phys = priv->underrun_buf.phys;
		priv->active_vb2_buf[priv->ipu_buf_num] = शून्य;
	पूर्ण

	अगर (ipu_idmac_buffer_is_पढ़ोy(ch, priv->ipu_buf_num))
		ipu_idmac_clear_buffer(ch, priv->ipu_buf_num);

	अगर (priv->पूर्णांकerweave_swap && ch == priv->out_ch)
		phys += vdev->fmt.bytesperline;

	ipu_cpmem_set_buffer(ch, priv->ipu_buf_num, phys);
पूर्ण

अटल irqवापस_t prp_eof_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा prp_priv *priv = dev_id;
	काष्ठा ipuv3_channel *channel;

	spin_lock(&priv->irqlock);

	अगर (priv->last_eof) अणु
		complete(&priv->last_eof_comp);
		priv->last_eof = false;
		जाओ unlock;
	पूर्ण

	channel = (ipu_rot_mode_is_irt(priv->rot_mode)) ?
		priv->rot_out_ch : priv->out_ch;

	prp_vb2_buf_करोne(priv, channel);

	/* select new IPU buf */
	ipu_idmac_select_buffer(channel, priv->ipu_buf_num);
	/* toggle IPU द्विगुन-buffer index */
	priv->ipu_buf_num ^= 1;

	/* bump the खातापूर्ण समयout समयr */
	mod_समयr(&priv->eof_समयout_समयr,
		  jअगरfies + msecs_to_jअगरfies(IMX_MEDIA_खातापूर्ण_TIMEOUT));

unlock:
	spin_unlock(&priv->irqlock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t prp_nfb4eof_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा prp_priv *priv = dev_id;
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;

	spin_lock(&priv->irqlock);

	/*
	 * this is not an unrecoverable error, just mark
	 * the next captured frame with vb2 error flag.
	 */
	priv->nfb4eof = true;

	v4l2_err(&ic_priv->sd, "NFB4EOF\n");

	spin_unlock(&priv->irqlock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * खातापूर्ण समयout समयr function.
 */
/*
 * खातापूर्ण समयout समयr function. This is an unrecoverable condition
 * without a stream restart.
 */
अटल व्योम prp_eof_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा prp_priv *priv = from_समयr(priv, t, eof_समयout_समयr);
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;

	v4l2_err(&ic_priv->sd, "EOF timeout\n");

	/* संकेत a fatal error to capture device */
	imx_media_capture_device_error(vdev);
पूर्ण

अटल व्योम prp_setup_vb2_buf(काष्ठा prp_priv *priv, dma_addr_t *phys)
अणु
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	काष्ठा imx_media_buffer *buf;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		buf = imx_media_capture_device_next_buf(vdev);
		अगर (buf) अणु
			priv->active_vb2_buf[i] = buf;
			phys[i] = vb2_dma_contig_plane_dma_addr(
				&buf->vbuf.vb2_buf, 0);
		पूर्ण अन्यथा अणु
			priv->active_vb2_buf[i] = शून्य;
			phys[i] = priv->underrun_buf.phys;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prp_unsetup_vb2_buf(काष्ठा prp_priv *priv,
				क्रमागत vb2_buffer_state वापस_status)
अणु
	काष्ठा imx_media_buffer *buf;
	पूर्णांक i;

	/* वापस any reमुख्यing active frames with वापस_status */
	क्रम (i = 0; i < 2; i++) अणु
		buf = priv->active_vb2_buf[i];
		अगर (buf) अणु
			काष्ठा vb2_buffer *vb = &buf->vbuf.vb2_buf;

			vb->बारtamp = kसमय_get_ns();
			vb2_buffer_करोne(vb, वापस_status);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक prp_setup_channel(काष्ठा prp_priv *priv,
			     काष्ठा ipuv3_channel *channel,
			     क्रमागत ipu_rotate_mode rot_mode,
			     dma_addr_t addr0, dma_addr_t addr1,
			     bool rot_swap_width_height)
अणु
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	स्थिर काष्ठा imx_media_pixfmt *outcc;
	काष्ठा v4l2_mbus_framefmt *outfmt;
	अचिन्हित पूर्णांक burst_size;
	काष्ठा ipu_image image;
	bool पूर्णांकerweave;
	पूर्णांक ret;

	outfmt = &priv->क्रमmat_mbus[PRPENCVF_SRC_PAD];
	outcc = vdev->cc;

	ipu_cpmem_zero(channel);

	स_रखो(&image, 0, माप(image));
	image.pix = vdev->fmt;
	image.rect = vdev->compose;

	/*
	 * If the field type at capture पूर्णांकerface is पूर्णांकerlaced, and
	 * the output IDMAC pad is sequential, enable पूर्णांकerweave at
	 * the IDMAC output channel.
	 */
	पूर्णांकerweave = V4L2_FIELD_IS_INTERLACED(image.pix.field) &&
		V4L2_FIELD_IS_SEQUENTIAL(outfmt->field);
	priv->पूर्णांकerweave_swap = पूर्णांकerweave &&
		image.pix.field == V4L2_FIELD_INTERLACED_BT;

	अगर (rot_swap_width_height) अणु
		swap(image.pix.width, image.pix.height);
		swap(image.rect.width, image.rect.height);
		/* recalc stride using swapped width */
		image.pix.bytesperline = outcc->planar ?
			image.pix.width :
			(image.pix.width * outcc->bpp) >> 3;
	पूर्ण

	अगर (priv->पूर्णांकerweave_swap && channel == priv->out_ch) अणु
		/* start पूर्णांकerweave scan at 1st top line (2nd line) */
		image.rect.top = 1;
	पूर्ण

	image.phys0 = addr0;
	image.phys1 = addr1;

	/*
	 * Skip writing U and V components to odd rows in the output
	 * channels क्रम planar 4:2:0 (but not when enabling IDMAC
	 * पूर्णांकerweaving, they are incompatible).
	 */
	अगर ((channel == priv->out_ch && !पूर्णांकerweave) ||
	    channel == priv->rot_out_ch) अणु
		चयन (image.pix.pixelक्रमmat) अणु
		हाल V4L2_PIX_FMT_YUV420:
		हाल V4L2_PIX_FMT_YVU420:
		हाल V4L2_PIX_FMT_NV12:
			ipu_cpmem_skip_odd_chroma_rows(channel);
			अवरोध;
		पूर्ण
	पूर्ण

	ret = ipu_cpmem_set_image(channel, &image);
	अगर (ret)
		वापस ret;

	अगर (channel == priv->rot_in_ch ||
	    channel == priv->rot_out_ch) अणु
		burst_size = 8;
		ipu_cpmem_set_block_mode(channel);
	पूर्ण अन्यथा अणु
		burst_size = (image.pix.width & 0xf) ? 8 : 16;
	पूर्ण

	ipu_cpmem_set_burstsize(channel, burst_size);

	अगर (rot_mode)
		ipu_cpmem_set_rotation(channel, rot_mode);

	अगर (पूर्णांकerweave && channel == priv->out_ch)
		ipu_cpmem_पूर्णांकerlaced_scan(channel,
					  priv->पूर्णांकerweave_swap ?
					  -image.pix.bytesperline :
					  image.pix.bytesperline,
					  image.pix.pixelक्रमmat);

	ret = ipu_ic_task_idma_init(priv->ic, channel,
				    image.pix.width, image.pix.height,
				    burst_size, rot_mode);
	अगर (ret)
		वापस ret;

	ipu_cpmem_set_axi_id(channel, 1);

	ipu_idmac_set_द्विगुन_buffer(channel, true);

	वापस 0;
पूर्ण

अटल पूर्णांक prp_setup_rotation(काष्ठा prp_priv *priv)
अणु
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;
	स्थिर काष्ठा imx_media_pixfmt *outcc, *incc;
	काष्ठा v4l2_mbus_framefmt *infmt;
	काष्ठा v4l2_pix_क्रमmat *outfmt;
	काष्ठा ipu_ic_csc csc;
	dma_addr_t phys[2];
	पूर्णांक ret;

	infmt = &priv->क्रमmat_mbus[PRPENCVF_SINK_PAD];
	outfmt = &vdev->fmt;
	incc = priv->cc[PRPENCVF_SINK_PAD];
	outcc = vdev->cc;

	ret = ipu_ic_calc_csc(&csc,
			      infmt->ycbcr_enc, infmt->quantization,
			      incc->cs,
			      outfmt->ycbcr_enc, outfmt->quantization,
			      outcc->cs);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd, "ipu_ic_calc_csc failed, %d\n",
			 ret);
		वापस ret;
	पूर्ण

	ret = imx_media_alloc_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[0],
				      outfmt->sizeimage);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd, "failed to alloc rot_buf[0], %d\n", ret);
		वापस ret;
	पूर्ण
	ret = imx_media_alloc_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[1],
				      outfmt->sizeimage);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd, "failed to alloc rot_buf[1], %d\n", ret);
		जाओ मुक्त_rot0;
	पूर्ण

	ret = ipu_ic_task_init(priv->ic, &csc,
			       infmt->width, infmt->height,
			       outfmt->height, outfmt->width);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd, "ipu_ic_task_init failed, %d\n", ret);
		जाओ मुक्त_rot1;
	पूर्ण

	/* init the IC-PRP-->MEM IDMAC channel */
	ret = prp_setup_channel(priv, priv->out_ch, IPU_ROTATE_NONE,
				priv->rot_buf[0].phys, priv->rot_buf[1].phys,
				true);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd,
			 "prp_setup_channel(out_ch) failed, %d\n", ret);
		जाओ मुक्त_rot1;
	पूर्ण

	/* init the MEM-->IC-PRP ROT IDMAC channel */
	ret = prp_setup_channel(priv, priv->rot_in_ch, priv->rot_mode,
				priv->rot_buf[0].phys, priv->rot_buf[1].phys,
				true);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd,
			 "prp_setup_channel(rot_in_ch) failed, %d\n", ret);
		जाओ मुक्त_rot1;
	पूर्ण

	prp_setup_vb2_buf(priv, phys);

	/* init the destination IC-PRP ROT-->MEM IDMAC channel */
	ret = prp_setup_channel(priv, priv->rot_out_ch, IPU_ROTATE_NONE,
				phys[0], phys[1],
				false);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd,
			 "prp_setup_channel(rot_out_ch) failed, %d\n", ret);
		जाओ unsetup_vb2;
	पूर्ण

	/* now link IC-PRP-->MEM to MEM-->IC-PRP ROT */
	ipu_idmac_link(priv->out_ch, priv->rot_in_ch);

	/* enable the IC */
	ipu_ic_enable(priv->ic);

	/* set buffers पढ़ोy */
	ipu_idmac_select_buffer(priv->out_ch, 0);
	ipu_idmac_select_buffer(priv->out_ch, 1);
	ipu_idmac_select_buffer(priv->rot_out_ch, 0);
	ipu_idmac_select_buffer(priv->rot_out_ch, 1);

	/* enable the channels */
	ipu_idmac_enable_channel(priv->out_ch);
	ipu_idmac_enable_channel(priv->rot_in_ch);
	ipu_idmac_enable_channel(priv->rot_out_ch);

	/* and finally enable the IC PRP task */
	ipu_ic_task_enable(priv->ic);

	वापस 0;

unsetup_vb2:
	prp_unsetup_vb2_buf(priv, VB2_BUF_STATE_QUEUED);
मुक्त_rot1:
	imx_media_मुक्त_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[1]);
मुक्त_rot0:
	imx_media_मुक्त_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[0]);
	वापस ret;
पूर्ण

अटल व्योम prp_unsetup_rotation(काष्ठा prp_priv *priv)
अणु
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;

	ipu_ic_task_disable(priv->ic);

	ipu_idmac_disable_channel(priv->out_ch);
	ipu_idmac_disable_channel(priv->rot_in_ch);
	ipu_idmac_disable_channel(priv->rot_out_ch);

	ipu_idmac_unlink(priv->out_ch, priv->rot_in_ch);

	ipu_ic_disable(priv->ic);

	imx_media_मुक्त_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[0]);
	imx_media_मुक्त_dma_buf(ic_priv->ipu_dev, &priv->rot_buf[1]);
पूर्ण

अटल पूर्णांक prp_setup_norotation(काष्ठा prp_priv *priv)
अणु
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;
	स्थिर काष्ठा imx_media_pixfmt *outcc, *incc;
	काष्ठा v4l2_mbus_framefmt *infmt;
	काष्ठा v4l2_pix_क्रमmat *outfmt;
	काष्ठा ipu_ic_csc csc;
	dma_addr_t phys[2];
	पूर्णांक ret;

	infmt = &priv->क्रमmat_mbus[PRPENCVF_SINK_PAD];
	outfmt = &vdev->fmt;
	incc = priv->cc[PRPENCVF_SINK_PAD];
	outcc = vdev->cc;

	ret = ipu_ic_calc_csc(&csc,
			      infmt->ycbcr_enc, infmt->quantization,
			      incc->cs,
			      outfmt->ycbcr_enc, outfmt->quantization,
			      outcc->cs);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd, "ipu_ic_calc_csc failed, %d\n",
			 ret);
		वापस ret;
	पूर्ण

	ret = ipu_ic_task_init(priv->ic, &csc,
			       infmt->width, infmt->height,
			       outfmt->width, outfmt->height);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd, "ipu_ic_task_init failed, %d\n", ret);
		वापस ret;
	पूर्ण

	prp_setup_vb2_buf(priv, phys);

	/* init the IC PRP-->MEM IDMAC channel */
	ret = prp_setup_channel(priv, priv->out_ch, priv->rot_mode,
				phys[0], phys[1], false);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd,
			 "prp_setup_channel(out_ch) failed, %d\n", ret);
		जाओ unsetup_vb2;
	पूर्ण

	ipu_cpmem_dump(priv->out_ch);
	ipu_ic_dump(priv->ic);
	ipu_dump(ic_priv->ipu);

	ipu_ic_enable(priv->ic);

	/* set buffers पढ़ोy */
	ipu_idmac_select_buffer(priv->out_ch, 0);
	ipu_idmac_select_buffer(priv->out_ch, 1);

	/* enable the channels */
	ipu_idmac_enable_channel(priv->out_ch);

	/* enable the IC task */
	ipu_ic_task_enable(priv->ic);

	वापस 0;

unsetup_vb2:
	prp_unsetup_vb2_buf(priv, VB2_BUF_STATE_QUEUED);
	वापस ret;
पूर्ण

अटल व्योम prp_unsetup_norotation(काष्ठा prp_priv *priv)
अणु
	ipu_ic_task_disable(priv->ic);
	ipu_idmac_disable_channel(priv->out_ch);
	ipu_ic_disable(priv->ic);
पूर्ण

अटल व्योम prp_unsetup(काष्ठा prp_priv *priv,
			क्रमागत vb2_buffer_state state)
अणु
	अगर (ipu_rot_mode_is_irt(priv->rot_mode))
		prp_unsetup_rotation(priv);
	अन्यथा
		prp_unsetup_norotation(priv);

	prp_unsetup_vb2_buf(priv, state);
पूर्ण

अटल पूर्णांक prp_start(काष्ठा prp_priv *priv)
अणु
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	पूर्णांक ret;

	ret = prp_get_ipu_resources(priv);
	अगर (ret)
		वापस ret;

	ret = imx_media_alloc_dma_buf(ic_priv->ipu_dev, &priv->underrun_buf,
				      vdev->fmt.sizeimage);
	अगर (ret)
		जाओ out_put_ipu;

	priv->ipu_buf_num = 0;

	/* init खातापूर्ण completion रुकोq */
	init_completion(&priv->last_eof_comp);
	priv->frame_sequence = 0;
	priv->last_eof = false;
	priv->nfb4eof = false;

	अगर (ipu_rot_mode_is_irt(priv->rot_mode))
		ret = prp_setup_rotation(priv);
	अन्यथा
		ret = prp_setup_norotation(priv);
	अगर (ret)
		जाओ out_मुक्त_underrun;

	priv->nfb4eof_irq = ipu_idmac_channel_irq(ic_priv->ipu,
						  priv->out_ch,
						  IPU_IRQ_NFB4खातापूर्ण);
	ret = devm_request_irq(ic_priv->ipu_dev, priv->nfb4eof_irq,
			       prp_nfb4eof_पूर्णांकerrupt, 0,
			       "imx-ic-prp-nfb4eof", priv);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd,
			 "Error registering NFB4EOF irq: %d\n", ret);
		जाओ out_unsetup;
	पूर्ण

	अगर (ipu_rot_mode_is_irt(priv->rot_mode))
		priv->eof_irq = ipu_idmac_channel_irq(
			ic_priv->ipu, priv->rot_out_ch, IPU_IRQ_खातापूर्ण);
	अन्यथा
		priv->eof_irq = ipu_idmac_channel_irq(
			ic_priv->ipu, priv->out_ch, IPU_IRQ_खातापूर्ण);

	ret = devm_request_irq(ic_priv->ipu_dev, priv->eof_irq,
			       prp_eof_पूर्णांकerrupt, 0,
			       "imx-ic-prp-eof", priv);
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd,
			 "Error registering eof irq: %d\n", ret);
		जाओ out_मुक्त_nfb4eof_irq;
	पूर्ण

	/* start upstream */
	ret = v4l2_subdev_call(priv->src_sd, video, s_stream, 1);
	ret = (ret && ret != -ENOIOCTLCMD) ? ret : 0;
	अगर (ret) अणु
		v4l2_err(&ic_priv->sd,
			 "upstream stream on failed: %d\n", ret);
		जाओ out_मुक्त_eof_irq;
	पूर्ण

	/* start the खातापूर्ण समयout समयr */
	mod_समयr(&priv->eof_समयout_समयr,
		  jअगरfies + msecs_to_jअगरfies(IMX_MEDIA_खातापूर्ण_TIMEOUT));

	वापस 0;

out_मुक्त_eof_irq:
	devm_मुक्त_irq(ic_priv->ipu_dev, priv->eof_irq, priv);
out_मुक्त_nfb4eof_irq:
	devm_मुक्त_irq(ic_priv->ipu_dev, priv->nfb4eof_irq, priv);
out_unsetup:
	prp_unsetup(priv, VB2_BUF_STATE_QUEUED);
out_मुक्त_underrun:
	imx_media_मुक्त_dma_buf(ic_priv->ipu_dev, &priv->underrun_buf);
out_put_ipu:
	prp_put_ipu_resources(priv);
	वापस ret;
पूर्ण

अटल व्योम prp_stop(काष्ठा prp_priv *priv)
अणु
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* mark next खातापूर्ण पूर्णांकerrupt as the last beक्रमe stream off */
	spin_lock_irqsave(&priv->irqlock, flags);
	priv->last_eof = true;
	spin_unlock_irqrestore(&priv->irqlock, flags);

	/*
	 * and then रुको क्रम पूर्णांकerrupt handler to mark completion.
	 */
	ret = रुको_क्रम_completion_समयout(
		&priv->last_eof_comp,
		msecs_to_jअगरfies(IMX_MEDIA_खातापूर्ण_TIMEOUT));
	अगर (ret == 0)
		v4l2_warn(&ic_priv->sd, "wait last EOF timeout\n");

	/* stop upstream */
	ret = v4l2_subdev_call(priv->src_sd, video, s_stream, 0);
	अगर (ret && ret != -ENOIOCTLCMD)
		v4l2_warn(&ic_priv->sd,
			  "upstream stream off failed: %d\n", ret);

	devm_मुक्त_irq(ic_priv->ipu_dev, priv->eof_irq, priv);
	devm_मुक्त_irq(ic_priv->ipu_dev, priv->nfb4eof_irq, priv);

	prp_unsetup(priv, VB2_BUF_STATE_ERROR);

	imx_media_मुक्त_dma_buf(ic_priv->ipu_dev, &priv->underrun_buf);

	/* cancel the खातापूर्ण समयout समयr */
	del_समयr_sync(&priv->eof_समयout_समयr);

	prp_put_ipu_resources(priv);
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__prp_get_fmt(काष्ठा prp_priv *priv, काष्ठा v4l2_subdev_pad_config *cfg,
	      अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;

	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&ic_priv->sd, cfg, pad);
	अन्यथा
		वापस &priv->क्रमmat_mbus[pad];
पूर्ण

/*
 * Applies IC resizer and IDMAC alignment restrictions to output
 * rectangle given the input rectangle, and depending on given
 * rotation mode.
 *
 * The IC resizer cannot करोwnsize more than 4:1. Note also that
 * क्रम 90 or 270 rotation, _both_ output width and height must
 * be aligned by W_ALIGN_SRC, because the पूर्णांकermediate rotation
 * buffer swaps output width/height, and the final output buffer
 * करोes not.
 *
 * Returns true अगर the output rectangle was modअगरied.
 */
अटल bool prp_bound_align_output(काष्ठा v4l2_mbus_framefmt *outfmt,
				   काष्ठा v4l2_mbus_framefmt *infmt,
				   क्रमागत ipu_rotate_mode rot_mode)
अणु
	u32 orig_width = outfmt->width;
	u32 orig_height = outfmt->height;

	अगर (ipu_rot_mode_is_irt(rot_mode))
		v4l_bound_align_image(&outfmt->width,
				      infmt->height / 4, MAX_H_SRC,
				      W_ALIGN_SRC,
				      &outfmt->height,
				      infmt->width / 4, MAX_W_SRC,
				      W_ALIGN_SRC, S_ALIGN);
	अन्यथा
		v4l_bound_align_image(&outfmt->width,
				      infmt->width / 4, MAX_W_SRC,
				      W_ALIGN_SRC,
				      &outfmt->height,
				      infmt->height / 4, MAX_H_SRC,
				      H_ALIGN_SRC, S_ALIGN);

	वापस outfmt->width != orig_width || outfmt->height != orig_height;
पूर्ण

/*
 * V4L2 subdev operations.
 */

अटल पूर्णांक prp_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad >= PRPENCVF_NUM_PADS)
		वापस -EINVAL;

	वापस imx_media_क्रमागत_ipu_क्रमmats(&code->code, code->index,
					  PIXFMT_SEL_YUV_RGB);
पूर्ण

अटल पूर्णांक prp_get_fmt(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा prp_priv *priv = sd_to_priv(sd);
	काष्ठा v4l2_mbus_framefmt *fmt;
	पूर्णांक ret = 0;

	अगर (sdक्रमmat->pad >= PRPENCVF_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	fmt = __prp_get_fmt(priv, cfg, sdक्रमmat->pad, sdक्रमmat->which);
	अगर (!fmt) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	sdक्रमmat->क्रमmat = *fmt;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल व्योम prp_try_fmt(काष्ठा prp_priv *priv,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat,
			स्थिर काष्ठा imx_media_pixfmt **cc)
अणु
	काष्ठा v4l2_mbus_framefmt *infmt;

	*cc = imx_media_find_ipu_क्रमmat(sdक्रमmat->क्रमmat.code,
					PIXFMT_SEL_YUV_RGB);
	अगर (!*cc) अणु
		u32 code;

		imx_media_क्रमागत_ipu_क्रमmats(&code, 0, PIXFMT_SEL_YUV_RGB);
		*cc = imx_media_find_ipu_क्रमmat(code, PIXFMT_SEL_YUV_RGB);

		sdक्रमmat->क्रमmat.code = (*cc)->codes[0];
	पूर्ण

	infmt = __prp_get_fmt(priv, cfg, PRPENCVF_SINK_PAD, sdक्रमmat->which);

	अगर (sdक्रमmat->pad == PRPENCVF_SRC_PAD) अणु
		sdक्रमmat->क्रमmat.field = infmt->field;

		prp_bound_align_output(&sdक्रमmat->क्रमmat, infmt,
				       priv->rot_mode);

		/* propagate colorimetry from sink */
		sdक्रमmat->क्रमmat.colorspace = infmt->colorspace;
		sdक्रमmat->क्रमmat.xfer_func = infmt->xfer_func;
	पूर्ण अन्यथा अणु
		v4l_bound_align_image(&sdक्रमmat->क्रमmat.width,
				      MIN_W_SINK, MAX_W_SINK, W_ALIGN_SINK,
				      &sdक्रमmat->क्रमmat.height,
				      MIN_H_SINK, MAX_H_SINK, H_ALIGN_SINK,
				      S_ALIGN);

		अगर (sdक्रमmat->क्रमmat.field == V4L2_FIELD_ANY)
			sdक्रमmat->क्रमmat.field = V4L2_FIELD_NONE;
	पूर्ण

	imx_media_try_colorimetry(&sdक्रमmat->क्रमmat, true);
पूर्ण

अटल पूर्णांक prp_set_fmt(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा prp_priv *priv = sd_to_priv(sd);
	स्थिर काष्ठा imx_media_pixfmt *cc;
	काष्ठा v4l2_mbus_framefmt *fmt;
	पूर्णांक ret = 0;

	अगर (sdक्रमmat->pad >= PRPENCVF_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	अगर (priv->stream_count > 0) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	prp_try_fmt(priv, cfg, sdक्रमmat, &cc);

	fmt = __prp_get_fmt(priv, cfg, sdक्रमmat->pad, sdक्रमmat->which);
	*fmt = sdक्रमmat->क्रमmat;

	/* propagate a शेष क्रमmat to source pad */
	अगर (sdक्रमmat->pad == PRPENCVF_SINK_PAD) अणु
		स्थिर काष्ठा imx_media_pixfmt *outcc;
		काष्ठा v4l2_mbus_framefmt *outfmt;
		काष्ठा v4l2_subdev_क्रमmat क्रमmat;

		क्रमmat.pad = PRPENCVF_SRC_PAD;
		क्रमmat.which = sdक्रमmat->which;
		क्रमmat.क्रमmat = sdक्रमmat->क्रमmat;
		prp_try_fmt(priv, cfg, &क्रमmat, &outcc);

		outfmt = __prp_get_fmt(priv, cfg, PRPENCVF_SRC_PAD,
				       sdक्रमmat->which);
		*outfmt = क्रमmat.क्रमmat;
		अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
			priv->cc[PRPENCVF_SRC_PAD] = outcc;
	पूर्ण

	अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		priv->cc[sdक्रमmat->pad] = cc;

out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक prp_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा prp_priv *priv = sd_to_priv(sd);
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणुपूर्ण;
	स्थिर काष्ठा imx_media_pixfmt *cc;
	पूर्णांक ret = 0;

	अगर (fse->pad >= PRPENCVF_NUM_PADS || fse->index != 0)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	क्रमmat.pad = fse->pad;
	क्रमmat.which = fse->which;
	क्रमmat.क्रमmat.code = fse->code;
	क्रमmat.क्रमmat.width = 1;
	क्रमmat.क्रमmat.height = 1;
	prp_try_fmt(priv, cfg, &क्रमmat, &cc);
	fse->min_width = क्रमmat.क्रमmat.width;
	fse->min_height = क्रमmat.क्रमmat.height;

	अगर (क्रमmat.क्रमmat.code != fse->code) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	क्रमmat.क्रमmat.code = fse->code;
	क्रमmat.क्रमmat.width = -1;
	क्रमmat.क्रमmat.height = -1;
	prp_try_fmt(priv, cfg, &क्रमmat, &cc);
	fse->max_width = क्रमmat.क्रमmat.width;
	fse->max_height = क्रमmat.क्रमmat.height;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक prp_link_setup(काष्ठा media_entity *entity,
			  स्थिर काष्ठा media_pad *local,
			  स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा imx_ic_priv *ic_priv = v4l2_get_subdevdata(sd);
	काष्ठा prp_priv *priv = ic_priv->task_priv;
	काष्ठा v4l2_subdev *remote_sd;
	पूर्णांक ret = 0;

	dev_dbg(ic_priv->ipu_dev, "%s: link setup %s -> %s",
		ic_priv->sd.name, remote->entity->name, local->entity->name);

	mutex_lock(&priv->lock);

	अगर (local->flags & MEDIA_PAD_FL_SINK) अणु
		अगर (!is_media_entity_v4l2_subdev(remote->entity)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		remote_sd = media_entity_to_v4l2_subdev(remote->entity);

		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (priv->src_sd) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			priv->src_sd = remote_sd;
		पूर्ण अन्यथा अणु
			priv->src_sd = शून्य;
		पूर्ण

		जाओ out;
	पूर्ण

	/* this is the source pad */

	/* the remote must be the device node */
	अगर (!is_media_entity_v4l2_video_device(remote->entity)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
		अगर (priv->sink) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->sink = शून्य;
		जाओ out;
	पूर्ण

	priv->sink = remote->entity;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक prp_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा prp_priv *priv = container_of(ctrl->handler,
					       काष्ठा prp_priv, ctrl_hdlr);
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;
	क्रमागत ipu_rotate_mode rot_mode;
	पूर्णांक rotation, ret = 0;
	bool hflip, vflip;

	mutex_lock(&priv->lock);

	rotation = priv->rotation;
	hflip = priv->hflip;
	vflip = priv->vflip;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_HFLIP:
		hflip = (ctrl->val == 1);
		अवरोध;
	हाल V4L2_CID_VFLIP:
		vflip = (ctrl->val == 1);
		अवरोध;
	हाल V4L2_CID_ROTATE:
		rotation = ctrl->val;
		अवरोध;
	शेष:
		v4l2_err(&ic_priv->sd, "Invalid control\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = ipu_degrees_to_rot_mode(&rot_mode, rotation, hflip, vflip);
	अगर (ret)
		जाओ out;

	अगर (rot_mode != priv->rot_mode) अणु
		काष्ठा v4l2_mbus_framefmt outfmt, infmt;

		/* can't change rotation mid-streaming */
		अगर (priv->stream_count > 0) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण

		outfmt = priv->क्रमmat_mbus[PRPENCVF_SRC_PAD];
		infmt = priv->क्रमmat_mbus[PRPENCVF_SINK_PAD];

		अगर (prp_bound_align_output(&outfmt, &infmt, rot_mode)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		priv->rot_mode = rot_mode;
		priv->rotation = rotation;
		priv->hflip = hflip;
		priv->vflip = vflip;
	पूर्ण

out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops prp_ctrl_ops = अणु
	.s_ctrl = prp_s_ctrl,
पूर्ण;

अटल पूर्णांक prp_init_controls(काष्ठा prp_priv *priv)
अणु
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;
	काष्ठा v4l2_ctrl_handler *hdlr = &priv->ctrl_hdlr;
	पूर्णांक ret;

	v4l2_ctrl_handler_init(hdlr, 3);

	v4l2_ctrl_new_std(hdlr, &prp_ctrl_ops, V4L2_CID_HFLIP,
			  0, 1, 1, 0);
	v4l2_ctrl_new_std(hdlr, &prp_ctrl_ops, V4L2_CID_VFLIP,
			  0, 1, 1, 0);
	v4l2_ctrl_new_std(hdlr, &prp_ctrl_ops, V4L2_CID_ROTATE,
			  0, 270, 90, 0);

	ic_priv->sd.ctrl_handler = hdlr;

	अगर (hdlr->error) अणु
		ret = hdlr->error;
		जाओ out_मुक्त;
	पूर्ण

	v4l2_ctrl_handler_setup(hdlr);
	वापस 0;

out_मुक्त:
	v4l2_ctrl_handler_मुक्त(hdlr);
	वापस ret;
पूर्ण

अटल पूर्णांक prp_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा imx_ic_priv *ic_priv = v4l2_get_subdevdata(sd);
	काष्ठा prp_priv *priv = ic_priv->task_priv;
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	अगर (!priv->src_sd || !priv->sink) अणु
		ret = -EPIPE;
		जाओ out;
	पूर्ण

	/*
	 * enable/disable streaming only अगर stream_count is
	 * going from 0 to 1 / 1 to 0.
	 */
	अगर (priv->stream_count != !enable)
		जाओ update_count;

	dev_dbg(ic_priv->ipu_dev, "%s: stream %s\n", sd->name,
		enable ? "ON" : "OFF");

	अगर (enable)
		ret = prp_start(priv);
	अन्यथा
		prp_stop(priv);
	अगर (ret)
		जाओ out;

update_count:
	priv->stream_count += enable ? 1 : -1;
	अगर (priv->stream_count < 0)
		priv->stream_count = 0;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक prp_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा prp_priv *priv = sd_to_priv(sd);

	अगर (fi->pad >= PRPENCVF_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&priv->lock);
	fi->पूर्णांकerval = priv->frame_पूर्णांकerval;
	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक prp_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा prp_priv *priv = sd_to_priv(sd);

	अगर (fi->pad >= PRPENCVF_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	/* No limits on valid frame पूर्णांकervals */
	अगर (fi->पूर्णांकerval.numerator == 0 || fi->पूर्णांकerval.denominator == 0)
		fi->पूर्णांकerval = priv->frame_पूर्णांकerval;
	अन्यथा
		priv->frame_पूर्णांकerval = fi->पूर्णांकerval;

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक prp_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा prp_priv *priv = sd_to_priv(sd);
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;
	पूर्णांक i, ret;
	u32 code;

	/* set a शेष mbus क्रमmat  */
	imx_media_क्रमागत_ipu_क्रमmats(&code, 0, PIXFMT_SEL_YUV);

	क्रम (i = 0; i < PRPENCVF_NUM_PADS; i++) अणु
		ret = imx_media_init_mbus_fmt(&priv->क्रमmat_mbus[i],
					      IMX_MEDIA_DEF_PIX_WIDTH,
					      IMX_MEDIA_DEF_PIX_HEIGHT, code,
					      V4L2_FIELD_NONE, &priv->cc[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* init शेष frame पूर्णांकerval */
	priv->frame_पूर्णांकerval.numerator = 1;
	priv->frame_पूर्णांकerval.denominator = 30;

	priv->vdev = imx_media_capture_device_init(ic_priv->ipu_dev,
						   &ic_priv->sd,
						   PRPENCVF_SRC_PAD, true);
	अगर (IS_ERR(priv->vdev))
		वापस PTR_ERR(priv->vdev);

	ret = imx_media_capture_device_रेजिस्टर(priv->vdev, 0);
	अगर (ret)
		जाओ हटाओ_vdev;

	ret = prp_init_controls(priv);
	अगर (ret)
		जाओ unreg_vdev;

	वापस 0;

unreg_vdev:
	imx_media_capture_device_unरेजिस्टर(priv->vdev);
हटाओ_vdev:
	imx_media_capture_device_हटाओ(priv->vdev);
	वापस ret;
पूर्ण

अटल व्योम prp_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा prp_priv *priv = sd_to_priv(sd);

	imx_media_capture_device_unरेजिस्टर(priv->vdev);
	imx_media_capture_device_हटाओ(priv->vdev);

	v4l2_ctrl_handler_मुक्त(&priv->ctrl_hdlr);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops prp_pad_ops = अणु
	.init_cfg = imx_media_init_cfg,
	.क्रमागत_mbus_code = prp_क्रमागत_mbus_code,
	.क्रमागत_frame_size = prp_क्रमागत_frame_size,
	.get_fmt = prp_get_fmt,
	.set_fmt = prp_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops prp_video_ops = अणु
	.g_frame_पूर्णांकerval = prp_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = prp_s_frame_पूर्णांकerval,
	.s_stream = prp_s_stream,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations prp_entity_ops = अणु
	.link_setup = prp_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops prp_subdev_ops = अणु
	.video = &prp_video_ops,
	.pad = &prp_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops prp_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = prp_रेजिस्टरed,
	.unरेजिस्टरed = prp_unरेजिस्टरed,
पूर्ण;

अटल पूर्णांक prp_init(काष्ठा imx_ic_priv *ic_priv)
अणु
	काष्ठा prp_priv *priv;
	पूर्णांक i, ret;

	priv = devm_kzalloc(ic_priv->ipu_dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ic_priv->task_priv = priv;
	priv->ic_priv = ic_priv;

	spin_lock_init(&priv->irqlock);
	समयr_setup(&priv->eof_समयout_समयr, prp_eof_समयout, 0);

	mutex_init(&priv->lock);

	क्रम (i = 0; i < PRPENCVF_NUM_PADS; i++) अणु
		priv->pad[i].flags = (i == PRPENCVF_SINK_PAD) ?
			MEDIA_PAD_FL_SINK : MEDIA_PAD_FL_SOURCE;
	पूर्ण

	ret = media_entity_pads_init(&ic_priv->sd.entity, PRPENCVF_NUM_PADS,
				     priv->pad);
	अगर (ret)
		mutex_destroy(&priv->lock);

	वापस ret;
पूर्ण

अटल व्योम prp_हटाओ(काष्ठा imx_ic_priv *ic_priv)
अणु
	काष्ठा prp_priv *priv = ic_priv->task_priv;

	mutex_destroy(&priv->lock);
पूर्ण

काष्ठा imx_ic_ops imx_ic_prpencvf_ops = अणु
	.subdev_ops = &prp_subdev_ops,
	.पूर्णांकernal_ops = &prp_पूर्णांकernal_ops,
	.entity_ops = &prp_entity_ops,
	.init = prp_init,
	.हटाओ = prp_हटाओ,
पूर्ण;
