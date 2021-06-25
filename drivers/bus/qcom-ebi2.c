<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm External Bus Interface 2 (EBI2) driver
 * an older version of the Qualcomm Parallel Interface Controller (QPIC)
 *
 * Copyright (C) 2016 Linaro Ltd.
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 *
 * See the device tree bindings क्रम this block क्रम more details on the
 * hardware.
 */

#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>

/*
 * CS0, CS1, CS4 and CS5 are two bits wide, CS2 and CS3 are one bit.
 */
#घोषणा EBI2_CS0_ENABLE_MASK BIT(0)|BIT(1)
#घोषणा EBI2_CS1_ENABLE_MASK BIT(2)|BIT(3)
#घोषणा EBI2_CS2_ENABLE_MASK BIT(4)
#घोषणा EBI2_CS3_ENABLE_MASK BIT(5)
#घोषणा EBI2_CS4_ENABLE_MASK BIT(6)|BIT(7)
#घोषणा EBI2_CS5_ENABLE_MASK BIT(8)|BIT(9)
#घोषणा EBI2_CSN_MASK GENMASK(9, 0)

#घोषणा EBI2_XMEM_CFG 0x0000 /* Power management etc */

/*
 * SLOW CSn CFG
 *
 * Bits 31-28: RECOVERY recovery cycles (0 = 1, 1 = 2 etc) this is the समय the
 *             memory जारीs to drive the data bus after OE is de-निश्चितed.
 *             Inserted when पढ़ोing one CS and चयनing to another CS or पढ़ो
 *             followed by ग_लिखो on the same CS. Valid values 0 thru 15.
 * Bits 27-24: WR_HOLD ग_लिखो hold cycles, these are extra cycles inserted after
 *             every ग_लिखो minimum 1. The data out is driven from the समय WE is
 *             निश्चितed until CS is निश्चितed. With a hold of 1, the CS stays
 *             active क्रम 1 extra cycle etc. Valid values 0 thru 15.
 * Bits 23-16: WR_DELTA initial latency क्रम ग_लिखो cycles inserted क्रम the first
 *             ग_लिखो to a page or burst memory
 * Bits 15-8:  RD_DELTA initial latency क्रम पढ़ो cycles inserted क्रम the first
 *             पढ़ो to a page or burst memory
 * Bits 7-4:   WR_WAIT number of रुको cycles क्रम every ग_लिखो access, 0=1 cycle
 *             so 1 thru 16 cycles.
 * Bits 3-0:   RD_WAIT number of रुको cycles क्रम every पढ़ो access, 0=1 cycle
 *             so 1 thru 16 cycles.
 */
#घोषणा EBI2_XMEM_CS0_SLOW_CFG 0x0008
#घोषणा EBI2_XMEM_CS1_SLOW_CFG 0x000C
#घोषणा EBI2_XMEM_CS2_SLOW_CFG 0x0010
#घोषणा EBI2_XMEM_CS3_SLOW_CFG 0x0014
#घोषणा EBI2_XMEM_CS4_SLOW_CFG 0x0018
#घोषणा EBI2_XMEM_CS5_SLOW_CFG 0x001C

#घोषणा EBI2_XMEM_RECOVERY_SHIFT	28
#घोषणा EBI2_XMEM_WR_HOLD_SHIFT		24
#घोषणा EBI2_XMEM_WR_DELTA_SHIFT	16
#घोषणा EBI2_XMEM_RD_DELTA_SHIFT	8
#घोषणा EBI2_XMEM_WR_WAIT_SHIFT		4
#घोषणा EBI2_XMEM_RD_WAIT_SHIFT		0

/*
 * FAST CSn CFG
 * Bits 31-28: ?
 * Bits 27-24: RD_HOLD: the length in cycles of the first segment of a पढ़ो
 *             transfer. For a single पढ़ो tअक्रमfer this will be the समय
 *             from CS निश्चितion to OE निश्चितion.
 * Bits 18-24: ?
 * Bits 17-16: ADV_OE_RECOVERY, the number of cycles elapsed beक्रमe an OE
 *             निश्चितion, with respect to the cycle where ADV is निश्चितed.
 *             2 means 2 cycles between ADV and OE. Values 0, 1, 2 or 3.
 * Bits 5:     ADDR_HOLD_ENA, The address is held क्रम an extra cycle to meet
 *             hold समय requirements with ADV निश्चितion.
 *
 * The manual mentions "write precharge cycles" and "precharge cycles".
 * We have not been able to figure out which bit fields these correspond to
 * in the hardware, or what valid values exist. The current hypothesis is that
 * this is something just used on the FAST chip selects. There is also a "byte
 * device enable" flag somewhere क्रम 8bit memories.
 */
#घोषणा EBI2_XMEM_CS0_FAST_CFG 0x0028
#घोषणा EBI2_XMEM_CS1_FAST_CFG 0x002C
#घोषणा EBI2_XMEM_CS2_FAST_CFG 0x0030
#घोषणा EBI2_XMEM_CS3_FAST_CFG 0x0034
#घोषणा EBI2_XMEM_CS4_FAST_CFG 0x0038
#घोषणा EBI2_XMEM_CS5_FAST_CFG 0x003C

#घोषणा EBI2_XMEM_RD_HOLD_SHIFT		24
#घोषणा EBI2_XMEM_ADV_OE_RECOVERY_SHIFT	16
#घोषणा EBI2_XMEM_ADDR_HOLD_ENA_SHIFT	5

/**
 * काष्ठा cs_data - काष्ठा with info on a chipselect setting
 * @enable_mask: mask to enable the chipselect in the EBI2 config
 * @slow_cfg0: offset to XMEMC slow CS config
 * @fast_cfg1: offset to XMEMC fast CS config
 */
काष्ठा cs_data अणु
	u32 enable_mask;
	u16 slow_cfg;
	u16 fast_cfg;
पूर्ण;

अटल स्थिर काष्ठा cs_data cs_info[] = अणु
	अणु
		/* CS0 */
		.enable_mask = EBI2_CS0_ENABLE_MASK,
		.slow_cfg = EBI2_XMEM_CS0_SLOW_CFG,
		.fast_cfg = EBI2_XMEM_CS0_FAST_CFG,
	पूर्ण,
	अणु
		/* CS1 */
		.enable_mask = EBI2_CS1_ENABLE_MASK,
		.slow_cfg = EBI2_XMEM_CS1_SLOW_CFG,
		.fast_cfg = EBI2_XMEM_CS1_FAST_CFG,
	पूर्ण,
	अणु
		/* CS2 */
		.enable_mask = EBI2_CS2_ENABLE_MASK,
		.slow_cfg = EBI2_XMEM_CS2_SLOW_CFG,
		.fast_cfg = EBI2_XMEM_CS2_FAST_CFG,
	पूर्ण,
	अणु
		/* CS3 */
		.enable_mask = EBI2_CS3_ENABLE_MASK,
		.slow_cfg = EBI2_XMEM_CS3_SLOW_CFG,
		.fast_cfg = EBI2_XMEM_CS3_FAST_CFG,
	पूर्ण,
	अणु
		/* CS4 */
		.enable_mask = EBI2_CS4_ENABLE_MASK,
		.slow_cfg = EBI2_XMEM_CS4_SLOW_CFG,
		.fast_cfg = EBI2_XMEM_CS4_FAST_CFG,
	पूर्ण,
	अणु
		/* CS5 */
		.enable_mask = EBI2_CS5_ENABLE_MASK,
		.slow_cfg = EBI2_XMEM_CS5_SLOW_CFG,
		.fast_cfg = EBI2_XMEM_CS5_FAST_CFG,
	पूर्ण,
पूर्ण;

/**
 * काष्ठा ebi2_xmem_prop - describes an XMEM config property
 * @prop: the device tree binding name
 * @max: maximum value क्रम the property
 * @slowreg: true अगर this property is in the SLOW CS config रेजिस्टर
 * अन्यथा it is assumed to be in the FAST config रेजिस्टर
 * @shअगरt: the bit field start in the SLOW or FAST रेजिस्टर क्रम this
 * property
 */
काष्ठा ebi2_xmem_prop अणु
	स्थिर अक्षर *prop;
	u32 max;
	bool slowreg;
	u16 shअगरt;
पूर्ण;

अटल स्थिर काष्ठा ebi2_xmem_prop xmem_props[] = अणु
	अणु
		.prop = "qcom,xmem-recovery-cycles",
		.max = 15,
		.slowreg = true,
		.shअगरt = EBI2_XMEM_RECOVERY_SHIFT,
	पूर्ण,
	अणु
		.prop = "qcom,xmem-write-hold-cycles",
		.max = 15,
		.slowreg = true,
		.shअगरt = EBI2_XMEM_WR_HOLD_SHIFT,
	पूर्ण,
	अणु
		.prop = "qcom,xmem-write-delta-cycles",
		.max = 255,
		.slowreg = true,
		.shअगरt = EBI2_XMEM_WR_DELTA_SHIFT,
	पूर्ण,
	अणु
		.prop = "qcom,xmem-read-delta-cycles",
		.max = 255,
		.slowreg = true,
		.shअगरt = EBI2_XMEM_RD_DELTA_SHIFT,
	पूर्ण,
	अणु
		.prop = "qcom,xmem-write-wait-cycles",
		.max = 15,
		.slowreg = true,
		.shअगरt = EBI2_XMEM_WR_WAIT_SHIFT,
	पूर्ण,
	अणु
		.prop = "qcom,xmem-read-wait-cycles",
		.max = 15,
		.slowreg = true,
		.shअगरt = EBI2_XMEM_RD_WAIT_SHIFT,
	पूर्ण,
	अणु
		.prop = "qcom,xmem-address-hold-enable",
		.max = 1, /* boolean prop */
		.slowreg = false,
		.shअगरt = EBI2_XMEM_ADDR_HOLD_ENA_SHIFT,
	पूर्ण,
	अणु
		.prop = "qcom,xmem-adv-to-oe-recovery-cycles",
		.max = 3,
		.slowreg = false,
		.shअगरt = EBI2_XMEM_ADV_OE_RECOVERY_SHIFT,
	पूर्ण,
	अणु
		.prop = "qcom,xmem-read-hold-cycles",
		.max = 15,
		.slowreg = false,
		.shअगरt = EBI2_XMEM_RD_HOLD_SHIFT,
	पूर्ण,
पूर्ण;

अटल व्योम qcom_ebi2_setup_chipselect(काष्ठा device_node *np,
				       काष्ठा device *dev,
				       व्योम __iomem *ebi2_base,
				       व्योम __iomem *ebi2_xmem,
				       u32 csindex)
अणु
	स्थिर काष्ठा cs_data *csd;
	u32 slowcfg, fastcfg;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	csd = &cs_info[csindex];
	val = पढ़ोl(ebi2_base);
	val |= csd->enable_mask;
	ग_लिखोl(val, ebi2_base);
	dev_dbg(dev, "enabled CS%u\n", csindex);

	/* Next set up the XMEMC */
	slowcfg = 0;
	fastcfg = 0;

	क्रम (i = 0; i < ARRAY_SIZE(xmem_props); i++) अणु
		स्थिर काष्ठा ebi2_xmem_prop *xp = &xmem_props[i];

		/* All are regular u32 values */
		ret = of_property_पढ़ो_u32(np, xp->prop, &val);
		अगर (ret) अणु
			dev_dbg(dev, "could not read %s for CS%d\n",
				xp->prop, csindex);
			जारी;
		पूर्ण

		/* First check boolean props */
		अगर (xp->max == 1 && val) अणु
			अगर (xp->slowreg)
				slowcfg |= BIT(xp->shअगरt);
			अन्यथा
				fastcfg |= BIT(xp->shअगरt);
			dev_dbg(dev, "set %s flag\n", xp->prop);
			जारी;
		पूर्ण

		/* We're dealing with an u32 */
		अगर (val > xp->max) अणु
			dev_err(dev,
				"too high value for %s: %u, capped at %u\n",
				xp->prop, val, xp->max);
			val = xp->max;
		पूर्ण
		अगर (xp->slowreg)
			slowcfg |= (val << xp->shअगरt);
		अन्यथा
			fastcfg |= (val << xp->shअगरt);
		dev_dbg(dev, "set %s to %u\n", xp->prop, val);
	पूर्ण

	dev_info(dev, "CS%u: SLOW CFG 0x%08x, FAST CFG 0x%08x\n",
		 csindex, slowcfg, fastcfg);

	अगर (slowcfg)
		ग_लिखोl(slowcfg, ebi2_xmem + csd->slow_cfg);
	अगर (fastcfg)
		ग_लिखोl(fastcfg, ebi2_xmem + csd->fast_cfg);
पूर्ण

अटल पूर्णांक qcom_ebi2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *child;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	व्योम __iomem *ebi2_base;
	व्योम __iomem *ebi2_xmem;
	काष्ठा clk *ebi2xclk;
	काष्ठा clk *ebi2clk;
	bool have_children = false;
	u32 val;
	पूर्णांक ret;

	ebi2xclk = devm_clk_get(dev, "ebi2x");
	अगर (IS_ERR(ebi2xclk))
		वापस PTR_ERR(ebi2xclk);

	ret = clk_prepare_enable(ebi2xclk);
	अगर (ret) अणु
		dev_err(dev, "could not enable EBI2X clk (%d)\n", ret);
		वापस ret;
	पूर्ण

	ebi2clk = devm_clk_get(dev, "ebi2");
	अगर (IS_ERR(ebi2clk)) अणु
		ret = PTR_ERR(ebi2clk);
		जाओ err_disable_2x_clk;
	पूर्ण

	ret = clk_prepare_enable(ebi2clk);
	अगर (ret) अणु
		dev_err(dev, "could not enable EBI2 clk\n");
		जाओ err_disable_2x_clk;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ebi2_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ebi2_base)) अणु
		ret = PTR_ERR(ebi2_base);
		जाओ err_disable_clk;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	ebi2_xmem = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ebi2_xmem)) अणु
		ret = PTR_ERR(ebi2_xmem);
		जाओ err_disable_clk;
	पूर्ण

	/* Allegedly this turns the घातer save mode off */
	ग_लिखोl(0UL, ebi2_xmem + EBI2_XMEM_CFG);

	/* Disable all chipselects */
	val = पढ़ोl(ebi2_base);
	val &= ~EBI2_CSN_MASK;
	ग_लिखोl(val, ebi2_base);

	/* Walk over the child nodes and see what chipselects we use */
	क्रम_each_available_child_of_node(np, child) अणु
		u32 csindex;

		/* Figure out the chipselect */
		ret = of_property_पढ़ो_u32(child, "reg", &csindex);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण

		अगर (csindex > 5) अणु
			dev_err(dev,
				"invalid chipselect %u, we only support 0-5\n",
				csindex);
			जारी;
		पूर्ण

		qcom_ebi2_setup_chipselect(child,
					   dev,
					   ebi2_base,
					   ebi2_xmem,
					   csindex);

		/* We have at least one child */
		have_children = true;
	पूर्ण

	अगर (have_children)
		वापस of_platक्रमm_शेष_populate(np, शून्य, dev);
	वापस 0;

err_disable_clk:
	clk_disable_unprepare(ebi2clk);
err_disable_2x_clk:
	clk_disable_unprepare(ebi2xclk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_ebi2_of_match[] = अणु
	अणु .compatible = "qcom,msm8660-ebi2", पूर्ण,
	अणु .compatible = "qcom,apq8060-ebi2", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver qcom_ebi2_driver = अणु
	.probe = qcom_ebi2_probe,
	.driver = अणु
		.name = "qcom-ebi2",
		.of_match_table = qcom_ebi2_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_ebi2_driver);
MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("Qualcomm EBI2 driver");
MODULE_LICENSE("GPL");
