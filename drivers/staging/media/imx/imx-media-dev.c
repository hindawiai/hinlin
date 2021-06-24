<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * V4L2 Media Controller Driver क्रम Freescale i.MX5/6 SOC
 *
 * Copyright (c) 2016-2019 Mentor Graphics Inc.
 */
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/imx.h>
#समावेश "imx-media.h"

अटल अंतरभूत काष्ठा imx_media_dev *notअगरier2dev(काष्ठा v4l2_async_notअगरier *n)
अणु
	वापस container_of(n, काष्ठा imx_media_dev, notअगरier);
पूर्ण

/* async subdev bound notअगरier */
अटल पूर्णांक imx_media_subdev_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
				  काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा imx_media_dev *imxmd = notअगरier2dev(notअगरier);
	पूर्णांक ret;

	अगर (sd->grp_id & IMX_MEDIA_GRP_ID_IPU_CSI) अणु
		/* रेजिस्टर the IPU पूर्णांकernal subdevs */
		ret = imx_media_रेजिस्टर_ipu_पूर्णांकernal_subdevs(imxmd, sd);
		अगर (ret)
			वापस ret;
	पूर्ण

	dev_dbg(imxmd->md.dev, "subdev %s bound\n", sd->name);

	वापस 0;
पूर्ण

/* async subdev complete notअगरier */
अटल पूर्णांक imx6_media_probe_complete(काष्ठा v4l2_async_notअगरier *notअगरier)
अणु
	काष्ठा imx_media_dev *imxmd = notअगरier2dev(notअगरier);
	पूर्णांक ret;

	/* call the imx5/6/7 common probe completion handler */
	ret = imx_media_probe_complete(notअगरier);
	अगर (ret)
		वापस ret;

	mutex_lock(&imxmd->mutex);

	imxmd->m2m_vdev = imx_media_csc_scaler_device_init(imxmd);
	अगर (IS_ERR(imxmd->m2m_vdev)) अणु
		ret = PTR_ERR(imxmd->m2m_vdev);
		imxmd->m2m_vdev = शून्य;
		जाओ unlock;
	पूर्ण

	ret = imx_media_csc_scaler_device_रेजिस्टर(imxmd->m2m_vdev);
unlock:
	mutex_unlock(&imxmd->mutex);
	वापस ret;
पूर्ण

/* async subdev complete notअगरier */
अटल स्थिर काष्ठा v4l2_async_notअगरier_operations imx_media_notअगरier_ops = अणु
	.bound = imx_media_subdev_bound,
	.complete = imx6_media_probe_complete,
पूर्ण;

अटल पूर्णांक imx_media_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा imx_media_dev *imxmd;
	पूर्णांक ret;

	imxmd = imx_media_dev_init(dev, शून्य);
	अगर (IS_ERR(imxmd))
		वापस PTR_ERR(imxmd);

	ret = imx_media_add_of_subdevs(imxmd, node);
	अगर (ret) अणु
		v4l2_err(&imxmd->v4l2_dev,
			 "add_of_subdevs failed with %d\n", ret);
		जाओ cleanup;
	पूर्ण

	ret = imx_media_dev_notअगरier_रेजिस्टर(imxmd, &imx_media_notअगरier_ops);
	अगर (ret)
		जाओ cleanup;

	वापस 0;

cleanup:
	v4l2_async_notअगरier_cleanup(&imxmd->notअगरier);
	v4l2_device_unरेजिस्टर(&imxmd->v4l2_dev);
	media_device_cleanup(&imxmd->md);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_media_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_media_dev *imxmd =
		(काष्ठा imx_media_dev *)platक्रमm_get_drvdata(pdev);

	v4l2_info(&imxmd->v4l2_dev, "Removing imx-media\n");

	अगर (imxmd->m2m_vdev) अणु
		imx_media_csc_scaler_device_unरेजिस्टर(imxmd->m2m_vdev);
		imxmd->m2m_vdev = शून्य;
	पूर्ण

	v4l2_async_notअगरier_unरेजिस्टर(&imxmd->notअगरier);
	imx_media_unरेजिस्टर_ipu_पूर्णांकernal_subdevs(imxmd);
	v4l2_async_notअगरier_cleanup(&imxmd->notअगरier);
	media_device_unरेजिस्टर(&imxmd->md);
	v4l2_device_unरेजिस्टर(&imxmd->v4l2_dev);
	media_device_cleanup(&imxmd->md);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_media_dt_ids[] = अणु
	अणु .compatible = "fsl,imx-capture-subsystem" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_media_dt_ids);

अटल काष्ठा platक्रमm_driver imx_media_pdrv = अणु
	.probe		= imx_media_probe,
	.हटाओ		= imx_media_हटाओ,
	.driver		= अणु
		.name	= "imx-media",
		.of_match_table	= imx_media_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(imx_media_pdrv);

MODULE_DESCRIPTION("i.MX5/6 v4l2 media controller driver");
MODULE_AUTHOR("Steve Longerbeam <steve_longerbeam@mentor.com>");
MODULE_LICENSE("GPL");
