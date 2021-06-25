<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// System Control and Management Interface (SCMI) based regulator driver
//
// Copyright (C) 2020-2021 ARM Ltd.
//
// Implements a regulator driver on top of the SCMI Voltage Protocol.
//
// The ARM SCMI Protocol aims in general to hide as much as possible all the
// underlying operational details जबतक providing an असलtracted पूर्णांकerface क्रम
// its users to operate upon: as a consequence the resulting operational
// capabilities and configurability of this regulator device are much more
// limited than the ones usually available on a standard physical regulator.
//
// The supported SCMI regulator ops are restricted to the bare minimum:
//
//  - 'status_ops': enable/disable/is_enabled
//  - 'voltage_ops': get_voltage_sel/set_voltage_sel
//		     list_voltage/map_voltage
//
// Each SCMI regulator instance is associated, through the means of a proper DT
// entry description, to a specअगरic SCMI Voltage Doमुख्य.

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/linear_range.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/scmi_protocol.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

अटल स्थिर काष्ठा scmi_voltage_proto_ops *voltage_ops;

काष्ठा scmi_regulator अणु
	u32 id;
	काष्ठा scmi_device *sdev;
	काष्ठा scmi_protocol_handle *ph;
	काष्ठा regulator_dev *rdev;
	काष्ठा device_node *of_node;
	काष्ठा regulator_desc desc;
	काष्ठा regulator_config conf;
पूर्ण;

काष्ठा scmi_regulator_info अणु
	पूर्णांक num_करोms;
	काष्ठा scmi_regulator **sregv;
पूर्ण;

अटल पूर्णांक scmi_reg_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा scmi_regulator *sreg = rdev_get_drvdata(rdev);

	वापस voltage_ops->config_set(sreg->ph, sreg->id,
				       SCMI_VOLTAGE_ARCH_STATE_ON);
पूर्ण

अटल पूर्णांक scmi_reg_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा scmi_regulator *sreg = rdev_get_drvdata(rdev);

	वापस voltage_ops->config_set(sreg->ph, sreg->id,
				       SCMI_VOLTAGE_ARCH_STATE_OFF);
पूर्ण

अटल पूर्णांक scmi_reg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	u32 config;
	काष्ठा scmi_regulator *sreg = rdev_get_drvdata(rdev);

	ret = voltage_ops->config_get(sreg->ph, sreg->id, &config);
	अगर (ret) अणु
		dev_err(&sreg->sdev->dev,
			"Error %d reading regulator %s status.\n",
			ret, sreg->desc.name);
		वापस ret;
	पूर्ण

	वापस config & SCMI_VOLTAGE_ARCH_STATE_ON;
पूर्ण

अटल पूर्णांक scmi_reg_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	s32 volt_uV;
	काष्ठा scmi_regulator *sreg = rdev_get_drvdata(rdev);

	ret = voltage_ops->level_get(sreg->ph, sreg->id, &volt_uV);
	अगर (ret)
		वापस ret;

	वापस sreg->desc.ops->map_voltage(rdev, volt_uV, volt_uV);
पूर्ण

अटल पूर्णांक scmi_reg_set_voltage_sel(काष्ठा regulator_dev *rdev,
				    अचिन्हित पूर्णांक selector)
अणु
	s32 volt_uV;
	काष्ठा scmi_regulator *sreg = rdev_get_drvdata(rdev);

	volt_uV = sreg->desc.ops->list_voltage(rdev, selector);
	अगर (volt_uV <= 0)
		वापस -EINVAL;

	वापस voltage_ops->level_set(sreg->ph, sreg->id, 0x0, volt_uV);
पूर्ण

अटल स्थिर काष्ठा regulator_ops scmi_reg_fixed_ops = अणु
	.enable = scmi_reg_enable,
	.disable = scmi_reg_disable,
	.is_enabled = scmi_reg_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops scmi_reg_linear_ops = अणु
	.enable = scmi_reg_enable,
	.disable = scmi_reg_disable,
	.is_enabled = scmi_reg_is_enabled,
	.get_voltage_sel = scmi_reg_get_voltage_sel,
	.set_voltage_sel = scmi_reg_set_voltage_sel,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops scmi_reg_discrete_ops = अणु
	.enable = scmi_reg_enable,
	.disable = scmi_reg_disable,
	.is_enabled = scmi_reg_is_enabled,
	.get_voltage_sel = scmi_reg_get_voltage_sel,
	.set_voltage_sel = scmi_reg_set_voltage_sel,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_iterate,
पूर्ण;

अटल पूर्णांक
scmi_config_linear_regulator_mappings(काष्ठा scmi_regulator *sreg,
				      स्थिर काष्ठा scmi_voltage_info *vinfo)
अणु
	s32 delta_uV;

	/*
	 * Note that SCMI voltage करोमुख्यs describable by linear ranges
	 * (segments) अणुlow, high, stepपूर्ण are guaranteed to come in one single
	 * triplet by the SCMI Voltage Doमुख्य protocol support itself.
	 */

	delta_uV = (vinfo->levels_uv[SCMI_VOLTAGE_SEGMENT_HIGH] -
			vinfo->levels_uv[SCMI_VOLTAGE_SEGMENT_LOW]);

	/* Rule out buggy negative-पूर्णांकervals answers from fw */
	अगर (delta_uV < 0) अणु
		dev_err(&sreg->sdev->dev,
			"Invalid volt-range %d-%duV for domain %d\n",
			vinfo->levels_uv[SCMI_VOLTAGE_SEGMENT_LOW],
			vinfo->levels_uv[SCMI_VOLTAGE_SEGMENT_HIGH],
			sreg->id);
		वापस -EINVAL;
	पूर्ण

	अगर (!delta_uV) अणु
		/* Just one fixed voltage exposed by SCMI */
		sreg->desc.fixed_uV =
			vinfo->levels_uv[SCMI_VOLTAGE_SEGMENT_LOW];
		sreg->desc.n_voltages = 1;
		sreg->desc.ops = &scmi_reg_fixed_ops;
	पूर्ण अन्यथा अणु
		/* One simple linear mapping. */
		sreg->desc.min_uV =
			vinfo->levels_uv[SCMI_VOLTAGE_SEGMENT_LOW];
		sreg->desc.uV_step =
			vinfo->levels_uv[SCMI_VOLTAGE_SEGMENT_STEP];
		sreg->desc.linear_min_sel = 0;
		sreg->desc.n_voltages = (delta_uV / sreg->desc.uV_step) + 1;
		sreg->desc.ops = &scmi_reg_linear_ops;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
scmi_config_discrete_regulator_mappings(काष्ठा scmi_regulator *sreg,
					स्थिर काष्ठा scmi_voltage_info *vinfo)
अणु
	/* Discrete non linear levels are mapped to volt_table */
	sreg->desc.n_voltages = vinfo->num_levels;

	अगर (sreg->desc.n_voltages > 1) अणु
		sreg->desc.volt_table = (स्थिर अचिन्हित पूर्णांक *)vinfo->levels_uv;
		sreg->desc.ops = &scmi_reg_discrete_ops;
	पूर्ण अन्यथा अणु
		sreg->desc.fixed_uV = vinfo->levels_uv[0];
		sreg->desc.ops = &scmi_reg_fixed_ops;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक scmi_regulator_common_init(काष्ठा scmi_regulator *sreg)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &sreg->sdev->dev;
	स्थिर काष्ठा scmi_voltage_info *vinfo;

	vinfo = voltage_ops->info_get(sreg->ph, sreg->id);
	अगर (!vinfo) अणु
		dev_warn(dev, "Failure to get voltage domain %d\n",
			 sreg->id);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Regulator framework करोes not fully support negative voltages
	 * so we discard any voltage करोमुख्य reported as supporting negative
	 * voltages: as a consequence each levels_uv entry is guaranteed to
	 * be non-negative from here on.
	 */
	अगर (vinfo->negative_volts_allowed) अणु
		dev_warn(dev, "Negative voltages NOT supported...skip %s\n",
			 sreg->of_node->full_name);
		वापस -EOPNOTSUPP;
	पूर्ण

	sreg->desc.name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s", vinfo->name);
	अगर (!sreg->desc.name)
		वापस -ENOMEM;

	sreg->desc.id = sreg->id;
	sreg->desc.type = REGULATOR_VOLTAGE;
	sreg->desc.owner = THIS_MODULE;
	sreg->desc.of_match_full_name = true;
	sreg->desc.of_match = sreg->of_node->full_name;
	sreg->desc.regulators_node = "regulators";
	अगर (vinfo->segmented)
		ret = scmi_config_linear_regulator_mappings(sreg, vinfo);
	अन्यथा
		ret = scmi_config_discrete_regulator_mappings(sreg, vinfo);
	अगर (ret)
		वापस ret;

	/*
	 * Using the scmi device here to have DT searched from Voltage
	 * protocol node करोwn.
	 */
	sreg->conf.dev = dev;

	/* Store क्रम later retrieval via rdev_get_drvdata() */
	sreg->conf.driver_data = sreg;

	वापस 0;
पूर्ण

अटल पूर्णांक process_scmi_regulator_of_node(काष्ठा scmi_device *sdev,
					  काष्ठा scmi_protocol_handle *ph,
					  काष्ठा device_node *np,
					  काष्ठा scmi_regulator_info *rinfo)
अणु
	u32 करोm, ret;

	ret = of_property_पढ़ो_u32(np, "reg", &करोm);
	अगर (ret)
		वापस ret;

	अगर (करोm >= rinfo->num_करोms)
		वापस -ENODEV;

	अगर (rinfo->sregv[करोm]) अणु
		dev_err(&sdev->dev,
			"SCMI Voltage Domain %d already in use. Skipping: %s\n",
			करोm, np->full_name);
		वापस -EINVAL;
	पूर्ण

	rinfo->sregv[करोm] = devm_kzalloc(&sdev->dev,
					 माप(काष्ठा scmi_regulator),
					 GFP_KERNEL);
	अगर (!rinfo->sregv[करोm])
		वापस -ENOMEM;

	rinfo->sregv[करोm]->id = करोm;
	rinfo->sregv[करोm]->sdev = sdev;
	rinfo->sregv[करोm]->ph = ph;

	/* get hold of good nodes */
	of_node_get(np);
	rinfo->sregv[करोm]->of_node = np;

	dev_dbg(&sdev->dev,
		"Found SCMI Regulator entry -- OF node [%d] -> %s\n",
		करोm, np->full_name);

	वापस 0;
पूर्ण

अटल पूर्णांक scmi_regulator_probe(काष्ठा scmi_device *sdev)
अणु
	पूर्णांक d, ret, num_करोms;
	काष्ठा device_node *np, *child;
	स्थिर काष्ठा scmi_handle *handle = sdev->handle;
	काष्ठा scmi_regulator_info *rinfo;
	काष्ठा scmi_protocol_handle *ph;

	अगर (!handle)
		वापस -ENODEV;

	voltage_ops = handle->devm_protocol_get(sdev,
						SCMI_PROTOCOL_VOLTAGE, &ph);
	अगर (IS_ERR(voltage_ops))
		वापस PTR_ERR(voltage_ops);

	num_करोms = voltage_ops->num_करोमुख्यs_get(ph);
	अगर (num_करोms <= 0) अणु
		अगर (!num_करोms) अणु
			dev_err(&sdev->dev,
				"number of voltage domains invalid\n");
			num_करोms = -EINVAL;
		पूर्ण अन्यथा अणु
			dev_err(&sdev->dev,
				"failed to get voltage domains - err:%d\n",
				num_करोms);
		पूर्ण

		वापस num_करोms;
	पूर्ण

	rinfo = devm_kzalloc(&sdev->dev, माप(*rinfo), GFP_KERNEL);
	अगर (!rinfo)
		वापस -ENOMEM;

	/* Allocate poपूर्णांकers array क्रम all possible करोमुख्यs */
	rinfo->sregv = devm_kसुस्मृति(&sdev->dev, num_करोms,
				    माप(व्योम *), GFP_KERNEL);
	अगर (!rinfo->sregv)
		वापस -ENOMEM;

	rinfo->num_करोms = num_करोms;

	/*
	 * Start collecting पूर्णांकo rinfo->sregv possibly good SCMI Regulators as
	 * described by a well-क्रमmed DT entry and associated with an existing
	 * plausible SCMI Voltage Doमुख्य number, all beदीर्घing to this SCMI
	 * platक्रमm instance node (handle->dev->of_node).
	 */
	np = of_find_node_by_name(handle->dev->of_node, "regulators");
	क्रम_each_child_of_node(np, child) अणु
		ret = process_scmi_regulator_of_node(sdev, ph, child, rinfo);
		/* पात on any mem issue */
		अगर (ret == -ENOMEM) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Register a regulator क्रम each valid regulator-DT-entry that we
	 * can successfully reach via SCMI and has a valid associated voltage
	 * करोमुख्य.
	 */
	क्रम (d = 0; d < num_करोms; d++) अणु
		काष्ठा scmi_regulator *sreg = rinfo->sregv[d];

		/* Skip empty slots */
		अगर (!sreg)
			जारी;

		ret = scmi_regulator_common_init(sreg);
		/* Skip invalid voltage करोमुख्यs */
		अगर (ret)
			जारी;

		sreg->rdev = devm_regulator_रेजिस्टर(&sdev->dev, &sreg->desc,
						     &sreg->conf);
		अगर (IS_ERR(sreg->rdev)) अणु
			sreg->rdev = शून्य;
			जारी;
		पूर्ण

		dev_info(&sdev->dev,
			 "Regulator %s registered for domain [%d]\n",
			 sreg->desc.name, sreg->id);
	पूर्ण

	dev_set_drvdata(&sdev->dev, rinfo);

	वापस 0;
पूर्ण

अटल व्योम scmi_regulator_हटाओ(काष्ठा scmi_device *sdev)
अणु
	पूर्णांक d;
	काष्ठा scmi_regulator_info *rinfo;

	rinfo = dev_get_drvdata(&sdev->dev);
	अगर (!rinfo)
		वापस;

	क्रम (d = 0; d < rinfo->num_करोms; d++) अणु
		अगर (!rinfo->sregv[d])
			जारी;
		of_node_put(rinfo->sregv[d]->of_node);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा scmi_device_id scmi_regulator_id_table[] = अणु
	अणु SCMI_PROTOCOL_VOLTAGE,  "regulator" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(scmi, scmi_regulator_id_table);

अटल काष्ठा scmi_driver scmi_drv = अणु
	.name		= "scmi-regulator",
	.probe		= scmi_regulator_probe,
	.हटाओ		= scmi_regulator_हटाओ,
	.id_table	= scmi_regulator_id_table,
पूर्ण;

module_scmi_driver(scmi_drv);

MODULE_AUTHOR("Cristian Marussi <cristian.marussi@arm.com>");
MODULE_DESCRIPTION("ARM SCMI regulator driver");
MODULE_LICENSE("GPL v2");
