<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt274.c  --  RT274 ALSA SoC audio codec driver
 *
 * Copyright 2017 Realtek Semiconductor Corp.
 * Author: Bard Liao <bardliao@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/jack.h>
#समावेश <linux/workqueue.h>

#समावेश "rl6347a.h"
#समावेश "rt274.h"

#घोषणा RT274_VENDOR_ID 0x10ec0274

काष्ठा rt274_priv अणु
	काष्ठा reg_शेष *index_cache;
	पूर्णांक index_cache_size;
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_component *component;
	काष्ठा i2c_client *i2c;
	काष्ठा snd_soc_jack *jack;
	काष्ठा delayed_work jack_detect_work;
	पूर्णांक sys_clk;
	पूर्णांक clk_id;
	पूर्णांक fs;
	bool master;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt274_index_def[] = अणु
	अणु 0x00, 0x1004 पूर्ण,
	अणु 0x01, 0xaaaa पूर्ण,
	अणु 0x02, 0x88aa पूर्ण,
	अणु 0x03, 0x0002 पूर्ण,
	अणु 0x04, 0xaa09 पूर्ण,
	अणु 0x05, 0x0700 पूर्ण,
	अणु 0x06, 0x6110 पूर्ण,
	अणु 0x07, 0x0200 पूर्ण,
	अणु 0x08, 0xa807 पूर्ण,
	अणु 0x09, 0x0021 पूर्ण,
	अणु 0x0a, 0x7770 पूर्ण,
	अणु 0x0b, 0x7770 पूर्ण,
	अणु 0x0c, 0x002b पूर्ण,
	अणु 0x0d, 0x2420 पूर्ण,
	अणु 0x0e, 0x65c0 पूर्ण,
	अणु 0x0f, 0x7770 पूर्ण,
	अणु 0x10, 0x0420 पूर्ण,
	अणु 0x11, 0x7418 पूर्ण,
	अणु 0x12, 0x6bd0 पूर्ण,
	अणु 0x13, 0x645f पूर्ण,
	अणु 0x14, 0x0400 पूर्ण,
	अणु 0x15, 0x8ccc पूर्ण,
	अणु 0x16, 0x4c50 पूर्ण,
	अणु 0x17, 0xff00 पूर्ण,
	अणु 0x18, 0x0003 पूर्ण,
	अणु 0x19, 0x2c11 पूर्ण,
	अणु 0x1a, 0x830b पूर्ण,
	अणु 0x1b, 0x4e4b पूर्ण,
	अणु 0x1c, 0x0000 पूर्ण,
	अणु 0x1d, 0x0000 पूर्ण,
	अणु 0x1e, 0x0000 पूर्ण,
	अणु 0x1f, 0x0000 पूर्ण,
	अणु 0x20, 0x51ff पूर्ण,
	अणु 0x21, 0x8000 पूर्ण,
	अणु 0x22, 0x8f00 पूर्ण,
	अणु 0x23, 0x88f4 पूर्ण,
	अणु 0x24, 0x0000 पूर्ण,
	अणु 0x25, 0x0000 पूर्ण,
	अणु 0x26, 0x0000 पूर्ण,
	अणु 0x27, 0x0000 पूर्ण,
	अणु 0x28, 0x0000 पूर्ण,
	अणु 0x29, 0x3000 पूर्ण,
	अणु 0x2a, 0x0000 पूर्ण,
	अणु 0x2b, 0x0000 पूर्ण,
	अणु 0x2c, 0x0f00 पूर्ण,
	अणु 0x2d, 0x100f पूर्ण,
	अणु 0x2e, 0x2902 पूर्ण,
	अणु 0x2f, 0xe280 पूर्ण,
	अणु 0x30, 0x1000 पूर्ण,
	अणु 0x31, 0x8400 पूर्ण,
	अणु 0x32, 0x5aaa पूर्ण,
	अणु 0x33, 0x8420 पूर्ण,
	अणु 0x34, 0xa20c पूर्ण,
	अणु 0x35, 0x096a पूर्ण,
	अणु 0x36, 0x5757 पूर्ण,
	अणु 0x37, 0xfe05 पूर्ण,
	अणु 0x38, 0x4901 पूर्ण,
	अणु 0x39, 0x110a पूर्ण,
	अणु 0x3a, 0x0010 पूर्ण,
	अणु 0x3b, 0x60d9 पूर्ण,
	अणु 0x3c, 0xf214 पूर्ण,
	अणु 0x3d, 0xc2ba पूर्ण,
	अणु 0x3e, 0xa928 पूर्ण,
	अणु 0x3f, 0x0000 पूर्ण,
	अणु 0x40, 0x9800 पूर्ण,
	अणु 0x41, 0x0000 पूर्ण,
	अणु 0x42, 0x2000 पूर्ण,
	अणु 0x43, 0x3d90 पूर्ण,
	अणु 0x44, 0x4900 पूर्ण,
	अणु 0x45, 0x5289 पूर्ण,
	अणु 0x46, 0x0004 पूर्ण,
	अणु 0x47, 0xa47a पूर्ण,
	अणु 0x48, 0xd049 पूर्ण,
	अणु 0x49, 0x0049 पूर्ण,
	अणु 0x4a, 0xa83b पूर्ण,
	अणु 0x4b, 0x0777 पूर्ण,
	अणु 0x4c, 0x065c पूर्ण,
	अणु 0x4d, 0x7fff पूर्ण,
	अणु 0x4e, 0x7fff पूर्ण,
	अणु 0x4f, 0x0000 पूर्ण,
	अणु 0x50, 0x0000 पूर्ण,
	अणु 0x51, 0x0000 पूर्ण,
	अणु 0x52, 0xbf5f पूर्ण,
	अणु 0x53, 0x3320 पूर्ण,
	अणु 0x54, 0xcc00 पूर्ण,
	अणु 0x55, 0x0000 पूर्ण,
	अणु 0x56, 0x3f00 पूर्ण,
	अणु 0x57, 0x0000 पूर्ण,
	अणु 0x58, 0x0000 पूर्ण,
	अणु 0x59, 0x0000 पूर्ण,
	अणु 0x5a, 0x1300 पूर्ण,
	अणु 0x5b, 0x005f पूर्ण,
	अणु 0x5c, 0x0000 पूर्ण,
	अणु 0x5d, 0x1001 पूर्ण,
	अणु 0x5e, 0x1000 पूर्ण,
	अणु 0x5f, 0x0000 पूर्ण,
	अणु 0x60, 0x5554 पूर्ण,
	अणु 0x61, 0xffc0 पूर्ण,
	अणु 0x62, 0xa000 पूर्ण,
	अणु 0x63, 0xd010 पूर्ण,
	अणु 0x64, 0x0000 पूर्ण,
	अणु 0x65, 0x3fb1 पूर्ण,
	अणु 0x66, 0x1881 पूर्ण,
	अणु 0x67, 0xc810 पूर्ण,
	अणु 0x68, 0x2000 पूर्ण,
	अणु 0x69, 0xfff0 पूर्ण,
	अणु 0x6a, 0x0300 पूर्ण,
	अणु 0x6b, 0x5060 पूर्ण,
	अणु 0x6c, 0x0000 पूर्ण,
	अणु 0x6d, 0x0000 पूर्ण,
	अणु 0x6e, 0x0c25 पूर्ण,
	अणु 0x6f, 0x0c0b पूर्ण,
	अणु 0x70, 0x8000 पूर्ण,
	अणु 0x71, 0x4008 पूर्ण,
	अणु 0x72, 0x0000 पूर्ण,
	अणु 0x73, 0x0800 पूर्ण,
	अणु 0x74, 0xa28f पूर्ण,
	अणु 0x75, 0xa050 पूर्ण,
	अणु 0x76, 0x7fe8 पूर्ण,
	अणु 0x77, 0xdb8c पूर्ण,
	अणु 0x78, 0x0000 पूर्ण,
	अणु 0x79, 0x0000 पूर्ण,
	अणु 0x7a, 0x2a96 पूर्ण,
	अणु 0x7b, 0x800f पूर्ण,
	अणु 0x7c, 0x0200 पूर्ण,
	अणु 0x7d, 0x1600 पूर्ण,
	अणु 0x7e, 0x0000 पूर्ण,
	अणु 0x7f, 0x0000 पूर्ण,
पूर्ण;
#घोषणा INDEX_CACHE_SIZE ARRAY_SIZE(rt274_index_def)

अटल स्थिर काष्ठा reg_शेष rt274_reg[] = अणु
	अणु 0x00170500, 0x00000400 पूर्ण,
	अणु 0x00220000, 0x00000031 पूर्ण,
	अणु 0x00239000, 0x00000057 पूर्ण,
	अणु 0x0023a000, 0x00000057 पूर्ण,
	अणु 0x00270500, 0x00000400 पूर्ण,
	अणु 0x00370500, 0x00000400 पूर्ण,
	अणु 0x00870500, 0x00000400 पूर्ण,
	अणु 0x00920000, 0x00000031 पूर्ण,
	अणु 0x00935000, 0x00000097 पूर्ण,
	अणु 0x00936000, 0x00000097 पूर्ण,
	अणु 0x00970500, 0x00000400 पूर्ण,
	अणु 0x00b37000, 0x00000400 पूर्ण,
	अणु 0x00b37200, 0x00000400 पूर्ण,
	अणु 0x00b37300, 0x00000400 पूर्ण,
	अणु 0x00c37000, 0x00000400 पूर्ण,
	अणु 0x00c37100, 0x00000400 पूर्ण,
	अणु 0x01270500, 0x00000400 पूर्ण,
	अणु 0x01370500, 0x00000400 पूर्ण,
	अणु 0x01371f00, 0x411111f0 पूर्ण,
	अणु 0x01937000, 0x00000000 पूर्ण,
	अणु 0x01970500, 0x00000400 पूर्ण,
	अणु 0x02050000, 0x0000001b पूर्ण,
	अणु 0x02139000, 0x00000080 पूर्ण,
	अणु 0x0213a000, 0x00000080 पूर्ण,
	अणु 0x02170100, 0x00000001 पूर्ण,
	अणु 0x02170500, 0x00000400 पूर्ण,
	अणु 0x02170700, 0x00000000 पूर्ण,
	अणु 0x02270100, 0x00000000 पूर्ण,
	अणु 0x02370100, 0x00000000 पूर्ण,
	अणु 0x01970700, 0x00000020 पूर्ण,
	अणु 0x00830000, 0x00000097 पूर्ण,
	अणु 0x00930000, 0x00000097 पूर्ण,
	अणु 0x01270700, 0x00000000 पूर्ण,
पूर्ण;

अटल bool rt274_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0 ... 0xff:
	हाल RT274_GET_PARAM(AC_NODE_ROOT, AC_PAR_VENDOR_ID):
	हाल RT274_GET_HP_SENSE:
	हाल RT274_GET_MIC_SENSE:
	हाल RT274_PROC_COEF:
	हाल VERB_CMD(AC_VERB_GET_EAPD_BTLENABLE, RT274_MIC, 0):
	हाल VERB_CMD(AC_VERB_GET_EAPD_BTLENABLE, RT274_HP_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_STREAM_FORMAT, RT274_DAC_OUT0, 0):
	हाल VERB_CMD(AC_VERB_GET_STREAM_FORMAT, RT274_DAC_OUT1, 0):
	हाल VERB_CMD(AC_VERB_GET_STREAM_FORMAT, RT274_ADC_IN1, 0):
	हाल VERB_CMD(AC_VERB_GET_STREAM_FORMAT, RT274_ADC_IN2, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_DAC_OUT0, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_DAC_OUT1, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_ADC_IN1, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_ADC_IN2, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_DMIC1, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_DMIC2, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_MIC, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_LINE1, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_LINE2, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_HP_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_CONNECT_SEL, RT274_HP_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_CONNECT_SEL, RT274_MIXER_IN1, 0):
	हाल VERB_CMD(AC_VERB_GET_CONNECT_SEL, RT274_MIXER_IN2, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_DMIC1, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_DMIC2, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_MIC, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_LINE1, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_LINE2, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_HP_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_UNSOLICITED_RESPONSE, RT274_HP_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_UNSOLICITED_RESPONSE, RT274_MIC, 0):
	हाल VERB_CMD(AC_VERB_GET_UNSOLICITED_RESPONSE, RT274_INLINE_CMD, 0):
		वापस true;
	शेष:
		वापस false;
	पूर्ण


पूर्ण

अटल bool rt274_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0 ... 0xff:
	हाल RT274_GET_PARAM(AC_NODE_ROOT, AC_PAR_VENDOR_ID):
	हाल RT274_GET_HP_SENSE:
	हाल RT274_GET_MIC_SENSE:
	हाल RT274_SET_AUDIO_POWER:
	हाल RT274_SET_HPO_POWER:
	हाल RT274_SET_DMIC1_POWER:
	हाल RT274_LOUT_MUX:
	हाल RT274_HPO_MUX:
	हाल RT274_ADC0_MUX:
	हाल RT274_ADC1_MUX:
	हाल RT274_SET_MIC:
	हाल RT274_SET_PIN_HPO:
	हाल RT274_SET_PIN_LOUT3:
	हाल RT274_SET_PIN_DMIC1:
	हाल RT274_SET_AMP_GAIN_HPO:
	हाल RT274_SET_DMIC2_DEFAULT:
	हाल RT274_DAC0L_GAIN:
	हाल RT274_DAC0R_GAIN:
	हाल RT274_DAC1L_GAIN:
	हाल RT274_DAC1R_GAIN:
	हाल RT274_ADCL_GAIN:
	हाल RT274_ADCR_GAIN:
	हाल RT274_MIC_GAIN:
	हाल RT274_HPOL_GAIN:
	हाल RT274_HPOR_GAIN:
	हाल RT274_LOUTL_GAIN:
	हाल RT274_LOUTR_GAIN:
	हाल RT274_DAC_FORMAT:
	हाल RT274_ADC_FORMAT:
	हाल RT274_COEF_INDEX:
	हाल RT274_PROC_COEF:
	हाल RT274_SET_AMP_GAIN_ADC_IN1:
	हाल RT274_SET_AMP_GAIN_ADC_IN2:
	हाल RT274_SET_POWER(RT274_DAC_OUT0):
	हाल RT274_SET_POWER(RT274_DAC_OUT1):
	हाल RT274_SET_POWER(RT274_ADC_IN1):
	हाल RT274_SET_POWER(RT274_ADC_IN2):
	हाल RT274_SET_POWER(RT274_DMIC2):
	हाल RT274_SET_POWER(RT274_MIC):
	हाल VERB_CMD(AC_VERB_GET_EAPD_BTLENABLE, RT274_MIC, 0):
	हाल VERB_CMD(AC_VERB_GET_EAPD_BTLENABLE, RT274_HP_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_STREAM_FORMAT, RT274_DAC_OUT0, 0):
	हाल VERB_CMD(AC_VERB_GET_STREAM_FORMAT, RT274_DAC_OUT1, 0):
	हाल VERB_CMD(AC_VERB_GET_STREAM_FORMAT, RT274_ADC_IN1, 0):
	हाल VERB_CMD(AC_VERB_GET_STREAM_FORMAT, RT274_ADC_IN2, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_DAC_OUT0, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_DAC_OUT1, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_ADC_IN1, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_ADC_IN2, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_DMIC1, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_DMIC2, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_MIC, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_LINE1, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_LINE2, 0):
	हाल VERB_CMD(AC_VERB_GET_AMP_GAIN_MUTE, RT274_HP_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_CONNECT_SEL, RT274_HP_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_CONNECT_SEL, RT274_MIXER_IN1, 0):
	हाल VERB_CMD(AC_VERB_GET_CONNECT_SEL, RT274_MIXER_IN2, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_DMIC1, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_DMIC2, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_MIC, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_LINE1, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_LINE2, 0):
	हाल VERB_CMD(AC_VERB_GET_PIN_WIDGET_CONTROL, RT274_HP_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_UNSOLICITED_RESPONSE, RT274_HP_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_UNSOLICITED_RESPONSE, RT274_MIC, 0):
	हाल VERB_CMD(AC_VERB_GET_UNSOLICITED_RESPONSE, RT274_INLINE_CMD, 0):
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम rt274_index_sync(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	क्रम (i = 0; i < INDEX_CACHE_SIZE; i++) अणु
		snd_soc_component_ग_लिखो(component, rt274->index_cache[i].reg,
				  rt274->index_cache[i].def);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rt274_jack_detect(काष्ठा rt274_priv *rt274, bool *hp, bool *mic)
अणु
	अचिन्हित पूर्णांक buf;
	पूर्णांक ret;

	*hp = false;
	*mic = false;

	अगर (!rt274->component)
		वापस -EINVAL;

	ret = regmap_पढ़ो(rt274->regmap, RT274_GET_HP_SENSE, &buf);
	अगर (ret)
		वापस ret;

	*hp = buf & 0x80000000;
	ret = regmap_पढ़ो(rt274->regmap, RT274_GET_MIC_SENSE, &buf);
	अगर (ret)
		वापस ret;

	*mic = buf & 0x80000000;

	pr_debug("*hp = %d *mic = %d\n", *hp, *mic);

	वापस 0;
पूर्ण

अटल व्योम rt274_jack_detect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt274_priv *rt274 =
		container_of(work, काष्ठा rt274_priv, jack_detect_work.work);
	पूर्णांक status = 0;
	bool hp = false;
	bool mic = false;

	अगर (rt274_jack_detect(rt274, &hp, &mic) < 0)
		वापस;

	अगर (hp)
		status |= SND_JACK_HEADPHONE;

	अगर (mic)
		status |= SND_JACK_MICROPHONE;

	snd_soc_jack_report(rt274->jack, status,
		SND_JACK_MICROPHONE | SND_JACK_HEADPHONE);
पूर्ण

अटल irqवापस_t rt274_irq(पूर्णांक irq, व्योम *data);

अटल पूर्णांक rt274_mic_detect(काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_jack *jack,  व्योम *data)
अणु
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);

	rt274->jack = jack;

	अगर (jack == शून्य) अणु
		/* Disable jack detection */
		regmap_update_bits(rt274->regmap, RT274_EAPD_GPIO_IRQ_CTRL,
					RT274_IRQ_EN, RT274_IRQ_DIS);

		वापस 0;
	पूर्ण

	regmap_update_bits(rt274->regmap, RT274_EAPD_GPIO_IRQ_CTRL,
				RT274_IRQ_EN, RT274_IRQ_EN);

	/* Send an initial report */
	rt274_irq(0, rt274);

	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(out_vol_tlv, -6350, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_vol_tlv, 0, 1000, 0);

अटल स्थिर काष्ठा snd_kcontrol_new rt274_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("DAC0 Playback Volume", RT274_DAC0L_GAIN,
			 RT274_DAC0R_GAIN, 0, 0x7f, 0, out_vol_tlv),
	SOC_DOUBLE_R_TLV("DAC1 Playback Volume", RT274_DAC1L_GAIN,
			 RT274_DAC1R_GAIN, 0, 0x7f, 0, out_vol_tlv),
	SOC_DOUBLE_R_TLV("ADC0 Capture Volume", RT274_ADCL_GAIN,
			    RT274_ADCR_GAIN, 0, 0x7f, 0, out_vol_tlv),
	SOC_DOUBLE_R("ADC0 Capture Switch", RT274_ADCL_GAIN,
			    RT274_ADCR_GAIN, RT274_MUTE_SFT, 1, 1),
	SOC_SINGLE_TLV("AMIC Volume", RT274_MIC_GAIN,
			    0, 0x3, 0, mic_vol_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new hpol_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT274_HPOL_GAIN,
			RT274_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpor_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT274_HPOR_GAIN,
			RT274_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new loutl_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT274_LOUTL_GAIN,
			RT274_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new loutr_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT274_LOUTR_GAIN,
			RT274_MUTE_SFT, 1, 1);

/* ADC0 source */
अटल स्थिर अक्षर * स्थिर rt274_adc_src[] = अणु
	"Mic", "Line1", "Line2", "Dmic"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt274_adc0_क्रमागत, RT274_ADC0_MUX, RT274_ADC_SEL_SFT,
	rt274_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt274_adc0_mux =
	SOC_DAPM_ENUM("ADC 0 source", rt274_adc0_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(
	rt274_adc1_क्रमागत, RT274_ADC1_MUX, RT274_ADC_SEL_SFT,
	rt274_adc_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt274_adc1_mux =
	SOC_DAPM_ENUM("ADC 1 source", rt274_adc1_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt274_dac_src[] = अणु
	"DAC OUT0", "DAC OUT1"
पूर्ण;
/* HP-OUT source */
अटल SOC_ENUM_SINGLE_DECL(rt274_hpo_क्रमागत, RT274_HPO_MUX,
				0, rt274_dac_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt274_hpo_mux =
SOC_DAPM_ENUM("HPO source", rt274_hpo_क्रमागत);

/* Line out source */
अटल SOC_ENUM_SINGLE_DECL(rt274_lout_क्रमागत, RT274_LOUT_MUX,
				0, rt274_dac_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt274_lout_mux =
SOC_DAPM_ENUM("LOUT source", rt274_lout_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget rt274_dapm_widमाला_लो[] = अणु
	/* Input Lines */
	SND_SOC_DAPM_INPUT("DMIC1 Pin"),
	SND_SOC_DAPM_INPUT("DMIC2 Pin"),
	SND_SOC_DAPM_INPUT("MIC"),
	SND_SOC_DAPM_INPUT("LINE1"),
	SND_SOC_DAPM_INPUT("LINE2"),

	/* DMIC */
	SND_SOC_DAPM_PGA("DMIC1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DMIC2", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC 0", शून्य, RT274_SET_STREAMID_ADC1, 4, 0),
	SND_SOC_DAPM_ADC("ADC 1", शून्य, RT274_SET_STREAMID_ADC2, 4, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX("ADC 0 Mux", SND_SOC_NOPM, 0, 0,
		&rt274_adc0_mux),
	SND_SOC_DAPM_MUX("ADC 1 Mux", SND_SOC_NOPM, 0, 0,
		&rt274_adc1_mux),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RXL", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF1RXR", "AIF1 Playback", 1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TXL", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TXR", "AIF1 Capture", 1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2RXL", "AIF1 Playback", 2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2RXR", "AIF1 Playback", 3, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TXL", "AIF1 Capture", 2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TXR", "AIF1 Capture", 3, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DACs */
	SND_SOC_DAPM_DAC("DAC 0", शून्य, RT274_SET_STREAMID_DAC0, 4, 0),
	SND_SOC_DAPM_DAC("DAC 1", शून्य, RT274_SET_STREAMID_DAC1, 4, 0),

	/* Output Mux */
	SND_SOC_DAPM_MUX("HPO Mux", SND_SOC_NOPM, 0, 0, &rt274_hpo_mux),
	SND_SOC_DAPM_MUX("LOUT Mux", SND_SOC_NOPM, 0, 0, &rt274_lout_mux),

	SND_SOC_DAPM_SUPPLY("HP Power", RT274_SET_PIN_HPO,
		RT274_SET_PIN_SFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("LOUT Power", RT274_SET_PIN_LOUT3,
		RT274_SET_PIN_SFT, 0, शून्य, 0),

	/* Output Mixer */
	SND_SOC_DAPM_PGA("DAC OUT0", SND_SOC_NOPM, 0, 0,
			शून्य, 0),
	SND_SOC_DAPM_PGA("DAC OUT1", SND_SOC_NOPM, 0, 0,
			शून्य, 0),

	/* Output Pga */
	SND_SOC_DAPM_SWITCH("LOUT L", SND_SOC_NOPM, 0, 0,
		&loutl_enable_control),
	SND_SOC_DAPM_SWITCH("LOUT R", SND_SOC_NOPM, 0, 0,
		&loutr_enable_control),
	SND_SOC_DAPM_SWITCH("HPO L", SND_SOC_NOPM, 0, 0,
		&hpol_enable_control),
	SND_SOC_DAPM_SWITCH("HPO R", SND_SOC_NOPM, 0, 0,
		&hpor_enable_control),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("HPO Pin"),
	SND_SOC_DAPM_OUTPUT("SPDIF"),
	SND_SOC_DAPM_OUTPUT("LINE3"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt274_dapm_routes[] = अणु
	अणु"DMIC1", शून्य, "DMIC1 Pin"पूर्ण,
	अणु"DMIC2", शून्य, "DMIC2 Pin"पूर्ण,

	अणु"ADC 0 Mux", "Mic", "MIC"पूर्ण,
	अणु"ADC 0 Mux", "Dmic", "DMIC1"पूर्ण,
	अणु"ADC 0 Mux", "Line1", "LINE1"पूर्ण,
	अणु"ADC 0 Mux", "Line2", "LINE2"पूर्ण,
	अणु"ADC 1 Mux", "Mic", "MIC"पूर्ण,
	अणु"ADC 1 Mux", "Dmic", "DMIC2"पूर्ण,
	अणु"ADC 1 Mux", "Line1", "LINE1"पूर्ण,
	अणु"ADC 1 Mux", "Line2", "LINE2"पूर्ण,

	अणु"ADC 0", शून्य, "ADC 0 Mux"पूर्ण,
	अणु"ADC 1", शून्य, "ADC 1 Mux"पूर्ण,

	अणु"AIF1TXL", शून्य, "ADC 0"पूर्ण,
	अणु"AIF1TXR", शून्य, "ADC 0"पूर्ण,
	अणु"AIF2TXL", शून्य, "ADC 1"पूर्ण,
	अणु"AIF2TXR", शून्य, "ADC 1"पूर्ण,

	अणु"DAC 0", शून्य, "AIF1RXL"पूर्ण,
	अणु"DAC 0", शून्य, "AIF1RXR"पूर्ण,
	अणु"DAC 1", शून्य, "AIF2RXL"पूर्ण,
	अणु"DAC 1", शून्य, "AIF2RXR"पूर्ण,

	अणु"DAC OUT0", शून्य, "DAC 0"पूर्ण,

	अणु"DAC OUT1", शून्य, "DAC 1"पूर्ण,

	अणु"LOUT Mux", "DAC OUT0", "DAC OUT0"पूर्ण,
	अणु"LOUT Mux", "DAC OUT1", "DAC OUT1"पूर्ण,

	अणु"LOUT L", "Switch", "LOUT Mux"पूर्ण,
	अणु"LOUT R", "Switch", "LOUT Mux"पूर्ण,
	अणु"LOUT L", शून्य, "LOUT Power"पूर्ण,
	अणु"LOUT R", शून्य, "LOUT Power"पूर्ण,

	अणु"LINE3", शून्य, "LOUT L"पूर्ण,
	अणु"LINE3", शून्य, "LOUT R"पूर्ण,

	अणु"HPO Mux", "DAC OUT0", "DAC OUT0"पूर्ण,
	अणु"HPO Mux", "DAC OUT1", "DAC OUT1"पूर्ण,

	अणु"HPO L", "Switch", "HPO Mux"पूर्ण,
	अणु"HPO R", "Switch", "HPO Mux"पूर्ण,
	अणु"HPO L", शून्य, "HP Power"पूर्ण,
	अणु"HPO R", शून्य, "HP Power"पूर्ण,

	अणु"HPO Pin", शून्य, "HPO L"पूर्ण,
	अणु"HPO Pin", शून्य, "HPO R"पूर्ण,
पूर्ण;

अटल पूर्णांक rt274_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक d_len_code = 0, c_len_code = 0;

	चयन (params_rate(params)) अणु
	/* bit 14 0:48K 1:44.1K */
	हाल 44100:
	हाल 48000:
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported sample rate %d\n",
					params_rate(params));
		वापस -EINVAL;
	पूर्ण
	चयन (rt274->sys_clk) अणु
	हाल 12288000:
	हाल 24576000:
		अगर (params_rate(params) != 48000) अणु
			dev_err(component->dev, "Sys_clk is not matched (%d %d)\n",
					params_rate(params), rt274->sys_clk);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 11289600:
	हाल 22579200:
		अगर (params_rate(params) != 44100) अणु
			dev_err(component->dev, "Sys_clk is not matched (%d %d)\n",
					params_rate(params), rt274->sys_clk);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (params_channels(params) <= 16) अणु
		/* bit 3:0 Number of Channel */
		val |= (params_channels(params) - 1);
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Unsupported channels %d\n",
					params_channels(params));
		वापस -EINVAL;
	पूर्ण

	चयन (params_width(params)) अणु
	/* bit 6:4 Bits per Sample */
	हाल 16:
		d_len_code = 0;
		c_len_code = 0;
		val |= (0x1 << 4);
		अवरोध;
	हाल 32:
		d_len_code = 2;
		c_len_code = 3;
		val |= (0x4 << 4);
		अवरोध;
	हाल 20:
		d_len_code = 1;
		c_len_code = 1;
		val |= (0x2 << 4);
		अवरोध;
	हाल 24:
		d_len_code = 2;
		c_len_code = 2;
		val |= (0x3 << 4);
		अवरोध;
	हाल 8:
		d_len_code = 3;
		c_len_code = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (rt274->master)
		c_len_code = 0x3;

	snd_soc_component_update_bits(component,
		RT274_I2S_CTRL1, 0xc018, d_len_code << 3 | c_len_code << 14);
	dev_dbg(component->dev, "format val = 0x%x\n", val);

	snd_soc_component_update_bits(component, RT274_DAC_FORMAT, 0x407f, val);
	snd_soc_component_update_bits(component, RT274_ADC_FORMAT, 0x407f, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt274_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL1, RT274_I2S_MODE_MASK, RT274_I2S_MODE_M);
		rt274->master = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL1, RT274_I2S_MODE_MASK, RT274_I2S_MODE_S);
		rt274->master = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		snd_soc_component_update_bits(component, RT274_I2S_CTRL1,
					RT274_I2S_FMT_MASK, RT274_I2S_FMT_I2S);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		snd_soc_component_update_bits(component, RT274_I2S_CTRL1,
					RT274_I2S_FMT_MASK, RT274_I2S_FMT_LJ);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		snd_soc_component_update_bits(component, RT274_I2S_CTRL1,
					RT274_I2S_FMT_MASK, RT274_I2S_FMT_PCMA);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		snd_soc_component_update_bits(component, RT274_I2S_CTRL1,
					RT274_I2S_FMT_MASK, RT274_I2S_FMT_PCMB);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* bit 15 Stream Type 0:PCM 1:Non-PCM */
	snd_soc_component_update_bits(component, RT274_DAC_FORMAT, 0x8000, 0);
	snd_soc_component_update_bits(component, RT274_ADC_FORMAT, 0x8000, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rt274_set_dai_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);

	चयन (source) अणु
	हाल RT274_PLL2_S_MCLK:
		snd_soc_component_update_bits(component, RT274_PLL2_CTRL,
				RT274_PLL2_SRC_MASK, RT274_PLL2_SRC_MCLK);
		अवरोध;
	शेष:
		dev_warn(component->dev, "invalid pll source, use BCLK\n");
		fallthrough;
	हाल RT274_PLL2_S_BCLK:
		snd_soc_component_update_bits(component, RT274_PLL2_CTRL,
				RT274_PLL2_SRC_MASK, RT274_PLL2_SRC_BCLK);
		अवरोध;
	पूर्ण

	अगर (source == RT274_PLL2_S_BCLK) अणु
		snd_soc_component_update_bits(component, RT274_MCLK_CTRL,
				(0x3 << 12), (0x3 << 12));
		चयन (rt274->fs) अणु
		हाल 50:
			snd_soc_component_ग_लिखो(component, 0x7a, 0xaab6);
			snd_soc_component_ग_लिखो(component, 0x7b, 0x0301);
			snd_soc_component_ग_लिखो(component, 0x7c, 0x04fe);
			अवरोध;
		हाल 64:
			snd_soc_component_ग_लिखो(component, 0x7a, 0xaa96);
			snd_soc_component_ग_लिखो(component, 0x7b, 0x8003);
			snd_soc_component_ग_लिखो(component, 0x7c, 0x081e);
			अवरोध;
		हाल 128:
			snd_soc_component_ग_लिखो(component, 0x7a, 0xaa96);
			snd_soc_component_ग_लिखो(component, 0x7b, 0x8003);
			snd_soc_component_ग_लिखो(component, 0x7c, 0x080e);
			अवरोध;
		शेष:
			dev_warn(component->dev, "invalid freq_in, assume 4.8M\n");
			fallthrough;
		हाल 100:
			snd_soc_component_ग_लिखो(component, 0x7a, 0xaab6);
			snd_soc_component_ग_लिखो(component, 0x7b, 0x0301);
			snd_soc_component_ग_लिखो(component, 0x7c, 0x047e);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt274_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
				पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक clk_src, mclk_en;

	dev_dbg(component->dev, "%s freq=%d\n", __func__, freq);

	चयन (clk_id) अणु
	हाल RT274_SCLK_S_MCLK:
		mclk_en = RT274_MCLK_MODE_EN;
		clk_src = RT274_CLK_SRC_MCLK;
		अवरोध;
	हाल RT274_SCLK_S_PLL1:
		mclk_en = RT274_MCLK_MODE_DIS;
		clk_src = RT274_CLK_SRC_MCLK;
		अवरोध;
	हाल RT274_SCLK_S_PLL2:
		mclk_en = RT274_MCLK_MODE_EN;
		clk_src = RT274_CLK_SRC_PLL2;
		अवरोध;
	शेष:
		mclk_en = RT274_MCLK_MODE_DIS;
		clk_src = RT274_CLK_SRC_MCLK;
		dev_warn(component->dev, "invalid sysclk source, use PLL1\n");
		अवरोध;
	पूर्ण
	snd_soc_component_update_bits(component, RT274_MCLK_CTRL,
			RT274_MCLK_MODE_MASK, mclk_en);
	snd_soc_component_update_bits(component, RT274_CLK_CTRL,
			RT274_CLK_SRC_MASK, clk_src);

	चयन (freq) अणु
	हाल 19200000:
		अगर (clk_id == RT274_SCLK_S_MCLK) अणु
			dev_err(component->dev, "Should not use MCLK\n");
			वापस -EINVAL;
		पूर्ण
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL2, 0x40, 0x40);
		अवरोध;
	हाल 24000000:
		अगर (clk_id == RT274_SCLK_S_MCLK) अणु
			dev_err(component->dev, "Should not use MCLK\n");
			वापस -EINVAL;
		पूर्ण
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL2, 0x40, 0x0);
		अवरोध;
	हाल 12288000:
	हाल 11289600:
		snd_soc_component_update_bits(component,
			RT274_MCLK_CTRL, 0x1fcf, 0x0008);
		अवरोध;
	हाल 24576000:
	हाल 22579200:
		snd_soc_component_update_bits(component,
			RT274_MCLK_CTRL, 0x1fcf, 0x1543);
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported system clock\n");
		वापस -EINVAL;
	पूर्ण

	rt274->sys_clk = freq;
	rt274->clk_id = clk_id;

	वापस 0;
पूर्ण

अटल पूर्णांक rt274_set_bclk_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "%s ratio=%d\n", __func__, ratio);
	rt274->fs = ratio;
	अगर ((ratio / 50) == 0)
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL1, 0x1000, 0x1000);
	अन्यथा
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL1, 0x1000, 0x0);


	वापस 0;
पूर्ण

अटल पूर्णांक rt274_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)

अणु
	काष्ठा snd_soc_component *component = dai->component;

	अगर (rx_mask || tx_mask) अणु
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL1, RT274_TDM_EN, RT274_TDM_EN);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL1, RT274_TDM_EN, RT274_TDM_DIS);
		वापस 0;
	पूर्ण

	चयन (slots) अणु
	हाल 4:
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL1, RT274_TDM_CH_NUM, RT274_TDM_4CH);
		अवरोध;
	हाल 2:
		snd_soc_component_update_bits(component,
			RT274_I2S_CTRL1, RT274_TDM_CH_NUM, RT274_TDM_2CH);
		अवरोध;
	शेष:
		dev_err(component->dev,
			"Support 2 or 4 slots TDM only\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt274_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (SND_SOC_BIAS_STANDBY ==
			snd_soc_component_get_bias_level(component)) अणु
			snd_soc_component_ग_लिखो(component,
				RT274_SET_AUDIO_POWER, AC_PWRST_D0);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_ग_लिखो(component,
			RT274_SET_AUDIO_POWER, AC_PWRST_D3);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t rt274_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt274_priv *rt274 = data;
	bool hp = false;
	bool mic = false;
	पूर्णांक ret, status = 0;

	/* Clear IRQ */
	regmap_update_bits(rt274->regmap, RT274_EAPD_GPIO_IRQ_CTRL,
				RT274_IRQ_CLR, RT274_IRQ_CLR);

	ret = rt274_jack_detect(rt274, &hp, &mic);

	अगर (ret == 0) अणु
		अगर (hp)
			status |= SND_JACK_HEADPHONE;

		अगर (mic)
			status |= SND_JACK_MICROPHONE;

		snd_soc_jack_report(rt274->jack, status,
			SND_JACK_MICROPHONE | SND_JACK_HEADPHONE);

		pm_wakeup_event(&rt274->i2c->dev, 300);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rt274_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);

	rt274->component = component;

	अगर (rt274->i2c->irq) अणु
		INIT_DELAYED_WORK(&rt274->jack_detect_work,
					rt274_jack_detect_work);
		schedule_delayed_work(&rt274->jack_detect_work,
					msecs_to_jअगरfies(1250));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt274_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);

	cancel_delayed_work_sync(&rt274->jack_detect_work);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt274_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt274->regmap, true);
	regcache_mark_dirty(rt274->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rt274_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt274_priv *rt274 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt274->regmap, false);
	rt274_index_sync(component);
	regcache_sync(rt274->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt274_suspend शून्य
#घोषणा rt274_resume शून्य
#पूर्ण_अगर

#घोषणा RT274_STEREO_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)
#घोषणा RT274_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt274_aअगर_dai_ops = अणु
	.hw_params = rt274_hw_params,
	.set_fmt = rt274_set_dai_fmt,
	.set_sysclk = rt274_set_dai_sysclk,
	.set_pll = rt274_set_dai_pll,
	.set_bclk_ratio = rt274_set_bclk_ratio,
	.set_tdm_slot = rt274_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt274_dai[] = अणु
	अणु
		.name = "rt274-aif1",
		.id = RT274_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT274_STEREO_RATES,
			.क्रमmats = RT274_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT274_STEREO_RATES,
			.क्रमmats = RT274_FORMATS,
		पूर्ण,
		.ops = &rt274_aअगर_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt274 = अणु
	.probe			= rt274_probe,
	.हटाओ			= rt274_हटाओ,
	.suspend		= rt274_suspend,
	.resume			= rt274_resume,
	.set_bias_level		= rt274_set_bias_level,
	.set_jack		= rt274_mic_detect,
	.controls		= rt274_snd_controls,
	.num_controls		= ARRAY_SIZE(rt274_snd_controls),
	.dapm_widमाला_लो		= rt274_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt274_dapm_widमाला_लो),
	.dapm_routes		= rt274_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt274_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt274_regmap = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.max_रेजिस्टर = 0x05bfffff,
	.अस्थिर_reg = rt274_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt274_पढ़ोable_रेजिस्टर,
	.reg_ग_लिखो = rl6347a_hw_ग_लिखो,
	.reg_पढ़ो = rl6347a_hw_पढ़ो,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt274_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt274_reg),
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rt274_of_match[] = अणु
	अणु.compatible = "realtek,rt274"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt274_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id rt274_i2c_id[] = अणु
	अणु"rt274", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt274_i2c_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt274_acpi_match[] = अणु
	अणु "10EC0274", 0 पूर्ण,
	अणु "INT34C2", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt274_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक rt274_i2c_probe(काष्ठा i2c_client *i2c,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt274_priv *rt274;

	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	rt274 = devm_kzalloc(&i2c->dev,	माप(*rt274),
				GFP_KERNEL);
	अगर (rt274 == शून्य)
		वापस -ENOMEM;

	rt274->regmap = devm_regmap_init(&i2c->dev, शून्य, i2c, &rt274_regmap);
	अगर (IS_ERR(rt274->regmap)) अणु
		ret = PTR_ERR(rt274->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(rt274->regmap,
		RT274_GET_PARAM(AC_NODE_ROOT, AC_PAR_VENDOR_ID), &val);
	अगर (ret)
		वापस ret;

	अगर (val != RT274_VENDOR_ID) अणु
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt274\n", val);
		वापस -ENODEV;
	पूर्ण

	rt274->index_cache = devm_kmemdup(&i2c->dev, rt274_index_def,
					  माप(rt274_index_def), GFP_KERNEL);
	अगर (!rt274->index_cache)
		वापस -ENOMEM;

	rt274->index_cache_size = INDEX_CACHE_SIZE;
	rt274->i2c = i2c;
	i2c_set_clientdata(i2c, rt274);

	/* reset codec */
	regmap_ग_लिखो(rt274->regmap, RT274_RESET, 0);
	regmap_update_bits(rt274->regmap, 0x1a, 0x4000, 0x4000);

	/* Set Pad PDB is भग्नing */
	regmap_update_bits(rt274->regmap, RT274_PAD_CTRL12, 0x3, 0x0);
	regmap_ग_लिखो(rt274->regmap, RT274_COEF5b_INDEX, 0x01);
	regmap_ग_लिखो(rt274->regmap, RT274_COEF5b_COEF, 0x8540);
	regmap_update_bits(rt274->regmap, 0x6f, 0x0100, 0x0100);
	/* Combo jack स्वतः detect */
	regmap_ग_लिखो(rt274->regmap, 0x4a, 0x201b);
	/* Aux mode off */
	regmap_update_bits(rt274->regmap, 0x6f, 0x3000, 0x2000);
	/* HP DC Calibration */
	regmap_update_bits(rt274->regmap, 0x6f, 0xf, 0x0);
	/* Set NID=58h.Index 00h [15]= 1b; */
	regmap_ग_लिखो(rt274->regmap, RT274_COEF58_INDEX, 0x00);
	regmap_ग_लिखो(rt274->regmap, RT274_COEF58_COEF, 0xb888);
	msleep(500);
	regmap_update_bits(rt274->regmap, 0x6f, 0xf, 0xb);
	regmap_ग_लिखो(rt274->regmap, RT274_COEF58_INDEX, 0x00);
	regmap_ग_लिखो(rt274->regmap, RT274_COEF58_COEF, 0x3888);
	/* Set pin widget */
	regmap_ग_लिखो(rt274->regmap, RT274_SET_PIN_HPO, 0x40);
	regmap_ग_लिखो(rt274->regmap, RT274_SET_PIN_LOUT3, 0x40);
	regmap_ग_लिखो(rt274->regmap, RT274_SET_MIC, 0x20);
	regmap_ग_लिखो(rt274->regmap, RT274_SET_PIN_DMIC1, 0x20);

	regmap_update_bits(rt274->regmap, RT274_I2S_CTRL2, 0xc004, 0x4004);
	regmap_update_bits(rt274->regmap, RT274_EAPD_GPIO_IRQ_CTRL,
				RT274_GPI2_SEL_MASK, RT274_GPI2_SEL_DMIC_CLK);

	/* jack detection */
	regmap_ग_लिखो(rt274->regmap, RT274_UNSOLICITED_HP_OUT, 0x81);
	regmap_ग_लिखो(rt274->regmap, RT274_UNSOLICITED_MIC, 0x82);

	अगर (rt274->i2c->irq) अणु
		ret = request_thपढ़ोed_irq(rt274->i2c->irq, शून्य, rt274_irq,
			IRQF_TRIGGER_HIGH | IRQF_ONESHOT, "rt274", rt274);
		अगर (ret != 0) अणु
			dev_err(&i2c->dev,
				"Failed to reguest IRQ: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				     &soc_component_dev_rt274,
				     rt274_dai, ARRAY_SIZE(rt274_dai));

	वापस ret;
पूर्ण

अटल पूर्णांक rt274_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rt274_priv *rt274 = i2c_get_clientdata(i2c);

	अगर (i2c->irq)
		मुक्त_irq(i2c->irq, rt274);

	वापस 0;
पूर्ण


अटल काष्ठा i2c_driver rt274_i2c_driver = अणु
	.driver = अणु
		   .name = "rt274",
		   .acpi_match_table = ACPI_PTR(rt274_acpi_match),
#अगर_घोषित CONFIG_OF
		   .of_match_table = of_match_ptr(rt274_of_match),
#पूर्ण_अगर
		   पूर्ण,
	.probe = rt274_i2c_probe,
	.हटाओ = rt274_i2c_हटाओ,
	.id_table = rt274_i2c_id,
पूर्ण;

module_i2c_driver(rt274_i2c_driver);

MODULE_DESCRIPTION("ASoC RT274 driver");
MODULE_AUTHOR("Bard Liao <bardliao@realtek.com>");
MODULE_LICENSE("GPL v2");
