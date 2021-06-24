<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Fieldbus Device Driver Core
 *
 */

#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>

/* move to <linux/fieldbus_dev.h> when taking this out of staging */
#समावेश "fieldbus_dev.h"

/* Maximum number of fieldbus devices */
#घोषणा MAX_FIELDBUSES		32

/* the dev_t काष्ठाure to store the dynamically allocated fieldbus devices */
अटल dev_t fieldbus_devt;
अटल DEFINE_IDA(fieldbus_ida);
अटल DEFINE_MUTEX(fieldbus_mtx);

अटल sमाप_प्रकार online_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा fieldbus_dev *fb = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", !!fb->online);
पूर्ण
अटल DEVICE_ATTR_RO(online);

अटल sमाप_प्रकार enabled_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा fieldbus_dev *fb = dev_get_drvdata(dev);

	अगर (!fb->enable_get)
		वापस -EINVAL;
	वापस प्र_लिखो(buf, "%d\n", !!fb->enable_get(fb));
पूर्ण

अटल sमाप_प्रकार enabled_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा fieldbus_dev *fb = dev_get_drvdata(dev);
	bool value;
	पूर्णांक ret;

	अगर (!fb->simple_enable_set)
		वापस -ENOTSUPP;
	ret = kstrtobool(buf, &value);
	अगर (ret)
		वापस ret;
	ret = fb->simple_enable_set(fb, value);
	अगर (ret < 0)
		वापस ret;
	वापस n;
पूर्ण
अटल DEVICE_ATTR_RW(enabled);

अटल sमाप_प्रकार card_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा fieldbus_dev *fb = dev_get_drvdata(dev);

	/*
	 * card_name was provided by child driver, could potentially be दीर्घ.
	 * protect against buffer overrun.
	 */
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", fb->card_name);
पूर्ण
अटल DEVICE_ATTR_RO(card_name);

अटल sमाप_प्रकार पढ़ो_area_size_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fieldbus_dev *fb = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%zu\n", fb->पढ़ो_area_sz);
पूर्ण
अटल DEVICE_ATTR_RO(पढ़ो_area_size);

अटल sमाप_प्रकार ग_लिखो_area_size_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fieldbus_dev *fb = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%zu\n", fb->ग_लिखो_area_sz);
पूर्ण
अटल DEVICE_ATTR_RO(ग_लिखो_area_size);

अटल sमाप_प्रकार fieldbus_id_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fieldbus_dev *fb = dev_get_drvdata(dev);

	वापस fb->fieldbus_id_get(fb, buf, PAGE_SIZE);
पूर्ण
अटल DEVICE_ATTR_RO(fieldbus_id);

अटल sमाप_प्रकार fieldbus_type_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fieldbus_dev *fb = dev_get_drvdata(dev);
	स्थिर अक्षर *t;

	चयन (fb->fieldbus_type) अणु
	हाल FIELDBUS_DEV_TYPE_PROFINET:
		t = "profinet";
		अवरोध;
	शेष:
		t = "unknown";
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", t);
पूर्ण
अटल DEVICE_ATTR_RO(fieldbus_type);

अटल काष्ठा attribute *fieldbus_attrs[] = अणु
	&dev_attr_enabled.attr,
	&dev_attr_card_name.attr,
	&dev_attr_fieldbus_id.attr,
	&dev_attr_पढ़ो_area_size.attr,
	&dev_attr_ग_लिखो_area_size.attr,
	&dev_attr_online.attr,
	&dev_attr_fieldbus_type.attr,
	शून्य,
पूर्ण;

अटल umode_t fieldbus_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				   पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा fieldbus_dev *fb = dev_get_drvdata(dev);
	umode_t mode = attr->mode;

	अगर (attr == &dev_attr_enabled.attr) अणु
		mode = 0;
		अगर (fb->enable_get)
			mode |= 0444;
		अगर (fb->simple_enable_set)
			mode |= 0200;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group fieldbus_group = अणु
	.attrs = fieldbus_attrs,
	.is_visible = fieldbus_is_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(fieldbus);

अटल काष्ठा class fieldbus_class = अणु
	.name =		"fieldbus_dev",
	.owner =	THIS_MODULE,
	.dev_groups =	fieldbus_groups,
पूर्ण;

काष्ठा fb_खोलो_file अणु
	काष्ठा fieldbus_dev *fbdev;
	पूर्णांक dc_event;
पूर्ण;

अटल पूर्णांक fieldbus_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा fb_खोलो_file *of;
	काष्ठा fieldbus_dev *fbdev = container_of(inode->i_cdev,
						काष्ठा fieldbus_dev,
						cdev);

	of = kzalloc(माप(*of), GFP_KERNEL);
	अगर (!of)
		वापस -ENOMEM;
	of->fbdev = fbdev;
	filp->निजी_data = of;
	वापस 0;
पूर्ण

अटल पूर्णांक fieldbus_release(काष्ठा inode *node, काष्ठा file *filp)
अणु
	काष्ठा fb_खोलो_file *of = filp->निजी_data;

	kमुक्त(of);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार fieldbus_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार size,
			     loff_t *offset)
अणु
	काष्ठा fb_खोलो_file *of = filp->निजी_data;
	काष्ठा fieldbus_dev *fbdev = of->fbdev;

	of->dc_event = fbdev->dc_event;
	वापस fbdev->पढ़ो_area(fbdev, buf, size, offset);
पूर्ण

अटल sमाप_प्रकार fieldbus_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			      माप_प्रकार size, loff_t *offset)
अणु
	काष्ठा fb_खोलो_file *of = filp->निजी_data;
	काष्ठा fieldbus_dev *fbdev = of->fbdev;

	वापस fbdev->ग_लिखो_area(fbdev, buf, size, offset);
पूर्ण

अटल __poll_t fieldbus_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा fb_खोलो_file *of = filp->निजी_data;
	काष्ठा fieldbus_dev *fbdev = of->fbdev;
	__poll_t mask = EPOLLIN | EPOLLRDNORM | EPOLLOUT | EPOLLWRNORM;

	poll_रुको(filp, &fbdev->dc_wq, रुको);
	/* data changed ? */
	अगर (fbdev->dc_event != of->dc_event)
		mask |= EPOLLPRI | EPOLLERR;
	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations fieldbus_fops = अणु
	.खोलो		= fieldbus_खोलो,
	.release	= fieldbus_release,
	.पढ़ो		= fieldbus_पढ़ो,
	.ग_लिखो		= fieldbus_ग_लिखो,
	.poll		= fieldbus_poll,
	.llseek		= generic_file_llseek,
	.owner		= THIS_MODULE,
पूर्ण;

व्योम fieldbus_dev_area_updated(काष्ठा fieldbus_dev *fb)
अणु
	fb->dc_event++;
	wake_up_all(&fb->dc_wq);
पूर्ण
EXPORT_SYMBOL_GPL(fieldbus_dev_area_updated);

व्योम fieldbus_dev_online_changed(काष्ठा fieldbus_dev *fb, bool online)
अणु
	fb->online = online;
	kobject_uevent(&fb->dev->kobj, KOBJ_CHANGE);
पूर्ण
EXPORT_SYMBOL_GPL(fieldbus_dev_online_changed);

अटल व्योम __fieldbus_dev_unरेजिस्टर(काष्ठा fieldbus_dev *fb)
अणु
	अगर (!fb)
		वापस;
	device_destroy(&fieldbus_class, fb->cdev.dev);
	cdev_del(&fb->cdev);
	ida_simple_हटाओ(&fieldbus_ida, fb->id);
पूर्ण

व्योम fieldbus_dev_unरेजिस्टर(काष्ठा fieldbus_dev *fb)
अणु
	mutex_lock(&fieldbus_mtx);
	__fieldbus_dev_unरेजिस्टर(fb);
	mutex_unlock(&fieldbus_mtx);
पूर्ण
EXPORT_SYMBOL_GPL(fieldbus_dev_unरेजिस्टर);

अटल पूर्णांक __fieldbus_dev_रेजिस्टर(काष्ठा fieldbus_dev *fb)
अणु
	dev_t devno;
	पूर्णांक err;

	अगर (!fb)
		वापस -EINVAL;
	अगर (!fb->पढ़ो_area || !fb->ग_लिखो_area || !fb->fieldbus_id_get)
		वापस -EINVAL;
	fb->id = ida_simple_get(&fieldbus_ida, 0, MAX_FIELDBUSES, GFP_KERNEL);
	अगर (fb->id < 0)
		वापस fb->id;
	devno = MKDEV(MAJOR(fieldbus_devt), fb->id);
	init_रुकोqueue_head(&fb->dc_wq);
	cdev_init(&fb->cdev, &fieldbus_fops);
	err = cdev_add(&fb->cdev, devno, 1);
	अगर (err) अणु
		pr_err("fieldbus_dev%d unable to add device %d:%d\n",
		       fb->id, MAJOR(fieldbus_devt), fb->id);
		जाओ err_cdev;
	पूर्ण
	fb->dev = device_create(&fieldbus_class, fb->parent, devno, fb,
				"fieldbus_dev%d", fb->id);
	अगर (IS_ERR(fb->dev)) अणु
		err = PTR_ERR(fb->dev);
		जाओ err_dev_create;
	पूर्ण
	वापस 0;

err_dev_create:
	cdev_del(&fb->cdev);
err_cdev:
	ida_simple_हटाओ(&fieldbus_ida, fb->id);
	वापस err;
पूर्ण

पूर्णांक fieldbus_dev_रेजिस्टर(काष्ठा fieldbus_dev *fb)
अणु
	पूर्णांक err;

	mutex_lock(&fieldbus_mtx);
	err = __fieldbus_dev_रेजिस्टर(fb);
	mutex_unlock(&fieldbus_mtx);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fieldbus_dev_रेजिस्टर);

अटल पूर्णांक __init fieldbus_init(व्योम)
अणु
	पूर्णांक err;

	err = class_रेजिस्टर(&fieldbus_class);
	अगर (err < 0) अणु
		pr_err("fieldbus_dev: could not register class\n");
		वापस err;
	पूर्ण
	err = alloc_chrdev_region(&fieldbus_devt, 0,
				  MAX_FIELDBUSES, "fieldbus_dev");
	अगर (err < 0) अणु
		pr_err("fieldbus_dev: unable to allocate char dev region\n");
		जाओ err_alloc;
	पूर्ण
	वापस 0;

err_alloc:
	class_unरेजिस्टर(&fieldbus_class);
	वापस err;
पूर्ण

अटल व्योम __निकास fieldbus_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev_region(fieldbus_devt, MAX_FIELDBUSES);
	class_unरेजिस्टर(&fieldbus_class);
	ida_destroy(&fieldbus_ida);
पूर्ण

subsys_initcall(fieldbus_init);
module_निकास(fieldbus_निकास);

MODULE_AUTHOR("Sven Van Asbroeck <TheSven73@gmail.com>");
MODULE_AUTHOR("Jonathan Stiles <jonathans@arcx.com>");
MODULE_DESCRIPTION("Fieldbus Device Driver Core");
MODULE_LICENSE("GPL v2");
