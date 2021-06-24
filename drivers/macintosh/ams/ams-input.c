<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Apple Motion Sensor driver (joystick emulation)
 *
 * Copyright (C) 2005 Stelian Pop (stelian@popies.net)
 * Copyright (C) 2006 Michael Hanselmann (linux-kernel@hansmi.ch)
 */

#समावेश <linux/module.h>

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश "ams.h"

अटल bool joystick;
module_param(joystick, bool, S_IRUGO);
MODULE_PARM_DESC(joystick, "Enable the input class device on module load");

अटल bool invert;
module_param(invert, bool, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(invert, "Invert input data on X and Y axis");

अटल DEFINE_MUTEX(ams_input_mutex);

अटल व्योम ams_idev_poll(काष्ठा input_dev *idev)
अणु
	s8 x, y, z;

	mutex_lock(&ams_info.lock);

	ams_sensors(&x, &y, &z);

	x -= ams_info.xcalib;
	y -= ams_info.ycalib;
	z -= ams_info.zcalib;

	input_report_असल(idev, ABS_X, invert ? -x : x);
	input_report_असल(idev, ABS_Y, invert ? -y : y);
	input_report_असल(idev, ABS_Z, z);

	input_sync(idev);

	mutex_unlock(&ams_info.lock);
पूर्ण

/* Call with ams_info.lock held! */
अटल पूर्णांक ams_input_enable(व्योम)
अणु
	काष्ठा input_dev *input;
	s8 x, y, z;
	पूर्णांक error;

	ams_sensors(&x, &y, &z);
	ams_info.xcalib = x;
	ams_info.ycalib = y;
	ams_info.zcalib = z;

	input = input_allocate_device();
	अगर (!input)
		वापस -ENOMEM;

	input->name = "Apple Motion Sensor";
	input->id.bustype = ams_info.bustype;
	input->id.venकरोr = 0;
	input->dev.parent = &ams_info.of_dev->dev;

	input_set_असल_params(input, ABS_X, -50, 50, 3, 0);
	input_set_असल_params(input, ABS_Y, -50, 50, 3, 0);
	input_set_असल_params(input, ABS_Z, -50, 50, 3, 0);
	input_set_capability(input, EV_KEY, BTN_TOUCH);

	error = input_setup_polling(input, ams_idev_poll);
	अगर (error)
		जाओ err_मुक्त_input;

	input_set_poll_पूर्णांकerval(input, 25);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		जाओ err_मुक्त_input;

	ams_info.idev = input;
	joystick = true;

	वापस 0;

err_मुक्त_input:
	input_मुक्त_device(input);
	वापस error;
पूर्ण

अटल व्योम ams_input_disable(व्योम)
अणु
	अगर (ams_info.idev) अणु
		input_unरेजिस्टर_device(ams_info.idev);
		ams_info.idev = शून्य;
	पूर्ण

	joystick = false;
पूर्ण

अटल sमाप_प्रकार ams_input_show_joystick(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", joystick);
पूर्ण

अटल sमाप_प्रकार ams_input_store_joystick(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ enable;
	पूर्णांक error = 0;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &enable);
	अगर (ret)
		वापस ret;
	अगर (enable > 1)
		वापस -EINVAL;

	mutex_lock(&ams_input_mutex);

	अगर (enable != joystick) अणु
		अगर (enable)
			error = ams_input_enable();
		अन्यथा
			ams_input_disable();
	पूर्ण

	mutex_unlock(&ams_input_mutex);

	वापस error ? error : count;
पूर्ण

अटल DEVICE_ATTR(joystick, S_IRUGO | S_IWUSR,
	ams_input_show_joystick, ams_input_store_joystick);

पूर्णांक ams_input_init(व्योम)
अणु
	अगर (joystick)
		ams_input_enable();

	वापस device_create_file(&ams_info.of_dev->dev, &dev_attr_joystick);
पूर्ण

व्योम ams_input_निकास(व्योम)
अणु
	device_हटाओ_file(&ams_info.of_dev->dev, &dev_attr_joystick);

	mutex_lock(&ams_input_mutex);
	ams_input_disable();
	mutex_unlock(&ams_input_mutex);
पूर्ण
