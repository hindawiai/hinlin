<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * radio-timb.c Timberdale FPGA Radio driver
 * Copyright (c) 2009 Intel Corporation
 */

#समावेश <linux/पन.स>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/media/timb_radपन.स>

#घोषणा DRIVER_NAME "timb-radio"

काष्ठा timbradio अणु
	काष्ठा timb_radio_platक्रमm_data	pdata;
	काष्ठा v4l2_subdev	*sd_tuner;
	काष्ठा v4l2_subdev	*sd_dsp;
	काष्ठा video_device	video_dev;
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा mutex		lock;
पूर्ण;


अटल पूर्णांक timbradio_vidioc_querycap(काष्ठा file *file, व्योम  *priv,
	काष्ठा v4l2_capability *v)
अणु
	strscpy(v->driver, DRIVER_NAME, माप(v->driver));
	strscpy(v->card, "Timberdale Radio", माप(v->card));
	snम_लिखो(v->bus_info, माप(v->bus_info), "platform:"DRIVER_NAME);
	वापस 0;
पूर्ण

अटल पूर्णांक timbradio_vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_tuner *v)
अणु
	काष्ठा timbradio *tr = video_drvdata(file);
	वापस v4l2_subdev_call(tr->sd_tuner, tuner, g_tuner, v);
पूर्ण

अटल पूर्णांक timbradio_vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
	स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा timbradio *tr = video_drvdata(file);
	वापस v4l2_subdev_call(tr->sd_tuner, tuner, s_tuner, v);
पूर्ण

अटल पूर्णांक timbradio_vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
	स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा timbradio *tr = video_drvdata(file);
	वापस v4l2_subdev_call(tr->sd_tuner, tuner, s_frequency, f);
पूर्ण

अटल पूर्णांक timbradio_vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_frequency *f)
अणु
	काष्ठा timbradio *tr = video_drvdata(file);
	वापस v4l2_subdev_call(tr->sd_tuner, tuner, g_frequency, f);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops timbradio_ioctl_ops = अणु
	.vidioc_querycap	= timbradio_vidioc_querycap,
	.vidioc_g_tuner		= timbradio_vidioc_g_tuner,
	.vidioc_s_tuner		= timbradio_vidioc_s_tuner,
	.vidioc_g_frequency	= timbradio_vidioc_g_frequency,
	.vidioc_s_frequency	= timbradio_vidioc_s_frequency,
	.vidioc_log_status      = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations timbradio_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.release	= v4l2_fh_release,
	.poll		= v4l2_ctrl_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल पूर्णांक timbradio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा timb_radio_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा timbradio *tr;
	पूर्णांक err;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "Platform data missing\n");
		err = -EINVAL;
		जाओ err;
	पूर्ण

	tr = devm_kzalloc(&pdev->dev, माप(*tr), GFP_KERNEL);
	अगर (!tr) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	tr->pdata = *pdata;
	mutex_init(&tr->lock);

	strscpy(tr->video_dev.name, "Timberdale Radio",
		माप(tr->video_dev.name));
	tr->video_dev.fops = &timbradio_fops;
	tr->video_dev.ioctl_ops = &timbradio_ioctl_ops;
	tr->video_dev.release = video_device_release_empty;
	tr->video_dev.minor = -1;
	tr->video_dev.lock = &tr->lock;
	tr->video_dev.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO;

	strscpy(tr->v4l2_dev.name, DRIVER_NAME, माप(tr->v4l2_dev.name));
	err = v4l2_device_रेजिस्टर(शून्य, &tr->v4l2_dev);
	अगर (err)
		जाओ err;

	tr->video_dev.v4l2_dev = &tr->v4l2_dev;

	tr->sd_tuner = v4l2_i2c_new_subdev_board(&tr->v4l2_dev,
		i2c_get_adapter(pdata->i2c_adapter), pdata->tuner, शून्य);
	tr->sd_dsp = v4l2_i2c_new_subdev_board(&tr->v4l2_dev,
		i2c_get_adapter(pdata->i2c_adapter), pdata->dsp, शून्य);
	अगर (tr->sd_tuner == शून्य || tr->sd_dsp == शून्य) अणु
		err = -ENODEV;
		जाओ err_video_req;
	पूर्ण

	tr->v4l2_dev.ctrl_handler = tr->sd_dsp->ctrl_handler;

	err = video_रेजिस्टर_device(&tr->video_dev, VFL_TYPE_RADIO, -1);
	अगर (err) अणु
		dev_err(&pdev->dev, "Error reg video\n");
		जाओ err_video_req;
	पूर्ण

	video_set_drvdata(&tr->video_dev, tr);

	platक्रमm_set_drvdata(pdev, tr);
	वापस 0;

err_video_req:
	v4l2_device_unरेजिस्टर(&tr->v4l2_dev);
err:
	dev_err(&pdev->dev, "Failed to register: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक timbradio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा timbradio *tr = platक्रमm_get_drvdata(pdev);

	video_unरेजिस्टर_device(&tr->video_dev);
	v4l2_device_unरेजिस्टर(&tr->v4l2_dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver timbradio_platक्रमm_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
	पूर्ण,
	.probe		= timbradio_probe,
	.हटाओ		= timbradio_हटाओ,
पूर्ण;

module_platक्रमm_driver(timbradio_platक्रमm_driver);

MODULE_DESCRIPTION("Timberdale Radio driver");
MODULE_AUTHOR("Mocean Laboratories <info@mocean-labs.com>");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("0.0.2");
MODULE_ALIAS("platform:"DRIVER_NAME);
