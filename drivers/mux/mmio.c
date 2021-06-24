<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MMIO रेजिस्टर bitfield-controlled multiplexer driver
 *
 * Copyright (C) 2017 Pengutronix, Philipp Zabel <kernel@pengutronix.de>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mux/driver.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>

अटल पूर्णांक mux_mmio_set(काष्ठा mux_control *mux, पूर्णांक state)
अणु
	काष्ठा regmap_field **fields = mux_chip_priv(mux->chip);

	वापस regmap_field_ग_लिखो(fields[mux_control_get_index(mux)], state);
पूर्ण

अटल स्थिर काष्ठा mux_control_ops mux_mmio_ops = अणु
	.set = mux_mmio_set,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mux_mmio_dt_ids[] = अणु
	अणु .compatible = "mmio-mux", पूर्ण,
	अणु .compatible = "reg-mux", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mux_mmio_dt_ids);

अटल पूर्णांक mux_mmio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap_field **fields;
	काष्ठा mux_chip *mux_chip;
	काष्ठा regmap *regmap;
	पूर्णांक num_fields;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (of_device_is_compatible(np, "mmio-mux"))
		regmap = syscon_node_to_regmap(np->parent);
	अन्यथा
		regmap = dev_get_regmap(dev->parent, शून्य) ?: ERR_PTR(-ENODEV);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(dev, "failed to get regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_count_u32_elems(np, "mux-reg-masks");
	अगर (ret == 0 || ret % 2)
		ret = -EINVAL;
	अगर (ret < 0) अणु
		dev_err(dev, "mux-reg-masks property missing or invalid: %d\n",
			ret);
		वापस ret;
	पूर्ण
	num_fields = ret / 2;

	mux_chip = devm_mux_chip_alloc(dev, num_fields, num_fields *
				       माप(*fields));
	अगर (IS_ERR(mux_chip))
		वापस PTR_ERR(mux_chip);

	fields = mux_chip_priv(mux_chip);

	क्रम (i = 0; i < num_fields; i++) अणु
		काष्ठा mux_control *mux = &mux_chip->mux[i];
		काष्ठा reg_field field;
		s32 idle_state = MUX_IDLE_AS_IS;
		u32 reg, mask;
		पूर्णांक bits;

		ret = of_property_पढ़ो_u32_index(np, "mux-reg-masks",
						 2 * i, &reg);
		अगर (!ret)
			ret = of_property_पढ़ो_u32_index(np, "mux-reg-masks",
							 2 * i + 1, &mask);
		अगर (ret < 0) अणु
			dev_err(dev, "bitfield %d: failed to read mux-reg-masks property: %d\n",
				i, ret);
			वापस ret;
		पूर्ण

		field.reg = reg;
		field.msb = fls(mask) - 1;
		field.lsb = ffs(mask) - 1;

		अगर (mask != GENMASK(field.msb, field.lsb)) अणु
			dev_err(dev, "bitfield %d: invalid mask 0x%x\n",
				i, mask);
			वापस -EINVAL;
		पूर्ण

		fields[i] = devm_regmap_field_alloc(dev, regmap, field);
		अगर (IS_ERR(fields[i])) अणु
			ret = PTR_ERR(fields[i]);
			dev_err(dev, "bitfield %d: failed allocate: %d\n",
				i, ret);
			वापस ret;
		पूर्ण

		bits = 1 + field.msb - field.lsb;
		mux->states = 1 << bits;

		of_property_पढ़ो_u32_index(np, "idle-states", i,
					   (u32 *)&idle_state);
		अगर (idle_state != MUX_IDLE_AS_IS) अणु
			अगर (idle_state < 0 || idle_state >= mux->states) अणु
				dev_err(dev, "bitfield: %d: out of range idle state %d\n",
					i, idle_state);
				वापस -EINVAL;
			पूर्ण

			mux->idle_state = idle_state;
		पूर्ण
	पूर्ण

	mux_chip->ops = &mux_mmio_ops;

	वापस devm_mux_chip_रेजिस्टर(dev, mux_chip);
पूर्ण

अटल काष्ठा platक्रमm_driver mux_mmio_driver = अणु
	.driver = अणु
		.name = "mmio-mux",
		.of_match_table	= of_match_ptr(mux_mmio_dt_ids),
	पूर्ण,
	.probe = mux_mmio_probe,
पूर्ण;
module_platक्रमm_driver(mux_mmio_driver);

MODULE_DESCRIPTION("MMIO register bitfield-controlled multiplexer driver");
MODULE_AUTHOR("Philipp Zabel <p.zabel@pengutronix.de>");
MODULE_LICENSE("GPL v2");
