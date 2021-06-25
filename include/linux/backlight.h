<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Backlight Lowlevel Control Abstraction
 *
 * Copyright (C) 2003,2004 Hewlett-Packard Company
 *
 */

#अगर_अघोषित _LINUX_BACKLIGHT_H
#घोषणा _LINUX_BACKLIGHT_H

#समावेश <linux/device.h>
#समावेश <linux/fb.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>

/**
 * क्रमागत backlight_update_reason - what method was used to update backlight
 *
 * A driver indicates the method (reason) used क्रम updating the backlight
 * when calling backlight_क्रमce_update().
 */
क्रमागत backlight_update_reason अणु
	/**
	 * @BACKLIGHT_UPDATE_HOTKEY: The backlight was updated using a hot-key.
	 */
	BACKLIGHT_UPDATE_HOTKEY,

	/**
	 * @BACKLIGHT_UPDATE_SYSFS: The backlight was updated using sysfs.
	 */
	BACKLIGHT_UPDATE_SYSFS,
पूर्ण;

/**
 * क्रमागत backlight_type - the type of backlight control
 *
 * The type of पूर्णांकerface used to control the backlight.
 */
क्रमागत backlight_type अणु
	/**
	 * @BACKLIGHT_RAW:
	 *
	 * The backlight is controlled using hardware रेजिस्टरs.
	 */
	BACKLIGHT_RAW = 1,

	/**
	 * @BACKLIGHT_PLATFORM:
	 *
	 * The backlight is controlled using a platक्रमm-specअगरic पूर्णांकerface.
	 */
	BACKLIGHT_PLATFORM,

	/**
	 * @BACKLIGHT_FIRMWARE:
	 *
	 * The backlight is controlled using a standard firmware पूर्णांकerface.
	 */
	BACKLIGHT_FIRMWARE,

	/**
	 * @BACKLIGHT_TYPE_MAX: Number of entries.
	 */
	BACKLIGHT_TYPE_MAX,
पूर्ण;

/**
 * क्रमागत backlight_notअगरication - the type of notअगरication
 *
 * The notअगरications that is used क्रम notअगरication sent to the receiver
 * that रेजिस्टरed notअगरications using backlight_रेजिस्टर_notअगरier().
 */
क्रमागत backlight_notअगरication अणु
	/**
	 * @BACKLIGHT_REGISTERED: The backlight device is रेजिस्टरed.
	 */
	BACKLIGHT_REGISTERED,

	/**
	 * @BACKLIGHT_UNREGISTERED: The backlight revice is unरेजिस्टरed.
	 */
	BACKLIGHT_UNREGISTERED,
पूर्ण;

/** क्रमागत backlight_scale - the type of scale used क्रम brightness values
 *
 * The type of scale used क्रम brightness values.
 */
क्रमागत backlight_scale अणु
	/**
	 * @BACKLIGHT_SCALE_UNKNOWN: The scale is unknown.
	 */
	BACKLIGHT_SCALE_UNKNOWN = 0,

	/**
	 * @BACKLIGHT_SCALE_LINEAR: The scale is linear.
	 *
	 * The linear scale will increase brightness the same क्रम each step.
	 */
	BACKLIGHT_SCALE_LINEAR,

	/**
	 * @BACKLIGHT_SCALE_NON_LINEAR: The scale is not linear.
	 *
	 * This is often used when the brightness values tries to adjust to
	 * the relative perception of the eye demanding a non-linear scale.
	 */
	BACKLIGHT_SCALE_NON_LINEAR,
पूर्ण;

काष्ठा backlight_device;
काष्ठा fb_info;

/**
 * काष्ठा backlight_ops - backlight operations
 *
 * The backlight operations are specअगरied when the backlight device is रेजिस्टरed.
 */
काष्ठा backlight_ops अणु
	/**
	 * @options: Configure how operations are called from the core.
	 *
	 * The options parameter is used to adjust the behaviour of the core.
	 * Set BL_CORE_SUSPENDRESUME to get the update_status() operation called
	 * upon suspend and resume.
	 */
	अचिन्हित पूर्णांक options;

#घोषणा BL_CORE_SUSPENDRESUME	(1 << 0)

	/**
	 * @update_status: Operation called when properties have changed.
	 *
	 * Notअगरy the backlight driver some property has changed.
	 * The update_status operation is रक्षित by the update_lock.
	 *
	 * The backlight driver is expected to use backlight_is_blank()
	 * to check अगर the display is blanked and set brightness accordingly.
	 * update_status() is called when any of the properties has changed.
	 *
	 * RETURNS:
	 *
	 * 0 on success, negative error code अगर any failure occurred.
	 */
	पूर्णांक (*update_status)(काष्ठा backlight_device *);

	/**
	 * @get_brightness: Return the current backlight brightness.
	 *
	 * The driver may implement this as a पढ़ोback from the HW.
	 * This operation is optional and अगर not present then the current
	 * brightness property value is used.
	 *
	 * RETURNS:
	 *
	 * A brightness value which is 0 or a positive number.
	 * On failure a negative error code is वापसed.
	 */
	पूर्णांक (*get_brightness)(काष्ठा backlight_device *);

	/**
	 * @check_fb: Check the framebuffer device.
	 *
	 * Check अगर given framebuffer device is the one bound to this backlight.
	 * This operation is optional and अगर not implemented it is assumed that the
	 * fbdev is always the one bound to the backlight.
	 *
	 * RETURNS:
	 *
	 * If info is शून्य or the info matches the fbdev bound to the backlight वापस true.
	 * If info करोes not match the fbdev bound to the backlight वापस false.
	 */
	पूर्णांक (*check_fb)(काष्ठा backlight_device *bd, काष्ठा fb_info *info);
पूर्ण;

/**
 * काष्ठा backlight_properties - backlight properties
 *
 * This काष्ठाure defines all the properties of a backlight.
 */
काष्ठा backlight_properties अणु
	/**
	 * @brightness: The current brightness requested by the user.
	 *
	 * The backlight core makes sure the range is (0 to max_brightness)
	 * when the brightness is set via the sysfs attribute:
	 * /sys/class/backlight/<backlight>/brightness.
	 *
	 * This value can be set in the backlight_properties passed
	 * to devm_backlight_device_रेजिस्टर() to set a शेष brightness
	 * value.
	 */
	पूर्णांक brightness;

	/**
	 * @max_brightness: The maximum brightness value.
	 *
	 * This value must be set in the backlight_properties passed to
	 * devm_backlight_device_रेजिस्टर() and shall not be modअगरied by the
	 * driver after registration.
	 */
	पूर्णांक max_brightness;

	/**
	 * @घातer: The current घातer mode.
	 *
	 * User space can configure the घातer mode using the sysfs
	 * attribute: /sys/class/backlight/<backlight>/bl_घातer
	 * When the घातer property is updated update_status() is called.
	 *
	 * The possible values are: (0: full on, 1 to 3: घातer saving
	 * modes; 4: full off), see FB_BLANK_XXX.
	 *
	 * When the backlight device is enabled @घातer is set
	 * to FB_BLANK_UNBLANK. When the backlight device is disabled
	 * @घातer is set to FB_BLANK_POWERDOWN.
	 */
	पूर्णांक घातer;

	/**
	 * @fb_blank: The घातer state from the FBIOBLANK ioctl.
	 *
	 * When the FBIOBLANK ioctl is called @fb_blank is set to the
	 * blank parameter and the update_status() operation is called.
	 *
	 * When the backlight device is enabled @fb_blank is set
	 * to FB_BLANK_UNBLANK. When the backlight device is disabled
	 * @fb_blank is set to FB_BLANK_POWERDOWN.
	 *
	 * Backlight drivers should aव्योम using this property. It has been
	 * replaced by state & BL_CORE_FBLANK (although most drivers should
	 * use backlight_is_blank() as the preferred means to get the blank
	 * state).
	 *
	 * fb_blank is deprecated and will be हटाओd.
	 */
	पूर्णांक fb_blank;

	/**
	 * @type: The type of backlight supported.
	 *
	 * The backlight type allows userspace to make appropriate
	 * policy decisions based on the backlight type.
	 *
	 * This value must be set in the backlight_properties
	 * passed to devm_backlight_device_रेजिस्टर().
	 */
	क्रमागत backlight_type type;

	/**
	 * @state: The state of the backlight core.
	 *
	 * The state is a biपंचांगask. BL_CORE_FBBLANK is set when the display
	 * is expected to be blank. BL_CORE_SUSPENDED is set when the
	 * driver is suspended.
	 *
	 * backlight drivers are expected to use backlight_is_blank()
	 * in their update_status() operation rather than पढ़ोing the
	 * state property.
	 *
	 * The state is मुख्यtained by the core and drivers may not modअगरy it.
	 */
	अचिन्हित पूर्णांक state;

#घोषणा BL_CORE_SUSPENDED	(1 << 0)	/* backlight is suspended */
#घोषणा BL_CORE_FBBLANK		(1 << 1)	/* backlight is under an fb blank event */

	/**
	 * @scale: The type of the brightness scale.
	 */
	क्रमागत backlight_scale scale;
पूर्ण;

/**
 * काष्ठा backlight_device - backlight device data
 *
 * This काष्ठाure holds all data required by a backlight device.
 */
काष्ठा backlight_device अणु
	/**
	 * @props: Backlight properties
	 */
	काष्ठा backlight_properties props;

	/**
	 * @update_lock: The lock used when calling the update_status() operation.
	 *
	 * update_lock is an पूर्णांकernal backlight lock that serialise access
	 * to the update_status() operation. The backlight core holds the update_lock
	 * when calling the update_status() operation. The update_lock shall not
	 * be used by backlight drivers.
	 */
	काष्ठा mutex update_lock;

	/**
	 * @ops_lock: The lock used around everything related to backlight_ops.
	 *
	 * ops_lock is an पूर्णांकernal backlight lock that protects the ops poपूर्णांकer
	 * and is used around all accesses to ops and when the operations are
	 * invoked. The ops_lock shall not be used by backlight drivers.
	 */
	काष्ठा mutex ops_lock;

	/**
	 * @ops: Poपूर्णांकer to the backlight operations.
	 *
	 * If ops is शून्य, the driver that रेजिस्टरed this device has been unloaded,
	 * and अगर class_get_devdata() poपूर्णांकs to something in the body of that driver,
	 * it is also invalid.
	 */
	स्थिर काष्ठा backlight_ops *ops;

	/**
	 * @fb_notअगर: The framebuffer notअगरier block
	 */
	काष्ठा notअगरier_block fb_notअगर;

	/**
	 * @entry: List entry of all रेजिस्टरed backlight devices
	 */
	काष्ठा list_head entry;

	/**
	 * @dev: Parent device.
	 */
	काष्ठा device dev;

	/**
	 * @fb_bl_on: The state of inभागidual fbdev's.
	 *
	 * Multiple fbdev's may share one backlight device. The fb_bl_on
	 * records the state of the inभागidual fbdev.
	 */
	bool fb_bl_on[FB_MAX];

	/**
	 * @use_count: The number of uses of fb_bl_on.
	 */
	पूर्णांक use_count;
पूर्ण;

/**
 * backlight_update_status - क्रमce an update of the backlight device status
 * @bd: the backlight device
 */
अटल अंतरभूत पूर्णांक backlight_update_status(काष्ठा backlight_device *bd)
अणु
	पूर्णांक ret = -ENOENT;

	mutex_lock(&bd->update_lock);
	अगर (bd->ops && bd->ops->update_status)
		ret = bd->ops->update_status(bd);
	mutex_unlock(&bd->update_lock);

	वापस ret;
पूर्ण

/**
 * backlight_enable - Enable backlight
 * @bd: the backlight device to enable
 */
अटल अंतरभूत पूर्णांक backlight_enable(काष्ठा backlight_device *bd)
अणु
	अगर (!bd)
		वापस 0;

	bd->props.घातer = FB_BLANK_UNBLANK;
	bd->props.fb_blank = FB_BLANK_UNBLANK;
	bd->props.state &= ~BL_CORE_FBBLANK;

	वापस backlight_update_status(bd);
पूर्ण

/**
 * backlight_disable - Disable backlight
 * @bd: the backlight device to disable
 */
अटल अंतरभूत पूर्णांक backlight_disable(काष्ठा backlight_device *bd)
अणु
	अगर (!bd)
		वापस 0;

	bd->props.घातer = FB_BLANK_POWERDOWN;
	bd->props.fb_blank = FB_BLANK_POWERDOWN;
	bd->props.state |= BL_CORE_FBBLANK;

	वापस backlight_update_status(bd);
पूर्ण

/**
 * backlight_is_blank - Return true अगर display is expected to be blank
 * @bd: the backlight device
 *
 * Display is expected to be blank अगर any of these is true::
 *
 *   1) अगर घातer in not UNBLANK
 *   2) अगर fb_blank is not UNBLANK
 *   3) अगर state indicate BLANK or SUSPENDED
 *
 * Returns true अगर display is expected to be blank, false otherwise.
 */
अटल अंतरभूत bool backlight_is_blank(स्थिर काष्ठा backlight_device *bd)
अणु
	वापस bd->props.घातer != FB_BLANK_UNBLANK ||
	       bd->props.fb_blank != FB_BLANK_UNBLANK ||
	       bd->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK);
पूर्ण

/**
 * backlight_get_brightness - Returns the current brightness value
 * @bd: the backlight device
 *
 * Returns the current brightness value, taking in consideration the current
 * state. If backlight_is_blank() वापसs true then वापस 0 as brightness
 * otherwise वापस the current brightness property value.
 *
 * Backlight drivers are expected to use this function in their update_status()
 * operation to get the brightness value.
 */
अटल अंतरभूत पूर्णांक backlight_get_brightness(स्थिर काष्ठा backlight_device *bd)
अणु
	अगर (backlight_is_blank(bd))
		वापस 0;
	अन्यथा
		वापस bd->props.brightness;
पूर्ण

काष्ठा backlight_device *
backlight_device_रेजिस्टर(स्थिर अक्षर *name, काष्ठा device *dev, व्योम *devdata,
			  स्थिर काष्ठा backlight_ops *ops,
			  स्थिर काष्ठा backlight_properties *props);
काष्ठा backlight_device *
devm_backlight_device_रेजिस्टर(काष्ठा device *dev, स्थिर अक्षर *name,
			       काष्ठा device *parent, व्योम *devdata,
			       स्थिर काष्ठा backlight_ops *ops,
			       स्थिर काष्ठा backlight_properties *props);
व्योम backlight_device_unरेजिस्टर(काष्ठा backlight_device *bd);
व्योम devm_backlight_device_unरेजिस्टर(काष्ठा device *dev,
				      काष्ठा backlight_device *bd);
व्योम backlight_क्रमce_update(काष्ठा backlight_device *bd,
			    क्रमागत backlight_update_reason reason);
पूर्णांक backlight_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक backlight_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
काष्ठा backlight_device *backlight_device_get_by_name(स्थिर अक्षर *name);
काष्ठा backlight_device *backlight_device_get_by_type(क्रमागत backlight_type type);
पूर्णांक backlight_device_set_brightness(काष्ठा backlight_device *bd,
				    अचिन्हित दीर्घ brightness);

#घोषणा to_backlight_device(obj) container_of(obj, काष्ठा backlight_device, dev)

/**
 * bl_get_data - access devdata
 * @bl_dev: poपूर्णांकer to backlight device
 *
 * When a backlight device is रेजिस्टरed the driver has the possibility
 * to supply a व्योम * devdata. bl_get_data() वापस a poपूर्णांकer to the
 * devdata.
 *
 * RETURNS:
 *
 * poपूर्णांकer to devdata stored जबतक रेजिस्टरing the backlight device.
 */
अटल अंतरभूत व्योम * bl_get_data(काष्ठा backlight_device *bl_dev)
अणु
	वापस dev_get_drvdata(&bl_dev->dev);
पूर्ण

#अगर_घोषित CONFIG_OF
काष्ठा backlight_device *of_find_backlight_by_node(काष्ठा device_node *node);
#अन्यथा
अटल अंतरभूत काष्ठा backlight_device *
of_find_backlight_by_node(काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_BACKLIGHT_CLASS_DEVICE)
काष्ठा backlight_device *devm_of_find_backlight(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत काष्ठा backlight_device *
devm_of_find_backlight(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
