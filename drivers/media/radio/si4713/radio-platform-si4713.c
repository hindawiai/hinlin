<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/media/radio/radio-si4713.c
 *
 * Platक्रमm Driver क्रम Silicon Lअसल Si4713 FM Radio Transmitter:
 *
 * Copyright (c) 2008 Instituto Nokia de Tecnologia - INdT
 * Contact: Eduarकरो Valentin <eduarकरो.valentin@nokia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>
#समावेश "si4713.h"

/* module parameters */
अटल पूर्णांक radio_nr = -1;	/* radio device minor (-1 ==> स्वतः assign) */
module_param(radio_nr, पूर्णांक, 0);
MODULE_PARM_DESC(radio_nr,
		 "Minor number for radio device (-1 ==> auto assign)");

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Eduardo Valentin <eduardo.valentin@nokia.com>");
MODULE_DESCRIPTION("Platform driver for Si4713 FM Radio Transmitter");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("platform:radio-si4713");

/* Driver state काष्ठा */
काष्ठा radio_si4713_device अणु
	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा video_device		radio_dev;
	काष्ठा mutex lock;
पूर्ण;

/* radio_si4713_fops - file operations पूर्णांकerface */
अटल स्थिर काष्ठा v4l2_file_operations radio_si4713_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = v4l2_fh_release,
	.poll = v4l2_ctrl_poll,
	/* Note: locking is करोne at the subdev level in the i2c driver. */
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

/* Video4Linux Interface */

/* radio_si4713_querycap - query device capabilities */
अटल पूर्णांक radio_si4713_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *capability)
अणु
	strscpy(capability->driver, "radio-si4713", माप(capability->driver));
	strscpy(capability->card, "Silicon Labs Si4713 Modulator",
		माप(capability->card));
	strscpy(capability->bus_info, "platform:radio-si4713",
		माप(capability->bus_info));
	वापस 0;
पूर्ण

/*
 * v4l2 ioctl call backs.
 * we are just a wrapper क्रम v4l2_sub_devs.
 */
अटल अंतरभूत काष्ठा v4l2_device *get_v4l2_dev(काष्ठा file *file)
अणु
	वापस &((काष्ठा radio_si4713_device *)video_drvdata(file))->v4l2_dev;
पूर्ण

अटल पूर्णांक radio_si4713_g_modulator(काष्ठा file *file, व्योम *p,
				    काष्ठा v4l2_modulator *vm)
अणु
	वापस v4l2_device_call_until_err(get_v4l2_dev(file), 0, tuner,
					  g_modulator, vm);
पूर्ण

अटल पूर्णांक radio_si4713_s_modulator(काष्ठा file *file, व्योम *p,
				    स्थिर काष्ठा v4l2_modulator *vm)
अणु
	वापस v4l2_device_call_until_err(get_v4l2_dev(file), 0, tuner,
					  s_modulator, vm);
पूर्ण

अटल पूर्णांक radio_si4713_g_frequency(काष्ठा file *file, व्योम *p,
				    काष्ठा v4l2_frequency *vf)
अणु
	वापस v4l2_device_call_until_err(get_v4l2_dev(file), 0, tuner,
					  g_frequency, vf);
पूर्ण

अटल पूर्णांक radio_si4713_s_frequency(काष्ठा file *file, व्योम *p,
				    स्थिर काष्ठा v4l2_frequency *vf)
अणु
	वापस v4l2_device_call_until_err(get_v4l2_dev(file), 0, tuner,
					  s_frequency, vf);
पूर्ण

अटल दीर्घ radio_si4713_शेष(काष्ठा file *file, व्योम *p,
				 bool valid_prio, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	वापस v4l2_device_call_until_err(get_v4l2_dev(file), 0, core,
					  ioctl, cmd, arg);
पूर्ण

अटल काष्ठा v4l2_ioctl_ops radio_si4713_ioctl_ops = अणु
	.vidioc_querycap	= radio_si4713_querycap,
	.vidioc_g_modulator	= radio_si4713_g_modulator,
	.vidioc_s_modulator	= radio_si4713_s_modulator,
	.vidioc_g_frequency	= radio_si4713_g_frequency,
	.vidioc_s_frequency	= radio_si4713_s_frequency,
	.vidioc_log_status      = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_शेष		= radio_si4713_शेष,
पूर्ण;

/* radio_si4713_vdev_ढाँचा - video device पूर्णांकerface */
अटल स्थिर काष्ठा video_device radio_si4713_vdev_ढाँचा = अणु
	.fops			= &radio_si4713_fops,
	.name			= "radio-si4713",
	.release		= video_device_release_empty,
	.ioctl_ops		= &radio_si4713_ioctl_ops,
	.vfl_dir		= VFL_सूची_TX,
पूर्ण;

/* Platक्रमm driver पूर्णांकerface */
/* radio_si4713_pdriver_probe - probe क्रम the device */
अटल पूर्णांक radio_si4713_pdriver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा radio_si4713_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा radio_si4713_device *rsdev;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक rval = 0;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "Cannot proceed without platform data.\n");
		rval = -EINVAL;
		जाओ निकास;
	पूर्ण

	rsdev = devm_kzalloc(&pdev->dev, माप(*rsdev), GFP_KERNEL);
	अगर (!rsdev) अणु
		dev_err(&pdev->dev, "Failed to alloc video device.\n");
		rval = -ENOMEM;
		जाओ निकास;
	पूर्ण
	mutex_init(&rsdev->lock);

	rval = v4l2_device_रेजिस्टर(&pdev->dev, &rsdev->v4l2_dev);
	अगर (rval) अणु
		dev_err(&pdev->dev, "Failed to register v4l2 device.\n");
		जाओ निकास;
	पूर्ण

	sd = i2c_get_clientdata(pdata->subdev);
	rval = v4l2_device_रेजिस्टर_subdev(&rsdev->v4l2_dev, sd);
	अगर (rval) अणु
		dev_err(&pdev->dev, "Cannot get v4l2 subdevice\n");
		जाओ unरेजिस्टर_v4l2_dev;
	पूर्ण

	rsdev->radio_dev = radio_si4713_vdev_ढाँचा;
	rsdev->radio_dev.v4l2_dev = &rsdev->v4l2_dev;
	rsdev->radio_dev.ctrl_handler = sd->ctrl_handler;
	/* Serialize all access to the si4713 */
	rsdev->radio_dev.lock = &rsdev->lock;
	rsdev->radio_dev.device_caps = V4L2_CAP_MODULATOR | V4L2_CAP_RDS_OUTPUT;
	video_set_drvdata(&rsdev->radio_dev, rsdev);
	अगर (video_रेजिस्टर_device(&rsdev->radio_dev, VFL_TYPE_RADIO, radio_nr)) अणु
		dev_err(&pdev->dev, "Could not register video device.\n");
		rval = -EIO;
		जाओ unरेजिस्टर_v4l2_dev;
	पूर्ण
	dev_info(&pdev->dev, "New device successfully probed\n");

	जाओ निकास;

unरेजिस्टर_v4l2_dev:
	v4l2_device_unरेजिस्टर(&rsdev->v4l2_dev);
निकास:
	वापस rval;
पूर्ण

/* radio_si4713_pdriver_हटाओ - हटाओ the device */
अटल पूर्णांक radio_si4713_pdriver_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा radio_si4713_device *rsdev;

	rsdev = container_of(v4l2_dev, काष्ठा radio_si4713_device, v4l2_dev);
	video_unरेजिस्टर_device(&rsdev->radio_dev);
	v4l2_device_unरेजिस्टर(&rsdev->v4l2_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver radio_si4713_pdriver = अणु
	.driver		= अणु
		.name	= "radio-si4713",
	पूर्ण,
	.probe		= radio_si4713_pdriver_probe,
	.हटाओ         = radio_si4713_pdriver_हटाओ,
पूर्ण;

module_platक्रमm_driver(radio_si4713_pdriver);
