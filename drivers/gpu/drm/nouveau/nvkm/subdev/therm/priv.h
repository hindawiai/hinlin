<शैली गुरु>
#अगर_अघोषित __NVTHERM_PRIV_H__
#घोषणा __NVTHERM_PRIV_H__
#घोषणा nvkm_therm(p) container_of((p), काष्ठा nvkm_therm, subdev)
/*
 * Copyright 2012 The Nouveau community
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Martin Peres
 */
#समावेश <subdev/therm.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/extdev.h>
#समावेश <subdev/bios/gpपन.स>
#समावेश <subdev/bios/perf.h>

पूर्णांक nvkm_therm_new_(स्थिर काष्ठा nvkm_therm_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type,
		    पूर्णांक, काष्ठा nvkm_therm **);
व्योम nvkm_therm_ctor(काष्ठा nvkm_therm *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		     स्थिर काष्ठा nvkm_therm_func *);

काष्ठा nvkm_fan अणु
	काष्ठा nvkm_therm *parent;
	स्थिर अक्षर *type;

	काष्ठा nvbios_therm_fan bios;
	काष्ठा nvbios_perf_fan perf;

	काष्ठा nvkm_alarm alarm;
	spinlock_t lock;
	पूर्णांक percent;

	पूर्णांक (*get)(काष्ठा nvkm_therm *);
	पूर्णांक (*set)(काष्ठा nvkm_therm *, पूर्णांक percent);

	काष्ठा dcb_gpio_func tach;
पूर्ण;

पूर्णांक nvkm_therm_fan_mode(काष्ठा nvkm_therm *, पूर्णांक mode);
पूर्णांक nvkm_therm_attr_get(काष्ठा nvkm_therm *, क्रमागत nvkm_therm_attr_type);
पूर्णांक nvkm_therm_attr_set(काष्ठा nvkm_therm *, क्रमागत nvkm_therm_attr_type, पूर्णांक);

व्योम nvkm_therm_ic_ctor(काष्ठा nvkm_therm *);

पूर्णांक nvkm_therm_sensor_ctor(काष्ठा nvkm_therm *);

पूर्णांक nvkm_therm_fan_ctor(काष्ठा nvkm_therm *);
पूर्णांक nvkm_therm_fan_init(काष्ठा nvkm_therm *);
पूर्णांक nvkm_therm_fan_fini(काष्ठा nvkm_therm *, bool suspend);
पूर्णांक nvkm_therm_fan_get(काष्ठा nvkm_therm *);
पूर्णांक nvkm_therm_fan_set(काष्ठा nvkm_therm *, bool now, पूर्णांक percent);
पूर्णांक nvkm_therm_fan_user_get(काष्ठा nvkm_therm *);
पूर्णांक nvkm_therm_fan_user_set(काष्ठा nvkm_therm *, पूर्णांक percent);

पूर्णांक  nvkm_therm_sensor_init(काष्ठा nvkm_therm *);
पूर्णांक  nvkm_therm_sensor_fini(काष्ठा nvkm_therm *, bool suspend);
व्योम nvkm_therm_sensor_preinit(काष्ठा nvkm_therm *);
व्योम nvkm_therm_sensor_set_threshold_state(काष्ठा nvkm_therm *,
					   क्रमागत nvkm_therm_thrs,
					   क्रमागत nvkm_therm_thrs_state);
क्रमागत nvkm_therm_thrs_state
nvkm_therm_sensor_get_threshold_state(काष्ठा nvkm_therm *,
				      क्रमागत nvkm_therm_thrs);
व्योम nvkm_therm_sensor_event(काष्ठा nvkm_therm *, क्रमागत nvkm_therm_thrs,
			     क्रमागत nvkm_therm_thrs_direction);
व्योम nvkm_therm_program_alarms_polling(काष्ठा nvkm_therm *);

काष्ठा nvkm_therm_func अणु
	व्योम (*init)(काष्ठा nvkm_therm *);
	व्योम (*fini)(काष्ठा nvkm_therm *);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_therm *);

	पूर्णांक (*pwm_ctrl)(काष्ठा nvkm_therm *, पूर्णांक line, bool);
	पूर्णांक (*pwm_get)(काष्ठा nvkm_therm *, पूर्णांक line, u32 *, u32 *);
	पूर्णांक (*pwm_set)(काष्ठा nvkm_therm *, पूर्णांक line, u32, u32);
	पूर्णांक (*pwm_घड़ी)(काष्ठा nvkm_therm *, पूर्णांक line);

	पूर्णांक (*temp_get)(काष्ठा nvkm_therm *);

	पूर्णांक (*fan_sense)(काष्ठा nvkm_therm *);

	व्योम (*program_alarms)(काष्ठा nvkm_therm *);

	व्योम (*clkgate_init)(काष्ठा nvkm_therm *,
			     स्थिर काष्ठा nvkm_therm_clkgate_pack *);
	व्योम (*clkgate_enable)(काष्ठा nvkm_therm *);
	व्योम (*clkgate_fini)(काष्ठा nvkm_therm *, bool);
पूर्ण;

व्योम nv40_therm_पूर्णांकr(काष्ठा nvkm_therm *);

पूर्णांक  nv50_fan_pwm_ctrl(काष्ठा nvkm_therm *, पूर्णांक, bool);
पूर्णांक  nv50_fan_pwm_get(काष्ठा nvkm_therm *, पूर्णांक, u32 *, u32 *);
पूर्णांक  nv50_fan_pwm_set(काष्ठा nvkm_therm *, पूर्णांक, u32, u32);
पूर्णांक  nv50_fan_pwm_घड़ी(काष्ठा nvkm_therm *, पूर्णांक);

पूर्णांक  g84_temp_get(काष्ठा nvkm_therm *);
व्योम g84_sensor_setup(काष्ठा nvkm_therm *);
व्योम g84_therm_fini(काष्ठा nvkm_therm *);

पूर्णांक gt215_therm_fan_sense(काष्ठा nvkm_therm *);

व्योम gf100_clkgate_init(काष्ठा nvkm_therm *,
			स्थिर काष्ठा nvkm_therm_clkgate_pack *);

व्योम g84_therm_init(काष्ठा nvkm_therm *);

पूर्णांक gf119_fan_pwm_ctrl(काष्ठा nvkm_therm *, पूर्णांक, bool);
पूर्णांक gf119_fan_pwm_get(काष्ठा nvkm_therm *, पूर्णांक, u32 *, u32 *);
पूर्णांक gf119_fan_pwm_set(काष्ठा nvkm_therm *, पूर्णांक, u32, u32);
पूर्णांक gf119_fan_pwm_घड़ी(काष्ठा nvkm_therm *, पूर्णांक);
व्योम gf119_therm_init(काष्ठा nvkm_therm *);

व्योम gk104_therm_init(काष्ठा nvkm_therm *);
व्योम gk104_clkgate_enable(काष्ठा nvkm_therm *);
व्योम gk104_clkgate_fini(काष्ठा nvkm_therm *, bool);

पूर्णांक nvkm_fanpwm_create(काष्ठा nvkm_therm *, काष्ठा dcb_gpio_func *);
पूर्णांक nvkm_fantog_create(काष्ठा nvkm_therm *, काष्ठा dcb_gpio_func *);
पूर्णांक nvkm_fannil_create(काष्ठा nvkm_therm *);
#पूर्ण_अगर
