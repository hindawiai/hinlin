<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम voltage controller regulators
 *
 * Copyright (C) 2017 Google, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/coupler.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/sort.h>

#समावेश "internal.h"

काष्ठा vctrl_voltage_range अणु
	पूर्णांक min_uV;
	पूर्णांक max_uV;
पूर्ण;

काष्ठा vctrl_voltage_ranges अणु
	काष्ठा vctrl_voltage_range ctrl;
	काष्ठा vctrl_voltage_range out;
पूर्ण;

काष्ठा vctrl_voltage_table अणु
	पूर्णांक ctrl;
	पूर्णांक out;
	पूर्णांक ovp_min_sel;
पूर्ण;

काष्ठा vctrl_data अणु
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_desc desc;
	काष्ठा regulator *ctrl_reg;
	bool enabled;
	अचिन्हित पूर्णांक min_slew_करोwn_rate;
	अचिन्हित पूर्णांक ovp_threshold;
	काष्ठा vctrl_voltage_ranges vrange;
	काष्ठा vctrl_voltage_table *vtable;
	अचिन्हित पूर्णांक sel;
पूर्ण;

अटल पूर्णांक vctrl_calc_ctrl_voltage(काष्ठा vctrl_data *vctrl, पूर्णांक out_uV)
अणु
	काष्ठा vctrl_voltage_range *ctrl = &vctrl->vrange.ctrl;
	काष्ठा vctrl_voltage_range *out = &vctrl->vrange.out;

	वापस ctrl->min_uV +
		DIV_ROUND_CLOSEST_ULL((s64)(out_uV - out->min_uV) *
				      (ctrl->max_uV - ctrl->min_uV),
				      out->max_uV - out->min_uV);
पूर्ण

अटल पूर्णांक vctrl_calc_output_voltage(काष्ठा vctrl_data *vctrl, पूर्णांक ctrl_uV)
अणु
	काष्ठा vctrl_voltage_range *ctrl = &vctrl->vrange.ctrl;
	काष्ठा vctrl_voltage_range *out = &vctrl->vrange.out;

	अगर (ctrl_uV < 0) अणु
		pr_err("vctrl: failed to get control voltage\n");
		वापस ctrl_uV;
	पूर्ण

	अगर (ctrl_uV < ctrl->min_uV)
		वापस out->min_uV;

	अगर (ctrl_uV > ctrl->max_uV)
		वापस out->max_uV;

	वापस out->min_uV +
		DIV_ROUND_CLOSEST_ULL((s64)(ctrl_uV - ctrl->min_uV) *
				      (out->max_uV - out->min_uV),
				      ctrl->max_uV - ctrl->min_uV);
पूर्ण

अटल पूर्णांक vctrl_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा vctrl_data *vctrl = rdev_get_drvdata(rdev);
	पूर्णांक ctrl_uV = regulator_get_voltage_rdev(vctrl->ctrl_reg->rdev);

	वापस vctrl_calc_output_voltage(vctrl, ctrl_uV);
पूर्ण

अटल पूर्णांक vctrl_set_voltage(काष्ठा regulator_dev *rdev,
			     पूर्णांक req_min_uV, पूर्णांक req_max_uV,
			     अचिन्हित पूर्णांक *selector)
अणु
	काष्ठा vctrl_data *vctrl = rdev_get_drvdata(rdev);
	काष्ठा regulator *ctrl_reg = vctrl->ctrl_reg;
	पूर्णांक orig_ctrl_uV = regulator_get_voltage_rdev(ctrl_reg->rdev);
	पूर्णांक uV = vctrl_calc_output_voltage(vctrl, orig_ctrl_uV);
	पूर्णांक ret;

	अगर (req_min_uV >= uV || !vctrl->ovp_threshold)
		/* voltage rising or no OVP */
		वापस regulator_set_voltage_rdev(ctrl_reg->rdev,
			vctrl_calc_ctrl_voltage(vctrl, req_min_uV),
			vctrl_calc_ctrl_voltage(vctrl, req_max_uV),
			PM_SUSPEND_ON);

	जबतक (uV > req_min_uV) अणु
		पूर्णांक max_drop_uV = (uV * vctrl->ovp_threshold) / 100;
		पूर्णांक next_uV;
		पूर्णांक next_ctrl_uV;
		पूर्णांक delay;

		/* Make sure no infinite loop even in crazy हालs */
		अगर (max_drop_uV == 0)
			max_drop_uV = 1;

		next_uV = max_t(पूर्णांक, req_min_uV, uV - max_drop_uV);
		next_ctrl_uV = vctrl_calc_ctrl_voltage(vctrl, next_uV);

		ret = regulator_set_voltage_rdev(ctrl_reg->rdev,
					    next_ctrl_uV,
					    next_ctrl_uV,
					    PM_SUSPEND_ON);
		अगर (ret)
			जाओ err;

		delay = DIV_ROUND_UP(uV - next_uV, vctrl->min_slew_करोwn_rate);
		usleep_range(delay, delay + DIV_ROUND_UP(delay, 10));

		uV = next_uV;
	पूर्ण

	वापस 0;

err:
	/* Try to go back to original voltage */
	regulator_set_voltage_rdev(ctrl_reg->rdev, orig_ctrl_uV, orig_ctrl_uV,
				   PM_SUSPEND_ON);

	वापस ret;
पूर्ण

अटल पूर्णांक vctrl_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा vctrl_data *vctrl = rdev_get_drvdata(rdev);

	वापस vctrl->sel;
पूर्ण

अटल पूर्णांक vctrl_set_voltage_sel(काष्ठा regulator_dev *rdev,
				 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा vctrl_data *vctrl = rdev_get_drvdata(rdev);
	काष्ठा regulator *ctrl_reg = vctrl->ctrl_reg;
	अचिन्हित पूर्णांक orig_sel = vctrl->sel;
	पूर्णांक ret;

	अगर (selector >= rdev->desc->n_voltages)
		वापस -EINVAL;

	अगर (selector >= vctrl->sel || !vctrl->ovp_threshold) अणु
		/* voltage rising or no OVP */
		ret = regulator_set_voltage_rdev(ctrl_reg->rdev,
					    vctrl->vtable[selector].ctrl,
					    vctrl->vtable[selector].ctrl,
					    PM_SUSPEND_ON);
		अगर (!ret)
			vctrl->sel = selector;

		वापस ret;
	पूर्ण

	जबतक (vctrl->sel != selector) अणु
		अचिन्हित पूर्णांक next_sel;
		पूर्णांक delay;

		अगर (selector >= vctrl->vtable[vctrl->sel].ovp_min_sel)
			next_sel = selector;
		अन्यथा
			next_sel = vctrl->vtable[vctrl->sel].ovp_min_sel;

		ret = regulator_set_voltage_rdev(ctrl_reg->rdev,
					    vctrl->vtable[next_sel].ctrl,
					    vctrl->vtable[next_sel].ctrl,
					    PM_SUSPEND_ON);
		अगर (ret) अणु
			dev_err(&rdev->dev,
				"failed to set control voltage to %duV\n",
				vctrl->vtable[next_sel].ctrl);
			जाओ err;
		पूर्ण
		vctrl->sel = next_sel;

		delay = DIV_ROUND_UP(vctrl->vtable[vctrl->sel].out -
				     vctrl->vtable[next_sel].out,
				     vctrl->min_slew_करोwn_rate);
		usleep_range(delay, delay + DIV_ROUND_UP(delay, 10));
	पूर्ण

	वापस 0;

err:
	अगर (vctrl->sel != orig_sel) अणु
		/* Try to go back to original voltage */
		अगर (!regulator_set_voltage_rdev(ctrl_reg->rdev,
					   vctrl->vtable[orig_sel].ctrl,
					   vctrl->vtable[orig_sel].ctrl,
					   PM_SUSPEND_ON))
			vctrl->sel = orig_sel;
		अन्यथा
			dev_warn(&rdev->dev,
				 "failed to restore original voltage\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vctrl_list_voltage(काष्ठा regulator_dev *rdev,
			      अचिन्हित पूर्णांक selector)
अणु
	काष्ठा vctrl_data *vctrl = rdev_get_drvdata(rdev);

	अगर (selector >= rdev->desc->n_voltages)
		वापस -EINVAL;

	वापस vctrl->vtable[selector].out;
पूर्ण

अटल पूर्णांक vctrl_parse_dt(काष्ठा platक्रमm_device *pdev,
			  काष्ठा vctrl_data *vctrl)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 pval;
	u32 vrange_ctrl[2];

	vctrl->ctrl_reg = devm_regulator_get(&pdev->dev, "ctrl");
	अगर (IS_ERR(vctrl->ctrl_reg))
		वापस PTR_ERR(vctrl->ctrl_reg);

	ret = of_property_पढ़ो_u32(np, "ovp-threshold-percent", &pval);
	अगर (!ret) अणु
		vctrl->ovp_threshold = pval;
		अगर (vctrl->ovp_threshold > 100) अणु
			dev_err(&pdev->dev,
				"ovp-threshold-percent (%u) > 100\n",
				vctrl->ovp_threshold);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "min-slew-down-rate", &pval);
	अगर (!ret) अणु
		vctrl->min_slew_करोwn_rate = pval;

		/* We use the value as पूर्णांक and as भागider; sanity check */
		अगर (vctrl->min_slew_करोwn_rate == 0) अणु
			dev_err(&pdev->dev,
				"min-slew-down-rate must not be 0\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (vctrl->min_slew_करोwn_rate > पूर्णांक_उच्च) अणु
			dev_err(&pdev->dev, "min-slew-down-rate (%u) too big\n",
				vctrl->min_slew_करोwn_rate);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (vctrl->ovp_threshold && !vctrl->min_slew_करोwn_rate) अणु
		dev_err(&pdev->dev,
			"ovp-threshold-percent requires min-slew-down-rate\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "regulator-min-microvolt", &pval);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to read regulator-min-microvolt: %d\n", ret);
		वापस ret;
	पूर्ण
	vctrl->vrange.out.min_uV = pval;

	ret = of_property_पढ़ो_u32(np, "regulator-max-microvolt", &pval);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to read regulator-max-microvolt: %d\n", ret);
		वापस ret;
	पूर्ण
	vctrl->vrange.out.max_uV = pval;

	ret = of_property_पढ़ो_u32_array(np, "ctrl-voltage-range", vrange_ctrl,
					 2);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to read ctrl-voltage-range: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (vrange_ctrl[0] >= vrange_ctrl[1]) अणु
		dev_err(&pdev->dev, "ctrl-voltage-range is invalid: %d-%d\n",
			vrange_ctrl[0], vrange_ctrl[1]);
		वापस -EINVAL;
	पूर्ण

	vctrl->vrange.ctrl.min_uV = vrange_ctrl[0];
	vctrl->vrange.ctrl.max_uV = vrange_ctrl[1];

	वापस 0;
पूर्ण

अटल पूर्णांक vctrl_cmp_ctrl_uV(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा vctrl_voltage_table *at = a;
	स्थिर काष्ठा vctrl_voltage_table *bt = b;

	वापस at->ctrl - bt->ctrl;
पूर्ण

अटल पूर्णांक vctrl_init_vtable(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vctrl_data *vctrl = platक्रमm_get_drvdata(pdev);
	काष्ठा regulator_desc *rdesc = &vctrl->desc;
	काष्ठा regulator *ctrl_reg = vctrl->ctrl_reg;
	काष्ठा vctrl_voltage_range *vrange_ctrl = &vctrl->vrange.ctrl;
	पूर्णांक n_voltages;
	पूर्णांक ctrl_uV;
	पूर्णांक i, idx_vt;

	n_voltages = regulator_count_voltages(ctrl_reg);

	rdesc->n_voltages = n_voltages;

	/* determine number of steps within the range of the vctrl regulator */
	क्रम (i = 0; i < n_voltages; i++) अणु
		ctrl_uV = regulator_list_voltage(ctrl_reg, i);

		अगर (ctrl_uV < vrange_ctrl->min_uV ||
		    ctrl_uV > vrange_ctrl->max_uV)
			rdesc->n_voltages--;
	पूर्ण

	अगर (rdesc->n_voltages == 0) अणु
		dev_err(&pdev->dev, "invalid configuration\n");
		वापस -EINVAL;
	पूर्ण

	vctrl->vtable = devm_kसुस्मृति(&pdev->dev, rdesc->n_voltages,
				     माप(काष्ठा vctrl_voltage_table),
				     GFP_KERNEL);
	अगर (!vctrl->vtable)
		वापस -ENOMEM;

	/* create mapping control <=> output voltage */
	क्रम (i = 0, idx_vt = 0; i < n_voltages; i++) अणु
		ctrl_uV = regulator_list_voltage(ctrl_reg, i);

		अगर (ctrl_uV < vrange_ctrl->min_uV ||
		    ctrl_uV > vrange_ctrl->max_uV)
			जारी;

		vctrl->vtable[idx_vt].ctrl = ctrl_uV;
		vctrl->vtable[idx_vt].out =
			vctrl_calc_output_voltage(vctrl, ctrl_uV);
		idx_vt++;
	पूर्ण

	/* we rely on the table to be ordered by ascending voltage */
	sort(vctrl->vtable, rdesc->n_voltages,
	     माप(काष्ठा vctrl_voltage_table), vctrl_cmp_ctrl_uV,
	     शून्य);

	/* pre-calculate OVP-safe करोwnward transitions */
	क्रम (i = rdesc->n_voltages - 1; i > 0; i--) अणु
		पूर्णांक j;
		पूर्णांक ovp_min_uV = (vctrl->vtable[i].out *
				  (100 - vctrl->ovp_threshold)) / 100;

		क्रम (j = 0; j < i; j++) अणु
			अगर (vctrl->vtable[j].out >= ovp_min_uV) अणु
				vctrl->vtable[i].ovp_min_sel = j;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (j == i) अणु
			dev_warn(&pdev->dev, "switching down from %duV may cause OVP shutdown\n",
				vctrl->vtable[i].out);
			/* use next lowest voltage */
			vctrl->vtable[i].ovp_min_sel = i - 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vctrl_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा vctrl_data *vctrl = rdev_get_drvdata(rdev);
	पूर्णांक ret = regulator_enable(vctrl->ctrl_reg);

	अगर (!ret)
		vctrl->enabled = true;

	वापस ret;
पूर्ण

अटल पूर्णांक vctrl_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा vctrl_data *vctrl = rdev_get_drvdata(rdev);
	पूर्णांक ret = regulator_disable(vctrl->ctrl_reg);

	अगर (!ret)
		vctrl->enabled = false;

	वापस ret;
पूर्ण

अटल पूर्णांक vctrl_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा vctrl_data *vctrl = rdev_get_drvdata(rdev);

	वापस vctrl->enabled;
पूर्ण

अटल स्थिर काष्ठा regulator_ops vctrl_ops_cont = अणु
	.enable		  = vctrl_enable,
	.disable	  = vctrl_disable,
	.is_enabled	  = vctrl_is_enabled,
	.get_voltage	  = vctrl_get_voltage,
	.set_voltage	  = vctrl_set_voltage,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops vctrl_ops_non_cont = अणु
	.enable		  = vctrl_enable,
	.disable	  = vctrl_disable,
	.is_enabled	  = vctrl_is_enabled,
	.set_voltage_sel = vctrl_set_voltage_sel,
	.get_voltage_sel = vctrl_get_voltage_sel,
	.list_voltage    = vctrl_list_voltage,
	.map_voltage     = regulator_map_voltage_iterate,
पूर्ण;

अटल पूर्णांक vctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा vctrl_data *vctrl;
	स्थिर काष्ठा regulator_init_data *init_data;
	काष्ठा regulator_desc *rdesc;
	काष्ठा regulator_config cfg = अणु पूर्ण;
	काष्ठा vctrl_voltage_range *vrange_ctrl;
	पूर्णांक ctrl_uV;
	पूर्णांक ret;

	vctrl = devm_kzalloc(&pdev->dev, माप(काष्ठा vctrl_data),
			     GFP_KERNEL);
	अगर (!vctrl)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, vctrl);

	ret = vctrl_parse_dt(pdev, vctrl);
	अगर (ret)
		वापस ret;

	vrange_ctrl = &vctrl->vrange.ctrl;

	rdesc = &vctrl->desc;
	rdesc->name = "vctrl";
	rdesc->type = REGULATOR_VOLTAGE;
	rdesc->owner = THIS_MODULE;

	अगर ((regulator_get_linear_step(vctrl->ctrl_reg) == 1) ||
	    (regulator_count_voltages(vctrl->ctrl_reg) == -EINVAL)) अणु
		rdesc->continuous_voltage_range = true;
		rdesc->ops = &vctrl_ops_cont;
	पूर्ण अन्यथा अणु
		rdesc->ops = &vctrl_ops_non_cont;
	पूर्ण

	init_data = of_get_regulator_init_data(&pdev->dev, np, rdesc);
	अगर (!init_data)
		वापस -ENOMEM;

	cfg.of_node = np;
	cfg.dev = &pdev->dev;
	cfg.driver_data = vctrl;
	cfg.init_data = init_data;

	अगर (!rdesc->continuous_voltage_range) अणु
		ret = vctrl_init_vtable(pdev);
		अगर (ret)
			वापस ret;

		ctrl_uV = regulator_get_voltage_rdev(vctrl->ctrl_reg->rdev);
		अगर (ctrl_uV < 0) अणु
			dev_err(&pdev->dev, "failed to get control voltage\n");
			वापस ctrl_uV;
		पूर्ण

		/* determine current voltage selector from control voltage */
		अगर (ctrl_uV < vrange_ctrl->min_uV) अणु
			vctrl->sel = 0;
		पूर्ण अन्यथा अगर (ctrl_uV > vrange_ctrl->max_uV) अणु
			vctrl->sel = rdesc->n_voltages - 1;
		पूर्ण अन्यथा अणु
			पूर्णांक i;

			क्रम (i = 0; i < rdesc->n_voltages; i++) अणु
				अगर (ctrl_uV == vctrl->vtable[i].ctrl) अणु
					vctrl->sel = i;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	vctrl->rdev = devm_regulator_रेजिस्टर(&pdev->dev, rdesc, &cfg);
	अगर (IS_ERR(vctrl->rdev)) अणु
		ret = PTR_ERR(vctrl->rdev);
		dev_err(&pdev->dev, "failed to register regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vctrl_of_match[] = अणु
	अणु .compatible = "vctrl-regulator", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vctrl_of_match);

अटल काष्ठा platक्रमm_driver vctrl_driver = अणु
	.probe		= vctrl_probe,
	.driver		= अणु
		.name		= "vctrl-regulator",
		.of_match_table = of_match_ptr(vctrl_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vctrl_driver);

MODULE_DESCRIPTION("Voltage Controlled Regulator Driver");
MODULE_AUTHOR("Matthias Kaehlcke <mka@chromium.org>");
MODULE_LICENSE("GPL v2");
