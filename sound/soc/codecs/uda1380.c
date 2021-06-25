<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * uda1380.c - Philips UDA1380 ALSA SoC audio driver
 *
 * Copyright (c) 2007-2009 Philipp Zabel <philipp.zabel@gmail.com>
 *
 * Modअगरied by Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com> to fit पूर्णांकo SoC
 * codec model.
 *
 * Copyright (c) 2005 Giorgio Padrin <giorgio@mandarinlogiq.org>
 * Copyright 2005 Openedhand Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/uda1380.h>

#समावेश "uda1380.h"

/* codec निजी data */
काष्ठा uda1380_priv अणु
	काष्ठा snd_soc_component *component;
	अचिन्हित पूर्णांक dac_clk;
	काष्ठा work_काष्ठा work;
	काष्ठा i2c_client *i2c;
	u16 *reg_cache;
पूर्ण;

/*
 * uda1380 रेजिस्टर cache
 */
अटल स्थिर u16 uda1380_reg[UDA1380_CACHEREGNUM] = अणु
	0x0502, 0x0000, 0x0000, 0x3f3f,
	0x0202, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0xff00, 0x0000, 0x4800,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x8000, 0x0002, 0x0000,
पूर्ण;

अटल अचिन्हित दीर्घ uda1380_cache_dirty;

/*
 * पढ़ो uda1380 रेजिस्टर cache
 */
अटल अंतरभूत अचिन्हित पूर्णांक uda1380_पढ़ो_reg_cache(काष्ठा snd_soc_component *component,
	अचिन्हित पूर्णांक reg)
अणु
	काष्ठा uda1380_priv *uda1380 = snd_soc_component_get_drvdata(component);
	u16 *cache = uda1380->reg_cache;

	अगर (reg == UDA1380_RESET)
		वापस 0;
	अगर (reg >= UDA1380_CACHEREGNUM)
		वापस -1;
	वापस cache[reg];
पूर्ण

/*
 * ग_लिखो uda1380 रेजिस्टर cache
 */
अटल अंतरभूत व्योम uda1380_ग_लिखो_reg_cache(काष्ठा snd_soc_component *component,
	u16 reg, अचिन्हित पूर्णांक value)
अणु
	काष्ठा uda1380_priv *uda1380 = snd_soc_component_get_drvdata(component);
	u16 *cache = uda1380->reg_cache;

	अगर (reg >= UDA1380_CACHEREGNUM)
		वापस;
	अगर ((reg >= 0x10) && (cache[reg] != value))
		set_bit(reg - 0x10, &uda1380_cache_dirty);
	cache[reg] = value;
पूर्ण

/*
 * ग_लिखो to the UDA1380 रेजिस्टर space
 */
अटल पूर्णांक uda1380_ग_लिखो(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक value)
अणु
	काष्ठा uda1380_priv *uda1380 = snd_soc_component_get_drvdata(component);
	u8 data[3];

	/* data is
	 *   data[0] is रेजिस्टर offset
	 *   data[1] is MS byte
	 *   data[2] is LS byte
	 */
	data[0] = reg;
	data[1] = (value & 0xff00) >> 8;
	data[2] = value & 0x00ff;

	uda1380_ग_लिखो_reg_cache(component, reg, value);

	/* the पूर्णांकerpolator & decimator regs must only be written when the
	 * codec DAI is active.
	 */
	अगर (!snd_soc_component_active(component) && (reg >= UDA1380_MVOL))
		वापस 0;
	pr_debug("uda1380: hw write %x val %x\n", reg, value);
	अगर (i2c_master_send(uda1380->i2c, data, 3) == 3) अणु
		अचिन्हित पूर्णांक val;
		i2c_master_send(uda1380->i2c, data, 1);
		i2c_master_recv(uda1380->i2c, data, 2);
		val = (data[0]<<8) | data[1];
		अगर (val != value) अणु
			pr_debug("uda1380: READ BACK VAL %x\n",
					(data[0]<<8) | data[1]);
			वापस -EIO;
		पूर्ण
		अगर (reg >= 0x10)
			clear_bit(reg - 0x10, &uda1380_cache_dirty);
		वापस 0;
	पूर्ण अन्यथा
		वापस -EIO;
पूर्ण

अटल व्योम uda1380_sync_cache(काष्ठा snd_soc_component *component)
अणु
	काष्ठा uda1380_priv *uda1380 = snd_soc_component_get_drvdata(component);
	पूर्णांक reg;
	u8 data[3];
	u16 *cache = uda1380->reg_cache;

	/* Sync reg_cache with the hardware */
	क्रम (reg = 0; reg < UDA1380_MVOL; reg++) अणु
		data[0] = reg;
		data[1] = (cache[reg] & 0xff00) >> 8;
		data[2] = cache[reg] & 0x00ff;
		अगर (i2c_master_send(uda1380->i2c, data, 3) != 3)
			dev_err(component->dev, "%s: write to reg 0x%x failed\n",
				__func__, reg);
	पूर्ण
पूर्ण

अटल पूर्णांक uda1380_reset(काष्ठा snd_soc_component *component)
अणु
	काष्ठा uda1380_platक्रमm_data *pdata = component->dev->platक्रमm_data;
	काष्ठा uda1380_priv *uda1380 = snd_soc_component_get_drvdata(component);

	अगर (gpio_is_valid(pdata->gpio_reset)) अणु
		gpio_set_value(pdata->gpio_reset, 1);
		mdelay(1);
		gpio_set_value(pdata->gpio_reset, 0);
	पूर्ण अन्यथा अणु
		u8 data[3];

		data[0] = UDA1380_RESET;
		data[1] = 0;
		data[2] = 0;

		अगर (i2c_master_send(uda1380->i2c, data, 3) != 3) अणु
			dev_err(component->dev, "%s: failed\n", __func__);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uda1380_flush_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uda1380_priv *uda1380 = container_of(work, काष्ठा uda1380_priv, work);
	काष्ठा snd_soc_component *uda1380_component = uda1380->component;
	पूर्णांक bit, reg;

	क्रम_each_set_bit(bit, &uda1380_cache_dirty, UDA1380_CACHEREGNUM - 0x10) अणु
		reg = 0x10 + bit;
		pr_debug("uda1380: flush reg %x val %x:\n", reg,
				uda1380_पढ़ो_reg_cache(uda1380_component, reg));
		uda1380_ग_लिखो(uda1380_component, reg,
				uda1380_पढ़ो_reg_cache(uda1380_component, reg));
		clear_bit(bit, &uda1380_cache_dirty);
	पूर्ण

पूर्ण

/* declarations of ALSA reg_elem_REAL controls */
अटल स्थिर अक्षर *uda1380_deemp[] = अणु
	"None",
	"32kHz",
	"44.1kHz",
	"48kHz",
	"96kHz",
पूर्ण;
अटल स्थिर अक्षर *uda1380_input_sel[] = अणु
	"Line",
	"Mic + Line R",
	"Line L",
	"Mic",
पूर्ण;
अटल स्थिर अक्षर *uda1380_output_sel[] = अणु
	"DAC",
	"Analog Mixer",
पूर्ण;
अटल स्थिर अक्षर *uda1380_spf_mode[] = अणु
	"Flat",
	"Minimum1",
	"Minimum2",
	"Maximum"
पूर्ण;
अटल स्थिर अक्षर *uda1380_capture_sel[] = अणु
	"ADC",
	"Digital Mixer"
पूर्ण;
अटल स्थिर अक्षर *uda1380_sel_ns[] = अणु
	"3rd-order",
	"5th-order"
पूर्ण;
अटल स्थिर अक्षर *uda1380_mix_control[] = अणु
	"off",
	"PCM only",
	"before sound processing",
	"after sound processing"
पूर्ण;
अटल स्थिर अक्षर *uda1380_sdet_setting[] = अणु
	"3200",
	"4800",
	"9600",
	"19200"
पूर्ण;
अटल स्थिर अक्षर *uda1380_os_setting[] = अणु
	"single-speed",
	"double-speed (no mixing)",
	"quad-speed (no mixing)"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत uda1380_deemp_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(UDA1380_DEEMP, 8, ARRAY_SIZE(uda1380_deemp),
			uda1380_deemp),
	SOC_ENUM_SINGLE(UDA1380_DEEMP, 0, ARRAY_SIZE(uda1380_deemp),
			uda1380_deemp),
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(uda1380_input_sel_क्रमागत,
			    UDA1380_ADC, 2, uda1380_input_sel);		/* SEL_MIC, SEL_LNA */
अटल SOC_ENUM_SINGLE_DECL(uda1380_output_sel_क्रमागत,
			    UDA1380_PM, 7, uda1380_output_sel);		/* R02_EN_AVC */
अटल SOC_ENUM_SINGLE_DECL(uda1380_spf_क्रमागत,
			    UDA1380_MODE, 14, uda1380_spf_mode);		/* M */
अटल SOC_ENUM_SINGLE_DECL(uda1380_capture_sel_क्रमागत,
			    UDA1380_IFACE, 6, uda1380_capture_sel);	/* SEL_SOURCE */
अटल SOC_ENUM_SINGLE_DECL(uda1380_sel_ns_क्रमागत,
			    UDA1380_MIXER, 14, uda1380_sel_ns);		/* SEL_NS */
अटल SOC_ENUM_SINGLE_DECL(uda1380_mix_क्रमागत,
			    UDA1380_MIXER, 12, uda1380_mix_control);	/* MIX, MIX_POS */
अटल SOC_ENUM_SINGLE_DECL(uda1380_sdet_क्रमागत,
			    UDA1380_MIXER, 4, uda1380_sdet_setting);	/* SD_VALUE */
अटल SOC_ENUM_SINGLE_DECL(uda1380_os_क्रमागत,
			    UDA1380_MIXER, 0, uda1380_os_setting);	/* OS */

/*
 * from -48 dB in 1.5 dB steps (mute instead of -49.5 dB)
 */
अटल DECLARE_TLV_DB_SCALE(amix_tlv, -4950, 150, 1);

/*
 * from -78 dB in 1 dB steps (3 dB steps, really. LSB are ignored),
 * from -66 dB in 0.5 dB steps (2 dB steps, really) and
 * from -52 dB in 0.25 dB steps
 */
अटल स्थिर DECLARE_TLV_DB_RANGE(mvol_tlv,
	0, 15, TLV_DB_SCALE_ITEM(-8200, 100, 1),
	16, 43, TLV_DB_SCALE_ITEM(-6600, 50, 0),
	44, 252, TLV_DB_SCALE_ITEM(-5200, 25, 0)
);

/*
 * from -72 dB in 1.5 dB steps (6 dB steps really),
 * from -66 dB in 0.75 dB steps (3 dB steps really),
 * from -60 dB in 0.5 dB steps (2 dB steps really) and
 * from -46 dB in 0.25 dB steps
 */
अटल स्थिर DECLARE_TLV_DB_RANGE(vc_tlv,
	0, 7, TLV_DB_SCALE_ITEM(-7800, 150, 1),
	8, 15, TLV_DB_SCALE_ITEM(-6600, 75, 0),
	16, 43, TLV_DB_SCALE_ITEM(-6000, 50, 0),
	44, 228, TLV_DB_SCALE_ITEM(-4600, 25, 0)
);

/* from 0 to 6 dB in 2 dB steps अगर SPF mode != flat */
अटल DECLARE_TLV_DB_SCALE(tr_tlv, 0, 200, 0);

/* from 0 to 24 dB in 2 dB steps, अगर SPF mode == maximum, otherwise cuts
 * off at 18 dB max) */
अटल DECLARE_TLV_DB_SCALE(bb_tlv, 0, 200, 0);

/* from -63 to 24 dB in 0.5 dB steps (-128...48) */
अटल DECLARE_TLV_DB_SCALE(dec_tlv, -6400, 50, 1);

/* from 0 to 24 dB in 3 dB steps */
अटल DECLARE_TLV_DB_SCALE(pga_tlv, 0, 300, 0);

/* from 0 to 30 dB in 2 dB steps */
अटल DECLARE_TLV_DB_SCALE(vga_tlv, 0, 200, 0);

अटल स्थिर काष्ठा snd_kcontrol_new uda1380_snd_controls[] = अणु
	SOC_DOUBLE_TLV("Analog Mixer Volume", UDA1380_AMIX, 0, 8, 44, 1, amix_tlv),	/* AVCR, AVCL */
	SOC_DOUBLE_TLV("Master Playback Volume", UDA1380_MVOL, 0, 8, 252, 1, mvol_tlv),	/* MVCL, MVCR */
	SOC_SINGLE_TLV("ADC Playback Volume", UDA1380_MIXVOL, 8, 228, 1, vc_tlv),	/* VC2 */
	SOC_SINGLE_TLV("PCM Playback Volume", UDA1380_MIXVOL, 0, 228, 1, vc_tlv),	/* VC1 */
	SOC_ENUM("Sound Processing Filter", uda1380_spf_क्रमागत),				/* M */
	SOC_DOUBLE_TLV("Tone Control - Treble", UDA1380_MODE, 4, 12, 3, 0, tr_tlv), 	/* TRL, TRR */
	SOC_DOUBLE_TLV("Tone Control - Bass", UDA1380_MODE, 0, 8, 15, 0, bb_tlv),	/* BBL, BBR */
/**/	SOC_SINGLE("Master Playback Switch", UDA1380_DEEMP, 14, 1, 1),		/* MTM */
	SOC_SINGLE("ADC Playback Switch", UDA1380_DEEMP, 11, 1, 1),		/* MT2 from decimation filter */
	SOC_ENUM("ADC Playback De-emphasis", uda1380_deemp_क्रमागत[0]),		/* DE2 */
	SOC_SINGLE("PCM Playback Switch", UDA1380_DEEMP, 3, 1, 1),		/* MT1, from digital data input */
	SOC_ENUM("PCM Playback De-emphasis", uda1380_deemp_क्रमागत[1]),		/* DE1 */
	SOC_SINGLE("DAC Polarity inverting Switch", UDA1380_MIXER, 15, 1, 0),	/* DA_POL_INV */
	SOC_ENUM("Noise Shaper", uda1380_sel_ns_क्रमागत),				/* SEL_NS */
	SOC_ENUM("Digital Mixer Signal Control", uda1380_mix_क्रमागत),		/* MIX_POS, MIX */
	SOC_SINGLE("Silence Detector Switch", UDA1380_MIXER, 6, 1, 0),		/* SDET_ON */
	SOC_ENUM("Silence Detector Setting", uda1380_sdet_क्रमागत),		/* SD_VALUE */
	SOC_ENUM("Oversampling Input", uda1380_os_क्रमागत),			/* OS */
	SOC_DOUBLE_S8_TLV("ADC Capture Volume", UDA1380_DEC, -128, 48, dec_tlv),	/* ML_DEC, MR_DEC */
/**/	SOC_SINGLE("ADC Capture Switch", UDA1380_PGA, 15, 1, 1),		/* MT_ADC */
	SOC_DOUBLE_TLV("Line Capture Volume", UDA1380_PGA, 0, 8, 8, 0, pga_tlv), /* PGA_GAINCTRLL, PGA_GAINCTRLR */
	SOC_SINGLE("ADC Polarity inverting Switch", UDA1380_ADC, 12, 1, 0),	/* ADCPOL_INV */
	SOC_SINGLE_TLV("Mic Capture Volume", UDA1380_ADC, 8, 15, 0, vga_tlv),	/* VGA_CTRL */
	SOC_SINGLE("DC Filter Bypass Switch", UDA1380_ADC, 1, 1, 0),		/* SKIP_DCFIL (beक्रमe decimator) */
	SOC_SINGLE("DC Filter Enable Switch", UDA1380_ADC, 0, 1, 0),		/* EN_DCFIL (at output of decimator) */
	SOC_SINGLE("AGC Timing", UDA1380_AGC, 8, 7, 0),			/* TODO: क्रमागत, see table 62 */
	SOC_SINGLE("AGC Target level", UDA1380_AGC, 2, 3, 1),			/* AGC_LEVEL */
	/* -5.5, -8, -11.5, -14 dBFS */
	SOC_SINGLE("AGC Switch", UDA1380_AGC, 0, 1, 0),
पूर्ण;

/* Input mux */
अटल स्थिर काष्ठा snd_kcontrol_new uda1380_input_mux_control =
	SOC_DAPM_ENUM("Route", uda1380_input_sel_क्रमागत);

/* Output mux */
अटल स्थिर काष्ठा snd_kcontrol_new uda1380_output_mux_control =
	SOC_DAPM_ENUM("Route", uda1380_output_sel_क्रमागत);

/* Capture mux */
अटल स्थिर काष्ठा snd_kcontrol_new uda1380_capture_mux_control =
	SOC_DAPM_ENUM("Route", uda1380_capture_sel_क्रमागत);


अटल स्थिर काष्ठा snd_soc_dapm_widget uda1380_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0,
		&uda1380_input_mux_control),
	SND_SOC_DAPM_MUX("Output Mux", SND_SOC_NOPM, 0, 0,
		&uda1380_output_mux_control),
	SND_SOC_DAPM_MUX("Capture Mux", SND_SOC_NOPM, 0, 0,
		&uda1380_capture_mux_control),
	SND_SOC_DAPM_PGA("Left PGA", UDA1380_PM, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Right PGA", UDA1380_PM, 1, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mic LNA", UDA1380_PM, 4, 0, शून्य, 0),
	SND_SOC_DAPM_ADC("Left ADC", "Left Capture", UDA1380_PM, 2, 0),
	SND_SOC_DAPM_ADC("Right ADC", "Right Capture", UDA1380_PM, 0, 0),
	SND_SOC_DAPM_INPUT("VINM"),
	SND_SOC_DAPM_INPUT("VINL"),
	SND_SOC_DAPM_INPUT("VINR"),
	SND_SOC_DAPM_MIXER("Analog Mixer", UDA1380_PM, 6, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("VOUTLHP"),
	SND_SOC_DAPM_OUTPUT("VOUTRHP"),
	SND_SOC_DAPM_OUTPUT("VOUTL"),
	SND_SOC_DAPM_OUTPUT("VOUTR"),
	SND_SOC_DAPM_DAC("DAC", "Playback", UDA1380_PM, 10, 0),
	SND_SOC_DAPM_PGA("HeadPhone Driver", UDA1380_PM, 13, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route uda1380_dapm_routes[] = अणु

	/* output mux */
	अणु"HeadPhone Driver", शून्य, "Output Mux"पूर्ण,
	अणु"VOUTR", शून्य, "Output Mux"पूर्ण,
	अणु"VOUTL", शून्य, "Output Mux"पूर्ण,

	अणु"Analog Mixer", शून्य, "VINR"पूर्ण,
	अणु"Analog Mixer", शून्य, "VINL"पूर्ण,
	अणु"Analog Mixer", शून्य, "DAC"पूर्ण,

	अणु"Output Mux", "DAC", "DAC"पूर्ण,
	अणु"Output Mux", "Analog Mixer", "Analog Mixer"पूर्ण,

	/* अणु"DAC", "Digital Mixer", "I2S" पूर्ण */

	/* headphone driver */
	अणु"VOUTLHP", शून्य, "HeadPhone Driver"पूर्ण,
	अणु"VOUTRHP", शून्य, "HeadPhone Driver"पूर्ण,

	/* input mux */
	अणु"Left ADC", शून्य, "Input Mux"पूर्ण,
	अणु"Input Mux", "Mic", "Mic LNA"पूर्ण,
	अणु"Input Mux", "Mic + Line R", "Mic LNA"पूर्ण,
	अणु"Input Mux", "Line L", "Left PGA"पूर्ण,
	अणु"Input Mux", "Line", "Left PGA"पूर्ण,

	/* right input */
	अणु"Right ADC", "Mic + Line R", "Right PGA"पूर्ण,
	अणु"Right ADC", "Line", "Right PGA"पूर्ण,

	/* inमाला_दो */
	अणु"Mic LNA", शून्य, "VINM"पूर्ण,
	अणु"Left PGA", शून्य, "VINL"पूर्ण,
	अणु"Right PGA", शून्य, "VINR"पूर्ण,
पूर्ण;

अटल पूर्णांक uda1380_set_dai_fmt_both(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक अगरace;

	/* set up DAI based upon fmt */
	अगरace = uda1380_पढ़ो_reg_cache(component, UDA1380_IFACE);
	अगरace &= ~(R01_SFORI_MASK | R01_SIM | R01_SFORO_MASK);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= R01_SFORI_I2S | R01_SFORO_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LSB:
		अगरace |= R01_SFORI_LSB16 | R01_SFORO_LSB16;
		अवरोध;
	हाल SND_SOC_DAIFMT_MSB:
		अगरace |= R01_SFORI_MSB | R01_SFORO_MSB;
	पूर्ण

	/* DATAI is slave only, so in single-link mode, this has to be slave */
	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS)
		वापस -EINVAL;

	uda1380_ग_लिखो_reg_cache(component, UDA1380_IFACE, अगरace);

	वापस 0;
पूर्ण

अटल पूर्णांक uda1380_set_dai_fmt_playback(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक अगरace;

	/* set up DAI based upon fmt */
	अगरace = uda1380_पढ़ो_reg_cache(component, UDA1380_IFACE);
	अगरace &= ~R01_SFORI_MASK;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= R01_SFORI_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LSB:
		अगरace |= R01_SFORI_LSB16;
		अवरोध;
	हाल SND_SOC_DAIFMT_MSB:
		अगरace |= R01_SFORI_MSB;
	पूर्ण

	/* DATAI is slave only, so this has to be slave */
	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS)
		वापस -EINVAL;

	uda1380_ग_लिखो(component, UDA1380_IFACE, अगरace);

	वापस 0;
पूर्ण

अटल पूर्णांक uda1380_set_dai_fmt_capture(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक अगरace;

	/* set up DAI based upon fmt */
	अगरace = uda1380_पढ़ो_reg_cache(component, UDA1380_IFACE);
	अगरace &= ~(R01_SIM | R01_SFORO_MASK);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= R01_SFORO_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LSB:
		अगरace |= R01_SFORO_LSB16;
		अवरोध;
	हाल SND_SOC_DAIFMT_MSB:
		अगरace |= R01_SFORO_MSB;
	पूर्ण

	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) == SND_SOC_DAIFMT_CBM_CFM)
		अगरace |= R01_SIM;

	uda1380_ग_लिखो(component, UDA1380_IFACE, अगरace);

	वापस 0;
पूर्ण

अटल पूर्णांक uda1380_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा uda1380_priv *uda1380 = snd_soc_component_get_drvdata(component);
	पूर्णांक mixer = uda1380_पढ़ो_reg_cache(component, UDA1380_MIXER);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		uda1380_ग_लिखो_reg_cache(component, UDA1380_MIXER,
					mixer & ~R14_SILENCE);
		schedule_work(&uda1380->work);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		uda1380_ग_लिखो_reg_cache(component, UDA1380_MIXER,
					mixer | R14_SILENCE);
		schedule_work(&uda1380->work);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक uda1380_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 clk = uda1380_पढ़ो_reg_cache(component, UDA1380_CLK);

	/* set WSPLL घातer and भागider अगर running from this घड़ी */
	अगर (clk & R00_DAC_CLK) अणु
		पूर्णांक rate = params_rate(params);
		u16 pm = uda1380_पढ़ो_reg_cache(component, UDA1380_PM);
		clk &= ~0x3; /* clear SEL_LOOP_DIV */
		चयन (rate) अणु
		हाल 6250 ... 12500:
			clk |= 0x0;
			अवरोध;
		हाल 12501 ... 25000:
			clk |= 0x1;
			अवरोध;
		हाल 25001 ... 50000:
			clk |= 0x2;
			अवरोध;
		हाल 50001 ... 100000:
			clk |= 0x3;
			अवरोध;
		पूर्ण
		uda1380_ग_लिखो(component, UDA1380_PM, R02_PON_PLL | pm);
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		clk |= R00_EN_DAC | R00_EN_INT;
	अन्यथा
		clk |= R00_EN_ADC | R00_EN_DEC;

	uda1380_ग_लिखो(component, UDA1380_CLK, clk);
	वापस 0;
पूर्ण

अटल व्योम uda1380_pcm_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 clk = uda1380_पढ़ो_reg_cache(component, UDA1380_CLK);

	/* shut करोwn WSPLL घातer अगर running from this घड़ी */
	अगर (clk & R00_DAC_CLK) अणु
		u16 pm = uda1380_पढ़ो_reg_cache(component, UDA1380_PM);
		uda1380_ग_लिखो(component, UDA1380_PM, ~R02_PON_PLL & pm);
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		clk &= ~(R00_EN_DAC | R00_EN_INT);
	अन्यथा
		clk &= ~(R00_EN_ADC | R00_EN_DEC);

	uda1380_ग_लिखो(component, UDA1380_CLK, clk);
पूर्ण

अटल पूर्णांक uda1380_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक pm = uda1380_पढ़ो_reg_cache(component, UDA1380_PM);
	पूर्णांक reg;
	काष्ठा uda1380_platक्रमm_data *pdata = component->dev->platक्रमm_data;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		/* ADC, DAC on */
		uda1380_ग_लिखो(component, UDA1380_PM, R02_PON_BIAS | pm);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			अगर (gpio_is_valid(pdata->gpio_घातer)) अणु
				gpio_set_value(pdata->gpio_घातer, 1);
				mdelay(1);
				uda1380_reset(component);
			पूर्ण

			uda1380_sync_cache(component);
		पूर्ण
		uda1380_ग_लिखो(component, UDA1380_PM, 0x0);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अगर (!gpio_is_valid(pdata->gpio_घातer))
			अवरोध;

		gpio_set_value(pdata->gpio_घातer, 0);

		/* Mark mixer regs cache dirty to sync them with
		 * codec regs on घातer on.
		 */
		क्रम (reg = UDA1380_MVOL; reg < UDA1380_CACHEREGNUM; reg++)
			set_bit(reg - 0x10, &uda1380_cache_dirty);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा UDA1380_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		       SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |\
		       SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)

अटल स्थिर काष्ठा snd_soc_dai_ops uda1380_dai_ops = अणु
	.hw_params	= uda1380_pcm_hw_params,
	.shutकरोwn	= uda1380_pcm_shutकरोwn,
	.trigger	= uda1380_trigger,
	.set_fmt	= uda1380_set_dai_fmt_both,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops uda1380_dai_ops_playback = अणु
	.hw_params	= uda1380_pcm_hw_params,
	.shutकरोwn	= uda1380_pcm_shutकरोwn,
	.trigger	= uda1380_trigger,
	.set_fmt	= uda1380_set_dai_fmt_playback,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops uda1380_dai_ops_capture = अणु
	.hw_params	= uda1380_pcm_hw_params,
	.shutकरोwn	= uda1380_pcm_shutकरोwn,
	.trigger	= uda1380_trigger,
	.set_fmt	= uda1380_set_dai_fmt_capture,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver uda1380_dai[] = अणु
अणु
	.name = "uda1380-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = UDA1380_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = UDA1380_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.ops = &uda1380_dai_ops,
पूर्ण,
अणु /* playback only - dual पूर्णांकerface */
	.name = "uda1380-hifi-playback",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = UDA1380_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &uda1380_dai_ops_playback,
पूर्ण,
अणु /* capture only - dual पूर्णांकerface*/
	.name = "uda1380-hifi-capture",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = UDA1380_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &uda1380_dai_ops_capture,
पूर्ण,
पूर्ण;

अटल पूर्णांक uda1380_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा uda1380_platक्रमm_data *pdata =component->dev->platक्रमm_data;
	काष्ठा uda1380_priv *uda1380 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	uda1380->component = component;

	अगर (!gpio_is_valid(pdata->gpio_घातer)) अणु
		ret = uda1380_reset(component);
		अगर (ret)
			वापस ret;
	पूर्ण

	INIT_WORK(&uda1380->work, uda1380_flush_work);

	/* set घड़ी input */
	चयन (pdata->dac_clk) अणु
	हाल UDA1380_DAC_CLK_SYSCLK:
		uda1380_ग_लिखो_reg_cache(component, UDA1380_CLK, 0);
		अवरोध;
	हाल UDA1380_DAC_CLK_WSPLL:
		uda1380_ग_लिखो_reg_cache(component, UDA1380_CLK,
			R00_DAC_CLK);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_uda1380 = अणु
	.probe			= uda1380_probe,
	.पढ़ो			= uda1380_पढ़ो_reg_cache,
	.ग_लिखो			= uda1380_ग_लिखो,
	.set_bias_level		= uda1380_set_bias_level,
	.controls		= uda1380_snd_controls,
	.num_controls		= ARRAY_SIZE(uda1380_snd_controls),
	.dapm_widमाला_लो		= uda1380_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(uda1380_dapm_widमाला_लो),
	.dapm_routes		= uda1380_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(uda1380_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक uda1380_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा uda1380_platक्रमm_data *pdata = i2c->dev.platक्रमm_data;
	काष्ठा uda1380_priv *uda1380;
	पूर्णांक ret;

	अगर (!pdata)
		वापस -EINVAL;

	uda1380 = devm_kzalloc(&i2c->dev, माप(काष्ठा uda1380_priv),
			       GFP_KERNEL);
	अगर (uda1380 == शून्य)
		वापस -ENOMEM;

	अगर (gpio_is_valid(pdata->gpio_reset)) अणु
		ret = devm_gpio_request_one(&i2c->dev, pdata->gpio_reset,
			GPIOF_OUT_INIT_LOW, "uda1380 reset");
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (gpio_is_valid(pdata->gpio_घातer)) अणु
		ret = devm_gpio_request_one(&i2c->dev, pdata->gpio_घातer,
			GPIOF_OUT_INIT_LOW, "uda1380 power");
		अगर (ret)
			वापस ret;
	पूर्ण

	uda1380->reg_cache = devm_kmemdup(&i2c->dev,
					uda1380_reg,
					ARRAY_SIZE(uda1380_reg) * माप(u16),
					GFP_KERNEL);
	अगर (!uda1380->reg_cache)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, uda1380);
	uda1380->i2c = i2c;

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_uda1380, uda1380_dai, ARRAY_SIZE(uda1380_dai));
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id uda1380_i2c_id[] = अणु
	अणु "uda1380", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, uda1380_i2c_id);

अटल स्थिर काष्ठा of_device_id uda1380_of_match[] = अणु
	अणु .compatible = "nxp,uda1380", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uda1380_of_match);

अटल काष्ठा i2c_driver uda1380_i2c_driver = अणु
	.driver = अणु
		.name =  "uda1380-codec",
		.of_match_table = uda1380_of_match,
	पूर्ण,
	.probe =    uda1380_i2c_probe,
	.id_table = uda1380_i2c_id,
पूर्ण;

module_i2c_driver(uda1380_i2c_driver);

MODULE_AUTHOR("Giorgio Padrin");
MODULE_DESCRIPTION("Audio support for codec Philips UDA1380");
MODULE_LICENSE("GPL");
