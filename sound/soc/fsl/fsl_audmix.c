<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NXP AUDMIX ALSA SoC Digital Audio Interface (DAI) driver
 *
 * Copyright 2017 NXP
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#समावेश "fsl_audmix.h"

#घोषणा SOC_ENUM_SINGLE_S(xreg, xshअगरt, xtexts) \
	SOC_ENUM_SINGLE(xreg, xshअगरt, ARRAY_SIZE(xtexts), xtexts)

अटल स्थिर अक्षर
	*tdm_sel[] = अणु "TDM1", "TDM2", पूर्ण,
	*mode_sel[] = अणु "Disabled", "TDM1", "TDM2", "Mixed", पूर्ण,
	*width_sel[] = अणु "16b", "18b", "20b", "24b", "32b", पूर्ण,
	*endis_sel[] = अणु "Disabled", "Enabled", पूर्ण,
	*updn_sel[] = अणु "Downward", "Upward", पूर्ण,
	*mask_sel[] = अणु "Unmask", "Mask", पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत fsl_audmix_क्रमागत[] = अणु
/* FSL_AUDMIX_CTR क्रमागतs */
SOC_ENUM_SINGLE_S(FSL_AUDMIX_CTR, FSL_AUDMIX_CTR_MIXCLK_SHIFT, tdm_sel),
SOC_ENUM_SINGLE_S(FSL_AUDMIX_CTR, FSL_AUDMIX_CTR_OUTSRC_SHIFT, mode_sel),
SOC_ENUM_SINGLE_S(FSL_AUDMIX_CTR, FSL_AUDMIX_CTR_OUTWIDTH_SHIFT, width_sel),
SOC_ENUM_SINGLE_S(FSL_AUDMIX_CTR, FSL_AUDMIX_CTR_MASKRTDF_SHIFT, mask_sel),
SOC_ENUM_SINGLE_S(FSL_AUDMIX_CTR, FSL_AUDMIX_CTR_MASKCKDF_SHIFT, mask_sel),
SOC_ENUM_SINGLE_S(FSL_AUDMIX_CTR, FSL_AUDMIX_CTR_SYNCMODE_SHIFT, endis_sel),
SOC_ENUM_SINGLE_S(FSL_AUDMIX_CTR, FSL_AUDMIX_CTR_SYNCSRC_SHIFT, tdm_sel),
/* FSL_AUDMIX_ATCR0 क्रमागतs */
SOC_ENUM_SINGLE_S(FSL_AUDMIX_ATCR0, 0, endis_sel),
SOC_ENUM_SINGLE_S(FSL_AUDMIX_ATCR0, 1, updn_sel),
/* FSL_AUDMIX_ATCR1 क्रमागतs */
SOC_ENUM_SINGLE_S(FSL_AUDMIX_ATCR1, 0, endis_sel),
SOC_ENUM_SINGLE_S(FSL_AUDMIX_ATCR1, 1, updn_sel),
पूर्ण;

काष्ठा fsl_audmix_state अणु
	u8 tdms;
	u8 clk;
	अक्षर msg[64];
पूर्ण;

अटल स्थिर काष्ठा fsl_audmix_state prms[4][4] = अणुअणु
	/* DIS->DIS, करो nothing */
	अणु .tdms = 0, .clk = 0, .msg = "" पूर्ण,
	/* DIS->TDM1*/
	अणु .tdms = 1, .clk = 1, .msg = "DIS->TDM1: TDM1 not started!\n" पूर्ण,
	/* DIS->TDM2*/
	अणु .tdms = 2, .clk = 2, .msg = "DIS->TDM2: TDM2 not started!\n" पूर्ण,
	/* DIS->MIX */
	अणु .tdms = 3, .clk = 0, .msg = "DIS->MIX: Please start both TDMs!\n" पूर्ण
पूर्ण, अणु	/* TDM1->DIS */
	अणु .tdms = 1, .clk = 0, .msg = "TDM1->DIS: TDM1 not started!\n" पूर्ण,
	/* TDM1->TDM1, करो nothing */
	अणु .tdms = 0, .clk = 0, .msg = "" पूर्ण,
	/* TDM1->TDM2 */
	अणु .tdms = 3, .clk = 2, .msg = "TDM1->TDM2: Please start both TDMs!\n" पूर्ण,
	/* TDM1->MIX */
	अणु .tdms = 3, .clk = 0, .msg = "TDM1->MIX: Please start both TDMs!\n" पूर्ण
पूर्ण, अणु	/* TDM2->DIS */
	अणु .tdms = 2, .clk = 0, .msg = "TDM2->DIS: TDM2 not started!\n" पूर्ण,
	/* TDM2->TDM1 */
	अणु .tdms = 3, .clk = 1, .msg = "TDM2->TDM1: Please start both TDMs!\n" पूर्ण,
	/* TDM2->TDM2, करो nothing */
	अणु .tdms = 0, .clk = 0, .msg = "" पूर्ण,
	/* TDM2->MIX */
	अणु .tdms = 3, .clk = 0, .msg = "TDM2->MIX: Please start both TDMs!\n" पूर्ण
पूर्ण, अणु	/* MIX->DIS */
	अणु .tdms = 3, .clk = 0, .msg = "MIX->DIS: Please start both TDMs!\n" पूर्ण,
	/* MIX->TDM1 */
	अणु .tdms = 3, .clk = 1, .msg = "MIX->TDM1: Please start both TDMs!\n" पूर्ण,
	/* MIX->TDM2 */
	अणु .tdms = 3, .clk = 2, .msg = "MIX->TDM2: Please start both TDMs!\n" पूर्ण,
	/* MIX->MIX, करो nothing */
	अणु .tdms = 0, .clk = 0, .msg = "" पूर्ण
पूर्ण, पूर्ण;

अटल पूर्णांक fsl_audmix_state_trans(काष्ठा snd_soc_component *comp,
				  अचिन्हित पूर्णांक *mask, अचिन्हित पूर्णांक *ctr,
				  स्थिर काष्ठा fsl_audmix_state prm)
अणु
	काष्ठा fsl_audmix *priv = snd_soc_component_get_drvdata(comp);
	/* Enक्रमce all required TDMs are started */
	अगर ((priv->tdms & prm.tdms) != prm.tdms) अणु
		dev_dbg(comp->dev, "%s", prm.msg);
		वापस -EINVAL;
	पूर्ण

	चयन (prm.clk) अणु
	हाल 1:
	हाल 2:
		/* Set mix घड़ी */
		(*mask) |= FSL_AUDMIX_CTR_MIXCLK_MASK;
		(*ctr)  |= FSL_AUDMIX_CTR_MIXCLK(prm.clk - 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_audmix_put_mix_clk_src(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_audmix *priv = snd_soc_component_get_drvdata(comp);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;
	अचिन्हित पूर्णांक reg_val, val, mix_clk;

	/* Get current state */
	reg_val = snd_soc_component_पढ़ो(comp, FSL_AUDMIX_CTR);
	mix_clk = ((reg_val & FSL_AUDMIX_CTR_MIXCLK_MASK)
			>> FSL_AUDMIX_CTR_MIXCLK_SHIFT);
	val = snd_soc_क्रमागत_item_to_val(e, item[0]);

	dev_dbg(comp->dev, "TDMs=x%08x, val=x%08x\n", priv->tdms, val);

	/**
	 * Ensure the current selected mixer घड़ी is available
	 * क्रम configuration propagation
	 */
	अगर (!(priv->tdms & BIT(mix_clk))) अणु
		dev_err(comp->dev,
			"Started TDM%d needed for config propagation!\n",
			mix_clk + 1);
		वापस -EINVAL;
	पूर्ण

	अगर (!(priv->tdms & BIT(val))) अणु
		dev_err(comp->dev,
			"The selected clock source has no TDM%d enabled!\n",
			val + 1);
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
पूर्ण

अटल पूर्णांक fsl_audmix_put_out_src(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_kcontrol_chip(kcontrol);
	काष्ठा fsl_audmix *priv = snd_soc_component_get_drvdata(comp);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;
	u32 out_src, mix_clk;
	अचिन्हित पूर्णांक reg_val, val, mask = 0, ctr = 0;
	पूर्णांक ret;

	/* Get current state */
	reg_val = snd_soc_component_पढ़ो(comp, FSL_AUDMIX_CTR);

	/* "From" state */
	out_src = ((reg_val & FSL_AUDMIX_CTR_OUTSRC_MASK)
			>> FSL_AUDMIX_CTR_OUTSRC_SHIFT);
	mix_clk = ((reg_val & FSL_AUDMIX_CTR_MIXCLK_MASK)
			>> FSL_AUDMIX_CTR_MIXCLK_SHIFT);

	/* "To" state */
	val = snd_soc_क्रमागत_item_to_val(e, item[0]);

	dev_dbg(comp->dev, "TDMs=x%08x, val=x%08x\n", priv->tdms, val);

	/* Check अगर state is changing ... */
	अगर (out_src == val)
		वापस 0;
	/**
	 * Ensure the current selected mixer घड़ी is available
	 * क्रम configuration propagation
	 */
	अगर (!(priv->tdms & BIT(mix_clk))) अणु
		dev_err(comp->dev,
			"Started TDM%d needed for config propagation!\n",
			mix_clk + 1);
		वापस -EINVAL;
	पूर्ण

	/* Check state transition स्थिरraपूर्णांकs */
	ret = fsl_audmix_state_trans(comp, &mask, &ctr, prms[out_src][val]);
	अगर (ret)
		वापस ret;

	/* Complete transition to new state */
	mask |= FSL_AUDMIX_CTR_OUTSRC_MASK;
	ctr  |= FSL_AUDMIX_CTR_OUTSRC(val);

	वापस snd_soc_component_update_bits(comp, FSL_AUDMIX_CTR, mask, ctr);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new fsl_audmix_snd_controls[] = अणु
	/* FSL_AUDMIX_CTR controls */
	अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Mixing Clock Source",
		.info = snd_soc_info_क्रमागत_द्विगुन,
		.access = SNDRV_CTL_ELEM_ACCESS_WRITE,
		.put = fsl_audmix_put_mix_clk_src,
		.निजी_value = (अचिन्हित दीर्घ)&fsl_audmix_क्रमागत[0] पूर्ण,
	अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Output Source",
		.info = snd_soc_info_क्रमागत_द्विगुन,
		.access = SNDRV_CTL_ELEM_ACCESS_WRITE,
		.put = fsl_audmix_put_out_src,
		.निजी_value = (अचिन्हित दीर्घ)&fsl_audmix_क्रमागत[1] पूर्ण,
	SOC_ENUM("Output Width", fsl_audmix_क्रमागत[2]),
	SOC_ENUM("Frame Rate Diff Error", fsl_audmix_क्रमागत[3]),
	SOC_ENUM("Clock Freq Diff Error", fsl_audmix_क्रमागत[4]),
	SOC_ENUM("Sync Mode Config", fsl_audmix_क्रमागत[5]),
	SOC_ENUM("Sync Mode Clk Source", fsl_audmix_क्रमागत[6]),
	/* TDM1 Attenuation controls */
	SOC_ENUM("TDM1 Attenuation", fsl_audmix_क्रमागत[7]),
	SOC_ENUM("TDM1 Attenuation Direction", fsl_audmix_क्रमागत[8]),
	SOC_SINGLE("TDM1 Attenuation Step Divider", FSL_AUDMIX_ATCR0,
		   2, 0x00fff, 0),
	SOC_SINGLE("TDM1 Attenuation Initial Value", FSL_AUDMIX_ATIVAL0,
		   0, 0x3ffff, 0),
	SOC_SINGLE("TDM1 Attenuation Step Up Factor", FSL_AUDMIX_ATSTPUP0,
		   0, 0x3ffff, 0),
	SOC_SINGLE("TDM1 Attenuation Step Down Factor", FSL_AUDMIX_ATSTPDN0,
		   0, 0x3ffff, 0),
	SOC_SINGLE("TDM1 Attenuation Step Target", FSL_AUDMIX_ATSTPTGT0,
		   0, 0x3ffff, 0),
	/* TDM2 Attenuation controls */
	SOC_ENUM("TDM2 Attenuation", fsl_audmix_क्रमागत[9]),
	SOC_ENUM("TDM2 Attenuation Direction", fsl_audmix_क्रमागत[10]),
	SOC_SINGLE("TDM2 Attenuation Step Divider", FSL_AUDMIX_ATCR1,
		   2, 0x00fff, 0),
	SOC_SINGLE("TDM2 Attenuation Initial Value", FSL_AUDMIX_ATIVAL1,
		   0, 0x3ffff, 0),
	SOC_SINGLE("TDM2 Attenuation Step Up Factor", FSL_AUDMIX_ATSTPUP1,
		   0, 0x3ffff, 0),
	SOC_SINGLE("TDM2 Attenuation Step Down Factor", FSL_AUDMIX_ATSTPDN1,
		   0, 0x3ffff, 0),
	SOC_SINGLE("TDM2 Attenuation Step Target", FSL_AUDMIX_ATSTPTGT1,
		   0, 0x3ffff, 0),
पूर्ण;

अटल पूर्णांक fsl_audmix_dai_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	u32 mask = 0, ctr = 0;

	/* AUDMIX is working in DSP_A क्रमmat only */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* For playback the AUDMIX is slave, and क्रम record is master */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_NF:
		/* Output data will be written on positive edge of the घड़ी */
		ctr |= FSL_AUDMIX_CTR_OUTCKPOL(0);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		/* Output data will be written on negative edge of the घड़ी */
		ctr |= FSL_AUDMIX_CTR_OUTCKPOL(1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask |= FSL_AUDMIX_CTR_OUTCKPOL_MASK;

	वापस snd_soc_component_update_bits(comp, FSL_AUDMIX_CTR, mask, ctr);
पूर्ण

अटल पूर्णांक fsl_audmix_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_audmix *priv = snd_soc_dai_get_drvdata(dai);
	अचिन्हित दीर्घ lock_flags;

	/* Capture stream shall not be handled */
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		वापस 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		spin_lock_irqsave(&priv->lock, lock_flags);
		priv->tdms |= BIT(dai->driver->id);
		spin_unlock_irqrestore(&priv->lock, lock_flags);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&priv->lock, lock_flags);
		priv->tdms &= ~BIT(dai->driver->id);
		spin_unlock_irqrestore(&priv->lock, lock_flags);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_audmix_dai_ops = अणु
	.set_fmt      = fsl_audmix_dai_set_fmt,
	.trigger      = fsl_audmix_dai_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver fsl_audmix_dai[] = अणु
	अणु
		.id   = 0,
		.name = "audmix-0",
		.playback = अणु
			.stream_name = "AUDMIX-Playback-0",
			.channels_min = 8,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 96000,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = FSL_AUDMIX_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AUDMIX-Capture-0",
			.channels_min = 8,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 96000,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = FSL_AUDMIX_FORMATS,
		पूर्ण,
		.ops = &fsl_audmix_dai_ops,
	पूर्ण,
	अणु
		.id   = 1,
		.name = "audmix-1",
		.playback = अणु
			.stream_name = "AUDMIX-Playback-1",
			.channels_min = 8,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 96000,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = FSL_AUDMIX_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AUDMIX-Capture-1",
			.channels_min = 8,
			.channels_max = 8,
			.rate_min = 8000,
			.rate_max = 96000,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = FSL_AUDMIX_FORMATS,
		पूर्ण,
		.ops = &fsl_audmix_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsl_audmix_component = अणु
	.name		  = "fsl-audmix-dai",
	.controls	  = fsl_audmix_snd_controls,
	.num_controls	  = ARRAY_SIZE(fsl_audmix_snd_controls),
पूर्ण;

अटल bool fsl_audmix_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल FSL_AUDMIX_CTR:
	हाल FSL_AUDMIX_STR:
	हाल FSL_AUDMIX_ATCR0:
	हाल FSL_AUDMIX_ATIVAL0:
	हाल FSL_AUDMIX_ATSTPUP0:
	हाल FSL_AUDMIX_ATSTPDN0:
	हाल FSL_AUDMIX_ATSTPTGT0:
	हाल FSL_AUDMIX_ATTNVAL0:
	हाल FSL_AUDMIX_ATSTP0:
	हाल FSL_AUDMIX_ATCR1:
	हाल FSL_AUDMIX_ATIVAL1:
	हाल FSL_AUDMIX_ATSTPUP1:
	हाल FSL_AUDMIX_ATSTPDN1:
	हाल FSL_AUDMIX_ATSTPTGT1:
	हाल FSL_AUDMIX_ATTNVAL1:
	हाल FSL_AUDMIX_ATSTP1:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_audmix_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल FSL_AUDMIX_CTR:
	हाल FSL_AUDMIX_ATCR0:
	हाल FSL_AUDMIX_ATIVAL0:
	हाल FSL_AUDMIX_ATSTPUP0:
	हाल FSL_AUDMIX_ATSTPDN0:
	हाल FSL_AUDMIX_ATSTPTGT0:
	हाल FSL_AUDMIX_ATCR1:
	हाल FSL_AUDMIX_ATIVAL1:
	हाल FSL_AUDMIX_ATSTPUP1:
	हाल FSL_AUDMIX_ATSTPDN1:
	हाल FSL_AUDMIX_ATSTPTGT1:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_शेष fsl_audmix_reg[] = अणु
	अणु FSL_AUDMIX_CTR,       0x00060 पूर्ण,
	अणु FSL_AUDMIX_STR,       0x00003 पूर्ण,
	अणु FSL_AUDMIX_ATCR0,     0x00000 पूर्ण,
	अणु FSL_AUDMIX_ATIVAL0,   0x3FFFF पूर्ण,
	अणु FSL_AUDMIX_ATSTPUP0,  0x2AAAA पूर्ण,
	अणु FSL_AUDMIX_ATSTPDN0,  0x30000 पूर्ण,
	अणु FSL_AUDMIX_ATSTPTGT0, 0x00010 पूर्ण,
	अणु FSL_AUDMIX_ATTNVAL0,  0x00000 पूर्ण,
	अणु FSL_AUDMIX_ATSTP0,    0x00000 पूर्ण,
	अणु FSL_AUDMIX_ATCR1,     0x00000 पूर्ण,
	अणु FSL_AUDMIX_ATIVAL1,   0x3FFFF पूर्ण,
	अणु FSL_AUDMIX_ATSTPUP1,  0x2AAAA पूर्ण,
	अणु FSL_AUDMIX_ATSTPDN1,  0x30000 पूर्ण,
	अणु FSL_AUDMIX_ATSTPTGT1, 0x00010 पूर्ण,
	अणु FSL_AUDMIX_ATTNVAL1,  0x00000 पूर्ण,
	अणु FSL_AUDMIX_ATSTP1,    0x00000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config fsl_audmix_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = FSL_AUDMIX_ATSTP1,
	.reg_शेषs = fsl_audmix_reg,
	.num_reg_शेषs = ARRAY_SIZE(fsl_audmix_reg),
	.पढ़ोable_reg = fsl_audmix_पढ़ोable_reg,
	.ग_लिखोable_reg = fsl_audmix_ग_लिखोable_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_audmix_ids[] = अणु
	अणु
		.compatible = "fsl,imx8qm-audmix",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_audmix_ids);

अटल पूर्णांक fsl_audmix_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fsl_audmix *priv;
	व्योम __iomem *regs;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* Get the addresses */
	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	priv->regmap = devm_regmap_init_mmio(dev, regs, &fsl_audmix_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(dev, "failed to init regmap\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	priv->ipg_clk = devm_clk_get(dev, "ipg");
	अगर (IS_ERR(priv->ipg_clk)) अणु
		dev_err(dev, "failed to get ipg clock\n");
		वापस PTR_ERR(priv->ipg_clk);
	पूर्ण

	spin_lock_init(&priv->lock);
	platक्रमm_set_drvdata(pdev, priv);
	pm_runसमय_enable(dev);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &fsl_audmix_component,
					      fsl_audmix_dai,
					      ARRAY_SIZE(fsl_audmix_dai));
	अगर (ret) अणु
		dev_err(dev, "failed to register ASoC DAI\n");
		जाओ err_disable_pm;
	पूर्ण

	priv->pdev = platक्रमm_device_रेजिस्टर_data(dev, "imx-audmix", 0, शून्य, 0);
	अगर (IS_ERR(priv->pdev)) अणु
		ret = PTR_ERR(priv->pdev);
		dev_err(dev, "failed to register platform: %d\n", ret);
		जाओ err_disable_pm;
	पूर्ण

	वापस 0;

err_disable_pm:
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_audmix_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_audmix *priv = dev_get_drvdata(&pdev->dev);

	pm_runसमय_disable(&pdev->dev);

	अगर (priv->pdev)
		platक्रमm_device_unरेजिस्टर(priv->pdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fsl_audmix_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_audmix *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->ipg_clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable IPG clock: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(priv->regmap, false);
	regcache_mark_dirty(priv->regmap);

	वापस regcache_sync(priv->regmap);
पूर्ण

अटल पूर्णांक fsl_audmix_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_audmix *priv = dev_get_drvdata(dev);

	regcache_cache_only(priv->regmap, true);

	clk_disable_unprepare(priv->ipg_clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops fsl_audmix_pm = अणु
	SET_RUNTIME_PM_OPS(fsl_audmix_runसमय_suspend,
			   fsl_audmix_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_audmix_driver = अणु
	.probe = fsl_audmix_probe,
	.हटाओ = fsl_audmix_हटाओ,
	.driver = अणु
		.name = "fsl-audmix",
		.of_match_table = fsl_audmix_ids,
		.pm = &fsl_audmix_pm,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(fsl_audmix_driver);

MODULE_DESCRIPTION("NXP AUDMIX ASoC DAI driver");
MODULE_AUTHOR("Viorel Suman <viorel.suman@nxp.com>");
MODULE_ALIAS("platform:fsl-audmix");
MODULE_LICENSE("GPL v2");
