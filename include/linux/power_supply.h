<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Universal घातer supply monitor class
 *
 *  Copyright तऊ 2007  Anton Vorontsov <cbou@mail.ru>
 *  Copyright तऊ 2004  Szabolcs Gyurko
 *  Copyright तऊ 2003  Ian Molton <spyro@f2s.com>
 *
 *  Modअगरied: 2004, Oct     Szabolcs Gyurko
 */

#अगर_अघोषित __LINUX_POWER_SUPPLY_H__
#घोषणा __LINUX_POWER_SUPPLY_H__

#समावेश <linux/device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/leds.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/notअगरier.h>

/*
 * All voltages, currents, अक्षरges, energies, समय and temperatures in uV,
 * तगA, तगAh, तगWh, seconds and tenths of degree Celsius unless otherwise
 * stated. It's driver's job to convert its raw values to units in which
 * this class operates.
 */

/*
 * For प्रणालीs where the अक्षरger determines the maximum battery capacity
 * the min and max fields should be used to present these values to user
 * space. Unused/unknown fields will not appear in sysfs.
 */

क्रमागत अणु
	POWER_SUPPLY_STATUS_UNKNOWN = 0,
	POWER_SUPPLY_STATUS_CHARGING,
	POWER_SUPPLY_STATUS_DISCHARGING,
	POWER_SUPPLY_STATUS_NOT_CHARGING,
	POWER_SUPPLY_STATUS_FULL,
पूर्ण;

/* What algorithm is the अक्षरger using? */
क्रमागत अणु
	POWER_SUPPLY_CHARGE_TYPE_UNKNOWN = 0,
	POWER_SUPPLY_CHARGE_TYPE_NONE,
	POWER_SUPPLY_CHARGE_TYPE_TRICKLE,	/* slow speed */
	POWER_SUPPLY_CHARGE_TYPE_FAST,		/* fast speed */
	POWER_SUPPLY_CHARGE_TYPE_STANDARD,	/* normal speed */
	POWER_SUPPLY_CHARGE_TYPE_ADAPTIVE,	/* dynamically adjusted speed */
	POWER_SUPPLY_CHARGE_TYPE_CUSTOM,	/* use CHARGE_CONTROL_* props */
	POWER_SUPPLY_CHARGE_TYPE_LONGLIFE,	/* slow speed, दीर्घer lअगरe */
पूर्ण;

क्रमागत अणु
	POWER_SUPPLY_HEALTH_UNKNOWN = 0,
	POWER_SUPPLY_HEALTH_GOOD,
	POWER_SUPPLY_HEALTH_OVERHEAT,
	POWER_SUPPLY_HEALTH_DEAD,
	POWER_SUPPLY_HEALTH_OVERVOLTAGE,
	POWER_SUPPLY_HEALTH_UNSPEC_FAILURE,
	POWER_SUPPLY_HEALTH_COLD,
	POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE,
	POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE,
	POWER_SUPPLY_HEALTH_OVERCURRENT,
	POWER_SUPPLY_HEALTH_CALIBRATION_REQUIRED,
	POWER_SUPPLY_HEALTH_WARM,
	POWER_SUPPLY_HEALTH_COOL,
	POWER_SUPPLY_HEALTH_HOT,
पूर्ण;

क्रमागत अणु
	POWER_SUPPLY_TECHNOLOGY_UNKNOWN = 0,
	POWER_SUPPLY_TECHNOLOGY_NiMH,
	POWER_SUPPLY_TECHNOLOGY_LION,
	POWER_SUPPLY_TECHNOLOGY_LIPO,
	POWER_SUPPLY_TECHNOLOGY_LiFe,
	POWER_SUPPLY_TECHNOLOGY_NiCd,
	POWER_SUPPLY_TECHNOLOGY_LiMn,
पूर्ण;

क्रमागत अणु
	POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN = 0,
	POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL,
	POWER_SUPPLY_CAPACITY_LEVEL_LOW,
	POWER_SUPPLY_CAPACITY_LEVEL_NORMAL,
	POWER_SUPPLY_CAPACITY_LEVEL_HIGH,
	POWER_SUPPLY_CAPACITY_LEVEL_FULL,
पूर्ण;

क्रमागत अणु
	POWER_SUPPLY_SCOPE_UNKNOWN = 0,
	POWER_SUPPLY_SCOPE_SYSTEM,
	POWER_SUPPLY_SCOPE_DEVICE,
पूर्ण;

क्रमागत घातer_supply_property अणु
	/* Properties of type `पूर्णांक' */
	POWER_SUPPLY_PROP_STATUS = 0,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_AUTHENTIC,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_VOLTAGE_MIN,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_VOLTAGE_OCV,
	POWER_SUPPLY_PROP_VOLTAGE_BOOT,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CURRENT_BOOT,
	POWER_SUPPLY_PROP_POWER_NOW,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_EMPTY,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_AVG,
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_START_THRESHOLD, /* in percents! */
	POWER_SUPPLY_PROP_CHARGE_CONTROL_END_THRESHOLD, /* in percents! */
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT,
	POWER_SUPPLY_PROP_INPUT_POWER_LIMIT,
	POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN,
	POWER_SUPPLY_PROP_ENERGY_EMPTY_DESIGN,
	POWER_SUPPLY_PROP_ENERGY_FULL,
	POWER_SUPPLY_PROP_ENERGY_EMPTY,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_ENERGY_AVG,
	POWER_SUPPLY_PROP_CAPACITY, /* in percents! */
	POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN, /* in percents! */
	POWER_SUPPLY_PROP_CAPACITY_ALERT_MAX, /* in percents! */
	POWER_SUPPLY_PROP_CAPACITY_ERROR_MARGIN, /* in percents! */
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TEMP_MAX,
	POWER_SUPPLY_PROP_TEMP_MIN,
	POWER_SUPPLY_PROP_TEMP_ALERT_MIN,
	POWER_SUPPLY_PROP_TEMP_ALERT_MAX,
	POWER_SUPPLY_PROP_TEMP_AMBIENT,
	POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN,
	POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TIME_TO_FULL_AVG,
	POWER_SUPPLY_PROP_TYPE, /* use घातer_supply.type instead */
	POWER_SUPPLY_PROP_USB_TYPE,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_PRECHARGE_CURRENT,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
	POWER_SUPPLY_PROP_CALIBRATE,
	POWER_SUPPLY_PROP_MANUFACTURE_YEAR,
	POWER_SUPPLY_PROP_MANUFACTURE_MONTH,
	POWER_SUPPLY_PROP_MANUFACTURE_DAY,
	/* Properties of type `स्थिर अक्षर *' */
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
पूर्ण;

क्रमागत घातer_supply_type अणु
	POWER_SUPPLY_TYPE_UNKNOWN = 0,
	POWER_SUPPLY_TYPE_BATTERY,
	POWER_SUPPLY_TYPE_UPS,
	POWER_SUPPLY_TYPE_MAINS,
	POWER_SUPPLY_TYPE_USB,			/* Standard Downstream Port */
	POWER_SUPPLY_TYPE_USB_DCP,		/* Dedicated Charging Port */
	POWER_SUPPLY_TYPE_USB_CDP,		/* Charging Downstream Port */
	POWER_SUPPLY_TYPE_USB_ACA,		/* Accessory Charger Adapters */
	POWER_SUPPLY_TYPE_USB_TYPE_C,		/* Type C Port */
	POWER_SUPPLY_TYPE_USB_PD,		/* Power Delivery Port */
	POWER_SUPPLY_TYPE_USB_PD_DRP,		/* PD Dual Role Port */
	POWER_SUPPLY_TYPE_APPLE_BRICK_ID,	/* Apple Charging Method */
	POWER_SUPPLY_TYPE_WIRELESS,		/* Wireless */
पूर्ण;

क्रमागत घातer_supply_usb_type अणु
	POWER_SUPPLY_USB_TYPE_UNKNOWN = 0,
	POWER_SUPPLY_USB_TYPE_SDP,		/* Standard Downstream Port */
	POWER_SUPPLY_USB_TYPE_DCP,		/* Dedicated Charging Port */
	POWER_SUPPLY_USB_TYPE_CDP,		/* Charging Downstream Port */
	POWER_SUPPLY_USB_TYPE_ACA,		/* Accessory Charger Adapters */
	POWER_SUPPLY_USB_TYPE_C,		/* Type C Port */
	POWER_SUPPLY_USB_TYPE_PD,		/* Power Delivery Port */
	POWER_SUPPLY_USB_TYPE_PD_DRP,		/* PD Dual Role Port */
	POWER_SUPPLY_USB_TYPE_PD_PPS,		/* PD Programmable Power Supply */
	POWER_SUPPLY_USB_TYPE_APPLE_BRICK_ID,	/* Apple Charging Method */
पूर्ण;

क्रमागत घातer_supply_notअगरier_events अणु
	PSY_EVENT_PROP_CHANGED,
पूर्ण;

जोड़ घातer_supply_propval अणु
	पूर्णांक पूर्णांकval;
	स्थिर अक्षर *strval;
पूर्ण;

काष्ठा device_node;
काष्ठा घातer_supply;

/* Run-समय specअगरic घातer supply configuration */
काष्ठा घातer_supply_config अणु
	काष्ठा device_node *of_node;
	काष्ठा fwnode_handle *fwnode;

	/* Driver निजी data */
	व्योम *drv_data;

	/* Device specअगरic sysfs attributes */
	स्थिर काष्ठा attribute_group **attr_grp;

	अक्षर **supplied_to;
	माप_प्रकार num_supplicants;
पूर्ण;

/* Description of घातer supply */
काष्ठा घातer_supply_desc अणु
	स्थिर अक्षर *name;
	क्रमागत घातer_supply_type type;
	स्थिर क्रमागत घातer_supply_usb_type *usb_types;
	माप_प्रकार num_usb_types;
	स्थिर क्रमागत घातer_supply_property *properties;
	माप_प्रकार num_properties;

	/*
	 * Functions क्रम drivers implementing घातer supply class.
	 * These shouldn't be called directly by other drivers क्रम accessing
	 * this घातer supply. Instead use घातer_supply_*() functions (क्रम
	 * example घातer_supply_get_property()).
	 */
	पूर्णांक (*get_property)(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val);
	पूर्णांक (*set_property)(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    स्थिर जोड़ घातer_supply_propval *val);
	/*
	 * property_is_ग_लिखोable() will be called during registration
	 * of घातer supply. If this happens during device probe then it must
	 * not access पूर्णांकernal data of device (because probe did not end).
	 */
	पूर्णांक (*property_is_ग_लिखोable)(काष्ठा घातer_supply *psy,
				     क्रमागत घातer_supply_property psp);
	व्योम (*बाह्यal_घातer_changed)(काष्ठा घातer_supply *psy);
	व्योम (*set_अक्षरged)(काष्ठा घातer_supply *psy);

	/*
	 * Set अगर thermal zone should not be created क्रम this घातer supply.
	 * For example क्रम भव supplies क्रमwarding calls to actual
	 * sensors or other supplies.
	 */
	bool no_thermal;
	/* For APM emulation, think legacy userspace. */
	पूर्णांक use_क्रम_apm;
पूर्ण;

काष्ठा घातer_supply अणु
	स्थिर काष्ठा घातer_supply_desc *desc;

	अक्षर **supplied_to;
	माप_प्रकार num_supplicants;

	अक्षर **supplied_from;
	माप_प्रकार num_supplies;
	काष्ठा device_node *of_node;

	/* Driver निजी data */
	व्योम *drv_data;

	/* निजी */
	काष्ठा device dev;
	काष्ठा work_काष्ठा changed_work;
	काष्ठा delayed_work deferred_रेजिस्टर_work;
	spinlock_t changed_lock;
	bool changed;
	bool initialized;
	bool removing;
	atomic_t use_cnt;
#अगर_घोषित CONFIG_THERMAL
	काष्ठा thermal_zone_device *tzd;
	काष्ठा thermal_cooling_device *tcd;
#पूर्ण_अगर

#अगर_घोषित CONFIG_LEDS_TRIGGERS
	काष्ठा led_trigger *अक्षरging_full_trig;
	अक्षर *अक्षरging_full_trig_name;
	काष्ठा led_trigger *अक्षरging_trig;
	अक्षर *अक्षरging_trig_name;
	काष्ठा led_trigger *full_trig;
	अक्षर *full_trig_name;
	काष्ठा led_trigger *online_trig;
	अक्षर *online_trig_name;
	काष्ठा led_trigger *अक्षरging_blink_full_solid_trig;
	अक्षर *अक्षरging_blink_full_solid_trig_name;
#पूर्ण_अगर
पूर्ण;

/*
 * This is recommended काष्ठाure to specअगरy अटल घातer supply parameters.
 * Generic one, parametrizable क्रम dअगरferent घातer supplies. Power supply
 * class itself करोes not use it, but that's what implementing most platक्रमm
 * drivers, should try reuse क्रम consistency.
 */

काष्ठा घातer_supply_info अणु
	स्थिर अक्षर *name;
	पूर्णांक technology;
	पूर्णांक voltage_max_design;
	पूर्णांक voltage_min_design;
	पूर्णांक अक्षरge_full_design;
	पूर्णांक अक्षरge_empty_design;
	पूर्णांक energy_full_design;
	पूर्णांक energy_empty_design;
	पूर्णांक use_क्रम_apm;
पूर्ण;

काष्ठा घातer_supply_battery_ocv_table अणु
	पूर्णांक ocv;	/* microVolts */
	पूर्णांक capacity;	/* percent */
पूर्ण;

काष्ठा घातer_supply_resistance_temp_table अणु
	पूर्णांक temp;	/* celsius */
	पूर्णांक resistance;	/* पूर्णांकernal resistance percent */
पूर्ण;

#घोषणा POWER_SUPPLY_OCV_TEMP_MAX 20

/*
 * This is the recommended काष्ठा to manage अटल battery parameters,
 * populated by घातer_supply_get_battery_info(). Most platक्रमm drivers should
 * use these क्रम consistency.
 * Its field names must correspond to elements in क्रमागत घातer_supply_property.
 * The शेष field value is -EINVAL.
 * Power supply class itself करोesn't use this.
 */

काष्ठा घातer_supply_battery_info अणु
	पूर्णांक energy_full_design_uwh;	    /* microWatt-hours */
	पूर्णांक अक्षरge_full_design_uah;	    /* microAmp-hours */
	पूर्णांक voltage_min_design_uv;	    /* microVolts */
	पूर्णांक voltage_max_design_uv;	    /* microVolts */
	पूर्णांक trickleअक्षरge_current_ua;	    /* microAmps */
	पूर्णांक preअक्षरge_current_ua;	    /* microAmps */
	पूर्णांक preअक्षरge_voltage_max_uv;	    /* microVolts */
	पूर्णांक अक्षरge_term_current_ua;	    /* microAmps */
	पूर्णांक अक्षरge_restart_voltage_uv;	    /* microVolts */
	पूर्णांक overvoltage_limit_uv;	    /* microVolts */
	पूर्णांक स्थिरant_अक्षरge_current_max_ua; /* microAmps */
	पूर्णांक स्थिरant_अक्षरge_voltage_max_uv; /* microVolts */
	पूर्णांक factory_पूर्णांकernal_resistance_uohm;   /* microOhms */
	पूर्णांक ocv_temp[POWER_SUPPLY_OCV_TEMP_MAX];/* celsius */
	पूर्णांक temp_ambient_alert_min;             /* celsius */
	पूर्णांक temp_ambient_alert_max;             /* celsius */
	पूर्णांक temp_alert_min;                     /* celsius */
	पूर्णांक temp_alert_max;                     /* celsius */
	पूर्णांक temp_min;                           /* celsius */
	पूर्णांक temp_max;                           /* celsius */
	काष्ठा घातer_supply_battery_ocv_table *ocv_table[POWER_SUPPLY_OCV_TEMP_MAX];
	पूर्णांक ocv_table_size[POWER_SUPPLY_OCV_TEMP_MAX];
	काष्ठा घातer_supply_resistance_temp_table *resist_table;
	पूर्णांक resist_table_size;
पूर्ण;

बाह्य काष्ठा atomic_notअगरier_head घातer_supply_notअगरier;
बाह्य पूर्णांक घातer_supply_reg_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य व्योम घातer_supply_unreg_notअगरier(काष्ठा notअगरier_block *nb);
#अगर IS_ENABLED(CONFIG_POWER_SUPPLY)
बाह्य काष्ठा घातer_supply *घातer_supply_get_by_name(स्थिर अक्षर *name);
बाह्य व्योम घातer_supply_put(काष्ठा घातer_supply *psy);
#अन्यथा
अटल अंतरभूत व्योम घातer_supply_put(काष्ठा घातer_supply *psy) अणुपूर्ण
अटल अंतरभूत काष्ठा घातer_supply *घातer_supply_get_by_name(स्थिर अक्षर *name)
अणु वापस शून्य; पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_OF
बाह्य काष्ठा घातer_supply *घातer_supply_get_by_phandle(काष्ठा device_node *np,
							स्थिर अक्षर *property);
बाह्य काष्ठा घातer_supply *devm_घातer_supply_get_by_phandle(
				    काष्ठा device *dev, स्थिर अक्षर *property);
#अन्यथा /* !CONFIG_OF */
अटल अंतरभूत काष्ठा घातer_supply *
घातer_supply_get_by_phandle(काष्ठा device_node *np, स्थिर अक्षर *property)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा घातer_supply *
devm_घातer_supply_get_by_phandle(काष्ठा device *dev, स्थिर अक्षर *property)
अणु वापस शून्य; पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

बाह्य पूर्णांक घातer_supply_get_battery_info(काष्ठा घातer_supply *psy,
					 काष्ठा घातer_supply_battery_info *info);
बाह्य व्योम घातer_supply_put_battery_info(काष्ठा घातer_supply *psy,
					  काष्ठा घातer_supply_battery_info *info);
बाह्य पूर्णांक घातer_supply_ocv2cap_simple(काष्ठा घातer_supply_battery_ocv_table *table,
				       पूर्णांक table_len, पूर्णांक ocv);
बाह्य काष्ठा घातer_supply_battery_ocv_table *
घातer_supply_find_ocv2cap_table(काष्ठा घातer_supply_battery_info *info,
				पूर्णांक temp, पूर्णांक *table_len);
बाह्य पूर्णांक घातer_supply_batinfo_ocv2cap(काष्ठा घातer_supply_battery_info *info,
					पूर्णांक ocv, पूर्णांक temp);
बाह्य पूर्णांक
घातer_supply_temp2resist_simple(काष्ठा घातer_supply_resistance_temp_table *table,
				पूर्णांक table_len, पूर्णांक temp);
बाह्य व्योम घातer_supply_changed(काष्ठा घातer_supply *psy);
बाह्य पूर्णांक घातer_supply_am_i_supplied(काष्ठा घातer_supply *psy);
बाह्य पूर्णांक घातer_supply_set_input_current_limit_from_supplier(
					 काष्ठा घातer_supply *psy);
बाह्य पूर्णांक घातer_supply_set_battery_अक्षरged(काष्ठा घातer_supply *psy);

#अगर_घोषित CONFIG_POWER_SUPPLY
बाह्य पूर्णांक घातer_supply_is_प्रणाली_supplied(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक घातer_supply_is_प्रणाली_supplied(व्योम) अणु वापस -ENOSYS; पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक घातer_supply_get_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val);
#अगर IS_ENABLED(CONFIG_POWER_SUPPLY)
बाह्य पूर्णांक घातer_supply_set_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    स्थिर जोड़ घातer_supply_propval *val);
#अन्यथा
अटल अंतरभूत पूर्णांक घातer_supply_set_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    स्थिर जोड़ घातer_supply_propval *val)
अणु वापस 0; पूर्ण
#पूर्ण_अगर
बाह्य पूर्णांक घातer_supply_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp);
बाह्य व्योम घातer_supply_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy);

बाह्य काष्ठा घातer_supply *__must_check
घातer_supply_रेजिस्टर(काष्ठा device *parent,
				 स्थिर काष्ठा घातer_supply_desc *desc,
				 स्थिर काष्ठा घातer_supply_config *cfg);
बाह्य काष्ठा घातer_supply *__must_check
घातer_supply_रेजिस्टर_no_ws(काष्ठा device *parent,
				 स्थिर काष्ठा घातer_supply_desc *desc,
				 स्थिर काष्ठा घातer_supply_config *cfg);
बाह्य काष्ठा घातer_supply *__must_check
devm_घातer_supply_रेजिस्टर(काष्ठा device *parent,
				 स्थिर काष्ठा घातer_supply_desc *desc,
				 स्थिर काष्ठा घातer_supply_config *cfg);
बाह्य काष्ठा घातer_supply *__must_check
devm_घातer_supply_रेजिस्टर_no_ws(काष्ठा device *parent,
				 स्थिर काष्ठा घातer_supply_desc *desc,
				 स्थिर काष्ठा घातer_supply_config *cfg);
बाह्य व्योम घातer_supply_unरेजिस्टर(काष्ठा घातer_supply *psy);
बाह्य पूर्णांक घातer_supply_घातers(काष्ठा घातer_supply *psy, काष्ठा device *dev);

#घोषणा to_घातer_supply(device) container_of(device, काष्ठा घातer_supply, dev)

बाह्य व्योम *घातer_supply_get_drvdata(काष्ठा घातer_supply *psy);
/* For APM emulation, think legacy userspace. */
बाह्य काष्ठा class *घातer_supply_class;

अटल अंतरभूत bool घातer_supply_is_amp_property(क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
	हाल POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN:
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
	हाल POWER_SUPPLY_PROP_CHARGE_EMPTY:
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
	हाल POWER_SUPPLY_PROP_CHARGE_AVG:
	हाल POWER_SUPPLY_PROP_CHARGE_COUNTER:
	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
	हाल POWER_SUPPLY_PROP_CURRENT_BOOT:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत bool घातer_supply_is_watt_property(क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
	हाल POWER_SUPPLY_PROP_ENERGY_EMPTY_DESIGN:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL:
	हाल POWER_SUPPLY_PROP_ENERGY_EMPTY:
	हाल POWER_SUPPLY_PROP_ENERGY_NOW:
	हाल POWER_SUPPLY_PROP_ENERGY_AVG:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
	हाल POWER_SUPPLY_PROP_VOLTAGE_OCV:
	हाल POWER_SUPPLY_PROP_VOLTAGE_BOOT:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
	हाल POWER_SUPPLY_PROP_POWER_NOW:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_POWER_SUPPLY_HWMON
पूर्णांक घातer_supply_add_hwmon_sysfs(काष्ठा घातer_supply *psy);
व्योम घातer_supply_हटाओ_hwmon_sysfs(काष्ठा घातer_supply *psy);
#अन्यथा
अटल अंतरभूत पूर्णांक घातer_supply_add_hwmon_sysfs(काष्ठा घातer_supply *psy)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम घातer_supply_हटाओ_hwmon_sysfs(काष्ठा घातer_supply *psy) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_POWER_SUPPLY_H__ */
