<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Analog Devices ADV748X CSI-2 Transmitter
 *
 * Copyright (C) 2017 Renesas Electronics Corp.
 */

#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "adv748x.h"

पूर्णांक adv748x_csi2_set_भव_channel(काष्ठा adv748x_csi2 *tx, अचिन्हित पूर्णांक vc)
अणु
	वापस tx_ग_लिखो(tx, ADV748X_CSI_VC_REF, vc << ADV748X_CSI_VC_REF_SHIFT);
पूर्ण

/**
 * adv748x_csi2_रेजिस्टर_link : Register and link पूर्णांकernal entities
 *
 * @tx: CSI2 निजी entity
 * @v4l2_dev: Video registration device
 * @src: Source subdevice to establish link
 * @src_pad: Pad number of source to link to this @tx
 * @enable: Link enabled flag
 *
 * Ensure that the subdevice is रेजिस्टरed against the v4l2_device, and link the
 * source pad to the sink pad of the CSI2 bus entity.
 */
अटल पूर्णांक adv748x_csi2_रेजिस्टर_link(काष्ठा adv748x_csi2 *tx,
				      काष्ठा v4l2_device *v4l2_dev,
				      काष्ठा v4l2_subdev *src,
				      अचिन्हित पूर्णांक src_pad,
				      bool enable)
अणु
	पूर्णांक ret;

	अगर (!src->v4l2_dev) अणु
		ret = v4l2_device_रेजिस्टर_subdev(v4l2_dev, src);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = media_create_pad_link(&src->entity, src_pad,
				    &tx->sd.entity, ADV748X_CSI2_SINK,
				    enable ? MEDIA_LNK_FL_ENABLED : 0);
	अगर (ret)
		वापस ret;

	अगर (enable)
		tx->src = src;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * v4l2_subdev_पूर्णांकernal_ops
 *
 * We use the पूर्णांकernal रेजिस्टरed operation to be able to ensure that our
 * incremental subdevices (not connected in the क्रमward path) can be रेजिस्टरed
 * against the resulting video path and media device.
 */

अटल पूर्णांक adv748x_csi2_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	काष्ठा adv748x_state *state = tx->state;
	पूर्णांक ret;

	adv_dbg(state, "Registered %s (%s)", is_txa(tx) ? "TXA":"TXB",
			sd->name);

	/*
	 * Link TXA to AFE and HDMI, and TXB to AFE only as TXB cannot output
	 * HDMI.
	 *
	 * The HDMI->TXA link is enabled by शेष, as is the AFE->TXB one.
	 */
	अगर (is_afe_enabled(state)) अणु
		ret = adv748x_csi2_रेजिस्टर_link(tx, sd->v4l2_dev,
						 &state->afe.sd,
						 ADV748X_AFE_SOURCE,
						 is_txb(tx));
		अगर (ret)
			वापस ret;

		/* TXB can output AFE संकेतs only. */
		अगर (is_txb(tx))
			state->afe.tx = tx;
	पूर्ण

	/* Register link to HDMI क्रम TXA only. */
	अगर (is_txb(tx) || !is_hdmi_enabled(state))
		वापस 0;

	ret = adv748x_csi2_रेजिस्टर_link(tx, sd->v4l2_dev, &state->hdmi.sd,
					 ADV748X_HDMI_SOURCE, true);
	अगर (ret)
		वापस ret;

	/* The शेष HDMI output is TXA. */
	state->hdmi.tx = tx;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops adv748x_csi2_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = adv748x_csi2_रेजिस्टरed,
पूर्ण;

/* -----------------------------------------------------------------------------
 * v4l2_subdev_video_ops
 */

अटल पूर्णांक adv748x_csi2_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	काष्ठा v4l2_subdev *src;

	src = adv748x_get_remote_sd(&tx->pads[ADV748X_CSI2_SINK]);
	अगर (!src)
		वापस -EPIPE;

	वापस v4l2_subdev_call(src, video, s_stream, enable);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops adv748x_csi2_video_ops = अणु
	.s_stream = adv748x_csi2_s_stream,
पूर्ण;

/* -----------------------------------------------------------------------------
 * v4l2_subdev_pad_ops
 *
 * The CSI2 bus pads are ignorant to the data sizes or क्रमmats.
 * But we must support setting the pad क्रमmats क्रम क्रमmat propagation.
 */

अटल काष्ठा v4l2_mbus_framefmt *
adv748x_csi2_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    अचिन्हित पूर्णांक pad, u32 which)
अणु
	काष्ठा adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);

	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(sd, cfg, pad);

	वापस &tx->क्रमmat;
पूर्ण

अटल पूर्णांक adv748x_csi2_get_क्रमmat(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	काष्ठा adv748x_state *state = tx->state;
	काष्ठा v4l2_mbus_framefmt *mbusक्रमmat;

	mbusक्रमmat = adv748x_csi2_get_pad_क्रमmat(sd, cfg, sdक्रमmat->pad,
						 sdक्रमmat->which);
	अगर (!mbusक्रमmat)
		वापस -EINVAL;

	mutex_lock(&state->mutex);

	sdक्रमmat->क्रमmat = *mbusक्रमmat;

	mutex_unlock(&state->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक adv748x_csi2_set_क्रमmat(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);
	काष्ठा adv748x_state *state = tx->state;
	काष्ठा v4l2_mbus_framefmt *mbusक्रमmat;
	पूर्णांक ret = 0;

	mbusक्रमmat = adv748x_csi2_get_pad_क्रमmat(sd, cfg, sdक्रमmat->pad,
						 sdक्रमmat->which);
	अगर (!mbusक्रमmat)
		वापस -EINVAL;

	mutex_lock(&state->mutex);

	अगर (sdक्रमmat->pad == ADV748X_CSI2_SOURCE) अणु
		स्थिर काष्ठा v4l2_mbus_framefmt *sink_fmt;

		sink_fmt = adv748x_csi2_get_pad_क्रमmat(sd, cfg,
						       ADV748X_CSI2_SINK,
						       sdक्रमmat->which);

		अगर (!sink_fmt) अणु
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण

		sdक्रमmat->क्रमmat = *sink_fmt;
	पूर्ण

	*mbusक्रमmat = sdक्रमmat->क्रमmat;

unlock:
	mutex_unlock(&state->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक adv748x_csi2_get_mbus_config(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
					काष्ठा v4l2_mbus_config *config)
अणु
	काष्ठा adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);

	अगर (pad != ADV748X_CSI2_SOURCE)
		वापस -EINVAL;

	config->type = V4L2_MBUS_CSI2_DPHY;
	चयन (tx->active_lanes) अणु
	हाल 1:
		config->flags = V4L2_MBUS_CSI2_1_LANE;
		अवरोध;

	हाल 2:
		config->flags = V4L2_MBUS_CSI2_2_LANE;
		अवरोध;

	हाल 3:
		config->flags = V4L2_MBUS_CSI2_3_LANE;
		अवरोध;

	हाल 4:
		config->flags = V4L2_MBUS_CSI2_4_LANE;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops adv748x_csi2_pad_ops = अणु
	.get_fmt = adv748x_csi2_get_क्रमmat,
	.set_fmt = adv748x_csi2_set_क्रमmat,
	.get_mbus_config = adv748x_csi2_get_mbus_config,
पूर्ण;

/* -----------------------------------------------------------------------------
 * v4l2_subdev_ops
 */

अटल स्थिर काष्ठा v4l2_subdev_ops adv748x_csi2_ops = अणु
	.video = &adv748x_csi2_video_ops,
	.pad = &adv748x_csi2_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Subdev module and controls
 */

पूर्णांक adv748x_csi2_set_pixelrate(काष्ठा v4l2_subdev *sd, s64 rate)
अणु
	काष्ठा adv748x_csi2 *tx = adv748x_sd_to_csi2(sd);

	अगर (!tx->pixel_rate)
		वापस -EINVAL;

	वापस v4l2_ctrl_s_ctrl_पूर्णांक64(tx->pixel_rate, rate);
पूर्ण

अटल पूर्णांक adv748x_csi2_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	चयन (ctrl->id) अणु
	हाल V4L2_CID_PIXEL_RATE:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops adv748x_csi2_ctrl_ops = अणु
	.s_ctrl = adv748x_csi2_s_ctrl,
पूर्ण;

अटल पूर्णांक adv748x_csi2_init_controls(काष्ठा adv748x_csi2 *tx)
अणु

	v4l2_ctrl_handler_init(&tx->ctrl_hdl, 1);

	tx->pixel_rate = v4l2_ctrl_new_std(&tx->ctrl_hdl,
					   &adv748x_csi2_ctrl_ops,
					   V4L2_CID_PIXEL_RATE, 1, पूर्णांक_उच्च,
					   1, 1);

	tx->sd.ctrl_handler = &tx->ctrl_hdl;
	अगर (tx->ctrl_hdl.error) अणु
		v4l2_ctrl_handler_मुक्त(&tx->ctrl_hdl);
		वापस tx->ctrl_hdl.error;
	पूर्ण

	वापस v4l2_ctrl_handler_setup(&tx->ctrl_hdl);
पूर्ण

पूर्णांक adv748x_csi2_init(काष्ठा adv748x_state *state, काष्ठा adv748x_csi2 *tx)
अणु
	पूर्णांक ret;

	अगर (!is_tx_enabled(tx))
		वापस 0;

	adv748x_subdev_init(&tx->sd, state, &adv748x_csi2_ops,
			    MEDIA_ENT_F_VID_IF_BRIDGE,
			    is_txa(tx) ? "txa" : "txb");

	/* Ensure that matching is based upon the endpoपूर्णांक fwnodes */
	tx->sd.fwnode = of_fwnode_handle(state->endpoपूर्णांकs[tx->port]);

	/* Register पूर्णांकernal ops क्रम incremental subdev registration */
	tx->sd.पूर्णांकernal_ops = &adv748x_csi2_पूर्णांकernal_ops;

	tx->pads[ADV748X_CSI2_SINK].flags = MEDIA_PAD_FL_SINK;
	tx->pads[ADV748X_CSI2_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&tx->sd.entity, ADV748X_CSI2_NR_PADS,
				     tx->pads);
	अगर (ret)
		वापस ret;

	ret = adv748x_csi2_init_controls(tx);
	अगर (ret)
		जाओ err_मुक्त_media;

	ret = v4l2_async_रेजिस्टर_subdev(&tx->sd);
	अगर (ret)
		जाओ err_मुक्त_ctrl;

	वापस 0;

err_मुक्त_ctrl:
	v4l2_ctrl_handler_मुक्त(&tx->ctrl_hdl);
err_मुक्त_media:
	media_entity_cleanup(&tx->sd.entity);

	वापस ret;
पूर्ण

व्योम adv748x_csi2_cleanup(काष्ठा adv748x_csi2 *tx)
अणु
	अगर (!is_tx_enabled(tx))
		वापस;

	v4l2_async_unरेजिस्टर_subdev(&tx->sd);
	media_entity_cleanup(&tx->sd.entity);
	v4l2_ctrl_handler_मुक्त(&tx->ctrl_hdl);
पूर्ण
