<शैली गुरु>
/*
 * EIM driver क्रम Freescale's i.MX chips
 *
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <linux/regmap.h>

काष्ठा imx_weim_devtype अणु
	अचिन्हित पूर्णांक	cs_count;
	अचिन्हित पूर्णांक	cs_regs_count;
	अचिन्हित पूर्णांक	cs_stride;
	अचिन्हित पूर्णांक	wcr_offset;
	अचिन्हित पूर्णांक	wcr_bcm;
पूर्ण;

अटल स्थिर काष्ठा imx_weim_devtype imx1_weim_devtype = अणु
	.cs_count	= 6,
	.cs_regs_count	= 2,
	.cs_stride	= 0x08,
पूर्ण;

अटल स्थिर काष्ठा imx_weim_devtype imx27_weim_devtype = अणु
	.cs_count	= 6,
	.cs_regs_count	= 3,
	.cs_stride	= 0x10,
पूर्ण;

अटल स्थिर काष्ठा imx_weim_devtype imx50_weim_devtype = अणु
	.cs_count	= 4,
	.cs_regs_count	= 6,
	.cs_stride	= 0x18,
	.wcr_offset	= 0x90,
	.wcr_bcm	= BIT(0),
पूर्ण;

अटल स्थिर काष्ठा imx_weim_devtype imx51_weim_devtype = अणु
	.cs_count	= 6,
	.cs_regs_count	= 6,
	.cs_stride	= 0x18,
पूर्ण;

#घोषणा MAX_CS_REGS_COUNT	6
#घोषणा MAX_CS_COUNT		6
#घोषणा OF_REG_SIZE		3

काष्ठा cs_timing अणु
	bool is_applied;
	u32 regs[MAX_CS_REGS_COUNT];
पूर्ण;

काष्ठा cs_timing_state अणु
	काष्ठा cs_timing cs[MAX_CS_COUNT];
पूर्ण;

अटल स्थिर काष्ठा of_device_id weim_id_table[] = अणु
	/* i.MX1/21 */
	अणु .compatible = "fsl,imx1-weim", .data = &imx1_weim_devtype, पूर्ण,
	/* i.MX25/27/31/35 */
	अणु .compatible = "fsl,imx27-weim", .data = &imx27_weim_devtype, पूर्ण,
	/* i.MX50/53/6Q */
	अणु .compatible = "fsl,imx50-weim", .data = &imx50_weim_devtype, पूर्ण,
	अणु .compatible = "fsl,imx6q-weim", .data = &imx50_weim_devtype, पूर्ण,
	/* i.MX51 */
	अणु .compatible = "fsl,imx51-weim", .data = &imx51_weim_devtype, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, weim_id_table);

अटल पूर्णांक imx_weim_gpr_setup(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा property *prop;
	स्थिर __be32 *p;
	काष्ठा regmap *gpr;
	u32 gprvals[4] = अणु
		05,	/* CS0(128M) CS1(0M)  CS2(0M)  CS3(0M)  */
		033,	/* CS0(64M)  CS1(64M) CS2(0M)  CS3(0M)  */
		0113,	/* CS0(64M)  CS1(32M) CS2(32M) CS3(0M)  */
		01111,	/* CS0(32M)  CS1(32M) CS2(32M) CS3(32M) */
	पूर्ण;
	u32 gprval = 0;
	u32 val;
	पूर्णांक cs = 0;
	पूर्णांक i = 0;

	gpr = syscon_regmap_lookup_by_phandle(np, "fsl,weim-cs-gpr");
	अगर (IS_ERR(gpr)) अणु
		dev_dbg(&pdev->dev, "failed to find weim-cs-gpr\n");
		वापस 0;
	पूर्ण

	of_property_क्रम_each_u32(np, "ranges", prop, p, val) अणु
		अगर (i % 4 == 0) अणु
			cs = val;
		पूर्ण अन्यथा अगर (i % 4 == 3 && val) अणु
			val = (val / SZ_32M) | 1;
			gprval |= val << cs * 3;
		पूर्ण
		i++;
	पूर्ण

	अगर (i == 0 || i % 4)
		जाओ err;

	क्रम (i = 0; i < ARRAY_SIZE(gprvals); i++) अणु
		अगर (gprval == gprvals[i]) अणु
			/* Found it. Set up IOMUXC_GPR1[11:0] with it. */
			regmap_update_bits(gpr, IOMUXC_GPR1, 0xfff, gprval);
			वापस 0;
		पूर्ण
	पूर्ण

err:
	dev_err(&pdev->dev, "Invalid 'ranges' configuration\n");
	वापस -EINVAL;
पूर्ण

/* Parse and set the timing क्रम this device. */
अटल पूर्णांक weim_timing_setup(काष्ठा device *dev,
			     काष्ठा device_node *np, व्योम __iomem *base,
			     स्थिर काष्ठा imx_weim_devtype *devtype,
			     काष्ठा cs_timing_state *ts)
अणु
	u32 cs_idx, value[MAX_CS_REGS_COUNT];
	पूर्णांक i, ret;
	पूर्णांक reg_idx, num_regs;
	काष्ठा cs_timing *cst;

	अगर (WARN_ON(devtype->cs_regs_count > MAX_CS_REGS_COUNT))
		वापस -EINVAL;
	अगर (WARN_ON(devtype->cs_count > MAX_CS_COUNT))
		वापस -EINVAL;

	ret = of_property_पढ़ो_u32_array(np, "fsl,weim-cs-timing",
					 value, devtype->cs_regs_count);
	अगर (ret)
		वापस ret;

	/*
	 * the child node's "reg" property may contain multiple address ranges,
	 * extract the chip select क्रम each.
	 */
	num_regs = of_property_count_elems_of_size(np, "reg", OF_REG_SIZE);
	अगर (num_regs < 0)
		वापस num_regs;
	अगर (!num_regs)
		वापस -EINVAL;
	क्रम (reg_idx = 0; reg_idx < num_regs; reg_idx++) अणु
		/* get the CS index from this child node's "reg" property. */
		ret = of_property_पढ़ो_u32_index(np, "reg",
					reg_idx * OF_REG_SIZE, &cs_idx);
		अगर (ret)
			अवरोध;

		अगर (cs_idx >= devtype->cs_count)
			वापस -EINVAL;

		/* prevent re-configuring a CS that's alपढ़ोy been configured */
		cst = &ts->cs[cs_idx];
		अगर (cst->is_applied && स_भेद(value, cst->regs,
					devtype->cs_regs_count * माप(u32))) अणु
			dev_err(dev, "fsl,weim-cs-timing conflict on %pOF", np);
			वापस -EINVAL;
		पूर्ण

		/* set the timing क्रम WEIM */
		क्रम (i = 0; i < devtype->cs_regs_count; i++)
			ग_लिखोl(value[i],
				base + cs_idx * devtype->cs_stride + i * 4);
		अगर (!cst->is_applied) अणु
			cst->is_applied = true;
			स_नकल(cst->regs, value,
				devtype->cs_regs_count * माप(u32));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक weim_parse_dt(काष्ठा platक्रमm_device *pdev, व्योम __iomem *base)
अणु
	स्थिर काष्ठा of_device_id *of_id = of_match_device(weim_id_table,
							   &pdev->dev);
	स्थिर काष्ठा imx_weim_devtype *devtype = of_id->data;
	काष्ठा device_node *child;
	पूर्णांक ret, have_child = 0;
	काष्ठा cs_timing_state ts = अणुपूर्ण;
	u32 reg;

	अगर (devtype == &imx50_weim_devtype) अणु
		ret = imx_weim_gpr_setup(pdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "fsl,burst-clk-enable")) अणु
		अगर (devtype->wcr_bcm) अणु
			reg = पढ़ोl(base + devtype->wcr_offset);
			ग_लिखोl(reg | devtype->wcr_bcm,
				base + devtype->wcr_offset);
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "burst clk mode not supported.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम_each_available_child_of_node(pdev->dev.of_node, child) अणु
		ret = weim_timing_setup(&pdev->dev, child, base, devtype, &ts);
		अगर (ret)
			dev_warn(&pdev->dev, "%pOF set timing failed.\n",
				child);
		अन्यथा
			have_child = 1;
	पूर्ण

	अगर (have_child)
		ret = of_platक्रमm_शेष_populate(pdev->dev.of_node,
						   शून्य, &pdev->dev);
	अगर (ret)
		dev_err(&pdev->dev, "%pOF fail to create devices.\n",
			pdev->dev.of_node);
	वापस ret;
पूर्ण

अटल पूर्णांक weim_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	पूर्णांक ret;

	/* get the resource */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	/* get the घड़ी */
	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	/* parse the device node */
	ret = weim_parse_dt(pdev, base);
	अगर (ret)
		clk_disable_unprepare(clk);
	अन्यथा
		dev_info(&pdev->dev, "Driver registered.\n");

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver weim_driver = अणु
	.driver = अणु
		.name		= "imx-weim",
		.of_match_table	= weim_id_table,
	पूर्ण,
	.probe = weim_probe,
पूर्ण;
module_platक्रमm_driver(weim_driver);

MODULE_AUTHOR("Freescale Semiconductor Inc.");
MODULE_DESCRIPTION("i.MX EIM Controller Driver");
MODULE_LICENSE("GPL");
