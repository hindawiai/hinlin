<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LOONGSON_HWMON_H_
#घोषणा __LOONGSON_HWMON_H_

#समावेश <linux/types.h>

#घोषणा MIN_TEMP	0
#घोषणा MAX_TEMP	255
#घोषणा NOT_VALID_TEMP	999

प्रकार पूर्णांक (*get_temp_fun)(पूर्णांक);
बाह्य पूर्णांक loongson3_cpu_temp(पूर्णांक);

/* 0:Max speed, 1:Manual, 2:Auto */
क्रमागत fan_control_mode अणु
	FAN_FULL_MODE = 0,
	FAN_MANUAL_MODE = 1,
	FAN_AUTO_MODE = 2,
	FAN_MODE_END
पूर्ण;

काष्ठा temp_range अणु
	u8 low;
	u8 high;
	u8 level;
पूर्ण;

#घोषणा CONSTANT_SPEED_POLICY	0  /* at स्थिरant speed */
#घोषणा STEP_SPEED_POLICY	1  /* use up/करोwn arrays to describe policy */
#घोषणा KERNEL_HELPER_POLICY	2  /* kernel as a helper to fan control */

#घोषणा MAX_STEP_NUM	16
#घोषणा MAX_FAN_LEVEL	255

/* loongson_fan_policy works when fan work at FAN_AUTO_MODE */
काष्ठा loongson_fan_policy अणु
	u8	type;

	/* percent only used when type is CONSTANT_SPEED_POLICY */
	u8	percent;

	/* period between two check. (Unit: S) */
	u8	adjust_period;

	/* fan adjust usually depend on a temprature input */
	get_temp_fun	depend_temp;

	/* up_step/करोwn_step used when type is STEP_SPEED_POLICY */
	u8	up_step_num;
	u8	करोwn_step_num;
	काष्ठा temp_range up_step[MAX_STEP_NUM];
	काष्ठा temp_range करोwn_step[MAX_STEP_NUM];
	काष्ठा delayed_work work;
पूर्ण;

#पूर्ण_अगर /* __LOONGSON_HWMON_H_*/
