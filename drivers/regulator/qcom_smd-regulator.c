<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Sony Mobile Communications AB.
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/soc/qcom/smd-rpm.h>

काष्ठा qcom_rpm_reg अणु
	काष्ठा device *dev;

	काष्ठा qcom_smd_rpm *rpm;

	u32 type;
	u32 id;

	काष्ठा regulator_desc desc;

	पूर्णांक is_enabled;
	पूर्णांक uV;
	u32 load;

	अचिन्हित पूर्णांक enabled_updated:1;
	अचिन्हित पूर्णांक uv_updated:1;
	अचिन्हित पूर्णांक load_updated:1;
पूर्ण;

काष्ठा rpm_regulator_req अणु
	__le32 key;
	__le32 nbytes;
	__le32 value;
पूर्ण;

#घोषणा RPM_KEY_SWEN	0x6e657773 /* "swen" */
#घोषणा RPM_KEY_UV	0x00007675 /* "uv" */
#घोषणा RPM_KEY_MA	0x0000616d /* "ma" */

अटल पूर्णांक rpm_reg_ग_लिखो_active(काष्ठा qcom_rpm_reg *vreg)
अणु
	काष्ठा rpm_regulator_req req[3];
	पूर्णांक reqlen = 0;
	पूर्णांक ret;

	अगर (vreg->enabled_updated) अणु
		req[reqlen].key = cpu_to_le32(RPM_KEY_SWEN);
		req[reqlen].nbytes = cpu_to_le32(माप(u32));
		req[reqlen].value = cpu_to_le32(vreg->is_enabled);
		reqlen++;
	पूर्ण

	अगर (vreg->uv_updated && vreg->is_enabled) अणु
		req[reqlen].key = cpu_to_le32(RPM_KEY_UV);
		req[reqlen].nbytes = cpu_to_le32(माप(u32));
		req[reqlen].value = cpu_to_le32(vreg->uV);
		reqlen++;
	पूर्ण

	अगर (vreg->load_updated && vreg->is_enabled) अणु
		req[reqlen].key = cpu_to_le32(RPM_KEY_MA);
		req[reqlen].nbytes = cpu_to_le32(माप(u32));
		req[reqlen].value = cpu_to_le32(vreg->load / 1000);
		reqlen++;
	पूर्ण

	अगर (!reqlen)
		वापस 0;

	ret = qcom_rpm_smd_ग_लिखो(vreg->rpm, QCOM_SMD_RPM_ACTIVE_STATE,
				 vreg->type, vreg->id,
				 req, माप(req[0]) * reqlen);
	अगर (!ret) अणु
		vreg->enabled_updated = 0;
		vreg->uv_updated = 0;
		vreg->load_updated = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	vreg->is_enabled = 1;
	vreg->enabled_updated = 1;

	ret = rpm_reg_ग_लिखो_active(vreg);
	अगर (ret)
		vreg->is_enabled = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);

	वापस vreg->is_enabled;
पूर्ण

अटल पूर्णांक rpm_reg_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	vreg->is_enabled = 0;
	vreg->enabled_updated = 1;

	ret = rpm_reg_ग_लिखो_active(vreg);
	अगर (ret)
		vreg->is_enabled = 1;

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);

	वापस vreg->uV;
पूर्ण

अटल पूर्णांक rpm_reg_set_voltage(काष्ठा regulator_dev *rdev,
			       पूर्णांक min_uV,
			       पूर्णांक max_uV,
			       अचिन्हित *selector)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	पूर्णांक ret;
	पूर्णांक old_uV = vreg->uV;

	vreg->uV = min_uV;
	vreg->uv_updated = 1;

	ret = rpm_reg_ग_लिखो_active(vreg);
	अगर (ret)
		vreg->uV = old_uV;

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_set_load(काष्ठा regulator_dev *rdev, पूर्णांक load_uA)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	u32 old_load = vreg->load;
	पूर्णांक ret;

	vreg->load = load_uA;
	vreg->load_updated = 1;
	ret = rpm_reg_ग_लिखो_active(vreg);
	अगर (ret)
		vreg->load = old_load;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops rpm_smps_lकरो_ops = अणु
	.enable = rpm_reg_enable,
	.disable = rpm_reg_disable,
	.is_enabled = rpm_reg_is_enabled,
	.list_voltage = regulator_list_voltage_linear_range,

	.get_voltage = rpm_reg_get_voltage,
	.set_voltage = rpm_reg_set_voltage,

	.set_load = rpm_reg_set_load,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rpm_smps_lकरो_ops_fixed = अणु
	.enable = rpm_reg_enable,
	.disable = rpm_reg_disable,
	.is_enabled = rpm_reg_is_enabled,

	.get_voltage = rpm_reg_get_voltage,
	.set_voltage = rpm_reg_set_voltage,

	.set_load = rpm_reg_set_load,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rpm_चयन_ops = अणु
	.enable = rpm_reg_enable,
	.disable = rpm_reg_disable,
	.is_enabled = rpm_reg_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rpm_bob_ops = अणु
	.enable = rpm_reg_enable,
	.disable = rpm_reg_disable,
	.is_enabled = rpm_reg_is_enabled,

	.get_voltage = rpm_reg_get_voltage,
	.set_voltage = rpm_reg_set_voltage,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rpm_mp5496_ops = अणु
	.enable = rpm_reg_enable,
	.disable = rpm_reg_disable,
	.is_enabled = rpm_reg_is_enabled,
	.list_voltage = regulator_list_voltage_linear_range,

	.set_voltage = rpm_reg_set_voltage,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pma8084_hfsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(375000,  0,  95, 12500),
		REGULATOR_LINEAR_RANGE(1550000, 96, 158, 25000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 159,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pma8084_ftsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(350000,  0, 184, 5000),
		REGULATOR_LINEAR_RANGE(1280000, 185, 261, 10000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 262,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pma8084_plकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE( 750000,  0,  63, 12500),
		REGULATOR_LINEAR_RANGE(1550000, 64, 126, 25000),
		REGULATOR_LINEAR_RANGE(3100000, 127, 163, 50000),
	पूर्ण,
	.n_linear_ranges = 3,
	.n_voltages = 164,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pma8084_nlकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(750000, 0, 63, 12500),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 64,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pma8084_चयन = अणु
	.ops = &rpm_चयन_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8x41_hfsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE( 375000,  0,  95, 12500),
		REGULATOR_LINEAR_RANGE(1575000, 96, 158, 25000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 159,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8841_ftsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(350000,  0, 184, 5000),
		REGULATOR_LINEAR_RANGE(1280000, 185, 261, 10000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 262,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8941_boost = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(4000000, 0, 30, 50000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 31,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8941_plकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE( 750000,  0,  63, 12500),
		REGULATOR_LINEAR_RANGE(1550000, 64, 126, 25000),
		REGULATOR_LINEAR_RANGE(3100000, 127, 163, 50000),
	पूर्ण,
	.n_linear_ranges = 3,
	.n_voltages = 164,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8941_nlकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(750000, 0, 63, 12500),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 64,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8941_lnlकरो = अणु
	.fixed_uV = 1740000,
	.n_voltages = 1,
	.ops = &rpm_smps_lकरो_ops_fixed,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8941_चयन = अणु
	.ops = &rpm_चयन_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8916_plकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(750000, 0, 208, 12500),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 209,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8916_nlकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(375000, 0, 93, 12500),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 94,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8916_buck_lvo_smps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(375000, 0, 95, 12500),
		REGULATOR_LINEAR_RANGE(750000, 96, 127, 25000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 128,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8916_buck_hvo_smps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1550000, 0, 31, 25000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 32,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8950_hfsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(375000, 0, 95, 12500),
		REGULATOR_LINEAR_RANGE(1550000, 96, 127, 25000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 128,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8950_ftsmps2p5 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(80000, 0, 255, 5000),
		REGULATOR_LINEAR_RANGE(160000, 256, 460, 10000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 461,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8950_ult_nlकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(375000, 0, 202, 12500),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 203,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8950_ult_plकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1750000, 0, 127, 12500),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 128,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8950_plकरो_lv = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1500000, 0, 16, 25000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 17,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8950_plकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(975000, 0, 164, 12500),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 165,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8953_lnlकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1380000, 8, 15, 120000),
		REGULATOR_LINEAR_RANGE(690000, 0, 7, 60000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 16,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8953_ult_nlकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(375000, 0, 93, 12500),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 94,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8994_hfsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE( 375000,  0,  95, 12500),
		REGULATOR_LINEAR_RANGE(1550000, 96, 158, 25000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 159,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8994_ftsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(350000,  0, 199, 5000),
		REGULATOR_LINEAR_RANGE(700000, 200, 349, 10000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 350,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8994_nlकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(750000, 0, 63, 12500),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 64,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8994_plकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE( 750000,  0,  63, 12500),
		REGULATOR_LINEAR_RANGE(1550000, 64, 126, 25000),
		REGULATOR_LINEAR_RANGE(3100000, 127, 163, 50000),
	पूर्ण,
	.n_linear_ranges = 3,
	.n_voltages = 164,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8994_चयन = अणु
	.ops = &rpm_चयन_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8994_lnlकरो = अणु
	.fixed_uV = 1740000,
	.n_voltages = 1,
	.ops = &rpm_smps_lकरो_ops_fixed,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pmi8994_ftsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(350000,  0, 199, 5000),
		REGULATOR_LINEAR_RANGE(700000, 200, 349, 10000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 350,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pmi8994_hfsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(350000,  0,  80, 12500),
		REGULATOR_LINEAR_RANGE(700000, 81, 141, 25000),
	पूर्ण,
	.n_linear_ranges = 2,
	.n_voltages = 142,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pmi8994_bby = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(3000000, 0, 44, 50000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 45,
	.ops = &rpm_bob_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8998_ftsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(320000, 0, 258, 4000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 259,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8998_hfsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(320000, 0, 215, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 216,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8998_nlकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(312000, 0, 127, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 128,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8998_plकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1664000, 0, 255, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 256,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8998_plकरो_lv = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1256000, 0, 127, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 128,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm8998_चयन = अणु
	.ops = &rpm_चयन_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pmi8998_bob = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1824000, 0, 83, 32000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 84,
	.ops = &rpm_bob_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm660_ftsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(355000, 0, 199, 5000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 200,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm660_hfsmps = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(320000, 0, 216, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 217,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm660_ht_nlकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(312000, 0, 124, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 125,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm660_ht_lvplकरो = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1504000, 0, 62, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 63,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm660_nlकरो660 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(320000, 0, 123, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 124,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm660_plकरो660 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1504000, 0, 255, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 256,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pm660l_bob = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1800000, 0, 84, 32000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 85,
	.ops = &rpm_bob_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pms405_hfsmps3 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(320000, 0, 215, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 216,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pms405_nlकरो300 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(312000, 0, 127, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 128,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pms405_nlकरो1200 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(312000, 0, 127, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 128,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pms405_plकरो50 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1664000, 0, 128, 16000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 129,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pms405_plकरो150 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1664000, 0, 128, 16000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 129,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pms405_plकरो600 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1256000, 0, 98, 8000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 99,
	.ops = &rpm_smps_lकरो_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc mp5496_smpa2 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(725000, 0, 27, 12500),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 28,
	.ops = &rpm_mp5496_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc mp5496_lकरोa2 = अणु
	.linear_ranges = (काष्ठा linear_range[]) अणु
		REGULATOR_LINEAR_RANGE(1800000, 0, 60, 25000),
	पूर्ण,
	.n_linear_ranges = 1,
	.n_voltages = 61,
	.ops = &rpm_mp5496_ops,
पूर्ण;

काष्ठा rpm_regulator_data अणु
	स्थिर अक्षर *name;
	u32 type;
	u32 id;
	स्थिर काष्ठा regulator_desc *desc;
	स्थिर अक्षर *supply;
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_mp5496_regulators[] = अणु
	अणु "s2", QCOM_SMD_RPM_SMPA, 2, &mp5496_smpa2, "s2" पूर्ण,
	अणु "l2", QCOM_SMD_RPM_LDOA, 2, &mp5496_lकरोa2, "l2" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8841_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPB, 1, &pm8x41_hfsmps, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPB, 2, &pm8841_ftsmps, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_SMPB, 3, &pm8x41_hfsmps, "vdd_s3" पूर्ण,
	अणु "s4", QCOM_SMD_RPM_SMPB, 4, &pm8841_ftsmps, "vdd_s4" पूर्ण,
	अणु "s5", QCOM_SMD_RPM_SMPB, 5, &pm8841_ftsmps, "vdd_s5" पूर्ण,
	अणु "s6", QCOM_SMD_RPM_SMPB, 6, &pm8841_ftsmps, "vdd_s6" पूर्ण,
	अणु "s7", QCOM_SMD_RPM_SMPB, 7, &pm8841_ftsmps, "vdd_s7" पूर्ण,
	अणु "s8", QCOM_SMD_RPM_SMPB, 8, &pm8841_ftsmps, "vdd_s8" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8916_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPA, 1, &pm8916_buck_lvo_smps, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPA, 2, &pm8916_buck_lvo_smps, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_SMPA, 3, &pm8916_buck_lvo_smps, "vdd_s3" पूर्ण,
	अणु "s4", QCOM_SMD_RPM_SMPA, 4, &pm8916_buck_hvo_smps, "vdd_s4" पूर्ण,
	अणु "l1", QCOM_SMD_RPM_LDOA, 1, &pm8916_nlकरो, "vdd_l1_l2_l3" पूर्ण,
	अणु "l2", QCOM_SMD_RPM_LDOA, 2, &pm8916_nlकरो, "vdd_l1_l2_l3" पूर्ण,
	अणु "l3", QCOM_SMD_RPM_LDOA, 3, &pm8916_nlकरो, "vdd_l1_l2_l3" पूर्ण,
	अणु "l4", QCOM_SMD_RPM_LDOA, 4, &pm8916_plकरो, "vdd_l4_l5_l6" पूर्ण,
	अणु "l5", QCOM_SMD_RPM_LDOA, 5, &pm8916_plकरो, "vdd_l4_l5_l6" पूर्ण,
	अणु "l6", QCOM_SMD_RPM_LDOA, 6, &pm8916_plकरो, "vdd_l4_l5_l6" पूर्ण,
	अणु "l7", QCOM_SMD_RPM_LDOA, 7, &pm8916_plकरो, "vdd_l7" पूर्ण,
	अणु "l8", QCOM_SMD_RPM_LDOA, 8, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18" पूर्ण,
	अणु "l9", QCOM_SMD_RPM_LDOA, 9, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18" पूर्ण,
	अणु "l10", QCOM_SMD_RPM_LDOA, 10, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18"पूर्ण,
	अणु "l11", QCOM_SMD_RPM_LDOA, 11, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18"पूर्ण,
	अणु "l12", QCOM_SMD_RPM_LDOA, 12, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18"पूर्ण,
	अणु "l13", QCOM_SMD_RPM_LDOA, 13, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18"पूर्ण,
	अणु "l14", QCOM_SMD_RPM_LDOA, 14, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18"पूर्ण,
	अणु "l15", QCOM_SMD_RPM_LDOA, 15, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18"पूर्ण,
	अणु "l16", QCOM_SMD_RPM_LDOA, 16, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18"पूर्ण,
	अणु "l17", QCOM_SMD_RPM_LDOA, 17, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18"पूर्ण,
	अणु "l18", QCOM_SMD_RPM_LDOA, 18, &pm8916_plकरो, "vdd_l8_l9_l10_l11_l12_l13_l14_l15_l16_l17_l18"पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8941_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPA, 1, &pm8x41_hfsmps, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPA, 2, &pm8x41_hfsmps, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_SMPA, 3, &pm8x41_hfsmps, "vdd_s3" पूर्ण,
	अणु "s4", QCOM_SMD_RPM_BOOST, 1, &pm8941_boost पूर्ण,

	अणु "l1", QCOM_SMD_RPM_LDOA, 1, &pm8941_nlकरो, "vdd_l1_l3" पूर्ण,
	अणु "l2", QCOM_SMD_RPM_LDOA, 2, &pm8941_nlकरो, "vdd_l2_lvs1_2_3" पूर्ण,
	अणु "l3", QCOM_SMD_RPM_LDOA, 3, &pm8941_nlकरो, "vdd_l1_l3" पूर्ण,
	अणु "l4", QCOM_SMD_RPM_LDOA, 4, &pm8941_nlकरो, "vdd_l4_l11" पूर्ण,
	अणु "l5", QCOM_SMD_RPM_LDOA, 5, &pm8941_lnlकरो, "vdd_l5_l7" पूर्ण,
	अणु "l6", QCOM_SMD_RPM_LDOA, 6, &pm8941_plकरो, "vdd_l6_l12_l14_l15" पूर्ण,
	अणु "l7", QCOM_SMD_RPM_LDOA, 7, &pm8941_lnlकरो, "vdd_l5_l7" पूर्ण,
	अणु "l8", QCOM_SMD_RPM_LDOA, 8, &pm8941_plकरो, "vdd_l8_l16_l18_l19" पूर्ण,
	अणु "l9", QCOM_SMD_RPM_LDOA, 9, &pm8941_plकरो, "vdd_l9_l10_l17_l22" पूर्ण,
	अणु "l10", QCOM_SMD_RPM_LDOA, 10, &pm8941_plकरो, "vdd_l9_l10_l17_l22" पूर्ण,
	अणु "l11", QCOM_SMD_RPM_LDOA, 11, &pm8941_nlकरो, "vdd_l4_l11" पूर्ण,
	अणु "l12", QCOM_SMD_RPM_LDOA, 12, &pm8941_plकरो, "vdd_l6_l12_l14_l15" पूर्ण,
	अणु "l13", QCOM_SMD_RPM_LDOA, 13, &pm8941_plकरो, "vdd_l13_l20_l23_l24" पूर्ण,
	अणु "l14", QCOM_SMD_RPM_LDOA, 14, &pm8941_plकरो, "vdd_l6_l12_l14_l15" पूर्ण,
	अणु "l15", QCOM_SMD_RPM_LDOA, 15, &pm8941_plकरो, "vdd_l6_l12_l14_l15" पूर्ण,
	अणु "l16", QCOM_SMD_RPM_LDOA, 16, &pm8941_plकरो, "vdd_l8_l16_l18_l19" पूर्ण,
	अणु "l17", QCOM_SMD_RPM_LDOA, 17, &pm8941_plकरो, "vdd_l9_l10_l17_l22" पूर्ण,
	अणु "l18", QCOM_SMD_RPM_LDOA, 18, &pm8941_plकरो, "vdd_l8_l16_l18_l19" पूर्ण,
	अणु "l19", QCOM_SMD_RPM_LDOA, 19, &pm8941_plकरो, "vdd_l8_l16_l18_l19" पूर्ण,
	अणु "l20", QCOM_SMD_RPM_LDOA, 20, &pm8941_plकरो, "vdd_l13_l20_l23_l24" पूर्ण,
	अणु "l21", QCOM_SMD_RPM_LDOA, 21, &pm8941_plकरो, "vdd_l21" पूर्ण,
	अणु "l22", QCOM_SMD_RPM_LDOA, 22, &pm8941_plकरो, "vdd_l9_l10_l17_l22" पूर्ण,
	अणु "l23", QCOM_SMD_RPM_LDOA, 23, &pm8941_plकरो, "vdd_l13_l20_l23_l24" पूर्ण,
	अणु "l24", QCOM_SMD_RPM_LDOA, 24, &pm8941_plकरो, "vdd_l13_l20_l23_l24" पूर्ण,

	अणु "lvs1", QCOM_SMD_RPM_VSA, 1, &pm8941_चयन, "vdd_l2_lvs1_2_3" पूर्ण,
	अणु "lvs2", QCOM_SMD_RPM_VSA, 2, &pm8941_चयन, "vdd_l2_lvs1_2_3" पूर्ण,
	अणु "lvs3", QCOM_SMD_RPM_VSA, 3, &pm8941_चयन, "vdd_l2_lvs1_2_3" पूर्ण,

	अणु "5vs1", QCOM_SMD_RPM_VSA, 4, &pm8941_चयन, "vin_5vs" पूर्ण,
	अणु "5vs2", QCOM_SMD_RPM_VSA, 5, &pm8941_चयन, "vin_5vs" पूर्ण,

	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pma8084_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPA, 1, &pma8084_ftsmps, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPA, 2, &pma8084_ftsmps, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_SMPA, 3, &pma8084_hfsmps, "vdd_s3" पूर्ण,
	अणु "s4", QCOM_SMD_RPM_SMPA, 4, &pma8084_hfsmps, "vdd_s4" पूर्ण,
	अणु "s5", QCOM_SMD_RPM_SMPA, 5, &pma8084_hfsmps, "vdd_s5" पूर्ण,
	अणु "s6", QCOM_SMD_RPM_SMPA, 6, &pma8084_ftsmps, "vdd_s6" पूर्ण,
	अणु "s7", QCOM_SMD_RPM_SMPA, 7, &pma8084_ftsmps, "vdd_s7" पूर्ण,
	अणु "s8", QCOM_SMD_RPM_SMPA, 8, &pma8084_ftsmps, "vdd_s8" पूर्ण,
	अणु "s9", QCOM_SMD_RPM_SMPA, 9, &pma8084_ftsmps, "vdd_s9" पूर्ण,
	अणु "s10", QCOM_SMD_RPM_SMPA, 10, &pma8084_ftsmps, "vdd_s10" पूर्ण,
	अणु "s11", QCOM_SMD_RPM_SMPA, 11, &pma8084_ftsmps, "vdd_s11" पूर्ण,
	अणु "s12", QCOM_SMD_RPM_SMPA, 12, &pma8084_ftsmps, "vdd_s12" पूर्ण,

	अणु "l1", QCOM_SMD_RPM_LDOA, 1, &pma8084_nlकरो, "vdd_l1_l11" पूर्ण,
	अणु "l2", QCOM_SMD_RPM_LDOA, 2, &pma8084_nlकरो, "vdd_l2_l3_l4_l27" पूर्ण,
	अणु "l3", QCOM_SMD_RPM_LDOA, 3, &pma8084_nlकरो, "vdd_l2_l3_l4_l27" पूर्ण,
	अणु "l4", QCOM_SMD_RPM_LDOA, 4, &pma8084_nlकरो, "vdd_l2_l3_l4_l27" पूर्ण,
	अणु "l5", QCOM_SMD_RPM_LDOA, 5, &pma8084_plकरो, "vdd_l5_l7" पूर्ण,
	अणु "l6", QCOM_SMD_RPM_LDOA, 6, &pma8084_plकरो, "vdd_l6_l12_l14_l15_l26" पूर्ण,
	अणु "l7", QCOM_SMD_RPM_LDOA, 7, &pma8084_plकरो, "vdd_l5_l7" पूर्ण,
	अणु "l8", QCOM_SMD_RPM_LDOA, 8, &pma8084_plकरो, "vdd_l8" पूर्ण,
	अणु "l9", QCOM_SMD_RPM_LDOA, 9, &pma8084_plकरो, "vdd_l9_l10_l13_l20_l23_l24" पूर्ण,
	अणु "l10", QCOM_SMD_RPM_LDOA, 10, &pma8084_plकरो, "vdd_l9_l10_l13_l20_l23_l24" पूर्ण,
	अणु "l11", QCOM_SMD_RPM_LDOA, 11, &pma8084_nlकरो, "vdd_l1_l11" पूर्ण,
	अणु "l12", QCOM_SMD_RPM_LDOA, 12, &pma8084_plकरो, "vdd_l6_l12_l14_l15_l26" पूर्ण,
	अणु "l13", QCOM_SMD_RPM_LDOA, 13, &pma8084_plकरो, "vdd_l9_l10_l13_l20_l23_l24" पूर्ण,
	अणु "l14", QCOM_SMD_RPM_LDOA, 14, &pma8084_plकरो, "vdd_l6_l12_l14_l15_l26" पूर्ण,
	अणु "l15", QCOM_SMD_RPM_LDOA, 15, &pma8084_plकरो, "vdd_l6_l12_l14_l15_l26" पूर्ण,
	अणु "l16", QCOM_SMD_RPM_LDOA, 16, &pma8084_plकरो, "vdd_l16_l25" पूर्ण,
	अणु "l17", QCOM_SMD_RPM_LDOA, 17, &pma8084_plकरो, "vdd_l17" पूर्ण,
	अणु "l18", QCOM_SMD_RPM_LDOA, 18, &pma8084_plकरो, "vdd_l18" पूर्ण,
	अणु "l19", QCOM_SMD_RPM_LDOA, 19, &pma8084_plकरो, "vdd_l19" पूर्ण,
	अणु "l20", QCOM_SMD_RPM_LDOA, 20, &pma8084_plकरो, "vdd_l9_l10_l13_l20_l23_l24" पूर्ण,
	अणु "l21", QCOM_SMD_RPM_LDOA, 21, &pma8084_plकरो, "vdd_l21" पूर्ण,
	अणु "l22", QCOM_SMD_RPM_LDOA, 22, &pma8084_plकरो, "vdd_l22" पूर्ण,
	अणु "l23", QCOM_SMD_RPM_LDOA, 23, &pma8084_plकरो, "vdd_l9_l10_l13_l20_l23_l24" पूर्ण,
	अणु "l24", QCOM_SMD_RPM_LDOA, 24, &pma8084_plकरो, "vdd_l9_l10_l13_l20_l23_l24" पूर्ण,
	अणु "l25", QCOM_SMD_RPM_LDOA, 25, &pma8084_plकरो, "vdd_l16_l25" पूर्ण,
	अणु "l26", QCOM_SMD_RPM_LDOA, 26, &pma8084_plकरो, "vdd_l6_l12_l14_l15_l26" पूर्ण,
	अणु "l27", QCOM_SMD_RPM_LDOA, 27, &pma8084_nlकरो, "vdd_l2_l3_l4_l27" पूर्ण,

	अणु "lvs1", QCOM_SMD_RPM_VSA, 1, &pma8084_चयन पूर्ण,
	अणु "lvs2", QCOM_SMD_RPM_VSA, 2, &pma8084_चयन पूर्ण,
	अणु "lvs3", QCOM_SMD_RPM_VSA, 3, &pma8084_चयन पूर्ण,
	अणु "lvs4", QCOM_SMD_RPM_VSA, 4, &pma8084_चयन पूर्ण,
	अणु "5vs1", QCOM_SMD_RPM_VSA, 5, &pma8084_चयन पूर्ण,

	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8950_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPA, 1, &pm8950_hfsmps, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPA, 2, &pm8950_hfsmps, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_SMPA, 3, &pm8950_hfsmps, "vdd_s3" पूर्ण,
	अणु "s4", QCOM_SMD_RPM_SMPA, 4, &pm8950_hfsmps, "vdd_s4" पूर्ण,
	अणु "s5", QCOM_SMD_RPM_SMPA, 5, &pm8950_ftsmps2p5, "vdd_s5" पूर्ण,
	अणु "s6", QCOM_SMD_RPM_SMPA, 6, &pm8950_hfsmps, "vdd_s6" पूर्ण,

	अणु "l1", QCOM_SMD_RPM_LDOA, 1, &pm8950_ult_nlकरो, "vdd_l1_l19" पूर्ण,
	अणु "l2", QCOM_SMD_RPM_LDOA, 2, &pm8950_ult_nlकरो, "vdd_l2_l23" पूर्ण,
	अणु "l3", QCOM_SMD_RPM_LDOA, 3, &pm8950_ult_nlकरो, "vdd_l3" पूर्ण,
	अणु "l4", QCOM_SMD_RPM_LDOA, 4, &pm8950_ult_plकरो, "vdd_l4_l5_l6_l7_l16" पूर्ण,
	अणु "l5", QCOM_SMD_RPM_LDOA, 5, &pm8950_plकरो_lv, "vdd_l4_l5_l6_l7_l16" पूर्ण,
	अणु "l6", QCOM_SMD_RPM_LDOA, 6, &pm8950_plकरो_lv, "vdd_l4_l5_l6_l7_l16" पूर्ण,
	अणु "l7", QCOM_SMD_RPM_LDOA, 7, &pm8950_plकरो_lv, "vdd_l4_l5_l6_l7_l16" पूर्ण,
	अणु "l8", QCOM_SMD_RPM_LDOA, 8, &pm8950_ult_plकरो, "vdd_l8_l11_l12_l17_l22" पूर्ण,
	अणु "l9", QCOM_SMD_RPM_LDOA, 9, &pm8950_ult_plकरो, "vdd_l9_l10_l13_l14_l15_l18" पूर्ण,
	अणु "l10", QCOM_SMD_RPM_LDOA, 10, &pm8950_ult_nlकरो, "vdd_l9_l10_l13_l14_l15_l18"पूर्ण,
	अणु "l11", QCOM_SMD_RPM_LDOA, 11, &pm8950_ult_plकरो, "vdd_l8_l11_l12_l17_l22"पूर्ण,
	अणु "l12", QCOM_SMD_RPM_LDOA, 12, &pm8950_ult_plकरो, "vdd_l8_l11_l12_l17_l22"पूर्ण,
	अणु "l13", QCOM_SMD_RPM_LDOA, 13, &pm8950_ult_plकरो, "vdd_l9_l10_l13_l14_l15_l18"पूर्ण,
	अणु "l14", QCOM_SMD_RPM_LDOA, 14, &pm8950_ult_plकरो, "vdd_l9_l10_l13_l14_l15_l18"पूर्ण,
	अणु "l15", QCOM_SMD_RPM_LDOA, 15, &pm8950_ult_plकरो, "vdd_l9_l10_l13_l14_l15_l18"पूर्ण,
	अणु "l16", QCOM_SMD_RPM_LDOA, 16, &pm8950_ult_plकरो, "vdd_l4_l5_l6_l7_l16"पूर्ण,
	अणु "l17", QCOM_SMD_RPM_LDOA, 17, &pm8950_ult_plकरो, "vdd_l8_l11_l12_l17_l22"पूर्ण,
	अणु "l18", QCOM_SMD_RPM_LDOA, 18, &pm8950_ult_plकरो, "vdd_l9_l10_l13_l14_l15_l18"पूर्ण,
	अणु "l19", QCOM_SMD_RPM_LDOA, 18, &pm8950_plकरो, "vdd_l1_l19"पूर्ण,
	अणु "l20", QCOM_SMD_RPM_LDOA, 18, &pm8950_plकरो, "vdd_l20"पूर्ण,
	अणु "l21", QCOM_SMD_RPM_LDOA, 18, &pm8950_plकरो, "vdd_l21"पूर्ण,
	अणु "l22", QCOM_SMD_RPM_LDOA, 18, &pm8950_plकरो, "vdd_l8_l11_l12_l17_l22"पूर्ण,
	अणु "l23", QCOM_SMD_RPM_LDOA, 18, &pm8950_plकरो, "vdd_l2_l23"पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8953_regulators[] = अणु
	अणु  "s1", QCOM_SMD_RPM_SMPA,  1, &pm8998_hfsmps, "vdd_s1" पूर्ण,
	अणु  "s2", QCOM_SMD_RPM_SMPA,  2, &pm8998_hfsmps, "vdd_s2" पूर्ण,
	अणु  "s3", QCOM_SMD_RPM_SMPA,  3, &pm8998_hfsmps, "vdd_s3" पूर्ण,
	अणु  "s4", QCOM_SMD_RPM_SMPA,  4, &pm8998_hfsmps, "vdd_s4" पूर्ण,
	अणु  "s5", QCOM_SMD_RPM_SMPA,  5, &pm8950_ftsmps2p5, "vdd_s5" पूर्ण,
	अणु  "s6", QCOM_SMD_RPM_SMPA,  6, &pm8950_ftsmps2p5, "vdd_s6" पूर्ण,
	अणु  "s7", QCOM_SMD_RPM_SMPA,  7, &pm8998_hfsmps, "vdd_s7" पूर्ण,

	अणु  "l1", QCOM_SMD_RPM_LDOA,  1, &pm8953_ult_nlकरो, "vdd_l1" पूर्ण,
	अणु  "l2", QCOM_SMD_RPM_LDOA,  2, &pm8953_ult_nlकरो, "vdd_l2_l3" पूर्ण,
	अणु  "l3", QCOM_SMD_RPM_LDOA,  3, &pm8953_ult_nlकरो, "vdd_l2_l3" पूर्ण,
	अणु  "l4", QCOM_SMD_RPM_LDOA,  4, &pm8950_ult_plकरो, "vdd_l4_l5_l6_l7_l16_l19" पूर्ण,
	अणु  "l5", QCOM_SMD_RPM_LDOA,  5, &pm8950_ult_plकरो, "vdd_l4_l5_l6_l7_l16_l19" पूर्ण,
	अणु  "l6", QCOM_SMD_RPM_LDOA,  6, &pm8950_ult_plकरो, "vdd_l4_l5_l6_l7_l16_l19" पूर्ण,
	अणु  "l7", QCOM_SMD_RPM_LDOA,  7, &pm8950_ult_plकरो, "vdd_l4_l5_l6_l7_l16_l19" पूर्ण,
	अणु  "l8", QCOM_SMD_RPM_LDOA,  8, &pm8950_ult_plकरो, "vdd_l8_l11_l12_l13_l14_l15" पूर्ण,
	अणु  "l9", QCOM_SMD_RPM_LDOA,  9, &pm8950_ult_plकरो, "vdd_l9_l10_l17_l18_l22" पूर्ण,
	अणु "l10", QCOM_SMD_RPM_LDOA, 10, &pm8950_ult_plकरो, "vdd_l9_l10_l17_l18_l22" पूर्ण,
	अणु "l11", QCOM_SMD_RPM_LDOA, 11, &pm8950_ult_plकरो, "vdd_l8_l11_l12_l13_l14_l15" पूर्ण,
	अणु "l12", QCOM_SMD_RPM_LDOA, 12, &pm8950_ult_plकरो, "vdd_l8_l11_l12_l13_l14_l15" पूर्ण,
	अणु "l13", QCOM_SMD_RPM_LDOA, 13, &pm8950_ult_plकरो, "vdd_l8_l11_l12_l13_l14_l15" पूर्ण,
	अणु "l14", QCOM_SMD_RPM_LDOA, 14, &pm8950_ult_plकरो, "vdd_l8_l11_l12_l13_l14_l15" पूर्ण,
	अणु "l15", QCOM_SMD_RPM_LDOA, 15, &pm8950_ult_plकरो, "vdd_l8_l11_l12_l13_l14_l15" पूर्ण,
	अणु "l16", QCOM_SMD_RPM_LDOA, 16, &pm8950_ult_plकरो, "vdd_l4_l5_l6_l7_l16_l19" पूर्ण,
	अणु "l17", QCOM_SMD_RPM_LDOA, 17, &pm8950_ult_plकरो, "vdd_l9_l10_l17_l18_l22" पूर्ण,
	अणु "l18", QCOM_SMD_RPM_LDOA, 18, &pm8950_ult_plकरो, "vdd_l9_l10_l17_l18_l22" पूर्ण,
	अणु "l19", QCOM_SMD_RPM_LDOA, 19, &pm8953_ult_nlकरो, "vdd_l4_l5_l6_l7_l16_l19" पूर्ण,
	अणु "l20", QCOM_SMD_RPM_LDOA, 20, &pm8953_lnlकरो,    "vdd_l20" पूर्ण,
	अणु "l21", QCOM_SMD_RPM_LDOA, 21, &pm8953_lnlकरो,    "vdd_l21" पूर्ण,
	अणु "l22", QCOM_SMD_RPM_LDOA, 22, &pm8950_ult_plकरो, "vdd_l9_l10_l17_l18_l22" पूर्ण,
	अणु "l23", QCOM_SMD_RPM_LDOA, 23, &pm8953_ult_nlकरो, "vdd_l23" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8994_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPA, 1, &pm8994_ftsmps, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPA, 2, &pm8994_ftsmps, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_SMPA, 3, &pm8994_hfsmps, "vdd_s3" पूर्ण,
	अणु "s4", QCOM_SMD_RPM_SMPA, 4, &pm8994_hfsmps, "vdd_s4" पूर्ण,
	अणु "s5", QCOM_SMD_RPM_SMPA, 5, &pm8994_hfsmps, "vdd_s5" पूर्ण,
	अणु "s6", QCOM_SMD_RPM_SMPA, 6, &pm8994_ftsmps, "vdd_s6" पूर्ण,
	अणु "s7", QCOM_SMD_RPM_SMPA, 7, &pm8994_hfsmps, "vdd_s7" पूर्ण,
	अणु "s8", QCOM_SMD_RPM_SMPA, 8, &pm8994_ftsmps, "vdd_s8" पूर्ण,
	अणु "s9", QCOM_SMD_RPM_SMPA, 9, &pm8994_ftsmps, "vdd_s9" पूर्ण,
	अणु "s10", QCOM_SMD_RPM_SMPA, 10, &pm8994_ftsmps, "vdd_s10" पूर्ण,
	अणु "s11", QCOM_SMD_RPM_SMPA, 11, &pm8994_ftsmps, "vdd_s11" पूर्ण,
	अणु "s12", QCOM_SMD_RPM_SMPA, 12, &pm8994_ftsmps, "vdd_s12" पूर्ण,
	अणु "l1", QCOM_SMD_RPM_LDOA, 1, &pm8994_nlकरो, "vdd_l1" पूर्ण,
	अणु "l2", QCOM_SMD_RPM_LDOA, 2, &pm8994_nlकरो, "vdd_l2_l26_l28" पूर्ण,
	अणु "l3", QCOM_SMD_RPM_LDOA, 3, &pm8994_nlकरो, "vdd_l3_l11" पूर्ण,
	अणु "l4", QCOM_SMD_RPM_LDOA, 4, &pm8994_nlकरो, "vdd_l4_l27_l31" पूर्ण,
	अणु "l5", QCOM_SMD_RPM_LDOA, 5, &pm8994_lnlकरो, "vdd_l5_l7" पूर्ण,
	अणु "l6", QCOM_SMD_RPM_LDOA, 6, &pm8994_plकरो, "vdd_l6_l12_l32" पूर्ण,
	अणु "l7", QCOM_SMD_RPM_LDOA, 7, &pm8994_lnlकरो, "vdd_l5_l7" पूर्ण,
	अणु "l8", QCOM_SMD_RPM_LDOA, 8, &pm8994_plकरो, "vdd_l8_l16_l30" पूर्ण,
	अणु "l9", QCOM_SMD_RPM_LDOA, 9, &pm8994_plकरो, "vdd_l9_l10_l18_l22" पूर्ण,
	अणु "l10", QCOM_SMD_RPM_LDOA, 10, &pm8994_plकरो, "vdd_l9_l10_l18_l22" पूर्ण,
	अणु "l11", QCOM_SMD_RPM_LDOA, 11, &pm8994_nlकरो, "vdd_l3_l11" पूर्ण,
	अणु "l12", QCOM_SMD_RPM_LDOA, 12, &pm8994_plकरो, "vdd_l6_l12_l32" पूर्ण,
	अणु "l13", QCOM_SMD_RPM_LDOA, 13, &pm8994_plकरो, "vdd_l13_l19_l23_l24" पूर्ण,
	अणु "l14", QCOM_SMD_RPM_LDOA, 14, &pm8994_plकरो, "vdd_l14_l15" पूर्ण,
	अणु "l15", QCOM_SMD_RPM_LDOA, 15, &pm8994_plकरो, "vdd_l14_l15" पूर्ण,
	अणु "l16", QCOM_SMD_RPM_LDOA, 16, &pm8994_plकरो, "vdd_l8_l16_l30" पूर्ण,
	अणु "l17", QCOM_SMD_RPM_LDOA, 17, &pm8994_plकरो, "vdd_l17_l29" पूर्ण,
	अणु "l18", QCOM_SMD_RPM_LDOA, 18, &pm8994_plकरो, "vdd_l9_l10_l18_l22" पूर्ण,
	अणु "l19", QCOM_SMD_RPM_LDOA, 19, &pm8994_plकरो, "vdd_l13_l19_l23_l24" पूर्ण,
	अणु "l20", QCOM_SMD_RPM_LDOA, 20, &pm8994_plकरो, "vdd_l20_l21" पूर्ण,
	अणु "l21", QCOM_SMD_RPM_LDOA, 21, &pm8994_plकरो, "vdd_l20_l21" पूर्ण,
	अणु "l22", QCOM_SMD_RPM_LDOA, 22, &pm8994_plकरो, "vdd_l9_l10_l18_l22" पूर्ण,
	अणु "l23", QCOM_SMD_RPM_LDOA, 23, &pm8994_plकरो, "vdd_l13_l19_l23_l24" पूर्ण,
	अणु "l24", QCOM_SMD_RPM_LDOA, 24, &pm8994_plकरो, "vdd_l13_l19_l23_l24" पूर्ण,
	अणु "l25", QCOM_SMD_RPM_LDOA, 25, &pm8994_plकरो, "vdd_l25" पूर्ण,
	अणु "l26", QCOM_SMD_RPM_LDOA, 26, &pm8994_nlकरो, "vdd_l2_l26_l28" पूर्ण,
	अणु "l27", QCOM_SMD_RPM_LDOA, 27, &pm8994_nlकरो, "vdd_l4_l27_l31" पूर्ण,
	अणु "l28", QCOM_SMD_RPM_LDOA, 28, &pm8994_nlकरो, "vdd_l2_l26_l28" पूर्ण,
	अणु "l29", QCOM_SMD_RPM_LDOA, 29, &pm8994_plकरो, "vdd_l17_l29" पूर्ण,
	अणु "l30", QCOM_SMD_RPM_LDOA, 30, &pm8994_plकरो, "vdd_l8_l16_l30" पूर्ण,
	अणु "l31", QCOM_SMD_RPM_LDOA, 31, &pm8994_nlकरो, "vdd_l4_l27_l31" पूर्ण,
	अणु "l32", QCOM_SMD_RPM_LDOA, 32, &pm8994_plकरो, "vdd_l6_l12_l32" पूर्ण,
	अणु "lvs1", QCOM_SMD_RPM_VSA, 1, &pm8994_चयन, "vdd_lvs1_2" पूर्ण,
	अणु "lvs2", QCOM_SMD_RPM_VSA, 2, &pm8994_चयन, "vdd_lvs1_2" पूर्ण,

	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pmi8994_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPB, 1, &pmi8994_ftsmps, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPB, 2, &pmi8994_hfsmps, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_SMPB, 3, &pmi8994_hfsmps, "vdd_s3" पूर्ण,
	अणु "boost-bypass", QCOM_SMD_RPM_BBYB, 1, &pmi8994_bby, "vdd_bst_byp" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8998_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPA, 1, &pm8998_ftsmps, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPA, 2, &pm8998_ftsmps, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_SMPA, 3, &pm8998_hfsmps, "vdd_s3" पूर्ण,
	अणु "s4", QCOM_SMD_RPM_SMPA, 4, &pm8998_hfsmps, "vdd_s4" पूर्ण,
	अणु "s5", QCOM_SMD_RPM_SMPA, 5, &pm8998_hfsmps, "vdd_s5" पूर्ण,
	अणु "s6", QCOM_SMD_RPM_SMPA, 6, &pm8998_ftsmps, "vdd_s6" पूर्ण,
	अणु "s7", QCOM_SMD_RPM_SMPA, 7, &pm8998_ftsmps, "vdd_s7" पूर्ण,
	अणु "s8", QCOM_SMD_RPM_SMPA, 8, &pm8998_ftsmps, "vdd_s8" पूर्ण,
	अणु "s9", QCOM_SMD_RPM_SMPA, 9, &pm8998_ftsmps, "vdd_s9" पूर्ण,
	अणु "s10", QCOM_SMD_RPM_SMPA, 10, &pm8998_ftsmps, "vdd_s10" पूर्ण,
	अणु "s11", QCOM_SMD_RPM_SMPA, 11, &pm8998_ftsmps, "vdd_s11" पूर्ण,
	अणु "s12", QCOM_SMD_RPM_SMPA, 12, &pm8998_ftsmps, "vdd_s12" पूर्ण,
	अणु "s13", QCOM_SMD_RPM_SMPA, 13, &pm8998_ftsmps, "vdd_s13" पूर्ण,
	अणु "l1", QCOM_SMD_RPM_LDOA, 1, &pm8998_nlकरो, "vdd_l1_l27" पूर्ण,
	अणु "l2", QCOM_SMD_RPM_LDOA, 2, &pm8998_nlकरो, "vdd_l2_l8_l17" पूर्ण,
	अणु "l3", QCOM_SMD_RPM_LDOA, 3, &pm8998_nlकरो, "vdd_l3_l11" पूर्ण,
	अणु "l4", QCOM_SMD_RPM_LDOA, 4, &pm8998_nlकरो, "vdd_l4_l5" पूर्ण,
	अणु "l5", QCOM_SMD_RPM_LDOA, 5, &pm8998_nlकरो, "vdd_l4_l5" पूर्ण,
	अणु "l6", QCOM_SMD_RPM_LDOA, 6, &pm8998_plकरो, "vdd_l6" पूर्ण,
	अणु "l7", QCOM_SMD_RPM_LDOA, 7, &pm8998_plकरो_lv, "vdd_l7_l12_l14_l15" पूर्ण,
	अणु "l8", QCOM_SMD_RPM_LDOA, 8, &pm8998_nlकरो, "vdd_l2_l8_l17" पूर्ण,
	अणु "l9", QCOM_SMD_RPM_LDOA, 9, &pm8998_plकरो, "vdd_l9" पूर्ण,
	अणु "l10", QCOM_SMD_RPM_LDOA, 10, &pm8998_plकरो, "vdd_l10_l23_l25" पूर्ण,
	अणु "l11", QCOM_SMD_RPM_LDOA, 11, &pm8998_nlकरो, "vdd_l3_l11" पूर्ण,
	अणु "l12", QCOM_SMD_RPM_LDOA, 12, &pm8998_plकरो_lv, "vdd_l7_l12_l14_l15" पूर्ण,
	अणु "l13", QCOM_SMD_RPM_LDOA, 13, &pm8998_plकरो, "vdd_l13_l19_l21" पूर्ण,
	अणु "l14", QCOM_SMD_RPM_LDOA, 14, &pm8998_plकरो_lv, "vdd_l7_l12_l14_l15" पूर्ण,
	अणु "l15", QCOM_SMD_RPM_LDOA, 15, &pm8998_plकरो_lv, "vdd_l7_l12_l14_l15" पूर्ण,
	अणु "l16", QCOM_SMD_RPM_LDOA, 16, &pm8998_plकरो, "vdd_l16_l28" पूर्ण,
	अणु "l17", QCOM_SMD_RPM_LDOA, 17, &pm8998_nlकरो, "vdd_l2_l8_l17" पूर्ण,
	अणु "l18", QCOM_SMD_RPM_LDOA, 18, &pm8998_plकरो, "vdd_l18_l22" पूर्ण,
	अणु "l19", QCOM_SMD_RPM_LDOA, 19, &pm8998_plकरो, "vdd_l13_l19_l21" पूर्ण,
	अणु "l20", QCOM_SMD_RPM_LDOA, 20, &pm8998_plकरो, "vdd_l20_l24" पूर्ण,
	अणु "l21", QCOM_SMD_RPM_LDOA, 21, &pm8998_plकरो, "vdd_l13_l19_l21" पूर्ण,
	अणु "l22", QCOM_SMD_RPM_LDOA, 22, &pm8998_plकरो, "vdd_l18_l22" पूर्ण,
	अणु "l23", QCOM_SMD_RPM_LDOA, 23, &pm8998_plकरो, "vdd_l10_l23_l25" पूर्ण,
	अणु "l24", QCOM_SMD_RPM_LDOA, 24, &pm8998_plकरो, "vdd_l20_l24" पूर्ण,
	अणु "l25", QCOM_SMD_RPM_LDOA, 25, &pm8998_plकरो, "vdd_l10_l23_l25" पूर्ण,
	अणु "l26", QCOM_SMD_RPM_LDOA, 26, &pm8998_nlकरो, "vdd_l26" पूर्ण,
	अणु "l27", QCOM_SMD_RPM_LDOA, 27, &pm8998_nlकरो, "vdd_l1_l27" पूर्ण,
	अणु "l28", QCOM_SMD_RPM_LDOA, 28, &pm8998_plकरो, "vdd_l16_l28" पूर्ण,
	अणु "lvs1", QCOM_SMD_RPM_VSA, 1, &pm8998_चयन, "vdd_lvs1_lvs2" पूर्ण,
	अणु "lvs2", QCOM_SMD_RPM_VSA, 2, &pm8998_चयन, "vdd_lvs1_lvs2" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pmi8998_regulators[] = अणु
	अणु "bob", QCOM_SMD_RPM_BOBB, 1, &pmi8998_bob, "vdd_bob" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm660_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPA, 1, &pm660_ftsmps, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPA, 2, &pm660_ftsmps, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_SMPA, 3, &pm660_ftsmps, "vdd_s3" पूर्ण,
	अणु "s4", QCOM_SMD_RPM_SMPA, 4, &pm660_hfsmps, "vdd_s4" पूर्ण,
	अणु "s5", QCOM_SMD_RPM_SMPA, 5, &pm660_hfsmps, "vdd_s5" पूर्ण,
	अणु "s6", QCOM_SMD_RPM_SMPA, 6, &pm660_hfsmps, "vdd_s6" पूर्ण,
	अणु "l1", QCOM_SMD_RPM_LDOA, 1, &pm660_nlकरो660, "vdd_l1_l6_l7" पूर्ण,
	अणु "l2", QCOM_SMD_RPM_LDOA, 2, &pm660_ht_nlकरो, "vdd_l2_l3" पूर्ण,
	अणु "l3", QCOM_SMD_RPM_LDOA, 3, &pm660_nlकरो660, "vdd_l2_l3" पूर्ण,
	/* l4 is unaccessible on PM660 */
	अणु "l5", QCOM_SMD_RPM_LDOA, 5, &pm660_ht_nlकरो, "vdd_l5" पूर्ण,
	अणु "l6", QCOM_SMD_RPM_LDOA, 6, &pm660_ht_nlकरो, "vdd_l1_l6_l7" पूर्ण,
	अणु "l7", QCOM_SMD_RPM_LDOA, 7, &pm660_ht_nlकरो, "vdd_l1_l6_l7" पूर्ण,
	अणु "l8", QCOM_SMD_RPM_LDOA, 8, &pm660_ht_lvplकरो, "vdd_l8_l9_l10_l11_l12_l13_l14" पूर्ण,
	अणु "l9", QCOM_SMD_RPM_LDOA, 9, &pm660_ht_lvplकरो, "vdd_l8_l9_l10_l11_l12_l13_l14" पूर्ण,
	अणु "l10", QCOM_SMD_RPM_LDOA, 10, &pm660_ht_lvplकरो, "vdd_l8_l9_l10_l11_l12_l13_l14" पूर्ण,
	अणु "l11", QCOM_SMD_RPM_LDOA, 11, &pm660_ht_lvplकरो, "vdd_l8_l9_l10_l11_l12_l13_l14" पूर्ण,
	अणु "l12", QCOM_SMD_RPM_LDOA, 12, &pm660_ht_lvplकरो, "vdd_l8_l9_l10_l11_l12_l13_l14" पूर्ण,
	अणु "l13", QCOM_SMD_RPM_LDOA, 13, &pm660_ht_lvplकरो, "vdd_l8_l9_l10_l11_l12_l13_l14" पूर्ण,
	अणु "l14", QCOM_SMD_RPM_LDOA, 14, &pm660_ht_lvplकरो, "vdd_l8_l9_l10_l11_l12_l13_l14" पूर्ण,
	अणु "l15", QCOM_SMD_RPM_LDOA, 15, &pm660_plकरो660, "vdd_l15_l16_l17_l18_l19" पूर्ण,
	अणु "l16", QCOM_SMD_RPM_LDOA, 16, &pm660_plकरो660, "vdd_l15_l16_l17_l18_l19" पूर्ण,
	अणु "l17", QCOM_SMD_RPM_LDOA, 17, &pm660_plकरो660, "vdd_l15_l16_l17_l18_l19" पूर्ण,
	अणु "l18", QCOM_SMD_RPM_LDOA, 18, &pm660_plकरो660, "vdd_l15_l16_l17_l18_l19" पूर्ण,
	अणु "l19", QCOM_SMD_RPM_LDOA, 19, &pm660_plकरो660, "vdd_l15_l16_l17_l18_l19" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm660l_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPB, 1, &pm660_ftsmps, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPB, 2, &pm660_ftsmps, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_RWCX, 0, &pm660_ftsmps, "vdd_s3_s4" पूर्ण,
	अणु "s5", QCOM_SMD_RPM_RWMX, 0, &pm660_ftsmps, "vdd_s5" पूर्ण,
	अणु "l1", QCOM_SMD_RPM_LDOB, 1, &pm660_nlकरो660, "vdd_l1_l9_l10" पूर्ण,
	अणु "l2", QCOM_SMD_RPM_LDOB, 2, &pm660_plकरो660, "vdd_l2" पूर्ण,
	अणु "l3", QCOM_SMD_RPM_LDOB, 3, &pm660_plकरो660, "vdd_l3_l5_l7_l8" पूर्ण,
	अणु "l4", QCOM_SMD_RPM_LDOB, 4, &pm660_plकरो660, "vdd_l4_l6" पूर्ण,
	अणु "l5", QCOM_SMD_RPM_LDOB, 5, &pm660_plकरो660, "vdd_l3_l5_l7_l8" पूर्ण,
	अणु "l6", QCOM_SMD_RPM_LDOB, 6, &pm660_plकरो660, "vdd_l4_l6" पूर्ण,
	अणु "l7", QCOM_SMD_RPM_LDOB, 7, &pm660_plकरो660, "vdd_l3_l5_l7_l8" पूर्ण,
	अणु "l8", QCOM_SMD_RPM_LDOB, 8, &pm660_plकरो660, "vdd_l3_l5_l7_l8" पूर्ण,
	अणु "l9", QCOM_SMD_RPM_RWLC, 0, &pm660_ht_nlकरो, "vdd_l1_l9_l10" पूर्ण,
	अणु "l10", QCOM_SMD_RPM_RWLM, 0, &pm660_ht_nlकरो, "vdd_l1_l9_l10" पूर्ण,
	अणु "bob", QCOM_SMD_RPM_BOBB, 1, &pm660l_bob, "vdd_bob", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pms405_regulators[] = अणु
	अणु "s1", QCOM_SMD_RPM_SMPA, 1, &pms405_hfsmps3, "vdd_s1" पूर्ण,
	अणु "s2", QCOM_SMD_RPM_SMPA, 2, &pms405_hfsmps3, "vdd_s2" पूर्ण,
	अणु "s3", QCOM_SMD_RPM_SMPA, 3, &pms405_hfsmps3, "vdd_s3" पूर्ण,
	अणु "s4", QCOM_SMD_RPM_SMPA, 4, &pms405_hfsmps3, "vdd_s4" पूर्ण,
	अणु "s5", QCOM_SMD_RPM_SMPA, 5, &pms405_hfsmps3, "vdd_s5" पूर्ण,
	अणु "l1", QCOM_SMD_RPM_LDOA, 1, &pms405_nlकरो1200, "vdd_l1_l2" पूर्ण,
	अणु "l2", QCOM_SMD_RPM_LDOA, 2, &pms405_nlकरो1200, "vdd_l1_l2" पूर्ण,
	अणु "l3", QCOM_SMD_RPM_LDOA, 3, &pms405_nlकरो1200, "vdd_l3_l8" पूर्ण,
	अणु "l4", QCOM_SMD_RPM_LDOA, 4, &pms405_nlकरो300, "vdd_l4" पूर्ण,
	अणु "l5", QCOM_SMD_RPM_LDOA, 5, &pms405_plकरो600, "vdd_l5_l6" पूर्ण,
	अणु "l6", QCOM_SMD_RPM_LDOA, 6, &pms405_plकरो600, "vdd_l5_l6" पूर्ण,
	अणु "l7", QCOM_SMD_RPM_LDOA, 7, &pms405_plकरो150, "vdd_l7" पूर्ण,
	अणु "l8", QCOM_SMD_RPM_LDOA, 8, &pms405_nlकरो1200, "vdd_l3_l8" पूर्ण,
	अणु "l9", QCOM_SMD_RPM_LDOA, 9, &pms405_nlकरो1200, "vdd_l9" पूर्ण,
	अणु "l10", QCOM_SMD_RPM_LDOA, 10, &pms405_plकरो50, "vdd_l10_l11_l12_l13" पूर्ण,
	अणु "l11", QCOM_SMD_RPM_LDOA, 11, &pms405_plकरो150, "vdd_l10_l11_l12_l13" पूर्ण,
	अणु "l12", QCOM_SMD_RPM_LDOA, 12, &pms405_plकरो150, "vdd_l10_l11_l12_l13" पूर्ण,
	अणु "l13", QCOM_SMD_RPM_LDOA, 13, &pms405_plकरो150, "vdd_l10_l11_l12_l13" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id rpm_of_match[] = अणु
	अणु .compatible = "qcom,rpm-mp5496-regulators", .data = &rpm_mp5496_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm8841-regulators", .data = &rpm_pm8841_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm8916-regulators", .data = &rpm_pm8916_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm8941-regulators", .data = &rpm_pm8941_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm8950-regulators", .data = &rpm_pm8950_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm8953-regulators", .data = &rpm_pm8953_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm8994-regulators", .data = &rpm_pm8994_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm8998-regulators", .data = &rpm_pm8998_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm660-regulators", .data = &rpm_pm660_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm660l-regulators", .data = &rpm_pm660l_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pma8084-regulators", .data = &rpm_pma8084_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pmi8994-regulators", .data = &rpm_pmi8994_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pmi8998-regulators", .data = &rpm_pmi8998_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pms405-regulators", .data = &rpm_pms405_regulators पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rpm_of_match);

अटल पूर्णांक rpm_reg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा rpm_regulator_data *reg;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा qcom_rpm_reg *vreg;
	काष्ठा qcom_smd_rpm *rpm;

	rpm = dev_get_drvdata(pdev->dev.parent);
	अगर (!rpm) अणु
		dev_err(&pdev->dev, "unable to retrieve handle to rpm\n");
		वापस -ENODEV;
	पूर्ण

	match = of_match_device(rpm_of_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (reg = match->data; reg->name; reg++) अणु
		vreg = devm_kzalloc(&pdev->dev, माप(*vreg), GFP_KERNEL);
		अगर (!vreg)
			वापस -ENOMEM;

		vreg->dev = &pdev->dev;
		vreg->type = reg->type;
		vreg->id = reg->id;
		vreg->rpm = rpm;

		स_नकल(&vreg->desc, reg->desc, माप(vreg->desc));

		vreg->desc.id = -1;
		vreg->desc.owner = THIS_MODULE;
		vreg->desc.type = REGULATOR_VOLTAGE;
		vreg->desc.name = reg->name;
		vreg->desc.supply_name = reg->supply;
		vreg->desc.of_match = reg->name;

		config.dev = &pdev->dev;
		config.driver_data = vreg;
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &vreg->desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register %s\n", reg->name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rpm_reg_driver = अणु
	.probe = rpm_reg_probe,
	.driver = अणु
		.name  = "qcom_rpm_smd_regulator",
		.of_match_table = rpm_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rpm_reg_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rpm_reg_driver);
पूर्ण
subsys_initcall(rpm_reg_init);

अटल व्योम __निकास rpm_reg_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&rpm_reg_driver);
पूर्ण
module_निकास(rpm_reg_निकास)

MODULE_DESCRIPTION("Qualcomm RPM regulator driver");
MODULE_LICENSE("GPL v2");
