<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017 Netronome Systems, Inc. */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/hwmon.h>

#समावेश "nfpcore/nfp_cpp.h"
#समावेश "nfpcore/nfp_nsp.h"
#समावेश "nfp_main.h"

#घोषणा NFP_TEMP_MAX		(95 * 1000)
#घोषणा NFP_TEMP_CRIT		(105 * 1000)

#घोषणा NFP_POWER_MAX		(25 * 1000 * 1000)

अटल पूर्णांक nfp_hwmon_sensor_id(क्रमागत hwmon_sensor_types type, पूर्णांक channel)
अणु
	अगर (type == hwmon_temp)
		वापस NFP_SENSOR_CHIP_TEMPERATURE;
	अगर (type == hwmon_घातer)
		वापस NFP_SENSOR_ASSEMBLY_POWER + channel;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nfp_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
	       पूर्णांक channel, दीर्घ *val)
अणु
	अटल स्थिर काष्ठा अणु
		क्रमागत hwmon_sensor_types type;
		u32 attr;
		दीर्घ val;
	पूर्ण स्थिर_vals[] = अणु
		अणु hwmon_temp,	hwmon_temp_max,		NFP_TEMP_MAX पूर्ण,
		अणु hwmon_temp,	hwmon_temp_crit,	NFP_TEMP_CRIT पूर्ण,
		अणु hwmon_घातer,	hwmon_घातer_max,	NFP_POWER_MAX पूर्ण,
	पूर्ण;
	काष्ठा nfp_pf *pf = dev_get_drvdata(dev);
	क्रमागत nfp_nsp_sensor_id id;
	पूर्णांक err, i;

	क्रम (i = 0; i < ARRAY_SIZE(स्थिर_vals); i++)
		अगर (स्थिर_vals[i].type == type && स्थिर_vals[i].attr == attr) अणु
			*val = स्थिर_vals[i].val;
			वापस 0;
		पूर्ण

	err = nfp_hwmon_sensor_id(type, channel);
	अगर (err < 0)
		वापस err;
	id = err;

	अगर (!(pf->nspi->sensor_mask & BIT(id)))
		वापस -EOPNOTSUPP;

	अगर (type == hwmon_temp && attr == hwmon_temp_input)
		वापस nfp_hwmon_पढ़ो_sensor(pf->cpp, id, val);
	अगर (type == hwmon_घातer && attr == hwmon_घातer_input)
		वापस nfp_hwmon_पढ़ो_sensor(pf->cpp, id, val);

	वापस -EINVAL;
पूर्ण

अटल umode_t
nfp_hwmon_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type, u32 attr,
		     पूर्णांक channel)
अणु
	अगर (type == hwmon_temp) अणु
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_crit:
		हाल hwmon_temp_max:
			वापस 0444;
		पूर्ण
	पूर्ण अन्यथा अगर (type == hwmon_घातer) अणु
		चयन (attr) अणु
		हाल hwmon_घातer_input:
		हाल hwmon_घातer_max:
			वापस 0444;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 nfp_chip_config[] = अणु
	HWMON_C_REGISTER_TZ,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info nfp_chip = अणु
	.type = hwmon_chip,
	.config = nfp_chip_config,
पूर्ण;

अटल u32 nfp_temp_config[] = अणु
	HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info nfp_temp = अणु
	.type = hwmon_temp,
	.config = nfp_temp_config,
पूर्ण;

अटल u32 nfp_घातer_config[] = अणु
	HWMON_P_INPUT | HWMON_P_MAX,
	HWMON_P_INPUT,
	HWMON_P_INPUT,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info nfp_घातer = अणु
	.type = hwmon_घातer,
	.config = nfp_घातer_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *nfp_hwmon_info[] = अणु
	&nfp_chip,
	&nfp_temp,
	&nfp_घातer,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops nfp_hwmon_ops = अणु
	.is_visible = nfp_hwmon_is_visible,
	.पढ़ो = nfp_hwmon_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info nfp_chip_info = अणु
	.ops = &nfp_hwmon_ops,
	.info = nfp_hwmon_info,
पूर्ण;

पूर्णांक nfp_hwmon_रेजिस्टर(काष्ठा nfp_pf *pf)
अणु
	अगर (!IS_REACHABLE(CONFIG_HWMON))
		वापस 0;

	अगर (!pf->nspi) अणु
		nfp_warn(pf->cpp, "not registering HWMON (no NSP info)\n");
		वापस 0;
	पूर्ण
	अगर (!pf->nspi->sensor_mask) अणु
		nfp_info(pf->cpp,
			 "not registering HWMON (NSP doesn't report sensors)\n");
		वापस 0;
	पूर्ण

	pf->hwmon_dev = hwmon_device_रेजिस्टर_with_info(&pf->pdev->dev, "nfp",
							pf, &nfp_chip_info,
							शून्य);
	वापस PTR_ERR_OR_ZERO(pf->hwmon_dev);
पूर्ण

व्योम nfp_hwmon_unरेजिस्टर(काष्ठा nfp_pf *pf)
अणु
	अगर (!IS_REACHABLE(CONFIG_HWMON) || !pf->hwmon_dev)
		वापस;

	hwmon_device_unरेजिस्टर(pf->hwmon_dev);
पूर्ण
