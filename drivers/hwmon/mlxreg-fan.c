<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
//
// Copyright (c) 2018 Mellanox Technologies. All rights reserved.
// Copyright (c) 2018 Vadim Pasternak <vadimp@mellanox.com>

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/mlxreg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>

#घोषणा MLXREG_FAN_MAX_TACHO		12
#घोषणा MLXREG_FAN_MAX_STATE		10
#घोषणा MLXREG_FAN_MIN_DUTY		51	/* 20% */
#घोषणा MLXREG_FAN_MAX_DUTY		255	/* 100% */
/*
 * Minimum and maximum FAN allowed speed in percent: from 20% to 100%. Values
 * MLXREG_FAN_MAX_STATE + x, where x is between 2 and 10 are used क्रम
 * setting FAN speed dynamic minimum. For example, अगर value is set to 14 (40%)
 * cooling levels vector will be set to 4, 4, 4, 4, 4, 5, 6, 7, 8, 9, 10 to
 * पूर्णांकroduce PWM speed in percent: 40, 40, 40, 40, 40, 50, 60. 70, 80, 90, 100.
 */
#घोषणा MLXREG_FAN_SPEED_MIN			(MLXREG_FAN_MAX_STATE + 2)
#घोषणा MLXREG_FAN_SPEED_MAX			(MLXREG_FAN_MAX_STATE * 2)
#घोषणा MLXREG_FAN_SPEED_MIN_LEVEL		2	/* 20 percent */
#घोषणा MLXREG_FAN_TACHO_SAMPLES_PER_PULSE_DEF	44
#घोषणा MLXREG_FAN_TACHO_DIV_MIN		283
#घोषणा MLXREG_FAN_TACHO_DIV_DEF		(MLXREG_FAN_TACHO_DIV_MIN * 4)
#घोषणा MLXREG_FAN_TACHO_DIV_SCALE_MAX	64
/*
 * FAN datasheet defines the क्रमmula क्रम RPM calculations as RPM = 15/t-high.
 * The logic in a programmable device measures the समय t-high by sampling the
 * tachometer every t-sample (with the शेष value 11.32 uS) and increment
 * a counter (N) as दीर्घ as the pulse has not change:
 * RPM = 15 / (t-sample * (K + Regval)), where:
 * Regval: is the value पढ़ो from the programmable device रेजिस्टर;
 *  - 0xff - represents tachometer fault;
 *  - 0xfe - represents tachometer minimum value , which is 4444 RPM;
 *  - 0x00 - represents tachometer maximum value , which is 300000 RPM;
 * K: is 44 and it represents the minimum allowed samples per pulse;
 * N: is equal K + Regval;
 * In order to calculate RPM from the रेजिस्टर value the following क्रमmula is
 * used: RPM = 15 / ((Regval + K) * 11.32) * 10^(-6)), which in  the
 * शेष हाल is modअगरied to:
 * RPM = 15000000 * 100 / ((Regval + 44) * 1132);
 * - क्रम Regval 0x00, RPM will be 15000000 * 100 / (44 * 1132) = 30115;
 * - क्रम Regval 0xfe, RPM will be 15000000 * 100 / ((254 + 44) * 1132) = 4446;
 * In common हाल the क्रमmula is modअगरied to:
 * RPM = 15000000 * 100 / ((Regval + samples) * भागider).
 */
#घोषणा MLXREG_FAN_GET_RPM(rval, d, s)	(DIV_ROUND_CLOSEST(15000000 * 100, \
					 ((rval) + (s)) * (d)))
#घोषणा MLXREG_FAN_GET_FAULT(val, mask) ((val) == (mask))
#घोषणा MLXREG_FAN_PWM_DUTY2STATE(duty)	(DIV_ROUND_CLOSEST((duty) *	\
					 MLXREG_FAN_MAX_STATE,		\
					 MLXREG_FAN_MAX_DUTY))
#घोषणा MLXREG_FAN_PWM_STATE2DUTY(stat)	(DIV_ROUND_CLOSEST((stat) *	\
					 MLXREG_FAN_MAX_DUTY,		\
					 MLXREG_FAN_MAX_STATE))

/*
 * काष्ठा mlxreg_fan_tacho - tachometer data (पूर्णांकernal use):
 *
 * @connected: indicates अगर tachometer is connected;
 * @reg: रेजिस्टर offset;
 * @mask: fault mask;
 * @prsnt: present रेजिस्टर offset;
 */
काष्ठा mlxreg_fan_tacho अणु
	bool connected;
	u32 reg;
	u32 mask;
	u32 prsnt;
पूर्ण;

/*
 * काष्ठा mlxreg_fan_pwm - PWM data (पूर्णांकernal use):
 *
 * @connected: indicates अगर PWM is connected;
 * @reg: रेजिस्टर offset;
 */
काष्ठा mlxreg_fan_pwm अणु
	bool connected;
	u32 reg;
पूर्ण;

/*
 * काष्ठा mlxreg_fan - निजी data (पूर्णांकernal use):
 *
 * @dev: basic device;
 * @regmap: रेजिस्टर map of parent device;
 * @tacho: tachometer data;
 * @pwm: PWM data;
 * @tachos_per_drwr - number of tachometers per drawer;
 * @samples: minimum allowed samples per pulse;
 * @भागider: भागider value क्रम tachometer RPM calculation;
 * @cooling: cooling device levels;
 * @cdev: cooling device;
 */
काष्ठा mlxreg_fan अणु
	काष्ठा device *dev;
	व्योम *regmap;
	काष्ठा mlxreg_core_platक्रमm_data *pdata;
	काष्ठा mlxreg_fan_tacho tacho[MLXREG_FAN_MAX_TACHO];
	काष्ठा mlxreg_fan_pwm pwm;
	पूर्णांक tachos_per_drwr;
	पूर्णांक samples;
	पूर्णांक भागider;
	u8 cooling_levels[MLXREG_FAN_MAX_STATE + 1];
	काष्ठा thermal_cooling_device *cdev;
पूर्ण;

अटल पूर्णांक
mlxreg_fan_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
		पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा mlxreg_fan *fan = dev_get_drvdata(dev);
	काष्ठा mlxreg_fan_tacho *tacho;
	u32 regval;
	पूर्णांक err;

	चयन (type) अणु
	हाल hwmon_fan:
		tacho = &fan->tacho[channel];
		चयन (attr) अणु
		हाल hwmon_fan_input:
			/*
			 * Check FAN presence: FAN related bit in presence रेजिस्टर is one,
			 * अगर FAN is physically connected, zero - otherwise.
			 */
			अगर (tacho->prsnt && fan->tachos_per_drwr) अणु
				err = regmap_पढ़ो(fan->regmap, tacho->prsnt, &regval);
				अगर (err)
					वापस err;

				/*
				 * Map channel to presence bit - drawer can be equipped with
				 * one or few FANs, जबतक presence is indicated per drawer.
				 */
				अगर (BIT(channel / fan->tachos_per_drwr) & regval) अणु
					/* FAN is not connected - वापस zero क्रम FAN speed. */
					*val = 0;
					वापस 0;
				पूर्ण
			पूर्ण

			err = regmap_पढ़ो(fan->regmap, tacho->reg, &regval);
			अगर (err)
				वापस err;

			*val = MLXREG_FAN_GET_RPM(regval, fan->भागider,
						  fan->samples);
			अवरोध;

		हाल hwmon_fan_fault:
			err = regmap_पढ़ो(fan->regmap, tacho->reg, &regval);
			अगर (err)
				वापस err;

			*val = MLXREG_FAN_GET_FAULT(regval, tacho->mask);
			अवरोध;

		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;

	हाल hwmon_pwm:
		चयन (attr) अणु
		हाल hwmon_pwm_input:
			err = regmap_पढ़ो(fan->regmap, fan->pwm.reg, &regval);
			अगर (err)
				वापस err;

			*val = regval;
			अवरोध;

		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxreg_fan_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
		 पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा mlxreg_fan *fan = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_pwm:
		चयन (attr) अणु
		हाल hwmon_pwm_input:
			अगर (val < MLXREG_FAN_MIN_DUTY ||
			    val > MLXREG_FAN_MAX_DUTY)
				वापस -EINVAL;
			वापस regmap_ग_लिखो(fan->regmap, fan->pwm.reg, val);
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल umode_t
mlxreg_fan_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type, u32 attr,
		      पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_fan:
		अगर (!(((काष्ठा mlxreg_fan *)data)->tacho[channel].connected))
			वापस 0;

		चयन (attr) अणु
		हाल hwmon_fan_input:
		हाल hwmon_fan_fault:
			वापस 0444;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल hwmon_pwm:
		अगर (!(((काष्ठा mlxreg_fan *)data)->pwm.connected))
			वापस 0;

		चयन (attr) अणु
		हाल hwmon_pwm_input:
			वापस 0644;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *mlxreg_fan_hwmon_info[] = अणु
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_FAULT),
	HWMON_CHANNEL_INFO(pwm,
			   HWMON_PWM_INPUT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops mlxreg_fan_hwmon_hwmon_ops = अणु
	.is_visible = mlxreg_fan_is_visible,
	.पढ़ो = mlxreg_fan_पढ़ो,
	.ग_लिखो = mlxreg_fan_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info mlxreg_fan_hwmon_chip_info = अणु
	.ops = &mlxreg_fan_hwmon_hwmon_ops,
	.info = mlxreg_fan_hwmon_info,
पूर्ण;

अटल पूर्णांक mlxreg_fan_get_max_state(काष्ठा thermal_cooling_device *cdev,
				    अचिन्हित दीर्घ *state)
अणु
	*state = MLXREG_FAN_MAX_STATE;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxreg_fan_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				    अचिन्हित दीर्घ *state)

अणु
	काष्ठा mlxreg_fan *fan = cdev->devdata;
	u32 regval;
	पूर्णांक err;

	err = regmap_पढ़ो(fan->regmap, fan->pwm.reg, &regval);
	अगर (err) अणु
		dev_err(fan->dev, "Failed to query PWM duty\n");
		वापस err;
	पूर्ण

	*state = MLXREG_FAN_PWM_DUTY2STATE(regval);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxreg_fan_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				    अचिन्हित दीर्घ state)

अणु
	काष्ठा mlxreg_fan *fan = cdev->devdata;
	अचिन्हित दीर्घ cur_state;
	u32 regval;
	पूर्णांक i;
	पूर्णांक err;

	/*
	 * Verअगरy अगर this request is क्रम changing allowed FAN dynamical
	 * minimum. If it is - update cooling levels accordingly and update
	 * state, अगर current state is below the newly requested minimum state.
	 * For example, अगर current state is 5, and minimal state is to be
	 * changed from 4 to 6, fan->cooling_levels[0 to 5] will be changed all
	 * from 4 to 6. And state 5 (fan->cooling_levels[4]) should be
	 * overwritten.
	 */
	अगर (state >= MLXREG_FAN_SPEED_MIN && state <= MLXREG_FAN_SPEED_MAX) अणु
		state -= MLXREG_FAN_MAX_STATE;
		क्रम (i = 0; i < state; i++)
			fan->cooling_levels[i] = state;
		क्रम (i = state; i <= MLXREG_FAN_MAX_STATE; i++)
			fan->cooling_levels[i] = i;

		err = regmap_पढ़ो(fan->regmap, fan->pwm.reg, &regval);
		अगर (err) अणु
			dev_err(fan->dev, "Failed to query PWM duty\n");
			वापस err;
		पूर्ण

		cur_state = MLXREG_FAN_PWM_DUTY2STATE(regval);
		अगर (state < cur_state)
			वापस 0;

		state = cur_state;
	पूर्ण

	अगर (state > MLXREG_FAN_MAX_STATE)
		वापस -EINVAL;

	/* Normalize the state to the valid speed range. */
	state = fan->cooling_levels[state];
	err = regmap_ग_लिखो(fan->regmap, fan->pwm.reg,
			   MLXREG_FAN_PWM_STATE2DUTY(state));
	अगर (err) अणु
		dev_err(fan->dev, "Failed to write PWM duty\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops mlxreg_fan_cooling_ops = अणु
	.get_max_state	= mlxreg_fan_get_max_state,
	.get_cur_state	= mlxreg_fan_get_cur_state,
	.set_cur_state	= mlxreg_fan_set_cur_state,
पूर्ण;

अटल पूर्णांक mlxreg_fan_connect_verअगरy(काष्ठा mlxreg_fan *fan,
				     काष्ठा mlxreg_core_data *data)
अणु
	u32 regval;
	पूर्णांक err;

	err = regmap_पढ़ो(fan->regmap, data->capability, &regval);
	अगर (err) अणु
		dev_err(fan->dev, "Failed to query capability register 0x%08x\n",
			data->capability);
		वापस err;
	पूर्ण

	वापस !!(regval & data->bit);
पूर्ण

अटल पूर्णांक mlxreg_fan_speed_भागider_get(काष्ठा mlxreg_fan *fan,
					काष्ठा mlxreg_core_data *data)
अणु
	u32 regval;
	पूर्णांक err;

	err = regmap_पढ़ो(fan->regmap, data->capability, &regval);
	अगर (err) अणु
		dev_err(fan->dev, "Failed to query capability register 0x%08x\n",
			data->capability);
		वापस err;
	पूर्ण

	/*
	 * Set भागider value according to the capability रेजिस्टर, in हाल it
	 * contains valid value. Otherwise use शेष value. The purpose of
	 * this validation is to protect against the old hardware, in which
	 * this रेजिस्टर can वापस zero.
	 */
	अगर (regval > 0 && regval <= MLXREG_FAN_TACHO_DIV_SCALE_MAX)
		fan->भागider = regval * MLXREG_FAN_TACHO_DIV_MIN;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxreg_fan_config(काष्ठा mlxreg_fan *fan,
			     काष्ठा mlxreg_core_platक्रमm_data *pdata)
अणु
	काष्ठा mlxreg_core_data *data = pdata->data;
	पूर्णांक tacho_num = 0, tacho_avail = 0, i;
	bool configured = false;
	पूर्णांक err;

	fan->samples = MLXREG_FAN_TACHO_SAMPLES_PER_PULSE_DEF;
	fan->भागider = MLXREG_FAN_TACHO_DIV_DEF;
	क्रम (i = 0; i < pdata->counter; i++, data++) अणु
		अगर (strnstr(data->label, "tacho", माप(data->label))) अणु
			अगर (tacho_num == MLXREG_FAN_MAX_TACHO) अणु
				dev_err(fan->dev, "too many tacho entries: %s\n",
					data->label);
				वापस -EINVAL;
			पूर्ण

			अगर (data->capability) अणु
				err = mlxreg_fan_connect_verअगरy(fan, data);
				अगर (err < 0)
					वापस err;
				अन्यथा अगर (!err) अणु
					tacho_num++;
					जारी;
				पूर्ण
			पूर्ण

			fan->tacho[tacho_num].reg = data->reg;
			fan->tacho[tacho_num].mask = data->mask;
			fan->tacho[tacho_num].prsnt = data->reg_prsnt;
			fan->tacho[tacho_num++].connected = true;
			tacho_avail++;
		पूर्ण अन्यथा अगर (strnstr(data->label, "pwm", माप(data->label))) अणु
			अगर (fan->pwm.connected) अणु
				dev_err(fan->dev, "duplicate pwm entry: %s\n",
					data->label);
				वापस -EINVAL;
			पूर्ण
			fan->pwm.reg = data->reg;
			fan->pwm.connected = true;
		पूर्ण अन्यथा अगर (strnstr(data->label, "conf", माप(data->label))) अणु
			अगर (configured) अणु
				dev_err(fan->dev, "duplicate conf entry: %s\n",
					data->label);
				वापस -EINVAL;
			पूर्ण
			/* Validate that conf parameters are not zeros. */
			अगर (!data->mask && !data->bit && !data->capability) अणु
				dev_err(fan->dev, "invalid conf entry params: %s\n",
					data->label);
				वापस -EINVAL;
			पूर्ण
			अगर (data->capability) अणु
				err = mlxreg_fan_speed_भागider_get(fan, data);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अणु
				अगर (data->mask)
					fan->samples = data->mask;
				अगर (data->bit)
					fan->भागider = data->bit;
			पूर्ण
			configured = true;
		पूर्ण अन्यथा अणु
			dev_err(fan->dev, "invalid label: %s\n", data->label);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (pdata->capability) अणु
		पूर्णांक drwr_avail;
		u32 regval;

		/* Obtain the number of FAN drawers, supported by प्रणाली. */
		err = regmap_पढ़ो(fan->regmap, pdata->capability, &regval);
		अगर (err) अणु
			dev_err(fan->dev, "Failed to query capability register 0x%08x\n",
				pdata->capability);
			वापस err;
		पूर्ण

		drwr_avail = hweight32(regval);
		अगर (!tacho_avail || !drwr_avail || tacho_avail < drwr_avail) अणु
			dev_err(fan->dev, "Configuration is invalid: drawers num %d tachos num %d\n",
				drwr_avail, tacho_avail);
			वापस -EINVAL;
		पूर्ण

		/* Set the number of tachometers per one drawer. */
		fan->tachos_per_drwr = tacho_avail / drwr_avail;
	पूर्ण

	/* Init cooling levels per PWM state. */
	क्रम (i = 0; i < MLXREG_FAN_SPEED_MIN_LEVEL; i++)
		fan->cooling_levels[i] = MLXREG_FAN_SPEED_MIN_LEVEL;
	क्रम (i = MLXREG_FAN_SPEED_MIN_LEVEL; i <= MLXREG_FAN_MAX_STATE; i++)
		fan->cooling_levels[i] = i;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxreg_fan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxreg_core_platक्रमm_data *pdata;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mlxreg_fan *fan;
	काष्ठा device *hwm;
	पूर्णांक err;

	pdata = dev_get_platdata(dev);
	अगर (!pdata) अणु
		dev_err(dev, "Failed to get platform data.\n");
		वापस -EINVAL;
	पूर्ण

	fan = devm_kzalloc(dev, माप(*fan), GFP_KERNEL);
	अगर (!fan)
		वापस -ENOMEM;

	fan->dev = dev;
	fan->regmap = pdata->regmap;

	err = mlxreg_fan_config(fan, pdata);
	अगर (err)
		वापस err;

	hwm = devm_hwmon_device_रेजिस्टर_with_info(dev, "mlxreg_fan",
						   fan,
						   &mlxreg_fan_hwmon_chip_info,
						   शून्य);
	अगर (IS_ERR(hwm)) अणु
		dev_err(dev, "Failed to register hwmon device\n");
		वापस PTR_ERR(hwm);
	पूर्ण

	अगर (IS_REACHABLE(CONFIG_THERMAL)) अणु
		fan->cdev = devm_thermal_of_cooling_device_रेजिस्टर(dev,
			शून्य, "mlxreg_fan", fan, &mlxreg_fan_cooling_ops);
		अगर (IS_ERR(fan->cdev)) अणु
			dev_err(dev, "Failed to register cooling device\n");
			वापस PTR_ERR(fan->cdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mlxreg_fan_driver = अणु
	.driver = अणु
	    .name = "mlxreg-fan",
	पूर्ण,
	.probe = mlxreg_fan_probe,
पूर्ण;

module_platक्रमm_driver(mlxreg_fan_driver);

MODULE_AUTHOR("Vadim Pasternak <vadimp@mellanox.com>");
MODULE_DESCRIPTION("Mellanox FAN driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mlxreg-fan");
