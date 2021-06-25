<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    V4L2 device support.

    Copyright (C) 2008  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

पूर्णांक v4l2_device_रेजिस्टर(काष्ठा device *dev, काष्ठा v4l2_device *v4l2_dev)
अणु
	अगर (v4l2_dev == शून्य)
		वापस -EINVAL;

	INIT_LIST_HEAD(&v4l2_dev->subdevs);
	spin_lock_init(&v4l2_dev->lock);
	v4l2_prio_init(&v4l2_dev->prio);
	kref_init(&v4l2_dev->ref);
	get_device(dev);
	v4l2_dev->dev = dev;
	अगर (dev == शून्य) अणु
		/* If dev == शून्य, then name must be filled in by the caller */
		अगर (WARN_ON(!v4l2_dev->name[0]))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	/* Set name to driver name + device name अगर it is empty. */
	अगर (!v4l2_dev->name[0])
		snम_लिखो(v4l2_dev->name, माप(v4l2_dev->name), "%s %s",
			dev->driver->name, dev_name(dev));
	अगर (!dev_get_drvdata(dev))
		dev_set_drvdata(dev, v4l2_dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_device_रेजिस्टर);

अटल व्योम v4l2_device_release(काष्ठा kref *ref)
अणु
	काष्ठा v4l2_device *v4l2_dev =
		container_of(ref, काष्ठा v4l2_device, ref);

	अगर (v4l2_dev->release)
		v4l2_dev->release(v4l2_dev);
पूर्ण

पूर्णांक v4l2_device_put(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस kref_put(&v4l2_dev->ref, v4l2_device_release);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_device_put);

पूर्णांक v4l2_device_set_name(काष्ठा v4l2_device *v4l2_dev, स्थिर अक्षर *basename,
						atomic_t *instance)
अणु
	पूर्णांक num = atomic_inc_वापस(instance) - 1;
	पूर्णांक len = म_माप(basename);

	अगर (basename[len - 1] >= '0' && basename[len - 1] <= '9')
		snम_लिखो(v4l2_dev->name, माप(v4l2_dev->name),
				"%s-%d", basename, num);
	अन्यथा
		snम_लिखो(v4l2_dev->name, माप(v4l2_dev->name),
				"%s%d", basename, num);
	वापस num;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_device_set_name);

व्योम v4l2_device_disconnect(काष्ठा v4l2_device *v4l2_dev)
अणु
	अगर (v4l2_dev->dev == शून्य)
		वापस;

	अगर (dev_get_drvdata(v4l2_dev->dev) == v4l2_dev)
		dev_set_drvdata(v4l2_dev->dev, शून्य);
	put_device(v4l2_dev->dev);
	v4l2_dev->dev = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_device_disconnect);

व्योम v4l2_device_unरेजिस्टर(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा v4l2_subdev *sd, *next;

	/* Just वापस अगर v4l2_dev is शून्य or अगर it was alपढ़ोy
	 * unरेजिस्टरed beक्रमe. */
	अगर (v4l2_dev == शून्य || !v4l2_dev->name[0])
		वापस;
	v4l2_device_disconnect(v4l2_dev);

	/* Unरेजिस्टर subdevs */
	list_क्रम_each_entry_safe(sd, next, &v4l2_dev->subdevs, list) अणु
		v4l2_device_unरेजिस्टर_subdev(sd);
		अगर (sd->flags & V4L2_SUBDEV_FL_IS_I2C)
			v4l2_i2c_subdev_unरेजिस्टर(sd);
		अन्यथा अगर (sd->flags & V4L2_SUBDEV_FL_IS_SPI)
			v4l2_spi_subdev_unरेजिस्टर(sd);
	पूर्ण
	/* Mark as unरेजिस्टरed, thus preventing duplicate unregistrations */
	v4l2_dev->name[0] = '\0';
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_device_unरेजिस्टर);

पूर्णांक v4l2_device_रेजिस्टर_subdev(काष्ठा v4l2_device *v4l2_dev,
				काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक err;

	/* Check क्रम valid input */
	अगर (!v4l2_dev || !sd || sd->v4l2_dev || !sd->name[0])
		वापस -EINVAL;

	/*
	 * The reason to acquire the module here is to aव्योम unloading
	 * a module of sub-device which is रेजिस्टरed to a media
	 * device. To make it possible to unload modules क्रम media
	 * devices that also रेजिस्टर sub-devices, करो not
	 * try_module_get() such sub-device owners.
	 */
	sd->owner_v4l2_dev = v4l2_dev->dev && v4l2_dev->dev->driver &&
		sd->owner == v4l2_dev->dev->driver->owner;

	अगर (!sd->owner_v4l2_dev && !try_module_get(sd->owner))
		वापस -ENODEV;

	sd->v4l2_dev = v4l2_dev;
	/* This just वापसs 0 अगर either of the two args is शून्य */
	err = v4l2_ctrl_add_handler(v4l2_dev->ctrl_handler, sd->ctrl_handler,
				    शून्य, true);
	अगर (err)
		जाओ error_module;

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	/* Register the entity. */
	अगर (v4l2_dev->mdev) अणु
		err = media_device_रेजिस्टर_entity(v4l2_dev->mdev, &sd->entity);
		अगर (err < 0)
			जाओ error_module;
	पूर्ण
#पूर्ण_अगर

	अगर (sd->पूर्णांकernal_ops && sd->पूर्णांकernal_ops->रेजिस्टरed) अणु
		err = sd->पूर्णांकernal_ops->रेजिस्टरed(sd);
		अगर (err)
			जाओ error_unरेजिस्टर;
	पूर्ण

	spin_lock(&v4l2_dev->lock);
	list_add_tail(&sd->list, &v4l2_dev->subdevs);
	spin_unlock(&v4l2_dev->lock);

	वापस 0;

error_unरेजिस्टर:
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	media_device_unरेजिस्टर_entity(&sd->entity);
#पूर्ण_अगर
error_module:
	अगर (!sd->owner_v4l2_dev)
		module_put(sd->owner);
	sd->v4l2_dev = शून्य;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_device_रेजिस्टर_subdev);

अटल व्योम v4l2_subdev_release(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा module *owner = !sd->owner_v4l2_dev ? sd->owner : शून्य;

	अगर (sd->पूर्णांकernal_ops && sd->पूर्णांकernal_ops->release)
		sd->पूर्णांकernal_ops->release(sd);
	sd->devnode = शून्य;
	module_put(owner);
पूर्ण

अटल व्योम v4l2_device_release_subdev_node(काष्ठा video_device *vdev)
अणु
	v4l2_subdev_release(video_get_drvdata(vdev));
	kमुक्त(vdev);
पूर्ण

पूर्णांक __v4l2_device_रेजिस्टर_subdev_nodes(काष्ठा v4l2_device *v4l2_dev,
					bool पढ़ो_only)
अणु
	काष्ठा video_device *vdev;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक err;

	/* Register a device node क्रम every subdev marked with the
	 * V4L2_SUBDEV_FL_HAS_DEVNODE flag.
	 */
	list_क्रम_each_entry(sd, &v4l2_dev->subdevs, list) अणु
		अगर (!(sd->flags & V4L2_SUBDEV_FL_HAS_DEVNODE))
			जारी;

		अगर (sd->devnode)
			जारी;

		vdev = kzalloc(माप(*vdev), GFP_KERNEL);
		अगर (!vdev) अणु
			err = -ENOMEM;
			जाओ clean_up;
		पूर्ण

		video_set_drvdata(vdev, sd);
		strscpy(vdev->name, sd->name, माप(vdev->name));
		vdev->dev_parent = sd->dev;
		vdev->v4l2_dev = v4l2_dev;
		vdev->fops = &v4l2_subdev_fops;
		vdev->release = v4l2_device_release_subdev_node;
		vdev->ctrl_handler = sd->ctrl_handler;
		अगर (पढ़ो_only)
			set_bit(V4L2_FL_SUBDEV_RO_DEVNODE, &vdev->flags);
		sd->devnode = vdev;
		err = __video_रेजिस्टर_device(vdev, VFL_TYPE_SUBDEV, -1, 1,
					      sd->owner);
		अगर (err < 0) अणु
			sd->devnode = शून्य;
			kमुक्त(vdev);
			जाओ clean_up;
		पूर्ण
#अगर defined(CONFIG_MEDIA_CONTROLLER)
		sd->entity.info.dev.major = VIDEO_MAJOR;
		sd->entity.info.dev.minor = vdev->minor;

		/* Interface is created by __video_रेजिस्टर_device() */
		अगर (vdev->v4l2_dev->mdev) अणु
			काष्ठा media_link *link;

			link = media_create_पूर्णांकf_link(&sd->entity,
						      &vdev->पूर्णांकf_devnode->पूर्णांकf,
						      MEDIA_LNK_FL_ENABLED |
						      MEDIA_LNK_FL_IMMUTABLE);
			अगर (!link) अणु
				err = -ENOMEM;
				जाओ clean_up;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस 0;

clean_up:
	list_क्रम_each_entry(sd, &v4l2_dev->subdevs, list) अणु
		अगर (!sd->devnode)
			अवरोध;
		video_unरेजिस्टर_device(sd->devnode);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__v4l2_device_रेजिस्टर_subdev_nodes);

व्योम v4l2_device_unरेजिस्टर_subdev(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा v4l2_device *v4l2_dev;

	/* वापस अगर it isn't रेजिस्टरed */
	अगर (sd == शून्य || sd->v4l2_dev == शून्य)
		वापस;

	v4l2_dev = sd->v4l2_dev;

	spin_lock(&v4l2_dev->lock);
	list_del(&sd->list);
	spin_unlock(&v4l2_dev->lock);

	अगर (sd->पूर्णांकernal_ops && sd->पूर्णांकernal_ops->unरेजिस्टरed)
		sd->पूर्णांकernal_ops->unरेजिस्टरed(sd);
	sd->v4l2_dev = शून्य;

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	अगर (v4l2_dev->mdev) अणु
		/*
		 * No need to explicitly हटाओ links, as both pads and
		 * links are हटाओd by the function below, in the right order
		 */
		media_device_unरेजिस्टर_entity(&sd->entity);
	पूर्ण
#पूर्ण_अगर
	अगर (sd->devnode)
		video_unरेजिस्टर_device(sd->devnode);
	अन्यथा
		v4l2_subdev_release(sd);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_device_unरेजिस्टर_subdev);
