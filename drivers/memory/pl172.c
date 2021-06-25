<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Memory controller driver क्रम ARM PrimeCell PL172
 * PrimeCell MultiPort Memory Controller (PL172)
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * Based on:
 * TI AEMIF driver, Copyright (C) 2010 - 2013 Texas Instruments Inc.
 */

#समावेश <linux/amba/bus.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/समय.स>

#घोषणा MPMC_STATIC_CFG(n)		(0x200 + 0x20 * (n))
#घोषणा  MPMC_STATIC_CFG_MW_8BIT	0x0
#घोषणा  MPMC_STATIC_CFG_MW_16BIT	0x1
#घोषणा  MPMC_STATIC_CFG_MW_32BIT	0x2
#घोषणा  MPMC_STATIC_CFG_PM		BIT(3)
#घोषणा  MPMC_STATIC_CFG_PC		BIT(6)
#घोषणा  MPMC_STATIC_CFG_PB		BIT(7)
#घोषणा  MPMC_STATIC_CFG_EW		BIT(8)
#घोषणा  MPMC_STATIC_CFG_B		BIT(19)
#घोषणा  MPMC_STATIC_CFG_P		BIT(20)
#घोषणा MPMC_STATIC_WAIT_WEN(n)		(0x204 + 0x20 * (n))
#घोषणा  MPMC_STATIC_WAIT_WEN_MAX	0x0f
#घोषणा MPMC_STATIC_WAIT_OEN(n)		(0x208 + 0x20 * (n))
#घोषणा  MPMC_STATIC_WAIT_OEN_MAX	0x0f
#घोषणा MPMC_STATIC_WAIT_RD(n)		(0x20c + 0x20 * (n))
#घोषणा  MPMC_STATIC_WAIT_RD_MAX	0x1f
#घोषणा MPMC_STATIC_WAIT_PAGE(n)	(0x210 + 0x20 * (n))
#घोषणा  MPMC_STATIC_WAIT_PAGE_MAX	0x1f
#घोषणा MPMC_STATIC_WAIT_WR(n)		(0x214 + 0x20 * (n))
#घोषणा  MPMC_STATIC_WAIT_WR_MAX	0x1f
#घोषणा MPMC_STATIC_WAIT_TURN(n)	(0x218 + 0x20 * (n))
#घोषणा  MPMC_STATIC_WAIT_TURN_MAX	0x0f

/* Maximum number of अटल chip selects */
#घोषणा PL172_MAX_CS		4

काष्ठा pl172_data अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक pl172_timing_prop(काष्ठा amba_device *adev,
			     स्थिर काष्ठा device_node *np, स्थिर अक्षर *name,
			     u32 reg_offset, u32 max, पूर्णांक start)
अणु
	काष्ठा pl172_data *pl172 = amba_get_drvdata(adev);
	पूर्णांक cycles;
	u32 val;

	अगर (!of_property_पढ़ो_u32(np, name, &val)) अणु
		cycles = DIV_ROUND_UP(val * pl172->rate, NSEC_PER_MSEC) - start;
		अगर (cycles < 0) अणु
			cycles = 0;
		पूर्ण अन्यथा अगर (cycles > max) अणु
			dev_err(&adev->dev, "%s timing too tight\n", name);
			वापस -EINVAL;
		पूर्ण

		ग_लिखोl(cycles, pl172->base + reg_offset);
	पूर्ण

	dev_dbg(&adev->dev, "%s: %u cycle(s)\n", name, start +
				पढ़ोl(pl172->base + reg_offset));

	वापस 0;
पूर्ण

अटल पूर्णांक pl172_setup_अटल(काष्ठा amba_device *adev,
			      काष्ठा device_node *np, u32 cs)
अणु
	काष्ठा pl172_data *pl172 = amba_get_drvdata(adev);
	u32 cfg;
	पूर्णांक ret;

	/* MPMC अटल memory configuration */
	अगर (!of_property_पढ़ो_u32(np, "mpmc,memory-width", &cfg)) अणु
		अगर (cfg == 8) अणु
			cfg = MPMC_STATIC_CFG_MW_8BIT;
		पूर्ण अन्यथा अगर (cfg == 16) अणु
			cfg = MPMC_STATIC_CFG_MW_16BIT;
		पूर्ण अन्यथा अगर (cfg == 32) अणु
			cfg = MPMC_STATIC_CFG_MW_32BIT;
		पूर्ण अन्यथा अणु
			dev_err(&adev->dev, "invalid memory width cs%u\n", cs);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&adev->dev, "memory-width property required\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "mpmc,async-page-mode"))
		cfg |= MPMC_STATIC_CFG_PM;

	अगर (of_property_पढ़ो_bool(np, "mpmc,cs-active-high"))
		cfg |= MPMC_STATIC_CFG_PC;

	अगर (of_property_पढ़ो_bool(np, "mpmc,byte-lane-low"))
		cfg |= MPMC_STATIC_CFG_PB;

	अगर (of_property_पढ़ो_bool(np, "mpmc,extended-wait"))
		cfg |= MPMC_STATIC_CFG_EW;

	अगर (amba_part(adev) == 0x172 &&
	    of_property_पढ़ो_bool(np, "mpmc,buffer-enable"))
		cfg |= MPMC_STATIC_CFG_B;

	अगर (of_property_पढ़ो_bool(np, "mpmc,write-protect"))
		cfg |= MPMC_STATIC_CFG_P;

	ग_लिखोl(cfg, pl172->base + MPMC_STATIC_CFG(cs));
	dev_dbg(&adev->dev, "mpmc static config cs%u: 0x%08x\n", cs, cfg);

	/* MPMC अटल memory timing */
	ret = pl172_timing_prop(adev, np, "mpmc,write-enable-delay",
				MPMC_STATIC_WAIT_WEN(cs),
				MPMC_STATIC_WAIT_WEN_MAX, 1);
	अगर (ret)
		जाओ fail;

	ret = pl172_timing_prop(adev, np, "mpmc,output-enable-delay",
				MPMC_STATIC_WAIT_OEN(cs),
				MPMC_STATIC_WAIT_OEN_MAX, 0);
	अगर (ret)
		जाओ fail;

	ret = pl172_timing_prop(adev, np, "mpmc,read-access-delay",
				MPMC_STATIC_WAIT_RD(cs),
				MPMC_STATIC_WAIT_RD_MAX, 1);
	अगर (ret)
		जाओ fail;

	ret = pl172_timing_prop(adev, np, "mpmc,page-mode-read-delay",
				MPMC_STATIC_WAIT_PAGE(cs),
				MPMC_STATIC_WAIT_PAGE_MAX, 1);
	अगर (ret)
		जाओ fail;

	ret = pl172_timing_prop(adev, np, "mpmc,write-access-delay",
				MPMC_STATIC_WAIT_WR(cs),
				MPMC_STATIC_WAIT_WR_MAX, 2);
	अगर (ret)
		जाओ fail;

	ret = pl172_timing_prop(adev, np, "mpmc,turn-round-delay",
				MPMC_STATIC_WAIT_TURN(cs),
				MPMC_STATIC_WAIT_TURN_MAX, 1);
	अगर (ret)
		जाओ fail;

	वापस 0;
fail:
	dev_err(&adev->dev, "failed to configure cs%u\n", cs);
	वापस ret;
पूर्ण

अटल पूर्णांक pl172_parse_cs_config(काष्ठा amba_device *adev,
				 काष्ठा device_node *np)
अणु
	u32 cs;

	अगर (!of_property_पढ़ो_u32(np, "mpmc,cs", &cs)) अणु
		अगर (cs >= PL172_MAX_CS) अणु
			dev_err(&adev->dev, "cs%u invalid\n", cs);
			वापस -EINVAL;
		पूर्ण

		वापस pl172_setup_अटल(adev, np, cs);
	पूर्ण

	dev_err(&adev->dev, "cs property required\n");

	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर * स्थिर pl172_revisions[] = अणु"r1", "r2", "r2p3", "r2p4"पूर्ण;
अटल स्थिर अक्षर * स्थिर pl175_revisions[] = अणु"r1"पूर्ण;
अटल स्थिर अक्षर * स्थिर pl176_revisions[] = अणु"r0"पूर्ण;

अटल पूर्णांक pl172_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा device_node *child_np, *np = adev->dev.of_node;
	काष्ठा device *dev = &adev->dev;
	अटल स्थिर अक्षर *rev = "?";
	काष्ठा pl172_data *pl172;
	पूर्णांक ret;

	अगर (amba_part(adev) == 0x172) अणु
		अगर (amba_rev(adev) < ARRAY_SIZE(pl172_revisions))
			rev = pl172_revisions[amba_rev(adev)];
	पूर्ण अन्यथा अगर (amba_part(adev) == 0x175) अणु
		अगर (amba_rev(adev) < ARRAY_SIZE(pl175_revisions))
			rev = pl175_revisions[amba_rev(adev)];
	पूर्ण अन्यथा अगर (amba_part(adev) == 0x176) अणु
		अगर (amba_rev(adev) < ARRAY_SIZE(pl176_revisions))
			rev = pl176_revisions[amba_rev(adev)];
	पूर्ण

	dev_info(dev, "ARM PL%x revision %s\n", amba_part(adev), rev);

	pl172 = devm_kzalloc(dev, माप(*pl172), GFP_KERNEL);
	अगर (!pl172)
		वापस -ENOMEM;

	pl172->clk = devm_clk_get(dev, "mpmcclk");
	अगर (IS_ERR(pl172->clk)) अणु
		dev_err(dev, "no mpmcclk provided clock\n");
		वापस PTR_ERR(pl172->clk);
	पूर्ण

	ret = clk_prepare_enable(pl172->clk);
	अगर (ret) अणु
		dev_err(dev, "unable to mpmcclk enable clock\n");
		वापस ret;
	पूर्ण

	pl172->rate = clk_get_rate(pl172->clk) / MSEC_PER_SEC;
	अगर (!pl172->rate) अणु
		dev_err(dev, "unable to get mpmcclk clock rate\n");
		ret = -EINVAL;
		जाओ err_clk_enable;
	पूर्ण

	ret = amba_request_regions(adev, शून्य);
	अगर (ret) अणु
		dev_err(dev, "unable to request AMBA regions\n");
		जाओ err_clk_enable;
	पूर्ण

	pl172->base = devm_ioremap(dev, adev->res.start,
				   resource_size(&adev->res));
	अगर (!pl172->base) अणु
		dev_err(dev, "ioremap failed\n");
		ret = -ENOMEM;
		जाओ err_no_ioremap;
	पूर्ण

	amba_set_drvdata(adev, pl172);

	/*
	 * Loop through each child node, which represent a chip select, and
	 * configure parameters and timing. If successful; populate devices
	 * under that node.
	 */
	क्रम_each_available_child_of_node(np, child_np) अणु
		ret = pl172_parse_cs_config(adev, child_np);
		अगर (ret)
			जारी;

		of_platक्रमm_populate(child_np, शून्य, शून्य, dev);
	पूर्ण

	वापस 0;

err_no_ioremap:
	amba_release_regions(adev);
err_clk_enable:
	clk_disable_unprepare(pl172->clk);
	वापस ret;
पूर्ण

अटल व्योम pl172_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा pl172_data *pl172 = amba_get_drvdata(adev);

	clk_disable_unprepare(pl172->clk);
	amba_release_regions(adev);
पूर्ण

अटल स्थिर काष्ठा amba_id pl172_ids[] = अणु
	/*  PrimeCell MPMC PL172, EMC found on NXP LPC18xx and LPC43xx */
	अणु
		.id	= 0x07041172,
		.mask	= 0x3f0fffff,
	पूर्ण,
	/* PrimeCell MPMC PL175, EMC found on NXP LPC32xx */
	अणु
		.id	= 0x07041175,
		.mask	= 0x3f0fffff,
	पूर्ण,
	/* PrimeCell MPMC PL176 */
	अणु
		.id	= 0x89041176,
		.mask	= 0xff0fffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(amba, pl172_ids);

अटल काष्ठा amba_driver pl172_driver = अणु
	.drv = अणु
		.name	= "memory-pl172",
	पूर्ण,
	.probe		= pl172_probe,
	.हटाओ		= pl172_हटाओ,
	.id_table	= pl172_ids,
पूर्ण;
module_amba_driver(pl172_driver);

MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_DESCRIPTION("PL172 Memory Controller Driver");
MODULE_LICENSE("GPL v2");
