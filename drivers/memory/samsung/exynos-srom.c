<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2015 Samsung Electronics Co., Ltd.
//	      http://www.samsung.com/
//
// Exynos - SROM Controller support
// Author: Pankaj Dubey <pankaj.dubey@samsung.com>

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "exynos-srom.h"

अटल स्थिर अचिन्हित दीर्घ exynos_srom_offsets[] = अणु
	/* SROM side */
	EXYNOS_SROM_BW,
	EXYNOS_SROM_BC0,
	EXYNOS_SROM_BC1,
	EXYNOS_SROM_BC2,
	EXYNOS_SROM_BC3,
पूर्ण;

/**
 * काष्ठा exynos_srom_reg_dump: रेजिस्टर dump of SROM Controller रेजिस्टरs.
 * @offset: srom रेजिस्टर offset from the controller base address.
 * @value: the value of रेजिस्टर under the offset.
 */
काष्ठा exynos_srom_reg_dump अणु
	u32     offset;
	u32     value;
पूर्ण;

/**
 * काष्ठा exynos_srom: platक्रमm data क्रम exynos srom controller driver.
 * @dev: platक्रमm device poपूर्णांकer
 * @reg_base: srom base address
 * @reg_offset: exynos_srom_reg_dump poपूर्णांकer to hold offset and its value.
 */
काष्ठा exynos_srom अणु
	काष्ठा device *dev;
	व्योम __iomem *reg_base;
	काष्ठा exynos_srom_reg_dump *reg_offset;
पूर्ण;

अटल काष्ठा exynos_srom_reg_dump *
exynos_srom_alloc_reg_dump(स्थिर अचिन्हित दीर्घ *rdump,
			   अचिन्हित दीर्घ nr_rdump)
अणु
	काष्ठा exynos_srom_reg_dump *rd;
	अचिन्हित पूर्णांक i;

	rd = kसुस्मृति(nr_rdump, माप(*rd), GFP_KERNEL);
	अगर (!rd)
		वापस शून्य;

	क्रम (i = 0; i < nr_rdump; ++i)
		rd[i].offset = rdump[i];

	वापस rd;
पूर्ण

अटल पूर्णांक exynos_srom_configure_bank(काष्ठा exynos_srom *srom,
				      काष्ठा device_node *np)
अणु
	u32 bank, width, pmc = 0;
	u32 timing[6];
	u32 cs, bw;

	अगर (of_property_पढ़ो_u32(np, "reg", &bank))
		वापस -EINVAL;
	अगर (of_property_पढ़ो_u32(np, "reg-io-width", &width))
		width = 1;
	अगर (of_property_पढ़ो_bool(np, "samsung,srom-page-mode"))
		pmc = 1 << EXYNOS_SROM_BCX__PMC__SHIFT;
	अगर (of_property_पढ़ो_u32_array(np, "samsung,srom-timing", timing,
				       ARRAY_SIZE(timing)))
		वापस -EINVAL;

	bank *= 4; /* Convert bank पूर्णांकo shअगरt/offset */

	cs = 1 << EXYNOS_SROM_BW__BYTEENABLE__SHIFT;
	अगर (width == 2)
		cs |= 1 << EXYNOS_SROM_BW__DATAWIDTH__SHIFT;

	bw = पढ़ोl_relaxed(srom->reg_base + EXYNOS_SROM_BW);
	bw = (bw & ~(EXYNOS_SROM_BW__CS_MASK << bank)) | (cs << bank);
	ग_लिखोl_relaxed(bw, srom->reg_base + EXYNOS_SROM_BW);

	ग_लिखोl_relaxed(pmc | (timing[0] << EXYNOS_SROM_BCX__TACP__SHIFT) |
		       (timing[1] << EXYNOS_SROM_BCX__TCAH__SHIFT) |
		       (timing[2] << EXYNOS_SROM_BCX__TCOH__SHIFT) |
		       (timing[3] << EXYNOS_SROM_BCX__TACC__SHIFT) |
		       (timing[4] << EXYNOS_SROM_BCX__TCOS__SHIFT) |
		       (timing[5] << EXYNOS_SROM_BCX__TACS__SHIFT),
		       srom->reg_base + EXYNOS_SROM_BC0 + bank);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_srom_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np, *child;
	काष्ठा exynos_srom *srom;
	काष्ठा device *dev = &pdev->dev;
	bool bad_bank_config = false;

	np = dev->of_node;
	अगर (!np) अणु
		dev_err(&pdev->dev, "could not find device info\n");
		वापस -EINVAL;
	पूर्ण

	srom = devm_kzalloc(&pdev->dev,
			    माप(काष्ठा exynos_srom), GFP_KERNEL);
	अगर (!srom)
		वापस -ENOMEM;

	srom->dev = dev;
	srom->reg_base = of_iomap(np, 0);
	अगर (!srom->reg_base) अणु
		dev_err(&pdev->dev, "iomap of exynos srom controller failed\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, srom);

	srom->reg_offset = exynos_srom_alloc_reg_dump(exynos_srom_offsets,
						      ARRAY_SIZE(exynos_srom_offsets));
	अगर (!srom->reg_offset) अणु
		iounmap(srom->reg_base);
		वापस -ENOMEM;
	पूर्ण

	क्रम_each_child_of_node(np, child) अणु
		अगर (exynos_srom_configure_bank(srom, child)) अणु
			dev_err(dev,
				"Could not decode bank configuration for %pOFn\n",
				child);
			bad_bank_config = true;
		पूर्ण
	पूर्ण

	/*
	 * If any bank failed to configure, we still provide suspend/resume,
	 * but करो not probe child devices
	 */
	अगर (bad_bank_config)
		वापस 0;

	वापस of_platक्रमm_populate(np, शून्य, शून्य, dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम exynos_srom_save(व्योम __iomem *base,
			     काष्ठा exynos_srom_reg_dump *rd,
			     अचिन्हित पूर्णांक num_regs)
अणु
	क्रम (; num_regs > 0; --num_regs, ++rd)
		rd->value = पढ़ोl(base + rd->offset);
पूर्ण

अटल व्योम exynos_srom_restore(व्योम __iomem *base,
				स्थिर काष्ठा exynos_srom_reg_dump *rd,
				अचिन्हित पूर्णांक num_regs)
अणु
	क्रम (; num_regs > 0; --num_regs, ++rd)
		ग_लिखोl(rd->value, base + rd->offset);
पूर्ण

अटल पूर्णांक exynos_srom_suspend(काष्ठा device *dev)
अणु
	काष्ठा exynos_srom *srom = dev_get_drvdata(dev);

	exynos_srom_save(srom->reg_base, srom->reg_offset,
			 ARRAY_SIZE(exynos_srom_offsets));
	वापस 0;
पूर्ण

अटल पूर्णांक exynos_srom_resume(काष्ठा device *dev)
अणु
	काष्ठा exynos_srom *srom = dev_get_drvdata(dev);

	exynos_srom_restore(srom->reg_base, srom->reg_offset,
			    ARRAY_SIZE(exynos_srom_offsets));
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id of_exynos_srom_ids[] = अणु
	अणु
		.compatible	= "samsung,exynos4210-srom",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(exynos_srom_pm_ops, exynos_srom_suspend, exynos_srom_resume);

अटल काष्ठा platक्रमm_driver exynos_srom_driver = अणु
	.probe = exynos_srom_probe,
	.driver = अणु
		.name = "exynos-srom",
		.of_match_table = of_exynos_srom_ids,
		.pm = &exynos_srom_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(exynos_srom_driver);
