<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LCD Lowlevel Control Abstraction
 *
 * Copyright (C) 2003,2004 Hewlett-Packard Company
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/lcd.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/slab.h>

#अगर defined(CONFIG_FB) || (defined(CONFIG_FB_MODULE) && \
			   defined(CONFIG_LCD_CLASS_DEVICE_MODULE))
/* This callback माला_लो called when something important happens inside a
 * framebuffer driver. We're looking अगर that important event is blanking,
 * and अगर it is, we're चयनing lcd घातer as well ...
 */
अटल पूर्णांक fb_notअगरier_callback(काष्ठा notअगरier_block *self,
				 अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा lcd_device *ld;
	काष्ठा fb_event *evdata = data;

	ld = container_of(self, काष्ठा lcd_device, fb_notअगर);
	अगर (!ld->ops)
		वापस 0;

	mutex_lock(&ld->ops_lock);
	अगर (!ld->ops->check_fb || ld->ops->check_fb(ld, evdata->info)) अणु
		अगर (event == FB_EVENT_BLANK) अणु
			अगर (ld->ops->set_घातer)
				ld->ops->set_घातer(ld, *(पूर्णांक *)evdata->data);
		पूर्ण अन्यथा अणु
			अगर (ld->ops->set_mode)
				ld->ops->set_mode(ld, evdata->data);
		पूर्ण
	पूर्ण
	mutex_unlock(&ld->ops_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक lcd_रेजिस्टर_fb(काष्ठा lcd_device *ld)
अणु
	स_रखो(&ld->fb_notअगर, 0, माप(ld->fb_notअगर));
	ld->fb_notअगर.notअगरier_call = fb_notअगरier_callback;
	वापस fb_रेजिस्टर_client(&ld->fb_notअगर);
पूर्ण

अटल व्योम lcd_unरेजिस्टर_fb(काष्ठा lcd_device *ld)
अणु
	fb_unरेजिस्टर_client(&ld->fb_notअगर);
पूर्ण
#अन्यथा
अटल पूर्णांक lcd_रेजिस्टर_fb(काष्ठा lcd_device *ld)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम lcd_unरेजिस्टर_fb(काष्ठा lcd_device *ld)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_FB */

अटल sमाप_प्रकार lcd_घातer_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	पूर्णांक rc;
	काष्ठा lcd_device *ld = to_lcd_device(dev);

	mutex_lock(&ld->ops_lock);
	अगर (ld->ops && ld->ops->get_घातer)
		rc = प्र_लिखो(buf, "%d\n", ld->ops->get_घातer(ld));
	अन्यथा
		rc = -ENXIO;
	mutex_unlock(&ld->ops_lock);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार lcd_घातer_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	काष्ठा lcd_device *ld = to_lcd_device(dev);
	अचिन्हित दीर्घ घातer;

	rc = kम_से_अदीर्घ(buf, 0, &घातer);
	अगर (rc)
		वापस rc;

	rc = -ENXIO;

	mutex_lock(&ld->ops_lock);
	अगर (ld->ops && ld->ops->set_घातer) अणु
		pr_debug("set power to %lu\n", घातer);
		ld->ops->set_घातer(ld, घातer);
		rc = count;
	पूर्ण
	mutex_unlock(&ld->ops_lock);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(lcd_घातer);

अटल sमाप_प्रकार contrast_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc = -ENXIO;
	काष्ठा lcd_device *ld = to_lcd_device(dev);

	mutex_lock(&ld->ops_lock);
	अगर (ld->ops && ld->ops->get_contrast)
		rc = प्र_लिखो(buf, "%d\n", ld->ops->get_contrast(ld));
	mutex_unlock(&ld->ops_lock);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार contrast_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	काष्ठा lcd_device *ld = to_lcd_device(dev);
	अचिन्हित दीर्घ contrast;

	rc = kम_से_अदीर्घ(buf, 0, &contrast);
	अगर (rc)
		वापस rc;

	rc = -ENXIO;

	mutex_lock(&ld->ops_lock);
	अगर (ld->ops && ld->ops->set_contrast) अणु
		pr_debug("set contrast to %lu\n", contrast);
		ld->ops->set_contrast(ld, contrast);
		rc = count;
	पूर्ण
	mutex_unlock(&ld->ops_lock);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(contrast);

अटल sमाप_प्रकार max_contrast_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lcd_device *ld = to_lcd_device(dev);

	वापस प्र_लिखो(buf, "%d\n", ld->props.max_contrast);
पूर्ण
अटल DEVICE_ATTR_RO(max_contrast);

अटल काष्ठा class *lcd_class;

अटल व्योम lcd_device_release(काष्ठा device *dev)
अणु
	काष्ठा lcd_device *ld = to_lcd_device(dev);
	kमुक्त(ld);
पूर्ण

अटल काष्ठा attribute *lcd_device_attrs[] = अणु
	&dev_attr_lcd_घातer.attr,
	&dev_attr_contrast.attr,
	&dev_attr_max_contrast.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(lcd_device);

/**
 * lcd_device_रेजिस्टर - रेजिस्टर a new object of lcd_device class.
 * @name: the name of the new object(must be the same as the name of the
 *   respective framebuffer device).
 * @parent: poपूर्णांकer to the parent's काष्ठा device .
 * @devdata: an optional poपूर्णांकer to be stored in the device. The
 *   methods may retrieve it by using lcd_get_data(ld).
 * @ops: the lcd operations काष्ठाure.
 *
 * Creates and रेजिस्टरs a new lcd device. Returns either an ERR_PTR()
 * or a poपूर्णांकer to the newly allocated device.
 */
काष्ठा lcd_device *lcd_device_रेजिस्टर(स्थिर अक्षर *name, काष्ठा device *parent,
		व्योम *devdata, काष्ठा lcd_ops *ops)
अणु
	काष्ठा lcd_device *new_ld;
	पूर्णांक rc;

	pr_debug("lcd_device_register: name=%s\n", name);

	new_ld = kzalloc(माप(काष्ठा lcd_device), GFP_KERNEL);
	अगर (!new_ld)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&new_ld->ops_lock);
	mutex_init(&new_ld->update_lock);

	new_ld->dev.class = lcd_class;
	new_ld->dev.parent = parent;
	new_ld->dev.release = lcd_device_release;
	dev_set_name(&new_ld->dev, "%s", name);
	dev_set_drvdata(&new_ld->dev, devdata);

	new_ld->ops = ops;

	rc = device_रेजिस्टर(&new_ld->dev);
	अगर (rc) अणु
		put_device(&new_ld->dev);
		वापस ERR_PTR(rc);
	पूर्ण

	rc = lcd_रेजिस्टर_fb(new_ld);
	अगर (rc) अणु
		device_unरेजिस्टर(&new_ld->dev);
		वापस ERR_PTR(rc);
	पूर्ण

	वापस new_ld;
पूर्ण
EXPORT_SYMBOL(lcd_device_रेजिस्टर);

/**
 * lcd_device_unरेजिस्टर - unरेजिस्टरs a object of lcd_device class.
 * @ld: the lcd device object to be unरेजिस्टरed and मुक्तd.
 *
 * Unरेजिस्टरs a previously रेजिस्टरed via lcd_device_रेजिस्टर object.
 */
व्योम lcd_device_unरेजिस्टर(काष्ठा lcd_device *ld)
अणु
	अगर (!ld)
		वापस;

	mutex_lock(&ld->ops_lock);
	ld->ops = शून्य;
	mutex_unlock(&ld->ops_lock);
	lcd_unरेजिस्टर_fb(ld);

	device_unरेजिस्टर(&ld->dev);
पूर्ण
EXPORT_SYMBOL(lcd_device_unरेजिस्टर);

अटल व्योम devm_lcd_device_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा lcd_device *lcd = *(काष्ठा lcd_device **)res;

	lcd_device_unरेजिस्टर(lcd);
पूर्ण

अटल पूर्णांक devm_lcd_device_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा lcd_device **r = res;

	वापस *r == data;
पूर्ण

/**
 * devm_lcd_device_रेजिस्टर - resource managed lcd_device_रेजिस्टर()
 * @dev: the device to रेजिस्टर
 * @name: the name of the device
 * @parent: a poपूर्णांकer to the parent device
 * @devdata: an optional poपूर्णांकer to be stored क्रम निजी driver use
 * @ops: the lcd operations काष्ठाure
 *
 * @वापस a काष्ठा lcd on success, or an ERR_PTR on error
 *
 * Managed lcd_device_रेजिस्टर(). The lcd_device वापसed from this function
 * are स्वतःmatically मुक्तd on driver detach. See lcd_device_रेजिस्टर()
 * क्रम more inक्रमmation.
 */
काष्ठा lcd_device *devm_lcd_device_रेजिस्टर(काष्ठा device *dev,
		स्थिर अक्षर *name, काष्ठा device *parent,
		व्योम *devdata, काष्ठा lcd_ops *ops)
अणु
	काष्ठा lcd_device **ptr, *lcd;

	ptr = devres_alloc(devm_lcd_device_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	lcd = lcd_device_रेजिस्टर(name, parent, devdata, ops);
	अगर (!IS_ERR(lcd)) अणु
		*ptr = lcd;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस lcd;
पूर्ण
EXPORT_SYMBOL(devm_lcd_device_रेजिस्टर);

/**
 * devm_lcd_device_unरेजिस्टर - resource managed lcd_device_unरेजिस्टर()
 * @dev: the device to unरेजिस्टर
 * @ld: the lcd device to unरेजिस्टर
 *
 * Deallocated a lcd allocated with devm_lcd_device_रेजिस्टर(). Normally
 * this function will not need to be called and the resource management
 * code will ensure that the resource is मुक्तd.
 */
व्योम devm_lcd_device_unरेजिस्टर(काष्ठा device *dev, काष्ठा lcd_device *ld)
अणु
	पूर्णांक rc;

	rc = devres_release(dev, devm_lcd_device_release,
				devm_lcd_device_match, ld);
	WARN_ON(rc);
पूर्ण
EXPORT_SYMBOL(devm_lcd_device_unरेजिस्टर);


अटल व्योम __निकास lcd_class_निकास(व्योम)
अणु
	class_destroy(lcd_class);
पूर्ण

अटल पूर्णांक __init lcd_class_init(व्योम)
अणु
	lcd_class = class_create(THIS_MODULE, "lcd");
	अगर (IS_ERR(lcd_class)) अणु
		pr_warn("Unable to create backlight class; errno = %ld\n",
			PTR_ERR(lcd_class));
		वापस PTR_ERR(lcd_class);
	पूर्ण

	lcd_class->dev_groups = lcd_device_groups;
	वापस 0;
पूर्ण

/*
 * अगर this is compiled पूर्णांकo the kernel, we need to ensure that the
 * class is रेजिस्टरed beक्रमe users of the class try to रेजिस्टर lcd's
 */
postcore_initcall(lcd_class_init);
module_निकास(lcd_class_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jamey Hicks <jamey.hicks@hp.com>, Andrew Zabolotny <zap@homelink.ru>");
MODULE_DESCRIPTION("LCD Lowlevel Control Abstraction");
