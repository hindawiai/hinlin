<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_THERM_H__
#घोषणा __NVKM_THERM_H__
#समावेश <core/subdev.h>

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/therm.h>
#समावेश <subdev/समयr.h>

क्रमागत nvkm_therm_thrs_direction अणु
	NVKM_THERM_THRS_FALLING = 0,
	NVKM_THERM_THRS_RISING = 1
पूर्ण;

क्रमागत nvkm_therm_thrs_state अणु
	NVKM_THERM_THRS_LOWER = 0,
	NVKM_THERM_THRS_HIGHER = 1
पूर्ण;

क्रमागत nvkm_therm_thrs अणु
	NVKM_THERM_THRS_FANBOOST = 0,
	NVKM_THERM_THRS_DOWNCLOCK = 1,
	NVKM_THERM_THRS_CRITICAL = 2,
	NVKM_THERM_THRS_SHUTDOWN = 3,
	NVKM_THERM_THRS_NR
पूर्ण;

क्रमागत nvkm_therm_fan_mode अणु
	NVKM_THERM_CTRL_NONE = 0,
	NVKM_THERM_CTRL_MANUAL = 1,
	NVKM_THERM_CTRL_AUTO = 2,
पूर्ण;

क्रमागत nvkm_therm_attr_type अणु
	NVKM_THERM_ATTR_FAN_MIN_DUTY = 0,
	NVKM_THERM_ATTR_FAN_MAX_DUTY = 1,
	NVKM_THERM_ATTR_FAN_MODE = 2,

	NVKM_THERM_ATTR_THRS_FAN_BOOST = 10,
	NVKM_THERM_ATTR_THRS_FAN_BOOST_HYST = 11,
	NVKM_THERM_ATTR_THRS_DOWN_CLK = 12,
	NVKM_THERM_ATTR_THRS_DOWN_CLK_HYST = 13,
	NVKM_THERM_ATTR_THRS_CRITICAL = 14,
	NVKM_THERM_ATTR_THRS_CRITICAL_HYST = 15,
	NVKM_THERM_ATTR_THRS_SHUTDOWN = 16,
	NVKM_THERM_ATTR_THRS_SHUTDOWN_HYST = 17,
पूर्ण;

काष्ठा nvkm_therm_clkgate_init अणु
	u32 addr;
	u8  count;
	u32 data;
पूर्ण;

काष्ठा nvkm_therm_clkgate_pack अणु
	स्थिर काष्ठा nvkm_therm_clkgate_init *init;
पूर्ण;

काष्ठा nvkm_therm अणु
	स्थिर काष्ठा nvkm_therm_func *func;
	काष्ठा nvkm_subdev subdev;

	/* स्वतःmatic thermal management */
	काष्ठा nvkm_alarm alarm;
	spinlock_t lock;
	काष्ठा nvbios_therm_trip_poपूर्णांक *last_trip;
	पूर्णांक mode;
	पूर्णांक cstate;
	पूर्णांक suspend;

	/* bios */
	काष्ठा nvbios_therm_sensor bios_sensor;

	/* fan priv */
	काष्ठा nvkm_fan *fan;

	/* alarms priv */
	काष्ठा अणु
		spinlock_t alarm_program_lock;
		काष्ठा nvkm_alarm therm_poll_alarm;
		क्रमागत nvkm_therm_thrs_state alarm_state[NVKM_THERM_THRS_NR];
	पूर्ण sensor;

	/* what should be करोne अगर the card overheats */
	काष्ठा अणु
		व्योम (*करोwnघड़ी)(काष्ठा nvkm_therm *, bool active);
		व्योम (*छोड़ो)(काष्ठा nvkm_therm *, bool active);
	पूर्ण emergency;

	/* ic */
	काष्ठा i2c_client *ic;

	पूर्णांक (*fan_get)(काष्ठा nvkm_therm *);
	पूर्णांक (*fan_set)(काष्ठा nvkm_therm *, पूर्णांक);

	पूर्णांक (*attr_get)(काष्ठा nvkm_therm *, क्रमागत nvkm_therm_attr_type);
	पूर्णांक (*attr_set)(काष्ठा nvkm_therm *, क्रमागत nvkm_therm_attr_type, पूर्णांक);

	bool clkgating_enabled;
पूर्ण;

पूर्णांक nvkm_therm_temp_get(काष्ठा nvkm_therm *);
पूर्णांक nvkm_therm_fan_sense(काष्ठा nvkm_therm *);
पूर्णांक nvkm_therm_cstate(काष्ठा nvkm_therm *, पूर्णांक, पूर्णांक);
व्योम nvkm_therm_clkgate_init(काष्ठा nvkm_therm *,
			     स्थिर काष्ठा nvkm_therm_clkgate_pack *);
व्योम nvkm_therm_clkgate_enable(काष्ठा nvkm_therm *);
व्योम nvkm_therm_clkgate_fini(काष्ठा nvkm_therm *, bool);

पूर्णांक nv40_therm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_therm **);
पूर्णांक nv50_therm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_therm **);
पूर्णांक g84_therm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_therm **);
पूर्णांक gt215_therm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_therm **);
पूर्णांक gf119_therm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_therm **);
पूर्णांक gk104_therm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_therm **);
पूर्णांक gm107_therm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_therm **);
पूर्णांक gm200_therm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_therm **);
पूर्णांक gp100_therm_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_therm **);
#पूर्ण_अगर
