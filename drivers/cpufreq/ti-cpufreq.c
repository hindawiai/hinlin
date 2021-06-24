<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI CPUFreq/OPP hw-supported driver
 *
 * Copyright (C) 2016-2017 Texas Instruments, Inc.
 *	 Dave Gerlach <d-gerlach@ti.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा REVISION_MASK				0xF
#घोषणा REVISION_SHIFT				28

#घोषणा AM33XX_800M_ARM_MPU_MAX_FREQ		0x1E2F
#घोषणा AM43XX_600M_ARM_MPU_MAX_FREQ		0xFFA

#घोषणा DRA7_EFUSE_HAS_OD_MPU_OPP		11
#घोषणा DRA7_EFUSE_HAS_HIGH_MPU_OPP		15
#घोषणा DRA76_EFUSE_HAS_PLUS_MPU_OPP		18
#घोषणा DRA7_EFUSE_HAS_ALL_MPU_OPP		23
#घोषणा DRA76_EFUSE_HAS_ALL_MPU_OPP		24

#घोषणा DRA7_EFUSE_NOM_MPU_OPP			BIT(0)
#घोषणा DRA7_EFUSE_OD_MPU_OPP			BIT(1)
#घोषणा DRA7_EFUSE_HIGH_MPU_OPP			BIT(2)
#घोषणा DRA76_EFUSE_PLUS_MPU_OPP		BIT(3)

#घोषणा OMAP3_CONTROL_DEVICE_STATUS		0x4800244C
#घोषणा OMAP3_CONTROL_IDCODE			0x4830A204
#घोषणा OMAP34xx_ProdID_SKUID			0x4830A20C
#घोषणा OMAP3_SYSCON_BASE	(0x48000000 + 0x2000 + 0x270)

#घोषणा VERSION_COUNT				2

काष्ठा ti_cpufreq_data;

काष्ठा ti_cpufreq_soc_data अणु
	स्थिर अक्षर * स्थिर *reg_names;
	अचिन्हित दीर्घ (*efuse_xlate)(काष्ठा ti_cpufreq_data *opp_data,
				     अचिन्हित दीर्घ efuse);
	अचिन्हित दीर्घ efuse_fallback;
	अचिन्हित दीर्घ efuse_offset;
	अचिन्हित दीर्घ efuse_mask;
	अचिन्हित दीर्घ efuse_shअगरt;
	अचिन्हित दीर्घ rev_offset;
	bool multi_regulator;
पूर्ण;

काष्ठा ti_cpufreq_data अणु
	काष्ठा device *cpu_dev;
	काष्ठा device_node *opp_node;
	काष्ठा regmap *syscon;
	स्थिर काष्ठा ti_cpufreq_soc_data *soc_data;
	काष्ठा opp_table *opp_table;
पूर्ण;

अटल अचिन्हित दीर्घ amx3_efuse_xlate(काष्ठा ti_cpufreq_data *opp_data,
				      अचिन्हित दीर्घ efuse)
अणु
	अगर (!efuse)
		efuse = opp_data->soc_data->efuse_fallback;
	/* AM335x and AM437x use "OPP disable" bits, so invert */
	वापस ~efuse;
पूर्ण

अटल अचिन्हित दीर्घ dra7_efuse_xlate(काष्ठा ti_cpufreq_data *opp_data,
				      अचिन्हित दीर्घ efuse)
अणु
	अचिन्हित दीर्घ calculated_efuse = DRA7_EFUSE_NOM_MPU_OPP;

	/*
	 * The efuse on dra7 and am57 parts contains a specअगरic
	 * value indicating the highest available OPP.
	 */

	चयन (efuse) अणु
	हाल DRA76_EFUSE_HAS_PLUS_MPU_OPP:
	हाल DRA76_EFUSE_HAS_ALL_MPU_OPP:
		calculated_efuse |= DRA76_EFUSE_PLUS_MPU_OPP;
		fallthrough;
	हाल DRA7_EFUSE_HAS_ALL_MPU_OPP:
	हाल DRA7_EFUSE_HAS_HIGH_MPU_OPP:
		calculated_efuse |= DRA7_EFUSE_HIGH_MPU_OPP;
		fallthrough;
	हाल DRA7_EFUSE_HAS_OD_MPU_OPP:
		calculated_efuse |= DRA7_EFUSE_OD_MPU_OPP;
	पूर्ण

	वापस calculated_efuse;
पूर्ण

अटल अचिन्हित दीर्घ omap3_efuse_xlate(काष्ठा ti_cpufreq_data *opp_data,
				      अचिन्हित दीर्घ efuse)
अणु
	/* OPP enable bit ("Speed Binned") */
	वापस BIT(efuse);
पूर्ण

अटल काष्ठा ti_cpufreq_soc_data am3x_soc_data = अणु
	.efuse_xlate = amx3_efuse_xlate,
	.efuse_fallback = AM33XX_800M_ARM_MPU_MAX_FREQ,
	.efuse_offset = 0x07fc,
	.efuse_mask = 0x1fff,
	.rev_offset = 0x600,
	.multi_regulator = false,
पूर्ण;

अटल काष्ठा ti_cpufreq_soc_data am4x_soc_data = अणु
	.efuse_xlate = amx3_efuse_xlate,
	.efuse_fallback = AM43XX_600M_ARM_MPU_MAX_FREQ,
	.efuse_offset = 0x0610,
	.efuse_mask = 0x3f,
	.rev_offset = 0x600,
	.multi_regulator = false,
पूर्ण;

अटल काष्ठा ti_cpufreq_soc_data dra7_soc_data = अणु
	.efuse_xlate = dra7_efuse_xlate,
	.efuse_offset = 0x020c,
	.efuse_mask = 0xf80000,
	.efuse_shअगरt = 19,
	.rev_offset = 0x204,
	.multi_regulator = true,
पूर्ण;

/*
 * OMAP35x TRM (SPRUF98K):
 *  CONTROL_IDCODE (0x4830 A204) describes Silicon revisions.
 *  Control OMAP Status Register 15:0 (Address 0x4800 244C)
 *    to separate between omap3503, omap3515, omap3525, omap3530
 *    and feature presence.
 *    There are encodings क्रम versions limited to 400/266MHz
 *    but we ignore.
 *    Not clear अगर this also holds क्रम omap34xx.
 *  some eFuse values e.g. CONTROL_FUSE_OPP1_VDD1
 *    are stored in the SYSCON रेजिस्टर range
 *  Register 0x4830A20C [ProdID.SKUID] [0:3]
 *    0x0 क्रम normal 600/430MHz device.
 *    0x8 क्रम 720/520MHz device.
 *    Not clear what omap34xx value is.
 */

अटल काष्ठा ti_cpufreq_soc_data omap34xx_soc_data = अणु
	.efuse_xlate = omap3_efuse_xlate,
	.efuse_offset = OMAP34xx_ProdID_SKUID - OMAP3_SYSCON_BASE,
	.efuse_shअगरt = 3,
	.efuse_mask = BIT(3),
	.rev_offset = OMAP3_CONTROL_IDCODE - OMAP3_SYSCON_BASE,
	.multi_regulator = false,
पूर्ण;

/*
 * AM/DM37x TRM (SPRUGN4M)
 *  CONTROL_IDCODE (0x4830 A204) describes Silicon revisions.
 *  Control Device Status Register 15:0 (Address 0x4800 244C)
 *    to separate between am3703, am3715, dm3725, dm3730
 *    and feature presence.
 *   Speed Binned = Bit 9
 *     0 800/600 MHz
 *     1 1000/800 MHz
 *  some eFuse values e.g. CONTROL_FUSE_OPP 1G_VDD1
 *    are stored in the SYSCON रेजिस्टर range.
 *  There is no 0x4830A20C [ProdID.SKUID] रेजिस्टर (exists but
 *    seems to always पढ़ो as 0).
 */

अटल स्थिर अक्षर * स्थिर omap3_reg_names[] = अणु"cpu0", "vbb"पूर्ण;

अटल काष्ठा ti_cpufreq_soc_data omap36xx_soc_data = अणु
	.reg_names = omap3_reg_names,
	.efuse_xlate = omap3_efuse_xlate,
	.efuse_offset = OMAP3_CONTROL_DEVICE_STATUS - OMAP3_SYSCON_BASE,
	.efuse_shअगरt = 9,
	.efuse_mask = BIT(9),
	.rev_offset = OMAP3_CONTROL_IDCODE - OMAP3_SYSCON_BASE,
	.multi_regulator = true,
पूर्ण;

/*
 * AM3517 is quite similar to AM/DM37x except that it has no
 * high speed grade eFuse and no abb lकरो
 */

अटल काष्ठा ti_cpufreq_soc_data am3517_soc_data = अणु
	.efuse_xlate = omap3_efuse_xlate,
	.efuse_offset = OMAP3_CONTROL_DEVICE_STATUS - OMAP3_SYSCON_BASE,
	.efuse_shअगरt = 0,
	.efuse_mask = 0,
	.rev_offset = OMAP3_CONTROL_IDCODE - OMAP3_SYSCON_BASE,
	.multi_regulator = false,
पूर्ण;


/**
 * ti_cpufreq_get_efuse() - Parse and वापस efuse value present on SoC
 * @opp_data: poपूर्णांकer to ti_cpufreq_data context
 * @efuse_value: Set to the value parsed from efuse
 *
 * Returns error code अगर efuse not पढ़ो properly.
 */
अटल पूर्णांक ti_cpufreq_get_efuse(काष्ठा ti_cpufreq_data *opp_data,
				u32 *efuse_value)
अणु
	काष्ठा device *dev = opp_data->cpu_dev;
	u32 efuse;
	पूर्णांक ret;

	ret = regmap_पढ़ो(opp_data->syscon, opp_data->soc_data->efuse_offset,
			  &efuse);
	अगर (ret == -EIO) अणु
		/* not a syscon रेजिस्टर! */
		व्योम __iomem *regs = ioremap(OMAP3_SYSCON_BASE +
				opp_data->soc_data->efuse_offset, 4);

		अगर (!regs)
			वापस -ENOMEM;
		efuse = पढ़ोl(regs);
		iounmap(regs);
		पूर्ण
	अन्यथा अगर (ret) अणु
		dev_err(dev,
			"Failed to read the efuse value from syscon: %d\n",
			ret);
		वापस ret;
	पूर्ण

	efuse = (efuse & opp_data->soc_data->efuse_mask);
	efuse >>= opp_data->soc_data->efuse_shअगरt;

	*efuse_value = opp_data->soc_data->efuse_xlate(opp_data, efuse);

	वापस 0;
पूर्ण

/**
 * ti_cpufreq_get_rev() - Parse and वापस rev value present on SoC
 * @opp_data: poपूर्णांकer to ti_cpufreq_data context
 * @revision_value: Set to the value parsed from revision रेजिस्टर
 *
 * Returns error code अगर revision not पढ़ो properly.
 */
अटल पूर्णांक ti_cpufreq_get_rev(काष्ठा ti_cpufreq_data *opp_data,
			      u32 *revision_value)
अणु
	काष्ठा device *dev = opp_data->cpu_dev;
	u32 revision;
	पूर्णांक ret;

	ret = regmap_पढ़ो(opp_data->syscon, opp_data->soc_data->rev_offset,
			  &revision);
	अगर (ret == -EIO) अणु
		/* not a syscon रेजिस्टर! */
		व्योम __iomem *regs = ioremap(OMAP3_SYSCON_BASE +
				opp_data->soc_data->rev_offset, 4);

		अगर (!regs)
			वापस -ENOMEM;
		revision = पढ़ोl(regs);
		iounmap(regs);
		पूर्ण
	अन्यथा अगर (ret) अणु
		dev_err(dev,
			"Failed to read the revision number from syscon: %d\n",
			ret);
		वापस ret;
	पूर्ण

	*revision_value = BIT((revision >> REVISION_SHIFT) & REVISION_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक ti_cpufreq_setup_syscon_रेजिस्टर(काष्ठा ti_cpufreq_data *opp_data)
अणु
	काष्ठा device *dev = opp_data->cpu_dev;
	काष्ठा device_node *np = opp_data->opp_node;

	opp_data->syscon = syscon_regmap_lookup_by_phandle(np,
							"syscon");
	अगर (IS_ERR(opp_data->syscon)) अणु
		dev_err(dev,
			"\"syscon\" is missing, cannot use OPPv2 table.\n");
		वापस PTR_ERR(opp_data->syscon);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_cpufreq_of_match[] = अणु
	अणु .compatible = "ti,am33xx", .data = &am3x_soc_data, पूर्ण,
	अणु .compatible = "ti,am3517", .data = &am3517_soc_data, पूर्ण,
	अणु .compatible = "ti,am43", .data = &am4x_soc_data, पूर्ण,
	अणु .compatible = "ti,dra7", .data = &dra7_soc_data पूर्ण,
	अणु .compatible = "ti,omap34xx", .data = &omap34xx_soc_data, पूर्ण,
	अणु .compatible = "ti,omap36xx", .data = &omap36xx_soc_data, पूर्ण,
	/* legacy */
	अणु .compatible = "ti,omap3430", .data = &omap34xx_soc_data, पूर्ण,
	अणु .compatible = "ti,omap3630", .data = &omap36xx_soc_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id *ti_cpufreq_match_node(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;

	np = of_find_node_by_path("/");
	match = of_match_node(ti_cpufreq_of_match, np);
	of_node_put(np);

	वापस match;
पूर्ण

अटल पूर्णांक ti_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 version[VERSION_COUNT];
	स्थिर काष्ठा of_device_id *match;
	काष्ठा opp_table *ti_opp_table;
	काष्ठा ti_cpufreq_data *opp_data;
	स्थिर अक्षर * स्थिर शेष_reg_names[] = अणु"vdd", "vbb"पूर्ण;
	पूर्णांक ret;

	match = dev_get_platdata(&pdev->dev);
	अगर (!match)
		वापस -ENODEV;

	opp_data = devm_kzalloc(&pdev->dev, माप(*opp_data), GFP_KERNEL);
	अगर (!opp_data)
		वापस -ENOMEM;

	opp_data->soc_data = match->data;

	opp_data->cpu_dev = get_cpu_device(0);
	अगर (!opp_data->cpu_dev) अणु
		pr_err("%s: Failed to get device for CPU0\n", __func__);
		वापस -ENODEV;
	पूर्ण

	opp_data->opp_node = dev_pm_opp_of_get_opp_desc_node(opp_data->cpu_dev);
	अगर (!opp_data->opp_node) अणु
		dev_info(opp_data->cpu_dev,
			 "OPP-v2 not supported, cpufreq-dt will attempt to use legacy tables.\n");
		जाओ रेजिस्टर_cpufreq_dt;
	पूर्ण

	ret = ti_cpufreq_setup_syscon_रेजिस्टर(opp_data);
	अगर (ret)
		जाओ fail_put_node;

	/*
	 * OPPs determine whether or not they are supported based on
	 * two metrics:
	 *	0 - SoC Revision
	 *	1 - eFuse value
	 */
	ret = ti_cpufreq_get_rev(opp_data, &version[0]);
	अगर (ret)
		जाओ fail_put_node;

	ret = ti_cpufreq_get_efuse(opp_data, &version[1]);
	अगर (ret)
		जाओ fail_put_node;

	ti_opp_table = dev_pm_opp_set_supported_hw(opp_data->cpu_dev,
						   version, VERSION_COUNT);
	अगर (IS_ERR(ti_opp_table)) अणु
		dev_err(opp_data->cpu_dev,
			"Failed to set supported hardware\n");
		ret = PTR_ERR(ti_opp_table);
		जाओ fail_put_node;
	पूर्ण

	opp_data->opp_table = ti_opp_table;

	अगर (opp_data->soc_data->multi_regulator) अणु
		स्थिर अक्षर * स्थिर *reg_names = शेष_reg_names;

		अगर (opp_data->soc_data->reg_names)
			reg_names = opp_data->soc_data->reg_names;
		ti_opp_table = dev_pm_opp_set_regulators(opp_data->cpu_dev,
							 reg_names,
							 ARRAY_SIZE(शेष_reg_names));
		अगर (IS_ERR(ti_opp_table)) अणु
			dev_pm_opp_put_supported_hw(opp_data->opp_table);
			ret =  PTR_ERR(ti_opp_table);
			जाओ fail_put_node;
		पूर्ण
	पूर्ण

	of_node_put(opp_data->opp_node);
रेजिस्टर_cpufreq_dt:
	platक्रमm_device_रेजिस्टर_simple("cpufreq-dt", -1, शून्य, 0);

	वापस 0;

fail_put_node:
	of_node_put(opp_data->opp_node);

	वापस ret;
पूर्ण

अटल पूर्णांक ti_cpufreq_init(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;

	/* Check to ensure we are on a compatible platक्रमm */
	match = ti_cpufreq_match_node();
	अगर (match)
		platक्रमm_device_रेजिस्टर_data(शून्य, "ti-cpufreq", -1, match,
					      माप(*match));

	वापस 0;
पूर्ण
module_init(ti_cpufreq_init);

अटल काष्ठा platक्रमm_driver ti_cpufreq_driver = अणु
	.probe = ti_cpufreq_probe,
	.driver = अणु
		.name = "ti-cpufreq",
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ti_cpufreq_driver);

MODULE_DESCRIPTION("TI CPUFreq/OPP hw-supported driver");
MODULE_AUTHOR("Dave Gerlach <d-gerlach@ti.com>");
MODULE_LICENSE("GPL v2");
