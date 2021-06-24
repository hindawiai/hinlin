<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * पूर्णांक340x_thermal_zone.h
 * Copyright (c) 2015, Intel Corporation.
 */

#अगर_अघोषित __INT340X_THERMAL_ZONE_H__
#घोषणा __INT340X_THERMAL_ZONE_H__

#समावेश <acpi/acpi_lpat.h>

#घोषणा INT340X_THERMAL_MAX_ACT_TRIP_COUNT	10

काष्ठा active_trip अणु
	पूर्णांक temp;
	पूर्णांक id;
	bool valid;
पूर्ण;

काष्ठा पूर्णांक34x_thermal_zone अणु
	काष्ठा acpi_device *adev;
	काष्ठा active_trip act_trips[INT340X_THERMAL_MAX_ACT_TRIP_COUNT];
	अचिन्हित दीर्घ *aux_trips;
	पूर्णांक aux_trip_nr;
	पूर्णांक psv_temp;
	पूर्णांक psv_trip_id;
	पूर्णांक crt_temp;
	पूर्णांक crt_trip_id;
	पूर्णांक hot_temp;
	पूर्णांक hot_trip_id;
	काष्ठा thermal_zone_device *zone;
	काष्ठा thermal_zone_device_ops *override_ops;
	व्योम *priv_data;
	काष्ठा acpi_lpat_conversion_table *lpat_table;
पूर्ण;

काष्ठा पूर्णांक34x_thermal_zone *पूर्णांक340x_thermal_zone_add(काष्ठा acpi_device *,
				काष्ठा thermal_zone_device_ops *override_ops);
व्योम पूर्णांक340x_thermal_zone_हटाओ(काष्ठा पूर्णांक34x_thermal_zone *);
पूर्णांक पूर्णांक340x_thermal_पढ़ो_trips(काष्ठा पूर्णांक34x_thermal_zone *पूर्णांक34x_zone);

अटल अंतरभूत व्योम पूर्णांक340x_thermal_zone_set_priv_data(
			काष्ठा पूर्णांक34x_thermal_zone *tzone, व्योम *priv_data)
अणु
	tzone->priv_data = priv_data;
पूर्ण

अटल अंतरभूत व्योम *पूर्णांक340x_thermal_zone_get_priv_data(
			काष्ठा पूर्णांक34x_thermal_zone *tzone)
अणु
	वापस tzone->priv_data;
पूर्ण

अटल अंतरभूत व्योम पूर्णांक340x_thermal_zone_device_update(
					काष्ठा पूर्णांक34x_thermal_zone *tzone,
					क्रमागत thermal_notअगरy_event event)
अणु
	thermal_zone_device_update(tzone->zone, event);
पूर्ण

#पूर्ण_अगर
