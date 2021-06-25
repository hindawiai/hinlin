<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/host1x.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <media/v4l2-event.h>

#समावेश "video.h"

अटल व्योम tegra_v4l2_dev_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा tegra_video_device *vid;

	vid = container_of(v4l2_dev, काष्ठा tegra_video_device, v4l2_dev);

	/* cleanup channels here as all video device nodes are released */
	tegra_channels_cleanup(vid->vi);

	v4l2_device_unरेजिस्टर(v4l2_dev);
	media_device_unरेजिस्टर(&vid->media_dev);
	media_device_cleanup(&vid->media_dev);
	kमुक्त(vid);
पूर्ण

अटल व्योम tegra_v4l2_dev_notअगरy(काष्ठा v4l2_subdev *sd,
				  अचिन्हित पूर्णांक notअगरication, व्योम *arg)
अणु
	काष्ठा tegra_vi_channel *chan;
	स्थिर काष्ठा v4l2_event *ev = arg;

	अगर (notअगरication != V4L2_DEVICE_NOTIFY_EVENT)
		वापस;

	chan = v4l2_get_subdev_hostdata(sd);
	v4l2_event_queue(&chan->video, arg);
	अगर (ev->type == V4L2_EVENT_SOURCE_CHANGE && vb2_is_streaming(&chan->queue))
		vb2_queue_error(&chan->queue);
पूर्ण

अटल पूर्णांक host1x_video_probe(काष्ठा host1x_device *dev)
अणु
	काष्ठा tegra_video_device *vid;
	पूर्णांक ret;

	vid = kzalloc(माप(*vid), GFP_KERNEL);
	अगर (!vid)
		वापस -ENOMEM;

	dev_set_drvdata(&dev->dev, vid);

	vid->media_dev.dev = &dev->dev;
	strscpy(vid->media_dev.model, "NVIDIA Tegra Video Input Device",
		माप(vid->media_dev.model));

	media_device_init(&vid->media_dev);
	ret = media_device_रेजिस्टर(&vid->media_dev);
	अगर (ret < 0) अणु
		dev_err(&dev->dev,
			"failed to register media device: %d\n", ret);
		जाओ cleanup;
	पूर्ण

	vid->v4l2_dev.mdev = &vid->media_dev;
	vid->v4l2_dev.release = tegra_v4l2_dev_release;
	vid->v4l2_dev.notअगरy = tegra_v4l2_dev_notअगरy;
	ret = v4l2_device_रेजिस्टर(&dev->dev, &vid->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(&dev->dev,
			"V4L2 device registration failed: %d\n", ret);
		जाओ unरेजिस्टर_media;
	पूर्ण

	ret = host1x_device_init(dev);
	अगर (ret < 0)
		जाओ unरेजिस्टर_v4l2;

	अगर (IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG)) अणु
		/*
		 * Both vi and csi channels are available now.
		 * Register v4l2 nodes and create media links क्रम TPG.
		 */
		ret = tegra_v4l2_nodes_setup_tpg(vid);
		अगर (ret < 0) अणु
			dev_err(&dev->dev,
				"failed to setup tpg graph: %d\n", ret);
			जाओ device_निकास;
		पूर्ण
	पूर्ण

	वापस 0;

device_निकास:
	host1x_device_निकास(dev);
	/* vi निकास ops करोes not clean channels, so clean them here */
	tegra_channels_cleanup(vid->vi);
unरेजिस्टर_v4l2:
	v4l2_device_unरेजिस्टर(&vid->v4l2_dev);
unरेजिस्टर_media:
	media_device_unरेजिस्टर(&vid->media_dev);
cleanup:
	media_device_cleanup(&vid->media_dev);
	kमुक्त(vid);
	वापस ret;
पूर्ण

अटल पूर्णांक host1x_video_हटाओ(काष्ठा host1x_device *dev)
अणु
	काष्ठा tegra_video_device *vid = dev_get_drvdata(&dev->dev);

	अगर (IS_ENABLED(CONFIG_VIDEO_TEGRA_TPG))
		tegra_v4l2_nodes_cleanup_tpg(vid);

	host1x_device_निकास(dev);

	/* This calls v4l2_dev release callback on last reference */
	v4l2_device_put(&vid->v4l2_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id host1x_video_subdevs[] = अणु
#अगर defined(CONFIG_ARCH_TEGRA_210_SOC)
	अणु .compatible = "nvidia,tegra210-csi", पूर्ण,
	अणु .compatible = "nvidia,tegra210-vi", पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल काष्ठा host1x_driver host1x_video_driver = अणु
	.driver = अणु
		.name = "tegra-video",
	पूर्ण,
	.probe = host1x_video_probe,
	.हटाओ = host1x_video_हटाओ,
	.subdevs = host1x_video_subdevs,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&tegra_csi_driver,
	&tegra_vi_driver,
पूर्ण;

अटल पूर्णांक __init host1x_video_init(व्योम)
अणु
	पूर्णांक err;

	err = host1x_driver_रेजिस्टर(&host1x_video_driver);
	अगर (err < 0)
		वापस err;

	err = platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
	अगर (err < 0)
		जाओ unरेजिस्टर_host1x;

	वापस 0;

unरेजिस्टर_host1x:
	host1x_driver_unरेजिस्टर(&host1x_video_driver);
	वापस err;
पूर्ण
module_init(host1x_video_init);

अटल व्योम __निकास host1x_video_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
	host1x_driver_unरेजिस्टर(&host1x_video_driver);
पूर्ण
module_निकास(host1x_video_निकास);

MODULE_AUTHOR("Sowjanya Komatineni <skomatineni@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra Host1x Video driver");
MODULE_LICENSE("GPL v2");
