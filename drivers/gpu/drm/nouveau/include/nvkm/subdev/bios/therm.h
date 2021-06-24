<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_THERM_H__
#घोषणा __NVBIOS_THERM_H__
काष्ठा nvbios_therm_threshold अणु
	u8 temp;
	u8 hysteresis;
पूर्ण;

काष्ठा nvbios_therm_sensor अणु
	/* diode */
	s16 slope_mult;
	s16 slope_भाग;
	s16 offset_num;
	s16 offset_den;
	s8 offset_स्थिरant;

	/* thresholds */
	काष्ठा nvbios_therm_threshold thrs_fan_boost;
	काष्ठा nvbios_therm_threshold thrs_करोwn_घड़ी;
	काष्ठा nvbios_therm_threshold thrs_critical;
	काष्ठा nvbios_therm_threshold thrs_shutकरोwn;
पूर्ण;

क्रमागत nvbios_therm_fan_type अणु
	NVBIOS_THERM_FAN_UNK = 0,
	NVBIOS_THERM_FAN_TOGGLE = 1,
	NVBIOS_THERM_FAN_PWM = 2,
पूर्ण;

/* no vbios have more than 6 */
#घोषणा NVKM_TEMP_FAN_TRIP_MAX 10
काष्ठा nvbios_therm_trip_poपूर्णांक अणु
	पूर्णांक fan_duty;
	पूर्णांक temp;
	पूर्णांक hysteresis;
पूर्ण;

क्रमागत nvbios_therm_fan_mode अणु
	NVBIOS_THERM_FAN_TRIP = 0,
	NVBIOS_THERM_FAN_LINEAR = 1,
	NVBIOS_THERM_FAN_OTHER = 2,
पूर्ण;

काष्ठा nvbios_therm_fan अणु
	क्रमागत nvbios_therm_fan_type type;

	u32 pwm_freq;

	u8 min_duty;
	u8 max_duty;

	u16 bump_period;
	u16 slow_करोwn_period;

	क्रमागत nvbios_therm_fan_mode fan_mode;
	काष्ठा nvbios_therm_trip_poपूर्णांक trip[NVKM_TEMP_FAN_TRIP_MAX];
	u8 nr_fan_trip;
	u8 linear_min_temp;
	u8 linear_max_temp;
पूर्ण;

क्रमागत nvbios_therm_करोमुख्य अणु
	NVBIOS_THERM_DOMAIN_CORE,
	NVBIOS_THERM_DOMAIN_AMBIENT,
पूर्ण;

पूर्णांक
nvbios_therm_sensor_parse(काष्ठा nvkm_bios *, क्रमागत nvbios_therm_करोमुख्य,
			  काष्ठा nvbios_therm_sensor *);

पूर्णांक
nvbios_therm_fan_parse(काष्ठा nvkm_bios *, काष्ठा nvbios_therm_fan *);
#पूर्ण_अगर
