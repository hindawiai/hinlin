<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max98088.c -- MAX98088 ALSA SoC Audio driver
 *
 * Copyright 2010 Maxim Integrated Products
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <sound/max98088.h>
#समावेश "max98088.h"

क्रमागत max98088_type अणु
       MAX98088,
       MAX98089,
पूर्ण;

काष्ठा max98088_cdata अणु
       अचिन्हित पूर्णांक rate;
       अचिन्हित पूर्णांक fmt;
       पूर्णांक eq_sel;
पूर्ण;

काष्ठा max98088_priv अणु
	काष्ठा regmap *regmap;
	क्रमागत max98088_type devtype;
	काष्ठा max98088_pdata *pdata;
	काष्ठा clk *mclk;
	अचिन्हित अक्षर mclk_prescaler;
	अचिन्हित पूर्णांक sysclk;
	काष्ठा max98088_cdata dai[2];
	पूर्णांक eq_textcnt;
	स्थिर अक्षर **eq_texts;
	काष्ठा soc_क्रमागत eq_क्रमागत;
	u8 ina_state;
	u8 inb_state;
	अचिन्हित पूर्णांक ex_mode;
	अचिन्हित पूर्णांक digmic;
	अचिन्हित पूर्णांक mic1pre;
	अचिन्हित पूर्णांक mic2pre;
	अचिन्हित पूर्णांक exपंचांगic_mode;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष max98088_reg[] = अणु
	अणु  0xf, 0x00 पूर्ण, /* 0F पूर्णांकerrupt enable */

	अणु 0x10, 0x00 पूर्ण, /* 10 master घड़ी */
	अणु 0x11, 0x00 पूर्ण, /* 11 DAI1 घड़ी mode */
	अणु 0x12, 0x00 पूर्ण, /* 12 DAI1 घड़ी control */
	अणु 0x13, 0x00 पूर्ण, /* 13 DAI1 घड़ी control */
	अणु 0x14, 0x00 पूर्ण, /* 14 DAI1 क्रमmat */
	अणु 0x15, 0x00 पूर्ण, /* 15 DAI1 घड़ी */
	अणु 0x16, 0x00 पूर्ण, /* 16 DAI1 config */
	अणु 0x17, 0x00 पूर्ण, /* 17 DAI1 TDM */
	अणु 0x18, 0x00 पूर्ण, /* 18 DAI1 filters */
	अणु 0x19, 0x00 पूर्ण, /* 19 DAI2 घड़ी mode */
	अणु 0x1a, 0x00 पूर्ण, /* 1A DAI2 घड़ी control */
	अणु 0x1b, 0x00 पूर्ण, /* 1B DAI2 घड़ी control */
	अणु 0x1c, 0x00 पूर्ण, /* 1C DAI2 क्रमmat */
	अणु 0x1d, 0x00 पूर्ण, /* 1D DAI2 घड़ी */
	अणु 0x1e, 0x00 पूर्ण, /* 1E DAI2 config */
	अणु 0x1f, 0x00 पूर्ण, /* 1F DAI2 TDM */

	अणु 0x20, 0x00 पूर्ण, /* 20 DAI2 filters */
	अणु 0x21, 0x00 पूर्ण, /* 21 data config */
	अणु 0x22, 0x00 पूर्ण, /* 22 DAC mixer */
	अणु 0x23, 0x00 पूर्ण, /* 23 left ADC mixer */
	अणु 0x24, 0x00 पूर्ण, /* 24 right ADC mixer */
	अणु 0x25, 0x00 पूर्ण, /* 25 left HP mixer */
	अणु 0x26, 0x00 पूर्ण, /* 26 right HP mixer */
	अणु 0x27, 0x00 पूर्ण, /* 27 HP control */
	अणु 0x28, 0x00 पूर्ण, /* 28 left REC mixer */
	अणु 0x29, 0x00 पूर्ण, /* 29 right REC mixer */
	अणु 0x2a, 0x00 पूर्ण, /* 2A REC control */
	अणु 0x2b, 0x00 पूर्ण, /* 2B left SPK mixer */
	अणु 0x2c, 0x00 पूर्ण, /* 2C right SPK mixer */
	अणु 0x2d, 0x00 पूर्ण, /* 2D SPK control */
	अणु 0x2e, 0x00 पूर्ण, /* 2E sidetone */
	अणु 0x2f, 0x00 पूर्ण, /* 2F DAI1 playback level */

	अणु 0x30, 0x00 पूर्ण, /* 30 DAI1 playback level */
	अणु 0x31, 0x00 पूर्ण, /* 31 DAI2 playback level */
	अणु 0x32, 0x00 पूर्ण, /* 32 DAI2 playbakc level */
	अणु 0x33, 0x00 पूर्ण, /* 33 left ADC level */
	अणु 0x34, 0x00 पूर्ण, /* 34 right ADC level */
	अणु 0x35, 0x00 पूर्ण, /* 35 MIC1 level */
	अणु 0x36, 0x00 पूर्ण, /* 36 MIC2 level */
	अणु 0x37, 0x00 पूर्ण, /* 37 INA level */
	अणु 0x38, 0x00 पूर्ण, /* 38 INB level */
	अणु 0x39, 0x00 पूर्ण, /* 39 left HP volume */
	अणु 0x3a, 0x00 पूर्ण, /* 3A right HP volume */
	अणु 0x3b, 0x00 पूर्ण, /* 3B left REC volume */
	अणु 0x3c, 0x00 पूर्ण, /* 3C right REC volume */
	अणु 0x3d, 0x00 पूर्ण, /* 3D left SPK volume */
	अणु 0x3e, 0x00 पूर्ण, /* 3E right SPK volume */
	अणु 0x3f, 0x00 पूर्ण, /* 3F MIC config */

	अणु 0x40, 0x00 पूर्ण, /* 40 MIC threshold */
	अणु 0x41, 0x00 पूर्ण, /* 41 excursion limiter filter */
	अणु 0x42, 0x00 पूर्ण, /* 42 excursion limiter threshold */
	अणु 0x43, 0x00 पूर्ण, /* 43 ALC */
	अणु 0x44, 0x00 पूर्ण, /* 44 घातer limiter threshold */
	अणु 0x45, 0x00 पूर्ण, /* 45 घातer limiter config */
	अणु 0x46, 0x00 पूर्ण, /* 46 distortion limiter config */
	अणु 0x47, 0x00 पूर्ण, /* 47 audio input */
        अणु 0x48, 0x00 पूर्ण, /* 48 microphone */
	अणु 0x49, 0x00 पूर्ण, /* 49 level control */
	अणु 0x4a, 0x00 पूर्ण, /* 4A bypass चयनes */
	अणु 0x4b, 0x00 पूर्ण, /* 4B jack detect */
	अणु 0x4c, 0x00 पूर्ण, /* 4C input enable */
	अणु 0x4d, 0x00 पूर्ण, /* 4D output enable */
	अणु 0x4e, 0xF0 पूर्ण, /* 4E bias control */
	अणु 0x4f, 0x00 पूर्ण, /* 4F DAC घातer */

	अणु 0x50, 0x0F पूर्ण, /* 50 DAC घातer */
	अणु 0x51, 0x00 पूर्ण, /* 51 प्रणाली */
	अणु 0x52, 0x00 पूर्ण, /* 52 DAI1 EQ1 */
	अणु 0x53, 0x00 पूर्ण, /* 53 DAI1 EQ1 */
	अणु 0x54, 0x00 पूर्ण, /* 54 DAI1 EQ1 */
	अणु 0x55, 0x00 पूर्ण, /* 55 DAI1 EQ1 */
	अणु 0x56, 0x00 पूर्ण, /* 56 DAI1 EQ1 */
	अणु 0x57, 0x00 पूर्ण, /* 57 DAI1 EQ1 */
	अणु 0x58, 0x00 पूर्ण, /* 58 DAI1 EQ1 */
	अणु 0x59, 0x00 पूर्ण, /* 59 DAI1 EQ1 */
	अणु 0x5a, 0x00 पूर्ण, /* 5A DAI1 EQ1 */
	अणु 0x5b, 0x00 पूर्ण, /* 5B DAI1 EQ1 */
	अणु 0x5c, 0x00 पूर्ण, /* 5C DAI1 EQ2 */
	अणु 0x5d, 0x00 पूर्ण, /* 5D DAI1 EQ2 */
	अणु 0x5e, 0x00 पूर्ण, /* 5E DAI1 EQ2 */
	अणु 0x5f, 0x00 पूर्ण, /* 5F DAI1 EQ2 */

	अणु 0x60, 0x00 पूर्ण, /* 60 DAI1 EQ2 */
	अणु 0x61, 0x00 पूर्ण, /* 61 DAI1 EQ2 */
	अणु 0x62, 0x00 पूर्ण, /* 62 DAI1 EQ2 */
	अणु 0x63, 0x00 पूर्ण, /* 63 DAI1 EQ2 */
	अणु 0x64, 0x00 पूर्ण, /* 64 DAI1 EQ2 */
	अणु 0x65, 0x00 पूर्ण, /* 65 DAI1 EQ2 */
	अणु 0x66, 0x00 पूर्ण, /* 66 DAI1 EQ3 */
	अणु 0x67, 0x00 पूर्ण, /* 67 DAI1 EQ3 */
	अणु 0x68, 0x00 पूर्ण, /* 68 DAI1 EQ3 */
	अणु 0x69, 0x00 पूर्ण, /* 69 DAI1 EQ3 */
	अणु 0x6a, 0x00 पूर्ण, /* 6A DAI1 EQ3 */
	अणु 0x6b, 0x00 पूर्ण, /* 6B DAI1 EQ3 */
	अणु 0x6c, 0x00 पूर्ण, /* 6C DAI1 EQ3 */
	अणु 0x6d, 0x00 पूर्ण, /* 6D DAI1 EQ3 */
	अणु 0x6e, 0x00 पूर्ण, /* 6E DAI1 EQ3 */
	अणु 0x6f, 0x00 पूर्ण, /* 6F DAI1 EQ3 */

	अणु 0x70, 0x00 पूर्ण, /* 70 DAI1 EQ4 */
	अणु 0x71, 0x00 पूर्ण, /* 71 DAI1 EQ4 */
	अणु 0x72, 0x00 पूर्ण, /* 72 DAI1 EQ4 */
	अणु 0x73, 0x00 पूर्ण, /* 73 DAI1 EQ4 */
	अणु 0x74, 0x00 पूर्ण, /* 74 DAI1 EQ4 */
	अणु 0x75, 0x00 पूर्ण, /* 75 DAI1 EQ4 */
	अणु 0x76, 0x00 पूर्ण, /* 76 DAI1 EQ4 */
	अणु 0x77, 0x00 पूर्ण, /* 77 DAI1 EQ4 */
	अणु 0x78, 0x00 पूर्ण, /* 78 DAI1 EQ4 */
	अणु 0x79, 0x00 पूर्ण, /* 79 DAI1 EQ4 */
	अणु 0x7a, 0x00 पूर्ण, /* 7A DAI1 EQ5 */
	अणु 0x7b, 0x00 पूर्ण, /* 7B DAI1 EQ5 */
	अणु 0x7c, 0x00 पूर्ण, /* 7C DAI1 EQ5 */
	अणु 0x7d, 0x00 पूर्ण, /* 7D DAI1 EQ5 */
	अणु 0x7e, 0x00 पूर्ण, /* 7E DAI1 EQ5 */
	अणु 0x7f, 0x00 पूर्ण, /* 7F DAI1 EQ5 */

	अणु 0x80, 0x00 पूर्ण, /* 80 DAI1 EQ5 */
	अणु 0x81, 0x00 पूर्ण, /* 81 DAI1 EQ5 */
	अणु 0x82, 0x00 पूर्ण, /* 82 DAI1 EQ5 */
	अणु 0x83, 0x00 पूर्ण, /* 83 DAI1 EQ5 */
	अणु 0x84, 0x00 पूर्ण, /* 84 DAI2 EQ1 */
	अणु 0x85, 0x00 पूर्ण, /* 85 DAI2 EQ1 */
	अणु 0x86, 0x00 पूर्ण, /* 86 DAI2 EQ1 */
	अणु 0x87, 0x00 पूर्ण, /* 87 DAI2 EQ1 */
	अणु 0x88, 0x00 पूर्ण, /* 88 DAI2 EQ1 */
	अणु 0x89, 0x00 पूर्ण, /* 89 DAI2 EQ1 */
	अणु 0x8a, 0x00 पूर्ण, /* 8A DAI2 EQ1 */
	अणु 0x8b, 0x00 पूर्ण, /* 8B DAI2 EQ1 */
	अणु 0x8c, 0x00 पूर्ण, /* 8C DAI2 EQ1 */
	अणु 0x8d, 0x00 पूर्ण, /* 8D DAI2 EQ1 */
	अणु 0x8e, 0x00 पूर्ण, /* 8E DAI2 EQ2 */
	अणु 0x8f, 0x00 पूर्ण, /* 8F DAI2 EQ2 */

	अणु 0x90, 0x00 पूर्ण, /* 90 DAI2 EQ2 */
	अणु 0x91, 0x00 पूर्ण, /* 91 DAI2 EQ2 */
	अणु 0x92, 0x00 पूर्ण, /* 92 DAI2 EQ2 */
	अणु 0x93, 0x00 पूर्ण, /* 93 DAI2 EQ2 */
	अणु 0x94, 0x00 पूर्ण, /* 94 DAI2 EQ2 */
	अणु 0x95, 0x00 पूर्ण, /* 95 DAI2 EQ2 */
	अणु 0x96, 0x00 पूर्ण, /* 96 DAI2 EQ2 */
	अणु 0x97, 0x00 पूर्ण, /* 97 DAI2 EQ2 */
	अणु 0x98, 0x00 पूर्ण, /* 98 DAI2 EQ3 */
	अणु 0x99, 0x00 पूर्ण, /* 99 DAI2 EQ3 */
	अणु 0x9a, 0x00 पूर्ण, /* 9A DAI2 EQ3 */
        अणु 0x9b, 0x00 पूर्ण, /* 9B DAI2 EQ3 */
	अणु 0x9c, 0x00 पूर्ण, /* 9C DAI2 EQ3 */
	अणु 0x9d, 0x00 पूर्ण, /* 9D DAI2 EQ3 */
	अणु 0x9e, 0x00 पूर्ण, /* 9E DAI2 EQ3 */
	अणु 0x9f, 0x00 पूर्ण, /* 9F DAI2 EQ3 */

	अणु 0xa0, 0x00 पूर्ण, /* A0 DAI2 EQ3 */
	अणु 0xa1, 0x00 पूर्ण, /* A1 DAI2 EQ3 */
	अणु 0xa2, 0x00 पूर्ण, /* A2 DAI2 EQ4 */
	अणु 0xa3, 0x00 पूर्ण, /* A3 DAI2 EQ4 */
	अणु 0xa4, 0x00 पूर्ण, /* A4 DAI2 EQ4 */
	अणु 0xa5, 0x00 पूर्ण, /* A5 DAI2 EQ4 */
	अणु 0xa6, 0x00 पूर्ण, /* A6 DAI2 EQ4 */
	अणु 0xa7, 0x00 पूर्ण, /* A7 DAI2 EQ4 */
	अणु 0xa8, 0x00 पूर्ण, /* A8 DAI2 EQ4 */
	अणु 0xa9, 0x00 पूर्ण, /* A9 DAI2 EQ4 */
	अणु 0xaa, 0x00 पूर्ण, /* AA DAI2 EQ4 */
	अणु 0xab, 0x00 पूर्ण, /* AB DAI2 EQ4 */
	अणु 0xac, 0x00 पूर्ण, /* AC DAI2 EQ5 */
	अणु 0xad, 0x00 पूर्ण, /* AD DAI2 EQ5 */
	अणु 0xae, 0x00 पूर्ण, /* AE DAI2 EQ5 */
	अणु 0xaf, 0x00 पूर्ण, /* AF DAI2 EQ5 */

	अणु 0xb0, 0x00 पूर्ण, /* B0 DAI2 EQ5 */
	अणु 0xb1, 0x00 पूर्ण, /* B1 DAI2 EQ5 */
	अणु 0xb2, 0x00 पूर्ण, /* B2 DAI2 EQ5 */
	अणु 0xb3, 0x00 पूर्ण, /* B3 DAI2 EQ5 */
	अणु 0xb4, 0x00 पूर्ण, /* B4 DAI2 EQ5 */
	अणु 0xb5, 0x00 पूर्ण, /* B5 DAI2 EQ5 */
	अणु 0xb6, 0x00 पूर्ण, /* B6 DAI1 biquad */
	अणु 0xb7, 0x00 पूर्ण, /* B7 DAI1 biquad */
	अणु 0xb8 ,0x00 पूर्ण, /* B8 DAI1 biquad */
	अणु 0xb9, 0x00 पूर्ण, /* B9 DAI1 biquad */
	अणु 0xba, 0x00 पूर्ण, /* BA DAI1 biquad */
	अणु 0xbb, 0x00 पूर्ण, /* BB DAI1 biquad */
	अणु 0xbc, 0x00 पूर्ण, /* BC DAI1 biquad */
	अणु 0xbd, 0x00 पूर्ण, /* BD DAI1 biquad */
	अणु 0xbe, 0x00 पूर्ण, /* BE DAI1 biquad */
        अणु 0xbf, 0x00 पूर्ण, /* BF DAI1 biquad */

	अणु 0xc0, 0x00 पूर्ण, /* C0 DAI2 biquad */
	अणु 0xc1, 0x00 पूर्ण, /* C1 DAI2 biquad */
	अणु 0xc2, 0x00 पूर्ण, /* C2 DAI2 biquad */
	अणु 0xc3, 0x00 पूर्ण, /* C3 DAI2 biquad */
	अणु 0xc4, 0x00 पूर्ण, /* C4 DAI2 biquad */
	अणु 0xc5, 0x00 पूर्ण, /* C5 DAI2 biquad */
	अणु 0xc6, 0x00 पूर्ण, /* C6 DAI2 biquad */
	अणु 0xc7, 0x00 पूर्ण, /* C7 DAI2 biquad */
	अणु 0xc8, 0x00 पूर्ण, /* C8 DAI2 biquad */
	अणु 0xc9, 0x00 पूर्ण, /* C9 DAI2 biquad */
पूर्ण;

अटल bool max98088_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल M98088_REG_00_IRQ_STATUS ... 0xC9:
	हाल M98088_REG_FF_REV_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max98088_ग_लिखोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल M98088_REG_03_BATTERY_VOLTAGE ... 0xC9:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max98088_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल M98088_REG_00_IRQ_STATUS ... M98088_REG_03_BATTERY_VOLTAGE:
	हाल M98088_REG_FF_REV_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config max98088_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.पढ़ोable_reg = max98088_पढ़ोable_रेजिस्टर,
	.ग_लिखोable_reg = max98088_ग_लिखोable_रेजिस्टर,
	.अस्थिर_reg = max98088_अस्थिर_रेजिस्टर,
	.max_रेजिस्टर = 0xff,

	.reg_शेषs = max98088_reg,
	.num_reg_शेषs = ARRAY_SIZE(max98088_reg),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/*
 * Load equalizer DSP coefficient configurations रेजिस्टरs
 */
अटल व्योम m98088_eq_band(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक dai,
                   अचिन्हित पूर्णांक band, u16 *coefs)
अणु
       अचिन्हित पूर्णांक eq_reg;
       अचिन्हित पूर्णांक i;

	अगर (WARN_ON(band > 4) ||
	    WARN_ON(dai > 1))
		वापस;

       /* Load the base रेजिस्टर address */
       eq_reg = dai ? M98088_REG_84_DAI2_EQ_BASE : M98088_REG_52_DAI1_EQ_BASE;

       /* Add the band address offset, note adjusपंचांगent क्रम word address */
       eq_reg += band * (M98088_COEFS_PER_BAND << 1);

       /* Step through the रेजिस्टरs and coefs */
       क्रम (i = 0; i < M98088_COEFS_PER_BAND; i++) अणु
               snd_soc_component_ग_लिखो(component, eq_reg++, M98088_BYTE1(coefs[i]));
               snd_soc_component_ग_लिखो(component, eq_reg++, M98088_BYTE0(coefs[i]));
       पूर्ण
पूर्ण

/*
 * Excursion limiter modes
 */
अटल स्थिर अक्षर *max98088_exmode_texts[] = अणु
       "Off", "100Hz", "400Hz", "600Hz", "800Hz", "1000Hz", "200-400Hz",
       "400-600Hz", "400-800Hz",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max98088_exmode_values[] = अणु
       0x00, 0x43, 0x10, 0x20, 0x30, 0x40, 0x11, 0x22, 0x32
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(max98088_exmode_क्रमागत,
				  M98088_REG_41_SPKDHP, 0, 127,
				  max98088_exmode_texts,
				  max98088_exmode_values);

अटल स्थिर अक्षर *max98088_ex_thresh[] = अणु /* volts PP */
       "0.6", "1.2", "1.8", "2.4", "3.0", "3.6", "4.2", "4.8"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(max98088_ex_thresh_क्रमागत,
			    M98088_REG_42_SPKDHP_THRESH, 0,
			    max98088_ex_thresh);

अटल स्थिर अक्षर *max98088_fltr_mode[] = अणु"Voice", "Music" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(max98088_filter_mode_क्रमागत,
			    M98088_REG_18_DAI1_FILTERS, 7,
			    max98088_fltr_mode);

अटल स्थिर अक्षर *max98088_exपंचांगic_text[] = अणु "None", "MIC1", "MIC2" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98088_exपंचांगic_क्रमागत,
			    M98088_REG_48_CFG_MIC, 0,
			    max98088_exपंचांगic_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98088_exपंचांगic_mux =
       SOC_DAPM_ENUM("External MIC Mux", max98088_exपंचांगic_क्रमागत);

अटल स्थिर अक्षर *max98088_dai1_fltr[] = अणु
       "Off", "fc=258/fs=16k", "fc=500/fs=16k",
       "fc=258/fs=8k", "fc=500/fs=8k", "fc=200"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(max98088_dai1_dac_filter_क्रमागत,
			    M98088_REG_18_DAI1_FILTERS, 0,
			    max98088_dai1_fltr);
अटल SOC_ENUM_SINGLE_DECL(max98088_dai1_adc_filter_क्रमागत,
			    M98088_REG_18_DAI1_FILTERS, 4,
			    max98088_dai1_fltr);

अटल पूर्णांक max98088_mic1pre_set(काष्ठा snd_kcontrol *kcontrol,
                               काष्ठा snd_ctl_elem_value *ucontrol)
अणु
       काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       अचिन्हित पूर्णांक sel = ucontrol->value.पूर्णांकeger.value[0];

       max98088->mic1pre = sel;
       snd_soc_component_update_bits(component, M98088_REG_35_LVL_MIC1, M98088_MICPRE_MASK,
               (1+sel)<<M98088_MICPRE_SHIFT);

       वापस 0;
पूर्ण

अटल पूर्णांक max98088_mic1pre_get(काष्ठा snd_kcontrol *kcontrol,
                               काष्ठा snd_ctl_elem_value *ucontrol)
अणु
       काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);

       ucontrol->value.पूर्णांकeger.value[0] = max98088->mic1pre;
       वापस 0;
पूर्ण

अटल पूर्णांक max98088_mic2pre_set(काष्ठा snd_kcontrol *kcontrol,
                               काष्ठा snd_ctl_elem_value *ucontrol)
अणु
       काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       अचिन्हित पूर्णांक sel = ucontrol->value.पूर्णांकeger.value[0];

       max98088->mic2pre = sel;
       snd_soc_component_update_bits(component, M98088_REG_36_LVL_MIC2, M98088_MICPRE_MASK,
               (1+sel)<<M98088_MICPRE_SHIFT);

       वापस 0;
पूर्ण

अटल पूर्णांक max98088_mic2pre_get(काष्ठा snd_kcontrol *kcontrol,
                               काष्ठा snd_ctl_elem_value *ucontrol)
अणु
       काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);

       ucontrol->value.पूर्णांकeger.value[0] = max98088->mic2pre;
       वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_RANGE(max98088_micboost_tlv,
	0, 1, TLV_DB_SCALE_ITEM(0, 2000, 0),
	2, 2, TLV_DB_SCALE_ITEM(3000, 0, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98088_hp_tlv,
	0, 6, TLV_DB_SCALE_ITEM(-6700, 400, 0),
	7, 14, TLV_DB_SCALE_ITEM(-4000, 300, 0),
	15, 21, TLV_DB_SCALE_ITEM(-1700, 200, 0),
	22, 27, TLV_DB_SCALE_ITEM(-400, 100, 0),
	28, 31, TLV_DB_SCALE_ITEM(150, 50, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98088_spk_tlv,
	0, 6, TLV_DB_SCALE_ITEM(-6200, 400, 0),
	7, 14, TLV_DB_SCALE_ITEM(-3500, 300, 0),
	15, 21, TLV_DB_SCALE_ITEM(-1200, 200, 0),
	22, 27, TLV_DB_SCALE_ITEM(100, 100, 0),
	28, 31, TLV_DB_SCALE_ITEM(650, 50, 0)
);

अटल स्थिर काष्ठा snd_kcontrol_new max98088_snd_controls[] = अणु

	SOC_DOUBLE_R_TLV("Headphone Volume", M98088_REG_39_LVL_HP_L,
			 M98088_REG_3A_LVL_HP_R, 0, 31, 0, max98088_hp_tlv),
	SOC_DOUBLE_R_TLV("Speaker Volume", M98088_REG_3D_LVL_SPK_L,
			 M98088_REG_3E_LVL_SPK_R, 0, 31, 0, max98088_spk_tlv),
	SOC_DOUBLE_R_TLV("Receiver Volume", M98088_REG_3B_LVL_REC_L,
			 M98088_REG_3C_LVL_REC_R, 0, 31, 0, max98088_spk_tlv),

       SOC_DOUBLE_R("Headphone Switch", M98088_REG_39_LVL_HP_L,
               M98088_REG_3A_LVL_HP_R, 7, 1, 1),
       SOC_DOUBLE_R("Speaker Switch", M98088_REG_3D_LVL_SPK_L,
               M98088_REG_3E_LVL_SPK_R, 7, 1, 1),
       SOC_DOUBLE_R("Receiver Switch", M98088_REG_3B_LVL_REC_L,
               M98088_REG_3C_LVL_REC_R, 7, 1, 1),

       SOC_SINGLE("MIC1 Volume", M98088_REG_35_LVL_MIC1, 0, 31, 1),
       SOC_SINGLE("MIC2 Volume", M98088_REG_36_LVL_MIC2, 0, 31, 1),

       SOC_SINGLE_EXT_TLV("MIC1 Boost Volume",
                       M98088_REG_35_LVL_MIC1, 5, 2, 0,
                       max98088_mic1pre_get, max98088_mic1pre_set,
                       max98088_micboost_tlv),
       SOC_SINGLE_EXT_TLV("MIC2 Boost Volume",
                       M98088_REG_36_LVL_MIC2, 5, 2, 0,
                       max98088_mic2pre_get, max98088_mic2pre_set,
                       max98088_micboost_tlv),

       SOC_SINGLE("INA Volume", M98088_REG_37_LVL_INA, 0, 7, 1),
       SOC_SINGLE("INB Volume", M98088_REG_38_LVL_INB, 0, 7, 1),

       SOC_SINGLE("ADCL Volume", M98088_REG_33_LVL_ADC_L, 0, 15, 0),
       SOC_SINGLE("ADCR Volume", M98088_REG_34_LVL_ADC_R, 0, 15, 0),

       SOC_SINGLE("ADCL Boost Volume", M98088_REG_33_LVL_ADC_L, 4, 3, 0),
       SOC_SINGLE("ADCR Boost Volume", M98088_REG_34_LVL_ADC_R, 4, 3, 0),

       SOC_SINGLE("EQ1 Switch", M98088_REG_49_CFG_LEVEL, 0, 1, 0),
       SOC_SINGLE("EQ2 Switch", M98088_REG_49_CFG_LEVEL, 1, 1, 0),

       SOC_ENUM("EX Limiter Mode", max98088_exmode_क्रमागत),
       SOC_ENUM("EX Limiter Threshold", max98088_ex_thresh_क्रमागत),

       SOC_ENUM("DAI1 Filter Mode", max98088_filter_mode_क्रमागत),
       SOC_ENUM("DAI1 DAC Filter", max98088_dai1_dac_filter_क्रमागत),
       SOC_ENUM("DAI1 ADC Filter", max98088_dai1_adc_filter_क्रमागत),
       SOC_SINGLE("DAI2 DC Block Switch", M98088_REG_20_DAI2_FILTERS,
               0, 1, 0),

       SOC_SINGLE("ALC Switch", M98088_REG_43_SPKALC_COMP, 7, 1, 0),
       SOC_SINGLE("ALC Threshold", M98088_REG_43_SPKALC_COMP, 0, 7, 0),
       SOC_SINGLE("ALC Multiband", M98088_REG_43_SPKALC_COMP, 3, 1, 0),
       SOC_SINGLE("ALC Release Time", M98088_REG_43_SPKALC_COMP, 4, 7, 0),

       SOC_SINGLE("PWR Limiter Threshold", M98088_REG_44_PWRLMT_CFG,
               4, 15, 0),
       SOC_SINGLE("PWR Limiter Weight", M98088_REG_44_PWRLMT_CFG, 0, 7, 0),
       SOC_SINGLE("PWR Limiter Time1", M98088_REG_45_PWRLMT_TIME, 0, 15, 0),
       SOC_SINGLE("PWR Limiter Time2", M98088_REG_45_PWRLMT_TIME, 4, 15, 0),

       SOC_SINGLE("THD Limiter Threshold", M98088_REG_46_THDLMT_CFG, 4, 15, 0),
       SOC_SINGLE("THD Limiter Time", M98088_REG_46_THDLMT_CFG, 0, 7, 0),
पूर्ण;

/* Left speaker mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98088_left_speaker_mixer_controls[] = अणु
       SOC_DAPM_SINGLE("Left DAC1 Switch", M98088_REG_2B_MIX_SPK_LEFT, 0, 1, 0),
       SOC_DAPM_SINGLE("Right DAC1 Switch", M98088_REG_2B_MIX_SPK_LEFT, 7, 1, 0),
       SOC_DAPM_SINGLE("Left DAC2 Switch", M98088_REG_2B_MIX_SPK_LEFT, 0, 1, 0),
       SOC_DAPM_SINGLE("Right DAC2 Switch", M98088_REG_2B_MIX_SPK_LEFT, 7, 1, 0),
       SOC_DAPM_SINGLE("MIC1 Switch", M98088_REG_2B_MIX_SPK_LEFT, 5, 1, 0),
       SOC_DAPM_SINGLE("MIC2 Switch", M98088_REG_2B_MIX_SPK_LEFT, 6, 1, 0),
       SOC_DAPM_SINGLE("INA1 Switch", M98088_REG_2B_MIX_SPK_LEFT, 1, 1, 0),
       SOC_DAPM_SINGLE("INA2 Switch", M98088_REG_2B_MIX_SPK_LEFT, 2, 1, 0),
       SOC_DAPM_SINGLE("INB1 Switch", M98088_REG_2B_MIX_SPK_LEFT, 3, 1, 0),
       SOC_DAPM_SINGLE("INB2 Switch", M98088_REG_2B_MIX_SPK_LEFT, 4, 1, 0),
पूर्ण;

/* Right speaker mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98088_right_speaker_mixer_controls[] = अणु
       SOC_DAPM_SINGLE("Left DAC1 Switch", M98088_REG_2C_MIX_SPK_RIGHT, 7, 1, 0),
       SOC_DAPM_SINGLE("Right DAC1 Switch", M98088_REG_2C_MIX_SPK_RIGHT, 0, 1, 0),
       SOC_DAPM_SINGLE("Left DAC2 Switch", M98088_REG_2C_MIX_SPK_RIGHT, 7, 1, 0),
       SOC_DAPM_SINGLE("Right DAC2 Switch", M98088_REG_2C_MIX_SPK_RIGHT, 0, 1, 0),
       SOC_DAPM_SINGLE("MIC1 Switch", M98088_REG_2C_MIX_SPK_RIGHT, 5, 1, 0),
       SOC_DAPM_SINGLE("MIC2 Switch", M98088_REG_2C_MIX_SPK_RIGHT, 6, 1, 0),
       SOC_DAPM_SINGLE("INA1 Switch", M98088_REG_2C_MIX_SPK_RIGHT, 1, 1, 0),
       SOC_DAPM_SINGLE("INA2 Switch", M98088_REG_2C_MIX_SPK_RIGHT, 2, 1, 0),
       SOC_DAPM_SINGLE("INB1 Switch", M98088_REG_2C_MIX_SPK_RIGHT, 3, 1, 0),
       SOC_DAPM_SINGLE("INB2 Switch", M98088_REG_2C_MIX_SPK_RIGHT, 4, 1, 0),
पूर्ण;

/* Left headphone mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98088_left_hp_mixer_controls[] = अणु
       SOC_DAPM_SINGLE("Left DAC1 Switch", M98088_REG_25_MIX_HP_LEFT, 0, 1, 0),
       SOC_DAPM_SINGLE("Right DAC1 Switch", M98088_REG_25_MIX_HP_LEFT, 7, 1, 0),
       SOC_DAPM_SINGLE("Left DAC2 Switch", M98088_REG_25_MIX_HP_LEFT, 0, 1, 0),
       SOC_DAPM_SINGLE("Right DAC2 Switch", M98088_REG_25_MIX_HP_LEFT, 7, 1, 0),
       SOC_DAPM_SINGLE("MIC1 Switch", M98088_REG_25_MIX_HP_LEFT, 5, 1, 0),
       SOC_DAPM_SINGLE("MIC2 Switch", M98088_REG_25_MIX_HP_LEFT, 6, 1, 0),
       SOC_DAPM_SINGLE("INA1 Switch", M98088_REG_25_MIX_HP_LEFT, 1, 1, 0),
       SOC_DAPM_SINGLE("INA2 Switch", M98088_REG_25_MIX_HP_LEFT, 2, 1, 0),
       SOC_DAPM_SINGLE("INB1 Switch", M98088_REG_25_MIX_HP_LEFT, 3, 1, 0),
       SOC_DAPM_SINGLE("INB2 Switch", M98088_REG_25_MIX_HP_LEFT, 4, 1, 0),
पूर्ण;

/* Right headphone mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98088_right_hp_mixer_controls[] = अणु
       SOC_DAPM_SINGLE("Left DAC1 Switch", M98088_REG_26_MIX_HP_RIGHT, 7, 1, 0),
       SOC_DAPM_SINGLE("Right DAC1 Switch", M98088_REG_26_MIX_HP_RIGHT, 0, 1, 0),
       SOC_DAPM_SINGLE("Left DAC2 Switch", M98088_REG_26_MIX_HP_RIGHT, 7, 1, 0),
       SOC_DAPM_SINGLE("Right DAC2 Switch", M98088_REG_26_MIX_HP_RIGHT, 0, 1, 0),
       SOC_DAPM_SINGLE("MIC1 Switch", M98088_REG_26_MIX_HP_RIGHT, 5, 1, 0),
       SOC_DAPM_SINGLE("MIC2 Switch", M98088_REG_26_MIX_HP_RIGHT, 6, 1, 0),
       SOC_DAPM_SINGLE("INA1 Switch", M98088_REG_26_MIX_HP_RIGHT, 1, 1, 0),
       SOC_DAPM_SINGLE("INA2 Switch", M98088_REG_26_MIX_HP_RIGHT, 2, 1, 0),
       SOC_DAPM_SINGLE("INB1 Switch", M98088_REG_26_MIX_HP_RIGHT, 3, 1, 0),
       SOC_DAPM_SINGLE("INB2 Switch", M98088_REG_26_MIX_HP_RIGHT, 4, 1, 0),
पूर्ण;

/* Left earpiece/receiver mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98088_left_rec_mixer_controls[] = अणु
       SOC_DAPM_SINGLE("Left DAC1 Switch", M98088_REG_28_MIX_REC_LEFT, 0, 1, 0),
       SOC_DAPM_SINGLE("Right DAC1 Switch", M98088_REG_28_MIX_REC_LEFT, 7, 1, 0),
       SOC_DAPM_SINGLE("Left DAC2 Switch", M98088_REG_28_MIX_REC_LEFT, 0, 1, 0),
       SOC_DAPM_SINGLE("Right DAC2 Switch", M98088_REG_28_MIX_REC_LEFT, 7, 1, 0),
       SOC_DAPM_SINGLE("MIC1 Switch", M98088_REG_28_MIX_REC_LEFT, 5, 1, 0),
       SOC_DAPM_SINGLE("MIC2 Switch", M98088_REG_28_MIX_REC_LEFT, 6, 1, 0),
       SOC_DAPM_SINGLE("INA1 Switch", M98088_REG_28_MIX_REC_LEFT, 1, 1, 0),
       SOC_DAPM_SINGLE("INA2 Switch", M98088_REG_28_MIX_REC_LEFT, 2, 1, 0),
       SOC_DAPM_SINGLE("INB1 Switch", M98088_REG_28_MIX_REC_LEFT, 3, 1, 0),
       SOC_DAPM_SINGLE("INB2 Switch", M98088_REG_28_MIX_REC_LEFT, 4, 1, 0),
पूर्ण;

/* Right earpiece/receiver mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98088_right_rec_mixer_controls[] = अणु
       SOC_DAPM_SINGLE("Left DAC1 Switch", M98088_REG_29_MIX_REC_RIGHT, 7, 1, 0),
       SOC_DAPM_SINGLE("Right DAC1 Switch", M98088_REG_29_MIX_REC_RIGHT, 0, 1, 0),
       SOC_DAPM_SINGLE("Left DAC2 Switch", M98088_REG_29_MIX_REC_RIGHT, 7, 1, 0),
       SOC_DAPM_SINGLE("Right DAC2 Switch", M98088_REG_29_MIX_REC_RIGHT, 0, 1, 0),
       SOC_DAPM_SINGLE("MIC1 Switch", M98088_REG_29_MIX_REC_RIGHT, 5, 1, 0),
       SOC_DAPM_SINGLE("MIC2 Switch", M98088_REG_29_MIX_REC_RIGHT, 6, 1, 0),
       SOC_DAPM_SINGLE("INA1 Switch", M98088_REG_29_MIX_REC_RIGHT, 1, 1, 0),
       SOC_DAPM_SINGLE("INA2 Switch", M98088_REG_29_MIX_REC_RIGHT, 2, 1, 0),
       SOC_DAPM_SINGLE("INB1 Switch", M98088_REG_29_MIX_REC_RIGHT, 3, 1, 0),
       SOC_DAPM_SINGLE("INB2 Switch", M98088_REG_29_MIX_REC_RIGHT, 4, 1, 0),
पूर्ण;

/* Left ADC mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98088_left_ADC_mixer_controls[] = अणु
       SOC_DAPM_SINGLE("MIC1 Switch", M98088_REG_23_MIX_ADC_LEFT, 7, 1, 0),
       SOC_DAPM_SINGLE("MIC2 Switch", M98088_REG_23_MIX_ADC_LEFT, 6, 1, 0),
       SOC_DAPM_SINGLE("INA1 Switch", M98088_REG_23_MIX_ADC_LEFT, 3, 1, 0),
       SOC_DAPM_SINGLE("INA2 Switch", M98088_REG_23_MIX_ADC_LEFT, 2, 1, 0),
       SOC_DAPM_SINGLE("INB1 Switch", M98088_REG_23_MIX_ADC_LEFT, 1, 1, 0),
       SOC_DAPM_SINGLE("INB2 Switch", M98088_REG_23_MIX_ADC_LEFT, 0, 1, 0),
पूर्ण;

/* Right ADC mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98088_right_ADC_mixer_controls[] = अणु
       SOC_DAPM_SINGLE("MIC1 Switch", M98088_REG_24_MIX_ADC_RIGHT, 7, 1, 0),
       SOC_DAPM_SINGLE("MIC2 Switch", M98088_REG_24_MIX_ADC_RIGHT, 6, 1, 0),
       SOC_DAPM_SINGLE("INA1 Switch", M98088_REG_24_MIX_ADC_RIGHT, 3, 1, 0),
       SOC_DAPM_SINGLE("INA2 Switch", M98088_REG_24_MIX_ADC_RIGHT, 2, 1, 0),
       SOC_DAPM_SINGLE("INB1 Switch", M98088_REG_24_MIX_ADC_RIGHT, 1, 1, 0),
       SOC_DAPM_SINGLE("INB2 Switch", M98088_REG_24_MIX_ADC_RIGHT, 0, 1, 0),
पूर्ण;

अटल पूर्णांक max98088_mic_event(काष्ठा snd_soc_dapm_widget *w,
                            काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
       काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);

       चयन (event) अणु
       हाल SND_SOC_DAPM_POST_PMU:
               अगर (w->reg == M98088_REG_35_LVL_MIC1) अणु
                       snd_soc_component_update_bits(component, w->reg, M98088_MICPRE_MASK,
                               (1+max98088->mic1pre)<<M98088_MICPRE_SHIFT);
               पूर्ण अन्यथा अणु
                       snd_soc_component_update_bits(component, w->reg, M98088_MICPRE_MASK,
                               (1+max98088->mic2pre)<<M98088_MICPRE_SHIFT);
               पूर्ण
               अवरोध;
       हाल SND_SOC_DAPM_POST_PMD:
               snd_soc_component_update_bits(component, w->reg, M98088_MICPRE_MASK, 0);
               अवरोध;
       शेष:
               वापस -EINVAL;
       पूर्ण

       वापस 0;
पूर्ण

/*
 * The line inमाला_दो are 2-channel stereo inमाला_दो with the left
 * and right channels sharing a common PGA घातer control संकेत.
 */
अटल पूर्णांक max98088_line_pga(काष्ठा snd_soc_dapm_widget *w,
                            पूर्णांक event, पूर्णांक line, u8 channel)
अणु
       काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       u8 *state;

	अगर (WARN_ON(!(channel == 1 || channel == 2)))
		वापस -EINVAL;

       चयन (line) अणु
       हाल LINE_INA:
               state = &max98088->ina_state;
               अवरोध;
       हाल LINE_INB:
               state = &max98088->inb_state;
               अवरोध;
       शेष:
               वापस -EINVAL;
       पूर्ण

       चयन (event) अणु
       हाल SND_SOC_DAPM_POST_PMU:
               *state |= channel;
               snd_soc_component_update_bits(component, w->reg,
                       (1 << w->shअगरt), (1 << w->shअगरt));
               अवरोध;
       हाल SND_SOC_DAPM_POST_PMD:
               *state &= ~channel;
               अगर (*state == 0) अणु
                       snd_soc_component_update_bits(component, w->reg,
                               (1 << w->shअगरt), 0);
               पूर्ण
               अवरोध;
       शेष:
               वापस -EINVAL;
       पूर्ण

       वापस 0;
पूर्ण

अटल पूर्णांक max98088_pga_ina1_event(काष्ठा snd_soc_dapm_widget *w,
                                  काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
       वापस max98088_line_pga(w, event, LINE_INA, 1);
पूर्ण

अटल पूर्णांक max98088_pga_ina2_event(काष्ठा snd_soc_dapm_widget *w,
                                  काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
       वापस max98088_line_pga(w, event, LINE_INA, 2);
पूर्ण

अटल पूर्णांक max98088_pga_inb1_event(काष्ठा snd_soc_dapm_widget *w,
                                  काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
       वापस max98088_line_pga(w, event, LINE_INB, 1);
पूर्ण

अटल पूर्णांक max98088_pga_inb2_event(काष्ठा snd_soc_dapm_widget *w,
                                  काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
       वापस max98088_line_pga(w, event, LINE_INB, 2);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget max98088_dapm_widमाला_लो[] = अणु

       SND_SOC_DAPM_ADC("ADCL", "HiFi Capture", M98088_REG_4C_PWR_EN_IN, 1, 0),
       SND_SOC_DAPM_ADC("ADCR", "HiFi Capture", M98088_REG_4C_PWR_EN_IN, 0, 0),

       SND_SOC_DAPM_DAC("DACL1", "HiFi Playback",
               M98088_REG_4D_PWR_EN_OUT, 1, 0),
       SND_SOC_DAPM_DAC("DACR1", "HiFi Playback",
               M98088_REG_4D_PWR_EN_OUT, 0, 0),
       SND_SOC_DAPM_DAC("DACL2", "Aux Playback",
               M98088_REG_4D_PWR_EN_OUT, 1, 0),
       SND_SOC_DAPM_DAC("DACR2", "Aux Playback",
               M98088_REG_4D_PWR_EN_OUT, 0, 0),

       SND_SOC_DAPM_PGA("HP Left Out", M98088_REG_4D_PWR_EN_OUT,
               7, 0, शून्य, 0),
       SND_SOC_DAPM_PGA("HP Right Out", M98088_REG_4D_PWR_EN_OUT,
               6, 0, शून्य, 0),

       SND_SOC_DAPM_PGA("SPK Left Out", M98088_REG_4D_PWR_EN_OUT,
               5, 0, शून्य, 0),
       SND_SOC_DAPM_PGA("SPK Right Out", M98088_REG_4D_PWR_EN_OUT,
               4, 0, शून्य, 0),

       SND_SOC_DAPM_PGA("REC Left Out", M98088_REG_4D_PWR_EN_OUT,
               3, 0, शून्य, 0),
       SND_SOC_DAPM_PGA("REC Right Out", M98088_REG_4D_PWR_EN_OUT,
               2, 0, शून्य, 0),

       SND_SOC_DAPM_MUX("External MIC", SND_SOC_NOPM, 0, 0,
               &max98088_exपंचांगic_mux),

       SND_SOC_DAPM_MIXER("Left HP Mixer", SND_SOC_NOPM, 0, 0,
               &max98088_left_hp_mixer_controls[0],
               ARRAY_SIZE(max98088_left_hp_mixer_controls)),

       SND_SOC_DAPM_MIXER("Right HP Mixer", SND_SOC_NOPM, 0, 0,
               &max98088_right_hp_mixer_controls[0],
               ARRAY_SIZE(max98088_right_hp_mixer_controls)),

       SND_SOC_DAPM_MIXER("Left SPK Mixer", SND_SOC_NOPM, 0, 0,
               &max98088_left_speaker_mixer_controls[0],
               ARRAY_SIZE(max98088_left_speaker_mixer_controls)),

       SND_SOC_DAPM_MIXER("Right SPK Mixer", SND_SOC_NOPM, 0, 0,
               &max98088_right_speaker_mixer_controls[0],
               ARRAY_SIZE(max98088_right_speaker_mixer_controls)),

       SND_SOC_DAPM_MIXER("Left REC Mixer", SND_SOC_NOPM, 0, 0,
         &max98088_left_rec_mixer_controls[0],
               ARRAY_SIZE(max98088_left_rec_mixer_controls)),

       SND_SOC_DAPM_MIXER("Right REC Mixer", SND_SOC_NOPM, 0, 0,
         &max98088_right_rec_mixer_controls[0],
               ARRAY_SIZE(max98088_right_rec_mixer_controls)),

       SND_SOC_DAPM_MIXER("Left ADC Mixer", SND_SOC_NOPM, 0, 0,
               &max98088_left_ADC_mixer_controls[0],
               ARRAY_SIZE(max98088_left_ADC_mixer_controls)),

       SND_SOC_DAPM_MIXER("Right ADC Mixer", SND_SOC_NOPM, 0, 0,
               &max98088_right_ADC_mixer_controls[0],
               ARRAY_SIZE(max98088_right_ADC_mixer_controls)),

       SND_SOC_DAPM_PGA_E("MIC1 Input", M98088_REG_35_LVL_MIC1,
               5, 0, शून्य, 0, max98088_mic_event,
               SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

       SND_SOC_DAPM_PGA_E("MIC2 Input", M98088_REG_36_LVL_MIC2,
               5, 0, शून्य, 0, max98088_mic_event,
               SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

       SND_SOC_DAPM_PGA_E("INA1 Input", M98088_REG_4C_PWR_EN_IN,
               7, 0, शून्य, 0, max98088_pga_ina1_event,
               SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

       SND_SOC_DAPM_PGA_E("INA2 Input", M98088_REG_4C_PWR_EN_IN,
               7, 0, शून्य, 0, max98088_pga_ina2_event,
               SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

       SND_SOC_DAPM_PGA_E("INB1 Input", M98088_REG_4C_PWR_EN_IN,
               6, 0, शून्य, 0, max98088_pga_inb1_event,
               SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

       SND_SOC_DAPM_PGA_E("INB2 Input", M98088_REG_4C_PWR_EN_IN,
               6, 0, शून्य, 0, max98088_pga_inb2_event,
               SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

       SND_SOC_DAPM_MICBIAS("MICBIAS", M98088_REG_4C_PWR_EN_IN, 3, 0),

       SND_SOC_DAPM_OUTPUT("HPL"),
       SND_SOC_DAPM_OUTPUT("HPR"),
       SND_SOC_DAPM_OUTPUT("SPKL"),
       SND_SOC_DAPM_OUTPUT("SPKR"),
       SND_SOC_DAPM_OUTPUT("RECL"),
       SND_SOC_DAPM_OUTPUT("RECR"),

       SND_SOC_DAPM_INPUT("MIC1"),
       SND_SOC_DAPM_INPUT("MIC2"),
       SND_SOC_DAPM_INPUT("INA1"),
       SND_SOC_DAPM_INPUT("INA2"),
       SND_SOC_DAPM_INPUT("INB1"),
       SND_SOC_DAPM_INPUT("INB2"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98088_audio_map[] = अणु
       /* Left headphone output mixer */
       अणु"Left HP Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
       अणु"Left HP Mixer", "Left DAC2 Switch", "DACL2"पूर्ण,
       अणु"Left HP Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
       अणु"Left HP Mixer", "Right DAC2 Switch", "DACR2"पूर्ण,
       अणु"Left HP Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
       अणु"Left HP Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
       अणु"Left HP Mixer", "INA1 Switch", "INA1 Input"पूर्ण,
       अणु"Left HP Mixer", "INA2 Switch", "INA2 Input"पूर्ण,
       अणु"Left HP Mixer", "INB1 Switch", "INB1 Input"पूर्ण,
       अणु"Left HP Mixer", "INB2 Switch", "INB2 Input"पूर्ण,

       /* Right headphone output mixer */
       अणु"Right HP Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
       अणु"Right HP Mixer", "Left DAC2 Switch", "DACL2"  पूर्ण,
       अणु"Right HP Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
       अणु"Right HP Mixer", "Right DAC2 Switch", "DACR2"पूर्ण,
       अणु"Right HP Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
       अणु"Right HP Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
       अणु"Right HP Mixer", "INA1 Switch", "INA1 Input"पूर्ण,
       अणु"Right HP Mixer", "INA2 Switch", "INA2 Input"पूर्ण,
       अणु"Right HP Mixer", "INB1 Switch", "INB1 Input"पूर्ण,
       अणु"Right HP Mixer", "INB2 Switch", "INB2 Input"पूर्ण,

       /* Left speaker output mixer */
       अणु"Left SPK Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
       अणु"Left SPK Mixer", "Left DAC2 Switch", "DACL2"पूर्ण,
       अणु"Left SPK Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
       अणु"Left SPK Mixer", "Right DAC2 Switch", "DACR2"पूर्ण,
       अणु"Left SPK Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
       अणु"Left SPK Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
       अणु"Left SPK Mixer", "INA1 Switch", "INA1 Input"पूर्ण,
       अणु"Left SPK Mixer", "INA2 Switch", "INA2 Input"पूर्ण,
       अणु"Left SPK Mixer", "INB1 Switch", "INB1 Input"पूर्ण,
       अणु"Left SPK Mixer", "INB2 Switch", "INB2 Input"पूर्ण,

       /* Right speaker output mixer */
       अणु"Right SPK Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
       अणु"Right SPK Mixer", "Left DAC2 Switch", "DACL2"पूर्ण,
       अणु"Right SPK Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
       अणु"Right SPK Mixer", "Right DAC2 Switch", "DACR2"पूर्ण,
       अणु"Right SPK Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
       अणु"Right SPK Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
       अणु"Right SPK Mixer", "INA1 Switch", "INA1 Input"पूर्ण,
       अणु"Right SPK Mixer", "INA2 Switch", "INA2 Input"पूर्ण,
       अणु"Right SPK Mixer", "INB1 Switch", "INB1 Input"पूर्ण,
       अणु"Right SPK Mixer", "INB2 Switch", "INB2 Input"पूर्ण,

       /* Earpiece/Receiver output mixer */
       अणु"Left REC Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
       अणु"Left REC Mixer", "Left DAC2 Switch", "DACL2"पूर्ण,
       अणु"Left REC Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
       अणु"Left REC Mixer", "Right DAC2 Switch", "DACR2"पूर्ण,
       अणु"Left REC Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
       अणु"Left REC Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
       अणु"Left REC Mixer", "INA1 Switch", "INA1 Input"पूर्ण,
       अणु"Left REC Mixer", "INA2 Switch", "INA2 Input"पूर्ण,
       अणु"Left REC Mixer", "INB1 Switch", "INB1 Input"पूर्ण,
       अणु"Left REC Mixer", "INB2 Switch", "INB2 Input"पूर्ण,

       /* Earpiece/Receiver output mixer */
       अणु"Right REC Mixer", "Left DAC1 Switch", "DACL1"पूर्ण,
       अणु"Right REC Mixer", "Left DAC2 Switch", "DACL2"पूर्ण,
       अणु"Right REC Mixer", "Right DAC1 Switch", "DACR1"पूर्ण,
       अणु"Right REC Mixer", "Right DAC2 Switch", "DACR2"पूर्ण,
       अणु"Right REC Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
       अणु"Right REC Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
       अणु"Right REC Mixer", "INA1 Switch", "INA1 Input"पूर्ण,
       अणु"Right REC Mixer", "INA2 Switch", "INA2 Input"पूर्ण,
       अणु"Right REC Mixer", "INB1 Switch", "INB1 Input"पूर्ण,
       अणु"Right REC Mixer", "INB2 Switch", "INB2 Input"पूर्ण,

       अणु"HP Left Out", शून्य, "Left HP Mixer"पूर्ण,
       अणु"HP Right Out", शून्य, "Right HP Mixer"पूर्ण,
       अणु"SPK Left Out", शून्य, "Left SPK Mixer"पूर्ण,
       अणु"SPK Right Out", शून्य, "Right SPK Mixer"पूर्ण,
       अणु"REC Left Out", शून्य, "Left REC Mixer"पूर्ण,
       अणु"REC Right Out", शून्य, "Right REC Mixer"पूर्ण,

       अणु"HPL", शून्य, "HP Left Out"पूर्ण,
       अणु"HPR", शून्य, "HP Right Out"पूर्ण,
       अणु"SPKL", शून्य, "SPK Left Out"पूर्ण,
       अणु"SPKR", शून्य, "SPK Right Out"पूर्ण,
       अणु"RECL", शून्य, "REC Left Out"पूर्ण,
       अणु"RECR", शून्य, "REC Right Out"पूर्ण,

       /* Left ADC input mixer */
       अणु"Left ADC Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
       अणु"Left ADC Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
       अणु"Left ADC Mixer", "INA1 Switch", "INA1 Input"पूर्ण,
       अणु"Left ADC Mixer", "INA2 Switch", "INA2 Input"पूर्ण,
       अणु"Left ADC Mixer", "INB1 Switch", "INB1 Input"पूर्ण,
       अणु"Left ADC Mixer", "INB2 Switch", "INB2 Input"पूर्ण,

       /* Right ADC input mixer */
       अणु"Right ADC Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
       अणु"Right ADC Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
       अणु"Right ADC Mixer", "INA1 Switch", "INA1 Input"पूर्ण,
       अणु"Right ADC Mixer", "INA2 Switch", "INA2 Input"पूर्ण,
       अणु"Right ADC Mixer", "INB1 Switch", "INB1 Input"पूर्ण,
       अणु"Right ADC Mixer", "INB2 Switch", "INB2 Input"पूर्ण,

       /* Inमाला_दो */
       अणु"ADCL", शून्य, "Left ADC Mixer"पूर्ण,
       अणु"ADCR", शून्य, "Right ADC Mixer"पूर्ण,
       अणु"INA1 Input", शून्य, "INA1"पूर्ण,
       अणु"INA2 Input", शून्य, "INA2"पूर्ण,
       अणु"INB1 Input", शून्य, "INB1"पूर्ण,
       अणु"INB2 Input", शून्य, "INB2"पूर्ण,
       अणु"MIC1 Input", शून्य, "MIC1"पूर्ण,
       अणु"MIC2 Input", शून्य, "MIC2"पूर्ण,
पूर्ण;

/* codec mclk घड़ी भागider coefficients */
अटल स्थिर काष्ठा अणु
       u32 rate;
       u8  sr;
पूर्ण rate_table[] = अणु
       अणु8000,  0x10पूर्ण,
       अणु11025, 0x20पूर्ण,
       अणु16000, 0x30पूर्ण,
       अणु22050, 0x40पूर्ण,
       अणु24000, 0x50पूर्ण,
       अणु32000, 0x60पूर्ण,
       अणु44100, 0x70पूर्ण,
       अणु48000, 0x80पूर्ण,
       अणु88200, 0x90पूर्ण,
       अणु96000, 0xA0पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक rate_value(पूर्णांक rate, u8 *value)
अणु
       पूर्णांक i;

       क्रम (i = 0; i < ARRAY_SIZE(rate_table); i++) अणु
               अगर (rate_table[i].rate >= rate) अणु
                       *value = rate_table[i].sr;
                       वापस 0;
               पूर्ण
       पूर्ण
       *value = rate_table[0].sr;
       वापस -EINVAL;
पूर्ण

अटल पूर्णांक max98088_dai1_hw_params(काष्ठा snd_pcm_substream *substream,
                                  काष्ठा snd_pcm_hw_params *params,
                                  काष्ठा snd_soc_dai *dai)
अणु
       काष्ठा snd_soc_component *component = dai->component;
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       काष्ठा max98088_cdata *cdata;
       अचिन्हित दीर्घ दीर्घ ni;
       अचिन्हित पूर्णांक rate;
       u8 regval;

       cdata = &max98088->dai[0];

       rate = params_rate(params);

       चयन (params_width(params)) अणु
       हाल 16:
               snd_soc_component_update_bits(component, M98088_REG_14_DAI1_FORMAT,
                       M98088_DAI_WS, 0);
               अवरोध;
       हाल 24:
               snd_soc_component_update_bits(component, M98088_REG_14_DAI1_FORMAT,
                       M98088_DAI_WS, M98088_DAI_WS);
               अवरोध;
       शेष:
               वापस -EINVAL;
       पूर्ण

       snd_soc_component_update_bits(component, M98088_REG_51_PWR_SYS, M98088_SHDNRUN, 0);

       अगर (rate_value(rate, &regval))
               वापस -EINVAL;

       snd_soc_component_update_bits(component, M98088_REG_11_DAI1_CLKMODE,
               M98088_CLKMODE_MASK, regval);
       cdata->rate = rate;

       /* Configure NI when operating as master */
       अगर (snd_soc_component_पढ़ो(component, M98088_REG_14_DAI1_FORMAT)
               & M98088_DAI_MAS) अणु
               अचिन्हित दीर्घ pclk;

               अगर (max98088->sysclk == 0) अणु
                       dev_err(component->dev, "Invalid system clock frequency\n");
                       वापस -EINVAL;
               पूर्ण
               ni = 65536ULL * (rate < 50000 ? 96ULL : 48ULL)
                               * (अचिन्हित दीर्घ दीर्घ पूर्णांक)rate;
               pclk = DIV_ROUND_CLOSEST(max98088->sysclk, max98088->mclk_prescaler);
               ni = DIV_ROUND_CLOSEST_ULL(ni, pclk);
               snd_soc_component_ग_लिखो(component, M98088_REG_12_DAI1_CLKCFG_HI,
                       (ni >> 8) & 0x7F);
               snd_soc_component_ग_लिखो(component, M98088_REG_13_DAI1_CLKCFG_LO,
                       ni & 0xFF);
       पूर्ण

       /* Update sample rate mode */
       अगर (rate < 50000)
               snd_soc_component_update_bits(component, M98088_REG_18_DAI1_FILTERS,
                       M98088_DAI_DHF, 0);
       अन्यथा
               snd_soc_component_update_bits(component, M98088_REG_18_DAI1_FILTERS,
                       M98088_DAI_DHF, M98088_DAI_DHF);

       snd_soc_component_update_bits(component, M98088_REG_51_PWR_SYS, M98088_SHDNRUN,
               M98088_SHDNRUN);

       वापस 0;
पूर्ण

अटल पूर्णांक max98088_dai2_hw_params(काष्ठा snd_pcm_substream *substream,
                                  काष्ठा snd_pcm_hw_params *params,
                                  काष्ठा snd_soc_dai *dai)
अणु
       काष्ठा snd_soc_component *component = dai->component;
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       काष्ठा max98088_cdata *cdata;
       अचिन्हित दीर्घ दीर्घ ni;
       अचिन्हित पूर्णांक rate;
       u8 regval;

       cdata = &max98088->dai[1];

       rate = params_rate(params);

       चयन (params_width(params)) अणु
       हाल 16:
               snd_soc_component_update_bits(component, M98088_REG_1C_DAI2_FORMAT,
                       M98088_DAI_WS, 0);
               अवरोध;
       हाल 24:
               snd_soc_component_update_bits(component, M98088_REG_1C_DAI2_FORMAT,
                       M98088_DAI_WS, M98088_DAI_WS);
               अवरोध;
       शेष:
               वापस -EINVAL;
       पूर्ण

       snd_soc_component_update_bits(component, M98088_REG_51_PWR_SYS, M98088_SHDNRUN, 0);

       अगर (rate_value(rate, &regval))
               वापस -EINVAL;

       snd_soc_component_update_bits(component, M98088_REG_19_DAI2_CLKMODE,
               M98088_CLKMODE_MASK, regval);
       cdata->rate = rate;

       /* Configure NI when operating as master */
       अगर (snd_soc_component_पढ़ो(component, M98088_REG_1C_DAI2_FORMAT)
               & M98088_DAI_MAS) अणु
               अचिन्हित दीर्घ pclk;

               अगर (max98088->sysclk == 0) अणु
                       dev_err(component->dev, "Invalid system clock frequency\n");
                       वापस -EINVAL;
               पूर्ण
               ni = 65536ULL * (rate < 50000 ? 96ULL : 48ULL)
                               * (अचिन्हित दीर्घ दीर्घ पूर्णांक)rate;
               pclk = DIV_ROUND_CLOSEST(max98088->sysclk, max98088->mclk_prescaler);
               ni = DIV_ROUND_CLOSEST_ULL(ni, pclk);
               snd_soc_component_ग_लिखो(component, M98088_REG_1A_DAI2_CLKCFG_HI,
                       (ni >> 8) & 0x7F);
               snd_soc_component_ग_लिखो(component, M98088_REG_1B_DAI2_CLKCFG_LO,
                       ni & 0xFF);
       पूर्ण

       /* Update sample rate mode */
       अगर (rate < 50000)
               snd_soc_component_update_bits(component, M98088_REG_20_DAI2_FILTERS,
                       M98088_DAI_DHF, 0);
       अन्यथा
               snd_soc_component_update_bits(component, M98088_REG_20_DAI2_FILTERS,
                       M98088_DAI_DHF, M98088_DAI_DHF);

       snd_soc_component_update_bits(component, M98088_REG_51_PWR_SYS, M98088_SHDNRUN,
               M98088_SHDNRUN);

       वापस 0;
पूर्ण

अटल पूर्णांक max98088_dai_set_sysclk(काष्ठा snd_soc_dai *dai,
                                  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
       काष्ठा snd_soc_component *component = dai->component;
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);

       /* Requested घड़ी frequency is alपढ़ोy setup */
       अगर (freq == max98088->sysclk)
               वापस 0;

	अगर (!IS_ERR(max98088->mclk)) अणु
		freq = clk_round_rate(max98088->mclk, freq);
		clk_set_rate(max98088->mclk, freq);
	पूर्ण

       /* Setup घड़ीs क्रम slave mode, and using the PLL
        * PSCLK = 0x01 (when master clk is 10MHz to 20MHz)
        *         0x02 (when master clk is 20MHz to 30MHz)..
        */
       अगर ((freq >= 10000000) && (freq < 20000000)) अणु
               snd_soc_component_ग_लिखो(component, M98088_REG_10_SYS_CLK, 0x10);
               max98088->mclk_prescaler = 1;
       पूर्ण अन्यथा अगर ((freq >= 20000000) && (freq < 30000000)) अणु
               snd_soc_component_ग_लिखो(component, M98088_REG_10_SYS_CLK, 0x20);
               max98088->mclk_prescaler = 2;
       पूर्ण अन्यथा अणु
               dev_err(component->dev, "Invalid master clock frequency\n");
               वापस -EINVAL;
       पूर्ण

       अगर (snd_soc_component_पढ़ो(component, M98088_REG_51_PWR_SYS)  & M98088_SHDNRUN) अणु
               snd_soc_component_update_bits(component, M98088_REG_51_PWR_SYS,
                       M98088_SHDNRUN, 0);
               snd_soc_component_update_bits(component, M98088_REG_51_PWR_SYS,
                       M98088_SHDNRUN, M98088_SHDNRUN);
       पूर्ण

       dev_dbg(dai->dev, "Clock source is %d at %uHz\n", clk_id, freq);

       max98088->sysclk = freq;
       वापस 0;
पूर्ण

अटल पूर्णांक max98088_dai1_set_fmt(काष्ठा snd_soc_dai *codec_dai,
                                अचिन्हित पूर्णांक fmt)
अणु
       काष्ठा snd_soc_component *component = codec_dai->component;
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       काष्ठा max98088_cdata *cdata;
       u8 reg15val;
       u8 reg14val = 0;

       cdata = &max98088->dai[0];

       अगर (fmt != cdata->fmt) अणु
               cdata->fmt = fmt;

               चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
               हाल SND_SOC_DAIFMT_CBS_CFS:
                       /* Slave mode PLL */
                       snd_soc_component_ग_लिखो(component, M98088_REG_12_DAI1_CLKCFG_HI,
                               0x80);
                       snd_soc_component_ग_लिखो(component, M98088_REG_13_DAI1_CLKCFG_LO,
                               0x00);
                       अवरोध;
               हाल SND_SOC_DAIFMT_CBM_CFM:
                       /* Set to master mode */
                       reg14val |= M98088_DAI_MAS;
                       अवरोध;
               हाल SND_SOC_DAIFMT_CBS_CFM:
               हाल SND_SOC_DAIFMT_CBM_CFS:
               शेष:
                       dev_err(component->dev, "Clock mode unsupported");
                       वापस -EINVAL;
               पूर्ण

               चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
               हाल SND_SOC_DAIFMT_I2S:
                       reg14val |= M98088_DAI_DLY;
                       अवरोध;
               हाल SND_SOC_DAIFMT_LEFT_J:
                       अवरोध;
               शेष:
                       वापस -EINVAL;
               पूर्ण

               चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
               हाल SND_SOC_DAIFMT_NB_NF:
                       अवरोध;
               हाल SND_SOC_DAIFMT_NB_IF:
                       reg14val |= M98088_DAI_WCI;
                       अवरोध;
               हाल SND_SOC_DAIFMT_IB_NF:
                       reg14val |= M98088_DAI_BCI;
                       अवरोध;
               हाल SND_SOC_DAIFMT_IB_IF:
                       reg14val |= M98088_DAI_BCI|M98088_DAI_WCI;
                       अवरोध;
               शेष:
                       वापस -EINVAL;
               पूर्ण

               snd_soc_component_update_bits(component, M98088_REG_14_DAI1_FORMAT,
                       M98088_DAI_MAS | M98088_DAI_DLY | M98088_DAI_BCI |
                       M98088_DAI_WCI, reg14val);

               reg15val = M98088_DAI_BSEL64;
               अगर (max98088->digmic)
                       reg15val |= M98088_DAI_OSR64;
               snd_soc_component_ग_लिखो(component, M98088_REG_15_DAI1_CLOCK, reg15val);
       पूर्ण

       वापस 0;
पूर्ण

अटल पूर्णांक max98088_dai2_set_fmt(काष्ठा snd_soc_dai *codec_dai,
                                अचिन्हित पूर्णांक fmt)
अणु
       काष्ठा snd_soc_component *component = codec_dai->component;
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       काष्ठा max98088_cdata *cdata;
       u8 reg1Cval = 0;

       cdata = &max98088->dai[1];

       अगर (fmt != cdata->fmt) अणु
               cdata->fmt = fmt;

               चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
               हाल SND_SOC_DAIFMT_CBS_CFS:
                       /* Slave mode PLL */
                       snd_soc_component_ग_लिखो(component, M98088_REG_1A_DAI2_CLKCFG_HI,
                               0x80);
                       snd_soc_component_ग_लिखो(component, M98088_REG_1B_DAI2_CLKCFG_LO,
                               0x00);
                       अवरोध;
               हाल SND_SOC_DAIFMT_CBM_CFM:
                       /* Set to master mode */
                       reg1Cval |= M98088_DAI_MAS;
                       अवरोध;
               हाल SND_SOC_DAIFMT_CBS_CFM:
               हाल SND_SOC_DAIFMT_CBM_CFS:
               शेष:
                       dev_err(component->dev, "Clock mode unsupported");
                       वापस -EINVAL;
               पूर्ण

               चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
               हाल SND_SOC_DAIFMT_I2S:
                       reg1Cval |= M98088_DAI_DLY;
                       अवरोध;
               हाल SND_SOC_DAIFMT_LEFT_J:
                       अवरोध;
               शेष:
                       वापस -EINVAL;
               पूर्ण

               चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
               हाल SND_SOC_DAIFMT_NB_NF:
                       अवरोध;
               हाल SND_SOC_DAIFMT_NB_IF:
                       reg1Cval |= M98088_DAI_WCI;
                       अवरोध;
               हाल SND_SOC_DAIFMT_IB_NF:
                       reg1Cval |= M98088_DAI_BCI;
                       अवरोध;
               हाल SND_SOC_DAIFMT_IB_IF:
                       reg1Cval |= M98088_DAI_BCI|M98088_DAI_WCI;
                       अवरोध;
               शेष:
                       वापस -EINVAL;
               पूर्ण

               snd_soc_component_update_bits(component, M98088_REG_1C_DAI2_FORMAT,
                       M98088_DAI_MAS | M98088_DAI_DLY | M98088_DAI_BCI |
                       M98088_DAI_WCI, reg1Cval);

               snd_soc_component_ग_लिखो(component, M98088_REG_1D_DAI2_CLOCK,
                       M98088_DAI_BSEL64);
       पूर्ण

       वापस 0;
पूर्ण

अटल पूर्णांक max98088_dai1_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute,
			      पूर्णांक direction)
अणु
       काष्ठा snd_soc_component *component = codec_dai->component;
       पूर्णांक reg;

       अगर (mute)
               reg = M98088_DAI_MUTE;
       अन्यथा
               reg = 0;

       snd_soc_component_update_bits(component, M98088_REG_2F_LVL_DAI1_PLAY,
                           M98088_DAI_MUTE_MASK, reg);
       वापस 0;
पूर्ण

अटल पूर्णांक max98088_dai2_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute,
			      पूर्णांक direction)
अणु
       काष्ठा snd_soc_component *component = codec_dai->component;
       पूर्णांक reg;

       अगर (mute)
               reg = M98088_DAI_MUTE;
       अन्यथा
               reg = 0;

       snd_soc_component_update_bits(component, M98088_REG_31_LVL_DAI2_PLAY,
                           M98088_DAI_MUTE_MASK, reg);
       वापस 0;
पूर्ण

अटल पूर्णांक max98088_set_bias_level(काष्ठा snd_soc_component *component,
                                  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/*
		 * SND_SOC_BIAS_PREPARE is called जबतक preparing क्रम a
		 * transition to ON or away from ON. If current bias_level
		 * is SND_SOC_BIAS_ON, then it is preparing क्रम a transition
		 * away from ON. Disable the घड़ी in that हाल, otherwise
		 * enable it.
		 */
		अगर (!IS_ERR(max98088->mclk)) अणु
			अगर (snd_soc_component_get_bias_level(component) ==
			    SND_SOC_BIAS_ON)
				clk_disable_unprepare(max98088->mclk);
			अन्यथा
				clk_prepare_enable(max98088->mclk);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			regcache_sync(max98088->regmap);

		snd_soc_component_update_bits(component, M98088_REG_4C_PWR_EN_IN,
				   M98088_MBEN, M98088_MBEN);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, M98088_REG_4C_PWR_EN_IN,
				    M98088_MBEN, 0);
		regcache_mark_dirty(max98088->regmap);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा MAX98088_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा MAX98088_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops max98088_dai1_ops = अणु
       .set_sysclk = max98088_dai_set_sysclk,
       .set_fmt = max98088_dai1_set_fmt,
       .hw_params = max98088_dai1_hw_params,
       .mute_stream = max98088_dai1_mute,
       .no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops max98088_dai2_ops = अणु
       .set_sysclk = max98088_dai_set_sysclk,
       .set_fmt = max98088_dai2_set_fmt,
       .hw_params = max98088_dai2_hw_params,
       .mute_stream = max98088_dai2_mute,
       .no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max98088_dai[] = अणु
अणु
       .name = "HiFi",
       .playback = अणु
               .stream_name = "HiFi Playback",
               .channels_min = 1,
               .channels_max = 2,
               .rates = MAX98088_RATES,
               .क्रमmats = MAX98088_FORMATS,
       पूर्ण,
       .capture = अणु
               .stream_name = "HiFi Capture",
               .channels_min = 1,
               .channels_max = 2,
               .rates = MAX98088_RATES,
               .क्रमmats = MAX98088_FORMATS,
       पूर्ण,
        .ops = &max98088_dai1_ops,
पूर्ण,
अणु
       .name = "Aux",
       .playback = अणु
               .stream_name = "Aux Playback",
               .channels_min = 1,
               .channels_max = 2,
               .rates = MAX98088_RATES,
               .क्रमmats = MAX98088_FORMATS,
       पूर्ण,
       .ops = &max98088_dai2_ops,
पूर्ण
पूर्ण;

अटल स्थिर अक्षर *eq_mode_name[] = अणु"EQ1 Mode", "EQ2 Mode"पूर्ण;

अटल पूर्णांक max98088_get_channel(काष्ठा snd_soc_component *component, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;

	ret = match_string(eq_mode_name, ARRAY_SIZE(eq_mode_name), name);
	अगर (ret < 0)
		dev_err(component->dev, "Bad EQ channel name '%s'\n", name);
	वापस ret;
पूर्ण

अटल व्योम max98088_setup_eq1(काष्ठा snd_soc_component *component)
अणु
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       काष्ठा max98088_pdata *pdata = max98088->pdata;
       काष्ठा max98088_eq_cfg *coef_set;
       पूर्णांक best, best_val, save, i, sel, fs;
       काष्ठा max98088_cdata *cdata;

       cdata = &max98088->dai[0];

       अगर (!pdata || !max98088->eq_textcnt)
               वापस;

       /* Find the selected configuration with nearest sample rate */
       fs = cdata->rate;
       sel = cdata->eq_sel;

       best = 0;
       best_val = पूर्णांक_उच्च;
       क्रम (i = 0; i < pdata->eq_cfgcnt; i++) अणु
               अगर (म_भेद(pdata->eq_cfg[i].name, max98088->eq_texts[sel]) == 0 &&
                   असल(pdata->eq_cfg[i].rate - fs) < best_val) अणु
                       best = i;
                       best_val = असल(pdata->eq_cfg[i].rate - fs);
               पूर्ण
       पूर्ण

       dev_dbg(component->dev, "Selected %s/%dHz for %dHz sample rate\n",
               pdata->eq_cfg[best].name,
               pdata->eq_cfg[best].rate, fs);

       /* Disable EQ जबतक configuring, and save current on/off state */
       save = snd_soc_component_पढ़ो(component, M98088_REG_49_CFG_LEVEL);
       snd_soc_component_update_bits(component, M98088_REG_49_CFG_LEVEL, M98088_EQ1EN, 0);

       coef_set = &pdata->eq_cfg[sel];

       m98088_eq_band(component, 0, 0, coef_set->band1);
       m98088_eq_band(component, 0, 1, coef_set->band2);
       m98088_eq_band(component, 0, 2, coef_set->band3);
       m98088_eq_band(component, 0, 3, coef_set->band4);
       m98088_eq_band(component, 0, 4, coef_set->band5);

       /* Restore the original on/off state */
       snd_soc_component_update_bits(component, M98088_REG_49_CFG_LEVEL, M98088_EQ1EN, save);
पूर्ण

अटल व्योम max98088_setup_eq2(काष्ठा snd_soc_component *component)
अणु
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       काष्ठा max98088_pdata *pdata = max98088->pdata;
       काष्ठा max98088_eq_cfg *coef_set;
       पूर्णांक best, best_val, save, i, sel, fs;
       काष्ठा max98088_cdata *cdata;

       cdata = &max98088->dai[1];

       अगर (!pdata || !max98088->eq_textcnt)
               वापस;

       /* Find the selected configuration with nearest sample rate */
       fs = cdata->rate;

       sel = cdata->eq_sel;
       best = 0;
       best_val = पूर्णांक_उच्च;
       क्रम (i = 0; i < pdata->eq_cfgcnt; i++) अणु
               अगर (म_भेद(pdata->eq_cfg[i].name, max98088->eq_texts[sel]) == 0 &&
                   असल(pdata->eq_cfg[i].rate - fs) < best_val) अणु
                       best = i;
                       best_val = असल(pdata->eq_cfg[i].rate - fs);
               पूर्ण
       पूर्ण

       dev_dbg(component->dev, "Selected %s/%dHz for %dHz sample rate\n",
               pdata->eq_cfg[best].name,
               pdata->eq_cfg[best].rate, fs);

       /* Disable EQ जबतक configuring, and save current on/off state */
       save = snd_soc_component_पढ़ो(component, M98088_REG_49_CFG_LEVEL);
       snd_soc_component_update_bits(component, M98088_REG_49_CFG_LEVEL, M98088_EQ2EN, 0);

       coef_set = &pdata->eq_cfg[sel];

       m98088_eq_band(component, 1, 0, coef_set->band1);
       m98088_eq_band(component, 1, 1, coef_set->band2);
       m98088_eq_band(component, 1, 2, coef_set->band3);
       m98088_eq_band(component, 1, 3, coef_set->band4);
       m98088_eq_band(component, 1, 4, coef_set->band5);

       /* Restore the original on/off state */
       snd_soc_component_update_bits(component, M98088_REG_49_CFG_LEVEL, M98088_EQ2EN,
               save);
पूर्ण

अटल पूर्णांक max98088_put_eq_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
                                काष्ठा snd_ctl_elem_value *ucontrol)
अणु
       काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       काष्ठा max98088_pdata *pdata = max98088->pdata;
       पूर्णांक channel = max98088_get_channel(component, kcontrol->id.name);
       काष्ठा max98088_cdata *cdata;
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];

       अगर (channel < 0)
	       वापस channel;

       cdata = &max98088->dai[channel];

       अगर (sel >= pdata->eq_cfgcnt)
               वापस -EINVAL;

       cdata->eq_sel = sel;

       चयन (channel) अणु
       हाल 0:
               max98088_setup_eq1(component);
               अवरोध;
       हाल 1:
               max98088_setup_eq2(component);
               अवरोध;
       पूर्ण

       वापस 0;
पूर्ण

अटल पूर्णांक max98088_get_eq_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
                                काष्ठा snd_ctl_elem_value *ucontrol)
अणु
       काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       पूर्णांक channel = max98088_get_channel(component, kcontrol->id.name);
       काष्ठा max98088_cdata *cdata;

       अगर (channel < 0)
	       वापस channel;

       cdata = &max98088->dai[channel];
       ucontrol->value.क्रमागतerated.item[0] = cdata->eq_sel;
       वापस 0;
पूर्ण

अटल व्योम max98088_handle_eq_pdata(काष्ठा snd_soc_component *component)
अणु
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       काष्ठा max98088_pdata *pdata = max98088->pdata;
       काष्ठा max98088_eq_cfg *cfg;
       अचिन्हित पूर्णांक cfgcnt;
       पूर्णांक i, j;
       स्थिर अक्षर **t;
       पूर्णांक ret;
       काष्ठा snd_kcontrol_new controls[] = अणु
               SOC_ENUM_EXT((अक्षर *)eq_mode_name[0],
                       max98088->eq_क्रमागत,
                       max98088_get_eq_क्रमागत,
                       max98088_put_eq_क्रमागत),
               SOC_ENUM_EXT((अक्षर *)eq_mode_name[1],
                       max98088->eq_क्रमागत,
                       max98088_get_eq_क्रमागत,
                       max98088_put_eq_क्रमागत),
       पूर्ण;
       BUILD_BUG_ON(ARRAY_SIZE(controls) != ARRAY_SIZE(eq_mode_name));

       cfg = pdata->eq_cfg;
       cfgcnt = pdata->eq_cfgcnt;

       /* Setup an array of texts क्रम the equalizer क्रमागत.
        * This is based on Mark Brown's equalizer driver code.
        */
       max98088->eq_textcnt = 0;
       max98088->eq_texts = शून्य;
       क्रम (i = 0; i < cfgcnt; i++) अणु
               क्रम (j = 0; j < max98088->eq_textcnt; j++) अणु
                       अगर (म_भेद(cfg[i].name, max98088->eq_texts[j]) == 0)
                               अवरोध;
               पूर्ण

               अगर (j != max98088->eq_textcnt)
                       जारी;

               /* Expand the array */
               t = kपुनः_स्मृति(max98088->eq_texts,
                            माप(अक्षर *) * (max98088->eq_textcnt + 1),
                            GFP_KERNEL);
               अगर (t == शून्य)
                       जारी;

               /* Store the new entry */
               t[max98088->eq_textcnt] = cfg[i].name;
               max98088->eq_textcnt++;
               max98088->eq_texts = t;
       पूर्ण

       /* Now poपूर्णांक the soc_क्रमागत to .texts array items */
       max98088->eq_क्रमागत.texts = max98088->eq_texts;
       max98088->eq_क्रमागत.items = max98088->eq_textcnt;

       ret = snd_soc_add_component_controls(component, controls, ARRAY_SIZE(controls));
       अगर (ret != 0)
               dev_err(component->dev, "Failed to add EQ control: %d\n", ret);
पूर्ण

अटल व्योम max98088_handle_pdata(काष्ठा snd_soc_component *component)
अणु
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       काष्ठा max98088_pdata *pdata = max98088->pdata;
       u8 regval = 0;

       अगर (!pdata) अणु
               dev_dbg(component->dev, "No platform data\n");
               वापस;
       पूर्ण

       /* Configure mic क्रम analog/digital mic mode */
       अगर (pdata->digmic_left_mode)
               regval |= M98088_DIGMIC_L;

       अगर (pdata->digmic_right_mode)
               regval |= M98088_DIGMIC_R;

       max98088->digmic = (regval ? 1 : 0);

       snd_soc_component_ग_लिखो(component, M98088_REG_48_CFG_MIC, regval);

       /* Configure receiver output */
       regval = ((pdata->receiver_mode) ? M98088_REC_LINEMODE : 0);
       snd_soc_component_update_bits(component, M98088_REG_2A_MIC_REC_CNTL,
               M98088_REC_LINEMODE_MASK, regval);

       /* Configure equalizers */
       अगर (pdata->eq_cfgcnt)
               max98088_handle_eq_pdata(component);
पूर्ण

अटल पूर्णांक max98088_probe(काष्ठा snd_soc_component *component)
अणु
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       काष्ठा max98088_cdata *cdata;
       पूर्णांक ret = 0;

       regcache_mark_dirty(max98088->regmap);

       /* initialize निजी data */

       max98088->sysclk = (अचिन्हित)-1;
       max98088->eq_textcnt = 0;

       cdata = &max98088->dai[0];
       cdata->rate = (अचिन्हित)-1;
       cdata->fmt  = (अचिन्हित)-1;
       cdata->eq_sel = 0;

       cdata = &max98088->dai[1];
       cdata->rate = (अचिन्हित)-1;
       cdata->fmt  = (अचिन्हित)-1;
       cdata->eq_sel = 0;

       max98088->ina_state = 0;
       max98088->inb_state = 0;
       max98088->ex_mode = 0;
       max98088->digmic = 0;
       max98088->mic1pre = 0;
       max98088->mic2pre = 0;

       ret = snd_soc_component_पढ़ो(component, M98088_REG_FF_REV_ID);
       अगर (ret < 0) अणु
               dev_err(component->dev, "Failed to read device revision: %d\n",
                       ret);
               जाओ err_access;
       पूर्ण
       dev_info(component->dev, "revision %c\n", ret - 0x40 + 'A');

       snd_soc_component_ग_लिखो(component, M98088_REG_51_PWR_SYS, M98088_PWRSV);

       snd_soc_component_ग_लिखो(component, M98088_REG_0F_IRQ_ENABLE, 0x00);

       snd_soc_component_ग_लिखो(component, M98088_REG_22_MIX_DAC,
               M98088_DAI1L_TO_DACL|M98088_DAI2L_TO_DACL|
               M98088_DAI1R_TO_DACR|M98088_DAI2R_TO_DACR);

       snd_soc_component_ग_लिखो(component, M98088_REG_4E_BIAS_CNTL, 0xF0);
       snd_soc_component_ग_लिखो(component, M98088_REG_50_DAC_BIAS2, 0x0F);

       snd_soc_component_ग_लिखो(component, M98088_REG_16_DAI1_IOCFG,
               M98088_S1NORMAL|M98088_SDATA);

       snd_soc_component_ग_लिखो(component, M98088_REG_1E_DAI2_IOCFG,
               M98088_S2NORMAL|M98088_SDATA);

       max98088_handle_pdata(component);

err_access:
       वापस ret;
पूर्ण

अटल व्योम max98088_हटाओ(काष्ठा snd_soc_component *component)
अणु
       काष्ठा max98088_priv *max98088 = snd_soc_component_get_drvdata(component);

       kमुक्त(max98088->eq_texts);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_max98088 = अणु
	.probe			= max98088_probe,
	.हटाओ			= max98088_हटाओ,
	.set_bias_level		= max98088_set_bias_level,
	.controls		= max98088_snd_controls,
	.num_controls		= ARRAY_SIZE(max98088_snd_controls),
	.dapm_widमाला_लो		= max98088_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max98088_dapm_widमाला_लो),
	.dapm_routes		= max98088_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(max98088_audio_map),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक max98088_i2c_probe(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
       काष्ठा max98088_priv *max98088;
       पूर्णांक ret;

       max98088 = devm_kzalloc(&i2c->dev, माप(काष्ठा max98088_priv),
			       GFP_KERNEL);
       अगर (max98088 == शून्य)
               वापस -ENOMEM;

       max98088->regmap = devm_regmap_init_i2c(i2c, &max98088_regmap);
       अगर (IS_ERR(max98088->regmap))
	       वापस PTR_ERR(max98088->regmap);

	max98088->mclk = devm_clk_get(&i2c->dev, "mclk");
	अगर (IS_ERR(max98088->mclk))
		अगर (PTR_ERR(max98088->mclk) == -EPROBE_DEFER)
			वापस PTR_ERR(max98088->mclk);

       max98088->devtype = id->driver_data;

       i2c_set_clientdata(i2c, max98088);
       max98088->pdata = i2c->dev.platक्रमm_data;

       ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
                       &soc_component_dev_max98088, &max98088_dai[0], 2);
       वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max98088_i2c_id[] = अणु
       अणु "max98088", MAX98088 पूर्ण,
       अणु "max98089", MAX98089 पूर्ण,
       अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max98088_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id max98088_of_match[] = अणु
	अणु .compatible = "maxim,max98088" पूर्ण,
	अणु .compatible = "maxim,max98089" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max98088_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max98088_i2c_driver = अणु
	.driver = अणु
		.name = "max98088",
		.of_match_table = of_match_ptr(max98088_of_match),
	पूर्ण,
	.probe  = max98088_i2c_probe,
	.id_table = max98088_i2c_id,
पूर्ण;

module_i2c_driver(max98088_i2c_driver);

MODULE_DESCRIPTION("ALSA SoC MAX98088 driver");
MODULE_AUTHOR("Peter Hsiang, Jesse Marroquin");
MODULE_LICENSE("GPL");
