<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * V4L2 Image Converter Subdev क्रम Freescale i.MX5/6 SOC
 *
 * Copyright (c) 2014-2016 Mentor Graphics Inc.
 */
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश "imx-media.h"
#समावेश "imx-ic.h"

#घोषणा IC_TASK_PRP IC_NUM_TASKS
#घोषणा IC_NUM_OPS  (IC_NUM_TASKS + 1)

अटल काष्ठा imx_ic_ops *ic_ops[IC_NUM_OPS] = अणु
	[IC_TASK_PRP]            = &imx_ic_prp_ops,
	[IC_TASK_ENCODER]        = &imx_ic_prpencvf_ops,
	[IC_TASK_VIEWFINDER]     = &imx_ic_prpencvf_ops,
पूर्ण;

काष्ठा v4l2_subdev *imx_media_ic_रेजिस्टर(काष्ठा v4l2_device *v4l2_dev,
					  काष्ठा device *ipu_dev,
					  काष्ठा ipu_soc *ipu,
					  u32 grp_id)
अणु
	काष्ठा imx_ic_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(ipu_dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	priv->ipu_dev = ipu_dev;
	priv->ipu = ipu;

	/* get our IC task id */
	चयन (grp_id) अणु
	हाल IMX_MEDIA_GRP_ID_IPU_IC_PRP:
		priv->task_id = IC_TASK_PRP;
		अवरोध;
	हाल IMX_MEDIA_GRP_ID_IPU_IC_PRPENC:
		priv->task_id = IC_TASK_ENCODER;
		अवरोध;
	हाल IMX_MEDIA_GRP_ID_IPU_IC_PRPVF:
		priv->task_id = IC_TASK_VIEWFINDER;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	v4l2_subdev_init(&priv->sd, ic_ops[priv->task_id]->subdev_ops);
	v4l2_set_subdevdata(&priv->sd, priv);
	priv->sd.पूर्णांकernal_ops = ic_ops[priv->task_id]->पूर्णांकernal_ops;
	priv->sd.entity.ops = ic_ops[priv->task_id]->entity_ops;
	priv->sd.entity.function = MEDIA_ENT_F_PROC_VIDEO_SCALER;
	priv->sd.owner = ipu_dev->driver->owner;
	priv->sd.flags = V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
	priv->sd.grp_id = grp_id;
	imx_media_grp_id_to_sd_name(priv->sd.name, माप(priv->sd.name),
				    priv->sd.grp_id, ipu_get_num(ipu));

	ret = ic_ops[priv->task_id]->init(priv);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = v4l2_device_रेजिस्टर_subdev(v4l2_dev, &priv->sd);
	अगर (ret) अणु
		ic_ops[priv->task_id]->हटाओ(priv);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &priv->sd;
पूर्ण

पूर्णांक imx_media_ic_unरेजिस्टर(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा imx_ic_priv *priv = container_of(sd, काष्ठा imx_ic_priv, sd);

	v4l2_info(sd, "Removing\n");

	ic_ops[priv->task_id]->हटाओ(priv);

	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);

	वापस 0;
पूर्ण
