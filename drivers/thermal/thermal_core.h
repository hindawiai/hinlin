<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  thermal_core.h
 *
 *  Copyright (C) 2012  Intel Corp
 *  Author: Durgaकरोss R <durgaकरोss.r@पूर्णांकel.com>
 */

#अगर_अघोषित __THERMAL_CORE_H__
#घोषणा __THERMAL_CORE_H__

#समावेश <linux/device.h>
#समावेश <linux/thermal.h>

#समावेश "thermal_netlink.h"

/* Default Thermal Governor */
#अगर defined(CONFIG_THERMAL_DEFAULT_GOV_STEP_WISE)
#घोषणा DEFAULT_THERMAL_GOVERNOR       "step_wise"
#या_अगर defined(CONFIG_THERMAL_DEFAULT_GOV_FAIR_SHARE)
#घोषणा DEFAULT_THERMAL_GOVERNOR       "fair_share"
#या_अगर defined(CONFIG_THERMAL_DEFAULT_GOV_USER_SPACE)
#घोषणा DEFAULT_THERMAL_GOVERNOR       "user_space"
#या_अगर defined(CONFIG_THERMAL_DEFAULT_GOV_POWER_ALLOCATOR)
#घोषणा DEFAULT_THERMAL_GOVERNOR       "power_allocator"
#पूर्ण_अगर

/* Initial state of a cooling device during binding */
#घोषणा THERMAL_NO_TARGET -1UL

/* Init section thermal table */
बाह्य काष्ठा thermal_governor *__governor_thermal_table[];
बाह्य काष्ठा thermal_governor *__governor_thermal_table_end[];

#घोषणा THERMAL_TABLE_ENTRY(table, name)			\
	अटल typeof(name) *__thermal_table_entry_##name	\
	__used __section("__" #table "_thermal_table") = &name

#घोषणा THERMAL_GOVERNOR_DECLARE(name)	THERMAL_TABLE_ENTRY(governor, name)

#घोषणा क्रम_each_governor_table(__governor)		\
	क्रम (__governor = __governor_thermal_table;	\
	     __governor < __governor_thermal_table_end;	\
	     __governor++)

पूर्णांक क्रम_each_thermal_zone(पूर्णांक (*cb)(काष्ठा thermal_zone_device *, व्योम *),
			  व्योम *);

पूर्णांक क्रम_each_thermal_cooling_device(पूर्णांक (*cb)(काष्ठा thermal_cooling_device *,
					      व्योम *), व्योम *);

पूर्णांक क्रम_each_thermal_governor(पूर्णांक (*cb)(काष्ठा thermal_governor *, व्योम *),
			      व्योम *thermal_governor);

काष्ठा thermal_zone_device *thermal_zone_get_by_id(पूर्णांक id);

काष्ठा thermal_attr अणु
	काष्ठा device_attribute attr;
	अक्षर name[THERMAL_NAME_LENGTH];
पूर्ण;

अटल अंतरभूत bool cdev_is_घातer_actor(काष्ठा thermal_cooling_device *cdev)
अणु
	वापस cdev->ops->get_requested_घातer && cdev->ops->state2घातer &&
		cdev->ops->घातer2state;
पूर्ण

व्योम thermal_cdev_update(काष्ठा thermal_cooling_device *);
व्योम __thermal_cdev_update(काष्ठा thermal_cooling_device *cdev);

/**
 * काष्ठा thermal_trip - representation of a poपूर्णांक in temperature करोमुख्य
 * @np: poपूर्णांकer to काष्ठा device_node that this trip poपूर्णांक was created from
 * @temperature: temperature value in miliCelsius
 * @hysteresis: relative hysteresis in miliCelsius
 * @type: trip poपूर्णांक type
 */
काष्ठा thermal_trip अणु
	काष्ठा device_node *np;
	पूर्णांक temperature;
	पूर्णांक hysteresis;
	क्रमागत thermal_trip_type type;
पूर्ण;

पूर्णांक get_tz_trend(काष्ठा thermal_zone_device *tz, पूर्णांक trip);

काष्ठा thermal_instance *
get_thermal_instance(काष्ठा thermal_zone_device *tz,
		     काष्ठा thermal_cooling_device *cdev,
		     पूर्णांक trip);

/*
 * This काष्ठाure is used to describe the behavior of
 * a certain cooling device on a certain trip poपूर्णांक
 * in a certain thermal zone
 */
काष्ठा thermal_instance अणु
	पूर्णांक id;
	अक्षर name[THERMAL_NAME_LENGTH];
	काष्ठा thermal_zone_device *tz;
	काष्ठा thermal_cooling_device *cdev;
	पूर्णांक trip;
	bool initialized;
	अचिन्हित दीर्घ upper;	/* Highest cooling state क्रम this trip poपूर्णांक */
	अचिन्हित दीर्घ lower;	/* Lowest cooling state क्रम this trip poपूर्णांक */
	अचिन्हित दीर्घ target;	/* expected cooling state */
	अक्षर attr_name[THERMAL_NAME_LENGTH];
	काष्ठा device_attribute attr;
	अक्षर weight_attr_name[THERMAL_NAME_LENGTH];
	काष्ठा device_attribute weight_attr;
	काष्ठा list_head tz_node; /* node in tz->thermal_instances */
	काष्ठा list_head cdev_node; /* node in cdev->thermal_instances */
	अचिन्हित पूर्णांक weight; /* The weight of the cooling device */
पूर्ण;

#घोषणा to_thermal_zone(_dev) \
	container_of(_dev, काष्ठा thermal_zone_device, device)

#घोषणा to_cooling_device(_dev)	\
	container_of(_dev, काष्ठा thermal_cooling_device, device)

पूर्णांक thermal_रेजिस्टर_governor(काष्ठा thermal_governor *);
व्योम thermal_unरेजिस्टर_governor(काष्ठा thermal_governor *);
पूर्णांक thermal_zone_device_set_policy(काष्ठा thermal_zone_device *, अक्षर *);
पूर्णांक thermal_build_list_of_policies(अक्षर *buf);

/* Helpers */
व्योम thermal_zone_set_trips(काष्ठा thermal_zone_device *tz);
व्योम thermal_set_delay_jअगरfies(अचिन्हित दीर्घ *delay_jअगरfies, पूर्णांक delay_ms);

/* sysfs I/F */
पूर्णांक thermal_zone_create_device_groups(काष्ठा thermal_zone_device *, पूर्णांक);
व्योम thermal_zone_destroy_device_groups(काष्ठा thermal_zone_device *);
व्योम thermal_cooling_device_setup_sysfs(काष्ठा thermal_cooling_device *);
व्योम thermal_cooling_device_destroy_sysfs(काष्ठा thermal_cooling_device *cdev);
/* used only at binding समय */
sमाप_प्रकार trip_poपूर्णांक_show(काष्ठा device *, काष्ठा device_attribute *, अक्षर *);
sमाप_प्रकार weight_show(काष्ठा device *, काष्ठा device_attribute *, अक्षर *);
sमाप_प्रकार weight_store(काष्ठा device *, काष्ठा device_attribute *, स्थिर अक्षर *,
		     माप_प्रकार);

#अगर_घोषित CONFIG_THERMAL_STATISTICS
व्योम thermal_cooling_device_stats_update(काष्ठा thermal_cooling_device *cdev,
					 अचिन्हित दीर्घ new_state);
#अन्यथा
अटल अंतरभूत व्योम
thermal_cooling_device_stats_update(काष्ठा thermal_cooling_device *cdev,
				    अचिन्हित दीर्घ new_state) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_THERMAL_STATISTICS */

/* device tree support */
#अगर_घोषित CONFIG_THERMAL_OF
पूर्णांक of_parse_thermal_zones(व्योम);
पूर्णांक of_thermal_get_ntrips(काष्ठा thermal_zone_device *);
bool of_thermal_is_trip_valid(काष्ठा thermal_zone_device *, पूर्णांक);
स्थिर काष्ठा thermal_trip *
of_thermal_get_trip_poपूर्णांकs(काष्ठा thermal_zone_device *);
#अन्यथा
अटल अंतरभूत पूर्णांक of_parse_thermal_zones(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक of_thermal_get_ntrips(काष्ठा thermal_zone_device *tz)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool of_thermal_is_trip_valid(काष्ठा thermal_zone_device *tz,
					    पूर्णांक trip)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत स्थिर काष्ठा thermal_trip *
of_thermal_get_trip_poपूर्णांकs(काष्ठा thermal_zone_device *tz)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

पूर्णांक thermal_zone_device_is_enabled(काष्ठा thermal_zone_device *tz);

#पूर्ण_अगर /* __THERMAL_CORE_H__ */
