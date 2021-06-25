<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) Linaro Ltd 2020
 *  Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 */

/* Netlink notअगरication function */
#अगर_घोषित CONFIG_THERMAL_NETLINK
पूर्णांक __init thermal_netlink_init(व्योम);
पूर्णांक thermal_notअगरy_tz_create(पूर्णांक tz_id, स्थिर अक्षर *name);
पूर्णांक thermal_notअगरy_tz_delete(पूर्णांक tz_id);
पूर्णांक thermal_notअगरy_tz_enable(पूर्णांक tz_id);
पूर्णांक thermal_notअगरy_tz_disable(पूर्णांक tz_id);
पूर्णांक thermal_notअगरy_tz_trip_करोwn(पूर्णांक tz_id, पूर्णांक id);
पूर्णांक thermal_notअगरy_tz_trip_up(पूर्णांक tz_id, पूर्णांक id);
पूर्णांक thermal_notअगरy_tz_trip_delete(पूर्णांक tz_id, पूर्णांक id);
पूर्णांक thermal_notअगरy_tz_trip_add(पूर्णांक tz_id, पूर्णांक id, पूर्णांक type,
			       पूर्णांक temp, पूर्णांक hyst);
पूर्णांक thermal_notअगरy_tz_trip_change(पूर्णांक tz_id, पूर्णांक id, पूर्णांक type,
				  पूर्णांक temp, पूर्णांक hyst);
पूर्णांक thermal_notअगरy_cdev_state_update(पूर्णांक cdev_id, पूर्णांक state);
पूर्णांक thermal_notअगरy_cdev_add(पूर्णांक cdev_id, स्थिर अक्षर *name, पूर्णांक max_state);
पूर्णांक thermal_notअगरy_cdev_delete(पूर्णांक cdev_id);
पूर्णांक thermal_notअगरy_tz_gov_change(पूर्णांक tz_id, स्थिर अक्षर *name);
पूर्णांक thermal_genl_sampling_temp(पूर्णांक id, पूर्णांक temp);
#अन्यथा
अटल अंतरभूत पूर्णांक thermal_netlink_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_tz_create(पूर्णांक tz_id, स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_tz_delete(पूर्णांक tz_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_tz_enable(पूर्णांक tz_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_tz_disable(पूर्णांक tz_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_tz_trip_करोwn(पूर्णांक tz_id, पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_tz_trip_up(पूर्णांक tz_id, पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_tz_trip_delete(पूर्णांक tz_id, पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_tz_trip_add(पूर्णांक tz_id, पूर्णांक id, पूर्णांक type,
					     पूर्णांक temp, पूर्णांक hyst)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_tz_trip_change(पूर्णांक tz_id, पूर्णांक id, पूर्णांक type,
						पूर्णांक temp, पूर्णांक hyst)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_cdev_state_update(पूर्णांक cdev_id, पूर्णांक state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_cdev_add(पूर्णांक cdev_id, स्थिर अक्षर *name,
					  पूर्णांक max_state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_cdev_delete(पूर्णांक cdev_id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_notअगरy_tz_gov_change(पूर्णांक tz_id, स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thermal_genl_sampling_temp(पूर्णांक id, पूर्णांक temp)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_THERMAL_NETLINK */
