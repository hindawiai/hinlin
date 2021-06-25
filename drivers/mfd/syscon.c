<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * System Control Driver
 *
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * Copyright (C) 2012 Linaro Ltd.
 *
 * Author: Dong Aisheng <करोng.aisheng@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/hwspinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_data/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/slab.h>

अटल काष्ठा platक्रमm_driver syscon_driver;

अटल DEFINE_SPINLOCK(syscon_list_slock);
अटल LIST_HEAD(syscon_list);

काष्ठा syscon अणु
	काष्ठा device_node *np;
	काष्ठा regmap *regmap;
	काष्ठा list_head list;
पूर्ण;

अटल स्थिर काष्ठा regmap_config syscon_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल काष्ठा syscon *of_syscon_रेजिस्टर(काष्ठा device_node *np, bool check_clk)
अणु
	काष्ठा clk *clk;
	काष्ठा syscon *syscon;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	u32 reg_io_width;
	पूर्णांक ret;
	काष्ठा regmap_config syscon_config = syscon_regmap_config;
	काष्ठा resource res;

	syscon = kzalloc(माप(*syscon), GFP_KERNEL);
	अगर (!syscon)
		वापस ERR_PTR(-ENOMEM);

	अगर (of_address_to_resource(np, 0, &res)) अणु
		ret = -ENOMEM;
		जाओ err_map;
	पूर्ण

	base = ioremap(res.start, resource_size(&res));
	अगर (!base) अणु
		ret = -ENOMEM;
		जाओ err_map;
	पूर्ण

	/* Parse the device's DT node क्रम an endianness specअगरication */
	अगर (of_property_पढ़ो_bool(np, "big-endian"))
		syscon_config.val_क्रमmat_endian = REGMAP_ENDIAN_BIG;
	अन्यथा अगर (of_property_पढ़ो_bool(np, "little-endian"))
		syscon_config.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE;
	अन्यथा अगर (of_property_पढ़ो_bool(np, "native-endian"))
		syscon_config.val_क्रमmat_endian = REGMAP_ENDIAN_NATIVE;

	/*
	 * search क्रम reg-io-width property in DT. If it is not provided,
	 * शेष to 4 bytes. regmap_init_mmio will वापस an error अगर values
	 * are invalid so there is no need to check them here.
	 */
	ret = of_property_पढ़ो_u32(np, "reg-io-width", &reg_io_width);
	अगर (ret)
		reg_io_width = 4;

	ret = of_hwspin_lock_get_id(np, 0);
	अगर (ret > 0 || (IS_ENABLED(CONFIG_HWSPINLOCK) && ret == 0)) अणु
		syscon_config.use_hwlock = true;
		syscon_config.hwlock_id = ret;
		syscon_config.hwlock_mode = HWLOCK_IRQSTATE;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		चयन (ret) अणु
		हाल -ENOENT:
			/* Ignore missing hwlock, it's optional. */
			अवरोध;
		शेष:
			pr_err("Failed to retrieve valid hwlock: %d\n", ret);
			fallthrough;
		हाल -EPROBE_DEFER:
			जाओ err_regmap;
		पूर्ण
	पूर्ण

	syscon_config.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn@%llx", np,
				       (u64)res.start);
	syscon_config.reg_stride = reg_io_width;
	syscon_config.val_bits = reg_io_width * 8;
	syscon_config.max_रेजिस्टर = resource_size(&res) - reg_io_width;

	regmap = regmap_init_mmio(शून्य, base, &syscon_config);
	अगर (IS_ERR(regmap)) अणु
		pr_err("regmap init failed\n");
		ret = PTR_ERR(regmap);
		जाओ err_regmap;
	पूर्ण

	अगर (check_clk) अणु
		clk = of_clk_get(np, 0);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			/* घड़ी is optional */
			अगर (ret != -ENOENT)
				जाओ err_clk;
		पूर्ण अन्यथा अणु
			ret = regmap_mmio_attach_clk(regmap, clk);
			अगर (ret)
				जाओ err_attach;
		पूर्ण
	पूर्ण

	syscon->regmap = regmap;
	syscon->np = np;

	spin_lock(&syscon_list_slock);
	list_add_tail(&syscon->list, &syscon_list);
	spin_unlock(&syscon_list_slock);

	वापस syscon;

err_attach:
	अगर (!IS_ERR(clk))
		clk_put(clk);
err_clk:
	regmap_निकास(regmap);
err_regmap:
	iounmap(base);
	kमुक्त(syscon_config.name);
err_map:
	kमुक्त(syscon);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा regmap *device_node_get_regmap(काष्ठा device_node *np,
					     bool check_clk)
अणु
	काष्ठा syscon *entry, *syscon = शून्य;

	spin_lock(&syscon_list_slock);

	list_क्रम_each_entry(entry, &syscon_list, list)
		अगर (entry->np == np) अणु
			syscon = entry;
			अवरोध;
		पूर्ण

	spin_unlock(&syscon_list_slock);

	अगर (!syscon)
		syscon = of_syscon_रेजिस्टर(np, check_clk);

	अगर (IS_ERR(syscon))
		वापस ERR_CAST(syscon);

	वापस syscon->regmap;
पूर्ण

काष्ठा regmap *device_node_to_regmap(काष्ठा device_node *np)
अणु
	वापस device_node_get_regmap(np, false);
पूर्ण
EXPORT_SYMBOL_GPL(device_node_to_regmap);

काष्ठा regmap *syscon_node_to_regmap(काष्ठा device_node *np)
अणु
	अगर (!of_device_is_compatible(np, "syscon"))
		वापस ERR_PTR(-EINVAL);

	वापस device_node_get_regmap(np, true);
पूर्ण
EXPORT_SYMBOL_GPL(syscon_node_to_regmap);

काष्ठा regmap *syscon_regmap_lookup_by_compatible(स्थिर अक्षर *s)
अणु
	काष्ठा device_node *syscon_np;
	काष्ठा regmap *regmap;

	syscon_np = of_find_compatible_node(शून्य, शून्य, s);
	अगर (!syscon_np)
		वापस ERR_PTR(-ENODEV);

	regmap = syscon_node_to_regmap(syscon_np);
	of_node_put(syscon_np);

	वापस regmap;
पूर्ण
EXPORT_SYMBOL_GPL(syscon_regmap_lookup_by_compatible);

काष्ठा regmap *syscon_regmap_lookup_by_phandle(काष्ठा device_node *np,
					स्थिर अक्षर *property)
अणु
	काष्ठा device_node *syscon_np;
	काष्ठा regmap *regmap;

	अगर (property)
		syscon_np = of_parse_phandle(np, property, 0);
	अन्यथा
		syscon_np = np;

	अगर (!syscon_np)
		वापस ERR_PTR(-ENODEV);

	regmap = syscon_node_to_regmap(syscon_np);
	of_node_put(syscon_np);

	वापस regmap;
पूर्ण
EXPORT_SYMBOL_GPL(syscon_regmap_lookup_by_phandle);

काष्ठा regmap *syscon_regmap_lookup_by_phandle_args(काष्ठा device_node *np,
					स्थिर अक्षर *property,
					पूर्णांक arg_count,
					अचिन्हित पूर्णांक *out_args)
अणु
	काष्ठा device_node *syscon_np;
	काष्ठा of_phandle_args args;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक index;
	पूर्णांक rc;

	rc = of_parse_phandle_with_fixed_args(np, property, arg_count,
			0, &args);
	अगर (rc)
		वापस ERR_PTR(rc);

	syscon_np = args.np;
	अगर (!syscon_np)
		वापस ERR_PTR(-ENODEV);

	regmap = syscon_node_to_regmap(syscon_np);
	क्रम (index = 0; index < arg_count; index++)
		out_args[index] = args.args[index];
	of_node_put(syscon_np);

	वापस regmap;
पूर्ण
EXPORT_SYMBOL_GPL(syscon_regmap_lookup_by_phandle_args);

/*
 * It behaves the same as syscon_regmap_lookup_by_phandle() except where
 * there is no regmap phandle. In this हाल, instead of वापसing -ENODEV,
 * the function वापसs शून्य.
 */
काष्ठा regmap *syscon_regmap_lookup_by_phandle_optional(काष्ठा device_node *np,
					स्थिर अक्षर *property)
अणु
	काष्ठा regmap *regmap;

	regmap = syscon_regmap_lookup_by_phandle(np, property);
	अगर (IS_ERR(regmap) && PTR_ERR(regmap) == -ENODEV)
		वापस शून्य;

	वापस regmap;
पूर्ण
EXPORT_SYMBOL_GPL(syscon_regmap_lookup_by_phandle_optional);

अटल पूर्णांक syscon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा syscon_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा syscon *syscon;
	काष्ठा regmap_config syscon_config = syscon_regmap_config;
	काष्ठा resource *res;
	व्योम __iomem *base;

	syscon = devm_kzalloc(dev, माप(*syscon), GFP_KERNEL);
	अगर (!syscon)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOENT;

	base = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!base)
		वापस -ENOMEM;

	syscon_config.max_रेजिस्टर = resource_size(res) - 4;
	अगर (pdata)
		syscon_config.name = pdata->label;
	syscon->regmap = devm_regmap_init_mmio(dev, base, &syscon_config);
	अगर (IS_ERR(syscon->regmap)) अणु
		dev_err(dev, "regmap init failed\n");
		वापस PTR_ERR(syscon->regmap);
	पूर्ण

	platक्रमm_set_drvdata(pdev, syscon);

	dev_dbg(dev, "regmap %pR registered\n", res);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id syscon_ids[] = अणु
	अणु "syscon", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver syscon_driver = अणु
	.driver = अणु
		.name = "syscon",
	पूर्ण,
	.probe		= syscon_probe,
	.id_table	= syscon_ids,
पूर्ण;

अटल पूर्णांक __init syscon_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&syscon_driver);
पूर्ण
postcore_initcall(syscon_init);
