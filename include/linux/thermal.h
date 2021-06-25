<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  thermal.h  ($Revision: 0 $)
 *
 *  Copyright (C) 2008  Intel Corp
 *  Copyright (C) 2008  Zhang Rui <rui.zhang@पूर्णांकel.com>
 *  Copyright (C) 2008  Sujith Thomas <sujith.thomas@पूर्णांकel.com>
 */

#अगर_अघोषित __THERMAL_H__
#घोषणा __THERMAL_H__

#समावेश <linux/of.h>
#समावेश <linux/idr.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/linux/thermal.h>

#घोषणा THERMAL_MAX_TRIPS	12

/* invalid cooling state */
#घोषणा THERMAL_CSTATE_INVALID -1UL

/* No upper/lower limit requirement */
#घोषणा THERMAL_NO_LIMIT	((u32)~0)

/* Default weight of a bound cooling device */
#घोषणा THERMAL_WEIGHT_DEFAULT 0

/* use value, which < 0K, to indicate an invalid/uninitialized temperature */
#घोषणा THERMAL_TEMP_INVALID	-274000

काष्ठा thermal_zone_device;
काष्ठा thermal_cooling_device;
काष्ठा thermal_instance;
काष्ठा thermal_attr;

क्रमागत thermal_trend अणु
	THERMAL_TREND_STABLE, /* temperature is stable */
	THERMAL_TREND_RAISING, /* temperature is raising */
	THERMAL_TREND_DROPPING, /* temperature is dropping */
	THERMAL_TREND_RAISE_FULL, /* apply highest cooling action */
	THERMAL_TREND_DROP_FULL, /* apply lowest cooling action */
पूर्ण;

/* Thermal notअगरication reason */
क्रमागत thermal_notअगरy_event अणु
	THERMAL_EVENT_UNSPECIFIED, /* Unspecअगरied event */
	THERMAL_EVENT_TEMP_SAMPLE, /* New Temperature sample */
	THERMAL_TRIP_VIOLATED, /* TRIP Poपूर्णांक violation */
	THERMAL_TRIP_CHANGED, /* TRIP Poपूर्णांक temperature changed */
	THERMAL_DEVICE_DOWN, /* Thermal device is करोwn */
	THERMAL_DEVICE_UP, /* Thermal device is up after a करोwn event */
	THERMAL_DEVICE_POWER_CAPABILITY_CHANGED, /* घातer capability changed */
	THERMAL_TABLE_CHANGED, /* Thermal table(s) changed */
	THERMAL_EVENT_KEEP_ALIVE, /* Request क्रम user space handler to respond */
पूर्ण;

काष्ठा thermal_zone_device_ops अणु
	पूर्णांक (*bind) (काष्ठा thermal_zone_device *,
		     काष्ठा thermal_cooling_device *);
	पूर्णांक (*unbind) (काष्ठा thermal_zone_device *,
		       काष्ठा thermal_cooling_device *);
	पूर्णांक (*get_temp) (काष्ठा thermal_zone_device *, पूर्णांक *);
	पूर्णांक (*set_trips) (काष्ठा thermal_zone_device *, पूर्णांक, पूर्णांक);
	पूर्णांक (*change_mode) (काष्ठा thermal_zone_device *,
		क्रमागत thermal_device_mode);
	पूर्णांक (*get_trip_type) (काष्ठा thermal_zone_device *, पूर्णांक,
		क्रमागत thermal_trip_type *);
	पूर्णांक (*get_trip_temp) (काष्ठा thermal_zone_device *, पूर्णांक, पूर्णांक *);
	पूर्णांक (*set_trip_temp) (काष्ठा thermal_zone_device *, पूर्णांक, पूर्णांक);
	पूर्णांक (*get_trip_hyst) (काष्ठा thermal_zone_device *, पूर्णांक, पूर्णांक *);
	पूर्णांक (*set_trip_hyst) (काष्ठा thermal_zone_device *, पूर्णांक, पूर्णांक);
	पूर्णांक (*get_crit_temp) (काष्ठा thermal_zone_device *, पूर्णांक *);
	पूर्णांक (*set_emul_temp) (काष्ठा thermal_zone_device *, पूर्णांक);
	पूर्णांक (*get_trend) (काष्ठा thermal_zone_device *, पूर्णांक,
			  क्रमागत thermal_trend *);
	व्योम (*hot)(काष्ठा thermal_zone_device *);
	व्योम (*critical)(काष्ठा thermal_zone_device *);
पूर्ण;

काष्ठा thermal_cooling_device_ops अणु
	पूर्णांक (*get_max_state) (काष्ठा thermal_cooling_device *, अचिन्हित दीर्घ *);
	पूर्णांक (*get_cur_state) (काष्ठा thermal_cooling_device *, अचिन्हित दीर्घ *);
	पूर्णांक (*set_cur_state) (काष्ठा thermal_cooling_device *, अचिन्हित दीर्घ);
	पूर्णांक (*get_requested_घातer)(काष्ठा thermal_cooling_device *, u32 *);
	पूर्णांक (*state2घातer)(काष्ठा thermal_cooling_device *, अचिन्हित दीर्घ, u32 *);
	पूर्णांक (*घातer2state)(काष्ठा thermal_cooling_device *, u32, अचिन्हित दीर्घ *);
पूर्ण;

काष्ठा thermal_cooling_device अणु
	पूर्णांक id;
	अक्षर *type;
	काष्ठा device device;
	काष्ठा device_node *np;
	व्योम *devdata;
	व्योम *stats;
	स्थिर काष्ठा thermal_cooling_device_ops *ops;
	bool updated; /* true अगर the cooling device करोes not need update */
	काष्ठा mutex lock; /* protect thermal_instances list */
	काष्ठा list_head thermal_instances;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा thermal_zone_device - काष्ठाure क्रम a thermal zone
 * @id:		unique id number क्रम each thermal zone
 * @type:	the thermal zone device type
 * @device:	&काष्ठा device क्रम this thermal zone
 * @trip_temp_attrs:	attributes क्रम trip poपूर्णांकs क्रम sysfs: trip temperature
 * @trip_type_attrs:	attributes क्रम trip poपूर्णांकs क्रम sysfs: trip type
 * @trip_hyst_attrs:	attributes क्रम trip poपूर्णांकs क्रम sysfs: trip hysteresis
 * @mode:		current mode of this thermal zone
 * @devdata:	निजी poपूर्णांकer क्रम device निजी data
 * @trips:	number of trip poपूर्णांकs the thermal zone supports
 * @trips_disabled;	biपंचांगap क्रम disabled trips
 * @passive_delay_jअगरfies: number of jअगरfies to रुको between polls when
 *			perक्रमming passive cooling.
 * @polling_delay_jअगरfies: number of jअगरfies to रुको between polls when
 *			checking whether trip poपूर्णांकs have been crossed (0 क्रम
 *			पूर्णांकerrupt driven प्रणालीs)
 * @temperature:	current temperature.  This is only क्रम core code,
 *			drivers should use thermal_zone_get_temp() to get the
 *			current temperature
 * @last_temperature:	previous temperature पढ़ो
 * @emul_temperature:	emulated temperature when using CONFIG_THERMAL_EMULATION
 * @passive:		1 अगर you've crossed a passive trip poपूर्णांक, 0 otherwise.
 * @prev_low_trip:	the low current temperature अगर you've crossed a passive
			trip poपूर्णांक.
 * @prev_high_trip:	the above current temperature अगर you've crossed a
			passive trip poपूर्णांक.
 * @need_update:	अगर equals 1, thermal_zone_device_update needs to be invoked.
 * @ops:	operations this &thermal_zone_device supports
 * @tzp:	thermal zone parameters
 * @governor:	poपूर्णांकer to the governor क्रम this thermal zone
 * @governor_data:	निजी poपूर्णांकer क्रम governor data
 * @thermal_instances:	list of &काष्ठा thermal_instance of this thermal zone
 * @ida:	&काष्ठा ida to generate unique id क्रम this zone's cooling
 *		devices
 * @lock:	lock to protect thermal_instances list
 * @node:	node in thermal_tz_list (in thermal_core.c)
 * @poll_queue:	delayed work क्रम polling
 * @notअगरy_event: Last notअगरication event
 */
काष्ठा thermal_zone_device अणु
	पूर्णांक id;
	अक्षर type[THERMAL_NAME_LENGTH];
	काष्ठा device device;
	काष्ठा attribute_group trips_attribute_group;
	काष्ठा thermal_attr *trip_temp_attrs;
	काष्ठा thermal_attr *trip_type_attrs;
	काष्ठा thermal_attr *trip_hyst_attrs;
	क्रमागत thermal_device_mode mode;
	व्योम *devdata;
	पूर्णांक trips;
	अचिन्हित दीर्घ trips_disabled;	/* biपंचांगap क्रम disabled trips */
	अचिन्हित दीर्घ passive_delay_jअगरfies;
	अचिन्हित दीर्घ polling_delay_jअगरfies;
	पूर्णांक temperature;
	पूर्णांक last_temperature;
	पूर्णांक emul_temperature;
	पूर्णांक passive;
	पूर्णांक prev_low_trip;
	पूर्णांक prev_high_trip;
	atomic_t need_update;
	काष्ठा thermal_zone_device_ops *ops;
	काष्ठा thermal_zone_params *tzp;
	काष्ठा thermal_governor *governor;
	व्योम *governor_data;
	काष्ठा list_head thermal_instances;
	काष्ठा ida ida;
	काष्ठा mutex lock;
	काष्ठा list_head node;
	काष्ठा delayed_work poll_queue;
	क्रमागत thermal_notअगरy_event notअगरy_event;
पूर्ण;

/**
 * काष्ठा thermal_governor - काष्ठाure that holds thermal governor inक्रमmation
 * @name:	name of the governor
 * @bind_to_tz: callback called when binding to a thermal zone.  If it
 *		वापसs 0, the governor is bound to the thermal zone,
 *		otherwise it fails.
 * @unbind_from_tz:	callback called when a governor is unbound from a
 *			thermal zone.
 * @throttle:	callback called क्रम every trip poपूर्णांक even अगर temperature is
 *		below the trip poपूर्णांक temperature
 * @governor_list:	node in thermal_governor_list (in thermal_core.c)
 */
काष्ठा thermal_governor अणु
	अक्षर name[THERMAL_NAME_LENGTH];
	पूर्णांक (*bind_to_tz)(काष्ठा thermal_zone_device *tz);
	व्योम (*unbind_from_tz)(काष्ठा thermal_zone_device *tz);
	पूर्णांक (*throttle)(काष्ठा thermal_zone_device *tz, पूर्णांक trip);
	काष्ठा list_head	governor_list;
पूर्ण;

/* Structure that holds binding parameters क्रम a zone */
काष्ठा thermal_bind_params अणु
	काष्ठा thermal_cooling_device *cdev;

	/*
	 * This is a measure of 'how effectively these devices can
	 * cool 'this' thermal zone. It shall be determined by
	 * platक्रमm अक्षरacterization. This value is relative to the
	 * rest of the weights so a cooling device whose weight is
	 * द्विगुन that of another cooling device is twice as
	 * effective. See Documentation/driver-api/thermal/sysfs-api.rst क्रम more
	 * inक्रमmation.
	 */
	पूर्णांक weight;

	/*
	 * This is a bit mask that gives the binding relation between this
	 * thermal zone and cdev, क्रम a particular trip poपूर्णांक.
	 * See Documentation/driver-api/thermal/sysfs-api.rst क्रम more inक्रमmation.
	 */
	पूर्णांक trip_mask;

	/*
	 * This is an array of cooling state limits. Must have exactly
	 * 2 * thermal_zone.number_of_trip_poपूर्णांकs. It is an array consisting
	 * of tuples <lower-state upper-state> of state limits. Each trip
	 * will be associated with one state limit tuple when binding.
	 * A शून्य poपूर्णांकer means <THERMAL_NO_LIMITS THERMAL_NO_LIMITS>
	 * on all trips.
	 */
	अचिन्हित दीर्घ *binding_limits;
	पूर्णांक (*match) (काष्ठा thermal_zone_device *tz,
			काष्ठा thermal_cooling_device *cdev);
पूर्ण;

/* Structure to define Thermal Zone parameters */
काष्ठा thermal_zone_params अणु
	अक्षर governor_name[THERMAL_NAME_LENGTH];

	/*
	 * a boolean to indicate अगर the thermal to hwmon sysfs पूर्णांकerface
	 * is required. when no_hwmon == false, a hwmon sysfs पूर्णांकerface
	 * will be created. when no_hwmon == true, nothing will be करोne
	 */
	bool no_hwmon;

	पूर्णांक num_tbps;	/* Number of tbp entries */
	काष्ठा thermal_bind_params *tbp;

	/*
	 * Sustainable घातer (heat) that this thermal zone can dissipate in
	 * mW
	 */
	u32 sustainable_घातer;

	/*
	 * Proportional parameter of the PID controller when
	 * overshooting (i.e., when temperature is below the target)
	 */
	s32 k_po;

	/*
	 * Proportional parameter of the PID controller when
	 * undershooting
	 */
	s32 k_pu;

	/* Integral parameter of the PID controller */
	s32 k_i;

	/* Derivative parameter of the PID controller */
	s32 k_d;

	/* threshold below which the error is no दीर्घer accumulated */
	s32 पूर्णांकegral_cutoff;

	/*
	 * @slope:	slope of a linear temperature adjusपंचांगent curve.
	 * 		Used by thermal zone drivers.
	 */
	पूर्णांक slope;
	/*
	 * @offset:	offset of a linear temperature adjusपंचांगent curve.
	 * 		Used by thermal zone drivers (शेष 0).
	 */
	पूर्णांक offset;
पूर्ण;

/**
 * काष्ठा thermal_zone_of_device_ops - scallbacks क्रम handling DT based zones
 *
 * Mandatory:
 * @get_temp: a poपूर्णांकer to a function that पढ़ोs the sensor temperature.
 *
 * Optional:
 * @get_trend: a poपूर्णांकer to a function that पढ़ोs the sensor temperature trend.
 * @set_trips: a poपूर्णांकer to a function that sets a temperature winकरोw. When
 *	       this winकरोw is left the driver must inक्रमm the thermal core via
 *	       thermal_zone_device_update.
 * @set_emul_temp: a poपूर्णांकer to a function that sets sensor emulated
 *		   temperature.
 * @set_trip_temp: a poपूर्णांकer to a function that sets the trip temperature on
 *		   hardware.
 */
काष्ठा thermal_zone_of_device_ops अणु
	पूर्णांक (*get_temp)(व्योम *, पूर्णांक *);
	पूर्णांक (*get_trend)(व्योम *, पूर्णांक, क्रमागत thermal_trend *);
	पूर्णांक (*set_trips)(व्योम *, पूर्णांक, पूर्णांक);
	पूर्णांक (*set_emul_temp)(व्योम *, पूर्णांक);
	पूर्णांक (*set_trip_temp)(व्योम *, पूर्णांक, पूर्णांक);
पूर्ण;

/* Function declarations */
#अगर_घोषित CONFIG_THERMAL_OF
पूर्णांक thermal_zone_of_get_sensor_id(काष्ठा device_node *tz_np,
				  काष्ठा device_node *sensor_np,
				  u32 *id);
काष्ठा thermal_zone_device *
thermal_zone_of_sensor_रेजिस्टर(काष्ठा device *dev, पूर्णांक id, व्योम *data,
				स्थिर काष्ठा thermal_zone_of_device_ops *ops);
व्योम thermal_zone_of_sensor_unरेजिस्टर(काष्ठा device *dev,
				       काष्ठा thermal_zone_device *tz);
काष्ठा thermal_zone_device *devm_thermal_zone_of_sensor_रेजिस्टर(
		काष्ठा device *dev, पूर्णांक id, व्योम *data,
		स्थिर काष्ठा thermal_zone_of_device_ops *ops);
व्योम devm_thermal_zone_of_sensor_unरेजिस्टर(काष्ठा device *dev,
					    काष्ठा thermal_zone_device *tz);
#अन्यथा

अटल अंतरभूत पूर्णांक thermal_zone_of_get_sensor_id(काष्ठा device_node *tz_np,
					 काष्ठा device_node *sensor_np,
					 u32 *id)
अणु
	वापस -ENOENT;
पूर्ण
अटल अंतरभूत काष्ठा thermal_zone_device *
thermal_zone_of_sensor_रेजिस्टर(काष्ठा device *dev, पूर्णांक id, व्योम *data,
				स्थिर काष्ठा thermal_zone_of_device_ops *ops)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत
व्योम thermal_zone_of_sensor_unरेजिस्टर(काष्ठा device *dev,
				       काष्ठा thermal_zone_device *tz)
अणु
पूर्ण

अटल अंतरभूत काष्ठा thermal_zone_device *devm_thermal_zone_of_sensor_रेजिस्टर(
		काष्ठा device *dev, पूर्णांक id, व्योम *data,
		स्थिर काष्ठा thermal_zone_of_device_ops *ops)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत
व्योम devm_thermal_zone_of_sensor_unरेजिस्टर(काष्ठा device *dev,
					    काष्ठा thermal_zone_device *tz)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_THERMAL
काष्ठा thermal_zone_device *thermal_zone_device_रेजिस्टर(स्थिर अक्षर *, पूर्णांक, पूर्णांक,
		व्योम *, काष्ठा thermal_zone_device_ops *,
		काष्ठा thermal_zone_params *, पूर्णांक, पूर्णांक);
व्योम thermal_zone_device_unरेजिस्टर(काष्ठा thermal_zone_device *);

पूर्णांक thermal_zone_bind_cooling_device(काष्ठा thermal_zone_device *, पूर्णांक,
				     काष्ठा thermal_cooling_device *,
				     अचिन्हित दीर्घ, अचिन्हित दीर्घ,
				     अचिन्हित पूर्णांक);
पूर्णांक thermal_zone_unbind_cooling_device(काष्ठा thermal_zone_device *, पूर्णांक,
				       काष्ठा thermal_cooling_device *);
व्योम thermal_zone_device_update(काष्ठा thermal_zone_device *,
				क्रमागत thermal_notअगरy_event);

काष्ठा thermal_cooling_device *thermal_cooling_device_रेजिस्टर(स्थिर अक्षर *,
		व्योम *, स्थिर काष्ठा thermal_cooling_device_ops *);
काष्ठा thermal_cooling_device *
thermal_of_cooling_device_रेजिस्टर(काष्ठा device_node *np, स्थिर अक्षर *, व्योम *,
				   स्थिर काष्ठा thermal_cooling_device_ops *);
काष्ठा thermal_cooling_device *
devm_thermal_of_cooling_device_रेजिस्टर(काष्ठा device *dev,
				काष्ठा device_node *np,
				अक्षर *type, व्योम *devdata,
				स्थिर काष्ठा thermal_cooling_device_ops *ops);
व्योम thermal_cooling_device_unरेजिस्टर(काष्ठा thermal_cooling_device *);
काष्ठा thermal_zone_device *thermal_zone_get_zone_by_name(स्थिर अक्षर *name);
पूर्णांक thermal_zone_get_temp(काष्ठा thermal_zone_device *tz, पूर्णांक *temp);
पूर्णांक thermal_zone_get_slope(काष्ठा thermal_zone_device *tz);
पूर्णांक thermal_zone_get_offset(काष्ठा thermal_zone_device *tz);

पूर्णांक thermal_zone_device_enable(काष्ठा thermal_zone_device *tz);
पूर्णांक thermal_zone_device_disable(काष्ठा thermal_zone_device *tz);
व्योम thermal_zone_device_critical(काष्ठा thermal_zone_device *tz);
#अन्यथा
अटल अंतरभूत काष्ठा thermal_zone_device *thermal_zone_device_रेजिस्टर(
	स्थिर अक्षर *type, पूर्णांक trips, पूर्णांक mask, व्योम *devdata,
	काष्ठा thermal_zone_device_ops *ops,
	काष्ठा thermal_zone_params *tzp,
	पूर्णांक passive_delay, पूर्णांक polling_delay)
अणु वापस ERR_PTR(-ENODEV); पूर्ण
अटल अंतरभूत व्योम thermal_zone_device_unरेजिस्टर(
	काष्ठा thermal_zone_device *tz)
अणु पूर्ण
अटल अंतरभूत काष्ठा thermal_cooling_device *
thermal_cooling_device_रेजिस्टर(अक्षर *type, व्योम *devdata,
	स्थिर काष्ठा thermal_cooling_device_ops *ops)
अणु वापस ERR_PTR(-ENODEV); पूर्ण
अटल अंतरभूत काष्ठा thermal_cooling_device *
thermal_of_cooling_device_रेजिस्टर(काष्ठा device_node *np,
	अक्षर *type, व्योम *devdata, स्थिर काष्ठा thermal_cooling_device_ops *ops)
अणु वापस ERR_PTR(-ENODEV); पूर्ण
अटल अंतरभूत काष्ठा thermal_cooling_device *
devm_thermal_of_cooling_device_रेजिस्टर(काष्ठा device *dev,
				काष्ठा device_node *np,
				अक्षर *type, व्योम *devdata,
				स्थिर काष्ठा thermal_cooling_device_ops *ops)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
अटल अंतरभूत व्योम thermal_cooling_device_unरेजिस्टर(
	काष्ठा thermal_cooling_device *cdev)
अणु पूर्ण
अटल अंतरभूत काष्ठा thermal_zone_device *thermal_zone_get_zone_by_name(
		स्थिर अक्षर *name)
अणु वापस ERR_PTR(-ENODEV); पूर्ण
अटल अंतरभूत पूर्णांक thermal_zone_get_temp(
		काष्ठा thermal_zone_device *tz, पूर्णांक *temp)
अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक thermal_zone_get_slope(
		काष्ठा thermal_zone_device *tz)
अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक thermal_zone_get_offset(
		काष्ठा thermal_zone_device *tz)
अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत पूर्णांक thermal_zone_device_enable(काष्ठा thermal_zone_device *tz)
अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत पूर्णांक thermal_zone_device_disable(काष्ठा thermal_zone_device *tz)
अणु वापस -ENODEV; पूर्ण
#पूर्ण_अगर /* CONFIG_THERMAL */

#पूर्ण_अगर /* __THERMAL_H__ */
