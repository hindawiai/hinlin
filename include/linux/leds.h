<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver model क्रम leds and led triggers
 *
 * Copyright (C) 2005 John Lenz <lenz@cs.wisc.edu>
 * Copyright (C) 2005 Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */
#अगर_अघोषित __LINUX_LEDS_H_INCLUDED
#घोषणा __LINUX_LEDS_H_INCLUDED

#समावेश <dt-bindings/leds/common.h>
#समावेश <linux/device.h>
#समावेश <linux/kernfs.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>

काष्ठा device;
काष्ठा led_pattern;
काष्ठा device_node;
/*
 * LED Core
 */

/* This is obsolete/useless. We now support variable maximum brightness. */
क्रमागत led_brightness अणु
	LED_OFF		= 0,
	LED_ON		= 1,
	LED_HALF	= 127,
	LED_FULL	= 255,
पूर्ण;

काष्ठा led_init_data अणु
	/* device fwnode handle */
	काष्ठा fwnode_handle *fwnode;
	/*
	 * शेष <color:function> tuple, क्रम backward compatibility
	 * with in-driver hard-coded LED names used as a fallback when
	 * DT "label" property is असलent; it should be set to शून्य
	 * in new LED class drivers.
	 */
	स्थिर अक्षर *शेष_label;
	/*
	 * string to be used क्रम devicename section of LED class device
	 * either क्रम label based LED name composition path or क्रम fwnode
	 * based when devname_mandatory is true
	 */
	स्थिर अक्षर *devicename;
	/*
	 * indicates अगर LED name should always comprise devicename section;
	 * only LEDs exposed by drivers of hot-pluggable devices should
	 * set it to true
	 */
	bool devname_mandatory;
पूर्ण;

काष्ठा led_hw_trigger_type अणु
	पूर्णांक dummy;
पूर्ण;

काष्ठा led_classdev अणु
	स्थिर अक्षर		*name;
	अचिन्हित पूर्णांक brightness;
	अचिन्हित पूर्णांक max_brightness;
	पूर्णांक			 flags;

	/* Lower 16 bits reflect status */
#घोषणा LED_SUSPENDED		BIT(0)
#घोषणा LED_UNREGISTERING	BIT(1)
	/* Upper 16 bits reflect control inक्रमmation */
#घोषणा LED_CORE_SUSPENDRESUME	BIT(16)
#घोषणा LED_SYSFS_DISABLE	BIT(17)
#घोषणा LED_DEV_CAP_FLASH	BIT(18)
#घोषणा LED_HW_PLUGGABLE	BIT(19)
#घोषणा LED_PANIC_INDICATOR	BIT(20)
#घोषणा LED_BRIGHT_HW_CHANGED	BIT(21)
#घोषणा LED_RETAIN_AT_SHUTDOWN	BIT(22)
#घोषणा LED_INIT_DEFAULT_TRIGGER BIT(23)

	/* set_brightness_work / blink_समयr flags, atomic, निजी. */
	अचिन्हित दीर्घ		work_flags;

#घोषणा LED_BLINK_SW			0
#घोषणा LED_BLINK_ONESHOT		1
#घोषणा LED_BLINK_ONESHOT_STOP		2
#घोषणा LED_BLINK_INVERT		3
#घोषणा LED_BLINK_BRIGHTNESS_CHANGE 	4
#घोषणा LED_BLINK_DISABLE		5

	/* Set LED brightness level
	 * Must not sleep. Use brightness_set_blocking क्रम drivers
	 * that can sleep जबतक setting brightness.
	 */
	व्योम		(*brightness_set)(काष्ठा led_classdev *led_cdev,
					  क्रमागत led_brightness brightness);
	/*
	 * Set LED brightness level immediately - it can block the caller क्रम
	 * the समय required क्रम accessing a LED device रेजिस्टर.
	 */
	पूर्णांक (*brightness_set_blocking)(काष्ठा led_classdev *led_cdev,
				       क्रमागत led_brightness brightness);
	/* Get LED brightness level */
	क्रमागत led_brightness (*brightness_get)(काष्ठा led_classdev *led_cdev);

	/*
	 * Activate hardware accelerated blink, delays are in milliseconds
	 * and अगर both are zero then a sensible शेष should be chosen.
	 * The call should adjust the timings in that हाल and अगर it can't
	 * match the values specअगरied exactly.
	 * Deactivate blinking again when the brightness is set to LED_OFF
	 * via the brightness_set() callback.
	 */
	पूर्णांक		(*blink_set)(काष्ठा led_classdev *led_cdev,
				     अचिन्हित दीर्घ *delay_on,
				     अचिन्हित दीर्घ *delay_off);

	पूर्णांक (*pattern_set)(काष्ठा led_classdev *led_cdev,
			   काष्ठा led_pattern *pattern, u32 len, पूर्णांक repeat);
	पूर्णांक (*pattern_clear)(काष्ठा led_classdev *led_cdev);

	काष्ठा device		*dev;
	स्थिर काष्ठा attribute_group	**groups;

	काष्ठा list_head	 node;			/* LED Device list */
	स्थिर अक्षर		*शेष_trigger;	/* Trigger to use */

	अचिन्हित दीर्घ		 blink_delay_on, blink_delay_off;
	काष्ठा समयr_list	 blink_समयr;
	पूर्णांक			 blink_brightness;
	पूर्णांक			 new_blink_brightness;
	व्योम			(*flash_resume)(काष्ठा led_classdev *led_cdev);

	काष्ठा work_काष्ठा	set_brightness_work;
	पूर्णांक			delayed_set_value;

#अगर_घोषित CONFIG_LEDS_TRIGGERS
	/* Protects the trigger data below */
	काष्ठा rw_semaphore	 trigger_lock;

	काष्ठा led_trigger	*trigger;
	काष्ठा list_head	 trig_list;
	व्योम			*trigger_data;
	/* true अगर activated - deactivate routine uses it to करो cleanup */
	bool			activated;

	/* LEDs that have निजी triggers have this set */
	काष्ठा led_hw_trigger_type	*trigger_type;
#पूर्ण_अगर

#अगर_घोषित CONFIG_LEDS_BRIGHTNESS_HW_CHANGED
	पूर्णांक			 brightness_hw_changed;
	काष्ठा kernfs_node	*brightness_hw_changed_kn;
#पूर्ण_अगर

	/* Ensures consistent access to the LED Flash Class device */
	काष्ठा mutex		led_access;
पूर्ण;

/**
 * led_classdev_रेजिस्टर_ext - रेजिस्टर a new object of LED class with
 *			       init data
 * @parent: LED controller device this LED is driven by
 * @led_cdev: the led_classdev काष्ठाure क्रम this device
 * @init_data: the LED class device initialization data
 *
 * Register a new object of LED class, with name derived from init_data.
 *
 * Returns: 0 on success or negative error value on failure
 */
पूर्णांक led_classdev_रेजिस्टर_ext(काष्ठा device *parent,
				     काष्ठा led_classdev *led_cdev,
				     काष्ठा led_init_data *init_data);

/**
 * led_classdev_रेजिस्टर - रेजिस्टर a new object of LED class
 * @parent: LED controller device this LED is driven by
 * @led_cdev: the led_classdev काष्ठाure क्रम this device
 *
 * Register a new object of LED class, with name derived from the name property
 * of passed led_cdev argument.
 *
 * Returns: 0 on success or negative error value on failure
 */
अटल अंतरभूत पूर्णांक led_classdev_रेजिस्टर(काष्ठा device *parent,
					काष्ठा led_classdev *led_cdev)
अणु
	वापस led_classdev_रेजिस्टर_ext(parent, led_cdev, शून्य);
पूर्ण

पूर्णांक devm_led_classdev_रेजिस्टर_ext(काष्ठा device *parent,
					  काष्ठा led_classdev *led_cdev,
					  काष्ठा led_init_data *init_data);

अटल अंतरभूत पूर्णांक devm_led_classdev_रेजिस्टर(काष्ठा device *parent,
					     काष्ठा led_classdev *led_cdev)
अणु
	वापस devm_led_classdev_रेजिस्टर_ext(parent, led_cdev, शून्य);
पूर्ण
व्योम led_classdev_unरेजिस्टर(काष्ठा led_classdev *led_cdev);
व्योम devm_led_classdev_unरेजिस्टर(काष्ठा device *parent,
				  काष्ठा led_classdev *led_cdev);
व्योम led_classdev_suspend(काष्ठा led_classdev *led_cdev);
व्योम led_classdev_resume(काष्ठा led_classdev *led_cdev);

बाह्य काष्ठा led_classdev *of_led_get(काष्ठा device_node *np, पूर्णांक index);
बाह्य व्योम led_put(काष्ठा led_classdev *led_cdev);
काष्ठा led_classdev *__must_check devm_of_led_get(काष्ठा device *dev,
						  पूर्णांक index);

/**
 * led_blink_set - set blinking with software fallback
 * @led_cdev: the LED to start blinking
 * @delay_on: the समय it should be on (in ms)
 * @delay_off: the समय it should ble off (in ms)
 *
 * This function makes the LED blink, attempting to use the
 * hardware acceleration अगर possible, but falling back to
 * software blinking अगर there is no hardware blinking or अगर
 * the LED refuses the passed values.
 *
 * Note that अगर software blinking is active, simply calling
 * led_cdev->brightness_set() will not stop the blinking,
 * use led_classdev_brightness_set() instead.
 */
व्योम led_blink_set(काष्ठा led_classdev *led_cdev, अचिन्हित दीर्घ *delay_on,
		   अचिन्हित दीर्घ *delay_off);
/**
 * led_blink_set_oneshot - करो a oneshot software blink
 * @led_cdev: the LED to start blinking
 * @delay_on: the समय it should be on (in ms)
 * @delay_off: the समय it should ble off (in ms)
 * @invert: blink off, then on, leaving the led on
 *
 * This function makes the LED blink one समय क्रम delay_on +
 * delay_off समय, ignoring the request अगर another one-shot
 * blink is alपढ़ोy in progress.
 *
 * If invert is set, led blinks क्रम delay_off first, then क्रम
 * delay_on and leave the led on after the on-off cycle.
 */
व्योम led_blink_set_oneshot(काष्ठा led_classdev *led_cdev,
			   अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off,
			   पूर्णांक invert);
/**
 * led_set_brightness - set LED brightness
 * @led_cdev: the LED to set
 * @brightness: the brightness to set it to
 *
 * Set an LED's brightness, and, अगर necessary, cancel the
 * software blink समयr that implements blinking when the
 * hardware करोesn't. This function is guaranteed not to sleep.
 */
व्योम led_set_brightness(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक brightness);

/**
 * led_set_brightness_sync - set LED brightness synchronously
 * @led_cdev: the LED to set
 * @value: the brightness to set it to
 *
 * Set an LED's brightness immediately. This function will block
 * the caller क्रम the समय required क्रम accessing device रेजिस्टरs,
 * and it can sleep.
 *
 * Returns: 0 on success or negative error value on failure
 */
पूर्णांक led_set_brightness_sync(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक value);

/**
 * led_update_brightness - update LED brightness
 * @led_cdev: the LED to query
 *
 * Get an LED's current brightness and update led_cdev->brightness
 * member with the obtained value.
 *
 * Returns: 0 on success or negative error value on failure
 */
पूर्णांक led_update_brightness(काष्ठा led_classdev *led_cdev);

/**
 * led_get_शेष_pattern - वापस शेष pattern
 *
 * @led_cdev: the LED to get शेष pattern क्रम
 * @size:     poपूर्णांकer क्रम storing the number of elements in वापसed array,
 *            modअगरied only अगर वापस != शून्य
 *
 * Return:    Allocated array of पूर्णांकegers with शेष pattern from device tree
 *            or शून्य.  Caller is responsible क्रम kमुक्त().
 */
u32 *led_get_शेष_pattern(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक *size);

/**
 * led_sysfs_disable - disable LED sysfs पूर्णांकerface
 * @led_cdev: the LED to set
 *
 * Disable the led_cdev's sysfs पूर्णांकerface.
 */
व्योम led_sysfs_disable(काष्ठा led_classdev *led_cdev);

/**
 * led_sysfs_enable - enable LED sysfs पूर्णांकerface
 * @led_cdev: the LED to set
 *
 * Enable the led_cdev's sysfs पूर्णांकerface.
 */
व्योम led_sysfs_enable(काष्ठा led_classdev *led_cdev);

/**
 * led_compose_name - compose LED class device name
 * @dev: LED controller device object
 * @init_data: the LED class device initialization data
 * @led_classdev_name: composed LED class device name
 *
 * Create LED class device name basing on the provided init_data argument.
 * The name can have <devicename:color:function> or <color:function>.
 * क्रमm, depending on the init_data configuration.
 *
 * Returns: 0 on success or negative error value on failure
 */
पूर्णांक led_compose_name(काष्ठा device *dev, काष्ठा led_init_data *init_data,
		     अक्षर *led_classdev_name);

/**
 * led_sysfs_is_disabled - check अगर LED sysfs पूर्णांकerface is disabled
 * @led_cdev: the LED to query
 *
 * Returns: true अगर the led_cdev's sysfs पूर्णांकerface is disabled.
 */
अटल अंतरभूत bool led_sysfs_is_disabled(काष्ठा led_classdev *led_cdev)
अणु
	वापस led_cdev->flags & LED_SYSFS_DISABLE;
पूर्ण

/*
 * LED Triggers
 */
/* Registration functions क्रम simple triggers */
#घोषणा DEFINE_LED_TRIGGER(x)		अटल काष्ठा led_trigger *x;
#घोषणा DEFINE_LED_TRIGGER_GLOBAL(x)	काष्ठा led_trigger *x;

#अगर_घोषित CONFIG_LEDS_TRIGGERS

#घोषणा TRIG_NAME_MAX 50

काष्ठा led_trigger अणु
	/* Trigger Properties */
	स्थिर अक्षर	 *name;
	पूर्णांक		(*activate)(काष्ठा led_classdev *led_cdev);
	व्योम		(*deactivate)(काष्ठा led_classdev *led_cdev);

	/* LED-निजी triggers have this set */
	काष्ठा led_hw_trigger_type *trigger_type;

	/* LEDs under control by this trigger (क्रम simple triggers) */
	rwlock_t	  leddev_list_lock;
	काष्ठा list_head  led_cdevs;

	/* Link to next रेजिस्टरed trigger */
	काष्ठा list_head  next_trig;

	स्थिर काष्ठा attribute_group **groups;
पूर्ण;

/*
 * Currently the attributes in काष्ठा led_trigger::groups are added directly to
 * the LED device. As this might change in the future, the following
 * macros असलtract getting the LED device and its trigger_data from the dev
 * parameter passed to the attribute accessor functions.
 */
#घोषणा led_trigger_get_led(dev)	((काष्ठा led_classdev *)dev_get_drvdata((dev)))
#घोषणा led_trigger_get_drvdata(dev)	(led_get_trigger_data(led_trigger_get_led(dev)))

/* Registration functions क्रम complex triggers */
पूर्णांक led_trigger_रेजिस्टर(काष्ठा led_trigger *trigger);
व्योम led_trigger_unरेजिस्टर(काष्ठा led_trigger *trigger);
पूर्णांक devm_led_trigger_रेजिस्टर(काष्ठा device *dev,
				     काष्ठा led_trigger *trigger);

व्योम led_trigger_रेजिस्टर_simple(स्थिर अक्षर *name,
				काष्ठा led_trigger **trigger);
व्योम led_trigger_unरेजिस्टर_simple(काष्ठा led_trigger *trigger);
व्योम led_trigger_event(काष्ठा led_trigger *trigger,  क्रमागत led_brightness event);
व्योम led_trigger_blink(काष्ठा led_trigger *trigger, अचिन्हित दीर्घ *delay_on,
		       अचिन्हित दीर्घ *delay_off);
व्योम led_trigger_blink_oneshot(काष्ठा led_trigger *trigger,
			       अचिन्हित दीर्घ *delay_on,
			       अचिन्हित दीर्घ *delay_off,
			       पूर्णांक invert);
व्योम led_trigger_set_शेष(काष्ठा led_classdev *led_cdev);
पूर्णांक led_trigger_set(काष्ठा led_classdev *led_cdev, काष्ठा led_trigger *trigger);
व्योम led_trigger_हटाओ(काष्ठा led_classdev *led_cdev);

अटल अंतरभूत व्योम led_set_trigger_data(काष्ठा led_classdev *led_cdev,
					व्योम *trigger_data)
अणु
	led_cdev->trigger_data = trigger_data;
पूर्ण

अटल अंतरभूत व्योम *led_get_trigger_data(काष्ठा led_classdev *led_cdev)
अणु
	वापस led_cdev->trigger_data;
पूर्ण

/**
 * led_trigger_नाम_अटल - नाम a trigger
 * @name: the new trigger name
 * @trig: the LED trigger to नाम
 *
 * Change a LED trigger name by copying the string passed in
 * name पूर्णांकo current trigger name, which MUST be large
 * enough क्रम the new string.
 *
 * Note that name must NOT poपूर्णांक to the same string used
 * during LED registration, as that could lead to races.
 *
 * This is meant to be used on triggers with अटलally
 * allocated name.
 */
व्योम led_trigger_नाम_अटल(स्थिर अक्षर *name, काष्ठा led_trigger *trig);

#घोषणा module_led_trigger(__led_trigger) \
	module_driver(__led_trigger, led_trigger_रेजिस्टर, \
		      led_trigger_unरेजिस्टर)

#अन्यथा

/* Trigger has no members */
काष्ठा led_trigger अणुपूर्ण;

/* Trigger अंतरभूत empty functions */
अटल अंतरभूत व्योम led_trigger_रेजिस्टर_simple(स्थिर अक्षर *name,
					काष्ठा led_trigger **trigger) अणुपूर्ण
अटल अंतरभूत व्योम led_trigger_unरेजिस्टर_simple(काष्ठा led_trigger *trigger) अणुपूर्ण
अटल अंतरभूत व्योम led_trigger_event(काष्ठा led_trigger *trigger,
				क्रमागत led_brightness event) अणुपूर्ण
अटल अंतरभूत व्योम led_trigger_blink(काष्ठा led_trigger *trigger,
				      अचिन्हित दीर्घ *delay_on,
				      अचिन्हित दीर्घ *delay_off) अणुपूर्ण
अटल अंतरभूत व्योम led_trigger_blink_oneshot(काष्ठा led_trigger *trigger,
				      अचिन्हित दीर्घ *delay_on,
				      अचिन्हित दीर्घ *delay_off,
				      पूर्णांक invert) अणुपूर्ण
अटल अंतरभूत व्योम led_trigger_set_शेष(काष्ठा led_classdev *led_cdev) अणुपूर्ण
अटल अंतरभूत पूर्णांक led_trigger_set(काष्ठा led_classdev *led_cdev,
				  काष्ठा led_trigger *trigger)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम led_trigger_हटाओ(काष्ठा led_classdev *led_cdev) अणुपूर्ण
अटल अंतरभूत व्योम led_set_trigger_data(काष्ठा led_classdev *led_cdev) अणुपूर्ण
अटल अंतरभूत व्योम *led_get_trigger_data(काष्ठा led_classdev *led_cdev)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_LEDS_TRIGGERS */

/* Trigger specअगरic functions */
#अगर_घोषित CONFIG_LEDS_TRIGGER_DISK
व्योम ledtrig_disk_activity(bool ग_लिखो);
#अन्यथा
अटल अंतरभूत व्योम ledtrig_disk_activity(bool ग_लिखो) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_LEDS_TRIGGER_MTD
व्योम ledtrig_mtd_activity(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ledtrig_mtd_activity(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_LEDS_TRIGGER_CAMERA) || defined(CONFIG_LEDS_TRIGGER_CAMERA_MODULE)
व्योम ledtrig_flash_ctrl(bool on);
व्योम ledtrig_torch_ctrl(bool on);
#अन्यथा
अटल अंतरभूत व्योम ledtrig_flash_ctrl(bool on) अणुपूर्ण
अटल अंतरभूत व्योम ledtrig_torch_ctrl(bool on) अणुपूर्ण
#पूर्ण_अगर

/*
 * Generic LED platक्रमm data क्रम describing LED names and शेष triggers.
 */
काष्ठा led_info अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*शेष_trigger;
	पूर्णांक		flags;
पूर्ण;

काष्ठा led_platक्रमm_data अणु
	पूर्णांक		num_leds;
	काष्ठा led_info	*leds;
पूर्ण;

काष्ठा led_properties अणु
	u32		color;
	bool		color_present;
	स्थिर अक्षर	*function;
	u32		func_क्रमागत;
	bool		func_क्रमागत_present;
	स्थिर अक्षर	*label;
पूर्ण;

काष्ठा gpio_desc;
प्रकार पूर्णांक (*gpio_blink_set_t)(काष्ठा gpio_desc *desc, पूर्णांक state,
				अचिन्हित दीर्घ *delay_on,
				अचिन्हित दीर्घ *delay_off);

/* For the leds-gpio driver */
काष्ठा gpio_led अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *शेष_trigger;
	अचिन्हित 	gpio;
	अचिन्हित	active_low : 1;
	अचिन्हित	retain_state_suspended : 1;
	अचिन्हित	panic_indicator : 1;
	अचिन्हित	शेष_state : 2;
	अचिन्हित	retain_state_shutकरोwn : 1;
	/* शेष_state should be one of LEDS_GPIO_DEFSTATE_(ON|OFF|KEEP) */
	काष्ठा gpio_desc *gpiod;
पूर्ण;
#घोषणा LEDS_GPIO_DEFSTATE_OFF		0
#घोषणा LEDS_GPIO_DEFSTATE_ON		1
#घोषणा LEDS_GPIO_DEFSTATE_KEEP		2

काष्ठा gpio_led_platक्रमm_data अणु
	पूर्णांक 		num_leds;
	स्थिर काष्ठा gpio_led *leds;

#घोषणा GPIO_LED_NO_BLINK_LOW	0	/* No blink GPIO state low */
#घोषणा GPIO_LED_NO_BLINK_HIGH	1	/* No blink GPIO state high */
#घोषणा GPIO_LED_BLINK		2	/* Please, blink */
	gpio_blink_set_t	gpio_blink_set;
पूर्ण;

#अगर_घोषित CONFIG_NEW_LEDS
काष्ठा platक्रमm_device *gpio_led_रेजिस्टर_device(
		पूर्णांक id, स्थिर काष्ठा gpio_led_platक्रमm_data *pdata);
#अन्यथा
अटल अंतरभूत काष्ठा platक्रमm_device *gpio_led_रेजिस्टर_device(
		पूर्णांक id, स्थिर काष्ठा gpio_led_platक्रमm_data *pdata)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

क्रमागत cpu_led_event अणु
	CPU_LED_IDLE_START,	/* CPU enters idle */
	CPU_LED_IDLE_END,	/* CPU idle ends */
	CPU_LED_START,		/* Machine starts, especially resume */
	CPU_LED_STOP,		/* Machine stops, especially suspend */
	CPU_LED_HALTED,		/* Machine shutकरोwn */
पूर्ण;
#अगर_घोषित CONFIG_LEDS_TRIGGER_CPU
व्योम ledtrig_cpu(क्रमागत cpu_led_event evt);
#अन्यथा
अटल अंतरभूत व्योम ledtrig_cpu(क्रमागत cpu_led_event evt)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_LEDS_BRIGHTNESS_HW_CHANGED
व्योम led_classdev_notअगरy_brightness_hw_changed(
	काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक brightness);
#अन्यथा
अटल अंतरभूत व्योम led_classdev_notअगरy_brightness_hw_changed(
	काष्ठा led_classdev *led_cdev, क्रमागत led_brightness brightness) अणु पूर्ण
#पूर्ण_अगर

/**
 * काष्ठा led_pattern - pattern पूर्णांकerval settings
 * @delta_t: pattern पूर्णांकerval delay, in milliseconds
 * @brightness: pattern पूर्णांकerval brightness
 */
काष्ठा led_pattern अणु
	u32 delta_t;
	पूर्णांक brightness;
पूर्ण;

क्रमागत led_audio अणु
	LED_AUDIO_MUTE,		/* master mute LED */
	LED_AUDIO_MICMUTE,	/* mic mute LED */
	NUM_AUDIO_LEDS
पूर्ण;

#अगर IS_ENABLED(CONFIG_LEDS_TRIGGER_AUDIO)
क्रमागत led_brightness ledtrig_audio_get(क्रमागत led_audio type);
व्योम ledtrig_audio_set(क्रमागत led_audio type, क्रमागत led_brightness state);
#अन्यथा
अटल अंतरभूत क्रमागत led_brightness ledtrig_audio_get(क्रमागत led_audio type)
अणु
	वापस LED_OFF;
पूर्ण
अटल अंतरभूत व्योम ledtrig_audio_set(क्रमागत led_audio type,
				     क्रमागत led_brightness state)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर		/* __LINUX_LEDS_H_INCLUDED */
