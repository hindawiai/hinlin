<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Framework क्रम ISA radio drivers.
 * This takes care of all the V4L2 scaffolding, allowing the ISA drivers
 * to concentrate on the actual hardware operation.
 *
 * Copyright (C) 2012 Hans Verkuil <hans.verkuil@cisco.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>

#समावेश "radio-isa.h"

MODULE_AUTHOR("Hans Verkuil");
MODULE_DESCRIPTION("A framework for ISA radio drivers.");
MODULE_LICENSE("GPL");

#घोषणा FREQ_LOW  (87U * 16000U)
#घोषणा FREQ_HIGH (108U * 16000U)

अटल पूर्णांक radio_isa_querycap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_capability *v)
अणु
	काष्ठा radio_isa_card *isa = video_drvdata(file);

	strscpy(v->driver, isa->drv->driver.driver.name, माप(v->driver));
	strscpy(v->card, isa->drv->card, माप(v->card));
	snम_लिखो(v->bus_info, माप(v->bus_info), "ISA:%s", isa->v4l2_dev.name);
	वापस 0;
पूर्ण

अटल पूर्णांक radio_isa_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *v)
अणु
	काष्ठा radio_isa_card *isa = video_drvdata(file);
	स्थिर काष्ठा radio_isa_ops *ops = isa->drv->ops;

	अगर (v->index > 0)
		वापस -EINVAL;

	strscpy(v->name, "FM", माप(v->name));
	v->type = V4L2_TUNER_RADIO;
	v->rangelow = FREQ_LOW;
	v->rangehigh = FREQ_HIGH;
	v->capability = V4L2_TUNER_CAP_LOW;
	अगर (isa->drv->has_stereo)
		v->capability |= V4L2_TUNER_CAP_STEREO;

	अगर (ops->g_rxsubchans)
		v->rxsubchans = ops->g_rxsubchans(isa);
	अन्यथा
		v->rxsubchans = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_STEREO;
	v->audmode = isa->stereo ? V4L2_TUNER_MODE_STEREO : V4L2_TUNER_MODE_MONO;
	अगर (ops->g_संकेत)
		v->संकेत = ops->g_संकेत(isa);
	अन्यथा
		v->संकेत = (v->rxsubchans & V4L2_TUNER_SUB_STEREO) ?
								0xffff : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक radio_isa_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *v)
अणु
	काष्ठा radio_isa_card *isa = video_drvdata(file);
	स्थिर काष्ठा radio_isa_ops *ops = isa->drv->ops;

	अगर (v->index)
		वापस -EINVAL;
	अगर (ops->s_stereo) अणु
		isa->stereo = (v->audmode == V4L2_TUNER_MODE_STEREO);
		वापस ops->s_stereo(isa, isa->stereo);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक radio_isa_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा radio_isa_card *isa = video_drvdata(file);
	u32 freq = f->frequency;
	पूर्णांक res;

	अगर (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;
	freq = clamp(freq, FREQ_LOW, FREQ_HIGH);
	res = isa->drv->ops->s_frequency(isa, freq);
	अगर (res == 0)
		isa->freq = freq;
	वापस res;
पूर्ण

अटल पूर्णांक radio_isa_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा radio_isa_card *isa = video_drvdata(file);

	अगर (f->tuner != 0)
		वापस -EINVAL;
	f->type = V4L2_TUNER_RADIO;
	f->frequency = isa->freq;
	वापस 0;
पूर्ण

अटल पूर्णांक radio_isa_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा radio_isa_card *isa =
		container_of(ctrl->handler, काष्ठा radio_isa_card, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		वापस isa->drv->ops->s_mute_volume(isa, ctrl->val,
				isa->volume ? isa->volume->val : 0);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक radio_isa_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा radio_isa_card *isa = video_drvdata(file);

	v4l2_info(&isa->v4l2_dev, "I/O Port = 0x%03x\n", isa->io);
	v4l2_ctrl_handler_log_status(&isa->hdl, isa->v4l2_dev.name);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops radio_isa_ctrl_ops = अणु
	.s_ctrl = radio_isa_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations radio_isa_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= v4l2_fh_खोलो,
	.release	= v4l2_fh_release,
	.poll		= v4l2_ctrl_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops radio_isa_ioctl_ops = अणु
	.vidioc_querycap    = radio_isa_querycap,
	.vidioc_g_tuner     = radio_isa_g_tuner,
	.vidioc_s_tuner     = radio_isa_s_tuner,
	.vidioc_g_frequency = radio_isa_g_frequency,
	.vidioc_s_frequency = radio_isa_s_frequency,
	.vidioc_log_status  = radio_isa_log_status,
	.vidioc_subscribe_event   = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

पूर्णांक radio_isa_match(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा radio_isa_driver *drv = pdev->platक्रमm_data;

	वापस drv->probe || drv->io_params[dev] >= 0;
पूर्ण
EXPORT_SYMBOL_GPL(radio_isa_match);

अटल bool radio_isa_valid_io(स्थिर काष्ठा radio_isa_driver *drv, पूर्णांक io)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < drv->num_of_io_ports; i++)
		अगर (drv->io_ports[i] == io)
			वापस true;
	वापस false;
पूर्ण

अटल काष्ठा radio_isa_card *radio_isa_alloc(काष्ठा radio_isa_driver *drv,
				काष्ठा device *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा radio_isa_card *isa = drv->ops->alloc();
	अगर (!isa)
		वापस शून्य;

	dev_set_drvdata(pdev, isa);
	isa->drv = drv;
	v4l2_dev = &isa->v4l2_dev;
	strscpy(v4l2_dev->name, dev_name(pdev), माप(v4l2_dev->name));

	वापस isa;
पूर्ण

अटल पूर्णांक radio_isa_common_probe(काष्ठा radio_isa_card *isa,
				  काष्ठा device *pdev,
				  पूर्णांक radio_nr, अचिन्हित region_size)
अणु
	स्थिर काष्ठा radio_isa_driver *drv = isa->drv;
	स्थिर काष्ठा radio_isa_ops *ops = drv->ops;
	काष्ठा v4l2_device *v4l2_dev = &isa->v4l2_dev;
	पूर्णांक res;

	अगर (!request_region(isa->io, region_size, v4l2_dev->name)) अणु
		v4l2_err(v4l2_dev, "port 0x%x already in use\n", isa->io);
		kमुक्त(isa);
		वापस -EBUSY;
	पूर्ण

	res = v4l2_device_रेजिस्टर(pdev, v4l2_dev);
	अगर (res < 0) अणु
		v4l2_err(v4l2_dev, "Could not register v4l2_device\n");
		जाओ err_dev_reg;
	पूर्ण

	v4l2_ctrl_handler_init(&isa->hdl, 1);
	isa->mute = v4l2_ctrl_new_std(&isa->hdl, &radio_isa_ctrl_ops,
				V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	अगर (drv->max_volume)
		isa->volume = v4l2_ctrl_new_std(&isa->hdl, &radio_isa_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, drv->max_volume, 1,
			drv->max_volume);
	v4l2_dev->ctrl_handler = &isa->hdl;
	अगर (isa->hdl.error) अणु
		res = isa->hdl.error;
		v4l2_err(v4l2_dev, "Could not register controls\n");
		जाओ err_hdl;
	पूर्ण
	अगर (drv->max_volume)
		v4l2_ctrl_cluster(2, &isa->mute);
	v4l2_dev->ctrl_handler = &isa->hdl;

	mutex_init(&isa->lock);
	isa->vdev.lock = &isa->lock;
	strscpy(isa->vdev.name, v4l2_dev->name, माप(isa->vdev.name));
	isa->vdev.v4l2_dev = v4l2_dev;
	isa->vdev.fops = &radio_isa_fops;
	isa->vdev.ioctl_ops = &radio_isa_ioctl_ops;
	isa->vdev.release = video_device_release_empty;
	isa->vdev.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO;
	video_set_drvdata(&isa->vdev, isa);
	isa->freq = FREQ_LOW;
	isa->stereo = drv->has_stereo;

	अगर (ops->init)
		res = ops->init(isa);
	अगर (!res)
		res = v4l2_ctrl_handler_setup(&isa->hdl);
	अगर (!res)
		res = ops->s_frequency(isa, isa->freq);
	अगर (!res && ops->s_stereo)
		res = ops->s_stereo(isa, isa->stereo);
	अगर (res < 0) अणु
		v4l2_err(v4l2_dev, "Could not setup card\n");
		जाओ err_hdl;
	पूर्ण
	res = video_रेजिस्टर_device(&isa->vdev, VFL_TYPE_RADIO, radio_nr);

	अगर (res < 0) अणु
		v4l2_err(v4l2_dev, "Could not register device node\n");
		जाओ err_hdl;
	पूर्ण

	v4l2_info(v4l2_dev, "Initialized radio card %s on port 0x%03x\n",
			drv->card, isa->io);
	वापस 0;

err_hdl:
	v4l2_ctrl_handler_मुक्त(&isa->hdl);
err_dev_reg:
	release_region(isa->io, region_size);
	kमुक्त(isa);
	वापस res;
पूर्ण

अटल व्योम radio_isa_common_हटाओ(काष्ठा radio_isa_card *isa,
				    अचिन्हित region_size)
अणु
	स्थिर काष्ठा radio_isa_ops *ops = isa->drv->ops;

	ops->s_mute_volume(isa, true, isa->volume ? isa->volume->cur.val : 0);
	video_unरेजिस्टर_device(&isa->vdev);
	v4l2_ctrl_handler_मुक्त(&isa->hdl);
	v4l2_device_unरेजिस्टर(&isa->v4l2_dev);
	release_region(isa->io, region_size);
	v4l2_info(&isa->v4l2_dev, "Removed radio card %s\n", isa->drv->card);
	kमुक्त(isa);
पूर्ण

पूर्णांक radio_isa_probe(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा radio_isa_driver *drv = pdev->platक्रमm_data;
	स्थिर काष्ठा radio_isa_ops *ops = drv->ops;
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा radio_isa_card *isa;

	isa = radio_isa_alloc(drv, pdev);
	अगर (!isa)
		वापस -ENOMEM;
	isa->io = drv->io_params[dev];
	v4l2_dev = &isa->v4l2_dev;

	अगर (drv->probe && ops->probe) अणु
		पूर्णांक i;

		क्रम (i = 0; i < drv->num_of_io_ports; ++i) अणु
			पूर्णांक io = drv->io_ports[i];

			अगर (request_region(io, drv->region_size, v4l2_dev->name)) अणु
				bool found = ops->probe(isa, io);

				release_region(io, drv->region_size);
				अगर (found) अणु
					isa->io = io;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!radio_isa_valid_io(drv, isa->io)) अणु
		पूर्णांक i;

		अगर (isa->io < 0)
			वापस -ENODEV;
		v4l2_err(v4l2_dev, "you must set an I/O address with io=0x%03x",
				drv->io_ports[0]);
		क्रम (i = 1; i < drv->num_of_io_ports; i++)
			prपूर्णांकk(KERN_CONT "/0x%03x", drv->io_ports[i]);
		prपूर्णांकk(KERN_CONT ".\n");
		kमुक्त(isa);
		वापस -EINVAL;
	पूर्ण

	वापस radio_isa_common_probe(isa, pdev, drv->radio_nr_params[dev],
					drv->region_size);
पूर्ण
EXPORT_SYMBOL_GPL(radio_isa_probe);

व्योम radio_isa_हटाओ(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा radio_isa_card *isa = dev_get_drvdata(pdev);

	radio_isa_common_हटाओ(isa, isa->drv->region_size);
पूर्ण
EXPORT_SYMBOL_GPL(radio_isa_हटाओ);

#अगर_घोषित CONFIG_PNP
पूर्णांक radio_isa_pnp_probe(काष्ठा pnp_dev *dev, स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	काष्ठा pnp_driver *pnp_drv = to_pnp_driver(dev->dev.driver);
	काष्ठा radio_isa_driver *drv = container_of(pnp_drv,
					काष्ठा radio_isa_driver, pnp_driver);
	काष्ठा radio_isa_card *isa;

	अगर (!pnp_port_valid(dev, 0))
		वापस -ENODEV;

	isa = radio_isa_alloc(drv, &dev->dev);
	अगर (!isa)
		वापस -ENOMEM;

	isa->io = pnp_port_start(dev, 0);

	वापस radio_isa_common_probe(isa, &dev->dev, drv->radio_nr_params[0],
					pnp_port_len(dev, 0));
पूर्ण
EXPORT_SYMBOL_GPL(radio_isa_pnp_probe);

व्योम radio_isa_pnp_हटाओ(काष्ठा pnp_dev *dev)
अणु
	काष्ठा radio_isa_card *isa = dev_get_drvdata(&dev->dev);

	radio_isa_common_हटाओ(isa, pnp_port_len(dev, 0));
पूर्ण
EXPORT_SYMBOL_GPL(radio_isa_pnp_हटाओ);
#पूर्ण_अगर
