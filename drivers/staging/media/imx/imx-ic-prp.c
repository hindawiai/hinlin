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
#समावेश <media/v4l2-subdev.h>
#समावेश <media/imx.h>
#समावेश "imx-media.h"
#समावेश "imx-ic.h"

/*
 * Min/Max supported width and heights.
 */
#घोषणा MIN_W        32
#घोषणा MIN_H        32
#घोषणा MAX_W      4096
#घोषणा MAX_H      4096
#घोषणा W_ALIGN    4 /* multiple of 16 pixels */
#घोषणा H_ALIGN    1 /* multiple of 2 lines */
#घोषणा S_ALIGN    1 /* multiple of 2 */

काष्ठा prp_priv अणु
	काष्ठा imx_ic_priv *ic_priv;
	काष्ठा media_pad pad[PRP_NUM_PADS];

	/* lock to protect all members below */
	काष्ठा mutex lock;

	काष्ठा v4l2_subdev *src_sd;
	काष्ठा v4l2_subdev *sink_sd_prpenc;
	काष्ठा v4l2_subdev *sink_sd_prpvf;

	/* the CSI id at link validate */
	पूर्णांक csi_id;

	काष्ठा v4l2_mbus_framefmt क्रमmat_mbus;
	काष्ठा v4l2_fract frame_पूर्णांकerval;

	पूर्णांक stream_count;
पूर्ण;

अटल अंतरभूत काष्ठा prp_priv *sd_to_priv(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा imx_ic_priv *ic_priv = v4l2_get_subdevdata(sd);

	वापस ic_priv->task_priv;
पूर्ण

अटल पूर्णांक prp_start(काष्ठा prp_priv *priv)
अणु
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;
	bool src_is_vdic;

	/* set IC to receive from CSI or VDI depending on source */
	src_is_vdic = !!(priv->src_sd->grp_id & IMX_MEDIA_GRP_ID_IPU_VDIC);

	ipu_set_ic_src_mux(ic_priv->ipu, priv->csi_id, src_is_vdic);

	वापस 0;
पूर्ण

अटल व्योम prp_stop(काष्ठा prp_priv *priv)
अणु
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__prp_get_fmt(काष्ठा prp_priv *priv, काष्ठा v4l2_subdev_pad_config *cfg,
	      अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	काष्ठा imx_ic_priv *ic_priv = priv->ic_priv;

	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&ic_priv->sd, cfg, pad);
	अन्यथा
		वापस &priv->क्रमmat_mbus;
पूर्ण

/*
 * V4L2 subdev operations.
 */

अटल पूर्णांक prp_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा prp_priv *priv = sd_to_priv(sd);
	काष्ठा v4l2_mbus_framefmt *infmt;
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	चयन (code->pad) अणु
	हाल PRP_SINK_PAD:
		ret = imx_media_क्रमागत_ipu_क्रमmats(&code->code, code->index,
						 PIXFMT_SEL_YUV_RGB);
		अवरोध;
	हाल PRP_SRC_PAD_PRPENC:
	हाल PRP_SRC_PAD_PRPVF:
		अगर (code->index != 0) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		infmt = __prp_get_fmt(priv, cfg, PRP_SINK_PAD, code->which);
		code->code = infmt->code;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक prp_get_fmt(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा prp_priv *priv = sd_to_priv(sd);
	काष्ठा v4l2_mbus_framefmt *fmt;
	पूर्णांक ret = 0;

	अगर (sdक्रमmat->pad >= PRP_NUM_PADS)
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

अटल पूर्णांक prp_set_fmt(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा prp_priv *priv = sd_to_priv(sd);
	काष्ठा v4l2_mbus_framefmt *fmt, *infmt;
	स्थिर काष्ठा imx_media_pixfmt *cc;
	पूर्णांक ret = 0;
	u32 code;

	अगर (sdक्रमmat->pad >= PRP_NUM_PADS)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	अगर (priv->stream_count > 0) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	infmt = __prp_get_fmt(priv, cfg, PRP_SINK_PAD, sdक्रमmat->which);

	चयन (sdक्रमmat->pad) अणु
	हाल PRP_SINK_PAD:
		v4l_bound_align_image(&sdक्रमmat->क्रमmat.width, MIN_W, MAX_W,
				      W_ALIGN, &sdक्रमmat->क्रमmat.height,
				      MIN_H, MAX_H, H_ALIGN, S_ALIGN);

		cc = imx_media_find_ipu_क्रमmat(sdक्रमmat->क्रमmat.code,
					       PIXFMT_SEL_YUV_RGB);
		अगर (!cc) अणु
			imx_media_क्रमागत_ipu_क्रमmats(&code, 0,
						   PIXFMT_SEL_YUV_RGB);
			cc = imx_media_find_ipu_क्रमmat(code,
						       PIXFMT_SEL_YUV_RGB);
			sdक्रमmat->क्रमmat.code = cc->codes[0];
		पूर्ण

		अगर (sdक्रमmat->क्रमmat.field == V4L2_FIELD_ANY)
			sdक्रमmat->क्रमmat.field = V4L2_FIELD_NONE;
		अवरोध;
	हाल PRP_SRC_PAD_PRPENC:
	हाल PRP_SRC_PAD_PRPVF:
		/* Output pads mirror input pad */
		sdक्रमmat->क्रमmat = *infmt;
		अवरोध;
	पूर्ण

	imx_media_try_colorimetry(&sdक्रमmat->क्रमmat, true);

	fmt = __prp_get_fmt(priv, cfg, sdक्रमmat->pad, sdक्रमmat->which);
	*fmt = sdक्रमmat->क्रमmat;
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

	remote_sd = media_entity_to_v4l2_subdev(remote->entity);

	mutex_lock(&priv->lock);

	अगर (local->flags & MEDIA_PAD_FL_SINK) अणु
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (priv->src_sd) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			अगर (priv->sink_sd_prpenc &&
			    (remote_sd->grp_id & IMX_MEDIA_GRP_ID_IPU_VDIC)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			priv->src_sd = remote_sd;
		पूर्ण अन्यथा अणु
			priv->src_sd = शून्य;
		पूर्ण

		जाओ out;
	पूर्ण

	/* this is a source pad */
	अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
		चयन (local->index) अणु
		हाल PRP_SRC_PAD_PRPENC:
			अगर (priv->sink_sd_prpenc) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			अगर (priv->src_sd && (priv->src_sd->grp_id &
					     IMX_MEDIA_GRP_ID_IPU_VDIC)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			priv->sink_sd_prpenc = remote_sd;
			अवरोध;
		हाल PRP_SRC_PAD_PRPVF:
			अगर (priv->sink_sd_prpvf) अणु
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			priv->sink_sd_prpvf = remote_sd;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (local->index) अणु
		हाल PRP_SRC_PAD_PRPENC:
			priv->sink_sd_prpenc = शून्य;
			अवरोध;
		हाल PRP_SRC_PAD_PRPVF:
			priv->sink_sd_prpvf = शून्य;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक prp_link_validate(काष्ठा v4l2_subdev *sd,
			     काष्ठा media_link *link,
			     काष्ठा v4l2_subdev_क्रमmat *source_fmt,
			     काष्ठा v4l2_subdev_क्रमmat *sink_fmt)
अणु
	काष्ठा imx_ic_priv *ic_priv = v4l2_get_subdevdata(sd);
	काष्ठा prp_priv *priv = ic_priv->task_priv;
	काष्ठा v4l2_subdev *csi;
	पूर्णांक ret;

	ret = v4l2_subdev_link_validate_शेष(sd, link,
						source_fmt, sink_fmt);
	अगर (ret)
		वापस ret;

	csi = imx_media_pipeline_subdev(&ic_priv->sd.entity,
					IMX_MEDIA_GRP_ID_IPU_CSI, true);
	अगर (IS_ERR(csi))
		csi = शून्य;

	mutex_lock(&priv->lock);

	अगर (priv->src_sd->grp_id & IMX_MEDIA_GRP_ID_IPU_VDIC) अणु
		/*
		 * the ->PRPENC link cannot be enabled अगर the source
		 * is the VDIC
		 */
		अगर (priv->sink_sd_prpenc) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* the source is a CSI */
		अगर (!csi) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (csi) अणु
		चयन (csi->grp_id) अणु
		हाल IMX_MEDIA_GRP_ID_IPU_CSI0:
			priv->csi_id = 0;
			अवरोध;
		हाल IMX_MEDIA_GRP_ID_IPU_CSI1:
			priv->csi_id = 1;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->csi_id = 0;
	पूर्ण

out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक prp_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा imx_ic_priv *ic_priv = v4l2_get_subdevdata(sd);
	काष्ठा prp_priv *priv = ic_priv->task_priv;
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	अगर (!priv->src_sd || (!priv->sink_sd_prpenc && !priv->sink_sd_prpvf)) अणु
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

	/* start/stop upstream */
	ret = v4l2_subdev_call(priv->src_sd, video, s_stream, enable);
	ret = (ret && ret != -ENOIOCTLCMD) ? ret : 0;
	अगर (ret) अणु
		अगर (enable)
			prp_stop(priv);
		जाओ out;
	पूर्ण

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

	अगर (fi->pad >= PRP_NUM_PADS)
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

	अगर (fi->pad >= PRP_NUM_PADS)
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
	u32 code;

	/* init शेष frame पूर्णांकerval */
	priv->frame_पूर्णांकerval.numerator = 1;
	priv->frame_पूर्णांकerval.denominator = 30;

	/* set a शेष mbus क्रमmat  */
	imx_media_क्रमागत_ipu_क्रमmats(&code, 0, PIXFMT_SEL_YUV);

	वापस imx_media_init_mbus_fmt(&priv->क्रमmat_mbus,
				       IMX_MEDIA_DEF_PIX_WIDTH,
				       IMX_MEDIA_DEF_PIX_HEIGHT, code,
				       V4L2_FIELD_NONE, शून्य);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops prp_pad_ops = अणु
	.init_cfg = imx_media_init_cfg,
	.क्रमागत_mbus_code = prp_क्रमागत_mbus_code,
	.get_fmt = prp_get_fmt,
	.set_fmt = prp_set_fmt,
	.link_validate = prp_link_validate,
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
पूर्ण;

अटल पूर्णांक prp_init(काष्ठा imx_ic_priv *ic_priv)
अणु
	काष्ठा prp_priv *priv;
	पूर्णांक i;

	priv = devm_kzalloc(ic_priv->ipu_dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->lock);
	ic_priv->task_priv = priv;
	priv->ic_priv = ic_priv;

	क्रम (i = 0; i < PRP_NUM_PADS; i++)
		priv->pad[i].flags = (i == PRP_SINK_PAD) ?
			MEDIA_PAD_FL_SINK : MEDIA_PAD_FL_SOURCE;

	वापस media_entity_pads_init(&ic_priv->sd.entity, PRP_NUM_PADS,
				      priv->pad);
पूर्ण

अटल व्योम prp_हटाओ(काष्ठा imx_ic_priv *ic_priv)
अणु
	काष्ठा prp_priv *priv = ic_priv->task_priv;

	mutex_destroy(&priv->lock);
पूर्ण

काष्ठा imx_ic_ops imx_ic_prp_ops = अणु
	.subdev_ops = &prp_subdev_ops,
	.पूर्णांकernal_ops = &prp_पूर्णांकernal_ops,
	.entity_ops = &prp_entity_ops,
	.init = prp_init,
	.हटाओ = prp_हटाओ,
पूर्ण;
