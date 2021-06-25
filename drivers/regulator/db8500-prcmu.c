<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Authors: Sundar Iyer <sundar.iyer@stericsson.com> क्रम ST-Ericsson
 *          Bengt Jonsson <bengt.g.jonsson@stericsson.com> क्रम ST-Ericsson
 *
 * Power करोमुख्य regulators on DB8500
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/dbx500-prcmu.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/db8500-prcmu.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश "dbx500-prcmu.h"

अटल पूर्णांक db8500_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा dbx500_regulator_info *info = rdev_get_drvdata(rdev);

	अगर (info == शून्य)
		वापस -EINVAL;

	dev_vdbg(rdev_get_dev(rdev), "regulator-%s-enable\n",
		info->desc.name);

	अगर (!info->is_enabled) अणु
		info->is_enabled = true;
		अगर (!info->exclude_from_घातer_state)
			घातer_state_active_enable();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक db8500_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा dbx500_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक ret = 0;

	अगर (info == शून्य)
		वापस -EINVAL;

	dev_vdbg(rdev_get_dev(rdev), "regulator-%s-disable\n",
		info->desc.name);

	अगर (info->is_enabled) अणु
		info->is_enabled = false;
		अगर (!info->exclude_from_घातer_state)
			ret = घातer_state_active_disable();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक db8500_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा dbx500_regulator_info *info = rdev_get_drvdata(rdev);

	अगर (info == शून्य)
		वापस -EINVAL;

	dev_vdbg(rdev_get_dev(rdev), "regulator-%s-is_enabled (is_enabled):"
		" %i\n", info->desc.name, info->is_enabled);

	वापस info->is_enabled;
पूर्ण

/* db8500 regulator operations */
अटल स्थिर काष्ठा regulator_ops db8500_regulator_ops = अणु
	.enable			= db8500_regulator_enable,
	.disable		= db8500_regulator_disable,
	.is_enabled		= db8500_regulator_is_enabled,
पूर्ण;

/*
 * EPOD control
 */
अटल bool epod_on[NUM_EPOD_ID];
अटल bool epod_ramret[NUM_EPOD_ID];

अटल पूर्णांक enable_epod(u16 epod_id, bool ramret)
अणु
	पूर्णांक ret;

	अगर (ramret) अणु
		अगर (!epod_on[epod_id]) अणु
			ret = prcmu_set_epod(epod_id, EPOD_STATE_RAMRET);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		epod_ramret[epod_id] = true;
	पूर्ण अन्यथा अणु
		ret = prcmu_set_epod(epod_id, EPOD_STATE_ON);
		अगर (ret < 0)
			वापस ret;
		epod_on[epod_id] = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक disable_epod(u16 epod_id, bool ramret)
अणु
	पूर्णांक ret;

	अगर (ramret) अणु
		अगर (!epod_on[epod_id]) अणु
			ret = prcmu_set_epod(epod_id, EPOD_STATE_OFF);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		epod_ramret[epod_id] = false;
	पूर्ण अन्यथा अणु
		अगर (epod_ramret[epod_id]) अणु
			ret = prcmu_set_epod(epod_id, EPOD_STATE_RAMRET);
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अणु
			ret = prcmu_set_epod(epod_id, EPOD_STATE_OFF);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		epod_on[epod_id] = false;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Regulator चयन
 */
अटल पूर्णांक db8500_regulator_चयन_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा dbx500_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	अगर (info == शून्य)
		वापस -EINVAL;

	dev_vdbg(rdev_get_dev(rdev), "regulator-switch-%s-enable\n",
		info->desc.name);

	ret = enable_epod(info->epod_id, info->is_ramret);
	अगर (ret < 0) अणु
		dev_err(rdev_get_dev(rdev),
			"regulator-switch-%s-enable: prcmu call failed\n",
			info->desc.name);
		जाओ out;
	पूर्ण

	info->is_enabled = true;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक db8500_regulator_चयन_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा dbx500_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	अगर (info == शून्य)
		वापस -EINVAL;

	dev_vdbg(rdev_get_dev(rdev), "regulator-switch-%s-disable\n",
		info->desc.name);

	ret = disable_epod(info->epod_id, info->is_ramret);
	अगर (ret < 0) अणु
		dev_err(rdev_get_dev(rdev),
			"regulator_switch-%s-disable: prcmu call failed\n",
			info->desc.name);
		जाओ out;
	पूर्ण

	info->is_enabled = false;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक db8500_regulator_चयन_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा dbx500_regulator_info *info = rdev_get_drvdata(rdev);

	अगर (info == शून्य)
		वापस -EINVAL;

	dev_vdbg(rdev_get_dev(rdev),
		"regulator-switch-%s-is_enabled (is_enabled): %i\n",
		info->desc.name, info->is_enabled);

	वापस info->is_enabled;
पूर्ण

अटल स्थिर काष्ठा regulator_ops db8500_regulator_चयन_ops = अणु
	.enable			= db8500_regulator_चयन_enable,
	.disable		= db8500_regulator_चयन_disable,
	.is_enabled		= db8500_regulator_चयन_is_enabled,
पूर्ण;

/*
 * Regulator inक्रमmation
 */
अटल काष्ठा dbx500_regulator_info
dbx500_regulator_info[DB8500_NUM_REGULATORS] = अणु
	[DB8500_REGULATOR_VAPE] = अणु
		.desc = अणु
			.name	= "db8500-vape",
			.of_match = of_match_ptr("db8500_vape"),
			.id	= DB8500_REGULATOR_VAPE,
			.ops	= &db8500_regulator_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VARM] = अणु
		.desc = अणु
			.name	= "db8500-varm",
			.of_match = of_match_ptr("db8500_varm"),
			.id	= DB8500_REGULATOR_VARM,
			.ops	= &db8500_regulator_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VMODEM] = अणु
		.desc = अणु
			.name	= "db8500-vmodem",
			.of_match = of_match_ptr("db8500_vmodem"),
			.id	= DB8500_REGULATOR_VMODEM,
			.ops	= &db8500_regulator_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VPLL] = अणु
		.desc = अणु
			.name	= "db8500-vpll",
			.of_match = of_match_ptr("db8500_vpll"),
			.id	= DB8500_REGULATOR_VPLL,
			.ops	= &db8500_regulator_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VSMPS1] = अणु
		.desc = अणु
			.name	= "db8500-vsmps1",
			.of_match = of_match_ptr("db8500_vsmps1"),
			.id	= DB8500_REGULATOR_VSMPS1,
			.ops	= &db8500_regulator_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VSMPS2] = अणु
		.desc = अणु
			.name	= "db8500-vsmps2",
			.of_match = of_match_ptr("db8500_vsmps2"),
			.id	= DB8500_REGULATOR_VSMPS2,
			.ops	= &db8500_regulator_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
			.fixed_uV = 1800000,
			.n_voltages = 1,
		पूर्ण,
		.exclude_from_घातer_state = true,
	पूर्ण,
	[DB8500_REGULATOR_VSMPS3] = अणु
		.desc = अणु
			.name	= "db8500-vsmps3",
			.of_match = of_match_ptr("db8500_vsmps3"),
			.id	= DB8500_REGULATOR_VSMPS3,
			.ops	= &db8500_regulator_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_VRF1] = अणु
		.desc = अणु
			.name	= "db8500-vrf1",
			.of_match = of_match_ptr("db8500_vrf1"),
			.id	= DB8500_REGULATOR_VRF1,
			.ops	= &db8500_regulator_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SVAMMDSP] = अणु
		.desc = अणु
			.name	= "db8500-sva-mmdsp",
			.of_match = of_match_ptr("db8500_sva_mmdsp"),
			.id	= DB8500_REGULATOR_SWITCH_SVAMMDSP,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id = EPOD_ID_SVAMMDSP,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SVAMMDSPRET] = अणु
		.desc = अणु
			.name	= "db8500-sva-mmdsp-ret",
			.of_match = of_match_ptr("db8500_sva_mmdsp_ret"),
			.id	= DB8500_REGULATOR_SWITCH_SVAMMDSPRET,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id = EPOD_ID_SVAMMDSP,
		.is_ramret = true,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SVAPIPE] = अणु
		.desc = अणु
			.name	= "db8500-sva-pipe",
			.of_match = of_match_ptr("db8500_sva_pipe"),
			.id	= DB8500_REGULATOR_SWITCH_SVAPIPE,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id = EPOD_ID_SVAPIPE,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SIAMMDSP] = अणु
		.desc = अणु
			.name	= "db8500-sia-mmdsp",
			.of_match = of_match_ptr("db8500_sia_mmdsp"),
			.id	= DB8500_REGULATOR_SWITCH_SIAMMDSP,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id = EPOD_ID_SIAMMDSP,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SIAMMDSPRET] = अणु
		.desc = अणु
			.name	= "db8500-sia-mmdsp-ret",
			.of_match = of_match_ptr("db8500_sia_mmdsp_ret"),
			.id	= DB8500_REGULATOR_SWITCH_SIAMMDSPRET,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id = EPOD_ID_SIAMMDSP,
		.is_ramret = true,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SIAPIPE] = अणु
		.desc = अणु
			.name	= "db8500-sia-pipe",
			.of_match = of_match_ptr("db8500_sia_pipe"),
			.id	= DB8500_REGULATOR_SWITCH_SIAPIPE,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id = EPOD_ID_SIAPIPE,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_SGA] = अणु
		.desc = अणु
			.name	= "db8500-sga",
			.of_match = of_match_ptr("db8500_sga"),
			.id	= DB8500_REGULATOR_SWITCH_SGA,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id = EPOD_ID_SGA,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_B2R2_MCDE] = अणु
		.desc = अणु
			.name	= "db8500-b2r2-mcde",
			.of_match = of_match_ptr("db8500_b2r2_mcde"),
			.id	= DB8500_REGULATOR_SWITCH_B2R2_MCDE,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id = EPOD_ID_B2R2_MCDE,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_ESRAM12] = अणु
		.desc = अणु
			.name	= "db8500-esram12",
			.of_match = of_match_ptr("db8500_esram12"),
			.id	= DB8500_REGULATOR_SWITCH_ESRAM12,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id	= EPOD_ID_ESRAM12,
		.is_enabled	= true,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_ESRAM12RET] = अणु
		.desc = अणु
			.name	= "db8500-esram12-ret",
			.of_match = of_match_ptr("db8500_esram12_ret"),
			.id	= DB8500_REGULATOR_SWITCH_ESRAM12RET,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id = EPOD_ID_ESRAM12,
		.is_ramret = true,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_ESRAM34] = अणु
		.desc = अणु
			.name	= "db8500-esram34",
			.of_match = of_match_ptr("db8500_esram34"),
			.id	= DB8500_REGULATOR_SWITCH_ESRAM34,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id	= EPOD_ID_ESRAM34,
		.is_enabled	= true,
	पूर्ण,
	[DB8500_REGULATOR_SWITCH_ESRAM34RET] = अणु
		.desc = अणु
			.name	= "db8500-esram34-ret",
			.of_match = of_match_ptr("db8500_esram34_ret"),
			.id	= DB8500_REGULATOR_SWITCH_ESRAM34RET,
			.ops	= &db8500_regulator_चयन_ops,
			.type	= REGULATOR_VOLTAGE,
			.owner	= THIS_MODULE,
		पूर्ण,
		.epod_id = EPOD_ID_ESRAM34,
		.is_ramret = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक db8500_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_init_data *db8500_init_data;
	काष्ठा dbx500_regulator_info *info;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक err, i;

	db8500_init_data = dev_get_platdata(&pdev->dev);

	क्रम (i = 0; i < ARRAY_SIZE(dbx500_regulator_info); i++) अणु
		/* assign per-regulator data */
		info = &dbx500_regulator_info[i];

		config.driver_data = info;
		config.dev = &pdev->dev;
		अगर (db8500_init_data)
			config.init_data = &db8500_init_data[i];

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &info->desc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			err = PTR_ERR(rdev);
			dev_err(&pdev->dev, "failed to register %s: err %i\n",
				info->desc.name, err);
			वापस err;
		पूर्ण
		dev_dbg(&pdev->dev, "regulator-%s-probed\n", info->desc.name);
	पूर्ण

	ux500_regulator_debug_init(pdev, dbx500_regulator_info,
				   ARRAY_SIZE(dbx500_regulator_info));
	वापस 0;
पूर्ण

अटल पूर्णांक db8500_regulator_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	ux500_regulator_debug_निकास();

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver db8500_regulator_driver = अणु
	.driver = अणु
		.name = "db8500-prcmu-regulators",
	पूर्ण,
	.probe = db8500_regulator_probe,
	.हटाओ = db8500_regulator_हटाओ,
पूर्ण;

अटल पूर्णांक __init db8500_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&db8500_regulator_driver);
पूर्ण

अटल व्योम __निकास db8500_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&db8500_regulator_driver);
पूर्ण

arch_initcall(db8500_regulator_init);
module_निकास(db8500_regulator_निकास);

MODULE_AUTHOR("STMicroelectronics/ST-Ericsson");
MODULE_DESCRIPTION("DB8500 regulator driver");
MODULE_LICENSE("GPL v2");
