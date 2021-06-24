<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Author: Ola Lilja <ola.o.lilja@stericsson.com>,
 *         Kristoffer Karlsson <kristoffer.karlsson@stericsson.com>,
 *         Roger Nilsson <roger.xr.nilsson@stericsson.com>,
 *         क्रम ST-Ericsson.
 *
 *         Based on the early work करोne by:
 *         Mikko J. Lehto <mikko.lehto@symbio.com>,
 *         Mikko Sarmanne <mikko.sarmanne@symbio.com>,
 *         Jarmo K. Kuronen <jarmo.kuronen@symbio.com>,
 *         क्रम ST-Ericsson.
 *
 * License terms:
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500-sysctrl.h>
#समावेश <linux/mfd/abx500/ab8500-codec.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>

#समावेश "ab8500-codec.h"

/* Macrocell value definitions */
#घोषणा CLK_32K_OUT2_DISABLE			0x01
#घोषणा INACTIVE_RESET_AUDIO			0x02
#घोषणा ENABLE_AUDIO_CLK_TO_AUDIO_BLK		0x10
#घोषणा ENABLE_VINTCORE12_SUPPLY		0x04
#घोषणा GPIO27_सूची_OUTPUT			0x04
#घोषणा GPIO29_सूची_OUTPUT			0x10
#घोषणा GPIO31_सूची_OUTPUT			0x40

/* Macrocell रेजिस्टर definitions */
#घोषणा AB8500_GPIO_सूची4_REG			0x13 /* Bank AB8500_MISC */

/* Nr of FIR/IIR-coeff banks in ANC-block */
#घोषणा AB8500_NR_OF_ANC_COEFF_BANKS		2

/* Minimum duration to keep ANC IIR Init bit high or
low beक्रमe proceeding with the configuration sequence */
#घोषणा AB8500_ANC_SM_DELAY			2000

#घोषणा AB8500_FILTER_CONTROL(xname, xcount, xmin, xmax) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.info = filter_control_info, \
	.get = filter_control_get, .put = filter_control_put, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा filter_control) \
		अणु.count = xcount, .min = xmin, .max = xmaxपूर्ण पूर्ण

काष्ठा filter_control अणु
	दीर्घ min, max;
	अचिन्हित पूर्णांक count;
	दीर्घ value[128];
पूर्ण;

/* Sidetone states */
अटल स्थिर अक्षर * स्थिर क्रमागत_sid_state[] = अणु
	"Unconfigured",
	"Apply FIR",
	"FIR is configured",
पूर्ण;
क्रमागत sid_state अणु
	SID_UNCONFIGURED = 0,
	SID_APPLY_FIR = 1,
	SID_FIR_CONFIGURED = 2,
पूर्ण;

अटल स्थिर अक्षर * स्थिर क्रमागत_anc_state[] = अणु
	"Unconfigured",
	"Apply FIR and IIR",
	"FIR and IIR are configured",
	"Apply FIR",
	"FIR is configured",
	"Apply IIR",
	"IIR is configured"
पूर्ण;
क्रमागत anc_state अणु
	ANC_UNCONFIGURED = 0,
	ANC_APPLY_FIR_IIR = 1,
	ANC_FIR_IIR_CONFIGURED = 2,
	ANC_APPLY_FIR = 3,
	ANC_FIR_CONFIGURED = 4,
	ANC_APPLY_IIR = 5,
	ANC_IIR_CONFIGURED = 6
पूर्ण;

/* Analog microphones */
क्रमागत amic_idx अणु
	AMIC_IDX_1A,
	AMIC_IDX_1B,
	AMIC_IDX_2
पूर्ण;

/* Private data क्रम AB8500 device-driver */
काष्ठा ab8500_codec_drvdata अणु
	काष्ठा regmap *regmap;
	काष्ठा mutex ctrl_lock;

	/* Sidetone */
	दीर्घ *sid_fir_values;
	क्रमागत sid_state sid_status;

	/* ANC */
	दीर्घ *anc_fir_values;
	दीर्घ *anc_iir_values;
	क्रमागत anc_state anc_status;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *amic_micbias_str(क्रमागत amic_micbias micbias)
अणु
	चयन (micbias) अणु
	हाल AMIC_MICBIAS_VAMIC1:
		वापस "VAMIC1";
	हाल AMIC_MICBIAS_VAMIC2:
		वापस "VAMIC2";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *amic_type_str(क्रमागत amic_type type)
अणु
	चयन (type) अणु
	हाल AMIC_TYPE_DIFFERENTIAL:
		वापस "DIFFERENTIAL";
	हाल AMIC_TYPE_SINGLE_ENDED:
		वापस "SINGLE ENDED";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

/*
 * Read'n'ग_लिखो functions
 */

/* Read a रेजिस्टर from the audio-bank of AB8500 */
अटल पूर्णांक ab8500_codec_पढ़ो_reg(व्योम *context, अचिन्हित पूर्णांक reg,
				 अचिन्हित पूर्णांक *value)
अणु
	काष्ठा device *dev = context;
	पूर्णांक status;

	u8 value8;
	status = abx500_get_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_AUDIO,
						   reg, &value8);
	*value = (अचिन्हित पूर्णांक)value8;

	वापस status;
पूर्ण

/* Write to a रेजिस्टर in the audio-bank of AB8500 */
अटल पूर्णांक ab8500_codec_ग_लिखो_reg(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक value)
अणु
	काष्ठा device *dev = context;

	वापस abx500_set_रेजिस्टर_पूर्णांकerruptible(dev, AB8500_AUDIO,
						 reg, value);
पूर्ण

अटल स्थिर काष्ठा regmap_config ab8500_codec_regmap = अणु
	.reg_पढ़ो = ab8500_codec_पढ़ो_reg,
	.reg_ग_लिखो = ab8500_codec_ग_लिखो_reg,
पूर्ण;

/*
 * Controls - DAPM
 */

/* Earpiece */

/* Earpiece source selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_ear_lineout_source[] = अणु"Headset Left",
						"Speaker Left"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_ear_lineout_source, AB8500_DMICFILTCONF,
			AB8500_DMICFILTCONF_DA3TOEAR, क्रमागत_ear_lineout_source);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_ear_lineout_source =
	SOC_DAPM_ENUM("Earpiece or LineOut Mono Source",
		dapm_क्रमागत_ear_lineout_source);

/* LineOut */

/* LineOut source selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_lineout_source[] = अणु"Mono Path", "Stereo Path"पूर्ण;
अटल SOC_ENUM_DOUBLE_DECL(dapm_क्रमागत_lineout_source, AB8500_ANACONF5,
			AB8500_ANACONF5_HSLDACTOLOL,
			AB8500_ANACONF5_HSRDACTOLOR, क्रमागत_lineout_source);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_lineout_source[] = अणु
	SOC_DAPM_ENUM("LineOut Source", dapm_क्रमागत_lineout_source),
पूर्ण;

/* Handsमुक्त */

/* Speaker Left - ANC selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_HFx_sel[] = अणु"Audio Path", "ANC"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_HFl_sel, AB8500_DIGMULTCONF2,
			AB8500_DIGMULTCONF2_HFLSEL, क्रमागत_HFx_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_HFl_select[] = अणु
	SOC_DAPM_ENUM("Speaker Left Source", dapm_क्रमागत_HFl_sel),
पूर्ण;

/* Speaker Right - ANC selector */
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_HFr_sel, AB8500_DIGMULTCONF2,
			AB8500_DIGMULTCONF2_HFRSEL, क्रमागत_HFx_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_HFr_select[] = अणु
	SOC_DAPM_ENUM("Speaker Right Source", dapm_क्रमागत_HFr_sel),
पूर्ण;

/* Mic 1 */

/* Mic 1 - Mic 1a or 1b selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_mic1ab_sel[] = अणु"Mic 1b", "Mic 1a"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_mic1ab_sel, AB8500_ANACONF3,
			AB8500_ANACONF3_MIC1SEL, क्रमागत_mic1ab_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_mic1ab_mux[] = अणु
	SOC_DAPM_ENUM("Mic 1a or 1b Select", dapm_क्रमागत_mic1ab_sel),
पूर्ण;

/* Mic 1 - AD3 - Mic 1 or DMic 3 selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_ad3_sel[] = अणु"Mic 1", "DMic 3"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_ad3_sel, AB8500_DIGMULTCONF1,
			AB8500_DIGMULTCONF1_AD3SEL, क्रमागत_ad3_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_ad3_select[] = अणु
	SOC_DAPM_ENUM("AD3 Source Select", dapm_क्रमागत_ad3_sel),
पूर्ण;

/* Mic 1 - AD6 - Mic 1 or DMic 6 selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_ad6_sel[] = अणु"Mic 1", "DMic 6"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_ad6_sel, AB8500_DIGMULTCONF1,
			AB8500_DIGMULTCONF1_AD6SEL, क्रमागत_ad6_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_ad6_select[] = अणु
	SOC_DAPM_ENUM("AD6 Source Select", dapm_क्रमागत_ad6_sel),
पूर्ण;

/* Mic 2 */

/* Mic 2 - AD5 - Mic 2 or DMic 5 selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_ad5_sel[] = अणु"Mic 2", "DMic 5"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_ad5_sel, AB8500_DIGMULTCONF1,
			AB8500_DIGMULTCONF1_AD5SEL, क्रमागत_ad5_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_ad5_select[] = अणु
	SOC_DAPM_ENUM("AD5 Source Select", dapm_क्रमागत_ad5_sel),
पूर्ण;

/* LineIn */

/* LineIn left - AD1 - LineIn Left or DMic 1 selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_ad1_sel[] = अणु"LineIn Left", "DMic 1"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_ad1_sel, AB8500_DIGMULTCONF1,
			AB8500_DIGMULTCONF1_AD1SEL, क्रमागत_ad1_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_ad1_select[] = अणु
	SOC_DAPM_ENUM("AD1 Source Select", dapm_क्रमागत_ad1_sel),
पूर्ण;

/* LineIn right - Mic 2 or LineIn Right selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_mic2lr_sel[] = अणु"Mic 2", "LineIn Right"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_mic2lr_sel, AB8500_ANACONF3,
			AB8500_ANACONF3_LINRSEL, क्रमागत_mic2lr_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_mic2lr_select[] = अणु
	SOC_DAPM_ENUM("Mic 2 or LINR Select", dapm_क्रमागत_mic2lr_sel),
पूर्ण;

/* LineIn right - AD2 - LineIn Right or DMic2 selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_ad2_sel[] = अणु"LineIn Right", "DMic 2"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_ad2_sel, AB8500_DIGMULTCONF1,
			AB8500_DIGMULTCONF1_AD2SEL, क्रमागत_ad2_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_ad2_select[] = अणु
	SOC_DAPM_ENUM("AD2 Source Select", dapm_क्रमागत_ad2_sel),
पूर्ण;


/* ANC */

अटल स्थिर अक्षर * स्थिर क्रमागत_anc_in_sel[] = अणु"Mic 1 / DMic 6",
					"Mic 2 / DMic 5"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_anc_in_sel, AB8500_DMICFILTCONF,
			AB8500_DMICFILTCONF_ANCINSEL, क्रमागत_anc_in_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_anc_in_select[] = अणु
	SOC_DAPM_ENUM("ANC Source", dapm_क्रमागत_anc_in_sel),
पूर्ण;

/* ANC - Enable/Disable */
अटल स्थिर काष्ठा snd_kcontrol_new dapm_anc_enable[] = अणु
	SOC_DAPM_SINGLE("Switch", AB8500_ANCCONF1,
			AB8500_ANCCONF1_Eन_अंकC, 0, 0),
पूर्ण;

/* ANC to Earpiece - Mute */
अटल स्थिर काष्ठा snd_kcontrol_new dapm_anc_ear_mute[] = अणु
	SOC_DAPM_SINGLE("Switch", AB8500_DIGMULTCONF1,
			AB8500_DIGMULTCONF1_ANCSEL, 1, 0),
पूर्ण;



/* Sidetone left */

/* Sidetone left - Input selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_stfir1_in_sel[] = अणु
	"LineIn Left", "LineIn Right", "Mic 1", "Headset Left"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_stfir1_in_sel, AB8500_DIGMULTCONF2,
			AB8500_DIGMULTCONF2_FIRSID1SEL, क्रमागत_stfir1_in_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_stfir1_in_select[] = अणु
	SOC_DAPM_ENUM("Sidetone Left Source", dapm_क्रमागत_stfir1_in_sel),
पूर्ण;

/* Sidetone right path */

/* Sidetone right - Input selector */
अटल स्थिर अक्षर * स्थिर क्रमागत_stfir2_in_sel[] = अणु
	"LineIn Right", "Mic 1", "DMic 4", "Headset Right"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_stfir2_in_sel, AB8500_DIGMULTCONF2,
			AB8500_DIGMULTCONF2_FIRSID2SEL, क्रमागत_stfir2_in_sel);
अटल स्थिर काष्ठा snd_kcontrol_new dapm_stfir2_in_select[] = अणु
	SOC_DAPM_ENUM("Sidetone Right Source", dapm_क्रमागत_stfir2_in_sel),
पूर्ण;

/* Vibra */

अटल स्थिर अक्षर * स्थिर क्रमागत_pwm2vibx[] = अणु"Audio Path", "PWM Generator"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_pwm2vib1, AB8500_PWMGENCONF1,
			AB8500_PWMGENCONF1_PWMTOVIB1, क्रमागत_pwm2vibx);

अटल स्थिर काष्ठा snd_kcontrol_new dapm_pwm2vib1[] = अणु
	SOC_DAPM_ENUM("Vibra 1 Controller", dapm_क्रमागत_pwm2vib1),
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dapm_क्रमागत_pwm2vib2, AB8500_PWMGENCONF1,
			AB8500_PWMGENCONF1_PWMTOVIB2, क्रमागत_pwm2vibx);

अटल स्थिर काष्ठा snd_kcontrol_new dapm_pwm2vib2[] = अणु
	SOC_DAPM_ENUM("Vibra 2 Controller", dapm_क्रमागत_pwm2vib2),
पूर्ण;

/*
 * DAPM-widमाला_लो
 */

अटल स्थिर काष्ठा snd_soc_dapm_widget ab8500_dapm_widमाला_लो[] = अणु

	/* Clocks */
	SND_SOC_DAPM_CLOCK_SUPPLY("audioclk"),

	/* Regulators */
	SND_SOC_DAPM_REGULATOR_SUPPLY("V-AUD", 0, 0),
	SND_SOC_DAPM_REGULATOR_SUPPLY("V-AMIC1", 0, 0),
	SND_SOC_DAPM_REGULATOR_SUPPLY("V-AMIC2", 0, 0),
	SND_SOC_DAPM_REGULATOR_SUPPLY("V-DMIC", 0, 0),

	/* Power */
	SND_SOC_DAPM_SUPPLY("Audio Power",
			AB8500_POWERUP, AB8500_POWERUP_POWERUP, 0,
			शून्य, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPLY("Audio Analog Power",
			AB8500_POWERUP, AB8500_POWERUP_Eन_अंकA, 0,
			शून्य, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* Main supply node */
	SND_SOC_DAPM_SUPPLY("Main Supply", SND_SOC_NOPM, 0, 0,
			शून्य, SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* DA/AD */

	SND_SOC_DAPM_INPUT("ADC Input"),
	SND_SOC_DAPM_ADC("ADC", "ab8500_0c", SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DAC", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("DAC Output"),

	SND_SOC_DAPM_AIF_IN("DA_IN1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DA_IN2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DA_IN3", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DA_IN4", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DA_IN5", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DA_IN6", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AD_OUT1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AD_OUT2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AD_OUT3", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AD_OUT4", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AD_OUT57", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AD_OUT68", शून्य, 0, SND_SOC_NOPM, 0, 0),

	/* Headset path */

	SND_SOC_DAPM_SUPPLY("Charge Pump", AB8500_ANACONF5,
			AB8500_ANACONF5_ENCPHS, 0, शून्य, 0),

	SND_SOC_DAPM_DAC("DA1 Enable", "ab8500_0p",
			AB8500_DAPATHENA, AB8500_DAPATHENA_ENDA1, 0),
	SND_SOC_DAPM_DAC("DA2 Enable", "ab8500_0p",
			AB8500_DAPATHENA, AB8500_DAPATHENA_ENDA2, 0),

	SND_SOC_DAPM_PGA("HSL Digital Volume", SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_PGA("HSR Digital Volume", SND_SOC_NOPM, 0, 0,
			शून्य, 0),

	SND_SOC_DAPM_DAC("HSL DAC", "ab8500_0p",
			AB8500_DAPATHCONF, AB8500_DAPATHCONF_ENDACHSL, 0),
	SND_SOC_DAPM_DAC("HSR DAC", "ab8500_0p",
			AB8500_DAPATHCONF, AB8500_DAPATHCONF_ENDACHSR, 0),
	SND_SOC_DAPM_MIXER("HSL DAC Mute", AB8500_MUTECONF,
			AB8500_MUTECONF_MUTDACHSL, 1,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("HSR DAC Mute", AB8500_MUTECONF,
			AB8500_MUTECONF_MUTDACHSR, 1,
			शून्य, 0),
	SND_SOC_DAPM_DAC("HSL DAC Driver", "ab8500_0p",
			AB8500_ANACONF3, AB8500_ANACONF3_ENDRVHSL, 0),
	SND_SOC_DAPM_DAC("HSR DAC Driver", "ab8500_0p",
			AB8500_ANACONF3, AB8500_ANACONF3_ENDRVHSR, 0),

	SND_SOC_DAPM_MIXER("HSL Mute",
			AB8500_MUTECONF, AB8500_MUTECONF_MUTHSL, 1,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("HSR Mute",
			AB8500_MUTECONF, AB8500_MUTECONF_MUTHSR, 1,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("HSL Enable",
			AB8500_ANACONF4, AB8500_ANACONF4_ENHSL, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("HSR Enable",
			AB8500_ANACONF4, AB8500_ANACONF4_ENHSR, 0,
			शून्य, 0),
	SND_SOC_DAPM_PGA("HSL Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_PGA("HSR Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),

	SND_SOC_DAPM_OUTPUT("Headset Left"),
	SND_SOC_DAPM_OUTPUT("Headset Right"),

	/* LineOut path */

	SND_SOC_DAPM_MUX("LineOut Source",
			SND_SOC_NOPM, 0, 0, dapm_lineout_source),

	SND_SOC_DAPM_MIXER("LOL Disable HFL",
			AB8500_ANACONF4, AB8500_ANACONF4_ENHFL, 1,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("LOR Disable HFR",
			AB8500_ANACONF4, AB8500_ANACONF4_ENHFR, 1,
			शून्य, 0),

	SND_SOC_DAPM_MIXER("LOL Enable",
			AB8500_ANACONF5, AB8500_ANACONF5_ENLOL, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("LOR Enable",
			AB8500_ANACONF5, AB8500_ANACONF5_ENLOR, 0,
			शून्य, 0),

	SND_SOC_DAPM_OUTPUT("LineOut Left"),
	SND_SOC_DAPM_OUTPUT("LineOut Right"),

	/* Earpiece path */

	SND_SOC_DAPM_MUX("Earpiece or LineOut Mono Source",
			SND_SOC_NOPM, 0, 0, &dapm_ear_lineout_source),
	SND_SOC_DAPM_MIXER("EAR DAC",
			AB8500_DAPATHCONF, AB8500_DAPATHCONF_ENDACEAR, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("EAR Mute",
			AB8500_MUTECONF, AB8500_MUTECONF_MUTEAR, 1,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("EAR Enable",
			AB8500_ANACONF4, AB8500_ANACONF4_ENEAR, 0,
			शून्य, 0),

	SND_SOC_DAPM_OUTPUT("Earpiece"),

	/* Handsमुक्त path */

	SND_SOC_DAPM_MIXER("DA3 Channel Volume",
			AB8500_DAPATHENA, AB8500_DAPATHENA_ENDA3, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("DA4 Channel Volume",
			AB8500_DAPATHENA, AB8500_DAPATHENA_ENDA4, 0,
			शून्य, 0),
	SND_SOC_DAPM_MUX("Speaker Left Source",
			SND_SOC_NOPM, 0, 0, dapm_HFl_select),
	SND_SOC_DAPM_MUX("Speaker Right Source",
			SND_SOC_NOPM, 0, 0, dapm_HFr_select),
	SND_SOC_DAPM_MIXER("HFL DAC", AB8500_DAPATHCONF,
			AB8500_DAPATHCONF_ENDACHFL, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("HFR DAC",
			AB8500_DAPATHCONF, AB8500_DAPATHCONF_ENDACHFR, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("DA4 or ANC path to HfR",
			AB8500_DIGMULTCONF2, AB8500_DIGMULTCONF2_DATOHFREN, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("DA3 or ANC path to HfL",
			AB8500_DIGMULTCONF2, AB8500_DIGMULTCONF2_DATOHFLEN, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("HFL Enable",
			AB8500_ANACONF4, AB8500_ANACONF4_ENHFL, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("HFR Enable",
			AB8500_ANACONF4, AB8500_ANACONF4_ENHFR, 0,
			शून्य, 0),

	SND_SOC_DAPM_OUTPUT("Speaker Left"),
	SND_SOC_DAPM_OUTPUT("Speaker Right"),

	/* Vibrator path */

	SND_SOC_DAPM_INPUT("PWMGEN1"),
	SND_SOC_DAPM_INPUT("PWMGEN2"),

	SND_SOC_DAPM_MIXER("DA5 Channel Volume",
			AB8500_DAPATHENA, AB8500_DAPATHENA_ENDA5, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("DA6 Channel Volume",
			AB8500_DAPATHENA, AB8500_DAPATHENA_ENDA6, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("VIB1 DAC",
			AB8500_DAPATHCONF, AB8500_DAPATHCONF_ENDACVIB1, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("VIB2 DAC",
			AB8500_DAPATHCONF, AB8500_DAPATHCONF_ENDACVIB2, 0,
			शून्य, 0),
	SND_SOC_DAPM_MUX("Vibra 1 Controller",
			SND_SOC_NOPM, 0, 0, dapm_pwm2vib1),
	SND_SOC_DAPM_MUX("Vibra 2 Controller",
			SND_SOC_NOPM, 0, 0, dapm_pwm2vib2),
	SND_SOC_DAPM_MIXER("VIB1 Enable",
			AB8500_ANACONF4, AB8500_ANACONF4_ENVIB1, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("VIB2 Enable",
			AB8500_ANACONF4, AB8500_ANACONF4_ENVIB2, 0,
			शून्य, 0),

	SND_SOC_DAPM_OUTPUT("Vibra 1"),
	SND_SOC_DAPM_OUTPUT("Vibra 2"),

	/* Mic 1 */

	SND_SOC_DAPM_INPUT("Mic 1"),

	SND_SOC_DAPM_MUX("Mic 1a or 1b Select",
			SND_SOC_NOPM, 0, 0, dapm_mic1ab_mux),
	SND_SOC_DAPM_MIXER("MIC1 Mute",
			AB8500_ANACONF2, AB8500_ANACONF2_MUTMIC1, 1,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("MIC1A V-AMICx Enable",
			AB8500_ANACONF2, AB8500_ANACONF2_ENMIC1, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("MIC1B V-AMICx Enable",
			AB8500_ANACONF2, AB8500_ANACONF2_ENMIC1, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("MIC1 ADC",
			AB8500_ANACONF3, AB8500_ANACONF3_ENADCMIC, 0,
			शून्य, 0),
	SND_SOC_DAPM_MUX("AD3 Source Select",
			SND_SOC_NOPM, 0, 0, dapm_ad3_select),
	SND_SOC_DAPM_MIXER("AD3 Channel Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("AD3 Enable",
			AB8500_ADPATHENA, AB8500_ADPATHENA_ENAD34, 0,
			शून्य, 0),

	/* Mic 2 */

	SND_SOC_DAPM_INPUT("Mic 2"),

	SND_SOC_DAPM_MIXER("MIC2 Mute",
			AB8500_ANACONF2, AB8500_ANACONF2_MUTMIC2, 1,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("MIC2 V-AMICx Enable", AB8500_ANACONF2,
			AB8500_ANACONF2_ENMIC2, 0,
			शून्य, 0),

	/* LineIn */

	SND_SOC_DAPM_INPUT("LineIn Left"),
	SND_SOC_DAPM_INPUT("LineIn Right"),

	SND_SOC_DAPM_MIXER("LINL Mute",
			AB8500_ANACONF2, AB8500_ANACONF2_MUTLINL, 1,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("LINR Mute",
			AB8500_ANACONF2, AB8500_ANACONF2_MUTLINR, 1,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("LINL Enable", AB8500_ANACONF2,
			AB8500_ANACONF2_ENLINL, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("LINR Enable", AB8500_ANACONF2,
			AB8500_ANACONF2_ENLINR, 0,
			शून्य, 0),

	/* LineIn Bypass path */
	SND_SOC_DAPM_MIXER("LINL to HSL Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("LINR to HSR Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),

	/* LineIn, Mic 2 */
	SND_SOC_DAPM_MUX("Mic 2 or LINR Select",
			SND_SOC_NOPM, 0, 0, dapm_mic2lr_select),
	SND_SOC_DAPM_MIXER("LINL ADC", AB8500_ANACONF3,
			AB8500_ANACONF3_ENADCLINL, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("LINR ADC", AB8500_ANACONF3,
			AB8500_ANACONF3_ENADCLINR, 0,
			शून्य, 0),
	SND_SOC_DAPM_MUX("AD1 Source Select",
			SND_SOC_NOPM, 0, 0, dapm_ad1_select),
	SND_SOC_DAPM_MUX("AD2 Source Select",
			SND_SOC_NOPM, 0, 0, dapm_ad2_select),
	SND_SOC_DAPM_MIXER("AD1 Channel Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("AD2 Channel Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),

	SND_SOC_DAPM_MIXER("AD12 Enable",
			AB8500_ADPATHENA, AB8500_ADPATHENA_ENAD12, 0,
			शून्य, 0),

	/* HD Capture path */

	SND_SOC_DAPM_MUX("AD5 Source Select",
			SND_SOC_NOPM, 0, 0, dapm_ad5_select),
	SND_SOC_DAPM_MUX("AD6 Source Select",
			SND_SOC_NOPM, 0, 0, dapm_ad6_select),
	SND_SOC_DAPM_MIXER("AD5 Channel Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("AD6 Channel Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("AD57 Enable",
			AB8500_ADPATHENA, AB8500_ADPATHENA_ENAD5768, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("AD68 Enable",
			AB8500_ADPATHENA, AB8500_ADPATHENA_ENAD5768, 0,
			शून्य, 0),

	/* Digital Microphone path */

	SND_SOC_DAPM_INPUT("DMic 1"),
	SND_SOC_DAPM_INPUT("DMic 2"),
	SND_SOC_DAPM_INPUT("DMic 3"),
	SND_SOC_DAPM_INPUT("DMic 4"),
	SND_SOC_DAPM_INPUT("DMic 5"),
	SND_SOC_DAPM_INPUT("DMic 6"),

	SND_SOC_DAPM_MIXER("DMIC1",
			AB8500_DIGMICCONF, AB8500_DIGMICCONF_ENDMIC1, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("DMIC2",
			AB8500_DIGMICCONF, AB8500_DIGMICCONF_ENDMIC2, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("DMIC3",
			AB8500_DIGMICCONF, AB8500_DIGMICCONF_ENDMIC3, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("DMIC4",
			AB8500_DIGMICCONF, AB8500_DIGMICCONF_ENDMIC4, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("DMIC5",
			AB8500_DIGMICCONF, AB8500_DIGMICCONF_ENDMIC5, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("DMIC6",
			AB8500_DIGMICCONF, AB8500_DIGMICCONF_ENDMIC6, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("AD4 Channel Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("AD4 Enable",
			AB8500_ADPATHENA, AB8500_ADPATHENA_ENAD34,
			0, शून्य, 0),

	/* Acoustical Noise Cancellation path */

	SND_SOC_DAPM_INPUT("ANC Configure Input"),
	SND_SOC_DAPM_OUTPUT("ANC Configure Output"),

	SND_SOC_DAPM_MUX("ANC Source",
			SND_SOC_NOPM, 0, 0,
			dapm_anc_in_select),
	SND_SOC_DAPM_SWITCH("ANC",
			SND_SOC_NOPM, 0, 0,
			dapm_anc_enable),
	SND_SOC_DAPM_SWITCH("ANC to Earpiece",
			SND_SOC_NOPM, 0, 0,
			dapm_anc_ear_mute),

	/* Sidetone Filter path */

	SND_SOC_DAPM_MUX("Sidetone Left Source",
			SND_SOC_NOPM, 0, 0,
			dapm_stfir1_in_select),
	SND_SOC_DAPM_MUX("Sidetone Right Source",
			SND_SOC_NOPM, 0, 0,
			dapm_stfir2_in_select),
	SND_SOC_DAPM_MIXER("STFIR1 Control",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("STFIR2 Control",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("STFIR1 Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_MIXER("STFIR2 Volume",
			SND_SOC_NOPM, 0, 0,
			शून्य, 0),
पूर्ण;

/*
 * DAPM-routes
 */
अटल स्थिर काष्ठा snd_soc_dapm_route ab8500_dapm_routes[] = अणु
	/* Power AB8500 audio-block when AD/DA is active */
	अणु"Main Supply", शून्य, "V-AUD"पूर्ण,
	अणु"Main Supply", शून्य, "audioclk"पूर्ण,
	अणु"Main Supply", शून्य, "Audio Power"पूर्ण,
	अणु"Main Supply", शून्य, "Audio Analog Power"पूर्ण,

	अणु"DAC", शून्य, "ab8500_0p"पूर्ण,
	अणु"DAC", शून्य, "Main Supply"पूर्ण,
	अणु"ADC", शून्य, "ab8500_0c"पूर्ण,
	अणु"ADC", शून्य, "Main Supply"पूर्ण,

	/* ANC Configure */
	अणु"ANC Configure Input", शून्य, "Main Supply"पूर्ण,
	अणु"ANC Configure Output", शून्य, "ANC Configure Input"पूर्ण,

	/* AD/DA */
	अणु"ADC", शून्य, "ADC Input"पूर्ण,
	अणु"DAC Output", शून्य, "DAC"पूर्ण,

	/* Powerup अक्षरge pump अगर DA1/2 is in use */

	अणु"DA_IN1", शून्य, "ab8500_0p"पूर्ण,
	अणु"DA_IN1", शून्य, "Charge Pump"पूर्ण,
	अणु"DA_IN2", शून्य, "ab8500_0p"पूर्ण,
	अणु"DA_IN2", शून्य, "Charge Pump"पूर्ण,

	/* Headset path */

	अणु"DA1 Enable", शून्य, "DA_IN1"पूर्ण,
	अणु"DA2 Enable", शून्य, "DA_IN2"पूर्ण,

	अणु"HSL Digital Volume", शून्य, "DA1 Enable"पूर्ण,
	अणु"HSR Digital Volume", शून्य, "DA2 Enable"पूर्ण,

	अणु"HSL DAC", शून्य, "HSL Digital Volume"पूर्ण,
	अणु"HSR DAC", शून्य, "HSR Digital Volume"पूर्ण,

	अणु"HSL DAC Mute", शून्य, "HSL DAC"पूर्ण,
	अणु"HSR DAC Mute", शून्य, "HSR DAC"पूर्ण,

	अणु"HSL DAC Driver", शून्य, "HSL DAC Mute"पूर्ण,
	अणु"HSR DAC Driver", शून्य, "HSR DAC Mute"पूर्ण,

	अणु"HSL Mute", शून्य, "HSL DAC Driver"पूर्ण,
	अणु"HSR Mute", शून्य, "HSR DAC Driver"पूर्ण,

	अणु"HSL Enable", शून्य, "HSL Mute"पूर्ण,
	अणु"HSR Enable", शून्य, "HSR Mute"पूर्ण,

	अणु"HSL Volume", शून्य, "HSL Enable"पूर्ण,
	अणु"HSR Volume", शून्य, "HSR Enable"पूर्ण,

	अणु"Headset Left", शून्य, "HSL Volume"पूर्ण,
	अणु"Headset Right", शून्य, "HSR Volume"पूर्ण,

	/* HF or LineOut path */

	अणु"DA_IN3", शून्य, "ab8500_0p"पूर्ण,
	अणु"DA3 Channel Volume", शून्य, "DA_IN3"पूर्ण,
	अणु"DA_IN4", शून्य, "ab8500_0p"पूर्ण,
	अणु"DA4 Channel Volume", शून्य, "DA_IN4"पूर्ण,

	अणु"Speaker Left Source", "Audio Path", "DA3 Channel Volume"पूर्ण,
	अणु"Speaker Right Source", "Audio Path", "DA4 Channel Volume"पूर्ण,

	अणु"DA3 or ANC path to HfL", शून्य, "Speaker Left Source"पूर्ण,
	अणु"DA4 or ANC path to HfR", शून्य, "Speaker Right Source"पूर्ण,

	/* HF path */

	अणु"HFL DAC", शून्य, "DA3 or ANC path to HfL"पूर्ण,
	अणु"HFR DAC", शून्य, "DA4 or ANC path to HfR"पूर्ण,

	अणु"HFL Enable", शून्य, "HFL DAC"पूर्ण,
	अणु"HFR Enable", शून्य, "HFR DAC"पूर्ण,

	अणु"Speaker Left", शून्य, "HFL Enable"पूर्ण,
	अणु"Speaker Right", शून्य, "HFR Enable"पूर्ण,

	/* Earpiece path */

	अणु"Earpiece or LineOut Mono Source", "Headset Left",
		"HSL Digital Volume"पूर्ण,
	अणु"Earpiece or LineOut Mono Source", "Speaker Left",
		"DA3 or ANC path to HfL"पूर्ण,

	अणु"EAR DAC", शून्य, "Earpiece or LineOut Mono Source"पूर्ण,

	अणु"EAR Mute", शून्य, "EAR DAC"पूर्ण,

	अणु"EAR Enable", शून्य, "EAR Mute"पूर्ण,

	अणु"Earpiece", शून्य, "EAR Enable"पूर्ण,

	/* LineOut path stereo */

	अणु"LineOut Source", "Stereo Path", "HSL DAC Driver"पूर्ण,
	अणु"LineOut Source", "Stereo Path", "HSR DAC Driver"पूर्ण,

	/* LineOut path mono */

	अणु"LineOut Source", "Mono Path", "EAR DAC"पूर्ण,

	/* LineOut path */

	अणु"LOL Disable HFL", शून्य, "LineOut Source"पूर्ण,
	अणु"LOR Disable HFR", शून्य, "LineOut Source"पूर्ण,

	अणु"LOL Enable", शून्य, "LOL Disable HFL"पूर्ण,
	अणु"LOR Enable", शून्य, "LOR Disable HFR"पूर्ण,

	अणु"LineOut Left", शून्य, "LOL Enable"पूर्ण,
	अणु"LineOut Right", शून्य, "LOR Enable"पूर्ण,

	/* Vibrator path */

	अणु"DA_IN5", शून्य, "ab8500_0p"पूर्ण,
	अणु"DA5 Channel Volume", शून्य, "DA_IN5"पूर्ण,
	अणु"DA_IN6", शून्य, "ab8500_0p"पूर्ण,
	अणु"DA6 Channel Volume", शून्य, "DA_IN6"पूर्ण,

	अणु"VIB1 DAC", शून्य, "DA5 Channel Volume"पूर्ण,
	अणु"VIB2 DAC", शून्य, "DA6 Channel Volume"पूर्ण,

	अणु"Vibra 1 Controller", "Audio Path", "VIB1 DAC"पूर्ण,
	अणु"Vibra 2 Controller", "Audio Path", "VIB2 DAC"पूर्ण,
	अणु"Vibra 1 Controller", "PWM Generator", "PWMGEN1"पूर्ण,
	अणु"Vibra 2 Controller", "PWM Generator", "PWMGEN2"पूर्ण,

	अणु"VIB1 Enable", शून्य, "Vibra 1 Controller"पूर्ण,
	अणु"VIB2 Enable", शून्य, "Vibra 2 Controller"पूर्ण,

	अणु"Vibra 1", शून्य, "VIB1 Enable"पूर्ण,
	अणु"Vibra 2", शून्य, "VIB2 Enable"पूर्ण,


	/* Mic 2 */

	अणु"MIC2 V-AMICx Enable", शून्य, "Mic 2"पूर्ण,

	/* LineIn */
	अणु"LINL Mute", शून्य, "LineIn Left"पूर्ण,
	अणु"LINR Mute", शून्य, "LineIn Right"पूर्ण,

	अणु"LINL Enable", शून्य, "LINL Mute"पूर्ण,
	अणु"LINR Enable", शून्य, "LINR Mute"पूर्ण,

	/* LineIn, Mic 2 */
	अणु"Mic 2 or LINR Select", "LineIn Right", "LINR Enable"पूर्ण,
	अणु"Mic 2 or LINR Select", "Mic 2", "MIC2 V-AMICx Enable"पूर्ण,

	अणु"LINL ADC", शून्य, "LINL Enable"पूर्ण,
	अणु"LINR ADC", शून्य, "Mic 2 or LINR Select"पूर्ण,

	अणु"AD1 Source Select", "LineIn Left", "LINL ADC"पूर्ण,
	अणु"AD2 Source Select", "LineIn Right", "LINR ADC"पूर्ण,

	अणु"AD1 Channel Volume", शून्य, "AD1 Source Select"पूर्ण,
	अणु"AD2 Channel Volume", शून्य, "AD2 Source Select"पूर्ण,

	अणु"AD12 Enable", शून्य, "AD1 Channel Volume"पूर्ण,
	अणु"AD12 Enable", शून्य, "AD2 Channel Volume"पूर्ण,

	अणु"AD_OUT1", शून्य, "ab8500_0c"पूर्ण,
	अणु"AD_OUT1", शून्य, "AD12 Enable"पूर्ण,
	अणु"AD_OUT2", शून्य, "ab8500_0c"पूर्ण,
	अणु"AD_OUT2", शून्य, "AD12 Enable"पूर्ण,

	/* Mic 1 */

	अणु"MIC1 Mute", शून्य, "Mic 1"पूर्ण,

	अणु"MIC1A V-AMICx Enable", शून्य, "MIC1 Mute"पूर्ण,
	अणु"MIC1B V-AMICx Enable", शून्य, "MIC1 Mute"पूर्ण,

	अणु"Mic 1a or 1b Select", "Mic 1a", "MIC1A V-AMICx Enable"पूर्ण,
	अणु"Mic 1a or 1b Select", "Mic 1b", "MIC1B V-AMICx Enable"पूर्ण,

	अणु"MIC1 ADC", शून्य, "Mic 1a or 1b Select"पूर्ण,

	अणु"AD3 Source Select", "Mic 1", "MIC1 ADC"पूर्ण,

	अणु"AD3 Channel Volume", शून्य, "AD3 Source Select"पूर्ण,

	अणु"AD3 Enable", शून्य, "AD3 Channel Volume"पूर्ण,

	अणु"AD_OUT3", शून्य, "ab8500_0c"पूर्ण,
	अणु"AD_OUT3", शून्य, "AD3 Enable"पूर्ण,

	/* HD Capture path */

	अणु"AD5 Source Select", "Mic 2", "LINR ADC"पूर्ण,
	अणु"AD6 Source Select", "Mic 1", "MIC1 ADC"पूर्ण,

	अणु"AD5 Channel Volume", शून्य, "AD5 Source Select"पूर्ण,
	अणु"AD6 Channel Volume", शून्य, "AD6 Source Select"पूर्ण,

	अणु"AD57 Enable", शून्य, "AD5 Channel Volume"पूर्ण,
	अणु"AD68 Enable", शून्य, "AD6 Channel Volume"पूर्ण,

	अणु"AD_OUT57", शून्य, "ab8500_0c"पूर्ण,
	अणु"AD_OUT57", शून्य, "AD57 Enable"पूर्ण,
	अणु"AD_OUT68", शून्य, "ab8500_0c"पूर्ण,
	अणु"AD_OUT68", शून्य, "AD68 Enable"पूर्ण,

	/* Digital Microphone path */

	अणु"DMic 1", शून्य, "V-DMIC"पूर्ण,
	अणु"DMic 2", शून्य, "V-DMIC"पूर्ण,
	अणु"DMic 3", शून्य, "V-DMIC"पूर्ण,
	अणु"DMic 4", शून्य, "V-DMIC"पूर्ण,
	अणु"DMic 5", शून्य, "V-DMIC"पूर्ण,
	अणु"DMic 6", शून्य, "V-DMIC"पूर्ण,

	अणु"AD1 Source Select", शून्य, "DMic 1"पूर्ण,
	अणु"AD2 Source Select", शून्य, "DMic 2"पूर्ण,
	अणु"AD3 Source Select", शून्य, "DMic 3"पूर्ण,
	अणु"AD5 Source Select", शून्य, "DMic 5"पूर्ण,
	अणु"AD6 Source Select", शून्य, "DMic 6"पूर्ण,

	अणु"AD4 Channel Volume", शून्य, "DMic 4"पूर्ण,
	अणु"AD4 Enable", शून्य, "AD4 Channel Volume"पूर्ण,

	अणु"AD_OUT4", शून्य, "ab8500_0c"पूर्ण,
	अणु"AD_OUT4", शून्य, "AD4 Enable"पूर्ण,

	/* LineIn Bypass path */

	अणु"LINL to HSL Volume", शून्य, "LINL Enable"पूर्ण,
	अणु"LINR to HSR Volume", शून्य, "LINR Enable"पूर्ण,

	अणु"HSL DAC Driver", शून्य, "LINL to HSL Volume"पूर्ण,
	अणु"HSR DAC Driver", शून्य, "LINR to HSR Volume"पूर्ण,

	/* ANC path (Acoustic Noise Cancellation) */

	अणु"ANC Source", "Mic 2 / DMic 5", "AD5 Channel Volume"पूर्ण,
	अणु"ANC Source", "Mic 1 / DMic 6", "AD6 Channel Volume"पूर्ण,

	अणु"ANC", "Switch", "ANC Source"पूर्ण,

	अणु"Speaker Left Source", "ANC", "ANC"पूर्ण,
	अणु"Speaker Right Source", "ANC", "ANC"पूर्ण,
	अणु"ANC to Earpiece", "Switch", "ANC"पूर्ण,

	अणु"HSL Digital Volume", शून्य, "ANC to Earpiece"पूर्ण,

	/* Sidetone Filter path */

	अणु"Sidetone Left Source", "LineIn Left", "AD12 Enable"पूर्ण,
	अणु"Sidetone Left Source", "LineIn Right", "AD12 Enable"पूर्ण,
	अणु"Sidetone Left Source", "Mic 1", "AD3 Enable"पूर्ण,
	अणु"Sidetone Left Source", "Headset Left", "DA_IN1"पूर्ण,
	अणु"Sidetone Right Source", "LineIn Right", "AD12 Enable"पूर्ण,
	अणु"Sidetone Right Source", "Mic 1", "AD3 Enable"पूर्ण,
	अणु"Sidetone Right Source", "DMic 4", "AD4 Enable"पूर्ण,
	अणु"Sidetone Right Source", "Headset Right", "DA_IN2"पूर्ण,

	अणु"STFIR1 Control", शून्य, "Sidetone Left Source"पूर्ण,
	अणु"STFIR2 Control", शून्य, "Sidetone Right Source"पूर्ण,

	अणु"STFIR1 Volume", शून्य, "STFIR1 Control"पूर्ण,
	अणु"STFIR2 Volume", शून्य, "STFIR2 Control"पूर्ण,

	अणु"DA1 Enable", शून्य, "STFIR1 Volume"पूर्ण,
	अणु"DA2 Enable", शून्य, "STFIR2 Volume"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ab8500_dapm_routes_mic1a_vamicx[] = अणु
	अणु"MIC1A V-AMICx Enable", शून्य, "V-AMIC1"पूर्ण,
	अणु"MIC1A V-AMICx Enable", शून्य, "V-AMIC2"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ab8500_dapm_routes_mic1b_vamicx[] = अणु
	अणु"MIC1B V-AMICx Enable", शून्य, "V-AMIC1"पूर्ण,
	अणु"MIC1B V-AMICx Enable", शून्य, "V-AMIC2"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ab8500_dapm_routes_mic2_vamicx[] = अणु
	अणु"MIC2 V-AMICx Enable", शून्य, "V-AMIC1"पूर्ण,
	अणु"MIC2 V-AMICx Enable", शून्य, "V-AMIC2"पूर्ण,
पूर्ण;

/* ANC FIR-coefficients configuration sequence */
अटल व्योम anc_fir(काष्ठा snd_soc_component *component,
		अचिन्हित पूर्णांक bnk, अचिन्हित पूर्णांक par, अचिन्हित पूर्णांक val)
अणु
	अगर (par == 0 && bnk == 0)
		snd_soc_component_update_bits(component, AB8500_ANCCONF1,
			BIT(AB8500_ANCCONF1_ANCFIRUPDATE),
			BIT(AB8500_ANCCONF1_ANCFIRUPDATE));

	snd_soc_component_ग_लिखो(component, AB8500_ANCCONF5, val >> 8 & 0xff);
	snd_soc_component_ग_लिखो(component, AB8500_ANCCONF6, val &  0xff);

	अगर (par == AB8500_ANC_FIR_COEFFS - 1 && bnk == 1)
		snd_soc_component_update_bits(component, AB8500_ANCCONF1,
			BIT(AB8500_ANCCONF1_ANCFIRUPDATE), 0);
पूर्ण

/* ANC IIR-coefficients configuration sequence */
अटल व्योम anc_iir(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक bnk,
		अचिन्हित पूर्णांक par, अचिन्हित पूर्णांक val)
अणु
	अगर (par == 0) अणु
		अगर (bnk == 0) अणु
			snd_soc_component_update_bits(component, AB8500_ANCCONF1,
					BIT(AB8500_ANCCONF1_ANCIIRINIT),
					BIT(AB8500_ANCCONF1_ANCIIRINIT));
			usleep_range(AB8500_ANC_SM_DELAY, AB8500_ANC_SM_DELAY*2);
			snd_soc_component_update_bits(component, AB8500_ANCCONF1,
					BIT(AB8500_ANCCONF1_ANCIIRINIT), 0);
			usleep_range(AB8500_ANC_SM_DELAY, AB8500_ANC_SM_DELAY*2);
		पूर्ण अन्यथा अणु
			snd_soc_component_update_bits(component, AB8500_ANCCONF1,
					BIT(AB8500_ANCCONF1_ANCIIRUPDATE),
					BIT(AB8500_ANCCONF1_ANCIIRUPDATE));
		पूर्ण
	पूर्ण अन्यथा अगर (par > 3) अणु
		snd_soc_component_ग_लिखो(component, AB8500_ANCCONF7, 0);
		snd_soc_component_ग_लिखो(component, AB8500_ANCCONF8, val >> 16 & 0xff);
	पूर्ण

	snd_soc_component_ग_लिखो(component, AB8500_ANCCONF7, val >> 8 & 0xff);
	snd_soc_component_ग_लिखो(component, AB8500_ANCCONF8, val & 0xff);

	अगर (par == AB8500_ANC_IIR_COEFFS - 1 && bnk == 1)
		snd_soc_component_update_bits(component, AB8500_ANCCONF1,
			BIT(AB8500_ANCCONF1_ANCIIRUPDATE), 0);
पूर्ण

/* ANC IIR-/FIR-coefficients configuration sequence */
अटल व्योम anc_configure(काष्ठा snd_soc_component *component,
			bool apply_fir, bool apply_iir)
अणु
	काष्ठा ab8500_codec_drvdata *drvdata = dev_get_drvdata(component->dev);
	अचिन्हित पूर्णांक bnk, par, val;

	dev_dbg(component->dev, "%s: Enter.\n", __func__);

	अगर (apply_fir)
		snd_soc_component_update_bits(component, AB8500_ANCCONF1,
			BIT(AB8500_ANCCONF1_Eन_अंकC), 0);

	snd_soc_component_update_bits(component, AB8500_ANCCONF1,
		BIT(AB8500_ANCCONF1_Eन_अंकC), BIT(AB8500_ANCCONF1_Eन_अंकC));

	अगर (apply_fir)
		क्रम (bnk = 0; bnk < AB8500_NR_OF_ANC_COEFF_BANKS; bnk++)
			क्रम (par = 0; par < AB8500_ANC_FIR_COEFFS; par++) अणु
				val = snd_soc_component_पढ़ो(component,
						drvdata->anc_fir_values[par]);
				anc_fir(component, bnk, par, val);
			पूर्ण

	अगर (apply_iir)
		क्रम (bnk = 0; bnk < AB8500_NR_OF_ANC_COEFF_BANKS; bnk++)
			क्रम (par = 0; par < AB8500_ANC_IIR_COEFFS; par++) अणु
				val = snd_soc_component_पढ़ो(component,
						drvdata->anc_iir_values[par]);
				anc_iir(component, bnk, par, val);
			पूर्ण

	dev_dbg(component->dev, "%s: Exit.\n", __func__);
पूर्ण

/*
 * Control-events
 */

अटल पूर्णांक sid_status_control_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा ab8500_codec_drvdata *drvdata = dev_get_drvdata(component->dev);

	mutex_lock(&drvdata->ctrl_lock);
	ucontrol->value.क्रमागतerated.item[0] = drvdata->sid_status;
	mutex_unlock(&drvdata->ctrl_lock);

	वापस 0;
पूर्ण

/* Write sidetone FIR-coefficients configuration sequence */
अटल पूर्णांक sid_status_control_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा ab8500_codec_drvdata *drvdata = dev_get_drvdata(component->dev);
	अचिन्हित पूर्णांक param, sidconf, val;
	पूर्णांक status = 1;

	dev_dbg(component->dev, "%s: Enter\n", __func__);

	अगर (ucontrol->value.क्रमागतerated.item[0] != SID_APPLY_FIR) अणु
		dev_err(component->dev,
			"%s: ERROR: This control supports '%s' only!\n",
			__func__, क्रमागत_sid_state[SID_APPLY_FIR]);
		वापस -EIO;
	पूर्ण

	mutex_lock(&drvdata->ctrl_lock);

	sidconf = snd_soc_component_पढ़ो(component, AB8500_SIDFIRCONF);
	अगर (((sidconf & BIT(AB8500_SIDFIRCONF_FIRSIDBUSY)) != 0)) अणु
		अगर ((sidconf & BIT(AB8500_SIDFIRCONF_ENFIRSIDS)) == 0) अणु
			dev_err(component->dev, "%s: Sidetone busy while off!\n",
				__func__);
			status = -EPERM;
		पूर्ण अन्यथा अणु
			status = -EBUSY;
		पूर्ण
		जाओ out;
	पूर्ण

	snd_soc_component_ग_लिखो(component, AB8500_SIDFIRADR, 0);

	क्रम (param = 0; param < AB8500_SID_FIR_COEFFS; param++) अणु
		val = snd_soc_component_पढ़ो(component, drvdata->sid_fir_values[param]);
		snd_soc_component_ग_लिखो(component, AB8500_SIDFIRCOEF1, val >> 8 & 0xff);
		snd_soc_component_ग_लिखो(component, AB8500_SIDFIRCOEF2, val & 0xff);
	पूर्ण

	snd_soc_component_update_bits(component, AB8500_SIDFIRADR,
		BIT(AB8500_SIDFIRADR_FIRSIDSET),
		BIT(AB8500_SIDFIRADR_FIRSIDSET));
	snd_soc_component_update_bits(component, AB8500_SIDFIRADR,
		BIT(AB8500_SIDFIRADR_FIRSIDSET), 0);

	drvdata->sid_status = SID_FIR_CONFIGURED;

out:
	mutex_unlock(&drvdata->ctrl_lock);

	dev_dbg(component->dev, "%s: Exit\n", __func__);

	वापस status;
पूर्ण

अटल पूर्णांक anc_status_control_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा ab8500_codec_drvdata *drvdata = dev_get_drvdata(component->dev);

	mutex_lock(&drvdata->ctrl_lock);
	ucontrol->value.क्रमागतerated.item[0] = drvdata->anc_status;
	mutex_unlock(&drvdata->ctrl_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक anc_status_control_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा ab8500_codec_drvdata *drvdata = dev_get_drvdata(component->dev);
	काष्ठा device *dev = component->dev;
	bool apply_fir, apply_iir;
	अचिन्हित पूर्णांक req;
	पूर्णांक status;

	dev_dbg(dev, "%s: Enter.\n", __func__);

	mutex_lock(&drvdata->ctrl_lock);

	req = ucontrol->value.क्रमागतerated.item[0];
	अगर (req >= ARRAY_SIZE(क्रमागत_anc_state)) अणु
		status = -EINVAL;
		जाओ cleanup;
	पूर्ण
	अगर (req != ANC_APPLY_FIR_IIR && req != ANC_APPLY_FIR &&
		req != ANC_APPLY_IIR) अणु
		dev_err(dev, "%s: ERROR: Unsupported status to set '%s'!\n",
			__func__, क्रमागत_anc_state[req]);
		status = -EINVAL;
		जाओ cleanup;
	पूर्ण
	apply_fir = req == ANC_APPLY_FIR || req == ANC_APPLY_FIR_IIR;
	apply_iir = req == ANC_APPLY_IIR || req == ANC_APPLY_FIR_IIR;

	status = snd_soc_dapm_क्रमce_enable_pin(dapm, "ANC Configure Input");
	अगर (status < 0) अणु
		dev_err(dev,
			"%s: ERROR: Failed to enable power (status = %d)!\n",
			__func__, status);
		जाओ cleanup;
	पूर्ण
	snd_soc_dapm_sync(dapm);

	anc_configure(component, apply_fir, apply_iir);

	अगर (apply_fir) अणु
		अगर (drvdata->anc_status == ANC_IIR_CONFIGURED)
			drvdata->anc_status = ANC_FIR_IIR_CONFIGURED;
		अन्यथा अगर (drvdata->anc_status != ANC_FIR_IIR_CONFIGURED)
			drvdata->anc_status =  ANC_FIR_CONFIGURED;
	पूर्ण
	अगर (apply_iir) अणु
		अगर (drvdata->anc_status == ANC_FIR_CONFIGURED)
			drvdata->anc_status = ANC_FIR_IIR_CONFIGURED;
		अन्यथा अगर (drvdata->anc_status != ANC_FIR_IIR_CONFIGURED)
			drvdata->anc_status =  ANC_IIR_CONFIGURED;
	पूर्ण

	status = snd_soc_dapm_disable_pin(dapm, "ANC Configure Input");
	snd_soc_dapm_sync(dapm);

cleanup:
	mutex_unlock(&drvdata->ctrl_lock);

	अगर (status < 0)
		dev_err(dev, "%s: Unable to configure ANC! (status = %d)\n",
			__func__, status);

	dev_dbg(dev, "%s: Exit.\n", __func__);

	वापस (status < 0) ? status : 1;
पूर्ण

अटल पूर्णांक filter_control_info(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा filter_control *fc =
			(काष्ठा filter_control *)kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = fc->count;
	uinfo->value.पूर्णांकeger.min = fc->min;
	uinfo->value.पूर्णांकeger.max = fc->max;

	वापस 0;
पूर्ण

अटल पूर्णांक filter_control_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा ab8500_codec_drvdata *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा filter_control *fc =
			(काष्ठा filter_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक i;

	mutex_lock(&drvdata->ctrl_lock);
	क्रम (i = 0; i < fc->count; i++)
		ucontrol->value.पूर्णांकeger.value[i] = fc->value[i];
	mutex_unlock(&drvdata->ctrl_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक filter_control_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा ab8500_codec_drvdata *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा filter_control *fc =
			(काष्ठा filter_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक i;

	mutex_lock(&drvdata->ctrl_lock);
	क्रम (i = 0; i < fc->count; i++)
		fc->value[i] = ucontrol->value.पूर्णांकeger.value[i];
	mutex_unlock(&drvdata->ctrl_lock);

	वापस 0;
पूर्ण

/*
 * Controls - Non-DAPM ASoC
 */

अटल DECLARE_TLV_DB_SCALE(adx_dig_gain_tlv, -3200, 100, 1);
/* -32dB = Mute */

अटल DECLARE_TLV_DB_SCALE(dax_dig_gain_tlv, -6300, 100, 1);
/* -63dB = Mute */

अटल DECLARE_TLV_DB_SCALE(hs_ear_dig_gain_tlv, -100, 100, 1);
/* -1dB = Mute */

अटल स्थिर DECLARE_TLV_DB_RANGE(hs_gain_tlv,
	0, 3, TLV_DB_SCALE_ITEM(-3200, 400, 0),
	4, 15, TLV_DB_SCALE_ITEM(-1800, 200, 0)
);

अटल DECLARE_TLV_DB_SCALE(mic_gain_tlv, 0, 100, 0);

अटल DECLARE_TLV_DB_SCALE(lin_gain_tlv, -1000, 200, 0);

अटल DECLARE_TLV_DB_SCALE(lin2hs_gain_tlv, -3800, 200, 1);
/* -38dB = Mute */

अटल स्थिर अक्षर * स्थिर क्रमागत_hsfadspeed[] = अणु"2ms", "0.5ms", "10.6ms",
					"5ms"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_hsfadspeed,
	AB8500_DIGMICCONF, AB8500_DIGMICCONF_HSFADSPEED, क्रमागत_hsfadspeed);

अटल स्थिर अक्षर * स्थिर क्रमागत_envdetthre[] = अणु
	"250mV", "300mV", "350mV", "400mV",
	"450mV", "500mV", "550mV", "600mV",
	"650mV", "700mV", "750mV", "800mV",
	"850mV", "900mV", "950mV", "1.00V" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_envdeththre,
	AB8500_ENVCPCONF, AB8500_ENVCPCONF_ENVDETHTHRE, क्रमागत_envdetthre);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_envdetlthre,
	AB8500_ENVCPCONF, AB8500_ENVCPCONF_ENVDETLTHRE, क्रमागत_envdetthre);
अटल स्थिर अक्षर * स्थिर क्रमागत_envdetसमय[] = अणु
	"26.6us", "53.2us", "106us",  "213us",
	"426us",  "851us",  "1.70ms", "3.40ms",
	"6.81ms", "13.6ms", "27.2ms", "54.5ms",
	"109ms",  "218ms",  "436ms",  "872ms" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_envdetसमय,
	AB8500_SIGENVCONF, AB8500_SIGENVCONF_ENVDETTIME, क्रमागत_envdetसमय);

अटल स्थिर अक्षर * स्थिर क्रमागत_sinc31[] = अणु"Sinc 3", "Sinc 1"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_hsesinc, AB8500_HSLEARDIGGAIN,
			AB8500_HSLEARDIGGAIN_HSSINC1, क्रमागत_sinc31);

अटल स्थिर अक्षर * स्थिर क्रमागत_fadespeed[] = अणु"1ms", "4ms", "8ms", "16ms"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_fadespeed, AB8500_HSRDIGGAIN,
			AB8500_HSRDIGGAIN_FADESPEED, क्रमागत_fadespeed);

/* Earpiece */

अटल स्थिर अक्षर * स्थिर क्रमागत_lowघात[] = अणु"Normal", "Low Power"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_eardaclowघात, AB8500_ANACONF1,
			AB8500_ANACONF1_EARDACLOWPOW, क्रमागत_lowघात);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_eardrvlowघात, AB8500_ANACONF1,
			AB8500_ANACONF1_EARDRVLOWPOW, क्रमागत_lowघात);

अटल स्थिर अक्षर * स्थिर क्रमागत_av_mode[] = अणु"Audio", "Voice"पूर्ण;
अटल SOC_ENUM_DOUBLE_DECL(soc_क्रमागत_ad12voice, AB8500_ADFILTCONF,
	AB8500_ADFILTCONF_AD1VOICE, AB8500_ADFILTCONF_AD2VOICE, क्रमागत_av_mode);
अटल SOC_ENUM_DOUBLE_DECL(soc_क्रमागत_ad34voice, AB8500_ADFILTCONF,
	AB8500_ADFILTCONF_AD3VOICE, AB8500_ADFILTCONF_AD4VOICE, क्रमागत_av_mode);

/* DA */

अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da12voice,
			AB8500_DASLOTCONF1, AB8500_DASLOTCONF1_DA12VOICE,
			क्रमागत_av_mode);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da34voice,
			AB8500_DASLOTCONF3, AB8500_DASLOTCONF3_DA34VOICE,
			क्रमागत_av_mode);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da56voice,
			AB8500_DASLOTCONF5, AB8500_DASLOTCONF5_DA56VOICE,
			क्रमागत_av_mode);

अटल स्थिर अक्षर * स्थिर क्रमागत_da2hslr[] = अणु"Sidetone", "Audio Path"पूर्ण;
अटल SOC_ENUM_DOUBLE_DECL(soc_क्रमागत_da2hslr, AB8500_DIGMULTCONF1,
			AB8500_DIGMULTCONF1_DATOHSLEN,
			AB8500_DIGMULTCONF1_DATOHSREN, क्रमागत_da2hslr);

अटल स्थिर अक्षर * स्थिर क्रमागत_sinc53[] = अणु"Sinc 5", "Sinc 3"पूर्ण;
अटल SOC_ENUM_DOUBLE_DECL(soc_क्रमागत_dmic12sinc, AB8500_DMICFILTCONF,
			AB8500_DMICFILTCONF_DMIC1SINC3,
			AB8500_DMICFILTCONF_DMIC2SINC3, क्रमागत_sinc53);
अटल SOC_ENUM_DOUBLE_DECL(soc_क्रमागत_dmic34sinc, AB8500_DMICFILTCONF,
			AB8500_DMICFILTCONF_DMIC3SINC3,
			AB8500_DMICFILTCONF_DMIC4SINC3, क्रमागत_sinc53);
अटल SOC_ENUM_DOUBLE_DECL(soc_क्रमागत_dmic56sinc, AB8500_DMICFILTCONF,
			AB8500_DMICFILTCONF_DMIC5SINC3,
			AB8500_DMICFILTCONF_DMIC6SINC3, क्रमागत_sinc53);

/* Digital पूर्णांकerface - DA from slot mapping */
अटल स्थिर अक्षर * स्थिर क्रमागत_da_from_slot_map[] = अणु"SLOT0",
					"SLOT1",
					"SLOT2",
					"SLOT3",
					"SLOT4",
					"SLOT5",
					"SLOT6",
					"SLOT7",
					"SLOT8",
					"SLOT9",
					"SLOT10",
					"SLOT11",
					"SLOT12",
					"SLOT13",
					"SLOT14",
					"SLOT15",
					"SLOT16",
					"SLOT17",
					"SLOT18",
					"SLOT19",
					"SLOT20",
					"SLOT21",
					"SLOT22",
					"SLOT23",
					"SLOT24",
					"SLOT25",
					"SLOT26",
					"SLOT27",
					"SLOT28",
					"SLOT29",
					"SLOT30",
					"SLOT31"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da1sloपंचांगap,
			AB8500_DASLOTCONF1, AB8500_DASLOTCONFX_SLTODAX_SHIFT,
			क्रमागत_da_from_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da2sloपंचांगap,
			AB8500_DASLOTCONF2, AB8500_DASLOTCONFX_SLTODAX_SHIFT,
			क्रमागत_da_from_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da3sloपंचांगap,
			AB8500_DASLOTCONF3, AB8500_DASLOTCONFX_SLTODAX_SHIFT,
			क्रमागत_da_from_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da4sloपंचांगap,
			AB8500_DASLOTCONF4, AB8500_DASLOTCONFX_SLTODAX_SHIFT,
			क्रमागत_da_from_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da5sloपंचांगap,
			AB8500_DASLOTCONF5, AB8500_DASLOTCONFX_SLTODAX_SHIFT,
			क्रमागत_da_from_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da6sloपंचांगap,
			AB8500_DASLOTCONF6, AB8500_DASLOTCONFX_SLTODAX_SHIFT,
			क्रमागत_da_from_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da7sloपंचांगap,
			AB8500_DASLOTCONF7, AB8500_DASLOTCONFX_SLTODAX_SHIFT,
			क्रमागत_da_from_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_da8sloपंचांगap,
			AB8500_DASLOTCONF8, AB8500_DASLOTCONFX_SLTODAX_SHIFT,
			क्रमागत_da_from_slot_map);

/* Digital पूर्णांकerface - AD to slot mapping */
अटल स्थिर अक्षर * स्थिर क्रमागत_ad_to_slot_map[] = अणु"AD_OUT1",
					"AD_OUT2",
					"AD_OUT3",
					"AD_OUT4",
					"AD_OUT5",
					"AD_OUT6",
					"AD_OUT7",
					"AD_OUT8",
					"zeroes",
					"zeroes",
					"zeroes",
					"zeroes",
					"tristate",
					"tristate",
					"tristate",
					"tristate"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot0map,
			AB8500_ADSLOTSEL1, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot1map,
			AB8500_ADSLOTSEL1, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot2map,
			AB8500_ADSLOTSEL2, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot3map,
			AB8500_ADSLOTSEL2, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot4map,
			AB8500_ADSLOTSEL3, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot5map,
			AB8500_ADSLOTSEL3, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot6map,
			AB8500_ADSLOTSEL4, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot7map,
			AB8500_ADSLOTSEL4, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot8map,
			AB8500_ADSLOTSEL5, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot9map,
			AB8500_ADSLOTSEL5, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot10map,
			AB8500_ADSLOTSEL6, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot11map,
			AB8500_ADSLOTSEL6, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot12map,
			AB8500_ADSLOTSEL7, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot13map,
			AB8500_ADSLOTSEL7, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot14map,
			AB8500_ADSLOTSEL8, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot15map,
			AB8500_ADSLOTSEL8, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot16map,
			AB8500_ADSLOTSEL9, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot17map,
			AB8500_ADSLOTSEL9, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot18map,
			AB8500_ADSLOTSEL10, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot19map,
			AB8500_ADSLOTSEL10, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot20map,
			AB8500_ADSLOTSEL11, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot21map,
			AB8500_ADSLOTSEL11, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot22map,
			AB8500_ADSLOTSEL12, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot23map,
			AB8500_ADSLOTSEL12, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot24map,
			AB8500_ADSLOTSEL13, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot25map,
			AB8500_ADSLOTSEL13, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot26map,
			AB8500_ADSLOTSEL14, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot27map,
			AB8500_ADSLOTSEL14, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot28map,
			AB8500_ADSLOTSEL15, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot29map,
			AB8500_ADSLOTSEL15, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot30map,
			AB8500_ADSLOTSEL16, AB8500_ADSLOTSELX_EVEN_SHIFT,
			क्रमागत_ad_to_slot_map);
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_adslot31map,
			AB8500_ADSLOTSEL16, AB8500_ADSLOTSELX_ODD_SHIFT,
			क्रमागत_ad_to_slot_map);

/* Digital पूर्णांकerface - Burst mode */
अटल स्थिर अक्षर * स्थिर क्रमागत_mask[] = अणु"Unmasked", "Masked"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_bfअगरomask,
			AB8500_FIFOCONF1, AB8500_FIFOCONF1_BFIFOMASK,
			क्रमागत_mask);
अटल स्थिर अक्षर * स्थिर क्रमागत_bitclk0[] = अणु"19_2_MHz", "38_4_MHz"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_bfअगरo19m2,
			AB8500_FIFOCONF1, AB8500_FIFOCONF1_BFIFO19M2,
			क्रमागत_bitclk0);
अटल स्थिर अक्षर * स्थिर क्रमागत_slavemaster[] = अणु"Slave", "Master"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(soc_क्रमागत_bfअगरomast,
			AB8500_FIFOCONF3, AB8500_FIFOCONF3_BFIFOMAST_SHIFT,
			क्रमागत_slavemaster);

/* Sidetone */
अटल SOC_ENUM_SINGLE_EXT_DECL(soc_क्रमागत_sidstate, क्रमागत_sid_state);

/* ANC */
अटल SOC_ENUM_SINGLE_EXT_DECL(soc_क्रमागत_ancstate, क्रमागत_anc_state);

अटल काष्ठा snd_kcontrol_new ab8500_ctrls[] = अणु
	/* Charge pump */
	SOC_ENUM("Charge Pump High Threshold For Low Voltage",
		soc_क्रमागत_envdeththre),
	SOC_ENUM("Charge Pump Low Threshold For Low Voltage",
		soc_क्रमागत_envdetlthre),
	SOC_SINGLE("Charge Pump Envelope Detection Switch",
		AB8500_SIGENVCONF, AB8500_SIGENVCONF_ENVDETCPEN,
		1, 0),
	SOC_ENUM("Charge Pump Envelope Detection Decay Time",
		soc_क्रमागत_envdetसमय),

	/* Headset */
	SOC_ENUM("Headset Mode", soc_क्रमागत_da12voice),
	SOC_SINGLE("Headset High Pass Switch",
		AB8500_ANACONF1, AB8500_ANACONF1_HSHPEN,
		1, 0),
	SOC_SINGLE("Headset Low Power Switch",
		AB8500_ANACONF1, AB8500_ANACONF1_HSLOWPOW,
		1, 0),
	SOC_SINGLE("Headset DAC Low Power Switch",
		AB8500_ANACONF1, AB8500_ANACONF1_DACLOWPOW1,
		1, 0),
	SOC_SINGLE("Headset DAC Drv Low Power Switch",
		AB8500_ANACONF1, AB8500_ANACONF1_DACLOWPOW0,
		1, 0),
	SOC_ENUM("Headset Fade Speed", soc_क्रमागत_hsfadspeed),
	SOC_ENUM("Headset Source", soc_क्रमागत_da2hslr),
	SOC_ENUM("Headset Filter", soc_क्रमागत_hsesinc),
	SOC_DOUBLE_R_TLV("Headset Master Volume",
		AB8500_DADIGGAIN1, AB8500_DADIGGAIN2,
		0, AB8500_DADIGGAINX_DAXGAIN_MAX, 1, dax_dig_gain_tlv),
	SOC_DOUBLE_R_TLV("Headset Digital Volume",
		AB8500_HSLEARDIGGAIN, AB8500_HSRDIGGAIN,
		0, AB8500_HSLEARDIGGAIN_HSLDGAIN_MAX, 1, hs_ear_dig_gain_tlv),
	SOC_DOUBLE_TLV("Headset Volume",
		AB8500_ANAGAIN3,
		AB8500_ANAGAIN3_HSLGAIN, AB8500_ANAGAIN3_HSRGAIN,
		AB8500_ANAGAIN3_HSXGAIN_MAX, 1, hs_gain_tlv),

	/* Earpiece */
	SOC_ENUM("Earpiece DAC Mode",
		soc_क्रमागत_eardaclowघात),
	SOC_ENUM("Earpiece DAC Drv Mode",
		soc_क्रमागत_eardrvlowघात),

	/* HandsFree */
	SOC_ENUM("HF Mode", soc_क्रमागत_da34voice),
	SOC_SINGLE("HF and Headset Swap Switch",
		AB8500_DASLOTCONF1, AB8500_DASLOTCONF1_SWAPDA12_34,
		1, 0),
	SOC_DOUBLE("HF Low EMI Mode Switch",
		AB8500_CLASSDCONF1,
		AB8500_CLASSDCONF1_HFLSWAPEN, AB8500_CLASSDCONF1_HFRSWAPEN,
		1, 0),
	SOC_DOUBLE("HF FIR Bypass Switch",
		AB8500_CLASSDCONF2,
		AB8500_CLASSDCONF2_FIRBYP0, AB8500_CLASSDCONF2_FIRBYP1,
		1, 0),
	SOC_DOUBLE("HF High Volume Switch",
		AB8500_CLASSDCONF2,
		AB8500_CLASSDCONF2_HIGHVOLEN0, AB8500_CLASSDCONF2_HIGHVOLEN1,
		1, 0),
	SOC_SINGLE("HF L and R Bridge Switch",
		AB8500_CLASSDCONF1, AB8500_CLASSDCONF1_PARLHF,
		1, 0),
	SOC_DOUBLE_R_TLV("HF Master Volume",
		AB8500_DADIGGAIN3, AB8500_DADIGGAIN4,
		0, AB8500_DADIGGAINX_DAXGAIN_MAX, 1, dax_dig_gain_tlv),

	/* Vibra */
	SOC_DOUBLE("Vibra High Volume Switch",
		AB8500_CLASSDCONF2,
		AB8500_CLASSDCONF2_HIGHVOLEN2, AB8500_CLASSDCONF2_HIGHVOLEN3,
		1, 0),
	SOC_DOUBLE("Vibra Low EMI Mode Switch",
		AB8500_CLASSDCONF1,
		AB8500_CLASSDCONF1_VIB1SWAPEN, AB8500_CLASSDCONF1_VIB2SWAPEN,
		1, 0),
	SOC_DOUBLE("Vibra FIR Bypass Switch",
		AB8500_CLASSDCONF2,
		AB8500_CLASSDCONF2_FIRBYP2, AB8500_CLASSDCONF2_FIRBYP3,
		1, 0),
	SOC_ENUM("Vibra Mode", soc_क्रमागत_da56voice),
	SOC_DOUBLE_R("Vibra PWM Duty Cycle N",
		AB8500_PWMGENCONF3, AB8500_PWMGENCONF5,
		AB8500_PWMGENCONFX_PWMVIBXDUTCYC,
		AB8500_PWMGENCONFX_PWMVIBXDUTCYC_MAX, 0),
	SOC_DOUBLE_R("Vibra PWM Duty Cycle P",
		AB8500_PWMGENCONF2, AB8500_PWMGENCONF4,
		AB8500_PWMGENCONFX_PWMVIBXDUTCYC,
		AB8500_PWMGENCONFX_PWMVIBXDUTCYC_MAX, 0),
	SOC_SINGLE("Vibra 1 and 2 Bridge Switch",
		AB8500_CLASSDCONF1, AB8500_CLASSDCONF1_PARLVIB,
		1, 0),
	SOC_DOUBLE_R_TLV("Vibra Master Volume",
		AB8500_DADIGGAIN5, AB8500_DADIGGAIN6,
		0, AB8500_DADIGGAINX_DAXGAIN_MAX, 1, dax_dig_gain_tlv),

	/* HandsFree, Vibra */
	SOC_SINGLE("ClassD High Pass Volume",
		AB8500_CLASSDCONF3, AB8500_CLASSDCONF3_DITHHPGAIN,
		AB8500_CLASSDCONF3_DITHHPGAIN_MAX, 0),
	SOC_SINGLE("ClassD White Volume",
		AB8500_CLASSDCONF3, AB8500_CLASSDCONF3_DITHWGAIN,
		AB8500_CLASSDCONF3_DITHWGAIN_MAX, 0),

	/* Mic 1, Mic 2, LineIn */
	SOC_DOUBLE_R_TLV("Mic Master Volume",
		AB8500_ADDIGGAIN3, AB8500_ADDIGGAIN4,
		0, AB8500_ADDIGGAINX_ADXGAIN_MAX, 1, adx_dig_gain_tlv),

	/* Mic 1 */
	SOC_SINGLE_TLV("Mic 1",
		AB8500_ANAGAIN1,
		AB8500_ANAGAINX_MICXGAIN,
		AB8500_ANAGAINX_MICXGAIN_MAX, 0, mic_gain_tlv),
	SOC_SINGLE("Mic 1 Low Power Switch",
		AB8500_ANAGAIN1, AB8500_ANAGAINX_LOWPOWMICX,
		1, 0),

	/* Mic 2 */
	SOC_DOUBLE("Mic High Pass Switch",
		AB8500_ADFILTCONF,
		AB8500_ADFILTCONF_AD3NH, AB8500_ADFILTCONF_AD4NH,
		1, 1),
	SOC_ENUM("Mic Mode", soc_क्रमागत_ad34voice),
	SOC_ENUM("Mic Filter", soc_क्रमागत_dmic34sinc),
	SOC_SINGLE_TLV("Mic 2",
		AB8500_ANAGAIN2,
		AB8500_ANAGAINX_MICXGAIN,
		AB8500_ANAGAINX_MICXGAIN_MAX, 0, mic_gain_tlv),
	SOC_SINGLE("Mic 2 Low Power Switch",
		AB8500_ANAGAIN2, AB8500_ANAGAINX_LOWPOWMICX,
		1, 0),

	/* LineIn */
	SOC_DOUBLE("LineIn High Pass Switch",
		AB8500_ADFILTCONF,
		AB8500_ADFILTCONF_AD1NH, AB8500_ADFILTCONF_AD2NH,
		1, 1),
	SOC_ENUM("LineIn Filter", soc_क्रमागत_dmic12sinc),
	SOC_ENUM("LineIn Mode", soc_क्रमागत_ad12voice),
	SOC_DOUBLE_R_TLV("LineIn Master Volume",
		AB8500_ADDIGGAIN1, AB8500_ADDIGGAIN2,
		0, AB8500_ADDIGGAINX_ADXGAIN_MAX, 1, adx_dig_gain_tlv),
	SOC_DOUBLE_TLV("LineIn",
		AB8500_ANAGAIN4,
		AB8500_ANAGAIN4_LINLGAIN, AB8500_ANAGAIN4_LINRGAIN,
		AB8500_ANAGAIN4_LINXGAIN_MAX, 0, lin_gain_tlv),
	SOC_DOUBLE_R_TLV("LineIn to Headset Volume",
		AB8500_DIGLINHSLGAIN, AB8500_DIGLINHSRGAIN,
		AB8500_DIGLINHSXGAIN_LINTOHSXGAIN,
		AB8500_DIGLINHSXGAIN_LINTOHSXGAIN_MAX,
		1, lin2hs_gain_tlv),

	/* DMic */
	SOC_ENUM("DMic Filter", soc_क्रमागत_dmic56sinc),
	SOC_DOUBLE_R_TLV("DMic Master Volume",
		AB8500_ADDIGGAIN5, AB8500_ADDIGGAIN6,
		0, AB8500_ADDIGGAINX_ADXGAIN_MAX, 1, adx_dig_gain_tlv),

	/* Digital gains */
	SOC_ENUM("Digital Gain Fade Speed", soc_क्रमागत_fadespeed),

	/* Analog loopback */
	SOC_DOUBLE_R_TLV("Analog Loopback Volume",
		AB8500_ADDIGLOOPGAIN1, AB8500_ADDIGLOOPGAIN2,
		0, AB8500_ADDIGLOOPGAINX_ADXLBGAIN_MAX, 1, dax_dig_gain_tlv),

	/* Digital पूर्णांकerface - DA from slot mapping */
	SOC_ENUM("Digital Interface DA 1 From Slot Map", soc_क्रमागत_da1sloपंचांगap),
	SOC_ENUM("Digital Interface DA 2 From Slot Map", soc_क्रमागत_da2sloपंचांगap),
	SOC_ENUM("Digital Interface DA 3 From Slot Map", soc_क्रमागत_da3sloपंचांगap),
	SOC_ENUM("Digital Interface DA 4 From Slot Map", soc_क्रमागत_da4sloपंचांगap),
	SOC_ENUM("Digital Interface DA 5 From Slot Map", soc_क्रमागत_da5sloपंचांगap),
	SOC_ENUM("Digital Interface DA 6 From Slot Map", soc_क्रमागत_da6sloपंचांगap),
	SOC_ENUM("Digital Interface DA 7 From Slot Map", soc_क्रमागत_da7sloपंचांगap),
	SOC_ENUM("Digital Interface DA 8 From Slot Map", soc_क्रमागत_da8sloपंचांगap),

	/* Digital पूर्णांकerface - AD to slot mapping */
	SOC_ENUM("Digital Interface AD To Slot 0 Map", soc_क्रमागत_adslot0map),
	SOC_ENUM("Digital Interface AD To Slot 1 Map", soc_क्रमागत_adslot1map),
	SOC_ENUM("Digital Interface AD To Slot 2 Map", soc_क्रमागत_adslot2map),
	SOC_ENUM("Digital Interface AD To Slot 3 Map", soc_क्रमागत_adslot3map),
	SOC_ENUM("Digital Interface AD To Slot 4 Map", soc_क्रमागत_adslot4map),
	SOC_ENUM("Digital Interface AD To Slot 5 Map", soc_क्रमागत_adslot5map),
	SOC_ENUM("Digital Interface AD To Slot 6 Map", soc_क्रमागत_adslot6map),
	SOC_ENUM("Digital Interface AD To Slot 7 Map", soc_क्रमागत_adslot7map),
	SOC_ENUM("Digital Interface AD To Slot 8 Map", soc_क्रमागत_adslot8map),
	SOC_ENUM("Digital Interface AD To Slot 9 Map", soc_क्रमागत_adslot9map),
	SOC_ENUM("Digital Interface AD To Slot 10 Map", soc_क्रमागत_adslot10map),
	SOC_ENUM("Digital Interface AD To Slot 11 Map", soc_क्रमागत_adslot11map),
	SOC_ENUM("Digital Interface AD To Slot 12 Map", soc_क्रमागत_adslot12map),
	SOC_ENUM("Digital Interface AD To Slot 13 Map", soc_क्रमागत_adslot13map),
	SOC_ENUM("Digital Interface AD To Slot 14 Map", soc_क्रमागत_adslot14map),
	SOC_ENUM("Digital Interface AD To Slot 15 Map", soc_क्रमागत_adslot15map),
	SOC_ENUM("Digital Interface AD To Slot 16 Map", soc_क्रमागत_adslot16map),
	SOC_ENUM("Digital Interface AD To Slot 17 Map", soc_क्रमागत_adslot17map),
	SOC_ENUM("Digital Interface AD To Slot 18 Map", soc_क्रमागत_adslot18map),
	SOC_ENUM("Digital Interface AD To Slot 19 Map", soc_क्रमागत_adslot19map),
	SOC_ENUM("Digital Interface AD To Slot 20 Map", soc_क्रमागत_adslot20map),
	SOC_ENUM("Digital Interface AD To Slot 21 Map", soc_क्रमागत_adslot21map),
	SOC_ENUM("Digital Interface AD To Slot 22 Map", soc_क्रमागत_adslot22map),
	SOC_ENUM("Digital Interface AD To Slot 23 Map", soc_क्रमागत_adslot23map),
	SOC_ENUM("Digital Interface AD To Slot 24 Map", soc_क्रमागत_adslot24map),
	SOC_ENUM("Digital Interface AD To Slot 25 Map", soc_क्रमागत_adslot25map),
	SOC_ENUM("Digital Interface AD To Slot 26 Map", soc_क्रमागत_adslot26map),
	SOC_ENUM("Digital Interface AD To Slot 27 Map", soc_क्रमागत_adslot27map),
	SOC_ENUM("Digital Interface AD To Slot 28 Map", soc_क्रमागत_adslot28map),
	SOC_ENUM("Digital Interface AD To Slot 29 Map", soc_क्रमागत_adslot29map),
	SOC_ENUM("Digital Interface AD To Slot 30 Map", soc_क्रमागत_adslot30map),
	SOC_ENUM("Digital Interface AD To Slot 31 Map", soc_क्रमागत_adslot31map),

	/* Digital पूर्णांकerface - Loopback */
	SOC_SINGLE("Digital Interface AD 1 Loopback Switch",
		AB8500_DASLOTCONF1, AB8500_DASLOTCONF1_DAI7TOADO1,
		1, 0),
	SOC_SINGLE("Digital Interface AD 2 Loopback Switch",
		AB8500_DASLOTCONF2, AB8500_DASLOTCONF2_DAI8TOADO2,
		1, 0),
	SOC_SINGLE("Digital Interface AD 3 Loopback Switch",
		AB8500_DASLOTCONF3, AB8500_DASLOTCONF3_DAI7TOADO3,
		1, 0),
	SOC_SINGLE("Digital Interface AD 4 Loopback Switch",
		AB8500_DASLOTCONF4, AB8500_DASLOTCONF4_DAI8TOADO4,
		1, 0),
	SOC_SINGLE("Digital Interface AD 5 Loopback Switch",
		AB8500_DASLOTCONF5, AB8500_DASLOTCONF5_DAI7TOADO5,
		1, 0),
	SOC_SINGLE("Digital Interface AD 6 Loopback Switch",
		AB8500_DASLOTCONF6, AB8500_DASLOTCONF6_DAI8TOADO6,
		1, 0),
	SOC_SINGLE("Digital Interface AD 7 Loopback Switch",
		AB8500_DASLOTCONF7, AB8500_DASLOTCONF7_DAI8TOADO7,
		1, 0),
	SOC_SINGLE("Digital Interface AD 8 Loopback Switch",
		AB8500_DASLOTCONF8, AB8500_DASLOTCONF8_DAI7TOADO8,
		1, 0),

	/* Digital पूर्णांकerface - Burst FIFO */
	SOC_SINGLE("Digital Interface 0 FIFO Enable Switch",
		AB8500_DIGIFCONF3, AB8500_DIGIFCONF3_IF0BFIFOEN,
		1, 0),
	SOC_ENUM("Burst FIFO Mask", soc_क्रमागत_bfअगरomask),
	SOC_ENUM("Burst FIFO Bit-clock Frequency", soc_क्रमागत_bfअगरo19m2),
	SOC_SINGLE("Burst FIFO Threshold",
		AB8500_FIFOCONF1, AB8500_FIFOCONF1_BFIFOINT_SHIFT,
		AB8500_FIFOCONF1_BFIFOपूर्णांक_उच्च, 0),
	SOC_SINGLE("Burst FIFO Length",
		AB8500_FIFOCONF2, AB8500_FIFOCONF2_BFIFOTX_SHIFT,
		AB8500_FIFOCONF2_BFIFOTX_MAX, 0),
	SOC_SINGLE("Burst FIFO EOS Extra Slots",
		AB8500_FIFOCONF3, AB8500_FIFOCONF3_BFIFOEXSL_SHIFT,
		AB8500_FIFOCONF3_BFIFOEXSL_MAX, 0),
	SOC_SINGLE("Burst FIFO FS Extra Bit-clocks",
		AB8500_FIFOCONF3, AB8500_FIFOCONF3_PREBITCLK0_SHIFT,
		AB8500_FIFOCONF3_PREBITCLK0_MAX, 0),
	SOC_ENUM("Burst FIFO Interface Mode", soc_क्रमागत_bfअगरomast),

	SOC_SINGLE("Burst FIFO Interface Switch",
		AB8500_FIFOCONF3, AB8500_FIFOCONF3_BFIFORUN_SHIFT,
		1, 0),
	SOC_SINGLE("Burst FIFO Switch Frame Number",
		AB8500_FIFOCONF4, AB8500_FIFOCONF4_BFIFOFRAMSW_SHIFT,
		AB8500_FIFOCONF4_BFIFOFRAMSW_MAX, 0),
	SOC_SINGLE("Burst FIFO Wake Up Delay",
		AB8500_FIFOCONF5, AB8500_FIFOCONF5_BFIFOWAKEUP_SHIFT,
		AB8500_FIFOCONF5_BFIFOWAKEUP_MAX, 0),
	SOC_SINGLE("Burst FIFO Samples In FIFO",
		AB8500_FIFOCONF6, AB8500_FIFOCONF6_BFIFOSAMPLE_SHIFT,
		AB8500_FIFOCONF6_BFIFOSAMPLE_MAX, 0),

	/* ANC */
	SOC_ENUM_EXT("ANC Status", soc_क्रमागत_ancstate,
		anc_status_control_get, anc_status_control_put),
	SOC_SINGLE_XR_SX("ANC Warp Delay Shift",
		AB8500_ANCCONF2, 1, AB8500_ANCCONF2_SHIFT,
		AB8500_ANCCONF2_MIN, AB8500_ANCCONF2_MAX, 0),
	SOC_SINGLE_XR_SX("ANC FIR Output Shift",
		AB8500_ANCCONF3, 1, AB8500_ANCCONF3_SHIFT,
		AB8500_ANCCONF3_MIN, AB8500_ANCCONF3_MAX, 0),
	SOC_SINGLE_XR_SX("ANC IIR Output Shift",
		AB8500_ANCCONF4, 1, AB8500_ANCCONF4_SHIFT,
		AB8500_ANCCONF4_MIN, AB8500_ANCCONF4_MAX, 0),
	SOC_SINGLE_XR_SX("ANC Warp Delay",
		AB8500_ANCCONF9, 2, AB8500_ANC_WARP_DELAY_SHIFT,
		AB8500_ANC_WARP_DELAY_MIN, AB8500_ANC_WARP_DELAY_MAX, 0),

	/* Sidetone */
	SOC_ENUM_EXT("Sidetone Status", soc_क्रमागत_sidstate,
		sid_status_control_get, sid_status_control_put),
	SOC_SINGLE_STROBE("Sidetone Reset",
		AB8500_SIDFIRADR, AB8500_SIDFIRADR_FIRSIDSET, 0),
पूर्ण;

अटल काष्ठा snd_kcontrol_new ab8500_filter_controls[] = अणु
	AB8500_FILTER_CONTROL("ANC FIR Coefficients", AB8500_ANC_FIR_COEFFS,
		AB8500_ANC_FIR_COEFF_MIN, AB8500_ANC_FIR_COEFF_MAX),
	AB8500_FILTER_CONTROL("ANC IIR Coefficients", AB8500_ANC_IIR_COEFFS,
		AB8500_ANC_IIR_COEFF_MIN, AB8500_ANC_IIR_COEFF_MAX),
	AB8500_FILTER_CONTROL("Sidetone FIR Coefficients",
			AB8500_SID_FIR_COEFFS, AB8500_SID_FIR_COEFF_MIN,
			AB8500_SID_FIR_COEFF_MAX)
पूर्ण;
क्रमागत ab8500_filter अणु
	AB8500_FILTER_ANC_FIR = 0,
	AB8500_FILTER_ANC_IIR = 1,
	AB8500_FILTER_SID_FIR = 2,
पूर्ण;

/*
 * Extended पूर्णांकerface क्रम codec-driver
 */

अटल पूर्णांक ab8500_audio_init_audioblock(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक status;

	dev_dbg(component->dev, "%s: Enter.\n", __func__);

	/* Reset audio-रेजिस्टरs and disable 32kHz-घड़ी output 2 */
	status = ab8500_sysctrl_ग_लिखो(AB8500_STW4500CTRL3,
				AB8500_STW4500CTRL3_CLK32KOUT2DIS |
					AB8500_STW4500CTRL3_RESETAUDN,
				AB8500_STW4500CTRL3_RESETAUDN);
	अगर (status < 0)
		वापस status;

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_audio_setup_mics(काष्ठा snd_soc_component *component,
			काष्ठा amic_settings *amics)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	u8 value8;
	अचिन्हित पूर्णांक value;
	पूर्णांक status;
	स्थिर काष्ठा snd_soc_dapm_route *route;

	dev_dbg(component->dev, "%s: Enter.\n", __func__);

	/* Set DMic-घड़ीs to outमाला_दो */
	status = abx500_get_रेजिस्टर_पूर्णांकerruptible(component->dev, AB8500_MISC,
						AB8500_GPIO_सूची4_REG,
						&value8);
	अगर (status < 0)
		वापस status;
	value = value8 | GPIO27_सूची_OUTPUT | GPIO29_सूची_OUTPUT |
		GPIO31_सूची_OUTPUT;
	status = abx500_set_रेजिस्टर_पूर्णांकerruptible(component->dev,
						AB8500_MISC,
						AB8500_GPIO_सूची4_REG,
						value);
	अगर (status < 0)
		वापस status;

	/* Attach regulators to AMic DAPM-paths */
	dev_dbg(component->dev, "%s: Mic 1a regulator: %s\n", __func__,
		amic_micbias_str(amics->mic1a_micbias));
	route = &ab8500_dapm_routes_mic1a_vamicx[amics->mic1a_micbias];
	status = snd_soc_dapm_add_routes(dapm, route, 1);
	dev_dbg(component->dev, "%s: Mic 1b regulator: %s\n", __func__,
		amic_micbias_str(amics->mic1b_micbias));
	route = &ab8500_dapm_routes_mic1b_vamicx[amics->mic1b_micbias];
	status |= snd_soc_dapm_add_routes(dapm, route, 1);
	dev_dbg(component->dev, "%s: Mic 2 regulator: %s\n", __func__,
		amic_micbias_str(amics->mic2_micbias));
	route = &ab8500_dapm_routes_mic2_vamicx[amics->mic2_micbias];
	status |= snd_soc_dapm_add_routes(dapm, route, 1);
	अगर (status < 0) अणु
		dev_err(component->dev,
			"%s: Failed to add AMic-regulator DAPM-routes (%d).\n",
			__func__, status);
		वापस status;
	पूर्ण

	/* Set AMic-configuration */
	dev_dbg(component->dev, "%s: Mic 1 mic-type: %s\n", __func__,
		amic_type_str(amics->mic1_type));
	snd_soc_component_update_bits(component, AB8500_ANAGAIN1, AB8500_ANAGAINX_ENSEMICX,
			amics->mic1_type == AMIC_TYPE_DIFFERENTIAL ?
				0 : AB8500_ANAGAINX_ENSEMICX);
	dev_dbg(component->dev, "%s: Mic 2 mic-type: %s\n", __func__,
		amic_type_str(amics->mic2_type));
	snd_soc_component_update_bits(component, AB8500_ANAGAIN2, AB8500_ANAGAINX_ENSEMICX,
			amics->mic2_type == AMIC_TYPE_DIFFERENTIAL ?
				0 : AB8500_ANAGAINX_ENSEMICX);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_audio_set_ear_cmv(काष्ठा snd_soc_component *component,
				क्रमागत ear_cm_voltage ear_cmv)
अणु
	अक्षर *cmv_str;

	चयन (ear_cmv) अणु
	हाल EAR_CMV_0_95V:
		cmv_str = "0.95V";
		अवरोध;
	हाल EAR_CMV_1_10V:
		cmv_str = "1.10V";
		अवरोध;
	हाल EAR_CMV_1_27V:
		cmv_str = "1.27V";
		अवरोध;
	हाल EAR_CMV_1_58V:
		cmv_str = "1.58V";
		अवरोध;
	शेष:
		dev_err(component->dev,
			"%s: Unknown earpiece CM-voltage (%d)!\n",
			__func__, (पूर्णांक)ear_cmv);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(component->dev, "%s: Earpiece CM-voltage: %s\n", __func__,
		cmv_str);
	snd_soc_component_update_bits(component, AB8500_ANACONF1, AB8500_ANACONF1_EARSELCM,
			ear_cmv);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_audio_set_bit_delay(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक delay)
अणु
	अचिन्हित पूर्णांक mask, val;
	काष्ठा snd_soc_component *component = dai->component;

	mask = BIT(AB8500_DIGIFCONF2_IF0DEL);
	val = 0;

	चयन (delay) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		val |= BIT(AB8500_DIGIFCONF2_IF0DEL);
		अवरोध;
	शेष:
		dev_err(dai->component->dev,
			"%s: ERROR: Unsupported bit-delay (0x%x)!\n",
			__func__, delay);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->component->dev, "%s: IF0 Bit-delay: %d bits.\n",
		__func__, delay);
	snd_soc_component_update_bits(component, AB8500_DIGIFCONF2, mask, val);

	वापस 0;
पूर्ण

/* Gates घड़ीing according क्रमmat mask */
अटल पूर्णांक ab8500_codec_set_dai_घड़ी_gate(काष्ठा snd_soc_component *component,
					अचिन्हित पूर्णांक fmt)
अणु
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;

	mask = BIT(AB8500_DIGIFCONF1_ENMASTGEN) |
			BIT(AB8500_DIGIFCONF1_ENFSBITCLK0);

	val = BIT(AB8500_DIGIFCONF1_ENMASTGEN);

	चयन (fmt & SND_SOC_DAIFMT_CLOCK_MASK) अणु
	हाल SND_SOC_DAIFMT_CONT: /* continuous घड़ी */
		dev_dbg(component->dev, "%s: IF0 Clock is continuous.\n",
			__func__);
		val |= BIT(AB8500_DIGIFCONF1_ENFSBITCLK0);
		अवरोध;
	हाल SND_SOC_DAIFMT_GATED: /* घड़ी is gated */
		dev_dbg(component->dev, "%s: IF0 Clock is gated.\n",
			__func__);
		अवरोध;
	शेष:
		dev_err(component->dev,
			"%s: ERROR: Unsupported clock mask (0x%x)!\n",
			__func__, fmt & SND_SOC_DAIFMT_CLOCK_MASK);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AB8500_DIGIFCONF1, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_codec_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक status;

	dev_dbg(component->dev, "%s: Enter (fmt = 0x%x)\n", __func__, fmt);

	mask = BIT(AB8500_DIGIFCONF3_IF1DATOIF0AD) |
			BIT(AB8500_DIGIFCONF3_IF1CLKTOIF0CLK) |
			BIT(AB8500_DIGIFCONF3_IF0BFIFOEN) |
			BIT(AB8500_DIGIFCONF3_IF0MASTER);
	val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM: /* codec clk & FRM master */
		dev_dbg(dai->component->dev,
			"%s: IF0 Master-mode: AB8500 master.\n", __func__);
		val |= BIT(AB8500_DIGIFCONF3_IF0MASTER);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS: /* codec clk & FRM slave */
		dev_dbg(dai->component->dev,
			"%s: IF0 Master-mode: AB8500 slave.\n", __func__);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM: /* codec clk slave & FRM master */
	हाल SND_SOC_DAIFMT_CBM_CFS: /* codec clk master & frame slave */
		dev_err(dai->component->dev,
			"%s: ERROR: The device is either a master or a slave.\n",
			__func__);
		fallthrough;
	शेष:
		dev_err(dai->component->dev,
			"%s: ERROR: Unsupporter master mask 0x%x\n",
			__func__, fmt & SND_SOC_DAIFMT_MASTER_MASK);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AB8500_DIGIFCONF3, mask, val);

	/* Set घड़ी gating */
	status = ab8500_codec_set_dai_घड़ी_gate(component, fmt);
	अगर (status) अणु
		dev_err(dai->component->dev,
			"%s: ERROR: Failed to set clock gate (%d).\n",
			__func__, status);
		वापस status;
	पूर्ण

	/* Setting data transfer क्रमmat */

	mask = BIT(AB8500_DIGIFCONF2_IF0FORMAT0) |
		BIT(AB8500_DIGIFCONF2_IF0FORMAT1) |
		BIT(AB8500_DIGIFCONF2_FSYNC0P) |
		BIT(AB8500_DIGIFCONF2_BITCLK0P);
	val = 0;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S: /* I2S mode */
		dev_dbg(dai->component->dev, "%s: IF0 Protocol: I2S\n", __func__);
		val |= BIT(AB8500_DIGIFCONF2_IF0FORMAT1);
		ab8500_audio_set_bit_delay(dai, 0);
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A: /* L data MSB after FRM LRC */
		dev_dbg(dai->component->dev,
			"%s: IF0 Protocol: DSP A (TDM)\n", __func__);
		val |= BIT(AB8500_DIGIFCONF2_IF0FORMAT0);
		ab8500_audio_set_bit_delay(dai, 1);
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_B: /* L data MSB during FRM LRC */
		dev_dbg(dai->component->dev,
			"%s: IF0 Protocol: DSP B (TDM)\n", __func__);
		val |= BIT(AB8500_DIGIFCONF2_IF0FORMAT0);
		ab8500_audio_set_bit_delay(dai, 0);
		अवरोध;

	शेष:
		dev_err(dai->component->dev,
			"%s: ERROR: Unsupported format (0x%x)!\n",
			__func__, fmt & SND_SOC_DAIFMT_FORMAT_MASK);
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF: /* normal bit घड़ी + frame */
		dev_dbg(dai->component->dev,
			"%s: IF0: Normal bit clock, normal frame\n",
			__func__);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF: /* normal BCLK + inv FRM */
		dev_dbg(dai->component->dev,
			"%s: IF0: Normal bit clock, inverted frame\n",
			__func__);
		val |= BIT(AB8500_DIGIFCONF2_FSYNC0P);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF: /* invert BCLK + nor FRM */
		dev_dbg(dai->component->dev,
			"%s: IF0: Inverted bit clock, normal frame\n",
			__func__);
		val |= BIT(AB8500_DIGIFCONF2_BITCLK0P);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF: /* invert BCLK + FRM */
		dev_dbg(dai->component->dev,
			"%s: IF0: Inverted bit clock, inverted frame\n",
			__func__);
		val |= BIT(AB8500_DIGIFCONF2_FSYNC0P);
		val |= BIT(AB8500_DIGIFCONF2_BITCLK0P);
		अवरोध;
	शेष:
		dev_err(dai->component->dev,
			"%s: ERROR: Unsupported INV mask 0x%x\n",
			__func__, fmt & SND_SOC_DAIFMT_INV_MASK);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AB8500_DIGIFCONF2, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_codec_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
		पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val, mask, slot, slots_active;

	mask = BIT(AB8500_DIGIFCONF2_IF0WL0) |
		BIT(AB8500_DIGIFCONF2_IF0WL1);
	val = 0;

	चयन (slot_width) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		val |= BIT(AB8500_DIGIFCONF2_IF0WL0);
		अवरोध;
	हाल 24:
		val |= BIT(AB8500_DIGIFCONF2_IF0WL1);
		अवरोध;
	हाल 32:
		val |= BIT(AB8500_DIGIFCONF2_IF0WL1) |
			BIT(AB8500_DIGIFCONF2_IF0WL0);
		अवरोध;
	शेष:
		dev_err(dai->component->dev, "%s: Unsupported slot-width 0x%x\n",
			__func__, slot_width);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dai->component->dev, "%s: IF0 slot-width: %d bits.\n",
		__func__, slot_width);
	snd_soc_component_update_bits(component, AB8500_DIGIFCONF2, mask, val);

	/* Setup TDM घड़ीing according to slot count */
	dev_dbg(dai->component->dev, "%s: Slots, total: %d\n", __func__, slots);
	mask = BIT(AB8500_DIGIFCONF1_IF0BITCLKOS0) |
			BIT(AB8500_DIGIFCONF1_IF0BITCLKOS1);
	चयन (slots) अणु
	हाल 2:
		val = AB8500_MASK_NONE;
		अवरोध;
	हाल 4:
		val = BIT(AB8500_DIGIFCONF1_IF0BITCLKOS0);
		अवरोध;
	हाल 8:
		val = BIT(AB8500_DIGIFCONF1_IF0BITCLKOS1);
		अवरोध;
	हाल 16:
		val = BIT(AB8500_DIGIFCONF1_IF0BITCLKOS0) |
			BIT(AB8500_DIGIFCONF1_IF0BITCLKOS1);
		अवरोध;
	शेष:
		dev_err(dai->component->dev,
			"%s: ERROR: Unsupported number of slots (%d)!\n",
			__func__, slots);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, AB8500_DIGIFCONF1, mask, val);

	/* Setup TDM DA according to active tx slots */

	अगर (tx_mask & ~0xff)
		वापस -EINVAL;

	mask = AB8500_DASLOTCONFX_SLTODAX_MASK;
	tx_mask = tx_mask << AB8500_DA_DATA0_OFFSET;
	slots_active = hweight32(tx_mask);

	dev_dbg(dai->component->dev, "%s: Slots, active, TX: %d\n", __func__,
		slots_active);

	चयन (slots_active) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		slot = ffs(tx_mask);
		snd_soc_component_update_bits(component, AB8500_DASLOTCONF1, mask, slot);
		snd_soc_component_update_bits(component, AB8500_DASLOTCONF3, mask, slot);
		snd_soc_component_update_bits(component, AB8500_DASLOTCONF2, mask, slot);
		snd_soc_component_update_bits(component, AB8500_DASLOTCONF4, mask, slot);
		अवरोध;
	हाल 2:
		slot = ffs(tx_mask);
		snd_soc_component_update_bits(component, AB8500_DASLOTCONF1, mask, slot);
		snd_soc_component_update_bits(component, AB8500_DASLOTCONF3, mask, slot);
		slot = fls(tx_mask);
		snd_soc_component_update_bits(component, AB8500_DASLOTCONF2, mask, slot);
		snd_soc_component_update_bits(component, AB8500_DASLOTCONF4, mask, slot);
		अवरोध;
	हाल 8:
		dev_dbg(dai->component->dev,
			"%s: In 8-channel mode DA-from-slot mapping is set manually.",
			__func__);
		अवरोध;
	शेष:
		dev_err(dai->component->dev,
			"%s: Unsupported number of active TX-slots (%d)!\n",
			__func__, slots_active);
		वापस -EINVAL;
	पूर्ण

	/* Setup TDM AD according to active RX-slots */

	अगर (rx_mask & ~0xff)
		वापस -EINVAL;

	rx_mask = rx_mask << AB8500_AD_DATA0_OFFSET;
	slots_active = hweight32(rx_mask);

	dev_dbg(dai->component->dev, "%s: Slots, active, RX: %d\n", __func__,
		slots_active);

	चयन (slots_active) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		slot = ffs(rx_mask);
		snd_soc_component_update_bits(component, AB8500_ADSLOTSEL(slot),
				AB8500_MASK_SLOT(slot),
				AB8500_ADSLOTSELX_AD_OUT_TO_SLOT(AB8500_AD_OUT3, slot));
		अवरोध;
	हाल 2:
		slot = ffs(rx_mask);
		snd_soc_component_update_bits(component,
				AB8500_ADSLOTSEL(slot),
				AB8500_MASK_SLOT(slot),
				AB8500_ADSLOTSELX_AD_OUT_TO_SLOT(AB8500_AD_OUT3, slot));
		slot = fls(rx_mask);
		snd_soc_component_update_bits(component,
				AB8500_ADSLOTSEL(slot),
				AB8500_MASK_SLOT(slot),
				AB8500_ADSLOTSELX_AD_OUT_TO_SLOT(AB8500_AD_OUT2, slot));
		अवरोध;
	हाल 8:
		dev_dbg(dai->component->dev,
			"%s: In 8-channel mode AD-to-slot mapping is set manually.",
			__func__);
		अवरोध;
	शेष:
		dev_err(dai->component->dev,
			"%s: Unsupported number of active RX-slots (%d)!\n",
			__func__, slots_active);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ab8500_codec_ops = अणु
	.set_fmt = ab8500_codec_set_dai_fmt,
	.set_tdm_slot = ab8500_codec_set_dai_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ab8500_codec_dai[] = अणु
	अणु
		.name = "ab8500-codec-dai.0",
		.id = 0,
		.playback = अणु
			.stream_name = "ab8500_0p",
			.channels_min = 1,
			.channels_max = 8,
			.rates = AB8500_SUPPORTED_RATE,
			.क्रमmats = AB8500_SUPPORTED_FMT,
		पूर्ण,
		.ops = &ab8500_codec_ops,
		.symmetric_rate = 1
	पूर्ण,
	अणु
		.name = "ab8500-codec-dai.1",
		.id = 1,
		.capture = अणु
			.stream_name = "ab8500_0c",
			.channels_min = 1,
			.channels_max = 8,
			.rates = AB8500_SUPPORTED_RATE,
			.क्रमmats = AB8500_SUPPORTED_FMT,
		पूर्ण,
		.ops = &ab8500_codec_ops,
		.symmetric_rate = 1
	पूर्ण
पूर्ण;

अटल व्योम ab8500_codec_of_probe(काष्ठा device *dev, काष्ठा device_node *np,
				काष्ठा ab8500_codec_platक्रमm_data *codec)
अणु
	u32 value;

	अगर (of_property_पढ़ो_bool(np, "stericsson,amic1-type-single-ended"))
		codec->amics.mic1_type = AMIC_TYPE_SINGLE_ENDED;
	अन्यथा
		codec->amics.mic1_type = AMIC_TYPE_DIFFERENTIAL;

	अगर (of_property_पढ़ो_bool(np, "stericsson,amic2-type-single-ended"))
		codec->amics.mic2_type = AMIC_TYPE_SINGLE_ENDED;
	अन्यथा
		codec->amics.mic2_type = AMIC_TYPE_DIFFERENTIAL;

	/* Has a non-standard Vamic been requested? */
	अगर (of_property_पढ़ो_bool(np, "stericsson,amic1a-bias-vamic2"))
		codec->amics.mic1a_micbias = AMIC_MICBIAS_VAMIC2;
	अन्यथा
		codec->amics.mic1a_micbias = AMIC_MICBIAS_VAMIC1;

	अगर (of_property_पढ़ो_bool(np, "stericsson,amic1b-bias-vamic2"))
		codec->amics.mic1b_micbias = AMIC_MICBIAS_VAMIC2;
	अन्यथा
		codec->amics.mic1b_micbias = AMIC_MICBIAS_VAMIC1;

	अगर (of_property_पढ़ो_bool(np, "stericsson,amic2-bias-vamic1"))
		codec->amics.mic2_micbias = AMIC_MICBIAS_VAMIC1;
	अन्यथा
		codec->amics.mic2_micbias = AMIC_MICBIAS_VAMIC2;

	अगर (!of_property_पढ़ो_u32(np, "stericsson,earpeice-cmv", &value)) अणु
		चयन (value) अणु
		हाल 950 :
			codec->ear_cmv = EAR_CMV_0_95V;
			अवरोध;
		हाल 1100 :
			codec->ear_cmv = EAR_CMV_1_10V;
			अवरोध;
		हाल 1270 :
			codec->ear_cmv = EAR_CMV_1_27V;
			अवरोध;
		हाल 1580 :
			codec->ear_cmv = EAR_CMV_1_58V;
			अवरोध;
		शेष :
			codec->ear_cmv = EAR_CMV_UNKNOWN;
			dev_err(dev, "Unsuitable earpiece voltage found in DT\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(dev, "No earpiece voltage found in DT - using default\n");
		codec->ear_cmv = EAR_CMV_0_95V;
	पूर्ण
पूर्ण

अटल पूर्णांक ab8500_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा device *dev = component->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा ab8500_codec_drvdata *drvdata = dev_get_drvdata(dev);
	काष्ठा ab8500_codec_platक्रमm_data codec_pdata;
	काष्ठा filter_control *fc;
	पूर्णांक status;

	dev_dbg(dev, "%s: Enter.\n", __func__);

	ab8500_codec_of_probe(dev, np, &codec_pdata);

	status = ab8500_audio_setup_mics(component, &codec_pdata.amics);
	अगर (status < 0) अणु
		pr_err("%s: Failed to setup mics (%d)!\n", __func__, status);
		वापस status;
	पूर्ण
	status = ab8500_audio_set_ear_cmv(component, codec_pdata.ear_cmv);
	अगर (status < 0) अणु
		pr_err("%s: Failed to set earpiece CM-voltage (%d)!\n",
			__func__, status);
		वापस status;
	पूर्ण

	status = ab8500_audio_init_audioblock(component);
	अगर (status < 0) अणु
		dev_err(dev, "%s: failed to init audio-block (%d)!\n",
			__func__, status);
		वापस status;
	पूर्ण

	/* Override HW-शेषs */
	snd_soc_component_ग_लिखो(component, AB8500_ANACONF5,
		      BIT(AB8500_ANACONF5_HSAUTOEN));
	snd_soc_component_ग_लिखो(component, AB8500_SHORTCIRCONF,
		      BIT(AB8500_SHORTCIRCONF_HSZCDDIS));

	/* Add filter controls */
	status = snd_soc_add_component_controls(component, ab8500_filter_controls,
				ARRAY_SIZE(ab8500_filter_controls));
	अगर (status < 0) अणु
		dev_err(dev,
			"%s: failed to add ab8500 filter controls (%d).\n",
			__func__, status);
		वापस status;
	पूर्ण
	fc = (काष्ठा filter_control *)
		&ab8500_filter_controls[AB8500_FILTER_ANC_FIR].निजी_value;
	drvdata->anc_fir_values = (दीर्घ *)fc->value;
	fc = (काष्ठा filter_control *)
		&ab8500_filter_controls[AB8500_FILTER_ANC_IIR].निजी_value;
	drvdata->anc_iir_values = (दीर्घ *)fc->value;
	fc = (काष्ठा filter_control *)
		&ab8500_filter_controls[AB8500_FILTER_SID_FIR].निजी_value;
	drvdata->sid_fir_values = (दीर्घ *)fc->value;

	snd_soc_dapm_disable_pin(dapm, "ANC Configure Input");

	mutex_init(&drvdata->ctrl_lock);

	वापस status;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver ab8500_component_driver = अणु
	.probe			= ab8500_codec_probe,
	.controls		= ab8500_ctrls,
	.num_controls		= ARRAY_SIZE(ab8500_ctrls),
	.dapm_widमाला_लो		= ab8500_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ab8500_dapm_widमाला_लो),
	.dapm_routes		= ab8500_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(ab8500_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक ab8500_codec_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक status;
	काष्ठा ab8500_codec_drvdata *drvdata;

	dev_dbg(&pdev->dev, "%s: Enter.\n", __func__);

	/* Create driver निजी-data काष्ठा */
	drvdata = devm_kzalloc(&pdev->dev, माप(काष्ठा ab8500_codec_drvdata),
			GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;
	drvdata->sid_status = SID_UNCONFIGURED;
	drvdata->anc_status = ANC_UNCONFIGURED;
	dev_set_drvdata(&pdev->dev, drvdata);

	drvdata->regmap = devm_regmap_init(&pdev->dev, शून्य, &pdev->dev,
					   &ab8500_codec_regmap);
	अगर (IS_ERR(drvdata->regmap)) अणु
		status = PTR_ERR(drvdata->regmap);
		dev_err(&pdev->dev, "%s: Failed to allocate regmap: %d\n",
			__func__, status);
		वापस status;
	पूर्ण

	dev_dbg(&pdev->dev, "%s: Register codec.\n", __func__);
	status = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				&ab8500_component_driver,
				ab8500_codec_dai,
				ARRAY_SIZE(ab8500_codec_dai));
	अगर (status < 0)
		dev_err(&pdev->dev,
			"%s: Error: Failed to register codec (%d).\n",
			__func__, status);

	वापस status;
पूर्ण

अटल काष्ठा platक्रमm_driver ab8500_codec_platक्रमm_driver = अणु
	.driver	= अणु
		.name	= "ab8500-codec",
	पूर्ण,
	.probe		= ab8500_codec_driver_probe,
पूर्ण;
module_platक्रमm_driver(ab8500_codec_platक्रमm_driver);

MODULE_LICENSE("GPL v2");
