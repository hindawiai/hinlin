<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Userspace driver क्रम the LED subप्रणाली
 *
 * Copyright (C) 2016 David Lechner <david@lechnology.com>
 *
 * Based on uinput.c: Aristeu Sergio Rozanski Filho <aris@cathedralद_असल.org>
 */
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <uapi/linux/uleds.h>

#घोषणा ULEDS_NAME	"uleds"

क्रमागत uleds_state अणु
	ULEDS_STATE_UNKNOWN,
	ULEDS_STATE_REGISTERED,
पूर्ण;

काष्ठा uleds_device अणु
	काष्ठा uleds_user_dev	user_dev;
	काष्ठा led_classdev	led_cdev;
	काष्ठा mutex		mutex;
	क्रमागत uleds_state	state;
	रुको_queue_head_t	रुकोq;
	पूर्णांक			brightness;
	bool			new_data;
पूर्ण;

अटल काष्ठा miscdevice uleds_misc;

अटल व्योम uleds_brightness_set(काष्ठा led_classdev *led_cdev,
				 क्रमागत led_brightness brightness)
अणु
	काष्ठा uleds_device *udev = container_of(led_cdev, काष्ठा uleds_device,
						 led_cdev);

	अगर (udev->brightness != brightness) अणु
		udev->brightness = brightness;
		udev->new_data = true;
		wake_up_पूर्णांकerruptible(&udev->रुकोq);
	पूर्ण
पूर्ण

अटल पूर्णांक uleds_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा uleds_device *udev;

	udev = kzalloc(माप(*udev), GFP_KERNEL);
	अगर (!udev)
		वापस -ENOMEM;

	udev->led_cdev.name = udev->user_dev.name;
	udev->led_cdev.brightness_set = uleds_brightness_set;

	mutex_init(&udev->mutex);
	init_रुकोqueue_head(&udev->रुकोq);
	udev->state = ULEDS_STATE_UNKNOWN;

	file->निजी_data = udev;
	stream_खोलो(inode, file);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार uleds_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा uleds_device *udev = file->निजी_data;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	अगर (count == 0)
		वापस 0;

	ret = mutex_lock_पूर्णांकerruptible(&udev->mutex);
	अगर (ret)
		वापस ret;

	अगर (udev->state == ULEDS_STATE_REGISTERED) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (count != माप(काष्ठा uleds_user_dev)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (copy_from_user(&udev->user_dev, buffer,
			   माप(काष्ठा uleds_user_dev))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	name = udev->user_dev.name;
	अगर (!name[0] || !म_भेद(name, ".") || !म_भेद(name, "..") ||
	    म_अक्षर(name, '/')) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (udev->user_dev.max_brightness <= 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	udev->led_cdev.max_brightness = udev->user_dev.max_brightness;

	ret = devm_led_classdev_रेजिस्टर(uleds_misc.this_device,
					 &udev->led_cdev);
	अगर (ret < 0)
		जाओ out;

	udev->new_data = true;
	udev->state = ULEDS_STATE_REGISTERED;
	ret = count;

out:
	mutex_unlock(&udev->mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार uleds_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count,
			  loff_t *ppos)
अणु
	काष्ठा uleds_device *udev = file->निजी_data;
	sमाप_प्रकार retval;

	अगर (count < माप(udev->brightness))
		वापस 0;

	करो अणु
		retval = mutex_lock_पूर्णांकerruptible(&udev->mutex);
		अगर (retval)
			वापस retval;

		अगर (udev->state != ULEDS_STATE_REGISTERED) अणु
			retval = -ENODEV;
		पूर्ण अन्यथा अगर (!udev->new_data && (file->f_flags & O_NONBLOCK)) अणु
			retval = -EAGAIN;
		पूर्ण अन्यथा अगर (udev->new_data) अणु
			retval = copy_to_user(buffer, &udev->brightness,
					      माप(udev->brightness));
			udev->new_data = false;
			retval = माप(udev->brightness);
		पूर्ण

		mutex_unlock(&udev->mutex);

		अगर (retval)
			अवरोध;

		अगर (!(file->f_flags & O_NONBLOCK))
			retval = रुको_event_पूर्णांकerruptible(udev->रुकोq,
					udev->new_data ||
					udev->state != ULEDS_STATE_REGISTERED);
	पूर्ण जबतक (retval == 0);

	वापस retval;
पूर्ण

अटल __poll_t uleds_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा uleds_device *udev = file->निजी_data;

	poll_रुको(file, &udev->रुकोq, रुको);

	अगर (udev->new_data)
		वापस EPOLLIN | EPOLLRDNORM;

	वापस 0;
पूर्ण

अटल पूर्णांक uleds_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा uleds_device *udev = file->निजी_data;

	अगर (udev->state == ULEDS_STATE_REGISTERED) अणु
		udev->state = ULEDS_STATE_UNKNOWN;
		devm_led_classdev_unरेजिस्टर(uleds_misc.this_device,
					     &udev->led_cdev);
	पूर्ण
	kमुक्त(udev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations uleds_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= uleds_खोलो,
	.release	= uleds_release,
	.पढ़ो		= uleds_पढ़ो,
	.ग_लिखो		= uleds_ग_लिखो,
	.poll		= uleds_poll,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice uleds_misc = अणु
	.fops		= &uleds_fops,
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= ULEDS_NAME,
पूर्ण;

अटल पूर्णांक __init uleds_init(व्योम)
अणु
	वापस misc_रेजिस्टर(&uleds_misc);
पूर्ण
module_init(uleds_init);

अटल व्योम __निकास uleds_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&uleds_misc);
पूर्ण
module_निकास(uleds_निकास);

MODULE_AUTHOR("David Lechner <david@lechnology.com>");
MODULE_DESCRIPTION("Userspace driver for the LED subsystem");
MODULE_LICENSE("GPL");
