<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aपंचांगel SMC (Static Memory Controller) helper functions.
 *
 * Copyright (C) 2017 Aपंचांगel
 * Copyright (C) 2017 Free Electrons
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/mfd/syscon/aपंचांगel-smc.h>
#समावेश <linux/माला.स>

/**
 * aपंचांगel_smc_cs_conf_init - initialize a SMC CS conf
 * @conf: the SMC CS conf to initialize
 *
 * Set all fields to 0 so that one can start defining a new config.
 */
व्योम aपंचांगel_smc_cs_conf_init(काष्ठा aपंचांगel_smc_cs_conf *conf)
अणु
	स_रखो(conf, 0, माप(*conf));
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_smc_cs_conf_init);

/**
 * aपंचांगel_smc_cs_encode_ncycles - encode a number of MCK clk cycles in the
 *				 क्रमmat expected by the SMC engine
 * @ncycles: number of MCK clk cycles
 * @msbpos: position of the MSB part of the timing field
 * @msbwidth: width of the MSB part of the timing field
 * @msbfactor: factor applied to the MSB
 * @encodedval: param used to store the encoding result
 *
 * This function encodes the @ncycles value as described in the datasheet
 * (section "SMC Setup/Pulse/Cycle/Timings Register"). This is a generic
 * helper which called with dअगरferent parameter depending on the encoding
 * scheme.
 *
 * If the @ncycles value is too big to be encoded, -दुस्फल is वापसed and
 * the encodedval is contains the maximum val. Otherwise, 0 is वापसed.
 */
अटल पूर्णांक aपंचांगel_smc_cs_encode_ncycles(अचिन्हित पूर्णांक ncycles,
				       अचिन्हित पूर्णांक msbpos,
				       अचिन्हित पूर्णांक msbwidth,
				       अचिन्हित पूर्णांक msbfactor,
				       अचिन्हित पूर्णांक *encodedval)
अणु
	अचिन्हित पूर्णांक lsbmask = GENMASK(msbpos - 1, 0);
	अचिन्हित पूर्णांक msbmask = GENMASK(msbwidth - 1, 0);
	अचिन्हित पूर्णांक msb, lsb;
	पूर्णांक ret = 0;

	msb = ncycles / msbfactor;
	lsb = ncycles % msbfactor;

	अगर (lsb > lsbmask) अणु
		lsb = 0;
		msb++;
	पूर्ण

	/*
	 * Let's just put the maximum we can अगर the requested setting करोes
	 * not fit in the रेजिस्टर field.
	 * We still वापस -दुस्फल in हाल the caller cares.
	 */
	अगर (msb > msbmask) अणु
		msb = msbmask;
		lsb = lsbmask;
		ret = -दुस्फल;
	पूर्ण

	*encodedval = (msb << msbpos) | lsb;

	वापस ret;
पूर्ण

/**
 * aपंचांगel_smc_cs_conf_set_timing - set the SMC CS conf Txx parameter to a
 *				  specअगरic value
 * @conf: SMC CS conf descriptor
 * @shअगरt: the position of the Txx field in the TIMINGS रेजिस्टर
 * @ncycles: value (expressed in MCK clk cycles) to assign to this Txx
 *	     parameter
 *
 * This function encodes the @ncycles value as described in the datasheet
 * (section "SMC Timings Register"), and then stores the result in the
 * @conf->timings field at @shअगरt position.
 *
 * Returns -EINVAL अगर shअगरt is invalid, -दुस्फल अगर ncycles करोes not fit in
 * the field, and 0 otherwise.
 */
पूर्णांक aपंचांगel_smc_cs_conf_set_timing(काष्ठा aपंचांगel_smc_cs_conf *conf,
				 अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक ncycles)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (shअगरt != ATMEL_HSMC_TIMINGS_TCLR_SHIFT &&
	    shअगरt != ATMEL_HSMC_TIMINGS_TADL_SHIFT &&
	    shअगरt != ATMEL_HSMC_TIMINGS_TAR_SHIFT &&
	    shअगरt != ATMEL_HSMC_TIMINGS_TRR_SHIFT &&
	    shअगरt != ATMEL_HSMC_TIMINGS_TWB_SHIFT)
		वापस -EINVAL;

	/*
	 * The क्रमmula described in aपंचांगel datasheets (section "HSMC Timings
	 * Register"):
	 *
	 * ncycles = (Txx[3] * 64) + Txx[2:0]
	 */
	ret = aपंचांगel_smc_cs_encode_ncycles(ncycles, 3, 1, 64, &val);
	conf->timings &= ~GENMASK(shअगरt + 3, shअगरt);
	conf->timings |= val << shअगरt;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_smc_cs_conf_set_timing);

/**
 * aपंचांगel_smc_cs_conf_set_setup - set the SMC CS conf xx_SETUP parameter to a
 *				 specअगरic value
 * @conf: SMC CS conf descriptor
 * @shअगरt: the position of the xx_SETUP field in the SETUP रेजिस्टर
 * @ncycles: value (expressed in MCK clk cycles) to assign to this xx_SETUP
 *	     parameter
 *
 * This function encodes the @ncycles value as described in the datasheet
 * (section "SMC Setup Register"), and then stores the result in the
 * @conf->setup field at @shअगरt position.
 *
 * Returns -EINVAL अगर @shअगरt is invalid, -दुस्फल अगर @ncycles करोes not fit in
 * the field, and 0 otherwise.
 */
पूर्णांक aपंचांगel_smc_cs_conf_set_setup(काष्ठा aपंचांगel_smc_cs_conf *conf,
				अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक ncycles)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (shअगरt != ATMEL_SMC_NWE_SHIFT && shअगरt != ATMEL_SMC_NCS_WR_SHIFT &&
	    shअगरt != ATMEL_SMC_NRD_SHIFT && shअगरt != ATMEL_SMC_NCS_RD_SHIFT)
		वापस -EINVAL;

	/*
	 * The क्रमmula described in aपंचांगel datasheets (section "SMC Setup
	 * Register"):
	 *
	 * ncycles = (128 * xx_SETUP[5]) + xx_SETUP[4:0]
	 */
	ret = aपंचांगel_smc_cs_encode_ncycles(ncycles, 5, 1, 128, &val);
	conf->setup &= ~GENMASK(shअगरt + 7, shअगरt);
	conf->setup |= val << shअगरt;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_smc_cs_conf_set_setup);

/**
 * aपंचांगel_smc_cs_conf_set_pulse - set the SMC CS conf xx_PULSE parameter to a
 *				 specअगरic value
 * @conf: SMC CS conf descriptor
 * @shअगरt: the position of the xx_PULSE field in the PULSE रेजिस्टर
 * @ncycles: value (expressed in MCK clk cycles) to assign to this xx_PULSE
 *	     parameter
 *
 * This function encodes the @ncycles value as described in the datasheet
 * (section "SMC Pulse Register"), and then stores the result in the
 * @conf->setup field at @shअगरt position.
 *
 * Returns -EINVAL अगर @shअगरt is invalid, -दुस्फल अगर @ncycles करोes not fit in
 * the field, and 0 otherwise.
 */
पूर्णांक aपंचांगel_smc_cs_conf_set_pulse(काष्ठा aपंचांगel_smc_cs_conf *conf,
				अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक ncycles)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (shअगरt != ATMEL_SMC_NWE_SHIFT && shअगरt != ATMEL_SMC_NCS_WR_SHIFT &&
	    shअगरt != ATMEL_SMC_NRD_SHIFT && shअगरt != ATMEL_SMC_NCS_RD_SHIFT)
		वापस -EINVAL;

	/*
	 * The क्रमmula described in aपंचांगel datasheets (section "SMC Pulse
	 * Register"):
	 *
	 * ncycles = (256 * xx_PULSE[6]) + xx_PULSE[5:0]
	 */
	ret = aपंचांगel_smc_cs_encode_ncycles(ncycles, 6, 1, 256, &val);
	conf->pulse &= ~GENMASK(shअगरt + 7, shअगरt);
	conf->pulse |= val << shअगरt;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_smc_cs_conf_set_pulse);

/**
 * aपंचांगel_smc_cs_conf_set_cycle - set the SMC CS conf xx_CYCLE parameter to a
 *				 specअगरic value
 * @conf: SMC CS conf descriptor
 * @shअगरt: the position of the xx_CYCLE field in the CYCLE रेजिस्टर
 * @ncycles: value (expressed in MCK clk cycles) to assign to this xx_CYCLE
 *	     parameter
 *
 * This function encodes the @ncycles value as described in the datasheet
 * (section "SMC Cycle Register"), and then stores the result in the
 * @conf->setup field at @shअगरt position.
 *
 * Returns -EINVAL अगर @shअगरt is invalid, -दुस्फल अगर @ncycles करोes not fit in
 * the field, and 0 otherwise.
 */
पूर्णांक aपंचांगel_smc_cs_conf_set_cycle(काष्ठा aपंचांगel_smc_cs_conf *conf,
				अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक ncycles)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (shअगरt != ATMEL_SMC_NWE_SHIFT && shअगरt != ATMEL_SMC_NRD_SHIFT)
		वापस -EINVAL;

	/*
	 * The क्रमmula described in aपंचांगel datasheets (section "SMC Cycle
	 * Register"):
	 *
	 * ncycles = (xx_CYCLE[8:7] * 256) + xx_CYCLE[6:0]
	 */
	ret = aपंचांगel_smc_cs_encode_ncycles(ncycles, 7, 2, 256, &val);
	conf->cycle &= ~GENMASK(shअगरt + 15, shअगरt);
	conf->cycle |= val << shअगरt;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_smc_cs_conf_set_cycle);

/**
 * aपंचांगel_smc_cs_conf_apply - apply an SMC CS conf
 * @regmap: the SMC regmap
 * @cs: the CS id
 * @conf: the SMC CS conf to apply
 *
 * Applies an SMC CS configuration.
 * Only valid on at91sam9/avr32 SoCs.
 */
व्योम aपंचांगel_smc_cs_conf_apply(काष्ठा regmap *regmap, पूर्णांक cs,
			     स्थिर काष्ठा aपंचांगel_smc_cs_conf *conf)
अणु
	regmap_ग_लिखो(regmap, ATMEL_SMC_SETUP(cs), conf->setup);
	regmap_ग_लिखो(regmap, ATMEL_SMC_PULSE(cs), conf->pulse);
	regmap_ग_लिखो(regmap, ATMEL_SMC_CYCLE(cs), conf->cycle);
	regmap_ग_लिखो(regmap, ATMEL_SMC_MODE(cs), conf->mode);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_smc_cs_conf_apply);

/**
 * aपंचांगel_hsmc_cs_conf_apply - apply an SMC CS conf
 * @regmap: the HSMC regmap
 * @cs: the CS id
 * @layout: the layout of रेजिस्टरs
 * @conf: the SMC CS conf to apply
 *
 * Applies an SMC CS configuration.
 * Only valid on post-sama5 SoCs.
 */
व्योम aपंचांगel_hsmc_cs_conf_apply(काष्ठा regmap *regmap,
			      स्थिर काष्ठा aपंचांगel_hsmc_reg_layout *layout,
			      पूर्णांक cs, स्थिर काष्ठा aपंचांगel_smc_cs_conf *conf)
अणु
	regmap_ग_लिखो(regmap, ATMEL_HSMC_SETUP(layout, cs), conf->setup);
	regmap_ग_लिखो(regmap, ATMEL_HSMC_PULSE(layout, cs), conf->pulse);
	regmap_ग_लिखो(regmap, ATMEL_HSMC_CYCLE(layout, cs), conf->cycle);
	regmap_ग_लिखो(regmap, ATMEL_HSMC_TIMINGS(layout, cs), conf->timings);
	regmap_ग_लिखो(regmap, ATMEL_HSMC_MODE(layout, cs), conf->mode);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_hsmc_cs_conf_apply);

/**
 * aपंचांगel_smc_cs_conf_get - retrieve the current SMC CS conf
 * @regmap: the SMC regmap
 * @cs: the CS id
 * @conf: the SMC CS conf object to store the current conf
 *
 * Retrieve the SMC CS configuration.
 * Only valid on at91sam9/avr32 SoCs.
 */
व्योम aपंचांगel_smc_cs_conf_get(काष्ठा regmap *regmap, पूर्णांक cs,
			   काष्ठा aपंचांगel_smc_cs_conf *conf)
अणु
	regmap_पढ़ो(regmap, ATMEL_SMC_SETUP(cs), &conf->setup);
	regmap_पढ़ो(regmap, ATMEL_SMC_PULSE(cs), &conf->pulse);
	regmap_पढ़ो(regmap, ATMEL_SMC_CYCLE(cs), &conf->cycle);
	regmap_पढ़ो(regmap, ATMEL_SMC_MODE(cs), &conf->mode);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_smc_cs_conf_get);

/**
 * aपंचांगel_hsmc_cs_conf_get - retrieve the current SMC CS conf
 * @regmap: the HSMC regmap
 * @cs: the CS id
 * @layout: the layout of रेजिस्टरs
 * @conf: the SMC CS conf object to store the current conf
 *
 * Retrieve the SMC CS configuration.
 * Only valid on post-sama5 SoCs.
 */
व्योम aपंचांगel_hsmc_cs_conf_get(काष्ठा regmap *regmap,
			    स्थिर काष्ठा aपंचांगel_hsmc_reg_layout *layout,
			    पूर्णांक cs, काष्ठा aपंचांगel_smc_cs_conf *conf)
अणु
	regmap_पढ़ो(regmap, ATMEL_HSMC_SETUP(layout, cs), &conf->setup);
	regmap_पढ़ो(regmap, ATMEL_HSMC_PULSE(layout, cs), &conf->pulse);
	regmap_पढ़ो(regmap, ATMEL_HSMC_CYCLE(layout, cs), &conf->cycle);
	regmap_पढ़ो(regmap, ATMEL_HSMC_TIMINGS(layout, cs), &conf->timings);
	regmap_पढ़ो(regmap, ATMEL_HSMC_MODE(layout, cs), &conf->mode);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_hsmc_cs_conf_get);

अटल स्थिर काष्ठा aपंचांगel_hsmc_reg_layout sama5d3_reg_layout = अणु
	.timing_regs_offset = 0x600,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hsmc_reg_layout sama5d2_reg_layout = अणु
	.timing_regs_offset = 0x700,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_smc_ids[] = अणु
	अणु .compatible = "atmel,at91sam9260-smc", .data = शून्य पूर्ण,
	अणु .compatible = "atmel,sama5d3-smc", .data = &sama5d3_reg_layout पूर्ण,
	अणु .compatible = "atmel,sama5d2-smc", .data = &sama5d2_reg_layout पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

/**
 * aपंचांगel_hsmc_get_reg_layout - retrieve the layout of HSMC रेजिस्टरs
 * @np: the HSMC regmap
 *
 * Retrieve the layout of HSMC रेजिस्टरs.
 *
 * Returns शून्य in हाल of SMC, a काष्ठा aपंचांगel_hsmc_reg_layout poपूर्णांकer
 * in HSMC हाल, otherwise ERR_PTR(-EINVAL).
 */
स्थिर काष्ठा aपंचांगel_hsmc_reg_layout *
aपंचांगel_hsmc_get_reg_layout(काष्ठा device_node *np)
अणु
	स्थिर काष्ठा of_device_id *match;

	match = of_match_node(aपंचांगel_smc_ids, np);

	वापस match ? match->data : ERR_PTR(-EINVAL);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_hsmc_get_reg_layout);
