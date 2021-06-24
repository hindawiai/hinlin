<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Match running platक्रमm with pre-defined OPP values क्रम CPUFreq
 *
 * Author: Ajit Pal Singh <ajitpal.singh@st.com>
 *         Lee Jones <lee.jones@linaro.org>
 *
 * Copyright (C) 2015 STMicroelectronics (R&D) Limited
 */

#समावेश <linux/cpu.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regmap.h>

#घोषणा VERSION_ELEMENTS	3
#घोषणा MAX_PCODE_NAME_LEN	7

#घोषणा VERSION_SHIFT		28
#घोषणा HW_INFO_INDEX		1
#घोषणा MAJOR_ID_INDEX		1
#घोषणा MINOR_ID_INDEX		2

/*
 * Only match on "suitable for ALL versions" entries
 *
 * This will be used with the BIT() macro.  It sets the
 * top bit of a 32bit value and is equal to 0x80000000.
 */
#घोषणा DEFAULT_VERSION		31

क्रमागत अणु
	PCODE = 0,
	SUBSTRATE,
	DVFS_MAX_REGFIELDS,
पूर्ण;

/**
 * काष्ठा sti_cpufreq_ddata - ST CPUFreq Driver Data
 *
 * @cpu:		CPU's OF node
 * @syscfg_eng:		Engineering Syscon रेजिस्टर map
 * @syscfg:		Syscon रेजिस्टर map
 */
अटल काष्ठा sti_cpufreq_ddata अणु
	काष्ठा device *cpu;
	काष्ठा regmap *syscfg_eng;
	काष्ठा regmap *syscfg;
पूर्ण ddata;

अटल पूर्णांक sti_cpufreq_fetch_major(व्योम) अणु
	काष्ठा device_node *np = ddata.cpu->of_node;
	काष्ठा device *dev = ddata.cpu;
	अचिन्हित पूर्णांक major_offset;
	अचिन्हित पूर्णांक socid;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32_index(np, "st,syscfg",
					 MAJOR_ID_INDEX, &major_offset);
	अगर (ret) अणु
		dev_err(dev, "No major number offset provided in %pOF [%d]\n",
			np, ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(ddata.syscfg, major_offset, &socid);
	अगर (ret) अणु
		dev_err(dev, "Failed to read major number from syscon [%d]\n",
			ret);
		वापस ret;
	पूर्ण

	वापस ((socid >> VERSION_SHIFT) & 0xf) + 1;
पूर्ण

अटल पूर्णांक sti_cpufreq_fetch_minor(व्योम)
अणु
	काष्ठा device *dev = ddata.cpu;
	काष्ठा device_node *np = dev->of_node;
	अचिन्हित पूर्णांक minor_offset;
	अचिन्हित पूर्णांक minid;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32_index(np, "st,syscfg-eng",
					 MINOR_ID_INDEX, &minor_offset);
	अगर (ret) अणु
		dev_err(dev,
			"No minor number offset provided %pOF [%d]\n",
			np, ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(ddata.syscfg_eng, minor_offset, &minid);
	अगर (ret) अणु
		dev_err(dev,
			"Failed to read the minor number from syscon [%d]\n",
			ret);
		वापस ret;
	पूर्ण

	वापस minid & 0xf;
पूर्ण

अटल पूर्णांक sti_cpufreq_fetch_regmap_field(स्थिर काष्ठा reg_field *reg_fields,
					  पूर्णांक hw_info_offset, पूर्णांक field)
अणु
	काष्ठा regmap_field *regmap_field;
	काष्ठा reg_field reg_field = reg_fields[field];
	काष्ठा device *dev = ddata.cpu;
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	reg_field.reg = hw_info_offset;
	regmap_field = devm_regmap_field_alloc(dev,
					       ddata.syscfg_eng,
					       reg_field);
	अगर (IS_ERR(regmap_field)) अणु
		dev_err(dev, "Failed to allocate reg field\n");
		वापस PTR_ERR(regmap_field);
	पूर्ण

	ret = regmap_field_पढ़ो(regmap_field, &value);
	अगर (ret) अणु
		dev_err(dev, "Failed to read %s code\n",
			field ? "SUBSTRATE" : "PCODE");
		वापस ret;
	पूर्ण

	वापस value;
पूर्ण

अटल स्थिर काष्ठा reg_field sti_stih407_dvfs_regfields[DVFS_MAX_REGFIELDS] = अणु
	[PCODE]		= REG_FIELD(0, 16, 19),
	[SUBSTRATE]	= REG_FIELD(0, 0, 2),
पूर्ण;

अटल स्थिर काष्ठा reg_field *sti_cpufreq_match(व्योम)
अणु
	अगर (of_machine_is_compatible("st,stih407") ||
	    of_machine_is_compatible("st,stih410") ||
	    of_machine_is_compatible("st,stih418"))
		वापस sti_stih407_dvfs_regfields;

	वापस शून्य;
पूर्ण

अटल पूर्णांक sti_cpufreq_set_opp_info(व्योम)
अणु
	काष्ठा device *dev = ddata.cpu;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा reg_field *reg_fields;
	अचिन्हित पूर्णांक hw_info_offset;
	अचिन्हित पूर्णांक version[VERSION_ELEMENTS];
	पूर्णांक pcode, substrate, major, minor;
	पूर्णांक ret;
	अक्षर name[MAX_PCODE_NAME_LEN];
	काष्ठा opp_table *opp_table;

	reg_fields = sti_cpufreq_match();
	अगर (!reg_fields) अणु
		dev_err(dev, "This SoC doesn't support voltage scaling\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(np, "st,syscfg-eng",
					 HW_INFO_INDEX, &hw_info_offset);
	अगर (ret) अणु
		dev_warn(dev, "Failed to read HW info offset from DT\n");
		substrate = DEFAULT_VERSION;
		pcode = 0;
		जाओ use_शेषs;
	पूर्ण

	pcode = sti_cpufreq_fetch_regmap_field(reg_fields,
					       hw_info_offset,
					       PCODE);
	अगर (pcode < 0) अणु
		dev_warn(dev, "Failed to obtain process code\n");
		/* Use शेष pcode */
		pcode = 0;
	पूर्ण

	substrate = sti_cpufreq_fetch_regmap_field(reg_fields,
						   hw_info_offset,
						   SUBSTRATE);
	अगर (substrate) अणु
		dev_warn(dev, "Failed to obtain substrate code\n");
		/* Use शेष substrate */
		substrate = DEFAULT_VERSION;
	पूर्ण

use_शेषs:
	major = sti_cpufreq_fetch_major();
	अगर (major < 0) अणु
		dev_err(dev, "Failed to obtain major version\n");
		/* Use शेष major number */
		major = DEFAULT_VERSION;
	पूर्ण

	minor = sti_cpufreq_fetch_minor();
	अगर (minor < 0) अणु
		dev_err(dev, "Failed to obtain minor version\n");
		/* Use शेष minor number */
		minor = DEFAULT_VERSION;
	पूर्ण

	snम_लिखो(name, MAX_PCODE_NAME_LEN, "pcode%d", pcode);

	opp_table = dev_pm_opp_set_prop_name(dev, name);
	अगर (IS_ERR(opp_table)) अणु
		dev_err(dev, "Failed to set prop name\n");
		वापस PTR_ERR(opp_table);
	पूर्ण

	version[0] = BIT(major);
	version[1] = BIT(minor);
	version[2] = BIT(substrate);

	opp_table = dev_pm_opp_set_supported_hw(dev, version, VERSION_ELEMENTS);
	अगर (IS_ERR(opp_table)) अणु
		dev_err(dev, "Failed to set supported hardware\n");
		ret = PTR_ERR(opp_table);
		जाओ err_put_prop_name;
	पूर्ण

	dev_dbg(dev, "pcode: %d major: %d minor: %d substrate: %d\n",
		pcode, major, minor, substrate);
	dev_dbg(dev, "version[0]: %x version[1]: %x version[2]: %x\n",
		version[0], version[1], version[2]);

	वापस 0;

err_put_prop_name:
	dev_pm_opp_put_prop_name(opp_table);
	वापस ret;
पूर्ण

अटल पूर्णांक sti_cpufreq_fetch_syscon_रेजिस्टरs(व्योम)
अणु
	काष्ठा device *dev = ddata.cpu;
	काष्ठा device_node *np = dev->of_node;

	ddata.syscfg = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(ddata.syscfg)) अणु
		dev_err(dev,  "\"st,syscfg\" not supplied\n");
		वापस PTR_ERR(ddata.syscfg);
	पूर्ण

	ddata.syscfg_eng = syscon_regmap_lookup_by_phandle(np, "st,syscfg-eng");
	अगर (IS_ERR(ddata.syscfg_eng)) अणु
		dev_err(dev, "\"st,syscfg-eng\" not supplied\n");
		वापस PTR_ERR(ddata.syscfg_eng);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sti_cpufreq_init(व्योम)
अणु
	पूर्णांक ret;

	अगर ((!of_machine_is_compatible("st,stih407")) &&
		(!of_machine_is_compatible("st,stih410")) &&
		(!of_machine_is_compatible("st,stih418")))
		वापस -ENODEV;

	ddata.cpu = get_cpu_device(0);
	अगर (!ddata.cpu) अणु
		dev_err(ddata.cpu, "Failed to get device for CPU0\n");
		जाओ skip_voltage_scaling;
	पूर्ण

	अगर (!of_get_property(ddata.cpu->of_node, "operating-points-v2", शून्य)) अणु
		dev_err(ddata.cpu, "OPP-v2 not supported\n");
		जाओ skip_voltage_scaling;
	पूर्ण

	ret = sti_cpufreq_fetch_syscon_रेजिस्टरs();
	अगर (ret)
		जाओ skip_voltage_scaling;

	ret = sti_cpufreq_set_opp_info();
	अगर (!ret)
		जाओ रेजिस्टर_cpufreq_dt;

skip_voltage_scaling:
	dev_err(ddata.cpu, "Not doing voltage scaling\n");

रेजिस्टर_cpufreq_dt:
	platक्रमm_device_रेजिस्टर_simple("cpufreq-dt", -1, शून्य, 0);

	वापस 0;
पूर्ण
module_init(sti_cpufreq_init);

अटल स्थिर काष्ठा of_device_id __maybe_unused sti_cpufreq_of_match[] = अणु
	अणु .compatible = "st,stih407" पूर्ण,
	अणु .compatible = "st,stih410" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sti_cpufreq_of_match);

MODULE_DESCRIPTION("STMicroelectronics CPUFreq/OPP driver");
MODULE_AUTHOR("Ajitpal Singh <ajitpal.singh@st.com>");
MODULE_AUTHOR("Lee Jones <lee.jones@linaro.org>");
MODULE_LICENSE("GPL v2");
