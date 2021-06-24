<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, Sony Mobile Communications AB.
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/qcom_rpm.h>

#समावेश <dt-bindings/mfd/qcom-rpm.h>

#घोषणा MAX_REQUEST_LEN 2

काष्ठा request_member अणु
	पूर्णांक		word;
	अचिन्हित पूर्णांक	mask;
	पूर्णांक		shअगरt;
पूर्ण;

काष्ठा rpm_reg_parts अणु
	काष्ठा request_member mV;		/* used अगर voltage is in mV */
	काष्ठा request_member uV;		/* used अगर voltage is in uV */
	काष्ठा request_member ip;		/* peak current in mA */
	काष्ठा request_member pd;		/* pull करोwn enable */
	काष्ठा request_member ia;		/* average current in mA */
	काष्ठा request_member fm;		/* क्रमce mode */
	काष्ठा request_member pm;		/* घातer mode */
	काष्ठा request_member pc;		/* pin control */
	काष्ठा request_member pf;		/* pin function */
	काष्ठा request_member enable_state;	/* NCP and चयन */
	काष्ठा request_member comp_mode;	/* NCP */
	काष्ठा request_member freq;		/* frequency: NCP and SMPS */
	काष्ठा request_member freq_clk_src;	/* घड़ी source: SMPS */
	काष्ठा request_member hpm;		/* चयन: control OCP and SS */
	पूर्णांक request_len;
पूर्ण;

#घोषणा FORCE_MODE_IS_2_BITS(reg) \
	(((reg)->parts->fm.mask >> (reg)->parts->fm.shअगरt) == 3)

काष्ठा qcom_rpm_reg अणु
	काष्ठा qcom_rpm *rpm;

	काष्ठा mutex lock;
	काष्ठा device *dev;
	काष्ठा regulator_desc desc;
	स्थिर काष्ठा rpm_reg_parts *parts;

	पूर्णांक resource;
	u32 val[MAX_REQUEST_LEN];

	पूर्णांक uV;
	पूर्णांक is_enabled;

	bool supports_क्रमce_mode_स्वतः;
	bool supports_क्रमce_mode_bypass;
पूर्ण;

अटल स्थिर काष्ठा rpm_reg_parts rpm8660_lकरो_parts = अणु
	.request_len    = 2,
	.mV             = अणु 0, 0x00000FFF,  0 पूर्ण,
	.ip             = अणु 0, 0x00FFF000, 12 पूर्ण,
	.fm             = अणु 0, 0x03000000, 24 पूर्ण,
	.pc             = अणु 0, 0x3C000000, 26 पूर्ण,
	.pf             = अणु 0, 0xC0000000, 30 पूर्ण,
	.pd             = अणु 1, 0x00000001,  0 पूर्ण,
	.ia             = अणु 1, 0x00001FFE,  1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpm_reg_parts rpm8660_smps_parts = अणु
	.request_len    = 2,
	.mV             = अणु 0, 0x00000FFF,  0 पूर्ण,
	.ip             = अणु 0, 0x00FFF000, 12 पूर्ण,
	.fm             = अणु 0, 0x03000000, 24 पूर्ण,
	.pc             = अणु 0, 0x3C000000, 26 पूर्ण,
	.pf             = अणु 0, 0xC0000000, 30 पूर्ण,
	.pd             = अणु 1, 0x00000001,  0 पूर्ण,
	.ia             = अणु 1, 0x00001FFE,  1 पूर्ण,
	.freq           = अणु 1, 0x001FE000, 13 पूर्ण,
	.freq_clk_src   = अणु 1, 0x00600000, 21 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpm_reg_parts rpm8660_चयन_parts = अणु
	.request_len    = 1,
	.enable_state   = अणु 0, 0x00000001,  0 पूर्ण,
	.pd             = अणु 0, 0x00000002,  1 पूर्ण,
	.pc             = अणु 0, 0x0000003C,  2 पूर्ण,
	.pf             = अणु 0, 0x000000C0,  6 पूर्ण,
	.hpm            = अणु 0, 0x00000300,  8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpm_reg_parts rpm8660_ncp_parts = अणु
	.request_len    = 1,
	.mV             = अणु 0, 0x00000FFF,  0 पूर्ण,
	.enable_state   = अणु 0, 0x00001000, 12 पूर्ण,
	.comp_mode      = अणु 0, 0x00002000, 13 पूर्ण,
	.freq           = अणु 0, 0x003FC000, 14 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpm_reg_parts rpm8960_lकरो_parts = अणु
	.request_len    = 2,
	.uV             = अणु 0, 0x007FFFFF,  0 पूर्ण,
	.pd             = अणु 0, 0x00800000, 23 पूर्ण,
	.pc             = अणु 0, 0x0F000000, 24 पूर्ण,
	.pf             = अणु 0, 0xF0000000, 28 पूर्ण,
	.ip             = अणु 1, 0x000003FF,  0 पूर्ण,
	.ia             = अणु 1, 0x000FFC00, 10 पूर्ण,
	.fm             = अणु 1, 0x00700000, 20 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpm_reg_parts rpm8960_smps_parts = अणु
	.request_len    = 2,
	.uV             = अणु 0, 0x007FFFFF,  0 पूर्ण,
	.pd             = अणु 0, 0x00800000, 23 पूर्ण,
	.pc             = अणु 0, 0x0F000000, 24 पूर्ण,
	.pf             = अणु 0, 0xF0000000, 28 पूर्ण,
	.ip             = अणु 1, 0x000003FF,  0 पूर्ण,
	.ia             = अणु 1, 0x000FFC00, 10 पूर्ण,
	.fm             = अणु 1, 0x00700000, 20 पूर्ण,
	.pm             = अणु 1, 0x00800000, 23 पूर्ण,
	.freq           = अणु 1, 0x1F000000, 24 पूर्ण,
	.freq_clk_src   = अणु 1, 0x60000000, 29 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpm_reg_parts rpm8960_चयन_parts = अणु
	.request_len    = 1,
	.enable_state   = अणु 0, 0x00000001,  0 पूर्ण,
	.pd             = अणु 0, 0x00000002,  1 पूर्ण,
	.pc             = अणु 0, 0x0000003C,  2 पूर्ण,
	.pf             = अणु 0, 0x000003C0,  6 पूर्ण,
	.hpm            = अणु 0, 0x00000C00, 10 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpm_reg_parts rpm8960_ncp_parts = अणु
	.request_len    = 1,
	.uV             = अणु 0, 0x007FFFFF,  0 पूर्ण,
	.enable_state   = अणु 0, 0x00800000, 23 पूर्ण,
	.comp_mode      = अणु 0, 0x01000000, 24 पूर्ण,
	.freq           = अणु 0, 0x3E000000, 25 पूर्ण,
पूर्ण;

/*
 * Physically available PMIC regulator voltage ranges
 */
अटल स्थिर काष्ठा linear_range plकरो_ranges[] = अणु
	REGULATOR_LINEAR_RANGE( 750000,   0,  59, 12500),
	REGULATOR_LINEAR_RANGE(1500000,  60, 123, 25000),
	REGULATOR_LINEAR_RANGE(3100000, 124, 160, 50000),
पूर्ण;

अटल स्थिर काष्ठा linear_range nlकरो_ranges[] = अणु
	REGULATOR_LINEAR_RANGE( 750000,   0,  63, 12500),
पूर्ण;

अटल स्थिर काष्ठा linear_range nlकरो1200_ranges[] = अणु
	REGULATOR_LINEAR_RANGE( 375000,   0,  59,  6250),
	REGULATOR_LINEAR_RANGE( 750000,  60, 123, 12500),
पूर्ण;

अटल स्थिर काष्ठा linear_range smps_ranges[] = अणु
	REGULATOR_LINEAR_RANGE( 375000,   0,  29, 12500),
	REGULATOR_LINEAR_RANGE( 750000,  30,  89, 12500),
	REGULATOR_LINEAR_RANGE(1500000,  90, 153, 25000),
पूर्ण;

अटल स्थिर काष्ठा linear_range ftsmps_ranges[] = अणु
	REGULATOR_LINEAR_RANGE( 350000,   0,   6, 50000),
	REGULATOR_LINEAR_RANGE( 700000,   7,  63, 12500),
	REGULATOR_LINEAR_RANGE(1500000,  64, 100, 50000),
पूर्ण;

अटल स्थिर काष्ठा linear_range smb208_ranges[] = अणु
	REGULATOR_LINEAR_RANGE( 375000,   0,  29, 12500),
	REGULATOR_LINEAR_RANGE( 750000,  30,  89, 12500),
	REGULATOR_LINEAR_RANGE(1500000,  90, 153, 25000),
	REGULATOR_LINEAR_RANGE(3100000, 154, 234, 25000),
पूर्ण;

अटल स्थिर काष्ठा linear_range ncp_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1500000,   0,  31, 50000),
पूर्ण;

अटल पूर्णांक rpm_reg_ग_लिखो(काष्ठा qcom_rpm_reg *vreg,
			 स्थिर काष्ठा request_member *req,
			 स्थिर पूर्णांक value)
अणु
	अगर (WARN_ON((value << req->shअगरt) & ~req->mask))
		वापस -EINVAL;

	vreg->val[req->word] &= ~req->mask;
	vreg->val[req->word] |= value << req->shअगरt;

	वापस qcom_rpm_ग_लिखो(vreg->rpm,
			      QCOM_RPM_ACTIVE_STATE,
			      vreg->resource,
			      vreg->val,
			      vreg->parts->request_len);
पूर्ण

अटल पूर्णांक rpm_reg_set_mV_sel(काष्ठा regulator_dev *rdev,
			      अचिन्हित selector)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा rpm_reg_parts *parts = vreg->parts;
	स्थिर काष्ठा request_member *req = &parts->mV;
	पूर्णांक ret = 0;
	पूर्णांक uV;

	अगर (req->mask == 0)
		वापस -EINVAL;

	uV = regulator_list_voltage_linear_range(rdev, selector);
	अगर (uV < 0)
		वापस uV;

	mutex_lock(&vreg->lock);
	अगर (vreg->is_enabled)
		ret = rpm_reg_ग_लिखो(vreg, req, uV / 1000);

	अगर (!ret)
		vreg->uV = uV;
	mutex_unlock(&vreg->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_set_uV_sel(काष्ठा regulator_dev *rdev,
			      अचिन्हित selector)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा rpm_reg_parts *parts = vreg->parts;
	स्थिर काष्ठा request_member *req = &parts->uV;
	पूर्णांक ret = 0;
	पूर्णांक uV;

	अगर (req->mask == 0)
		वापस -EINVAL;

	uV = regulator_list_voltage_linear_range(rdev, selector);
	अगर (uV < 0)
		वापस uV;

	mutex_lock(&vreg->lock);
	अगर (vreg->is_enabled)
		ret = rpm_reg_ग_लिखो(vreg, req, uV);

	अगर (!ret)
		vreg->uV = uV;
	mutex_unlock(&vreg->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);

	वापस vreg->uV;
पूर्ण

अटल पूर्णांक rpm_reg_mV_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा rpm_reg_parts *parts = vreg->parts;
	स्थिर काष्ठा request_member *req = &parts->mV;
	पूर्णांक ret;

	अगर (req->mask == 0)
		वापस -EINVAL;

	mutex_lock(&vreg->lock);
	ret = rpm_reg_ग_लिखो(vreg, req, vreg->uV / 1000);
	अगर (!ret)
		vreg->is_enabled = 1;
	mutex_unlock(&vreg->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_uV_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा rpm_reg_parts *parts = vreg->parts;
	स्थिर काष्ठा request_member *req = &parts->uV;
	पूर्णांक ret;

	अगर (req->mask == 0)
		वापस -EINVAL;

	mutex_lock(&vreg->lock);
	ret = rpm_reg_ग_लिखो(vreg, req, vreg->uV);
	अगर (!ret)
		vreg->is_enabled = 1;
	mutex_unlock(&vreg->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_चयन_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा rpm_reg_parts *parts = vreg->parts;
	स्थिर काष्ठा request_member *req = &parts->enable_state;
	पूर्णांक ret;

	अगर (req->mask == 0)
		वापस -EINVAL;

	mutex_lock(&vreg->lock);
	ret = rpm_reg_ग_लिखो(vreg, req, 1);
	अगर (!ret)
		vreg->is_enabled = 1;
	mutex_unlock(&vreg->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_mV_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा rpm_reg_parts *parts = vreg->parts;
	स्थिर काष्ठा request_member *req = &parts->mV;
	पूर्णांक ret;

	अगर (req->mask == 0)
		वापस -EINVAL;

	mutex_lock(&vreg->lock);
	ret = rpm_reg_ग_लिखो(vreg, req, 0);
	अगर (!ret)
		vreg->is_enabled = 0;
	mutex_unlock(&vreg->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_uV_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा rpm_reg_parts *parts = vreg->parts;
	स्थिर काष्ठा request_member *req = &parts->uV;
	पूर्णांक ret;

	अगर (req->mask == 0)
		वापस -EINVAL;

	mutex_lock(&vreg->lock);
	ret = rpm_reg_ग_लिखो(vreg, req, 0);
	अगर (!ret)
		vreg->is_enabled = 0;
	mutex_unlock(&vreg->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_चयन_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा rpm_reg_parts *parts = vreg->parts;
	स्थिर काष्ठा request_member *req = &parts->enable_state;
	पूर्णांक ret;

	अगर (req->mask == 0)
		वापस -EINVAL;

	mutex_lock(&vreg->lock);
	ret = rpm_reg_ग_लिखो(vreg, req, 0);
	अगर (!ret)
		vreg->is_enabled = 0;
	mutex_unlock(&vreg->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpm_reg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);

	वापस vreg->is_enabled;
पूर्ण

अटल पूर्णांक rpm_reg_set_load(काष्ठा regulator_dev *rdev, पूर्णांक load_uA)
अणु
	काष्ठा qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	स्थिर काष्ठा rpm_reg_parts *parts = vreg->parts;
	स्थिर काष्ठा request_member *req = &parts->ia;
	पूर्णांक load_mA = load_uA / 1000;
	पूर्णांक max_mA = req->mask >> req->shअगरt;
	पूर्णांक ret;

	अगर (req->mask == 0)
		वापस -EINVAL;

	अगर (load_mA > max_mA)
		load_mA = max_mA;

	mutex_lock(&vreg->lock);
	ret = rpm_reg_ग_लिखो(vreg, req, load_mA);
	mutex_unlock(&vreg->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops uV_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,

	.set_voltage_sel = rpm_reg_set_uV_sel,
	.get_voltage = rpm_reg_get_voltage,

	.enable = rpm_reg_uV_enable,
	.disable = rpm_reg_uV_disable,
	.is_enabled = rpm_reg_is_enabled,

	.set_load = rpm_reg_set_load,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mV_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,

	.set_voltage_sel = rpm_reg_set_mV_sel,
	.get_voltage = rpm_reg_get_voltage,

	.enable = rpm_reg_mV_enable,
	.disable = rpm_reg_mV_disable,
	.is_enabled = rpm_reg_is_enabled,

	.set_load = rpm_reg_set_load,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops चयन_ops = अणु
	.enable = rpm_reg_चयन_enable,
	.disable = rpm_reg_चयन_disable,
	.is_enabled = rpm_reg_is_enabled,
पूर्ण;

/*
 * PM8018 regulators
 */
अटल स्थिर काष्ठा qcom_rpm_reg pm8018_plकरो = अणु
	.desc.linear_ranges = plकरो_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(plकरो_ranges),
	.desc.n_voltages = 161,
	.desc.ops = &uV_ops,
	.parts = &rpm8960_lकरो_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = false,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8018_nlकरो = अणु
	.desc.linear_ranges = nlकरो_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(nlकरो_ranges),
	.desc.n_voltages = 64,
	.desc.ops = &uV_ops,
	.parts = &rpm8960_lकरो_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = false,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8018_smps = अणु
	.desc.linear_ranges = smps_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(smps_ranges),
	.desc.n_voltages = 154,
	.desc.ops = &uV_ops,
	.parts = &rpm8960_smps_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = false,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8018_चयन = अणु
	.desc.ops = &चयन_ops,
	.parts = &rpm8960_चयन_parts,
पूर्ण;

/*
 * PM8058 regulators
 */
अटल स्थिर काष्ठा qcom_rpm_reg pm8058_plकरो = अणु
	.desc.linear_ranges = plकरो_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(plकरो_ranges),
	.desc.n_voltages = 161,
	.desc.ops = &mV_ops,
	.parts = &rpm8660_lकरो_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = false,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8058_nlकरो = अणु
	.desc.linear_ranges = nlकरो_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(nlकरो_ranges),
	.desc.n_voltages = 64,
	.desc.ops = &mV_ops,
	.parts = &rpm8660_lकरो_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = false,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8058_smps = अणु
	.desc.linear_ranges = smps_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(smps_ranges),
	.desc.n_voltages = 154,
	.desc.ops = &mV_ops,
	.parts = &rpm8660_smps_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = false,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8058_ncp = अणु
	.desc.linear_ranges = ncp_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(ncp_ranges),
	.desc.n_voltages = 32,
	.desc.ops = &mV_ops,
	.parts = &rpm8660_ncp_parts,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8058_चयन = अणु
	.desc.ops = &चयन_ops,
	.parts = &rpm8660_चयन_parts,
पूर्ण;

/*
 * PM8901 regulators
 */
अटल स्थिर काष्ठा qcom_rpm_reg pm8901_plकरो = अणु
	.desc.linear_ranges = plकरो_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(plकरो_ranges),
	.desc.n_voltages = 161,
	.desc.ops = &mV_ops,
	.parts = &rpm8660_lकरो_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8901_nlकरो = अणु
	.desc.linear_ranges = nlकरो_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(nlकरो_ranges),
	.desc.n_voltages = 64,
	.desc.ops = &mV_ops,
	.parts = &rpm8660_lकरो_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8901_ftsmps = अणु
	.desc.linear_ranges = ftsmps_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(ftsmps_ranges),
	.desc.n_voltages = 101,
	.desc.ops = &mV_ops,
	.parts = &rpm8660_smps_parts,
	.supports_क्रमce_mode_स्वतः = true,
	.supports_क्रमce_mode_bypass = false,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8901_चयन = अणु
	.desc.ops = &चयन_ops,
	.parts = &rpm8660_चयन_parts,
पूर्ण;

/*
 * PM8921 regulators
 */
अटल स्थिर काष्ठा qcom_rpm_reg pm8921_plकरो = अणु
	.desc.linear_ranges = plकरो_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(plकरो_ranges),
	.desc.n_voltages = 161,
	.desc.ops = &uV_ops,
	.parts = &rpm8960_lकरो_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8921_nlकरो = अणु
	.desc.linear_ranges = nlकरो_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(nlकरो_ranges),
	.desc.n_voltages = 64,
	.desc.ops = &uV_ops,
	.parts = &rpm8960_lकरो_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8921_nlकरो1200 = अणु
	.desc.linear_ranges = nlकरो1200_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(nlकरो1200_ranges),
	.desc.n_voltages = 124,
	.desc.ops = &uV_ops,
	.parts = &rpm8960_lकरो_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = true,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8921_smps = अणु
	.desc.linear_ranges = smps_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(smps_ranges),
	.desc.n_voltages = 154,
	.desc.ops = &uV_ops,
	.parts = &rpm8960_smps_parts,
	.supports_क्रमce_mode_स्वतः = true,
	.supports_क्रमce_mode_bypass = false,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8921_ncp = अणु
	.desc.linear_ranges = ncp_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(ncp_ranges),
	.desc.n_voltages = 32,
	.desc.ops = &uV_ops,
	.parts = &rpm8960_ncp_parts,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg pm8921_चयन = अणु
	.desc.ops = &चयन_ops,
	.parts = &rpm8960_चयन_parts,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_reg smb208_smps = अणु
	.desc.linear_ranges = smb208_ranges,
	.desc.n_linear_ranges = ARRAY_SIZE(smb208_ranges),
	.desc.n_voltages = 235,
	.desc.ops = &uV_ops,
	.parts = &rpm8960_smps_parts,
	.supports_क्रमce_mode_स्वतः = false,
	.supports_क्रमce_mode_bypass = false,
पूर्ण;

अटल पूर्णांक rpm_reg_set(काष्ठा qcom_rpm_reg *vreg,
		       स्थिर काष्ठा request_member *req,
		       स्थिर पूर्णांक value)
अणु
	अगर (req->mask == 0 || (value << req->shअगरt) & ~req->mask)
		वापस -EINVAL;

	vreg->val[req->word] &= ~req->mask;
	vreg->val[req->word] |= value << req->shअगरt;

	वापस 0;
पूर्ण

अटल पूर्णांक rpm_reg_of_parse_freq(काष्ठा device *dev,
				 काष्ठा device_node *node,
				 काष्ठा qcom_rpm_reg *vreg)
अणु
	अटल स्थिर पूर्णांक freq_table[] = अणु
		19200000, 9600000, 6400000, 4800000, 3840000, 3200000, 2740000,
		2400000, 2130000, 1920000, 1750000, 1600000, 1480000, 1370000,
		1280000, 1200000,

	पूर्ण;
	स्थिर अक्षर *key;
	u32 freq;
	पूर्णांक ret;
	पूर्णांक i;

	key = "qcom,switch-mode-frequency";
	ret = of_property_पढ़ो_u32(node, key, &freq);
	अगर (ret) अणु
		dev_err(dev, "regulator requires %s property\n", key);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(freq_table); i++) अणु
		अगर (freq == freq_table[i]) अणु
			rpm_reg_set(vreg, &vreg->parts->freq, i + 1);
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(dev, "invalid frequency %d\n", freq);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rpm_reg_of_parse(काष्ठा device_node *node,
			    स्थिर काष्ठा regulator_desc *desc,
			    काष्ठा regulator_config *config)
अणु
	काष्ठा qcom_rpm_reg *vreg = config->driver_data;
	काष्ठा device *dev = config->dev;
	स्थिर अक्षर *key;
	u32 क्रमce_mode;
	bool pwm;
	u32 val;
	पूर्णांक ret;

	key = "bias-pull-down";
	अगर (of_property_पढ़ो_bool(node, key)) अणु
		ret = rpm_reg_set(vreg, &vreg->parts->pd, 1);
		अगर (ret) अणु
			dev_err(dev, "%s is invalid", key);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (vreg->parts->freq.mask) अणु
		ret = rpm_reg_of_parse_freq(dev, node, vreg);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (vreg->parts->pm.mask) अणु
		key = "qcom,power-mode-hysteretic";
		pwm = !of_property_पढ़ो_bool(node, key);

		ret = rpm_reg_set(vreg, &vreg->parts->pm, pwm);
		अगर (ret) अणु
			dev_err(dev, "failed to set power mode\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (vreg->parts->fm.mask) अणु
		क्रमce_mode = -1;

		key = "qcom,force-mode";
		ret = of_property_पढ़ो_u32(node, key, &val);
		अगर (ret == -EINVAL) अणु
			val = QCOM_RPM_FORCE_MODE_NONE;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			dev_err(dev, "failed to read %s\n", key);
			वापस ret;
		पूर्ण

		/*
		 * If क्रमce-mode is encoded as 2 bits then the
		 * possible रेजिस्टर values are:
		 * NONE, LPM, HPM
		 * otherwise:
		 * NONE, LPM, AUTO, HPM, BYPASS
		 */
		चयन (val) अणु
		हाल QCOM_RPM_FORCE_MODE_NONE:
			क्रमce_mode = 0;
			अवरोध;
		हाल QCOM_RPM_FORCE_MODE_LPM:
			क्रमce_mode = 1;
			अवरोध;
		हाल QCOM_RPM_FORCE_MODE_HPM:
			अगर (FORCE_MODE_IS_2_BITS(vreg))
				क्रमce_mode = 2;
			अन्यथा
				क्रमce_mode = 3;
			अवरोध;
		हाल QCOM_RPM_FORCE_MODE_AUTO:
			अगर (vreg->supports_क्रमce_mode_स्वतः)
				क्रमce_mode = 2;
			अवरोध;
		हाल QCOM_RPM_FORCE_MODE_BYPASS:
			अगर (vreg->supports_क्रमce_mode_bypass)
				क्रमce_mode = 4;
			अवरोध;
		पूर्ण

		अगर (क्रमce_mode == -1) अणु
			dev_err(dev, "invalid force mode\n");
			वापस -EINVAL;
		पूर्ण

		ret = rpm_reg_set(vreg, &vreg->parts->fm, क्रमce_mode);
		अगर (ret) अणु
			dev_err(dev, "failed to set force mode\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा rpm_regulator_data अणु
	स्थिर अक्षर *name;
	पूर्णांक resource;
	स्थिर काष्ठा qcom_rpm_reg *ढाँचा;
	स्थिर अक्षर *supply;
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8018_regulators[] = अणु
	अणु "s1",  QCOM_RPM_PM8018_SMPS1, &pm8018_smps, "vdd_s1" पूर्ण,
	अणु "s2",  QCOM_RPM_PM8018_SMPS2, &pm8018_smps, "vdd_s2" पूर्ण,
	अणु "s3",  QCOM_RPM_PM8018_SMPS3, &pm8018_smps, "vdd_s3" पूर्ण,
	अणु "s4",  QCOM_RPM_PM8018_SMPS4, &pm8018_smps, "vdd_s4" पूर्ण,
	अणु "s5",  QCOM_RPM_PM8018_SMPS5, &pm8018_smps, "vdd_s5" पूर्ण,

	अणु "l2",  QCOM_RPM_PM8018_LDO2,  &pm8018_plकरो, "vdd_l2" पूर्ण,
	अणु "l3",  QCOM_RPM_PM8018_LDO3,  &pm8018_plकरो, "vdd_l3" पूर्ण,
	अणु "l4",  QCOM_RPM_PM8018_LDO4,  &pm8018_plकरो, "vdd_l4" पूर्ण,
	अणु "l5",  QCOM_RPM_PM8018_LDO5,  &pm8018_plकरो, "vdd_l5" पूर्ण,
	अणु "l6",  QCOM_RPM_PM8018_LDO6,  &pm8018_plकरो, "vdd_l7" पूर्ण,
	अणु "l7",  QCOM_RPM_PM8018_LDO7,  &pm8018_plकरो, "vdd_l7" पूर्ण,
	अणु "l8",  QCOM_RPM_PM8018_LDO8,  &pm8018_nlकरो, "vdd_l8" पूर्ण,
	अणु "l9",  QCOM_RPM_PM8018_LDO9,  &pm8921_nlकरो1200,
						      "vdd_l9_l10_l11_l12" पूर्ण,
	अणु "l10", QCOM_RPM_PM8018_LDO10, &pm8018_nlकरो, "vdd_l9_l10_l11_l12" पूर्ण,
	अणु "l11", QCOM_RPM_PM8018_LDO11, &pm8018_nlकरो, "vdd_l9_l10_l11_l12" पूर्ण,
	अणु "l12", QCOM_RPM_PM8018_LDO12, &pm8018_nlकरो, "vdd_l9_l10_l11_l12" पूर्ण,
	अणु "l14", QCOM_RPM_PM8018_LDO14, &pm8018_plकरो, "vdd_l14" पूर्ण,

	अणु "lvs1", QCOM_RPM_PM8018_LVS1, &pm8018_चयन, "lvs1_in" पूर्ण,

	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8058_regulators[] = अणु
	अणु "l0",   QCOM_RPM_PM8058_LDO0,   &pm8058_nlकरो, "vdd_l0_l1_lvs"	पूर्ण,
	अणु "l1",   QCOM_RPM_PM8058_LDO1,   &pm8058_nlकरो, "vdd_l0_l1_lvs" पूर्ण,
	अणु "l2",   QCOM_RPM_PM8058_LDO2,   &pm8058_plकरो, "vdd_l2_l11_l12" पूर्ण,
	अणु "l3",   QCOM_RPM_PM8058_LDO3,   &pm8058_plकरो, "vdd_l3_l4_l5" पूर्ण,
	अणु "l4",   QCOM_RPM_PM8058_LDO4,   &pm8058_plकरो, "vdd_l3_l4_l5" पूर्ण,
	अणु "l5",   QCOM_RPM_PM8058_LDO5,   &pm8058_plकरो, "vdd_l3_l4_l5" पूर्ण,
	अणु "l6",   QCOM_RPM_PM8058_LDO6,   &pm8058_plकरो, "vdd_l6_l7" पूर्ण,
	अणु "l7",   QCOM_RPM_PM8058_LDO7,   &pm8058_plकरो, "vdd_l6_l7" पूर्ण,
	अणु "l8",   QCOM_RPM_PM8058_LDO8,   &pm8058_plकरो, "vdd_l8" पूर्ण,
	अणु "l9",   QCOM_RPM_PM8058_LDO9,   &pm8058_plकरो, "vdd_l9" पूर्ण,
	अणु "l10",  QCOM_RPM_PM8058_LDO10,  &pm8058_plकरो, "vdd_l10" पूर्ण,
	अणु "l11",  QCOM_RPM_PM8058_LDO11,  &pm8058_plकरो, "vdd_l2_l11_l12" पूर्ण,
	अणु "l12",  QCOM_RPM_PM8058_LDO12,  &pm8058_plकरो, "vdd_l2_l11_l12" पूर्ण,
	अणु "l13",  QCOM_RPM_PM8058_LDO13,  &pm8058_plकरो, "vdd_l13_l16" पूर्ण,
	अणु "l14",  QCOM_RPM_PM8058_LDO14,  &pm8058_plकरो, "vdd_l14_l15" पूर्ण,
	अणु "l15",  QCOM_RPM_PM8058_LDO15,  &pm8058_plकरो, "vdd_l14_l15" पूर्ण,
	अणु "l16",  QCOM_RPM_PM8058_LDO16,  &pm8058_plकरो, "vdd_l13_l16" पूर्ण,
	अणु "l17",  QCOM_RPM_PM8058_LDO17,  &pm8058_plकरो, "vdd_l17_l18" पूर्ण,
	अणु "l18",  QCOM_RPM_PM8058_LDO18,  &pm8058_plकरो, "vdd_l17_l18" पूर्ण,
	अणु "l19",  QCOM_RPM_PM8058_LDO19,  &pm8058_plकरो, "vdd_l19_l20" पूर्ण,
	अणु "l20",  QCOM_RPM_PM8058_LDO20,  &pm8058_plकरो, "vdd_l19_l20" पूर्ण,
	अणु "l21",  QCOM_RPM_PM8058_LDO21,  &pm8058_nlकरो, "vdd_l21" पूर्ण,
	अणु "l22",  QCOM_RPM_PM8058_LDO22,  &pm8058_nlकरो, "vdd_l22" पूर्ण,
	अणु "l23",  QCOM_RPM_PM8058_LDO23,  &pm8058_nlकरो, "vdd_l23_l24_l25" पूर्ण,
	अणु "l24",  QCOM_RPM_PM8058_LDO24,  &pm8058_nlकरो, "vdd_l23_l24_l25" पूर्ण,
	अणु "l25",  QCOM_RPM_PM8058_LDO25,  &pm8058_nlकरो, "vdd_l23_l24_l25" पूर्ण,

	अणु "s0",   QCOM_RPM_PM8058_SMPS0,  &pm8058_smps, "vdd_s0" पूर्ण,
	अणु "s1",   QCOM_RPM_PM8058_SMPS1,  &pm8058_smps, "vdd_s1" पूर्ण,
	अणु "s2",   QCOM_RPM_PM8058_SMPS2,  &pm8058_smps, "vdd_s2" पूर्ण,
	अणु "s3",   QCOM_RPM_PM8058_SMPS3,  &pm8058_smps, "vdd_s3" पूर्ण,
	अणु "s4",   QCOM_RPM_PM8058_SMPS4,  &pm8058_smps, "vdd_s4" पूर्ण,

	अणु "lvs0", QCOM_RPM_PM8058_LVS0, &pm8058_चयन, "vdd_l0_l1_lvs" पूर्ण,
	अणु "lvs1", QCOM_RPM_PM8058_LVS1, &pm8058_चयन, "vdd_l0_l1_lvs" पूर्ण,

	अणु "ncp",  QCOM_RPM_PM8058_NCP, &pm8058_ncp, "vdd_ncp" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8901_regulators[] = अणु
	अणु "l0",   QCOM_RPM_PM8901_LDO0, &pm8901_nlकरो, "vdd_l0" पूर्ण,
	अणु "l1",   QCOM_RPM_PM8901_LDO1, &pm8901_plकरो, "vdd_l1" पूर्ण,
	अणु "l2",   QCOM_RPM_PM8901_LDO2, &pm8901_plकरो, "vdd_l2" पूर्ण,
	अणु "l3",   QCOM_RPM_PM8901_LDO3, &pm8901_plकरो, "vdd_l3" पूर्ण,
	अणु "l4",   QCOM_RPM_PM8901_LDO4, &pm8901_plकरो, "vdd_l4" पूर्ण,
	अणु "l5",   QCOM_RPM_PM8901_LDO5, &pm8901_plकरो, "vdd_l5" पूर्ण,
	अणु "l6",   QCOM_RPM_PM8901_LDO6, &pm8901_plकरो, "vdd_l6" पूर्ण,

	अणु "s0",   QCOM_RPM_PM8901_SMPS0, &pm8901_ftsmps, "vdd_s0" पूर्ण,
	अणु "s1",   QCOM_RPM_PM8901_SMPS1, &pm8901_ftsmps, "vdd_s1" पूर्ण,
	अणु "s2",   QCOM_RPM_PM8901_SMPS2, &pm8901_ftsmps, "vdd_s2" पूर्ण,
	अणु "s3",   QCOM_RPM_PM8901_SMPS3, &pm8901_ftsmps, "vdd_s3" पूर्ण,
	अणु "s4",   QCOM_RPM_PM8901_SMPS4, &pm8901_ftsmps, "vdd_s4" पूर्ण,

	अणु "lvs0", QCOM_RPM_PM8901_LVS0, &pm8901_चयन, "lvs0_in" पूर्ण,
	अणु "lvs1", QCOM_RPM_PM8901_LVS1, &pm8901_चयन, "lvs1_in" पूर्ण,
	अणु "lvs2", QCOM_RPM_PM8901_LVS2, &pm8901_चयन, "lvs2_in" पूर्ण,
	अणु "lvs3", QCOM_RPM_PM8901_LVS3, &pm8901_चयन, "lvs3_in" पूर्ण,

	अणु "mvs", QCOM_RPM_PM8901_MVS, &pm8901_चयन, "mvs_in" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_pm8921_regulators[] = अणु
	अणु "s1",  QCOM_RPM_PM8921_SMPS1, &pm8921_smps, "vdd_s1" पूर्ण,
	अणु "s2",  QCOM_RPM_PM8921_SMPS2, &pm8921_smps, "vdd_s2" पूर्ण,
	अणु "s3",  QCOM_RPM_PM8921_SMPS3, &pm8921_smps पूर्ण,
	अणु "s4",  QCOM_RPM_PM8921_SMPS4, &pm8921_smps, "vdd_s4" पूर्ण,
	अणु "s7",  QCOM_RPM_PM8921_SMPS7, &pm8921_smps, "vdd_s7" पूर्ण,
	अणु "s8",  QCOM_RPM_PM8921_SMPS8, &pm8921_smps, "vdd_s8"  पूर्ण,

	अणु "l1",  QCOM_RPM_PM8921_LDO1, &pm8921_nlकरो, "vdd_l1_l2_l12_l18" पूर्ण,
	अणु "l2",  QCOM_RPM_PM8921_LDO2, &pm8921_nlकरो, "vdd_l1_l2_l12_l18" पूर्ण,
	अणु "l3",  QCOM_RPM_PM8921_LDO3, &pm8921_plकरो, "vdd_l3_l15_l17" पूर्ण,
	अणु "l4",  QCOM_RPM_PM8921_LDO4, &pm8921_plकरो, "vdd_l4_l14" पूर्ण,
	अणु "l5",  QCOM_RPM_PM8921_LDO5, &pm8921_plकरो, "vdd_l5_l8_l16" पूर्ण,
	अणु "l6",  QCOM_RPM_PM8921_LDO6, &pm8921_plकरो, "vdd_l6_l7" पूर्ण,
	अणु "l7",  QCOM_RPM_PM8921_LDO7, &pm8921_plकरो, "vdd_l6_l7" पूर्ण,
	अणु "l8",  QCOM_RPM_PM8921_LDO8, &pm8921_plकरो, "vdd_l5_l8_l16" पूर्ण,
	अणु "l9",  QCOM_RPM_PM8921_LDO9, &pm8921_plकरो, "vdd_l9_l11" पूर्ण,
	अणु "l10", QCOM_RPM_PM8921_LDO10, &pm8921_plकरो, "vdd_l10_l22" पूर्ण,
	अणु "l11", QCOM_RPM_PM8921_LDO11, &pm8921_plकरो, "vdd_l9_l11" पूर्ण,
	अणु "l12", QCOM_RPM_PM8921_LDO12, &pm8921_nlकरो, "vdd_l1_l2_l12_l18" पूर्ण,
	अणु "l14", QCOM_RPM_PM8921_LDO14, &pm8921_plकरो, "vdd_l4_l14" पूर्ण,
	अणु "l15", QCOM_RPM_PM8921_LDO15, &pm8921_plकरो, "vdd_l3_l15_l17" पूर्ण,
	अणु "l16", QCOM_RPM_PM8921_LDO16, &pm8921_plकरो, "vdd_l5_l8_l16" पूर्ण,
	अणु "l17", QCOM_RPM_PM8921_LDO17, &pm8921_plकरो, "vdd_l3_l15_l17" पूर्ण,
	अणु "l18", QCOM_RPM_PM8921_LDO18, &pm8921_nlकरो, "vdd_l1_l2_l12_l18" पूर्ण,
	अणु "l21", QCOM_RPM_PM8921_LDO21, &pm8921_plकरो, "vdd_l21_l23_l29" पूर्ण,
	अणु "l22", QCOM_RPM_PM8921_LDO22, &pm8921_plकरो, "vdd_l10_l22" पूर्ण,
	अणु "l23", QCOM_RPM_PM8921_LDO23, &pm8921_plकरो, "vdd_l21_l23_l29" पूर्ण,
	अणु "l24", QCOM_RPM_PM8921_LDO24, &pm8921_nlकरो1200, "vdd_l24" पूर्ण,
	अणु "l25", QCOM_RPM_PM8921_LDO25, &pm8921_nlकरो1200, "vdd_l25" पूर्ण,
	अणु "l26", QCOM_RPM_PM8921_LDO26, &pm8921_nlकरो1200, "vdd_l26" पूर्ण,
	अणु "l27", QCOM_RPM_PM8921_LDO27, &pm8921_nlकरो1200, "vdd_l27" पूर्ण,
	अणु "l28", QCOM_RPM_PM8921_LDO28, &pm8921_nlकरो1200, "vdd_l28" पूर्ण,
	अणु "l29", QCOM_RPM_PM8921_LDO29, &pm8921_plकरो, "vdd_l21_l23_l29" पूर्ण,

	अणु "lvs1", QCOM_RPM_PM8921_LVS1, &pm8921_चयन, "vin_lvs1_3_6" पूर्ण,
	अणु "lvs2", QCOM_RPM_PM8921_LVS2, &pm8921_चयन, "vin_lvs2" पूर्ण,
	अणु "lvs3", QCOM_RPM_PM8921_LVS3, &pm8921_चयन, "vin_lvs1_3_6" पूर्ण,
	अणु "lvs4", QCOM_RPM_PM8921_LVS4, &pm8921_चयन, "vin_lvs4_5_7" पूर्ण,
	अणु "lvs5", QCOM_RPM_PM8921_LVS5, &pm8921_चयन, "vin_lvs4_5_7" पूर्ण,
	अणु "lvs6", QCOM_RPM_PM8921_LVS6, &pm8921_चयन, "vin_lvs1_3_6" पूर्ण,
	अणु "lvs7", QCOM_RPM_PM8921_LVS7, &pm8921_चयन, "vin_lvs4_5_7" पूर्ण,

	अणु "usb-switch", QCOM_RPM_USB_OTG_SWITCH, &pm8921_चयन, "vin_5vs" पूर्ण,
	अणु "hdmi-switch", QCOM_RPM_HDMI_SWITCH, &pm8921_चयन, "vin_5vs" पूर्ण,
	अणु "ncp", QCOM_RPM_PM8921_NCP, &pm8921_ncp, "vdd_ncp" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpm_regulator_data rpm_smb208_regulators[] = अणु
	अणु "s1a",  QCOM_RPM_SMB208_S1a, &smb208_smps, "vin_s1a" पूर्ण,
	अणु "s1b",  QCOM_RPM_SMB208_S1b, &smb208_smps, "vin_s1b" पूर्ण,
	अणु "s2a",  QCOM_RPM_SMB208_S2a, &smb208_smps, "vin_s2a" पूर्ण,
	अणु "s2b",  QCOM_RPM_SMB208_S2b, &smb208_smps, "vin_s2b" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id rpm_of_match[] = अणु
	अणु .compatible = "qcom,rpm-pm8018-regulators",
		.data = &rpm_pm8018_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm8058-regulators", .data = &rpm_pm8058_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm8901-regulators", .data = &rpm_pm8901_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-pm8921-regulators", .data = &rpm_pm8921_regulators पूर्ण,
	अणु .compatible = "qcom,rpm-smb208-regulators", .data = &rpm_smb208_regulators पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rpm_of_match);

अटल पूर्णांक rpm_reg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा rpm_regulator_data *reg;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा qcom_rpm_reg *vreg;
	काष्ठा qcom_rpm *rpm;

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
		vreg = devm_kदो_स्मृति(&pdev->dev, माप(*vreg), GFP_KERNEL);
		अगर (!vreg)
			वापस -ENOMEM;

		स_नकल(vreg, reg->ढाँचा, माप(*vreg));
		mutex_init(&vreg->lock);

		vreg->dev = &pdev->dev;
		vreg->resource = reg->resource;
		vreg->rpm = rpm;

		vreg->desc.id = -1;
		vreg->desc.owner = THIS_MODULE;
		vreg->desc.type = REGULATOR_VOLTAGE;
		vreg->desc.name = reg->name;
		vreg->desc.supply_name = reg->supply;
		vreg->desc.of_match = reg->name;
		vreg->desc.of_parse_cb = rpm_reg_of_parse;

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
	.probe          = rpm_reg_probe,
	.driver  = अणु
		.name  = "qcom_rpm_reg",
		.of_match_table = of_match_ptr(rpm_of_match),
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
