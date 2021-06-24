<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight Lowlevel Control Abstraction
 *
 * Copyright (C) 2003,2004 Hewlett-Packard Company
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/backlight.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/slab.h>

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
#समावेश <यंत्र/backlight.h>
#पूर्ण_अगर

/**
 * DOC: overview
 *
 * The backlight core supports implementing backlight drivers.
 *
 * A backlight driver रेजिस्टरs a driver using
 * devm_backlight_device_रेजिस्टर(). The properties of the backlight
 * driver such as type and max_brightness must be specअगरied.
 * When the core detect changes in क्रम example brightness or घातer state
 * the update_status() operation is called. The backlight driver shall
 * implement this operation and use it to adjust backlight.
 *
 * Several sysfs attributes are provided by the backlight core::
 *
 * - brightness         R/W, set the requested brightness level
 * - actual_brightness  RO, the brightness level used by the HW
 * - max_brightness     RO, the maximum  brightness level supported
 *
 * See Documentation/ABI/stable/sysfs-class-backlight क्रम the full list.
 *
 * The backlight can be adjusted using the sysfs पूर्णांकerface, and
 * the backlight driver may also support adjusting backlight using
 * a hot-key or some other platक्रमm or firmware specअगरic way.
 *
 * The driver must implement the get_brightness() operation अगर
 * the HW करो not support all the levels that can be specअगरied in
 * brightness, thus providing user-space access to the actual level
 * via the actual_brightness attribute.
 *
 * When the backlight changes this is reported to user-space using
 * an uevent connected to the actual_brightness attribute.
 * When brightness is set by platक्रमm specअगरic means, क्रम example
 * a hot-key to adjust backlight, the driver must notअगरy the backlight
 * core that brightness has changed using backlight_क्रमce_update().
 *
 * The backlight driver core receives notअगरications from fbdev and
 * अगर the event is FB_EVENT_BLANK and अगर the value of blank, from the
 * FBIOBLANK ioctrl, results in a change in the backlight state the
 * update_status() operation is called.
 */

अटल काष्ठा list_head backlight_dev_list;
अटल काष्ठा mutex backlight_dev_list_mutex;
अटल काष्ठा blocking_notअगरier_head backlight_notअगरier;

अटल स्थिर अक्षर *स्थिर backlight_types[] = अणु
	[BACKLIGHT_RAW] = "raw",
	[BACKLIGHT_PLATFORM] = "platform",
	[BACKLIGHT_FIRMWARE] = "firmware",
पूर्ण;

अटल स्थिर अक्षर *स्थिर backlight_scale_types[] = अणु
	[BACKLIGHT_SCALE_UNKNOWN]	= "unknown",
	[BACKLIGHT_SCALE_LINEAR]	= "linear",
	[BACKLIGHT_SCALE_NON_LINEAR]	= "non-linear",
पूर्ण;

#अगर defined(CONFIG_FB) || (defined(CONFIG_FB_MODULE) && \
			   defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE))
/*
 * fb_notअगरier_callback
 *
 * This callback माला_लो called when something important happens inside a
 * framebuffer driver. The backlight core only cares about FB_BLANK_UNBLANK
 * which is reported to the driver using backlight_update_status()
 * as a state change.
 *
 * There may be several fbdev's connected to the backlight device,
 * in which हाल they are kept track of. A state change is only reported
 * अगर there is a change in backlight क्रम the specअगरied fbdev.
 */
अटल पूर्णांक fb_notअगरier_callback(काष्ठा notअगरier_block *self,
				अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा backlight_device *bd;
	काष्ठा fb_event *evdata = data;
	पूर्णांक node = evdata->info->node;
	पूर्णांक fb_blank = 0;

	/* If we aren't पूर्णांकerested in this event, skip it immediately ... */
	अगर (event != FB_EVENT_BLANK)
		वापस 0;

	bd = container_of(self, काष्ठा backlight_device, fb_notअगर);
	mutex_lock(&bd->ops_lock);

	अगर (!bd->ops)
		जाओ out;
	अगर (bd->ops->check_fb && !bd->ops->check_fb(bd, evdata->info))
		जाओ out;

	fb_blank = *(पूर्णांक *)evdata->data;
	अगर (fb_blank == FB_BLANK_UNBLANK && !bd->fb_bl_on[node]) अणु
		bd->fb_bl_on[node] = true;
		अगर (!bd->use_count++) अणु
			bd->props.state &= ~BL_CORE_FBBLANK;
			bd->props.fb_blank = FB_BLANK_UNBLANK;
			backlight_update_status(bd);
		पूर्ण
	पूर्ण अन्यथा अगर (fb_blank != FB_BLANK_UNBLANK && bd->fb_bl_on[node]) अणु
		bd->fb_bl_on[node] = false;
		अगर (!(--bd->use_count)) अणु
			bd->props.state |= BL_CORE_FBBLANK;
			bd->props.fb_blank = fb_blank;
			backlight_update_status(bd);
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&bd->ops_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक backlight_रेजिस्टर_fb(काष्ठा backlight_device *bd)
अणु
	स_रखो(&bd->fb_notअगर, 0, माप(bd->fb_notअगर));
	bd->fb_notअगर.notअगरier_call = fb_notअगरier_callback;

	वापस fb_रेजिस्टर_client(&bd->fb_notअगर);
पूर्ण

अटल व्योम backlight_unरेजिस्टर_fb(काष्ठा backlight_device *bd)
अणु
	fb_unरेजिस्टर_client(&bd->fb_notअगर);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक backlight_रेजिस्टर_fb(काष्ठा backlight_device *bd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम backlight_unरेजिस्टर_fb(काष्ठा backlight_device *bd)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_FB */

अटल व्योम backlight_generate_event(काष्ठा backlight_device *bd,
				     क्रमागत backlight_update_reason reason)
अणु
	अक्षर *envp[2];

	चयन (reason) अणु
	हाल BACKLIGHT_UPDATE_SYSFS:
		envp[0] = "SOURCE=sysfs";
		अवरोध;
	हाल BACKLIGHT_UPDATE_HOTKEY:
		envp[0] = "SOURCE=hotkey";
		अवरोध;
	शेष:
		envp[0] = "SOURCE=unknown";
		अवरोध;
	पूर्ण
	envp[1] = शून्य;
	kobject_uevent_env(&bd->dev.kobj, KOBJ_CHANGE, envp);
	sysfs_notअगरy(&bd->dev.kobj, शून्य, "actual_brightness");
पूर्ण

अटल sमाप_प्रकार bl_घातer_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा backlight_device *bd = to_backlight_device(dev);

	वापस प्र_लिखो(buf, "%d\n", bd->props.घातer);
पूर्ण

अटल sमाप_प्रकार bl_घातer_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	काष्ठा backlight_device *bd = to_backlight_device(dev);
	अचिन्हित दीर्घ घातer, old_घातer;

	rc = kम_से_अदीर्घ(buf, 0, &घातer);
	अगर (rc)
		वापस rc;

	rc = -ENXIO;
	mutex_lock(&bd->ops_lock);
	अगर (bd->ops) अणु
		pr_debug("set power to %lu\n", घातer);
		अगर (bd->props.घातer != घातer) अणु
			old_घातer = bd->props.घातer;
			bd->props.घातer = घातer;
			rc = backlight_update_status(bd);
			अगर (rc)
				bd->props.घातer = old_घातer;
			अन्यथा
				rc = count;
		पूर्ण अन्यथा अणु
			rc = count;
		पूर्ण
	पूर्ण
	mutex_unlock(&bd->ops_lock);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(bl_घातer);

अटल sमाप_प्रकार brightness_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा backlight_device *bd = to_backlight_device(dev);

	वापस प्र_लिखो(buf, "%d\n", bd->props.brightness);
पूर्ण

पूर्णांक backlight_device_set_brightness(काष्ठा backlight_device *bd,
				    अचिन्हित दीर्घ brightness)
अणु
	पूर्णांक rc = -ENXIO;

	mutex_lock(&bd->ops_lock);
	अगर (bd->ops) अणु
		अगर (brightness > bd->props.max_brightness)
			rc = -EINVAL;
		अन्यथा अणु
			pr_debug("set brightness to %lu\n", brightness);
			bd->props.brightness = brightness;
			rc = backlight_update_status(bd);
		पूर्ण
	पूर्ण
	mutex_unlock(&bd->ops_lock);

	backlight_generate_event(bd, BACKLIGHT_UPDATE_SYSFS);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(backlight_device_set_brightness);

अटल sमाप_प्रकार brightness_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	काष्ठा backlight_device *bd = to_backlight_device(dev);
	अचिन्हित दीर्घ brightness;

	rc = kम_से_अदीर्घ(buf, 0, &brightness);
	अगर (rc)
		वापस rc;

	rc = backlight_device_set_brightness(bd, brightness);

	वापस rc ? rc : count;
पूर्ण
अटल DEVICE_ATTR_RW(brightness);

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा backlight_device *bd = to_backlight_device(dev);

	वापस प्र_लिखो(buf, "%s\n", backlight_types[bd->props.type]);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार max_brightness_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा backlight_device *bd = to_backlight_device(dev);

	वापस प्र_लिखो(buf, "%d\n", bd->props.max_brightness);
पूर्ण
अटल DEVICE_ATTR_RO(max_brightness);

अटल sमाप_प्रकार actual_brightness_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc = -ENXIO;
	काष्ठा backlight_device *bd = to_backlight_device(dev);

	mutex_lock(&bd->ops_lock);
	अगर (bd->ops && bd->ops->get_brightness)
		rc = प्र_लिखो(buf, "%d\n", bd->ops->get_brightness(bd));
	अन्यथा
		rc = प्र_लिखो(buf, "%d\n", bd->props.brightness);
	mutex_unlock(&bd->ops_lock);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(actual_brightness);

अटल sमाप_प्रकार scale_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा backlight_device *bd = to_backlight_device(dev);

	अगर (WARN_ON(bd->props.scale > BACKLIGHT_SCALE_NON_LINEAR))
		वापस प्र_लिखो(buf, "unknown\n");

	वापस प्र_लिखो(buf, "%s\n", backlight_scale_types[bd->props.scale]);
पूर्ण
अटल DEVICE_ATTR_RO(scale);

अटल काष्ठा class *backlight_class;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक backlight_suspend(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bd = to_backlight_device(dev);

	mutex_lock(&bd->ops_lock);
	अगर (bd->ops && bd->ops->options & BL_CORE_SUSPENDRESUME) अणु
		bd->props.state |= BL_CORE_SUSPENDED;
		backlight_update_status(bd);
	पूर्ण
	mutex_unlock(&bd->ops_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक backlight_resume(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bd = to_backlight_device(dev);

	mutex_lock(&bd->ops_lock);
	अगर (bd->ops && bd->ops->options & BL_CORE_SUSPENDRESUME) अणु
		bd->props.state &= ~BL_CORE_SUSPENDED;
		backlight_update_status(bd);
	पूर्ण
	mutex_unlock(&bd->ops_lock);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(backlight_class_dev_pm_ops, backlight_suspend,
			 backlight_resume);

अटल व्योम bl_device_release(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bd = to_backlight_device(dev);
	kमुक्त(bd);
पूर्ण

अटल काष्ठा attribute *bl_device_attrs[] = अणु
	&dev_attr_bl_घातer.attr,
	&dev_attr_brightness.attr,
	&dev_attr_actual_brightness.attr,
	&dev_attr_max_brightness.attr,
	&dev_attr_scale.attr,
	&dev_attr_type.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(bl_device);

/**
 * backlight_क्रमce_update - tell the backlight subप्रणाली that hardware state
 *   has changed
 * @bd: the backlight device to update
 * @reason: reason क्रम update
 *
 * Updates the पूर्णांकernal state of the backlight in response to a hardware event,
 * and generates an uevent to notअगरy userspace. A backlight driver shall call
 * backlight_क्रमce_update() when the backlight is changed using, क्रम example,
 * a hot-key. The updated brightness is पढ़ो using get_brightness() and the
 * brightness value is reported using an uevent.
 */
व्योम backlight_क्रमce_update(काष्ठा backlight_device *bd,
			    क्रमागत backlight_update_reason reason)
अणु
	mutex_lock(&bd->ops_lock);
	अगर (bd->ops && bd->ops->get_brightness)
		bd->props.brightness = bd->ops->get_brightness(bd);
	mutex_unlock(&bd->ops_lock);
	backlight_generate_event(bd, reason);
पूर्ण
EXPORT_SYMBOL(backlight_क्रमce_update);

/* deprecated - use devm_backlight_device_रेजिस्टर() */
काष्ठा backlight_device *backlight_device_रेजिस्टर(स्थिर अक्षर *name,
	काष्ठा device *parent, व्योम *devdata, स्थिर काष्ठा backlight_ops *ops,
	स्थिर काष्ठा backlight_properties *props)
अणु
	काष्ठा backlight_device *new_bd;
	पूर्णांक rc;

	pr_debug("backlight_device_register: name=%s\n", name);

	new_bd = kzalloc(माप(काष्ठा backlight_device), GFP_KERNEL);
	अगर (!new_bd)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&new_bd->update_lock);
	mutex_init(&new_bd->ops_lock);

	new_bd->dev.class = backlight_class;
	new_bd->dev.parent = parent;
	new_bd->dev.release = bl_device_release;
	dev_set_name(&new_bd->dev, "%s", name);
	dev_set_drvdata(&new_bd->dev, devdata);

	/* Set शेष properties */
	अगर (props) अणु
		स_नकल(&new_bd->props, props,
		       माप(काष्ठा backlight_properties));
		अगर (props->type <= 0 || props->type >= BACKLIGHT_TYPE_MAX) अणु
			WARN(1, "%s: invalid backlight type", name);
			new_bd->props.type = BACKLIGHT_RAW;
		पूर्ण
	पूर्ण अन्यथा अणु
		new_bd->props.type = BACKLIGHT_RAW;
	पूर्ण

	rc = device_रेजिस्टर(&new_bd->dev);
	अगर (rc) अणु
		put_device(&new_bd->dev);
		वापस ERR_PTR(rc);
	पूर्ण

	rc = backlight_रेजिस्टर_fb(new_bd);
	अगर (rc) अणु
		device_unरेजिस्टर(&new_bd->dev);
		वापस ERR_PTR(rc);
	पूर्ण

	new_bd->ops = ops;

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	mutex_lock(&pmac_backlight_mutex);
	अगर (!pmac_backlight)
		pmac_backlight = new_bd;
	mutex_unlock(&pmac_backlight_mutex);
#पूर्ण_अगर

	mutex_lock(&backlight_dev_list_mutex);
	list_add(&new_bd->entry, &backlight_dev_list);
	mutex_unlock(&backlight_dev_list_mutex);

	blocking_notअगरier_call_chain(&backlight_notअगरier,
				     BACKLIGHT_REGISTERED, new_bd);

	वापस new_bd;
पूर्ण
EXPORT_SYMBOL(backlight_device_रेजिस्टर);

/** backlight_device_get_by_type - find first backlight device of a type
 * @type: the type of backlight device
 *
 * Look up the first backlight device of the specअगरied type
 *
 * RETURNS:
 *
 * Poपूर्णांकer to backlight device अगर any was found. Otherwise शून्य.
 */
काष्ठा backlight_device *backlight_device_get_by_type(क्रमागत backlight_type type)
अणु
	bool found = false;
	काष्ठा backlight_device *bd;

	mutex_lock(&backlight_dev_list_mutex);
	list_क्रम_each_entry(bd, &backlight_dev_list, entry) अणु
		अगर (bd->props.type == type) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&backlight_dev_list_mutex);

	वापस found ? bd : शून्य;
पूर्ण
EXPORT_SYMBOL(backlight_device_get_by_type);

/**
 * backlight_device_get_by_name - Get backlight device by name
 * @name: Device name
 *
 * This function looks up a backlight device by its name. It obtains a reference
 * on the backlight device and it is the caller's responsibility to drop the
 * reference by calling backlight_put().
 *
 * Returns:
 * A poपूर्णांकer to the backlight device अगर found, otherwise शून्य.
 */
काष्ठा backlight_device *backlight_device_get_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा device *dev;

	dev = class_find_device_by_name(backlight_class, name);

	वापस dev ? to_backlight_device(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL(backlight_device_get_by_name);

/* deprecated - use devm_backlight_device_unरेजिस्टर() */
व्योम backlight_device_unरेजिस्टर(काष्ठा backlight_device *bd)
अणु
	अगर (!bd)
		वापस;

	mutex_lock(&backlight_dev_list_mutex);
	list_del(&bd->entry);
	mutex_unlock(&backlight_dev_list_mutex);

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	mutex_lock(&pmac_backlight_mutex);
	अगर (pmac_backlight == bd)
		pmac_backlight = शून्य;
	mutex_unlock(&pmac_backlight_mutex);
#पूर्ण_अगर

	blocking_notअगरier_call_chain(&backlight_notअगरier,
				     BACKLIGHT_UNREGISTERED, bd);

	mutex_lock(&bd->ops_lock);
	bd->ops = शून्य;
	mutex_unlock(&bd->ops_lock);

	backlight_unरेजिस्टर_fb(bd);
	device_unरेजिस्टर(&bd->dev);
पूर्ण
EXPORT_SYMBOL(backlight_device_unरेजिस्टर);

अटल व्योम devm_backlight_device_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा backlight_device *backlight = *(काष्ठा backlight_device **)res;

	backlight_device_unरेजिस्टर(backlight);
पूर्ण

अटल पूर्णांक devm_backlight_device_match(काष्ठा device *dev, व्योम *res,
					व्योम *data)
अणु
	काष्ठा backlight_device **r = res;

	वापस *r == data;
पूर्ण

/**
 * backlight_रेजिस्टर_notअगरier - get notअगरied of backlight (un)registration
 * @nb: notअगरier block with the notअगरier to call on backlight (un)registration
 *
 * Register a notअगरier to get notअगरied when backlight devices get रेजिस्टरed
 * or unरेजिस्टरed.
 *
 * RETURNS:
 *
 * 0 on success, otherwise a negative error code
 */
पूर्णांक backlight_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&backlight_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL(backlight_रेजिस्टर_notअगरier);

/**
 * backlight_unरेजिस्टर_notअगरier - unरेजिस्टर a backlight notअगरier
 * @nb: notअगरier block to unरेजिस्टर
 *
 * Register a notअगरier to get notअगरied when backlight devices get रेजिस्टरed
 * or unरेजिस्टरed.
 *
 * RETURNS:
 *
 * 0 on success, otherwise a negative error code
 */
पूर्णांक backlight_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&backlight_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL(backlight_unरेजिस्टर_notअगरier);

/**
 * devm_backlight_device_रेजिस्टर - रेजिस्टर a new backlight device
 * @dev: the device to रेजिस्टर
 * @name: the name of the device
 * @parent: a poपूर्णांकer to the parent device (often the same as @dev)
 * @devdata: an optional poपूर्णांकer to be stored क्रम निजी driver use
 * @ops: the backlight operations काष्ठाure
 * @props: the backlight properties
 *
 * Creates and रेजिस्टरs new backlight device. When a backlight device
 * is रेजिस्टरed the configuration must be specअगरied in the @props
 * parameter. See description of &backlight_properties.
 *
 * RETURNS:
 *
 * काष्ठा backlight on success, or an ERR_PTR on error
 */
काष्ठा backlight_device *devm_backlight_device_रेजिस्टर(काष्ठा device *dev,
	स्थिर अक्षर *name, काष्ठा device *parent, व्योम *devdata,
	स्थिर काष्ठा backlight_ops *ops,
	स्थिर काष्ठा backlight_properties *props)
अणु
	काष्ठा backlight_device **ptr, *backlight;

	ptr = devres_alloc(devm_backlight_device_release, माप(*ptr),
			GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	backlight = backlight_device_रेजिस्टर(name, parent, devdata, ops,
						props);
	अगर (!IS_ERR(backlight)) अणु
		*ptr = backlight;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस backlight;
पूर्ण
EXPORT_SYMBOL(devm_backlight_device_रेजिस्टर);

/**
 * devm_backlight_device_unरेजिस्टर - unरेजिस्टर backlight device
 * @dev: the device to unरेजिस्टर
 * @bd: the backlight device to unरेजिस्टर
 *
 * Deallocates a backlight allocated with devm_backlight_device_रेजिस्टर().
 * Normally this function will not need to be called and the resource management
 * code will ensure that the resources are मुक्तd.
 */
व्योम devm_backlight_device_unरेजिस्टर(काष्ठा device *dev,
				काष्ठा backlight_device *bd)
अणु
	पूर्णांक rc;

	rc = devres_release(dev, devm_backlight_device_release,
				devm_backlight_device_match, bd);
	WARN_ON(rc);
पूर्ण
EXPORT_SYMBOL(devm_backlight_device_unरेजिस्टर);

#अगर_घोषित CONFIG_OF
अटल पूर्णांक of_parent_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस dev->parent && dev->parent->of_node == data;
पूर्ण

/**
 * of_find_backlight_by_node() - find backlight device by device-tree node
 * @node: device-tree node of the backlight device
 *
 * Returns a poपूर्णांकer to the backlight device corresponding to the given DT
 * node or शून्य अगर no such backlight device exists or अगर the device hasn't
 * been probed yet.
 *
 * This function obtains a reference on the backlight device and it is the
 * caller's responsibility to drop the reference by calling put_device() on
 * the backlight device's .dev field.
 */
काष्ठा backlight_device *of_find_backlight_by_node(काष्ठा device_node *node)
अणु
	काष्ठा device *dev;

	dev = class_find_device(backlight_class, शून्य, node, of_parent_match);

	वापस dev ? to_backlight_device(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL(of_find_backlight_by_node);
#पूर्ण_अगर

अटल काष्ठा backlight_device *of_find_backlight(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bd = शून्य;
	काष्ठा device_node *np;

	अगर (!dev)
		वापस शून्य;

	अगर (IS_ENABLED(CONFIG_OF) && dev->of_node) अणु
		np = of_parse_phandle(dev->of_node, "backlight", 0);
		अगर (np) अणु
			bd = of_find_backlight_by_node(np);
			of_node_put(np);
			अगर (!bd)
				वापस ERR_PTR(-EPROBE_DEFER);
			/*
			 * Note: gpio_backlight uses brightness as
			 * घातer state during probe
			 */
			अगर (!bd->props.brightness)
				bd->props.brightness = bd->props.max_brightness;
		पूर्ण
	पूर्ण

	वापस bd;
पूर्ण

अटल व्योम devm_backlight_release(व्योम *data)
अणु
	काष्ठा backlight_device *bd = data;

	अगर (bd)
		put_device(&bd->dev);
पूर्ण

/**
 * devm_of_find_backlight - find backlight क्रम a device
 * @dev: the device
 *
 * This function looks क्रम a property named 'backlight' on the DT node
 * connected to @dev and looks up the backlight device. The lookup is
 * device managed so the reference to the backlight device is स्वतःmatically
 * dropped on driver detach.
 *
 * RETURNS:
 *
 * A poपूर्णांकer to the backlight device अगर found.
 * Error poपूर्णांकer -EPROBE_DEFER अगर the DT property is set, but no backlight
 * device is found. शून्य अगर there's no backlight property.
 */
काष्ठा backlight_device *devm_of_find_backlight(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bd;
	पूर्णांक ret;

	bd = of_find_backlight(dev);
	अगर (IS_ERR_OR_शून्य(bd))
		वापस bd;
	ret = devm_add_action(dev, devm_backlight_release, bd);
	अगर (ret) अणु
		put_device(&bd->dev);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस bd;
पूर्ण
EXPORT_SYMBOL(devm_of_find_backlight);

अटल व्योम __निकास backlight_class_निकास(व्योम)
अणु
	class_destroy(backlight_class);
पूर्ण

अटल पूर्णांक __init backlight_class_init(व्योम)
अणु
	backlight_class = class_create(THIS_MODULE, "backlight");
	अगर (IS_ERR(backlight_class)) अणु
		pr_warn("Unable to create backlight class; errno = %ld\n",
			PTR_ERR(backlight_class));
		वापस PTR_ERR(backlight_class);
	पूर्ण

	backlight_class->dev_groups = bl_device_groups;
	backlight_class->pm = &backlight_class_dev_pm_ops;
	INIT_LIST_HEAD(&backlight_dev_list);
	mutex_init(&backlight_dev_list_mutex);
	BLOCKING_INIT_NOTIFIER_HEAD(&backlight_notअगरier);

	वापस 0;
पूर्ण

/*
 * अगर this is compiled पूर्णांकo the kernel, we need to ensure that the
 * class is रेजिस्टरed beक्रमe users of the class try to रेजिस्टर lcd's
 */
postcore_initcall(backlight_class_init);
module_निकास(backlight_class_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jamey Hicks <jamey.hicks@hp.com>, Andrew Zabolotny <zap@homelink.ru>");
MODULE_DESCRIPTION("Backlight Lowlevel Control Abstraction");
