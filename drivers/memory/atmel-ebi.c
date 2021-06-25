<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * EBI driver क्रम Aपंचांगel chips
 * inspired by the fsl weim bus driver
 *
 * Copyright (C) 2013 Jean-Jacques Hiblot <jjhiblot@traphandler.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/aपंचांगel-matrix.h>
#समावेश <linux/mfd/syscon/aपंचांगel-smc.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <soc/at91/aपंचांगel-sfr.h>

#घोषणा AT91_EBI_NUM_CS		8

काष्ठा aपंचांगel_ebi_dev_config अणु
	पूर्णांक cs;
	काष्ठा aपंचांगel_smc_cs_conf smcconf;
पूर्ण;

काष्ठा aपंचांगel_ebi;

काष्ठा aपंचांगel_ebi_dev अणु
	काष्ठा list_head node;
	काष्ठा aपंचांगel_ebi *ebi;
	u32 mode;
	पूर्णांक numcs;
	काष्ठा aपंचांगel_ebi_dev_config configs[];
पूर्ण;

काष्ठा aपंचांगel_ebi_caps अणु
	अचिन्हित पूर्णांक available_cs;
	अचिन्हित पूर्णांक ebi_csa_offs;
	स्थिर अक्षर *regmap_name;
	व्योम (*get_config)(काष्ठा aपंचांगel_ebi_dev *ebid,
			   काष्ठा aपंचांगel_ebi_dev_config *conf);
	पूर्णांक (*xlate_config)(काष्ठा aपंचांगel_ebi_dev *ebid,
			    काष्ठा device_node *configs_np,
			    काष्ठा aपंचांगel_ebi_dev_config *conf);
	व्योम (*apply_config)(काष्ठा aपंचांगel_ebi_dev *ebid,
			     काष्ठा aपंचांगel_ebi_dev_config *conf);
पूर्ण;

काष्ठा aपंचांगel_ebi अणु
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;
	काष्ठा  अणु
		काष्ठा regmap *regmap;
		काष्ठा clk *clk;
		स्थिर काष्ठा aपंचांगel_hsmc_reg_layout *layout;
	पूर्ण smc;

	काष्ठा device *dev;
	स्थिर काष्ठा aपंचांगel_ebi_caps *caps;
	काष्ठा list_head devs;
पूर्ण;

काष्ठा aपंचांगel_smc_timing_xlate अणु
	स्थिर अक्षर *name;
	पूर्णांक (*converter)(काष्ठा aपंचांगel_smc_cs_conf *conf,
			 अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक nycles);
	अचिन्हित पूर्णांक shअगरt;
पूर्ण;

#घोषणा ATMEL_SMC_SETUP_XLATE(nm, pos)	\
	अणु .name = nm, .converter = aपंचांगel_smc_cs_conf_set_setup, .shअगरt = posपूर्ण

#घोषणा ATMEL_SMC_PULSE_XLATE(nm, pos)	\
	अणु .name = nm, .converter = aपंचांगel_smc_cs_conf_set_pulse, .shअगरt = posपूर्ण

#घोषणा ATMEL_SMC_CYCLE_XLATE(nm, pos)	\
	अणु .name = nm, .converter = aपंचांगel_smc_cs_conf_set_cycle, .shअगरt = posपूर्ण

अटल व्योम at91sam9_ebi_get_config(काष्ठा aपंचांगel_ebi_dev *ebid,
				    काष्ठा aपंचांगel_ebi_dev_config *conf)
अणु
	aपंचांगel_smc_cs_conf_get(ebid->ebi->smc.regmap, conf->cs,
			      &conf->smcconf);
पूर्ण

अटल व्योम sama5_ebi_get_config(काष्ठा aपंचांगel_ebi_dev *ebid,
				 काष्ठा aपंचांगel_ebi_dev_config *conf)
अणु
	aपंचांगel_hsmc_cs_conf_get(ebid->ebi->smc.regmap, ebid->ebi->smc.layout,
			       conf->cs, &conf->smcconf);
पूर्ण

अटल स्थिर काष्ठा aपंचांगel_smc_timing_xlate timings_xlate_table[] = अणु
	ATMEL_SMC_SETUP_XLATE("atmel,smc-ncs-rd-setup-ns",
			      ATMEL_SMC_NCS_RD_SHIFT),
	ATMEL_SMC_SETUP_XLATE("atmel,smc-ncs-wr-setup-ns",
			      ATMEL_SMC_NCS_WR_SHIFT),
	ATMEL_SMC_SETUP_XLATE("atmel,smc-nrd-setup-ns", ATMEL_SMC_NRD_SHIFT),
	ATMEL_SMC_SETUP_XLATE("atmel,smc-nwe-setup-ns", ATMEL_SMC_NWE_SHIFT),
	ATMEL_SMC_PULSE_XLATE("atmel,smc-ncs-rd-pulse-ns",
			      ATMEL_SMC_NCS_RD_SHIFT),
	ATMEL_SMC_PULSE_XLATE("atmel,smc-ncs-wr-pulse-ns",
			      ATMEL_SMC_NCS_WR_SHIFT),
	ATMEL_SMC_PULSE_XLATE("atmel,smc-nrd-pulse-ns", ATMEL_SMC_NRD_SHIFT),
	ATMEL_SMC_PULSE_XLATE("atmel,smc-nwe-pulse-ns", ATMEL_SMC_NWE_SHIFT),
	ATMEL_SMC_CYCLE_XLATE("atmel,smc-nrd-cycle-ns", ATMEL_SMC_NRD_SHIFT),
	ATMEL_SMC_CYCLE_XLATE("atmel,smc-nwe-cycle-ns", ATMEL_SMC_NWE_SHIFT),
पूर्ण;

अटल पूर्णांक aपंचांगel_ebi_xslate_smc_timings(काष्ठा aपंचांगel_ebi_dev *ebid,
					काष्ठा device_node *np,
					काष्ठा aपंचांगel_smc_cs_conf *smcconf)
अणु
	अचिन्हित पूर्णांक clk_rate = clk_get_rate(ebid->ebi->clk);
	अचिन्हित पूर्णांक clk_period_ns = NSEC_PER_SEC / clk_rate;
	bool required = false;
	अचिन्हित पूर्णांक ncycles;
	पूर्णांक ret, i;
	u32 val;

	ret = of_property_पढ़ो_u32(np, "atmel,smc-tdf-ns", &val);
	अगर (!ret) अणु
		required = true;
		ncycles = DIV_ROUND_UP(val, clk_period_ns);
		अगर (ncycles > ATMEL_SMC_MODE_TDF_MAX) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (ncycles < ATMEL_SMC_MODE_TDF_MIN)
			ncycles = ATMEL_SMC_MODE_TDF_MIN;

		smcconf->mode |= ATMEL_SMC_MODE_TDF(ncycles);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(timings_xlate_table); i++) अणु
		स्थिर काष्ठा aपंचांगel_smc_timing_xlate *xlate;

		xlate = &timings_xlate_table[i];

		ret = of_property_पढ़ो_u32(np, xlate->name, &val);
		अगर (ret) अणु
			अगर (!required)
				जारी;
			अन्यथा
				अवरोध;
		पूर्ण

		अगर (!required) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ncycles = DIV_ROUND_UP(val, clk_period_ns);
		ret = xlate->converter(smcconf, xlate->shअगरt, ncycles);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	अगर (ret) अणु
		dev_err(ebid->ebi->dev,
			"missing or invalid timings definition in %pOF",
			np);
		वापस ret;
	पूर्ण

	वापस required;
पूर्ण

अटल पूर्णांक aपंचांगel_ebi_xslate_smc_config(काष्ठा aपंचांगel_ebi_dev *ebid,
				       काष्ठा device_node *np,
				       काष्ठा aपंचांगel_ebi_dev_config *conf)
अणु
	काष्ठा aपंचांगel_smc_cs_conf *smcconf = &conf->smcconf;
	bool required = false;
	स्थिर अक्षर *पंचांगp_str;
	u32 पंचांगp;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "atmel,smc-bus-width", &पंचांगp);
	अगर (!ret) अणु
		चयन (पंचांगp) अणु
		हाल 8:
			smcconf->mode |= ATMEL_SMC_MODE_DBW_8;
			अवरोध;

		हाल 16:
			smcconf->mode |= ATMEL_SMC_MODE_DBW_16;
			अवरोध;

		हाल 32:
			smcconf->mode |= ATMEL_SMC_MODE_DBW_32;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

		required = true;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "atmel,smc-tdf-optimized")) अणु
		smcconf->mode |= ATMEL_SMC_MODE_TDFMODE_OPTIMIZED;
		required = true;
	पूर्ण

	पंचांगp_str = शून्य;
	of_property_पढ़ो_string(np, "atmel,smc-byte-access-type", &पंचांगp_str);
	अगर (पंचांगp_str && !म_भेद(पंचांगp_str, "write")) अणु
		smcconf->mode |= ATMEL_SMC_MODE_BAT_WRITE;
		required = true;
	पूर्ण

	पंचांगp_str = शून्य;
	of_property_पढ़ो_string(np, "atmel,smc-read-mode", &पंचांगp_str);
	अगर (पंचांगp_str && !म_भेद(पंचांगp_str, "nrd")) अणु
		smcconf->mode |= ATMEL_SMC_MODE_READMODE_NRD;
		required = true;
	पूर्ण

	पंचांगp_str = शून्य;
	of_property_पढ़ो_string(np, "atmel,smc-write-mode", &पंचांगp_str);
	अगर (पंचांगp_str && !म_भेद(पंचांगp_str, "nwe")) अणु
		smcconf->mode |= ATMEL_SMC_MODE_WRITEMODE_NWE;
		required = true;
	पूर्ण

	पंचांगp_str = शून्य;
	of_property_पढ़ो_string(np, "atmel,smc-exnw-mode", &पंचांगp_str);
	अगर (पंचांगp_str) अणु
		अगर (!म_भेद(पंचांगp_str, "frozen"))
			smcconf->mode |= ATMEL_SMC_MODE_EXNWMODE_FROZEN;
		अन्यथा अगर (!म_भेद(पंचांगp_str, "ready"))
			smcconf->mode |= ATMEL_SMC_MODE_EXNWMODE_READY;
		अन्यथा अगर (म_भेद(पंचांगp_str, "disabled"))
			वापस -EINVAL;

		required = true;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "atmel,smc-page-mode", &पंचांगp);
	अगर (!ret) अणु
		चयन (पंचांगp) अणु
		हाल 4:
			smcconf->mode |= ATMEL_SMC_MODE_PS_4;
			अवरोध;

		हाल 8:
			smcconf->mode |= ATMEL_SMC_MODE_PS_8;
			अवरोध;

		हाल 16:
			smcconf->mode |= ATMEL_SMC_MODE_PS_16;
			अवरोध;

		हाल 32:
			smcconf->mode |= ATMEL_SMC_MODE_PS_32;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

		smcconf->mode |= ATMEL_SMC_MODE_PMEN;
		required = true;
	पूर्ण

	ret = aपंचांगel_ebi_xslate_smc_timings(ebid, np, &conf->smcconf);
	अगर (ret < 0)
		वापस -EINVAL;

	अगर ((ret > 0 && !required) || (!ret && required)) अणु
		dev_err(ebid->ebi->dev, "missing atmel,smc- properties in %pOF",
			np);
		वापस -EINVAL;
	पूर्ण

	वापस required;
पूर्ण

अटल व्योम at91sam9_ebi_apply_config(काष्ठा aपंचांगel_ebi_dev *ebid,
				      काष्ठा aपंचांगel_ebi_dev_config *conf)
अणु
	aपंचांगel_smc_cs_conf_apply(ebid->ebi->smc.regmap, conf->cs,
				&conf->smcconf);
पूर्ण

अटल व्योम sama5_ebi_apply_config(काष्ठा aपंचांगel_ebi_dev *ebid,
				   काष्ठा aपंचांगel_ebi_dev_config *conf)
अणु
	aपंचांगel_hsmc_cs_conf_apply(ebid->ebi->smc.regmap, ebid->ebi->smc.layout,
				 conf->cs, &conf->smcconf);
पूर्ण

अटल पूर्णांक aपंचांगel_ebi_dev_setup(काष्ठा aपंचांगel_ebi *ebi, काष्ठा device_node *np,
			       पूर्णांक reg_cells)
अणु
	स्थिर काष्ठा aपंचांगel_ebi_caps *caps = ebi->caps;
	काष्ठा aपंचांगel_ebi_dev_config conf = अणु पूर्ण;
	काष्ठा device *dev = ebi->dev;
	काष्ठा aपंचांगel_ebi_dev *ebid;
	अचिन्हित दीर्घ cslines = 0;
	पूर्णांक ret, numcs = 0, nentries, i;
	bool apply = false;
	u32 cs;

	nentries = of_property_count_elems_of_size(np, "reg",
						   reg_cells * माप(u32));
	क्रम (i = 0; i < nentries; i++) अणु
		ret = of_property_पढ़ो_u32_index(np, "reg", i * reg_cells,
						 &cs);
		अगर (ret)
			वापस ret;

		अगर (cs >= AT91_EBI_NUM_CS ||
		    !(ebi->caps->available_cs & BIT(cs))) अणु
			dev_err(dev, "invalid reg property in %pOF\n", np);
			वापस -EINVAL;
		पूर्ण

		अगर (!test_and_set_bit(cs, &cslines))
			numcs++;
	पूर्ण

	अगर (!numcs) अणु
		dev_err(dev, "invalid reg property in %pOF\n", np);
		वापस -EINVAL;
	पूर्ण

	ebid = devm_kzalloc(ebi->dev, काष्ठा_size(ebid, configs, numcs),
			    GFP_KERNEL);
	अगर (!ebid)
		वापस -ENOMEM;

	ebid->ebi = ebi;
	ebid->numcs = numcs;

	ret = caps->xlate_config(ebid, np, &conf);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret)
		apply = true;

	i = 0;
	क्रम_each_set_bit(cs, &cslines, AT91_EBI_NUM_CS) अणु
		ebid->configs[i].cs = cs;

		अगर (apply) अणु
			conf.cs = cs;
			caps->apply_config(ebid, &conf);
		पूर्ण

		caps->get_config(ebid, &ebid->configs[i]);

		/*
		 * Attach the EBI device to the generic SMC logic अगर at least
		 * one "atmel,smc-" property is present.
		 */
		अगर (ebi->caps->ebi_csa_offs && apply)
			regmap_update_bits(ebi->regmap,
					   ebi->caps->ebi_csa_offs,
					   BIT(cs), 0);

		i++;
	पूर्ण

	list_add_tail(&ebid->node, &ebi->devs);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा aपंचांगel_ebi_caps at91sam9260_ebi_caps = अणु
	.available_cs = 0xff,
	.ebi_csa_offs = AT91SAM9260_MATRIX_EBICSA,
	.regmap_name = "atmel,matrix",
	.get_config = at91sam9_ebi_get_config,
	.xlate_config = aपंचांगel_ebi_xslate_smc_config,
	.apply_config = at91sam9_ebi_apply_config,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_ebi_caps at91sam9261_ebi_caps = अणु
	.available_cs = 0xff,
	.ebi_csa_offs = AT91SAM9261_MATRIX_EBICSA,
	.regmap_name = "atmel,matrix",
	.get_config = at91sam9_ebi_get_config,
	.xlate_config = aपंचांगel_ebi_xslate_smc_config,
	.apply_config = at91sam9_ebi_apply_config,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_ebi_caps at91sam9263_ebi0_caps = अणु
	.available_cs = 0x3f,
	.ebi_csa_offs = AT91SAM9263_MATRIX_EBI0CSA,
	.regmap_name = "atmel,matrix",
	.get_config = at91sam9_ebi_get_config,
	.xlate_config = aपंचांगel_ebi_xslate_smc_config,
	.apply_config = at91sam9_ebi_apply_config,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_ebi_caps at91sam9263_ebi1_caps = अणु
	.available_cs = 0x7,
	.ebi_csa_offs = AT91SAM9263_MATRIX_EBI1CSA,
	.regmap_name = "atmel,matrix",
	.get_config = at91sam9_ebi_get_config,
	.xlate_config = aपंचांगel_ebi_xslate_smc_config,
	.apply_config = at91sam9_ebi_apply_config,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_ebi_caps at91sam9rl_ebi_caps = अणु
	.available_cs = 0x3f,
	.ebi_csa_offs = AT91SAM9RL_MATRIX_EBICSA,
	.regmap_name = "atmel,matrix",
	.get_config = at91sam9_ebi_get_config,
	.xlate_config = aपंचांगel_ebi_xslate_smc_config,
	.apply_config = at91sam9_ebi_apply_config,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_ebi_caps at91sam9g45_ebi_caps = अणु
	.available_cs = 0x3f,
	.ebi_csa_offs = AT91SAM9G45_MATRIX_EBICSA,
	.regmap_name = "atmel,matrix",
	.get_config = at91sam9_ebi_get_config,
	.xlate_config = aपंचांगel_ebi_xslate_smc_config,
	.apply_config = at91sam9_ebi_apply_config,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_ebi_caps at91sam9x5_ebi_caps = अणु
	.available_cs = 0x3f,
	.ebi_csa_offs = AT91SAM9X5_MATRIX_EBICSA,
	.regmap_name = "atmel,matrix",
	.get_config = at91sam9_ebi_get_config,
	.xlate_config = aपंचांगel_ebi_xslate_smc_config,
	.apply_config = at91sam9_ebi_apply_config,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_ebi_caps sama5d3_ebi_caps = अणु
	.available_cs = 0xf,
	.get_config = sama5_ebi_get_config,
	.xlate_config = aपंचांगel_ebi_xslate_smc_config,
	.apply_config = sama5_ebi_apply_config,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_ebi_caps sam9x60_ebi_caps = अणु
	.available_cs = 0x3f,
	.ebi_csa_offs = AT91_SFR_CCFG_EBICSA,
	.regmap_name = "microchip,sfr",
	.get_config = at91sam9_ebi_get_config,
	.xlate_config = aपंचांगel_ebi_xslate_smc_config,
	.apply_config = at91sam9_ebi_apply_config,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_ebi_id_table[] = अणु
	अणु
		.compatible = "atmel,at91sam9260-ebi",
		.data = &at91sam9260_ebi_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9261-ebi",
		.data = &at91sam9261_ebi_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9263-ebi0",
		.data = &at91sam9263_ebi0_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9263-ebi1",
		.data = &at91sam9263_ebi1_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9rl-ebi",
		.data = &at91sam9rl_ebi_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9g45-ebi",
		.data = &at91sam9g45_ebi_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9x5-ebi",
		.data = &at91sam9x5_ebi_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d3-ebi",
		.data = &sama5d3_ebi_caps,
	पूर्ण,
	अणु
		.compatible = "microchip,sam9x60-ebi",
		.data = &sam9x60_ebi_caps,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक aपंचांगel_ebi_dev_disable(काष्ठा aपंचांगel_ebi *ebi, काष्ठा device_node *np)
अणु
	काष्ठा device *dev = ebi->dev;
	काष्ठा property *newprop;

	newprop = devm_kzalloc(dev, माप(*newprop), GFP_KERNEL);
	अगर (!newprop)
		वापस -ENOMEM;

	newprop->name = devm_kstrdup(dev, "status", GFP_KERNEL);
	अगर (!newprop->name)
		वापस -ENOMEM;

	newprop->value = devm_kstrdup(dev, "disabled", GFP_KERNEL);
	अगर (!newprop->value)
		वापस -ENOMEM;

	newprop->length = माप("disabled");

	वापस of_update_property(np, newprop);
पूर्ण

अटल पूर्णांक aपंचांगel_ebi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *child, *np = dev->of_node, *smc_np;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा aपंचांगel_ebi *ebi;
	पूर्णांक ret, reg_cells;
	काष्ठा clk *clk;
	u32 val;

	match = of_match_device(aपंचांगel_ebi_id_table, dev);
	अगर (!match || !match->data)
		वापस -EINVAL;

	ebi = devm_kzalloc(dev, माप(*ebi), GFP_KERNEL);
	अगर (!ebi)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ebi);

	INIT_LIST_HEAD(&ebi->devs);
	ebi->caps = match->data;
	ebi->dev = dev;

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ebi->clk = clk;

	smc_np = of_parse_phandle(dev->of_node, "atmel,smc", 0);

	ebi->smc.regmap = syscon_node_to_regmap(smc_np);
	अगर (IS_ERR(ebi->smc.regmap))
		वापस PTR_ERR(ebi->smc.regmap);

	ebi->smc.layout = aपंचांगel_hsmc_get_reg_layout(smc_np);
	अगर (IS_ERR(ebi->smc.layout))
		वापस PTR_ERR(ebi->smc.layout);

	ebi->smc.clk = of_clk_get(smc_np, 0);
	अगर (IS_ERR(ebi->smc.clk)) अणु
		अगर (PTR_ERR(ebi->smc.clk) != -ENOENT)
			वापस PTR_ERR(ebi->smc.clk);

		ebi->smc.clk = शून्य;
	पूर्ण
	ret = clk_prepare_enable(ebi->smc.clk);
	अगर (ret)
		वापस ret;

	/*
	 * The sama5d3 करोes not provide an EBICSA रेजिस्टर and thus करोes need
	 * to access it.
	 */
	अगर (ebi->caps->ebi_csa_offs) अणु
		ebi->regmap =
			syscon_regmap_lookup_by_phandle(np,
							ebi->caps->regmap_name);
		अगर (IS_ERR(ebi->regmap))
			वापस PTR_ERR(ebi->regmap);
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "#address-cells", &val);
	अगर (ret) अणु
		dev_err(dev, "missing #address-cells property\n");
		वापस ret;
	पूर्ण

	reg_cells = val;

	ret = of_property_पढ़ो_u32(np, "#size-cells", &val);
	अगर (ret) अणु
		dev_err(dev, "missing #address-cells property\n");
		वापस ret;
	पूर्ण

	reg_cells += val;

	क्रम_each_available_child_of_node(np, child) अणु
		अगर (!of_find_property(child, "reg", शून्य))
			जारी;

		ret = aपंचांगel_ebi_dev_setup(ebi, child, reg_cells);
		अगर (ret) अणु
			dev_err(dev, "failed to configure EBI bus for %pOF, disabling the device",
				child);

			ret = aपंचांगel_ebi_dev_disable(ebi, child);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस of_platक्रमm_populate(np, शून्य, शून्य, dev);
पूर्ण

अटल __maybe_unused पूर्णांक aपंचांगel_ebi_resume(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_ebi *ebi = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_ebi_dev *ebid;

	list_क्रम_each_entry(ebid, &ebi->devs, node) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ebid->numcs; i++)
			ebid->ebi->caps->apply_config(ebid, &ebid->configs[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(aपंचांगel_ebi_pm_ops, शून्य, aपंचांगel_ebi_resume);

अटल काष्ठा platक्रमm_driver aपंचांगel_ebi_driver = अणु
	.driver = अणु
		.name = "atmel-ebi",
		.of_match_table	= aपंचांगel_ebi_id_table,
		.pm = &aपंचांगel_ebi_pm_ops,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver_probe(aपंचांगel_ebi_driver, aपंचांगel_ebi_probe);
