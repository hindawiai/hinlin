<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * V4L2 Deपूर्णांकerlacer Subdev क्रम Freescale i.MX5/6 SOC
 *
 * Copyright (c) 2017 Mentor Graphics Inc.
 */
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/imx.h>
#समावेश "imx-media.h"

/*
 * This subdev implements two dअगरferent video pipelines:
 *
 * CSI -> VDIC
 *
 * In this pipeline, the CSI sends a single पूर्णांकerlaced field F(n-1)
 * directly to the VDIC (and optionally the following field F(n)
 * can be sent to memory via IDMAC channel 13). This pipeline only works
 * in VDIC's high motion mode, which only requires a single field क्रम
 * processing. The other motion modes (low and medium) require three
 * fields, so this pipeline करोes not work in those modes. Also, it is
 * not clear how this pipeline can deal with the various field orders
 * (sequential BT/TB, पूर्णांकerlaced BT/TB).
 *
 * MEM -> CH8,9,10 -> VDIC
 *
 * In this pipeline, previous field F(n-1), current field F(n), and next
 * field F(n+1) are transferred to the VDIC via IDMAC channels 8,9,10.
 * These memory buffers can come from a video output or mem2mem device.
 * All motion modes are supported by this pipeline.
 *
 * The "direct" CSI->VDIC pipeline requires no DMA, but it can only be
 * used in high motion mode.
 */

काष्ठा vdic_priv;

काष्ठा vdic_pipeline_ops अणु
	पूर्णांक (*setup)(काष्ठा vdic_priv *priv);
	व्योम (*start)(काष्ठा vdic_priv *priv);
	व्योम (*stop)(काष्ठा vdic_priv *priv);
	व्योम (*disable)(काष्ठा vdic_priv *priv);
पूर्ण;

/*
 * Min/Max supported width and heights.
 */
#घोषणा MIN_W        32
#घोषणा MIN_H        32
#घोषणा MAX_W_VDIC  968
#घोषणा MAX_H_VDIC 2048
#घोषणा W_ALIGN    4 /* multiple of 16 pixels */
#घोषणा H_ALIGN    1 /* multiple of 2 lines */
#घोषणा S_ALIGN    1 /* multiple of 2 */

काष्ठा vdic_priv अणु
	काष्ठा device *ipu_dev;
	काष्ठा ipu_soc *ipu;

	काष्ठा v4l2_subdev   sd;
	काष्ठा media_pad pad[VDIC_NUM_PADS];

	/* lock to protect all members below */
	काष्ठा mutex lock;

	/* IPU units we require */
	काष्ठा ipu_vdi *vdi;

	पूर्णांक active_input_pad;

	काष्ठा ipuv3_channel *vdi_in_ch_p; /* F(n-1) transfer channel */
	काष्ठा ipuv3_channel *vdi_in_ch;   /* F(n) transfer channel */
	काष्ठा ipuv3_channel *vdi_in_ch_n; /* F(n+1) transfer channel */

	/* pipeline operations */
	काष्ठा vdic_pipeline_ops *ops;

	/* current and previous input buffers indirect path */
	काष्ठा imx_media_buffer *curr_in_buf;
	काष्ठा imx_media_buffer *prev_in_buf;

	/*
	 * translated field type, input line stride, and field size
	 * क्रम indirect path
	 */
	u32 fieldtype;
	u32 in_stride;
	u32 field_size;

	/* the source (a video device or subdev) */
	काष्ठा media_entity *src;
	/* the sink that will receive the progressive out buffers */
	काष्ठा v4l2_subdev *sink_sd;

	काष्ठा v4l2_mbus_framefmt क्रमmat_mbus[VDIC_NUM_PADS];
	स्थिर काष्ठा imx_media_pixfmt *cc[VDIC_NUM_PADS];
	काष्ठा v4l2_fract frame_पूर्णांकerval[VDIC_NUM_PADS];

	/* the video device at IDMAC input pad */
	काष्ठा imx_media_video_dev *vdev;

	bool csi_direct;  /* using direct CSI->VDIC->IC pipeline */

	/* motion select control */
	काष्ठा v4l2_ctrl_handler ctrl_hdlr;
	क्रमागत ipu_motion_sel motion;

	पूर्णांक stream_count;
पूर्ण;

अटल व्योम vdic_put_ipu_resources(काष्ठा vdic_priv *priv)
अणु
	अगर (priv->vdi_in_ch_p)
		ipu_idmac_put(priv->vdi_in_ch_p);
	priv->vdi_in_ch_p = शून्य;

	अगर (priv->vdi_in_ch)
		ipu_idmac_put(priv->vdi_in_ch);
	priv->vdi_in_ch = शून्य;

	अगर (priv->vdi_in_ch_n)
		ipu_idmac_put(priv->vdi_in_ch_n);
	priv->vdi_in_ch_n = शून्य;

	अगर (!IS_ERR_OR_शून्य(priv->vdi))
		ipu_vdi_put(priv->vdi);
	priv->vdi = शून्य;
पूर्ण

अटल पूर्णांक vdic_get_ipu_resources(काष्ठा vdic_priv *priv)
अणु
	पूर्णांक ret, err_chan;
	काष्ठा ipuv3_channel *ch;
	काष्ठा ipu_vdi *vdi;

	vdi = ipu_vdi_get(priv->ipu);
	अगर (IS_ERR(vdi)) अणु
		v4l2_err(&priv->sd, "failed to get VDIC\n");
		ret = PTR_ERR(vdi);
		जाओ out;
	पूर्ण
	priv->vdi = vdi;

	अगर (!priv->csi_direct) अणु
		ch = ipu_idmac_get(priv->ipu, IPUV3_CHANNEL_MEM_VDI_PREV);
		अगर (IS_ERR(ch)) अणु
			err_chan = IPUV3_CHANNEL_MEM_VDI_PREV;
			ret = PTR_ERR(ch);
			जाओ out_err_chan;
		पूर्ण
		priv->vdi_in_ch_p = ch;

		ch = ipu_idmac_get(priv->ipu, IPUV3_CHANNEL_MEM_VDI_CUR);
		अगर (IS_ERR(ch)) अणु
			err_chan = IPUV3_CHANNEL_MEM_VDI_CUR;
			ret = PTR_ERR(ch);
			जाओ out_err_chan;
		पूर्ण
		priv->vdi_in_ch = ch;

		ch = ipu_idmac_get(priv->ipu, IPUV3_CHANNEL_MEM_VDI_NEXT);
		अगर (IS_ERR(ch)) अणु
			err_chan = IPUV3_CHANNEL_MEM_VDI_NEXT;
			ret = PTR_ERR(ch);
			जाओ out_err_chan;
		पूर्ण
		priv->vdi_in_ch_n = ch;
	पूर्ण

	वापस 0;

out_err_chan:
	v4l2_err(&priv->sd, "could not get IDMAC channel %u\n", err_chan);
out:
	vdic_put_ipu_resources(priv);
	वापस ret;
पूर्ण

/*
 * This function is currently unused, but will be called when the
 * output/mem2mem device at the IDMAC input pad sends us a new
 * buffer. It kicks off the IDMAC पढ़ो channels to bring in the
 * buffer fields from memory and begin the conversions.
 */
अटल व्योम __maybe_unused prepare_vdi_in_buffers(काष्ठा vdic_priv *priv,
						  काष्ठा imx_media_buffer *curr)
अणु
	dma_addr_t prev_phys, curr_phys, next_phys;
	काष्ठा imx_media_buffer *prev;
	काष्ठा vb2_buffer *curr_vb, *prev_vb;
	u32 fs = priv->field_size;
	u32 is = priv->in_stride;

	/* current input buffer is now previous */
	priv->prev_in_buf = priv->curr_in_buf;
	priv->curr_in_buf = curr;
	prev = priv->prev_in_buf ? priv->prev_in_buf : curr;

	prev_vb = &prev->vbuf.vb2_buf;
	curr_vb = &curr->vbuf.vb2_buf;

	चयन (priv->fieldtype) अणु
	हाल V4L2_FIELD_SEQ_TB:
	हाल V4L2_FIELD_SEQ_BT:
		prev_phys = vb2_dma_contig_plane_dma_addr(prev_vb, 0) + fs;
		curr_phys = vb2_dma_contig_plane_dma_addr(curr_vb, 0);
		next_phys = vb2_dma_contig_plane_dma_addr(curr_vb, 0) + fs;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED_TB:
	हाल V4L2_FIELD_INTERLACED_BT:
	हाल V4L2_FIELD_INTERLACED:
		prev_phys = vb2_dma_contig_plane_dma_addr(prev_vb, 0) + is;
		curr_phys = vb2_dma_contig_plane_dma_addr(curr_vb, 0);
		next_phys = vb2_dma_contig_plane_dma_addr(curr_vb, 0) + is;
		अवरोध;
	शेष:
		/*
		 * can't get here, priv->fieldtype can only be one of
		 * the above. This is to quiet smatch errors.
		 */
		वापस;
	पूर्ण

	ipu_cpmem_set_buffer(priv->vdi_in_ch_p, 0, prev_phys);
	ipu_cpmem_set_buffer(priv->vdi_in_ch,   0, curr_phys);
	ipu_cpmem_set_buffer(priv->vdi_in_ch_n, 0, next_phys);

	ipu_idmac_select_buffer(priv->vdi_in_ch_p, 0);
	ipu_idmac_select_buffer(priv->vdi_in_ch, 0);
	ipu_idmac_select_buffer(priv->vdi_in_ch_n, 0);
पूर्ण

अटल पूर्णांक setup_vdi_channel(काष्ठा vdic_priv *priv,
			     काष्ठा ipuv3_channel *channel,
			     dma_addr_t phys0, dma_addr_t phys1)
अणु
	काष्ठा imx_media_video_dev *vdev = priv->vdev;
	अचिन्हित पूर्णांक burst_size;
	काष्ठा ipu_image image;
	पूर्णांक ret;

	ipu_cpmem_zero(channel);

	स_रखो(&image, 0, माप(image));
	image.pix = vdev->fmt;
	image.rect = vdev->compose;
	/* one field to VDIC channels */
	image.pix.height /= 2;
	image.rect.height /= 2;
	image.phys0 = phys0;
	image.phys1 = phys1;

	ret = ipu_cpmem_set_image(channel, &image);
	अगर (ret)
		वापस ret;

	burst_size = (image.pix.width & 0xf) ? 8 : 16;
	ipu_cpmem_set_burstsize(channel, burst_size);

	ipu_cpmem_set_axi_id(channel, 1);

	ipu_idmac_set_द्विगुन_buffer(channel, false);

	वापस 0;
पूर्ण

अटल पूर्णांक vdic_setup_direct(काष्ठा vdic_priv *priv)
अणु
	/* set VDIC to receive from CSI क्रम direct path */
	ipu_fsu_link(priv->ipu, IPUV3_CHANNEL_CSI_सूचीECT,
		     IPUV3_CHANNEL_CSI_VDI_PREV);

	वापस 0;
पूर्ण

अटल व्योम vdic_start_direct(काष्ठा vdic_priv *priv)
अणु
पूर्ण

अटल व्योम vdic_stop_direct(काष्ठा vdic_priv *priv)
अणु
पूर्ण

अटल व्योम vdic_disable_direct(काष्ठा vdic_priv *priv)
अणु
	ipu_fsu_unlink(priv->ipu, IPUV3_CHANNEL_CSI_सूचीECT,
		       IPUV3_CHANNEL_CSI_VDI_PREV);
पूर्ण

अटल पूर्णांक vdic_setup_indirect(काष्ठा vdic_priv *priv)
अणु
	काष्ठा v4l2_mbus_framefmt *infmt;
	स्थिर काष्ठा imx_media_pixfmt *incc;
	पूर्णांक in_size, ret;

	infmt = &priv->क्रमmat_mbus[VDIC_SINK_PAD_IDMAC];
	incc = priv->cc[VDIC_SINK_PAD_IDMAC];

	in_size = (infmt->width * incc->bpp * infmt->height) >> 3;

	/* 1/2 full image size */
	priv->field_size = in_size / 2;
	priv->in_stride = incc->planar ?
		infmt->width : (infmt->width * incc->bpp) >> 3;

	priv->prev_in_buf = शून्य;
	priv->curr_in_buf = शून्य;

	priv->fieldtype = infmt->field;

	/* init the vdi-in channels */
	ret = setup_vdi_channel(priv, priv->vdi_in_ch_p, 0, 0);
	अगर (ret)
		वापस ret;
	ret = setup_vdi_channel(priv, priv->vdi_in_ch, 0, 0);
	अगर (ret)
		वापस ret;
	वापस setup_vdi_channel(priv, priv->vdi_in_ch_n, 0, 0);
पूर्ण

अटल व्योम vdic_start_indirect(काष्ठा vdic_priv *priv)
अणु
	/* enable the channels */
	ipu_idmac_enable_channel(priv->vdi_in_ch_p);
	ipu_idmac_enable_channel(priv->vdi_in_ch);
	ipu_idmac_enable_channel(priv->vdi_in_ch_n);
पूर्ण

अटल व्योम vdic_stop_indirect(काष्ठा vdic_priv *priv)
अणु
	/* disable channels */
	ipu_idmac_disable_channel(priv->vdi_in_ch_p);
	ipu_idmac_disable_channel(priv->vdi_in_ch);
	ipu_idmac_disable_channel(priv->vdi_in_ch_n);
पूर्ण

अटल व्योम vdic_disable_indirect(काष्ठा vdic_priv *priv)
अणु
पूर्ण

अटल काष्ठा vdic_pipeline_ops direct_ops = अणु
	.setup = vdic_setup_direct,
	.start = vdic_start_direct,
	.stop = vdic_stop_direct,
	.disable = vdic_disable_direct,
पूर्ण;

अटल काष्ठा vdic_pipeline_ops indirect_ops = अणु
	.setup = vdic_setup_indirect,
	.start = vdic_start_indirect,
	.stop = vdic_stop_indirect,
	.disable = vdic_disable_indirect,
पूर्ण;

अटल पूर्णांक vdic_start(काष्ठा vdic_priv *priv)
अणु
	काष्ठा v4l2_mbus_framefmt *infmt;
	पूर्णांक ret;

	infmt = &priv->क्रमmat_mbus[priv->active_input_pad];

	priv->ops = priv->csi_direct ? &direct_ops : &indirect_ops;

	ret = vdic_get_ipu_resources(priv);
	अगर (ret)
		वापस ret;

	/*
	 * init the VDIC.
	 *
	 * note we करोn't give infmt->code to ipu_vdi_setup(). The VDIC
	 * only supports 4:2:2 or 4:2:0, and this subdev will only
	 * negotiate 4:2:2 at its sink pads.
	 */
	ipu_vdi_setup(priv->vdi, MEDIA_BUS_FMT_UYVY8_2X8,
		      infmt->width, infmt->height);
	ipu_vdi_set_field_order(priv->vdi, V4L2_STD_UNKNOWN, infmt->field);
	ipu_vdi_set_motion(priv->vdi, priv->motion);

	ret = priv->ops->setup(priv);
	अगर (ret)
		जाओ out_put_ipu;

	ipu_vdi_enable(priv->vdi);

	priv->ops->start(priv);

	वापस 0;

out_put_ipu:
	vdic_put_ipu_resources(priv);
	वापस ret;
पूर्ण

अटल व्योम vdic_stop(काष्ठा vdic_priv *priv)
अणु
	priv->ops->stop(priv);
	ipu_vdi_disable(priv->vdi);
	priv->ops->disable(priv);

	vdic_put_ipu_resources(priv);
पूर्ण

/*
 * V4L2 subdev operations.
 */

अटल पूर्णांक vdic_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा vdic_priv *priv = container_of(ctrl->handler,
					      काष्ठा vdic_priv, ctrl_hdlr);
	क्रमागत ipu_motion_sel motion;
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_DEINTERLACING_MODE:
		motion = ctrl->val;
		अगर (motion != priv->motion) अणु
			/* can't change motion control mid-streaming */
			अगर (priv->stream_count > 0) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			priv->motion = motion;
		पूर्ण
		अवरोध;
	शेष:
		v4l2_err(&priv->sd, "Invalid control\n");
		ret = -EINVAL;
	पूर्ण

out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vdic_ctrl_ops = अणु
	.s_ctrl = vdic_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vdic_ctrl_motion_menu[] = अणु
	"No Motion Compensation",
	"Low Motion",
	"Medium Motion",
	"High Motion",
पूर्ण;

अटल पूर्णांक vdic_init_controls(काष्ठा vdic_priv *priv)
अणु
	काष्ठा v4l2_ctrl_handler *hdlr = &priv->ctrl_hdlr;
	पूर्णांक ret;

	v4l2_ctrl_handler_init(hdlr, 1);

	v4l2_ctrl_new_std_menu_items(hdlr, &vdic_ctrl_ops,
				     V4L2_CID_DEINTERLACING_MODE,
				     HIGH_MOTION, 0, HIGH_MOTION,
				     vdic_ctrl_motion_menu);

	priv->sd.ctrl_handler = hdlr;

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

अटल पूर्णांक vdic_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा vdic_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_subdev *src_sd = शून्य;
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	अगर (!priv->src || !priv->sink_sd) अणु
		ret = -EPIPE;
		जाओ out;
	पूर्ण

	अगर (priv->csi_direct)
		src_sd = media_entity_to_v4l2_subdev(priv->src);

	/*
	 * enable/disable streaming only अगर stream_count is
	 * going from 0 to 1 / 1 to 0.
	 */
	अगर (priv->stream_count != !enable)
		जाओ update_count;

	dev_dbg(priv->ipu_dev, "%s: stream %s\n", sd->name,
		enable ? "ON" : "OFF");

	अगर (enable)
		ret = vdic_start(priv);
	अन्यथा
		vdic_stop(priv);
	अगर (ret)
		जाओ out;

	अगर (src_sd) अणु
		/* start/stop upstream */
		ret = v4l2_subdev_call(src_sd, video, s_stream, enable);
		ret = (ret && ret != -ENOIOCTLCMD) ? ret : 0;
		अगर (ret) अणु
			अगर (enable)
				vdic_stop(priv);
			जाओ out;
		पूर्ण
	पूर्ण

update_count:
	priv->stream_count += enable ? 1 : -1;
	अगर (priv->stream_count < 0)
		priv->stream_count = 0;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__vdic_get_fmt(काष्ठा vdic_priv *priv, काष्ठा v4l2_subdev_pad_config *cfg,
	       अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&priv->sd, cfg, pad);
	अन्यथा
		वापस &priv->क्रमmat_mbus[pad];
पूर्ण

अटल पूर्णांक vdic_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad >= VDIC_NUM_PADS)
		वापस -EINVAL;

	वापस imx_media_क्रमागत_ipu_क्रमmats(&code->code, code->index,
					  PIXFMT_SEL_YUV);
पूर्ण

अटल पूर्णांक vdic_get_fmt(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा vdic_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *fmt;
	पूर्णांक ret = 0;

	अगर (sdक्रमmat->pad >= VDIC_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	fmt = __vdic_get_fmt(priv, cfg, sdक्रमmat->pad, sdक्रमmat->which);
	अगर (!fmt) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	sdक्रमmat->क्रमmat = *fmt;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल व्योम vdic_try_fmt(काष्ठा vdic_priv *priv,
			 काष्ठा v4l2_subdev_pad_config *cfg,
			 काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat,
			 स्थिर काष्ठा imx_media_pixfmt **cc)
अणु
	काष्ठा v4l2_mbus_framefmt *infmt;

	*cc = imx_media_find_ipu_क्रमmat(sdक्रमmat->क्रमmat.code,
					PIXFMT_SEL_YUV);
	अगर (!*cc) अणु
		u32 code;

		imx_media_क्रमागत_ipu_क्रमmats(&code, 0, PIXFMT_SEL_YUV);
		*cc = imx_media_find_ipu_क्रमmat(code, PIXFMT_SEL_YUV);
		sdक्रमmat->क्रमmat.code = (*cc)->codes[0];
	पूर्ण

	infmt = __vdic_get_fmt(priv, cfg, priv->active_input_pad,
			       sdक्रमmat->which);

	चयन (sdक्रमmat->pad) अणु
	हाल VDIC_SRC_PAD_सूचीECT:
		sdक्रमmat->क्रमmat = *infmt;
		/* output is always progressive! */
		sdक्रमmat->क्रमmat.field = V4L2_FIELD_NONE;
		अवरोध;
	हाल VDIC_SINK_PAD_सूचीECT:
	हाल VDIC_SINK_PAD_IDMAC:
		v4l_bound_align_image(&sdक्रमmat->क्रमmat.width,
				      MIN_W, MAX_W_VDIC, W_ALIGN,
				      &sdक्रमmat->क्रमmat.height,
				      MIN_H, MAX_H_VDIC, H_ALIGN, S_ALIGN);

		/* input must be पूर्णांकerlaced! Choose SEQ_TB अगर not */
		अगर (!V4L2_FIELD_HAS_BOTH(sdक्रमmat->क्रमmat.field))
			sdक्रमmat->क्रमmat.field = V4L2_FIELD_SEQ_TB;
		अवरोध;
	पूर्ण

	imx_media_try_colorimetry(&sdक्रमmat->क्रमmat, true);
पूर्ण

अटल पूर्णांक vdic_set_fmt(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा vdic_priv *priv = v4l2_get_subdevdata(sd);
	स्थिर काष्ठा imx_media_pixfmt *cc;
	काष्ठा v4l2_mbus_framefmt *fmt;
	पूर्णांक ret = 0;

	अगर (sdक्रमmat->pad >= VDIC_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	अगर (priv->stream_count > 0) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	vdic_try_fmt(priv, cfg, sdक्रमmat, &cc);

	fmt = __vdic_get_fmt(priv, cfg, sdक्रमmat->pad, sdक्रमmat->which);
	*fmt = sdक्रमmat->क्रमmat;

	/* propagate क्रमmat to source pad */
	अगर (sdक्रमmat->pad == VDIC_SINK_PAD_सूचीECT ||
	    sdक्रमmat->pad == VDIC_SINK_PAD_IDMAC) अणु
		स्थिर काष्ठा imx_media_pixfmt *outcc;
		काष्ठा v4l2_mbus_framefmt *outfmt;
		काष्ठा v4l2_subdev_क्रमmat क्रमmat;

		क्रमmat.pad = VDIC_SRC_PAD_सूचीECT;
		क्रमmat.which = sdक्रमmat->which;
		क्रमmat.क्रमmat = sdक्रमmat->क्रमmat;
		vdic_try_fmt(priv, cfg, &क्रमmat, &outcc);

		outfmt = __vdic_get_fmt(priv, cfg, VDIC_SRC_PAD_सूचीECT,
					sdक्रमmat->which);
		*outfmt = क्रमmat.क्रमmat;
		अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
			priv->cc[VDIC_SRC_PAD_सूचीECT] = outcc;
	पूर्ण

	अगर (sdक्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		priv->cc[sdक्रमmat->pad] = cc;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vdic_link_setup(काष्ठा media_entity *entity,
			    स्थिर काष्ठा media_pad *local,
			    स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा vdic_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_subdev *remote_sd;
	पूर्णांक ret = 0;

	dev_dbg(priv->ipu_dev, "%s: link setup %s -> %s",
		sd->name, remote->entity->name, local->entity->name);

	mutex_lock(&priv->lock);

	अगर (local->flags & MEDIA_PAD_FL_SOURCE) अणु
		अगर (!is_media_entity_v4l2_subdev(remote->entity)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		remote_sd = media_entity_to_v4l2_subdev(remote->entity);

		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (priv->sink_sd) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			priv->sink_sd = remote_sd;
		पूर्ण अन्यथा अणु
			priv->sink_sd = शून्य;
		पूर्ण

		जाओ out;
	पूर्ण

	/* this is a sink pad */

	अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
		अगर (priv->src) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->src = शून्य;
		जाओ out;
	पूर्ण

	अगर (local->index == VDIC_SINK_PAD_IDMAC) अणु
		काष्ठा imx_media_video_dev *vdev = priv->vdev;

		अगर (!is_media_entity_v4l2_video_device(remote->entity)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (!vdev) अणु
			ret = -ENODEV;
			जाओ out;
		पूर्ण

		priv->csi_direct = false;
	पूर्ण अन्यथा अणु
		अगर (!is_media_entity_v4l2_subdev(remote->entity)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		remote_sd = media_entity_to_v4l2_subdev(remote->entity);

		/* direct pad must connect to a CSI */
		अगर (!(remote_sd->grp_id & IMX_MEDIA_GRP_ID_IPU_CSI) ||
		    remote->index != CSI_SRC_PAD_सूचीECT) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		priv->csi_direct = true;
	पूर्ण

	priv->src = remote->entity;
	/* record which input pad is now active */
	priv->active_input_pad = local->index;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vdic_link_validate(काष्ठा v4l2_subdev *sd,
			      काष्ठा media_link *link,
			      काष्ठा v4l2_subdev_क्रमmat *source_fmt,
			      काष्ठा v4l2_subdev_क्रमmat *sink_fmt)
अणु
	काष्ठा vdic_priv *priv = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	ret = v4l2_subdev_link_validate_शेष(sd, link,
						source_fmt, sink_fmt);
	अगर (ret)
		वापस ret;

	mutex_lock(&priv->lock);

	अगर (priv->csi_direct && priv->motion != HIGH_MOTION) अणु
		v4l2_err(&priv->sd,
			 "direct CSI pipeline requires high motion\n");
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vdic_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा vdic_priv *priv = v4l2_get_subdevdata(sd);

	अगर (fi->pad >= VDIC_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	fi->पूर्णांकerval = priv->frame_पूर्णांकerval[fi->pad];

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vdic_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा vdic_priv *priv = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_fract *input_fi, *output_fi;
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	input_fi = &priv->frame_पूर्णांकerval[priv->active_input_pad];
	output_fi = &priv->frame_पूर्णांकerval[VDIC_SRC_PAD_सूचीECT];

	चयन (fi->pad) अणु
	हाल VDIC_SINK_PAD_सूचीECT:
	हाल VDIC_SINK_PAD_IDMAC:
		/* No limits on valid input frame पूर्णांकervals */
		अगर (fi->पूर्णांकerval.numerator == 0 ||
		    fi->पूर्णांकerval.denominator == 0)
			fi->पूर्णांकerval = priv->frame_पूर्णांकerval[fi->pad];
		/* Reset output पूर्णांकerval */
		*output_fi = fi->पूर्णांकerval;
		अगर (priv->csi_direct)
			output_fi->denominator *= 2;
		अवरोध;
	हाल VDIC_SRC_PAD_सूचीECT:
		/*
		 * frame rate at output pad is द्विगुन input
		 * rate when using direct CSI->VDIC pipeline.
		 *
		 * TODO: implement VDIC frame skipping
		 */
		fi->पूर्णांकerval = *input_fi;
		अगर (priv->csi_direct)
			fi->पूर्णांकerval.denominator *= 2;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	priv->frame_पूर्णांकerval[fi->pad] = fi->पूर्णांकerval;
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vdic_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा vdic_priv *priv = v4l2_get_subdevdata(sd);
	पूर्णांक i, ret;
	u32 code;

	क्रम (i = 0; i < VDIC_NUM_PADS; i++) अणु
		code = 0;
		अगर (i != VDIC_SINK_PAD_IDMAC)
			imx_media_क्रमागत_ipu_क्रमmats(&code, 0, PIXFMT_SEL_YUV);

		/* set a शेष mbus क्रमmat  */
		ret = imx_media_init_mbus_fmt(&priv->क्रमmat_mbus[i],
					      IMX_MEDIA_DEF_PIX_WIDTH,
					      IMX_MEDIA_DEF_PIX_HEIGHT, code,
					      V4L2_FIELD_NONE, &priv->cc[i]);
		अगर (ret)
			वापस ret;

		/* init शेष frame पूर्णांकerval */
		priv->frame_पूर्णांकerval[i].numerator = 1;
		priv->frame_पूर्णांकerval[i].denominator = 30;
		अगर (i == VDIC_SRC_PAD_सूचीECT)
			priv->frame_पूर्णांकerval[i].denominator *= 2;
	पूर्ण

	priv->active_input_pad = VDIC_SINK_PAD_सूचीECT;

	वापस vdic_init_controls(priv);
पूर्ण

अटल व्योम vdic_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा vdic_priv *priv = v4l2_get_subdevdata(sd);

	v4l2_ctrl_handler_मुक्त(&priv->ctrl_hdlr);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops vdic_pad_ops = अणु
	.init_cfg = imx_media_init_cfg,
	.क्रमागत_mbus_code = vdic_क्रमागत_mbus_code,
	.get_fmt = vdic_get_fmt,
	.set_fmt = vdic_set_fmt,
	.link_validate = vdic_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops vdic_video_ops = अणु
	.g_frame_पूर्णांकerval = vdic_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = vdic_s_frame_पूर्णांकerval,
	.s_stream = vdic_s_stream,
पूर्ण;

अटल स्थिर काष्ठा media_entity_operations vdic_entity_ops = अणु
	.link_setup = vdic_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops vdic_subdev_ops = अणु
	.video = &vdic_video_ops,
	.pad = &vdic_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops vdic_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = vdic_रेजिस्टरed,
	.unरेजिस्टरed = vdic_unरेजिस्टरed,
पूर्ण;

काष्ठा v4l2_subdev *imx_media_vdic_रेजिस्टर(काष्ठा v4l2_device *v4l2_dev,
					    काष्ठा device *ipu_dev,
					    काष्ठा ipu_soc *ipu,
					    u32 grp_id)
अणु
	काष्ठा vdic_priv *priv;
	पूर्णांक i, ret;

	priv = devm_kzalloc(ipu_dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	priv->ipu_dev = ipu_dev;
	priv->ipu = ipu;

	v4l2_subdev_init(&priv->sd, &vdic_subdev_ops);
	v4l2_set_subdevdata(&priv->sd, priv);
	priv->sd.पूर्णांकernal_ops = &vdic_पूर्णांकernal_ops;
	priv->sd.entity.ops = &vdic_entity_ops;
	priv->sd.entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
	priv->sd.owner = ipu_dev->driver->owner;
	priv->sd.flags = V4L2_SUBDEV_FL_HAS_DEVNODE;
	priv->sd.grp_id = grp_id;
	imx_media_grp_id_to_sd_name(priv->sd.name, माप(priv->sd.name),
				    priv->sd.grp_id, ipu_get_num(ipu));

	mutex_init(&priv->lock);

	क्रम (i = 0; i < VDIC_NUM_PADS; i++)
		priv->pad[i].flags = (i == VDIC_SRC_PAD_सूचीECT) ?
			MEDIA_PAD_FL_SOURCE : MEDIA_PAD_FL_SINK;

	ret = media_entity_pads_init(&priv->sd.entity, VDIC_NUM_PADS,
				     priv->pad);
	अगर (ret)
		जाओ मुक्त;

	ret = v4l2_device_रेजिस्टर_subdev(v4l2_dev, &priv->sd);
	अगर (ret)
		जाओ मुक्त;

	वापस &priv->sd;
मुक्त:
	mutex_destroy(&priv->lock);
	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक imx_media_vdic_unरेजिस्टर(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा vdic_priv *priv = v4l2_get_subdevdata(sd);

	v4l2_info(sd, "Removing\n");

	v4l2_device_unरेजिस्टर_subdev(sd);
	mutex_destroy(&priv->lock);
	media_entity_cleanup(&sd->entity);

	वापस 0;
पूर्ण
