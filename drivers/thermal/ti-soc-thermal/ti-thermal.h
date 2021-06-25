<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP thermal definitions
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
 * Contact:
 *   Eduarकरो Valentin <eduarकरो.valentin@ti.com>
 */
#अगर_अघोषित __TI_THERMAL_H
#घोषणा __TI_THERMAL_H

#समावेश "ti-bandgap.h"

/* PCB sensor calculation स्थिरants */
#घोषणा OMAP_GRADIENT_SLOPE_W_PCB_4430				0
#घोषणा OMAP_GRADIENT_CONST_W_PCB_4430				20000
#घोषणा OMAP_GRADIENT_SLOPE_W_PCB_4460				1142
#घोषणा OMAP_GRADIENT_CONST_W_PCB_4460				-393
#घोषणा OMAP_GRADIENT_SLOPE_W_PCB_4470				1063
#घोषणा OMAP_GRADIENT_CONST_W_PCB_4470				-477

#घोषणा OMAP_GRADIENT_SLOPE_W_PCB_5430_CPU			100
#घोषणा OMAP_GRADIENT_CONST_W_PCB_5430_CPU			484
#घोषणा OMAP_GRADIENT_SLOPE_W_PCB_5430_GPU			464
#घोषणा OMAP_GRADIENT_CONST_W_PCB_5430_GPU			-5102

#घोषणा DRA752_GRADIENT_SLOPE_W_PCB				0
#घोषणा DRA752_GRADIENT_CONST_W_PCB				2000

/* trip poपूर्णांकs of पूर्णांकerest in milicelsius (at hotspot level) */
#घोषणा OMAP_TRIP_COLD						100000
#घोषणा OMAP_TRIP_HOT						110000
#घोषणा OMAP_TRIP_SHUTDOWN					125000
#घोषणा OMAP_TRIP_NUMBER					2
#घोषणा OMAP_TRIP_STEP							\
	((OMAP_TRIP_SHUTDOWN - OMAP_TRIP_HOT) / (OMAP_TRIP_NUMBER - 1))

/* Update rates */
#घोषणा FAST_TEMP_MONITORING_RATE				250

/* helper macros */
/**
 * ti_thermal_get_trip_value - वापसs trip temperature based on index
 * @i:	trip index
 */
#घोषणा ti_thermal_get_trip_value(i)					\
	(OMAP_TRIP_HOT + ((i) * OMAP_TRIP_STEP))

/**
 * ti_thermal_is_valid_trip - check क्रम trip index
 * @i:	trip index
 */
#घोषणा ti_thermal_is_valid_trip(trip)				\
	((trip) >= 0 && (trip) < OMAP_TRIP_NUMBER)

#अगर_घोषित CONFIG_TI_THERMAL
पूर्णांक ti_thermal_expose_sensor(काष्ठा ti_bandgap *bgp, पूर्णांक id, अक्षर *करोमुख्य);
पूर्णांक ti_thermal_हटाओ_sensor(काष्ठा ti_bandgap *bgp, पूर्णांक id);
पूर्णांक ti_thermal_report_sensor_temperature(काष्ठा ti_bandgap *bgp, पूर्णांक id);
पूर्णांक ti_thermal_रेजिस्टर_cpu_cooling(काष्ठा ti_bandgap *bgp, पूर्णांक id);
पूर्णांक ti_thermal_unरेजिस्टर_cpu_cooling(काष्ठा ti_bandgap *bgp, पूर्णांक id);
#अन्यथा
अटल अंतरभूत
पूर्णांक ti_thermal_expose_sensor(काष्ठा ti_bandgap *bgp, पूर्णांक id, अक्षर *करोमुख्य)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक ti_thermal_हटाओ_sensor(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक ti_thermal_report_sensor_temperature(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक ti_thermal_रेजिस्टर_cpu_cooling(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक ti_thermal_unरेजिस्टर_cpu_cooling(काष्ठा ti_bandgap *bgp, पूर्णांक id)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
