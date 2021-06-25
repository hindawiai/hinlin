<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max98090.c -- MAX98090 ALSA SoC Audio driver
 *
 * Copyright 2011-2012 Maxim Integrated Products
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/max98090.h>
#समावेश "max98090.h"

/* Allows क्रम sparsely populated रेजिस्टर maps */
अटल स्थिर काष्ठा reg_शेष max98090_reg[] = अणु
	अणु 0x00, 0x00 पूर्ण, /* 00 Software Reset */
	अणु 0x03, 0x04 पूर्ण, /* 03 Interrupt Masks */
	अणु 0x04, 0x00 पूर्ण, /* 04 System Clock Quick */
	अणु 0x05, 0x00 पूर्ण, /* 05 Sample Rate Quick */
	अणु 0x06, 0x00 पूर्ण, /* 06 DAI Interface Quick */
	अणु 0x07, 0x00 पूर्ण, /* 07 DAC Path Quick */
	अणु 0x08, 0x00 पूर्ण, /* 08 Mic/Direct to ADC Quick */
	अणु 0x09, 0x00 पूर्ण, /* 09 Line to ADC Quick */
	अणु 0x0A, 0x00 पूर्ण, /* 0A Analog Mic Loop Quick */
	अणु 0x0B, 0x00 पूर्ण, /* 0B Analog Line Loop Quick */
	अणु 0x0C, 0x00 पूर्ण, /* 0C Reserved */
	अणु 0x0D, 0x00 पूर्ण, /* 0D Input Config */
	अणु 0x0E, 0x1B पूर्ण, /* 0E Line Input Level */
	अणु 0x0F, 0x00 पूर्ण, /* 0F Line Config */

	अणु 0x10, 0x14 पूर्ण, /* 10 Mic1 Input Level */
	अणु 0x11, 0x14 पूर्ण, /* 11 Mic2 Input Level */
	अणु 0x12, 0x00 पूर्ण, /* 12 Mic Bias Voltage */
	अणु 0x13, 0x00 पूर्ण, /* 13 Digital Mic Config */
	अणु 0x14, 0x00 पूर्ण, /* 14 Digital Mic Mode */
	अणु 0x15, 0x00 पूर्ण, /* 15 Left ADC Mixer */
	अणु 0x16, 0x00 पूर्ण, /* 16 Right ADC Mixer */
	अणु 0x17, 0x03 पूर्ण, /* 17 Left ADC Level */
	अणु 0x18, 0x03 पूर्ण, /* 18 Right ADC Level */
	अणु 0x19, 0x00 पूर्ण, /* 19 ADC Biquad Level */
	अणु 0x1A, 0x00 पूर्ण, /* 1A ADC Sidetone */
	अणु 0x1B, 0x00 पूर्ण, /* 1B System Clock */
	अणु 0x1C, 0x00 पूर्ण, /* 1C Clock Mode */
	अणु 0x1D, 0x00 पूर्ण, /* 1D Any Clock 1 */
	अणु 0x1E, 0x00 पूर्ण, /* 1E Any Clock 2 */
	अणु 0x1F, 0x00 पूर्ण, /* 1F Any Clock 3 */

	अणु 0x20, 0x00 पूर्ण, /* 20 Any Clock 4 */
	अणु 0x21, 0x00 पूर्ण, /* 21 Master Mode */
	अणु 0x22, 0x00 पूर्ण, /* 22 Interface Format */
	अणु 0x23, 0x00 पूर्ण, /* 23 TDM Format 1*/
	अणु 0x24, 0x00 पूर्ण, /* 24 TDM Format 2*/
	अणु 0x25, 0x00 पूर्ण, /* 25 I/O Configuration */
	अणु 0x26, 0x80 पूर्ण, /* 26 Filter Config */
	अणु 0x27, 0x00 पूर्ण, /* 27 DAI Playback Level */
	अणु 0x28, 0x00 पूर्ण, /* 28 EQ Playback Level */
	अणु 0x29, 0x00 पूर्ण, /* 29 Left HP Mixer */
	अणु 0x2A, 0x00 पूर्ण, /* 2A Right HP Mixer */
	अणु 0x2B, 0x00 पूर्ण, /* 2B HP Control */
	अणु 0x2C, 0x1A पूर्ण, /* 2C Left HP Volume */
	अणु 0x2D, 0x1A पूर्ण, /* 2D Right HP Volume */
	अणु 0x2E, 0x00 पूर्ण, /* 2E Left Spk Mixer */
	अणु 0x2F, 0x00 पूर्ण, /* 2F Right Spk Mixer */

	अणु 0x30, 0x00 पूर्ण, /* 30 Spk Control */
	अणु 0x31, 0x2C पूर्ण, /* 31 Left Spk Volume */
	अणु 0x32, 0x2C पूर्ण, /* 32 Right Spk Volume */
	अणु 0x33, 0x00 पूर्ण, /* 33 ALC Timing */
	अणु 0x34, 0x00 पूर्ण, /* 34 ALC Compressor */
	अणु 0x35, 0x00 पूर्ण, /* 35 ALC Expander */
	अणु 0x36, 0x00 पूर्ण, /* 36 ALC Gain */
	अणु 0x37, 0x00 पूर्ण, /* 37 Rcv/Line OutL Mixer */
	अणु 0x38, 0x00 पूर्ण, /* 38 Rcv/Line OutL Control */
	अणु 0x39, 0x15 पूर्ण, /* 39 Rcv/Line OutL Volume */
	अणु 0x3A, 0x00 पूर्ण, /* 3A Line OutR Mixer */
	अणु 0x3B, 0x00 पूर्ण, /* 3B Line OutR Control */
	अणु 0x3C, 0x15 पूर्ण, /* 3C Line OutR Volume */
	अणु 0x3D, 0x00 पूर्ण, /* 3D Jack Detect */
	अणु 0x3E, 0x00 पूर्ण, /* 3E Input Enable */
	अणु 0x3F, 0x00 पूर्ण, /* 3F Output Enable */

	अणु 0x40, 0x00 पूर्ण, /* 40 Level Control */
	अणु 0x41, 0x00 पूर्ण, /* 41 DSP Filter Enable */
	अणु 0x42, 0x00 पूर्ण, /* 42 Bias Control */
	अणु 0x43, 0x00 पूर्ण, /* 43 DAC Control */
	अणु 0x44, 0x06 पूर्ण, /* 44 ADC Control */
	अणु 0x45, 0x00 पूर्ण, /* 45 Device Shutकरोwn */
	अणु 0x46, 0x00 पूर्ण, /* 46 Equalizer Band 1 Coefficient B0 */
	अणु 0x47, 0x00 पूर्ण, /* 47 Equalizer Band 1 Coefficient B0 */
	अणु 0x48, 0x00 पूर्ण, /* 48 Equalizer Band 1 Coefficient B0 */
	अणु 0x49, 0x00 पूर्ण, /* 49 Equalizer Band 1 Coefficient B1 */
	अणु 0x4A, 0x00 पूर्ण, /* 4A Equalizer Band 1 Coefficient B1 */
	अणु 0x4B, 0x00 पूर्ण, /* 4B Equalizer Band 1 Coefficient B1 */
	अणु 0x4C, 0x00 पूर्ण, /* 4C Equalizer Band 1 Coefficient B2 */
	अणु 0x4D, 0x00 पूर्ण, /* 4D Equalizer Band 1 Coefficient B2 */
	अणु 0x4E, 0x00 पूर्ण, /* 4E Equalizer Band 1 Coefficient B2 */
	अणु 0x4F, 0x00 पूर्ण, /* 4F Equalizer Band 1 Coefficient A1 */

	अणु 0x50, 0x00 पूर्ण, /* 50 Equalizer Band 1 Coefficient A1 */
	अणु 0x51, 0x00 पूर्ण, /* 51 Equalizer Band 1 Coefficient A1 */
	अणु 0x52, 0x00 पूर्ण, /* 52 Equalizer Band 1 Coefficient A2 */
	अणु 0x53, 0x00 पूर्ण, /* 53 Equalizer Band 1 Coefficient A2 */
	अणु 0x54, 0x00 पूर्ण, /* 54 Equalizer Band 1 Coefficient A2 */
	अणु 0x55, 0x00 पूर्ण, /* 55 Equalizer Band 2 Coefficient B0 */
	अणु 0x56, 0x00 पूर्ण, /* 56 Equalizer Band 2 Coefficient B0 */
	अणु 0x57, 0x00 पूर्ण, /* 57 Equalizer Band 2 Coefficient B0 */
	अणु 0x58, 0x00 पूर्ण, /* 58 Equalizer Band 2 Coefficient B1 */
	अणु 0x59, 0x00 पूर्ण, /* 59 Equalizer Band 2 Coefficient B1 */
	अणु 0x5A, 0x00 पूर्ण, /* 5A Equalizer Band 2 Coefficient B1 */
	अणु 0x5B, 0x00 पूर्ण, /* 5B Equalizer Band 2 Coefficient B2 */
	अणु 0x5C, 0x00 पूर्ण, /* 5C Equalizer Band 2 Coefficient B2 */
	अणु 0x5D, 0x00 पूर्ण, /* 5D Equalizer Band 2 Coefficient B2 */
	अणु 0x5E, 0x00 पूर्ण, /* 5E Equalizer Band 2 Coefficient A1 */
	अणु 0x5F, 0x00 पूर्ण, /* 5F Equalizer Band 2 Coefficient A1 */

	अणु 0x60, 0x00 पूर्ण, /* 60 Equalizer Band 2 Coefficient A1 */
	अणु 0x61, 0x00 पूर्ण, /* 61 Equalizer Band 2 Coefficient A2 */
	अणु 0x62, 0x00 पूर्ण, /* 62 Equalizer Band 2 Coefficient A2 */
	अणु 0x63, 0x00 पूर्ण, /* 63 Equalizer Band 2 Coefficient A2 */
	अणु 0x64, 0x00 पूर्ण, /* 64 Equalizer Band 3 Coefficient B0 */
	अणु 0x65, 0x00 पूर्ण, /* 65 Equalizer Band 3 Coefficient B0 */
	अणु 0x66, 0x00 पूर्ण, /* 66 Equalizer Band 3 Coefficient B0 */
	अणु 0x67, 0x00 पूर्ण, /* 67 Equalizer Band 3 Coefficient B1 */
	अणु 0x68, 0x00 पूर्ण, /* 68 Equalizer Band 3 Coefficient B1 */
	अणु 0x69, 0x00 पूर्ण, /* 69 Equalizer Band 3 Coefficient B1 */
	अणु 0x6A, 0x00 पूर्ण, /* 6A Equalizer Band 3 Coefficient B2 */
	अणु 0x6B, 0x00 पूर्ण, /* 6B Equalizer Band 3 Coefficient B2 */
	अणु 0x6C, 0x00 पूर्ण, /* 6C Equalizer Band 3 Coefficient B2 */
	अणु 0x6D, 0x00 पूर्ण, /* 6D Equalizer Band 3 Coefficient A1 */
	अणु 0x6E, 0x00 पूर्ण, /* 6E Equalizer Band 3 Coefficient A1 */
	अणु 0x6F, 0x00 पूर्ण, /* 6F Equalizer Band 3 Coefficient A1 */

	अणु 0x70, 0x00 पूर्ण, /* 70 Equalizer Band 3 Coefficient A2 */
	अणु 0x71, 0x00 पूर्ण, /* 71 Equalizer Band 3 Coefficient A2 */
	अणु 0x72, 0x00 पूर्ण, /* 72 Equalizer Band 3 Coefficient A2 */
	अणु 0x73, 0x00 पूर्ण, /* 73 Equalizer Band 4 Coefficient B0 */
	अणु 0x74, 0x00 पूर्ण, /* 74 Equalizer Band 4 Coefficient B0 */
	अणु 0x75, 0x00 पूर्ण, /* 75 Equalizer Band 4 Coefficient B0 */
	अणु 0x76, 0x00 पूर्ण, /* 76 Equalizer Band 4 Coefficient B1 */
	अणु 0x77, 0x00 पूर्ण, /* 77 Equalizer Band 4 Coefficient B1 */
	अणु 0x78, 0x00 पूर्ण, /* 78 Equalizer Band 4 Coefficient B1 */
	अणु 0x79, 0x00 पूर्ण, /* 79 Equalizer Band 4 Coefficient B2 */
	अणु 0x7A, 0x00 पूर्ण, /* 7A Equalizer Band 4 Coefficient B2 */
	अणु 0x7B, 0x00 पूर्ण, /* 7B Equalizer Band 4 Coefficient B2 */
	अणु 0x7C, 0x00 पूर्ण, /* 7C Equalizer Band 4 Coefficient A1 */
	अणु 0x7D, 0x00 पूर्ण, /* 7D Equalizer Band 4 Coefficient A1 */
	अणु 0x7E, 0x00 पूर्ण, /* 7E Equalizer Band 4 Coefficient A1 */
	अणु 0x7F, 0x00 पूर्ण, /* 7F Equalizer Band 4 Coefficient A2 */

	अणु 0x80, 0x00 पूर्ण, /* 80 Equalizer Band 4 Coefficient A2 */
	अणु 0x81, 0x00 पूर्ण, /* 81 Equalizer Band 4 Coefficient A2 */
	अणु 0x82, 0x00 पूर्ण, /* 82 Equalizer Band 5 Coefficient B0 */
	अणु 0x83, 0x00 पूर्ण, /* 83 Equalizer Band 5 Coefficient B0 */
	अणु 0x84, 0x00 पूर्ण, /* 84 Equalizer Band 5 Coefficient B0 */
	अणु 0x85, 0x00 पूर्ण, /* 85 Equalizer Band 5 Coefficient B1 */
	अणु 0x86, 0x00 पूर्ण, /* 86 Equalizer Band 5 Coefficient B1 */
	अणु 0x87, 0x00 पूर्ण, /* 87 Equalizer Band 5 Coefficient B1 */
	अणु 0x88, 0x00 पूर्ण, /* 88 Equalizer Band 5 Coefficient B2 */
	अणु 0x89, 0x00 पूर्ण, /* 89 Equalizer Band 5 Coefficient B2 */
	अणु 0x8A, 0x00 पूर्ण, /* 8A Equalizer Band 5 Coefficient B2 */
	अणु 0x8B, 0x00 पूर्ण, /* 8B Equalizer Band 5 Coefficient A1 */
	अणु 0x8C, 0x00 पूर्ण, /* 8C Equalizer Band 5 Coefficient A1 */
	अणु 0x8D, 0x00 पूर्ण, /* 8D Equalizer Band 5 Coefficient A1 */
	अणु 0x8E, 0x00 पूर्ण, /* 8E Equalizer Band 5 Coefficient A2 */
	अणु 0x8F, 0x00 पूर्ण, /* 8F Equalizer Band 5 Coefficient A2 */

	अणु 0x90, 0x00 पूर्ण, /* 90 Equalizer Band 5 Coefficient A2 */
	अणु 0x91, 0x00 पूर्ण, /* 91 Equalizer Band 6 Coefficient B0 */
	अणु 0x92, 0x00 पूर्ण, /* 92 Equalizer Band 6 Coefficient B0 */
	अणु 0x93, 0x00 पूर्ण, /* 93 Equalizer Band 6 Coefficient B0 */
	अणु 0x94, 0x00 पूर्ण, /* 94 Equalizer Band 6 Coefficient B1 */
	अणु 0x95, 0x00 पूर्ण, /* 95 Equalizer Band 6 Coefficient B1 */
	अणु 0x96, 0x00 पूर्ण, /* 96 Equalizer Band 6 Coefficient B1 */
	अणु 0x97, 0x00 पूर्ण, /* 97 Equalizer Band 6 Coefficient B2 */
	अणु 0x98, 0x00 पूर्ण, /* 98 Equalizer Band 6 Coefficient B2 */
	अणु 0x99, 0x00 पूर्ण, /* 99 Equalizer Band 6 Coefficient B2 */
	अणु 0x9A, 0x00 पूर्ण, /* 9A Equalizer Band 6 Coefficient A1 */
	अणु 0x9B, 0x00 पूर्ण, /* 9B Equalizer Band 6 Coefficient A1 */
	अणु 0x9C, 0x00 पूर्ण, /* 9C Equalizer Band 6 Coefficient A1 */
	अणु 0x9D, 0x00 पूर्ण, /* 9D Equalizer Band 6 Coefficient A2 */
	अणु 0x9E, 0x00 पूर्ण, /* 9E Equalizer Band 6 Coefficient A2 */
	अणु 0x9F, 0x00 पूर्ण, /* 9F Equalizer Band 6 Coefficient A2 */

	अणु 0xA0, 0x00 पूर्ण, /* A0 Equalizer Band 7 Coefficient B0 */
	अणु 0xA1, 0x00 पूर्ण, /* A1 Equalizer Band 7 Coefficient B0 */
	अणु 0xA2, 0x00 पूर्ण, /* A2 Equalizer Band 7 Coefficient B0 */
	अणु 0xA3, 0x00 पूर्ण, /* A3 Equalizer Band 7 Coefficient B1 */
	अणु 0xA4, 0x00 पूर्ण, /* A4 Equalizer Band 7 Coefficient B1 */
	अणु 0xA5, 0x00 पूर्ण, /* A5 Equalizer Band 7 Coefficient B1 */
	अणु 0xA6, 0x00 पूर्ण, /* A6 Equalizer Band 7 Coefficient B2 */
	अणु 0xA7, 0x00 पूर्ण, /* A7 Equalizer Band 7 Coefficient B2 */
	अणु 0xA8, 0x00 पूर्ण, /* A8 Equalizer Band 7 Coefficient B2 */
	अणु 0xA9, 0x00 पूर्ण, /* A9 Equalizer Band 7 Coefficient A1 */
	अणु 0xAA, 0x00 पूर्ण, /* AA Equalizer Band 7 Coefficient A1 */
	अणु 0xAB, 0x00 पूर्ण, /* AB Equalizer Band 7 Coefficient A1 */
	अणु 0xAC, 0x00 पूर्ण, /* AC Equalizer Band 7 Coefficient A2 */
	अणु 0xAD, 0x00 पूर्ण, /* AD Equalizer Band 7 Coefficient A2 */
	अणु 0xAE, 0x00 पूर्ण, /* AE Equalizer Band 7 Coefficient A2 */
	अणु 0xAF, 0x00 पूर्ण, /* AF ADC Biquad Coefficient B0 */

	अणु 0xB0, 0x00 पूर्ण, /* B0 ADC Biquad Coefficient B0 */
	अणु 0xB1, 0x00 पूर्ण, /* B1 ADC Biquad Coefficient B0 */
	अणु 0xB2, 0x00 पूर्ण, /* B2 ADC Biquad Coefficient B1 */
	अणु 0xB3, 0x00 पूर्ण, /* B3 ADC Biquad Coefficient B1 */
	अणु 0xB4, 0x00 पूर्ण, /* B4 ADC Biquad Coefficient B1 */
	अणु 0xB5, 0x00 पूर्ण, /* B5 ADC Biquad Coefficient B2 */
	अणु 0xB6, 0x00 पूर्ण, /* B6 ADC Biquad Coefficient B2 */
	अणु 0xB7, 0x00 पूर्ण, /* B7 ADC Biquad Coefficient B2 */
	अणु 0xB8, 0x00 पूर्ण, /* B8 ADC Biquad Coefficient A1 */
	अणु 0xB9, 0x00 पूर्ण, /* B9 ADC Biquad Coefficient A1 */
	अणु 0xBA, 0x00 पूर्ण, /* BA ADC Biquad Coefficient A1 */
	अणु 0xBB, 0x00 पूर्ण, /* BB ADC Biquad Coefficient A2 */
	अणु 0xBC, 0x00 पूर्ण, /* BC ADC Biquad Coefficient A2 */
	अणु 0xBD, 0x00 पूर्ण, /* BD ADC Biquad Coefficient A2 */
	अणु 0xBE, 0x00 पूर्ण, /* BE Digital Mic 3 Volume */
	अणु 0xBF, 0x00 पूर्ण, /* BF Digital Mic 4 Volume */

	अणु 0xC0, 0x00 पूर्ण, /* C0 Digital Mic 34 Biquad Pre Atten */
	अणु 0xC1, 0x00 पूर्ण, /* C1 Record TDM Slot */
	अणु 0xC2, 0x00 पूर्ण, /* C2 Sample Rate */
	अणु 0xC3, 0x00 पूर्ण, /* C3 Digital Mic 34 Biquad Coefficient C3 */
	अणु 0xC4, 0x00 पूर्ण, /* C4 Digital Mic 34 Biquad Coefficient C4 */
	अणु 0xC5, 0x00 पूर्ण, /* C5 Digital Mic 34 Biquad Coefficient C5 */
	अणु 0xC6, 0x00 पूर्ण, /* C6 Digital Mic 34 Biquad Coefficient C6 */
	अणु 0xC7, 0x00 पूर्ण, /* C7 Digital Mic 34 Biquad Coefficient C7 */
	अणु 0xC8, 0x00 पूर्ण, /* C8 Digital Mic 34 Biquad Coefficient C8 */
	अणु 0xC9, 0x00 पूर्ण, /* C9 Digital Mic 34 Biquad Coefficient C9 */
	अणु 0xCA, 0x00 पूर्ण, /* CA Digital Mic 34 Biquad Coefficient CA */
	अणु 0xCB, 0x00 पूर्ण, /* CB Digital Mic 34 Biquad Coefficient CB */
	अणु 0xCC, 0x00 पूर्ण, /* CC Digital Mic 34 Biquad Coefficient CC */
	अणु 0xCD, 0x00 पूर्ण, /* CD Digital Mic 34 Biquad Coefficient CD */
	अणु 0xCE, 0x00 पूर्ण, /* CE Digital Mic 34 Biquad Coefficient CE */
	अणु 0xCF, 0x00 पूर्ण, /* CF Digital Mic 34 Biquad Coefficient CF */

	अणु 0xD0, 0x00 पूर्ण, /* D0 Digital Mic 34 Biquad Coefficient D0 */
	अणु 0xD1, 0x00 पूर्ण, /* D1 Digital Mic 34 Biquad Coefficient D1 */
पूर्ण;

अटल bool max98090_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल M98090_REG_SOFTWARE_RESET:
	हाल M98090_REG_DEVICE_STATUS:
	हाल M98090_REG_JACK_STATUS:
	हाल M98090_REG_REVISION_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max98090_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल M98090_REG_DEVICE_STATUS ... M98090_REG_INTERRUPT_S:
	हाल M98090_REG_LINE_INPUT_CONFIG ... 0xD1:
	हाल M98090_REG_REVISION_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक max98090_reset(काष्ठा max98090_priv *max98090)
अणु
	पूर्णांक ret;

	/* Reset the codec by writing to this ग_लिखो-only reset रेजिस्टर */
	ret = regmap_ग_लिखो(max98090->regmap, M98090_REG_SOFTWARE_RESET,
		M98090_SWRESET_MASK);
	अगर (ret < 0) अणु
		dev_err(max98090->component->dev,
			"Failed to reset codec: %d\n", ret);
		वापस ret;
	पूर्ण

	msleep(20);
	वापस ret;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_RANGE(max98090_micboost_tlv,
	0, 1, TLV_DB_SCALE_ITEM(0, 2000, 0),
	2, 2, TLV_DB_SCALE_ITEM(3000, 0, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(max98090_mic_tlv, 0, 100, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(max98090_line_single_ended_tlv,
	-600, 600, 0);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98090_line_tlv,
	0, 3, TLV_DB_SCALE_ITEM(-600, 300, 0),
	4, 5, TLV_DB_SCALE_ITEM(1400, 600, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(max98090_avg_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(max98090_av_tlv, -1200, 100, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(max98090_dvg_tlv, 0, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(max98090_dv_tlv, -1500, 100, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(max98090_alcmakeup_tlv, 0, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(max98090_alccomp_tlv, -3100, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(max98090_drcexp_tlv, -6600, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(max98090_sdg_tlv, 50, 200, 0);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98090_mixout_tlv,
	0, 1, TLV_DB_SCALE_ITEM(-1200, 250, 0),
	2, 3, TLV_DB_SCALE_ITEM(-600, 600, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98090_hp_tlv,
	0, 6, TLV_DB_SCALE_ITEM(-6700, 400, 0),
	7, 14, TLV_DB_SCALE_ITEM(-4000, 300, 0),
	15, 21, TLV_DB_SCALE_ITEM(-1700, 200, 0),
	22, 27, TLV_DB_SCALE_ITEM(-400, 100, 0),
	28, 31, TLV_DB_SCALE_ITEM(150, 50, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98090_spk_tlv,
	0, 4, TLV_DB_SCALE_ITEM(-4800, 400, 0),
	5, 10, TLV_DB_SCALE_ITEM(-2900, 300, 0),
	11, 14, TLV_DB_SCALE_ITEM(-1200, 200, 0),
	15, 29, TLV_DB_SCALE_ITEM(-500, 100, 0),
	30, 39, TLV_DB_SCALE_ITEM(950, 50, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98090_rcv_lout_tlv,
	0, 6, TLV_DB_SCALE_ITEM(-6200, 400, 0),
	7, 14, TLV_DB_SCALE_ITEM(-3500, 300, 0),
	15, 21, TLV_DB_SCALE_ITEM(-1200, 200, 0),
	22, 27, TLV_DB_SCALE_ITEM(100, 100, 0),
	28, 31, TLV_DB_SCALE_ITEM(650, 50, 0)
);

अटल पूर्णांक max98090_get_enab_tlv(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक mask = (1 << fls(mc->max)) - 1;
	अचिन्हित पूर्णांक val = snd_soc_component_पढ़ो(component, mc->reg);
	अचिन्हित पूर्णांक *select;

	चयन (mc->reg) अणु
	हाल M98090_REG_MIC1_INPUT_LEVEL:
		select = &(max98090->pa1en);
		अवरोध;
	हाल M98090_REG_MIC2_INPUT_LEVEL:
		select = &(max98090->pa2en);
		अवरोध;
	हाल M98090_REG_ADC_SIDETONE:
		select = &(max98090->sidetone);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = (val >> mc->shअगरt) & mask;

	अगर (val >= 1) अणु
		/* If on, वापस the volume */
		val = val - 1;
		*select = val;
	पूर्ण अन्यथा अणु
		/* If off, वापस last stored value */
		val = *select;
	पूर्ण

	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक max98090_put_enab_tlv(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक mask = (1 << fls(mc->max)) - 1;
	अचिन्हित पूर्णांक sel = ucontrol->value.पूर्णांकeger.value[0];
	अचिन्हित पूर्णांक val = snd_soc_component_पढ़ो(component, mc->reg);
	अचिन्हित पूर्णांक *select;

	चयन (mc->reg) अणु
	हाल M98090_REG_MIC1_INPUT_LEVEL:
		select = &(max98090->pa1en);
		अवरोध;
	हाल M98090_REG_MIC2_INPUT_LEVEL:
		select = &(max98090->pa2en);
		अवरोध;
	हाल M98090_REG_ADC_SIDETONE:
		select = &(max98090->sidetone);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = (val >> mc->shअगरt) & mask;

	*select = sel;

	/* Setting a volume is only valid अगर it is alपढ़ोy On */
	अगर (val >= 1) अणु
		sel = sel + 1;
	पूर्ण अन्यथा अणु
		/* Write what was alपढ़ोy there */
		sel = val;
	पूर्ण

	snd_soc_component_update_bits(component, mc->reg,
		mask << mc->shअगरt,
		sel << mc->shअगरt);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *max98090_perf_pwr_text[] =
	अणु "High Performance", "Low Power" पूर्ण;
अटल स्थिर अक्षर *max98090_pwr_perf_text[] =
	अणु "Low Power", "High Performance" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98090_vcmbandgap_क्रमागत,
			    M98090_REG_BIAS_CONTROL,
			    M98090_VCM_MODE_SHIFT,
			    max98090_pwr_perf_text);

अटल स्थिर अक्षर *max98090_osr128_text[] = अणु "64*fs", "128*fs" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98090_osr128_क्रमागत,
			    M98090_REG_ADC_CONTROL,
			    M98090_OSR128_SHIFT,
			    max98090_osr128_text);

अटल स्थिर अक्षर *max98090_mode_text[] = अणु "Voice", "Music" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98090_mode_क्रमागत,
			    M98090_REG_FILTER_CONFIG,
			    M98090_MODE_SHIFT,
			    max98090_mode_text);

अटल SOC_ENUM_SINGLE_DECL(max98090_filter_dmic34mode_क्रमागत,
			    M98090_REG_FILTER_CONFIG,
			    M98090_FLT_DMIC34MODE_SHIFT,
			    max98090_mode_text);

अटल स्थिर अक्षर *max98090_drcatk_text[] =
	अणु "0.5ms", "1ms", "5ms", "10ms", "25ms", "50ms", "100ms", "200ms" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98090_drcatk_क्रमागत,
			    M98090_REG_DRC_TIMING,
			    M98090_DRCATK_SHIFT,
			    max98090_drcatk_text);

अटल स्थिर अक्षर *max98090_drcrls_text[] =
	अणु "8s", "4s", "2s", "1s", "0.5s", "0.25s", "0.125s", "0.0625s" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98090_drcrls_क्रमागत,
			    M98090_REG_DRC_TIMING,
			    M98090_DRCRLS_SHIFT,
			    max98090_drcrls_text);

अटल स्थिर अक्षर *max98090_alccmp_text[] =
	अणु "1:1", "1:1.5", "1:2", "1:4", "1:INF" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98090_alccmp_क्रमागत,
			    M98090_REG_DRC_COMPRESSOR,
			    M98090_DRCCMP_SHIFT,
			    max98090_alccmp_text);

अटल स्थिर अक्षर *max98090_drcexp_text[] = अणु "1:1", "2:1", "3:1" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98090_drcexp_क्रमागत,
			    M98090_REG_DRC_EXPANDER,
			    M98090_DRCEXP_SHIFT,
			    max98090_drcexp_text);

अटल SOC_ENUM_SINGLE_DECL(max98090_dac_perभ_शेषe_क्रमागत,
			    M98090_REG_DAC_CONTROL,
			    M98090_PERFMODE_SHIFT,
			    max98090_perf_pwr_text);

अटल SOC_ENUM_SINGLE_DECL(max98090_dachp_क्रमागत,
			    M98090_REG_DAC_CONTROL,
			    M98090_DACHP_SHIFT,
			    max98090_pwr_perf_text);

अटल SOC_ENUM_SINGLE_DECL(max98090_adchp_क्रमागत,
			    M98090_REG_ADC_CONTROL,
			    M98090_ADCHP_SHIFT,
			    max98090_pwr_perf_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_snd_controls[] = अणु
	SOC_ENUM("MIC Bias VCM Bandgap", max98090_vcmbandgap_क्रमागत),

	SOC_SINGLE("DMIC MIC Comp Filter Config", M98090_REG_DIGITAL_MIC_CONFIG,
		M98090_DMIC_COMP_SHIFT, M98090_DMIC_COMP_NUM - 1, 0),

	SOC_SINGLE_EXT_TLV("MIC1 Boost Volume",
		M98090_REG_MIC1_INPUT_LEVEL, M98090_MIC_PA1EN_SHIFT,
		M98090_MIC_PA1EN_NUM - 1, 0, max98090_get_enab_tlv,
		max98090_put_enab_tlv, max98090_micboost_tlv),

	SOC_SINGLE_EXT_TLV("MIC2 Boost Volume",
		M98090_REG_MIC2_INPUT_LEVEL, M98090_MIC_PA2EN_SHIFT,
		M98090_MIC_PA2EN_NUM - 1, 0, max98090_get_enab_tlv,
		max98090_put_enab_tlv, max98090_micboost_tlv),

	SOC_SINGLE_TLV("MIC1 Volume", M98090_REG_MIC1_INPUT_LEVEL,
		M98090_MIC_PGAM1_SHIFT, M98090_MIC_PGAM1_NUM - 1, 1,
		max98090_mic_tlv),

	SOC_SINGLE_TLV("MIC2 Volume", M98090_REG_MIC2_INPUT_LEVEL,
		M98090_MIC_PGAM2_SHIFT, M98090_MIC_PGAM2_NUM - 1, 1,
		max98090_mic_tlv),

	SOC_SINGLE_RANGE_TLV("LINEA Single Ended Volume",
		M98090_REG_LINE_INPUT_LEVEL, M98090_MIXG135_SHIFT, 0,
		M98090_MIXG135_NUM - 1, 1, max98090_line_single_ended_tlv),

	SOC_SINGLE_RANGE_TLV("LINEB Single Ended Volume",
		M98090_REG_LINE_INPUT_LEVEL, M98090_MIXG246_SHIFT, 0,
		M98090_MIXG246_NUM - 1, 1, max98090_line_single_ended_tlv),

	SOC_SINGLE_RANGE_TLV("LINEA Volume", M98090_REG_LINE_INPUT_LEVEL,
		M98090_LINAPGA_SHIFT, 0, M98090_LINAPGA_NUM - 1, 1,
		max98090_line_tlv),

	SOC_SINGLE_RANGE_TLV("LINEB Volume", M98090_REG_LINE_INPUT_LEVEL,
		M98090_LINBPGA_SHIFT, 0, M98090_LINBPGA_NUM - 1, 1,
		max98090_line_tlv),

	SOC_SINGLE("LINEA Ext Resistor Gain Mode", M98090_REG_INPUT_MODE,
		M98090_EXTBUFA_SHIFT, M98090_EXTBUFA_NUM - 1, 0),
	SOC_SINGLE("LINEB Ext Resistor Gain Mode", M98090_REG_INPUT_MODE,
		M98090_EXTBUFB_SHIFT, M98090_EXTBUFB_NUM - 1, 0),

	SOC_SINGLE_TLV("ADCL Boost Volume", M98090_REG_LEFT_ADC_LEVEL,
		M98090_AVLG_SHIFT, M98090_AVLG_NUM - 1, 0,
		max98090_avg_tlv),
	SOC_SINGLE_TLV("ADCR Boost Volume", M98090_REG_RIGHT_ADC_LEVEL,
		M98090_AVRG_SHIFT, M98090_AVLG_NUM - 1, 0,
		max98090_avg_tlv),

	SOC_SINGLE_TLV("ADCL Volume", M98090_REG_LEFT_ADC_LEVEL,
		M98090_AVL_SHIFT, M98090_AVL_NUM - 1, 1,
		max98090_av_tlv),
	SOC_SINGLE_TLV("ADCR Volume", M98090_REG_RIGHT_ADC_LEVEL,
		M98090_AVR_SHIFT, M98090_AVR_NUM - 1, 1,
		max98090_av_tlv),

	SOC_ENUM("ADC Oversampling Rate", max98090_osr128_क्रमागत),
	SOC_SINGLE("ADC Quantizer Dither", M98090_REG_ADC_CONTROL,
		M98090_ADCDITHER_SHIFT, M98090_ADCDITHER_NUM - 1, 0),
	SOC_ENUM("ADC High Performance Mode", max98090_adchp_क्रमागत),

	SOC_SINGLE("DAC Mono Mode", M98090_REG_IO_CONFIGURATION,
		M98090_DMONO_SHIFT, M98090_DMONO_NUM - 1, 0),
	SOC_SINGLE("SDIN Mode", M98090_REG_IO_CONFIGURATION,
		M98090_SDIEN_SHIFT, M98090_SDIEN_NUM - 1, 0),
	SOC_SINGLE("SDOUT Mode", M98090_REG_IO_CONFIGURATION,
		M98090_SDOEN_SHIFT, M98090_SDOEN_NUM - 1, 0),
	SOC_SINGLE("SDOUT Hi-Z Mode", M98090_REG_IO_CONFIGURATION,
		M98090_HIZOFF_SHIFT, M98090_HIZOFF_NUM - 1, 1),
	SOC_ENUM("Filter Mode", max98090_mode_क्रमागत),
	SOC_SINGLE("Record Path DC Blocking", M98090_REG_FILTER_CONFIG,
		M98090_AHPF_SHIFT, M98090_AHPF_NUM - 1, 0),
	SOC_SINGLE("Playback Path DC Blocking", M98090_REG_FILTER_CONFIG,
		M98090_DHPF_SHIFT, M98090_DHPF_NUM - 1, 0),
	SOC_SINGLE_TLV("Digital BQ Volume", M98090_REG_ADC_BIQUAD_LEVEL,
		M98090_AVBQ_SHIFT, M98090_AVBQ_NUM - 1, 1, max98090_dv_tlv),
	SOC_SINGLE_EXT_TLV("Digital Sidetone Volume",
		M98090_REG_ADC_SIDETONE, M98090_DVST_SHIFT,
		M98090_DVST_NUM - 1, 1, max98090_get_enab_tlv,
		max98090_put_enab_tlv, max98090_sdg_tlv),
	SOC_SINGLE_TLV("Digital Coarse Volume", M98090_REG_DAI_PLAYBACK_LEVEL,
		M98090_DVG_SHIFT, M98090_DVG_NUM - 1, 0,
		max98090_dvg_tlv),
	SOC_SINGLE_TLV("Digital Volume", M98090_REG_DAI_PLAYBACK_LEVEL,
		M98090_DV_SHIFT, M98090_DV_NUM - 1, 1,
		max98090_dv_tlv),
	SND_SOC_BYTES("EQ Coefficients", M98090_REG_EQUALIZER_BASE, 105),
	SOC_SINGLE("Digital EQ 3 Band Switch", M98090_REG_DSP_FILTER_ENABLE,
		M98090_EQ3BANDEN_SHIFT, M98090_EQ3BANDEN_NUM - 1, 0),
	SOC_SINGLE("Digital EQ 5 Band Switch", M98090_REG_DSP_FILTER_ENABLE,
		M98090_EQ5BANDEN_SHIFT, M98090_EQ5BANDEN_NUM - 1, 0),
	SOC_SINGLE("Digital EQ 7 Band Switch", M98090_REG_DSP_FILTER_ENABLE,
		M98090_EQ7BANDEN_SHIFT, M98090_EQ7BANDEN_NUM - 1, 0),
	SOC_SINGLE("Digital EQ Clipping Detection", M98090_REG_DAI_PLAYBACK_LEVEL_EQ,
		M98090_EQCLPN_SHIFT, M98090_EQCLPN_NUM - 1,
		1),
	SOC_SINGLE_TLV("Digital EQ Volume", M98090_REG_DAI_PLAYBACK_LEVEL_EQ,
		M98090_DVEQ_SHIFT, M98090_DVEQ_NUM - 1, 1,
		max98090_dv_tlv),

	SOC_SINGLE("ALC Enable", M98090_REG_DRC_TIMING,
		M98090_DRCEN_SHIFT, M98090_DRCEN_NUM - 1, 0),
	SOC_ENUM("ALC Attack Time", max98090_drcatk_क्रमागत),
	SOC_ENUM("ALC Release Time", max98090_drcrls_क्रमागत),
	SOC_SINGLE_TLV("ALC Make Up Volume", M98090_REG_DRC_GAIN,
		M98090_DRCG_SHIFT, M98090_DRCG_NUM - 1, 0,
		max98090_alcmakeup_tlv),
	SOC_ENUM("ALC Compression Ratio", max98090_alccmp_क्रमागत),
	SOC_ENUM("ALC Expansion Ratio", max98090_drcexp_क्रमागत),
	SOC_SINGLE_TLV("ALC Compression Threshold Volume",
		M98090_REG_DRC_COMPRESSOR, M98090_DRCTHC_SHIFT,
		M98090_DRCTHC_NUM - 1, 1, max98090_alccomp_tlv),
	SOC_SINGLE_TLV("ALC Expansion Threshold Volume",
		M98090_REG_DRC_EXPANDER, M98090_DRCTHE_SHIFT,
		M98090_DRCTHE_NUM - 1, 1, max98090_drcexp_tlv),

	SOC_ENUM("DAC HP Playback Performance Mode",
		max98090_dac_perभ_शेषe_क्रमागत),
	SOC_ENUM("DAC High Performance Mode", max98090_dachp_क्रमागत),

	SOC_SINGLE_TLV("Headphone Left Mixer Volume",
		M98090_REG_HP_CONTROL, M98090_MIXHPLG_SHIFT,
		M98090_MIXHPLG_NUM - 1, 1, max98090_mixout_tlv),
	SOC_SINGLE_TLV("Headphone Right Mixer Volume",
		M98090_REG_HP_CONTROL, M98090_MIXHPRG_SHIFT,
		M98090_MIXHPRG_NUM - 1, 1, max98090_mixout_tlv),

	SOC_SINGLE_TLV("Speaker Left Mixer Volume",
		M98090_REG_SPK_CONTROL, M98090_MIXSPLG_SHIFT,
		M98090_MIXSPLG_NUM - 1, 1, max98090_mixout_tlv),
	SOC_SINGLE_TLV("Speaker Right Mixer Volume",
		M98090_REG_SPK_CONTROL, M98090_MIXSPRG_SHIFT,
		M98090_MIXSPRG_NUM - 1, 1, max98090_mixout_tlv),

	SOC_SINGLE_TLV("Receiver Left Mixer Volume",
		M98090_REG_RCV_LOUTL_CONTROL, M98090_MIXRCVLG_SHIFT,
		M98090_MIXRCVLG_NUM - 1, 1, max98090_mixout_tlv),
	SOC_SINGLE_TLV("Receiver Right Mixer Volume",
		M98090_REG_LOUTR_CONTROL, M98090_MIXRCVRG_SHIFT,
		M98090_MIXRCVRG_NUM - 1, 1, max98090_mixout_tlv),

	SOC_DOUBLE_R_TLV("Headphone Volume", M98090_REG_LEFT_HP_VOLUME,
		M98090_REG_RIGHT_HP_VOLUME, M98090_HPVOLL_SHIFT,
		M98090_HPVOLL_NUM - 1, 0, max98090_hp_tlv),

	SOC_DOUBLE_R_RANGE_TLV("Speaker Volume",
		M98090_REG_LEFT_SPK_VOLUME, M98090_REG_RIGHT_SPK_VOLUME,
		M98090_SPVOLL_SHIFT, 24, M98090_SPVOLL_NUM - 1 + 24,
		0, max98090_spk_tlv),

	SOC_DOUBLE_R_TLV("Receiver Volume", M98090_REG_RCV_LOUTL_VOLUME,
		M98090_REG_LOUTR_VOLUME, M98090_RCVLVOL_SHIFT,
		M98090_RCVLVOL_NUM - 1, 0, max98090_rcv_lout_tlv),

	SOC_SINGLE("Headphone Left Switch", M98090_REG_LEFT_HP_VOLUME,
		M98090_HPLM_SHIFT, 1, 1),
	SOC_SINGLE("Headphone Right Switch", M98090_REG_RIGHT_HP_VOLUME,
		M98090_HPRM_SHIFT, 1, 1),

	SOC_SINGLE("Speaker Left Switch", M98090_REG_LEFT_SPK_VOLUME,
		M98090_SPLM_SHIFT, 1, 1),
	SOC_SINGLE("Speaker Right Switch", M98090_REG_RIGHT_SPK_VOLUME,
		M98090_SPRM_SHIFT, 1, 1),

	SOC_SINGLE("Receiver Left Switch", M98090_REG_RCV_LOUTL_VOLUME,
		M98090_RCVLM_SHIFT, 1, 1),
	SOC_SINGLE("Receiver Right Switch", M98090_REG_LOUTR_VOLUME,
		M98090_RCVRM_SHIFT, 1, 1),

	SOC_SINGLE("Zero-Crossing Detection", M98090_REG_LEVEL_CONTROL,
		M98090_ZDENN_SHIFT, M98090_ZDENN_NUM - 1, 1),
	SOC_SINGLE("Enhanced Vol Smoothing", M98090_REG_LEVEL_CONTROL,
		M98090_VS2ENN_SHIFT, M98090_VS2ENN_NUM - 1, 1),
	SOC_SINGLE("Volume Adjustment Smoothing", M98090_REG_LEVEL_CONTROL,
		M98090_VSENN_SHIFT, M98090_VSENN_NUM - 1, 1),

	SND_SOC_BYTES("Biquad Coefficients", M98090_REG_RECORD_BIQUAD_BASE, 15),
	SOC_SINGLE("Biquad Switch", M98090_REG_DSP_FILTER_ENABLE,
		M98090_ADCBQEN_SHIFT, M98090_ADCBQEN_NUM - 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new max98091_snd_controls[] = अणु

	SOC_SINGLE("DMIC34 Zeropad", M98090_REG_SAMPLE_RATE,
		M98090_DMIC34_ZEROPAD_SHIFT,
		M98090_DMIC34_ZEROPAD_NUM - 1, 0),

	SOC_ENUM("Filter DMIC34 Mode", max98090_filter_dmic34mode_क्रमागत),
	SOC_SINGLE("DMIC34 DC Blocking", M98090_REG_FILTER_CONFIG,
		M98090_FLT_DMIC34HPF_SHIFT,
		M98090_FLT_DMIC34HPF_NUM - 1, 0),

	SOC_SINGLE_TLV("DMIC3 Boost Volume", M98090_REG_DMIC3_VOLUME,
		M98090_DMIC_AV3G_SHIFT, M98090_DMIC_AV3G_NUM - 1, 0,
		max98090_avg_tlv),
	SOC_SINGLE_TLV("DMIC4 Boost Volume", M98090_REG_DMIC4_VOLUME,
		M98090_DMIC_AV4G_SHIFT, M98090_DMIC_AV4G_NUM - 1, 0,
		max98090_avg_tlv),

	SOC_SINGLE_TLV("DMIC3 Volume", M98090_REG_DMIC3_VOLUME,
		M98090_DMIC_AV3_SHIFT, M98090_DMIC_AV3_NUM - 1, 1,
		max98090_av_tlv),
	SOC_SINGLE_TLV("DMIC4 Volume", M98090_REG_DMIC4_VOLUME,
		M98090_DMIC_AV4_SHIFT, M98090_DMIC_AV4_NUM - 1, 1,
		max98090_av_tlv),

	SND_SOC_BYTES("DMIC34 Biquad Coefficients",
		M98090_REG_DMIC34_BIQUAD_BASE, 15),
	SOC_SINGLE("DMIC34 Biquad Switch", M98090_REG_DSP_FILTER_ENABLE,
		M98090_DMIC34BQEN_SHIFT, M98090_DMIC34BQEN_NUM - 1, 0),

	SOC_SINGLE_TLV("DMIC34 BQ PreAttenuation Volume",
		M98090_REG_DMIC34_BQ_PREATTEN, M98090_AV34BQ_SHIFT,
		M98090_AV34BQ_NUM - 1, 1, max98090_dv_tlv),
पूर्ण;

अटल पूर्णांक max98090_micinput_event(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	अचिन्हित पूर्णांक val = snd_soc_component_पढ़ो(component, w->reg);

	अगर (w->reg == M98090_REG_MIC1_INPUT_LEVEL)
		val = (val & M98090_MIC_PA1EN_MASK) >> M98090_MIC_PA1EN_SHIFT;
	अन्यथा
		val = (val & M98090_MIC_PA2EN_MASK) >> M98090_MIC_PA2EN_SHIFT;

	अगर (val >= 1) अणु
		अगर (w->reg == M98090_REG_MIC1_INPUT_LEVEL) अणु
			max98090->pa1en = val - 1; /* Update क्रम अस्थिर */
		पूर्ण अन्यथा अणु
			max98090->pa2en = val - 1; /* Update क्रम अस्थिर */
		पूर्ण
	पूर्ण

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* If turning on, set to most recently selected volume */
		अगर (w->reg == M98090_REG_MIC1_INPUT_LEVEL)
			val = max98090->pa1en + 1;
		अन्यथा
			val = max98090->pa2en + 1;
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* If turning off, turn off */
		val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (w->reg == M98090_REG_MIC1_INPUT_LEVEL)
		snd_soc_component_update_bits(component, w->reg, M98090_MIC_PA1EN_MASK,
			val << M98090_MIC_PA1EN_SHIFT);
	अन्यथा
		snd_soc_component_update_bits(component, w->reg, M98090_MIC_PA2EN_MASK,
			val << M98090_MIC_PA2EN_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक max98090_shdn_event(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	अगर (event & SND_SOC_DAPM_POST_PMU)
		max98090->shdn_pending = true;

	वापस 0;

पूर्ण

अटल स्थिर अक्षर *mic1_mux_text[] = अणु "IN12", "IN56" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mic1_mux_क्रमागत,
			    M98090_REG_INPUT_MODE,
			    M98090_EXTMIC1_SHIFT,
			    mic1_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_mic1_mux =
	SOC_DAPM_ENUM("MIC1 Mux", mic1_mux_क्रमागत);

अटल स्थिर अक्षर *mic2_mux_text[] = अणु "IN34", "IN56" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mic2_mux_क्रमागत,
			    M98090_REG_INPUT_MODE,
			    M98090_EXTMIC2_SHIFT,
			    mic2_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_mic2_mux =
	SOC_DAPM_ENUM("MIC2 Mux", mic2_mux_क्रमागत);

अटल स्थिर अक्षर *dmic_mux_text[] = अणु "ADC", "DMIC" पूर्ण;

अटल SOC_ENUM_SINGLE_VIRT_DECL(dmic_mux_क्रमागत, dmic_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_dmic_mux =
	SOC_DAPM_ENUM("DMIC Mux", dmic_mux_क्रमागत);

/* LINEA mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98090_linea_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("IN1 Switch", M98090_REG_LINE_INPUT_CONFIG,
		M98090_IN1SEEN_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("IN3 Switch", M98090_REG_LINE_INPUT_CONFIG,
		M98090_IN3SEEN_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("IN5 Switch", M98090_REG_LINE_INPUT_CONFIG,
		M98090_IN5SEEN_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("IN34 Switch", M98090_REG_LINE_INPUT_CONFIG,
		M98090_IN34DIFF_SHIFT, 1, 0),
पूर्ण;

/* LINEB mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98090_lineb_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("IN2 Switch", M98090_REG_LINE_INPUT_CONFIG,
		M98090_IN2SEEN_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("IN4 Switch", M98090_REG_LINE_INPUT_CONFIG,
		M98090_IN4SEEN_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("IN6 Switch", M98090_REG_LINE_INPUT_CONFIG,
		M98090_IN6SEEN_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("IN56 Switch", M98090_REG_LINE_INPUT_CONFIG,
		M98090_IN56DIFF_SHIFT, 1, 0),
पूर्ण;

/* Left ADC mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98090_left_adc_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("IN12 Switch", M98090_REG_LEFT_ADC_MIXER,
		M98090_MIXADL_IN12DIFF_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("IN34 Switch", M98090_REG_LEFT_ADC_MIXER,
		M98090_MIXADL_IN34DIFF_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("IN56 Switch", M98090_REG_LEFT_ADC_MIXER,
		M98090_MIXADL_IN65DIFF_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEA Switch", M98090_REG_LEFT_ADC_MIXER,
		M98090_MIXADL_LINEA_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEB Switch", M98090_REG_LEFT_ADC_MIXER,
		M98090_MIXADL_LINEB_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98090_REG_LEFT_ADC_MIXER,
		M98090_MIXADL_MIC1_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98090_REG_LEFT_ADC_MIXER,
		M98090_MIXADL_MIC2_SHIFT, 1, 0),
पूर्ण;

/* Right ADC mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98090_right_adc_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("IN12 Switch", M98090_REG_RIGHT_ADC_MIXER,
		M98090_MIXADR_IN12DIFF_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("IN34 Switch", M98090_REG_RIGHT_ADC_MIXER,
		M98090_MIXADR_IN34DIFF_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("IN56 Switch", M98090_REG_RIGHT_ADC_MIXER,
		M98090_MIXADR_IN65DIFF_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEA Switch", M98090_REG_RIGHT_ADC_MIXER,
		M98090_MIXADR_LINEA_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEB Switch", M98090_REG_RIGHT_ADC_MIXER,
		M98090_MIXADR_LINEB_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98090_REG_RIGHT_ADC_MIXER,
		M98090_MIXADR_MIC1_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98090_REG_RIGHT_ADC_MIXER,
		M98090_MIXADR_MIC2_SHIFT, 1, 0),
पूर्ण;

अटल स्थिर अक्षर *lten_mux_text[] = अणु "Normal", "Loopthrough" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ltenl_mux_क्रमागत,
			    M98090_REG_IO_CONFIGURATION,
			    M98090_LTEN_SHIFT,
			    lten_mux_text);

अटल SOC_ENUM_SINGLE_DECL(ltenr_mux_क्रमागत,
			    M98090_REG_IO_CONFIGURATION,
			    M98090_LTEN_SHIFT,
			    lten_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_ltenl_mux =
	SOC_DAPM_ENUM("LTENL Mux", ltenl_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_ltenr_mux =
	SOC_DAPM_ENUM("LTENR Mux", ltenr_mux_क्रमागत);

अटल स्थिर अक्षर *lben_mux_text[] = अणु "Normal", "Loopback" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(lbenl_mux_क्रमागत,
			    M98090_REG_IO_CONFIGURATION,
			    M98090_LBEN_SHIFT,
			    lben_mux_text);

अटल SOC_ENUM_SINGLE_DECL(lbenr_mux_क्रमागत,
			    M98090_REG_IO_CONFIGURATION,
			    M98090_LBEN_SHIFT,
			    lben_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_lbenl_mux =
	SOC_DAPM_ENUM("LBENL Mux", lbenl_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_lbenr_mux =
	SOC_DAPM_ENUM("LBENR Mux", lbenr_mux_क्रमागत);

अटल स्थिर अक्षर *stenl_mux_text[] = अणु "Normal", "Sidetone Left" पूर्ण;

अटल स्थिर अक्षर *stenr_mux_text[] = अणु "Normal", "Sidetone Right" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(stenl_mux_क्रमागत,
			    M98090_REG_ADC_SIDETONE,
			    M98090_DSTSL_SHIFT,
			    stenl_mux_text);

अटल SOC_ENUM_SINGLE_DECL(stenr_mux_क्रमागत,
			    M98090_REG_ADC_SIDETONE,
			    M98090_DSTSR_SHIFT,
			    stenr_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_stenl_mux =
	SOC_DAPM_ENUM("STENL Mux", stenl_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_stenr_mux =
	SOC_DAPM_ENUM("STENR Mux", stenr_mux_क्रमागत);

/* Left speaker mixer चयन */
अटल स्थिर काष्ठा
	snd_kcontrol_new max98090_left_speaker_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC Switch", M98090_REG_LEFT_SPK_MIXER,
		M98090_MIXSPL_DACL_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("Right DAC Switch", M98090_REG_LEFT_SPK_MIXER,
		M98090_MIXSPL_DACR_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEA Switch", M98090_REG_LEFT_SPK_MIXER,
		M98090_MIXSPL_LINEA_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEB Switch", M98090_REG_LEFT_SPK_MIXER,
		M98090_MIXSPL_LINEB_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98090_REG_LEFT_SPK_MIXER,
		M98090_MIXSPL_MIC1_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98090_REG_LEFT_SPK_MIXER,
		M98090_MIXSPL_MIC2_SHIFT, 1, 0),
पूर्ण;

/* Right speaker mixer चयन */
अटल स्थिर काष्ठा
	snd_kcontrol_new max98090_right_speaker_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC Switch", M98090_REG_RIGHT_SPK_MIXER,
		M98090_MIXSPR_DACL_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("Right DAC Switch", M98090_REG_RIGHT_SPK_MIXER,
		M98090_MIXSPR_DACR_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEA Switch", M98090_REG_RIGHT_SPK_MIXER,
		M98090_MIXSPR_LINEA_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEB Switch", M98090_REG_RIGHT_SPK_MIXER,
		M98090_MIXSPR_LINEB_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98090_REG_RIGHT_SPK_MIXER,
		M98090_MIXSPR_MIC1_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98090_REG_RIGHT_SPK_MIXER,
		M98090_MIXSPR_MIC2_SHIFT, 1, 0),
पूर्ण;

/* Left headphone mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98090_left_hp_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC Switch", M98090_REG_LEFT_HP_MIXER,
		M98090_MIXHPL_DACL_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("Right DAC Switch", M98090_REG_LEFT_HP_MIXER,
		M98090_MIXHPL_DACR_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEA Switch", M98090_REG_LEFT_HP_MIXER,
		M98090_MIXHPL_LINEA_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEB Switch", M98090_REG_LEFT_HP_MIXER,
		M98090_MIXHPL_LINEB_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98090_REG_LEFT_HP_MIXER,
		M98090_MIXHPL_MIC1_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98090_REG_LEFT_HP_MIXER,
		M98090_MIXHPL_MIC2_SHIFT, 1, 0),
पूर्ण;

/* Right headphone mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98090_right_hp_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC Switch", M98090_REG_RIGHT_HP_MIXER,
		M98090_MIXHPR_DACL_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("Right DAC Switch", M98090_REG_RIGHT_HP_MIXER,
		M98090_MIXHPR_DACR_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEA Switch", M98090_REG_RIGHT_HP_MIXER,
		M98090_MIXHPR_LINEA_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEB Switch", M98090_REG_RIGHT_HP_MIXER,
		M98090_MIXHPR_LINEB_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98090_REG_RIGHT_HP_MIXER,
		M98090_MIXHPR_MIC1_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98090_REG_RIGHT_HP_MIXER,
		M98090_MIXHPR_MIC2_SHIFT, 1, 0),
पूर्ण;

/* Left receiver mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98090_left_rcv_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC Switch", M98090_REG_RCV_LOUTL_MIXER,
		M98090_MIXRCVL_DACL_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("Right DAC Switch", M98090_REG_RCV_LOUTL_MIXER,
		M98090_MIXRCVL_DACR_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEA Switch", M98090_REG_RCV_LOUTL_MIXER,
		M98090_MIXRCVL_LINEA_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEB Switch", M98090_REG_RCV_LOUTL_MIXER,
		M98090_MIXRCVL_LINEB_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98090_REG_RCV_LOUTL_MIXER,
		M98090_MIXRCVL_MIC1_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98090_REG_RCV_LOUTL_MIXER,
		M98090_MIXRCVL_MIC2_SHIFT, 1, 0),
पूर्ण;

/* Right receiver mixer चयन */
अटल स्थिर काष्ठा snd_kcontrol_new max98090_right_rcv_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Left DAC Switch", M98090_REG_LOUTR_MIXER,
		M98090_MIXRCVR_DACL_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("Right DAC Switch", M98090_REG_LOUTR_MIXER,
		M98090_MIXRCVR_DACR_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEA Switch", M98090_REG_LOUTR_MIXER,
		M98090_MIXRCVR_LINEA_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("LINEB Switch", M98090_REG_LOUTR_MIXER,
		M98090_MIXRCVR_LINEB_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC1 Switch", M98090_REG_LOUTR_MIXER,
		M98090_MIXRCVR_MIC1_SHIFT, 1, 0),
	SOC_DAPM_SINGLE("MIC2 Switch", M98090_REG_LOUTR_MIXER,
		M98090_MIXRCVR_MIC2_SHIFT, 1, 0),
पूर्ण;

अटल स्थिर अक्षर *linmod_mux_text[] = अणु "Left Only", "Left and Right" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(linmod_mux_क्रमागत,
			    M98090_REG_LOUTR_MIXER,
			    M98090_LINMOD_SHIFT,
			    linmod_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_linmod_mux =
	SOC_DAPM_ENUM("LINMOD Mux", linmod_mux_क्रमागत);

अटल स्थिर अक्षर *mixhpsel_mux_text[] = अणु "DAC Only", "HP Mixer" पूर्ण;

/*
 * This is a mux as it selects the HP output, but to DAPM it is a Mixer enable
 */
अटल SOC_ENUM_SINGLE_DECL(mixhplsel_mux_क्रमागत,
			    M98090_REG_HP_CONTROL,
			    M98090_MIXHPLSEL_SHIFT,
			    mixhpsel_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_mixhplsel_mux =
	SOC_DAPM_ENUM("MIXHPLSEL Mux", mixhplsel_mux_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(mixhprsel_mux_क्रमागत,
			    M98090_REG_HP_CONTROL,
			    M98090_MIXHPRSEL_SHIFT,
			    mixhpsel_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98090_mixhprsel_mux =
	SOC_DAPM_ENUM("MIXHPRSEL Mux", mixhprsel_mux_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget max98090_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("DMICL"),
	SND_SOC_DAPM_INPUT("DMICR"),
	SND_SOC_DAPM_INPUT("IN1"),
	SND_SOC_DAPM_INPUT("IN2"),
	SND_SOC_DAPM_INPUT("IN3"),
	SND_SOC_DAPM_INPUT("IN4"),
	SND_SOC_DAPM_INPUT("IN5"),
	SND_SOC_DAPM_INPUT("IN6"),
	SND_SOC_DAPM_INPUT("IN12"),
	SND_SOC_DAPM_INPUT("IN34"),
	SND_SOC_DAPM_INPUT("IN56"),

	SND_SOC_DAPM_SUPPLY("MICBIAS", M98090_REG_INPUT_ENABLE,
		M98090_MBEN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SHDN", M98090_REG_DEVICE_SHUTDOWN,
		M98090_SHDNN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SDIEN", M98090_REG_IO_CONFIGURATION,
		M98090_SDIEN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SDOEN", M98090_REG_IO_CONFIGURATION,
		M98090_SDOEN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMICL_ENA", M98090_REG_DIGITAL_MIC_ENABLE,
		 M98090_DIGMICL_SHIFT, 0, max98090_shdn_event,
			SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("DMICR_ENA", M98090_REG_DIGITAL_MIC_ENABLE,
		 M98090_DIGMICR_SHIFT, 0, max98090_shdn_event,
			 SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SUPPLY("AHPF", M98090_REG_FILTER_CONFIG,
		M98090_AHPF_SHIFT, 0, शून्य, 0),

/*
 * Note: Sysclk and misc घातer supplies are taken care of by SHDN
 */

	SND_SOC_DAPM_MUX("MIC1 Mux", SND_SOC_NOPM,
		0, 0, &max98090_mic1_mux),

	SND_SOC_DAPM_MUX("MIC2 Mux", SND_SOC_NOPM,
		0, 0, &max98090_mic2_mux),

	SND_SOC_DAPM_MUX("DMIC Mux", SND_SOC_NOPM, 0, 0, &max98090_dmic_mux),

	SND_SOC_DAPM_PGA_E("MIC1 Input", M98090_REG_MIC1_INPUT_LEVEL,
		M98090_MIC_PA1EN_SHIFT, 0, शून्य, 0, max98090_micinput_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_PGA_E("MIC2 Input", M98090_REG_MIC2_INPUT_LEVEL,
		M98090_MIC_PA2EN_SHIFT, 0, शून्य, 0, max98090_micinput_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_MIXER("LINEA Mixer", SND_SOC_NOPM, 0, 0,
		&max98090_linea_mixer_controls[0],
		ARRAY_SIZE(max98090_linea_mixer_controls)),

	SND_SOC_DAPM_MIXER("LINEB Mixer", SND_SOC_NOPM, 0, 0,
		&max98090_lineb_mixer_controls[0],
		ARRAY_SIZE(max98090_lineb_mixer_controls)),

	SND_SOC_DAPM_PGA("LINEA Input", M98090_REG_INPUT_ENABLE,
		M98090_LINEAEN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("LINEB Input", M98090_REG_INPUT_ENABLE,
		M98090_LINEBEN_SHIFT, 0, शून्य, 0),

	SND_SOC_DAPM_MIXER("Left ADC Mixer", SND_SOC_NOPM, 0, 0,
		&max98090_left_adc_mixer_controls[0],
		ARRAY_SIZE(max98090_left_adc_mixer_controls)),

	SND_SOC_DAPM_MIXER("Right ADC Mixer", SND_SOC_NOPM, 0, 0,
		&max98090_right_adc_mixer_controls[0],
		ARRAY_SIZE(max98090_right_adc_mixer_controls)),

	SND_SOC_DAPM_ADC_E("ADCL", शून्य, M98090_REG_INPUT_ENABLE,
		M98090_ADLEN_SHIFT, 0, max98090_shdn_event,
		SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_ADC_E("ADCR", शून्य, M98090_REG_INPUT_ENABLE,
		M98090_ADREN_SHIFT, 0, max98090_shdn_event,
		SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_AIF_OUT("AIFOUTL", "HiFi Capture", 0,
		SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIFOUTR", "HiFi Capture", 1,
		SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX("LBENL Mux", SND_SOC_NOPM,
		0, 0, &max98090_lbenl_mux),

	SND_SOC_DAPM_MUX("LBENR Mux", SND_SOC_NOPM,
		0, 0, &max98090_lbenr_mux),

	SND_SOC_DAPM_MUX("LTENL Mux", SND_SOC_NOPM,
		0, 0, &max98090_ltenl_mux),

	SND_SOC_DAPM_MUX("LTENR Mux", SND_SOC_NOPM,
		0, 0, &max98090_ltenr_mux),

	SND_SOC_DAPM_MUX("STENL Mux", SND_SOC_NOPM,
		0, 0, &max98090_stenl_mux),

	SND_SOC_DAPM_MUX("STENR Mux", SND_SOC_NOPM,
		0, 0, &max98090_stenr_mux),

	SND_SOC_DAPM_AIF_IN("AIFINL", "HiFi Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFINR", "HiFi Playback", 1, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DACL", शून्य, M98090_REG_OUTPUT_ENABLE,
		M98090_DALEN_SHIFT, 0),
	SND_SOC_DAPM_DAC("DACR", शून्य, M98090_REG_OUTPUT_ENABLE,
		M98090_DAREN_SHIFT, 0),

	SND_SOC_DAPM_MIXER("Left Headphone Mixer", SND_SOC_NOPM, 0, 0,
		&max98090_left_hp_mixer_controls[0],
		ARRAY_SIZE(max98090_left_hp_mixer_controls)),

	SND_SOC_DAPM_MIXER("Right Headphone Mixer", SND_SOC_NOPM, 0, 0,
		&max98090_right_hp_mixer_controls[0],
		ARRAY_SIZE(max98090_right_hp_mixer_controls)),

	SND_SOC_DAPM_MIXER("Left Speaker Mixer", SND_SOC_NOPM, 0, 0,
		&max98090_left_speaker_mixer_controls[0],
		ARRAY_SIZE(max98090_left_speaker_mixer_controls)),

	SND_SOC_DAPM_MIXER("Right Speaker Mixer", SND_SOC_NOPM, 0, 0,
		&max98090_right_speaker_mixer_controls[0],
		ARRAY_SIZE(max98090_right_speaker_mixer_controls)),

	SND_SOC_DAPM_MIXER("Left Receiver Mixer", SND_SOC_NOPM, 0, 0,
		&max98090_left_rcv_mixer_controls[0],
		ARRAY_SIZE(max98090_left_rcv_mixer_controls)),

	SND_SOC_DAPM_MIXER("Right Receiver Mixer", SND_SOC_NOPM, 0, 0,
		&max98090_right_rcv_mixer_controls[0],
		ARRAY_SIZE(max98090_right_rcv_mixer_controls)),

	SND_SOC_DAPM_MUX("LINMOD Mux", SND_SOC_NOPM, 0, 0,
		&max98090_linmod_mux),

	SND_SOC_DAPM_MUX("MIXHPLSEL Mux", SND_SOC_NOPM, 0, 0,
		&max98090_mixhplsel_mux),

	SND_SOC_DAPM_MUX("MIXHPRSEL Mux", SND_SOC_NOPM, 0, 0,
		&max98090_mixhprsel_mux),

	SND_SOC_DAPM_PGA("HP Left Out", M98090_REG_OUTPUT_ENABLE,
		M98090_HPLEN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HP Right Out", M98090_REG_OUTPUT_ENABLE,
		M98090_HPREN_SHIFT, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("SPK Left Out", M98090_REG_OUTPUT_ENABLE,
		M98090_SPLEN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("SPK Right Out", M98090_REG_OUTPUT_ENABLE,
		M98090_SPREN_SHIFT, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("RCV Left Out", M98090_REG_OUTPUT_ENABLE,
		M98090_RCVLEN_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("RCV Right Out", M98090_REG_OUTPUT_ENABLE,
		M98090_RCVREN_SHIFT, 0, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("SPKL"),
	SND_SOC_DAPM_OUTPUT("SPKR"),
	SND_SOC_DAPM_OUTPUT("RCVL"),
	SND_SOC_DAPM_OUTPUT("RCVR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget max98091_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("DMIC3"),
	SND_SOC_DAPM_INPUT("DMIC4"),

	SND_SOC_DAPM_SUPPLY("DMIC3_ENA", M98090_REG_DIGITAL_MIC_ENABLE,
		 M98090_DIGMIC3_SHIFT, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC4_ENA", M98090_REG_DIGITAL_MIC_ENABLE,
		 M98090_DIGMIC4_SHIFT, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98090_dapm_routes[] = अणु
	अणु"MIC1 Input", शून्य, "MIC1"पूर्ण,
	अणु"MIC2 Input", शून्य, "MIC2"पूर्ण,

	अणु"DMICL", शून्य, "DMICL_ENA"पूर्ण,
	अणु"DMICL", शून्य, "DMICR_ENA"पूर्ण,
	अणु"DMICR", शून्य, "DMICL_ENA"पूर्ण,
	अणु"DMICR", शून्य, "DMICR_ENA"पूर्ण,
	अणु"DMICL", शून्य, "AHPF"पूर्ण,
	अणु"DMICR", शून्य, "AHPF"पूर्ण,

	/* MIC1 input mux */
	अणु"MIC1 Mux", "IN12", "IN12"पूर्ण,
	अणु"MIC1 Mux", "IN56", "IN56"पूर्ण,

	/* MIC2 input mux */
	अणु"MIC2 Mux", "IN34", "IN34"पूर्ण,
	अणु"MIC2 Mux", "IN56", "IN56"पूर्ण,

	अणु"MIC1 Input", शून्य, "MIC1 Mux"पूर्ण,
	अणु"MIC2 Input", शून्य, "MIC2 Mux"पूर्ण,

	/* Left ADC input mixer */
	अणु"Left ADC Mixer", "IN12 Switch", "IN12"पूर्ण,
	अणु"Left ADC Mixer", "IN34 Switch", "IN34"पूर्ण,
	अणु"Left ADC Mixer", "IN56 Switch", "IN56"पूर्ण,
	अणु"Left ADC Mixer", "LINEA Switch", "LINEA Input"पूर्ण,
	अणु"Left ADC Mixer", "LINEB Switch", "LINEB Input"पूर्ण,
	अणु"Left ADC Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Left ADC Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,

	/* Right ADC input mixer */
	अणु"Right ADC Mixer", "IN12 Switch", "IN12"पूर्ण,
	अणु"Right ADC Mixer", "IN34 Switch", "IN34"पूर्ण,
	अणु"Right ADC Mixer", "IN56 Switch", "IN56"पूर्ण,
	अणु"Right ADC Mixer", "LINEA Switch", "LINEA Input"पूर्ण,
	अणु"Right ADC Mixer", "LINEB Switch", "LINEB Input"पूर्ण,
	अणु"Right ADC Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Right ADC Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,

	/* Line A input mixer */
	अणु"LINEA Mixer", "IN1 Switch", "IN1"पूर्ण,
	अणु"LINEA Mixer", "IN3 Switch", "IN3"पूर्ण,
	अणु"LINEA Mixer", "IN5 Switch", "IN5"पूर्ण,
	अणु"LINEA Mixer", "IN34 Switch", "IN34"पूर्ण,

	/* Line B input mixer */
	अणु"LINEB Mixer", "IN2 Switch", "IN2"पूर्ण,
	अणु"LINEB Mixer", "IN4 Switch", "IN4"पूर्ण,
	अणु"LINEB Mixer", "IN6 Switch", "IN6"पूर्ण,
	अणु"LINEB Mixer", "IN56 Switch", "IN56"पूर्ण,

	अणु"LINEA Input", शून्य, "LINEA Mixer"पूर्ण,
	अणु"LINEB Input", शून्य, "LINEB Mixer"पूर्ण,

	/* Inमाला_दो */
	अणु"ADCL", शून्य, "Left ADC Mixer"पूर्ण,
	अणु"ADCR", शून्य, "Right ADC Mixer"पूर्ण,
	अणु"ADCL", शून्य, "SHDN"पूर्ण,
	अणु"ADCR", शून्य, "SHDN"पूर्ण,

	अणु"DMIC Mux", "ADC", "ADCL"पूर्ण,
	अणु"DMIC Mux", "ADC", "ADCR"पूर्ण,
	अणु"DMIC Mux", "DMIC", "DMICL"पूर्ण,
	अणु"DMIC Mux", "DMIC", "DMICR"पूर्ण,

	अणु"LBENL Mux", "Normal", "DMIC Mux"पूर्ण,
	अणु"LBENL Mux", "Loopback", "LTENL Mux"पूर्ण,
	अणु"LBENR Mux", "Normal", "DMIC Mux"पूर्ण,
	अणु"LBENR Mux", "Loopback", "LTENR Mux"पूर्ण,

	अणु"AIFOUTL", शून्य, "LBENL Mux"पूर्ण,
	अणु"AIFOUTR", शून्य, "LBENR Mux"पूर्ण,
	अणु"AIFOUTL", शून्य, "SHDN"पूर्ण,
	अणु"AIFOUTR", शून्य, "SHDN"पूर्ण,
	अणु"AIFOUTL", शून्य, "SDOEN"पूर्ण,
	अणु"AIFOUTR", शून्य, "SDOEN"पूर्ण,

	अणु"LTENL Mux", "Normal", "AIFINL"पूर्ण,
	अणु"LTENL Mux", "Loopthrough", "LBENL Mux"पूर्ण,
	अणु"LTENR Mux", "Normal", "AIFINR"पूर्ण,
	अणु"LTENR Mux", "Loopthrough", "LBENR Mux"पूर्ण,

	अणु"DACL", शून्य, "LTENL Mux"पूर्ण,
	अणु"DACR", शून्य, "LTENR Mux"पूर्ण,

	अणु"STENL Mux", "Sidetone Left", "ADCL"पूर्ण,
	अणु"STENL Mux", "Sidetone Left", "DMICL"पूर्ण,
	अणु"STENR Mux", "Sidetone Right", "ADCR"पूर्ण,
	अणु"STENR Mux", "Sidetone Right", "DMICR"पूर्ण,
	अणु"DACL", शून्य, "STENL Mux"पूर्ण,
	अणु"DACR", शून्य, "STENR Mux"पूर्ण,

	अणु"AIFINL", शून्य, "SHDN"पूर्ण,
	अणु"AIFINR", शून्य, "SHDN"पूर्ण,
	अणु"AIFINL", शून्य, "SDIEN"पूर्ण,
	अणु"AIFINR", शून्य, "SDIEN"पूर्ण,
	अणु"DACL", शून्य, "SHDN"पूर्ण,
	अणु"DACR", शून्य, "SHDN"पूर्ण,

	/* Left headphone output mixer */
	अणु"Left Headphone Mixer", "Left DAC Switch", "DACL"पूर्ण,
	अणु"Left Headphone Mixer", "Right DAC Switch", "DACR"पूर्ण,
	अणु"Left Headphone Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Left Headphone Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Left Headphone Mixer", "LINEA Switch", "LINEA Input"पूर्ण,
	अणु"Left Headphone Mixer", "LINEB Switch", "LINEB Input"पूर्ण,

	/* Right headphone output mixer */
	अणु"Right Headphone Mixer", "Left DAC Switch", "DACL"पूर्ण,
	अणु"Right Headphone Mixer", "Right DAC Switch", "DACR"पूर्ण,
	अणु"Right Headphone Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Right Headphone Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Right Headphone Mixer", "LINEA Switch", "LINEA Input"पूर्ण,
	अणु"Right Headphone Mixer", "LINEB Switch", "LINEB Input"पूर्ण,

	/* Left speaker output mixer */
	अणु"Left Speaker Mixer", "Left DAC Switch", "DACL"पूर्ण,
	अणु"Left Speaker Mixer", "Right DAC Switch", "DACR"पूर्ण,
	अणु"Left Speaker Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Left Speaker Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Left Speaker Mixer", "LINEA Switch", "LINEA Input"पूर्ण,
	अणु"Left Speaker Mixer", "LINEB Switch", "LINEB Input"पूर्ण,

	/* Right speaker output mixer */
	अणु"Right Speaker Mixer", "Left DAC Switch", "DACL"पूर्ण,
	अणु"Right Speaker Mixer", "Right DAC Switch", "DACR"पूर्ण,
	अणु"Right Speaker Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Right Speaker Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Right Speaker Mixer", "LINEA Switch", "LINEA Input"पूर्ण,
	अणु"Right Speaker Mixer", "LINEB Switch", "LINEB Input"पूर्ण,

	/* Left Receiver output mixer */
	अणु"Left Receiver Mixer", "Left DAC Switch", "DACL"पूर्ण,
	अणु"Left Receiver Mixer", "Right DAC Switch", "DACR"पूर्ण,
	अणु"Left Receiver Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Left Receiver Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Left Receiver Mixer", "LINEA Switch", "LINEA Input"पूर्ण,
	अणु"Left Receiver Mixer", "LINEB Switch", "LINEB Input"पूर्ण,

	/* Right Receiver output mixer */
	अणु"Right Receiver Mixer", "Left DAC Switch", "DACL"पूर्ण,
	अणु"Right Receiver Mixer", "Right DAC Switch", "DACR"पूर्ण,
	अणु"Right Receiver Mixer", "MIC1 Switch", "MIC1 Input"पूर्ण,
	अणु"Right Receiver Mixer", "MIC2 Switch", "MIC2 Input"पूर्ण,
	अणु"Right Receiver Mixer", "LINEA Switch", "LINEA Input"पूर्ण,
	अणु"Right Receiver Mixer", "LINEB Switch", "LINEB Input"पूर्ण,

	अणु"MIXHPLSEL Mux", "HP Mixer", "Left Headphone Mixer"पूर्ण,

	/*
	 * Disable this क्रम lowest घातer अगर bypassing
	 * the DAC with an analog संकेत
	 */
	अणु"HP Left Out", शून्य, "DACL"पूर्ण,
	अणु"HP Left Out", शून्य, "MIXHPLSEL Mux"पूर्ण,

	अणु"MIXHPRSEL Mux", "HP Mixer", "Right Headphone Mixer"पूर्ण,

	/*
	 * Disable this क्रम lowest घातer अगर bypassing
	 * the DAC with an analog संकेत
	 */
	अणु"HP Right Out", शून्य, "DACR"पूर्ण,
	अणु"HP Right Out", शून्य, "MIXHPRSEL Mux"पूर्ण,

	अणु"SPK Left Out", शून्य, "Left Speaker Mixer"पूर्ण,
	अणु"SPK Right Out", शून्य, "Right Speaker Mixer"पूर्ण,
	अणु"RCV Left Out", शून्य, "Left Receiver Mixer"पूर्ण,

	अणु"LINMOD Mux", "Left and Right", "Right Receiver Mixer"पूर्ण,
	अणु"LINMOD Mux", "Left Only",  "Left Receiver Mixer"पूर्ण,
	अणु"RCV Right Out", शून्य, "LINMOD Mux"पूर्ण,

	अणु"HPL", शून्य, "HP Left Out"पूर्ण,
	अणु"HPR", शून्य, "HP Right Out"पूर्ण,
	अणु"SPKL", शून्य, "SPK Left Out"पूर्ण,
	अणु"SPKR", शून्य, "SPK Right Out"पूर्ण,
	अणु"RCVL", शून्य, "RCV Left Out"पूर्ण,
	अणु"RCVR", शून्य, "RCV Right Out"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98091_dapm_routes[] = अणु
	/* DMIC inमाला_दो */
	अणु"DMIC3", शून्य, "DMIC3_ENA"पूर्ण,
	अणु"DMIC4", शून्य, "DMIC4_ENA"पूर्ण,
	अणु"DMIC3", शून्य, "AHPF"पूर्ण,
	अणु"DMIC4", शून्य, "AHPF"पूर्ण,
पूर्ण;

अटल पूर्णांक max98090_add_widमाला_लो(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_add_component_controls(component, max98090_snd_controls,
		ARRAY_SIZE(max98090_snd_controls));

	अगर (max98090->devtype == MAX98091) अणु
		snd_soc_add_component_controls(component, max98091_snd_controls,
			ARRAY_SIZE(max98091_snd_controls));
	पूर्ण

	snd_soc_dapm_new_controls(dapm, max98090_dapm_widमाला_लो,
		ARRAY_SIZE(max98090_dapm_widमाला_लो));

	snd_soc_dapm_add_routes(dapm, max98090_dapm_routes,
		ARRAY_SIZE(max98090_dapm_routes));

	अगर (max98090->devtype == MAX98091) अणु
		snd_soc_dapm_new_controls(dapm, max98091_dapm_widमाला_लो,
			ARRAY_SIZE(max98091_dapm_widमाला_लो));

		snd_soc_dapm_add_routes(dapm, max98091_dapm_routes,
			ARRAY_SIZE(max98091_dapm_routes));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक pclk_rates[] = अणु
	12000000, 12000000, 13000000, 13000000,
	16000000, 16000000, 19200000, 19200000
पूर्ण;

अटल स्थिर पूर्णांक lrclk_rates[] = अणु
	8000, 16000, 8000, 16000,
	8000, 16000, 8000, 16000
पूर्ण;

अटल स्थिर पूर्णांक user_pclk_rates[] = अणु
	13000000, 13000000, 19200000, 19200000,
पूर्ण;

अटल स्थिर पूर्णांक user_lrclk_rates[] = अणु
	44100, 48000, 44100, 48000,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ दीर्घ ni_value[] = अणु
	3528, 768, 441, 8
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ दीर्घ mi_value[] = अणु
	8125, 1625, 1500, 25
पूर्ण;

अटल व्योम max98090_configure_bclk(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ दीर्घ ni;
	पूर्णांक i;

	अगर (!max98090->sysclk) अणु
		dev_err(component->dev, "No SYSCLK configured\n");
		वापस;
	पूर्ण

	अगर (!max98090->bclk || !max98090->lrclk) अणु
		dev_err(component->dev, "No audio clocks configured\n");
		वापस;
	पूर्ण

	/* Skip configuration when operating as slave */
	अगर (!(snd_soc_component_पढ़ो(component, M98090_REG_MASTER_MODE) &
		M98090_MAS_MASK)) अणु
		वापस;
	पूर्ण

	/* Check क्रम supported PCLK to LRCLK ratios */
	क्रम (i = 0; i < ARRAY_SIZE(pclk_rates); i++) अणु
		अगर ((pclk_rates[i] == max98090->sysclk) &&
			(lrclk_rates[i] == max98090->lrclk)) अणु
			dev_dbg(component->dev,
				"Found supported PCLK to LRCLK rates 0x%x\n",
				i + 0x8);

			snd_soc_component_update_bits(component, M98090_REG_CLOCK_MODE,
				M98090_FREQ_MASK,
				(i + 0x8) << M98090_FREQ_SHIFT);
			snd_soc_component_update_bits(component, M98090_REG_CLOCK_MODE,
				M98090_USE_M1_MASK, 0);
			वापस;
		पूर्ण
	पूर्ण

	/* Check क्रम user calculated MI and NI ratios */
	क्रम (i = 0; i < ARRAY_SIZE(user_pclk_rates); i++) अणु
		अगर ((user_pclk_rates[i] == max98090->sysclk) &&
			(user_lrclk_rates[i] == max98090->lrclk)) अणु
			dev_dbg(component->dev,
				"Found user supported PCLK to LRCLK rates\n");
			dev_dbg(component->dev, "i %d ni %lld mi %lld\n",
				i, ni_value[i], mi_value[i]);

			snd_soc_component_update_bits(component, M98090_REG_CLOCK_MODE,
				M98090_FREQ_MASK, 0);
			snd_soc_component_update_bits(component, M98090_REG_CLOCK_MODE,
				M98090_USE_M1_MASK,
					1 << M98090_USE_M1_SHIFT);

			snd_soc_component_ग_लिखो(component, M98090_REG_CLOCK_RATIO_NI_MSB,
				(ni_value[i] >> 8) & 0x7F);
			snd_soc_component_ग_लिखो(component, M98090_REG_CLOCK_RATIO_NI_LSB,
				ni_value[i] & 0xFF);
			snd_soc_component_ग_लिखो(component, M98090_REG_CLOCK_RATIO_MI_MSB,
				(mi_value[i] >> 8) & 0x7F);
			snd_soc_component_ग_लिखो(component, M98090_REG_CLOCK_RATIO_MI_LSB,
				mi_value[i] & 0xFF);

			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Calculate based on MI = 65536 (not as good as either method above)
	 */
	snd_soc_component_update_bits(component, M98090_REG_CLOCK_MODE,
		M98090_FREQ_MASK, 0);
	snd_soc_component_update_bits(component, M98090_REG_CLOCK_MODE,
		M98090_USE_M1_MASK, 0);

	/*
	 * Configure NI when operating as master
	 * Note: There is a small, but signअगरicant audio quality improvement
	 * by calculating ni and mi.
	 */
	ni = 65536ULL * (max98090->lrclk < 50000 ? 96ULL : 48ULL)
			* (अचिन्हित दीर्घ दीर्घ पूर्णांक)max98090->lrclk;
	करो_भाग(ni, (अचिन्हित दीर्घ दीर्घ पूर्णांक)max98090->sysclk);
	dev_info(component->dev, "No better method found\n");
	dev_info(component->dev, "Calculating ni %lld with mi 65536\n", ni);
	snd_soc_component_ग_लिखो(component, M98090_REG_CLOCK_RATIO_NI_MSB,
		(ni >> 8) & 0x7F);
	snd_soc_component_ग_लिखो(component, M98090_REG_CLOCK_RATIO_NI_LSB, ni & 0xFF);
पूर्ण

अटल पूर्णांक max98090_dai_set_fmt(काष्ठा snd_soc_dai *codec_dai,
				 अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	काष्ठा max98090_cdata *cdata;
	u8 regval;

	max98090->dai_fmt = fmt;
	cdata = &max98090->dai[0];

	अगर (fmt != cdata->fmt) अणु
		cdata->fmt = fmt;

		regval = 0;
		चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
		हाल SND_SOC_DAIFMT_CBS_CFS:
			/* Set to slave mode PLL - MAS mode off */
			snd_soc_component_ग_लिखो(component,
				M98090_REG_CLOCK_RATIO_NI_MSB, 0x00);
			snd_soc_component_ग_लिखो(component,
				M98090_REG_CLOCK_RATIO_NI_LSB, 0x00);
			snd_soc_component_update_bits(component, M98090_REG_CLOCK_MODE,
				M98090_USE_M1_MASK, 0);
			max98090->master = false;
			अवरोध;
		हाल SND_SOC_DAIFMT_CBM_CFM:
			/* Set to master mode */
			अगर (max98090->tdm_slots == 4) अणु
				/* TDM */
				regval |= M98090_MAS_MASK |
					M98090_BSEL_64;
			पूर्ण अन्यथा अगर (max98090->tdm_slots == 3) अणु
				/* TDM */
				regval |= M98090_MAS_MASK |
					M98090_BSEL_48;
			पूर्ण अन्यथा अणु
				/* Few TDM slots, or No TDM */
				regval |= M98090_MAS_MASK |
					M98090_BSEL_32;
			पूर्ण
			max98090->master = true;
			अवरोध;
		हाल SND_SOC_DAIFMT_CBS_CFM:
		हाल SND_SOC_DAIFMT_CBM_CFS:
		शेष:
			dev_err(component->dev, "DAI clock mode unsupported");
			वापस -EINVAL;
		पूर्ण
		snd_soc_component_ग_लिखो(component, M98090_REG_MASTER_MODE, regval);

		regval = 0;
		चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
		हाल SND_SOC_DAIFMT_I2S:
			regval |= M98090_DLY_MASK;
			अवरोध;
		हाल SND_SOC_DAIFMT_LEFT_J:
			अवरोध;
		हाल SND_SOC_DAIFMT_RIGHT_J:
			regval |= M98090_RJ_MASK;
			अवरोध;
		हाल SND_SOC_DAIFMT_DSP_A:
			/* Not supported mode */
		शेष:
			dev_err(component->dev, "DAI format unsupported");
			वापस -EINVAL;
		पूर्ण

		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			regval |= M98090_WCI_MASK;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			regval |= M98090_BCI_MASK;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			regval |= M98090_BCI_MASK|M98090_WCI_MASK;
			अवरोध;
		शेष:
			dev_err(component->dev, "DAI invert mode unsupported");
			वापस -EINVAL;
		पूर्ण

		/*
		 * This accommodates an inverted logic in the MAX98090 chip
		 * क्रम Bit Clock Invert (BCI). The inverted logic is only
		 * seen क्रम the हाल of TDM mode. The reमुख्यing हालs have
		 * normal logic.
		 */
		अगर (max98090->tdm_slots > 1)
			regval ^= M98090_BCI_MASK;

		snd_soc_component_ग_लिखो(component,
			M98090_REG_INTERFACE_FORMAT, regval);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max98090_set_tdm_slot(काष्ठा snd_soc_dai *codec_dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	काष्ठा max98090_cdata *cdata;
	cdata = &max98090->dai[0];

	अगर (slots < 0 || slots > 4)
		वापस -EINVAL;

	max98090->tdm_slots = slots;
	max98090->tdm_width = slot_width;

	अगर (max98090->tdm_slots > 1) अणु
		/* SLOTL SLOTR SLOTDLY */
		snd_soc_component_ग_लिखो(component, M98090_REG_TDM_FORMAT,
			0 << M98090_TDM_SLOTL_SHIFT |
			1 << M98090_TDM_SLOTR_SHIFT |
			0 << M98090_TDM_SLOTDLY_SHIFT);

		/* FSW TDM */
		snd_soc_component_update_bits(component, M98090_REG_TDM_CONTROL,
			M98090_TDM_MASK,
			M98090_TDM_MASK);
	पूर्ण

	/*
	 * Normally advisable to set TDM first, but this permits either order
	 */
	cdata->fmt = 0;
	max98090_dai_set_fmt(codec_dai, max98090->dai_fmt);

	वापस 0;
पूर्ण

अटल पूर्णांक max98090_set_bias_level(काष्ठा snd_soc_component *component,
				   क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

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
		अगर (IS_ERR(max98090->mclk))
			अवरोध;

		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_ON) अणु
			clk_disable_unprepare(max98090->mclk);
		पूर्ण अन्यथा अणु
			ret = clk_prepare_enable(max98090->mclk);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regcache_sync(max98090->regmap);
			अगर (ret != 0) अणु
				dev_err(component->dev,
					"Failed to sync cache: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* Set पूर्णांकernal pull-up to lowest घातer mode */
		snd_soc_component_update_bits(component, M98090_REG_JACK_DETECT,
			M98090_JDWK_MASK, M98090_JDWK_MASK);
		regcache_mark_dirty(max98090->regmap);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक dmic_भागisors[] = अणु 2, 3, 4, 5, 6, 8 पूर्ण;

अटल स्थिर पूर्णांक comp_lrclk_rates[] = अणु
	8000, 16000, 32000, 44100, 48000, 96000
पूर्ण;

काष्ठा dmic_table अणु
	पूर्णांक pclk;
	काष्ठा अणु
		पूर्णांक freq;
		पूर्णांक comp[6]; /* One each क्रम 8, 16, 32, 44.1, 48, and 96 kHz */
	पूर्ण settings[6]; /* One क्रम each dmic भागisor. */
पूर्ण;

अटल स्थिर काष्ठा dmic_table dmic_table[] = अणु /* One क्रम each pclk freq. */
	अणु
		.pclk = 11289600,
		.settings = अणु
			अणु .freq = 2, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
			अणु .freq = 1, .comp = अणु 7, 8, 2, 2, 2, 2 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 6, 6, 6, 6 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.pclk = 12000000,
		.settings = अणु
			अणु .freq = 2, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
			अणु .freq = 1, .comp = अणु 7, 8, 2, 2, 2, 2 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 5, 5, 6, 6 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
		पूर्ण
	पूर्ण,
	अणु
		.pclk = 12288000,
		.settings = अणु
			अणु .freq = 2, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
			अणु .freq = 1, .comp = अणु 7, 8, 2, 2, 2, 2 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 6, 6, 6, 6 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 3, 3, 3, 3 पूर्ण पूर्ण,
		पूर्ण
	पूर्ण,
	अणु
		.pclk = 13000000,
		.settings = अणु
			अणु .freq = 2, .comp = अणु 7, 8, 1, 1, 1, 1 पूर्ण पूर्ण,
			अणु .freq = 1, .comp = अणु 7, 8, 0, 0, 0, 0 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 1, 1, 1, 1 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 4, 4, 5, 5 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 1, 1, 1, 1 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 1, 1, 1, 1 पूर्ण पूर्ण,
		पूर्ण
	पूर्ण,
	अणु
		.pclk = 19200000,
		.settings = अणु
			अणु .freq = 2, .comp = अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
			अणु .freq = 1, .comp = अणु 7, 8, 1, 1, 1, 1 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 5, 5, 6, 6 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 2, 2, 3, 3 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 1, 1, 2, 2 पूर्ण पूर्ण,
			अणु .freq = 0, .comp = अणु 7, 8, 5, 5, 6, 6 पूर्ण पूर्ण,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक max98090_find_भागisor(पूर्णांक target_freq, पूर्णांक pclk)
अणु
	पूर्णांक current_dअगरf = पूर्णांक_उच्च;
	पूर्णांक test_dअगरf;
	पूर्णांक भागisor_index = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dmic_भागisors); i++) अणु
		test_dअगरf = असल(target_freq - (pclk / dmic_भागisors[i]));
		अगर (test_dअगरf < current_dअगरf) अणु
			current_dअगरf = test_dअगरf;
			भागisor_index = i;
		पूर्ण
	पूर्ण

	वापस भागisor_index;
पूर्ण

अटल पूर्णांक max98090_find_बंदst_pclk(पूर्णांक pclk)
अणु
	पूर्णांक m1;
	पूर्णांक m2;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dmic_table); i++) अणु
		अगर (pclk == dmic_table[i].pclk)
			वापस i;
		अगर (pclk < dmic_table[i].pclk) अणु
			अगर (i == 0)
				वापस i;
			m1 = pclk - dmic_table[i-1].pclk;
			m2 = dmic_table[i].pclk - pclk;
			अगर (m1 < m2)
				वापस i - 1;
			अन्यथा
				वापस i;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max98090_configure_dmic(काष्ठा max98090_priv *max98090,
				   पूर्णांक target_dmic_clk, पूर्णांक pclk, पूर्णांक fs)
अणु
	पूर्णांक micclk_index;
	पूर्णांक pclk_index;
	पूर्णांक dmic_freq;
	पूर्णांक dmic_comp;
	पूर्णांक i;

	pclk_index = max98090_find_बंदst_pclk(pclk);
	अगर (pclk_index < 0)
		वापस pclk_index;

	micclk_index = max98090_find_भागisor(target_dmic_clk, pclk);

	क्रम (i = 0; i < ARRAY_SIZE(comp_lrclk_rates) - 1; i++) अणु
		अगर (fs <= (comp_lrclk_rates[i] + comp_lrclk_rates[i+1]) / 2)
			अवरोध;
	पूर्ण

	dmic_freq = dmic_table[pclk_index].settings[micclk_index].freq;
	dmic_comp = dmic_table[pclk_index].settings[micclk_index].comp[i];

	regmap_update_bits(max98090->regmap, M98090_REG_DIGITAL_MIC_ENABLE,
			   M98090_MICCLK_MASK,
			   micclk_index << M98090_MICCLK_SHIFT);

	regmap_update_bits(max98090->regmap, M98090_REG_DIGITAL_MIC_CONFIG,
			   M98090_DMIC_COMP_MASK | M98090_DMIC_FREQ_MASK,
			   dmic_comp << M98090_DMIC_COMP_SHIFT |
			   dmic_freq << M98090_DMIC_FREQ_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक max98090_dai_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक fmt = max98090->dai_fmt;

	/* Remove 24-bit क्रमmat support अगर it is not in right justअगरied mode. */
	अगर ((fmt & SND_SOC_DAIFMT_FORMAT_MASK) != SND_SOC_DAIFMT_RIGHT_J) अणु
		substream->runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
		snd_pcm_hw_स्थिरraपूर्णांक_msbits(substream->runसमय, 0, 16, 16);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max98090_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	काष्ठा max98090_cdata *cdata;

	cdata = &max98090->dai[0];
	max98090->bclk = snd_soc_params_to_bclk(params);
	अगर (params_channels(params) == 1)
		max98090->bclk *= 2;

	max98090->lrclk = params_rate(params);

	चयन (params_width(params)) अणु
	हाल 16:
		snd_soc_component_update_bits(component, M98090_REG_INTERFACE_FORMAT,
			M98090_WS_MASK, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (max98090->master)
		max98090_configure_bclk(component);

	cdata->rate = max98090->lrclk;

	/* Update filter mode */
	अगर (max98090->lrclk < 24000)
		snd_soc_component_update_bits(component, M98090_REG_FILTER_CONFIG,
			M98090_MODE_MASK, 0);
	अन्यथा
		snd_soc_component_update_bits(component, M98090_REG_FILTER_CONFIG,
			M98090_MODE_MASK, M98090_MODE_MASK);

	/* Update sample rate mode */
	अगर (max98090->lrclk < 50000)
		snd_soc_component_update_bits(component, M98090_REG_FILTER_CONFIG,
			M98090_DHF_MASK, 0);
	अन्यथा
		snd_soc_component_update_bits(component, M98090_REG_FILTER_CONFIG,
			M98090_DHF_MASK, M98090_DHF_MASK);

	max98090_configure_dmic(max98090, max98090->dmic_freq, max98090->pclk,
				max98090->lrclk);

	वापस 0;
पूर्ण

/*
 * PLL / Sysclk
 */
अटल पूर्णांक max98090_dai_set_sysclk(काष्ठा snd_soc_dai *dai,
				   पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	/* Requested घड़ी frequency is alपढ़ोy setup */
	अगर (freq == max98090->sysclk)
		वापस 0;

	अगर (!IS_ERR(max98090->mclk)) अणु
		freq = clk_round_rate(max98090->mclk, freq);
		clk_set_rate(max98090->mclk, freq);
	पूर्ण

	/* Setup घड़ीs क्रम slave mode, and using the PLL
	 * PSCLK = 0x01 (when master clk is 10MHz to 20MHz)
	 *		 0x02 (when master clk is 20MHz to 40MHz)..
	 *		 0x03 (when master clk is 40MHz to 60MHz)..
	 */
	अगर ((freq >= 10000000) && (freq <= 20000000)) अणु
		snd_soc_component_ग_लिखो(component, M98090_REG_SYSTEM_CLOCK,
			M98090_PSCLK_DIV1);
		max98090->pclk = freq;
	पूर्ण अन्यथा अगर ((freq > 20000000) && (freq <= 40000000)) अणु
		snd_soc_component_ग_लिखो(component, M98090_REG_SYSTEM_CLOCK,
			M98090_PSCLK_DIV2);
		max98090->pclk = freq >> 1;
	पूर्ण अन्यथा अगर ((freq > 40000000) && (freq <= 60000000)) अणु
		snd_soc_component_ग_लिखो(component, M98090_REG_SYSTEM_CLOCK,
			M98090_PSCLK_DIV4);
		max98090->pclk = freq >> 2;
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Invalid master clock frequency\n");
		वापस -EINVAL;
	पूर्ण

	max98090->sysclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक max98090_dai_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute,
			     पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक regval;

	regval = mute ? M98090_DVM_MASK : 0;
	snd_soc_component_update_bits(component, M98090_REG_DAI_PLAYBACK_LEVEL,
		M98090_DVM_MASK, regval);

	वापस 0;
पूर्ण

अटल पूर्णांक max98090_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (!max98090->master && snd_soc_dai_active(dai) == 1)
			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					   &max98090->pll_det_enable_work,
					   msecs_to_jअगरfies(10));
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (!max98090->master && snd_soc_dai_active(dai) == 1)
			schedule_work(&max98090->pll_det_disable_work);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max98090_pll_det_enable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max98090_priv *max98090 =
		container_of(work, काष्ठा max98090_priv,
			     pll_det_enable_work.work);
	काष्ठा snd_soc_component *component = max98090->component;
	अचिन्हित पूर्णांक status, mask;

	/*
	 * Clear status रेजिस्टर in order to clear possibly alपढ़ोy occurred
	 * PLL unlock. If PLL hasn't still locked, the status will be set
	 * again and PLL unlock पूर्णांकerrupt will occur.
	 * Note this will clear all status bits
	 */
	regmap_पढ़ो(max98090->regmap, M98090_REG_DEVICE_STATUS, &status);

	/*
	 * Queue jack work in हाल jack state has just changed but handler
	 * hasn't run yet
	 */
	regmap_पढ़ो(max98090->regmap, M98090_REG_INTERRUPT_S, &mask);
	status &= mask;
	अगर (status & M98090_JDET_MASK)
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &max98090->jack_work,
				   msecs_to_jअगरfies(100));

	/* Enable PLL unlock पूर्णांकerrupt */
	snd_soc_component_update_bits(component, M98090_REG_INTERRUPT_S,
			    M98090_IULK_MASK,
			    1 << M98090_IULK_SHIFT);
पूर्ण

अटल व्योम max98090_pll_det_disable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max98090_priv *max98090 =
		container_of(work, काष्ठा max98090_priv, pll_det_disable_work);
	काष्ठा snd_soc_component *component = max98090->component;

	cancel_delayed_work_sync(&max98090->pll_det_enable_work);

	/* Disable PLL unlock पूर्णांकerrupt */
	snd_soc_component_update_bits(component, M98090_REG_INTERRUPT_S,
			    M98090_IULK_MASK, 0);
पूर्ण

अटल व्योम max98090_pll_work(काष्ठा max98090_priv *max98090)
अणु
	काष्ठा snd_soc_component *component = max98090->component;
	अचिन्हित पूर्णांक pll;
	पूर्णांक i;

	अगर (!snd_soc_component_active(component))
		वापस;

	dev_info_ratelimited(component->dev, "PLL unlocked\n");

	/*
	 * As the datasheet suggested, the maximum PLL lock समय should be
	 * 7 msec.  The workaround resets the codec softly by toggling SHDN
	 * off and on अगर PLL failed to lock क्रम 10 msec.  Notably, there is
	 * no suggested hold समय क्रम SHDN off.
	 */

	/* Toggle shutकरोwn OFF then ON */
	snd_soc_component_update_bits(component, M98090_REG_DEVICE_SHUTDOWN,
			    M98090_SHDNN_MASK, 0);
	snd_soc_component_update_bits(component, M98090_REG_DEVICE_SHUTDOWN,
			    M98090_SHDNN_MASK, M98090_SHDNN_MASK);

	क्रम (i = 0; i < 10; ++i) अणु
		/* Give PLL समय to lock */
		usleep_range(1000, 1200);

		/* Check lock status */
		pll = snd_soc_component_पढ़ो(
				component, M98090_REG_DEVICE_STATUS);
		अगर (!(pll & M98090_ULK_MASK))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम max98090_jack_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max98090_priv *max98090 = container_of(work,
		काष्ठा max98090_priv,
		jack_work.work);
	काष्ठा snd_soc_component *component = max98090->component;
	पूर्णांक status = 0;
	पूर्णांक reg;

	/* Read a second समय */
	अगर (max98090->jack_state == M98090_JACK_STATE_NO_HEADSET) अणु

		/* Strong pull up allows mic detection */
		snd_soc_component_update_bits(component, M98090_REG_JACK_DETECT,
			M98090_JDWK_MASK, 0);

		msleep(50);

		reg = snd_soc_component_पढ़ो(component, M98090_REG_JACK_STATUS);

		/* Weak pull up allows only insertion detection */
		snd_soc_component_update_bits(component, M98090_REG_JACK_DETECT,
			M98090_JDWK_MASK, M98090_JDWK_MASK);
	पूर्ण अन्यथा अणु
		reg = snd_soc_component_पढ़ो(component, M98090_REG_JACK_STATUS);
	पूर्ण

	reg = snd_soc_component_पढ़ो(component, M98090_REG_JACK_STATUS);

	चयन (reg & (M98090_LSNS_MASK | M98090_JKSNS_MASK)) अणु
		हाल M98090_LSNS_MASK | M98090_JKSNS_MASK:
			dev_dbg(component->dev, "No Headset Detected\n");

			max98090->jack_state = M98090_JACK_STATE_NO_HEADSET;

			status |= 0;

			अवरोध;

		हाल 0:
			अगर (max98090->jack_state ==
				M98090_JACK_STATE_HEADSET) अणु

				dev_dbg(component->dev,
					"Headset Button Down Detected\n");

				/*
				 * max98090_headset_button_event(codec)
				 * could be defined, then called here.
				 */

				status |= SND_JACK_HEADSET;
				status |= SND_JACK_BTN_0;

				अवरोध;
			पूर्ण

			/* Line is reported as Headphone */
			/* Nokia Headset is reported as Headphone */
			/* Mono Headphone is reported as Headphone */
			dev_dbg(component->dev, "Headphone Detected\n");

			max98090->jack_state = M98090_JACK_STATE_HEADPHONE;

			status |= SND_JACK_HEADPHONE;

			अवरोध;

		हाल M98090_JKSNS_MASK:
			dev_dbg(component->dev, "Headset Detected\n");

			max98090->jack_state = M98090_JACK_STATE_HEADSET;

			status |= SND_JACK_HEADSET;

			अवरोध;

		शेष:
			dev_dbg(component->dev, "Unrecognized Jack Status\n");
			अवरोध;
	पूर्ण

	snd_soc_jack_report(max98090->jack, status,
			    SND_JACK_HEADSET | SND_JACK_BTN_0);
पूर्ण

अटल irqवापस_t max98090_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max98090_priv *max98090 = data;
	काष्ठा snd_soc_component *component = max98090->component;
	पूर्णांक ret;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक active;

	/* Treat पूर्णांकerrupt beक्रमe codec is initialized as spurious */
	अगर (component == शून्य)
		वापस IRQ_NONE;

	dev_dbg(component->dev, "***** max98090_interrupt *****\n");

	ret = regmap_पढ़ो(max98090->regmap, M98090_REG_INTERRUPT_S, &mask);

	अगर (ret != 0) अणु
		dev_err(component->dev,
			"failed to read M98090_REG_INTERRUPT_S: %d\n",
			ret);
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_पढ़ो(max98090->regmap, M98090_REG_DEVICE_STATUS, &active);

	अगर (ret != 0) अणु
		dev_err(component->dev,
			"failed to read M98090_REG_DEVICE_STATUS: %d\n",
			ret);
		वापस IRQ_NONE;
	पूर्ण

	dev_dbg(component->dev, "active=0x%02x mask=0x%02x -> active=0x%02x\n",
		active, mask, active & mask);

	active &= mask;

	अगर (!active)
		वापस IRQ_NONE;

	अगर (active & M98090_CLD_MASK)
		dev_err(component->dev, "M98090_CLD_MASK\n");

	अगर (active & M98090_SLD_MASK)
		dev_dbg(component->dev, "M98090_SLD_MASK\n");

	अगर (active & M98090_ULK_MASK) अणु
		dev_dbg(component->dev, "M98090_ULK_MASK\n");
		max98090_pll_work(max98090);
	पूर्ण

	अगर (active & M98090_JDET_MASK) अणु
		dev_dbg(component->dev, "M98090_JDET_MASK\n");

		pm_wakeup_event(component->dev, 100);

		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				   &max98090->jack_work,
				   msecs_to_jअगरfies(100));
	पूर्ण

	अगर (active & M98090_DRCACT_MASK)
		dev_dbg(component->dev, "M98090_DRCACT_MASK\n");

	अगर (active & M98090_DRCCLP_MASK)
		dev_err(component->dev, "M98090_DRCCLP_MASK\n");

	वापस IRQ_HANDLED;
पूर्ण

/**
 * max98090_mic_detect - Enable microphone detection via the MAX98090 IRQ
 *
 * @component:  MAX98090 component
 * @jack:   jack to report detection events on
 *
 * Enable microphone detection via IRQ on the MAX98090.  If GPIOs are
 * being used to bring out संकेतs to the processor then only platक्रमm
 * data configuration is needed क्रम MAX98090 and processor GPIOs should
 * be configured using snd_soc_jack_add_gpios() instead.
 *
 * If no jack is supplied detection will be disabled.
 */
पूर्णांक max98090_mic_detect(काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "max98090_mic_detect\n");

	max98090->jack = jack;
	अगर (jack) अणु
		snd_soc_component_update_bits(component, M98090_REG_INTERRUPT_S,
			M98090_IJDET_MASK,
			1 << M98090_IJDET_SHIFT);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, M98090_REG_INTERRUPT_S,
			M98090_IJDET_MASK,
			0);
	पूर्ण

	/* Send an initial empty report */
	snd_soc_jack_report(max98090->jack, 0,
			    SND_JACK_HEADSET | SND_JACK_BTN_0);

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &max98090->jack_work,
			   msecs_to_jअगरfies(100));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max98090_mic_detect);

#घोषणा MAX98090_RATES SNDRV_PCM_RATE_8000_96000
#घोषणा MAX98090_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops max98090_dai_ops = अणु
	.startup = max98090_dai_startup,
	.set_sysclk = max98090_dai_set_sysclk,
	.set_fmt = max98090_dai_set_fmt,
	.set_tdm_slot = max98090_set_tdm_slot,
	.hw_params = max98090_dai_hw_params,
	.mute_stream = max98090_dai_mute,
	.trigger = max98090_dai_trigger,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max98090_dai[] = अणु
अणु
	.name = "HiFi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = MAX98090_RATES,
		.क्रमmats = MAX98090_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = MAX98090_RATES,
		.क्रमmats = MAX98090_FORMATS,
	पूर्ण,
	 .ops = &max98090_dai_ops,
पूर्ण
पूर्ण;

अटल पूर्णांक max98090_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	काष्ठा max98090_cdata *cdata;
	क्रमागत max98090_type devtype;
	पूर्णांक ret = 0;
	पूर्णांक err;
	अचिन्हित पूर्णांक micbias;

	dev_dbg(component->dev, "max98090_probe\n");

	max98090->mclk = devm_clk_get(component->dev, "mclk");
	अगर (PTR_ERR(max98090->mclk) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	max98090->component = component;

	/* Reset the codec, the DSP core, and disable all पूर्णांकerrupts */
	max98090_reset(max98090);

	/* Initialize निजी data */

	max98090->sysclk = (अचिन्हित)-1;
	max98090->pclk = (अचिन्हित)-1;
	max98090->master = false;

	cdata = &max98090->dai[0];
	cdata->rate = (अचिन्हित)-1;
	cdata->fmt  = (अचिन्हित)-1;

	max98090->lin_state = 0;
	max98090->pa1en = 0;
	max98090->pa2en = 0;

	ret = snd_soc_component_पढ़ो(component, M98090_REG_REVISION_ID);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to read device revision: %d\n",
			ret);
		जाओ err_access;
	पूर्ण

	अगर ((ret >= M98090_REVA) && (ret <= M98090_REVA + 0x0f)) अणु
		devtype = MAX98090;
		dev_info(component->dev, "MAX98090 REVID=0x%02x\n", ret);
	पूर्ण अन्यथा अगर ((ret >= M98091_REVA) && (ret <= M98091_REVA + 0x0f)) अणु
		devtype = MAX98091;
		dev_info(component->dev, "MAX98091 REVID=0x%02x\n", ret);
	पूर्ण अन्यथा अणु
		devtype = MAX98090;
		dev_err(component->dev, "Unrecognized revision 0x%02x\n", ret);
	पूर्ण

	अगर (max98090->devtype != devtype) अणु
		dev_warn(component->dev, "Mismatch in DT specified CODEC type.\n");
		max98090->devtype = devtype;
	पूर्ण

	max98090->jack_state = M98090_JACK_STATE_NO_HEADSET;

	INIT_DELAYED_WORK(&max98090->jack_work, max98090_jack_work);
	INIT_DELAYED_WORK(&max98090->pll_det_enable_work,
			  max98090_pll_det_enable_work);
	INIT_WORK(&max98090->pll_det_disable_work,
		  max98090_pll_det_disable_work);

	/* Enable jack detection */
	snd_soc_component_ग_लिखो(component, M98090_REG_JACK_DETECT,
		M98090_JDETEN_MASK | M98090_JDEB_25MS);

	/*
	 * Clear any old पूर्णांकerrupts.
	 * An old पूर्णांकerrupt ocurring prior to installing the ISR
	 * can keep a new पूर्णांकerrupt from generating a trigger.
	 */
	snd_soc_component_पढ़ो(component, M98090_REG_DEVICE_STATUS);

	/* High Perक्रमmance is शेष */
	snd_soc_component_update_bits(component, M98090_REG_DAC_CONTROL,
		M98090_DACHP_MASK,
		1 << M98090_DACHP_SHIFT);
	snd_soc_component_update_bits(component, M98090_REG_DAC_CONTROL,
		M98090_PERFMODE_MASK,
		0 << M98090_PERFMODE_SHIFT);
	snd_soc_component_update_bits(component, M98090_REG_ADC_CONTROL,
		M98090_ADCHP_MASK,
		1 << M98090_ADCHP_SHIFT);

	/* Turn on VCM bandgap reference */
	snd_soc_component_ग_लिखो(component, M98090_REG_BIAS_CONTROL,
		M98090_VCM_MODE_MASK);

	err = device_property_पढ़ो_u32(component->dev, "maxim,micbias", &micbias);
	अगर (err) अणु
		micbias = M98090_MBVSEL_2V8;
		dev_info(component->dev, "use default 2.8v micbias\n");
	पूर्ण अन्यथा अगर (micbias > M98090_MBVSEL_2V8) अणु
		dev_err(component->dev, "micbias out of range 0x%x\n", micbias);
		micbias = M98090_MBVSEL_2V8;
	पूर्ण

	snd_soc_component_update_bits(component, M98090_REG_MIC_BIAS_VOLTAGE,
		M98090_MBVSEL_MASK, micbias);

	max98090_add_widमाला_लो(component);

err_access:
	वापस ret;
पूर्ण

अटल व्योम max98090_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	cancel_delayed_work_sync(&max98090->jack_work);
	cancel_delayed_work_sync(&max98090->pll_det_enable_work);
	cancel_work_sync(&max98090->pll_det_disable_work);
	max98090->component = शून्य;
पूर्ण

अटल व्योम max98090_seq_notअगरier(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_dapm_type event, पूर्णांक subseq)
अणु
	काष्ठा max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	अगर (max98090->shdn_pending) अणु
		snd_soc_component_update_bits(component, M98090_REG_DEVICE_SHUTDOWN,
				M98090_SHDNN_MASK, 0);
		msleep(40);
		snd_soc_component_update_bits(component, M98090_REG_DEVICE_SHUTDOWN,
				M98090_SHDNN_MASK, M98090_SHDNN_MASK);
		max98090->shdn_pending = false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_max98090 = अणु
	.probe			= max98090_probe,
	.हटाओ			= max98090_हटाओ,
	.seq_notअगरier		= max98090_seq_notअगरier,
	.set_bias_level		= max98090_set_bias_level,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max98090_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = MAX98090_MAX_REGISTER,
	.reg_शेषs = max98090_reg,
	.num_reg_शेषs = ARRAY_SIZE(max98090_reg),
	.अस्थिर_reg = max98090_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = max98090_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक max98090_i2c_probe(काष्ठा i2c_client *i2c,
				 स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा max98090_priv *max98090;
	स्थिर काष्ठा acpi_device_id *acpi_id;
	kernel_uदीर्घ_t driver_data = 0;
	पूर्णांक ret;

	pr_debug("max98090_i2c_probe\n");

	max98090 = devm_kzalloc(&i2c->dev, माप(काष्ठा max98090_priv),
		GFP_KERNEL);
	अगर (max98090 == शून्य)
		वापस -ENOMEM;

	अगर (ACPI_HANDLE(&i2c->dev)) अणु
		acpi_id = acpi_match_device(i2c->dev.driver->acpi_match_table,
					    &i2c->dev);
		अगर (!acpi_id) अणु
			dev_err(&i2c->dev, "No driver data\n");
			वापस -EINVAL;
		पूर्ण
		driver_data = acpi_id->driver_data;
	पूर्ण अन्यथा अगर (i2c_id) अणु
		driver_data = i2c_id->driver_data;
	पूर्ण

	max98090->devtype = driver_data;
	i2c_set_clientdata(i2c, max98090);
	max98090->pdata = i2c->dev.platक्रमm_data;

	ret = of_property_पढ़ो_u32(i2c->dev.of_node, "maxim,dmic-freq",
				   &max98090->dmic_freq);
	अगर (ret < 0)
		max98090->dmic_freq = MAX98090_DEFAULT_DMIC_FREQ;

	max98090->regmap = devm_regmap_init_i2c(i2c, &max98090_regmap);
	अगर (IS_ERR(max98090->regmap)) अणु
		ret = PTR_ERR(max98090->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&i2c->dev, i2c->irq, शून्य,
		max98090_पूर्णांकerrupt, IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
		"max98090_interrupt", max98090);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "request_irq failed: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_max98090, max98090_dai,
			ARRAY_SIZE(max98090_dai));
err_enable:
	वापस ret;
पूर्ण

अटल व्योम max98090_i2c_shutकरोwn(काष्ठा i2c_client *i2c)
अणु
	काष्ठा max98090_priv *max98090 = dev_get_drvdata(&i2c->dev);

	/*
	 * Enable volume smoothing, disable zero cross.  This will cause
	 * a quick 40ms ramp to mute on shutकरोwn.
	 */
	regmap_ग_लिखो(max98090->regmap,
		M98090_REG_LEVEL_CONTROL, M98090_VSENN_MASK);
	regmap_ग_लिखो(max98090->regmap,
		M98090_REG_DEVICE_SHUTDOWN, 0x00);
	msleep(40);
पूर्ण

अटल पूर्णांक max98090_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	max98090_i2c_shutकरोwn(client);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक max98090_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा max98090_priv *max98090 = dev_get_drvdata(dev);

	regcache_cache_only(max98090->regmap, false);

	max98090_reset(max98090);

	regcache_sync(max98090->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक max98090_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा max98090_priv *max98090 = dev_get_drvdata(dev);

	regcache_cache_only(max98090->regmap, true);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max98090_resume(काष्ठा device *dev)
अणु
	काष्ठा max98090_priv *max98090 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक status;

	regcache_mark_dirty(max98090->regmap);

	max98090_reset(max98090);

	/* clear IRQ status */
	regmap_पढ़ो(max98090->regmap, M98090_REG_DEVICE_STATUS, &status);

	regcache_sync(max98090->regmap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops max98090_pm = अणु
	SET_RUNTIME_PM_OPS(max98090_runसमय_suspend,
		max98090_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(शून्य, max98090_resume)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id max98090_i2c_id[] = अणु
	अणु "max98090", MAX98090 पूर्ण,
	अणु "max98091", MAX98091 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max98090_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max98090_of_match[] = अणु
	अणु .compatible = "maxim,max98090", पूर्ण,
	अणु .compatible = "maxim,max98091", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max98090_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id max98090_acpi_match[] = अणु
	अणु "193C9890", MAX98090 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, max98090_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max98090_i2c_driver = अणु
	.driver = अणु
		.name = "max98090",
		.pm = &max98090_pm,
		.of_match_table = of_match_ptr(max98090_of_match),
		.acpi_match_table = ACPI_PTR(max98090_acpi_match),
	पूर्ण,
	.probe  = max98090_i2c_probe,
	.shutकरोwn = max98090_i2c_shutकरोwn,
	.हटाओ = max98090_i2c_हटाओ,
	.id_table = max98090_i2c_id,
पूर्ण;

module_i2c_driver(max98090_i2c_driver);

MODULE_DESCRIPTION("ALSA SoC MAX98090 driver");
MODULE_AUTHOR("Peter Hsiang, Jesse Marroqin, Jerry Wong");
MODULE_LICENSE("GPL");
