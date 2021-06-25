<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ALSA SoC TLV320AIC31xx CODEC Driver
 *
 * Copyright (C) 2014-2017 Texas Instruments Incorporated - https://www.ti.com/
 *	Jyri Sarha <jsarha@ti.com>
 *
 * Based on ground work by: Ajit Kulkarni <x0175765@ti.com>
 *
 * The TLV320AIC31xx series of audio codecs are low-घातer, highly पूर्णांकegrated
 * high perक्रमmance codecs which provides a stereo DAC, a mono ADC,
 * and mono/stereo Class-D speaker driver.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <dt-bindings/sound/tlv320aic31xx-micbias.h>

#समावेश "tlv320aic31xx.h"

अटल स्थिर काष्ठा reg_शेष aic31xx_reg_शेषs[] = अणु
	अणु AIC31XX_CLKMUX, 0x00 पूर्ण,
	अणु AIC31XX_PLLPR, 0x11 पूर्ण,
	अणु AIC31XX_PLLJ, 0x04 पूर्ण,
	अणु AIC31XX_PLLDMSB, 0x00 पूर्ण,
	अणु AIC31XX_PLLDLSB, 0x00 पूर्ण,
	अणु AIC31XX_NDAC, 0x01 पूर्ण,
	अणु AIC31XX_MDAC, 0x01 पूर्ण,
	अणु AIC31XX_DOSRMSB, 0x00 पूर्ण,
	अणु AIC31XX_DOSRLSB, 0x80 पूर्ण,
	अणु AIC31XX_NADC, 0x01 पूर्ण,
	अणु AIC31XX_MADC, 0x01 पूर्ण,
	अणु AIC31XX_AOSR, 0x80 पूर्ण,
	अणु AIC31XX_IFACE1, 0x00 पूर्ण,
	अणु AIC31XX_DATA_OFFSET, 0x00 पूर्ण,
	अणु AIC31XX_IFACE2, 0x00 पूर्ण,
	अणु AIC31XX_BCLKN, 0x01 पूर्ण,
	अणु AIC31XX_DACSETUP, 0x14 पूर्ण,
	अणु AIC31XX_DACMUTE, 0x0c पूर्ण,
	अणु AIC31XX_LDACVOL, 0x00 पूर्ण,
	अणु AIC31XX_RDACVOL, 0x00 पूर्ण,
	अणु AIC31XX_ADCSETUP, 0x00 पूर्ण,
	अणु AIC31XX_ADCFGA, 0x80 पूर्ण,
	अणु AIC31XX_ADCVOL, 0x00 पूर्ण,
	अणु AIC31XX_HPDRIVER, 0x04 पूर्ण,
	अणु AIC31XX_SPKAMP, 0x06 पूर्ण,
	अणु AIC31XX_DACMIXERROUTE, 0x00 पूर्ण,
	अणु AIC31XX_LANALOGHPL, 0x7f पूर्ण,
	अणु AIC31XX_RANALOGHPR, 0x7f पूर्ण,
	अणु AIC31XX_LANALOGSPL, 0x7f पूर्ण,
	अणु AIC31XX_RANALOGSPR, 0x7f पूर्ण,
	अणु AIC31XX_HPLGAIN, 0x02 पूर्ण,
	अणु AIC31XX_HPRGAIN, 0x02 पूर्ण,
	अणु AIC31XX_SPLGAIN, 0x00 पूर्ण,
	अणु AIC31XX_SPRGAIN, 0x00 पूर्ण,
	अणु AIC31XX_MICBIAS, 0x00 पूर्ण,
	अणु AIC31XX_MICPGA, 0x80 पूर्ण,
	अणु AIC31XX_MICPGAPI, 0x00 पूर्ण,
	अणु AIC31XX_MICPGAMI, 0x00 पूर्ण,
पूर्ण;

अटल bool aic31xx_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AIC31XX_PAGECTL: /* regmap implementation requires this */
	हाल AIC31XX_RESET: /* always clears after ग_लिखो */
	हाल AIC31XX_OT_FLAG:
	हाल AIC31XX_ADCFLAG:
	हाल AIC31XX_DACFLAG1:
	हाल AIC31XX_DACFLAG2:
	हाल AIC31XX_OFFLAG: /* Sticky पूर्णांकerrupt flags */
	हाल AIC31XX_INTRDACFLAG: /* Sticky पूर्णांकerrupt flags */
	हाल AIC31XX_INTRADCFLAG: /* Sticky पूर्णांकerrupt flags */
	हाल AIC31XX_INTRDACFLAG2:
	हाल AIC31XX_INTRADCFLAG2:
	हाल AIC31XX_HSDETECT:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool aic31xx_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AIC31XX_OT_FLAG:
	हाल AIC31XX_ADCFLAG:
	हाल AIC31XX_DACFLAG1:
	हाल AIC31XX_DACFLAG2:
	हाल AIC31XX_OFFLAG: /* Sticky पूर्णांकerrupt flags */
	हाल AIC31XX_INTRDACFLAG: /* Sticky पूर्णांकerrupt flags */
	हाल AIC31XX_INTRADCFLAG: /* Sticky पूर्णांकerrupt flags */
	हाल AIC31XX_INTRDACFLAG2:
	हाल AIC31XX_INTRADCFLAG2:
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल स्थिर काष्ठा regmap_range_cfg aic31xx_ranges[] = अणु
	अणु
		.range_min = 0,
		.range_max = 12 * 128,
		.selector_reg = AIC31XX_PAGECTL,
		.selector_mask = 0xff,
		.selector_shअगरt = 0,
		.winकरोw_start = 0,
		.winकरोw_len = 128,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config aic31xx_i2c_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखोable_reg = aic31xx_ग_लिखोable,
	.अस्थिर_reg = aic31xx_अस्थिर,
	.reg_शेषs = aic31xx_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(aic31xx_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.ranges = aic31xx_ranges,
	.num_ranges = ARRAY_SIZE(aic31xx_ranges),
	.max_रेजिस्टर = 12 * 128,
पूर्ण;

अटल स्थिर अक्षर * स्थिर aic31xx_supply_names[] = अणु
	"HPVDD",
	"SPRVDD",
	"SPLVDD",
	"AVDD",
	"IOVDD",
	"DVDD",
पूर्ण;

#घोषणा AIC31XX_NUM_SUPPLIES ARRAY_SIZE(aic31xx_supply_names)

काष्ठा aic31xx_disable_nb अणु
	काष्ठा notअगरier_block nb;
	काष्ठा aic31xx_priv *aic31xx;
पूर्ण;

काष्ठा aic31xx_priv अणु
	काष्ठा snd_soc_component *component;
	u8 i2c_regs_status;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	क्रमागत aic31xx_type codec_type;
	काष्ठा gpio_desc *gpio_reset;
	पूर्णांक micbias_vg;
	काष्ठा aic31xx_pdata pdata;
	काष्ठा regulator_bulk_data supplies[AIC31XX_NUM_SUPPLIES];
	काष्ठा aic31xx_disable_nb disable_nb[AIC31XX_NUM_SUPPLIES];
	काष्ठा snd_soc_jack *jack;
	अचिन्हित पूर्णांक sysclk;
	u8 p_भाग;
	पूर्णांक rate_भाग_line;
	bool master_dapm_route_applied;
	पूर्णांक irq;
	u8 ocmv; /* output common-mode voltage */
पूर्ण;

काष्ठा aic31xx_rate_भागs अणु
	u32 mclk_p;
	u32 rate;
	u8 pll_j;
	u16 pll_d;
	u16 करोsr;
	u8 ndac;
	u8 mdac;
	u8 aosr;
	u8 nadc;
	u8 madc;
पूर्ण;

/* ADC भागiders can be disabled by configuring them to 0 */
अटल स्थिर काष्ठा aic31xx_rate_भागs aic31xx_भागs[] = अणु
	/* mclk/p    rate  pll: j     d        करोsr ndac mdac  aors nadc madc */
	/* 8k rate */
	अणु12000000,   8000,	8, 1920,	128,  48,  2,	128,  48,  2पूर्ण,
	अणु12000000,   8000,	8, 1920,	128,  32,  3,	128,  32,  3पूर्ण,
	अणु12500000,   8000,	7, 8643,	128,  48,  2,	128,  48,  2पूर्ण,
	/* 11.025k rate */
	अणु12000000,  11025,	7, 5264,	128,  32,  2,	128,  32,  2पूर्ण,
	अणु12000000,  11025,	8, 4672,	128,  24,  3,	128,  24,  3पूर्ण,
	अणु12500000,  11025,	7, 2253,	128,  32,  2,	128,  32,  2पूर्ण,
	/* 16k rate */
	अणु12000000,  16000,	8, 1920,	128,  24,  2,	128,  24,  2पूर्ण,
	अणु12000000,  16000,	8, 1920,	128,  16,  3,	128,  16,  3पूर्ण,
	अणु12500000,  16000,	7, 8643,	128,  24,  2,	128,  24,  2पूर्ण,
	/* 22.05k rate */
	अणु12000000,  22050,	7, 5264,	128,  16,  2,	128,  16,  2पूर्ण,
	अणु12000000,  22050,	8, 4672,	128,  12,  3,	128,  12,  3पूर्ण,
	अणु12500000,  22050,	7, 2253,	128,  16,  2,	128,  16,  2पूर्ण,
	/* 32k rate */
	अणु12000000,  32000,	8, 1920,	128,  12,  2,	128,  12,  2पूर्ण,
	अणु12000000,  32000,	8, 1920,	128,   8,  3,	128,   8,  3पूर्ण,
	अणु12500000,  32000,	7, 8643,	128,  12,  2,	128,  12,  2पूर्ण,
	/* 44.1k rate */
	अणु12000000,  44100,	7, 5264,	128,   8,  2,	128,   8,  2पूर्ण,
	अणु12000000,  44100,	8, 4672,	128,   6,  3,	128,   6,  3पूर्ण,
	अणु12500000,  44100,	7, 2253,	128,   8,  2,	128,   8,  2पूर्ण,
	/* 48k rate */
	अणु12000000,  48000,	8, 1920,	128,   8,  2,	128,   8,  2पूर्ण,
	अणु12000000,  48000,	7, 6800,	 96,   5,  4,	 96,   5,  4पूर्ण,
	अणु12500000,  48000,	7, 8643,	128,   8,  2,	128,   8,  2पूर्ण,
	/* 88.2k rate */
	अणु12000000,  88200,	7, 5264,	 64,   8,  2,	 64,   8,  2पूर्ण,
	अणु12000000,  88200,	8, 4672,	 64,   6,  3,	 64,   6,  3पूर्ण,
	अणु12500000,  88200,	7, 2253,	 64,   8,  2,	 64,   8,  2पूर्ण,
	/* 96k rate */
	अणु12000000,  96000,	8, 1920,	 64,   8,  2,	 64,   8,  2पूर्ण,
	अणु12000000,  96000,	7, 6800,	 48,   5,  4,	 48,   5,  4पूर्ण,
	अणु12500000,  96000,	7, 8643,	 64,   8,  2,	 64,   8,  2पूर्ण,
	/* 176.4k rate */
	अणु12000000, 176400,	7, 5264,	 32,   8,  2,	 32,   8,  2पूर्ण,
	अणु12000000, 176400,	8, 4672,	 32,   6,  3,	 32,   6,  3पूर्ण,
	अणु12500000, 176400,	7, 2253,	 32,   8,  2,	 32,   8,  2पूर्ण,
	/* 192k rate */
	अणु12000000, 192000,	8, 1920,	 32,   8,  2,	 32,   8,  2पूर्ण,
	अणु12000000, 192000,	7, 6800,	 24,   5,  4,	 24,   5,  4पूर्ण,
	अणु12500000, 192000,	7, 8643,	 32,   8,  2,	 32,   8,  2पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ldac_in_text[] = अणु
	"Off", "Left Data", "Right Data", "Mono"
पूर्ण;

अटल स्थिर अक्षर * स्थिर rdac_in_text[] = अणु
	"Off", "Right Data", "Left Data", "Mono"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ldac_in_क्रमागत, AIC31XX_DACSETUP, 4, ldac_in_text);

अटल SOC_ENUM_SINGLE_DECL(rdac_in_क्रमागत, AIC31XX_DACSETUP, 2, rdac_in_text);

अटल स्थिर अक्षर * स्थिर mic_select_text[] = अणु
	"Off", "FFR 10 Ohm", "FFR 20 Ohm", "FFR 40 Ohm"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mic1lp_p_क्रमागत, AIC31XX_MICPGAPI, 6,
	mic_select_text);
अटल SOC_ENUM_SINGLE_DECL(mic1rp_p_क्रमागत, AIC31XX_MICPGAPI, 4,
	mic_select_text);
अटल SOC_ENUM_SINGLE_DECL(mic1lm_p_क्रमागत, AIC31XX_MICPGAPI, 2,
	mic_select_text);

अटल SOC_ENUM_SINGLE_DECL(mic1lm_m_क्रमागत, AIC31XX_MICPGAMI, 4,
	mic_select_text);

अटल स्थिर अक्षर * स्थिर hp_घातeron_समय_प्रकारext[] = अणु
	"0us", "15.3us", "153us", "1.53ms", "15.3ms", "76.2ms",
	"153ms", "304ms", "610ms", "1.22s", "3.04s", "6.1s" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(hp_घातeron_समय_क्रमागत, AIC31XX_HPPOP, 3,
	hp_घातeron_समय_प्रकारext);

अटल स्थिर अक्षर * स्थिर hp_rampup_step_text[] = अणु
	"0ms", "0.98ms", "1.95ms", "3.9ms" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(hp_rampup_step_क्रमागत, AIC31XX_HPPOP, 1,
	hp_rampup_step_text);

अटल स्थिर अक्षर * स्थिर vol_soft_step_mode_text[] = अणु
	"fast", "slow", "disabled" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(vol_soft_step_mode_क्रमागत, AIC31XX_DACSETUP, 0,
	vol_soft_step_mode_text);

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_vol_tlv, -6350, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_fgain_tlv, 0, 10, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_cgain_tlv, -2000, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_pga_tlv, 0, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(hp_drv_tlv, 0, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(class_D_drv_tlv, 600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(hp_vol_tlv, -6350, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(sp_vol_tlv, -6350, 50, 0);

/*
 * controls to be exported to the user space
 */
अटल स्थिर काष्ठा snd_kcontrol_new common31xx_snd_controls[] = अणु
	SOC_DOUBLE_R_S_TLV("DAC Playback Volume", AIC31XX_LDACVOL,
			   AIC31XX_RDACVOL, 0, -127, 48, 7, 0, dac_vol_tlv),

	SOC_DOUBLE_R("HP Driver Playback Switch", AIC31XX_HPLGAIN,
		     AIC31XX_HPRGAIN, 2, 1, 0),
	SOC_DOUBLE_R_TLV("HP Driver Playback Volume", AIC31XX_HPLGAIN,
			 AIC31XX_HPRGAIN, 3, 0x09, 0, hp_drv_tlv),

	SOC_DOUBLE_R_TLV("HP Analog Playback Volume", AIC31XX_LANALOGHPL,
			 AIC31XX_RANALOGHPR, 0, 0x7F, 1, hp_vol_tlv),

	/* HP de-pop control: apply घातer not immediately but via ramp
	 * function with these psarameters. Note that घातer up sequence
	 * has to रुको क्रम this to complete; this is implemented by
	 * polling HP driver status in aic31xx_dapm_घातer_event()
	 */
	SOC_ENUM("HP Output Driver Power-On time", hp_घातeron_समय_क्रमागत),
	SOC_ENUM("HP Output Driver Ramp-up step", hp_rampup_step_क्रमागत),

	SOC_ENUM("Volume Soft Stepping", vol_soft_step_mode_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic31xx_snd_controls[] = अणु
	SOC_SINGLE_TLV("ADC Fine Capture Volume", AIC31XX_ADCFGA, 4, 4, 1,
		       adc_fgain_tlv),

	SOC_SINGLE("ADC Capture Switch", AIC31XX_ADCFGA, 7, 1, 1),
	SOC_DOUBLE_R_S_TLV("ADC Capture Volume", AIC31XX_ADCVOL, AIC31XX_ADCVOL,
			   0, -24, 40, 6, 0, adc_cgain_tlv),

	SOC_SINGLE_TLV("Mic PGA Capture Volume", AIC31XX_MICPGA, 0,
		       119, 0, mic_pga_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic311x_snd_controls[] = अणु
	SOC_DOUBLE_R("Speaker Driver Playback Switch", AIC31XX_SPLGAIN,
		     AIC31XX_SPRGAIN, 2, 1, 0),
	SOC_DOUBLE_R_TLV("Speaker Driver Playback Volume", AIC31XX_SPLGAIN,
			 AIC31XX_SPRGAIN, 3, 3, 0, class_D_drv_tlv),

	SOC_DOUBLE_R_TLV("Speaker Analog Playback Volume", AIC31XX_LANALOGSPL,
			 AIC31XX_RANALOGSPR, 0, 0x7F, 1, sp_vol_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic310x_snd_controls[] = अणु
	SOC_SINGLE("Speaker Driver Playback Switch", AIC31XX_SPLGAIN,
		   2, 1, 0),
	SOC_SINGLE_TLV("Speaker Driver Playback Volume", AIC31XX_SPLGAIN,
		       3, 3, 0, class_D_drv_tlv),

	SOC_SINGLE_TLV("Speaker Analog Playback Volume", AIC31XX_LANALOGSPL,
		       0, 0x7F, 1, sp_vol_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ldac_in_control =
	SOC_DAPM_ENUM("DAC Left Input", ldac_in_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rdac_in_control =
	SOC_DAPM_ENUM("DAC Right Input", rdac_in_क्रमागत);

अटल पूर्णांक aic31xx_रुको_bits(काष्ठा aic31xx_priv *aic31xx, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक wbits, पूर्णांक sleep,
			     पूर्णांक count)
अणु
	अचिन्हित पूर्णांक bits;
	पूर्णांक counter = count;
	पूर्णांक ret = regmap_पढ़ो(aic31xx->regmap, reg, &bits);

	जबतक ((bits & mask) != wbits && counter && !ret) अणु
		usleep_range(sleep, sleep * 2);
		ret = regmap_पढ़ो(aic31xx->regmap, reg, &bits);
		counter--;
	पूर्ण
	अगर ((bits & mask) != wbits) अणु
		dev_err(aic31xx->dev,
			"%s: Failed! 0x%x was 0x%x expected 0x%x (%d, 0x%x, %d us)\n",
			__func__, reg, bits, wbits, ret, mask,
			(count - counter) * sleep);
		ret = -1;
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा WIDGET_BIT(reg, shअगरt) (((shअगरt) << 8) | (reg))

अटल पूर्णांक aic31xx_dapm_घातer_event(काष्ठा snd_soc_dapm_widget *w,
				    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg = AIC31XX_DACFLAG1;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक समयout = 500 * USEC_PER_MSEC;

	चयन (WIDGET_BIT(w->reg, w->shअगरt)) अणु
	हाल WIDGET_BIT(AIC31XX_DACSETUP, 7):
		mask = AIC31XX_LDACPWRSTATUS_MASK;
		अवरोध;
	हाल WIDGET_BIT(AIC31XX_DACSETUP, 6):
		mask = AIC31XX_RDACPWRSTATUS_MASK;
		अवरोध;
	हाल WIDGET_BIT(AIC31XX_HPDRIVER, 7):
		mask = AIC31XX_HPLDRVPWRSTATUS_MASK;
		अगर (event == SND_SOC_DAPM_POST_PMU)
			समयout = 7 * USEC_PER_SEC;
		अवरोध;
	हाल WIDGET_BIT(AIC31XX_HPDRIVER, 6):
		mask = AIC31XX_HPRDRVPWRSTATUS_MASK;
		अगर (event == SND_SOC_DAPM_POST_PMU)
			समयout = 7 * USEC_PER_SEC;
		अवरोध;
	हाल WIDGET_BIT(AIC31XX_SPKAMP, 7):
		mask = AIC31XX_SPLDRVPWRSTATUS_MASK;
		अवरोध;
	हाल WIDGET_BIT(AIC31XX_SPKAMP, 6):
		mask = AIC31XX_SPRDRVPWRSTATUS_MASK;
		अवरोध;
	हाल WIDGET_BIT(AIC31XX_ADCSETUP, 7):
		mask = AIC31XX_ADCPWRSTATUS_MASK;
		reg = AIC31XX_ADCFLAG;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unknown widget '%s' calling %s\n",
			w->name, __func__);
		वापस -EINVAL;
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		वापस aic31xx_रुको_bits(aic31xx, reg, mask, mask,
				5000, समयout / 5000);
	हाल SND_SOC_DAPM_POST_PMD:
		वापस aic31xx_रुको_bits(aic31xx, reg, mask, 0,
				5000, समयout / 5000);
	शेष:
		dev_dbg(component->dev,
			"Unhandled dapm widget event %d from %s\n",
			event, w->name);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new aic31xx_left_output_चयनes[] = अणु
	SOC_DAPM_SINGLE("From Left DAC", AIC31XX_DACMIXERROUTE, 6, 1, 0),
	SOC_DAPM_SINGLE("From MIC1LP", AIC31XX_DACMIXERROUTE, 5, 1, 0),
	SOC_DAPM_SINGLE("From MIC1RP", AIC31XX_DACMIXERROUTE, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic31xx_right_output_चयनes[] = अणु
	SOC_DAPM_SINGLE("From Right DAC", AIC31XX_DACMIXERROUTE, 2, 1, 0),
	SOC_DAPM_SINGLE("From MIC1RP", AIC31XX_DACMIXERROUTE, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dac31xx_left_output_चयनes[] = अणु
	SOC_DAPM_SINGLE("From Left DAC", AIC31XX_DACMIXERROUTE, 6, 1, 0),
	SOC_DAPM_SINGLE("From AIN1", AIC31XX_DACMIXERROUTE, 5, 1, 0),
	SOC_DAPM_SINGLE("From AIN2", AIC31XX_DACMIXERROUTE, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new dac31xx_right_output_चयनes[] = अणु
	SOC_DAPM_SINGLE("From Right DAC", AIC31XX_DACMIXERROUTE, 2, 1, 0),
	SOC_DAPM_SINGLE("From AIN2", AIC31XX_DACMIXERROUTE, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new p_term_mic1lp =
	SOC_DAPM_ENUM("MIC1LP P-Terminal", mic1lp_p_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new p_term_mic1rp =
	SOC_DAPM_ENUM("MIC1RP P-Terminal", mic1rp_p_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new p_term_mic1lm =
	SOC_DAPM_ENUM("MIC1LM P-Terminal", mic1lm_p_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new m_term_mic1lm =
	SOC_DAPM_ENUM("MIC1LM M-Terminal", mic1lm_m_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new aic31xx_dapm_hpl_चयन =
	SOC_DAPM_SINGLE("Switch", AIC31XX_LANALOGHPL, 7, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new aic31xx_dapm_hpr_चयन =
	SOC_DAPM_SINGLE("Switch", AIC31XX_RANALOGHPR, 7, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new aic31xx_dapm_spl_चयन =
	SOC_DAPM_SINGLE("Switch", AIC31XX_LANALOGSPL, 7, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new aic31xx_dapm_spr_चयन =
	SOC_DAPM_SINGLE("Switch", AIC31XX_RANALOGSPR, 7, 1, 0);

अटल पूर्णांक mic_bias_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* change mic bias voltage to user defined */
		snd_soc_component_update_bits(component, AIC31XX_MICBIAS,
				    AIC31XX_MICBIAS_MASK,
				    aic31xx->micbias_vg <<
				    AIC31XX_MICBIAS_SHIFT);
		dev_dbg(component->dev, "%s: turned on\n", __func__);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		/* turn mic bias off */
		snd_soc_component_update_bits(component, AIC31XX_MICBIAS,
				    AIC31XX_MICBIAS_MASK, 0);
		dev_dbg(component->dev, "%s: turned off\n", __func__);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget common31xx_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("AIF IN", "Playback", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX("DAC Left Input",
			 SND_SOC_NOPM, 0, 0, &ldac_in_control),
	SND_SOC_DAPM_MUX("DAC Right Input",
			 SND_SOC_NOPM, 0, 0, &rdac_in_control),
	/* DACs */
	SND_SOC_DAPM_DAC_E("DAC Left", "Left Playback",
			   AIC31XX_DACSETUP, 7, 0, aic31xx_dapm_घातer_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_DAC_E("DAC Right", "Right Playback",
			   AIC31XX_DACSETUP, 6, 0, aic31xx_dapm_घातer_event,
			   SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	/* HP */
	SND_SOC_DAPM_SWITCH("HP Left", SND_SOC_NOPM, 0, 0,
			    &aic31xx_dapm_hpl_चयन),
	SND_SOC_DAPM_SWITCH("HP Right", SND_SOC_NOPM, 0, 0,
			    &aic31xx_dapm_hpr_चयन),

	/* Output drivers */
	SND_SOC_DAPM_OUT_DRV_E("HPL Driver", AIC31XX_HPDRIVER, 7, 0,
			       शून्य, 0, aic31xx_dapm_घातer_event,
			       SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_OUT_DRV_E("HPR Driver", AIC31XX_HPDRIVER, 6, 0,
			       शून्य, 0, aic31xx_dapm_घातer_event,
			       SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_POST_PMU),

	/* Mic Bias */
	SND_SOC_DAPM_SUPPLY("MICBIAS", SND_SOC_NOPM, 0, 0, mic_bias_event,
			    SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	/* Keep BCLK/WCLK enabled even अगर DAC/ADC is घातered करोwn */
	SND_SOC_DAPM_SUPPLY("Activate I2S clocks", AIC31XX_IFACE2, 2, 0,
			    शून्य, 0),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget dac31xx_dapm_widमाला_लो[] = अणु
	/* Inमाला_दो */
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),

	/* Output Mixers */
	SND_SOC_DAPM_MIXER("Output Left", SND_SOC_NOPM, 0, 0,
			   dac31xx_left_output_चयनes,
			   ARRAY_SIZE(dac31xx_left_output_चयनes)),
	SND_SOC_DAPM_MIXER("Output Right", SND_SOC_NOPM, 0, 0,
			   dac31xx_right_output_चयनes,
			   ARRAY_SIZE(dac31xx_right_output_चयनes)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget aic31xx_dapm_widमाला_लो[] = अणु
	/* Inमाला_दो */
	SND_SOC_DAPM_INPUT("MIC1LP"),
	SND_SOC_DAPM_INPUT("MIC1RP"),
	SND_SOC_DAPM_INPUT("MIC1LM"),

	/* Input Selection to MIC_PGA */
	SND_SOC_DAPM_MUX("MIC1LP P-Terminal", SND_SOC_NOPM, 0, 0,
			 &p_term_mic1lp),
	SND_SOC_DAPM_MUX("MIC1RP P-Terminal", SND_SOC_NOPM, 0, 0,
			 &p_term_mic1rp),
	SND_SOC_DAPM_MUX("MIC1LM P-Terminal", SND_SOC_NOPM, 0, 0,
			 &p_term_mic1lm),

	/* ADC */
	SND_SOC_DAPM_ADC_E("ADC", "Capture", AIC31XX_ADCSETUP, 7, 0,
			   aic31xx_dapm_घातer_event, SND_SOC_DAPM_POST_PMU |
			   SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MUX("MIC1LM M-Terminal", SND_SOC_NOPM, 0, 0,
			 &m_term_mic1lm),

	/* Enabling & Disabling MIC Gain Ctl */
	SND_SOC_DAPM_PGA("MIC_GAIN_CTL", AIC31XX_MICPGA,
			 7, 1, शून्य, 0),

	/* Output Mixers */
	SND_SOC_DAPM_MIXER("Output Left", SND_SOC_NOPM, 0, 0,
			   aic31xx_left_output_चयनes,
			   ARRAY_SIZE(aic31xx_left_output_चयनes)),
	SND_SOC_DAPM_MIXER("Output Right", SND_SOC_NOPM, 0, 0,
			   aic31xx_right_output_चयनes,
			   ARRAY_SIZE(aic31xx_right_output_चयनes)),

	SND_SOC_DAPM_AIF_OUT("AIF OUT", "Capture", 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget aic311x_dapm_widमाला_लो[] = अणु
	/* AIC3111 and AIC3110 have stereo class-D amplअगरier */
	SND_SOC_DAPM_OUT_DRV_E("SPL ClassD", AIC31XX_SPKAMP, 7, 0, शून्य, 0,
			       aic31xx_dapm_घातer_event, SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUT_DRV_E("SPR ClassD", AIC31XX_SPKAMP, 6, 0, शून्य, 0,
			       aic31xx_dapm_घातer_event, SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH("Speaker Left", SND_SOC_NOPM, 0, 0,
			    &aic31xx_dapm_spl_चयन),
	SND_SOC_DAPM_SWITCH("Speaker Right", SND_SOC_NOPM, 0, 0,
			    &aic31xx_dapm_spr_चयन),
	SND_SOC_DAPM_OUTPUT("SPL"),
	SND_SOC_DAPM_OUTPUT("SPR"),
पूर्ण;

/* AIC3100 and AIC3120 have only mono class-D amplअगरier */
अटल स्थिर काष्ठा snd_soc_dapm_widget aic310x_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUT_DRV_E("SPK ClassD", AIC31XX_SPKAMP, 7, 0, शून्य, 0,
			       aic31xx_dapm_घातer_event, SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SWITCH("Speaker", SND_SOC_NOPM, 0, 0,
			    &aic31xx_dapm_spl_चयन),
	SND_SOC_DAPM_OUTPUT("SPK"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route
common31xx_audio_map[] = अणु
	/* DAC Input Routing */
	अणु"DAC Left Input", "Left Data", "AIF IN"पूर्ण,
	अणु"DAC Left Input", "Right Data", "AIF IN"पूर्ण,
	अणु"DAC Left Input", "Mono", "AIF IN"पूर्ण,
	अणु"DAC Right Input", "Left Data", "AIF IN"पूर्ण,
	अणु"DAC Right Input", "Right Data", "AIF IN"पूर्ण,
	अणु"DAC Right Input", "Mono", "AIF IN"पूर्ण,
	अणु"DAC Left", शून्य, "DAC Left Input"पूर्ण,
	अणु"DAC Right", शून्य, "DAC Right Input"पूर्ण,

	/* HPL path */
	अणु"HP Left", "Switch", "Output Left"पूर्ण,
	अणु"HPL Driver", शून्य, "HP Left"पूर्ण,
	अणु"HPL", शून्य, "HPL Driver"पूर्ण,

	/* HPR path */
	अणु"HP Right", "Switch", "Output Right"पूर्ण,
	अणु"HPR Driver", शून्य, "HP Right"पूर्ण,
	अणु"HPR", शून्य, "HPR Driver"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route
dac31xx_audio_map[] = अणु
	/* Left Output */
	अणु"Output Left", "From Left DAC", "DAC Left"पूर्ण,
	अणु"Output Left", "From AIN1", "AIN1"पूर्ण,
	अणु"Output Left", "From AIN2", "AIN2"पूर्ण,

	/* Right Output */
	अणु"Output Right", "From Right DAC", "DAC Right"पूर्ण,
	अणु"Output Right", "From AIN2", "AIN2"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route
aic31xx_audio_map[] = अणु
	/* Mic input */
	अणु"MIC1LP P-Terminal", "FFR 10 Ohm", "MIC1LP"पूर्ण,
	अणु"MIC1LP P-Terminal", "FFR 20 Ohm", "MIC1LP"पूर्ण,
	अणु"MIC1LP P-Terminal", "FFR 40 Ohm", "MIC1LP"पूर्ण,
	अणु"MIC1RP P-Terminal", "FFR 10 Ohm", "MIC1RP"पूर्ण,
	अणु"MIC1RP P-Terminal", "FFR 20 Ohm", "MIC1RP"पूर्ण,
	अणु"MIC1RP P-Terminal", "FFR 40 Ohm", "MIC1RP"पूर्ण,
	अणु"MIC1LM P-Terminal", "FFR 10 Ohm", "MIC1LM"पूर्ण,
	अणु"MIC1LM P-Terminal", "FFR 20 Ohm", "MIC1LM"पूर्ण,
	अणु"MIC1LM P-Terminal", "FFR 40 Ohm", "MIC1LM"पूर्ण,

	अणु"MIC1LM M-Terminal", "FFR 10 Ohm", "MIC1LM"पूर्ण,
	अणु"MIC1LM M-Terminal", "FFR 20 Ohm", "MIC1LM"पूर्ण,
	अणु"MIC1LM M-Terminal", "FFR 40 Ohm", "MIC1LM"पूर्ण,

	अणु"MIC_GAIN_CTL", शून्य, "MIC1LP P-Terminal"पूर्ण,
	अणु"MIC_GAIN_CTL", शून्य, "MIC1RP P-Terminal"पूर्ण,
	अणु"MIC_GAIN_CTL", शून्य, "MIC1LM P-Terminal"पूर्ण,
	अणु"MIC_GAIN_CTL", शून्य, "MIC1LM M-Terminal"पूर्ण,

	अणु"ADC", शून्य, "MIC_GAIN_CTL"पूर्ण,

	अणु"AIF OUT", शून्य, "ADC"पूर्ण,

	/* Left Output */
	अणु"Output Left", "From Left DAC", "DAC Left"पूर्ण,
	अणु"Output Left", "From MIC1LP", "MIC1LP"पूर्ण,
	अणु"Output Left", "From MIC1RP", "MIC1RP"पूर्ण,

	/* Right Output */
	अणु"Output Right", "From Right DAC", "DAC Right"पूर्ण,
	अणु"Output Right", "From MIC1RP", "MIC1RP"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route
aic311x_audio_map[] = अणु
	/* SP L path */
	अणु"Speaker Left", "Switch", "Output Left"पूर्ण,
	अणु"SPL ClassD", शून्य, "Speaker Left"पूर्ण,
	अणु"SPL", शून्य, "SPL ClassD"पूर्ण,

	/* SP R path */
	अणु"Speaker Right", "Switch", "Output Right"पूर्ण,
	अणु"SPR ClassD", शून्य, "Speaker Right"पूर्ण,
	अणु"SPR", शून्य, "SPR ClassD"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route
aic310x_audio_map[] = अणु
	/* SP L path */
	अणु"Speaker", "Switch", "Output Left"पूर्ण,
	अणु"SPK ClassD", शून्य, "Speaker"पूर्ण,
	अणु"SPK", शून्य, "SPK ClassD"पूर्ण,
पूर्ण;

/*
 * Always connected DAPM routes क्रम codec घड़ी master modes.
 * If the codec is the master on the I2S bus, we need to घातer up components
 * to have valid DAC_CLK.
 *
 * In order to have the I2S घड़ीs on the bus either the DACs/ADC need to be
 * enabled, or the P0/R29/D2 (Keep bclk/wclk in घातer करोwn) need to be set.
 *
 * Otherwise the codec will not generate घड़ीs on the bus.
 */
अटल स्थिर काष्ठा snd_soc_dapm_route
common31xx_cm_audio_map[] = अणु
	अणु"HPL", शून्य, "AIF IN"पूर्ण,
	अणु"HPR", शून्य, "AIF IN"पूर्ण,

	अणु"AIF IN", शून्य, "Activate I2S clocks"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route
aic31xx_cm_audio_map[] = अणु
	अणु"AIF OUT", शून्य, "MIC1LP"पूर्ण,
	अणु"AIF OUT", शून्य, "MIC1RP"पूर्ण,
	अणु"AIF OUT", शून्य, "MIC1LM"पूर्ण,

	अणु"AIF OUT", शून्य, "Activate I2S clocks"पूर्ण,
पूर्ण;

अटल पूर्णांक aic31xx_add_controls(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret = 0;
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);

	अगर (!(aic31xx->codec_type & DAC31XX_BIT))
		ret = snd_soc_add_component_controls(
			component, aic31xx_snd_controls,
			ARRAY_SIZE(aic31xx_snd_controls));
	अगर (ret)
		वापस ret;

	अगर (aic31xx->codec_type & AIC31XX_STEREO_CLASS_D_BIT)
		ret = snd_soc_add_component_controls(
			component, aic311x_snd_controls,
			ARRAY_SIZE(aic311x_snd_controls));
	अन्यथा
		ret = snd_soc_add_component_controls(
			component, aic310x_snd_controls,
			ARRAY_SIZE(aic310x_snd_controls));

	वापस ret;
पूर्ण

अटल पूर्णांक aic31xx_add_widमाला_लो(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	अगर (aic31xx->codec_type & DAC31XX_BIT) अणु
		ret = snd_soc_dapm_new_controls(
			dapm, dac31xx_dapm_widमाला_लो,
			ARRAY_SIZE(dac31xx_dapm_widमाला_लो));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_add_routes(dapm, dac31xx_audio_map,
					      ARRAY_SIZE(dac31xx_audio_map));
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = snd_soc_dapm_new_controls(
			dapm, aic31xx_dapm_widमाला_लो,
			ARRAY_SIZE(aic31xx_dapm_widमाला_लो));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_add_routes(dapm, aic31xx_audio_map,
					      ARRAY_SIZE(aic31xx_audio_map));
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (aic31xx->codec_type & AIC31XX_STEREO_CLASS_D_BIT) अणु
		ret = snd_soc_dapm_new_controls(
			dapm, aic311x_dapm_widमाला_लो,
			ARRAY_SIZE(aic311x_dapm_widमाला_लो));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_add_routes(dapm, aic311x_audio_map,
					      ARRAY_SIZE(aic311x_audio_map));
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = snd_soc_dapm_new_controls(
			dapm, aic310x_dapm_widमाला_लो,
			ARRAY_SIZE(aic310x_dapm_widमाला_लो));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_add_routes(dapm, aic310x_audio_map,
					      ARRAY_SIZE(aic310x_audio_map));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aic31xx_setup_pll(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	पूर्णांक bclk_score = snd_soc_params_to_frame_size(params);
	पूर्णांक mclk_p;
	पूर्णांक bclk_n = 0;
	पूर्णांक match = -1;
	पूर्णांक i;

	अगर (!aic31xx->sysclk || !aic31xx->p_भाग) अणु
		dev_err(component->dev, "Master clock not supplied\n");
		वापस -EINVAL;
	पूर्ण
	mclk_p = aic31xx->sysclk / aic31xx->p_भाग;

	/* Use PLL as CODEC_CLKIN and DAC_CLK as BDIV_CLKIN */
	snd_soc_component_update_bits(component, AIC31XX_CLKMUX,
			    AIC31XX_CODEC_CLKIN_MASK, AIC31XX_CODEC_CLKIN_PLL);
	snd_soc_component_update_bits(component, AIC31XX_IFACE2,
			    AIC31XX_BDIVCLK_MASK, AIC31XX_DAC2BCLK);

	क्रम (i = 0; i < ARRAY_SIZE(aic31xx_भागs); i++) अणु
		अगर (aic31xx_भागs[i].rate == params_rate(params) &&
		    aic31xx_भागs[i].mclk_p == mclk_p) अणु
			पूर्णांक s =	(aic31xx_भागs[i].करोsr * aic31xx_भागs[i].mdac) %
				snd_soc_params_to_frame_size(params);
			पूर्णांक bn = (aic31xx_भागs[i].करोsr * aic31xx_भागs[i].mdac) /
				snd_soc_params_to_frame_size(params);
			अगर (s < bclk_score && bn > 0) अणु
				match = i;
				bclk_n = bn;
				bclk_score = s;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (match == -1) अणु
		dev_err(component->dev,
			"%s: Sample rate (%u) and format not supported\n",
			__func__, params_rate(params));
		/* See bellow क्रम details how fix this. */
		वापस -EINVAL;
	पूर्ण
	अगर (bclk_score != 0) अणु
		dev_warn(component->dev, "Can not produce exact bitclock");
		/* This is fine अगर using dsp क्रमmat, but अगर using i2s
		   there may be trouble. To fix the issue edit the
		   aic31xx_भागs table क्रम your mclk and sample
		   rate. Details can be found from:
		   https://www.ti.com/lit/ds/symlink/tlv320aic3100.pdf
		   Section: 5.6 CLOCK Generation and PLL
		*/
	पूर्ण
	i = match;

	/* PLL configuration */
	snd_soc_component_update_bits(component, AIC31XX_PLLPR, AIC31XX_PLL_MASK,
			    (aic31xx->p_भाग << 4) | 0x01);
	snd_soc_component_ग_लिखो(component, AIC31XX_PLLJ, aic31xx_भागs[i].pll_j);

	snd_soc_component_ग_लिखो(component, AIC31XX_PLLDMSB,
		      aic31xx_भागs[i].pll_d >> 8);
	snd_soc_component_ग_लिखो(component, AIC31XX_PLLDLSB,
		      aic31xx_भागs[i].pll_d & 0xff);

	/* DAC भागiders configuration */
	snd_soc_component_update_bits(component, AIC31XX_NDAC, AIC31XX_PLL_MASK,
			    aic31xx_भागs[i].ndac);
	snd_soc_component_update_bits(component, AIC31XX_MDAC, AIC31XX_PLL_MASK,
			    aic31xx_भागs[i].mdac);

	snd_soc_component_ग_लिखो(component, AIC31XX_DOSRMSB, aic31xx_भागs[i].करोsr >> 8);
	snd_soc_component_ग_लिखो(component, AIC31XX_DOSRLSB, aic31xx_भागs[i].करोsr & 0xff);

	/* ADC भागiders configuration. Write reset value 1 अगर not used. */
	snd_soc_component_update_bits(component, AIC31XX_NADC, AIC31XX_PLL_MASK,
			    aic31xx_भागs[i].nadc ? aic31xx_भागs[i].nadc : 1);
	snd_soc_component_update_bits(component, AIC31XX_MADC, AIC31XX_PLL_MASK,
			    aic31xx_भागs[i].madc ? aic31xx_भागs[i].madc : 1);

	snd_soc_component_ग_लिखो(component, AIC31XX_AOSR, aic31xx_भागs[i].aosr);

	/* Bit घड़ी भागider configuration. */
	snd_soc_component_update_bits(component, AIC31XX_BCLKN,
			    AIC31XX_PLL_MASK, bclk_n);

	aic31xx->rate_भाग_line = i;

	dev_dbg(component->dev,
		"pll %d.%04d/%d dosr %d n %d m %d aosr %d n %d m %d bclk_n %d\n",
		aic31xx_भागs[i].pll_j,
		aic31xx_भागs[i].pll_d,
		aic31xx->p_भाग,
		aic31xx_भागs[i].करोsr,
		aic31xx_भागs[i].ndac,
		aic31xx_भागs[i].mdac,
		aic31xx_भागs[i].aosr,
		aic31xx_भागs[i].nadc,
		aic31xx_भागs[i].madc,
		bclk_n
	);

	वापस 0;
पूर्ण

अटल पूर्णांक aic31xx_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 data = 0;

	dev_dbg(component->dev, "## %s: width %d rate %d\n",
		__func__, params_width(params),
		params_rate(params));

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		data = (AIC31XX_WORD_LEN_20BITS <<
			AIC31XX_IFACE1_DATALEN_SHIFT);
		अवरोध;
	हाल 24:
		data = (AIC31XX_WORD_LEN_24BITS <<
			AIC31XX_IFACE1_DATALEN_SHIFT);
		अवरोध;
	हाल 32:
		data = (AIC31XX_WORD_LEN_32BITS <<
			AIC31XX_IFACE1_DATALEN_SHIFT);
		अवरोध;
	शेष:
		dev_err(component->dev, "%s: Unsupported width %d\n",
			__func__, params_width(params));
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AIC31XX_IFACE1,
			    AIC31XX_IFACE1_DATALEN_MASK,
			    data);

	वापस aic31xx_setup_pll(component, params);
पूर्ण

अटल पूर्णांक aic31xx_dac_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute,
			    पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;

	अगर (mute) अणु
		snd_soc_component_update_bits(component, AIC31XX_DACMUTE,
				    AIC31XX_DACMUTE_MASK,
				    AIC31XX_DACMUTE_MASK);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, AIC31XX_DACMUTE,
				    AIC31XX_DACMUTE_MASK, 0x0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aic31xx_घड़ी_master_routes(काष्ठा snd_soc_component *component,
				       अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	fmt &= SND_SOC_DAIFMT_MASTER_MASK;
	अगर (fmt == SND_SOC_DAIFMT_CBS_CFS &&
	    aic31xx->master_dapm_route_applied) अणु
		/*
		 * Remove the DAPM route(s) क्रम codec घड़ी master modes,
		 * अगर applied
		 */
		ret = snd_soc_dapm_del_routes(dapm, common31xx_cm_audio_map,
					ARRAY_SIZE(common31xx_cm_audio_map));
		अगर (!ret && !(aic31xx->codec_type & DAC31XX_BIT))
			ret = snd_soc_dapm_del_routes(dapm,
					aic31xx_cm_audio_map,
					ARRAY_SIZE(aic31xx_cm_audio_map));

		अगर (ret)
			वापस ret;

		aic31xx->master_dapm_route_applied = false;
	पूर्ण अन्यथा अगर (fmt != SND_SOC_DAIFMT_CBS_CFS &&
		   !aic31xx->master_dapm_route_applied) अणु
		/*
		 * Add the needed DAPM route(s) क्रम codec घड़ी master modes,
		 * अगर it is not करोne alपढ़ोy
		 */
		ret = snd_soc_dapm_add_routes(dapm, common31xx_cm_audio_map,
					ARRAY_SIZE(common31xx_cm_audio_map));
		अगर (!ret && !(aic31xx->codec_type & DAC31XX_BIT))
			ret = snd_soc_dapm_add_routes(dapm,
					aic31xx_cm_audio_map,
					ARRAY_SIZE(aic31xx_cm_audio_map));

		अगर (ret)
			वापस ret;

		aic31xx->master_dapm_route_applied = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aic31xx_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			       अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u8 अगरace_reg1 = 0;
	u8 अगरace_reg2 = 0;
	u8 dsp_a_val = 0;

	dev_dbg(component->dev, "## %s: fmt = 0x%x\n", __func__, fmt);

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace_reg1 |= AIC31XX_BCLK_MASTER | AIC31XX_WCLK_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		अगरace_reg1 |= AIC31XX_WCLK_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		अगरace_reg1 |= AIC31XX_BCLK_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI master/slave interface\n");
		वापस -EINVAL;
	पूर्ण

	/* संकेत polarity */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace_reg2 |= AIC31XX_BCLKINV_MASK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI clock signal polarity\n");
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		dsp_a_val = 0x1;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_B:
		/*
		 * NOTE: This CODEC samples on the falling edge of BCLK in
		 * DSP mode, this is inverted compared to what most DAIs
		 * expect, so we invert क्रम this mode
		 */
		अगरace_reg2 ^= AIC31XX_BCLKINV_MASK;
		अगरace_reg1 |= (AIC31XX_DSP_MODE <<
			       AIC31XX_IFACE1_DATATYPE_SHIFT);
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अगरace_reg1 |= (AIC31XX_RIGHT_JUSTIFIED_MODE <<
			       AIC31XX_IFACE1_DATATYPE_SHIFT);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace_reg1 |= (AIC31XX_LEFT_JUSTIFIED_MODE <<
			       AIC31XX_IFACE1_DATATYPE_SHIFT);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI interface format\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AIC31XX_IFACE1,
			    AIC31XX_IFACE1_DATATYPE_MASK |
			    AIC31XX_IFACE1_MASTER_MASK,
			    अगरace_reg1);
	snd_soc_component_update_bits(component, AIC31XX_DATA_OFFSET,
			    AIC31XX_DATA_OFFSET_MASK,
			    dsp_a_val);
	snd_soc_component_update_bits(component, AIC31XX_IFACE2,
			    AIC31XX_BCLKINV_MASK,
			    अगरace_reg2);

	वापस aic31xx_घड़ी_master_routes(component, fmt);
पूर्ण

अटल पूर्णांक aic31xx_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	dev_dbg(component->dev, "## %s: clk_id = %d, freq = %d, dir = %d\n",
		__func__, clk_id, freq, dir);

	क्रम (i = 1; i < 8; i++)
		अगर (freq / i <= 20000000)
			अवरोध;
	अगर (freq/i > 20000000) अणु
		dev_err(aic31xx->dev, "%s: Too high mclk frequency %u\n",
			__func__, freq);
		वापस -EINVAL;
	पूर्ण
	aic31xx->p_भाग = i;

	क्रम (i = 0; i < ARRAY_SIZE(aic31xx_भागs); i++)
		अगर (aic31xx_भागs[i].mclk_p == freq / aic31xx->p_भाग)
			अवरोध;
	अगर (i == ARRAY_SIZE(aic31xx_भागs)) अणु
		dev_err(aic31xx->dev, "%s: Unsupported frequency %d\n",
			__func__, freq);
		वापस -EINVAL;
	पूर्ण

	/* set घड़ी on MCLK, BCLK, or GPIO1 as PLL input */
	snd_soc_component_update_bits(component, AIC31XX_CLKMUX, AIC31XX_PLL_CLKIN_MASK,
			    clk_id << AIC31XX_PLL_CLKIN_SHIFT);

	aic31xx->sysclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक aic31xx_regulator_event(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा aic31xx_disable_nb *disable_nb =
		container_of(nb, काष्ठा aic31xx_disable_nb, nb);
	काष्ठा aic31xx_priv *aic31xx = disable_nb->aic31xx;

	अगर (event & REGULATOR_EVENT_DISABLE) अणु
		/*
		 * Put codec to reset and as at least one of the
		 * supplies was disabled.
		 */
		अगर (aic31xx->gpio_reset)
			gpiod_set_value(aic31xx->gpio_reset, 1);

		regcache_mark_dirty(aic31xx->regmap);
		dev_dbg(aic31xx->dev, "## %s: DISABLE received\n", __func__);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aic31xx_reset(काष्ठा aic31xx_priv *aic31xx)
अणु
	पूर्णांक ret = 0;

	अगर (aic31xx->gpio_reset) अणु
		gpiod_set_value(aic31xx->gpio_reset, 1);
		ndelay(10); /* At least 10ns */
		gpiod_set_value(aic31xx->gpio_reset, 0);
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(aic31xx->regmap, AIC31XX_RESET, 1);
	पूर्ण
	mdelay(1); /* At least 1ms */

	वापस ret;
पूर्ण

अटल व्योम aic31xx_clk_on(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	u8 mask = AIC31XX_PM_MASK;
	u8 on = AIC31XX_PM_MASK;

	dev_dbg(component->dev, "codec clock -> on (rate %d)\n",
		aic31xx_भागs[aic31xx->rate_भाग_line].rate);
	snd_soc_component_update_bits(component, AIC31XX_PLLPR, mask, on);
	mdelay(10);
	snd_soc_component_update_bits(component, AIC31XX_NDAC, mask, on);
	snd_soc_component_update_bits(component, AIC31XX_MDAC, mask, on);
	अगर (aic31xx_भागs[aic31xx->rate_भाग_line].nadc)
		snd_soc_component_update_bits(component, AIC31XX_NADC, mask, on);
	अगर (aic31xx_भागs[aic31xx->rate_भाग_line].madc)
		snd_soc_component_update_bits(component, AIC31XX_MADC, mask, on);
	snd_soc_component_update_bits(component, AIC31XX_BCLKN, mask, on);
पूर्ण

अटल व्योम aic31xx_clk_off(काष्ठा snd_soc_component *component)
अणु
	u8 mask = AIC31XX_PM_MASK;
	u8 off = 0;

	dev_dbg(component->dev, "codec clock -> off\n");
	snd_soc_component_update_bits(component, AIC31XX_BCLKN, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_MADC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_NADC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_MDAC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_NDAC, mask, off);
	snd_soc_component_update_bits(component, AIC31XX_PLLPR, mask, off);
पूर्ण

अटल पूर्णांक aic31xx_घातer_on(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(aic31xx->supplies),
				    aic31xx->supplies);
	अगर (ret)
		वापस ret;

	regcache_cache_only(aic31xx->regmap, false);

	/* Reset device रेजिस्टरs क्रम a consistent घातer-on like state */
	ret = aic31xx_reset(aic31xx);
	अगर (ret < 0)
		dev_err(aic31xx->dev, "Could not reset device: %d\n", ret);

	ret = regcache_sync(aic31xx->regmap);
	अगर (ret) अणु
		dev_err(component->dev,
			"Failed to restore cache: %d\n", ret);
		regcache_cache_only(aic31xx->regmap, true);
		regulator_bulk_disable(ARRAY_SIZE(aic31xx->supplies),
				       aic31xx->supplies);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम aic31xx_घातer_off(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);

	regcache_cache_only(aic31xx->regmap, true);
	regulator_bulk_disable(ARRAY_SIZE(aic31xx->supplies),
			       aic31xx->supplies);
पूर्ण

अटल पूर्णांक aic31xx_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	dev_dbg(component->dev, "## %s: %d -> %d\n", __func__,
		snd_soc_component_get_bias_level(component), level);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY)
			aic31xx_clk_on(component);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		चयन (snd_soc_component_get_bias_level(component)) अणु
		हाल SND_SOC_BIAS_OFF:
			aic31xx_घातer_on(component);
			अवरोध;
		हाल SND_SOC_BIAS_PREPARE:
			aic31xx_clk_off(component);
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY)
			aic31xx_घातer_off(component);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aic31xx_set_jack(काष्ठा snd_soc_component *component,
			    काष्ठा snd_soc_jack *jack, व्योम *data)
अणु
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);

	aic31xx->jack = jack;

	/* Enable/Disable jack detection */
	regmap_ग_लिखो(aic31xx->regmap, AIC31XX_HSDETECT,
		     jack ? AIC31XX_HSD_ENABLE : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक aic31xx_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic31xx_priv *aic31xx = snd_soc_component_get_drvdata(component);
	पूर्णांक i, ret;

	dev_dbg(aic31xx->dev, "## %s\n", __func__);

	aic31xx->component = component;

	क्रम (i = 0; i < ARRAY_SIZE(aic31xx->supplies); i++) अणु
		aic31xx->disable_nb[i].nb.notअगरier_call =
			aic31xx_regulator_event;
		aic31xx->disable_nb[i].aic31xx = aic31xx;
		ret = devm_regulator_रेजिस्टर_notअगरier(
						aic31xx->supplies[i].consumer,
						&aic31xx->disable_nb[i].nb);
		अगर (ret) अणु
			dev_err(component->dev,
				"Failed to request regulator notifier: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	regcache_cache_only(aic31xx->regmap, true);
	regcache_mark_dirty(aic31xx->regmap);

	ret = aic31xx_add_controls(component);
	अगर (ret)
		वापस ret;

	ret = aic31xx_add_widमाला_लो(component);
	अगर (ret)
		वापस ret;

	/* set output common-mode voltage */
	snd_soc_component_update_bits(component, AIC31XX_HPDRIVER,
				      AIC31XX_HPD_OCMV_MASK,
				      aic31xx->ocmv << AIC31XX_HPD_OCMV_SHIFT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_driver_aic31xx = अणु
	.probe			= aic31xx_codec_probe,
	.set_jack		= aic31xx_set_jack,
	.set_bias_level		= aic31xx_set_bias_level,
	.controls		= common31xx_snd_controls,
	.num_controls		= ARRAY_SIZE(common31xx_snd_controls),
	.dapm_widमाला_लो		= common31xx_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(common31xx_dapm_widमाला_लो),
	.dapm_routes		= common31xx_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(common31xx_audio_map),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops aic31xx_dai_ops = अणु
	.hw_params	= aic31xx_hw_params,
	.set_sysclk	= aic31xx_set_dai_sysclk,
	.set_fmt	= aic31xx_set_dai_fmt,
	.mute_stream	= aic31xx_dac_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver dac31xx_dai_driver[] = अणु
	अणु
		.name = "tlv320dac31xx-hifi",
		.playback = अणु
			.stream_name	 = "Playback",
			.channels_min	 = 2,
			.channels_max	 = 2,
			.rates		 = AIC31XX_RATES,
			.क्रमmats	 = AIC31XX_FORMATS,
		पूर्ण,
		.ops = &aic31xx_dai_ops,
		.symmetric_rate = 1,
	पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_dai_driver aic31xx_dai_driver[] = अणु
	अणु
		.name = "tlv320aic31xx-hifi",
		.playback = अणु
			.stream_name	 = "Playback",
			.channels_min	 = 2,
			.channels_max	 = 2,
			.rates		 = AIC31XX_RATES,
			.क्रमmats	 = AIC31XX_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name	 = "Capture",
			.channels_min	 = 2,
			.channels_max	 = 2,
			.rates		 = AIC31XX_RATES,
			.क्रमmats	 = AIC31XX_FORMATS,
		पूर्ण,
		.ops = &aic31xx_dai_ops,
		.symmetric_rate = 1,
	पूर्ण
पूर्ण;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tlv320aic31xx_of_match[] = अणु
	अणु .compatible = "ti,tlv320aic310x" पूर्ण,
	अणु .compatible = "ti,tlv320aic311x" पूर्ण,
	अणु .compatible = "ti,tlv320aic3100" पूर्ण,
	अणु .compatible = "ti,tlv320aic3110" पूर्ण,
	अणु .compatible = "ti,tlv320aic3120" पूर्ण,
	अणु .compatible = "ti,tlv320aic3111" पूर्ण,
	अणु .compatible = "ti,tlv320dac3100" पूर्ण,
	अणु .compatible = "ti,tlv320dac3101" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tlv320aic31xx_of_match);
#पूर्ण_अगर /* CONFIG_OF */

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id aic31xx_acpi_match[] = अणु
	अणु "10TI3100", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, aic31xx_acpi_match);
#पूर्ण_अगर

अटल irqवापस_t aic31xx_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा aic31xx_priv *aic31xx = data;
	काष्ठा device *dev = aic31xx->dev;
	अचिन्हित पूर्णांक value;
	bool handled = false;
	पूर्णांक ret;

	ret = regmap_पढ़ो(aic31xx->regmap, AIC31XX_INTRDACFLAG, &value);
	अगर (ret) अणु
		dev_err(dev, "Failed to read interrupt mask: %d\n", ret);
		जाओ निकास;
	पूर्ण

	अगर (value)
		handled = true;
	अन्यथा
		जाओ पढ़ो_overflow;

	अगर (value & AIC31XX_HPLSCDETECT)
		dev_err(dev, "Short circuit on Left output is detected\n");
	अगर (value & AIC31XX_HPRSCDETECT)
		dev_err(dev, "Short circuit on Right output is detected\n");
	अगर (value & (AIC31XX_HSPLUG | AIC31XX_BUTTONPRESS)) अणु
		अचिन्हित पूर्णांक val;
		पूर्णांक status = 0;

		ret = regmap_पढ़ो(aic31xx->regmap, AIC31XX_INTRDACFLAG2,
				  &val);
		अगर (ret) अणु
			dev_err(dev, "Failed to read interrupt mask: %d\n",
				ret);
			जाओ निकास;
		पूर्ण

		अगर (val & AIC31XX_BUTTONPRESS)
			status |= SND_JACK_BTN_0;

		ret = regmap_पढ़ो(aic31xx->regmap, AIC31XX_HSDETECT, &val);
		अगर (ret) अणु
			dev_err(dev, "Failed to read headset type: %d\n", ret);
			जाओ निकास;
		पूर्ण

		चयन ((val & AIC31XX_HSD_TYPE_MASK) >>
			AIC31XX_HSD_TYPE_SHIFT) अणु
		हाल AIC31XX_HSD_HP:
			status |= SND_JACK_HEADPHONE;
			अवरोध;
		हाल AIC31XX_HSD_HS:
			status |= SND_JACK_HEADSET;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (aic31xx->jack)
			snd_soc_jack_report(aic31xx->jack, status,
					    AIC31XX_JACK_MASK);
	पूर्ण
	अगर (value & ~(AIC31XX_HPLSCDETECT |
		      AIC31XX_HPRSCDETECT |
		      AIC31XX_HSPLUG |
		      AIC31XX_BUTTONPRESS))
		dev_err(dev, "Unknown DAC interrupt flags: 0x%08x\n", value);

पढ़ो_overflow:
	ret = regmap_पढ़ो(aic31xx->regmap, AIC31XX_OFFLAG, &value);
	अगर (ret) अणु
		dev_err(dev, "Failed to read overflow flag: %d\n", ret);
		जाओ निकास;
	पूर्ण

	अगर (value)
		handled = true;
	अन्यथा
		जाओ निकास;

	अगर (value & AIC31XX_DAC_OF_LEFT)
		dev_warn(dev, "Left-channel DAC overflow has occurred\n");
	अगर (value & AIC31XX_DAC_OF_RIGHT)
		dev_warn(dev, "Right-channel DAC overflow has occurred\n");
	अगर (value & AIC31XX_DAC_OF_SHIFTER)
		dev_warn(dev, "DAC barrel shifter overflow has occurred\n");
	अगर (value & AIC31XX_ADC_OF)
		dev_warn(dev, "ADC overflow has occurred\n");
	अगर (value & AIC31XX_ADC_OF_SHIFTER)
		dev_warn(dev, "ADC barrel shifter overflow has occurred\n");
	अगर (value & ~(AIC31XX_DAC_OF_LEFT |
		      AIC31XX_DAC_OF_RIGHT |
		      AIC31XX_DAC_OF_SHIFTER |
		      AIC31XX_ADC_OF |
		      AIC31XX_ADC_OF_SHIFTER))
		dev_warn(dev, "Unknown overflow interrupt flags: 0x%08x\n", value);

निकास:
	अगर (handled)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल व्योम aic31xx_configure_ocmv(काष्ठा aic31xx_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;
	पूर्णांक dvdd, avdd;
	u32 value;

	अगर (dev->fwnode &&
	    fwnode_property_पढ़ो_u32(dev->fwnode, "ai31xx-ocmv", &value)) अणु
		/* OCMV setting is क्रमced by DT */
		अगर (value <= 3) अणु
			priv->ocmv = value;
			वापस;
		पूर्ण
	पूर्ण

	avdd = regulator_get_voltage(priv->supplies[3].consumer);
	dvdd = regulator_get_voltage(priv->supplies[5].consumer);

	अगर (avdd > 3600000 || dvdd > 1950000) अणु
		dev_warn(dev,
			 "Too high supply voltage(s) AVDD: %d, DVDD: %d\n",
			 avdd, dvdd);
	पूर्ण अन्यथा अगर (avdd == 3600000 && dvdd == 1950000) अणु
		priv->ocmv = AIC31XX_HPD_OCMV_1_8V;
	पूर्ण अन्यथा अगर (avdd >= 3300000 && dvdd >= 1800000) अणु
		priv->ocmv = AIC31XX_HPD_OCMV_1_65V;
	पूर्ण अन्यथा अगर (avdd >= 3000000 && dvdd >= 1650000) अणु
		priv->ocmv = AIC31XX_HPD_OCMV_1_5V;
	पूर्ण अन्यथा अगर (avdd >= 2700000 && dvdd >= 1525000) अणु
		priv->ocmv = AIC31XX_HPD_OCMV_1_35V;
	पूर्ण अन्यथा अणु
		dev_warn(dev,
			 "Invalid supply voltage(s) AVDD: %d, DVDD: %d\n",
			 avdd, dvdd);
	पूर्ण
पूर्ण

अटल पूर्णांक aic31xx_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा aic31xx_priv *aic31xx;
	अचिन्हित पूर्णांक micbias_value = MICBIAS_2_0V;
	पूर्णांक i, ret;

	dev_dbg(&i2c->dev, "## %s: %s codec_type = %d\n", __func__,
		id->name, (पूर्णांक)id->driver_data);

	aic31xx = devm_kzalloc(&i2c->dev, माप(*aic31xx), GFP_KERNEL);
	अगर (!aic31xx)
		वापस -ENOMEM;

	aic31xx->regmap = devm_regmap_init_i2c(i2c, &aic31xx_i2c_regmap);
	अगर (IS_ERR(aic31xx->regmap)) अणु
		ret = PTR_ERR(aic31xx->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण
	aic31xx->dev = &i2c->dev;
	aic31xx->irq = i2c->irq;

	aic31xx->codec_type = id->driver_data;

	dev_set_drvdata(aic31xx->dev, aic31xx);

	fwnode_property_पढ़ो_u32(aic31xx->dev->fwnode, "ai31xx-micbias-vg",
				 &micbias_value);
	चयन (micbias_value) अणु
	हाल MICBIAS_2_0V:
	हाल MICBIAS_2_5V:
	हाल MICBIAS_AVDDV:
		aic31xx->micbias_vg = micbias_value;
		अवरोध;
	शेष:
		dev_err(aic31xx->dev, "Bad ai31xx-micbias-vg value %d\n",
			micbias_value);
		aic31xx->micbias_vg = MICBIAS_2_0V;
	पूर्ण

	अगर (dev_get_platdata(aic31xx->dev)) अणु
		स_नकल(&aic31xx->pdata, dev_get_platdata(aic31xx->dev), माप(aic31xx->pdata));
		aic31xx->codec_type = aic31xx->pdata.codec_type;
		aic31xx->micbias_vg = aic31xx->pdata.micbias_vg;
	पूर्ण

	aic31xx->gpio_reset = devm_gpiod_get_optional(aic31xx->dev, "reset",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(aic31xx->gpio_reset)) अणु
		अगर (PTR_ERR(aic31xx->gpio_reset) != -EPROBE_DEFER)
			dev_err(aic31xx->dev, "not able to acquire gpio\n");
		वापस PTR_ERR(aic31xx->gpio_reset);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(aic31xx->supplies); i++)
		aic31xx->supplies[i].supply = aic31xx_supply_names[i];

	ret = devm_regulator_bulk_get(aic31xx->dev,
				      ARRAY_SIZE(aic31xx->supplies),
				      aic31xx->supplies);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(aic31xx->dev,
				"Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	aic31xx_configure_ocmv(aic31xx);

	अगर (aic31xx->irq > 0) अणु
		regmap_update_bits(aic31xx->regmap, AIC31XX_GPIO1,
				   AIC31XX_GPIO1_FUNC_MASK,
				   AIC31XX_GPIO1_INT1 <<
				   AIC31XX_GPIO1_FUNC_SHIFT);

		regmap_ग_लिखो(aic31xx->regmap, AIC31XX_INT1CTRL,
			     AIC31XX_HSPLUGDET |
			     AIC31XX_BUTTONPRESSDET |
			     AIC31XX_SC |
			     AIC31XX_ENGINE);

		ret = devm_request_thपढ़ोed_irq(aic31xx->dev, aic31xx->irq,
						शून्य, aic31xx_irq,
						IRQF_ONESHOT, "aic31xx-irq",
						aic31xx);
		अगर (ret) अणु
			dev_err(aic31xx->dev, "Unable to request IRQ\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (aic31xx->codec_type & DAC31XX_BIT)
		वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				&soc_codec_driver_aic31xx,
				dac31xx_dai_driver,
				ARRAY_SIZE(dac31xx_dai_driver));
	अन्यथा
		वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				&soc_codec_driver_aic31xx,
				aic31xx_dai_driver,
				ARRAY_SIZE(aic31xx_dai_driver));
पूर्ण

अटल स्थिर काष्ठा i2c_device_id aic31xx_i2c_id[] = अणु
	अणु "tlv320aic310x", AIC3100 पूर्ण,
	अणु "tlv320aic311x", AIC3110 पूर्ण,
	अणु "tlv320aic3100", AIC3100 पूर्ण,
	अणु "tlv320aic3110", AIC3110 पूर्ण,
	अणु "tlv320aic3120", AIC3120 पूर्ण,
	अणु "tlv320aic3111", AIC3111 पूर्ण,
	अणु "tlv320dac3100", DAC3100 पूर्ण,
	अणु "tlv320dac3101", DAC3101 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, aic31xx_i2c_id);

अटल काष्ठा i2c_driver aic31xx_i2c_driver = अणु
	.driver = अणु
		.name	= "tlv320aic31xx-codec",
		.of_match_table = of_match_ptr(tlv320aic31xx_of_match),
		.acpi_match_table = ACPI_PTR(aic31xx_acpi_match),
	पूर्ण,
	.probe		= aic31xx_i2c_probe,
	.id_table	= aic31xx_i2c_id,
पूर्ण;
module_i2c_driver(aic31xx_i2c_driver);

MODULE_AUTHOR("Jyri Sarha <jsarha@ti.com>");
MODULE_DESCRIPTION("ASoC TLV320AIC31xx CODEC Driver");
MODULE_LICENSE("GPL v2");
