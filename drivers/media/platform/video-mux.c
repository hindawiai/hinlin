<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * video stream multiplexer controlled via mux control
 *
 * Copyright (C) 2013 Pengutronix, Sascha Hauer <kernel@pengutronix.de>
 * Copyright (C) 2016-2017 Pengutronix, Philipp Zabel <kernel@pengutronix.de>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>

काष्ठा video_mux अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा media_pad *pads;
	काष्ठा v4l2_mbus_framefmt *क्रमmat_mbus;
	काष्ठा mux_control *mux;
	काष्ठा mutex lock;
	पूर्णांक active;
पूर्ण;

अटल स्थिर काष्ठा v4l2_mbus_framefmt video_mux_क्रमmat_mbus_शेष = अणु
	.width = 1,
	.height = 1,
	.code = MEDIA_BUS_FMT_Y8_1X8,
	.field = V4L2_FIELD_NONE,
पूर्ण;

अटल अंतरभूत काष्ठा video_mux *
notअगरier_to_video_mux(काष्ठा v4l2_async_notअगरier *n)
अणु
	वापस container_of(n, काष्ठा video_mux, notअगरier);
पूर्ण

अटल अंतरभूत काष्ठा video_mux *v4l2_subdev_to_video_mux(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा video_mux, subdev);
पूर्ण

अटल पूर्णांक video_mux_link_setup(काष्ठा media_entity *entity,
				स्थिर काष्ठा media_pad *local,
				स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा video_mux *vmux = v4l2_subdev_to_video_mux(sd);
	u16 source_pad = entity->num_pads - 1;
	पूर्णांक ret = 0;

	/*
	 * The mux state is determined by the enabled sink pad link.
	 * Enabling or disabling the source pad link has no effect.
	 */
	अगर (local->flags & MEDIA_PAD_FL_SOURCE)
		वापस 0;

	dev_dbg(sd->dev, "link setup '%s':%d->'%s':%d[%d]",
		remote->entity->name, remote->index, local->entity->name,
		local->index, flags & MEDIA_LNK_FL_ENABLED);

	mutex_lock(&vmux->lock);

	अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
		अगर (vmux->active == local->index)
			जाओ out;

		अगर (vmux->active >= 0) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण

		dev_dbg(sd->dev, "setting %d active\n", local->index);
		ret = mux_control_try_select(vmux->mux, local->index);
		अगर (ret < 0)
			जाओ out;
		vmux->active = local->index;

		/* Propagate the active क्रमmat to the source */
		vmux->क्रमmat_mbus[source_pad] = vmux->क्रमmat_mbus[vmux->active];
	पूर्ण अन्यथा अणु
		अगर (vmux->active != local->index)
			जाओ out;

		dev_dbg(sd->dev, "going inactive\n");
		mux_control_deselect(vmux->mux);
		vmux->active = -1;
	पूर्ण

out:
	mutex_unlock(&vmux->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा media_entity_operations video_mux_ops = अणु
	.link_setup = video_mux_link_setup,
	.link_validate = v4l2_subdev_link_validate,
	.get_fwnode_pad = v4l2_subdev_get_fwnode_pad_1_to_1,
पूर्ण;

अटल पूर्णांक video_mux_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा video_mux *vmux = v4l2_subdev_to_video_mux(sd);
	काष्ठा v4l2_subdev *upstream_sd;
	काष्ठा media_pad *pad;

	अगर (vmux->active == -1) अणु
		dev_err(sd->dev, "Can not start streaming on inactive mux\n");
		वापस -EINVAL;
	पूर्ण

	pad = media_entity_remote_pad(&sd->entity.pads[vmux->active]);
	अगर (!pad) अणु
		dev_err(sd->dev, "Failed to find remote source pad\n");
		वापस -ENOLINK;
	पूर्ण

	अगर (!is_media_entity_v4l2_subdev(pad->entity)) अणु
		dev_err(sd->dev, "Upstream entity is not a v4l2 subdev\n");
		वापस -ENODEV;
	पूर्ण

	upstream_sd = media_entity_to_v4l2_subdev(pad->entity);

	वापस v4l2_subdev_call(upstream_sd, video, s_stream, enable);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops video_mux_subdev_video_ops = अणु
	.s_stream = video_mux_s_stream,
पूर्ण;

अटल काष्ठा v4l2_mbus_framefmt *
__video_mux_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   अचिन्हित पूर्णांक pad, u32 which)
अणु
	काष्ठा video_mux *vmux = v4l2_subdev_to_video_mux(sd);

	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(sd, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &vmux->क्रमmat_mbus[pad];
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक video_mux_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा video_mux *vmux = v4l2_subdev_to_video_mux(sd);

	mutex_lock(&vmux->lock);

	sdक्रमmat->क्रमmat = *__video_mux_get_pad_क्रमmat(sd, cfg, sdक्रमmat->pad,
						       sdक्रमmat->which);

	mutex_unlock(&vmux->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक video_mux_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *sdक्रमmat)
अणु
	काष्ठा video_mux *vmux = v4l2_subdev_to_video_mux(sd);
	काष्ठा v4l2_mbus_framefmt *mbusक्रमmat, *source_mbusक्रमmat;
	काष्ठा media_pad *pad = &vmux->pads[sdक्रमmat->pad];
	u16 source_pad = sd->entity.num_pads - 1;

	mbusक्रमmat = __video_mux_get_pad_क्रमmat(sd, cfg, sdक्रमmat->pad,
					    sdक्रमmat->which);
	अगर (!mbusक्रमmat)
		वापस -EINVAL;

	source_mbusक्रमmat = __video_mux_get_pad_क्रमmat(sd, cfg, source_pad,
						       sdक्रमmat->which);
	अगर (!source_mbusक्रमmat)
		वापस -EINVAL;

	/* No size limitations except V4L2 compliance requirements */
	v4l_bound_align_image(&sdक्रमmat->क्रमmat.width, 1, 65536, 0,
			      &sdक्रमmat->क्रमmat.height, 1, 65536, 0, 0);

	/* All क्रमmats except LVDS and venकरोr specअगरic क्रमmats are acceptable */
	चयन (sdक्रमmat->क्रमmat.code) अणु
	हाल MEDIA_BUS_FMT_RGB444_1X12:
	हाल MEDIA_BUS_FMT_RGB444_2X8_PADHI_BE:
	हाल MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE:
	हाल MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE:
	हाल MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
	हाल MEDIA_BUS_FMT_RGB565_1X16:
	हाल MEDIA_BUS_FMT_BGR565_2X8_BE:
	हाल MEDIA_BUS_FMT_BGR565_2X8_LE:
	हाल MEDIA_BUS_FMT_RGB565_2X8_BE:
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
	हाल MEDIA_BUS_FMT_RGB666_1X18:
	हाल MEDIA_BUS_FMT_RBG888_1X24:
	हाल MEDIA_BUS_FMT_RGB666_1X24_CPADHI:
	हाल MEDIA_BUS_FMT_BGR888_1X24:
	हाल MEDIA_BUS_FMT_GBR888_1X24:
	हाल MEDIA_BUS_FMT_RGB888_1X24:
	हाल MEDIA_BUS_FMT_RGB888_2X12_BE:
	हाल MEDIA_BUS_FMT_RGB888_2X12_LE:
	हाल MEDIA_BUS_FMT_ARGB8888_1X32:
	हाल MEDIA_BUS_FMT_RGB888_1X32_PADHI:
	हाल MEDIA_BUS_FMT_RGB101010_1X30:
	हाल MEDIA_BUS_FMT_RGB121212_1X36:
	हाल MEDIA_BUS_FMT_RGB161616_1X48:
	हाल MEDIA_BUS_FMT_Y8_1X8:
	हाल MEDIA_BUS_FMT_UV8_1X8:
	हाल MEDIA_BUS_FMT_UYVY8_1_5X8:
	हाल MEDIA_BUS_FMT_VYUY8_1_5X8:
	हाल MEDIA_BUS_FMT_YUYV8_1_5X8:
	हाल MEDIA_BUS_FMT_YVYU8_1_5X8:
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
	हाल MEDIA_BUS_FMT_VYUY8_2X8:
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
	हाल MEDIA_BUS_FMT_Y10_1X10:
	हाल MEDIA_BUS_FMT_UYVY10_2X10:
	हाल MEDIA_BUS_FMT_VYUY10_2X10:
	हाल MEDIA_BUS_FMT_YUYV10_2X10:
	हाल MEDIA_BUS_FMT_YVYU10_2X10:
	हाल MEDIA_BUS_FMT_Y12_1X12:
	हाल MEDIA_BUS_FMT_UYVY12_2X12:
	हाल MEDIA_BUS_FMT_VYUY12_2X12:
	हाल MEDIA_BUS_FMT_YUYV12_2X12:
	हाल MEDIA_BUS_FMT_YVYU12_2X12:
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_VYUY8_1X16:
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
	हाल MEDIA_BUS_FMT_YVYU8_1X16:
	हाल MEDIA_BUS_FMT_YDYUYDYV8_1X16:
	हाल MEDIA_BUS_FMT_UYVY10_1X20:
	हाल MEDIA_BUS_FMT_VYUY10_1X20:
	हाल MEDIA_BUS_FMT_YUYV10_1X20:
	हाल MEDIA_BUS_FMT_YVYU10_1X20:
	हाल MEDIA_BUS_FMT_VUY8_1X24:
	हाल MEDIA_BUS_FMT_YUV8_1X24:
	हाल MEDIA_BUS_FMT_UYYVYY8_0_5X24:
	हाल MEDIA_BUS_FMT_UYVY12_1X24:
	हाल MEDIA_BUS_FMT_VYUY12_1X24:
	हाल MEDIA_BUS_FMT_YUYV12_1X24:
	हाल MEDIA_BUS_FMT_YVYU12_1X24:
	हाल MEDIA_BUS_FMT_YUV10_1X30:
	हाल MEDIA_BUS_FMT_UYYVYY10_0_5X30:
	हाल MEDIA_BUS_FMT_AYUV8_1X32:
	हाल MEDIA_BUS_FMT_UYYVYY12_0_5X36:
	हाल MEDIA_BUS_FMT_YUV12_1X36:
	हाल MEDIA_BUS_FMT_YUV16_1X48:
	हाल MEDIA_BUS_FMT_UYYVYY16_0_5X48:
	हाल MEDIA_BUS_FMT_JPEG_1X8:
	हाल MEDIA_BUS_FMT_AHSV8888_1X32:
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
	हाल MEDIA_BUS_FMT_SGBRG10_1X10:
	हाल MEDIA_BUS_FMT_SGRBG10_1X10:
	हाल MEDIA_BUS_FMT_SRGGB10_1X10:
	हाल MEDIA_BUS_FMT_SBGGR12_1X12:
	हाल MEDIA_BUS_FMT_SGBRG12_1X12:
	हाल MEDIA_BUS_FMT_SGRBG12_1X12:
	हाल MEDIA_BUS_FMT_SRGGB12_1X12:
	हाल MEDIA_BUS_FMT_SBGGR14_1X14:
	हाल MEDIA_BUS_FMT_SGBRG14_1X14:
	हाल MEDIA_BUS_FMT_SGRBG14_1X14:
	हाल MEDIA_BUS_FMT_SRGGB14_1X14:
	हाल MEDIA_BUS_FMT_SBGGR16_1X16:
	हाल MEDIA_BUS_FMT_SGBRG16_1X16:
	हाल MEDIA_BUS_FMT_SGRBG16_1X16:
	हाल MEDIA_BUS_FMT_SRGGB16_1X16:
		अवरोध;
	शेष:
		sdक्रमmat->क्रमmat.code = MEDIA_BUS_FMT_Y8_1X8;
		अवरोध;
	पूर्ण
	अगर (sdक्रमmat->क्रमmat.field == V4L2_FIELD_ANY)
		sdक्रमmat->क्रमmat.field = V4L2_FIELD_NONE;

	mutex_lock(&vmux->lock);

	/* Source pad mirrors active sink pad, no limitations on sink pads */
	अगर ((pad->flags & MEDIA_PAD_FL_SOURCE) && vmux->active >= 0)
		sdक्रमmat->क्रमmat = vmux->क्रमmat_mbus[vmux->active];

	*mbusक्रमmat = sdक्रमmat->क्रमmat;

	/* Propagate the क्रमmat from an active sink to source */
	अगर ((pad->flags & MEDIA_PAD_FL_SINK) && (pad->index == vmux->active))
		*source_mbusक्रमmat = sdक्रमmat->क्रमmat;

	mutex_unlock(&vmux->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक video_mux_init_cfg(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा video_mux *vmux = v4l2_subdev_to_video_mux(sd);
	काष्ठा v4l2_mbus_framefmt *mbusक्रमmat;
	अचिन्हित पूर्णांक i;

	mutex_lock(&vmux->lock);

	क्रम (i = 0; i < sd->entity.num_pads; i++) अणु
		mbusक्रमmat = v4l2_subdev_get_try_क्रमmat(sd, cfg, i);
		*mbusक्रमmat = video_mux_क्रमmat_mbus_शेष;
	पूर्ण

	mutex_unlock(&vmux->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops video_mux_pad_ops = अणु
	.init_cfg = video_mux_init_cfg,
	.get_fmt = video_mux_get_क्रमmat,
	.set_fmt = video_mux_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops video_mux_subdev_ops = अणु
	.pad = &video_mux_pad_ops,
	.video = &video_mux_subdev_video_ops,
पूर्ण;

अटल पूर्णांक video_mux_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				  काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा video_mux *vmux = notअगरier_to_video_mux(notअगरier);

	वापस v4l2_create_fwnode_links(sd, &vmux->subdev);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations video_mux_notअगरy_ops = अणु
	.bound = video_mux_notअगरy_bound,
पूर्ण;

अटल पूर्णांक video_mux_async_रेजिस्टर(काष्ठा video_mux *vmux,
				    अचिन्हित पूर्णांक num_input_pads)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	v4l2_async_notअगरier_init(&vmux->notअगरier);

	क्रम (i = 0; i < num_input_pads; i++) अणु
		काष्ठा v4l2_async_subdev *asd;
		काष्ठा fwnode_handle *ep;

		ep = fwnode_graph_get_endpoपूर्णांक_by_id(
			dev_fwnode(vmux->subdev.dev), i, 0,
			FWNODE_GRAPH_ENDPOINT_NEXT);
		अगर (!ep)
			जारी;

		asd = v4l2_async_notअगरier_add_fwnode_remote_subdev(
			&vmux->notअगरier, ep, काष्ठा v4l2_async_subdev);

		fwnode_handle_put(ep);

		अगर (IS_ERR(asd)) अणु
			ret = PTR_ERR(asd);
			/* OK अगर asd alपढ़ोy exists */
			अगर (ret != -EEXIST)
				वापस ret;
		पूर्ण
	पूर्ण

	vmux->notअगरier.ops = &video_mux_notअगरy_ops;

	ret = v4l2_async_subdev_notअगरier_रेजिस्टर(&vmux->subdev,
						  &vmux->notअगरier);
	अगर (ret)
		वापस ret;

	वापस v4l2_async_रेजिस्टर_subdev(&vmux->subdev);
पूर्ण

अटल पूर्णांक video_mux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *ep;
	काष्ठा video_mux *vmux;
	अचिन्हित पूर्णांक num_pads = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	vmux = devm_kzalloc(dev, माप(*vmux), GFP_KERNEL);
	अगर (!vmux)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, vmux);

	v4l2_subdev_init(&vmux->subdev, &video_mux_subdev_ops);
	snम_लिखो(vmux->subdev.name, माप(vmux->subdev.name), "%pOFn", np);
	vmux->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	vmux->subdev.dev = dev;

	/*
	 * The largest numbered port is the output port. It determines
	 * total number of pads.
	 */
	क्रम_each_endpoपूर्णांक_of_node(np, ep) अणु
		काष्ठा of_endpoपूर्णांक endpoपूर्णांक;

		of_graph_parse_endpoपूर्णांक(ep, &endpoपूर्णांक);
		num_pads = max(num_pads, endpoपूर्णांक.port + 1);
	पूर्ण

	अगर (num_pads < 2) अणु
		dev_err(dev, "Not enough ports %d\n", num_pads);
		वापस -EINVAL;
	पूर्ण

	vmux->mux = devm_mux_control_get(dev, शून्य);
	अगर (IS_ERR(vmux->mux)) अणु
		ret = PTR_ERR(vmux->mux);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get mux: %d\n", ret);
		वापस ret;
	पूर्ण

	mutex_init(&vmux->lock);
	vmux->active = -1;
	vmux->pads = devm_kसुस्मृति(dev, num_pads, माप(*vmux->pads),
				  GFP_KERNEL);
	अगर (!vmux->pads)
		वापस -ENOMEM;

	vmux->क्रमmat_mbus = devm_kसुस्मृति(dev, num_pads,
					 माप(*vmux->क्रमmat_mbus),
					 GFP_KERNEL);
	अगर (!vmux->क्रमmat_mbus)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_pads; i++) अणु
		vmux->pads[i].flags = (i < num_pads - 1) ? MEDIA_PAD_FL_SINK
							 : MEDIA_PAD_FL_SOURCE;
		vmux->क्रमmat_mbus[i] = video_mux_क्रमmat_mbus_शेष;
	पूर्ण

	vmux->subdev.entity.function = MEDIA_ENT_F_VID_MUX;
	ret = media_entity_pads_init(&vmux->subdev.entity, num_pads,
				     vmux->pads);
	अगर (ret < 0)
		वापस ret;

	vmux->subdev.entity.ops = &video_mux_ops;

	ret = video_mux_async_रेजिस्टर(vmux, num_pads - 1);
	अगर (ret) अणु
		v4l2_async_notअगरier_unरेजिस्टर(&vmux->notअगरier);
		v4l2_async_notअगरier_cleanup(&vmux->notअगरier);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक video_mux_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा video_mux *vmux = platक्रमm_get_drvdata(pdev);
	काष्ठा v4l2_subdev *sd = &vmux->subdev;

	v4l2_async_notअगरier_unरेजिस्टर(&vmux->notअगरier);
	v4l2_async_notअगरier_cleanup(&vmux->notअगरier);
	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id video_mux_dt_ids[] = अणु
	अणु .compatible = "video-mux", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, video_mux_dt_ids);

अटल काष्ठा platक्रमm_driver video_mux_driver = अणु
	.probe		= video_mux_probe,
	.हटाओ		= video_mux_हटाओ,
	.driver		= अणु
		.of_match_table = video_mux_dt_ids,
		.name = "video-mux",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(video_mux_driver);

MODULE_DESCRIPTION("video stream multiplexer");
MODULE_AUTHOR("Sascha Hauer, Pengutronix");
MODULE_AUTHOR("Philipp Zabel, Pengutronix");
MODULE_LICENSE("GPL");
