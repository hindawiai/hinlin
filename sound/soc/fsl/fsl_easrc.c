<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2019 NXP

#समावेश <linux/atomic.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kobject.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <linux/gcd.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/core.h>

#समावेश "fsl_easrc.h"
#समावेश "imx-pcm.h"

#घोषणा FSL_EASRC_FORMATS       (SNDRV_PCM_FMTBIT_S16_LE | \
				 SNDRV_PCM_FMTBIT_U16_LE | \
				 SNDRV_PCM_FMTBIT_S24_LE | \
				 SNDRV_PCM_FMTBIT_S24_3LE | \
				 SNDRV_PCM_FMTBIT_U24_LE | \
				 SNDRV_PCM_FMTBIT_U24_3LE | \
				 SNDRV_PCM_FMTBIT_S32_LE | \
				 SNDRV_PCM_FMTBIT_U32_LE | \
				 SNDRV_PCM_FMTBIT_S20_3LE | \
				 SNDRV_PCM_FMTBIT_U20_3LE | \
				 SNDRV_PCM_FMTBIT_FLOAT_LE)

अटल पूर्णांक fsl_easrc_iec958_put_bits(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_asrc *easrc = snd_soc_component_get_drvdata(comp);
	काष्ठा fsl_easrc_priv *easrc_priv = easrc->निजी;
	काष्ठा soc_mreg_control *mc =
		(काष्ठा soc_mreg_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक regval = ucontrol->value.पूर्णांकeger.value[0];

	easrc_priv->bps_iec958[mc->regbase] = regval;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_iec958_get_bits(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_asrc *easrc = snd_soc_component_get_drvdata(comp);
	काष्ठा fsl_easrc_priv *easrc_priv = easrc->निजी;
	काष्ठा soc_mreg_control *mc =
		(काष्ठा soc_mreg_control *)kcontrol->निजी_value;

	ucontrol->value.क्रमागतerated.item[0] = easrc_priv->bps_iec958[mc->regbase];

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_get_reg(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mreg_control *mc =
		(काष्ठा soc_mreg_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक regval;

	regval = snd_soc_component_पढ़ो(component, mc->regbase);

	ucontrol->value.पूर्णांकeger.value[0] = regval;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_set_reg(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mreg_control *mc =
		(काष्ठा soc_mreg_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक regval = ucontrol->value.पूर्णांकeger.value[0];
	पूर्णांक ret;

	ret = snd_soc_component_ग_लिखो(component, mc->regbase, regval);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

#घोषणा SOC_SINGLE_REG_RW(xname, xreg) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.info = snd_soc_info_xr_sx, .get = fsl_easrc_get_reg, \
	.put = fsl_easrc_set_reg, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_mreg_control) \
		अणु .regbase = xreg, .regcount = 1, .nbits = 32, \
		  .invert = 0, .min = 0, .max = 0xffffffff, पूर्ण पूर्ण

#घोषणा SOC_SINGLE_VAL_RW(xname, xreg) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.info = snd_soc_info_xr_sx, .get = fsl_easrc_iec958_get_bits, \
	.put = fsl_easrc_iec958_put_bits, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_mreg_control) \
		अणु .regbase = xreg, .regcount = 1, .nbits = 32, \
		  .invert = 0, .min = 0, .max = 2, पूर्ण पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new fsl_easrc_snd_controls[] = अणु
	SOC_SINGLE("Context 0 Dither Switch", REG_EASRC_COC(0), 0, 1, 0),
	SOC_SINGLE("Context 1 Dither Switch", REG_EASRC_COC(1), 0, 1, 0),
	SOC_SINGLE("Context 2 Dither Switch", REG_EASRC_COC(2), 0, 1, 0),
	SOC_SINGLE("Context 3 Dither Switch", REG_EASRC_COC(3), 0, 1, 0),

	SOC_SINGLE("Context 0 IEC958 Validity", REG_EASRC_COC(0), 2, 1, 0),
	SOC_SINGLE("Context 1 IEC958 Validity", REG_EASRC_COC(1), 2, 1, 0),
	SOC_SINGLE("Context 2 IEC958 Validity", REG_EASRC_COC(2), 2, 1, 0),
	SOC_SINGLE("Context 3 IEC958 Validity", REG_EASRC_COC(3), 2, 1, 0),

	SOC_SINGLE_VAL_RW("Context 0 IEC958 Bits Per Sample", 0),
	SOC_SINGLE_VAL_RW("Context 1 IEC958 Bits Per Sample", 1),
	SOC_SINGLE_VAL_RW("Context 2 IEC958 Bits Per Sample", 2),
	SOC_SINGLE_VAL_RW("Context 3 IEC958 Bits Per Sample", 3),

	SOC_SINGLE_REG_RW("Context 0 IEC958 CS0", REG_EASRC_CS0(0)),
	SOC_SINGLE_REG_RW("Context 1 IEC958 CS0", REG_EASRC_CS0(1)),
	SOC_SINGLE_REG_RW("Context 2 IEC958 CS0", REG_EASRC_CS0(2)),
	SOC_SINGLE_REG_RW("Context 3 IEC958 CS0", REG_EASRC_CS0(3)),
	SOC_SINGLE_REG_RW("Context 0 IEC958 CS1", REG_EASRC_CS1(0)),
	SOC_SINGLE_REG_RW("Context 1 IEC958 CS1", REG_EASRC_CS1(1)),
	SOC_SINGLE_REG_RW("Context 2 IEC958 CS1", REG_EASRC_CS1(2)),
	SOC_SINGLE_REG_RW("Context 3 IEC958 CS1", REG_EASRC_CS1(3)),
	SOC_SINGLE_REG_RW("Context 0 IEC958 CS2", REG_EASRC_CS2(0)),
	SOC_SINGLE_REG_RW("Context 1 IEC958 CS2", REG_EASRC_CS2(1)),
	SOC_SINGLE_REG_RW("Context 2 IEC958 CS2", REG_EASRC_CS2(2)),
	SOC_SINGLE_REG_RW("Context 3 IEC958 CS2", REG_EASRC_CS2(3)),
	SOC_SINGLE_REG_RW("Context 0 IEC958 CS3", REG_EASRC_CS3(0)),
	SOC_SINGLE_REG_RW("Context 1 IEC958 CS3", REG_EASRC_CS3(1)),
	SOC_SINGLE_REG_RW("Context 2 IEC958 CS3", REG_EASRC_CS3(2)),
	SOC_SINGLE_REG_RW("Context 3 IEC958 CS3", REG_EASRC_CS3(3)),
	SOC_SINGLE_REG_RW("Context 0 IEC958 CS4", REG_EASRC_CS4(0)),
	SOC_SINGLE_REG_RW("Context 1 IEC958 CS4", REG_EASRC_CS4(1)),
	SOC_SINGLE_REG_RW("Context 2 IEC958 CS4", REG_EASRC_CS4(2)),
	SOC_SINGLE_REG_RW("Context 3 IEC958 CS4", REG_EASRC_CS4(3)),
	SOC_SINGLE_REG_RW("Context 0 IEC958 CS5", REG_EASRC_CS5(0)),
	SOC_SINGLE_REG_RW("Context 1 IEC958 CS5", REG_EASRC_CS5(1)),
	SOC_SINGLE_REG_RW("Context 2 IEC958 CS5", REG_EASRC_CS5(2)),
	SOC_SINGLE_REG_RW("Context 3 IEC958 CS5", REG_EASRC_CS5(3)),
पूर्ण;

/*
 * fsl_easrc_set_rs_ratio
 *
 * According to the resample taps, calculate the resample ratio
 * ratio = in_rate / out_rate
 */
अटल पूर्णांक fsl_easrc_set_rs_ratio(काष्ठा fsl_asrc_pair *ctx)
अणु
	काष्ठा fsl_asrc *easrc = ctx->asrc;
	काष्ठा fsl_easrc_priv *easrc_priv = easrc->निजी;
	काष्ठा fsl_easrc_ctx_priv *ctx_priv = ctx->निजी;
	अचिन्हित पूर्णांक in_rate = ctx_priv->in_params.norm_rate;
	अचिन्हित पूर्णांक out_rate = ctx_priv->out_params.norm_rate;
	अचिन्हित पूर्णांक frac_bits;
	u64 val;
	u32 *r;

	चयन (easrc_priv->rs_num_taps) अणु
	हाल EASRC_RS_32_TAPS:
		/* पूर्णांकeger bits = 5; */
		frac_bits = 39;
		अवरोध;
	हाल EASRC_RS_64_TAPS:
		/* पूर्णांकeger bits = 6; */
		frac_bits = 38;
		अवरोध;
	हाल EASRC_RS_128_TAPS:
		/* पूर्णांकeger bits = 7; */
		frac_bits = 37;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = (u64)in_rate << frac_bits;
	करो_भाग(val, out_rate);
	r = (uपूर्णांक32_t *)&val;

	अगर (r[1] & 0xFFFFF000) अणु
		dev_err(&easrc->pdev->dev, "ratio exceed range\n");
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(easrc->regmap, REG_EASRC_RRL(ctx->index),
		     EASRC_RRL_RS_RL(r[0]));
	regmap_ग_लिखो(easrc->regmap, REG_EASRC_RRH(ctx->index),
		     EASRC_RRH_RS_RH(r[1]));

	वापस 0;
पूर्ण

/* Normalize input and output sample rates */
अटल व्योम fsl_easrc_normalize_rates(काष्ठा fsl_asrc_pair *ctx)
अणु
	काष्ठा fsl_easrc_ctx_priv *ctx_priv;
	पूर्णांक a, b;

	अगर (!ctx)
		वापस;

	ctx_priv = ctx->निजी;

	a = ctx_priv->in_params.sample_rate;
	b = ctx_priv->out_params.sample_rate;

	a = gcd(a, b);

	/* Divide by gcd to normalize the rate */
	ctx_priv->in_params.norm_rate = ctx_priv->in_params.sample_rate / a;
	ctx_priv->out_params.norm_rate = ctx_priv->out_params.sample_rate / a;
पूर्ण

/* Resets the poपूर्णांकer of the coeff memory poपूर्णांकers */
अटल पूर्णांक fsl_easrc_coeff_mem_ptr_reset(काष्ठा fsl_asrc *easrc,
					 अचिन्हित पूर्णांक ctx_id, पूर्णांक mem_type)
अणु
	काष्ठा device *dev;
	u32 reg, mask, val;

	अगर (!easrc)
		वापस -ENODEV;

	dev = &easrc->pdev->dev;

	चयन (mem_type) अणु
	हाल EASRC_PF_COEFF_MEM:
		/* This resets the prefilter memory poपूर्णांकer addr */
		अगर (ctx_id >= EASRC_CTX_MAX_NUM) अणु
			dev_err(dev, "Invalid context id[%d]\n", ctx_id);
			वापस -EINVAL;
		पूर्ण

		reg = REG_EASRC_CCE1(ctx_id);
		mask = EASRC_CCE1_COEF_MEM_RST_MASK;
		val = EASRC_CCE1_COEF_MEM_RST;
		अवरोध;
	हाल EASRC_RS_COEFF_MEM:
		/* This resets the resampling memory poपूर्णांकer addr */
		reg = REG_EASRC_CRCC;
		mask = EASRC_CRCC_RS_CPR_MASK;
		val = EASRC_CRCC_RS_CPR;
		अवरोध;
	शेष:
		dev_err(dev, "Unknown memory type\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * To reset the ग_लिखो poपूर्णांकer back to zero, the रेजिस्टर field
	 * ASRC_CTX_CTRL_EXT1x[PF_COEFF_MEM_RST] can be toggled from
	 * 0x0 to 0x1 to 0x0.
	 */
	regmap_update_bits(easrc->regmap, reg, mask, 0);
	regmap_update_bits(easrc->regmap, reg, mask, val);
	regmap_update_bits(easrc->regmap, reg, mask, 0);

	वापस 0;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t bits_taps_to_val(अचिन्हित पूर्णांक t)
अणु
	चयन (t) अणु
	हाल EASRC_RS_32_TAPS:
		वापस 32;
	हाल EASRC_RS_64_TAPS:
		वापस 64;
	हाल EASRC_RS_128_TAPS:
		वापस 128;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_resampler_config(काष्ठा fsl_asrc *easrc)
अणु
	काष्ठा device *dev = &easrc->pdev->dev;
	काष्ठा fsl_easrc_priv *easrc_priv = easrc->निजी;
	काष्ठा asrc_firmware_hdr *hdr =  easrc_priv->firmware_hdr;
	काष्ठा पूर्णांकerp_params *पूर्णांकerp = easrc_priv->पूर्णांकerp;
	काष्ठा पूर्णांकerp_params *selected_पूर्णांकerp = शून्य;
	अचिन्हित पूर्णांक num_coeff;
	अचिन्हित पूर्णांक i;
	u64 *coef;
	u32 *r;
	पूर्णांक ret;

	अगर (!hdr) अणु
		dev_err(dev, "firmware not loaded!\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < hdr->पूर्णांकerp_scen; i++) अणु
		अगर ((पूर्णांकerp[i].num_taps - 1) !=
		    bits_taps_to_val(easrc_priv->rs_num_taps))
			जारी;

		coef = पूर्णांकerp[i].coeff;
		selected_पूर्णांकerp = &पूर्णांकerp[i];
		dev_dbg(dev, "Selected interp_filter: %u taps - %u phases\n",
			selected_पूर्णांकerp->num_taps,
			selected_पूर्णांकerp->num_phases);
		अवरोध;
	पूर्ण

	अगर (!selected_पूर्णांकerp) अणु
		dev_err(dev, "failed to get interpreter configuration\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * RS_LOW - first half of center tap of the sinc function
	 * RS_HIGH - second half of center tap of the sinc function
	 * This is due to the fact the resampling function must be
	 * symetrical - i.e. odd number of taps
	 */
	r = (uपूर्णांक32_t *)&selected_पूर्णांकerp->center_tap;
	regmap_ग_लिखो(easrc->regmap, REG_EASRC_RCTCL, EASRC_RCTCL_RS_CL(r[0]));
	regmap_ग_लिखो(easrc->regmap, REG_EASRC_RCTCH, EASRC_RCTCH_RS_CH(r[1]));

	/*
	 * Write Number of Resampling Coefficient Taps
	 * 00b - 32-Tap Resampling Filter
	 * 01b - 64-Tap Resampling Filter
	 * 10b - 128-Tap Resampling Filter
	 * 11b - N/A
	 */
	regmap_update_bits(easrc->regmap, REG_EASRC_CRCC,
			   EASRC_CRCC_RS_TAPS_MASK,
			   EASRC_CRCC_RS_TAPS(easrc_priv->rs_num_taps));

	/* Reset prefilter coefficient poपूर्णांकer back to 0 */
	ret = fsl_easrc_coeff_mem_ptr_reset(easrc, 0, EASRC_RS_COEFF_MEM);
	अगर (ret)
		वापस ret;

	/*
	 * When the filter is programmed to run in:
	 * 32-tap mode, 16-taps, 128-phases 4-coefficients per phase
	 * 64-tap mode, 32-taps, 64-phases 4-coefficients per phase
	 * 128-tap mode, 64-taps, 32-phases 4-coefficients per phase
	 * This means the number of ग_लिखोs is स्थिरant no matter
	 * the mode we are using
	 */
	num_coeff = 16 * 128 * 4;

	क्रम (i = 0; i < num_coeff; i++) अणु
		r = (uपूर्णांक32_t *)&coef[i];
		regmap_ग_लिखो(easrc->regmap, REG_EASRC_CRCM,
			     EASRC_CRCM_RS_CWD(r[0]));
		regmap_ग_लिखो(easrc->regmap, REG_EASRC_CRCM,
			     EASRC_CRCM_RS_CWD(r[1]));
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  fsl_easrc_normalize_filter - Scale filter coefficients (64 bits भग्न)
 *  For input भग्न32 normalized range (1.0,-1.0) -> output पूर्णांक[16,24,32]:
 *      scale it by multiplying filter coefficients by 2^31
 *  For input पूर्णांक[16, 24, 32] -> output भग्न32
 *      scale it by multiplying filter coefficients by 2^-15, 2^-23, 2^-31
 *  input:
 *      @easrc:  Structure poपूर्णांकer of fsl_asrc
 *      @infilter : Poपूर्णांकer to non-scaled input filter
 *      @shअगरt:  The multiply factor
 *  output:
 *      @outfilter: scaled filter
 */
अटल पूर्णांक fsl_easrc_normalize_filter(काष्ठा fsl_asrc *easrc,
				      u64 *infilter,
				      u64 *outfilter,
				      पूर्णांक shअगरt)
अणु
	काष्ठा device *dev = &easrc->pdev->dev;
	u64 coef = *infilter;
	s64 exp  = (coef & 0x7ff0000000000000ll) >> 52;
	u64 outcoef;

	/*
	 * If exponent is zero (value == 0), or 7ff (value == NaNs)
	 * करोnt touch the content
	 */
	अगर (exp == 0 || exp == 0x7ff) अणु
		*outfilter = coef;
		वापस 0;
	पूर्ण

	/* coef * 2^shअगरt ==> exp + shअगरt */
	exp += shअगरt;

	अगर ((shअगरt > 0 && exp >= 0x7ff) || (shअगरt < 0 && exp <= 0)) अणु
		dev_err(dev, "coef out of range\n");
		वापस -EINVAL;
	पूर्ण

	outcoef = (u64)(coef & 0x800FFFFFFFFFFFFFll) + ((u64)exp << 52);
	*outfilter = outcoef;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_ग_लिखो_pf_coeff_mem(काष्ठा fsl_asrc *easrc, पूर्णांक ctx_id,
					u64 *coef, पूर्णांक n_taps, पूर्णांक shअगरt)
अणु
	काष्ठा device *dev = &easrc->pdev->dev;
	पूर्णांक ret = 0;
	पूर्णांक i;
	u32 *r;
	u64 पंचांगp;

	/* If STx_NUM_TAPS is set to 0x0 then वापस */
	अगर (!n_taps)
		वापस 0;

	अगर (!coef) अणु
		dev_err(dev, "coef table is NULL\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * When चयनing between stages, the address poपूर्णांकer
	 * should be reset back to 0x0 beक्रमe perक्रमming a ग_लिखो
	 */
	ret = fsl_easrc_coeff_mem_ptr_reset(easrc, ctx_id, EASRC_PF_COEFF_MEM);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < (n_taps + 1) / 2; i++) अणु
		ret = fsl_easrc_normalize_filter(easrc, &coef[i], &पंचांगp, shअगरt);
		अगर (ret)
			वापस ret;

		r = (uपूर्णांक32_t *)&पंचांगp;
		regmap_ग_लिखो(easrc->regmap, REG_EASRC_PCF(ctx_id),
			     EASRC_PCF_CD(r[0]));
		regmap_ग_लिखो(easrc->regmap, REG_EASRC_PCF(ctx_id),
			     EASRC_PCF_CD(r[1]));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_prefilter_config(काष्ठा fsl_asrc *easrc,
				      अचिन्हित पूर्णांक ctx_id)
अणु
	काष्ठा prefil_params *prefil, *selected_prefil = शून्य;
	काष्ठा fsl_easrc_ctx_priv *ctx_priv;
	काष्ठा fsl_easrc_priv *easrc_priv;
	काष्ठा asrc_firmware_hdr *hdr;
	काष्ठा fsl_asrc_pair *ctx;
	काष्ठा device *dev;
	u32 inrate, outrate, offset = 0;
	u32 in_s_rate, out_s_rate, in_s_fmt, out_s_fmt;
	पूर्णांक ret, i;

	अगर (!easrc)
		वापस -ENODEV;

	dev = &easrc->pdev->dev;

	अगर (ctx_id >= EASRC_CTX_MAX_NUM) अणु
		dev_err(dev, "Invalid context id[%d]\n", ctx_id);
		वापस -EINVAL;
	पूर्ण

	easrc_priv = easrc->निजी;

	ctx = easrc->pair[ctx_id];
	ctx_priv = ctx->निजी;

	in_s_rate = ctx_priv->in_params.sample_rate;
	out_s_rate = ctx_priv->out_params.sample_rate;
	in_s_fmt = ctx_priv->in_params.sample_क्रमmat;
	out_s_fmt = ctx_priv->out_params.sample_क्रमmat;

	ctx_priv->in_filled_sample = bits_taps_to_val(easrc_priv->rs_num_taps) / 2;
	ctx_priv->out_missed_sample = ctx_priv->in_filled_sample * out_s_rate / in_s_rate;

	ctx_priv->st1_num_taps = 0;
	ctx_priv->st2_num_taps = 0;

	regmap_ग_लिखो(easrc->regmap, REG_EASRC_CCE1(ctx_id), 0);
	regmap_ग_लिखो(easrc->regmap, REG_EASRC_CCE2(ctx_id), 0);

	/*
	 * The audio भग्न poपूर्णांक data range is (-1, 1), the asrc would output
	 * all zero क्रम भग्न poपूर्णांक input and पूर्णांकeger output हाल, that is to
	 * drop the fractional part of the data directly.
	 *
	 * In order to support भग्न to पूर्णांक conversion or पूर्णांक to भग्न
	 * conversion we need to करो special operation on the coefficient to
	 * enlarge/reduce the data to the expected range.
	 *
	 * For भग्न to पूर्णांक हाल:
	 * Up sampling:
	 * 1. Create a 1 tap filter with center tap (only tap) of 2^31
	 *    in 64 bits भग्नing poपूर्णांक.
	 *    द्विगुन value = (द्विगुन)(((uपूर्णांक64_t)1) << 31)
	 * 2. Program 1 tap prefilter with center tap above.
	 *
	 * Down sampling,
	 * 1. If the filter is single stage filter, add "shift" to the exponent
	 *    of stage 1 coefficients.
	 * 2. If the filter is two stage filter , add "shift" to the exponent
	 *    of stage 2 coefficients.
	 *
	 * The "shift" is 31, same क्रम पूर्णांक16, पूर्णांक24, पूर्णांक32 हाल.
	 *
	 * For पूर्णांक to भग्न हाल:
	 * Up sampling:
	 * 1. Create a 1 tap filter with center tap (only tap) of 2^-31
	 *    in 64 bits भग्नing poपूर्णांक.
	 * 2. Program 1 tap prefilter with center tap above.
	 *
	 * Down sampling,
	 * 1. If the filter is single stage filter, subtract "shift" to the
	 *    exponent of stage 1 coefficients.
	 * 2. If the filter is two stage filter , subtract "shift" to the
	 *    exponent of stage 2 coefficients.
	 *
	 * The "shift" is 15,23,31, dअगरferent क्रम पूर्णांक16, पूर्णांक24, पूर्णांक32 हाल.
	 *
	 */
	अगर (out_s_rate >= in_s_rate) अणु
		अगर (out_s_rate == in_s_rate)
			regmap_update_bits(easrc->regmap,
					   REG_EASRC_CCE1(ctx_id),
					   EASRC_CCE1_RS_BYPASS_MASK,
					   EASRC_CCE1_RS_BYPASS);

		ctx_priv->st1_num_taps = 1;
		ctx_priv->st1_coeff    = &easrc_priv->स्थिर_coeff;
		ctx_priv->st1_num_exp  = 1;
		ctx_priv->st2_num_taps = 0;

		अगर (in_s_fmt == SNDRV_PCM_FORMAT_FLOAT_LE &&
		    out_s_fmt != SNDRV_PCM_FORMAT_FLOAT_LE)
			ctx_priv->st1_addexp = 31;
		अन्यथा अगर (in_s_fmt != SNDRV_PCM_FORMAT_FLOAT_LE &&
			 out_s_fmt == SNDRV_PCM_FORMAT_FLOAT_LE)
			ctx_priv->st1_addexp -= ctx_priv->in_params.fmt.addexp;
	पूर्ण अन्यथा अणु
		inrate = ctx_priv->in_params.norm_rate;
		outrate = ctx_priv->out_params.norm_rate;

		hdr = easrc_priv->firmware_hdr;
		prefil = easrc_priv->prefil;

		क्रम (i = 0; i < hdr->prefil_scen; i++) अणु
			अगर (inrate == prefil[i].insr &&
			    outrate == prefil[i].outsr) अणु
				selected_prefil = &prefil[i];
				dev_dbg(dev, "Selected prefilter: %u insr, %u outsr, %u st1_taps, %u st2_taps\n",
					selected_prefil->insr,
					selected_prefil->outsr,
					selected_prefil->st1_taps,
					selected_prefil->st2_taps);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!selected_prefil) अणु
			dev_err(dev, "Conversion from in ratio %u(%u) to out ratio %u(%u) is not supported\n",
				in_s_rate, inrate,
				out_s_rate, outrate);
			वापस -EINVAL;
		पूर्ण

		/*
		 * In prefilter coeff array, first st1_num_taps represent the
		 * stage1 prefilter coefficients followed by next st2_num_taps
		 * representing stage 2 coefficients
		 */
		ctx_priv->st1_num_taps = selected_prefil->st1_taps;
		ctx_priv->st1_coeff    = selected_prefil->coeff;
		ctx_priv->st1_num_exp  = selected_prefil->st1_exp;

		offset = ((selected_prefil->st1_taps + 1) / 2);
		ctx_priv->st2_num_taps = selected_prefil->st2_taps;
		ctx_priv->st2_coeff    = selected_prefil->coeff + offset;

		अगर (in_s_fmt == SNDRV_PCM_FORMAT_FLOAT_LE &&
		    out_s_fmt != SNDRV_PCM_FORMAT_FLOAT_LE) अणु
			/* only change stage2 coefficient क्रम 2 stage हाल */
			अगर (ctx_priv->st2_num_taps > 0)
				ctx_priv->st2_addexp = 31;
			अन्यथा
				ctx_priv->st1_addexp = 31;
		पूर्ण अन्यथा अगर (in_s_fmt != SNDRV_PCM_FORMAT_FLOAT_LE &&
			   out_s_fmt == SNDRV_PCM_FORMAT_FLOAT_LE) अणु
			अगर (ctx_priv->st2_num_taps > 0)
				ctx_priv->st2_addexp -= ctx_priv->in_params.fmt.addexp;
			अन्यथा
				ctx_priv->st1_addexp -= ctx_priv->in_params.fmt.addexp;
		पूर्ण
	पूर्ण

	ctx_priv->in_filled_sample += (ctx_priv->st1_num_taps / 2) * ctx_priv->st1_num_exp +
				  ctx_priv->st2_num_taps / 2;
	ctx_priv->out_missed_sample = ctx_priv->in_filled_sample * out_s_rate / in_s_rate;

	अगर (ctx_priv->in_filled_sample * out_s_rate % in_s_rate != 0)
		ctx_priv->out_missed_sample += 1;
	/*
	 * To modअगरy the value of a prefilter coefficient, the user must
	 * perक्रमm a ग_लिखो to the रेजिस्टर ASRC_PRE_COEFF_FIFOn[COEFF_DATA]
	 * जबतक the respective context RUN_EN bit is set to 0b0
	 */
	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx_id),
			   EASRC_CC_EN_MASK, 0);

	अगर (ctx_priv->st1_num_taps > EASRC_MAX_PF_TAPS) अणु
		dev_err(dev, "ST1 taps [%d] mus be lower than %d\n",
			ctx_priv->st1_num_taps, EASRC_MAX_PF_TAPS);
		ret = -EINVAL;
		जाओ ctx_error;
	पूर्ण

	/* Update ctx ST1_NUM_TAPS in Context Control Extended 2 रेजिस्टर */
	regmap_update_bits(easrc->regmap, REG_EASRC_CCE2(ctx_id),
			   EASRC_CCE2_ST1_TAPS_MASK,
			   EASRC_CCE2_ST1_TAPS(ctx_priv->st1_num_taps - 1));

	/* Prefilter Coefficient Write Select to ग_लिखो in ST1 coeff */
	regmap_update_bits(easrc->regmap, REG_EASRC_CCE1(ctx_id),
			   EASRC_CCE1_COEF_WS_MASK,
			   EASRC_PF_ST1_COEFF_WR << EASRC_CCE1_COEF_WS_SHIFT);

	ret = fsl_easrc_ग_लिखो_pf_coeff_mem(easrc, ctx_id,
					   ctx_priv->st1_coeff,
					   ctx_priv->st1_num_taps,
					   ctx_priv->st1_addexp);
	अगर (ret)
		जाओ ctx_error;

	अगर (ctx_priv->st2_num_taps > 0) अणु
		अगर (ctx_priv->st2_num_taps + ctx_priv->st1_num_taps > EASRC_MAX_PF_TAPS) अणु
			dev_err(dev, "ST2 taps [%d] mus be lower than %d\n",
				ctx_priv->st2_num_taps, EASRC_MAX_PF_TAPS);
			ret = -EINVAL;
			जाओ ctx_error;
		पूर्ण

		regmap_update_bits(easrc->regmap, REG_EASRC_CCE1(ctx_id),
				   EASRC_CCE1_PF_TSEN_MASK,
				   EASRC_CCE1_PF_TSEN);
		/*
		 * Enable prefilter stage1 ग_लिखोback भग्नing poपूर्णांक
		 * which is used क्रम FLOAT_LE हाल
		 */
		regmap_update_bits(easrc->regmap, REG_EASRC_CCE1(ctx_id),
				   EASRC_CCE1_PF_ST1_WBFP_MASK,
				   EASRC_CCE1_PF_ST1_WBFP);

		regmap_update_bits(easrc->regmap, REG_EASRC_CCE1(ctx_id),
				   EASRC_CCE1_PF_EXP_MASK,
				   EASRC_CCE1_PF_EXP(ctx_priv->st1_num_exp - 1));

		/* Update ctx ST2_NUM_TAPS in Context Control Extended 2 reg */
		regmap_update_bits(easrc->regmap, REG_EASRC_CCE2(ctx_id),
				   EASRC_CCE2_ST2_TAPS_MASK,
				   EASRC_CCE2_ST2_TAPS(ctx_priv->st2_num_taps - 1));

		/* Prefilter Coefficient Write Select to ग_लिखो in ST2 coeff */
		regmap_update_bits(easrc->regmap, REG_EASRC_CCE1(ctx_id),
				   EASRC_CCE1_COEF_WS_MASK,
				   EASRC_PF_ST2_COEFF_WR << EASRC_CCE1_COEF_WS_SHIFT);

		ret = fsl_easrc_ग_लिखो_pf_coeff_mem(easrc, ctx_id,
						   ctx_priv->st2_coeff,
						   ctx_priv->st2_num_taps,
						   ctx_priv->st2_addexp);
		अगर (ret)
			जाओ ctx_error;
	पूर्ण

	वापस 0;

ctx_error:
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_easrc_max_ch_क्रम_slot(काष्ठा fsl_asrc_pair *ctx,
				     काष्ठा fsl_easrc_slot *slot)
अणु
	काष्ठा fsl_easrc_ctx_priv *ctx_priv = ctx->निजी;
	पूर्णांक st1_mem_alloc = 0, st2_mem_alloc = 0;
	पूर्णांक pf_mem_alloc = 0;
	पूर्णांक max_channels = 8 - slot->num_channel;
	पूर्णांक channels = 0;

	अगर (ctx_priv->st1_num_taps > 0) अणु
		अगर (ctx_priv->st2_num_taps > 0)
			st1_mem_alloc =
				(ctx_priv->st1_num_taps - 1) * ctx_priv->st1_num_exp + 1;
		अन्यथा
			st1_mem_alloc = ctx_priv->st1_num_taps;
	पूर्ण

	अगर (ctx_priv->st2_num_taps > 0)
		st2_mem_alloc = ctx_priv->st2_num_taps;

	pf_mem_alloc = st1_mem_alloc + st2_mem_alloc;

	अगर (pf_mem_alloc != 0)
		channels = (6144 - slot->pf_mem_used) / pf_mem_alloc;
	अन्यथा
		channels = 8;

	अगर (channels < max_channels)
		max_channels = channels;

	वापस max_channels;
पूर्ण

अटल पूर्णांक fsl_easrc_config_one_slot(काष्ठा fsl_asrc_pair *ctx,
				     काष्ठा fsl_easrc_slot *slot,
				     अचिन्हित पूर्णांक slot_ctx_idx,
				     अचिन्हित पूर्णांक *req_channels,
				     अचिन्हित पूर्णांक *start_channel,
				     अचिन्हित पूर्णांक *avail_channel)
अणु
	काष्ठा fsl_asrc *easrc = ctx->asrc;
	काष्ठा fsl_easrc_ctx_priv *ctx_priv = ctx->निजी;
	पूर्णांक st1_chanxexp, st1_mem_alloc = 0, st2_mem_alloc;
	अचिन्हित पूर्णांक reg0, reg1, reg2, reg3;
	अचिन्हित पूर्णांक addr;

	अगर (slot->slot_index == 0) अणु
		reg0 = REG_EASRC_DPCS0R0(slot_ctx_idx);
		reg1 = REG_EASRC_DPCS0R1(slot_ctx_idx);
		reg2 = REG_EASRC_DPCS0R2(slot_ctx_idx);
		reg3 = REG_EASRC_DPCS0R3(slot_ctx_idx);
	पूर्ण अन्यथा अणु
		reg0 = REG_EASRC_DPCS1R0(slot_ctx_idx);
		reg1 = REG_EASRC_DPCS1R1(slot_ctx_idx);
		reg2 = REG_EASRC_DPCS1R2(slot_ctx_idx);
		reg3 = REG_EASRC_DPCS1R3(slot_ctx_idx);
	पूर्ण

	अगर (*req_channels <= *avail_channel) अणु
		slot->num_channel = *req_channels;
		*req_channels = 0;
	पूर्ण अन्यथा अणु
		slot->num_channel = *avail_channel;
		*req_channels -= *avail_channel;
	पूर्ण

	slot->min_channel = *start_channel;
	slot->max_channel = *start_channel + slot->num_channel - 1;
	slot->ctx_index = ctx->index;
	slot->busy = true;
	*start_channel += slot->num_channel;

	regmap_update_bits(easrc->regmap, reg0,
			   EASRC_DPCS0R0_MAXCH_MASK,
			   EASRC_DPCS0R0_MAXCH(slot->max_channel));

	regmap_update_bits(easrc->regmap, reg0,
			   EASRC_DPCS0R0_MINCH_MASK,
			   EASRC_DPCS0R0_MINCH(slot->min_channel));

	regmap_update_bits(easrc->regmap, reg0,
			   EASRC_DPCS0R0_NUMCH_MASK,
			   EASRC_DPCS0R0_NUMCH(slot->num_channel - 1));

	regmap_update_bits(easrc->regmap, reg0,
			   EASRC_DPCS0R0_CTXNUM_MASK,
			   EASRC_DPCS0R0_CTXNUM(slot->ctx_index));

	अगर (ctx_priv->st1_num_taps > 0) अणु
		अगर (ctx_priv->st2_num_taps > 0)
			st1_mem_alloc =
				(ctx_priv->st1_num_taps - 1) * slot->num_channel *
				ctx_priv->st1_num_exp + slot->num_channel;
		अन्यथा
			st1_mem_alloc = ctx_priv->st1_num_taps * slot->num_channel;

		slot->pf_mem_used = st1_mem_alloc;
		regmap_update_bits(easrc->regmap, reg2,
				   EASRC_DPCS0R2_ST1_MA_MASK,
				   EASRC_DPCS0R2_ST1_MA(st1_mem_alloc));

		अगर (slot->slot_index == 1)
			addr = PREFILTER_MEM_LEN - st1_mem_alloc;
		अन्यथा
			addr = 0;

		regmap_update_bits(easrc->regmap, reg2,
				   EASRC_DPCS0R2_ST1_SA_MASK,
				   EASRC_DPCS0R2_ST1_SA(addr));
	पूर्ण

	अगर (ctx_priv->st2_num_taps > 0) अणु
		st1_chanxexp = slot->num_channel * (ctx_priv->st1_num_exp - 1);

		regmap_update_bits(easrc->regmap, reg1,
				   EASRC_DPCS0R1_ST1_EXP_MASK,
				   EASRC_DPCS0R1_ST1_EXP(st1_chanxexp));

		st2_mem_alloc = slot->num_channel * ctx_priv->st2_num_taps;
		slot->pf_mem_used += st2_mem_alloc;
		regmap_update_bits(easrc->regmap, reg3,
				   EASRC_DPCS0R3_ST2_MA_MASK,
				   EASRC_DPCS0R3_ST2_MA(st2_mem_alloc));

		अगर (slot->slot_index == 1)
			addr = PREFILTER_MEM_LEN - st1_mem_alloc - st2_mem_alloc;
		अन्यथा
			addr = st1_mem_alloc;

		regmap_update_bits(easrc->regmap, reg3,
				   EASRC_DPCS0R3_ST2_SA_MASK,
				   EASRC_DPCS0R3_ST2_SA(addr));
	पूर्ण

	regmap_update_bits(easrc->regmap, reg0,
			   EASRC_DPCS0R0_EN_MASK, EASRC_DPCS0R0_EN);

	वापस 0;
पूर्ण

/*
 * fsl_easrc_config_slot
 *
 * A single context can be split amongst any of the 4 context processing pipes
 * in the design.
 * The total number of channels consumed within the context processor must be
 * less than or equal to 8. अगर a single context is configured to contain more
 * than 8 channels then it must be distributed across multiple context
 * processing pipe slots.
 *
 */
अटल पूर्णांक fsl_easrc_config_slot(काष्ठा fsl_asrc *easrc, अचिन्हित पूर्णांक ctx_id)
अणु
	काष्ठा fsl_easrc_priv *easrc_priv = easrc->निजी;
	काष्ठा fsl_asrc_pair *ctx = easrc->pair[ctx_id];
	पूर्णांक req_channels = ctx->channels;
	पूर्णांक start_channel = 0, avail_channel;
	काष्ठा fsl_easrc_slot *slot0, *slot1;
	काष्ठा fsl_easrc_slot *slota, *slotb;
	पूर्णांक i, ret;

	अगर (req_channels <= 0)
		वापस -EINVAL;

	क्रम (i = 0; i < EASRC_CTX_MAX_NUM; i++) अणु
		slot0 = &easrc_priv->slot[i][0];
		slot1 = &easrc_priv->slot[i][1];

		अगर (slot0->busy && slot1->busy) अणु
			जारी;
		पूर्ण अन्यथा अगर ((slot0->busy && slot0->ctx_index == ctx->index) ||
			 (slot1->busy && slot1->ctx_index == ctx->index)) अणु
			जारी;
		पूर्ण अन्यथा अगर (!slot0->busy) अणु
			slota = slot0;
			slotb = slot1;
			slota->slot_index = 0;
		पूर्ण अन्यथा अगर (!slot1->busy) अणु
			slota = slot1;
			slotb = slot0;
			slota->slot_index = 1;
		पूर्ण

		अगर (!slota || !slotb)
			जारी;

		avail_channel = fsl_easrc_max_ch_क्रम_slot(ctx, slotb);
		अगर (avail_channel <= 0)
			जारी;

		ret = fsl_easrc_config_one_slot(ctx, slota, i, &req_channels,
						&start_channel, &avail_channel);
		अगर (ret)
			वापस ret;

		अगर (req_channels > 0)
			जारी;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (req_channels > 0) अणु
		dev_err(&easrc->pdev->dev, "no avail slot.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * fsl_easrc_release_slot
 *
 * Clear the slot configuration
 */
अटल पूर्णांक fsl_easrc_release_slot(काष्ठा fsl_asrc *easrc, अचिन्हित पूर्णांक ctx_id)
अणु
	काष्ठा fsl_easrc_priv *easrc_priv = easrc->निजी;
	काष्ठा fsl_asrc_pair *ctx = easrc->pair[ctx_id];
	पूर्णांक i;

	क्रम (i = 0; i < EASRC_CTX_MAX_NUM; i++) अणु
		अगर (easrc_priv->slot[i][0].busy &&
		    easrc_priv->slot[i][0].ctx_index == ctx->index) अणु
			easrc_priv->slot[i][0].busy = false;
			easrc_priv->slot[i][0].num_channel = 0;
			easrc_priv->slot[i][0].pf_mem_used = 0;
			/* set रेजिस्टरs */
			regmap_ग_लिखो(easrc->regmap, REG_EASRC_DPCS0R0(i), 0);
			regmap_ग_लिखो(easrc->regmap, REG_EASRC_DPCS0R1(i), 0);
			regmap_ग_लिखो(easrc->regmap, REG_EASRC_DPCS0R2(i), 0);
			regmap_ग_लिखो(easrc->regmap, REG_EASRC_DPCS0R3(i), 0);
		पूर्ण

		अगर (easrc_priv->slot[i][1].busy &&
		    easrc_priv->slot[i][1].ctx_index == ctx->index) अणु
			easrc_priv->slot[i][1].busy = false;
			easrc_priv->slot[i][1].num_channel = 0;
			easrc_priv->slot[i][1].pf_mem_used = 0;
			/* set रेजिस्टरs */
			regmap_ग_लिखो(easrc->regmap, REG_EASRC_DPCS1R0(i), 0);
			regmap_ग_लिखो(easrc->regmap, REG_EASRC_DPCS1R1(i), 0);
			regmap_ग_लिखो(easrc->regmap, REG_EASRC_DPCS1R2(i), 0);
			regmap_ग_लिखो(easrc->regmap, REG_EASRC_DPCS1R3(i), 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * fsl_easrc_config_context
 *
 * Configure the रेजिस्टर relate with context.
 */
अटल पूर्णांक fsl_easrc_config_context(काष्ठा fsl_asrc *easrc, अचिन्हित पूर्णांक ctx_id)
अणु
	काष्ठा fsl_easrc_ctx_priv *ctx_priv;
	काष्ठा fsl_asrc_pair *ctx;
	काष्ठा device *dev;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक ret;

	अगर (!easrc)
		वापस -ENODEV;

	dev = &easrc->pdev->dev;

	अगर (ctx_id >= EASRC_CTX_MAX_NUM) अणु
		dev_err(dev, "Invalid context id[%d]\n", ctx_id);
		वापस -EINVAL;
	पूर्ण

	ctx = easrc->pair[ctx_id];

	ctx_priv = ctx->निजी;

	fsl_easrc_normalize_rates(ctx);

	ret = fsl_easrc_set_rs_ratio(ctx);
	अगर (ret)
		वापस ret;

	/* Initialize the context coeficients */
	ret = fsl_easrc_prefilter_config(easrc, ctx->index);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&easrc->lock, lock_flags);
	ret = fsl_easrc_config_slot(easrc, ctx->index);
	spin_unlock_irqrestore(&easrc->lock, lock_flags);
	अगर (ret)
		वापस ret;

	/*
	 * Both prefilter and resampling filters can use following
	 * initialization modes:
	 * 2 - zero-fil mode
	 * 1 - replication mode
	 * 0 - software control
	 */
	regmap_update_bits(easrc->regmap, REG_EASRC_CCE1(ctx_id),
			   EASRC_CCE1_RS_INIT_MASK,
			   EASRC_CCE1_RS_INIT(ctx_priv->rs_init_mode));

	regmap_update_bits(easrc->regmap, REG_EASRC_CCE1(ctx_id),
			   EASRC_CCE1_PF_INIT_MASK,
			   EASRC_CCE1_PF_INIT(ctx_priv->pf_init_mode));

	/*
	 * Context Input FIFO Watermark
	 * DMA request is generated when input FIFO < FIFO_WTMK
	 */
	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx_id),
			   EASRC_CC_FIFO_WTMK_MASK,
			   EASRC_CC_FIFO_WTMK(ctx_priv->in_params.fअगरo_wपंचांगk));

	/*
	 * Context Output FIFO Watermark
	 * DMA request is generated when output FIFO > FIFO_WTMK
	 * So we set fअगरo_wपंचांगk -1 to रेजिस्टर.
	 */
	regmap_update_bits(easrc->regmap, REG_EASRC_COC(ctx_id),
			   EASRC_COC_FIFO_WTMK_MASK,
			   EASRC_COC_FIFO_WTMK(ctx_priv->out_params.fअगरo_wपंचांगk - 1));

	/* Number of channels */
	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx_id),
			   EASRC_CC_CHEN_MASK,
			   EASRC_CC_CHEN(ctx->channels - 1));
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_process_क्रमmat(काष्ठा fsl_asrc_pair *ctx,
				    काष्ठा fsl_easrc_data_fmt *fmt,
				    snd_pcm_क्रमmat_t raw_fmt)
अणु
	काष्ठा fsl_asrc *easrc = ctx->asrc;
	काष्ठा fsl_easrc_priv *easrc_priv = easrc->निजी;
	पूर्णांक ret;

	अगर (!fmt)
		वापस -EINVAL;

	/*
	 * Context Input Floating Poपूर्णांक Format
	 * 0 - Integer Format
	 * 1 - Single Precision FP Format
	 */
	fmt->भग्नing_poपूर्णांक = !snd_pcm_क्रमmat_linear(raw_fmt);
	fmt->sample_pos = 0;
	fmt->iec958 = 0;

	/* Get the data width */
	चयन (snd_pcm_क्रमmat_width(raw_fmt)) अणु
	हाल 16:
		fmt->width = EASRC_WIDTH_16_BIT;
		fmt->addexp = 15;
		अवरोध;
	हाल 20:
		fmt->width = EASRC_WIDTH_20_BIT;
		fmt->addexp = 19;
		अवरोध;
	हाल 24:
		fmt->width = EASRC_WIDTH_24_BIT;
		fmt->addexp = 23;
		अवरोध;
	हाल 32:
		fmt->width = EASRC_WIDTH_32_BIT;
		fmt->addexp = 31;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (raw_fmt) अणु
	हाल SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE:
		fmt->width = easrc_priv->bps_iec958[ctx->index];
		fmt->iec958 = 1;
		fmt->भग्नing_poपूर्णांक = 0;
		अगर (fmt->width == EASRC_WIDTH_16_BIT) अणु
			fmt->sample_pos = 12;
			fmt->addexp = 15;
		पूर्ण अन्यथा अगर (fmt->width == EASRC_WIDTH_20_BIT) अणु
			fmt->sample_pos = 8;
			fmt->addexp = 19;
		पूर्ण अन्यथा अगर (fmt->width == EASRC_WIDTH_24_BIT) अणु
			fmt->sample_pos = 4;
			fmt->addexp = 23;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Data Endianness
	 * 0 - Little-Endian
	 * 1 - Big-Endian
	 */
	ret = snd_pcm_क्रमmat_big_endian(raw_fmt);
	अगर (ret < 0)
		वापस ret;

	fmt->endianness = ret;

	/*
	 * Input Data sign
	 * 0b - Signed Format
	 * 1b - Unचिन्हित Format
	 */
	fmt->unsign = snd_pcm_क्रमmat_अचिन्हित(raw_fmt) > 0 ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_set_ctx_क्रमmat(काष्ठा fsl_asrc_pair *ctx,
				    snd_pcm_क्रमmat_t *in_raw_क्रमmat,
				    snd_pcm_क्रमmat_t *out_raw_क्रमmat)
अणु
	काष्ठा fsl_asrc *easrc = ctx->asrc;
	काष्ठा fsl_easrc_ctx_priv *ctx_priv = ctx->निजी;
	काष्ठा fsl_easrc_data_fmt *in_fmt = &ctx_priv->in_params.fmt;
	काष्ठा fsl_easrc_data_fmt *out_fmt = &ctx_priv->out_params.fmt;
	पूर्णांक ret = 0;

	/* Get the bitfield values क्रम input data क्रमmat */
	अगर (in_raw_क्रमmat && out_raw_क्रमmat) अणु
		ret = fsl_easrc_process_क्रमmat(ctx, in_fmt, *in_raw_क्रमmat);
		अगर (ret)
			वापस ret;
	पूर्ण

	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx->index),
			   EASRC_CC_BPS_MASK,
			   EASRC_CC_BPS(in_fmt->width));
	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx->index),
			   EASRC_CC_ENDIANNESS_MASK,
			   in_fmt->endianness << EASRC_CC_ENDIANNESS_SHIFT);
	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx->index),
			   EASRC_CC_FMT_MASK,
			   in_fmt->भग्नing_poपूर्णांक << EASRC_CC_FMT_SHIFT);
	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx->index),
			   EASRC_CC_INSIGN_MASK,
			   in_fmt->unsign << EASRC_CC_INSIGN_SHIFT);

	/* In Sample Position */
	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx->index),
			   EASRC_CC_SAMPLE_POS_MASK,
			   EASRC_CC_SAMPLE_POS(in_fmt->sample_pos));

	/* Get the bitfield values क्रम input data क्रमmat */
	अगर (in_raw_क्रमmat && out_raw_क्रमmat) अणु
		ret = fsl_easrc_process_क्रमmat(ctx, out_fmt, *out_raw_क्रमmat);
		अगर (ret)
			वापस ret;
	पूर्ण

	regmap_update_bits(easrc->regmap, REG_EASRC_COC(ctx->index),
			   EASRC_COC_BPS_MASK,
			   EASRC_COC_BPS(out_fmt->width));
	regmap_update_bits(easrc->regmap, REG_EASRC_COC(ctx->index),
			   EASRC_COC_ENDIANNESS_MASK,
			   out_fmt->endianness << EASRC_COC_ENDIANNESS_SHIFT);
	regmap_update_bits(easrc->regmap, REG_EASRC_COC(ctx->index),
			   EASRC_COC_FMT_MASK,
			   out_fmt->भग्नing_poपूर्णांक << EASRC_COC_FMT_SHIFT);
	regmap_update_bits(easrc->regmap, REG_EASRC_COC(ctx->index),
			   EASRC_COC_OUTSIGN_MASK,
			   out_fmt->unsign << EASRC_COC_OUTSIGN_SHIFT);

	/* Out Sample Position */
	regmap_update_bits(easrc->regmap, REG_EASRC_COC(ctx->index),
			   EASRC_COC_SAMPLE_POS_MASK,
			   EASRC_COC_SAMPLE_POS(out_fmt->sample_pos));

	regmap_update_bits(easrc->regmap, REG_EASRC_COC(ctx->index),
			   EASRC_COC_IEC_EN_MASK,
			   out_fmt->iec958 << EASRC_COC_IEC_EN_SHIFT);

	वापस ret;
पूर्ण

/*
 * The ASRC provides पूर्णांकerleaving support in hardware to ensure that a
 * variety of sample sources can be पूर्णांकernally combined
 * to conक्रमm with this क्रमmat. Interleaving parameters are accessed
 * through the ASRC_CTRL_IN_ACCESSa and ASRC_CTRL_OUT_ACCESSa रेजिस्टरs
 */
अटल पूर्णांक fsl_easrc_set_ctx_organziation(काष्ठा fsl_asrc_pair *ctx)
अणु
	काष्ठा fsl_easrc_ctx_priv *ctx_priv;
	काष्ठा fsl_asrc *easrc;

	अगर (!ctx)
		वापस -ENODEV;

	easrc = ctx->asrc;
	ctx_priv = ctx->निजी;

	/* input पूर्णांकerleaving parameters */
	regmap_update_bits(easrc->regmap, REG_EASRC_CIA(ctx->index),
			   EASRC_CIA_ITER_MASK,
			   EASRC_CIA_ITER(ctx_priv->in_params.iterations));
	regmap_update_bits(easrc->regmap, REG_EASRC_CIA(ctx->index),
			   EASRC_CIA_GRLEN_MASK,
			   EASRC_CIA_GRLEN(ctx_priv->in_params.group_len));
	regmap_update_bits(easrc->regmap, REG_EASRC_CIA(ctx->index),
			   EASRC_CIA_ACCLEN_MASK,
			   EASRC_CIA_ACCLEN(ctx_priv->in_params.access_len));

	/* output पूर्णांकerleaving parameters */
	regmap_update_bits(easrc->regmap, REG_EASRC_COA(ctx->index),
			   EASRC_COA_ITER_MASK,
			   EASRC_COA_ITER(ctx_priv->out_params.iterations));
	regmap_update_bits(easrc->regmap, REG_EASRC_COA(ctx->index),
			   EASRC_COA_GRLEN_MASK,
			   EASRC_COA_GRLEN(ctx_priv->out_params.group_len));
	regmap_update_bits(easrc->regmap, REG_EASRC_COA(ctx->index),
			   EASRC_COA_ACCLEN_MASK,
			   EASRC_COA_ACCLEN(ctx_priv->out_params.access_len));

	वापस 0;
पूर्ण

/*
 * Request one of the available contexts
 *
 * Returns a negative number on error and >=0 as context id
 * on success
 */
अटल पूर्णांक fsl_easrc_request_context(पूर्णांक channels, काष्ठा fsl_asrc_pair *ctx)
अणु
	क्रमागत asrc_pair_index index = ASRC_INVALID_PAIR;
	काष्ठा fsl_asrc *easrc = ctx->asrc;
	काष्ठा device *dev;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक ret = 0;
	पूर्णांक i;

	dev = &easrc->pdev->dev;

	spin_lock_irqsave(&easrc->lock, lock_flags);

	क्रम (i = ASRC_PAIR_A; i < EASRC_CTX_MAX_NUM; i++) अणु
		अगर (easrc->pair[i])
			जारी;

		index = i;
		अवरोध;
	पूर्ण

	अगर (index == ASRC_INVALID_PAIR) अणु
		dev_err(dev, "all contexts are busy\n");
		ret = -EBUSY;
	पूर्ण अन्यथा अगर (channels > easrc->channel_avail) अणु
		dev_err(dev, "can't give the required channels: %d\n",
			channels);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ctx->index = index;
		ctx->channels = channels;
		easrc->pair[index] = ctx;
		easrc->channel_avail -= channels;
	पूर्ण

	spin_unlock_irqrestore(&easrc->lock, lock_flags);

	वापस ret;
पूर्ण

/*
 * Release the context
 *
 * This funciton is मुख्यly करोing the revert thing in request context
 */
अटल व्योम fsl_easrc_release_context(काष्ठा fsl_asrc_pair *ctx)
अणु
	अचिन्हित दीर्घ lock_flags;
	काष्ठा fsl_asrc *easrc;

	अगर (!ctx)
		वापस;

	easrc = ctx->asrc;

	spin_lock_irqsave(&easrc->lock, lock_flags);

	fsl_easrc_release_slot(easrc, ctx->index);

	easrc->channel_avail += ctx->channels;
	easrc->pair[ctx->index] = शून्य;

	spin_unlock_irqrestore(&easrc->lock, lock_flags);
पूर्ण

/*
 * Start the context
 *
 * Enable the DMA request and context
 */
अटल पूर्णांक fsl_easrc_start_context(काष्ठा fsl_asrc_pair *ctx)
अणु
	काष्ठा fsl_asrc *easrc = ctx->asrc;

	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx->index),
			   EASRC_CC_FWMDE_MASK, EASRC_CC_FWMDE);
	regmap_update_bits(easrc->regmap, REG_EASRC_COC(ctx->index),
			   EASRC_COC_FWMDE_MASK, EASRC_COC_FWMDE);
	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx->index),
			   EASRC_CC_EN_MASK, EASRC_CC_EN);
	वापस 0;
पूर्ण

/*
 * Stop the context
 *
 * Disable the DMA request and context
 */
अटल पूर्णांक fsl_easrc_stop_context(काष्ठा fsl_asrc_pair *ctx)
अणु
	काष्ठा fsl_asrc *easrc = ctx->asrc;
	पूर्णांक val, i;
	पूर्णांक size;
	पूर्णांक retry = 200;

	regmap_पढ़ो(easrc->regmap, REG_EASRC_CC(ctx->index), &val);

	अगर (val & EASRC_CC_EN_MASK) अणु
		regmap_update_bits(easrc->regmap,
				   REG_EASRC_CC(ctx->index),
				   EASRC_CC_STOP_MASK, EASRC_CC_STOP);
		करो अणु
			regmap_पढ़ो(easrc->regmap, REG_EASRC_SFS(ctx->index), &val);
			val &= EASRC_SFS_NSGO_MASK;
			size = val >> EASRC_SFS_NSGO_SHIFT;

			/* Read FIFO, drop the data */
			क्रम (i = 0; i < size * ctx->channels; i++)
				regmap_पढ़ो(easrc->regmap, REG_EASRC_RDFIFO(ctx->index), &val);
			/* Check RUN_STOP_DONE */
			regmap_पढ़ो(easrc->regmap, REG_EASRC_IRQF, &val);
			अगर (val & EASRC_IRQF_RSD(1 << ctx->index)) अणु
				/*Clear RUN_STOP_DONE*/
				regmap_ग_लिखो_bits(easrc->regmap,
						  REG_EASRC_IRQF,
						  EASRC_IRQF_RSD(1 << ctx->index),
						  EASRC_IRQF_RSD(1 << ctx->index));
				अवरोध;
			पूर्ण
			udelay(100);
		पूर्ण जबतक (--retry);

		अगर (retry == 0)
			dev_warn(&easrc->pdev->dev, "RUN STOP fail\n");
	पूर्ण

	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx->index),
			   EASRC_CC_EN_MASK | EASRC_CC_STOP_MASK, 0);
	regmap_update_bits(easrc->regmap, REG_EASRC_CC(ctx->index),
			   EASRC_CC_FWMDE_MASK, 0);
	regmap_update_bits(easrc->regmap, REG_EASRC_COC(ctx->index),
			   EASRC_COC_FWMDE_MASK, 0);
	वापस 0;
पूर्ण

अटल काष्ठा dma_chan *fsl_easrc_get_dma_channel(काष्ठा fsl_asrc_pair *ctx,
						  bool dir)
अणु
	काष्ठा fsl_asrc *easrc = ctx->asrc;
	क्रमागत asrc_pair_index index = ctx->index;
	अक्षर name[8];

	/* Example of dma name: ctx0_rx */
	प्र_लिखो(name, "ctx%c_%cx", index + '0', dir == IN ? 'r' : 't');

	वापस dma_request_slave_channel(&easrc->pdev->dev, name);
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक easrc_rates[] = अणु
	8000, 11025, 12000, 16000,
	22050, 24000, 32000, 44100,
	48000, 64000, 88200, 96000,
	128000, 176400, 192000, 256000,
	352800, 384000, 705600, 768000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list easrc_rate_स्थिरraपूर्णांकs = अणु
	.count = ARRAY_SIZE(easrc_rates),
	.list = easrc_rates,
पूर्ण;

अटल पूर्णांक fsl_easrc_startup(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  &easrc_rate_स्थिरraपूर्णांकs);
पूर्ण

अटल पूर्णांक fsl_easrc_trigger(काष्ठा snd_pcm_substream *substream,
			     पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *ctx = runसमय->निजी_data;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = fsl_easrc_start_context(ctx);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = fsl_easrc_stop_context(ctx);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_asrc *easrc = snd_soc_dai_get_drvdata(dai);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा device *dev = &easrc->pdev->dev;
	काष्ठा fsl_asrc_pair *ctx = runसमय->निजी_data;
	काष्ठा fsl_easrc_ctx_priv *ctx_priv = ctx->निजी;
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक rate = params_rate(params);
	snd_pcm_क्रमmat_t क्रमmat = params_क्रमmat(params);
	पूर्णांक ret;

	ret = fsl_easrc_request_context(channels, ctx);
	अगर (ret) अणु
		dev_err(dev, "failed to request context\n");
		वापस ret;
	पूर्ण

	ctx_priv->ctx_streams |= BIT(substream->stream);

	/*
	 * Set the input and output ratio so we can compute
	 * the resampling ratio in RS_LOW/HIGH
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ctx_priv->in_params.sample_rate = rate;
		ctx_priv->in_params.sample_क्रमmat = क्रमmat;
		ctx_priv->out_params.sample_rate = easrc->asrc_rate;
		ctx_priv->out_params.sample_क्रमmat = easrc->asrc_क्रमmat;
	पूर्ण अन्यथा अणु
		ctx_priv->out_params.sample_rate = rate;
		ctx_priv->out_params.sample_क्रमmat = क्रमmat;
		ctx_priv->in_params.sample_rate = easrc->asrc_rate;
		ctx_priv->in_params.sample_क्रमmat = easrc->asrc_क्रमmat;
	पूर्ण

	ctx->channels = channels;
	ctx_priv->in_params.fअगरo_wपंचांगk  = 0x20;
	ctx_priv->out_params.fअगरo_wपंचांगk = 0x20;

	/*
	 * Do only rate conversion and keep the same क्रमmat क्रम input
	 * and output data
	 */
	ret = fsl_easrc_set_ctx_क्रमmat(ctx,
				       &ctx_priv->in_params.sample_क्रमmat,
				       &ctx_priv->out_params.sample_क्रमmat);
	अगर (ret) अणु
		dev_err(dev, "failed to set format %d", ret);
		वापस ret;
	पूर्ण

	ret = fsl_easrc_config_context(easrc, ctx->index);
	अगर (ret) अणु
		dev_err(dev, "failed to config context\n");
		वापस ret;
	पूर्ण

	ctx_priv->in_params.iterations = 1;
	ctx_priv->in_params.group_len = ctx->channels;
	ctx_priv->in_params.access_len = ctx->channels;
	ctx_priv->out_params.iterations = 1;
	ctx_priv->out_params.group_len = ctx->channels;
	ctx_priv->out_params.access_len = ctx->channels;

	ret = fsl_easrc_set_ctx_organziation(ctx);
	अगर (ret) अणु
		dev_err(dev, "failed to set fifo organization\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा fsl_asrc_pair *ctx = runसमय->निजी_data;
	काष्ठा fsl_easrc_ctx_priv *ctx_priv;

	अगर (!ctx)
		वापस -EINVAL;

	ctx_priv = ctx->निजी;

	अगर (ctx_priv->ctx_streams & BIT(substream->stream)) अणु
		ctx_priv->ctx_streams &= ~BIT(substream->stream);
		fsl_easrc_release_context(ctx);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_easrc_dai_ops = अणु
	.startup = fsl_easrc_startup,
	.trigger = fsl_easrc_trigger,
	.hw_params = fsl_easrc_hw_params,
	.hw_मुक्त = fsl_easrc_hw_मुक्त,
पूर्ण;

अटल पूर्णांक fsl_easrc_dai_probe(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा fsl_asrc *easrc = dev_get_drvdata(cpu_dai->dev);

	snd_soc_dai_init_dma_data(cpu_dai,
				  &easrc->dma_params_tx,
				  &easrc->dma_params_rx);
	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver fsl_easrc_dai = अणु
	.probe = fsl_easrc_dai_probe,
	.playback = अणु
		.stream_name = "ASRC-Playback",
		.channels_min = 1,
		.channels_max = 32,
		.rate_min = 8000,
		.rate_max = 768000,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = FSL_EASRC_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "ASRC-Capture",
		.channels_min = 1,
		.channels_max = 32,
		.rate_min = 8000,
		.rate_max = 768000,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = FSL_EASRC_FORMATS |
			   SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE,
	पूर्ण,
	.ops = &fsl_easrc_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsl_easrc_component = अणु
	.name		= "fsl-easrc-dai",
	.controls       = fsl_easrc_snd_controls,
	.num_controls   = ARRAY_SIZE(fsl_easrc_snd_controls),
पूर्ण;

अटल स्थिर काष्ठा reg_शेष fsl_easrc_reg_शेषs[] = अणु
	अणुREG_EASRC_WRFIFO(0),	0x00000000पूर्ण,
	अणुREG_EASRC_WRFIFO(1),	0x00000000पूर्ण,
	अणुREG_EASRC_WRFIFO(2),	0x00000000पूर्ण,
	अणुREG_EASRC_WRFIFO(3),	0x00000000पूर्ण,
	अणुREG_EASRC_RDFIFO(0),	0x00000000पूर्ण,
	अणुREG_EASRC_RDFIFO(1),	0x00000000पूर्ण,
	अणुREG_EASRC_RDFIFO(2),	0x00000000पूर्ण,
	अणुREG_EASRC_RDFIFO(3),	0x00000000पूर्ण,
	अणुREG_EASRC_CC(0),	0x00000000पूर्ण,
	अणुREG_EASRC_CC(1),	0x00000000पूर्ण,
	अणुREG_EASRC_CC(2),	0x00000000पूर्ण,
	अणुREG_EASRC_CC(3),	0x00000000पूर्ण,
	अणुREG_EASRC_CCE1(0),	0x00000000पूर्ण,
	अणुREG_EASRC_CCE1(1),	0x00000000पूर्ण,
	अणुREG_EASRC_CCE1(2),	0x00000000पूर्ण,
	अणुREG_EASRC_CCE1(3),	0x00000000पूर्ण,
	अणुREG_EASRC_CCE2(0),	0x00000000पूर्ण,
	अणुREG_EASRC_CCE2(1),	0x00000000पूर्ण,
	अणुREG_EASRC_CCE2(2),	0x00000000पूर्ण,
	अणुREG_EASRC_CCE2(3),	0x00000000पूर्ण,
	अणुREG_EASRC_CIA(0),	0x00000000पूर्ण,
	अणुREG_EASRC_CIA(1),	0x00000000पूर्ण,
	अणुREG_EASRC_CIA(2),	0x00000000पूर्ण,
	अणुREG_EASRC_CIA(3),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R0(0),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R0(1),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R0(2),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R0(3),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R1(0),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R1(1),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R1(2),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R1(3),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R2(0),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R2(1),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R2(2),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R2(3),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R3(0),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R3(1),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R3(2),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS0R3(3),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R0(0),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R0(1),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R0(2),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R0(3),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R1(0),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R1(1),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R1(2),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R1(3),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R2(0),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R2(1),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R2(2),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R2(3),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R3(0),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R3(1),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R3(2),	0x00000000पूर्ण,
	अणुREG_EASRC_DPCS1R3(3),	0x00000000पूर्ण,
	अणुREG_EASRC_COC(0),	0x00000000पूर्ण,
	अणुREG_EASRC_COC(1),	0x00000000पूर्ण,
	अणुREG_EASRC_COC(2),	0x00000000पूर्ण,
	अणुREG_EASRC_COC(3),	0x00000000पूर्ण,
	अणुREG_EASRC_COA(0),	0x00000000पूर्ण,
	अणुREG_EASRC_COA(1),	0x00000000पूर्ण,
	अणुREG_EASRC_COA(2),	0x00000000पूर्ण,
	अणुREG_EASRC_COA(3),	0x00000000पूर्ण,
	अणुREG_EASRC_SFS(0),	0x00000000पूर्ण,
	अणुREG_EASRC_SFS(1),	0x00000000पूर्ण,
	अणुREG_EASRC_SFS(2),	0x00000000पूर्ण,
	अणुREG_EASRC_SFS(3),	0x00000000पूर्ण,
	अणुREG_EASRC_RRL(0),	0x00000000पूर्ण,
	अणुREG_EASRC_RRL(1),	0x00000000पूर्ण,
	अणुREG_EASRC_RRL(2),	0x00000000पूर्ण,
	अणुREG_EASRC_RRL(3),	0x00000000पूर्ण,
	अणुREG_EASRC_RRH(0),	0x00000000पूर्ण,
	अणुREG_EASRC_RRH(1),	0x00000000पूर्ण,
	अणुREG_EASRC_RRH(2),	0x00000000पूर्ण,
	अणुREG_EASRC_RRH(3),	0x00000000पूर्ण,
	अणुREG_EASRC_RUC(0),	0x00000000पूर्ण,
	अणुREG_EASRC_RUC(1),	0x00000000पूर्ण,
	अणुREG_EASRC_RUC(2),	0x00000000पूर्ण,
	अणुREG_EASRC_RUC(3),	0x00000000पूर्ण,
	अणुREG_EASRC_RUR(0),	0x7FFFFFFFपूर्ण,
	अणुREG_EASRC_RUR(1),	0x7FFFFFFFपूर्ण,
	अणुREG_EASRC_RUR(2),	0x7FFFFFFFपूर्ण,
	अणुREG_EASRC_RUR(3),	0x7FFFFFFFपूर्ण,
	अणुREG_EASRC_RCTCL,	0x00000000पूर्ण,
	अणुREG_EASRC_RCTCH,	0x00000000पूर्ण,
	अणुREG_EASRC_PCF(0),	0x00000000पूर्ण,
	अणुREG_EASRC_PCF(1),	0x00000000पूर्ण,
	अणुREG_EASRC_PCF(2),	0x00000000पूर्ण,
	अणुREG_EASRC_PCF(3),	0x00000000पूर्ण,
	अणुREG_EASRC_CRCM,	0x00000000पूर्ण,
	अणुREG_EASRC_CRCC,	0x00000000पूर्ण,
	अणुREG_EASRC_IRQC,	0x00000FFFपूर्ण,
	अणुREG_EASRC_IRQF,	0x00000000पूर्ण,
	अणुREG_EASRC_CS0(0),	0x00000000पूर्ण,
	अणुREG_EASRC_CS0(1),	0x00000000पूर्ण,
	अणुREG_EASRC_CS0(2),	0x00000000पूर्ण,
	अणुREG_EASRC_CS0(3),	0x00000000पूर्ण,
	अणुREG_EASRC_CS1(0),	0x00000000पूर्ण,
	अणुREG_EASRC_CS1(1),	0x00000000पूर्ण,
	अणुREG_EASRC_CS1(2),	0x00000000पूर्ण,
	अणुREG_EASRC_CS1(3),	0x00000000पूर्ण,
	अणुREG_EASRC_CS2(0),	0x00000000पूर्ण,
	अणुREG_EASRC_CS2(1),	0x00000000पूर्ण,
	अणुREG_EASRC_CS2(2),	0x00000000पूर्ण,
	अणुREG_EASRC_CS2(3),	0x00000000पूर्ण,
	अणुREG_EASRC_CS3(0),	0x00000000पूर्ण,
	अणुREG_EASRC_CS3(1),	0x00000000पूर्ण,
	अणुREG_EASRC_CS3(2),	0x00000000पूर्ण,
	अणुREG_EASRC_CS3(3),	0x00000000पूर्ण,
	अणुREG_EASRC_CS4(0),	0x00000000पूर्ण,
	अणुREG_EASRC_CS4(1),	0x00000000पूर्ण,
	अणुREG_EASRC_CS4(2),	0x00000000पूर्ण,
	अणुREG_EASRC_CS4(3),	0x00000000पूर्ण,
	अणुREG_EASRC_CS5(0),	0x00000000पूर्ण,
	अणुREG_EASRC_CS5(1),	0x00000000पूर्ण,
	अणुREG_EASRC_CS5(2),	0x00000000पूर्ण,
	अणुREG_EASRC_CS5(3),	0x00000000पूर्ण,
	अणुREG_EASRC_DBGC,	0x00000000पूर्ण,
	अणुREG_EASRC_DBGS,	0x00000000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range fsl_easrc_पढ़ोable_ranges[] = अणु
	regmap_reg_range(REG_EASRC_RDFIFO(0), REG_EASRC_RCTCH),
	regmap_reg_range(REG_EASRC_PCF(0), REG_EASRC_PCF(3)),
	regmap_reg_range(REG_EASRC_CRCC, REG_EASRC_DBGS),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table fsl_easrc_पढ़ोable_table = अणु
	.yes_ranges = fsl_easrc_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(fsl_easrc_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range fsl_easrc_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(REG_EASRC_WRFIFO(0), REG_EASRC_WRFIFO(3)),
	regmap_reg_range(REG_EASRC_CC(0), REG_EASRC_COA(3)),
	regmap_reg_range(REG_EASRC_RRL(0), REG_EASRC_RCTCH),
	regmap_reg_range(REG_EASRC_PCF(0), REG_EASRC_DBGC),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table fsl_easrc_ग_लिखोable_table = अणु
	.yes_ranges = fsl_easrc_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(fsl_easrc_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range fsl_easrc_अस्थिरable_ranges[] = अणु
	regmap_reg_range(REG_EASRC_RDFIFO(0), REG_EASRC_RDFIFO(3)),
	regmap_reg_range(REG_EASRC_SFS(0), REG_EASRC_SFS(3)),
	regmap_reg_range(REG_EASRC_IRQF, REG_EASRC_IRQF),
	regmap_reg_range(REG_EASRC_DBGS, REG_EASRC_DBGS),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table fsl_easrc_अस्थिरable_table = अणु
	.yes_ranges = fsl_easrc_अस्थिरable_ranges,
	.n_yes_ranges = ARRAY_SIZE(fsl_easrc_अस्थिरable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config fsl_easrc_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,

	.max_रेजिस्टर = REG_EASRC_DBGS,
	.reg_शेषs = fsl_easrc_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(fsl_easrc_reg_शेषs),
	.rd_table = &fsl_easrc_पढ़ोable_table,
	.wr_table = &fsl_easrc_ग_लिखोable_table,
	.अस्थिर_table = &fsl_easrc_अस्थिरable_table,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

#अगर_घोषित DEBUG
अटल व्योम fsl_easrc_dump_firmware(काष्ठा fsl_asrc *easrc)
अणु
	काष्ठा fsl_easrc_priv *easrc_priv = easrc->निजी;
	काष्ठा asrc_firmware_hdr *firm = easrc_priv->firmware_hdr;
	काष्ठा पूर्णांकerp_params *पूर्णांकerp = easrc_priv->पूर्णांकerp;
	काष्ठा prefil_params *prefil = easrc_priv->prefil;
	काष्ठा device *dev = &easrc->pdev->dev;
	पूर्णांक i;

	अगर (firm->magic != FIRMWARE_MAGIC) अणु
		dev_err(dev, "Wrong magic. Something went wrong!");
		वापस;
	पूर्ण

	dev_dbg(dev, "Firmware v%u dump:\n", firm->firmware_version);
	dev_dbg(dev, "Num prefilter scenarios: %u\n", firm->prefil_scen);
	dev_dbg(dev, "Num interpolation scenarios: %u\n", firm->पूर्णांकerp_scen);
	dev_dbg(dev, "\nInterpolation scenarios:\n");

	क्रम (i = 0; i < firm->पूर्णांकerp_scen; i++) अणु
		अगर (पूर्णांकerp[i].magic != FIRMWARE_MAGIC) अणु
			dev_dbg(dev, "%d. wrong interp magic: %x\n",
				i, पूर्णांकerp[i].magic);
			जारी;
		पूर्ण
		dev_dbg(dev, "%d. taps: %u, phases: %u, center: %llu\n", i,
			पूर्णांकerp[i].num_taps, पूर्णांकerp[i].num_phases,
			पूर्णांकerp[i].center_tap);
	पूर्ण

	क्रम (i = 0; i < firm->prefil_scen; i++) अणु
		अगर (prefil[i].magic != FIRMWARE_MAGIC) अणु
			dev_dbg(dev, "%d. wrong prefil magic: %x\n",
				i, prefil[i].magic);
			जारी;
		पूर्ण
		dev_dbg(dev, "%d. insr: %u, outsr: %u, st1: %u, st2: %u\n", i,
			prefil[i].insr, prefil[i].outsr,
			prefil[i].st1_taps, prefil[i].st2_taps);
	पूर्ण

	dev_dbg(dev, "end of firmware dump\n");
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक fsl_easrc_get_firmware(काष्ठा fsl_asrc *easrc)
अणु
	काष्ठा fsl_easrc_priv *easrc_priv;
	स्थिर काष्ठा firmware **fw_p;
	u32 pnum, inum, offset;
	स्थिर u8 *data;
	पूर्णांक ret;

	अगर (!easrc)
		वापस -EINVAL;

	easrc_priv = easrc->निजी;
	fw_p = &easrc_priv->fw;

	ret = request_firmware(fw_p, easrc_priv->fw_name, &easrc->pdev->dev);
	अगर (ret)
		वापस ret;

	data = easrc_priv->fw->data;

	easrc_priv->firmware_hdr = (काष्ठा asrc_firmware_hdr *)data;
	pnum = easrc_priv->firmware_hdr->prefil_scen;
	inum = easrc_priv->firmware_hdr->पूर्णांकerp_scen;

	अगर (inum) अणु
		offset = माप(काष्ठा asrc_firmware_hdr);
		easrc_priv->पूर्णांकerp = (काष्ठा पूर्णांकerp_params *)(data + offset);
	पूर्ण

	अगर (pnum) अणु
		offset = माप(काष्ठा asrc_firmware_hdr) +
				inum * माप(काष्ठा पूर्णांकerp_params);
		easrc_priv->prefil = (काष्ठा prefil_params *)(data + offset);
	पूर्ण

#अगर_घोषित DEBUG
	fsl_easrc_dump_firmware(easrc);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल irqवापस_t fsl_easrc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_asrc *easrc = (काष्ठा fsl_asrc *)dev_id;
	काष्ठा device *dev = &easrc->pdev->dev;
	पूर्णांक val;

	regmap_पढ़ो(easrc->regmap, REG_EASRC_IRQF, &val);

	अगर (val & EASRC_IRQF_OER_MASK)
		dev_dbg(dev, "output FIFO underflow\n");

	अगर (val & EASRC_IRQF_IFO_MASK)
		dev_dbg(dev, "input FIFO overflow\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fsl_easrc_get_fअगरo_addr(u8 dir, क्रमागत asrc_pair_index index)
अणु
	वापस REG_EASRC_FIFO(dir, index);
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_easrc_dt_ids[] = अणु
	अणु .compatible = "fsl,imx8mn-easrc",पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_easrc_dt_ids);

अटल पूर्णांक fsl_easrc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_easrc_priv *easrc_priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fsl_asrc *easrc;
	काष्ठा resource *res;
	काष्ठा device_node *np;
	व्योम __iomem *regs;
	पूर्णांक ret, irq;

	easrc = devm_kzalloc(dev, माप(*easrc), GFP_KERNEL);
	अगर (!easrc)
		वापस -ENOMEM;

	easrc_priv = devm_kzalloc(dev, माप(*easrc_priv), GFP_KERNEL);
	अगर (!easrc_priv)
		वापस -ENOMEM;

	easrc->pdev = pdev;
	easrc->निजी = easrc_priv;
	np = dev->of_node;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	easrc->paddr = res->start;

	easrc->regmap = devm_regmap_init_mmio(dev, regs, &fsl_easrc_regmap_config);
	अगर (IS_ERR(easrc->regmap)) अणु
		dev_err(dev, "failed to init regmap");
		वापस PTR_ERR(easrc->regmap);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_err(dev, "no irq for node %pOF\n", np);
		वापस irq;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, fsl_easrc_isr, 0,
			       dev_name(dev), easrc);
	अगर (ret) अणु
		dev_err(dev, "failed to claim irq %u: %d\n", irq, ret);
		वापस ret;
	पूर्ण

	easrc->mem_clk = devm_clk_get(dev, "mem");
	अगर (IS_ERR(easrc->mem_clk)) अणु
		dev_err(dev, "failed to get mem clock\n");
		वापस PTR_ERR(easrc->mem_clk);
	पूर्ण

	/* Set शेष value */
	easrc->channel_avail = 32;
	easrc->get_dma_channel = fsl_easrc_get_dma_channel;
	easrc->request_pair = fsl_easrc_request_context;
	easrc->release_pair = fsl_easrc_release_context;
	easrc->get_fअगरo_addr = fsl_easrc_get_fअगरo_addr;
	easrc->pair_priv_size = माप(काष्ठा fsl_easrc_ctx_priv);

	easrc_priv->rs_num_taps = EASRC_RS_32_TAPS;
	easrc_priv->स्थिर_coeff = 0x3FF0000000000000;

	ret = of_property_पढ़ो_u32(np, "fsl,asrc-rate", &easrc->asrc_rate);
	अगर (ret) अणु
		dev_err(dev, "failed to asrc rate\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "fsl,asrc-format", &easrc->asrc_क्रमmat);
	अगर (ret) अणु
		dev_err(dev, "failed to asrc format\n");
		वापस ret;
	पूर्ण

	अगर (!(FSL_EASRC_FORMATS & (1ULL << easrc->asrc_क्रमmat))) अणु
		dev_warn(dev, "unsupported format, switching to S24_LE\n");
		easrc->asrc_क्रमmat = SNDRV_PCM_FORMAT_S24_LE;
	पूर्ण

	ret = of_property_पढ़ो_string(np, "firmware-name",
				      &easrc_priv->fw_name);
	अगर (ret) अणु
		dev_err(dev, "failed to get firmware name\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, easrc);
	pm_runसमय_enable(dev);

	spin_lock_init(&easrc->lock);

	regcache_cache_only(easrc->regmap, true);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &fsl_easrc_component,
					      &fsl_easrc_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "failed to register ASoC DAI\n");
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &fsl_asrc_component,
					      शून्य, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register ASoC platform\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_easrc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक fsl_easrc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_asrc *easrc = dev_get_drvdata(dev);
	काष्ठा fsl_easrc_priv *easrc_priv = easrc->निजी;
	अचिन्हित दीर्घ lock_flags;

	regcache_cache_only(easrc->regmap, true);

	clk_disable_unprepare(easrc->mem_clk);

	spin_lock_irqsave(&easrc->lock, lock_flags);
	easrc_priv->firmware_loaded = 0;
	spin_unlock_irqrestore(&easrc->lock, lock_flags);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक fsl_easrc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_asrc *easrc = dev_get_drvdata(dev);
	काष्ठा fsl_easrc_priv *easrc_priv = easrc->निजी;
	काष्ठा fsl_easrc_ctx_priv *ctx_priv;
	काष्ठा fsl_asrc_pair *ctx;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक ret;
	पूर्णांक i;

	ret = clk_prepare_enable(easrc->mem_clk);
	अगर (ret)
		वापस ret;

	regcache_cache_only(easrc->regmap, false);
	regcache_mark_dirty(easrc->regmap);
	regcache_sync(easrc->regmap);

	spin_lock_irqsave(&easrc->lock, lock_flags);
	अगर (easrc_priv->firmware_loaded) अणु
		spin_unlock_irqrestore(&easrc->lock, lock_flags);
		जाओ skip_load;
	पूर्ण
	easrc_priv->firmware_loaded = 1;
	spin_unlock_irqrestore(&easrc->lock, lock_flags);

	ret = fsl_easrc_get_firmware(easrc);
	अगर (ret) अणु
		dev_err(dev, "failed to get firmware\n");
		जाओ disable_mem_clk;
	पूर्ण

	/*
	 * Write Resampling Coefficients
	 * The coefficient RAM must be configured prior to beginning of
	 * any context processing within the ASRC
	 */
	ret = fsl_easrc_resampler_config(easrc);
	अगर (ret) अणु
		dev_err(dev, "resampler config failed\n");
		जाओ disable_mem_clk;
	पूर्ण

	क्रम (i = ASRC_PAIR_A; i < EASRC_CTX_MAX_NUM; i++) अणु
		ctx = easrc->pair[i];
		अगर (!ctx)
			जारी;

		ctx_priv = ctx->निजी;
		fsl_easrc_set_rs_ratio(ctx);
		ctx_priv->out_missed_sample = ctx_priv->in_filled_sample *
					      ctx_priv->out_params.sample_rate /
					      ctx_priv->in_params.sample_rate;
		अगर (ctx_priv->in_filled_sample * ctx_priv->out_params.sample_rate
		    % ctx_priv->in_params.sample_rate != 0)
			ctx_priv->out_missed_sample += 1;

		ret = fsl_easrc_ग_लिखो_pf_coeff_mem(easrc, i,
						   ctx_priv->st1_coeff,
						   ctx_priv->st1_num_taps,
						   ctx_priv->st1_addexp);
		अगर (ret)
			जाओ disable_mem_clk;

		ret = fsl_easrc_ग_लिखो_pf_coeff_mem(easrc, i,
						   ctx_priv->st2_coeff,
						   ctx_priv->st2_num_taps,
						   ctx_priv->st2_addexp);
		अगर (ret)
			जाओ disable_mem_clk;
	पूर्ण

skip_load:
	वापस 0;

disable_mem_clk:
	clk_disable_unprepare(easrc->mem_clk);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fsl_easrc_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fsl_easrc_runसमय_suspend,
			   fsl_easrc_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_easrc_driver = अणु
	.probe = fsl_easrc_probe,
	.हटाओ = fsl_easrc_हटाओ,
	.driver = अणु
		.name = "fsl-easrc",
		.pm = &fsl_easrc_pm_ops,
		.of_match_table = fsl_easrc_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(fsl_easrc_driver);

MODULE_DESCRIPTION("NXP Enhanced Asynchronous Sample Rate (eASRC) driver");
MODULE_LICENSE("GPL v2");
