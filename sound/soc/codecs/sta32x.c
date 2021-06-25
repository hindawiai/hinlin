<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Codec driver क्रम ST STA32x 2.1-channel high-efficiency digital audio प्रणाली
 *
 * Copyright: 2011 Raumfeld GmbH
 * Author: Johannes Stezenbach <js@sig21.net>
 *
 * based on code from:
 *	Wolfson Microelectronics PLC.
 *	  Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *	Freescale Semiconductor, Inc.
 *	  Timur Tabi <timur@मुक्तscale.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s:%d: " fmt, __func__, __LINE__

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश <sound/sta32x.h>
#समावेश "sta32x.h"

#घोषणा STA32X_RATES (SNDRV_PCM_RATE_32000 | \
		      SNDRV_PCM_RATE_44100 | \
		      SNDRV_PCM_RATE_48000 | \
		      SNDRV_PCM_RATE_88200 | \
		      SNDRV_PCM_RATE_96000 | \
		      SNDRV_PCM_RATE_176400 | \
		      SNDRV_PCM_RATE_192000)

#घोषणा STA32X_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE  | SNDRV_PCM_FMTBIT_S16_BE  | \
	 SNDRV_PCM_FMTBIT_S18_3LE | SNDRV_PCM_FMTBIT_S18_3BE | \
	 SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S20_3BE | \
	 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE | \
	 SNDRV_PCM_FMTBIT_S24_LE  | SNDRV_PCM_FMTBIT_S24_BE  | \
	 SNDRV_PCM_FMTBIT_S32_LE  | SNDRV_PCM_FMTBIT_S32_BE)

/* Power-up रेजिस्टर शेषs */
अटल स्थिर काष्ठा reg_शेष sta32x_regs[] = अणु
	अणु  0x0, 0x63 पूर्ण,
	अणु  0x1, 0x80 पूर्ण,
	अणु  0x2, 0xc2 पूर्ण,
	अणु  0x3, 0x40 पूर्ण,
	अणु  0x4, 0xc2 पूर्ण,
	अणु  0x5, 0x5c पूर्ण,
	अणु  0x6, 0x10 पूर्ण,
	अणु  0x7, 0xff पूर्ण,
	अणु  0x8, 0x60 पूर्ण,
	अणु  0x9, 0x60 पूर्ण,
	अणु  0xa, 0x60 पूर्ण,
	अणु  0xb, 0x80 पूर्ण,
	अणु  0xc, 0x00 पूर्ण,
	अणु  0xd, 0x00 पूर्ण,
	अणु  0xe, 0x00 पूर्ण,
	अणु  0xf, 0x40 पूर्ण,
	अणु 0x10, 0x80 पूर्ण,
	अणु 0x11, 0x77 पूर्ण,
	अणु 0x12, 0x6a पूर्ण,
	अणु 0x13, 0x69 पूर्ण,
	अणु 0x14, 0x6a पूर्ण,
	अणु 0x15, 0x69 पूर्ण,
	अणु 0x16, 0x00 पूर्ण,
	अणु 0x17, 0x00 पूर्ण,
	अणु 0x18, 0x00 पूर्ण,
	अणु 0x19, 0x00 पूर्ण,
	अणु 0x1a, 0x00 पूर्ण,
	अणु 0x1b, 0x00 पूर्ण,
	अणु 0x1c, 0x00 पूर्ण,
	अणु 0x1d, 0x00 पूर्ण,
	अणु 0x1e, 0x00 पूर्ण,
	अणु 0x1f, 0x00 पूर्ण,
	अणु 0x20, 0x00 पूर्ण,
	अणु 0x21, 0x00 पूर्ण,
	अणु 0x22, 0x00 पूर्ण,
	अणु 0x23, 0x00 पूर्ण,
	अणु 0x24, 0x00 पूर्ण,
	अणु 0x25, 0x00 पूर्ण,
	अणु 0x26, 0x00 पूर्ण,
	अणु 0x27, 0x2d पूर्ण,
	अणु 0x28, 0xc0 पूर्ण,
	अणु 0x2b, 0x00 पूर्ण,
	अणु 0x2c, 0x0c पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range sta32x_ग_लिखो_regs_range[] = अणु
	regmap_reg_range(STA32X_CONFA,  STA32X_FDRC2),
पूर्ण;

अटल स्थिर काष्ठा regmap_range sta32x_पढ़ो_regs_range[] = अणु
	regmap_reg_range(STA32X_CONFA,  STA32X_FDRC2),
पूर्ण;

अटल स्थिर काष्ठा regmap_range sta32x_अस्थिर_regs_range[] = अणु
	regmap_reg_range(STA32X_CFADDR2, STA32X_CFUD),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table sta32x_ग_लिखो_regs = अणु
	.yes_ranges =	sta32x_ग_लिखो_regs_range,
	.n_yes_ranges =	ARRAY_SIZE(sta32x_ग_लिखो_regs_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table sta32x_पढ़ो_regs = अणु
	.yes_ranges =	sta32x_पढ़ो_regs_range,
	.n_yes_ranges =	ARRAY_SIZE(sta32x_पढ़ो_regs_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table sta32x_अस्थिर_regs = अणु
	.yes_ranges =	sta32x_अस्थिर_regs_range,
	.n_yes_ranges =	ARRAY_SIZE(sta32x_अस्थिर_regs_range),
पूर्ण;

/* regulator घातer supply names */
अटल स्थिर अक्षर *sta32x_supply_names[] = अणु
	"Vdda",	/* analog supply, 3.3VV */
	"Vdd3",	/* digital supply, 3.3V */
	"Vcc"	/* घातer amp spply, 10V - 36V */
पूर्ण;

/* codec निजी data */
काष्ठा sta32x_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *xti_clk;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(sta32x_supply_names)];
	काष्ठा snd_soc_component *component;
	काष्ठा sta32x_platक्रमm_data *pdata;

	अचिन्हित पूर्णांक mclk;
	अचिन्हित पूर्णांक क्रमmat;

	u32 coef_shaकरोw[STA32X_COEF_COUNT];
	काष्ठा delayed_work watchकरोg_work;
	पूर्णांक shutकरोwn;
	काष्ठा gpio_desc *gpiod_nreset;
	काष्ठा mutex coeff_lock;
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(mvol_tlv, -12700, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(chvol_tlv, -7950, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(tone_tlv, -120, 200, 0);

अटल स्थिर अक्षर *sta32x_drc_ac[] = अणु
	"Anti-Clipping", "Dynamic Range Compression" पूर्ण;
अटल स्थिर अक्षर *sta32x_स्वतः_eq_mode[] = अणु
	"User", "Preset", "Loudness" पूर्ण;
अटल स्थिर अक्षर *sta32x_स्वतः_gc_mode[] = अणु
	"User", "AC no clipping", "AC limited clipping (10%)",
	"DRC nighttime listening mode" पूर्ण;
अटल स्थिर अक्षर *sta32x_स्वतः_xo_mode[] = अणु
	"User", "80Hz", "100Hz", "120Hz", "140Hz", "160Hz", "180Hz", "200Hz",
	"220Hz", "240Hz", "260Hz", "280Hz", "300Hz", "320Hz", "340Hz", "360Hz" पूर्ण;
अटल स्थिर अक्षर *sta32x_preset_eq_mode[] = अणु
	"Flat", "Rock", "Soft Rock", "Jazz", "Classical", "Dance", "Pop", "Soft",
	"Hard", "Party", "Vocal", "Hip-Hop", "Dialog", "Bass-boost #1",
	"Bass-boost #2", "Bass-boost #3", "Loudness 1", "Loudness 2",
	"Loudness 3", "Loudness 4", "Loudness 5", "Loudness 6", "Loudness 7",
	"Loudness 8", "Loudness 9", "Loudness 10", "Loudness 11", "Loudness 12",
	"Loudness 13", "Loudness 14", "Loudness 15", "Loudness 16" पूर्ण;
अटल स्थिर अक्षर *sta32x_limiter_select[] = अणु
	"Limiter Disabled", "Limiter #1", "Limiter #2" पूर्ण;
अटल स्थिर अक्षर *sta32x_limiter_attack_rate[] = अणु
	"3.1584", "2.7072", "2.2560", "1.8048", "1.3536", "0.9024",
	"0.4512", "0.2256", "0.1504", "0.1123", "0.0902", "0.0752",
	"0.0645", "0.0564", "0.0501", "0.0451" पूर्ण;
अटल स्थिर अक्षर *sta32x_limiter_release_rate[] = अणु
	"0.5116", "0.1370", "0.0744", "0.0499", "0.0360", "0.0299",
	"0.0264", "0.0208", "0.0198", "0.0172", "0.0147", "0.0137",
	"0.0134", "0.0117", "0.0110", "0.0104" पूर्ण;
अटल DECLARE_TLV_DB_RANGE(sta32x_limiter_ac_attack_tlv,
	0, 7, TLV_DB_SCALE_ITEM(-1200, 200, 0),
	8, 16, TLV_DB_SCALE_ITEM(300, 100, 0),
);

अटल DECLARE_TLV_DB_RANGE(sta32x_limiter_ac_release_tlv,
	0, 0, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 0),
	1, 1, TLV_DB_SCALE_ITEM(-2900, 0, 0),
	2, 2, TLV_DB_SCALE_ITEM(-2000, 0, 0),
	3, 8, TLV_DB_SCALE_ITEM(-1400, 200, 0),
	8, 16, TLV_DB_SCALE_ITEM(-700, 100, 0),
);

अटल DECLARE_TLV_DB_RANGE(sta32x_limiter_drc_attack_tlv,
	0, 7, TLV_DB_SCALE_ITEM(-3100, 200, 0),
	8, 13, TLV_DB_SCALE_ITEM(-1600, 100, 0),
	14, 16, TLV_DB_SCALE_ITEM(-1000, 300, 0),
);

अटल DECLARE_TLV_DB_RANGE(sta32x_limiter_drc_release_tlv,
	0, 0, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 0),
	1, 2, TLV_DB_SCALE_ITEM(-3800, 200, 0),
	3, 4, TLV_DB_SCALE_ITEM(-3300, 200, 0),
	5, 12, TLV_DB_SCALE_ITEM(-3000, 200, 0),
	13, 16, TLV_DB_SCALE_ITEM(-1500, 300, 0),
);

अटल SOC_ENUM_SINGLE_DECL(sta32x_drc_ac_क्रमागत,
			    STA32X_CONFD, STA32X_CONFD_DRC_SHIFT,
			    sta32x_drc_ac);
अटल SOC_ENUM_SINGLE_DECL(sta32x_स्वतः_eq_क्रमागत,
			    STA32X_AUTO1, STA32X_AUTO1_AMEQ_SHIFT,
			    sta32x_स्वतः_eq_mode);
अटल SOC_ENUM_SINGLE_DECL(sta32x_स्वतः_gc_क्रमागत,
			    STA32X_AUTO1, STA32X_AUTO1_AMGC_SHIFT,
			    sta32x_स्वतः_gc_mode);
अटल SOC_ENUM_SINGLE_DECL(sta32x_स्वतः_xo_क्रमागत,
			    STA32X_AUTO2, STA32X_AUTO2_XO_SHIFT,
			    sta32x_स्वतः_xo_mode);
अटल SOC_ENUM_SINGLE_DECL(sta32x_preset_eq_क्रमागत,
			    STA32X_AUTO3, STA32X_AUTO3_PEQ_SHIFT,
			    sta32x_preset_eq_mode);
अटल SOC_ENUM_SINGLE_DECL(sta32x_limiter_ch1_क्रमागत,
			    STA32X_C1CFG, STA32X_CxCFG_LS_SHIFT,
			    sta32x_limiter_select);
अटल SOC_ENUM_SINGLE_DECL(sta32x_limiter_ch2_क्रमागत,
			    STA32X_C2CFG, STA32X_CxCFG_LS_SHIFT,
			    sta32x_limiter_select);
अटल SOC_ENUM_SINGLE_DECL(sta32x_limiter_ch3_क्रमागत,
			    STA32X_C3CFG, STA32X_CxCFG_LS_SHIFT,
			    sta32x_limiter_select);
अटल SOC_ENUM_SINGLE_DECL(sta32x_limiter1_attack_rate_क्रमागत,
			    STA32X_L1AR, STA32X_LxA_SHIFT,
			    sta32x_limiter_attack_rate);
अटल SOC_ENUM_SINGLE_DECL(sta32x_limiter2_attack_rate_क्रमागत,
			    STA32X_L2AR, STA32X_LxA_SHIFT,
			    sta32x_limiter_attack_rate);
अटल SOC_ENUM_SINGLE_DECL(sta32x_limiter1_release_rate_क्रमागत,
			    STA32X_L1AR, STA32X_LxR_SHIFT,
			    sta32x_limiter_release_rate);
अटल SOC_ENUM_SINGLE_DECL(sta32x_limiter2_release_rate_क्रमागत,
			    STA32X_L2AR, STA32X_LxR_SHIFT,
			    sta32x_limiter_release_rate);

/* byte array controls क्रम setting biquad, mixer, scaling coefficients;
 * क्रम biquads all five coefficients need to be set in one go,
 * mixer and pre/postscale coefs can be set inभागidually;
 * each coef is 24bit, the bytes are ordered in the same way
 * as given in the STA32x data sheet (big endian; b1, b2, a1, a2, b0)
 */

अटल पूर्णांक sta32x_coefficient_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक numcoef = kcontrol->निजी_value >> 16;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = 3 * numcoef;
	वापस 0;
पूर्ण

अटल पूर्णांक sta32x_coefficient_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	पूर्णांक numcoef = kcontrol->निजी_value >> 16;
	पूर्णांक index = kcontrol->निजी_value & 0xffff;
	अचिन्हित पूर्णांक cfud, val;
	पूर्णांक i, ret = 0;

	mutex_lock(&sta32x->coeff_lock);

	/* preserve reserved bits in STA32X_CFUD */
	regmap_पढ़ो(sta32x->regmap, STA32X_CFUD, &cfud);
	cfud &= 0xf0;
	/*
	 * chip करोcumentation करोes not say अगर the bits are self clearing,
	 * so करो it explicitly
	 */
	regmap_ग_लिखो(sta32x->regmap, STA32X_CFUD, cfud);

	regmap_ग_लिखो(sta32x->regmap, STA32X_CFADDR2, index);
	अगर (numcoef == 1) अणु
		regmap_ग_लिखो(sta32x->regmap, STA32X_CFUD, cfud | 0x04);
	पूर्ण अन्यथा अगर (numcoef == 5) अणु
		regmap_ग_लिखो(sta32x->regmap, STA32X_CFUD, cfud | 0x08);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ निकास_unlock;
	पूर्ण

	क्रम (i = 0; i < 3 * numcoef; i++) अणु
		regmap_पढ़ो(sta32x->regmap, STA32X_B1CF1 + i, &val);
		ucontrol->value.bytes.data[i] = val;
	पूर्ण

निकास_unlock:
	mutex_unlock(&sta32x->coeff_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sta32x_coefficient_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	पूर्णांक numcoef = kcontrol->निजी_value >> 16;
	पूर्णांक index = kcontrol->निजी_value & 0xffff;
	अचिन्हित पूर्णांक cfud;
	पूर्णांक i;

	/* preserve reserved bits in STA32X_CFUD */
	regmap_पढ़ो(sta32x->regmap, STA32X_CFUD, &cfud);
	cfud &= 0xf0;
	/*
	 * chip करोcumentation करोes not say अगर the bits are self clearing,
	 * so करो it explicitly
	 */
	regmap_ग_लिखो(sta32x->regmap, STA32X_CFUD, cfud);

	regmap_ग_लिखो(sta32x->regmap, STA32X_CFADDR2, index);
	क्रम (i = 0; i < numcoef && (index + i < STA32X_COEF_COUNT); i++)
		sta32x->coef_shaकरोw[index + i] =
			  (ucontrol->value.bytes.data[3 * i] << 16)
			| (ucontrol->value.bytes.data[3 * i + 1] << 8)
			| (ucontrol->value.bytes.data[3 * i + 2]);
	क्रम (i = 0; i < 3 * numcoef; i++)
		regmap_ग_लिखो(sta32x->regmap, STA32X_B1CF1 + i,
			     ucontrol->value.bytes.data[i]);
	अगर (numcoef == 1)
		regmap_ग_लिखो(sta32x->regmap, STA32X_CFUD, cfud | 0x01);
	अन्यथा अगर (numcoef == 5)
		regmap_ग_लिखो(sta32x->regmap, STA32X_CFUD, cfud | 0x02);
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sta32x_sync_coef_shaकरोw(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक cfud;
	पूर्णांक i;

	/* preserve reserved bits in STA32X_CFUD */
	regmap_पढ़ो(sta32x->regmap, STA32X_CFUD, &cfud);
	cfud &= 0xf0;

	क्रम (i = 0; i < STA32X_COEF_COUNT; i++) अणु
		regmap_ग_लिखो(sta32x->regmap, STA32X_CFADDR2, i);
		regmap_ग_लिखो(sta32x->regmap, STA32X_B1CF1,
			     (sta32x->coef_shaकरोw[i] >> 16) & 0xff);
		regmap_ग_लिखो(sta32x->regmap, STA32X_B1CF2,
			     (sta32x->coef_shaकरोw[i] >> 8) & 0xff);
		regmap_ग_लिखो(sta32x->regmap, STA32X_B1CF3,
			     (sta32x->coef_shaकरोw[i]) & 0xff);
		/*
		 * chip करोcumentation करोes not say अगर the bits are
		 * self-clearing, so करो it explicitly
		 */
		regmap_ग_लिखो(sta32x->regmap, STA32X_CFUD, cfud);
		regmap_ग_लिखो(sta32x->regmap, STA32X_CFUD, cfud | 0x01);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sta32x_cache_sync(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक mute;
	पूर्णांक rc;

	/* mute during रेजिस्टर sync */
	regmap_पढ़ो(sta32x->regmap, STA32X_MMUTE, &mute);
	regmap_ग_लिखो(sta32x->regmap, STA32X_MMUTE, mute | STA32X_MMUTE_MMUTE);
	sta32x_sync_coef_shaकरोw(component);
	rc = regcache_sync(sta32x->regmap);
	regmap_ग_लिखो(sta32x->regmap, STA32X_MMUTE, mute);
	वापस rc;
पूर्ण

/* work around ESD issue where sta32x resets and loses all configuration */
अटल व्योम sta32x_watchकरोg(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sta32x_priv *sta32x = container_of(work, काष्ठा sta32x_priv,
						  watchकरोg_work.work);
	काष्ठा snd_soc_component *component = sta32x->component;
	अचिन्हित पूर्णांक confa, confa_cached;

	/* check अगर sta32x has reset itself */
	confa_cached = snd_soc_component_पढ़ो(component, STA32X_CONFA);
	regcache_cache_bypass(sta32x->regmap, true);
	confa = snd_soc_component_पढ़ो(component, STA32X_CONFA);
	regcache_cache_bypass(sta32x->regmap, false);
	अगर (confa != confa_cached) अणु
		regcache_mark_dirty(sta32x->regmap);
		sta32x_cache_sync(component);
	पूर्ण

	अगर (!sta32x->shutकरोwn)
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &sta32x->watchकरोg_work,
				   round_jअगरfies_relative(HZ));
पूर्ण

अटल व्योम sta32x_watchकरोg_start(काष्ठा sta32x_priv *sta32x)
अणु
	अगर (sta32x->pdata->needs_esd_watchकरोg) अणु
		sta32x->shutकरोwn = 0;
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &sta32x->watchकरोg_work,
				   round_jअगरfies_relative(HZ));
	पूर्ण
पूर्ण

अटल व्योम sta32x_watchकरोg_stop(काष्ठा sta32x_priv *sta32x)
अणु
	अगर (sta32x->pdata->needs_esd_watchकरोg) अणु
		sta32x->shutकरोwn = 1;
		cancel_delayed_work_sync(&sta32x->watchकरोg_work);
	पूर्ण
पूर्ण

#घोषणा SINGLE_COEF(xname, index) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = sta32x_coefficient_info, \
	.get = sta32x_coefficient_get,\
	.put = sta32x_coefficient_put, \
	.निजी_value = index | (1 << 16) पूर्ण

#घोषणा BIQUAD_COEFS(xname, index) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = sta32x_coefficient_info, \
	.get = sta32x_coefficient_get,\
	.put = sta32x_coefficient_put, \
	.निजी_value = index | (5 << 16) पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new sta32x_snd_controls[] = अणु
SOC_SINGLE_TLV("Master Volume", STA32X_MVOL, 0, 0xff, 1, mvol_tlv),
SOC_SINGLE("Master Switch", STA32X_MMUTE, 0, 1, 1),
SOC_SINGLE("Ch1 Switch", STA32X_MMUTE, 1, 1, 1),
SOC_SINGLE("Ch2 Switch", STA32X_MMUTE, 2, 1, 1),
SOC_SINGLE("Ch3 Switch", STA32X_MMUTE, 3, 1, 1),
SOC_SINGLE_TLV("Ch1 Volume", STA32X_C1VOL, 0, 0xff, 1, chvol_tlv),
SOC_SINGLE_TLV("Ch2 Volume", STA32X_C2VOL, 0, 0xff, 1, chvol_tlv),
SOC_SINGLE_TLV("Ch3 Volume", STA32X_C3VOL, 0, 0xff, 1, chvol_tlv),
SOC_SINGLE("De-emphasis Filter Switch", STA32X_CONFD, STA32X_CONFD_DEMP_SHIFT, 1, 0),
SOC_ENUM("Compressor/Limiter Switch", sta32x_drc_ac_क्रमागत),
SOC_SINGLE("Miami Mode Switch", STA32X_CONFD, STA32X_CONFD_MME_SHIFT, 1, 0),
SOC_SINGLE("Zero Cross Switch", STA32X_CONFE, STA32X_CONFE_ZCE_SHIFT, 1, 0),
SOC_SINGLE("Soft Ramp Switch", STA32X_CONFE, STA32X_CONFE_SVE_SHIFT, 1, 0),
SOC_SINGLE("Auto-Mute Switch", STA32X_CONFF, STA32X_CONFF_IDE_SHIFT, 1, 0),
SOC_ENUM("Automode EQ", sta32x_स्वतः_eq_क्रमागत),
SOC_ENUM("Automode GC", sta32x_स्वतः_gc_क्रमागत),
SOC_ENUM("Automode XO", sta32x_स्वतः_xo_क्रमागत),
SOC_ENUM("Preset EQ", sta32x_preset_eq_क्रमागत),
SOC_SINGLE("Ch1 Tone Control Bypass Switch", STA32X_C1CFG, STA32X_CxCFG_TCB_SHIFT, 1, 0),
SOC_SINGLE("Ch2 Tone Control Bypass Switch", STA32X_C2CFG, STA32X_CxCFG_TCB_SHIFT, 1, 0),
SOC_SINGLE("Ch1 EQ Bypass Switch", STA32X_C1CFG, STA32X_CxCFG_EQBP_SHIFT, 1, 0),
SOC_SINGLE("Ch2 EQ Bypass Switch", STA32X_C2CFG, STA32X_CxCFG_EQBP_SHIFT, 1, 0),
SOC_SINGLE("Ch1 Master Volume Bypass Switch", STA32X_C1CFG, STA32X_CxCFG_VBP_SHIFT, 1, 0),
SOC_SINGLE("Ch2 Master Volume Bypass Switch", STA32X_C1CFG, STA32X_CxCFG_VBP_SHIFT, 1, 0),
SOC_SINGLE("Ch3 Master Volume Bypass Switch", STA32X_C1CFG, STA32X_CxCFG_VBP_SHIFT, 1, 0),
SOC_ENUM("Ch1 Limiter Select", sta32x_limiter_ch1_क्रमागत),
SOC_ENUM("Ch2 Limiter Select", sta32x_limiter_ch2_क्रमागत),
SOC_ENUM("Ch3 Limiter Select", sta32x_limiter_ch3_क्रमागत),
SOC_SINGLE_TLV("Bass Tone Control", STA32X_TONE, STA32X_TONE_BTC_SHIFT, 15, 0, tone_tlv),
SOC_SINGLE_TLV("Treble Tone Control", STA32X_TONE, STA32X_TONE_TTC_SHIFT, 15, 0, tone_tlv),
SOC_ENUM("Limiter1 Attack Rate (dB/ms)", sta32x_limiter1_attack_rate_क्रमागत),
SOC_ENUM("Limiter2 Attack Rate (dB/ms)", sta32x_limiter2_attack_rate_क्रमागत),
SOC_ENUM("Limiter1 Release Rate (dB/ms)", sta32x_limiter1_release_rate_क्रमागत),
SOC_ENUM("Limiter2 Release Rate (dB/ms)", sta32x_limiter2_release_rate_क्रमागत),

/* depending on mode, the attack/release thresholds have
 * two dअगरferent क्रमागत definitions; provide both
 */
SOC_SINGLE_TLV("Limiter1 Attack Threshold (AC Mode)", STA32X_L1ATRT, STA32X_LxA_SHIFT,
	       16, 0, sta32x_limiter_ac_attack_tlv),
SOC_SINGLE_TLV("Limiter2 Attack Threshold (AC Mode)", STA32X_L2ATRT, STA32X_LxA_SHIFT,
	       16, 0, sta32x_limiter_ac_attack_tlv),
SOC_SINGLE_TLV("Limiter1 Release Threshold (AC Mode)", STA32X_L1ATRT, STA32X_LxR_SHIFT,
	       16, 0, sta32x_limiter_ac_release_tlv),
SOC_SINGLE_TLV("Limiter2 Release Threshold (AC Mode)", STA32X_L2ATRT, STA32X_LxR_SHIFT,
	       16, 0, sta32x_limiter_ac_release_tlv),
SOC_SINGLE_TLV("Limiter1 Attack Threshold (DRC Mode)", STA32X_L1ATRT, STA32X_LxA_SHIFT,
	       16, 0, sta32x_limiter_drc_attack_tlv),
SOC_SINGLE_TLV("Limiter2 Attack Threshold (DRC Mode)", STA32X_L2ATRT, STA32X_LxA_SHIFT,
	       16, 0, sta32x_limiter_drc_attack_tlv),
SOC_SINGLE_TLV("Limiter1 Release Threshold (DRC Mode)", STA32X_L1ATRT, STA32X_LxR_SHIFT,
	       16, 0, sta32x_limiter_drc_release_tlv),
SOC_SINGLE_TLV("Limiter2 Release Threshold (DRC Mode)", STA32X_L2ATRT, STA32X_LxR_SHIFT,
	       16, 0, sta32x_limiter_drc_release_tlv),

BIQUAD_COEFS("Ch1 - Biquad 1", 0),
BIQUAD_COEFS("Ch1 - Biquad 2", 5),
BIQUAD_COEFS("Ch1 - Biquad 3", 10),
BIQUAD_COEFS("Ch1 - Biquad 4", 15),
BIQUAD_COEFS("Ch2 - Biquad 1", 20),
BIQUAD_COEFS("Ch2 - Biquad 2", 25),
BIQUAD_COEFS("Ch2 - Biquad 3", 30),
BIQUAD_COEFS("Ch2 - Biquad 4", 35),
BIQUAD_COEFS("High-pass", 40),
BIQUAD_COEFS("Low-pass", 45),
SINGLE_COEF("Ch1 - Prescale", 50),
SINGLE_COEF("Ch2 - Prescale", 51),
SINGLE_COEF("Ch1 - Postscale", 52),
SINGLE_COEF("Ch2 - Postscale", 53),
SINGLE_COEF("Ch3 - Postscale", 54),
SINGLE_COEF("Thermal warning - Postscale", 55),
SINGLE_COEF("Ch1 - Mix 1", 56),
SINGLE_COEF("Ch1 - Mix 2", 57),
SINGLE_COEF("Ch2 - Mix 1", 58),
SINGLE_COEF("Ch2 - Mix 2", 59),
SINGLE_COEF("Ch3 - Mix 1", 60),
SINGLE_COEF("Ch3 - Mix 2", 61),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sta32x_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DAC", "Playback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_OUTPUT("LEFT"),
SND_SOC_DAPM_OUTPUT("RIGHT"),
SND_SOC_DAPM_OUTPUT("SUB"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sta32x_dapm_routes[] = अणु
	अणु "LEFT", शून्य, "DAC" पूर्ण,
	अणु "RIGHT", शून्य, "DAC" पूर्ण,
	अणु "SUB", शून्य, "DAC" पूर्ण,
पूर्ण;

/* MCLK पूर्णांकerpolation ratio per fs */
अटल काष्ठा अणु
	पूर्णांक fs;
	पूर्णांक ir;
पूर्ण पूर्णांकerpolation_ratios[] = अणु
	अणु 32000, 0 पूर्ण,
	अणु 44100, 0 पूर्ण,
	अणु 48000, 0 पूर्ण,
	अणु 88200, 1 पूर्ण,
	अणु 96000, 1 पूर्ण,
	अणु 176400, 2 पूर्ण,
	अणु 192000, 2 पूर्ण,
पूर्ण;

/* MCLK to fs घड़ी ratios */
अटल पूर्णांक mcs_ratio_table[3][7] = अणु
	अणु 768, 512, 384, 256, 128, 576, 0 पूर्ण,
	अणु 384, 256, 192, 128,  64,   0 पूर्ण,
	अणु 384, 256, 192, 128,  64,   0 पूर्ण,
पूर्ण;

/**
 * sta32x_set_dai_sysclk - configure MCLK
 * @codec_dai: the codec DAI
 * @clk_id: the घड़ी ID (ignored)
 * @freq: the MCLK input frequency
 * @dir: the घड़ी direction (ignored)
 *
 * The value of MCLK is used to determine which sample rates are supported
 * by the STA32X, based on the mclk_ratios table.
 *
 * This function must be called by the machine driver's 'startup' function,
 * otherwise the list of supported sample rates will not be available in
 * समय क्रम ALSA.
 *
 * For setups with variable MCLKs, pass 0 as 'freq' argument. This will cause
 * theoretically possible sample rates to be enabled. Call it again with a
 * proper value set one the बाह्यal घड़ी is set (most probably you would करो
 * that from a machine's driver 'hw_param' hook.
 */
अटल पूर्णांक sta32x_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "mclk=%u\n", freq);
	sta32x->mclk = freq;

	वापस 0;
पूर्ण

/**
 * sta32x_set_dai_fmt - configure the codec क्रम the selected audio क्रमmat
 * @codec_dai: the codec DAI
 * @fmt: a SND_SOC_DAIFMT_x value indicating the data क्रमmat
 *
 * This function takes a biपंचांगask of SND_SOC_DAIFMT_x bits and programs the
 * codec accordingly.
 */
अटल पूर्णांक sta32x_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			      अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	u8 confb = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_LEFT_J:
		sta32x->क्रमmat = fmt & SND_SOC_DAIFMT_FORMAT_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		confb |= STA32X_CONFB_C2IM;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		confb |= STA32X_CONFB_C1IM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(sta32x->regmap, STA32X_CONFB,
				  STA32X_CONFB_C1IM | STA32X_CONFB_C2IM, confb);
पूर्ण

/**
 * sta32x_hw_params - program the STA32X with the given hardware parameters.
 * @substream: the audio stream
 * @params: the hardware parameters to set
 * @dai: the SOC DAI (ignored)
 *
 * This function programs the hardware with the values provided.
 * Specअगरically, the sample rate and the data क्रमmat.
 */
अटल पूर्णांक sta32x_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	पूर्णांक i, mcs = -EINVAL, ir = -EINVAL;
	अचिन्हित पूर्णांक confa, confb;
	अचिन्हित पूर्णांक rate, ratio;
	पूर्णांक ret;

	अगर (!sta32x->mclk) अणु
		dev_err(component->dev,
			"sta32x->mclk is unset. Unable to determine ratio\n");
		वापस -EIO;
	पूर्ण

	rate = params_rate(params);
	ratio = sta32x->mclk / rate;
	dev_dbg(component->dev, "rate: %u, ratio: %u\n", rate, ratio);

	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकerpolation_ratios); i++) अणु
		अगर (पूर्णांकerpolation_ratios[i].fs == rate) अणु
			ir = पूर्णांकerpolation_ratios[i].ir;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ir < 0) अणु
		dev_err(component->dev, "Unsupported samplerate: %u\n", rate);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		अगर (mcs_ratio_table[ir][i] == ratio) अणु
			mcs = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mcs < 0) अणु
		dev_err(component->dev, "Unresolvable ratio: %u\n", ratio);
		वापस -EINVAL;
	पूर्ण

	confa = (ir << STA32X_CONFA_IR_SHIFT) |
		(mcs << STA32X_CONFA_MCS_SHIFT);
	confb = 0;

	चयन (params_width(params)) अणु
	हाल 24:
		dev_dbg(component->dev, "24bit\n");
		fallthrough;
	हाल 32:
		dev_dbg(component->dev, "24bit or 32bit\n");
		चयन (sta32x->क्रमmat) अणु
		हाल SND_SOC_DAIFMT_I2S:
			confb |= 0x0;
			अवरोध;
		हाल SND_SOC_DAIFMT_LEFT_J:
			confb |= 0x1;
			अवरोध;
		हाल SND_SOC_DAIFMT_RIGHT_J:
			confb |= 0x2;
			अवरोध;
		पूर्ण

		अवरोध;
	हाल 20:
		dev_dbg(component->dev, "20bit\n");
		चयन (sta32x->क्रमmat) अणु
		हाल SND_SOC_DAIFMT_I2S:
			confb |= 0x4;
			अवरोध;
		हाल SND_SOC_DAIFMT_LEFT_J:
			confb |= 0x5;
			अवरोध;
		हाल SND_SOC_DAIFMT_RIGHT_J:
			confb |= 0x6;
			अवरोध;
		पूर्ण

		अवरोध;
	हाल 18:
		dev_dbg(component->dev, "18bit\n");
		चयन (sta32x->क्रमmat) अणु
		हाल SND_SOC_DAIFMT_I2S:
			confb |= 0x8;
			अवरोध;
		हाल SND_SOC_DAIFMT_LEFT_J:
			confb |= 0x9;
			अवरोध;
		हाल SND_SOC_DAIFMT_RIGHT_J:
			confb |= 0xa;
			अवरोध;
		पूर्ण

		अवरोध;
	हाल 16:
		dev_dbg(component->dev, "16bit\n");
		चयन (sta32x->क्रमmat) अणु
		हाल SND_SOC_DAIFMT_I2S:
			confb |= 0x0;
			अवरोध;
		हाल SND_SOC_DAIFMT_LEFT_J:
			confb |= 0xd;
			अवरोध;
		हाल SND_SOC_DAIFMT_RIGHT_J:
			confb |= 0xe;
			अवरोध;
		पूर्ण

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(sta32x->regmap, STA32X_CONFA,
				 STA32X_CONFA_MCS_MASK | STA32X_CONFA_IR_MASK,
				 confa);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(sta32x->regmap, STA32X_CONFB,
				 STA32X_CONFB_SAI_MASK | STA32X_CONFB_SAIFB,
				 confb);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक sta32x_startup_sequence(काष्ठा sta32x_priv *sta32x)
अणु
	अगर (sta32x->gpiod_nreset) अणु
		gpiod_set_value(sta32x->gpiod_nreset, 0);
		mdelay(1);
		gpiod_set_value(sta32x->gpiod_nreset, 1);
		mdelay(1);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sta32x_set_bias_level - DAPM callback
 * @component: the component device
 * @level: DAPM घातer level
 *
 * This is called by ALSA to put the component पूर्णांकo low घातer mode
 * or to wake it up.  If the component is घातered off completely
 * all रेजिस्टरs must be restored after घातer on.
 */
अटल पूर्णांक sta32x_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक ret;
	काष्ठा sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "level = %d\n", level);
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* Full घातer on */
		regmap_update_bits(sta32x->regmap, STA32X_CONFF,
				    STA32X_CONFF_PWDN | STA32X_CONFF_EAPD,
				    STA32X_CONFF_PWDN | STA32X_CONFF_EAPD);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(sta32x->supplies),
						    sta32x->supplies);
			अगर (ret != 0) अणु
				dev_err(component->dev,
					"Failed to enable supplies: %d\n", ret);
				वापस ret;
			पूर्ण

			sta32x_startup_sequence(sta32x);
			sta32x_cache_sync(component);
			sta32x_watchकरोg_start(sta32x);
		पूर्ण

		/* Power करोwn */
		regmap_update_bits(sta32x->regmap, STA32X_CONFF,
				   STA32X_CONFF_PWDN | STA32X_CONFF_EAPD,
				   0);

		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* The chip runs through the घातer करोwn sequence क्रम us. */
		regmap_update_bits(sta32x->regmap, STA32X_CONFF,
				   STA32X_CONFF_PWDN | STA32X_CONFF_EAPD, 0);
		msleep(300);
		sta32x_watchकरोg_stop(sta32x);

		gpiod_set_value(sta32x->gpiod_nreset, 0);

		regulator_bulk_disable(ARRAY_SIZE(sta32x->supplies),
				       sta32x->supplies);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops sta32x_dai_ops = अणु
	.hw_params	= sta32x_hw_params,
	.set_sysclk	= sta32x_set_dai_sysclk,
	.set_fmt	= sta32x_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sta32x_dai = अणु
	.name = "sta32x-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = STA32X_RATES,
		.क्रमmats = STA32X_FORMATS,
	पूर्ण,
	.ops = &sta32x_dai_ops,
पूर्ण;

अटल पूर्णांक sta32x_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);
	काष्ठा sta32x_platक्रमm_data *pdata = sta32x->pdata;
	पूर्णांक i, ret = 0, thermal = 0;

	sta32x->component = component;

	अगर (sta32x->xti_clk) अणु
		ret = clk_prepare_enable(sta32x->xti_clk);
		अगर (ret != 0) अणु
			dev_err(component->dev,
				"Failed to enable clock: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(sta32x->supplies),
				    sta32x->supplies);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to enable supplies: %d\n", ret);
		जाओ err_clk_disable_unprepare;
	पूर्ण

	ret = sta32x_startup_sequence(sta32x);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to startup device\n");
		जाओ err_regulator_bulk_disable;
	पूर्ण

	/* CONFA */
	अगर (!pdata->thermal_warning_recovery)
		thermal |= STA32X_CONFA_TWAB;
	अगर (!pdata->thermal_warning_adjusपंचांगent)
		thermal |= STA32X_CONFA_TWRB;
	अगर (!pdata->fault_detect_recovery)
		thermal |= STA32X_CONFA_FDRB;
	regmap_update_bits(sta32x->regmap, STA32X_CONFA,
			   STA32X_CONFA_TWAB | STA32X_CONFA_TWRB |
			   STA32X_CONFA_FDRB,
			   thermal);

	/* CONFC */
	regmap_update_bits(sta32x->regmap, STA32X_CONFC,
			   STA32X_CONFC_CSZ_MASK,
			   pdata->drop_compensation_ns
				<< STA32X_CONFC_CSZ_SHIFT);

	/* CONFE */
	regmap_update_bits(sta32x->regmap, STA32X_CONFE,
			   STA32X_CONFE_MPCV,
			   pdata->max_घातer_use_mpcc ?
				STA32X_CONFE_MPCV : 0);
	regmap_update_bits(sta32x->regmap, STA32X_CONFE,
			   STA32X_CONFE_MPC,
			   pdata->max_घातer_correction ?
				STA32X_CONFE_MPC : 0);
	regmap_update_bits(sta32x->regmap, STA32X_CONFE,
			   STA32X_CONFE_AME,
			   pdata->am_reduction_mode ?
				STA32X_CONFE_AME : 0);
	regmap_update_bits(sta32x->regmap, STA32X_CONFE,
			   STA32X_CONFE_PWMS,
			   pdata->odd_pwm_speed_mode ?
				STA32X_CONFE_PWMS : 0);

	/*  CONFF */
	regmap_update_bits(sta32x->regmap, STA32X_CONFF,
			   STA32X_CONFF_IDE,
			   pdata->invalid_input_detect_mute ?
				STA32X_CONFF_IDE : 0);

	/* select output configuration  */
	regmap_update_bits(sta32x->regmap, STA32X_CONFF,
			   STA32X_CONFF_OCFG_MASK,
			   pdata->output_conf
				<< STA32X_CONFF_OCFG_SHIFT);

	/* channel to output mapping */
	regmap_update_bits(sta32x->regmap, STA32X_C1CFG,
			   STA32X_CxCFG_OM_MASK,
			   pdata->ch1_output_mapping
				<< STA32X_CxCFG_OM_SHIFT);
	regmap_update_bits(sta32x->regmap, STA32X_C2CFG,
			   STA32X_CxCFG_OM_MASK,
			   pdata->ch2_output_mapping
				<< STA32X_CxCFG_OM_SHIFT);
	regmap_update_bits(sta32x->regmap, STA32X_C3CFG,
			   STA32X_CxCFG_OM_MASK,
			   pdata->ch3_output_mapping
				<< STA32X_CxCFG_OM_SHIFT);

	/* initialize coefficient shaकरोw RAM with reset values */
	क्रम (i = 4; i <= 49; i += 5)
		sta32x->coef_shaकरोw[i] = 0x400000;
	क्रम (i = 50; i <= 54; i++)
		sta32x->coef_shaकरोw[i] = 0x7fffff;
	sta32x->coef_shaकरोw[55] = 0x5a9df7;
	sta32x->coef_shaकरोw[56] = 0x7fffff;
	sta32x->coef_shaकरोw[59] = 0x7fffff;
	sta32x->coef_shaकरोw[60] = 0x400000;
	sta32x->coef_shaकरोw[61] = 0x400000;

	अगर (sta32x->pdata->needs_esd_watchकरोg)
		INIT_DELAYED_WORK(&sta32x->watchकरोg_work, sta32x_watchकरोg);

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);
	/* Bias level configuration will have करोne an extra enable */
	regulator_bulk_disable(ARRAY_SIZE(sta32x->supplies), sta32x->supplies);

	वापस 0;

err_regulator_bulk_disable:
	regulator_bulk_disable(ARRAY_SIZE(sta32x->supplies), sta32x->supplies);
err_clk_disable_unprepare:
	अगर (sta32x->xti_clk)
		clk_disable_unprepare(sta32x->xti_clk);
	वापस ret;
पूर्ण

अटल व्योम sta32x_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);

	sta32x_watchकरोg_stop(sta32x);
	regulator_bulk_disable(ARRAY_SIZE(sta32x->supplies), sta32x->supplies);

	अगर (sta32x->xti_clk)
		clk_disable_unprepare(sta32x->xti_clk);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver sta32x_component = अणु
	.probe			= sta32x_probe,
	.हटाओ			= sta32x_हटाओ,
	.set_bias_level		= sta32x_set_bias_level,
	.controls		= sta32x_snd_controls,
	.num_controls		= ARRAY_SIZE(sta32x_snd_controls),
	.dapm_widमाला_लो		= sta32x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sta32x_dapm_widमाला_लो),
	.dapm_routes		= sta32x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(sta32x_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sta32x_regmap = अणु
	.reg_bits =		8,
	.val_bits =		8,
	.max_रेजिस्टर =		STA32X_FDRC2,
	.reg_शेषs =		sta32x_regs,
	.num_reg_शेषs =	ARRAY_SIZE(sta32x_regs),
	.cache_type =		REGCACHE_RBTREE,
	.wr_table =		&sta32x_ग_लिखो_regs,
	.rd_table =		&sta32x_पढ़ो_regs,
	.अस्थिर_table =	&sta32x_अस्थिर_regs,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id st32x_dt_ids[] = अणु
	अणु .compatible = "st,sta32x", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st32x_dt_ids);

अटल पूर्णांक sta32x_probe_dt(काष्ठा device *dev, काष्ठा sta32x_priv *sta32x)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sta32x_platक्रमm_data *pdata;
	u16 पंचांगp;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	of_property_पढ़ो_u8(np, "st,output-conf",
			    &pdata->output_conf);
	of_property_पढ़ो_u8(np, "st,ch1-output-mapping",
			    &pdata->ch1_output_mapping);
	of_property_पढ़ो_u8(np, "st,ch2-output-mapping",
			    &pdata->ch2_output_mapping);
	of_property_पढ़ो_u8(np, "st,ch3-output-mapping",
			    &pdata->ch3_output_mapping);

	अगर (of_get_property(np, "st,fault-detect-recovery", शून्य))
		pdata->fault_detect_recovery = 1;
	अगर (of_get_property(np, "st,thermal-warning-recovery", शून्य))
		pdata->thermal_warning_recovery = 1;
	अगर (of_get_property(np, "st,thermal-warning-adjustment", शून्य))
		pdata->thermal_warning_adjusपंचांगent = 1;
	अगर (of_get_property(np, "st,needs_esd_watchdog", शून्य))
		pdata->needs_esd_watchकरोg = 1;

	पंचांगp = 140;
	of_property_पढ़ो_u16(np, "st,drop-compensation-ns", &पंचांगp);
	pdata->drop_compensation_ns = clamp_t(u16, पंचांगp, 0, 300) / 20;

	/* CONFE */
	अगर (of_get_property(np, "st,max-power-use-mpcc", शून्य))
		pdata->max_घातer_use_mpcc = 1;

	अगर (of_get_property(np, "st,max-power-correction", शून्य))
		pdata->max_घातer_correction = 1;

	अगर (of_get_property(np, "st,am-reduction-mode", शून्य))
		pdata->am_reduction_mode = 1;

	अगर (of_get_property(np, "st,odd-pwm-speed-mode", शून्य))
		pdata->odd_pwm_speed_mode = 1;

	/* CONFF */
	अगर (of_get_property(np, "st,invalid-input-detect-mute", शून्य))
		pdata->invalid_input_detect_mute = 1;

	sta32x->pdata = pdata;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sta32x_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा sta32x_priv *sta32x;
	पूर्णांक ret, i;

	sta32x = devm_kzalloc(&i2c->dev, माप(काष्ठा sta32x_priv),
			      GFP_KERNEL);
	अगर (!sta32x)
		वापस -ENOMEM;

	mutex_init(&sta32x->coeff_lock);
	sta32x->pdata = dev_get_platdata(dev);

#अगर_घोषित CONFIG_OF
	अगर (dev->of_node) अणु
		ret = sta32x_probe_dt(dev, sta32x);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
#पूर्ण_अगर

	/* Clock */
	sta32x->xti_clk = devm_clk_get(dev, "xti");
	अगर (IS_ERR(sta32x->xti_clk)) अणु
		ret = PTR_ERR(sta32x->xti_clk);

		अगर (ret == -EPROBE_DEFER)
			वापस ret;

		sta32x->xti_clk = शून्य;
	पूर्ण

	/* GPIOs */
	sta32x->gpiod_nreset = devm_gpiod_get_optional(dev, "reset",
						       GPIOD_OUT_LOW);
	अगर (IS_ERR(sta32x->gpiod_nreset))
		वापस PTR_ERR(sta32x->gpiod_nreset);

	/* regulators */
	क्रम (i = 0; i < ARRAY_SIZE(sta32x->supplies); i++)
		sta32x->supplies[i].supply = sta32x_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(sta32x->supplies),
				      sta32x->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	sta32x->regmap = devm_regmap_init_i2c(i2c, &sta32x_regmap);
	अगर (IS_ERR(sta32x->regmap)) अणु
		ret = PTR_ERR(sta32x->regmap);
		dev_err(dev, "Failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, sta32x);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &sta32x_component,
					      &sta32x_dai, 1);
	अगर (ret < 0)
		dev_err(dev, "Failed to register component (%d)\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sta32x_i2c_id[] = अणु
	अणु "sta326", 0 पूर्ण,
	अणु "sta328", 0 पूर्ण,
	अणु "sta329", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sta32x_i2c_id);

अटल काष्ठा i2c_driver sta32x_i2c_driver = अणु
	.driver = अणु
		.name = "sta32x",
		.of_match_table = of_match_ptr(st32x_dt_ids),
	पूर्ण,
	.probe =    sta32x_i2c_probe,
	.id_table = sta32x_i2c_id,
पूर्ण;

module_i2c_driver(sta32x_i2c_driver);

MODULE_DESCRIPTION("ASoC STA32X driver");
MODULE_AUTHOR("Johannes Stezenbach <js@sig21.net>");
MODULE_LICENSE("GPL");
