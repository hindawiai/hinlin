<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Maxim MAX77620 Regulator driver
 *
 * Copyright (c) 2016-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Mallikarjun Kasoju <mkasoju@nvidia.com>
 *	Laxman Dewangan <ldewangan@nvidia.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/mfd/max77620.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा max77620_rails(_name)	"max77620-"#_name

/* Power Mode */
#घोषणा MAX77620_POWER_MODE_NORMAL		3
#घोषणा MAX77620_POWER_MODE_LPM			2
#घोषणा MAX77620_POWER_MODE_GLPM		1
#घोषणा MAX77620_POWER_MODE_DISABLE		0

/* SD Slew Rate */
#घोषणा MAX77620_SD_SR_13_75			0
#घोषणा MAX77620_SD_SR_27_5			1
#घोषणा MAX77620_SD_SR_55			2
#घोषणा MAX77620_SD_SR_100			3

क्रमागत max77620_regulators अणु
	MAX77620_REGULATOR_ID_SD0,
	MAX77620_REGULATOR_ID_SD1,
	MAX77620_REGULATOR_ID_SD2,
	MAX77620_REGULATOR_ID_SD3,
	MAX77620_REGULATOR_ID_SD4,
	MAX77620_REGULATOR_ID_LDO0,
	MAX77620_REGULATOR_ID_LDO1,
	MAX77620_REGULATOR_ID_LDO2,
	MAX77620_REGULATOR_ID_LDO3,
	MAX77620_REGULATOR_ID_LDO4,
	MAX77620_REGULATOR_ID_LDO5,
	MAX77620_REGULATOR_ID_LDO6,
	MAX77620_REGULATOR_ID_LDO7,
	MAX77620_REGULATOR_ID_LDO8,
	MAX77620_NUM_REGS,
पूर्ण;

/* Regulator types */
क्रमागत max77620_regulator_type अणु
	MAX77620_REGULATOR_TYPE_SD,
	MAX77620_REGULATOR_TYPE_LDO_N,
	MAX77620_REGULATOR_TYPE_LDO_P,
पूर्ण;

काष्ठा max77620_regulator_info अणु
	u8 type;
	u8 fps_addr;
	u8 volt_addr;
	u8 cfg_addr;
	u8 घातer_mode_mask;
	u8 घातer_mode_shअगरt;
	u8 remote_sense_addr;
	u8 remote_sense_mask;
	काष्ठा regulator_desc desc;
पूर्ण;

काष्ठा max77620_regulator_pdata अणु
	पूर्णांक active_fps_src;
	पूर्णांक active_fps_pd_slot;
	पूर्णांक active_fps_pu_slot;
	पूर्णांक suspend_fps_src;
	पूर्णांक suspend_fps_pd_slot;
	पूर्णांक suspend_fps_pu_slot;
	पूर्णांक current_mode;
	पूर्णांक घातer_ok;
	पूर्णांक ramp_rate_setting;
पूर्ण;

काष्ठा max77620_regulator अणु
	काष्ठा device *dev;
	काष्ठा regmap *rmap;
	काष्ठा max77620_regulator_info *rinfo[MAX77620_NUM_REGS];
	काष्ठा max77620_regulator_pdata reg_pdata[MAX77620_NUM_REGS];
	पूर्णांक enable_घातer_mode[MAX77620_NUM_REGS];
	पूर्णांक current_घातer_mode[MAX77620_NUM_REGS];
	पूर्णांक active_fps_src[MAX77620_NUM_REGS];
पूर्ण;

#घोषणा fps_src_name(fps_src)	\
	(fps_src == MAX77620_FPS_SRC_0 ? "FPS_SRC_0" :	\
	fps_src == MAX77620_FPS_SRC_1 ? "FPS_SRC_1" :	\
	fps_src == MAX77620_FPS_SRC_2 ? "FPS_SRC_2" : "FPS_SRC_NONE")

अटल पूर्णांक max77620_regulator_get_fps_src(काष्ठा max77620_regulator *pmic,
					  पूर्णांक id)
अणु
	काष्ठा max77620_regulator_info *rinfo = pmic->rinfo[id];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pmic->rmap, rinfo->fps_addr, &val);
	अगर (ret < 0) अणु
		dev_err(pmic->dev, "Reg 0x%02x read failed %d\n",
			rinfo->fps_addr, ret);
		वापस ret;
	पूर्ण

	वापस (val & MAX77620_FPS_SRC_MASK) >> MAX77620_FPS_SRC_SHIFT;
पूर्ण

अटल पूर्णांक max77620_regulator_set_fps_src(काष्ठा max77620_regulator *pmic,
					  पूर्णांक fps_src, पूर्णांक id)
अणु
	काष्ठा max77620_regulator_info *rinfo = pmic->rinfo[id];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (!rinfo)
		वापस 0;

	चयन (fps_src) अणु
	हाल MAX77620_FPS_SRC_0:
	हाल MAX77620_FPS_SRC_1:
	हाल MAX77620_FPS_SRC_2:
	हाल MAX77620_FPS_SRC_NONE:
		अवरोध;

	हाल MAX77620_FPS_SRC_DEF:
		ret = regmap_पढ़ो(pmic->rmap, rinfo->fps_addr, &val);
		अगर (ret < 0) अणु
			dev_err(pmic->dev, "Reg 0x%02x read failed %d\n",
				rinfo->fps_addr, ret);
			वापस ret;
		पूर्ण
		ret = (val & MAX77620_FPS_SRC_MASK) >> MAX77620_FPS_SRC_SHIFT;
		pmic->active_fps_src[id] = ret;
		वापस 0;

	शेष:
		dev_err(pmic->dev, "Invalid FPS %d for regulator %d\n",
			fps_src, id);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(pmic->rmap, rinfo->fps_addr,
				 MAX77620_FPS_SRC_MASK,
				 fps_src << MAX77620_FPS_SRC_SHIFT);
	अगर (ret < 0) अणु
		dev_err(pmic->dev, "Reg 0x%02x update failed %d\n",
			rinfo->fps_addr, ret);
		वापस ret;
	पूर्ण
	pmic->active_fps_src[id] = fps_src;

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_regulator_set_fps_slots(काष्ठा max77620_regulator *pmic,
					    पूर्णांक id, bool is_suspend)
अणु
	काष्ठा max77620_regulator_pdata *rpdata = &pmic->reg_pdata[id];
	काष्ठा max77620_regulator_info *rinfo = pmic->rinfo[id];
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित पूर्णांक mask = 0;
	पूर्णांक pu = rpdata->active_fps_pu_slot;
	पूर्णांक pd = rpdata->active_fps_pd_slot;
	पूर्णांक ret = 0;

	अगर (!rinfo)
		वापस 0;

	अगर (is_suspend) अणु
		pu = rpdata->suspend_fps_pu_slot;
		pd = rpdata->suspend_fps_pd_slot;
	पूर्ण

	/* FPS घातer up period setting */
	अगर (pu >= 0) अणु
		val |= (pu << MAX77620_FPS_PU_PERIOD_SHIFT);
		mask |= MAX77620_FPS_PU_PERIOD_MASK;
	पूर्ण

	/* FPS घातer करोwn period setting */
	अगर (pd >= 0) अणु
		val |= (pd << MAX77620_FPS_PD_PERIOD_SHIFT);
		mask |= MAX77620_FPS_PD_PERIOD_MASK;
	पूर्ण

	अगर (mask) अणु
		ret = regmap_update_bits(pmic->rmap, rinfo->fps_addr,
					 mask, val);
		अगर (ret < 0) अणु
			dev_err(pmic->dev, "Reg 0x%02x update failed: %d\n",
				rinfo->fps_addr, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक max77620_regulator_set_घातer_mode(काष्ठा max77620_regulator *pmic,
					     पूर्णांक घातer_mode, पूर्णांक id)
अणु
	काष्ठा max77620_regulator_info *rinfo = pmic->rinfo[id];
	u8 mask = rinfo->घातer_mode_mask;
	u8 shअगरt = rinfo->घातer_mode_shअगरt;
	u8 addr;
	पूर्णांक ret;

	चयन (rinfo->type) अणु
	हाल MAX77620_REGULATOR_TYPE_SD:
		addr = rinfo->cfg_addr;
		अवरोध;
	शेष:
		addr = rinfo->volt_addr;
		अवरोध;
	पूर्ण

	ret = regmap_update_bits(pmic->rmap, addr, mask, घातer_mode << shअगरt);
	अगर (ret < 0) अणु
		dev_err(pmic->dev, "Regulator %d mode set failed: %d\n",
			id, ret);
		वापस ret;
	पूर्ण
	pmic->current_घातer_mode[id] = घातer_mode;

	वापस ret;
पूर्ण

अटल पूर्णांक max77620_regulator_get_घातer_mode(काष्ठा max77620_regulator *pmic,
					     पूर्णांक id)
अणु
	काष्ठा max77620_regulator_info *rinfo = pmic->rinfo[id];
	अचिन्हित पूर्णांक val, addr;
	u8 mask = rinfo->घातer_mode_mask;
	u8 shअगरt = rinfo->घातer_mode_shअगरt;
	पूर्णांक ret;

	चयन (rinfo->type) अणु
	हाल MAX77620_REGULATOR_TYPE_SD:
		addr = rinfo->cfg_addr;
		अवरोध;
	शेष:
		addr = rinfo->volt_addr;
		अवरोध;
	पूर्ण

	ret = regmap_पढ़ो(pmic->rmap, addr, &val);
	अगर (ret < 0) अणु
		dev_err(pmic->dev, "Regulator %d: Reg 0x%02x read failed: %d\n",
			id, addr, ret);
		वापस ret;
	पूर्ण

	वापस (val & mask) >> shअगरt;
पूर्ण

अटल पूर्णांक max77620_पढ़ो_slew_rate(काष्ठा max77620_regulator *pmic, पूर्णांक id)
अणु
	काष्ठा max77620_regulator_info *rinfo = pmic->rinfo[id];
	अचिन्हित पूर्णांक rval;
	पूर्णांक slew_rate;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pmic->rmap, rinfo->cfg_addr, &rval);
	अगर (ret < 0) अणु
		dev_err(pmic->dev, "Register 0x%02x read failed: %d\n",
			rinfo->cfg_addr, ret);
		वापस ret;
	पूर्ण

	चयन (rinfo->type) अणु
	हाल MAX77620_REGULATOR_TYPE_SD:
		slew_rate = (rval >> MAX77620_SD_SR_SHIFT) & 0x3;
		चयन (slew_rate) अणु
		हाल 0:
			slew_rate = 13750;
			अवरोध;
		हाल 1:
			slew_rate = 27500;
			अवरोध;
		हाल 2:
			slew_rate = 55000;
			अवरोध;
		हाल 3:
			slew_rate = 100000;
			अवरोध;
		पूर्ण
		rinfo->desc.ramp_delay = slew_rate;
		अवरोध;
	शेष:
		slew_rate = rval & 0x1;
		चयन (slew_rate) अणु
		हाल 0:
			slew_rate = 100000;
			अवरोध;
		हाल 1:
			slew_rate = 5000;
			अवरोध;
		पूर्ण
		rinfo->desc.ramp_delay = slew_rate;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_set_slew_rate(काष्ठा max77620_regulator *pmic, पूर्णांक id,
				  पूर्णांक slew_rate)
अणु
	काष्ठा max77620_regulator_info *rinfo = pmic->rinfo[id];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	u8 mask;

	अगर (rinfo->type == MAX77620_REGULATOR_TYPE_SD) अणु
		अगर (slew_rate <= 13750)
			val = 0;
		अन्यथा अगर (slew_rate <= 27500)
			val = 1;
		अन्यथा अगर (slew_rate <= 55000)
			val = 2;
		अन्यथा
			val = 3;
		val <<= MAX77620_SD_SR_SHIFT;
		mask = MAX77620_SD_SR_MASK;
	पूर्ण अन्यथा अणु
		अगर (slew_rate <= 5000)
			val = 1;
		अन्यथा
			val = 0;
		mask = MAX77620_LDO_SLEW_RATE_MASK;
	पूर्ण

	ret = regmap_update_bits(pmic->rmap, rinfo->cfg_addr, mask, val);
	अगर (ret < 0) अणु
		dev_err(pmic->dev, "Regulator %d slew rate set failed: %d\n",
			id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_config_घातer_ok(काष्ठा max77620_regulator *pmic, पूर्णांक id)
अणु
	काष्ठा max77620_regulator_pdata *rpdata = &pmic->reg_pdata[id];
	काष्ठा max77620_regulator_info *rinfo = pmic->rinfo[id];
	काष्ठा max77620_chip *chip = dev_get_drvdata(pmic->dev->parent);
	u8 val, mask;
	पूर्णांक ret;

	चयन (chip->chip_id) अणु
	हाल MAX20024:
		अगर (rpdata->घातer_ok >= 0) अणु
			अगर (rinfo->type == MAX77620_REGULATOR_TYPE_SD)
				mask = MAX20024_SD_CFG1_MPOK_MASK;
			अन्यथा
				mask = MAX20024_LDO_CFG2_MPOK_MASK;

			val = rpdata->घातer_ok ? mask : 0;

			ret = regmap_update_bits(pmic->rmap, rinfo->cfg_addr,
						 mask, val);
			अगर (ret < 0) अणु
				dev_err(pmic->dev, "Reg 0x%02x update failed %d\n",
					rinfo->cfg_addr, ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_init_pmic(काष्ठा max77620_regulator *pmic, पूर्णांक id)
अणु
	काष्ठा max77620_regulator_pdata *rpdata = &pmic->reg_pdata[id];
	पूर्णांक ret;

	max77620_config_घातer_ok(pmic, id);

	/* Update घातer mode */
	ret = max77620_regulator_get_घातer_mode(pmic, id);
	अगर (ret < 0)
		वापस ret;

	pmic->current_घातer_mode[id] = ret;
	pmic->enable_घातer_mode[id] = MAX77620_POWER_MODE_NORMAL;

	अगर (rpdata->active_fps_src == MAX77620_FPS_SRC_DEF) अणु
		ret = max77620_regulator_get_fps_src(pmic, id);
		अगर (ret < 0)
			वापस ret;
		rpdata->active_fps_src = ret;
	पूर्ण

	 /* If rails are बाह्यally control of FPS then enable it always. */
	अगर (rpdata->active_fps_src == MAX77620_FPS_SRC_NONE) अणु
		ret = max77620_regulator_set_घातer_mode(pmic,
					pmic->enable_घातer_mode[id], id);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		अगर (pmic->current_घातer_mode[id] !=
		     pmic->enable_घातer_mode[id]) अणु
			ret = max77620_regulator_set_घातer_mode(pmic,
					pmic->enable_घातer_mode[id], id);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = max77620_regulator_set_fps_src(pmic, rpdata->active_fps_src, id);
	अगर (ret < 0)
		वापस ret;

	ret = max77620_regulator_set_fps_slots(pmic, id, false);
	अगर (ret < 0)
		वापस ret;

	अगर (rpdata->ramp_rate_setting) अणु
		ret = max77620_set_slew_rate(pmic, id,
					     rpdata->ramp_rate_setting);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max77620_regulator *pmic = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);

	अगर (pmic->active_fps_src[id] != MAX77620_FPS_SRC_NONE)
		वापस 0;

	वापस max77620_regulator_set_घातer_mode(pmic,
			pmic->enable_घातer_mode[id], id);
पूर्ण

अटल पूर्णांक max77620_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max77620_regulator *pmic = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);

	अगर (pmic->active_fps_src[id] != MAX77620_FPS_SRC_NONE)
		वापस 0;

	वापस max77620_regulator_set_घातer_mode(pmic,
			MAX77620_POWER_MODE_DISABLE, id);
पूर्ण

अटल पूर्णांक max77620_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max77620_regulator *pmic = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक ret;

	अगर (pmic->active_fps_src[id] != MAX77620_FPS_SRC_NONE)
		वापस 1;

	ret = max77620_regulator_get_घातer_mode(pmic, id);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != MAX77620_POWER_MODE_DISABLE)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_regulator_set_mode(काष्ठा regulator_dev *rdev,
				       अचिन्हित पूर्णांक mode)
अणु
	काष्ठा max77620_regulator *pmic = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा max77620_regulator_info *rinfo = pmic->rinfo[id];
	काष्ठा max77620_regulator_pdata *rpdata = &pmic->reg_pdata[id];
	bool fpwm = false;
	पूर्णांक घातer_mode;
	पूर्णांक ret;
	u8 val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		fpwm = true;
		घातer_mode = MAX77620_POWER_MODE_NORMAL;
		अवरोध;

	हाल REGULATOR_MODE_NORMAL:
		घातer_mode = MAX77620_POWER_MODE_NORMAL;
		अवरोध;

	हाल REGULATOR_MODE_IDLE:
		घातer_mode = MAX77620_POWER_MODE_LPM;
		अवरोध;

	शेष:
		dev_err(pmic->dev, "Regulator %d mode %d is invalid\n",
			id, mode);
		वापस -EINVAL;
	पूर्ण

	अगर (rinfo->type != MAX77620_REGULATOR_TYPE_SD)
		जाओ skip_fpwm;

	val = (fpwm) ? MAX77620_SD_FPWM_MASK : 0;
	ret = regmap_update_bits(pmic->rmap, rinfo->cfg_addr,
				 MAX77620_SD_FPWM_MASK, val);
	अगर (ret < 0) अणु
		dev_err(pmic->dev, "Reg 0x%02x update failed: %d\n",
			rinfo->cfg_addr, ret);
		वापस ret;
	पूर्ण
	rpdata->current_mode = mode;

skip_fpwm:
	ret = max77620_regulator_set_घातer_mode(pmic, घातer_mode, id);
	अगर (ret < 0)
		वापस ret;

	pmic->enable_घातer_mode[id] = घातer_mode;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक max77620_regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max77620_regulator *pmic = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा max77620_regulator_info *rinfo = pmic->rinfo[id];
	पूर्णांक fpwm = 0;
	पूर्णांक ret;
	पूर्णांक pm_mode, reg_mode;
	अचिन्हित पूर्णांक val;

	ret = max77620_regulator_get_घातer_mode(pmic, id);
	अगर (ret < 0)
		वापस 0;

	pm_mode = ret;

	अगर (rinfo->type == MAX77620_REGULATOR_TYPE_SD) अणु
		ret = regmap_पढ़ो(pmic->rmap, rinfo->cfg_addr, &val);
		अगर (ret < 0) अणु
			dev_err(pmic->dev, "Reg 0x%02x read failed: %d\n",
				rinfo->cfg_addr, ret);
			वापस ret;
		पूर्ण
		fpwm = !!(val & MAX77620_SD_FPWM_MASK);
	पूर्ण

	चयन (pm_mode) अणु
	हाल MAX77620_POWER_MODE_NORMAL:
	हाल MAX77620_POWER_MODE_DISABLE:
		अगर (fpwm)
			reg_mode = REGULATOR_MODE_FAST;
		अन्यथा
			reg_mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	हाल MAX77620_POWER_MODE_LPM:
	हाल MAX77620_POWER_MODE_GLPM:
		reg_mode = REGULATOR_MODE_IDLE;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस reg_mode;
पूर्ण

अटल पूर्णांक max77620_regulator_set_ramp_delay(काष्ठा regulator_dev *rdev,
					     पूर्णांक ramp_delay)
अणु
	काष्ठा max77620_regulator *pmic = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा max77620_regulator_pdata *rpdata = &pmic->reg_pdata[id];

	/* Device specअगरic ramp rate setting tells that platक्रमm has
	 * dअगरferent ramp rate from advertised value. In this हाल,
	 * करो not configure anything and just वापस success.
	 */
	अगर (rpdata->ramp_rate_setting)
		वापस 0;

	वापस max77620_set_slew_rate(pmic, id, ramp_delay);
पूर्ण

अटल पूर्णांक max77620_of_parse_cb(काष्ठा device_node *np,
				स्थिर काष्ठा regulator_desc *desc,
				काष्ठा regulator_config *config)
अणु
	काष्ठा max77620_regulator *pmic = config->driver_data;
	काष्ठा max77620_regulator_pdata *rpdata = &pmic->reg_pdata[desc->id];
	u32 pval;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "maxim,active-fps-source", &pval);
	rpdata->active_fps_src = (!ret) ? pval : MAX77620_FPS_SRC_DEF;

	ret = of_property_पढ़ो_u32(np, "maxim,active-fps-power-up-slot", &pval);
	rpdata->active_fps_pu_slot = (!ret) ? pval : -1;

	ret = of_property_पढ़ो_u32(
			np, "maxim,active-fps-power-down-slot", &pval);
	rpdata->active_fps_pd_slot = (!ret) ? pval : -1;

	ret = of_property_पढ़ो_u32(np, "maxim,suspend-fps-source", &pval);
	rpdata->suspend_fps_src = (!ret) ? pval : -1;

	ret = of_property_पढ़ो_u32(
			np, "maxim,suspend-fps-power-up-slot", &pval);
	rpdata->suspend_fps_pu_slot = (!ret) ? pval : -1;

	ret = of_property_पढ़ो_u32(
			np, "maxim,suspend-fps-power-down-slot", &pval);
	rpdata->suspend_fps_pd_slot = (!ret) ? pval : -1;

	ret = of_property_पढ़ो_u32(np, "maxim,power-ok-control", &pval);
	अगर (!ret)
		rpdata->घातer_ok = pval;
	अन्यथा
		rpdata->घातer_ok = -1;

	ret = of_property_पढ़ो_u32(np, "maxim,ramp-rate-setting", &pval);
	rpdata->ramp_rate_setting = (!ret) ? pval : 0;

	वापस max77620_init_pmic(pmic, desc->id);
पूर्ण

अटल स्थिर काष्ठा regulator_ops max77620_regulator_ops = अणु
	.is_enabled = max77620_regulator_is_enabled,
	.enable = max77620_regulator_enable,
	.disable = max77620_regulator_disable,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.set_mode = max77620_regulator_set_mode,
	.get_mode = max77620_regulator_get_mode,
	.set_ramp_delay = max77620_regulator_set_ramp_delay,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.set_active_disअक्षरge = regulator_set_active_disअक्षरge_regmap,
पूर्ण;

#घोषणा MAX77620_SD_CNF2_ROVS_EN_NONE	0
#घोषणा RAIL_SD(_id, _name, _sname, _volt_mask, _min_uV, _max_uV,	\
		_step_uV, _rs_add, _rs_mask)				\
	[MAX77620_REGULATOR_ID_##_id] = अणु				\
		.type = MAX77620_REGULATOR_TYPE_SD,			\
		.volt_addr = MAX77620_REG_##_id,			\
		.cfg_addr = MAX77620_REG_##_id##_CFG,			\
		.fps_addr = MAX77620_REG_FPS_##_id,			\
		.remote_sense_addr = _rs_add,				\
		.remote_sense_mask = MAX77620_SD_CNF2_ROVS_EN_##_rs_mask, \
		.घातer_mode_mask = MAX77620_SD_POWER_MODE_MASK,		\
		.घातer_mode_shअगरt = MAX77620_SD_POWER_MODE_SHIFT,	\
		.desc = अणु						\
			.name = max77620_rails(_name),			\
			.of_match = of_match_ptr(#_name),		\
			.regulators_node = of_match_ptr("regulators"),	\
			.of_parse_cb = max77620_of_parse_cb,		\
			.supply_name = _sname,				\
			.id = MAX77620_REGULATOR_ID_##_id,		\
			.ops = &max77620_regulator_ops,			\
			.n_voltages = ((_max_uV - _min_uV) / _step_uV) + 1, \
			.min_uV = _min_uV,				\
			.uV_step = _step_uV,				\
			.enable_समय = 500,				\
			.vsel_mask = MAX77620_##_volt_mask##_VOLT_MASK,	\
			.vsel_reg = MAX77620_REG_##_id,			\
			.active_disअक्षरge_off = 0,			\
			.active_disअक्षरge_on = MAX77620_SD_CFG1_ADE_ENABLE, \
			.active_disअक्षरge_mask = MAX77620_SD_CFG1_ADE_MASK, \
			.active_disअक्षरge_reg = MAX77620_REG_##_id##_CFG, \
			.type = REGULATOR_VOLTAGE,			\
			.owner = THIS_MODULE,				\
		पूर्ण,							\
	पूर्ण

#घोषणा RAIL_LDO(_id, _name, _sname, _type, _min_uV, _max_uV, _step_uV) \
	[MAX77620_REGULATOR_ID_##_id] = अणु				\
		.type = MAX77620_REGULATOR_TYPE_LDO_##_type,		\
		.volt_addr = MAX77620_REG_##_id##_CFG,			\
		.cfg_addr = MAX77620_REG_##_id##_CFG2,			\
		.fps_addr = MAX77620_REG_FPS_##_id,			\
		.remote_sense_addr = 0xFF,				\
		.घातer_mode_mask = MAX77620_LDO_POWER_MODE_MASK,	\
		.घातer_mode_shअगरt = MAX77620_LDO_POWER_MODE_SHIFT,	\
		.desc = अणु						\
			.name = max77620_rails(_name),			\
			.of_match = of_match_ptr(#_name),		\
			.regulators_node = of_match_ptr("regulators"),	\
			.of_parse_cb = max77620_of_parse_cb,		\
			.supply_name = _sname,				\
			.id = MAX77620_REGULATOR_ID_##_id,		\
			.ops = &max77620_regulator_ops,			\
			.n_voltages = ((_max_uV - _min_uV) / _step_uV) + 1, \
			.min_uV = _min_uV,				\
			.uV_step = _step_uV,				\
			.enable_समय = 500,				\
			.vsel_mask = MAX77620_LDO_VOLT_MASK,		\
			.vsel_reg = MAX77620_REG_##_id##_CFG,		\
			.active_disअक्षरge_off = 0,			\
			.active_disअक्षरge_on = MAX77620_LDO_CFG2_ADE_ENABLE, \
			.active_disअक्षरge_mask = MAX77620_LDO_CFG2_ADE_MASK, \
			.active_disअक्षरge_reg = MAX77620_REG_##_id##_CFG2, \
			.type = REGULATOR_VOLTAGE,			\
			.owner = THIS_MODULE,				\
		पूर्ण,							\
	पूर्ण

अटल काष्ठा max77620_regulator_info max77620_regs_info[MAX77620_NUM_REGS] = अणु
	RAIL_SD(SD0, sd0, "in-sd0", SD0, 600000, 1400000, 12500, 0x22, SD0),
	RAIL_SD(SD1, sd1, "in-sd1", SD1, 600000, 1550000, 12500, 0x22, SD1),
	RAIL_SD(SD2, sd2, "in-sd2", SDX, 600000, 3787500, 12500, 0xFF, NONE),
	RAIL_SD(SD3, sd3, "in-sd3", SDX, 600000, 3787500, 12500, 0xFF, NONE),

	RAIL_LDO(LDO0, lकरो0, "in-ldo0-1", N, 800000, 2375000, 25000),
	RAIL_LDO(LDO1, lकरो1, "in-ldo0-1", N, 800000, 2375000, 25000),
	RAIL_LDO(LDO2, lकरो2, "in-ldo2",   P, 800000, 3950000, 50000),
	RAIL_LDO(LDO3, lकरो3, "in-ldo3-5", P, 800000, 3950000, 50000),
	RAIL_LDO(LDO4, lकरो4, "in-ldo4-6", P, 800000, 1587500, 12500),
	RAIL_LDO(LDO5, lकरो5, "in-ldo3-5", P, 800000, 3950000, 50000),
	RAIL_LDO(LDO6, lकरो6, "in-ldo4-6", P, 800000, 3950000, 50000),
	RAIL_LDO(LDO7, lकरो7, "in-ldo7-8", N, 800000, 3950000, 50000),
	RAIL_LDO(LDO8, lकरो8, "in-ldo7-8", N, 800000, 3950000, 50000),
पूर्ण;

अटल काष्ठा max77620_regulator_info max20024_regs_info[MAX77620_NUM_REGS] = अणु
	RAIL_SD(SD0, sd0, "in-sd0", SD0, 800000, 1587500, 12500, 0x22, SD0),
	RAIL_SD(SD1, sd1, "in-sd1", SD1, 600000, 3387500, 12500, 0x22, SD1),
	RAIL_SD(SD2, sd2, "in-sd2", SDX, 600000, 3787500, 12500, 0xFF, NONE),
	RAIL_SD(SD3, sd3, "in-sd3", SDX, 600000, 3787500, 12500, 0xFF, NONE),
	RAIL_SD(SD4, sd4, "in-sd4", SDX, 600000, 3787500, 12500, 0xFF, NONE),

	RAIL_LDO(LDO0, lकरो0, "in-ldo0-1", N, 800000, 2375000, 25000),
	RAIL_LDO(LDO1, lकरो1, "in-ldo0-1", N, 800000, 2375000, 25000),
	RAIL_LDO(LDO2, lकरो2, "in-ldo2",   P, 800000, 3950000, 50000),
	RAIL_LDO(LDO3, lकरो3, "in-ldo3-5", P, 800000, 3950000, 50000),
	RAIL_LDO(LDO4, lकरो4, "in-ldo4-6", P, 800000, 1587500, 12500),
	RAIL_LDO(LDO5, lकरो5, "in-ldo3-5", P, 800000, 3950000, 50000),
	RAIL_LDO(LDO6, lकरो6, "in-ldo4-6", P, 800000, 3950000, 50000),
	RAIL_LDO(LDO7, lकरो7, "in-ldo7-8", N, 800000, 3950000, 50000),
	RAIL_LDO(LDO8, lकरो8, "in-ldo7-8", N, 800000, 3950000, 50000),
पूर्ण;

अटल काष्ठा max77620_regulator_info max77663_regs_info[MAX77620_NUM_REGS] = अणु
	RAIL_SD(SD0, sd0, "in-sd0", SD0, 600000, 3387500, 12500, 0xFF, NONE),
	RAIL_SD(SD1, sd1, "in-sd1", SD1, 800000, 1587500, 12500, 0xFF, NONE),
	RAIL_SD(SD2, sd2, "in-sd2", SDX, 600000, 3787500, 12500, 0xFF, NONE),
	RAIL_SD(SD3, sd3, "in-sd3", SDX, 600000, 3787500, 12500, 0xFF, NONE),
	RAIL_SD(SD4, sd4, "in-sd4", SDX, 600000, 3787500, 12500, 0xFF, NONE),

	RAIL_LDO(LDO0, lकरो0, "in-ldo0-1", N, 800000, 2375000, 25000),
	RAIL_LDO(LDO1, lकरो1, "in-ldo0-1", N, 800000, 2375000, 25000),
	RAIL_LDO(LDO2, lकरो2, "in-ldo2",   P, 800000, 3950000, 50000),
	RAIL_LDO(LDO3, lकरो3, "in-ldo3-5", P, 800000, 3950000, 50000),
	RAIL_LDO(LDO4, lकरो4, "in-ldo4-6", P, 800000, 1587500, 12500),
	RAIL_LDO(LDO5, lकरो5, "in-ldo3-5", P, 800000, 3950000, 50000),
	RAIL_LDO(LDO6, lकरो6, "in-ldo4-6", P, 800000, 3950000, 50000),
	RAIL_LDO(LDO7, lकरो7, "in-ldo7-8", N, 800000, 3950000, 50000),
	RAIL_LDO(LDO8, lकरो8, "in-ldo7-8", N, 800000, 3950000, 50000),
पूर्ण;

अटल पूर्णांक max77620_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77620_chip *max77620_chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max77620_regulator_info *rinfo;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा max77620_regulator *pmic;
	पूर्णांक ret = 0;
	पूर्णांक id;

	pmic = devm_kzalloc(dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pmic);
	pmic->dev = dev;
	pmic->rmap = max77620_chip->rmap;
	अगर (!dev->of_node)
		dev->of_node = pdev->dev.parent->of_node;

	चयन (max77620_chip->chip_id) अणु
	हाल MAX77620:
		rinfo = max77620_regs_info;
		अवरोध;
	हाल MAX20024:
		rinfo = max20024_regs_info;
		अवरोध;
	हाल MAX77663:
		rinfo = max77663_regs_info;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	config.regmap = pmic->rmap;
	config.dev = dev;
	config.driver_data = pmic;

	/*
	 * Set of_node_reuse flag to prevent driver core from attempting to
	 * claim any pinmux resources alपढ़ोy claimed by the parent device.
	 * Otherwise PMIC driver will fail to re-probe.
	 */
	device_set_of_node_from_dev(&pdev->dev, pdev->dev.parent);

	क्रम (id = 0; id < MAX77620_NUM_REGS; id++) अणु
		काष्ठा regulator_dev *rdev;
		काष्ठा regulator_desc *rdesc;

		अगर ((max77620_chip->chip_id == MAX77620) &&
		    (id == MAX77620_REGULATOR_ID_SD4))
			जारी;

		rdesc = &rinfo[id].desc;
		pmic->rinfo[id] = &rinfo[id];
		pmic->enable_घातer_mode[id] = MAX77620_POWER_MODE_NORMAL;
		pmic->reg_pdata[id].active_fps_src = -1;
		pmic->reg_pdata[id].active_fps_pd_slot = -1;
		pmic->reg_pdata[id].active_fps_pu_slot = -1;
		pmic->reg_pdata[id].suspend_fps_src = -1;
		pmic->reg_pdata[id].suspend_fps_pd_slot = -1;
		pmic->reg_pdata[id].suspend_fps_pu_slot = -1;
		pmic->reg_pdata[id].घातer_ok = -1;
		pmic->reg_pdata[id].ramp_rate_setting = -1;

		ret = max77620_पढ़ो_slew_rate(pmic, id);
		अगर (ret < 0)
			वापस ret;

		rdev = devm_regulator_रेजिस्टर(dev, rdesc, &config);
		अगर (IS_ERR(rdev))
			वापस dev_err_probe(dev, PTR_ERR(rdev),
					     "Regulator registration %s failed\n",
					     rdesc->name);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max77620_regulator_suspend(काष्ठा device *dev)
अणु
	काष्ठा max77620_regulator *pmic = dev_get_drvdata(dev);
	काष्ठा max77620_regulator_pdata *reg_pdata;
	पूर्णांक id;

	क्रम (id = 0; id < MAX77620_NUM_REGS; id++) अणु
		reg_pdata = &pmic->reg_pdata[id];

		max77620_regulator_set_fps_slots(pmic, id, true);
		अगर (reg_pdata->suspend_fps_src < 0)
			जारी;

		max77620_regulator_set_fps_src(pmic, reg_pdata->suspend_fps_src,
					       id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_regulator_resume(काष्ठा device *dev)
अणु
	काष्ठा max77620_regulator *pmic = dev_get_drvdata(dev);
	काष्ठा max77620_regulator_pdata *reg_pdata;
	पूर्णांक id;

	क्रम (id = 0; id < MAX77620_NUM_REGS; id++) अणु
		reg_pdata = &pmic->reg_pdata[id];

		max77620_config_घातer_ok(pmic, id);

		max77620_regulator_set_fps_slots(pmic, id, false);
		अगर (reg_pdata->active_fps_src < 0)
			जारी;
		max77620_regulator_set_fps_src(pmic, reg_pdata->active_fps_src,
					       id);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops max77620_regulator_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(max77620_regulator_suspend,
				max77620_regulator_resume)
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id max77620_regulator_devtype[] = अणु
	अणु .name = "max77620-pmic", पूर्ण,
	अणु .name = "max20024-pmic", पूर्ण,
	अणु .name = "max77663-pmic", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77620_regulator_devtype);

अटल काष्ठा platक्रमm_driver max77620_regulator_driver = अणु
	.probe = max77620_regulator_probe,
	.id_table = max77620_regulator_devtype,
	.driver = अणु
		.name = "max77620-pmic",
		.pm = &max77620_regulator_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(max77620_regulator_driver);

MODULE_DESCRIPTION("MAX77620/MAX20024 regulator driver");
MODULE_AUTHOR("Mallikarjun Kasoju <mkasoju@nvidia.com>");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
