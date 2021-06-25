<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Vibrator protocol driver.
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/idr.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/greybus.h>

काष्ठा gb_vibrator_device अणु
	काष्ठा gb_connection	*connection;
	काष्ठा device		*dev;
	पूर्णांक			minor;		/* vibrator minor number */
	काष्ठा delayed_work     delayed_work;
पूर्ण;

/* Greybus Vibrator operation types */
#घोषणा	GB_VIBRATOR_TYPE_ON			0x02
#घोषणा	GB_VIBRATOR_TYPE_OFF			0x03

अटल पूर्णांक turn_off(काष्ठा gb_vibrator_device *vib)
अणु
	काष्ठा gb_bundle *bundle = vib->connection->bundle;
	पूर्णांक ret;

	ret = gb_operation_sync(vib->connection, GB_VIBRATOR_TYPE_OFF,
				शून्य, 0, शून्य, 0);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक turn_on(काष्ठा gb_vibrator_device *vib, u16 समयout_ms)
अणु
	काष्ठा gb_bundle *bundle = vib->connection->bundle;
	पूर्णांक ret;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	/* Vibrator was चयनed ON earlier */
	अगर (cancel_delayed_work_sync(&vib->delayed_work))
		turn_off(vib);

	ret = gb_operation_sync(vib->connection, GB_VIBRATOR_TYPE_ON,
				शून्य, 0, शून्य, 0);
	अगर (ret) अणु
		gb_pm_runसमय_put_स्वतःsuspend(bundle);
		वापस ret;
	पूर्ण

	schedule_delayed_work(&vib->delayed_work, msecs_to_jअगरfies(समयout_ms));

	वापस 0;
पूर्ण

अटल व्योम gb_vibrator_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा gb_vibrator_device *vib =
		container_of(delayed_work,
			     काष्ठा gb_vibrator_device,
			     delayed_work);

	turn_off(vib);
पूर्ण

अटल sमाप_प्रकार समयout_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gb_vibrator_device *vib = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक retval;

	retval = kम_से_अदीर्घ(buf, 10, &val);
	अगर (retval < 0) अणु
		dev_err(dev, "could not parse timeout value %d\n", retval);
		वापस retval;
	पूर्ण

	अगर (val)
		retval = turn_on(vib, (u16)val);
	अन्यथा
		retval = turn_off(vib);
	अगर (retval)
		वापस retval;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(समयout);

अटल काष्ठा attribute *vibrator_attrs[] = अणु
	&dev_attr_समयout.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(vibrator);

अटल काष्ठा class vibrator_class = अणु
	.name		= "vibrator",
	.owner		= THIS_MODULE,
	.dev_groups	= vibrator_groups,
पूर्ण;

अटल DEFINE_IDA(minors);

अटल पूर्णांक gb_vibrator_probe(काष्ठा gb_bundle *bundle,
			     स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_connection *connection;
	काष्ठा gb_vibrator_device *vib;
	काष्ठा device *dev;
	पूर्णांक retval;

	अगर (bundle->num_cports != 1)
		वापस -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	अगर (cport_desc->protocol_id != GREYBUS_PROTOCOL_VIBRATOR)
		वापस -ENODEV;

	vib = kzalloc(माप(*vib), GFP_KERNEL);
	अगर (!vib)
		वापस -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  शून्य);
	अगर (IS_ERR(connection)) अणु
		retval = PTR_ERR(connection);
		जाओ err_मुक्त_vib;
	पूर्ण
	gb_connection_set_data(connection, vib);

	vib->connection = connection;

	greybus_set_drvdata(bundle, vib);

	retval = gb_connection_enable(connection);
	अगर (retval)
		जाओ err_connection_destroy;

	/*
	 * For now we create a device in sysfs क्रम the vibrator, but odds are
	 * there is a "real" device somewhere in the kernel क्रम this, but I
	 * can't find it at the moment...
	 */
	vib->minor = ida_simple_get(&minors, 0, 0, GFP_KERNEL);
	अगर (vib->minor < 0) अणु
		retval = vib->minor;
		जाओ err_connection_disable;
	पूर्ण
	dev = device_create(&vibrator_class, &bundle->dev,
			    MKDEV(0, 0), vib, "vibrator%d", vib->minor);
	अगर (IS_ERR(dev)) अणु
		retval = -EINVAL;
		जाओ err_ida_हटाओ;
	पूर्ण
	vib->dev = dev;

	INIT_DELAYED_WORK(&vib->delayed_work, gb_vibrator_worker);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस 0;

err_ida_हटाओ:
	ida_simple_हटाओ(&minors, vib->minor);
err_connection_disable:
	gb_connection_disable(connection);
err_connection_destroy:
	gb_connection_destroy(connection);
err_मुक्त_vib:
	kमुक्त(vib);

	वापस retval;
पूर्ण

अटल व्योम gb_vibrator_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_vibrator_device *vib = greybus_get_drvdata(bundle);
	पूर्णांक ret;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		gb_pm_runसमय_get_noresume(bundle);

	अगर (cancel_delayed_work_sync(&vib->delayed_work))
		turn_off(vib);

	device_unरेजिस्टर(vib->dev);
	ida_simple_हटाओ(&minors, vib->minor);
	gb_connection_disable(vib->connection);
	gb_connection_destroy(vib->connection);
	kमुक्त(vib);
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_vibrator_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_VIBRATOR) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(greybus, gb_vibrator_id_table);

अटल काष्ठा greybus_driver gb_vibrator_driver = अणु
	.name		= "vibrator",
	.probe		= gb_vibrator_probe,
	.disconnect	= gb_vibrator_disconnect,
	.id_table	= gb_vibrator_id_table,
पूर्ण;

अटल __init पूर्णांक gb_vibrator_init(व्योम)
अणु
	पूर्णांक retval;

	retval = class_रेजिस्टर(&vibrator_class);
	अगर (retval)
		वापस retval;

	retval = greybus_रेजिस्टर(&gb_vibrator_driver);
	अगर (retval)
		जाओ err_class_unरेजिस्टर;

	वापस 0;

err_class_unरेजिस्टर:
	class_unरेजिस्टर(&vibrator_class);

	वापस retval;
पूर्ण
module_init(gb_vibrator_init);

अटल __निकास व्योम gb_vibrator_निकास(व्योम)
अणु
	greybus_deरेजिस्टर(&gb_vibrator_driver);
	class_unरेजिस्टर(&vibrator_class);
	ida_destroy(&minors);
पूर्ण
module_निकास(gb_vibrator_निकास);

MODULE_LICENSE("GPL v2");
