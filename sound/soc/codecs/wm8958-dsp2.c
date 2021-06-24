<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8958-dsp2.c  --  WM8958 DSP2 support
 *
 * Copyright 2011 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <trace/events/asoc.h>

#समावेश <linux/mfd/wm8994/core.h>
#समावेश <linux/mfd/wm8994/रेजिस्टरs.h>
#समावेश <linux/mfd/wm8994/pdata.h>
#समावेश <linux/mfd/wm8994/gpपन.स>

#समावेश <यंत्र/unaligned.h>

#समावेश "wm8994.h"

#घोषणा WM_FW_BLOCK_INFO 0xff
#घोषणा WM_FW_BLOCK_PM   0x00
#घोषणा WM_FW_BLOCK_X    0x01
#घोषणा WM_FW_BLOCK_Y    0x02
#घोषणा WM_FW_BLOCK_Z    0x03
#घोषणा WM_FW_BLOCK_I    0x06
#घोषणा WM_FW_BLOCK_A    0x08
#घोषणा WM_FW_BLOCK_C    0x0c

अटल पूर्णांक wm8958_dsp2_fw(काष्ठा snd_soc_component *component, स्थिर अक्षर *name,
			  स्थिर काष्ठा firmware *fw, bool check)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	u64 data64;
	u32 data32;
	स्थिर u8 *data;
	अक्षर *str;
	माप_प्रकार block_len, len;
	पूर्णांक ret = 0;

	/* Suppress unneeded करोwnloads */
	अगर (wm8994->cur_fw == fw)
		वापस 0;

	अगर (fw->size < 32) अणु
		dev_err(component->dev, "%s: firmware too short (%zd bytes)\n",
			name, fw->size);
		जाओ err;
	पूर्ण

	अगर (स_भेद(fw->data, "WMFW", 4) != 0) अणु
		data32 = get_unaligned_be32(fw->data);
		dev_err(component->dev, "%s: firmware has bad file magic %08x\n",
			name, data32);
		जाओ err;
	पूर्ण

	len = get_unaligned_be32(fw->data + 4);
	data32 = get_unaligned_be32(fw->data + 8);

	अगर ((data32 >> 24) & 0xff) अणु
		dev_err(component->dev, "%s: unsupported firmware version %d\n",
			name, (data32 >> 24) & 0xff);
		जाओ err;
	पूर्ण
	अगर ((data32 & 0xffff) != 8958) अणु
		dev_err(component->dev, "%s: unsupported target device %d\n",
			name, data32 & 0xffff);
		जाओ err;
	पूर्ण
	अगर (((data32 >> 16) & 0xff) != 0xc) अणु
		dev_err(component->dev, "%s: unsupported target core %d\n",
			name, (data32 >> 16) & 0xff);
		जाओ err;
	पूर्ण

	अगर (check) अणु
		data64 = get_unaligned_be64(fw->data + 24);
		dev_info(component->dev, "%s timestamp %llx\n",  name, data64);
	पूर्ण अन्यथा अणु
		snd_soc_component_ग_लिखो(component, 0x102, 0x2);
		snd_soc_component_ग_लिखो(component, 0x900, 0x2);
	पूर्ण

	data = fw->data + len;
	len = fw->size - len;
	जबतक (len) अणु
		अगर (len < 12) अणु
			dev_err(component->dev, "%s short data block of %zd\n",
				name, len);
			जाओ err;
		पूर्ण

		block_len = get_unaligned_be32(data + 4);
		अगर (block_len + 8 > len) अणु
			dev_err(component->dev, "%zd byte block longer than file\n",
				block_len);
			जाओ err;
		पूर्ण
		अगर (block_len == 0) अणु
			dev_err(component->dev, "Zero length block\n");
			जाओ err;
		पूर्ण

		data32 = get_unaligned_be32(data);

		चयन ((data32 >> 24) & 0xff) अणु
		हाल WM_FW_BLOCK_INFO:
			/* Inक्रमmational text */
			अगर (!check)
				अवरोध;

			str = kzalloc(block_len + 1, GFP_KERNEL);
			अगर (str) अणु
				स_नकल(str, data + 8, block_len);
				dev_info(component->dev, "%s: %s\n", name, str);
				kमुक्त(str);
			पूर्ण अन्यथा अणु
				dev_err(component->dev, "Out of memory\n");
			पूर्ण
			अवरोध;
		हाल WM_FW_BLOCK_PM:
		हाल WM_FW_BLOCK_X:
		हाल WM_FW_BLOCK_Y:
		हाल WM_FW_BLOCK_Z:
		हाल WM_FW_BLOCK_I:
		हाल WM_FW_BLOCK_A:
		हाल WM_FW_BLOCK_C:
			dev_dbg(component->dev, "%s: %zd bytes of %x@%x\n", name,
				block_len, (data32 >> 24) & 0xff,
				data32 & 0xffffff);

			अगर (check)
				अवरोध;

			data32 &= 0xffffff;

			wm8994_bulk_ग_लिखो(wm8994->wm8994,
					  data32 & 0xffffff,
					  block_len / 2,
					  (व्योम *)(data + 8));

			अवरोध;
		शेष:
			dev_warn(component->dev, "%s: unknown block type %d\n",
				 name, (data32 >> 24) & 0xff);
			अवरोध;
		पूर्ण

		/* Round up to the next 32 bit word */
		block_len += block_len % 4;

		data += block_len + 8;
		len -= block_len + 8;
	पूर्ण

	अगर (!check) अणु
		dev_dbg(component->dev, "%s: download done\n", name);
		wm8994->cur_fw = fw;
	पूर्ण अन्यथा अणु
		dev_info(component->dev, "%s: got firmware\n", name);
	पूर्ण

	जाओ ok;

err:
	ret = -EINVAL;
ok:
	अगर (!check) अणु
		snd_soc_component_ग_लिखो(component, 0x900, 0x0);
		snd_soc_component_ग_लिखो(component, 0x102, 0x0);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम wm8958_dsp_start_mbc(काष्ठा snd_soc_component *component, पूर्णांक path)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक i;

	/* If the DSP is alपढ़ोy running then noop */
	अगर (snd_soc_component_पढ़ो(component, WM8958_DSP2_PROGRAM) & WM8958_DSP2_ENA)
		वापस;

	/* If we have MBC firmware करोwnload it */
	अगर (wm8994->mbc)
		wm8958_dsp2_fw(component, "MBC", wm8994->mbc, false);

	snd_soc_component_update_bits(component, WM8958_DSP2_PROGRAM,
			    WM8958_DSP2_ENA, WM8958_DSP2_ENA);

	/* If we've got user supplied MBC settings use them */
	अगर (control->pdata.num_mbc_cfgs) अणु
		काष्ठा wm8958_mbc_cfg *cfg
			= &control->pdata.mbc_cfgs[wm8994->mbc_cfg];

		क्रम (i = 0; i < ARRAY_SIZE(cfg->coeff_regs); i++)
			snd_soc_component_ग_लिखो(component, i + WM8958_MBC_BAND_1_K_1,
				      cfg->coeff_regs[i]);

		क्रम (i = 0; i < ARRAY_SIZE(cfg->cutoff_regs); i++)
			snd_soc_component_ग_लिखो(component,
				      i + WM8958_MBC_BAND_2_LOWER_CUTOFF_C1_1,
				      cfg->cutoff_regs[i]);
	पूर्ण

	/* Run the DSP */
	snd_soc_component_ग_लिखो(component, WM8958_DSP2_EXECCONTROL,
		      WM8958_DSP2_RUNR);

	/* And we're off! */
	snd_soc_component_update_bits(component, WM8958_DSP2_CONFIG,
			    WM8958_MBC_ENA |
			    WM8958_MBC_SEL_MASK,
			    path << WM8958_MBC_SEL_SHIFT |
			    WM8958_MBC_ENA);
पूर्ण

अटल व्योम wm8958_dsp_start_vss(काष्ठा snd_soc_component *component, पूर्णांक path)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक i, ena;

	अगर (wm8994->mbc_vss)
		wm8958_dsp2_fw(component, "MBC+VSS", wm8994->mbc_vss, false);

	snd_soc_component_update_bits(component, WM8958_DSP2_PROGRAM,
			    WM8958_DSP2_ENA, WM8958_DSP2_ENA);

	/* If we've got user supplied settings use them */
	अगर (control->pdata.num_mbc_cfgs) अणु
		काष्ठा wm8958_mbc_cfg *cfg
			= &control->pdata.mbc_cfgs[wm8994->mbc_cfg];

		क्रम (i = 0; i < ARRAY_SIZE(cfg->combined_regs); i++)
			snd_soc_component_ग_लिखो(component, i + 0x2800,
				      cfg->combined_regs[i]);
	पूर्ण

	अगर (control->pdata.num_vss_cfgs) अणु
		काष्ठा wm8958_vss_cfg *cfg
			= &control->pdata.vss_cfgs[wm8994->vss_cfg];

		क्रम (i = 0; i < ARRAY_SIZE(cfg->regs); i++)
			snd_soc_component_ग_लिखो(component, i + 0x2600, cfg->regs[i]);
	पूर्ण

	अगर (control->pdata.num_vss_hpf_cfgs) अणु
		काष्ठा wm8958_vss_hpf_cfg *cfg
			= &control->pdata.vss_hpf_cfgs[wm8994->vss_hpf_cfg];

		क्रम (i = 0; i < ARRAY_SIZE(cfg->regs); i++)
			snd_soc_component_ग_लिखो(component, i + 0x2400, cfg->regs[i]);
	पूर्ण

	/* Run the DSP */
	snd_soc_component_ग_लिखो(component, WM8958_DSP2_EXECCONTROL,
		      WM8958_DSP2_RUNR);

	/* Enable the algorithms we've selected */
	ena = 0;
	अगर (wm8994->mbc_ena[path])
		ena |= 0x8;
	अगर (wm8994->hpf2_ena[path])
		ena |= 0x4;
	अगर (wm8994->hpf1_ena[path])
		ena |= 0x2;
	अगर (wm8994->vss_ena[path])
		ena |= 0x1;

	snd_soc_component_ग_लिखो(component, 0x2201, ena);

	/* Switch the DSP पूर्णांकo the data path */
	snd_soc_component_update_bits(component, WM8958_DSP2_CONFIG,
			    WM8958_MBC_SEL_MASK | WM8958_MBC_ENA,
			    path << WM8958_MBC_SEL_SHIFT | WM8958_MBC_ENA);
पूर्ण

अटल व्योम wm8958_dsp_start_enh_eq(काष्ठा snd_soc_component *component, पूर्णांक path)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक i;

	wm8958_dsp2_fw(component, "ENH_EQ", wm8994->enh_eq, false);

	snd_soc_component_update_bits(component, WM8958_DSP2_PROGRAM,
			    WM8958_DSP2_ENA, WM8958_DSP2_ENA);

	/* If we've got user supplied settings use them */
	अगर (control->pdata.num_enh_eq_cfgs) अणु
		काष्ठा wm8958_enh_eq_cfg *cfg
			= &control->pdata.enh_eq_cfgs[wm8994->enh_eq_cfg];

		क्रम (i = 0; i < ARRAY_SIZE(cfg->regs); i++)
			snd_soc_component_ग_लिखो(component, i + 0x2200,
				      cfg->regs[i]);
	पूर्ण

	/* Run the DSP */
	snd_soc_component_ग_लिखो(component, WM8958_DSP2_EXECCONTROL,
		      WM8958_DSP2_RUNR);

	/* Switch the DSP पूर्णांकo the data path */
	snd_soc_component_update_bits(component, WM8958_DSP2_CONFIG,
			    WM8958_MBC_SEL_MASK | WM8958_MBC_ENA,
			    path << WM8958_MBC_SEL_SHIFT | WM8958_MBC_ENA);
पूर्ण

अटल व्योम wm8958_dsp_apply(काष्ठा snd_soc_component *component, पूर्णांक path, पूर्णांक start)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	पूर्णांक pwr_reg = snd_soc_component_पढ़ो(component, WM8994_POWER_MANAGEMENT_5);
	पूर्णांक ena, reg, aअगर;

	चयन (path) अणु
	हाल 0:
		pwr_reg &= (WM8994_AIF1DAC1L_ENA | WM8994_AIF1DAC1R_ENA);
		aअगर = 0;
		अवरोध;
	हाल 1:
		pwr_reg &= (WM8994_AIF1DAC2L_ENA | WM8994_AIF1DAC2R_ENA);
		aअगर = 0;
		अवरोध;
	हाल 2:
		pwr_reg &= (WM8994_AIF2DACL_ENA | WM8994_AIF2DACR_ENA);
		aअगर = 1;
		अवरोध;
	शेष:
		WARN(1, "Invalid path %d\n", path);
		वापस;
	पूर्ण

	/* Do we have both an active AIF and an active algorithm? */
	ena = wm8994->mbc_ena[path] || wm8994->vss_ena[path] ||
		wm8994->hpf1_ena[path] || wm8994->hpf2_ena[path] ||
		wm8994->enh_eq_ena[path];
	अगर (!pwr_reg)
		ena = 0;

	reg = snd_soc_component_पढ़ो(component, WM8958_DSP2_PROGRAM);

	dev_dbg(component->dev, "DSP path %d %d startup: %d, power: %x, DSP: %x\n",
		path, wm8994->dsp_active, start, pwr_reg, reg);

	अगर (start && ena) अणु
		/* If the DSP is alपढ़ोy running then noop */
		अगर (reg & WM8958_DSP2_ENA)
			वापस;

		/* If either AIFnCLK is not yet enabled postpone */
		अगर (!(snd_soc_component_पढ़ो(component, WM8994_AIF1_CLOCKING_1)
		      & WM8994_AIF1CLK_ENA_MASK) &&
		    !(snd_soc_component_पढ़ो(component, WM8994_AIF2_CLOCKING_1)
		      & WM8994_AIF2CLK_ENA_MASK))
			वापस;

		/* Switch the घड़ी over to the appropriate AIF */
		snd_soc_component_update_bits(component, WM8994_CLOCKING_1,
				    WM8958_DSP2CLK_SRC | WM8958_DSP2CLK_ENA,
				    aअगर << WM8958_DSP2CLK_SRC_SHIFT |
				    WM8958_DSP2CLK_ENA);

		अगर (wm8994->enh_eq_ena[path])
			wm8958_dsp_start_enh_eq(component, path);
		अन्यथा अगर (wm8994->vss_ena[path] || wm8994->hpf1_ena[path] ||
		    wm8994->hpf2_ena[path])
			wm8958_dsp_start_vss(component, path);
		अन्यथा अगर (wm8994->mbc_ena[path])
			wm8958_dsp_start_mbc(component, path);

		wm8994->dsp_active = path;

		dev_dbg(component->dev, "DSP running in path %d\n", path);
	पूर्ण

	अगर (!start && wm8994->dsp_active == path) अणु
		/* If the DSP is alपढ़ोy stopped then noop */
		अगर (!(reg & WM8958_DSP2_ENA))
			वापस;

		snd_soc_component_update_bits(component, WM8958_DSP2_CONFIG,
				    WM8958_MBC_ENA, 0);	
		snd_soc_component_ग_लिखो(component, WM8958_DSP2_EXECCONTROL,
			      WM8958_DSP2_STOP);
		snd_soc_component_update_bits(component, WM8958_DSP2_PROGRAM,
				    WM8958_DSP2_ENA, 0);
		snd_soc_component_update_bits(component, WM8994_CLOCKING_1,
				    WM8958_DSP2CLK_ENA, 0);

		wm8994->dsp_active = -1;

		dev_dbg(component->dev, "DSP stopped\n");
	पूर्ण
पूर्ण

पूर्णांक wm8958_aअगर_ev(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा wm8994 *control = dev_get_drvdata(component->dev->parent);
	पूर्णांक i;

	अगर (control->type != WM8958)
		वापस 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
	हाल SND_SOC_DAPM_PRE_PMU:
		क्रम (i = 0; i < 3; i++)
			wm8958_dsp_apply(component, i, 1);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
	हाल SND_SOC_DAPM_PRE_PMD:
		क्रम (i = 0; i < 3; i++)
			wm8958_dsp_apply(component, i, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Check अगर DSP2 is in use on another AIF */
अटल पूर्णांक wm8958_dsp2_busy(काष्ठा wm8994_priv *wm8994, पूर्णांक aअगर)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm8994->mbc_ena); i++) अणु
		अगर (i == aअगर)
			जारी;
		अगर (wm8994->mbc_ena[i] || wm8994->vss_ena[i] ||
		    wm8994->hpf1_ena[i] || wm8994->hpf2_ena[i])
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_put_mbc_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक value = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक reg;

	/* Don't allow on the fly reconfiguration */
	reg = snd_soc_component_पढ़ो(component, WM8994_CLOCKING_1);
	अगर (reg < 0 || reg & WM8958_DSP2CLK_ENA)
		वापस -EBUSY;

	अगर (value >= control->pdata.num_mbc_cfgs)
		वापस -EINVAL;

	wm8994->mbc_cfg = value;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_get_mbc_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = wm8994->mbc_cfg;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_mbc_info(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_mbc_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक mbc = kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wm8994->mbc_ena[mbc];

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_mbc_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक mbc = kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	अगर (wm8994->mbc_ena[mbc] == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;

	अगर (ucontrol->value.पूर्णांकeger.value[0] > 1)
		वापस -EINVAL;

	अगर (wm8958_dsp2_busy(wm8994, mbc)) अणु
		dev_dbg(component->dev, "DSP2 active on %d already\n", mbc);
		वापस -EBUSY;
	पूर्ण

	अगर (wm8994->enh_eq_ena[mbc])
		वापस -EBUSY;

	wm8994->mbc_ena[mbc] = ucontrol->value.पूर्णांकeger.value[0];

	wm8958_dsp_apply(component, mbc, wm8994->mbc_ena[mbc]);

	वापस 0;
पूर्ण

#घोषणा WM8958_MBC_SWITCH(xname, xval) अणु\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.info = wm8958_mbc_info, \
	.get = wm8958_mbc_get, .put = wm8958_mbc_put, \
	.निजी_value = xval पूर्ण

अटल पूर्णांक wm8958_put_vss_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक value = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक reg;

	/* Don't allow on the fly reconfiguration */
	reg = snd_soc_component_पढ़ो(component, WM8994_CLOCKING_1);
	अगर (reg < 0 || reg & WM8958_DSP2CLK_ENA)
		वापस -EBUSY;

	अगर (value >= control->pdata.num_vss_cfgs)
		वापस -EINVAL;

	wm8994->vss_cfg = value;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_get_vss_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = wm8994->vss_cfg;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_put_vss_hpf_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक value = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक reg;

	/* Don't allow on the fly reconfiguration */
	reg = snd_soc_component_पढ़ो(component, WM8994_CLOCKING_1);
	अगर (reg < 0 || reg & WM8958_DSP2CLK_ENA)
		वापस -EBUSY;

	अगर (value >= control->pdata.num_vss_hpf_cfgs)
		वापस -EINVAL;

	wm8994->vss_hpf_cfg = value;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_get_vss_hpf_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = wm8994->vss_hpf_cfg;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_vss_info(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_vss_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक vss = kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wm8994->vss_ena[vss];

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_vss_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक vss = kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	अगर (wm8994->vss_ena[vss] == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;

	अगर (ucontrol->value.पूर्णांकeger.value[0] > 1)
		वापस -EINVAL;

	अगर (!wm8994->mbc_vss)
		वापस -ENODEV;

	अगर (wm8958_dsp2_busy(wm8994, vss)) अणु
		dev_dbg(component->dev, "DSP2 active on %d already\n", vss);
		वापस -EBUSY;
	पूर्ण

	अगर (wm8994->enh_eq_ena[vss])
		वापस -EBUSY;

	wm8994->vss_ena[vss] = ucontrol->value.पूर्णांकeger.value[0];

	wm8958_dsp_apply(component, vss, wm8994->vss_ena[vss]);

	वापस 0;
पूर्ण


#घोषणा WM8958_VSS_SWITCH(xname, xval) अणु\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.info = wm8958_vss_info, \
	.get = wm8958_vss_get, .put = wm8958_vss_put, \
	.निजी_value = xval पूर्ण

अटल पूर्णांक wm8958_hpf_info(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_hpf_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक hpf = kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	अगर (hpf < 3)
		ucontrol->value.पूर्णांकeger.value[0] = wm8994->hpf1_ena[hpf % 3];
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = wm8994->hpf2_ena[hpf % 3];

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_hpf_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक hpf = kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	अगर (hpf < 3) अणु
		अगर (wm8994->hpf1_ena[hpf % 3] ==
		    ucontrol->value.पूर्णांकeger.value[0])
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (wm8994->hpf2_ena[hpf % 3] ==
		    ucontrol->value.पूर्णांकeger.value[0])
			वापस 0;
	पूर्ण

	अगर (ucontrol->value.पूर्णांकeger.value[0] > 1)
		वापस -EINVAL;

	अगर (!wm8994->mbc_vss)
		वापस -ENODEV;

	अगर (wm8958_dsp2_busy(wm8994, hpf % 3)) अणु
		dev_dbg(component->dev, "DSP2 active on %d already\n", hpf);
		वापस -EBUSY;
	पूर्ण

	अगर (wm8994->enh_eq_ena[hpf % 3])
		वापस -EBUSY;

	अगर (hpf < 3)
		wm8994->hpf1_ena[hpf % 3] = ucontrol->value.पूर्णांकeger.value[0];
	अन्यथा
		wm8994->hpf2_ena[hpf % 3] = ucontrol->value.पूर्णांकeger.value[0];

	wm8958_dsp_apply(component, hpf % 3, ucontrol->value.पूर्णांकeger.value[0]);

	वापस 0;
पूर्ण

#घोषणा WM8958_HPF_SWITCH(xname, xval) अणु\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.info = wm8958_hpf_info, \
	.get = wm8958_hpf_get, .put = wm8958_hpf_put, \
	.निजी_value = xval पूर्ण

अटल पूर्णांक wm8958_put_enh_eq_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	पूर्णांक value = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक reg;

	/* Don't allow on the fly reconfiguration */
	reg = snd_soc_component_पढ़ो(component, WM8994_CLOCKING_1);
	अगर (reg < 0 || reg & WM8958_DSP2CLK_ENA)
		वापस -EBUSY;

	अगर (value >= control->pdata.num_enh_eq_cfgs)
		वापस -EINVAL;

	wm8994->enh_eq_cfg = value;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_get_enh_eq_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	ucontrol->value.क्रमागतerated.item[0] = wm8994->enh_eq_cfg;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_enh_eq_info(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_enh_eq_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक eq = kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = wm8994->enh_eq_ena[eq];

	वापस 0;
पूर्ण

अटल पूर्णांक wm8958_enh_eq_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक eq = kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	अगर (wm8994->enh_eq_ena[eq] == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;

	अगर (ucontrol->value.पूर्णांकeger.value[0] > 1)
		वापस -EINVAL;

	अगर (!wm8994->enh_eq)
		वापस -ENODEV;

	अगर (wm8958_dsp2_busy(wm8994, eq)) अणु
		dev_dbg(component->dev, "DSP2 active on %d already\n", eq);
		वापस -EBUSY;
	पूर्ण

	अगर (wm8994->mbc_ena[eq] || wm8994->vss_ena[eq] ||
	    wm8994->hpf1_ena[eq] || wm8994->hpf2_ena[eq])
		वापस -EBUSY;

	wm8994->enh_eq_ena[eq] = ucontrol->value.पूर्णांकeger.value[0];

	wm8958_dsp_apply(component, eq, ucontrol->value.पूर्णांकeger.value[0]);

	वापस 0;
पूर्ण

#घोषणा WM8958_ENH_EQ_SWITCH(xname, xval) अणु\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.info = wm8958_enh_eq_info, \
	.get = wm8958_enh_eq_get, .put = wm8958_enh_eq_put, \
	.निजी_value = xval पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new wm8958_mbc_snd_controls[] = अणु
WM8958_MBC_SWITCH("AIF1DAC1 MBC Switch", 0),
WM8958_MBC_SWITCH("AIF1DAC2 MBC Switch", 1),
WM8958_MBC_SWITCH("AIF2DAC MBC Switch", 2),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8958_vss_snd_controls[] = अणु
WM8958_VSS_SWITCH("AIF1DAC1 VSS Switch", 0),
WM8958_VSS_SWITCH("AIF1DAC2 VSS Switch", 1),
WM8958_VSS_SWITCH("AIF2DAC VSS Switch", 2),
WM8958_HPF_SWITCH("AIF1DAC1 HPF1 Switch", 0),
WM8958_HPF_SWITCH("AIF1DAC2 HPF1 Switch", 1),
WM8958_HPF_SWITCH("AIF2DAC HPF1 Switch", 2),
WM8958_HPF_SWITCH("AIF1DAC1 HPF2 Switch", 3),
WM8958_HPF_SWITCH("AIF1DAC2 HPF2 Switch", 4),
WM8958_HPF_SWITCH("AIF2DAC HPF2 Switch", 5),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8958_enh_eq_snd_controls[] = अणु
WM8958_ENH_EQ_SWITCH("AIF1DAC1 Enhanced EQ Switch", 0),
WM8958_ENH_EQ_SWITCH("AIF1DAC2 Enhanced EQ Switch", 1),
WM8958_ENH_EQ_SWITCH("AIF2DAC Enhanced EQ Switch", 2),
पूर्ण;

अटल व्योम wm8958_enh_eq_loaded(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा snd_soc_component *component = context;
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	अगर (fw && (wm8958_dsp2_fw(component, "ENH_EQ", fw, true) == 0)) अणु
		mutex_lock(&wm8994->fw_lock);
		wm8994->enh_eq = fw;
		mutex_unlock(&wm8994->fw_lock);
	पूर्ण
पूर्ण

अटल व्योम wm8958_mbc_vss_loaded(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा snd_soc_component *component = context;
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	अगर (fw && (wm8958_dsp2_fw(component, "MBC+VSS", fw, true) == 0)) अणु
		mutex_lock(&wm8994->fw_lock);
		wm8994->mbc_vss = fw;
		mutex_unlock(&wm8994->fw_lock);
	पूर्ण
पूर्ण

अटल व्योम wm8958_mbc_loaded(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा snd_soc_component *component = context;
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);

	अगर (fw && (wm8958_dsp2_fw(component, "MBC", fw, true) == 0)) अणु
		mutex_lock(&wm8994->fw_lock);
		wm8994->mbc = fw;
		mutex_unlock(&wm8994->fw_lock);
	पूर्ण
पूर्ण

व्योम wm8958_dsp2_init(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	काष्ठा wm8994 *control = wm8994->wm8994;
	काष्ठा wm8994_pdata *pdata = &control->pdata;
	पूर्णांक ret, i;

	wm8994->dsp_active = -1;

	snd_soc_add_component_controls(component, wm8958_mbc_snd_controls,
			     ARRAY_SIZE(wm8958_mbc_snd_controls));
	snd_soc_add_component_controls(component, wm8958_vss_snd_controls,
			     ARRAY_SIZE(wm8958_vss_snd_controls));
	snd_soc_add_component_controls(component, wm8958_enh_eq_snd_controls,
			     ARRAY_SIZE(wm8958_enh_eq_snd_controls));


	/* We करोn't *require* firmware and don't want to delay boot */
	request_firmware_noरुको(THIS_MODULE, FW_ACTION_HOTPLUG,
				"wm8958_mbc.wfw", component->dev, GFP_KERNEL,
				component, wm8958_mbc_loaded);
	request_firmware_noरुको(THIS_MODULE, FW_ACTION_HOTPLUG,
				"wm8958_mbc_vss.wfw", component->dev, GFP_KERNEL,
				component, wm8958_mbc_vss_loaded);
	request_firmware_noरुको(THIS_MODULE, FW_ACTION_HOTPLUG,
				"wm8958_enh_eq.wfw", component->dev, GFP_KERNEL,
				component, wm8958_enh_eq_loaded);

	अगर (pdata->num_mbc_cfgs) अणु
		काष्ठा snd_kcontrol_new mbc_control[] = अणु
			SOC_ENUM_EXT("MBC Mode", wm8994->mbc_क्रमागत,
				     wm8958_get_mbc_क्रमागत, wm8958_put_mbc_क्रमागत),
		पूर्ण;

		/* We need an array of texts क्रम the क्रमागत API */
		wm8994->mbc_texts = kदो_स्मृति_array(pdata->num_mbc_cfgs,
						  माप(अक्षर *),
						  GFP_KERNEL);
		अगर (!wm8994->mbc_texts)
			वापस;

		क्रम (i = 0; i < pdata->num_mbc_cfgs; i++)
			wm8994->mbc_texts[i] = pdata->mbc_cfgs[i].name;

		wm8994->mbc_क्रमागत.items = pdata->num_mbc_cfgs;
		wm8994->mbc_क्रमागत.texts = wm8994->mbc_texts;

		ret = snd_soc_add_component_controls(wm8994->hubs.component,
						 mbc_control, 1);
		अगर (ret != 0)
			dev_err(wm8994->hubs.component->dev,
				"Failed to add MBC mode controls: %d\n", ret);
	पूर्ण

	अगर (pdata->num_vss_cfgs) अणु
		काष्ठा snd_kcontrol_new vss_control[] = अणु
			SOC_ENUM_EXT("VSS Mode", wm8994->vss_क्रमागत,
				     wm8958_get_vss_क्रमागत, wm8958_put_vss_क्रमागत),
		पूर्ण;

		/* We need an array of texts क्रम the क्रमागत API */
		wm8994->vss_texts = kदो_स्मृति_array(pdata->num_vss_cfgs,
						  माप(अक्षर *),
						  GFP_KERNEL);
		अगर (!wm8994->vss_texts)
			वापस;

		क्रम (i = 0; i < pdata->num_vss_cfgs; i++)
			wm8994->vss_texts[i] = pdata->vss_cfgs[i].name;

		wm8994->vss_क्रमागत.items = pdata->num_vss_cfgs;
		wm8994->vss_क्रमागत.texts = wm8994->vss_texts;

		ret = snd_soc_add_component_controls(wm8994->hubs.component,
						 vss_control, 1);
		अगर (ret != 0)
			dev_err(wm8994->hubs.component->dev,
				"Failed to add VSS mode controls: %d\n", ret);
	पूर्ण

	अगर (pdata->num_vss_hpf_cfgs) अणु
		काष्ठा snd_kcontrol_new hpf_control[] = अणु
			SOC_ENUM_EXT("VSS HPF Mode", wm8994->vss_hpf_क्रमागत,
				     wm8958_get_vss_hpf_क्रमागत,
				     wm8958_put_vss_hpf_क्रमागत),
		पूर्ण;

		/* We need an array of texts क्रम the क्रमागत API */
		wm8994->vss_hpf_texts = kदो_स्मृति_array(pdata->num_vss_hpf_cfgs,
						      माप(अक्षर *),
						      GFP_KERNEL);
		अगर (!wm8994->vss_hpf_texts)
			वापस;

		क्रम (i = 0; i < pdata->num_vss_hpf_cfgs; i++)
			wm8994->vss_hpf_texts[i] = pdata->vss_hpf_cfgs[i].name;

		wm8994->vss_hpf_क्रमागत.items = pdata->num_vss_hpf_cfgs;
		wm8994->vss_hpf_क्रमागत.texts = wm8994->vss_hpf_texts;

		ret = snd_soc_add_component_controls(wm8994->hubs.component,
						 hpf_control, 1);
		अगर (ret != 0)
			dev_err(wm8994->hubs.component->dev,
				"Failed to add VSS HPFmode controls: %d\n",
				ret);
	पूर्ण

	अगर (pdata->num_enh_eq_cfgs) अणु
		काष्ठा snd_kcontrol_new eq_control[] = अणु
			SOC_ENUM_EXT("Enhanced EQ Mode", wm8994->enh_eq_क्रमागत,
				     wm8958_get_enh_eq_क्रमागत,
				     wm8958_put_enh_eq_क्रमागत),
		पूर्ण;

		/* We need an array of texts क्रम the क्रमागत API */
		wm8994->enh_eq_texts = kदो_स्मृति_array(pdata->num_enh_eq_cfgs,
						     माप(अक्षर *),
						     GFP_KERNEL);
		अगर (!wm8994->enh_eq_texts)
			वापस;

		क्रम (i = 0; i < pdata->num_enh_eq_cfgs; i++)
			wm8994->enh_eq_texts[i] = pdata->enh_eq_cfgs[i].name;

		wm8994->enh_eq_क्रमागत.items = pdata->num_enh_eq_cfgs;
		wm8994->enh_eq_क्रमागत.texts = wm8994->enh_eq_texts;

		ret = snd_soc_add_component_controls(wm8994->hubs.component,
						 eq_control, 1);
		अगर (ret != 0)
			dev_err(wm8994->hubs.component->dev,
				"Failed to add enhanced EQ controls: %d\n",
				ret);
	पूर्ण
पूर्ण
